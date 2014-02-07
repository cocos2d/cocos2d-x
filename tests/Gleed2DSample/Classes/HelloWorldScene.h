//
//  HelloWorldScene.h
//  CuteAPultCocos2D-x
//
//  Created by Clawoo on 9/8/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#ifndef __HELLO_m_worldH__
#define __HELLO_m_worldH__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer{
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::Scene* scene();
    
	virtual bool init();
	
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLO_m_worldH__
