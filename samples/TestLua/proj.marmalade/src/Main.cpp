// Application main file.

#include "Main.h"
#include "../Classes/AppDelegate.h"

// Cocos2dx headers
#include "cocos2d.h"

// Marmalade headers
#include "IwGL.h"

USING_NS_CC;

int main()
{
	AppDelegate app;

	return cocos2d::CCApplication::sharedApplication()->Run();
}
