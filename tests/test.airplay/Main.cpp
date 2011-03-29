// Application main file.

#include "Main.h"
#include "AppDelegate.h"


int main()
{
	AppDelegate* app;
	int nRet = 0;
	
	app = new AppDelegate;
	nRet = cocos2d::CCApplication::sharedApplication().Run();;
	delete app;
	return nRet;
}
