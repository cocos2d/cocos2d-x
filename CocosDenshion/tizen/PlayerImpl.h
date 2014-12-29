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

#ifndef _PLAYER_IMPL_H_
#define _PLAYER_IMPL_H_

#include <unique_ptr.h>
#include "IOpenAlPlayer.h"

enum PlayerState
{
	PLAYER_STATE_INITIALIZED,       /**< The player is initialized */
	PLAYER_STATE_OPENING,           /**< The player's opening behavior is processed */
	PLAYER_STATE_OPENED,            /**< The source is opened */
	PLAYER_STATE_ENDOFCLIP,         /**< The player has reached the end of the clip */
	PLAYER_STATE_STOPPED,           /**< The player has stopped and has no current play-time, but the media content is still opened and initialized */
	PLAYER_STATE_PAUSED,            /**< The player's playback is paused */
	PLAYER_STATE_PLAYING,           /**< The player is playing the media content */
	PLAYER_STATE_CLOSED,            /**< The source is closed */
	PLAYER_STATE_ERROR,             /**< An error has occurred */

};

class _PlayerImpl
{
public:
	_PlayerImpl(void);
	virtual ~_PlayerImpl(void);

	result Construct(void);
	result OpenFile(const Tizen::Base::String& mediaLocalPath);
	result Play(void);
	result Pause(void);
	result Stop(void);
	result Close(void);
	PlayerState GetState(void);
	int GetVolume(void) const;
	result SeekTo(long msTime);
	result SetVolume(int volume);
	result SetLoop(bool flag);

private:
	_PlayerImpl(const _PlayerImpl&);
	_PlayerImpl& operator =(const _PlayerImpl& _PlayerImpl);

	std::unique_ptr<IOpenAlPlayer> __pOpenAlPlayer;

	int __currentVolume;
};

#endif
