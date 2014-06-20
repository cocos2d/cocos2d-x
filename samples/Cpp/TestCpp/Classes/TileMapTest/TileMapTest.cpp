#include "TileMapTest.h"
#include "../testResource.h"

enum 
{
    kTagTileMap = 1,
};

CCLayer* nextTileMapAction();
CCLayer* backTileMapAction();
CCLayer* restartTileMapAction();

//------------------------------------------------------------------
//
// TileMapTest
//
//------------------------------------------------------------------
TileMapTest::TileMapTest()
{
    CCTileMapAtlas* map = CCTileMapAtlas::create(s_TilesPng,  s_LevelMapTga, 16, 16);
    // Convert it to "alias" (GL_LINEAR filtering)
    map->getTexture()->setAntiAliasTexParameters();
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    // If you are not going to use the Map, you can free it now
    // NEW since v0.7
    map->releaseMap();
    
    addChild(map, 0, kTagTileMap);
    
    map->setAnchorPoint( ccp(0, 0.5f) );

    CCScaleBy *scale = CCScaleBy::create(4, 0.8f);
    CCActionInterval *scaleBack = scale->reverse();

    CCSequence* seq = CCSequence::create(scale, scaleBack, NULL);

    map->runAction(CCRepeatForever::create(seq));
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
    CCTileMapAtlas* map = CCTileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    // Create an Aliased Atlas
    map->getTexture()->setAliasTexParameters();
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // If you are not going to use the Map, you can free it now
    // [tilemap releaseMap);
    // And if you are going to use, it you can access the data with:
    schedule(schedule_selector(TileMapEditTest::updateMap), 0.2f);
    
    addChild(map, 0, kTagTileMap);
    
    map->setAnchorPoint( ccp(0, 0) );
    map->setPosition( ccp(-20,-200) );
}

void TileMapEditTest::updateMap(float dt)
{
    // IMPORTANT
    //   The only limitation is that you cannot change an empty, or assign an empty tile to a tile
    //   The value 0 not rendered so don't assign or change a tile with value 0

    CCTileMapAtlas* tilemap = (CCTileMapAtlas*) getChildByTag(kTagTileMap);
    
    //
    // For example you can iterate over all the tiles
    // using this code, but try to avoid the iteration
    // over all your tiles in every frame. It's very expensive
    //    for(int x=0; x < tilemap.tgaInfo->width; x++) {
    //        for(int y=0; y < tilemap.tgaInfo->height; y++) {
    //            ccColor3B c =[tilemap tileAt:CCSizeMake(x,y));
    //            if( c.r != 0 ) {
    //                ////----CCLOG("%d,%d = %d", x,y,c.r);
    //            }
    //        }
    //    }
    
    // NEW since v0.7
    ccColor3B c = tilemap->tileAt(ccp(13,21));        
    c.r++;
    c.r %= 50;
    if( c.r==0)
        c.r=1;
    
    // NEW since v0.7
    tilemap->setTile(c, ccp(13,21) );             
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
    //CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    //addChild(color, -1);

    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/orthogonal-test2.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    CCArray * pChildrenArray = map->getChildren();
    CCSpriteBatchNode* child = NULL;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = (CCSpriteBatchNode*)pObject;

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }
}

void TMXOrthoTest::onEnter()
{
    TileDemo::onEnter();
}

void TMXOrthoTest::onExit()
{
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
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/orthogonal-test1.tmx");
    addChild(map, 0, kTagTileMap);

    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    CCArray* pChildrenArray = map->getChildren();
    CCSpriteBatchNode* child = NULL;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = (CCSpriteBatchNode*)pObject;

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }

    map->runAction( CCScaleBy::create(2, 0.5f) ) ;
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test3.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    CCArray* pChildrenArray = map->getChildren();
    CCSpriteBatchNode* child = NULL;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = (CCSpriteBatchNode*)pObject;

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }
    
    map->setScale(0.2f);
    map->setAnchorPoint( ccp(0.5f, 0.5f) );
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test4.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s1 = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s1.width,s1.height);
    
    CCArray* pChildrenArray = map->getChildren();
    CCSpriteBatchNode* child = NULL;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        child = (CCSpriteBatchNode*)pObject;

        if(!child)
            break;

        child->getTexture()->setAntiAliasTexParameters();
    }
    
    map->setAnchorPoint(ccp(0, 0));

    CCTMXLayer* layer = map->layerNamed("Layer 0");
    CCSize s = layer->getLayerSize();
    
    CCSprite* sprite;
    sprite = layer->tileAt(ccp(0,0));
    sprite->setScale(2);
    sprite = layer->tileAt(ccp(s.width-1,0));
    sprite->setScale(2);
    sprite = layer->tileAt(ccp(0,s.height-1));
    sprite->setScale(2);
    sprite = layer->tileAt(ccp(s.width-1,s.height-1));
    sprite->setScale(2);

    schedule( schedule_selector(TMXOrthoTest4::removeSprite), 2 );

}

