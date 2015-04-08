//
//  Bug-Child.h
//  cocos2d_tests
//
//  Created by NiTe Luo on 5/12/14.
//
//

#ifndef __Bug_Child__
#define __Bug_Child__

#include "BugsTest.h"

class BugChild : public BugsTestBase
{
public:
    CREATE_FUNC(BugChild);

    virtual bool init() override;
    
    void switchChild(Ref* sender);
    
protected:
    
    Sprite* parent1;
    Sprite* parent2;
    
    Sprite* child;
    
    Menu* menu;
};

#endif /* defined(__Bug_Child__) */
