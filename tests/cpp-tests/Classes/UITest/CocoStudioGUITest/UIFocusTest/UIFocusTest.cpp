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
        leftItem->setPosition(Vec2(winSize.width - 100, winSize.height/2));
        _dpadMenu->addChild(leftItem);
        
        
        auto rightItem = MenuItemFont::create("Right", CC_CALLBACK_0(UIFocusTestBase::onRightKeyPressed, this));
        rightItem->setPosition(Vec2(winSize.width - 30, winSize.height/2));
        _dpadMenu->addChild(rightItem);
        
        auto upItem = MenuItemFont::create("Up", CC_CALLBACK_0(UIFocusTestBase::onUpKeyPressed, this));
        upItem->setPosition(Vec2(winSize.width - 60, winSize.height/2 + 50));
        _dpadMenu->addChild(upItem);
        
        auto downItem = MenuItemFont::create("Down", CC_CALLBACK_0(UIFocusTestBase::onDownKeyPressed, this));
        downItem->setPosition(Vec2(winSize.width - 60, winSize.height/2 - 50));
        _dpadMenu->addChild(downItem);
        
        _dpadMenu->setPosition(Vec2::ZERO);
        _uiLayer->addChild(_dpadMenu);
        
        //call this method to enable Dpad focus navigation
        Widget::enableDpadNavigation(true);
        
        _eventListener = EventListenerFocus::create();
        _eventListener->onFocusChanged = CC_CALLBACK_2(UIFocusTestBase::onFocusChanged, this);
        
        _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
        
        return true;
    }
    
    return false;
}

void UIFocusTestBase::onImageViewClicked(cocos2d::Ref *ref, Widget::TouchEventType touchType)
{
    if (touchType == Widget::TouchEventType::ENDED) {
        Widget *w = (Widget*)ref;
        if (w->isFocusEnabled()) {
            w->setFocusEnabled(false);
            w->setColor(Color3B::YELLOW);
        }else{
            w->setFocusEnabled(true);
            w->setColor(Color3B::WHITE);
        }
    }
}

void UIFocusTestBase::onLeftKeyPressed()
{
    cocos2d::EventKeyboard::KeyCode cocos2dKey =EventKeyboard::KeyCode::KEY_DPAD_LEFT;
    cocos2d::EventKeyboard event(cocos2dKey, false);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIFocusTestBase::onRightKeyPressed()
{
    cocos2d::EventKeyboard::KeyCode cocos2dKey =EventKeyboard::KeyCode::KEY_DPAD_RIGHT;
    cocos2d::EventKeyboard event(cocos2dKey, false);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void UIFocusTestBase::onUpKeyPressed()
{
    cocos2d::EventKeyboard::KeyCode cocos2dKey =EventKeyboard::KeyCode::KEY_DPAD_UP;
    cocos2d::EventKeyboard event(cocos2dKey, false);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    
}

void UIFocusTestBase::onDownKeyPressed()
{
    cocos2d::EventKeyboard::KeyCode cocos2dKey =EventKeyboard::KeyCode::KEY_DPAD_DOWN;
    cocos2d::EventKeyboard event(cocos2dKey, false);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    
}

void UIFocusTestBase::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    if (widgetGetFocus && widgetGetFocus->isFocusEnabled()) {
        widgetGetFocus->setColor(Color3B::RED);
    }
    
    if (widgetLostFocus && widgetLostFocus->isFocusEnabled()) {
        widgetLostFocus->setColor(Color3B::WHITE);
    }
    
    if (widgetLostFocus && widgetGetFocus) {
        CCLOG("on focus change, %d widget get focus, %d widget lose focus", widgetGetFocus->getTag(),  widgetLostFocus->getTag());
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
        _horizontalLayout->setPosition(Vec2(20, winSize.height/2 + 40));
        _uiLayer->addChild(_horizontalLayout);
        
        _horizontalLayout->setFocused(true);
        _horizontalLayout->setLoopFocus(true);
        _horizontalLayout->setTag(100);
        _firstFocusedWidget = _horizontalLayout;
        
        int count = 3;
        for (int i=0; i<count; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setTouchEnabled(true);
            w->setTag(i);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestHorizontal::onImageViewClicked, this));
            _horizontalLayout->addChild(w);
        }
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vec2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vec2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(CC_CALLBACK_2(UIFocusTestHorizontal::toggleFocusLoop,this));
        this->addChild(btn);
      
        
        return true;
    }
    return false;
}




