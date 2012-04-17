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

#ifndef __CC_APPLICATION_IOS_H__
#define __CC_APPLICATION_IOS_H__

#include "CCCommon.h"

NS_CC_BEGIN;

class CCRect;

class CC_DLL CCApplication
{
public:
        CCApplication();
        virtual ~CCApplication();
        
        /**
         @brief	Implement for initialize OpenGL instance, set source path, etc...
         */
        virtual bool initInstance() = 0;
        
        /**
         @brief	Implement CCDirector and CCScene init code here.
         @return true    Initialize success, app continue.
         @return false   Initialize failed, app terminate.
         */
        virtual bool applicationDidFinishLaunching() = 0;
        
        /**
         @brief  The function be called when the application enter background
         @param  the pointer of the application
         */
        virtual void applicationDidEnterBackground() = 0;
        
        /**
         @brief  The function be called when the application enter foreground
         @param  the pointer of the application
         */
        virtual void applicationWillEnterForeground() = 0;
        
        /**
         @brief	Callback by CCDirector for limit FPS.
         @interval       The time, which expressed in second in second, between current frame and next. 
         */
        void setAnimationInterval(double interval);
        
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
        Orientation setOrientation(Orientation orientation);
        
        /**
         @brief	Get status bar rectangle in EGLView window.
         */
        void    statusBarFrame(CCRect * rect);
        
        /**
         @brief	Run the message loop.
         */
        int run();
        
        /**
         @brief	Get current applicaiton instance.
         @return Current application instance pointer.
         */
        static CCApplication& sharedApplication();

        /**
        @brief Get current language config
        @return Current language config
        */
        static ccLanguageType getCurrentLanguage();

protected:
        static CCApplication * sm_pSharedApplication;
};

NS_CC_END;

#endif	// end of __CC_APPLICATION_IOS_H__
