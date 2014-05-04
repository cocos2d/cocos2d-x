//
//  UIFocusTest.cpp
//  cocos2d_tests
//
//  Created by guanghui on 5/4/14.
//
//

#include "UIFocusTest.h"

UIFocusTestBase::UIFocusTestBase()
{
    
}

UIFocusTestBase::~UIFocusTestBase()
{
    _eventDispatcher->removeEventListener(_eventListener);
}

bool UIFocusTestBase::init()
{
    if (UIScene::init()) {
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        background->removeFromParentAndCleanup(true);
        
        _dpadMenu = Menu::create();
        
        auto winSize = Director::getInstance()->getVisibleSize();
        auto leftItem = MenuItemFont::create("Left", CC_CALLBACK_0(UIFocusTestBase::onLeftKeyPressed, this));
        leftItem->setPosition(Vector2(winSize.width - 100, winSize.height/2));
        _dpadMenu->addChild(leftItem);
        
        
        auto rightItem = MenuItemFont::create("Right", CC_CALLBACK_0(UIFocusTestBase::onRightKeyPressed, this));
        rightItem->setPosition(Vector2(winSize.width - 30, winSize.height/2));
        _dpadMenu->addChild(rightItem);
        
        auto upItem = MenuItemFont::create("Up", CC_CALLBACK_0(UIFocusTestBase::onUpKeyPressed, this));
        upItem->setPosition(Vector2(winSize.width - 60, winSize.height/2 + 50));
        _dpadMenu->addChild(upItem);
        
        auto downItem = MenuItemFont::create("Down", CC_CALLBACK_0(UIFocusTestBase::onDownKeyPressed, this));
        downItem->setPosition(Vector2(winSize.width - 60, winSize.height/2 - 50));
        _dpadMenu->addChild(downItem);
        
        _dpadMenu->setPosition(Vector2::ZERO);
        _uiLayer->addChild(_dpadMenu);
        
        _eventListener = EventListenerFocus::create();
        _eventListener->onFocusChanged = CC_CALLBACK_2(UIFocusTestBase::onFocusChanged, this);
        
        _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
        
        return true;
    }
    
    return false;
}


//UIFocusTestHorizontal
UIFocusTestHorizontal::UIFocusTestHorizontal()
{
    
}

UIFocusTestHorizontal::~UIFocusTestHorizontal()
{
    
}

bool UIFocusTestHorizontal::init()
{
    if (UIFocusTestBase::init()) {
        
        Size winSize = Director::getInstance()->getVisibleSize();
        
        HBox *layout = HBox::create();
        layout->setPosition(Vector2(20, winSize.height/2 + 40));
        _uiLayer->addChild(layout);
        layout->setFocused(true);
        _firstFocusedWidget = layout;
        
        int count = 3;
        for (int i=0; i<count; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            layout->addChild(w);
        }
        
        
      
        
        return true;
    }
    return false;
}

void UIFocusTestHorizontal::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    //only change the widgets' state
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus) {
        widgetGetFocus->setScale(1.2);
        widgetGetFocus->setColor(Color3B::RED);
    }
    
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus) {
        widgetLostFocus->setScale(1.0);
        widgetLostFocus->setColor(Color3B::WHITE);
    }
}

void UIFocusTestHorizontal::onLeftKeyPressed()
{
    _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Left, _firstFocusedWidget);
}

void UIFocusTestHorizontal::onRightKeyPressed()
{
    _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Right, _firstFocusedWidget);
}

void UIFocusTestHorizontal::onUpKeyPressed()
{
    _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Up, _firstFocusedWidget);

}

void UIFocusTestHorizontal::onDownKeyPressed()
{
    _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Down, _firstFocusedWidget);

}