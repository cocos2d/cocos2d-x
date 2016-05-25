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
    ADD_TEST_CASE(SpritePolygonTest5);
    ADD_TEST_CASE(SpritePolygonPerformanceTestDynamic);
    ADD_TEST_CASE(SpritePerformanceTestDynamic);
    // FIXME: Tizen will crash with this example
#if (CC_TARGET_PLATFORM != CC_PLATFORM_TIZEN)
    ADD_TEST_CASE(SpritePolygonTestNoCrash);
#endif
    ADD_TEST_CASE(SpritePolygonTestTPIsland);
    ADD_TEST_CASE(SpritePolygonTestAutoPolyIsland);
    ADD_TEST_CASE(SpritePolygonTestFrameAnim);
}

SpritePolygonTestCase::SpritePolygonTestCase()
{
    _isDebugDraw = true;
    _isNeedDebugMenu = true;
}

SpritePolygonTestCase::~SpritePolygonTestCase()
{
    _drawNodes.clear();
}

void SpritePolygonTestCase::onEnter()
{
    TestCase::onEnter();
    Director::getInstance()->setClearColor(Color4F(102.0f/255.0f, 184.0f/255.0f, 204.0f/255.0f, 1.0f));
}

void SpritePolygonTestCase::onExit()
{
    Director::getInstance()->setClearColor(Color4F::BLACK);
    TestCase::onExit();
}

bool SpritePolygonTestCase::init()
{
    if(TestCase::init())
    {
        if (_isNeedDebugMenu)
        {
            TTFConfig ttfConfig("fonts/arial.ttf", 10);
            auto label = Label::createWithTTF(ttfConfig,"DebugDraw OFF");
            auto menuItem = MenuItemLabel::create(label, [=](Ref *ref){
                if (_isDebugDraw){
                    _isDebugDraw = false;
                    label->setString("DebugDraw ON");
                    for (int i = 0; i < _drawNodes.size(); i++)
                    {
                        _drawNodes.at(i)->setVisible(false);
                    }
                }else{
                    _isDebugDraw = true;
                    label->setString("DebugDraw OFF");
                    for (int i = 0; i < _drawNodes.size(); i++)
                    {
                        _drawNodes.at(i)->setVisible(true);
                        updateDrawNode();
                    }
                }
            });
            
            auto menu = Menu::create(menuItem, nullptr);
            menu->setPosition(Vec2::ZERO);
            menuItem->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
            menuItem->setPosition( VisibleRect::leftBottom() + Vec2(0, VisibleRect::leftTop().y/4));
            this->addChild(menu, 9999);
        }
        return true;
    }
    return false;
}

void SpritePolygonTestCase::updateDrawNode()
{
    if (_isDebugDraw && _drawNodes.size() > 0) {
        for (int i = 0; i < _drawNodes.size(); i++)
        {
                auto drawnode = _drawNodes.at(i);
                auto sp = (Sprite*)drawnode->getParent();
                if(!sp) return;
                auto polygoninfo = sp->getPolygonInfo();
                drawnode->clear();
                auto count = polygoninfo.triangles.indexCount/3;
                auto indices = polygoninfo.triangles.indices;
                auto verts = polygoninfo.triangles.verts;
                for(ssize_t i = 0; i < count; i++)
                {
                    //draw 3 lines
                    Vec3 from =verts[indices[i*3]].vertices;
                    Vec3 to = verts[indices[i*3+1]].vertices;
                    drawnode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);
                    
                    from =verts[indices[i*3+1]].vertices;
                    to = verts[indices[i*3+2]].vertices;
                    drawnode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);
                    
                    from =verts[indices[i*3+2]].vertices;
                    to = verts[indices[i*3]].vertices;
                    drawnode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);
                }
        }
    }
}

bool SpritePolygonTestDemo::init()
{
    if (SpritePolygonTestCase::init()) {
        _polygonSprite = nullptr;
        initSprites();
        initTouches();
        return true;
    }
    return false;
}

