#ifndef _MENU_TEST_H_
#define _MENU_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class MenuLayerMainMenu : public Layer
{
protected:
    MenuItem*    _disabledItem;

public:
    MenuLayerMainMenu(void);
    ~MenuLayerMainMenu();

public:
    virtual bool ccTouchBegan(Touch *touch, Event * pEvent);
    virtual void ccTouchEnded(Touch *touch, Event * pEvent);
    virtual void ccTouchCancelled(Touch *touch, Event * pEvent);
    virtual void ccTouchMoved(Touch *touch, Event * pEvent);

    void allowTouches(float dt);
    void menuCallback(Object* pSender);
    void menuCallbackConfig(Object* pSender);
    void menuCallbackDisabled(Object* pSender);
    void menuCallback2(Object* pSender);
    void menuCallbackPriorityTest(Object* pSender);
    void menuCallbackBugsTest(Object *pSender);
    void onQuit(Object* pSender);
    void menuMovingCallback(Object *pSender);

    //CREATE_NODE(MenuLayer1);
};

class MenuLayer2 : public Layer
{
protected:
    Point        _centeredMenu;
    bool                _alignedH; 

    void alignMenusH();
    void alignMenusV();

public:
    MenuLayer2(void);
    ~MenuLayer2();

public:
    void menuCallback(Object* pSender);
    void menuCallbackOpacity(Object* pSender);
    void menuCallbackAlign(Object* pSender);

    //CREATE_NODE(MenuLayer2);
};

class MenuLayer3 : public Layer
{
protected:
    MenuItem*    _disabledItem;

public:
    MenuLayer3(void);
    ~MenuLayer3();

    //CREATE_NODE(MenuLayer3);
};

class MenuLayer4 : public Layer
{
public:
    MenuLayer4(void);
    ~MenuLayer4();

public:
    void menuCallback(Object* pSender);
    void backCallback(Object* pSender);

    //CREATE_NODE(MenuLayer4);
};

class MenuLayerPriorityTest : public Layer
{
public:
    MenuLayerPriorityTest();
    ~MenuLayerPriorityTest();

    void menuCallback(Object* pSender);
private:
    Menu* _menu1;
    Menu* _menu2;
    bool _priority;
};

class BugsTest : public Layer
{
public:
    BugsTest();
    
    void issue1410MenuCallback(Object *pSender);
    void issue1410v2MenuCallback(Object *pSender);
    void backMenuCallback(Object *pSender);
};

class RemoveMenuItemWhenMove : public Layer
{
public:
    RemoveMenuItemWhenMove();
    ~RemoveMenuItemWhenMove();
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
    
    void goBack(Object *pSender);
    
private:
    MenuItemFont *item;
};


class MenuTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
