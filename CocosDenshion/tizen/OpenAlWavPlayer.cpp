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

#include <FBaseSysLog.h>
#include "OpenAlWavPlayer.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;

OpenAlWavPlayer::OpenAlWavPlayer()
: __alBuffer(0)
, __alSource(0)
, __openalPlayerState(OPENAL_PLAYER_STATE_NONE)
{

}
OpenAlWavPlayer::~OpenAlWavPlayer()
{
	if (__alSource)
	{
		alDeleteSources(1, &__alSource);
	}
	if ( __alBuffer != null)
	{
		alDeleteBuffers(1, &__alBuffer);
	}
}

/**
 * Construct OpenAL based player.
 * @return An error code
 * @param[in] filePath  The source file path that will be played.
 * @remarks If the filePath is wav file, then whole data will be loaded into memory.
 * @remarks For the compressed data, if the file size is less than some specific threshold the it will be decoded into memory.
 */
result
OpenAlWavPlayer::Construct(const Tizen::Base::String &filePath)
{
	result r = E_SUCCESS;
	Tizen::Io::FileAttributes attr;
	ALenum openAlResult = AL_NO_ERROR;
	AppLog( "file path: [%ls]", filePath.GetPointer());

	r = Tizen::Io::File::GetAttributes(filePath, attr);
	TryReturn(r == E_SUCCESS, r, "[%s] Propagated. file is %ls", GetErrorMessage(r), filePath.GetPointer());

	// wav only
	String ext =  Tizen::Io::File::GetFileExtension(filePath);
	TryReturn(ext.Equals(L"wav", false), E_UNSUPPORTED_FORMAT, "[E_UNSUPPORTED_FORMAT] File path is [%ls]" , filePath.GetPointer());

	alutInit(0,0);
	openAlResult = alGetError();
//	TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
//		"[%s] OpenAl init failed. file is [%ls]", GetErrorMessage(__ConvertError(openAlResult)), filePath.GetPointer());

	alGenSources(1, &__alSource);
	openAlResult = alGetError();
	TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
		"[%s] OpenAl gen source failed. file is [%ls]", GetErrorMessage(__ConvertError(openAlResult)), filePath.GetPointer());

	r = __FillAlFirstPcmBuffer(filePath);
	TryReturn(r == E_SUCCESS, r, "[%s] Propagated.", GetErrorMessage(r));

	alSourcei(__alSource, AL_BUFFER, __alBuffer);
	openAlResult = alGetError();
	TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult),
		"[%s] OpenAl Set buffer failed. file is [%ls]", GetErrorMessage(__ConvertError(openAlResult)), filePath.GetPointer());

	alSourcef (__alSource, AL_PITCH, 1.0);
	alSourcef (__alSource, AL_GAIN, 1.0);
	alSource3f(__alSource, AL_POSITION, 0.0, 0.0, 0.0);
	alSource3f(__alSource, AL_VELOCITY, 0.0, 0.0, 0.0);
	alSource3f(__alSource, AL_DIRECTION, 0.0, 0.0, 0.0);
	alSourcef(__alSource, AL_ROLLOFF_FACTOR, 0.0);
	alSourcei(__alSource, AL_SOURCE_RELATIVE, AL_TRUE);

	__openalPlayerState = OPENAL_PLAYER_STATE_INITIALIZED;
	return r;
}

result
OpenAlWavPlayer::__FillAlFirstPcmBuffer(const Tizen::Base::String& filePath)
{
	result r = E_SUCCESS;
	ALenum openAlResult = AL_NO_ERROR;

	// load wav file into buffer
	char filename[MAX_FILE_NAME];
	snprintf(filename, sizeof(filename), "%ls", filePath.GetPointer());
	__alBuffer = alutCreateBufferFromFile(filename);

	openAlResult = alGetError();
	TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult),
		"[%s] OpenAl create buffer failed.", GetErrorMessage(__ConvertError(openAlResult)));		

	return r;
}

