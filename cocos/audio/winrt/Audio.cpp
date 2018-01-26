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

#include "audio/winrt/Audio.h"
#include "platform/CCCommon.h"
#include "audio/winrt/AudioSourceReader.h"

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        // Set a breakpoint on this line to catch DX API errors.
        throw Platform::Exception::CreateException(hr);
    }
}

void AudioEngineCallbacks::Initialize(Audio *audio)
{
    m_audio = audio;
}

// Called in the event of a critical system error which requires XAudio2
// to be closed down and restarted.  The error code is given in error.
void  _stdcall AudioEngineCallbacks::OnCriticalError(HRESULT Error)
{
    UNUSED_PARAM(Error);
    m_audio->SetEngineExperiencedCriticalError();
};

Audio::Audio() :
    m_backgroundID(0),
	m_soundEffctVolume(1.0f),
	m_backgroundMusicVolume(1.0f)
{
}

void Audio::Initialize()
{
    m_engineExperiencedCriticalError = false;

	m_musicEngine = nullptr;
	m_soundEffectEngine = nullptr;
	m_musicMasteringVoice = nullptr;
	m_soundEffectMasteringVoice = nullptr;
}

void Audio::CreateResources()
{
    do
    {	
        if (FAILED(XAudio2Create(&m_musicEngine)))
        {
            m_engineExperiencedCriticalError = true;
            break;
        }

#if defined(_DEBUG)
        XAUDIO2_DEBUG_CONFIGURATION debugConfig = {0};
        debugConfig.BreakMask = XAUDIO2_LOG_ERRORS;
        debugConfig.TraceMask = XAUDIO2_LOG_ERRORS;
        m_musicEngine->SetDebugConfiguration(&debugConfig);
#endif

        m_musicEngineCallback.Initialize(this);
        m_musicEngine->RegisterForCallbacks(&m_musicEngineCallback);

	    // This sample plays the equivalent of background music, which we tag on the mastering voice as AudioCategory_GameMedia.
	    // In ordinary usage, if we were playing the music track with no effects, we could route it entirely through
	    // Media Foundation. Here we are using XAudio2 to apply a reverb effect to the music, so we use Media Foundation to
	    // decode the data then we feed it through the XAudio2 pipeline as a separate Mastering Voice, so that we can tag it
	    // as Game Media.
        // We default the mastering voice to 2 channels to simplify the reverb logic.
        if(FAILED(m_musicEngine->CreateMasteringVoice(&m_musicMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameMedia)))
        {
            m_engineExperiencedCriticalError = true;
            break;
        }

        // Create a separate engine and mastering voice for sound effects in the sample
	    // Games will use many voices in a complex graph for audio, mixing all effects down to a
	    // single mastering voice.
	    // We are creating an entirely new engine instance and mastering voice in order to tag
	    // our sound effects with the audio category AudioCategory_GameEffects.
        if(FAILED(XAudio2Create(&m_soundEffectEngine)))
        {
            m_engineExperiencedCriticalError = true;
            break;
        }
    
        m_soundEffectEngineCallback.Initialize(this);
        m_soundEffectEngine->RegisterForCallbacks(&m_soundEffectEngineCallback);

        // We default the mastering voice to 2 channels to simplify the reverb logic.
        if(FAILED(m_soundEffectEngine->CreateMasteringVoice(&m_soundEffectMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameEffects)))
        {
            m_engineExperiencedCriticalError = true;
            break;
        }
    } while (false);
}

unsigned int Audio::Hash(const char *key)
{
    unsigned int len = static_cast<unsigned int>(strlen(key));
    const char *end=key+len;
    unsigned int hash;

    for (hash = 0; key < end; key++)
    {
        hash *= 16777619;
        hash ^= (unsigned int) (unsigned char) toupper(*key);
    }
    return (hash);
}

