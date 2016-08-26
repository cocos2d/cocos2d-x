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

#ifndef _OPENAL_WAV_PLAYER_H_
#define _OPENAL_WAV_PLAYER_H_

#include <new>
#include <FBase.h>
#include <FMedia.h>
#include <AL/alut.h>
#include <AL/al.h>
#include "IOpenAlPlayer.h"

/* Note presently OpenAL Player does not use EventDriven Thread and ITimerEventListner
 * But this is necessary to keep it to test the performance in those conditions too
 */

class OpenAlWavPlayer
	: public IOpenAlPlayer
{
public:
	OpenAlWavPlayer() ;
	virtual ~OpenAlWavPlayer();
	result Construct(const Tizen::Base::String &filePath);
	result Play(void);
	result Stop(void);
	result Pause(void);
	result SetLoop(bool flag);
	result SeekTo(long msTime);
	result SetVolume(int volume);	
	OpenAlPlayerState GetState(void) const;

private:
	static const int MAX_FILE_NAME = 256;
	result __FillAlFirstPcmBuffer(const Tizen::Base::String& filePath);
	result __ConvertError(ALenum error) const;

	ALuint __alBuffer;
	ALuint __alSource;
	Tizen::Base::ByteBuffer __srcBuf;
	Tizen::Base::ByteBuffer __pcmBuf;
	int __sampleRate;
	OpenAlPlayerState __openalPlayerState;
};

#endif
