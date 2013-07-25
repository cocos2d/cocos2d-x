#include "TileMapTest.h"
#include "../testResource.h"

enum 
{
    kTagTileMap = 1,
};

Layer* nextTileMapAction();
Layer* backTileMapAction();
Layer* restartTileMapAction();

//------------------------------------------------------------------
//
// TileMapTest
//
//------------------------------------------------------------------
TileMapTest::TileMapTest()
{
    TileMapAtlas* map = TileMapAtlas::create(s_TilesPng,  s_LevelMapTga, 16, 16);
    // Convert it to "alias" (GL_LINEAR filtering)
    map->getTexture()->setAntiAliasTexParameters();
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    // If you are not going to use the Map, you can free it now
    // NEW since v0.7
    map->releaseMap();
    
    addChild(map, 0, kTagTileMap);
    
    map->setAnchorPoint( Point(0, 0.5f) );

    ScaleBy *scale = ScaleBy::create(4, 0.8f);
    ActionInterval *scaleBack = scale->reverse();

    Sequence* seq = Sequence::create(scale, scaleBack, NULL);

    map->runAction(RepeatForever::create(seq));
}

std::string TileMapTest::title()
{
    return "TileMapAtlas";
}

//------------------------------------------------------------------
//
// TileMapEditTest
//
//------------------------------------------------------------------
TileMapEditTest::TileMapEditTest()
{
    TileMapAtlas* map = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    // Create an Aliased Atlas
    map->getTexture()->setAliasTexParameters();
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // If you are not going to use the Map, you can free it now
    // [tilemap releaseMap);
    // And if you are going to use, it you can access the data with:
    schedule(schedule_selector(TileMapEditTest::updateMap), 0.2f);
    
    addChild(map, 0, kTagTileMap);
    
    map->setAnchorPoint( Point(0, 0) );
    map->setPosition( Point(-20,-200) );
}

void TileMapEditTest::updateMap(float dt)
{
    // IMPORTANT
    //   The only limitation is that you cannot change an empty, or assign an empty tile to a tile
    //   The value 0 not rendered so don't assign or change a tile with value 0

    TileMapAtlas* tilemap = (TileMapAtlas*) getChildByTag(kTagTileMap);
    
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
    Color3B c = tilemap->getTileAt(Point(13,21));        
    c.r++;
    c.r %= 50;
    if( c.r==0)
        c.r=1;
    
    // NEW since v0.7
    tilemap->setTile(c, Point(13,21) );             
}

std::string TileMapEditTest::title()
{
    return "Editable TileMapAtlas";
}

//------------------------------------------------------------------
//
// TMXOrthoTest
//
//------------------------------------------------------------------
TMXOrthoTest::TMXOrthoTest()
{
    //
    // Test orthogonal with 3d camera and anti-alias textures
    //
    // it should not flicker. No artifacts should appear
    //
    //CCLayerColor* color = LayerColor::create( Color4B(64,64,64,255) );
    //addChild(color, -1);

    TMXTiledMap* map = TMXTiledMap::create("TileMaps/orthogonal-test2.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    Array * pChildrenArray = map->getChildren();
    SpriteBatchNode* child = NULL;
    Object* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = static_cast<SpriteBatchNode*>(pObject);

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }

    float x, y, z;
    map->getCamera()->getEyeXYZ(&x, &y, &z);
    map->getCamera()->setEyeXYZ(x-200, y, z+300);    
}

void TMXOrthoTest::onEnter()
{
    TileDemo::onEnter();

    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void TMXOrthoTest::onExit()
{
    Director::getInstance()->setProjection(Director::Projection::_2D);
    TileDemo::onExit();
}

std::string TMXOrthoTest::title()
{
    return "TMX Orthogonal test";
}

//------------------------------------------------------------------
//
// TMXOrthoTest2
//
//------------------------------------------------------------------
TMXOrthoTest2::TMXOrthoTest2()
{
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/orthogonal-test1.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    Array* pChildrenArray = map->getChildren();
    SpriteBatchNode* child = NULL;
    Object* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = static_cast<SpriteBatchNode*>(pObject);

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }

    map->runAction( ScaleBy::create(2, 0.5f) ) ;
}

std::string TMXOrthoTest2::title()
{
    return "TMX Ortho test2";
}

//------------------------------------------------------------------
//
// TMXOrthoTest3
//
//------------------------------------------------------------------
TMXOrthoTest3::TMXOrthoTest3()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test3.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    Array* pChildrenArray = map->getChildren();
    SpriteBatchNode* child = NULL;
    Object* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = static_cast<SpriteBatchNode*>(pObject);

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }
    
    map->setScale(0.2f);
    map->setAnchorPoint( Point(0.5f, 0.5f) );
}

std::string TMXOrthoTest3::title()
{
    return "TMX anchorPoint test";
}