void TMXOrthoTest4::removeSprite(float dt)
{
    unschedule(schedule_selector(TMXOrthoTest4::removeSprite));

    CCTMXTiledMap *map = (CCTMXTiledMap*)getChildByTag(kTagTileMap);
    CCTMXLayer* layer = map->layerNamed("Layer 0");
    CCSize s = layer->getLayerSize();

    CCSprite* sprite = layer->tileAt( ccp(s.width-1,0) );
    CCSprite* sprite2 = layer->tileAt(ccp(s.width-1, s.height-1));
    layer->removeChild(sprite, true);
    CCSprite* sprite3 = layer->tileAt(ccp(2, s.height-1));
    layer->removeChild(sprite3, true);
    layer->removeChild(sprite2, true);
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
    m_gid = 0;
    
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/orthogonal-test2.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    
    CCTMXLayer* layer = map->layerNamed("Layer 0");
    layer->getTexture()->setAntiAliasTexParameters();

    map->setScale( 1 );

    CCSprite *tile0 = layer->tileAt(ccp(1,63));
    CCSprite *tile1 = layer->tileAt(ccp(2,63));
    CCSprite *tile2 = layer->tileAt(ccp(3,62));//ccp(1,62));
    CCSprite *tile3 = layer->tileAt(ccp(2,62));
    tile0->setAnchorPoint( ccp(0.5f, 0.5f) );
    tile1->setAnchorPoint( ccp(0.5f, 0.5f) );
    tile2->setAnchorPoint( ccp(0.5f, 0.5f) );
    tile3->setAnchorPoint( ccp(0.5f, 0.5f) );

    CCActionInterval* move = CCMoveBy::create(0.5f, ccp(0,160));
    CCActionInterval* rotate = CCRotateBy::create(2, 360);
    CCActionInterval* scale = CCScaleBy::create(2, 5);
    CCActionInterval* opacity = CCFadeOut::create(2);
    CCActionInterval* fadein = CCFadeIn::create(2);
    CCActionInterval* scaleback = CCScaleTo::create(1, 1);
    CCActionInstant* finish = CCCallFuncN::create(this, callfuncN_selector(TMXReadWriteTest::removeSprite));
    CCSequence* seq0 = CCSequence::create(move, rotate, scale, opacity, fadein, scaleback, finish, NULL);
    CCActionInterval* seq1 = (CCActionInterval*)(seq0->copy()->autorelease());
    CCActionInterval* seq2 = (CCActionInterval*)(seq0->copy()->autorelease());
    CCActionInterval* seq3 = (CCActionInterval*)(seq0->copy()->autorelease());
    
    tile0->runAction(seq0);
    tile1->runAction(seq1);
    tile2->runAction(seq2);
    tile3->runAction(seq3);
    
    
    m_gid = layer->tileGIDAt(ccp(0,63));
    ////----CCLOG("Tile GID at:(0,63) is: %d", m_gid);

    schedule(schedule_selector(TMXReadWriteTest::updateCol), 2.0f); 
    schedule(schedule_selector(TMXReadWriteTest::repaintWithGID), 2.05f);
    schedule(schedule_selector(TMXReadWriteTest::removeTiles), 1.0f); 

    ////----CCLOG("++++atlas quantity: %d", layer->textureAtlas()->getTotalQuads());
    ////----CCLOG("++++children: %d", layer->getChildren()->count() );
    
    m_gid2 = 0;
}

