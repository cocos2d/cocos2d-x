/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UIVideoPlayerTest.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::experimental::ui;

VideoPlayerTests::VideoPlayerTests()
{
    ADD_TEST_CASE(VideoPlayerTest);
    ADD_TEST_CASE(SimpleVideoPlayerTest);
}

bool VideoPlayerTest::init()
{
    if ( !UIScene::init() )
    {
        return false;
    }
    
    _visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();

    MenuItemFont::setFontSize(16);

    auto fullSwitch = MenuItemFont::create("FullScreenSwitch", CC_CALLBACK_1(VideoPlayerTest::menuFullScreenCallback, this));
    fullSwitch->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    fullSwitch->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 50));

    auto pauseItem = MenuItemFont::create("Pause", CC_CALLBACK_1(VideoPlayerTest::menuPauseCallback, this));
    pauseItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    pauseItem->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 100));

    auto resumeItem = MenuItemFont::create("Resume", CC_CALLBACK_1(VideoPlayerTest::menuResumeCallback, this));
    resumeItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    resumeItem->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 150));

    auto stopItem = MenuItemFont::create("Stop", CC_CALLBACK_1(VideoPlayerTest::menuStopCallback, this));
    stopItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    stopItem->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 200));

    auto hintItem = MenuItemFont::create("Hint", CC_CALLBACK_1(VideoPlayerTest::menuHintCallback, this));
    hintItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    hintItem->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 250));

    //-------------------------------------------------------------------------------------------------------------------
    auto resourceVideo = MenuItemFont::create("Play resource video", CC_CALLBACK_1(VideoPlayerTest::menuResourceVideoCallback, this));
    resourceVideo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    resourceVideo->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 50));

    auto onlineVideo = MenuItemFont::create("Play online video", CC_CALLBACK_1(VideoPlayerTest::menuOnlineVideoCallback, this));
    onlineVideo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    onlineVideo->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 100));

    auto ratioSwitch = MenuItemFont::create("KeepRatioSwitch", CC_CALLBACK_1(VideoPlayerTest::menuRatioCallback, this));
    ratioSwitch->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    ratioSwitch->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 150));
    
    auto loopToggle = MenuItemFont::create("LoopToogle", CC_CALLBACK_1(VideoPlayerTest::menuLoopCallback, this));
    loopToggle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    loopToggle->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 170));

    auto menu = Menu::create(resourceVideo,onlineVideo,ratioSwitch,loopToggle,fullSwitch,pauseItem,resumeItem,stopItem,hintItem,nullptr);
    menu->setPosition(Vec2::ZERO);
    _uiLayer->addChild(menu);

    _videoStateLabel = Label::createWithSystemFont("IDLE","Arial",16);
    _videoStateLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _videoStateLabel->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 200));
    _uiLayer->addChild(_videoStateLabel);
    
    _loopStatusLabel = Label::createWithSystemFont("(1)","Arial",10);
    _loopStatusLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _loopStatusLabel->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 185));
    _uiLayer->addChild(_loopStatusLabel);
    
    createVideo();

    return true;
}

void VideoPlayerTest::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
}

void VideoPlayerTest::menuFullScreenCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setFullScreenEnabled(! _videoPlayer->isFullScreenEnabled());
    }
}

void VideoPlayerTest::menuRatioCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setKeepAspectRatioEnabled(! _videoPlayer->isKeepAspectRatioEnabled());
    }
}

void VideoPlayerTest::menuLoopCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setLooping(! _videoPlayer->isLooping());
        _loopStatusLabel->setString(_videoPlayer->isLooping() ? "(OO)" : "(1)");
    }
}


void VideoPlayerTest::menuResourceVideoCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setFileName("cocosvideo.mp4");
        _videoPlayer->play();
    }
}

void VideoPlayerTest::menuOnlineVideoCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setURL("http://benchmark.cocos2d-x.org/cocosvideo.mp4");
        _videoPlayer->play();
    }
}

void VideoPlayerTest::menuPauseCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->pause();
    }
}

void VideoPlayerTest::menuResumeCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->resume();
    }
}

void VideoPlayerTest::menuStopCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->stop();
    }
}

void VideoPlayerTest::menuHintCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setVisible(! _videoPlayer->isVisible());
    }
}

void VideoPlayerTest::createVideo()
{
    auto centerPos = Vec2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);

    auto widgetSize = _widget->getContentSize();

    _videoPlayer = VideoPlayer::create();
    _videoPlayer->setPosition(centerPos);
    _videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _videoPlayer->setContentSize(Size(widgetSize.width * 0.4f,widgetSize.height * 0.4f));
    _uiLayer->addChild(_videoPlayer);
    
    _videoPlayer->addEventListener(CC_CALLBACK_2(VideoPlayerTest::videoEventCallback, this));
}

void VideoPlayerTest::createSlider()
{
    auto centerPos = Vec2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);

    auto hSlider = ui::Slider::create();
    hSlider->setTouchEnabled(true);
    hSlider->loadBarTexture("cocosui/sliderTrack.png");
    hSlider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    hSlider->loadProgressBarTexture("cocosui/sliderProgress.png");
    hSlider->setPosition(Vec2(centerPos.x, _visibleRect.origin.y + _visibleRect.size.height * 0.15f));
    hSlider->setPercent(50);
    hSlider->addEventListener(CC_CALLBACK_2(VideoPlayerTest::sliderCallback, this));
    _uiLayer->addChild(hSlider,0,1);

    auto vSlider = ui::Slider::create();
    vSlider->setTouchEnabled(true);
    vSlider->loadBarTexture("cocosui/sliderTrack.png");
    vSlider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    vSlider->loadProgressBarTexture("cocosui/sliderProgress.png");
    vSlider->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width * 0.15f, centerPos.y));
    vSlider->setRotation(90);
    vSlider->setPercent(50);
    vSlider->addEventListener(CC_CALLBACK_2(VideoPlayerTest::sliderCallback, this));
    _uiLayer->addChild(vSlider,0,2);
}

