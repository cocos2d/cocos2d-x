

//
//  AdvanceSpriteTest.h
//  test
//
//  Created by varadharaj on 16/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef _ADVANCESPRITE_TEST_H
#define _ADVANCESPRITE_TEST_H

#include "AdvanceSprite.h"
#include "../testBasic.h"

class AdvanceSpriteTest : public CCLayer
{
protected:
    AdvanceSprite *m_pAdvanceSprite;
    
public:
    AdvanceSpriteTest();
    ~AdvanceSpriteTest();
    
    virtual void onEnter(void);
	virtual std::string title();
};

class AdvanceSpriteScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif