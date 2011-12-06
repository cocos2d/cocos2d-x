#include "cocos2d.h"
#include "AppDelegate.h"

#define RESOURCE_PATH        "./app/native/Res"

USING_NS_CC;

int main(int argc, char **argv)
{
	AppDelegate* app;
	int ret = 0;

    CCFileUtils::setResourcePath(RESOURCE_PATH);

	app = new AppDelegate();
	ret = cocos2d::CCApplication::sharedApplication().run();
	delete app;

	return ret;
}
