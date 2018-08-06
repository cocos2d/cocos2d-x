/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

//
//  AppEvent.h
//  Simulator
//
//

#ifndef __Simulator__AppEvent__
#define __Simulator__AppEvent__

#include <string>
#include "cocos2d.h"

// encode / decode json
#include "json/document-wrapper.h"
#include "json/filereadstream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "SimulatorExport.h"

enum
{
    APP_EVENT_MENU = 1,
    APP_EVENT_DROP = 2
};

#define kAppEventDropName "APP.EVENT.DROP"
#define kAppEventName     "APP.EVENT"

class CC_LIBSIM_DLL AppEvent : public cocos2d::EventCustom
{
public:
    /** Constructor */
    AppEvent(const std::string& eventName, int type);
    
    /** Gets event name */
    inline const std::string& getEventName() const { return _eventName; };
    
    void setEventType(int type);
    int  getEventType();
    void setDataString(std::string data);
    std::string getDataString();
protected:
    std::string _eventName;
    std::string _dataString;
    int         _eventType;
};

#endif /* defined(__Simulator__AppEvent__) */