//------------------------------------------------------------------
//
// TMXOrthoTest4
//
//------------------------------------------------------------------
TMXOrthoTest4::TMXOrthoTest4()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test4.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s1 = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s1.width,s1.height);
    
    Array* pChildrenArray = map->getChildren();
    SpriteBatchNode* child = NULL;
    Object* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = static_cast<SpriteBatchNode*>(pObject);

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }
    
    map->setAnchorPoint(Point(0, 0));

    auto layer = map->getLayer("Layer 0");
    Size s = layer->getLayerSize();
    
    Sprite* sprite;
    sprite = layer->getTileAt(Point(0,0));
    sprite->setScale(2);
    sprite = layer->getTileAt(Point(s.width-1,0));
    sprite->setScale(2);
    sprite = layer->getTileAt(Point(0,s.height-1));
    sprite->setScale(2);
    sprite = layer->getTileAt(Point(s.width-1,s.height-1));
    sprite->setScale(2);

    schedule( schedule_selector(TMXOrthoTest4::removeSprite), 2 );

}

void TMXOrthoTest4::removeSprite(float dt)
{
    unschedule(schedule_selector(TMXOrthoTest4::removeSprite));

    auto map = static_cast<TMXTiledMap*>( getChildByTag(kTagTileMap) );
    auto layer = map->getLayer("Layer 0");
    Size s = layer->getLayerSize();

    Sprite* sprite = layer->getTileAt( Point(s.width-1,0) );
    layer->removeChild(sprite, true);
}

std::string TMXOrthoTest4::title()
{
    return "TMX width/height test";
}

//------------------------------------------------------------------
//
// TMXReadWriteTest
//
//------------------------------------------------------------------
enum
{
    SID_UPDATECOL = 100,
    SID_REPAINTWITHGID,
    SID_REMOVETILES
};

TMXReadWriteTest::TMXReadWriteTest()
{
    _gid = 0;
    
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/orthogonal-test2.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    
    TMXLayer* layer = map->getLayer("Layer 0");
    layer->getTexture()->setAntiAliasTexParameters();

    map->setScale( 1 );

    Sprite *tile0 = layer->getTileAt(Point(1,63));
    Sprite *tile1 = layer->getTileAt(Point(2,63));
    Sprite *tile2 = layer->getTileAt(Point(3,62));//Point(1,62));
    Sprite *tile3 = layer->getTileAt(Point(2,62));
    tile0->setAnchorPoint( Point(0.5f, 0.5f) );
    tile1->setAnchorPoint( Point(0.5f, 0.5f) );
    tile2->setAnchorPoint( Point(0.5f, 0.5f) );
    tile3->setAnchorPoint( Point(0.5f, 0.5f) );

    ActionInterval* move = MoveBy::create(0.5f, Point(0,160));
    ActionInterval* rotate = RotateBy::create(2, 360);
    ActionInterval* scale = ScaleBy::create(2, 5);
    ActionInterval* opacity = FadeOut::create(2);
    ActionInterval* fadein = FadeIn::create(2);
    ActionInterval* scaleback = ScaleTo::create(1, 1);
    ActionInstant* finish = CallFuncN::create(CC_CALLBACK_1(TMXReadWriteTest::removeSprite, this));
    Sequence* seq0 = Sequence::create(move, rotate, scale, opacity, fadein, scaleback, finish, NULL);
    ActionInterval* seq1 = seq0->clone();
    ActionInterval* seq2 = seq0->clone();
    ActionInterval* seq3 = seq0->clone();
    
    tile0->runAction(seq0);
    tile1->runAction(seq1);
    tile2->runAction(seq2);
    tile3->runAction(seq3);
    
    
    _gid = layer->getTileGIDAt(Point(0,63));
    ////----CCLOG("Tile GID at:(0,63) is: %d", _gid);

    schedule(schedule_selector(TMXReadWriteTest::updateCol), 2.0f); 
    schedule(schedule_selector(TMXReadWriteTest::repaintWithGID), 2.05f);
    schedule(schedule_selector(TMXReadWriteTest::removeTiles), 1.0f); 

    ////----CCLOG("++++atlas quantity: %d", layer->textureAtlas()->getTotalQuads());
    ////----CCLOG("++++children: %d", layer->getChildren()->count() );
    
    _gid2 = 0;
}

void TMXReadWriteTest::removeSprite(Node* sender)
{
    ////----CCLOG("removing tile: %x", sender);
    Node* p = ((Node*)sender)->getParent();

    if (p)
    {
        p->removeChild((Node*)sender, true);
    }    
    
    //////----CCLOG("atlas quantity: %d", p->textureAtlas()->totalQuads());
}