void TMXReadWriteTest::removeSprite(CCNode* sender)
{
    ////----CCLOG("removing tile: %x", sender);
    CCNode* p = ((CCNode*)sender)->getParent();

    if (p)
    {
        p->removeChild((CCNode*)sender, true);
    }    
    
    //////----CCLOG("atlas quantity: %d", p->textureAtlas()->totalQuads());
}

void TMXReadWriteTest::updateCol(float dt)
{    
    CCTMXTiledMap* map = (CCTMXTiledMap*)getChildByTag(kTagTileMap);
    CCTMXLayer *layer = (CCTMXLayer*)map->getChildByTag(0);

    ////----CCLOG("++++atlas quantity: %d", layer->textureAtlas()->getTotalQuads());
    ////----CCLOG("++++children: %d", layer->getChildren()->count() );


    CCSize s = layer->getLayerSize();

    for( int y=0; y< s.height; y++ ) 
    {
        layer->setTileGID(m_gid2, ccp((float)3, (float)y));
    }
    
    m_gid2 = (m_gid2 + 1) % 80;
}

void TMXReadWriteTest::repaintWithGID(float dt)
{
//    unschedule:_cmd);
    
    CCTMXTiledMap* map = (CCTMXTiledMap*)getChildByTag(kTagTileMap);
    CCTMXLayer *layer = (CCTMXLayer*)map->getChildByTag(0);
    
    CCSize s = layer->getLayerSize();
    for( int x=0; x<s.width;x++) 
    {
        int y = (int)s.height-1;
        unsigned int tmpgid = layer->tileGIDAt( ccp((float)x, (float)y) );
        layer->setTileGID(tmpgid+1, ccp((float)x, (float)y));
    }
}

void TMXReadWriteTest::removeTiles(float dt)
{
    unschedule(schedule_selector(TMXReadWriteTest::removeTiles));

    CCTMXTiledMap* map = (CCTMXTiledMap*)getChildByTag(kTagTileMap);
    CCTMXLayer *layer = (CCTMXLayer*)map->getChildByTag(0);
    CCSize s = layer->getLayerSize();

    for( int y=0; y< s.height; y++ ) 
    {
        layer->removeTileAt( ccp(5.0, (float)y) );
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
    CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    addChild(color, -1);
    
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/hexa-test.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
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
    CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    addChild(color, -1);
    
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/iso-test.tmx");
    addChild(map, 0, kTagTileMap);        
    
    // move map to the center of the screen
    CCSize ms = map->getMapSize();
    CCSize ts = map->getTileSize();
    map->runAction( CCMoveTo::create(1.0f, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 )) ); 
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
    CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    addChild(color, -1);
    
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/iso-test1.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    map->setAnchorPoint(ccp(0.5f, 0.5f));
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
    CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    addChild(color, -1);
    
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/iso-test2.tmx");
    addChild(map, 0, kTagTileMap);    
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // move map to the center of the screen
    CCSize ms = map->getMapSize();
    CCSize ts = map->getTileSize();
    map->runAction( CCMoveTo::create(1.0f, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ));
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
    CCLayerColor* color = CCLayerColor::create( ccc4(64,64,64,255) );
    addChild(color, -1);
    
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/iso-test2-uncompressed.tmx");
    addChild(map, 0, kTagTileMap);    
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // move map to the center of the screen
    CCSize ms = map->getMapSize();
    CCSize ts = map->getTileSize();
    map->runAction(CCMoveTo::create(1.0f, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ));
    
    // testing release map
    CCArray* pChildrenArray = map->getChildren();
    CCTMXLayer* layer;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pChildrenArray, pObject)
    {
        layer= (CCTMXLayer*)pObject;

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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test5.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    CCTMXLayer* layer;
    layer = map->layerNamed("Layer 0");
    layer->getTexture()->setAntiAliasTexParameters();
    
    layer = map->layerNamed("Layer 1");
    layer->getTexture()->setAntiAliasTexParameters();

    layer = map->layerNamed("Layer 2");
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/ortho-objects.tmx");
    addChild(map, -1, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    ////----CCLOG("----> Iterating over all the group objets");
    CCTMXObjectGroup* group = map->objectGroupNamed("Object Group 1");
    CCArray* objects = group->getObjects();

    CCDictionary* dict = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = (CCDictionary*)pObj;//dynamic_cast<CCStringToStringDictionary*>(*it);

        if(!dict)
            break;

        ////----CCLOG("object: %x", dict);
    }
    
    ////----CCLOG("----> Fetching 1 object by name");
    // CCStringToStringDictionary* platform = group->objectNamed("platform");
    ////----CCLOG("platform: %x", platform);
}

