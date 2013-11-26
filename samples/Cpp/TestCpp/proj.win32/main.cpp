#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

#ifdef __MINGW32__
int main(int argc, char **argv)
{
#else
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
#endif

    // create the application instance
    AppDelegate app;
    EGLView eglView;
    eglView.init("TestCPP",960,640);
    return Application::getInstance()->run();
}
