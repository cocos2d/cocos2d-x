#include "TileMapTest2.h"
#include "../testResource.h"

#include "2d/CCFastTMXLayer.h"
#include "2d/CCFastTMXTiledMap.h"

USING_NS_CC;

enum
{
    kTagTileMap = 1,
};

FastTileMapTests::FastTileMapTests()
{
    ADD_TEST_CASE(TMXIsoZorderNew);
    ADD_TEST_CASE(TMXOrthoZorderNew);
    ADD_TEST_CASE(TMXIsoVertexZNew);
    ADD_TEST_CASE(TMXOrthoVertexZNew);
    ADD_TEST_CASE(TMXOrthoTestNew);
    ADD_TEST_CASE(TMXOrthoTest2New);
    ADD_TEST_CASE(TMXOrthoTest3New);
    ADD_TEST_CASE(TMXOrthoTest4New);
    ADD_TEST_CASE(TMXIsoTestNew);
    ADD_TEST_CASE(TMXIsoTest1New);
    ADD_TEST_CASE(TMXIsoTest2New);
    ADD_TEST_CASE(TMXUncompressedTestNew);
    ADD_TEST_CASE(TMXHexTestNew);
    ADD_TEST_CASE(TMXReadWriteTestNew);
    ADD_TEST_CASE(TMXTilesetTestNew);
    ADD_TEST_CASE(TMXOrthoObjectsTestNew);
    ADD_TEST_CASE(TMXIsoObjectsTestNew);
    ADD_TEST_CASE(TMXResizeTestNew);
    ADD_TEST_CASE(TMXIsoMoveLayerNew);
    ADD_TEST_CASE(TMXOrthoMoveLayerNew);
    ADD_TEST_CASE(TMXOrthoFlipTestNew);
    ADD_TEST_CASE(TMXOrthoFlipRunTimeTestNew);
    ADD_TEST_CASE(TMXOrthoFromXMLTestNew);
    ADD_TEST_CASE(TMXOrthoXMLFormatTestNew);
    ADD_TEST_CASE(TileMapTestNew);
    ADD_TEST_CASE(TileMapEditTestNew);
    ADD_TEST_CASE(TMXBug987New);
    ADD_TEST_CASE(TMXBug787New);
    ADD_TEST_CASE(TMXGIDObjectsTestNew);
}

TileDemoNew::TileDemoNew()
{
    // fix bug #486, #419.
    // "test" is the default value in Director::setGLDefaultValues()
    // but TransitionTest may setDepthTest(false), we should revert it here
    Director::getInstance()->setDepthTest(true);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TileDemoNew::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

TileDemoNew::~TileDemoNew()
{
}

std::string TileDemoNew::title() const
{
    return "No title";
}

std::string TileDemoNew::subtitle() const
{
    return "drag the screen";
}

void TileDemoNew::onExit()
{
    TestCase::onExit();
    Director::getInstance()->setDepthTest(false);
}

void TileDemoNew::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
    auto touch = touches[0];

    auto diff = touch->getDelta();
    auto node = getChildByTag(kTagTileMap);
    auto currentPos = node->getPosition();
    node->setPosition(currentPos + diff);
}

//------------------------------------------------------------------
//
// TileMapTestNew
//
//------------------------------------------------------------------
TileMapTestNew::TileMapTestNew()
{
    auto map = TileMapAtlas::create(s_TilesPng,  s_LevelMapTga, 16, 16);
    // Convert it to "alias" (GL_LINEAR filtering)
    map->getTexture()->setAntiAliasTexParameters();
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    // If you are not going to use the Map, you can free it now
    // NEW since v0.7
    map->releaseMap();
    
    addChild(map, 0, kTagTileMap);
    
    map->setAnchorPoint( Vec2(0, 0.5f) );

    auto scale = ScaleBy::create(4, 0.8f);
    auto scaleBack = scale->reverse();

    auto seq = Sequence::create(scale, scaleBack, nullptr);

    map->runAction(RepeatForever::create(seq));
}

std::string TileMapTestNew::title() const
{
    return "TileMapAtlas";
}

//------------------------------------------------------------------
//
// TileMapEditTestNew
//
//------------------------------------------------------------------
TileMapEditTestNew::TileMapEditTestNew()
{
    auto map = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    // Create an Aliased Atlas
    map->getTexture()->setAliasTexParameters();
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // If you are not going to use the Map, you can free it now
    // [tilemap releaseMap);
    // And if you are going to use, it you can access the data with:
    schedule(CC_SCHEDULE_SELECTOR(TileMapEditTestNew::updateMap), 0.2f);
    
    addChild(map, 0, kTagTileMap);
    
    map->setAnchorPoint( Vec2(0, 0) );
    map->setPosition( Vec2(-20,-200) );
}

