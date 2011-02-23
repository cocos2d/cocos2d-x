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

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "ccxApplication.h"
#include "AppDelegate.h"

class Application : public cocos2d::ccxApplication
{
public:
        Application();
        virtual ~Application();

        /**
         @brief	Call for init OpenGL instance, source path, etc...
         */
        virtual bool initInstance();
        
        /**
         @brief	Callback by CCDirector for limit FPS.
         @interval       The time, which expressed in second in second, between current frame and next. 
         */
        virtual void    setAnimationInterval(double interval);
        
        /**
         @brief	Callback by CCDirector for change device orientation.
         @orientation    The defination of orientation which CCDirector want change to.
         @return         The actual orientation of the application.
         */
        virtual Orientation setOrientation(Orientation orientation);
        
        /**
         @brief	Get status bar rectangle in EGLView window.
         */
        virtual void    statusBarFrame(cocos2d::CGRect * rect);
	
    void Run();
        
protected:
        AppDelegate m_Delegate;
 };

#endif	// end of __CCX_APPLICATION_IPHONE_H__
