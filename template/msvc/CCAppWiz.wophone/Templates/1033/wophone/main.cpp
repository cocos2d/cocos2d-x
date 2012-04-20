#include  "AppDelegate.h"

Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
    AppDelegate app;

    cocos2d::CCApplication::sharedApplication().Run();
    return 1;
}