void TileMapEditTestNew::updateMap(float dt)
{
    // IMPORTANT
    //   The only limitation is that you cannot change an empty, or assign an empty tile to a tile
    //   The value 0 not rendered so don't assign or change a tile with value 0

    auto tilemap = (TileMapAtlas*) getChildByTag(kTagTileMap);
    
    //
    // For example you can iterate over all the tiles
    // using this code, but try to avoid the iteration
    // over all your tiles in every frame. It's very expensive
    //    for(int x=0; x < tilemap.tgaInfo->width; x++) {
    //        for(int y=0; y < tilemap.tgaInfo->height; y++) {
    //            Color3B c =[tilemap tileAt:Size(x,y));
    //            if( c.r != 0 ) {
    //                ////----CCLOG("%d,%d = %d", x,y,c.r);
    //            }
    //        }
    //    }
    
    // NEW since v0.7
    Color3B c = tilemap->getTileAt(Vec2(13,21));        
    c.r++;
    c.r %= 50;
    if( c.r==0)
        c.r=1;
    
    // NEW since v0.7
    tilemap->setTile(c, Vec2(13,21) );             
}

std::string TileMapEditTestNew::title() const
{
    return "Editable TileMapAtlas";
}

//------------------------------------------------------------------
//
// TMXOrthoTestNew
//
//------------------------------------------------------------------
TMXOrthoTestNew::TMXOrthoTestNew()
{
    //
    // Test orthogonal with 3d camera and anti-alias textures
    //
    // it should not flicker. No artifacts should appear
    //
    //auto color = LayerColor::create( Color4B(64,64,64,255) );
    //addChild(color, -1);

    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test2.tmx");

    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    auto scale = ScaleBy::create(10, 0.1f);
    auto back = scale->reverse();
    auto seq = Sequence::create(scale, back, nullptr);
    auto repeat = RepeatForever::create(seq);
    map->runAction(repeat);

//    float x, y, z;
//    map->getCamera()->getEye(&x, &y, &z);
//    map->getCamera()->setEye(x-200, y, z+300);    
}

void TMXOrthoTestNew::onEnter()
{
    TileDemoNew::onEnter();

    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void TMXOrthoTestNew::onExit()
{
    Director::getInstance()->setProjection(Director::Projection::DEFAULT);
    TileDemoNew::onExit();
}

std::string TMXOrthoTestNew::title() const
{
    return "TMX Orthogonal test";
}

//------------------------------------------------------------------
//
// TMXOrthoTest2New
//
//------------------------------------------------------------------
TMXOrthoTest2New::TMXOrthoTest2New()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test1.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    map->runAction( ScaleBy::create(2, 0.5f) ) ;
}

std::string TMXOrthoTest2New::title() const
{
    return "TMX Ortho test2";
}

//------------------------------------------------------------------
//
// TMXOrthoTest3New
//
//------------------------------------------------------------------
TMXOrthoTest3New::TMXOrthoTest3New()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test3.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    map->setScale(0.2f);
    map->setAnchorPoint( Vec2(0.5f, 0.5f) );
}

std::string TMXOrthoTest3New::title() const
{
    return "TMX anchorPoint test";
}

//------------------------------------------------------------------
//
// TMXOrthoTest4New
//
//------------------------------------------------------------------
TMXOrthoTest4New::TMXOrthoTest4New()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test4.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s1 = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s1.width,s1.height);
    
    map->setAnchorPoint(Vec2(0, 0));

    auto layer = map->getLayer("Layer 0");
    auto s = layer->getLayerSize();
    
    Sprite* sprite;
    sprite = layer->getTileAt(Vec2(0,0));
    sprite->setScale(2);
    sprite = layer->getTileAt(Vec2(s.width-1,0));
    sprite->setScale(2);
    sprite = layer->getTileAt(Vec2(0,s.height-1));
    sprite->setScale(2);
    sprite = layer->getTileAt(Vec2(s.width-1,s.height-1));
    sprite->setScale(2);

    schedule( CC_SCHEDULE_SELECTOR(TMXOrthoTest4New::removeSprite), 2 );

}