void TMXReadWriteTest::updateCol(float dt)
{    
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(kTagTileMap);
    TMXLayer *layer = (TMXLayer*)map->getChildByTag(0);

    ////----CCLOG("++++atlas quantity: %d", layer->textureAtlas()->getTotalQuads());
    ////----CCLOG("++++children: %d", layer->getChildren()->count() );


    Size s = layer->getLayerSize();

    for( int y=0; y< s.height; y++ ) 
    {
        layer->setTileGID(_gid2, Point((float)3, (float)y));
    }
    
    _gid2 = (_gid2 + 1) % 80;
}

void TMXReadWriteTest::repaintWithGID(float dt)
{
//    unschedule:_cmd);
    
    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(kTagTileMap);
    TMXLayer *layer = (TMXLayer*)map->getChildByTag(0);
    
    Size s = layer->getLayerSize();
    for( int x=0; x<s.width;x++) 
    {
        int y = (int)s.height-1;
        unsigned int tmpgid = layer->getTileGIDAt( Point((float)x, (float)y) );
        layer->setTileGID(tmpgid+1, Point((float)x, (float)y));
    }
}

void TMXReadWriteTest::removeTiles(float dt)
{
    unschedule(schedule_selector(TMXReadWriteTest::removeTiles));

    TMXTiledMap* map = (TMXTiledMap*)getChildByTag(kTagTileMap);
    TMXLayer *layer = (TMXLayer*)map->getChildByTag(0);
    Size s = layer->getLayerSize();

    for( int y=0; y< s.height; y++ ) 
    {
        layer->removeTileAt( Point(5.0, (float)y) );
    }
}



std::string TMXReadWriteTest::title()
{
    return "TMX Read/Write test";
}

//------------------------------------------------------------------
//
// TMXHexTest
//
//------------------------------------------------------------------
TMXHexTest::TMXHexTest()
{
    LayerColor* color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/hexa-test.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXHexTest::title()
{
    return "TMX Hex tes";
}

//------------------------------------------------------------------
//
// TMXIsoTest
//
//------------------------------------------------------------------
TMXIsoTest::TMXIsoTest()
{
    LayerColor* color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/iso-test.tmx");
    addChild(map, 0, kTagTileMap);        
    
    // move map to the center of the screen
    Size ms = map->getMapSize();
    Size ts = map->getTileSize();
    map->runAction( MoveTo::create(1.0f, Point( -ms.width * ts.width/2, -ms.height * ts.height/2 )) ); 
}

std::string TMXIsoTest::title()
{
    return "TMX Isometric test 0";
}

//------------------------------------------------------------------
//
// TMXIsoTest1
//
//------------------------------------------------------------------
TMXIsoTest1::TMXIsoTest1()
{
    LayerColor* color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/iso-test1.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    map->setAnchorPoint(Point(0.5f, 0.5f));
}

std::string TMXIsoTest1::title()
{
    return "TMX Isometric test + anchorPoint";
}

//------------------------------------------------------------------
//
// TMXIsoTest2
//
//------------------------------------------------------------------
TMXIsoTest2::TMXIsoTest2()
{
    LayerColor* color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/iso-test2.tmx");
    addChild(map, 0, kTagTileMap);    
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // move map to the center of the screen
    Size ms = map->getMapSize();
    Size ts = map->getTileSize();
    map->runAction( MoveTo::create(1.0f, Point( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ));
}

std::string TMXIsoTest2::title()
{
    return "TMX Isometric test 2";
}

//------------------------------------------------------------------
//
// TMXUncompressedTest
//
//------------------------------------------------------------------
TMXUncompressedTest::TMXUncompressedTest()
{
    LayerColor* color = LayerColor::create( Color4B(64,64,64,255) );
    addChild(color, -1);
    
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/iso-test2-uncompressed.tmx");
    addChild(map, 0, kTagTileMap);    
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // move map to the center of the screen
    Size ms = map->getMapSize();
    Size ts = map->getTileSize();
    map->runAction(MoveTo::create(1.0f, Point( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ));
    
    // testing release map
    Array* pChildrenArray = map->getChildren();
    TMXLayer* layer;
    Object* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        layer= static_cast<TMXLayer*>(pObject);

        if(!layer)
            break;

        layer->releaseMap();
    }

}

std::string TMXUncompressedTest::title()
{
    return "TMX Uncompressed test";
}

//------------------------------------------------------------------
//
// TMXTilesetTest
//
//------------------------------------------------------------------
TMXTilesetTest::TMXTilesetTest()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test5.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    TMXLayer* layer;
    layer = map->getLayer("Layer 0");
    layer->getTexture()->setAntiAliasTexParameters();
    
    layer = map->getLayer("Layer 1");
    layer->getTexture()->setAntiAliasTexParameters();

    layer = map->getLayer("Layer 2");
    layer->getTexture()->setAntiAliasTexParameters();
}

std::string TMXTilesetTest::title()
{
    return "TMX Tileset test";
}

//------------------------------------------------------------------
//
// TMXOrthoObjectsTest
//
//------------------------------------------------------------------
TMXOrthoObjectsTest::TMXOrthoObjectsTest()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/ortho-objects.tmx");
    addChild(map, -1, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    ////----CCLOG("----> Iterating over all the group objets");
    auto group = map->getObjectGroup("Object Group 1");
    Array* objects = group->getObjects();

    Dictionary* dict = NULL;
    Object* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = static_cast<Dictionary*>(pObj);

        if(!dict)
            break;

        ////----CCLOG("object: %x", dict);
    }
    
    ////----CCLOG("----> Fetching 1 object by name");
    // StringToStringDictionary* platform = group->objectNamed("platform");
    ////----CCLOG("platform: %x", platform);
}