void SpritePolygonTestDemo::initTouches()
{
    if(_polygonSprite) {
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = [&](Touch* touch, Event* event){
            return true;
        };
        touchListener->onTouchMoved = [&](Touch* touch, Event* event){
            auto pos = touch->getDelta();
            float newScale = clampf(_polygonSprite->getScale() + pos.x * 0.01f, 0.1f, 2.f);
            _polygonSprite->setScale(newScale);
            _normalSprite->setScale(newScale);
            updateDrawNode();
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    }
}

SpritePolygonTest1::SpritePolygonTest1()
{
    _title = "SpritePolygon Creation";
    _subtitle = "Sprite::create(AutoPolygon::generatePolygon(filename))";
}

void SpritePolygonTest1::initSprites()
{
    auto s = Director::getInstance()->getWinSize();
    auto offset = Vec2(0.15*s.width,0);
    auto filename = s_pathGrossini;
    
    //Sprite
    auto pinfo = AutoPolygon::generatePolygon(filename);
    _polygonSprite = Sprite::create(pinfo);
    _polygonSprite->setTag(101);
    addChild(_polygonSprite);
    _polygonSprite->setPosition(Vec2(s)/2 + offset);

    _normalSprite = Sprite::create(filename);
    _normalSprite->setTag(100);
    addChild(_normalSprite);
    _normalSprite->setPosition(Vec2(s)/2 - offset);

    //DrawNode
    auto spDrawNode = DrawNode::create();
    spDrawNode->setTag(_normalSprite->getTag());
    spDrawNode->clear();
    _normalSprite->addChild(spDrawNode);
    _drawNodes.pushBack(spDrawNode);
    
    auto sppDrawNode = DrawNode::create();
    sppDrawNode->setTag(_polygonSprite->getTag());
    sppDrawNode->clear();
    _polygonSprite->addChild(sppDrawNode);
    _drawNodes.pushBack(sppDrawNode);
    
    //Label
    TTFConfig ttfConfig("fonts/arial.ttf", 8);
    std::string temp = "Sprite:\nPixels drawn: ";
    auto spSize = _normalSprite->getContentSize();
    auto spArea = Label::createWithTTF(ttfConfig, temp+Value((int)spSize.width*(int)spSize.height).asString());
    _normalSprite->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    
    temp = "SpritePolygon:\nPixels drawn: ";
    auto vertCount = "\nverts:"+Value((int)pinfo.getVertCount()).asString();
    auto sppArea = Label::createWithTTF(ttfConfig, temp+Value((int)pinfo.getArea()).asString()+vertCount);
    _polygonSprite->addChild(sppArea);
    sppArea->setAnchorPoint(Vec2(0,1));
    
    updateDrawNode();
}

SpritePolygonTest2::SpritePolygonTest2()
{
    _title = "SpritePolygon Creation with a rect";
    _subtitle = "Sprite::create(AutoPolygon::generatePolygon(filename, rect))";
}

void SpritePolygonTest2::initSprites()
{
    auto s = Director::getInstance()->getWinSize();
    auto offset = Vec2(0.15*s.width,0);
    auto filename = s_pathGrossini;
    Rect head = Rect(30,25,25,25);
    
    //Sprite
    auto pinfo = AutoPolygon::generatePolygon(filename, head);
    _polygonSprite = Sprite::create(pinfo);
    _polygonSprite->setTag(101);
    addChild(_polygonSprite);
    _polygonSprite->setPosition(Vec2(s)/2 + offset);
    
    _normalSprite = Sprite::create(filename,head);
    _normalSprite->setTag(100);
    addChild(_normalSprite);
    _normalSprite->setPosition(Vec2(s)/2 - offset);

    //DrawNode
    auto spDrawNode = DrawNode::create();
    _drawNodes.pushBack(spDrawNode);
    spDrawNode->setTag(_normalSprite->getTag());
    spDrawNode->clear();
    _normalSprite->addChild(spDrawNode);

    auto sppDrawNode = DrawNode::create();
    _drawNodes.pushBack(sppDrawNode);
    sppDrawNode->setTag(_polygonSprite->getTag());
    sppDrawNode->clear();
    _polygonSprite->addChild(sppDrawNode);
    
    //Label
    TTFConfig ttfConfig("fonts/arial.ttf", 8);
    std::string temp = "Sprite:\nPixels drawn: ";
    auto spSize = _normalSprite->getContentSize();
    auto spArea = Label::createWithTTF(ttfConfig, temp+Value((int)spSize.width*(int)spSize.height).asString());
    _normalSprite->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    
    temp = "SpritePolygon:\nPixels drawn: ";
    auto vertCount = "\nverts:"+Value((int)pinfo.getVertCount()).asString();
    auto sppArea = Label::createWithTTF(ttfConfig, temp+Value((int)pinfo.getArea()).asString()+vertCount);
    _polygonSprite->addChild(sppArea);
    sppArea->setAnchorPoint(Vec2(0,1));
    
    updateDrawNode();
}

bool SpritePolygonTestSlider::init()
{
    if(SpritePolygonTestCase::init())
    {
        initSliders();
        initSprites();
        return true;
    }
    return false;
}

void SpritePolygonTestSlider::initSliders()
{
    auto vsize =Director::getInstance()->getVisibleSize();
    cocos2d::ui::Slider* slider = cocos2d::ui::Slider::create();
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(vsize.width/2, vsize.height/4));
    
    slider->addEventListener(CC_CALLBACK_2(SpritePolygonTestSlider::changeEpsilon, this));
    slider->setPercent((int)(sqrtf(1.0f/19.0f)*100));
    
    auto ttfConfig = TTFConfig("fonts/arial.ttf", 8);
    _epsilonLabel = Label::createWithTTF(ttfConfig, "Epsilon: 2.0");
    addChild(_epsilonLabel);
    _epsilonLabel->setPosition(Vec2(vsize.width/2, vsize.height/4 + 15));
    addChild(slider);
}