void TMXOrthoTest4New::removeSprite(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(TMXOrthoTest4New::removeSprite));

    auto map = static_cast<cocos2d::experimental::TMXTiledMap*>( getChildByTag(kTagTileMap) );
    auto layer = map->getLayer("Layer 0");
    auto s = layer->getLayerSize();

    auto sprite = layer->getTileAt( Vec2(s.width-1,0) );
    auto sprite2 = layer->getTileAt(Vec2(s.width-1, s.height-1));
    layer->removeChild(sprite, true);
    auto sprite3 = layer->getTileAt(Vec2(2, s.height-1));
    layer->removeChild(sprite3, true);
    layer->removeChild(sprite2, true);
}

std::string TMXOrthoTest4New::title() const
{
    return "TMX width/height test";
}

//------------------------------------------------------------------
//
// TMXReadWriteTestNew
//
//------------------------------------------------------------------
enum
{
    SID_UPDATECOL = 100,
    SID_REPAINTWITHGID,
    SID_REMOVETILES
};

TMXReadWriteTestNew::TMXReadWriteTestNew()
{
    _gid = 0;
    
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test2.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    
    auto layer = map->getLayer("Layer 0");

    map->setScale( 1 );

    auto tile0 = layer->getTileAt(Vec2(1,63));
    auto tile1 = layer->getTileAt(Vec2(2,63));
    auto tile2 = layer->getTileAt(Vec2(3,62));//Vec2(1,62));
    auto tile3 = layer->getTileAt(Vec2(2,62));
    tile0->setAnchorPoint( Vec2(0.5f, 0.5f) );
    tile1->setAnchorPoint( Vec2(0.5f, 0.5f) );
    tile2->setAnchorPoint( Vec2(0.5f, 0.5f) );
    tile3->setAnchorPoint( Vec2(0.5f, 0.5f) );

    auto move = MoveBy::create(0.5f, Vec2(0,160));
    auto rotate = RotateBy::create(2, 360);
    auto scale = ScaleBy::create(2, 5);
    auto opacity = FadeOut::create(2);
    auto fadein = FadeIn::create(2);
    auto scaleback = ScaleTo::create(1, 1);
    auto finish = CallFuncN::create(CC_CALLBACK_1(TMXReadWriteTestNew::removeSprite, this));
    auto seq0 = Sequence::create(move, rotate, scale, opacity, fadein, scaleback, finish, nullptr);
    auto seq1 = seq0->clone();
    auto seq2 = seq0->clone();
    auto seq3 = seq0->clone();
    
    tile0->runAction(seq0);
    tile1->runAction(seq1);
    tile2->runAction(seq2);
    tile3->runAction(seq3);
    
    
    _gid = layer->getTileGIDAt(Vec2(0,63));
    ////----CCLOG("Tile GID at:(0,63) is: %d", _gid);

    schedule(CC_SCHEDULE_SELECTOR(TMXReadWriteTestNew::updateCol), 2.0f); 
    schedule(CC_SCHEDULE_SELECTOR(TMXReadWriteTestNew::repaintWithGID), 2.05f);
    schedule(CC_SCHEDULE_SELECTOR(TMXReadWriteTestNew::removeTiles), 1.0f); 

    ////----CCLOG("++++atlas quantity: %d", layer->textureAtlas()->getTotalQuads());
    ////----CCLOG("++++children: %d", layer->getChildren()->count() );
    
    _gid2 = 0;
}

void TMXReadWriteTestNew::removeSprite(Node* sender)
{
    ////----CCLOG("removing tile: %x", sender);
    auto p = ((Node*)sender)->getParent();

    if (p)
    {
        p->removeChild((Node*)sender, true);
    }    
    
    //////----CCLOG("atlas quantity: %d", p->textureAtlas()->totalQuads());
}

void TMXReadWriteTestNew::updateCol(float dt)
{    
    auto map = (cocos2d::experimental::TMXTiledMap*)getChildByTag(kTagTileMap);
    auto layer = (cocos2d::experimental::TMXLayer*)map->getChildByTag(0);

    ////----CCLOG("++++atlas quantity: %d", layer->textureAtlas()->getTotalQuads());
    ////----CCLOG("++++children: %d", layer->getChildren()->count() );
 

    auto s = layer->getLayerSize();

    for( int y=0; y< s.height; y++ ) 
    {
        layer->setTileGID(_gid2, Vec2((float)3, (float)y));
    }
    
    _gid2 = (_gid2 + 1) % 80;
}

void TMXReadWriteTestNew::repaintWithGID(float dt)
{
//    unschedule:_cmd);
    
    auto map = (cocos2d::experimental::TMXTiledMap*)getChildByTag(kTagTileMap);
    auto layer = (cocos2d::experimental::TMXLayer*)map->getChildByTag(0);
    
    auto s = layer->getLayerSize();
    for( int x=0; x<s.width;x++) 
    {
        int y = (int)s.height-1;
        unsigned int tmpgid = layer->getTileGIDAt( Vec2((float)x, (float)y) );
        layer->setTileGID(tmpgid+1, Vec2((float)x, (float)y));
    }
}

