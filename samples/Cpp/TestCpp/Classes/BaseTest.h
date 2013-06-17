//
//  BaseTest.h
//  TestCpp
//
//  Created by Ricardo Quesada on 6/6/13.
//
//

#ifndef __TestCpp__BaseTest__
#define __TestCpp__BaseTest__

#include "cocos2d.h"

class BaseTest : public cocos2d::CCLayer
{
public:
    virtual void onEnter();
    virtual void onExit();

    virtual std::string title();
    virtual std::string subtitle();

	virtual void restartCallback(CCObject* pSender);
	virtual void nextCallback(CCObject* pSender);
	virtual void backCallback(CCObject* pSender);
};


#endif /* defined(__TestCpp__BaseTest__) */