void UIFocusTestHorizontal::toggleFocusLoop(cocos2d::Ref * pObjc, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _horizontalLayout->setLoopFocus(!_horizontalLayout->isLoopFocus());
        if (_horizontalLayout->isLoopFocus()) {
            _loopText->setString("loop enabled");
        }else{
            _loopText->setString("loop disabled");
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
        _verticalLayout->setPosition(Vec2(winSize.width/2 - 100, winSize.height - 70));
        _uiLayer->addChild(_verticalLayout);
        _verticalLayout->setTag(100);
        _verticalLayout->setScale(0.5);
        
        _verticalLayout->setFocused(true);
        _verticalLayout->setLoopFocus(true);
        _firstFocusedWidget = _verticalLayout;
        
        int count = 3;
        for (int i=0; i<count; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setTouchEnabled(true);
            w->setTag(i);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestVertical::onImageViewClicked, this));
            _verticalLayout->addChild(w);
            if (i == 2) {
                w->requestFocus();
            }
        }
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vec2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vec2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(CC_CALLBACK_2(UIFocusTestVertical::toggleFocusLoop, this));
        this->addChild(btn);
        
        
        return true;
    }
    return false;
}


void UIFocusTestVertical::toggleFocusLoop(cocos2d::Ref * pObjc, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _verticalLayout->setLoopFocus(!_verticalLayout->isLoopFocus());
        if (_verticalLayout->isLoopFocus()) {
            _loopText->setString("loop enabled");
        }else{
            _loopText->setString("loop disabled");
        }
    }
}

//UIFocusTestNestedLayout1
UIFocusTestNestedLayout1::UIFocusTestNestedLayout1()
{
    
}

UIFocusTestNestedLayout1::~UIFocusTestNestedLayout1()
{
    
}

bool UIFocusTestNestedLayout1::init()
{
    if (UIFocusTestBase::init()) {
        
        Size winSize = Director::getInstance()->getVisibleSize();
        
        _verticalLayout = VBox::create();
        _verticalLayout->setPosition(Vec2(winSize.width/2 - 80, winSize.height - 70));
        _uiLayer->addChild(_verticalLayout);
        _verticalLayout->setScale(0.5);
        
        _verticalLayout->setFocused(true);
        _verticalLayout->setLoopFocus(true);
        _verticalLayout->setTag(100);
        _firstFocusedWidget = _verticalLayout;
        
        int count1 = 1;
        for (int i=0; i<count1; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setAnchorPoint(Vec2::ZERO);
            w->setTouchEnabled(true);
            w->setScaleX(2.5);
            w->setTag(i+count1);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout1::onImageViewClicked, this));
            _verticalLayout->addChild(w);
        }
        
        //add HBox into VBox
        HBox *hbox = HBox::create();
        hbox->setScale(0.8f);
        hbox->setTag(101);
        _verticalLayout->addChild(hbox);
        
        int count2 = 2;
        for (int i=0; i < count2; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setAnchorPoint(Vec2(0,1));
            w->setScaleY(2.0);
            w->setTouchEnabled(true);
            w->setTag(i+count1+count2);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout1::onImageViewClicked, this));
            hbox->addChild(w);
        }
        
        VBox *innerVBox = VBox::create();
        hbox->addChild(innerVBox);
        innerVBox->setTag(102);
//        innerVBox->setPassFocusToChild(false);
//        innerVBox->setFocusEnabled(false);
       
        
        int count3 = 2;
        for (int i=0; i<count3; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setTouchEnabled(true);
            w->setTag(i+count1+count2+count3);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout1::onImageViewClicked, this));
            innerVBox->addChild(w);
        }

        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vec2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vec2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout1::toggleFocusLoop, this));
        this->addChild(btn);
        
        
        return true;
    }
    return false;
}