result
OpenAlWavPlayer::Play(void)
{
	result r = E_SUCCESS;
	int val = 0;
	ALenum openAlResult = AL_NO_ERROR;
	AppLog( "enter");

	alSourcePlay(__alSource);
	openAlResult = alGetError();
	TryCatch(openAlResult == AL_NO_ERROR, r=__ConvertError(openAlResult)
		, "[%s] alSourcePlay Failed with %d", GetErrorMessage(__ConvertError(openAlResult)), openAlResult);

	alGetSourcei(__alSource, AL_SOURCE_STATE, &val);
	TryCatch(val == AL_INITIAL || val == AL_PAUSED || val == AL_STOPPED
		, r=E_INVALID_STATE, "[E_INVALID_STATE] alSource state is wrong. state is %d", val);

	__openalPlayerState = OPENAL_PLAYER_STATE_PLAYING;
	return E_SUCCESS;

CATCH:
	return r;
}

result
OpenAlWavPlayer::Stop()
{
	ALenum openAlResult = AL_NO_ERROR;
	AppLog( "enter");

	__srcBuf.SetPosition(0);
	alSourceStop(__alSource);
	openAlResult = alGetError();
	TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
		"[%s] OpenAl stop failed.", GetErrorMessage(__ConvertError(openAlResult)));		

	__openalPlayerState = OPENAL_PLAYER_STATE_STOPPED;

	return E_SUCCESS;
}

result
OpenAlWavPlayer::Pause()
{
	AppLog("enter");
	int val = 0;
	ALenum openAlResult = AL_NO_ERROR;
	alGetSourcei(__alSource, AL_SOURCE_STATE, &val);
	if(val == AL_PLAYING)
	{
		alSourcePause(__alSource);
		openAlResult = alGetError();
		TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
			"[%s] OpenAl pause buffer failed.", GetErrorMessage(__ConvertError(openAlResult)));

		__openalPlayerState = OPENAL_PLAYER_STATE_PAUSED;
	}
	else if(val == AL_PAUSED)
	{
		__openalPlayerState = OPENAL_PLAYER_STATE_PAUSED;
	}

	return E_SUCCESS;
}

result
OpenAlWavPlayer::SetLoop(bool flag)
{
	alSourcei(__alSource, AL_LOOPING, (flag ? AL_TRUE : AL_FALSE));
	ALenum openAlResult = alGetError();
	TryReturn(openAlResult == AL_NO_ERROR, __ConvertError(openAlResult), 
		"[%s] OpenAl set loop failed.", GetErrorMessage(__ConvertError(openAlResult)));
	return __ConvertError(openAlResult);
}

ALuint playFromSeek(ALuint source, ALuint buffer, ALfloat seek) { 
	if (seek < 0 || seek > 1) return 0; //stopping if seek is invalid
	alSourcei(source, AL_BUFFER, buffer); //retrieving source's buffer
	ALint tot = 0;
	alGetBufferi(buffer, AL_SIZE, &tot); //size of buffer (in bytes)
	alSourcei(source, AL_BYTE_OFFSET, seek*tot); //positionning...
	alSourcePlay(source); //let's play
	return source;
}

ALfloat getBufferLengthInSec(ALuint buffer) {
	ALint size, bits, channels, freq;
	alGetBufferi(buffer, AL_SIZE, &size);
	alGetBufferi(buffer, AL_BITS, &bits);
	alGetBufferi(buffer, AL_CHANNELS, &channels);
	alGetBufferi(buffer, AL_FREQUENCY, &freq);
	if(alGetError() != AL_NO_ERROR) return -1.0f;
	return (ALfloat)((ALuint)size/channels/(bits/8)) / (ALfloat)freq;
}

void playFromSec(ALuint source, ALuint buffer, ALfloat sec) {
	//that's just a seek pos defined by sec / (total size in sec)
	playFromSeek(source, buffer, sec/getBufferLengthInSec(buffer));
}

result
OpenAlWavPlayer::SeekTo(long msTime)
{
	playFromSec(__alSource, __alBuffer, ALfloat(msTime)/ALfloat(1000));
	return E_SUCCESS;
}

result
OpenAlWavPlayer::SetVolume(int volume)
{
	float newVolume = float(volume) / float(100);
	alSourcef (__alSource, AL_GAIN, newVolume);
	return E_SUCCESS;
}

OpenAlPlayerState
OpenAlWavPlayer::GetState(void) const
{
	return __openalPlayerState;
}

result
OpenAlWavPlayer::__ConvertError(ALenum error) const
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