void TMXOrthoObjectsTest::draw()
{
    auto map = static_cast<TMXTiledMap*>( getChildByTag(kTagTileMap) );
    auto group = map->getObjectGroup("Object Group 1");

    Array* objects = group->getObjects();
    Dictionary* dict = NULL;
    Object* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = static_cast<Dictionary*>(pObj);
        
        if(!dict)
            break;
        const char* key = "x";
        int x = ((String*)dict->objectForKey(key))->intValue();
        key = "y";
        int y = ((String*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("y"))->getNumber();
        key = "width";
        int width = ((String*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("width"))->getNumber();
        key = "height";
        int height = ((String*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("height"))->getNumber();
        
        glLineWidth(3);
        
        DrawPrimitives::drawLine( Point((float)x, (float)y), Point((float)(x+width), (float)y) );
        DrawPrimitives::drawLine( Point((float)(x+width), (float)y), Point((float)(x+width), (float)(y+height)) );
        DrawPrimitives::drawLine( Point((float)(x+width), (float)(y+height)), Point((float)x, (float)(y+height)) );
        DrawPrimitives::drawLine( Point((float)x, (float)(y+height)), Point((float)x, (float)y) );
        
        glLineWidth(1);
    }
}

std::string TMXOrthoObjectsTest::title()
{
    return "TMX Ortho object test";
}

std::string TMXOrthoObjectsTest::subtitle()
{
    return "You should see a white box around the 3 platforms";
}


//------------------------------------------------------------------
//
// TMXIsoObjectsTest
//
//------------------------------------------------------------------

TMXIsoObjectsTest::TMXIsoObjectsTest()
{
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/iso-test-objectgroup.tmx");
    addChild(map, -1, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    TMXObjectGroup* group = map->getObjectGroup("Object Group 1");

    //UxMutableArray* objects = group->objects();
    Array* objects = group->getObjects();
    //UxMutableDictionary<std::string>* dict;
    Dictionary* dict;
    Object* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = static_cast<Dictionary*>(pObj);

        if(!dict)
            break;

        ////----CCLOG("object: %x", dict);
    }        
}

void TMXIsoObjectsTest::draw()
{
    TMXTiledMap *map = (TMXTiledMap*) getChildByTag(kTagTileMap);
    TMXObjectGroup *group = map->getObjectGroup("Object Group 1");

    Array* objects = group->getObjects();
    Dictionary* dict;
    Object* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = static_cast<Dictionary*>(pObj);

        if(!dict)
            break;
        const char* key = "x";
        int x = static_cast<String*>(dict->objectForKey(key))->intValue();
        key = "y";
        int y = static_cast<String*>(dict->objectForKey(key))->intValue();
        key = "width";
        int width = static_cast<String*>(dict->objectForKey(key))->intValue();
        key = "height";
        int height = static_cast<String*>(dict->objectForKey(key))->intValue();
        
        glLineWidth(3);
        
        DrawPrimitives::drawLine( Point(x,y), Point(x+width,y) );
        DrawPrimitives::drawLine( Point(x+width,y), Point(x+width,y+height) );
        DrawPrimitives::drawLine( Point(x+width,y+height), Point(x,y+height) );
        DrawPrimitives::drawLine( Point(x,y+height), Point(x,y) );
        
        glLineWidth(1);
    }
}

std::string TMXIsoObjectsTest::title()
{
    return "TMX Iso object test";
}

std::string TMXIsoObjectsTest::subtitle()
{
    return "You need to parse them manually. See bug #810";
}


//------------------------------------------------------------------
//
// TMXResizeTest
//
//------------------------------------------------------------------

TMXResizeTest::TMXResizeTest()
{
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/orthogonal-test5.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    TMXLayer* layer;
    layer = map->getLayer("Layer 0");

    Size ls = layer->getLayerSize();
    for (unsigned int y = 0; y < ls.height; y++) 
    {
        for (unsigned int x = 0; x < ls.width; x++) 
        {
            layer->setTileGID(1, Point( x, y ) );
        }
    }        
}

std::string TMXResizeTest::title()
{
    return "TMX resize test";
}

std::string TMXResizeTest::subtitle()
{
    return "Should not crash. Testing issue #740";
}


//------------------------------------------------------------------
//
// TMXIsoZorder
//
//------------------------------------------------------------------
TMXIsoZorder::TMXIsoZorder()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/iso-test-zorder.tmx");
    addChild(map, 0, kTagTileMap);

    Size s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    map->setPosition(Point(-s.width/2,0));
    
    _tamara = Sprite::create(s_pathSister1);
    map->addChild(_tamara, map->getChildren()->count() );
    _tamara->retain();
    int mapWidth = map->getMapSize().width * map->getTileSize().width;
    _tamara->setPosition(CC_POINT_PIXELS_TO_POINTS(Point( mapWidth/2,0)));
    _tamara->setAnchorPoint(Point(0.5f,0));

    
    ActionInterval* move = MoveBy::create(10, Point(300,250));
    ActionInterval* back = move->reverse();
    Sequence* seq = Sequence::create(move, back,NULL);
    _tamara->runAction( RepeatForever::create(seq) );
    
    schedule( schedule_selector(TMXIsoZorder::repositionSprite) );
}