void Audio::ReleaseResources()
{
	if (m_musicMasteringVoice != nullptr) 
    {
        m_musicMasteringVoice->DestroyVoice();
        m_musicMasteringVoice = nullptr;
    }
	if (m_soundEffectMasteringVoice != nullptr) 
    {
        m_soundEffectMasteringVoice->DestroyVoice();
        m_soundEffectMasteringVoice = nullptr;
    }

    for (auto& EffectIter : m_soundEffects)
	{
        if (EffectIter.second.m_soundEffectSourceVoice != nullptr)
        {
            EffectIter.second.m_soundEffectSourceVoice->DestroyVoice();
            EffectIter.second.m_soundEffectSourceVoice = nullptr;
        }
	}
    m_soundEffects.clear();

    m_musicEngine = nullptr;
    m_soundEffectEngine = nullptr;
}

void Audio::Start()
{	 
    if (m_engineExperiencedCriticalError)
    {
        return;
    }

    if (! m_backgroundFile.empty())
        PlayBackgroundMusic(m_backgroundFile.c_str(), m_backgroundLoop);
}

// This sample processes audio buffers during the render cycle of the application.
// As long as the sample maintains a high-enough frame rate, this approach should
// not glitch audio. In game code, it is best for audio buffers to be processed
// on a separate thread that is not synced to the main render loop of the game.
void Audio::Render()
{
    if (m_engineExperiencedCriticalError)
    {
        ReleaseResources();
        Initialize();
        CreateResources();
        Start();
        if (m_engineExperiencedCriticalError)
        {
            return;
        }
    }
}

void Audio::PlayBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    m_backgroundFile = pszFilePath;
    m_backgroundLoop = bLoop;

    if (m_engineExperiencedCriticalError) {
        return;
    }

    StopBackgroundMusic(true);
    PlaySoundEffect(pszFilePath, bLoop, m_backgroundID, true);
}

void Audio::StopBackgroundMusic(bool bReleaseData)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    StopSoundEffect(m_backgroundID);

    if (bReleaseData){
        UnloadSoundEffect(m_backgroundID);
        RemoveFromList(m_backgroundID);
    }
}

void Audio::PauseBackgroundMusic()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    PauseSoundEffect(m_backgroundID);
}

void Audio::ResumeBackgroundMusic()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    ResumeSoundEffect(m_backgroundID);
}

void Audio::RewindBackgroundMusic()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    RewindSoundEffect(m_backgroundID);
}

bool Audio::IsBackgroundMusicPlaying()
{
    return IsSoundEffectStarted(m_backgroundID) && !IsSoundEffectPaused(m_backgroundID);
}

void Audio::SetBackgroundVolume(float volume)
{
    m_backgroundMusicVolume = volume;

    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() != m_soundEffects.find(m_backgroundID))
    {
        m_soundEffects[m_backgroundID].m_soundEffectSourceVoice->SetVolume(volume);
    }
}

float Audio::GetBackgroundVolume()
{
    return m_backgroundMusicVolume;
}

void Audio::SetSoundEffectVolume(float volume)
{
    m_soundEffctVolume = volume;

    if (m_engineExperiencedCriticalError) {
        return;
    }

	for (auto& iter : m_soundEffects)
	{
        if (iter.first != m_backgroundID)
            iter.second.m_soundEffectSourceVoice->SetVolume(m_soundEffctVolume);
	}
}

float Audio::GetSoundEffectVolume()
{
    return m_soundEffctVolume;
}

void Audio::PlaySoundEffect(const char* pszFilePath, bool bLoop, unsigned int& sound, bool isMusic)
{
    sound = Hash(pszFilePath);

    if (m_soundEffects.end() == m_soundEffects.find(sound))
    {
        PreloadSoundEffect(pszFilePath, isMusic);
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    m_soundEffects[sound].m_audioBuffer.LoopCount = bLoop ? XAUDIO2_LOOP_INFINITE : 0;

    PlaySoundEffect(sound);
}

void Audio::PlaySoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    StopSoundEffect(sound);

    if (FAILED(m_soundEffects[sound].m_soundEffectSourceVoice->SubmitSourceBuffer(&m_soundEffects[sound].m_audioBuffer)))
    {
        m_engineExperiencedCriticalError = true;
    }

    if (m_engineExperiencedCriticalError) {
        // If there's an error, then we'll recreate the engine on the next render pass
        return;
    }

	SoundEffectData* soundEffect = &m_soundEffects[sound];
	HRESULT hr = soundEffect->m_soundEffectSourceVoice->Start();
	if FAILED(hr)
    {
        m_engineExperiencedCriticalError = true;
        return;
    }

    m_soundEffects[sound].m_soundEffectStarted = true;
    m_soundEffects[sound].m_soundEffectPaused = false;
}

