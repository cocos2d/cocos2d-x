/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2014 Won, KyungYoun

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

#include <unique_ptr.h>
#include <FBaseSysLog.h>
#include "OpenAlBufferPlayer.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;
using namespace Tizen::Media;
using namespace std;

OpenAlBufferPlayer::OpenAlBufferPlayer(void)
: __alSource(0)
, __alFormat(AL_FORMAT_MONO16)
, __alBufCount(0)
, __codecType(CODEC_NONE)
, __channelType(AUDIO_CHANNEL_TYPE_NONE)
, __sampleType(AUDIO_TYPE_NONE)
, __sampleRate(0)
, __openalPlayerState(OPENAL_PLAYER_STATE_NONE)
, __waitingUpdateQueueCount(0)
, __loop(false)
{

}

OpenAlBufferPlayer::~OpenAlBufferPlayer(void)
{
	__UnprepareOpenAl();
}


/**
 * Construct OpenAL based player.
 * @return An error code
 * @param[in] filePath  The source file path that will be played.
 * @remarks If the filePath is wav file, then whole data will be loaded into memory.
 * @remarks For the compressed data, if the file size is less than some specific threshold the it will be decoded into memory.
 */
result
OpenAlBufferPlayer::Construct(const Tizen::Base::String &filePath)
{
	result r = E_SUCCESS;
	Tizen::Io::FileAttributes attr;
	AppLog( "file path: [%ls]", filePath.GetPointer());

	r = Tizen::Io::File::GetAttributes(filePath, attr);
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated. file is %ls", GetErrorMessage(r), filePath.GetPointer());

	String ext =  Tizen::Io::File::GetFileExtension(filePath);
	ext.Equals(L"mp3", false) ? __codecType = CODEC_MP3 : 
		ext.Equals(L"aac", false) ? __codecType = CODEC_AAC : 
		ext.Equals(L"m4a", false) ? __codecType = CODEC_AAC :
			ext.Equals(L"wav", false) ? __codecType = CODEC_LPCM :
				ext.Equals(L"ogg", false) ? __codecType = CODEC_VORBIS :
					ext.Equals(L"amr", false) ? __codecType = CODEC_AMR_NB :
				__codecType == CODEC_NONE;

	TryReturn( __codecType != CODEC_NONE, E_UNSUPPORTED_FORMAT, 
		"[E_UNSUPPORTED_FORMAT] File path is [%ls]" , filePath.GetPointer());

	// compressed data
	Tizen::Io::File file;
	r = file.Construct(filePath, "r");
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated. file is [%ls]", GetErrorMessage(r), filePath.GetPointer());

	r = __srcBuf.Construct((int)attr.GetFileSize());
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated. file size is %d", GetErrorMessage(r), (int)attr.GetFileSize());
	file.Read(__srcBuf);
	__srcBuf.Flip();

	r = __pcmBuf.Construct(MAX_AL_BUFFER_SIZE);
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated. buffer size is %d", GetErrorMessage(r), MAX_AL_BUFFER_SIZE);

	// Make timer
	__pDecodingTimer.reset(new (std::nothrow) Timer());
	TryReturn( __pDecodingTimer.get() != null, E_OUT_OF_MEMORY, "[E_OUT_OF_MEMORY].");

	r = __pDecodingTimer->Construct(*this);
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated.", GetErrorMessage(r));

	__PrepareOpenAl();
	return r;
}