TMXIsoZorder::~TMXIsoZorder()
{
    _tamara->release();
}

void TMXIsoZorder::onExit()
{
    unschedule(schedule_selector(TMXIsoZorder::repositionSprite));
    TileDemo::onExit();
}

void TMXIsoZorder::repositionSprite(float dt)
{
    Point p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    Node *map = getChildByTag(kTagTileMap);
    
    // there are only 4 layers. (grass and 3 trees layers)
    // if tamara < 48, z=4
    // if tamara < 96, z=3
    // if tamara < 144,z=2
    
    int newZ = 4 - (p.y / 48);
    newZ = max(newZ,0);
    
    map->reorderChild(_tamara, newZ);    
}

std::string TMXIsoZorder::title()
{
    return "TMX Iso Zorder";
}

std::string TMXIsoZorder::subtitle()
{
    return "Sprite should hide behind the trees";
}


//------------------------------------------------------------------
//
// TMXOrthoZorder
//
//------------------------------------------------------------------
TMXOrthoZorder::TMXOrthoZorder()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test-zorder.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    _tamara = Sprite::create(s_pathSister1);
    map->addChild(_tamara,  map->getChildren()->count());
    _tamara->retain();
    _tamara->setAnchorPoint(Point(0.5f,0));

    
    ActionInterval* move = MoveBy::create(10, Point(400,450));
    ActionInterval* back = move->reverse();
    Sequence* seq = Sequence::create(move, back,NULL);
    _tamara->runAction( RepeatForever::create(seq));
    
    schedule( schedule_selector(TMXOrthoZorder::repositionSprite));
}

TMXOrthoZorder::~TMXOrthoZorder()
{
    _tamara->release();
}

void TMXOrthoZorder::repositionSprite(float dt)
{
    Point p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    Node* map = getChildByTag(kTagTileMap);
    
    // there are only 4 layers. (grass and 3 trees layers)
    // if tamara < 81, z=4
    // if tamara < 162, z=3
    // if tamara < 243,z=2

    // -10: customization for this particular sample
    int newZ = 4 - ( (p.y-10) / 81);
    newZ = max(newZ,0);

    map->reorderChild(_tamara, newZ);
}

std::string TMXOrthoZorder::title()
{
    return "TMX Ortho Zorder";
}

std::string TMXOrthoZorder::subtitle()
{
    return "Sprite should hide behind the trees";
}


//------------------------------------------------------------------
//
// TMXIsoVertexZ
//
//------------------------------------------------------------------
TMXIsoVertexZ::TMXIsoVertexZ()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/iso-test-vertexz.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size s = map->getContentSize();
    map->setPosition( Point(-s.width/2,0) );
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    // can use any Sprite and it will work OK.
    TMXLayer* layer = map->getLayer("Trees");
    _tamara = layer->getTileAt( Point(29,29) );
    _tamara->retain();
    
    ActionInterval* move = MoveBy::create(10, Point(300,250) * (1/CC_CONTENT_SCALE_FACTOR()));
    ActionInterval* back = move->reverse();
    Sequence* seq = Sequence::create(move, back,NULL);
    _tamara->runAction( RepeatForever::create(seq) );
    
    schedule( schedule_selector(TMXIsoVertexZ::repositionSprite));
    
}

TMXIsoVertexZ::~TMXIsoVertexZ()
{
    _tamara->release();
}

void TMXIsoVertexZ::repositionSprite(float dt)
{
    // tile height is 64x32
    // map size: 30x30
    Point p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    float newZ = -(p.y+32) /16;
    _tamara->setVertexZ( newZ );
}

void TMXIsoVertexZ::onEnter()
{
    TileDemo::onEnter();
    
    // TIP: 2d projection should be used
    Director::getInstance()->setProjection(Director::Projection::_2D);
}

