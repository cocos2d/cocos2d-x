/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#define LOG_TAG "AudioPlayerProvider"

#include "audio/android/AudioPlayerProvider.h"
#include "audio/android/UrlAudioPlayer.h"
#include "audio/android/PcmAudioPlayer.h"
#include "audio/android/AudioDecoder.h"
#include "audio/android/AudioMixerController.h"
#include "audio/android/PcmAudioService.h"
#include "audio/android/CCThreadPool.h"
#include "audio/android/ICallerThreadUtils.h"
#include "audio/android/utils/Utils.h"

#include <sys/system_properties.h>
#include <stdlib.h>
#include <algorithm> // for std::find_if

namespace cocos2d { namespace experimental {

static int getSystemAPILevel()
{
    static int __systemApiLevel = -1;
    if (__systemApiLevel > 0)
    {
        return __systemApiLevel;
    }

    int apiLevel = getSystemProperty("ro.build.version.sdk");
    if (apiLevel > 0)
    {
        ALOGD("Android API level: %d", apiLevel);
    }
    else
    {
        ALOGE("Fail to get Android API level!");
    }
    __systemApiLevel = apiLevel;
    return apiLevel;
}

struct AudioFileIndicator
{
    std::string extension;
    int smallSizeIndicator;
};

static AudioFileIndicator __audioFileIndicator[] = {
        {"default", 128000}, // If we could not handle the audio format, return default value, the position should be first.
        {".wav",    1024000},
        {".ogg",    128000},
        {".mp3",    160000}
};

AudioPlayerProvider::AudioPlayerProvider(SLEngineItf engineItf, SLObjectItf outputMixObject,
                                         int deviceSampleRate, int bufferSizeInFrames,
                                         const FdGetterCallback &fdGetterCallback,
                                         ICallerThreadUtils* callerThreadUtils)
        : _engineItf(engineItf), _outputMixObject(outputMixObject),
          _deviceSampleRate(deviceSampleRate), _bufferSizeInFrames(bufferSizeInFrames),
          _fdGetterCallback(fdGetterCallback), _callerThreadUtils(callerThreadUtils),
          _pcmAudioService(nullptr), _mixController(nullptr),
          _threadPool(ThreadPool::newCachedThreadPool(1, 8, 5, 2, 2))
{
    ALOGI("deviceSampleRate: %d, bufferSizeInFrames: %d", _deviceSampleRate, _bufferSizeInFrames);
    if (getSystemAPILevel() >= 17)
    {
        _mixController = new (std::nothrow) AudioMixerController(_bufferSizeInFrames, _deviceSampleRate, 2);
        _mixController->init();
        _pcmAudioService = new (std::nothrow) PcmAudioService(engineItf, outputMixObject);
        _pcmAudioService->init(_mixController, 2, deviceSampleRate, bufferSizeInFrames * 2);
    }

    ALOG_ASSERT(callerThreadUtils != nullptr, "Caller thread utils parameter should not be nullptr!");
}

AudioPlayerProvider::~AudioPlayerProvider()
{
    ALOGV("~AudioPlayerProvider()");
    UrlAudioPlayer::stopAll();

    SL_SAFE_DELETE(_pcmAudioService);
    SL_SAFE_DELETE(_mixController);
    SL_SAFE_DELETE(_threadPool);
}

IAudioPlayer *AudioPlayerProvider::getAudioPlayer(const std::string &audioFilePath)
{
    // Pcm data decoding by OpenSLES API only supports in API level 17 and later.
    if (getSystemAPILevel() < 17)
    {
        AudioFileInfo info = getFileInfo(audioFilePath);
        if (info.isValid())
        {
            return createUrlAudioPlayer(info);
        }

        return nullptr;
    }

    IAudioPlayer *player = nullptr;

    _pcmCacheMutex.lock();
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end())
    {// Found pcm cache means it was used to be a PcmAudioService
        PcmData pcmData = iter->second;
        _pcmCacheMutex.unlock();
        player = obtainPcmAudioPlayer(audioFilePath, pcmData);
        ALOGV_IF(player == nullptr, "%s, %d: player is nullptr, path: %s", __FUNCTION__, __LINE__, audioFilePath.c_str());
    }
    else
    {
        _pcmCacheMutex.unlock();
        // Check audio file size to determine to use a PcmAudioService or UrlAudioPlayer,
        // generally PcmAudioService is used for playing short audio like game effects while
        // playing background music uses UrlAudioPlayer
        AudioFileInfo info = getFileInfo(audioFilePath);
        if (info.isValid())
        {
            if (isSmallFile(info))
            {
                // Put an empty lambda to preloadEffect since we only want the future object to get PcmData
                auto pcmData = std::make_shared<PcmData>();
                auto isSucceed = std::make_shared<bool>(false);
                auto isReturnFromCache = std::make_shared<bool>(false);

                std::thread::id threadId = std::this_thread::get_id();

                preloadEffect(info, [&info, threadId, pcmData, isSucceed, isReturnFromCache](bool succeed, PcmData data){
                    // If the callback is in the same thread as caller's, it means that we found it
                    // in the cache
                    *isReturnFromCache = std::this_thread::get_id() == threadId;
                    *pcmData = data;
                    *isSucceed = succeed;
                    ALOGV("FileInfo (%p), Set isSucceed flag: %d, path: %s", &info, succeed, info.url.c_str());
                }, true);

                if (!*isReturnFromCache)
                {
                    std::unique_lock<std::mutex> lk(_preloadWaitMutex);
                    // Wait for 2 seconds for the decoding in sub thread finishes.
                    ALOGV("FileInfo (%p), Waiting preload (%s) to finish ...", &info, audioFilePath.c_str());
                    _preloadWaitCond.wait_for(lk, std::chrono::seconds(2));
                    ALOGV("FileInfo (%p), Waitup preload (%s) ...", &info, audioFilePath.c_str());
                }

                if (*isSucceed)
                {
                    if (pcmData->isValid())
                    {
                        player = obtainPcmAudioPlayer(info.url, *pcmData);
                        ALOGV_IF(player == nullptr, "%s, %d: player is nullptr, path: %s", __FUNCTION__, __LINE__, audioFilePath.c_str());
                    }
                    else
                    {
                        ALOGE("pcm data is invalid, path: %s", audioFilePath.c_str());
                    }
                }
                else
                {
                    ALOGE("FileInfo (%p), preloadEffect (%s) failed", &info, audioFilePath.c_str());
                }
            }
            else
            {
                player = createUrlAudioPlayer(info);
                ALOGV_IF(player == nullptr, "%s, %d: player is nullptr, path: %s", __FUNCTION__, __LINE__, audioFilePath.c_str());
            }
        }
        else
        {
            ALOGE("File info is invalid, path: %s", audioFilePath.c_str());
        }
    }

