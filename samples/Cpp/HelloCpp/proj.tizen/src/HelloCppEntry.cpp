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

/**
 * This file contains the Tizen C++ application entry point.
 */
#include "../../Classes/AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

_EXPORT_ int OspMain(int argc, char* pArgv[]);
void ApplicationInitialized(void);

/**
 * The entry function of Tizen C++ application called by the operating system.
 */
int
OspMain(int argc, char* pArgv[])
{
    AppLog("Application started.");
    ArrayList args;
    args.Construct();

    for (int i = 0; i < argc; i++)
    {
        args.Add(*(new (std::nothrow) String(pArgv[i])));
    }

    CCOspApplication::SetApplicationInitializedCallback(ApplicationInitialized);
    result r = Tizen::App::Application::Execute(CCOspApplication::CreateInstance, &args);

    TryLog(r == E_SUCCESS, "[%s] Application execution failed", GetErrorMessage(r));

    args.RemoveAll(true);
    AppLog("Application finished.");

    return static_cast<int>(r);
}

void
ApplicationInitialized(void)
{
    AppDelegate* pAppDelegate = new AppDelegate;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(720, 1280);

    CCApplication::sharedApplication()->run();
}


#ifdef __cplusplus
}
#endif // __cplusplus
