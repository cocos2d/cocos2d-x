#include "TG3.h"
#include "../AppDelegate.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	AppDelegate app;

#ifndef _TRANZDA_VM_  // on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
	cocos2d::CCFileUtils::setResource("TestCocos2dx.zip");
	CocosDenshion::SimpleAudioEngine::setResource("TestCocos2dx.zip");
#endif

	app.Run();

	return 1;
}