    ALOGV_IF(player == nullptr, "%s, %d return nullptr", __FUNCTION__, __LINE__);
    return player;
}

void AudioPlayerProvider::preloadEffect(const std::string &audioFilePath, const PreloadCallback& cb)
{
    // Pcm data decoding by OpenSLES API only supports in API level 17 and later.
    if (getSystemAPILevel() < 17)
    {
        PcmData data;
        cb(true, data);
        return;
    }

    {
        std::lock_guard<std::mutex> lk(_pcmCacheMutex);
        auto&& iter = _pcmCache.find(audioFilePath);
        if (iter != _pcmCache.end())
        {
            ALOGV("preload return from cache: (%s)", audioFilePath.c_str());
            cb(true, iter->second);
            return;
        }
    }

    auto info = getFileInfo(audioFilePath);
    preloadEffect(info, [this, cb, audioFilePath](bool succeed, PcmData data){

        _callerThreadUtils->performFunctionInCallerThread([this, succeed, data, cb](){
            cb(succeed, data);
        });

    }, false);
}

// Used internally
void AudioPlayerProvider::preloadEffect(const AudioFileInfo &info, const PreloadCallback& cb, bool isPreloadInPlay2d)
{
    PcmData pcmData;

    if (!info.isValid())
    {
        cb(false, pcmData);
        return;
    }

    if (isSmallFile(info))
    {
        std::string audioFilePath = info.url;

        {
            // 1. First time check, if it wasn't in the cache, goto 2 step
            std::lock_guard<std::mutex> lk(_pcmCacheMutex);
            auto&& iter = _pcmCache.find(audioFilePath);
            if (iter != _pcmCache.end())
            {
                ALOGV("1. Return pcm data from cache, url: %s", info.url.c_str());
                cb(true, iter->second);
                return;
            }
        }

        {
            // 2. Check whether the audio file is being preloaded, if it has been removed from map just now,
            // goto step 3
            std::lock_guard<std::mutex> lk(_preloadCallbackMutex);

            auto&& preloadIter = _preloadCallbackMap.find(audioFilePath);
            if (preloadIter != _preloadCallbackMap.end())
            {
                ALOGV("audio (%s) is being preloaded, add to callback vector!", audioFilePath.c_str());
                PreloadCallbackParam param;
                param.callback = cb;
                preloadIter->second.push_back(std::move(param));
                return;
            }

            {   // 3. Check it in cache again. If it has been removed from map just now, the file is in
                // the cache absolutely.
                std::lock_guard<std::mutex> lk2(_pcmCacheMutex);
                auto&& iter = _pcmCache.find(audioFilePath);
                if (iter != _pcmCache.end())
                {
                    ALOGV("2. Return pcm data from cache, url: %s", info.url.c_str());
                    cb(true, iter->second);
                    return;
                }
            }

            PreloadCallbackParam param;
            param.callback = cb;
            std::vector<PreloadCallbackParam> callbacks;
            callbacks.push_back(std::move(param));
            _preloadCallbackMap.insert(std::make_pair(audioFilePath, std::move(callbacks)));
        }

        _threadPool->pushTask([this, audioFilePath, isPreloadInPlay2d](int tid) {
            ALOGV("AudioPlayerProvider::preloadEffect: (%s)", audioFilePath.c_str());
            PcmData d;
            AudioDecoder decoder(_engineItf, audioFilePath, _bufferSizeInFrames, _deviceSampleRate, _fdGetterCallback);
            bool ret = decoder.start();
            if (ret)
            {
                d = decoder.getResult();
                std::lock_guard<std::mutex> lk(_pcmCacheMutex);
                _pcmCache.insert(std::make_pair(audioFilePath, d));
            }
            else
            {
                ALOGE("decode (%s) failed!", audioFilePath.c_str());
            }

            ALOGV("decode succeed.");
            std::lock_guard<std::mutex> lk(_preloadCallbackMutex);
            auto&& preloadIter = _preloadCallbackMap.find(audioFilePath);
            if (preloadIter != _preloadCallbackMap.end())
            {
                auto&& params = preloadIter->second;
                ALOGV("preload (%s) callback count: %d", audioFilePath.c_str(), params.size());
                PcmData result = decoder.getResult();
                for (auto&& param : params)
                {
                    param.callback(ret, result);
                }
                _preloadCallbackMap.erase(preloadIter);

                if (isPreloadInPlay2d)
                {
                    _preloadWaitCond.notify_one();
                }
            }
        });
    }
    else
    {
        ALOGV("File (%s) is too large, ignore preload!", info.url.c_str());
        cb(true, pcmData);
    }
}

AudioPlayerProvider::AudioFileInfo AudioPlayerProvider::getFileInfo(
        const std::string &audioFilePath)
{
    AudioFileInfo info;
    long fileSize = 0;
    off_t start = 0, length = 0;
    int assetFd = 0;

    if (audioFilePath[0] != '/')
    {
        std::string relativePath;
        size_t position = audioFilePath.find("assets/");

        if (0 == position)
        {
            // "assets/" is at the beginning of the path and we don't want it
            relativePath = audioFilePath.substr(strlen("assets/"));
        }
        else
        {
            relativePath = audioFilePath;
        }

        assetFd = _fdGetterCallback(relativePath, &start, &length);

        if (assetFd <= 0)
        {
            ALOGE("Failed to open file descriptor for '%s'", audioFilePath.c_str());
            return info;
        }

        fileSize = length;
    }
    else
    {
        FILE *fp = fopen(audioFilePath.c_str(), "rb");
        if (fp != nullptr)
        {
            fseek(fp, 0, SEEK_END);
            fileSize = ftell(fp);
            fclose(fp);
        }
        else
        {
            return info;
        }
    }

    info.url = audioFilePath;
    info.assetFd = std::make_shared<AssetFd>(assetFd);
    info.start = start;
    info.length = fileSize;

    ALOGV("(%s) file size: %ld", audioFilePath.c_str(), fileSize);

    return info;
}

bool AudioPlayerProvider::isSmallFile(const AudioFileInfo &info)
{
    //TODO: If file size is smaller than 100k, we think it's a small file. This value should be set by developers.
    AudioFileInfo &audioFileInfo = const_cast<AudioFileInfo &>(info);
    size_t judgeCount = sizeof(__audioFileIndicator) / sizeof(__audioFileIndicator[0]);
    size_t pos = audioFileInfo.url.rfind(".");
    std::string extension;
    if (pos != std::string::npos)
    {
        extension = audioFileInfo.url.substr(pos);
    }
    auto iter = std::find_if(std::begin(__audioFileIndicator), std::end(__audioFileIndicator),
                             [&extension](const AudioFileIndicator &judge) -> bool {
                                 return judge.extension == extension;
                             });

    if (iter != std::end(__audioFileIndicator))
    {
//        ALOGV("isSmallFile: found: %s: ", iter->extension.c_str());
        return info.length < iter->smallSizeIndicator;
    }

//    ALOGV("isSmallFile: not found return default value");
    return info.length < __audioFileIndicator[0].smallSizeIndicator;
}

void AudioPlayerProvider::clearPcmCache(const std::string &audioFilePath)
{
    std::lock_guard<std::mutex> lk(_pcmCacheMutex);
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end())
    {
        ALOGV("clear pcm cache: (%s)", audioFilePath.c_str());
        _pcmCache.erase(iter);
    }
    else
    {
        ALOGW("Couldn't find the pcm cache: (%s)", audioFilePath.c_str());
    }
}

