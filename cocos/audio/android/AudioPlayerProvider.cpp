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
#include "audio/android/AssetFd.h"

#include <sys/system_properties.h>
#include <stdlib.h>
#include <algorithm> // for std::find_if

namespace cocos2d {

static int getSystemAPILevel()
{
    static int __systemApiLevel = -1;
    if (__systemApiLevel > 0)
    {
        return __systemApiLevel;
    }

    int apiLevel = -1;
    char sdk_ver_str[PROP_VALUE_MAX] = {0};
    auto len = __system_property_get("ro.build.version.sdk", sdk_ver_str);
    if (len > 0)
    {
        apiLevel = atoi(sdk_ver_str);
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
          _pcmAudioService(nullptr), _mixController(nullptr)
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

    PcmData pcmData;
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end())
    {// Found pcm cache means it was used to be a PcmAudioService
        pcmData = iter->second;
        player = obtainPcmAudioPlayer(audioFilePath, pcmData);
    }
    else
    {
        // Check audio file size to determine to use a PcmAudioService or UrlAudioPlayer,
        // generally PcmAudioService is used for playing short audio like game effects while
        // playing background music uses UrlAudioPlayer
        AudioFileInfo info = getFileInfo(audioFilePath);
        if (info.isValid())
        {
            if (isSmallFile(info))
            {
                pcmData = preloadEffect(info);
                player = obtainPcmAudioPlayer(info.url, pcmData);
                if (player == nullptr)
                {
                    ALOGV("2, PcmAudioPlayerPool is full, use an UrlAudioPlayer to play instead!");
                    player = createUrlAudioPlayer(info);
                }
            }
            else
            {
                player = createUrlAudioPlayer(info);
            }
        }
    }

    return player;
}

PcmData AudioPlayerProvider::preloadEffect(const std::string &audioFilePath)
{
    auto info = getFileInfo(audioFilePath);
    return preloadEffect(info);
}

PcmData AudioPlayerProvider::preloadEffect(const AudioFileInfo &info)
{
    PcmData pcmData;
    // Pcm data decoding by OpenSLES API only supports in API level 17 and later.
    if (getSystemAPILevel() < 17)
    {
        return pcmData;
    }

    if (!info.isValid())
    {
        return pcmData;
    }

    std::string audioFilePath = info.url;
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end())
    {
        ALOGV("Return pcm data from cache, url: %s", info.url.c_str());
        return iter->second;
    }

    if (isSmallFile(info))
    {
        ALOGV("AudioPlayerProvider::preloadEffect: %s", audioFilePath.c_str());
        AudioDecoder decoder(_engineItf, audioFilePath, _deviceSampleRate);
        if (decoder.start(_fdGetterCallback))
        {
            pcmData = decoder.getResult();
            _pcmCache.insert(std::make_pair(audioFilePath, pcmData));
        }
        else
        {
            ALOGE("decode (%s) failed!", audioFilePath.c_str());
        }
    }
    else
    {
        ALOGV("File (%s) is too large, ignore preload!", audioFilePath.c_str());
    }
    return pcmData;
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
    auto iter = _pcmCache.find(audioFilePath);
    if (iter != _pcmCache.end())
    {
        _pcmCache.erase(iter);
    }
}

void AudioPlayerProvider::clearAllPcmCaches()
{
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

} // namespace cocos2d {