void TMXOrthoObjectsTest::draw()
{
    CCTMXTiledMap* map = (CCTMXTiledMap*) getChildByTag(kTagTileMap);
    CCTMXObjectGroup* group = map->objectGroupNamed("Object Group 1");

    CCArray* objects = group->getObjects();
    CCDictionary* dict = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = (CCDictionary*)pObj;//dynamic_cast<CCStringToStringDictionary*>(*it);
        
        if(!dict)
            break;
        const char* key = "x";
        int x = ((CCString*)dict->objectForKey(key))->intValue();
        key = "y";
        int y = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("y"))->getNumber();
        key = "width";
        int width = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("width"))->getNumber();
        key = "height";
        int height = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("height"))->getNumber();
        
        glLineWidth(3);
        
        ccDrawLine( ccp((float)x, (float)y), ccp((float)(x+width), (float)y) );
        ccDrawLine( ccp((float)(x+width), (float)y), ccp((float)(x+width), (float)(y+height)) );
        ccDrawLine( ccp((float)(x+width), (float)(y+height)), ccp((float)x, (float)(y+height)) );
        ccDrawLine( ccp((float)x, (float)(y+height)), ccp((float)x, (float)y) );
        
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
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/iso-test-objectgroup.tmx");
    addChild(map, -1, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    CCTMXObjectGroup* group = map->objectGroupNamed("Object Group 1");

    //UxMutableArray* objects = group->objects();
    CCArray* objects = group->getObjects();
    //UxMutableDictionary<std::string>* dict;
    CCDictionary* dict;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = (CCDictionary*)pObj;

        if(!dict)
            break;

        ////----CCLOG("object: %x", dict);
    }        
}

