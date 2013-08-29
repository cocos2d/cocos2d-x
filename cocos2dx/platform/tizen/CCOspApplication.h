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

#ifndef _CCOSPAPPLICATION_H_
#define _CCOSPAPPLICATION_H_

#include <FApp.h>
#include <FUi.h>

typedef void (*CCOspApplicationInitialized)(void);

class CCOspApplication
    : public Tizen::App::Application
{
public:
    /**
     * [OspApplication] application must have a factory method that creates an instance of itself.
     */
    static Tizen::App::Application* CreateInstance(void);
    static CCOspApplication* GetInstance(void);
    static void SetApplicationInitializedCallback(CCOspApplicationInitialized p);
    static void SetScreenOrientation(Tizen::Ui::Orientation orientation);

public:
    CCOspApplication();
    ~CCOspApplication();

    Tizen::Ui::Controls::Form* getCCOspForm();

    virtual bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);
    virtual bool OnAppInitialized(void);
    virtual bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);
    virtual void OnForeground(void);
    virtual void OnBackground(void);
    virtual void OnLowMemory(void);
    virtual void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);
    virtual void OnScreenOn(void);
    virtual void OnScreenOff(void);

protected:
    static CCOspApplication* sm_pSharedCCOspApplication;
    static CCOspApplicationInitialized sm_pApplicationInitialized;
    static Tizen::Ui::Orientation sm_eScreenOrientation;

private:
    Tizen::Ui::Controls::Frame* __pFrame;
    Tizen::Ui::Controls::Form* __pForm;
};

#endif // _CCOSPAPPLICATION_H_