result
OpenAlBufferPlayer::__FillAlFirstDecodedBuffers(void)
{
	result r = E_SUCCESS;
	ALenum openAlResult = AL_NO_ERROR;

	__srcBuf.SetPosition(0);

	__pDec.reset(new (std::nothrow) AudioDecoder());
	r = __pDec->Construct(__codecType, null);
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated. codecType is 0x%x", GetErrorMessage(r), __codecType);
	r = __pDec->Probe(__srcBuf, __sampleType, __channelType, __sampleRate);
	TryReturn( r == E_SUCCESS, r, "[%s] Propagated. sample type:%d, channel type:%d, sameplRate:%d", GetErrorMessage(r), __sampleType, __channelType, __sampleRate);

	TryReturn( __channelType != AUDIO_CHANNEL_TYPE_NONE, E_UNSUPPORTED_TYPE, "[E_UNSUPPORTED_TYPE] unsupported channel type.");
	TryReturn( __sampleRate != 0, E_UNSUPPORTED_TYPE, "[E_UNSUPPORTED_TYPE] unknown sample rate.");

	if(__channelType == AUDIO_CHANNEL_TYPE_MONO)
	{
		__alFormat = AL_FORMAT_MONO16;
	}
	else
	{
		__alFormat = AL_FORMAT_STEREO16;
	}		
//	AppLog( "__FillAlDecodedBuffer src size:%d, format is 0x%x", __srcBuf.GetLimit(), __alFormat);

	// Fill buffers
	__alBufCount = 0;
	for (int i=0; i< MAX_AL_BUFFER_COUNT; i++)
	{
		if (__FillAlDecodedBuffer(__alBuffers[i]) <= 0)
		{
			break;
		}
		__alBufCount++;
	}
	AppLog("alBufUsed = %d", __alBufCount);
	alSourceQueueBuffers(__alSource, __alBufCount, __alBuffers);
	openAlResult = alGetError();
	TryReturn( openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
		"[%s] OpenAl queue buffer failed.", GetErrorMessage(__ConvertError(openAlResult)));

	int queued = 0;
	alGetSourcei(__alSource, AL_BUFFERS_QUEUED, &queued);
//	AppLog( "Play __UpdateQueue queued:%d", queued);

	return r;
}

result
OpenAlBufferPlayer::Play(void)
{
	result r = E_SUCCESS;
	int val = 0;
	ALenum openAlResult = AL_NO_ERROR;
	
	AppLog( "enter");
	alGetSourcei(__alSource, AL_SOURCE_STATE, &val);
	AppLog( "Play state :0x%x", val);
	
	if(val == AL_INITIAL || val == AL_STOPPED)
	{
		r = __FillAlFirstDecodedBuffers();
		TryReturn( r == E_SUCCESS, r, "[%s] Propagated. al state is 0x%x", GetErrorMessage(r), val);
	}

	alSourcePlay(__alSource);
	alGetSourcei(__alSource, AL_SOURCE_STATE, &val);
	openAlResult = alGetError();
	TryReturn( /*val == AL_PLAYING &&*/ openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
		"[%s] Opanal play failed, state is 0x%x", GetErrorMessage(__ConvertError(openAlResult)), val);

	__openalPlayerState == OPENAL_PLAYER_STATE_PLAYING;

	AppLog("OpenAlBufferPlayer start timer");
	r = __pDecodingTimer->Start(TIME_OUT);

	return E_SUCCESS;
}

result
OpenAlBufferPlayer::Stop()
{
	AppLog( "enter");

	__srcBuf.SetPosition(0);
	alSourceStop(__alSource);
	for (int i=0; i< MAX_AL_BUFFER_COUNT; i++)
	{
		ALuint buffer;
		alSourceUnqueueBuffers(__alSource, 1, &buffer);
	}
	__openalPlayerState = OPENAL_PLAYER_STATE_STOPPED;

	if (__pDecodingTimer.get())
	{
		__pDecodingTimer->Cancel();
	}
	return E_SUCCESS;
}

result
OpenAlBufferPlayer::Pause()
{
	AppLog("enter");
	int val = 0;
	ALenum openAlResult = AL_NO_ERROR;
	alGetSourcei(__alSource, AL_SOURCE_STATE, &val);
	if(val == AL_PLAYING)
	{
		alSourcePause(__alSource);
		openAlResult = alGetError();
		TryReturn( openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
			"[%s] OpenAl pause buffer failed.", GetErrorMessage(__ConvertError(openAlResult)));

		__openalPlayerState = OPENAL_PLAYER_STATE_PAUSED;
	}
	else if(val == AL_PAUSED)
	{
		__openalPlayerState = OPENAL_PLAYER_STATE_PAUSED;
	}
	if (__pDecodingTimer.get())
	{
		__pDecodingTimer->Cancel();
	}

	AppLog("exit");
	return E_SUCCESS;
}