void SpritePolygonTestSlider::makeSprites(const std::string* list, const int count, const float y)
{
    auto vsize = Director::getInstance()->getVisibleSize();
    for(int i = 0; i < count; i++)
    {
        float offset = (vsize.width/(count+1)) * (i+1);
        auto sp = makeSprite(list[i], Vec2(offset, y));
        addChild(sp);
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
                updateLabel(sp, pinfo);
            }
        }
        _epsilonLabel->setString("Epsilon: "+ Value(epsilon).asString());
        updateDrawNode();
    }
}

void SpritePolygonTestSlider::updateLabel(const cocos2d::Sprite *sp, const PolygonInfo &pinfo)
{
    Label *label = (Label*)(sp->getChildByName(sp->getName()));
    auto filename = sp->getName();
    auto size = pinfo.rect.size/Director::getInstance()->getContentScaleFactor();
    label->setString(filename+"\nVerts: "+Value((int)pinfo.getVertCount()).asString()+ "\nPixels: "+Value((int)(pinfo.getArea()/(size.width*size.height)*100)).asString()+"%");
}

Sprite* SpritePolygonTestSlider::makeSprite(const std::string &filename, const Vec2 &pos)
{
    //Sprite
    auto quadSize = Sprite::create(filename)->getContentSize();
    int originalSize = quadSize.width * quadSize.height;
    auto pinfo = AutoPolygon::generatePolygon(filename);
    auto ret = Sprite::create(pinfo);
    ret->setName(filename);
    ret->setTag(_tagIndex);
    _tagIndex++;
    ret->setPosition(pos);
    
    //DrawNode
    auto drawNode = DrawNode::create();
    _drawNodes.pushBack(drawNode);
    drawNode->setTag(ret->getTag());
    drawNode->clear();
    ret->addChild(drawNode);
 
    //Label
    auto ttfConfig = TTFConfig("fonts/arial.ttf", 8);
    auto spArea = Label::createWithTTF(ttfConfig, filename+"\nVerts: "+Value((int)pinfo.getVertCount()).asString()+ "\nPixels: "+Value((int)(pinfo.getArea()/originalSize*100)).asString()+"%");
    ret->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    spArea->setName(filename);
    ret->setAnchorPoint(Vec2(0.5, 0));
    
    updateDrawNode();
    
    return ret;
}

