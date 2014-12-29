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

#include <FBase.h>

#ifndef _IOPENAL_PLAYER_H_
#define _IOPENAL_PLAYER_H_

enum OpenAlPlayerState{
	OPENAL_PLAYER_STATE_NONE,
	OPENAL_PLAYER_STATE_INITIALIZED,
	OPENAL_PLAYER_STATE_PLAYING,
	OPENAL_PLAYER_STATE_PAUSED,
	OPENAL_PLAYER_STATE_STOPPED
};

/* Note presently OpenAL Player does not use EventDriven Thread and ITimerEventListner
 * But this is necessary to keep it to test the performance in those conditions too
 */
class IOpenAlPlayer
: public Tizen::Base::Object
{
public:
	virtual ~IOpenAlPlayer(void){}
	virtual result Play(void) = 0;
	virtual result Stop(void) = 0;
	virtual result Pause(void) = 0;
	virtual result SetLoop(bool flag) = 0;
	virtual result SeekTo(long msTime) = 0;
	virtual result SetVolume(int volume) = 0;
	virtual OpenAlPlayerState GetState(void) const = 0;
};

#endif
