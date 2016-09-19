#ifndef __cocos2d_tests__Bug_12847__
#define __cocos2d_tests__Bug_12847__

#include "BugsTest.h"

class Bug12847Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug12847Layer);
    
    virtual bool init() override;
    
protected:
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
private:
    
    cocos2d::Sprite* sprite1;
    cocos2d::Sprite* sprite2;
    cocos2d::Sprite* sprite3;
    cocos2d::Sprite* sprite4;
};

#endif /* defined(__cocos2d_tests__Bug_12847__) */