void VideoPlayerTest::sliderCallback(Ref *sender, ui::Slider::EventType eventType)
{
    if (eventType == Slider::EventType::ON_PERCENTAGE_CHANGED && _videoPlayer)
    {
        Slider*  hSlider = (Slider*)this->getChildByTag(1);
        Slider*  vSlider = (Slider*)this->getChildByTag(2);

        auto newPosX = _visibleRect.origin.x + _visibleRect.size.width / 2 + hSlider->getPercent() - 50;
        auto newPosY = _visibleRect.origin.y + _visibleRect.size.height / 2 + 50 - vSlider->getPercent();

        _videoPlayer->setPosition(Vec2(newPosX,newPosY));
    }
}

void VideoPlayerTest::videoEventCallback(Ref* sender, VideoPlayer::EventType eventType)
{
    switch (eventType) {
        case VideoPlayer::EventType::PLAYING:
            _videoStateLabel->setString("PLAYING");
            break;
        case VideoPlayer::EventType::PAUSED:
            _videoStateLabel->setString("PAUSED");
            break;
        case VideoPlayer::EventType::STOPPED:
            _videoStateLabel->setString("STOPPED");
            break;
        case VideoPlayer::EventType::COMPLETED:
            _videoStateLabel->setString("COMPLETED");
            break;
        default:
            break;
    }
}


// Simple Video Test

SimpleVideoPlayerTest::SimpleVideoPlayerTest()
{
    _videoPlayer = nullptr;
    _style = cocos2d::experimental::ui::VideoPlayer::StyleType::NONE;
    _userInputEnabled = true;
    
    _switchUserInputEnabled = nullptr;
    _switchStyle = nullptr;
}

void SimpleVideoPlayerTest::updateButtonsTexts()
{
    if (_switchUserInputEnabled)
    {
        std::string str = _userInputEnabled ? "< User Input Enabled >" : "< User Input Disabled >";
        _switchUserInputEnabled->setString(str);
    }
    
    if (_switchStyle)
    {
        std::string str = " - ";
        switch(_style)
        {
            case cocos2d::experimental::ui::VideoPlayer::StyleType::NONE:
                _switchUserInputEnabled->setVisible(false);
                str = "< NO Sytle >";
                break;
                
            case cocos2d::experimental::ui::VideoPlayer::StyleType::DEFAULT:
                str = "< Default Style >";
                _switchUserInputEnabled->setVisible(true);
                break;
                
            default:
                break;
        }
        
        _switchStyle->setString(str);
    }
}

bool SimpleVideoPlayerTest::init()
{
    if ( !UIScene::init() )
    {
        return false;
    }
    
    _visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    
    MenuItemFont::setFontSize(16);
    
    _switchStyle = MenuItemFont::create("Switch Style", CC_CALLBACK_1(SimpleVideoPlayerTest::switchStyleCallback, this));
    _switchStyle->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _switchStyle->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 50));
    
    _switchUserInputEnabled = MenuItemFont::create("Enable User Input", CC_CALLBACK_1(SimpleVideoPlayerTest::switchUserInputCallback, this));
    _switchUserInputEnabled->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _switchUserInputEnabled->setPosition(Vec2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 100));
    
    auto menu = Menu::create(_switchUserInputEnabled,_switchStyle,nullptr);
    menu->setPosition(Vec2::ZERO);
    _uiLayer->addChild(menu);
    
    createVideo();
    updateButtonsTexts();

    return true;
}

void SimpleVideoPlayerTest::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void SimpleVideoPlayerTest::switchStyleCallback(Ref* sender)
{
    switch (_style) {
        case cocos2d::experimental::ui::VideoPlayer::StyleType::NONE:
            _style = cocos2d::experimental::ui::VideoPlayer::StyleType::DEFAULT;
            break;
            
        case cocos2d::experimental::ui::VideoPlayer::StyleType::DEFAULT:
            _style = cocos2d::experimental::ui::VideoPlayer::StyleType::NONE;
            break;
            
        default:
            break;
    }
    
    if (_videoPlayer)
    {
        _videoPlayer->setStyle(_style);
    }
    
    //createVideo();
    updateButtonsTexts();
}

void SimpleVideoPlayerTest::switchUserInputCallback(Ref* sender)
{
    _userInputEnabled = !_userInputEnabled;
    if (_videoPlayer)
    {
        _videoPlayer->setUserInputEnabled(_userInputEnabled);
    }
    
    //createVideo();
    updateButtonsTexts();
}


void SimpleVideoPlayerTest::createVideo()
{
    if (_videoPlayer)
    {
        _uiLayer->removeChild(_videoPlayer);
    }
    auto centerPos = Vec2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);
    
    auto widgetSize = _widget->getContentSize();
    
    _videoPlayer = VideoPlayer::create();
    _videoPlayer->setPosition(centerPos);
    _videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _videoPlayer->setContentSize(Size(widgetSize.width * 0.4f,widgetSize.height * 0.4f));
    _videoPlayer->setLooping(true);
    _videoPlayer->setStyle(_style);
    _videoPlayer->setUserInputEnabled(_userInputEnabled);
    
    _uiLayer->addChild(_videoPlayer);
    
   // _videoPlayer->addEventListener(CC_CALLBACK_2(SimpleVideoPlayerTest::videoEventCallback, this));
    
    _videoPlayer->setFileName("cocosvideo.mp4");
    _videoPlayer->play();
}