result
OpenAlBufferPlayer::SetLoop(bool flag)
{
	__loop = flag;
	return E_SUCCESS;
}

result
OpenAlBufferPlayer::SeekTo(long msTime)
{
	return E_SUCCESS;
}

result
OpenAlBufferPlayer::SetVolume(int volume)
{
	float newVolume = float(volume) / float(100);
	alSourcef (__alSource, AL_GAIN, newVolume);
	return E_SUCCESS;
}

OpenAlPlayerState
OpenAlBufferPlayer::GetState(void) const
{
	return __openalPlayerState;
}

void
OpenAlBufferPlayer::__PrepareOpenAl(void)
{
	ALenum openAlResult = AL_NO_ERROR;

	alutInit(0,0);
	openAlResult = alGetError();
//	TryReturn( openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
//		"[%s] OpenAl init failed. file is [%ls]", GetErrorMessage(__ConvertError(openAlResult)), filePath.GetPointer());

	alGenSources(1, &__alSource);
	openAlResult = alGetError();
//	TryReturn( openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
//		"[%s] OpenAl gen source failed. file is [%ls]", GetErrorMessage(__ConvertError(openAlResult)), filePath.GetPointer());

	// Generate buffers for openal
	alGenBuffers(MAX_AL_BUFFER_COUNT, __alBuffers);

	alSourcef (__alSource, AL_PITCH, 1.0);
	alSourcef (__alSource, AL_GAIN, 1.0);
	alSource3f(__alSource, AL_POSITION, 0.0, 0.0, 0.0);
	alSource3f(__alSource, AL_VELOCITY, 0.0, 0.0, 0.0);
	alSource3f(__alSource, AL_DIRECTION, 0.0, 0.0, 0.0);
	alSourcef(__alSource, AL_ROLLOFF_FACTOR, 0.0);
	alSourcei(__alSource, AL_SOURCE_RELATIVE, AL_TRUE);

	__openalPlayerState = OPENAL_PLAYER_STATE_INITIALIZED;
}

void
OpenAlBufferPlayer::__UnprepareOpenAl(void)
{
	if (__alSource)
	{
		alDeleteSources(1, &__alSource);
	}
	if (__alBufCount > 0 && __alBuffers != null)
	{
		alDeleteBuffers(__alBufCount, __alBuffers);
	}
}

int
OpenAlBufferPlayer::__FillAlDecodedBuffer(ALuint alBuffer)
{
	result r = E_SUCCESS;
	int ret = 0;

	__pcmBuf.Clear();
	AppLog( "__FillAlDecodedBuffer __pcmBuf.GetPosition:%d, GetRemaining():%d", __pcmBuf.GetPosition(), __pcmBuf.GetRemaining());

	int count = 3;
	while ( __srcBuf.GetRemaining() > 0 && __pcmBuf.GetRemaining() > 1024 && count-- > 0)
	{
		r = __pDec->Decode(__srcBuf, __pcmBuf);
		AppLog( "__FillAlDecodedBuffer decode src position:%d, pcm position:%d, remaining: %d", __srcBuf.GetPosition(), __pcmBuf.GetPosition(), __pcmBuf.GetRemaining());
		if (IsFailed(r))
		{
			AppLogException( "__FillAlDecodedBuffer decode fail");
			if (__srcBuf.GetRemaining() < 1024)
			{
				__srcBuf.SetPosition(0);
			}
			break;
		}
	}
#ifdef DUMP_FILE
	if (1)
	{
		static File *pFile = null;
		if (pFile == null)
		{
			pFile = new (std::nothrow) File();
			r = pFile->Construct(Tizen::App::App::GetInstance()->GetAppRootPath() + L"data/dump.pcm", L"wb");
			if (IsFailed(r))
			{
				delete pFile;
				pFile = null;
			}
		}
		if (pFile && __pcmBuf.GetPosition()>0)
		{
			pFile->Write(__pcmBuf.GetPointer(), __pcmBuf.GetPosition());
			pFile->Flush();
		}
	}
#endif

	if (__pcmBuf.GetPosition() > 0)
	{
		ALenum openAlResult = AL_NO_ERROR;
		alBufferData(alBuffer, __alFormat, __pcmBuf.GetPointer(), __pcmBuf.GetPosition(), __sampleRate);
		openAlResult = alGetError();
		TryReturn( openAlResult == AL_NO_ERROR, 0, 
			"[%s] OpenAl buffer data failed.", GetErrorMessage(__ConvertError(openAlResult)));
		
		ret = __pcmBuf.GetPosition();
		AppLog( "__FillAlDecodedBuffer fill size :%d", ret);
		return ret;
	}
	else
	{
		AppLogException( "__FillAlDecodedBuffer fill zero");
		return 0;
	}
}

