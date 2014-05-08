#include "UiVideoWidgetTest.h"

USING_NS_CC;
using namespace cocos2d::experimental::ui;

bool VideoWidgetTest::init()
{
    if ( !UIScene::init() )
    {
        return false;
    }
    
    _visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();

    MenuItemFont::setFontSize(16);

    auto fullSwitch = MenuItemFont::create("FullScreenSwitch", CC_CALLBACK_1(VideoWidgetTest::menuFullScreenCallback, this));
    fullSwitch->setAnchorPoint(Vector2::ANCHOR_BOTTOM_LEFT);
    fullSwitch->setPosition(Vector2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 50));

    auto pauseItem = MenuItemFont::create("Pause", CC_CALLBACK_1(VideoWidgetTest::menuPauseCallback, this));
    pauseItem->setAnchorPoint(Vector2::ANCHOR_BOTTOM_LEFT);
    pauseItem->setPosition(Vector2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 100));

    auto resumeItem = MenuItemFont::create("Resume", CC_CALLBACK_1(VideoWidgetTest::menuResumeCallback, this));
    resumeItem->setAnchorPoint(Vector2::ANCHOR_BOTTOM_LEFT);
    resumeItem->setPosition(Vector2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 150));

    auto stopItem = MenuItemFont::create("Stop", CC_CALLBACK_1(VideoWidgetTest::menuStopCallback, this));
    stopItem->setAnchorPoint(Vector2::ANCHOR_BOTTOM_LEFT);
    stopItem->setPosition(Vector2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 200));

    auto hintItem = MenuItemFont::create("Hint", CC_CALLBACK_1(VideoWidgetTest::menuHintCallback, this));
    hintItem->setAnchorPoint(Vector2::ANCHOR_BOTTOM_LEFT);
    hintItem->setPosition(Vector2(_visibleRect.origin.x + 10,_visibleRect.origin.y + 250));

    //-------------------------------------------------------------------------------------------------------------------
    auto resourceVideo = MenuItemFont::create("Play resource video", CC_CALLBACK_1(VideoWidgetTest::menuResourceVideoCallback, this));
    resourceVideo->setAnchorPoint(Vector2::ANCHOR_MIDDLE_RIGHT);
    resourceVideo->setPosition(Vector2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 50));

    auto onlineVideo = MenuItemFont::create("Play online video", CC_CALLBACK_1(VideoWidgetTest::menuOnlineVideoCallback, this));
    onlineVideo->setAnchorPoint(Vector2::ANCHOR_MIDDLE_RIGHT);
    onlineVideo->setPosition(Vector2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 100));

    auto ratioSwitch = MenuItemFont::create("KeepRatioSwitch", CC_CALLBACK_1(VideoWidgetTest::menuRatioCallback, this));
    ratioSwitch->setAnchorPoint(Vector2::ANCHOR_MIDDLE_RIGHT);
    ratioSwitch->setPosition(Vector2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 150));

    auto menu = Menu::create(resourceVideo,onlineVideo,ratioSwitch,fullSwitch,pauseItem,resumeItem,stopItem,hintItem,nullptr);
    menu->setPosition(Vector2::ZERO);
    _uiLayer->addChild(menu);

    _videoStateLabel = Label::createWithSystemFont("IDLE","Arial",16);
    _videoStateLabel->setAnchorPoint(Vector2::ANCHOR_MIDDLE_RIGHT);
    _videoStateLabel->setPosition(Vector2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 200));
    _uiLayer->addChild(_videoStateLabel);
    createVideo();

    return true;
}

void VideoWidgetTest::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void VideoWidgetTest::menuFullScreenCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->setFullScreenEnabled(! _videoWidget->isFullScreenEnabled());
    }
}

void VideoWidgetTest::menuRatioCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->setKeepAspectRatioEnabled(! _videoWidget->isKeepAspectRatioEnabled());
    }
}

void VideoWidgetTest::menuResourceVideoCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->setVideoFileName("cocosvideo.mp4");
        _videoWidget->startVideo();
    }
}