void TMXIsoVertexZ::onExit()
{
    // At exit use any other projection. 
    //    Director::getInstance()->setProjection:Director::Projection::_3D);
    TileDemo::onExit();
}

std::string TMXIsoVertexZ::title()
{
    return "TMX Iso VertexZ";
}

std::string TMXIsoVertexZ::subtitle()
{
    return "Sprite should hide behind the trees";
}


//------------------------------------------------------------------
//
// TMXOrthoVertexZ
//
//------------------------------------------------------------------
TMXOrthoVertexZ::TMXOrthoVertexZ()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test-vertexz.tmx");
    addChild(map, 0, kTagTileMap);
    
    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    // can use any Sprite and it will work OK.
    TMXLayer* layer = map->getLayer("trees");
    _tamara = layer->getTileAt(Point(0,11));
    CCLOG("%p vertexZ: %f", _tamara, _tamara->getVertexZ());
    _tamara->retain();

    ActionInterval* move = MoveBy::create(10, Point(400,450) * (1/CC_CONTENT_SCALE_FACTOR()));
    ActionInterval* back = move->reverse();
    Sequence* seq = Sequence::create(move, back,NULL);
    _tamara->runAction( RepeatForever::create(seq));
    
    schedule(schedule_selector(TMXOrthoVertexZ::repositionSprite));
    
}

TMXOrthoVertexZ::~TMXOrthoVertexZ()
{
    _tamara->release();
}

void TMXOrthoVertexZ::repositionSprite(float dt)
{
    // tile height is 101x81
    // map size: 12x12
    Point p = _tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    _tamara->setVertexZ( -( (p.y+81) /81) );
}

void TMXOrthoVertexZ::onEnter()
{
    TileDemo::onEnter();
    
    // TIP: 2d projection should be used
    Director::getInstance()->setProjection(Director::Projection::_2D);
}

void TMXOrthoVertexZ::onExit()
{
    // At exit use any other projection. 
    //    Director::getInstance()->setProjection:Director::Projection::_3D);
    TileDemo::onExit();
}

std::string TMXOrthoVertexZ::title()
{
    return "TMX Ortho vertexZ";
}

std::string TMXOrthoVertexZ::subtitle()
{
    return "Sprite should hide behind the trees";
}


//------------------------------------------------------------------
//
// TMXIsoMoveLayer
//
//------------------------------------------------------------------
TMXIsoMoveLayer::TMXIsoMoveLayer()
{
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/iso-test-movelayer.tmx");
    addChild(map, 0, kTagTileMap);
    
    map->setPosition(Point(-700,-50));

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXIsoMoveLayer::title()
{
    return "TMX Iso Move Layer";
}

std::string TMXIsoMoveLayer::subtitle()
{
    return "Trees should be horizontally aligned";
}


//------------------------------------------------------------------
//
// TMXOrthoMoveLayer
//
//------------------------------------------------------------------
TMXOrthoMoveLayer::TMXOrthoMoveLayer()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test-movelayer.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
}

std::string TMXOrthoMoveLayer::title()
{
    return "TMX Ortho Move Layer";
}

std::string TMXOrthoMoveLayer::subtitle()
{
    return "Trees should be horizontally aligned";
}

//------------------------------------------------------------------
//
// TMXTilePropertyTest
//
//------------------------------------------------------------------

TMXTilePropertyTest::TMXTilePropertyTest()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/ortho-tile-property.tmx");
    addChild(map ,0 ,kTagTileMap);

    for(int i=1;i<=20;i++){
        log("GID:%i, Properties:%p", i, map->getPropertiesForGID(i));
    }
}

std::string TMXTilePropertyTest::title()
{
    return "TMX Tile Property Test";
}

std::string TMXTilePropertyTest::subtitle()
{
    return "In the console you should see tile properties";
}

//------------------------------------------------------------------
//
// TMXOrthoFlipTest
//
//------------------------------------------------------------------

TMXOrthoFlipTest::TMXOrthoFlipTest()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/ortho-rotation-test.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);

    Object* pObj = NULL;
    CCARRAY_FOREACH(map->getChildren(), pObj)
    {
        SpriteBatchNode* child = static_cast<SpriteBatchNode*>(pObj);
        child->getTexture()->setAntiAliasTexParameters();
    }

    ScaleBy* action = ScaleBy::create(2, 0.5f);
    map->runAction(action);
}

std::string TMXOrthoFlipTest::title()
{
    return "TMX tile flip test";
}

//------------------------------------------------------------------
//
// TMXOrthoFlipRunTimeTest
//
//------------------------------------------------------------------

