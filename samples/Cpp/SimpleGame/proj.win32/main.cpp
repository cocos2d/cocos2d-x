#include "main.h"
#include "../Classes/AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

#ifdef __MINGW32__
int main(int argc, char **argv)
{
#else
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR lpCmdLine,
                     _In_ int nShowCmdw)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
#endif

    // create the application instance
    AppDelegate app;
    EGLView eglView;
    eglView.init("SimpleGame",900,640);
    return Application::getInstance()->run();
}
