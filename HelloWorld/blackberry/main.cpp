#include "cocos2d.h"
#include "AppDelegate.h"


USING_NS_CC;

int main(int argc, char **argv)
{
	AppDelegate* app;
	int ret = 0;
	app = new AppDelegate();
	ret = cocos2d::CCApplication::sharedApplication().run();
	delete app;

	return ret;
}
