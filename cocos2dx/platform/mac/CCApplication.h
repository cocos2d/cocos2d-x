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

#pragma once
#ifndef __CC_APPLICATION_MAC_H__
#define __CC_APPLICATION_MAC_H__

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"

NS_CC_BEGIN;

class CCRect;
class CCApplication;

class CC_DLL CCApplication : public CCApplicationProtocol
{
public:
        CCApplication();
        virtual ~CCApplication();
        
        /**
         @brief	Callback by CCDirector for limit FPS.
         @interval       The time, which expressed in second in second, between current frame and next. 
         */
        void setAnimationInterval(double interval);
        
        /**
         @brief	Get status bar rectangle in EGLView window.
         */
        //void    statusBarFrame(CCRect * rect);
        
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
        virtual ccLanguageType getCurrentLanguage();
		
	    virtual bool isIpad();

protected:
        static CCApplication * sm_pSharedApplication;
};

NS_CC_END;

#endif	// end of __CC_APPLICATION_MAC_H__