void TMXReadWriteTestNew::removeTiles(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(TMXReadWriteTestNew::removeTiles));

    auto map = (cocos2d::experimental::TMXTiledMap*)getChildByTag(kTagTileMap);
    auto layer = (cocos2d::experimental::TMXLayer*)map->getChildByTag(0);
    auto s = layer->getLayerSize();

    for( int y=0; y< s.height; y++ ) 
    {
        layer->removeTileAt( Vec2(5.0, (float)y) );
    }
}



std::string TMXReadWriteTestNew::title() const
{
    return "TMX Read/Write test";
}

//------------------------------------------------------------------
//
// TMXHexTestNew
//
//------------------------------------------------------------------
TMXHexTestNew::TMXHexTestNew()
{
    auto color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/hexa-test.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXHexTestNew::title() const
{
    return "TMX Hex tes";
}

//------------------------------------------------------------------
//
// TMXIsoTestNew
//
//------------------------------------------------------------------
TMXIsoTestNew::TMXIsoTestNew()
{
    auto color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test.tmx");
    addChild(map, 0, kTagTileMap);        
    
    // move map to the center of the screen
    auto ms = map->getMapSize();
    auto ts = map->getTileSize();
    map->runAction( MoveTo::create(1.0f, Vec2( -ms.width * ts.width/2, -ms.height * ts.height/2 )) ); 
}

std::string TMXIsoTestNew::title() const
{
    return "TMX Isometric test 0";
}

//------------------------------------------------------------------
//
// TMXIsoTest1New
//
//------------------------------------------------------------------
TMXIsoTest1New::TMXIsoTest1New()
{
    auto color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test1.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    map->setAnchorPoint(Vec2(0.5f, 0.5f));
}

std::string TMXIsoTest1New::title() const
{
    return "TMX Isometric test + anchorPoint";
}

//------------------------------------------------------------------
//
// TMXIsoTest2New
//
//------------------------------------------------------------------
TMXIsoTest2New::TMXIsoTest2New()
{
    auto color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test2.tmx");
    addChild(map, 0, kTagTileMap);    
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // move map to the center of the screen
    auto ms = map->getMapSize();
    auto ts = map->getTileSize();
    map->runAction( MoveTo::create(1.0f, Vec2( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ));
}

std::string TMXIsoTest2New::title() const
{
    return "TMX Isometric test 2";
}

//------------------------------------------------------------------
//
// TMXUncompressedTestNew
//
//------------------------------------------------------------------
TMXUncompressedTestNew::TMXUncompressedTestNew()
{
    auto color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test2-uncompressed.tmx");
    addChild(map, 0, kTagTileMap);    
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // move map to the center of the screen
    auto ms = map->getMapSize();
    auto ts = map->getTileSize();
    map->runAction(MoveTo::create(1.0f, Vec2( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ));
 
      //unsupported
//    // testing release map
//    TMXLayer* layer;
//    
//    auto& children = map->getChildren();
//    for(const auto &node : children) {
//        layer= static_cast<TMXLayer*>(node);
//        layer->releaseMap();
//    }

}

std::string TMXUncompressedTestNew::title() const
{
    return "TMX Uncompressed test";
}

//------------------------------------------------------------------
//
// TMXTilesetTestNew
//
//------------------------------------------------------------------
TMXTilesetTestNew::TMXTilesetTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test5.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXTilesetTestNew::title() const
{
    return "TMX Tileset test";
}

//------------------------------------------------------------------
//
// TMXOrthoObjectsTestNew
//
//------------------------------------------------------------------
TMXOrthoObjectsTestNew::TMXOrthoObjectsTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/ortho-objects.tmx");
    addChild(map, -1, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    auto group = map->getObjectGroup("Object Group 1");
    auto& objects = group->getObjects();

    Value objectsVal = Value(objects);
    CCLOG("%s", objectsVal.getDescription().c_str());
    
    auto drawNode = DrawNode::create();
    Color4F color(1.0, 1.0, 1.0, 1.0);
    for (auto& obj : objects)
    {
        ValueMap& dict = obj.asValueMap();
        
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        
        drawNode->drawLine(Vec2(x, y), Vec2(x + width, y), color);
        drawNode->drawLine(Vec2(x + width, y), Vec2(x + width, y + height), color);
        drawNode->drawLine(Vec2(x + width,y + height), Vec2(x,y + height), color);
        drawNode->drawLine(Vec2(x,y + height), Vec2(x,y), color);
    }
    map->addChild(drawNode);
}

std::string TMXOrthoObjectsTestNew::title() const
{
    return "TMX Ortho object test";
}

std::string TMXOrthoObjectsTestNew::subtitle() const
{
    return "You should see a white box around the 3 platforms";
}


//------------------------------------------------------------------
//
// TMXIsoObjectsTestNew
//
//------------------------------------------------------------------

TMXIsoObjectsTestNew::TMXIsoObjectsTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test-objectgroup.tmx");
    addChild(map, -1, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    auto group = map->getObjectGroup("Object Group 1");

    auto& objects = group->getObjects();
    
    Value objectsVal = Value(objects);
    CCLOG("%s", objectsVal.getDescription().c_str());
    
    auto drawNode = DrawNode::create();
    Color4F color(1.0, 1.0, 1.0, 1.0);
    for (auto& obj : objects)
    {
        ValueMap& dict = obj.asValueMap();
        
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        
        drawNode->drawLine(Vec2(x, y), Vec2(x + width, y), color);
        drawNode->drawLine(Vec2(x + width, y), Vec2(x + width, y + height), color);
        drawNode->drawLine(Vec2(x + width,y + height), Vec2(x,y + height), color);
        drawNode->drawLine(Vec2(x,y + height), Vec2(x,y), color);
    }
    map->addChild(drawNode, 10);
}

std::string TMXIsoObjectsTestNew::title() const
{
    return "TMX Iso object test";
}

std::string TMXIsoObjectsTestNew::subtitle() const
{
    return "You need to parse them manually. See bug #810";
}


//------------------------------------------------------------------
//
// TMXResizeTestNew
//
//------------------------------------------------------------------

TMXResizeTestNew::TMXResizeTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test5.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    cocos2d::experimental::TMXLayer* layer;
    layer = map->getLayer("Layer 0");

    auto ls = layer->getLayerSize();
    for (unsigned int y = 0; y < ls.height; y++) 
    {
        for (unsigned int x = 0; x < ls.width; x++) 
        {
            layer->setTileGID(1, Vec2( x, y ) );
        }
    }        
}

std::string TMXResizeTestNew::title() const
{
    return "TMX resize test";
}

std::string TMXResizeTestNew::subtitle() const
{
    return "Should not crash. Testing issue #740";
}


//------------------------------------------------------------------
//
// TMXIsoZorderNew
//
//------------------------------------------------------------------
TMXIsoZorderNew::TMXIsoZorderNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test-zorder.tmx");
    addChild(map, 0, kTagTileMap);

    auto s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    map->setPosition(Vec2(-s.width/2,0));
    
    _tamara = Sprite::create(s_pathSister1);
    map->addChild(_tamara, (int)map->getChildren().size() );
    _tamara->retain();
    int mapWidth = map->getMapSize().width * map->getTileSize().width;
    _tamara->setPosition(CC_POINT_PIXELS_TO_POINTS(Vec2( mapWidth/2,0)));
    _tamara->setAnchorPoint(Vec2(0.5f,0));

    
    auto move = MoveBy::create(10, Vec2(300,250));
    auto back = move->reverse();
    auto seq = Sequence::create(move, back,nullptr);
    _tamara->runAction( RepeatForever::create(seq) );
    
    schedule( CC_SCHEDULE_SELECTOR(TMXIsoZorderNew::repositionSprite) );
}

TMXIsoZorderNew::~TMXIsoZorderNew()
{
    _tamara->release();
}

void TMXIsoZorderNew::onExit()
{
    unschedule(CC_SCHEDULE_SELECTOR(TMXIsoZorderNew::repositionSprite));
    TileDemoNew::onExit();
}

void TMXIsoZorderNew::repositionSprite(float dt)
{
    auto p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    auto map = getChildByTag(kTagTileMap);
    
    // there are only 4 layers. (grass and 3 trees layers)
    // if tamara < 48, z=4
    // if tamara < 96, z=3
    // if tamara < 144,z=2
    
    int newZ = 4 - (p.y / 48);
    newZ = std::max(newZ,0);
    
    map->reorderChild(_tamara, newZ);    
}

std::string TMXIsoZorderNew::title() const
{
    return "TMX Iso Zorder";
}

std::string TMXIsoZorderNew::subtitle() const
{
    return "Sprite should hide behind the trees";
}


//------------------------------------------------------------------
//
// TMXOrthoZorderNew
//
//------------------------------------------------------------------
TMXOrthoZorderNew::TMXOrthoZorderNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test-zorder.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    _tamara = Sprite::create(s_pathSister1);
    map->addChild(_tamara,  (int)map->getChildren().size());
    _tamara->retain();
    _tamara->setAnchorPoint(Vec2(0.5f,0));

    
    auto move = MoveBy::create(10, Vec2(400,450));
    auto back = move->reverse();
    auto seq = Sequence::create(move, back,nullptr);
    _tamara->runAction( RepeatForever::create(seq));
    
    schedule( CC_SCHEDULE_SELECTOR(TMXOrthoZorderNew::repositionSprite));
}

