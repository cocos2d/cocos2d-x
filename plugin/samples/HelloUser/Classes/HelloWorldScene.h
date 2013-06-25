#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    void testLogin(Object* pSender);
    void testLogout(Object* pSender);
    
    void caseChanged(Object* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::MenuItemToggle* _caseItem;
    int _selectedCase;
};

#endif // __HELLOWORLD_SCENE_H__