void AudioPlayerProvider::clearAllPcmCaches()
{
    std::lock_guard<std::mutex> lk(_pcmCacheMutex);
    _pcmCache.clear();
}

PcmAudioPlayer *AudioPlayerProvider::obtainPcmAudioPlayer(const std::string &url,
                                                           const PcmData &pcmData)
{
    PcmAudioPlayer *pcmPlayer = nullptr;
    if (pcmData.isValid())
    {
        pcmPlayer = new(std::nothrow) PcmAudioPlayer(_mixController, _callerThreadUtils);
        if (pcmPlayer != nullptr)
        {
            pcmPlayer->prepare(url, pcmData);
        }
    }
    else
    {
        ALOGE("obtainPcmAudioPlayer failed, pcmData isn't valid!");
    }
    return pcmPlayer;
}

UrlAudioPlayer *AudioPlayerProvider::createUrlAudioPlayer(
        const AudioPlayerProvider::AudioFileInfo &info)
{
    if (info.url.empty())
    {
        ALOGE("createUrlAudioPlayer failed, url is empty!");
        return nullptr;
    }

    SLuint32 locatorType = info.assetFd > 0 ? SL_DATALOCATOR_ANDROIDFD : SL_DATALOCATOR_URI;
    auto urlPlayer = new (std::nothrow) UrlAudioPlayer(_engineItf, _outputMixObject, _callerThreadUtils);
    bool ret = urlPlayer->prepare(info.url, locatorType, info.assetFd, info.start, info.length);
    if (!ret)
    {
        SL_SAFE_DELETE(urlPlayer);
    }
    return urlPlayer;
}

void AudioPlayerProvider::pause()
{
    if (_mixController != nullptr)
    {
        _mixController->pause();
    }

    if (_pcmAudioService != nullptr)
    {
        _pcmAudioService->pause();
    }
}

void AudioPlayerProvider::resume()
{
    if (_mixController != nullptr)
    {
        _mixController->resume();
    }

    if (_pcmAudioService != nullptr)
    {
        _pcmAudioService->resume();
    }
}

}} // namespace cocos2d { namespace experimental {
