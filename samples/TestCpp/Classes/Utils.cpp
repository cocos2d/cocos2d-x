#include "Utils.h"
#include "cocos2d.h"

USING_NS_CC;

float getScaleFactor()
{
	float fScaleFactor = 1.0f; // scale factor is relative to 480*320 screen size.
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    if (winSize.width > 1024)
    {
        fScaleFactor = 2 * MIN(1024.0f/480.0f, 768.0f/320.0f);
    }
    else if (winSize.width > 960)
    {
    	fScaleFactor = MIN(1024.0f/480.0f, 768.0f/320.0f);
    }
    else if (winSize.width > 480)
    {
        fScaleFactor = 2.0f;
    }
    else
    {
    	fScaleFactor = 1.0f;
    }
    return fScaleFactor;
}