TMXOrthoZorderNew::~TMXOrthoZorderNew()
{
    _tamara->release();
}

void TMXOrthoZorderNew::repositionSprite(float dt)
{
    auto p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    auto map = getChildByTag(kTagTileMap);
    
    // there are only 4 layers. (grass and 3 trees layers)
    // if tamara < 81, z=4
    // if tamara < 162, z=3
    // if tamara < 243,z=2

    // -10: customization for this particular sample
    int newZ = 4 - ( (p.y-10) / 81);
    newZ = std::max(newZ,0);

    map->reorderChild(_tamara, newZ);
}

std::string TMXOrthoZorderNew::title() const
{
    return "TMX Ortho Zorder";
}

std::string TMXOrthoZorderNew::subtitle() const
{
    return "Sprite should hide behind the trees";
}


//------------------------------------------------------------------
//
// TMXIsoVertexZNew
//
//------------------------------------------------------------------
TMXIsoVertexZNew::TMXIsoVertexZNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test-vertexz.tmx");
    addChild(map, 0, kTagTileMap);
    
    auto s = map->getContentSize();
    map->setPosition( Vec2(-s.width/2,0) );
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    // can use any Sprite and it will work OK.
    auto layer = map->getLayer("Trees");
    _tamara = layer->getTileAt( Vec2(29,29) );
    _tamara->retain();
    
    auto move = MoveBy::create(10, Vec2(300,250) * (1/CC_CONTENT_SCALE_FACTOR()));
    auto back = move->reverse();
    auto seq = Sequence::create(move, back,nullptr);
    _tamara->runAction( RepeatForever::create(seq) );
    
    schedule( CC_SCHEDULE_SELECTOR(TMXIsoVertexZNew::repositionSprite));
    
}

