//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "Audio.h"
#include "MediaStreamer.h"

static std::wstring CCUtf8ToUnicode(const char * pszUtf8Str, unsigned len/* = -1*/)
{
    std::wstring ret;
    do
    {
        if (! pszUtf8Str) break;
		// get UTF8 string length
		if (-1 == len)
		{
			len = strlen(pszUtf8Str);
		}
        if (len <= 0) break;

		// get UTF16 string length
		int wLen = MultiByteToWideChar(CP_UTF8, 0, pszUtf8Str, len, 0, 0);
		if (0 == wLen || 0xFFFD == wLen) break;
		
		// convert string  
        wchar_t * pwszStr = new wchar_t[wLen + 1];
        if (! pwszStr) break;
        pwszStr[wLen] = 0;
        MultiByteToWideChar(CP_UTF8, 0, pszUtf8Str, len, pwszStr, wLen + 1);
        ret = pwszStr;
		if(pwszStr) { delete[] (pwszStr);};
    } while (0);
    return ret;
}

static inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        // Set a breakpoint on this line to catch DirectX API errors
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
    m_audio->SetEngineExperiencedCriticalError();
};

Audio::Audio() :
    m_backgroundID(0),
    m_soundEffctVolume(1.0),
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
    try
    {	
        ThrowIfFailed(
            XAudio2Create(&m_musicEngine)
            );

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
	    ThrowIfFailed(
		    m_musicEngine->CreateMasteringVoice(&m_musicMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameMedia)
        );

        // Create a separate engine and mastering voice for sound effects in the sample
	    // Games will use many voices in a complex graph for audio, mixing all effects down to a
	    // single mastering voice.
	    // We are creating an entirely new engine instance and mastering voice in order to tag
	    // our sound effects with the audio category AudioCategory_GameEffects.
	    ThrowIfFailed(
		    XAudio2Create(&m_soundEffectEngine)
		    );
    
        m_soundEffectEngineCallback.Initialize(this);
        m_soundEffectEngine->RegisterForCallbacks(&m_soundEffectEngineCallback);

        // We default the mastering voice to 2 channels to simplify the reverb logic.
	    ThrowIfFailed(
		    m_soundEffectEngine->CreateMasteringVoice(&m_soundEffectMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, nullptr, nullptr, AudioCategory_GameEffects)
		    );
    }
    catch (...)
    {
        m_engineExperiencedCriticalError = true;
    }
}