void Audio::StopSoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    HRESULT hr = m_soundEffects[sound].m_soundEffectSourceVoice->Stop();
    HRESULT hr1 = m_soundEffects[sound].m_soundEffectSourceVoice->FlushSourceBuffers();
    if (FAILED(hr) || FAILED(hr1))
    {
        // If there's an error, then we'll recreate the engine on the next render pass
        m_engineExperiencedCriticalError = true;
        return;
    }

    m_soundEffects[sound].m_soundEffectStarted = false;
    m_soundEffects[sound].m_soundEffectPaused = false;
}

void Audio::PauseSoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    HRESULT hr = m_soundEffects[sound].m_soundEffectSourceVoice->Stop();
    if FAILED(hr)
    {
        // If there's an error, then we'll recreate the engine on the next render pass
        m_engineExperiencedCriticalError = true;
        return;
    }
    m_soundEffects[sound].m_soundEffectPaused = true;
}

void Audio::ResumeSoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    HRESULT hr = m_soundEffects[sound].m_soundEffectSourceVoice->Start();
    if FAILED(hr)
    {
        // If there's an error, then we'll recreate the engine on the next render pass
        m_engineExperiencedCriticalError = true;
        return;
    }
    m_soundEffects[sound].m_soundEffectPaused = false;
}

void Audio::RewindSoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    StopSoundEffect(sound);
    PlaySoundEffect(sound);
}

void Audio::PauseAllSoundEffects()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

	for (auto& iter : m_soundEffects)
	{
        if (iter.first != m_backgroundID)
            PauseSoundEffect(iter.first);
	}
}

void Audio::ResumeAllSoundEffects()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

	for (auto& iter : m_soundEffects)
	{
        if (iter.first != m_backgroundID)
            ResumeSoundEffect(iter.first);
	}
}

void Audio::StopAllSoundEffects(bool bReleaseData)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    EffectList::iterator iter;
	for (iter = m_soundEffects.begin(); iter != m_soundEffects.end(); iter++)
	{
        if (iter->first != m_backgroundID){
            StopSoundEffect(iter->first);
            if (bReleaseData)
            {
                UnloadSoundEffect(iter->first);  
            }            
        }
	}
    if (bReleaseData)
    {
        for (iter = m_soundEffects.begin(); iter != m_soundEffects.end();)
        {
            if (iter->first != m_backgroundID){                
                m_soundEffects.erase(iter++);
            }
            else
            {
                iter++;
            }
        }
    }  
}

bool Audio::IsSoundEffectStarted(unsigned int sound)
{
    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return false;

    return m_soundEffects[sound].m_soundEffectStarted;
}

bool Audio::IsSoundEffectPaused(unsigned int sound)
{
    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return false;

    return m_soundEffects[sound].m_soundEffectPaused;
}