void TMXIsoObjectsTest::draw()
{
    CCTMXTiledMap *map = (CCTMXTiledMap*) getChildByTag(kTagTileMap);
    CCTMXObjectGroup *group = map->objectGroupNamed("Object Group 1");

    CCArray* objects = group->getObjects();
    CCDictionary* dict;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        dict = (CCDictionary*)pObj;//dynamic_cast<CCStringToStringDictionary*>(*it);

        if(!dict)
            break;
        const char* key = "x";
        int x = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("x"))->getNumber();
        key = "y";
        int y = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("y"))->getNumber();
        key = "width";
        int width = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("width"))->getNumber();
        key = "height";
        int height = ((CCString*)dict->objectForKey(key))->intValue();//dynamic_cast<NSNumber*>(dict->objectForKey("height"))->getNumber();
        
        glLineWidth(3);
        
        ccDrawLine( ccp(x,y), ccp(x+width,y) );
        ccDrawLine( ccp(x+width,y), ccp(x+width,y+height) );
        ccDrawLine( ccp(x+width,y+height), ccp(x,y+height) );
        ccDrawLine( ccp(x,y+height), ccp(x,y) );
        
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
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/orthogonal-test5.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);

    CCTMXLayer* layer;
    layer = map->layerNamed("Layer 0");

    CCSize ls = layer->getLayerSize();
    for (unsigned int y = 0; y < ls.height; y++) 
    {
        for (unsigned int x = 0; x < ls.width; x++) 
        {
            layer->setTileGID(1, ccp( x, y ) );
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/iso-test-zorder.tmx");
    addChild(map, 0, kTagTileMap);

    CCSize s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    map->setPosition(ccp(-s.width/2,0));
    
    m_tamara = CCSprite::create(s_pPathSister1);
    map->addChild(m_tamara, map->getChildren()->count() );
    m_tamara->retain();
    int mapWidth = map->getMapSize().width * map->getTileSize().width;
    m_tamara->setPosition(CC_POINT_PIXELS_TO_POINTS(ccp( mapWidth/2,0)));
    m_tamara->setAnchorPoint(ccp(0.5f,0));

    
    CCActionInterval* move = CCMoveBy::create(10, ccp(300,250));
    CCActionInterval* back = move->reverse();
    CCSequence* seq = CCSequence::create(move, back,NULL);
    m_tamara->runAction( CCRepeatForever::create(seq) );
    
    schedule( schedule_selector(TMXIsoZorder::repositionSprite) );
}

TMXIsoZorder::~TMXIsoZorder()
{
    m_tamara->release();
}

void TMXIsoZorder::onExit()
{
    unschedule(schedule_selector(TMXIsoZorder::repositionSprite));
    TileDemo::onExit();
}

void TMXIsoZorder::repositionSprite(float dt)
{
    CCPoint p = m_tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    CCNode *map = getChildByTag(kTagTileMap);
    
    // there are only 4 layers. (grass and 3 trees layers)
    // if tamara < 48, z=4
    // if tamara < 96, z=3
    // if tamara < 144,z=2
    
    int newZ = 4 - (p.y / 48);
    newZ = max(newZ,0);
    
    map->reorderChild(m_tamara, newZ);    
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test-zorder.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    m_tamara = CCSprite::create(s_pPathSister1);
    map->addChild(m_tamara,  map->getChildren()->count());
    m_tamara->retain();
    m_tamara->setAnchorPoint(ccp(0.5f,0));

    
    CCActionInterval* move = CCMoveBy::create(10, ccp(400,450));
    CCActionInterval* back = move->reverse();
    CCSequence* seq = CCSequence::create(move, back,NULL);
    m_tamara->runAction( CCRepeatForever::create(seq));
    
    schedule( schedule_selector(TMXOrthoZorder::repositionSprite));
}

TMXOrthoZorder::~TMXOrthoZorder()
{
    m_tamara->release();
}

void TMXOrthoZorder::repositionSprite(float dt)
{
    CCPoint p = m_tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    CCNode* map = getChildByTag(kTagTileMap);
    
    // there are only 4 layers. (grass and 3 trees layers)
    // if tamara < 81, z=4
    // if tamara < 162, z=3
    // if tamara < 243,z=2

    // -10: customization for this particular sample
    int newZ = 4 - ( (p.y-10) / 81);
    newZ = max(newZ,0);

    map->reorderChild(m_tamara, newZ);
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/iso-test-vertexz.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize s = map->getContentSize();
    map->setPosition( ccp(-s.width/2,0) );
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    // can use any CCSprite and it will work OK.
    CCTMXLayer* layer = map->layerNamed("Trees");
    m_tamara = layer->tileAt( ccp(29,29) );
    m_tamara->retain();
    
    CCActionInterval* move = CCMoveBy::create(10, ccpMult( ccp(300,250), 1/CC_CONTENT_SCALE_FACTOR() ) );
    CCActionInterval* back = move->reverse();
    CCSequence* seq = CCSequence::create(move, back,NULL);
    m_tamara->runAction( CCRepeatForever::create(seq) );
    
    schedule( schedule_selector(TMXIsoVertexZ::repositionSprite));
    
}

TMXIsoVertexZ::~TMXIsoVertexZ()
{
    m_tamara->release();
}

void TMXIsoVertexZ::repositionSprite(float dt)
{
    // tile height is 64x32
    // map size: 30x30
    CCPoint p = m_tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    float newZ = -(p.y+32) /16;
    m_tamara->setVertexZ( newZ );
}

void TMXIsoVertexZ::onEnter()
{
    TileDemo::onEnter();
    
    // TIP: 2d projection should be used
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
}

void TMXIsoVertexZ::onExit()
{
    // At exit use any other projection. 
    //    CCDirector::sharedDirector()->setProjection:kCCDirectorProjection3D);
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test-vertexz.tmx");
    addChild(map, 0, kTagTileMap);
    
    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s.width,s.height);
    
    // because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    // can use any CCSprite and it will work OK.
    CCTMXLayer* layer = map->layerNamed("trees");
    m_tamara = layer->tileAt(ccp(0,11));
    CCLOG("%p vertexZ: %f", m_tamara, m_tamara->getVertexZ());
    m_tamara->retain();

    CCActionInterval* move = CCMoveBy::create(10, ccpMult( ccp(400,450), 1/CC_CONTENT_SCALE_FACTOR()));
    CCActionInterval* back = move->reverse();
    CCSequence* seq = CCSequence::create(move, back,NULL);
    m_tamara->runAction( CCRepeatForever::create(seq));
    
    schedule(schedule_selector(TMXOrthoVertexZ::repositionSprite));
    
}

