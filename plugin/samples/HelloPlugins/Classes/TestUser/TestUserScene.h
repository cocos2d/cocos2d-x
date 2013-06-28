#ifndef __TEST_USER_SCENE_H__
#define __TEST_USER_SCENE_H__

#include "cocos2d.h"

class TestUser : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuBackCallback(Object* pSender);
    void testLogin(Object* pSender);
    void testLogout(Object* pSender);
    
    void caseChanged(Object* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(TestUser);

private:
    cocos2d::MenuItemToggle* _caseItem;
    int _selectedCase;
};

#endif // __TEST_USER_SCENE_H__
