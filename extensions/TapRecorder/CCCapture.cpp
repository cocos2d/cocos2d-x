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

#include "CCCapture.h"
#include <sstream>
#include "base/ccUtils.h"

USING_NS_CC_EXT;
using namespace TapRecorder;

Capture::Capture()
: Protocol()
, outputPath("")
, _eventListener(new EventListenerTapRecorder<Capture>())
{
}

Capture::~Capture()
{
    delete _eventListener;
    _eventListener = nullptr;
}

EventListenerTapRecorder<Capture>* Capture::getEventListener()
{
    return _eventListener;
}

void Capture::capture(const std::string& savename)
{
    std::string filename = savename;
    
    if (filename.empty()) {
        auto now     = std::chrono::system_clock::now();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
        
        std::stringstream ss;
        ss << "taprecorder_" << seconds.count() << ".png";
        filename = ss.str();
    }
    
    _eventListener->dispatchEvent(EventType::BEGAN);
    
    utils::captureScreen([this](bool succeed, const std::string& outputFile) {
        outputPath = "";
        
        if (succeed) {
            outputPath = outputFile;
            _eventListener->dispatchEvent(EventType::ENDED);
            log("capture succeed: %s", outputFile.c_str());
        }
        else {
            _eventListener->dispatchEvent(EventType::ERROR);
            log("faled to save capture");
        }
    }, filename);
}