bool
OpenAlBufferPlayer::__UpdateQueue()
{
	bool ret = false;
	int val = 0;
	alGetSourcei(__alSource, AL_SOURCE_STATE, &val);	//AL_PLAYING
//	AppLog( "__UpdateQueue state:0x%x", val);

	int processed = 0;
	alGetSourcei(__alSource, AL_BUFFERS_PROCESSED, &processed);
	AppLog( "__UpdateQueue processed:%d", processed);

	if (processed>0)
	{
		while (processed--)
		{
			ALuint alBuffer;
			int size;

			alSourceUnqueueBuffers(__alSource, 1, &alBuffer);

			size = __FillAlDecodedBuffer(alBuffer);
			if (size == 0)
			{
				break;
			}

			alSourceQueueBuffers(__alSource, 1, &alBuffer);
			ret = true;
		}
	}

	return ret;
}

void
OpenAlBufferPlayer::OnTimerExpired(Tizen::Base::Runtime::Timer& timer)
{
//	AppLog( "OnTimerExpired is called");
	bool ret;
	ret = __UpdateQueue();

	if (ret)	//if updated
	{
		__waitingUpdateQueueCount = 0;
	}
	else
	{
		__waitingUpdateQueueCount++;
	}

	if (__waitingUpdateQueueCount < MAX_WAITING_UPDATE_QUEUE)
	{
		int val = 0;
		alGetSourcei(__alSource, AL_SOURCE_STATE, &val);

		int queued = 0;
		alGetSourcei(__alSource, AL_BUFFERS_QUEUED, &queued);
		AppLog( "__UpdateQueue queued:%d, al state:0x%x, loop:%d", queued, val, __loop);

		if (queued > 0)
		{
			__pDecodingTimer->Start(TIME_OUT);
		}
		else if (queued ==0 && (val == AL_PLAYING || val == AL_PAUSED))
		{
			__pDecodingTimer->Start(TIME_OUT);	
		}
		else	if (queued==0 && __loop)		//AL_INIT, AL_STOPPED
		{
//			AppLog( "__UpdateQueue al state :0x%x", val);

			if (__srcBuf.GetRemaining() > (100))
			{
				// For preventing under-run. Checking openal consumed all src data. In this case we should wait.
				AppLog( "Feed under-run. Wait ! src remaining:%d", __srcBuf.GetRemaining());
				__pDecodingTimer->Start(TIME_OUT);
			}
			else
			{
				// Replay by loop
				AppLog( "Replay. src remaining:%d", __srcBuf.GetRemaining());
				Play();
			}
		}
	}
	else
	{
		AppLog( "Audio decode check stopped.");
	}


}

result
OpenAlBufferPlayer::__ConvertError(ALenum error) const
{
	result r = E_SUCCESS;
	switch(error)
	{
	case AL_NO_ERROR:
		r = E_SUCCESS;
		break;
	case AL_INVALID_NAME:
		r = E_INVALID_ARG;
		break;
	case AL_INVALID_ENUM:
		r = E_OUT_OF_RANGE;
		break;
	case AL_INVALID_VALUE:
		r = E_INVALID_ARG;
		break;
	case AL_INVALID_OPERATION:
		r = E_INVALID_OPERATION;;
		break;
	case AL_OUT_OF_MEMORY:
		r = E_OUT_OF_MEMORY;
		break;
	default:
		r = E_FAILURE;
		break;
	}
	return r;
}

