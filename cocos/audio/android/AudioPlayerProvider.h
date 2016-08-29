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

#pragma once

#include "audio/android/IAudioPlayer.h"
#include "audio/android/OpenSLHelper.h"
#include "audio/android/PcmData.h"

#include <unordered_map>
#include <memory>
#include <condition_variable>

namespace cocos2d { namespace experimental {
// Manage PcmAudioPlayer& UrlAudioPlayer

class PcmAudioPlayer;
class PcmAudioService;
class UrlAudioPlayer;
class AudioMixerController;
class ICallerThreadUtils;
class AssetFd;
class ThreadPool;

class AudioPlayerProvider
{
public:
    AudioPlayerProvider(SLEngineItf engineItf, SLObjectItf outputMixObject, int deviceSampleRate,
                        int bufferSizeInFrames, const FdGetterCallback &fdGetterCallback,
                        ICallerThreadUtils* callerThreadUtils);

    virtual ~AudioPlayerProvider();

    IAudioPlayer *getAudioPlayer(const std::string &audioFilePath);

    typedef std::function<void(bool/* succeed */, PcmData /* data */)> PreloadCallback;
    void preloadEffect(const std::string &audioFilePath, const PreloadCallback& cb);

    void clearPcmCache(const std::string &audioFilePath);

    void clearAllPcmCaches();

    void pause();

    void resume();

private:

    struct AudioFileInfo
    {
        std::string url;
        std::shared_ptr<AssetFd> assetFd;
        off_t start;
        off_t length;

        AudioFileInfo()
                : assetFd(nullptr), start(0), length(0)
        { };

        inline bool isValid() const
        {
            return !url.empty() && length > 0;
        }
    };

    PcmAudioPlayer *obtainPcmAudioPlayer(const std::string &url, const PcmData &pcmData);

    UrlAudioPlayer *createUrlAudioPlayer(const AudioFileInfo &info);

    void preloadEffect(const AudioFileInfo &info, const PreloadCallback& cb, bool isPreloadInPlay2d);

    AudioFileInfo getFileInfo(const std::string &audioFilePath);

    bool isSmallFile(const AudioFileInfo &info);

private:
    SLEngineItf _engineItf;
    SLObjectItf _outputMixObject;
    int _deviceSampleRate;
    int _bufferSizeInFrames;
    FdGetterCallback _fdGetterCallback;
    ICallerThreadUtils* _callerThreadUtils;

    std::unordered_map<std::string, PcmData> _pcmCache;
    std::mutex _pcmCacheMutex;

    struct PreloadCallbackParam
    {
        PreloadCallback callback;
    };

    std::unordered_map<std::string, std::vector<PreloadCallbackParam>> _preloadCallbackMap;
    std::mutex _preloadCallbackMutex;

    std::mutex _preloadWaitMutex;
    std::condition_variable _preloadWaitCond;

    PcmAudioService* _pcmAudioService;
    AudioMixerController *_mixController;

    ThreadPool* _threadPool;
};

}} // namespace cocos2d { namespace experimental {

