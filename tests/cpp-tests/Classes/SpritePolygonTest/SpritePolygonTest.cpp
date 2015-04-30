//
//  SpritePolygonTest.cpp
//  cocos2d_tests
//
//  Created by WuHao on 15/4/23.
//
//

#include "SpritePolygonTest.h"
#include "2d/SpritePolygon.h"
#include "../testResource.h"

USING_NS_CC;

SpritePolygonTest::SpritePolygonTest()
{
    ADD_TEST_CASE(SpritePolygonTest1);
    ADD_TEST_CASE(SpritePolygonTest2);
    ADD_TEST_CASE(SpritePolygonTest3);
    ADD_TEST_CASE(SpritePolygonTest4);
    ADD_TEST_CASE(SpritePolygonPerformanceTestStatic);
    ADD_TEST_CASE(SpritePerformanceTestStatic);
    ADD_TEST_CASE(SpritePolygonPerformanceTestDynamic);
    ADD_TEST_CASE(SpritePerformanceTestDynamic);
}
SpritePolygonPerformance::SpritePolygonPerformance()
{
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
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
//    std::string temp = "Nodes: " + Value(spriteCount).asString() + " Triangles: " + Value(triCount).asString() + "\nPixels: " + Value(pixelCount).asString() + " Vertices: " + Value(vertCount).asString();
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





SpritePolygonPerformanceTestStatic::SpritePolygonPerformanceTestStatic()
{
    _title = "Static SpritePolygon Performance";
    _subtitle = "Test running, please wait until it ends";
    initIncrementStats();
}
experimental::SpritePolygon* SpritePolygonPerformanceTestStatic::makeSprite()
{
    return experimental::SpritePolygon::create(s_pathGrossini);
}
void SpritePolygonPerformanceTestStatic::initIncrementStats()
{
    auto t = experimental::SpritePolygon::create(s_pathGrossini);
    _incVert = (int)t->getVertCount();
    _incTri = (int)t->getTrianglesCount();
    _incPix = (int)t->getArea();
}

SpritePolygonPerformanceTestDynamic::SpritePolygonPerformanceTestDynamic()
{
    _title = "Dynamic SpritePolygon Performance";
    _subtitle = "Test running, please wait until it ends";
    initIncrementStats();
}
experimental::SpritePolygon* SpritePolygonPerformanceTestDynamic::makeSprite()
{
    auto ret = experimental::SpritePolygon::create(s_pathGrossini);
    ret->runAction(RepeatForever::create(RotateBy::create(1.0,360.0)));
    return ret;
}


SpritePerformanceTestStatic::SpritePerformanceTestStatic()
{
    _title = "Static Sprite Performance";
    _subtitle = "Test running, please wait until it ends";
    initIncrementStats();
}
Sprite* SpritePerformanceTestStatic::makeSprite()
{
    return Sprite::create(s_pathGrossini);
}
void SpritePerformanceTestStatic::initIncrementStats()
{
    auto t = Sprite::create(s_pathGrossini);
    _incVert = 4;
    _incTri = 2;
    _incPix = t->getContentSize().width * t->getContentSize().height;
}

SpritePerformanceTestDynamic::SpritePerformanceTestDynamic()
{
    _title = "Dynamic Sprite Performance";
    _subtitle = "Test running, please wait until it ends";
    initIncrementStats();
}
Sprite* SpritePerformanceTestDynamic::makeSprite()
{
    auto ret = Sprite::create(s_pathGrossini);
    ret->runAction(RepeatForever::create(RotateBy::create(1.0,360.0)));
    return ret;
}



void SpritePolygonTestDemo::initDefaultSprite(const std::string &filename, cocos2d::experimental::SpritePolygon * inst)
{
    Director::getInstance()->setClearColor(Color4F(102.f/255, 184.f/255, 204.f/255, 255.f));
    
    spp = inst;
    addChild(spp);
    auto s = Director::getInstance()->getWinSize();
    auto offset = Vec2(0.15*s.width,0);
    spp->setPosition(Vec2(s)/2 + offset);

    
    sp = Sprite::create(filename);
    addChild(sp);
    sp->setPosition(Vec2(s)/2 - offset);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event){
        spp->showDebug(true);
        debugForNormalSprite->setVisible(true);
        return true;
    };
    touchListener->onTouchMoved = [&](Touch* touch, Event* event){
            auto pos = touch->getDelta();
            float newScale = clampf(spp->getScale() + pos.x * 0.01f, 0.1f, 2.f);
            spp->setScale(newScale);
            sp->setScale(newScale);
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        spp->showDebug(false);
        debugForNormalSprite->setVisible(false);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    debugForNormalSprite = DrawNode::create();
    sp->addChild(debugForNormalSprite);
    
    auto positions = new Vec2[4];
    auto spSize = sp->getContentSize();
    positions[0] = Vec2(0, spSize.height);
    positions[1] = Vec2(spSize);
    positions[2] = Vec2(spSize.width, 0);
    positions[3] = Vec2(0,0);
    debugForNormalSprite->drawPoints(positions, 4, 8, Color4F{0.0,1.0,1.0,1.0});
    debugForNormalSprite->drawLine(positions[0], positions[1], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[1], positions[2], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[2], positions[3], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[3], positions[0], Color4F::GREEN);
    debugForNormalSprite->drawLine(positions[0], positions[2], Color4F::GREEN);
    debugForNormalSprite->setVisible(false);
    
    TTFConfig ttfConfig("fonts/arial.ttf", 8);
    std::string temp = "Sprite:\nPixels drawn: ";
    auto spArea = Label::createWithTTF(ttfConfig, temp+Value((int)spSize.width*(int)spSize.height).asString());
    sp->addChild(spArea);
    spArea->setAnchorPoint(Vec2(0,1));
    
    temp = "SpritePolygon:\nPixels drawn: ";
    auto vertCount = "\nverts:"+Value((int)spp->getVertCount()).asString();
    auto sppArea = Label::createWithTTF(ttfConfig, temp+Value((int)spp->getArea()).asString()+vertCount);
    spp->addChild(sppArea);
    sppArea->setAnchorPoint(Vec2(0,1));
}
void SpritePolygonTestCase::onBackCallback(cocos2d::Ref *sender)
{
    TestCase::onBackCallback(sender);
    Director::getInstance()->setClearColor(Color4F::BLACK);
}


SpritePolygonTest1::SpritePolygonTest1()
{
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
    _title = "SpritePolygon Creation";
    _subtitle = "SpritePolygon::create(\"Images/grossini.png\")";
    cocos2d::experimental::SpritePolygon *s;
    for(int i = 0; i < 10; i ++)
    {
         s=   experimental::SpritePolygon::create(s_pathGrossini);
    }
    initDefaultSprite(s_pathGrossini, s);
}

SpritePolygonTest2::SpritePolygonTest2()
{
    /*
     36.5 128.5
     27.5 133.5
     24.5 145.5
     26.5 161.5
     33.5 168.5
     27.5 168.5
     16.5 179.5
     30.5 197.5
     28.5 237.5
     56.5 237.5
     54.5 197.5
     68.5 184.5
     57.5 168.5
     51.5 168.5
     60.5 154.5
     57.5 133.5
     48.5 127.5
     36.5 127.5
     */
    std::vector<Vec2> verts;
    verts.push_back(Vec2(36.5, 242.0-128.5));
    verts.push_back(Vec2(27.5, 242.0-133.5));
    verts.push_back(Vec2(24.5, 242.0-145.5));
    verts.push_back(Vec2(26.5, 242.0-161.5));
    verts.push_back(Vec2(33.5, 242.0-168.5));
    verts.push_back(Vec2(27.5, 242.0-168.5));
    verts.push_back(Vec2(16.5, 242.0-179.5));
    verts.push_back(Vec2(30.5, 242.0-197.5));
    verts.push_back(Vec2(28.5, 242.0-237.5));
    verts.push_back(Vec2(56.5, 242.0-237.5));
    verts.push_back(Vec2(54.5, 242.0-197.5));
    verts.push_back(Vec2(68.5, 242.0-184.5));
    verts.push_back(Vec2(57.5, 242.0-168.5));
    verts.push_back(Vec2(51.5, 242.0-168.5));
    verts.push_back(Vec2(60.5, 242.0-154.5));
    verts.push_back(Vec2(57.5, 242.0-133.5));
    verts.push_back(Vec2(48.5, 242.0-127.5));
    verts.push_back(Vec2(36.5, 242.0-127.5));
    
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
    _title = "SpritePolygon Creation";
    _subtitle = "SpritePolygon::create(\"Images/grossini.png\", verts)";
    auto s = experimental::SpritePolygon::create(s_pathGrossini, verts);
    initDefaultSprite(s_pathGrossini, s);
}

SpritePolygonTest3::SpritePolygonTest3()
{
    /*
     18, 48
     33.500000, 73.500000
     27.500000, 73.500000
     16.500000, 62.500000
     30.500000, 44.500000
     54.500000, 44.500000
     51.500000, 73.500000
     60.500000, 87.500000
     26.500000, 80.500000
     24.500000, 96.500000
     57.500000, 108.500000
     36.500000, 113.500000
     48.500000, 114.500000
     36.500000, 114.500000
     27.500000, 108.500000
     68.500000, 57.500000
     57.500000, 73.500000
     56.500000, 4.500000
     28.500000, 4.500000
     0, 1, 2
     3, 0, 2
     4, 0, 3
     5, 0, 4
     5, 6, 0
     0, 6, 7
     8, 7, 6
     6, 9, 8
     9, 10, 8
     9, 11, 10
     11, 12, 10
     8, 10, 13
     14, 5, 4
     15, 5, 14
     4, 3, 16
     3, 17, 16
     */
    std::vector<Vec2> verts;
    verts.push_back(Vec2(33.500000, 73.500000));
    verts.push_back(Vec2(27.500000, 73.500000));
    verts.push_back(Vec2(16.500000, 62.500000));
    verts.push_back(Vec2(30.500000, 44.500000));
    verts.push_back(Vec2(54.500000, 44.500000));
    verts.push_back(Vec2(51.500000, 73.500000));
    verts.push_back(Vec2(60.500000, 87.500000));
    verts.push_back(Vec2(26.500000, 80.500000));
    verts.push_back(Vec2(24.500000, 96.500000));
    verts.push_back(Vec2(57.500000, 108.500000));
    verts.push_back(Vec2(36.500000, 113.500000));
    verts.push_back(Vec2(48.500000, 114.500000));
    verts.push_back(Vec2(36.500000, 114.500000));
    verts.push_back(Vec2(27.500000, 108.500000));
    verts.push_back(Vec2(68.500000, 57.500000));
    verts.push_back(Vec2(57.500000, 73.500000));
    verts.push_back(Vec2(56.500000, 4.500000));
    verts.push_back(Vec2(28.500000, 4.500000));
    unsigned short indicesArr[] = {0, 1, 2, 3, 0, 2, 4, 0, 3, 5, 0, 4, 5, 6, 0, 0, 6, 7, 8, 7, 6, 6, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10, 8, 10, 13, 14, 5, 4, 15, 5, 14, 4, 3, 16, 3, 17, 16};
    std::vector<unsigned short> indices(indicesArr, indicesArr + sizeof indicesArr / sizeof indicesArr[0]);
    
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
    _title = "SpritePolygon Creation";
    _subtitle = "SpritePolygon::create(\"Images/grossini.png\", verts, indices)";
    auto s = experimental::SpritePolygon::create(s_pathGrossini, verts, indices);
    initDefaultSprite(s_pathGrossini, s);
}

SpritePolygonTest4::SpritePolygonTest4(){
    /*
     18, 48
     33.500000, 73.500000
     27.500000, 73.500000
     16.500000, 62.500000
     30.500000, 44.500000
     54.500000, 44.500000
     51.500000, 73.500000
     60.500000, 87.500000
     26.500000, 80.500000
     24.500000, 96.500000
     57.500000, 108.500000
     36.500000, 113.500000
     48.500000, 114.500000
     36.500000, 114.500000
     27.500000, 108.500000
     68.500000, 57.500000
     57.500000, 73.500000
     56.500000, 4.500000
     28.500000, 4.500000
     0, 1, 2,
     3, 0, 2,
     4, 0, 3,
     5, 0, 4,
     5, 6, 0,
     0, 6, 7,
     8, 7, 6,
     6, 9, 8,
     9, 10, 8,
     9, 11, 10,
     11, 12, 10,
     8, 10, 13,
     14, 5, 4,
     15, 5, 14,
     4, 3, 16,
     3, 17, 16,
     0.394118, 0.392562
     0.323529, 0.392562
     0.194118, 0.483471
     0.358824, 0.632231
     0.641176, 0.632231
     0.605882, 0.392562
     0.711765, 0.276859
     0.311765, 0.334711
     0.288235, 0.202479
     0.676471, 0.103306
     0.429412, 0.061983
     0.570588, 0.053719
     0.429412, 0.053719
     0.323529, 0.103306
     0.805882, 0.524793
     0.676471, 0.392562
     0.664706, 0.962810
     0.335294, 0.962810
     */
    Vec3 poss[] = {Vec3(33.500000, 73.500000,0),
    Vec3(27.500000, 73.500000,0),
    Vec3(16.500000, 62.500000,0),
    Vec3(30.500000, 44.500000,0),
    Vec3(54.500000, 44.500000,0),
    Vec3(51.500000, 73.500000,0),
    Vec3(60.500000, 87.500000,0),
    Vec3(26.500000, 80.500000,0),
    Vec3(24.500000, 96.500000,0),
    Vec3(57.500000, 108.500000,0),
    Vec3(36.500000, 113.500000,0),
    Vec3(48.500000, 114.500000,0),
    Vec3(36.500000, 114.500000,0),
    Vec3(27.500000, 108.500000,0),
    Vec3(68.500000, 57.500000,0),
    Vec3(57.500000, 73.500000,0),
    Vec3(56.500000, 4.500000,0),
    Vec3(28.500000, 4.50000, 0)
    };
    unsigned short idxs[] = {0, 1, 2, 3, 0, 2, 4, 0, 3, 5, 0, 4, 5, 6, 0, 0, 6, 7, 8, 7, 6, 6, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10, 8, 10, 13, 14, 5, 4, 15, 5, 14, 4, 3, 16, 3, 17, 16};
    std::vector<unsigned short> indices(idxs, idxs + sizeof idxs / sizeof idxs[0]);
    Tex2F t2f[] = {
        Tex2F(0.394118f, 0.392562f),
        Tex2F(0.323529f, 0.392562f),
        Tex2F(0.194118f, 0.483471f),
        Tex2F(0.358824f, 0.632231f),
        Tex2F(0.641176f, 0.632231f),
        Tex2F(0.605882f, 0.392562f),
        Tex2F(0.711765f, 0.276859f),
        Tex2F(0.311765f, 0.334711f),
        Tex2F(0.288235f, 0.202479f),
        Tex2F(0.676471f, 0.103306f),
        Tex2F(0.429412f, 0.061983f),
        Tex2F(0.570588f, 0.053719f),
        Tex2F(0.429412f, 0.053719f),
        Tex2F(0.323529f, 0.103306f),
        Tex2F(0.805882f, 0.524793f),
        Tex2F(0.676471f, 0.392562f),
        Tex2F(0.664706f, 0.962810f),
        Tex2F(0.335294f, 0.962810f)
    };
    std::vector<V3F_C4B_T2F> vs;
    for(int i = 0; i < 18; i++)
    {
        V3F_C4B_T2F t = {poss[i],Color4B::WHITE, t2f[i]};
        vs.push_back(t);
    }
    
    SpritePolygonCache::getInstance()->removeAllSpritePolygonCache();
    _title = "SpritePolygon Creation";
    _subtitle = "SpritePolygon::create(\"Images/grossini.png\", vector<V3F_C4B_T2F> v, vector<unsigned short> indices)";
    auto s = experimental::SpritePolygon::create(s_pathGrossini, vs, indices);
    initDefaultSprite(s_pathGrossini, s);
}

