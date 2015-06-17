#include "SpritePolygonTest.h"
#include "../testResource.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
SpritePolygonTest::SpritePolygonTest()
{
    ADD_TEST_CASE(SpritePolygonTest1);
    ADD_TEST_CASE(SpritePolygonTest2);
        ADD_TEST_CASE(SpritePolygonTest3);
        ADD_TEST_CASE(SpritePolygonTest4);
    ADD_TEST_CASE(SpritePolygonPerformanceTestDynamic);
    ADD_TEST_CASE(SpritePerformanceTestDynamic);
}
void SpritePolygonTestCase::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}
void SpritePolygonTestDemo::initTouchDebugDraw()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event){
        sp->debugDraw(true);
        spp->debugDraw(true);
        return true;
    };
    touchListener->onTouchMoved = [&](Touch* touch, Event* event){
        auto pos = touch->getDelta();
        float newScale = clampf(spp->getScale() + pos.x * 0.01f, 0.1f, 2.f);
        spp->setScale(newScale);
        sp->setScale(newScale);
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        spp->debugDraw(false);
        sp->debugDraw(false);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    


}
void SpritePolygonTest1::make2Sprites()
{
    Director::getInstance()->setClearColor(Color4F(102.f/255, 184.f/255, 204.f/255, 255.f));
    auto filename = s_pathGrossini;
    auto pinfo = AutoPolygon::generatePolygon(filename);
    spp = Sprite::create(pinfo);
    addChild(spp);
    auto s = Director::getInstance()->getWinSize();
    auto offset = Vec2(0.15*s.width,0);
    spp->setPosition(Vec2(s)/2 + offset);


    sp = Sprite::create(filename);
    addChild(sp);
    sp->setPosition(Vec2(s)/2 - offset);

    TTFConfig ttfConfig("fonts/arial.ttf", 8);
    std::string temp = "Sprite:\nPixels drawn: ";
    auto spSize = sp->getContentSize();
    auto spArea = Label::createWithTTF(ttfConfig, temp+Value((int)spSize.width*(int)spSize.height).asString());
    sp->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    
    temp = "SpritePolygon:\nPixels drawn: ";
    auto vertCount = "\nverts:"+Value((int)pinfo.getVertCount()).asString();
    auto sppArea = Label::createWithTTF(ttfConfig, temp+Value((int)pinfo.getArea()).asString()+vertCount);
    spp->addChild(sppArea);
    sppArea->setAnchorPoint(Vec2(0,1));
    
    initTouchDebugDraw();
}
SpritePolygonTest1::SpritePolygonTest1()
{
    _title = "SpritePolygon Creation";
    _subtitle = "Sprite::create(AutoPolygon::generatePolygon(filename))";
    make2Sprites();
}
SpritePolygonTest2::SpritePolygonTest2()
{
    _title = "SpritePolygon Creation with a rect";
    _subtitle = "Sprite::create(AutoPolygon::generatePolygon(filename, rect))";
    make2Sprites();
}
void SpritePolygonTest2::make2Sprites()
{
    Director::getInstance()->setClearColor(Color4F(102.f/255, 184.f/255, 204.f/255, 255.f));
    auto filename = s_pathGrossini;
    Rect head = Rect(30,25,25,25);
    auto pinfo = AutoPolygon::generatePolygon(filename, head);
    spp = Sprite::create(pinfo);
    addChild(spp);
    auto s = Director::getInstance()->getWinSize();
    auto offset = Vec2(0.15*s.width,0);
    spp->setPosition(Vec2(s)/2 + offset);
    
    
    sp = Sprite::create(filename,head);
    addChild(sp);
    sp->setPosition(Vec2(s)/2 - offset);
    
    TTFConfig ttfConfig("fonts/arial.ttf", 8);
    std::string temp = "Sprite:\nPixels drawn: ";
    auto spSize = sp->getContentSize();
    auto spArea = Label::createWithTTF(ttfConfig, temp+Value((int)spSize.width*(int)spSize.height).asString());
    sp->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    
    temp = "SpritePolygon:\nPixels drawn: ";
    auto vertCount = "\nverts:"+Value((int)pinfo.getVertCount()).asString();
    auto sppArea = Label::createWithTTF(ttfConfig, temp+Value((int)pinfo.getArea()).asString()+vertCount);
    spp->addChild(sppArea);
    sppArea->setAnchorPoint(Vec2(0,1));
    
    initTouchDebugDraw();
}



