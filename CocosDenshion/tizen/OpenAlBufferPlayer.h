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

#ifndef _FMEDIA_OPENAL_BUFFER_PLAYER_H_
#define _FMEDIA_OPENAL_BUFFER_PLAYER_H_

#include <unique_ptr.h>
#include <AL/alut.h>
#include <AL/al.h>
#include <FBase.h>
#include <FMedia.h>
#include "IOpenAlPlayer.h"

/* Note presently OpenAL Player does not use EventDriven Thread and ITimerEventListner
 * But this is necessary to keep it to test the performance in those conditions too
 */

class OpenAlBufferPlayer
	: public Tizen::Base::Runtime::ITimerEventListener
	 ,public IOpenAlPlayer
{
public:
	OpenAlBufferPlayer(void) ;
	virtual ~OpenAlBufferPlayer(void);
	result Construct(const Tizen::Base::String &filePath);
	result Play(void);
	result Stop(void);
	result Pause(void);
	result SetLoop(bool flag);
	result SeekTo(long msTime);
	result SetVolume(int volume);
	OpenAlPlayerState GetState(void) const;

private:
	static const int MAX_AL_BUFFER_COUNT = 8;
	static const int MAX_AL_BUFFER_SIZE = 1024*16;
	static const int MAX_FILE_NAME = 256;
	static const int TIME_OUT = 100;
	static const int MAX_WAITING_UPDATE_QUEUE = 20;	// TIME_OUT * MAX_WAITING_UPDATE_QUEUE = time to wait before killing the decode timer

	void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);
	result __FillAlFirstDecodedBuffers(void);
	bool __UpdateQueue();
	int __FillAlDecodedBuffer(ALuint alBuffer);
	void __PrepareOpenAl(void);
	void __UnprepareOpenAl(void);
	result __ConvertError(ALenum error) const;

	ALuint __alBuffers[MAX_AL_BUFFER_COUNT];
	ALuint __alSource;
	ALenum __alFormat;
	int __alBufCount;
	Tizen::Base::ByteBuffer __srcBuf;
	Tizen::Base::ByteBuffer __pcmBuf;
	std::unique_ptr<Tizen::Media::AudioDecoder> __pDec;
	Tizen::Media::CodecType __codecType;
	Tizen::Media::AudioChannelType __channelType;
	Tizen::Media::AudioSampleType __sampleType;
	int __sampleRate;
	OpenAlPlayerState __openalPlayerState;
	std::unique_ptr<Tizen::Base::Runtime::Timer> __pDecodingTimer;
	int __waitingUpdateQueueCount;
	bool __loop;
};

#endif
