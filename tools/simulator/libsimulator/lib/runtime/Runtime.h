/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef  _RUNTIME__H_
#define  _RUNTIME__H_

#include <string>
#include <functional>
#include <unordered_map>

void recvBuf(int fd, char *pbuf, unsigned long bufsize);

void sendBuf(int fd, const char *pbuf, unsigned long bufsize);

std::string& replaceAll(std::string& str, const std::string& old_value, const std::string& new_value);

std::string getIPAddress();

const char* getRuntimeVersion();

//
void resetDesignResolution();
const char* getRuntimeVersion();

//
// RuntimeEngine
//
#include "ProjectConfig/ProjectConfig.h"

#define kRuntimeEngineLua 1
#define kRuntimeEngineJs  2
#define kRuntimeEngineCCS 4

class RuntimeProtocol;
class RuntimeEngine
{
public:
    static RuntimeEngine* getInstance();
    
    //
    void setupRuntime();
    void setProjectConfig(const ProjectConfig &config);
    void setProjectPath(const std::string &path);
    const ProjectConfig &getProjectConfig();
    void startScript(const std::string &args);
    void start();
    void end();
    void setEventTrackingEnable(bool enable);
    
    void addRuntime(RuntimeProtocol *runtime, int type);
    RuntimeProtocol *getRuntime();
    
private:
    RuntimeEngine();
    bool startNetwork();
    void showUI();
    void updateConfigParser();
    
    // 
    void trackEvent(const std::string &eventName);
    void trackLaunchEvent();
    
    RuntimeProtocol *_runtime;  // weak ref
    ProjectConfig _project;
    bool _eventTrackingEnable;  // false default
    std::string _launchEvent;
    std::unordered_map<int,RuntimeProtocol*> _runtimes;
};

#endif // _RUNTIME__H_

