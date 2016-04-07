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

#ifndef TapRecorder_Recorder_h
#define TapRecorder_Recorder_h

#include "CCProtocol.h"
#include "base/CCTouch.h"
#include "base/CCEvent.h"
#include "base/CCEventListenerTouch.h"
#include "extensions/TapRecorder/CCEventListenerTapRecorder.h"

NS_CC_EXT_BEGIN

namespace TapRecorder
{
    class Recorder : public Protocol
    {
    public:
        enum EventType { BEGAN = 1, FINISHED, CANCELLED, SAVED };
        
        static Recorder* getInstance()
        {
            static Recorder instance;
            return &instance;
        }
        
        static std::string updateKey;
        
        EventListenerTapRecorder<Recorder>* getEventListener();
        
        Recorder();
        ~Recorder();
        
        void init();
        
        void beginUpdate();
        bool record(DurationUnit);
        bool recordForSeconds(DurationUnit, unsigned long seconds);
        bool recordForFrames(DurationUnit,  unsigned long frames);
        bool stop();
        
        bool isRecording();
        
        void add(Record);
        void add(cocos2d::Touch* touch, cocos2d::EventTouch::EventCode);
        void add(int, DurationUnit, cocos2d::EventTouch::EventCode, cocos2d::Vec2);
        
        void clear();
        
        bool save(const std::string& filename);
        std::string lastSavePath();
        
        void update(float dt);
        
    protected:
        DurationUnit _currentDurationUnit;
        bool _initialized;
        bool _recording;
        
        unsigned long _recordMillseconds;
        unsigned long _recordFrames;
        
        std::string _outputPath;
        
        // listeners are coocs2d::Ref thus they will be autoreleased
        cocos2d::EventListenerTouchOneByOne*  _listenerOneByOne;
        cocos2d::EventListenerTouchAllAtOnce* _listenerAllAtOnce;
        EventListenerTapRecorder<Recorder>*   _listenerTapEmultor;
        
        bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
        void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
        void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
        void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
        
        void onTouchesBegan(std::vector<cocos2d::Touch*>, cocos2d::Event*);
        void onTouchesMoved(std::vector<cocos2d::Touch*>, cocos2d::Event*);
        void onTouchesEnded(std::vector<cocos2d::Touch*>, cocos2d::Event*);
        void onTouchesCancelled(std::vector<cocos2d::Touch*>, cocos2d::Event*);
    };
}

NS_CC_EXT_END

#endif /* TapRecorder_Recorder_h */
