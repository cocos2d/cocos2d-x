/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CCX_APP_DELEGATE_H_YANGWS_20110122__
#define __CCX_APP_DELEGATE_H_YANGWS_20110122__

#include "ccxCommon.h"

NS_CC_BEGIN

class CGRect;

class CCX_DLL_PS ccxApplication
{
public:
    virtual ~ccxApplication() {}

    /**
    @brief	Call for init OpenGL instance, source path, etc...
    */
    virtual bool initInstance() = 0;
    
    /**
    @brief	Callback by CCDirector for limit FPS.
    @interval       The time, which expressed in second in second, between current frame and next. 
    */
    virtual void    setAnimationInterval(double interval) = 0;

    typedef enum
    {
        /// Device oriented vertically, home button on the bottom
        kOrientationPortrait = 0,
        /// Device oriented vertically, home button on the top
        kOrientationPortraitUpsideDown = 1,
        /// Device oriented horizontally, home button on the right
        kOrientationLandscapeLeft = 2,
        /// Device oriented horizontally, home button on the left
        kOrientationLandscapeRight = 3,
    } Orientation;
    /**
    @brief	Callback by CCDirector for change device orientation.
    @orientation    The defination of orientation which CCDirector want change to.
    @return         The actual orientation of the application.
    */
    virtual Orientation setOrientation(Orientation orientation) = 0;

    /**
    @brief	Get status bar rectangle in EGLView window.
    */
    virtual void    statusBarFrame(CGRect * rect) = 0;

    /**
    @brief	Get current applicaiton instance.
    @return Current application instance pointer.
    */
    static ccxApplication& sharedApplication();

#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_UPHONE)
    /**
    @brief Get the data path of the Application.
    @return If the app is installed,the return value is the path of .so file.
    else the return value is "/NEWPLUS/TG3/APP/"
    */
    virtual const char* getAppDataPath() = 0;

    virtual void switchNotify(int nTurnOn) = 0;
#endif

protected:
    ccxApplication() {}
    static void setSharedApplication(ccxApplication& app);
};

NS_CC_END;

#endif	// __CCX_APP_DELEGATE_H_YANGWS_20110122__
