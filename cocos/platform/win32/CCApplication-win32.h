/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#pragma once

#include "platform/CCStdC.h"
#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>

NS_CC_BEGIN

class CC_DLL Application : public ApplicationProtocol
{
public:
    /**
     * @js ctor
     */
    Application();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Application();

    /**
    @brief    Run the message loop.
    */
    int run();

    /**
    @brief    Get current application instance.
    @return Current application instance pointer.
    */
    static Application* getInstance();
    
    /* override functions */
    virtual void setAnimationInterval(float interval) override;

    virtual LanguageType getCurrentLanguage();

    virtual const char * getCurrentLanguageCode();
    
    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform();
    
    /**
    @brief Get application version
    */
    virtual std::string getVersion() override;

    /**
     @brief Open url in default browser
     @param String with url to open.
     @return true if the resource located by the URL was successfully opened; otherwise false.
     */
    virtual bool openURL(const std::string &url);

    /**
     *  Sets the Resource root path.
     *  @deprecated Please use FileUtils::getInstance()->setSearchPaths() instead.
     */
    CC_DEPRECATED_ATTRIBUTE void setResourceRootPath(const std::string& rootResDir);

    /** 
     *  Gets the Resource root path.
     *  @deprecated Please use FileUtils::getInstance()->getSearchPaths() instead. 
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getResourceRootPath();

    void setStartupScriptFilename(const std::string& startupScriptFile);

    const std::string& getStartupScriptFilename()
    {
        return _startupScriptFilename;
    }

protected:
    HINSTANCE           _instance;
    HACCEL              _accelTable;
    LARGE_INTEGER       _animationInterval;
    std::string         _resourceRootPath;
    std::string         _startupScriptFilename;

    static Application * sm_pSharedApplication;
};

NS_CC_END
