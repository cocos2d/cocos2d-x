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

#ifndef TapRecorder_CommandPlayer_h
#define TapRecorder_CommandPlayer_h

#include "CCCommandTapRecorder.h"
#include "extensions/TapRecorder/CCPlayer.h"
#include "extensions/TapRecorder/CCRecord.h"
#include <vector>
#include <condition_variable>

NS_CC_EXT_BEGIN

namespace TapRecorder { namespace Command {

    class Player : public TapRecorder
    {
    public:
        static const std::string commandName();
        static std::string createResponse(int signal, const std::string& message);
        
        static void parseArguments(int, std::vector<std::string>&);
        
        static void start(int, const std::vector<std::string>&);
        static void enableCalibration(int, const std::vector<std::string>&);
        static void disabledCalibration(int, const std::vector<std::string>&);
        static void stop(int, const std::vector<std::string>&);
        static void help(int, const std::vector<std::string>&);
        
    protected:
        static void eventCallback(int fd, std::condition_variable& condWait, bool sync, bool reportTouch, cocos2d::extension::TapRecorder::Player* player, int type);
        static void reportGestureEvent(int fd, int eventType, const cocos2d::extension::TapRecorder::Record& record);
    };
    
}}

NS_CC_EXT_END

#endif /* TapRecorder_CommandPlayer_h */