TMXOrthoVertexZ::~TMXOrthoVertexZ()
{
    m_tamara->release();
}

void TMXOrthoVertexZ::repositionSprite(float dt)
{
    // tile height is 101x81
    // map size: 12x12
    CCPoint p = m_tamara->getPosition();
    p = CC_POINT_POINTS_TO_PIXELS(p);
    m_tamara->setVertexZ( -( (p.y+81) /81) );
}

void TMXOrthoVertexZ::onEnter()
{
    TileDemo::onEnter();
    
    // TIP: 2d projection should be used
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
}

void TMXOrthoVertexZ::onExit()
{
    // At exit use any other projection. 
    //    CCDirector::sharedDirector()->setProjection:kCCDirectorProjection3D);
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
    CCTMXTiledMap* map = CCTMXTiledMap::create("TileMaps/iso-test-movelayer.tmx");
    addChild(map, 0, kTagTileMap);
    
    map->setPosition(ccp(-700,-50));

    CCSize CC_UNUSED s = map->getContentSize();
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test-movelayer.tmx");
    addChild(map, 0, kTagTileMap);

    CCSize CC_UNUSED s = map->getContentSize();
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/ortho-tile-property.tmx");
    addChild(map ,0 ,kTagTileMap);

    for(int i=1;i<=20;i++){
        CCLog("GID:%i, Properties:%p", i, map->propertiesForGID(i));
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/ortho-rotation-test.tmx");
    addChild(map, 0, kTagTileMap);

    CCSize CC_UNUSED s = map->getContentSize();
    CCLog("ContentSize: %f, %f", s.width,s.height);

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(map->getChildren(), pObj)
    {
        CCSpriteBatchNode* child = (CCSpriteBatchNode*)pObj;
        child->getTexture()->setAntiAliasTexParameters();
    }

    CCScaleBy* action = CCScaleBy::create(2, 0.5f);
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/ortho-rotation-test.tmx");
    addChild(map, 0, kTagTileMap);

    CCSize s = map->getContentSize();
    CCLog("ContentSize: %f, %f", s.width,s.height);

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(map->getChildren(), pObj)
    {
        CCSpriteBatchNode* child = (CCSpriteBatchNode*)pObj;
        child->getTexture()->setAntiAliasTexParameters();
    }

    CCScaleBy* action = CCScaleBy::create(2, 0.5f);
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
    CCTMXTiledMap *map = (CCTMXTiledMap*) getChildByTag(kTagTileMap); 
    CCTMXLayer *layer = map->layerNamed("Layer 0"); 

    //blue diamond 
    CCPoint tileCoord = ccp(1,10);
    int flags;
    unsigned int GID = layer->tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags);
    // Vertical
    if( flags & kCCTMXTileVerticalFlag )
        flags &= ~kCCTMXTileVerticalFlag;
    else
        flags |= kCCTMXTileVerticalFlag;
    layer->setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags);


    tileCoord = ccp(1,8);    
    GID = layer->tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags);
    // Vertical
    if( flags & kCCTMXTileVerticalFlag )
        flags &= ~kCCTMXTileVerticalFlag;
    else
        flags |= kCCTMXTileVerticalFlag;    
    layer->setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags);


    tileCoord = ccp(2,8);
    GID = layer->tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags);
    // Horizontal
    if( flags & kCCTMXTileHorizontalFlag )
        flags &= ~kCCTMXTileHorizontalFlag;
    else
        flags |= kCCTMXTileHorizontalFlag;    
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

    CCString* str = CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(file.c_str()).c_str());
    CCAssert(str != NULL, "Unable to open file");

    CCTMXTiledMap *map = CCTMXTiledMap::createWithXML(str->getCString() ,resources.c_str());
    addChild(map, 0, kTagTileMap);

    CCSize s = map->getContentSize();
    CCLog("ContentSize: %f, %f", s.width,s.height);

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(map->getChildren(), pObj)
    {
        CCSpriteBatchNode* child = (CCSpriteBatchNode*)pObj;
        child->getTexture()->setAntiAliasTexParameters();
    }

    CCScaleBy* action = CCScaleBy::create(2, 0.5f);
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test6.tmx");
    addChild(map, 0, kTagTileMap);

    CCSize CC_UNUSED s1 = map->getContentSize();
    CCLOG("ContentSize: %f, %f", s1.width,s1.height);

    CCArray* childs = map->getChildren();
    CCTMXLayer* pNode;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(childs, pObject)
    {
        pNode = (CCTMXLayer*) pObject;
        CC_BREAK_IF(!pNode);
        pNode->getTexture()->setAntiAliasTexParameters();
    }

    map->setAnchorPoint(ccp(0, 0));
    CCTMXLayer *layer = map->layerNamed("Tile Layer 1");
    layer->setTileGID(3, ccp(2,2));
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
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/iso-test-bug787.tmx");
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

