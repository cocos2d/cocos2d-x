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

void UIFocusTestBase::onImageViewClicked(cocos2d::Ref *ref, TouchEventType touchType)
{
    if (touchType == TouchEventType::TOUCH_EVENT_ENDED) {
        Widget *w = (Widget*)ref;
        if (w->isFocusEnabled()) {
            w->setFocusEnabled(false);
            w->setColor(Color3B::WHITE);
            w->setScale(0.8);
        }else{
            w->setFocusEnabled(true);
            w->setScale(1.0);
        }
    }
}

void UIFocusTestBase::onLeftKeyPressed()
{
    if (_firstFocusedWidget) {
        _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Left, _firstFocusedWidget);
    }
}

void UIFocusTestBase::onRightKeyPressed()
{
    if (_firstFocusedWidget) {
        _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Right, _firstFocusedWidget);
    }
}

void UIFocusTestBase::onUpKeyPressed()
{
    if (_firstFocusedWidget) {
        _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Up, _firstFocusedWidget);
    }
    
}

void UIFocusTestBase::onDownKeyPressed()
{
    if (_firstFocusedWidget) {
        _firstFocusedWidget = _firstFocusedWidget->nextFocusedWidget(FocusDirection::FocusDirection_Down, _firstFocusedWidget);
    }
    
}

void UIFocusTestBase::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    //only change the widgets' state
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus && widgetGetFocus->isFocusEnabled()) {
        widgetGetFocus->setScale(1.2);
        widgetGetFocus->setColor(Color3B::RED);
    }
    
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus && widgetLostFocus->isFocusEnabled()) {
        widgetLostFocus->setScale(1.0);
        widgetLostFocus->setColor(Color3B::WHITE);
    }
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
        
        _horizontalLayout = HBox::create();
        _horizontalLayout->setPosition(Vector2(20, winSize.height/2 + 40));
        _uiLayer->addChild(_horizontalLayout);
        
        _horizontalLayout->setFocused(true);
        _horizontalLayout->setLoopFocus(true);
        _firstFocusedWidget = _horizontalLayout;
        
        int count = 3;
        for (int i=0; i<count; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setTouchEnabled(true);
            w->addTouchEventListener(this, toucheventselector(UIFocusTestHorizontal::onImageViewClicked));
            _horizontalLayout->addChild(w);
        }
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vector2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vector2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(this, toucheventselector(UIFocusTestHorizontal::toggleFocusLoop));
        this->addChild(btn);
      
        
        return true;
    }
    return false;
}




void UIFocusTestHorizontal::toggleFocusLoop(cocos2d::Ref * pObjc, TouchEventType type)
{
    if (type == TouchEventType::TOUCH_EVENT_ENDED) {
        _horizontalLayout->setLoopFocus(!_horizontalLayout->getLoopFocus());
        if (_horizontalLayout->getLoopFocus()) {
            _loopText->setText("loop enabled");
        }else{
            _loopText->setText("loop disabled");
        }
    }
}


//UIFocusTestVertical
UIFocusTestVertical::UIFocusTestVertical()
{
    
}

UIFocusTestVertical::~UIFocusTestVertical()
{
    
}

bool UIFocusTestVertical::init()
{
    if (UIFocusTestBase::init()) {
        
        Size winSize = Director::getInstance()->getVisibleSize();
        
        _verticalLayout = VBox::create();
        _verticalLayout->setPosition(Vector2(winSize.width/2 - 100, winSize.height - 70));
        _uiLayer->addChild(_verticalLayout);
        _verticalLayout->setScale(0.8);
        
        _verticalLayout->setFocused(true);
        _verticalLayout->setLoopFocus(true);
        _firstFocusedWidget = _verticalLayout;
        
        int count = 3;
        for (int i=0; i<count; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setTouchEnabled(true);
            w->addTouchEventListener(this, toucheventselector(UIFocusTestVertical::onImageViewClicked));
            _verticalLayout->addChild(w);
        }
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vector2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vector2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(this, toucheventselector(UIFocusTestHorizontal::toggleFocusLoop));
        this->addChild(btn);
        
        
        return true;
    }
    return false;
}


void UIFocusTestVertical::toggleFocusLoop(cocos2d::Ref * pObjc, TouchEventType type)
{
    if (type == TouchEventType::TOUCH_EVENT_ENDED) {
        _verticalLayout->setLoopFocus(!_verticalLayout->getLoopFocus());
        if (_verticalLayout->getLoopFocus()) {
            _loopText->setText("loop enabled");
        }else{
            _loopText->setText("loop disabled");
        }
    }
}

//UIFocusTestNestedLayout1