TMXOrthoFlipRunTimeTest::TMXOrthoFlipRunTimeTest()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/ortho-rotation-test.tmx");
    addChild(map, 0, kTagTileMap);

    Size s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);

    Object* pObj = NULL;
    CCARRAY_FOREACH(map->getChildren(), pObj)
    {
        SpriteBatchNode* child = static_cast<SpriteBatchNode*>(pObj);
        child->getTexture()->setAntiAliasTexParameters();
    }

    ScaleBy* action = ScaleBy::create(2, 0.5f);
    map->runAction(action);

    schedule(schedule_selector(TMXOrthoFlipRunTimeTest::flipIt), 1.0f);
}

std::string TMXOrthoFlipRunTimeTest::title()
{
    return "TMX tile flip run time test";
}

std::string TMXOrthoFlipRunTimeTest::subtitle()
{
    return "in 2 sec bottom left tiles will flip";
}

void TMXOrthoFlipRunTimeTest::flipIt(float dt)
{
    TMXTiledMap *map = (TMXTiledMap*) getChildByTag(kTagTileMap); 
    TMXLayer *layer = map->getLayer("Layer 0");

    //blue diamond 
    Point tileCoord = Point(1,10);
    int flags;
    unsigned int GID = layer->getTileGIDAt(tileCoord, (ccTMXTileFlags*)&flags);
    // Vertical
    if( flags & kTMXTileVerticalFlag )
        flags &= ~kTMXTileVerticalFlag;
    else
        flags |= kTMXTileVerticalFlag;
    layer->setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags);


    tileCoord = Point(1,8);    
    GID = layer->getTileGIDAt(tileCoord, (ccTMXTileFlags*)&flags);
    // Vertical
    if( flags & kTMXTileVerticalFlag )
        flags &= ~kTMXTileVerticalFlag;
    else
        flags |= kTMXTileVerticalFlag;    
    layer->setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags);


    tileCoord = Point(2,8);
    GID = layer->getTileGIDAt(tileCoord, (ccTMXTileFlags*)&flags);
    // Horizontal
    if( flags & kTMXTileHorizontalFlag )
        flags &= ~kTMXTileHorizontalFlag;
    else
        flags |= kTMXTileHorizontalFlag;    
    layer->setTileGID(GID, tileCoord, (ccTMXTileFlags)flags);    
}
//------------------------------------------------------------------
//
// TMXOrthoFromXMLTest
//
//------------------------------------------------------------------

TMXOrthoFromXMLTest::TMXOrthoFromXMLTest()
{
    string resources = "TileMaps";        // partial paths are OK as resource paths.
    string file = resources + "/orthogonal-test1.tmx";

    String* str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
    CCASSERT(str != NULL, "Unable to open file");

    TMXTiledMap *map = TMXTiledMap::createWithXML(str->getCString() ,resources.c_str());
    addChild(map, 0, kTagTileMap);

    Size s = map->getContentSize();
    log("ContentSize: %f, %f", s.width,s.height);

    Object* pObj = NULL;
    CCARRAY_FOREACH(map->getChildren(), pObj)
    {
        SpriteBatchNode* child = static_cast<SpriteBatchNode*>(pObj);
        child->getTexture()->setAntiAliasTexParameters();
    }

    ScaleBy* action = ScaleBy::create(2, 0.5f);
    map->runAction(action);
}

std::string TMXOrthoFromXMLTest::title()
{
    return "TMX created from XML test";
}

//------------------------------------------------------------------
//
// TMXBug987
//
//------------------------------------------------------------------
TMXBug987::TMXBug987()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/orthogonal-test6.tmx");
    addChild(map, 0, kTagTileMap);

    Size CC_UNUSED s1 = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s1.width,s1.height);

    Array* childs = map->getChildren();
    TMXLayer* node;
    Object* pObject = NULL;
    CCARRAY_FOREACH(childs, pObject)
    {
        node = static_cast<TMXLayer*>(pObject);
        CC_BREAK_IF(!node);
        node->getTexture()->setAntiAliasTexParameters();
    }

    map->setAnchorPoint(Point(0, 0));
    TMXLayer *layer = map->getLayer("Tile Layer 1");
    layer->setTileGID(3, Point(2,2));
}

std::string TMXBug987::title()
{
    return "TMX Bug 987";
}

std::string TMXBug987::subtitle()
{
    return "You should see an square";
}

//------------------------------------------------------------------
//
// TMXBug787
//
//------------------------------------------------------------------
TMXBug787::TMXBug787()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/iso-test-bug787.tmx");
    addChild(map, 0, kTagTileMap);

    map->setScale(0.25f);
}

std::string TMXBug787::title()
{
    return "TMX Bug 787";
}

std::string TMXBug787::subtitle()
{
    return "You should see a map";
}

//------------------------------------------------------------------
//
// TileDemo
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1; 

#define MAX_LAYER    28