void UIFocusTestNestedLayout1::toggleFocusLoop(cocos2d::Ref * pObjc, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _verticalLayout->setLoopFocus(!_verticalLayout->isLoopFocus());
        if (_verticalLayout->isLoopFocus()) {
            _loopText->setString("loop enabled");
        }else{
            _loopText->setString("loop disabled");
        }
    }
}

//UIFocusTestNestedLayout2
UIFocusTestNestedLayout2::UIFocusTestNestedLayout2()
{
    
}

UIFocusTestNestedLayout2::~UIFocusTestNestedLayout2()
{
    
}

bool UIFocusTestNestedLayout2::init()
{
    if (UIFocusTestBase::init()) {
        
        Size winSize = Director::getInstance()->getVisibleSize();
        
        _horizontalLayout = HBox::create();
        _horizontalLayout->setPosition(Vec2(winSize.width/2 - 200, winSize.height - 70));
        _uiLayer->addChild(_horizontalLayout);
        _horizontalLayout->setScale(0.6f);
        
        _horizontalLayout->setFocused(true);
        _horizontalLayout->setLoopFocus(true);
        _horizontalLayout->setTag(100);
        _firstFocusedWidget = _horizontalLayout;
        
        int count1 = 2;
        for (int i=0; i<count1; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setAnchorPoint(Vec2(0,1));
            w->setTouchEnabled(true);
            w->setTag(i+count1);
            w->setScaleY(2.4f);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout2::onImageViewClicked, this));
            _horizontalLayout->addChild(w);
        }
        
        //add HBox into VBox
        VBox *vbox = VBox::create();
        vbox->setScale(0.8f);
        vbox->setTag(101);
        _horizontalLayout->addChild(vbox);
        
        int count2 = 2;
        for (int i=0; i < count2; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setAnchorPoint(Vec2(0,1));
            w->setScaleX(2.0);
            w->setTouchEnabled(true);
            w->setTag(i+count1+count2);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout2::onImageViewClicked, this));
            vbox->addChild(w);
        }
        
        HBox *innerHBox = HBox::create();
        vbox->addChild(innerHBox);
        innerHBox->setTag(102);
        //        innerVBox->setPassFocusToChild(false);
        //        innerVBox->setFocusEnabled(false);
        
        
        int count3 = 2;
        for (int i=0; i<count3; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setTouchEnabled(true);
            w->setTag(i+count1+count2+count3);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout2::onImageViewClicked, this));
            innerHBox->addChild(w);
        }
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vec2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vec2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout2::toggleFocusLoop, this));
        this->addChild(btn);
        
        
        return true;
    }
    return false;
}


void UIFocusTestNestedLayout2::toggleFocusLoop(cocos2d::Ref * pObjc, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _horizontalLayout->setLoopFocus(!_horizontalLayout->isLoopFocus());
        if (_horizontalLayout->isLoopFocus()) {
            _loopText->setString("loop enabled");
        }else{
            _loopText->setString("loop disabled");
        }
    }
}

//UIFocusTestNestedLayout3
UIFocusTestNestedLayout3::UIFocusTestNestedLayout3()
{
    
}

UIFocusTestNestedLayout3::~UIFocusTestNestedLayout3()
{
    
}