CCLayer* createTileMapLayer(int nIndex)
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

CCLayer* nextTileMapAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createTileMapLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backTileMapAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createTileMapLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartTileMapAction()
{
    CCLayer* pLayer = createTileMapLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


TileDemo::TileDemo(void)
{
    setTouchEnabled( true );

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    m_label = CCLabelTTF::create("", "Arial", 28);
    addChild(m_label, 1);
    m_label->setPosition( ccp(s.width/2, s.height-50) );
    m_label->retain();

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(s.width/2, s.height-80) );

        m_subtitle = l;
        m_subtitle->retain();
    }    

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TileDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TileDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TileDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);    
}

TileDemo::~TileDemo(void)
{
    m_label->release();
    m_subtitle->release();
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
    CCLayer::onEnter();

    m_label->setString(title().c_str());
    m_subtitle->setString(subtitle().c_str());
}

void TileDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new TileMapTestScene();
    s->addChild(restartTileMapAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TileDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new TileMapTestScene();
    s->addChild( nextTileMapAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void TileDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new TileMapTestScene();
    s->addChild( backTileMapAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void TileDemo::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    
    CCPoint diff = touch->getDelta();
    CCNode *node = getChildByTag(kTagTileMap);
    CCPoint currentPos = node->getPosition();
    node->setPosition( ccpAdd(currentPos, diff) );
}

void TileMapTestScene::runThisTest()
{
    CCLayer* pLayer = nextTileMapAction();
    addChild(pLayer);

    // fix bug #486, #419. 
    // "test" is the default value in CCDirector::setGLDefaultValues()
    // but TransitionTest may setDepthTest(false), we should revert it here
    CCDirector::sharedDirector()->setDepthTest(true);
    
    CCDirector::sharedDirector()->replaceScene(this);
}

TMXGIDObjectsTest::TMXGIDObjectsTest()
{
    CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/test-object-layer.tmx");
    addChild(map, -1, kTagTileMap);

    CCSize CC_UNUSED s = map->getContentSize();
    CCLOG("Contentsize: %f, %f", s.width, s.height);

    CCLOG("----> Iterating over all the group objets");
    //CCTMXObjectGroup *group = map->objectGroupNamed("Object Layer 1");

}

void TMXGIDObjectsTest::draw()
{
    CCTMXTiledMap *map = (CCTMXTiledMap*)getChildByTag(kTagTileMap);
    CCTMXObjectGroup *group = map->objectGroupNamed("Object Layer 1");

    CCArray *array = group->getObjects();
    CCDictionary* dict;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(array, pObj)
    {
        dict = (CCDictionary*)pObj;
        if(!dict)
        {
            break;
        }

        const char* key = "x";
        int x = ((CCString*)dict->objectForKey(key))->intValue();
        key = "y";
        int y = ((CCString*)dict->objectForKey(key))->intValue();
        key = "width";
        int width = ((CCString*)dict->objectForKey(key))->intValue();
        key = "height";
        int height = ((CCString*)dict->objectForKey(key))->intValue();

        glLineWidth(3);

        ccDrawLine(ccp(x, y), ccp(x + width, y));
        ccDrawLine(ccp(x + width, y), ccp(x + width, y + height));
        ccDrawLine(ccp(x + width,y + height), ccp(x,y + height));
        ccDrawLine(ccp(x,y + height), ccp(x,y));

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