SpritePolygonTest3::SpritePolygonTest3()
{
    _title = "Optimization Value (default:2.0)";
    _subtitle = "";
    _tagIndex = 100;
}

void SpritePolygonTest3::initSprites()
{
    auto vsize =Director::getInstance()->getVisibleSize();
    std::string list[] = {
        "Images/arrows.png",
        "Images/CyanTriangle.png",
        s_pathB2,
        "Images/elephant1_Diffuse.png"
    };
    int count = sizeof(list)/sizeof(list[0]);
    makeSprites(list, count, vsize.height/2);
}

SpritePolygonTest4::SpritePolygonTest4()
{
    _title = "Optimization Value (default:2.0)";
    _subtitle = "";
    _tagIndex = 100;
}

void SpritePolygonTest4::initSprites()
{
    auto vsize =Director::getInstance()->getVisibleSize();
    int count = 3;
    std::string list[] = {
        s_pathGrossini,
        "Images/grossinis_sister1.png",
        "Images/grossinis_sister2.png"
    };
    makeSprites(list, count, vsize.height/5*2);
}

SpritePolygonTest5::SpritePolygonTest5()
{
    _title = "SpritePolygon Actions";
    _subtitle = "Touch screen to add sprite with random action.";
    _tagIndex = 100;
}

bool SpritePolygonTest5::init()
{
    if (SpritePolygonTestCase::init())
    {
        _polygonInfo = AutoPolygon::generatePolygon(s_pathGrossini);
        loadDefaultSprites();
        initTouch();
        scheduleUpdate();
        return true;
    }
    return false;
}

