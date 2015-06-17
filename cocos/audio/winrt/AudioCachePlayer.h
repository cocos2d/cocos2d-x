/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT

#ifndef __AUDIO_CACHE_PLAYER_H_
#define __AUDIO_CACHE_PLAYER_H_

#include "AudioSourceReader.h"

NS_CC_BEGIN
namespace experimental{

typedef struct AudioInfo
{
    size_t _totalAudioBytes;
    WAVEFORMATEX _wfx;
} AudioInfo;

enum class AudioPlayerState
{
    ERRORED = -1,
    INITIALZING,
    READY,
    PLAYING,
    PAUSED,
    STOPPED
};

 class AudioCache
{
public:
    AudioCache();
    ~AudioCache();

    void readDataTask();
    void addCallback(const std::function<void()> &callback);
    bool getChunk(AudioDataChunk& chunk);
    void doBuffering();
    bool isStreamingSource();
    void seek(const float ratio);

protected:
    void invokeCallbacks();
    
private:
    AudioCache(const AudioCache&);
    AudioCache& operator=(const AudioCache&); 

private:
    bool _retry;
    bool _isReady;
    AudioInfo _audInfo;
    std::mutex _cbMutex;
    FileFormat _fileFormat;
    std::string _fileFullPath;
    AudioSourceReader *_srcReader;
    std::vector<std::function<void()>> _callbacks;


    friend class AudioPlayer;
    friend class AudioEngineImpl;
 };


 class AudioPlayer : public IXAudio2EngineCallback, IXAudio2VoiceCallback
 {
 public:
     AudioPlayer();
     virtual ~AudioPlayer();

     void stop();
     void pause();
     bool update();
     void resume();
     bool isInError();
     float getDuration();
     float getCurrentTime();
     bool setTime(float time);
     void setVolume(float volume);
     bool play2d(AudioCache* cache);
     AudioPlayerState getState() { return _state; }

 protected:
     AudioPlayer(AudioPlayer&);
     AudioPlayer& operator=(AudioPlayer&);
     
     void init();
     void free();
     void error();
     void popBuffer();
     void updateState();
     bool submitBuffers();
     void onBufferRunOut();
     void invokeFinishCallback();
     void _stop(bool pause = false);
     bool _play(bool resume = false);
     XAUDIO2_VOICE_STATE getSourceVoiceState(bool fast = false);

     // IXAudio2EngineCallback
     STDMETHOD_(void, OnProcessingPassStart) () override;
     STDMETHOD_(void, OnProcessingPassEnd) () override;
     STDMETHOD_(void, OnCriticalError) (HRESULT error) override;

     // IXAudio2VoiceCallback
     STDMETHOD_(void, OnVoiceProcessingPassStart) (UINT32 uBytesRequired) override;
     STDMETHOD_(void, OnVoiceProcessingPassEnd) () override;
     STDMETHOD_(void, OnStreamEnd) () override;
     STDMETHOD_(void, OnBufferStart) (void* pBufferContext) override;
     STDMETHOD_(void, OnBufferEnd) (void* pBufferContext) override;
     STDMETHOD_(void, OnLoopEnd) (void* pBufferContext) override;
     STDMETHOD_(void, OnVoiceError) (void *pBufferContext, HRESULT error) override;

 private:
     bool _loop;
     bool _ready;
     float _volume;
     float _current;
     float _duration;
     bool _criticalError;
     bool _isStreaming;
     UINT64 _totalSamples;
     UINT64 _samplesOffset;
     
     XAUDIO2_BUFFER _xaBuffer;
     IXAudio2SourceVoice *_xaSourceVoice;
     IXAudio2MasteringVoice *_xaMasterVoice;
     Microsoft::WRL::ComPtr<IXAudio2> _xaEngine;

     AudioCache *_cache;
     std::mutex _stMutex;
     std::mutex _bqMutex;
     AudioPlayerState _state;
     std::queue<AudioDataChunk> _cachedBufferQ;
     std::function<void(int, const std::string &)> _finishCallback;
     

     friend class AudioEngineImpl;
 };

}
NS_CC_END
#endif // __AUDIO_CACHE_PLAYER_H_
#endif

