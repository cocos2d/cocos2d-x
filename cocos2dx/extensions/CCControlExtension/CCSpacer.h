#ifndef __CCSPACER_H__
#define __CCSPACER_H__

#include "cocos2d.h"

USING_NS_CC;

class CC_DLL CCSpacer: public CCLayer
{
public:
	static CCSpacer* verticalSpacer(float space);
	static CCSpacer* horizontalSpacer(float space);
};


#endif