void Audio::PreloadSoundEffect(const char* pszFilePath, bool isMusic)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    int sound = Hash(pszFilePath);

    std::unique_ptr<cocos2d::experimental::AudioSourceReader> reader = std::make_unique<cocos2d::experimental::MP3Reader>();

    if (!reader) {
        return;
    }

    static_cast<cocos2d::experimental::MP3Reader*>(reader.get())->doLargeFileSupport(false);

    if (!reader->initialize(pszFilePath)) {
        return;
    }

    m_soundEffects[sound].m_soundID = sound;
    size_t bufferLength = reader->getTotalAudioBytes();
    WAVEFORMATEX wfx = reader->getWaveFormatInfo();

    cocos2d::experimental::AudioDataChunk chunk;
    if (!reader->consumeChunk(chunk)) {
        return;
    }

    m_soundEffects[sound].m_soundEffectBufferData = new (std::nothrow) BYTE[chunk._dataSize];
    if (nullptr == m_soundEffects[sound].m_soundEffectBufferData) {
        return;
    }

    m_soundEffects[sound].m_soundEffectBufferLength = chunk._dataSize;
    CopyMemory(m_soundEffects[sound].m_soundEffectBufferData, chunk._data->data(), chunk._dataSize);

    if (isMusic)
    {
        XAUDIO2_SEND_DESCRIPTOR descriptors[1];
	    descriptors[0].pOutputVoice = m_musicMasteringVoice;
	    descriptors[0].Flags = 0;
	    XAUDIO2_VOICE_SENDS sends = {0};
	    sends.SendCount = 1;
	    sends.pSends = descriptors;

        if (FAILED(m_musicEngine->CreateSourceVoice(&m_soundEffects[sound].m_soundEffectSourceVoice,
            &wfx, 0, 1.0f, &m_voiceContext, &sends)))
        {
            m_engineExperiencedCriticalError = true;
        }
		//fix bug: set a initial volume
		m_soundEffects[sound].m_soundEffectSourceVoice->SetVolume(m_backgroundMusicVolume);
    } else
    {
        XAUDIO2_SEND_DESCRIPTOR descriptors[1];
        descriptors[0].pOutputVoice = m_soundEffectMasteringVoice;
	    descriptors[0].Flags = 0;
	    XAUDIO2_VOICE_SENDS sends = {0};
	    sends.SendCount = 1;
	    sends.pSends = descriptors;

        if(FAILED(m_soundEffectEngine->CreateSourceVoice(&m_soundEffects[sound].m_soundEffectSourceVoice,
            &wfx, 0, 1.0f, &m_voiceContext, &sends, nullptr)))
        {
            m_engineExperiencedCriticalError = true;
        }
		//fix bug: set a initial volume
		m_soundEffects[sound].m_soundEffectSourceVoice->SetVolume(m_soundEffctVolume);
    }

	m_soundEffects[sound].m_soundEffectSampleRate = wfx.nSamplesPerSec;

	// Queue in-memory buffer for playback
	ZeroMemory(&m_soundEffects[sound].m_audioBuffer, sizeof(m_soundEffects[sound].m_audioBuffer));

	m_soundEffects[sound].m_audioBuffer.AudioBytes = static_cast<UINT32>(m_soundEffects[sound].m_soundEffectBufferLength);
	m_soundEffects[sound].m_audioBuffer.pAudioData = m_soundEffects[sound].m_soundEffectBufferData;
	m_soundEffects[sound].m_audioBuffer.pContext = &m_soundEffects[sound];
	m_soundEffects[sound].m_audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
    m_soundEffects[sound].m_audioBuffer.LoopCount = 0;
}

void Audio::UnloadSoundEffect(const char* pszFilePath)
{
    int sound = Hash(pszFilePath);

    UnloadSoundEffect(sound);

    RemoveFromList(sound);
}

void Audio::UnloadSoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    m_soundEffects[sound].m_soundEffectSourceVoice->DestroyVoice();

    if(m_soundEffects[sound].m_soundEffectBufferData)
        delete [] m_soundEffects[sound].m_soundEffectBufferData;

    m_soundEffects[sound].m_soundEffectBufferData = nullptr;
	m_soundEffects[sound].m_soundEffectSourceVoice = nullptr;
	m_soundEffects[sound].m_soundEffectStarted = false;
    m_soundEffects[sound].m_soundEffectPaused = false;
    ZeroMemory(&m_soundEffects[sound].m_audioBuffer, sizeof(m_soundEffects[sound].m_audioBuffer));    
}

void Audio::RemoveFromList( unsigned int sound )
{
    m_soundEffects.erase(sound);
}


