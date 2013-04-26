/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#ifndef _HELLO_CPP_H_
#define _HELLO_CPP_H_

#include <new>
#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FGraphicsOpengl2.h>
#include <FGrpFloatMatrix4.h>

#include "../../Classes/AppDelegate.h"
#include "cocos2d.h"

/**
 * [HelloCpp] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class HelloCpp
	: public Tizen::App::Application
	, public Tizen::Base::Runtime::ITimerEventListener
{
public:
	/**
	 * [HelloCpp] application must have a factory method that creates an instance of itself.
	 */
	static Tizen::App::Application* CreateInstance(void);

public:
	HelloCpp();
	~HelloCpp();

	virtual bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);
	virtual bool OnAppInitialized(void);
	virtual bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);
	virtual void OnForeground(void);
	virtual void OnBackground(void);
	virtual void OnLowMemory(void);
	virtual void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);
	virtual void OnScreenOn(void);
	virtual void OnScreenOff(void);

	virtual void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);

	bool Draw(void);

private:
	bool InitEGL(void);
	void DestroyGL(void);
	void Cleanup(void);

	void IncTimeStamp(void);

private:
	Tizen::Ui::Controls::Form*			__pForm;

	Tizen::Graphics::Opengl::EGLDisplay __eglDisplay;
	Tizen::Graphics::Opengl::EGLSurface __eglSurface;
	Tizen::Graphics::Opengl::EGLConfig  __eglConfig;
	Tizen::Graphics::Opengl::EGLContext __eglContext;

	Tizen::Base::Runtime::Timer*        __pTimer;
};

#endif
