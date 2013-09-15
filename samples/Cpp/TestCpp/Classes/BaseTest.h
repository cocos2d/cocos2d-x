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

class BaseTest : public cocos2d::Layer
{
public:
    virtual void onEnter();
    virtual void onExit();

    virtual std::string title();
    virtual std::string subtitle();

	virtual void restartCallback(Object* sender);
	virtual void nextCallback(Object* sender);
	virtual void backCallback(Object* sender);
};


#endif /* defined(__TestCpp__BaseTest__) */