TMXIsoVertexZNew::~TMXIsoVertexZNew()
{
    _tamara->release();
}

void TMXIsoVertexZNew::repositionSprite(float dt)
{
    // tile height is 64x32
    // map size: 30x30
    auto p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    float newZ = -(p.y+32) /16;
    _tamara->setPositionZ( newZ );
}

void TMXIsoVertexZNew::onEnter()
{
    TileDemoNew::onEnter();
    
    // TIP: 2d projection should be used
    Director::getInstance()->setProjection(Director::Projection::_2D);
    Director::getInstance()->setDepthTest(true);
}

void TMXIsoVertexZNew::onExit()
{
    // At exit use any other projection. 
    Director::getInstance()->setProjection(Director::Projection::DEFAULT);
    Director::getInstance()->setDepthTest(false);
    TileDemoNew::onExit();
}

std::string TMXIsoVertexZNew::title() const
{
    return "TMX Iso VertexZ";
}

std::string TMXIsoVertexZNew::subtitle() const
{
    return "Doesn't support yet";
}


//------------------------------------------------------------------
//
// TMXOrthoVertexZNew
//
//------------------------------------------------------------------
TMXOrthoVertexZNew::TMXOrthoVertexZNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test-vertexz.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    // can use any Sprite and it will work OK.
    auto layer = map->getLayer("trees");
    _tamara = layer->getTileAt(Vec2(0,11));
    CCLOG("%p vertexZ: %f", _tamara, _tamara->getPositionZ());
    _tamara->retain();

    auto move = MoveBy::create(10, Vec2(400,450) * (1/CC_CONTENT_SCALE_FACTOR()));
    auto back = move->reverse();
    auto seq = Sequence::create(move, back,nullptr);
    _tamara->runAction( RepeatForever::create(seq));
    
    schedule(CC_SCHEDULE_SELECTOR(TMXOrthoVertexZNew::repositionSprite));
    
}

TMXOrthoVertexZNew::~TMXOrthoVertexZNew()
{
    _tamara->release();
}

void TMXOrthoVertexZNew::repositionSprite(float dt)
{
    // tile height is 101x81
    // map size: 12x12
    auto p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    _tamara->setPositionZ( -( (p.y+81) /81) );
}