void VideoWidgetTest::menuOnlineVideoCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->setVideoURL("http://video001.smgbb.cn/gslb/program/FDN/FDN1190949/HLSVodService.m3u8?_mdCode=6065719&_cdnCode=B2B_XL_TEST&_type=0&_rCode=TerOut_18865&_userId=020341000456068&_categoryCode=SMG_HUAYU&_categoryPath=SMG_1002,SMG_HUAYU,&_adPositionId=01001000&_adCategorySource=0&_flag=.m3u8&_enCode=m3u8&taskID=ysh_ps_002-ott_1397459105893_020341000456068&_client=103&_cms=ctv&_CDNToken=76C043FD4969501754DC19E54EC8DC2C");
        _videoWidget->startVideo();
    }
}

void VideoWidgetTest::menuPauseCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->pauseVideo();
    }
}

void VideoWidgetTest::menuResumeCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->resumeVideo();
    }
}

void VideoWidgetTest::menuStopCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->stopVideo();
    }
}

void VideoWidgetTest::menuHintCallback(Ref* sender)
{
    if (_videoWidget)
    {
        _videoWidget->setVisible(! _videoWidget->isVisible());
    }
}

void VideoWidgetTest::createVideo()
{
    auto centerPos = Vector2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);

    auto widgetSize = _widget->getSize();

    _videoWidget = VideoWidget::create();
    _videoWidget->setPosition(centerPos);
    _videoWidget->setAnchorPoint(Vector2::ANCHOR_MIDDLE);
    _videoWidget->setContentSize(Size(widgetSize.width * 0.4f,widgetSize.height * 0.4f));
    _uiLayer->addChild(_videoWidget);
    
    _videoWidget->setEventListener(CC_CALLBACK_2(VideoWidgetTest::videoEventCallback, this));
}

void VideoWidgetTest::createSlider()
{
    auto centerPos = Vector2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);

    auto hSlider = ui::Slider::create();
    hSlider->setTouchEnabled(true);
    hSlider->loadBarTexture("cocosui/sliderTrack.png");
    hSlider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    hSlider->loadProgressBarTexture("cocosui/sliderProgress.png");
    hSlider->setPosition(Vector2(centerPos.x, _visibleRect.origin.y + _visibleRect.size.height * 0.15f));
    hSlider->setPercent(50);
    hSlider->addEventListenerSlider(this, sliderpercentchangedselector(VideoWidgetTest::sliderCallback));
    _uiLayer->addChild(hSlider,0,1);

    auto vSlider = ui::Slider::create();
    vSlider->setTouchEnabled(true);
    vSlider->loadBarTexture("cocosui/sliderTrack.png");
    vSlider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    vSlider->loadProgressBarTexture("cocosui/sliderProgress.png");
    vSlider->setPosition(Vector2(_visibleRect.origin.x + _visibleRect.size.width * 0.15f, centerPos.y));
    vSlider->setRotation(90);
    vSlider->setPercent(50);
    vSlider->addEventListenerSlider(this, sliderpercentchangedselector(VideoWidgetTest::sliderCallback));
    _uiLayer->addChild(vSlider,0,2);
}

void VideoWidgetTest::sliderCallback(Ref *sender, ui::SliderEventType eventType)
{
    if (eventType == SLIDER_PERCENTCHANGED && _videoWidget)
    {
        Slider*  hSlider = (Slider*)this->getChildByTag(1);
        Slider*  vSlider = (Slider*)this->getChildByTag(2);

        auto newPosX = _visibleRect.origin.x + _visibleRect.size.width / 2 + hSlider->getPercent() - 50;
        auto newPosY = _visibleRect.origin.y + _visibleRect.size.height / 2 + 50 - vSlider->getPercent();

        _videoWidget->setPosition(Vector2(newPosX,newPosY));
    }
}

void VideoWidgetTest::videoEventCallback(Ref* sender, VideoWidgetEvent eventType)
{
    switch (eventType) {
        case VideoWidgetEvent::PLAYING:
            _videoStateLabel->setString("PLAYING");
            break;
        case VideoWidgetEvent::PAUSED:
            _videoStateLabel->setString("PAUSED");
            break;
        case VideoWidgetEvent::STOPPED:
            _videoStateLabel->setString("STOPPED");
            break;
        case VideoWidgetEvent::COMPLETED:
            _videoStateLabel->setString("COMPLETED");
            break;
        default:
            break;
    }
}