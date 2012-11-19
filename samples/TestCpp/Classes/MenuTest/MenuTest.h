#ifndef _MENU_TEST_H_
#define _MENU_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class MenuLayerMainMenu : public CCLayer
{
protected:
    CCMenuItem*    m_disabledItem;

public:
    MenuLayerMainMenu(void);
    ~MenuLayerMainMenu();

public:
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

    void allowTouches(float dt);
    void menuCallback(CCObject* pSender);
    void menuCallbackConfig(CCObject* pSender);
    void menuCallbackDisabled(CCObject* pSender);
    void menuCallbackEnable(CCObject* pSender);
    void menuCallback2(CCObject* pSender);
    void menuCallbackPriorityTest(CCObject* pSender);
    void onQuit(CCObject* pSender);

    //CREATE_NODE(MenuLayer1);
};

class MenuLayer2 : public CCLayer
{
protected:
    CCPoint        m_centeredMenu;
    bool                m_alignedH; 

    void alignMenusH();
    void alignMenusV();

public:
    MenuLayer2(void);
    ~MenuLayer2();

public:
    void menuCallback(CCObject* pSender);
    void menuCallbackOpacity(CCObject* pSender);
    void menuCallbackAlign(CCObject* pSender);

    //CREATE_NODE(MenuLayer2);
};

class MenuLayer3 : public CCLayer
{
protected:
    CCMenuItem*    m_disabledItem;

public:
    MenuLayer3(void);
    ~MenuLayer3();

public:
    void menuCallback(CCObject* pSender);
    void menuCallback2(CCObject* pSender);
    void menuCallback3(CCObject* pSender);

    //CREATE_NODE(MenuLayer3);
};

class MenuLayer4 : public CCLayer
{
public:
    MenuLayer4(void);
    ~MenuLayer4();

public:
    void menuCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    //CREATE_NODE(MenuLayer4);
};

class MenuLayerPriorityTest : public CCLayer
{
public:
    MenuLayerPriorityTest();
    ~MenuLayerPriorityTest();

    void menuCallback(CCObject* pSender);
    void disableMenuCallback(CCObject* pSender);
    void enableMenuCallback();
    void togglePriorityCallback(CCObject* pSender);
private:
    CCMenu* m_pMenu1;
    CCMenu* m_pMenu2;
    bool m_bPriority;
};


class MenuTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