void TMXOrthoVertexZNew::onEnter()
{
    TileDemoNew::onEnter();
    
    // TIP: 2d projection should be used
    Director::getInstance()->setProjection(Director::Projection::_2D);
    Director::getInstance()->setDepthTest(true);
}

void TMXOrthoVertexZNew::onExit()
{
    // At exit use any other projection. 
    Director::getInstance()->setProjection(Director::Projection::DEFAULT);
    Director::getInstance()->setDepthTest(false);
    TileDemoNew::onExit();
}

std::string TMXOrthoVertexZNew::title() const
{
    return "TMX Ortho vertexZ";
}

std::string TMXOrthoVertexZNew::subtitle() const
{
    return "Doesn't support yet";
}


//------------------------------------------------------------------
//
// TMXIsoMoveLayerNew
//
//------------------------------------------------------------------
TMXIsoMoveLayerNew::TMXIsoMoveLayerNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test-movelayer.tmx");
    addChild(map, 0, kTagTileMap);
    
    map->setPosition(Vec2(-700,-50));

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXIsoMoveLayerNew::title() const
{
    return "TMX Iso Move Layer";
}

std::string TMXIsoMoveLayerNew::subtitle() const
{
    return "Trees should be horizontally aligned";
}


//------------------------------------------------------------------
//
// TMXOrthoMoveLayerNew
//
//------------------------------------------------------------------
TMXOrthoMoveLayerNew::TMXOrthoMoveLayerNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test-movelayer.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXOrthoMoveLayerNew::title() const
{
    return "TMX Ortho Move Layer";
}

std::string TMXOrthoMoveLayerNew::subtitle() const
{
    return "Trees should be horizontally aligned";
}

//------------------------------------------------------------------
//
// TMXTilePropertyTestNew
//
//------------------------------------------------------------------

TMXTilePropertyTestNew::TMXTilePropertyTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/ortho-tile-property.tmx");
    addChild(map ,0 ,kTagTileMap);

    for(int i=1;i<=20;i++){
        for(const auto& value : map->getPropertiesForGID(i).asValueMap())
        {
            log("GID:%i, Properties:%s, %s", i, value.first.c_str(), value.second.asString().c_str());
        }
    }
}

std::string TMXTilePropertyTestNew::title() const
{
    return "TMX Tile Property Test";
}

std::string TMXTilePropertyTestNew::subtitle() const
{
    return "In the console you should see tile properties";
}

//------------------------------------------------------------------
//
// TMXOrthoFlipTestNew
//
//------------------------------------------------------------------

TMXOrthoFlipTestNew::TMXOrthoFlipTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/ortho-rotation-test.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);

    auto action = ScaleBy::create(2, 0.5f);
    map->runAction(action);
}

std::string TMXOrthoFlipTestNew::title() const
{
    return "TMX tile flip test";
}

//------------------------------------------------------------------
//
// TMXOrthoFlipRunTimeTestNew
//
//------------------------------------------------------------------

TMXOrthoFlipRunTimeTestNew::TMXOrthoFlipRunTimeTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/ortho-rotation-test.tmx");
    addChild(map, 0, kTagTileMap);

    auto s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);

    auto action = ScaleBy::create(2, 0.5f);
    map->runAction(action);

    schedule(CC_SCHEDULE_SELECTOR(TMXOrthoFlipRunTimeTestNew::flipIt), 1.0f);
}

std::string TMXOrthoFlipRunTimeTestNew::title() const
{
    return "TMX tile flip run time test";
}

std::string TMXOrthoFlipRunTimeTestNew::subtitle() const
{
    return "in 2 sec bottom left tiles will flip";
}

void TMXOrthoFlipRunTimeTestNew::flipIt(float dt)
{
    auto map = (cocos2d::experimental::TMXTiledMap*) getChildByTag(kTagTileMap);
    auto layer = map->getLayer("Layer 0");

    //blue diamond 
    auto tileCoord = Vec2(1,10);
    int flags;
    unsigned int GID = layer->getTileGIDAt(tileCoord, (TMXTileFlags*)&flags);
    // Vertical
    if( flags & kTMXTileVerticalFlag )
        flags &= ~kTMXTileVerticalFlag;
    else
        flags |= kTMXTileVerticalFlag;
    layer->setTileGID(GID ,tileCoord, (TMXTileFlags)flags);


    tileCoord = Vec2(1,8);    
    GID = layer->getTileGIDAt(tileCoord, (TMXTileFlags*)&flags);
    // Vertical
    if( flags & kTMXTileVerticalFlag )
        flags &= ~kTMXTileVerticalFlag;
    else
        flags |= kTMXTileVerticalFlag;    
    layer->setTileGID(GID ,tileCoord, (TMXTileFlags)flags);


    tileCoord = Vec2(2,8);
    GID = layer->getTileGIDAt(tileCoord, (TMXTileFlags*)&flags);
    // Horizontal
    if( flags & kTMXTileHorizontalFlag )
        flags &= ~kTMXTileHorizontalFlag;
    else
        flags |= kTMXTileHorizontalFlag;    
    layer->setTileGID(GID, tileCoord, (TMXTileFlags)flags);    
}
//------------------------------------------------------------------
//
// TMXOrthoFromXMLTestNew
//
//------------------------------------------------------------------