unsigned int Audio::Hash(const char *key)
{
    unsigned int len = strlen(key);
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

    EffectList::iterator EffectIter = m_soundEffects.begin();
    for (; EffectIter != m_soundEffects.end(); EffectIter++)
	{
        if (EffectIter->second.m_soundEffectSourceVoice != nullptr) 
        {
            EffectIter->second.m_soundEffectSourceVoice->DestroyVoice();
            EffectIter->second.m_soundEffectSourceVoice = nullptr;
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

    if (bReleaseData)
        UnloadSoundEffect(m_backgroundID);
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
    return IsSoundEffectStarted(m_backgroundID);
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

    EffectList::iterator iter;
	for (iter = m_soundEffects.begin(); iter != m_soundEffects.end(); iter++)
	{
        if (iter->first != m_backgroundID)
            iter->second.m_soundEffectSourceVoice->SetVolume(m_soundEffctVolume);
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

    ThrowIfFailed(
		m_soundEffects[sound].m_soundEffectSourceVoice->SubmitSourceBuffer(&m_soundEffects[sound].m_audioBuffer)
		);

	XAUDIO2_BUFFER buf = {0};
	XAUDIO2_VOICE_STATE state = {0};

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

    EffectList::iterator iter;
	for (iter = m_soundEffects.begin(); iter != m_soundEffects.end(); iter++)
	{
        PauseSoundEffect(iter->first);
	}
}

void Audio::ResumeAllSoundEffects()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    EffectList::iterator iter;
	for (iter = m_soundEffects.begin(); iter != m_soundEffects.end(); iter++)
	{
        ResumeSoundEffect(iter->first);
	}
}

void Audio::StopAllSoundEffects()
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    EffectList::iterator iter;
	for (iter = m_soundEffects.begin(); iter != m_soundEffects.end(); iter++)
	{
        StopSoundEffect(iter->first);
	}
}

bool Audio::IsSoundEffectStarted(unsigned int sound)
{
    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return false;

    return m_soundEffects[sound].m_soundEffectStarted;
}

void Audio::PreloadSoundEffect(const char* pszFilePath, bool isMusic)
{

    if (m_engineExperiencedCriticalError) {
        return;
    }

    int sound = Hash(pszFilePath);

	if (m_soundEffects.end() != m_soundEffects.find(sound))
    {
       return;
    }

	MediaStreamer mediaStreamer;
	mediaStreamer.Initialize(CCUtf8ToUnicode(pszFilePath, -1).c_str());
	m_soundEffects[sound].m_soundID = sound;	
	
	uint32 bufferLength = mediaStreamer.GetMaxStreamLengthInBytes();

	if (m_soundEffects.find(sound) != m_soundEffects.end())
	{
		if (m_soundEffects[sound].m_soundEffectBufferData)
		{
			delete[] m_soundEffects[sound].m_soundEffectBufferData;
			m_soundEffects[sound].m_soundEffectBufferData = NULL;
		}
	}
	else
	{
		m_soundEffects[sound].m_soundEffectBufferData = NULL;
	}

	m_soundEffects[sound].m_soundEffectBufferData = new byte[bufferLength];
	mediaStreamer.ReadAll(m_soundEffects[sound].m_soundEffectBufferData, bufferLength, &m_soundEffects[sound].m_soundEffectBufferLength);

    if (isMusic)
    {
        XAUDIO2_SEND_DESCRIPTOR descriptors[1];
	    descriptors[0].pOutputVoice = m_musicMasteringVoice;
	    descriptors[0].Flags = 0;
	    XAUDIO2_VOICE_SENDS sends = {0};
	    sends.SendCount = 1;
	    sends.pSends = descriptors;

        ThrowIfFailed(
	    m_musicEngine->CreateSourceVoice(&m_soundEffects[sound].m_soundEffectSourceVoice,
            &(mediaStreamer.GetOutputWaveFormatEx()), 0, 1.0f, &m_voiceContext, &sends)
	    );
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

        ThrowIfFailed(
	    m_soundEffectEngine->CreateSourceVoice(&m_soundEffects[sound].m_soundEffectSourceVoice,
            &(mediaStreamer.GetOutputWaveFormatEx()), 0, 1.0f, &m_voiceContext, &sends, nullptr)
        );
		//fix bug: set a initial volume
		m_soundEffects[sound].m_soundEffectSourceVoice->SetVolume(m_soundEffctVolume);
    }

	m_soundEffects[sound].m_soundEffectSampleRate = mediaStreamer.GetOutputWaveFormatEx().nSamplesPerSec;

	// Queue in-memory buffer for playback
	ZeroMemory(&m_soundEffects[sound].m_audioBuffer, sizeof(m_soundEffects[sound].m_audioBuffer));

	m_soundEffects[sound].m_audioBuffer.AudioBytes = m_soundEffects[sound].m_soundEffectBufferLength;
	m_soundEffects[sound].m_audioBuffer.pAudioData = m_soundEffects[sound].m_soundEffectBufferData;
	m_soundEffects[sound].m_audioBuffer.pContext = &m_soundEffects[sound];
	m_soundEffects[sound].m_audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
    m_soundEffects[sound].m_audioBuffer.LoopCount = 0;
}

void Audio::UnloadSoundEffect(const char* pszFilePath)
{
    int sound = Hash(pszFilePath);

    UnloadSoundEffect(sound);
}

void Audio::UnloadSoundEffect(unsigned int sound)
{
    if (m_engineExperiencedCriticalError) {
        return;
    }

    if (m_soundEffects.end() == m_soundEffects.find(sound))
        return;

    m_soundEffects[sound].m_soundEffectSourceVoice->DestroyVoice();

	if (m_soundEffects[sound].m_soundEffectBufferData)
	{
		delete[] m_soundEffects[sound].m_soundEffectBufferData;
		m_soundEffects[sound].m_soundEffectBufferData = NULL;
	}

	m_soundEffects[sound].m_soundEffectSourceVoice = nullptr;
	m_soundEffects[sound].m_soundEffectStarted = false;//
    ZeroMemory(&m_soundEffects[sound].m_audioBuffer, sizeof(m_soundEffects[sound].m_audioBuffer));

    m_soundEffects.erase(sound);
}
