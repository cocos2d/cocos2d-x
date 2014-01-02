

#include "UIProgressTimerTest.h"

// UIProgressTimerTest_Radial
bool UIProgressTimerTest_Radial::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer Radial");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *to1 = CCProgressTo::create(2, 100);
        CCProgressTo *to2 = CCProgressTo::create(2, 100);
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 0.75, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeRadial);
        left->getVirtualRenderer()->runAction(CCRepeatForever::create(to1));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 0.75, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeRadial);
        // Makes the ridial CCW
        right->setReverseProgress(true);
        right->getVirtualRenderer()->runAction(CCRepeatForever::create(to2));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_Horizontal
bool UIProgressTimerTest_Horizontal::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer Horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *to1 = CCProgressTo::create(2, 100);
        CCProgressTo *to2 = CCProgressTo::create(2, 100);
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 0.75, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the left since the midpoint is 0 for the x
        left->setMidPoint(ccp(0, 0));
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        left->setBarChangeRate(ccp(1, 0));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create(to1));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 0.75, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the left since the midpoint is 1 for the x
        right->setMidPoint(ccp(1, 0));
        //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
        right->setBarChangeRate(ccp(1, 0));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create(to2));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_Vertical
bool UIProgressTimerTest_Vertical::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *to1 = CCProgressTo::create(2, 100);
        CCProgressTo *to2 = CCProgressTo::create(2, 100);
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 0.75, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(ccp(0, 0));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(ccp(0, 1));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create(to1));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 0.75, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(ccp(0, 1));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(ccp(0, 1));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create(to2));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_RadialMidpointChanged
bool UIProgressTimerTest_RadialMidpointChanged::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer Radial Midpoint Changed");
        alert->setFontName("Marker Felt");
        alert->setFontSize(17);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.325));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *action = CCProgressTo::create(2, 100);
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 0.75, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeRadial);
        left->setMidPoint(ccp(0.25f, 0.75f));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)action->copy()->autorelease()));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 0.75, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeRadial);
        right->setMidPoint(ccp(0.75f, 0.25f));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)action->copy()->autorelease()));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_BarVarious
bool UIProgressTimerTest_BarVarious::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer Bar Various");
        alert->setFontName("Marker Felt");
        alert->setFontSize(26);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.125));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *to = CCProgressTo::create(2, 100);
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 1.1, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(ccp(1, 0));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *middle = UIProgressTimer::create();
        middle->loadTexture("cocosgui/potentiometerProgress.png");
        middle->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + middle->getSize().height / 6));
        middle->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle->setBarChangeRate(ccp(1, 1));
        middle->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        m_pUiLayer->addWidget(middle);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 1.1, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(ccp(0, 1));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_BarTintAndFade
bool UIProgressTimerTest_BarTintAndFade::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer Bar Tint and Fade");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.725));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *to = CCProgressTo::create(6, 100);
        CCAction *tint = CCSequence::create(CCTintTo::create(1, 255, 0, 0),
                                            CCTintTo::create(1, 0, 255, 0),
                                            CCTintTo::create(1, 0, 0, 255),
                                            NULL);
        CCAction *fade = CCSequence::create(CCFadeTo::create(1.0f, 0),
                                            CCFadeTo::create(1.0f, 255),
                                            NULL);
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("cocosgui/potentiometerProgress.png");
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 1.1, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(ccp(1, 0));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)tint->copy()->autorelease()));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *middle = UIProgressTimer::create();
        middle->loadTexture("cocosgui/potentiometerProgress.png");
        middle->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + middle->getSize().height / 6));
        middle->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle->setBarChangeRate(ccp(1, 1));
        middle->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        middle->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)fade->copy()->autorelease()));
        m_pUiLayer->addWidget(middle);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("cocosgui/potentiometerProgress.png");
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 1.1, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(ccp(0, 1));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)tint->copy()->autorelease()));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)fade->copy()->autorelease()));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}

// UIProgressTimerTest_WithSpriteFrame
bool UIProgressTimerTest_WithSpriteFrame::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Progress Timer with SpriteFrame");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.725));
        m_pUiLayer->addWidget(alert);
        
        // Create the progress timer
        CCProgressTo *to = CCProgressTo::create(6, 100);
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zwoptex/grossini.plist");
        
        UIProgressTimer *left = UIProgressTimer::create();
        left->loadTexture("grossini_dance_01.png", UI_TEX_TYPE_PLIST);
        left->setPosition(ccp(widgetSize.width / 2 - left->getSize().width * 2, widgetSize.height / 2 + left->getSize().height / 6));
        left->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        left->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        left->setBarChangeRate(ccp(1, 0));
        left->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        m_pUiLayer->addWidget(left);
        
        UIProgressTimer *middle = UIProgressTimer::create();
        middle->loadTexture("grossini_dance_04.png", UI_TEX_TYPE_PLIST);
        middle->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2 + middle->getSize().height / 6));
        middle->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        middle->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        middle->setBarChangeRate(ccp(1, 1));
        middle->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        m_pUiLayer->addWidget(middle);
        
        UIProgressTimer *right = UIProgressTimer::create();
        right->loadTexture("grossini_dance_03.png", UI_TEX_TYPE_PLIST);
        right->setPosition(ccp(widgetSize.width / 2 + right->getSize().width * 2, widgetSize.height / 2 + right->getSize().height / 6));
        right->setType(kCCProgressTimerTypeBar);
        //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
        right->setMidPoint(ccp(0.5f, 0.5f));
        //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        right->setBarChangeRate(ccp(0, 1));
        right->getVirtualRenderer()->runAction(CCRepeatForever::create((CCActionInterval *)to->copy()->autorelease()));
        m_pUiLayer->addWidget(right);
        
        return true;
    }
    return false;
}
