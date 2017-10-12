/****************************************************************************
Copyright (c) 2016-2017 Chukong Technologies Inc.

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

#include <functional>

namespace cocos2d { namespace experimental {

class IAudioPlayer
{
public:
    enum class State
    {
        INVALID = 0,
        INITIALIZED,
        PLAYING,
        PAUSED,
        STOPPED,
        OVER
    };

    using PlayEventCallback = std::function<void(State)>;

    virtual ~IAudioPlayer()
    { };

    virtual int getId() const = 0;

    virtual void setId(int id) = 0;

    virtual std::string getUrl() const = 0;

    virtual State getState() const = 0;

    virtual void play() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void stop() = 0;

    virtual void rewind() = 0;

    virtual void setVolume(float volume) = 0;

    virtual float getVolume() const = 0;

    virtual void setAudioFocus(bool isFocus) = 0;

    virtual void setLoop(bool isLoop) = 0;

    virtual bool isLoop() const = 0;

    virtual float getDuration() const = 0;

    virtual float getPosition() const = 0;

    virtual bool setPosition(float pos) = 0;

    // @note: STOPPED event is invoked in main thread
    //        OVER event is invoked in sub thread
    virtual void setPlayEventCallback(const PlayEventCallback &playEventCallback) = 0;
};

}} // namespace cocos2d { namespace experimental {
