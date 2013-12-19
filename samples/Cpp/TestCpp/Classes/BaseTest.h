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
    virtual std::string title() const;
    virtual std::string subtitle() const;

	virtual void restartCallback(Object* sender);
	virtual void nextCallback(Object* sender);
	virtual void backCallback(Object* sender);

    virtual void onEnter() override;
    virtual void onExit() override;
};


#endif /* defined(__TestCpp__BaseTest__) */
