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

#include "CCOspApplication.h"
#include "CCOspForm.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace Tizen::App;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Runtime;

OspApplication * OspApplication::sm_pSharedOspApplication = 0;
OspApplicationInitialized OspApplication::sm_pApplicationInitialized = 0;
Orientation OspApplication::sm_eScreenOrientation = ORIENTATION_NONE;

OspApplication::OspApplication()
    : __pForm(null)
{
    CCAssert(! sm_pSharedOspApplication, "");
    sm_pSharedOspApplication = this;
}

OspApplication::~OspApplication()
{
    CCAssert(this == sm_pSharedOspApplication, "");
    sm_pSharedOspApplication = NULL;
}

Tizen::App::Application*
OspApplication::CreateInstance(void)
{
    // Create the instance through the constructor.
    return new (std::nothrow) OspApplication();
}

void
OspApplication::SetApplicationInitializedCallback(OspApplicationInitialized p)
{
    sm_pApplicationInitialized = p;
}

void
OspApplication::SetScreenOrientation(Orientation orientation)
{
    sm_eScreenOrientation = orientation;
}

OspApplication*
OspApplication::GetInstance(void)
{
    CCAssert(sm_pSharedOspApplication, "");
    return sm_pSharedOspApplication;
}

Tizen::Ui::Controls::Form*
OspApplication::getOspForm()
{
    return __pForm;
}

bool
OspApplication::OnAppInitializing(AppRegistry& appRegistry)
{
    CCLOG("OnAppInitializing");

    result r = E_SUCCESS;

    __pFrame = new (std::nothrow) Frame();
    TryReturn(__pFrame != null, E_FAILURE, "[OspApplication] Generating a frame failed.");

    r = __pFrame->Construct();
    TryReturn(!IsFailed(r), E_FAILURE, "[OspApplication] pAppFrame->Construct() failed.");

    this->AddFrame(*__pFrame);

    __pForm = new (std::nothrow) OspForm;
    TryCatch(__pForm != null, , "[OspApplication] Allocation of OspForm failed.");

    r = __pForm->Construct(FORM_STYLE_NORMAL);
    TryCatch(!IsFailed(r), , "[OspApplication] __pForm->Construct(FORM_STYLE_NORMAL) failed.");

    r = GetAppFrame()->GetFrame()->AddControl(*__pForm);
    TryCatch(!IsFailed(r), , "[OspApplication] GetAppFrame()->GetFrame()->AddControl(*__pForm) failed.");

    return true;

CATCH:
    delete __pForm;
    __pForm = null;

    return false;
}

bool
OspApplication::OnAppInitialized(void)
{
    sm_pApplicationInitialized();
    __pFrame->SetOrientation(sm_eScreenOrientation);
    return true;
}

bool
OspApplication::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
    EGLView::getInstance()->cleanup();

    return true;
}

void
OspApplication::OnForeground(void)
{
    Tizen::Base::Runtime::Timer* timer = EGLView::getInstance()->getTimer();

    if (timer != null)
    {
        timer->Start(cocos2d::Application::getInstance()->getAnimationInterval());
    }

    if (Director::getInstance()->getOpenGLView())
    {
        cocos2d::Application::getInstance()->applicationWillEnterForeground();
    }
}

void
OspApplication::OnBackground(void)
{
    Tizen::Base::Runtime::Timer* timer = EGLView::getInstance()->getTimer();

    if (timer != null)
    {
        timer->Cancel();
    }

    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

void
OspApplication::OnLowMemory(void)
{
}

void
OspApplication::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}

void
OspApplication::OnScreenOn(void)
{
}

void
OspApplication::OnScreenOff(void)
{
}