TMXOrthoFromXMLTestNew::TMXOrthoFromXMLTestNew()
{
    std::string resources = "TileMaps";        // partial paths are OK as resource paths.
    std::string file = resources + "/orthogonal-test1.tmx";

    auto str = __String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
    CCASSERT(str != nullptr, "Unable to open file");

    auto map = cocos2d::experimental::TMXTiledMap::createWithXML(str->getCString() ,resources.c_str());
    addChild(map, 0, kTagTileMap);

    auto s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);

    auto action = ScaleBy::create(2, 0.5f);
    map->runAction(action);
}

std::string TMXOrthoFromXMLTestNew::title() const
{
    return "TMX created from XML test";
}
//------------------------------------------------------------------
//
// TMXOrthoXMLFormatTestNew
//
//------------------------------------------------------------------

TMXOrthoXMLFormatTestNew::TMXOrthoXMLFormatTestNew()
{
    // this test tests for:
    // 1. load xml format tilemap
    // 2. gid lower than firstgid is ignored
    // 3. firstgid in tsx is ignored, tile property in tsx loaded correctly.
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/xml-test.tmx");
    addChild(map, 0, kTagTileMap);
    
    auto s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);
    
    for(int i=24;i<=26;i++){
        log("GID:%i, Properties:%s", i, map->getPropertiesForGID(i).asValueMap()["name"].asString().c_str());
    }
    
    auto action = ScaleBy::create(2, 0.5f);
    map->runAction(action);
}

std::string TMXOrthoXMLFormatTestNew::title() const
{
    return "you should see blue, green and yellow in console.";
}

//------------------------------------------------------------------
//
// TMXBug987New
//
//------------------------------------------------------------------
TMXBug987New::TMXBug987New()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/orthogonal-test6.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s1 = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s1.width,s1.height);

    map->setAnchorPoint(Vec2(0, 0));
    auto layer = map->getLayer("Tile Layer 1");
    layer->setTileGID(3, Vec2(2,2));
}

std::string TMXBug987New::title() const
{
    return "TMX Bug 987";
}

std::string TMXBug987New::subtitle() const
{
    return "You should see an square";
}

//------------------------------------------------------------------
//
// TMXBug787New
//
//------------------------------------------------------------------
TMXBug787New::TMXBug787New()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/iso-test-bug787.tmx");
    addChild(map, 0, kTagTileMap);

    map->setScale(0.25f);
}

std::string TMXBug787New::title() const
{
    return "TMX Bug 787";
}

std::string TMXBug787New::subtitle() const
{
    return "You should see a map";
}

//------------------------------------------------------------------
//
// TMXGIDObjectsTestNew
//
//------------------------------------------------------------------
TMXGIDObjectsTestNew::TMXGIDObjectsTestNew()
{
    auto map = cocos2d::experimental::TMXTiledMap::create("TileMaps/test-object-layer.tmx");
    addChild(map, -1, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("Contentsize: %f, %f", s.width, s.height);

    CCLOG("----> Iterating over all the group objets");
    
    auto drawNode = DrawNode::create();
    Color4F color(1.0, 1.0, 1.0, 1.0);
    auto group = map->getObjectGroup("Object Layer 1");
    auto objects = group->getObjects();
    for (auto& obj : objects)
    {
        ValueMap& dict = obj.asValueMap();
        
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        
        drawNode->drawLine(Vec2(x, y), Vec2(x + width, y), color);
        drawNode->drawLine(Vec2(x + width, y), Vec2(x + width, y + height), color);
        drawNode->drawLine(Vec2(x + width,y + height), Vec2(x,y + height), color);
        drawNode->drawLine(Vec2(x,y + height), Vec2(x,y), color);
    }
    map->addChild(drawNode, 10);
}

std::string TMXGIDObjectsTestNew::title() const
{
    return "TMX GID objects";
}

std::string TMXGIDObjectsTestNew::subtitle() const
{
    return "Tiles are created from an object group";
}