bool UIFocusTestNestedLayout3::init()
{
    if (UIFocusTestBase::init()) {
        
        Size winSize = Director::getInstance()->getVisibleSize();
        
        _verticalLayout = VBox::create();
        _verticalLayout->setPosition(Vec2(40, winSize.height - 70));
        _uiLayer->addChild(_verticalLayout);
        _verticalLayout->setScale(0.8f);
        
        _verticalLayout->setFocused(true);
        _verticalLayout->setLoopFocus(true);
        _verticalLayout->setTag(-1000);
        _firstFocusedWidget = _verticalLayout;
        
        
        HBox *upperHBox = HBox::create();
        upperHBox->setTag(-200);
        _verticalLayout->addChild(upperHBox);
        
        LinearLayoutParameter *params = LinearLayoutParameter::create();
        params->setMargin(Margin(0,0,50,0));
        
        LinearLayoutParameter *vparams = LinearLayoutParameter::create();
        vparams->setMargin(Margin(10, 0, 0, 140));
        upperHBox->setLayoutParameter(vparams);
        
        int count = 3;
        for (int i=0; i<count; ++i) {
            VBox *firstVbox = VBox::create();
            firstVbox->setScale(0.5);
            firstVbox->setLayoutParameter(params);
            firstVbox->setTag((i+1) * 100);
            
            int count1 = 3;
            for (int j=0; j<count1; ++j) {
                ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
                w->setTouchEnabled(true);
                w->setTag(j+firstVbox->getTag()+1);
                w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestBase::onImageViewClicked, this));
                firstVbox->addChild(w);
            }
            
            upperHBox->addChild(firstVbox);

        }
        
        HBox *bottomHBox = HBox::create();
        bottomHBox->setScale(0.5);
        bottomHBox->setTag(600);
        
        bottomHBox->setLayoutParameter(vparams);
        count = 3;
        LinearLayoutParameter *bottomParams = LinearLayoutParameter::create();
        bottomParams->setMargin(Margin(0, 0, 8, 0));
        for (int i=0; i < count; ++i) {
            ImageView *w = ImageView::create("cocosui/scrollviewbg.png");
            w->setLayoutParameter(bottomParams);
            w->setTouchEnabled(true);
            w->setTag(i+601);
            w->addTouchEventListener(CC_CALLBACK_2(UIFocusTestBase::onImageViewClicked, this));
            bottomHBox->addChild(w);
        }
        _verticalLayout->addChild(bottomHBox);
        
     
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vec2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vec2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(CC_CALLBACK_2(UIFocusTestNestedLayout3::toggleFocusLoop, this));
        this->addChild(btn);
        
        
        return true;
    }
    return false;
}


void UIFocusTestNestedLayout3::toggleFocusLoop(cocos2d::Ref * pObjc, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _verticalLayout->setLoopFocus(!_verticalLayout->isLoopFocus());
        if (_verticalLayout->isLoopFocus()) {
            _loopText->setString("loop enabled");
        }else{
            _loopText->setString("loop disabled");
        }
    }
}

//UIFocusTestListView
UIFocusTestListView::UIFocusTestListView()
{
    
}

UIFocusTestListView::~UIFocusTestListView()
{
    
}

bool UIFocusTestListView::init()
{
    if (UIFocusTestBase::init()) {
        
        Size winSize = Director::getInstance()->getVisibleSize();
        
        _listView = ListView::create();
        _listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        _listView->setBounceEnabled(true);
        _listView->setBackGroundImage("cocosui/green_edit.png");
        _listView->setBackGroundImageScale9Enabled(true);
        _listView->setContentSize(Size(240, 130));
        
        _listView->setPosition(Vec2(40, 70));
        _uiLayer->addChild(_listView);
        _listView->setScale(0.8f);
        
        _listView->setFocused(true);
        _listView->setLoopFocus(true);
        _listView->setTag(-1000);
        _firstFocusedWidget = _listView;
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        
        // set model
        _listView->setItemModel(default_button);
        
        // add default item
        ssize_t count = 20;
        for (int i = 0; i < count / 4; ++i)
        {
            _listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            _listView->insertDefaultItem(0);
        }
        
        
        
        _loopText = Text::create("loop enabled", "Airal", 20);
        _loopText->setPosition(Vec2(winSize.width/2, winSize.height - 50));
        _loopText->setColor(Color3B::GREEN);
        this->addChild(_loopText);
        
        auto btn = Button::create("cocosui/switch-mask.png");
        btn->setTitleText("Toggle Loop");
        btn->setPosition(Vec2(60, winSize.height - 50));
        btn->setTitleColor(Color3B::RED);
        btn->addTouchEventListener(CC_CALLBACK_2(UIFocusTestListView::toggleFocusLoop, this));
        this->addChild(btn);
        
        
        return true;
    }
    return false;
}


void UIFocusTestListView::toggleFocusLoop(cocos2d::Ref * pObjc, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        _listView->setLoopFocus(!_listView->isLoopFocus());
        if (_listView->isLoopFocus()) {
            _loopText->setString("loop enabled");
        }else{
            _loopText->setString("loop disabled");
        }
    }
}
