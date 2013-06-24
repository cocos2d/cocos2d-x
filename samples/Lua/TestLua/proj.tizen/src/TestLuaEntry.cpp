//
// This file contains the Tizen application entry point.
//
#include "../../Classes/AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void
ApplicationInitialized(void)
{
    AppDelegate* pAppDelegate = new AppDelegate;

    EGLView* eglView = EGLView::sharedOpenGLView();
    eglView->setFrameSize(1280, 720);

    Application::sharedApplication()->run();
}

//
// The entry function of Tizen application called by the operating system.
//
_EXPORT_ int
OspMain(int argc, char *pArgv[])
{
    AppLog("Application started.");
    ArrayList args(SingleObjectDeleter);
    args.Construct();
    for (int i = 0; i < argc; i++)
    {
        args.Add(new (std::nothrow) Tizen::Base::String(pArgv[i]));
    }

    OspApplication::SetApplicationInitializedCallback(ApplicationInitialized);
    OspApplication::SetScreenOrientation(Tizen::Ui::ORIENTATION_LANDSCAPE);
    result r = Tizen::App::Application::Execute(OspApplication::CreateInstance, &args);
    TryLog(r == E_SUCCESS, "[%s] Application execution failed", GetErrorMessage(r));
    AppLog("Application finished.");

    return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