SpritePolygonPerformance::SpritePolygonPerformance()
{
    Director::getInstance()->setClearColor(Color4F(102.f/255, 184.f/255, 204.f/255, 255.f));
    TTFConfig ttfConfig("fonts/arial.ttf", 10);
    perfLabel = Label::createWithTTF(ttfConfig, "performance test");
    addChild(perfLabel);
    perfLabel->setPosition(Director::getInstance()->getVisibleSize().width/2, 80);
    
    spriteCount = vertCount = triCount = pixelCount = continuousLowDt =0;
    auto size = Director::getInstance()->getVisibleSize();
    elapsedTime = 0;
    _posX = _leftX = size.width*0.15;
    _rightX = size.width*0.85;
    _posY = size.height/2;
    prevDt = 0.016f;
    goRight = true;
    ended = false;
    scheduleUpdate();
    continuousHighDtTime = 0.0;
    waitingTime = 0.0;
}
void SpritePolygonPerformance::updateLabel()
{
    std::string temp = "Nodes: " + Value(spriteCount).asString() + " Triangles: " + Value(triCount).asString() + "\nPixels: " + Value(pixelCount).asString() + " Vertices: " + Value(vertCount).asString();
    if(!ended)
    perfLabel->setString("Nodes: " + Value(spriteCount).asString() + "   Triangles: " + Value(triCount).asString() + "\nPixels: " + Value(pixelCount).asString() + "   Vertices: " + Value(vertCount).asString());
}
Node *SpritePolygonPerformance::makeSprite()
{
    return Node::create();
}
void SpritePolygonPerformance::update(float dt)
{
    dt = dt*0.3 + prevDt*0.7;
    prevDt = dt;
    elapsedTime += dt;
    int loops = (0.025-dt)*1000;
    if(dt < 0.025 && loops>0)
    {
        continuousHighDtTime = clampf(continuousHighDtTime-dt*2, 0.0, 1.0);
        waitingTime = clampf(waitingTime-dt, 0.0, 5.0);
        continuousLowDt++;
    }
    else
    {
        continuousHighDtTime+=dt;
        continuousLowDt = 0;
    }
    if (continuousLowDt >= 5 && loops > 0) {
        for(int i = 0; i < loops; i++)
        {
            if(_posX >= _rightX)
            {
                goRight = false;
            }
            else if(_posX <= _leftX)
            {
                goRight = true;
            }
            auto s = makeSprite();
            addChild(s);
            s->setPosition(_posX, _posY);
            if(goRight)
                _posX++;
            else
                _posX--;
            
            incrementStats();
        }
        updateLabel();
    }

    //if we have 10 continuous low dt, then we will start to create more sprites
    else if(continuousHighDtTime >= .5 || waitingTime > 3.0){
        // its now 1 seconds with high DT time, time to end
        ended = true;
        unscheduleUpdate();
        perfLabel->setString("Test ended in " + Value(elapsedTime).asString() + " seconds\nNodes: " + Value(spriteCount).asString() + "   Triangles: " + Value(triCount).asString() + "\nPixels: " + Value(pixelCount).asString() + "   Vertices: " + Value(vertCount).asString());
        _subtitleLabel->setString("Test ended");
    }
    else{
        waitingTime += dt;
    }
}
void SpritePolygonPerformance::incrementStats()
{
    spriteCount ++;
    vertCount += _incVert;
    triCount += _incTri;
    pixelCount += _incPix;
}
void SpritePolygonPerformanceTestDynamic::initIncrementStats()
{
    _incVert = _pinfo.getVertCount();
    _incTri = _pinfo.getTriaglesCount();
    _incPix = _pinfo.getArea();
}

SpritePolygonPerformanceTestDynamic::SpritePolygonPerformanceTestDynamic()
{
    _pinfo = AutoPolygon::generatePolygon(s_pathGrossini);
    _title = "Dynamic SpritePolygon Performance";
    _subtitle = "Test running, please wait until it ends";
    initIncrementStats();
}
Sprite* SpritePolygonPerformanceTestDynamic::makeSprite()
{
    auto ret = Sprite::create(_pinfo);
    ret->runAction(RepeatForever::create(RotateBy::create(1.0,360.0)));
    return ret;
}


SpritePerformanceTestDynamic::SpritePerformanceTestDynamic()
{
    _title = "Dynamic Sprite Performance";
    _subtitle = "Test running, please wait until it ends";
    initIncrementStats();
}
void SpritePerformanceTestDynamic::initIncrementStats()
{
    auto t = Sprite::create(s_pathGrossini);
    _incVert = 4;
    _incTri = 2;
    _incPix = t->getContentSize().width * t->getContentSize().height;
}
Sprite* SpritePerformanceTestDynamic::makeSprite()
{
    auto ret =  Sprite::create(s_pathGrossini);
    ret->runAction(RepeatForever::create(RotateBy::create(1.0,360.0)));
    return ret;
}


