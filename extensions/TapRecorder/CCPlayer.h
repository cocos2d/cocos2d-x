/****************************************************************************
 Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>
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

#ifndef TapRecorder_Player_h
#define TapRecorder_Player_h

#include "extensions/TapRecorder/CCProtocol.h"
#include "extensions/TapRecorder/CCEventListenerTapRecorder.h"

NS_CC_EXT_BEGIN

namespace TapRecorder
{
    class Player : public Protocol
    {
    public:
        static Player* getInstance()
        {
            static Player instance;
            return &instance;
        }
        
        static std::string updateKey;
        
        enum EventType { TOUCH_PLAYING = 1, TOUCH_PLAYED, PLAY_BEGAN, PLAY_STOPPED, PLAY_CANCELLED };
        
        EventListenerTapRecorder<Player>* getEventListener();
        
        bool calibrationEnabled;
        
        Player();
        ~Player();
        
        bool play(const std::string&);
        bool stop();
        
        const Record& getCurrentRecord();
        
        bool isPlaying();
        
        void update(float);
        
    protected:
        typedef std::unordered_map<int, cocos2d::Touch*> ClaimedTouches;
        
        EventListenerTapRecorder<Player>* _eventListener;
        
        cocos2d::Vec2 _calibration;
        
        Records::iterator _recordsCursor;
        ClaimedTouches _claimedTouches;
        
        Record _playingRecord;
        
        bool _playing;
        
        void dispatchCapture();
        void dispatchTouchEventWithRecord(const Record&);
        
        void cleanup();
        void calibrate();
    };
}

NS_CC_EXT_END

#endif /* TapRecorder_Player_h */