void SpritePolygonTest5::initTouch()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event){
        return true;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        auto pos = touch->getLocation();
        addSpritePolygon(pos);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void SpritePolygonTest5::loadDefaultSprites()
{
    auto s = Director::getInstance()->getVisibleSize();
    
    const int DEFAULT_SPRITEPOLYGON_COUNT = 8;
    Sprite* sprites[DEFAULT_SPRITEPOLYGON_COUNT];

    for (int i = 0; i < DEFAULT_SPRITEPOLYGON_COUNT; i++) {
        sprites[i] = Sprite::create(_polygonInfo);
        sprites[i]->setTag(_tagIndex);
        _tagIndex++;
        sprites[i]->setPosition(s.width * CCRANDOM_0_1(), s.height * CCRANDOM_0_1());
        this->addChild(sprites[i]);
        auto drawNode = DrawNode::create();
        _drawNodes.pushBack(drawNode);
        drawNode->setTag(sprites[i]->getTag());
        drawNode->clear();
        sprites[i]->addChild(drawNode);
    }
    sprites[0]->setColor(Color3B::RED);
    sprites[1]->setOpacity(100);
    sprites[2]->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister1.png"));
    sprites[3]->setTextureRect(Rect(0,0,100,30));
    sprites[4]->setScale(0.5f, 2.0f);
    sprites[5]->setFlippedY(true);
    sprites[6]->setSkewX(60);
    sprites[7]->setRotation(90);
    
    updateDrawNode();
}

void SpritePolygonTest5::addSpritePolygon(const Vec2& pos)
{
    auto sprite = Sprite::create(_polygonInfo);
    sprite->setTag(_tagIndex);
    _tagIndex++;
    sprite->setPosition(pos);
    this->addChild(sprite);
    auto drawNode = DrawNode::create();
    _drawNodes.pushBack(drawNode);
    drawNode->setTag(sprite->getTag());
    drawNode->clear();
    sprite->addChild(drawNode);
    
    ActionInterval* action;
    float random = CCRANDOM_0_1();
    if( random < 0.20 )
        action = ScaleBy::create(3, 2);
    else if(random < 0.40)
        action = RotateBy::create(3, 360);
    else if( random < 0.60)
        action = Blink::create(1, 3);
    else if( random < 0.8 )
        action = TintBy::create(2, 0, -255, -255);
    else
        action = FadeOut::create(2);
    auto seq = Sequence::create( action, action->reverse(), nullptr );
    sprite->runAction(RepeatForever::create(seq));
}

void SpritePolygonTest5::update(float dt)
{
    updateDrawNode();
}

SpritePolygonPerformance::SpritePolygonPerformance()
{
    TTFConfig ttfConfig("fonts/arial.ttf", 10);
    _perfLabel = Label::createWithTTF(ttfConfig, "performance test");
    addChild(_perfLabel);
    _perfLabel->setPosition(Director::getInstance()->getVisibleSize().width/2, 80);
    
    _spriteCount = _vertCount = _triCount = _pixelCount = _continuousLowDt =0;
    auto size = Director::getInstance()->getVisibleSize();
    _elapsedTime = 0;
    _posX = _leftX = size.width*0.15;
    _rightX = size.width*0.85;
    _posY = size.height/2;
    prevDt = 0.016f;
    goRight = true;
    ended = false;
    _continuousHighDtTime = 0.0;
    _waitingTime = 0.0;
    
    _isNeedDebugMenu = false;
}

bool SpritePolygonPerformance::init()
{
    if (SpritePolygonTestCase::init()) {
        initIncrementStats();
        scheduleUpdate();
        return true;
    }
    return false;
}

void SpritePolygonPerformance::updateLabel()
{
    std::string temp = "Nodes: " + Value(_spriteCount).asString() + " Triangles: " + Value(_triCount).asString() + "\nPixels: " + Value(_pixelCount).asString() + " Vertices: " + Value(_vertCount).asString();
    if(!ended)
    _perfLabel->setString("Nodes: " + Value(_spriteCount).asString() + "   Triangles: " + Value(_triCount).asString() + "\nPixels: " + Value(_pixelCount).asString() + "   Vertices: " + Value(_vertCount).asString());
}

Node *SpritePolygonPerformance::makeSprite()
{
    return nullptr;
}

void SpritePolygonPerformance::update(float dt)
{
    dt = dt*0.3 + prevDt*0.7;
    prevDt = dt;
    _elapsedTime += dt;
    int loops = (0.025-dt)*1000;
    if(dt < 0.025 && loops>0)
    {
        _continuousHighDtTime = clampf(_continuousHighDtTime-dt*2, 0.0, 1.0);
        _waitingTime = clampf(_waitingTime-dt, 0.0, 5.0);
        _continuousLowDt++;
    }
    else
    {
        _continuousHighDtTime+=dt;
        _continuousLowDt = 0;
    }
    if (_continuousLowDt >= 5 && loops > 0) {
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
    else if(_continuousHighDtTime >= .5 || _waitingTime > 3.0){
        // its now 1 seconds with high DT time, time to end
        ended = true;
        unscheduleUpdate();
        _perfLabel->setString("Test ended in " + Value(_elapsedTime).asString() + " seconds\nNodes: " + Value(_spriteCount).asString() + "   Triangles: " + Value(_triCount).asString() + "\nPixels: " + Value(_pixelCount).asString() + "   Vertices: " + Value(_vertCount).asString());
        _subtitleLabel->setString("Test ended");
    }
    else{
        _waitingTime += dt;
    }
}

void SpritePolygonPerformance::incrementStats()
{
    _spriteCount ++;
    _vertCount += _incVert;
    _triCount += _incTri;
    _pixelCount += _incPix;
}

void SpritePolygonPerformanceTestDynamic::initIncrementStats()
{
    _pinfo = AutoPolygon::generatePolygon(s_pathGrossini);
    _incVert = _pinfo.getVertCount();
    _incTri = _pinfo.getTrianglesCount();
    _incPix = _pinfo.getArea();
}

SpritePolygonPerformanceTestDynamic::SpritePolygonPerformanceTestDynamic()
{
    _title = "Dynamic SpritePolygon Performance";
    _subtitle = "Test running, please wait until it ends";
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

//
// SpritePolygonTestNoCrash
//
SpritePolygonTestNoCrash::SpritePolygonTestNoCrash()
{
    _title = "SpritePolygon ";
    _subtitle = "AutoPolygon: should not crash";
}

void SpritePolygonTestNoCrash::initSprites()
{
    auto s = Director::getInstance()->getWinSize();
    auto pinfo = AutoPolygon::generatePolygon("Images/sprite_polygon_crash.png", Rect::ZERO, 1);
    auto sprite = Sprite::create(pinfo);
    addChild(sprite);
    sprite->setPosition(s.width/2, s.height/2);

    //DrawNode
    auto spDrawNode = DrawNode::create();
    spDrawNode->setTag(sprite->getTag());
    spDrawNode->clear();
    sprite->addChild(spDrawNode);
    _drawNodes.pushBack(spDrawNode);

    updateDrawNode();
}

//
// SpritePolygonTestTPIsland
//
SpritePolygonTestTPIsland::SpritePolygonTestTPIsland()
{
    _title = "SpritePolygon ";
    _subtitle = "TexturePacker: Sprite with island";
}

void SpritePolygonTestTPIsland::initSprites()
{
    auto s = Director::getInstance()->getWinSize();
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Images/test_polygon.plist");

    auto sprite = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("island_polygon.png"));
    addChild(sprite);
    sprite->setPosition(s.width/2, s.height/2);

    //DrawNode
    auto spDrawNode = DrawNode::create();
    spDrawNode->setTag(sprite->getTag());
    spDrawNode->clear();
    sprite->addChild(spDrawNode);
    _drawNodes.pushBack(spDrawNode);

    updateDrawNode();
}

//
// SpritePolygonTestAutoPolyIsland
//
SpritePolygonTestAutoPolyIsland::SpritePolygonTestAutoPolyIsland()
{
    _title = "SpritePolygon";
    _subtitle = "AutoPolygon: Sprite with island";
}

void SpritePolygonTestAutoPolyIsland::initSprites()
{
    auto s = Director::getInstance()->getWinSize();

    auto pinfo = AutoPolygon::generatePolygon("Images/island_polygon.png", Rect::ZERO, 1);
    auto sprite = Sprite::create(pinfo);
    addChild(sprite);
    sprite->setPosition(s.width/2, s.height/2);

    //DrawNode
    auto spDrawNode = DrawNode::create();
    spDrawNode->setTag(sprite->getTag());
    spDrawNode->clear();
    sprite->addChild(spDrawNode);
    _drawNodes.pushBack(spDrawNode);

    updateDrawNode();
}

//
// SpritePolygonTestFrameAnim
//
SpritePolygonTestFrameAnim::SpritePolygonTestFrameAnim()
{
    _title = "SpritePolygon";
    _subtitle = "SpriteFrame animation";
}

void SpritePolygonTestFrameAnim::initSprites()
{
    auto screen = Director::getInstance()->getWinSize();

    auto rotate = RotateBy::create(10, 360);
    auto action = RepeatForever::create(rotate);
    char str[100] = {0};

    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("animations/grossini_dance_poly.plist");

    Sprite *sprite;
    for(int i=0;i<10;i++)
    {
        sprintf(str, "grossini_dance_%02d.png", i+1);
        sprite = Sprite::createWithSpriteFrameName(str);

        sprite->setPosition(Vec2(screen.width/6*(i%5+1), screen.height*2/3 - screen.height*(i/5)/3));

        auto point = Sprite::create("Images/r1.png");
        point->setScale( 0.1f );
        point->setPosition( sprite->getPosition() );
        addChild(point, 10);

        sprite->runAction( action->clone() );
        addChild(sprite, i);

        //DrawNode
        auto spDrawNode = DrawNode::create();
        spDrawNode->clear();
        sprite->addChild(spDrawNode);
        _drawNodes.pushBack(spDrawNode);
    }

    updateDrawNode();


    Vector<SpriteFrame*> animFrames(5);
    for(int i = 9; i < 14; i++)
    {
        sprintf(str, "grossini_dance_%02d.png", i+1);
        animFrames.pushBack(cache->getSpriteFrameByName(str));
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
    
}