SpritePolygonTestSlider::SpritePolygonTestSlider()
{
    _ttfConfig = TTFConfig("fonts/arial.ttf", 8);
    _title = "Optimization Value (default:2.0)";
    _subtitle = "";
    
    auto vsize =Director::getInstance()->getVisibleSize();
    cocos2d::ui::Slider* slider = cocos2d::ui::Slider::create();
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(vsize.width/2, vsize.height/4/* + slider->getSize().height * 2.0f*/));
    
    slider->addEventListener(CC_CALLBACK_2(SpritePolygonTestSlider::changeEpsilon, this));
    slider->setPercent((int)(sqrtf(1.0f/19.0f)*100));
    
    _epsilonLabel = Label::createWithTTF(_ttfConfig, "Epsilon: 2.0");
    addChild(_epsilonLabel);
    _epsilonLabel->setPosition(Vec2(vsize.width/2, vsize.height/4 + 15));
    addChild(slider);
}
void SpritePolygonTestSlider::makeSprites(const std::string* list, const int count, const float y)
{
    auto vsize =Director::getInstance()->getVisibleSize();
    float offset = (vsize.width-100)/(count-1);
    for(int i = 0; i < count; i++)
    {
        auto sp = makeSprite(list[i], Vec2(50+offset*i, y));
        addChild(sp);
        sp->debugDraw(true);
    }
}
void SpritePolygonTestSlider::changeEpsilon(cocos2d::Ref *pSender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(pSender);
        float epsilon = powf(slider->getPercent()/100.0,2)*19.0f + 1.0f;
        for(auto child : _children)
        {
            if(child->getName().size())
            {
                Sprite *sp = (Sprite*)child;
                auto file = sp->getName();
                auto pinfo = AutoPolygon::generatePolygon(file, Rect::ZERO, epsilon);
                sp->setPolygonInfo(pinfo);
                sp->debugDraw(true);
                updateLabel(sp, pinfo);
            }
        }
        _epsilonLabel->setString("Epsilon: "+ Value(epsilon).asString());
    }
}

void SpritePolygonTestSlider::updateLabel(const cocos2d::Sprite *sp, const PolygonInfo &pinfo)
{
    Label *label = (Label*)(sp->getChildren().at(0));
    auto filename = sp->getName();
    auto size = pinfo.rect.size/Director::getInstance()->getContentScaleFactor();
    label->setString(filename+"\nVerts: "+Value((int)pinfo.getVertCount()).asString()+ "\nPixels: "+Value((int)(pinfo.getArea()/(size.width*size.height)*100)).asString()+"%");
}

Sprite* SpritePolygonTestSlider::makeSprite(const std::string &filename, const Vec2 &pos)
{
    auto quadSize = Sprite::create(filename)->getContentSize();
    int originalSize = quadSize.width * quadSize.height;
    auto pinfo = AutoPolygon::generatePolygon(filename);
    auto ret = Sprite::create(pinfo);
    ret->setPosition(pos);
    
    auto spArea = Label::createWithTTF(_ttfConfig, filename+"\nVerts: "+Value((int)pinfo.getVertCount()).asString()+ "\nPixels: "+Value((int)(pinfo.getArea()/originalSize*100)).asString()+"%");
    ret->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    ret->setName(filename);
    ret->setAnchorPoint(Vec2(0.5, 0));
    return ret;
}
SpritePolygonTest3::SpritePolygonTest3()
{
    _ttfConfig = TTFConfig("fonts/arial.ttf", 8);
    _title = "Optimization Value (default:2.0)";
    _subtitle = "";
    auto vsize =Director::getInstance()->getVisibleSize();
    std::string list[] = {
        "Images/arrows.png",
        "Images/CyanTriangle.png",
        s_pathB2,
        "Images/elephant1_Diffuse.png"
    };
    int count = 4;
    makeSprites(list, count, vsize.height/2);
}
SpritePolygonTest4::SpritePolygonTest4()
{
    _ttfConfig = TTFConfig("fonts/arial.ttf", 8);
    _title = "Optimization Value (default:2.0)";
    _subtitle = "";
    auto vsize =Director::getInstance()->getVisibleSize();
    
    int count = 3;
    std::string list[] = {
        s_pathGrossini,
        "Images/grossinis_sister1.png",
        "Images/grossinis_sister2.png"
    };
    
    makeSprites(list, count, vsize.height/5*2);
}

