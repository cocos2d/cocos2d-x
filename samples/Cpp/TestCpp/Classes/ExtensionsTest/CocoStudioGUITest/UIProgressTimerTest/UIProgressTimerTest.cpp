

#include "UIProgressTimerTest.h"

// UIProgressTimerTest_Radial
bool UIProgressTimerTest_Radial::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer Radial");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* to1 = ProgressTo::create(2.0f, 100.0f);
        ProgressTo* to2 = ProgressTo::create(2.0f, 100.0f);
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 0.75f, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::RADIAL);
        left->getVirtualRenderer()->runAction(RepeatForever::create(to1));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 0.75f, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::RADIAL);
        // Makes the ridial CCW
        right->setReverseProgress(true);
        right->getVirtualRenderer()->runAction(RepeatForever::create(to2));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_Horizontal
bool UIProgressTimerTest_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer Horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* to1 = ProgressTo::create(2.0f, 100.0f);
        ProgressTo* to2 = ProgressTo::create(2.0f, 100.0f);
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 0.75f, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the left since the midpoint is 0 for the x
        left->setMidPoint(Point(0, 0));
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        left->setBarChangeRate(Point(1, 0));
        left->getVirtualRenderer()->runAction(RepeatForever::create(to1));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 0.75f, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the left since the midpoint is 1 for the x
        right->setMidPoint(Point(1, 0));
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        right->setBarChangeRate(Point(1, 0));
        right->getVirtualRenderer()->runAction(RepeatForever::create(to2));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_Vertical
bool UIProgressTimerTest_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* to1 = ProgressTo::create(2.0f, 100.0f);
        ProgressTo* to2 = ProgressTo::create(2.0f, 100.0f);
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 0.75f, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(Point(0, 0));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(Point(0, 1));
        left->getVirtualRenderer()->runAction(RepeatForever::create(to1));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 0.75f, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(Point(0, 1));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(Point(0, 1));
        right->getVirtualRenderer()->runAction(RepeatForever::create(to2));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_RadialMidpointChanged
bool UIProgressTimerTest_RadialMidpointChanged::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer Radial Midpoint Changed");
        alert->setFontName("Marker Felt");
        alert->setFontSize(17);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.325f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* action = ProgressTo::create(2.0f, 100.0f);
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 0.75f, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::RADIAL);
        left->setMidPoint(Point(0.25f, 0.75f));
        left->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)action->clone()));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 0.75f, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::RADIAL);
        right->setMidPoint(Point(0.75f, 0.25f));
        right->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)action->clone()));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_BarVarious
bool UIProgressTimerTest_BarVarious::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer Bar Various");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* to = ProgressTo::create(2.0f, 100.0f);
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 1.1, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(Point(1, 0));
        left->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* middle = gui::ProgressTimer::create();
        middle->loadTexture("cocosgui/potentiometerProgress.png");
        middle->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + middle->getSize().height / 6.0f));
        middle->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle->setBarChangeRate(Point(1, 1));
        middle->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        _uiLayer->addChild(middle);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 1.1, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(Point(0, 1));
        right->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_BarTintAndFade
bool UIProgressTimerTest_BarTintAndFade::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer Bar Tint and Fade");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.725f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* to = ProgressTo::create(6, 100.0f);
        Action* tint = Sequence::create(TintTo::create(1, 255, 0, 0),
                                        TintTo::create(1, 0, 255, 0),
                                        TintTo::create(1, 0, 0, 255),
                                        NULL);
        Action* fade = Sequence::create(FadeTo::create(1.0f, 0),
                                        FadeTo::create(1.0f, 255),
                                        NULL);
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 1.1, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(Point(1, 0));
        left->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        left->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)tint->clone()));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* middle = gui::ProgressTimer::create();
        middle->loadTexture("cocosgui/potentiometerProgress.png");
        middle->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + middle->getSize().height / 6.0f));
        middle->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle->setBarChangeRate(Point(1, 1));
        middle->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        middle->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)fade->clone()));
        _uiLayer->addChild(middle);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 1.1, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(Point(0, 1));
        right->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        right->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)tint->clone()));
        right->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)fade->clone()));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_WithSpriteFrame
bool UIProgressTimerTest_WithSpriteFrame::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Progress Timer with SpriteFrame");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.725f));
        _uiLayer->addChild(alert);
        
        // Create the progress timer
        ProgressTo* to = ProgressTo::create(6, 100.0f);
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwoptex/grossini.plist");
        
        gui::ProgressTimer* left = gui::ProgressTimer::create();
        left->loadTexture("grossini_dance_01.png", UI_TEX_TYPE_PLIST);
        left->setPosition(Point(widgetSize.width / 2.0f - left->getSize().width * 2.0f, widgetSize.height / 2.0f + left->getSize().height / 6.0f));
        left->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(Point(1, 0));
        left->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        _uiLayer->addChild(left);
        
        gui::ProgressTimer* middle = gui::ProgressTimer::create();
        middle->loadTexture("grossini_dance_04.png", UI_TEX_TYPE_PLIST);
        middle->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f + middle->getSize().height / 6.0f));
        middle->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle->setBarChangeRate(Point(1, 1));
        middle->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        _uiLayer->addChild(middle);
        
        gui::ProgressTimer* right = gui::ProgressTimer::create();
        right->loadTexture("grossini_dance_03.png", UI_TEX_TYPE_PLIST);
        right->setPosition(Point(widgetSize.width / 2.0f + right->getSize().width * 2.0f, widgetSize.height / 2.0f + right->getSize().height / 6.0f));
        right->setType(cocos2d::ProgressTimer::Type::BAR);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(Point(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(Point(0, 1));
        right->getVirtualRenderer()->runAction(RepeatForever::create((ActionInterval *)to->clone()));
        _uiLayer->addChild(right);
        
        return true;
    }
    return false;
}
