/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
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

#include "ConnectWaitLayer.h"
#include "Runtime.h"
#include "FileServer.h"
#include "ConfigParser.h"
#include "VisibleRect.h"
#include "ResData.h"

using namespace cocos2d;

ConnectWaitLayer::ConnectWaitLayer()
{
    int designWidth = 1280;
    int designHeight = 800;
    _imagebg = new Image();
    
    if (ConfigParser::getInstance()->isLanscape())
    {
        _imagebg->initWithImageData(__landscapePngData, sizeof(__landscapePngData));
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designWidth, designHeight, ResolutionPolicy::EXACT_FIT);
    } else
    {
        _imagebg->initWithImageData(__portraitPngData, sizeof(__portraitPngData));
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designHeight, designWidth, ResolutionPolicy::FIXED_HEIGHT);
    }
    Texture2D* texturebg = Director::getInstance()->getTextureCache()->addImage(_imagebg, "play_background");
    auto background = Sprite::createWithTexture(texturebg);
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setPosition(VisibleRect::center());
    addChild(background, 9000);

    // variable of below is"play" button position.
    int portraitX = 400;
    int portraitY = 500;
    int lanscaptX = 902;
    int lanscaptY = 400;
    _imageplay = new Image();
    _imageplay->initWithImageData(__playEnablePngData, sizeof(__playEnablePngData));
    Texture2D* textureplay = Director::getInstance()->getTextureCache()->addImage(_imageplay, "play_enable");
    auto playSprite = Sprite::createWithTexture(textureplay);
    addChild(playSprite, 9999);

    _imageShine = new Image();
    _imageShine->initWithImageData(__shinePngData, sizeof(__shinePngData));
    Texture2D* textureShine = Director::getInstance()->getTextureCache()->addImage(_imageShine, "shine");
    auto shineSprite = Sprite::createWithTexture(textureShine);
    shineSprite->setOpacity(0);
    Vector<FiniteTimeAction*> arrayOfActions;
    arrayOfActions.pushBack(DelayTime::create(0.4f));
    arrayOfActions.pushBack(FadeTo::create(0.8f, 200));
    arrayOfActions.pushBack(FadeTo::create(0.8f, 255));
    arrayOfActions.pushBack(FadeTo::create(0.8f, 200));
    arrayOfActions.pushBack(FadeTo::create(0.8f, 0));
    arrayOfActions.pushBack(DelayTime::create(0.4f));
    shineSprite->runAction(RepeatForever::create(Sequence::create(arrayOfActions)));
    addChild(shineSprite, 9998);

    std::string strip = getIPAddress();
	if (strip.empty())
	{
		strip = "0.0.0.0";
	}

    char szIPAddress[64] = {0};
    sprintf(szIPAddress, "IP: %s", strip.c_str());
    auto IPlabel = Label::createWithSystemFont(szIPAddress, "", 72);
    IPlabel->setAnchorPoint(Vec2(0, 0));
    int spaceSizex = 72;
    int spaceSizey = 200;
    IPlabel->setPosition(Point(VisibleRect::leftTop().x + spaceSizex, VisibleRect::top().y - spaceSizey));
    addChild(IPlabel, 9001);

    std::string transferTip = "waiting for file transfer ...";
    if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM || CC_PLATFORM_MAC == CC_TARGET_PLATFORM)
    {
        transferTip = "waiting for debugger to connect ...";
    }

    char szVersion[256] = {0};
    sprintf(szVersion, "runtimeVersion:%s \nengineVersion:%s", getRuntimeVersion(), cocos2dVersion());
    Label* verLable = Label::createWithSystemFont(szVersion, "", 24);
    verLable->setAnchorPoint(Vec2(0, 0));
    int width = verLable->getBoundingBox().size.width;
    verLable->setPosition(Point(VisibleRect::right().x - width, VisibleRect::rightBottom().y));
    verLable->setAlignment(TextHAlignment::LEFT);
    addChild(verLable, 9002);
    _labelUploadFile = Label::createWithSystemFont(transferTip, "", 36);
    _labelUploadFile->setAnchorPoint(Vec2(0, 0));
    _labelUploadFile->setPosition(Point(VisibleRect::leftTop().x + spaceSizex, IPlabel->getPositionY()- spaceSizex));
    _labelUploadFile->setAlignment(TextHAlignment::LEFT);
    addChild(_labelUploadFile, 9003);

    if (ConfigParser::getInstance()->isLanscape())
    {
        playSprite->setPosition(lanscaptX, lanscaptY);
        shineSprite->setPosition(lanscaptX, lanscaptY);
    }
    else
    {
        playSprite->setPosition(portraitX, portraitY);
        shineSprite->setPosition(portraitX, portraitY);
    }

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event  *event)->bool{
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 point = target->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
        auto rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (!rect.containsPoint(point)) return false;
        target->stopAllActions();
        target->runAction(Sequence::createWithTwoActions(ScaleBy::create(0.05f, 0.9f), ScaleTo::create(0.125f, 1)));
        return true;
    };
    listener->onTouchEnded = [](Touch* touch, Event  *event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 point = target->convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
        auto rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (!rect.containsPoint(point)) return;
        
        RuntimeEngine::getInstance()->setupRuntime();
        RuntimeEngine::getInstance()->startScript("");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, playSprite);

    this->scheduleUpdate();
}

ConnectWaitLayer::~ConnectWaitLayer()
{
	CC_SAFE_RELEASE(_imagebg);
	CC_SAFE_RELEASE(_imageplay);
	CC_SAFE_RELEASE(_imageShine);
}

// clean up: ignore stdin, stdout and stderr
void ConnectWaitLayer::update(float fDelta)
{
    std::string transferTip = FileServer::getShareInstance()->getTransingFileName();
    if (transferTip.empty()){
        return;
    }
    _labelUploadFile->setString(transferTip);
}