Layer* createTileMalayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new TMXIsoZorder();
        case 1: return new TMXOrthoZorder();
        case 2: return new TMXIsoVertexZ();
        case 3: return new TMXOrthoVertexZ();    
        case 4: return new TMXOrthoTest();
        case 5: return new TMXOrthoTest2();
        case 6: return new TMXOrthoTest3();
        case 7: return new TMXOrthoTest4();
        case 8: return new TMXIsoTest();
        case 9: return new TMXIsoTest1();
        case 10: return new TMXIsoTest2();
        case 11: return new TMXUncompressedTest ();
        case 12: return new TMXHexTest();
        case 13: return new TMXReadWriteTest();
        case 14: return new TMXTilesetTest();
        case 15: return new TMXOrthoObjectsTest();
        case 16: return new TMXIsoObjectsTest();
        case 17: return new TMXResizeTest();
        case 18: return new TMXIsoMoveLayer();
        case 19: return new TMXOrthoMoveLayer();
        case 20: return new TMXOrthoFlipTest();
        case 21: return new TMXOrthoFlipRunTimeTest();
        case 22: return new TMXOrthoFromXMLTest();
        case 23: return new TileMapTest();
        case 24: return new TileMapEditTest();
        case 25: return new TMXBug987();
        case 26: return new TMXBug787();
        case 27: return new TMXGIDObjectsTest();
    }

    return NULL;
}

Layer* nextTileMapAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* layer = createTileMalayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backTileMapAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* layer = createTileMalayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartTileMapAction()
{
    Layer* layer = createTileMalayer(sceneIdx);
    layer->autorelease();

    return layer;
} 


TileDemo::TileDemo(void)
: BaseTest()
{
    setTouchEnabled( true );
}

TileDemo::~TileDemo(void)
{
}

std::string TileDemo::title()
{
    return "No title";
}

std::string TileDemo::subtitle()
{
    return "drag the screen";
}

void TileDemo::onEnter()
{
    BaseTest::onEnter();
}

void TileDemo::restartCallback(Object* sender)
{
    Scene* s = new TileMapTestScene();
    s->addChild(restartTileMapAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void TileDemo::nextCallback(Object* sender)
{
    Scene* s = new TileMapTestScene();
    s->addChild( nextTileMapAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void TileDemo::backCallback(Object* sender)
{
    Scene* s = new TileMapTestScene();
    s->addChild( backTileMapAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void TileDemo::ccTouchesMoved(Set  *touches, Event  *event)
{
    Touch *touch = static_cast<Touch*>(touches->anyObject());
    
    Point diff = touch->getDelta();
    Node *node = getChildByTag(kTagTileMap);
    Point currentPos = node->getPosition();
    node->setPosition(currentPos + diff);
}

void TileMapTestScene::runThisTest()
{
    Layer* layer = nextTileMapAction();
    addChild(layer);

    // fix bug #486, #419. 
    // "test" is the default value in Director::setGLDefaultValues()
    // but TransitionTest may setDepthTest(false), we should revert it here
    Director::getInstance()->setDepthTest(true);
    
    Director::getInstance()->replaceScene(this);
}

TMXGIDObjectsTest::TMXGIDObjectsTest()
{
    TMXTiledMap *map = TMXTiledMap::create("TileMaps/test-object-layer.tmx");
    addChild(map, -1, kTagTileMap);

    Size CC_UNUSED s = map->getContentSize();
    CCLOG("Contentsize: %f, %f", s.width, s.height);

    CCLOG("----> Iterating over all the group objets");
    //CCTMXObjectGroup *group = map->objectGroupNamed("Object Layer 1");

}

void TMXGIDObjectsTest::draw()
{
    TMXTiledMap *map = (TMXTiledMap*)getChildByTag(kTagTileMap);
    TMXObjectGroup *group = map->getObjectGroup("Object Layer 1");

    Array *array = group->getObjects();
    Dictionary* dict;
    Object* pObj = NULL;
    CCARRAY_FOREACH(array, pObj)
    {
        dict = static_cast<Dictionary*>(pObj);
        if(!dict)
        {
            break;
        }

        const char* key = "x";
        int x = ((String*)dict->objectForKey(key))->intValue();
        key = "y";
        int y = ((String*)dict->objectForKey(key))->intValue();
        key = "width";
        int width = ((String*)dict->objectForKey(key))->intValue();
        key = "height";
        int height = ((String*)dict->objectForKey(key))->intValue();

        glLineWidth(3);

        DrawPrimitives::drawLine(Point(x, y), Point(x + width, y));
        DrawPrimitives::drawLine(Point(x + width, y), Point(x + width, y + height));
        DrawPrimitives::drawLine(Point(x + width,y + height), Point(x,y + height));
        DrawPrimitives::drawLine(Point(x,y + height), Point(x,y));

        glLineWidth(1);
    }
}

string TMXGIDObjectsTest::title()
{
    return "TMX GID objects";
}

string TMXGIDObjectsTest::subtitle()
{
    return "Tiles are created from an object group";
}
