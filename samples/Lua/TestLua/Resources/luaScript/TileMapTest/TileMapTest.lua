local kTagTileMap = 1

--------------------------------------------------------------------
--
-- TileMapTest
--
--------------------------------------------------------------------
TileMapTest:TileMapTest()

    local  map = CCTileMapAtlas:create(s_TilesPng,  s_LevelMapTga, 16, 16)
    -- Convert it to "alias" (GL_LINEAR filtering)
    map:getTexture():setAntiAliasTexParameters()
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)

    -- If you are not going to use the Map, you can free it now
    -- NEW since v0.7
    map:releaseMap()
    
    addChild(map, 0, kTagTileMap)
    
    map:setAnchorPoint( ccp(0, 0.5) )

    local scale = CCScaleBy:create(4, 0.8)
    local scaleBack = scale:reverse()

    local  seq = CCSequence:create(scale, scaleBack, NULL)

    map:runAction(CCRepeatForever:create(seq))
end

std:string TileMapTest:title()

    return "TileMapAtlas"
end

--------------------------------------------------------------------
--
-- TileMapEditTest
--
--------------------------------------------------------------------
TileMapEditTest:TileMapEditTest()

    local  map = CCTileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
    -- Create an Aliased Atlas
    map:getTexture():setAliasTexParameters()
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    -- If you are not going to use the Map, you can free it now
    -- [tilemap releaseMap)
    -- And if you are going to use, it you can access the data with:
    schedule(schedule_selector(TileMapEditTest:updateMap), 0.2)
    
    addChild(map, 0, kTagTileMap)
    
    map:setAnchorPoint( ccp(0, 0) )
    map:setPosition( ccp(-20,-200) )
end

void TileMapEditTest:updateMap(float dt)

    -- IMPORTANT
    --   The only limitation is that you cannot change an empty, or assign an empty tile to a tile
    --   The value 0 not rendered so don't assign or change a tile with value 0

    local  tilemap = tolua.cast(getChildByTag(kTagTileMap), "CCTileMapAtlas")
    
    --
    -- For example you can iterate over all the tiles
    -- using this code, but try to avoid the iteration
    -- over all your tiles in every frame. It's very expensive
    --    for(int x=0 x < tilemap.tgaInfo:width x++) 
    --        for(int y=0 y < tilemap.tgaInfo:height y++) 
    --            ccColor3B c =[tilemap tileAt:CCSizeMake(x,y))
    --            if( c.r != 0 ) 
    --                --------CCLOG("%d,%d = %d", x,y,c.r)
    --            end
    --        end
    --    end
    
    -- NEW since v0.7
    ccColor3B c = tilemap:tileAt(ccp(13,21))        
    c.r++
    c.r %= 50
    if( c.r==0)
        c.r=1
    
    -- NEW since v0.7
    tilemap:setTile(c, ccp(13,21) )             
end

std:string TileMapEditTest:title()

    return "Editable TileMapAtlas"
end

--------------------------------------------------------------------
--
-- TMXOrthoTest
--
--------------------------------------------------------------------
TMXOrthoTest:TMXOrthoTest()

    --
    -- Test orthogonal with 3d camera and anti-alias textures
    --
    -- it should not flicker. No artifacts should appear
    --
    --local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    --addChild(color, -1)

    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    local  pChildrenArray = map:getChildren()
    local  child = NULL
    local  pObject = NULL
    CCARRAY_FOREACH(pChildrenArray, pObject)
    
        child = (CCSpriteBatchNode*)pObject

        if(!child)
            break

        child:getTexture():setAntiAliasTexParameters()
    end

    float x, y, z
    map:getCamera():getEyeXYZ(&x, &y, &z)
    map:getCamera():setEyeXYZ(x-200, y, z+300)    
end

void TMXOrthoTest:onEnter()

    TileDemo:onEnter()

    CCDirector:sharedDirector():setProjection(kCCDirectorProjection3D)
end

void TMXOrthoTest:onExit()

    CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
    TileDemo:onExit()
end

std:string TMXOrthoTest:title()

    return "TMX Orthogonal test"
end

--------------------------------------------------------------------
--
-- TMXOrthoTest2
--
--------------------------------------------------------------------
TMXOrthoTest2:TMXOrthoTest2()

    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test1.tmx")
    addChild(map, 0, kTagTileMap)

    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)

    local  pChildrenArray = map:getChildren()
    local  child = NULL
    local  pObject = NULL
    CCARRAY_FOREACH(pChildrenArray, pObject)
    
        child = (CCSpriteBatchNode*)pObject

        if(!child)
            break

        child:getTexture():setAntiAliasTexParameters()
    end

    map:runAction( CCScaleBy:create(2, 0.5) ) 
end

std:string TMXOrthoTest2:title()

    return "TMX Ortho test2"
end

--------------------------------------------------------------------
--
-- TMXOrthoTest3
--
--------------------------------------------------------------------
TMXOrthoTest3:TMXOrthoTest3()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test3.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    local  pChildrenArray = map:getChildren()
    local  child = NULL
    local  pObject = NULL
    CCARRAY_FOREACH(pChildrenArray, pObject)
    
        child = (CCSpriteBatchNode*)pObject

        if(!child)
            break

        child:getTexture():setAntiAliasTexParameters()
    end
    
    map:setScale(0.2)
    map:setAnchorPoint( ccp(0.5, 0.5) )
end

std:string TMXOrthoTest3:title()

    return "TMX anchorPoint test"
end

--------------------------------------------------------------------
--
-- TMXOrthoTest4
--
--------------------------------------------------------------------
TMXOrthoTest4:TMXOrthoTest4()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test4.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s1 = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s1.width,s1.height)
    
    local  pChildrenArray = map:getChildren()
    local  child = NULL
    local  pObject = NULL
    CCARRAY_FOREACH(pChildrenArray, pObject)
    
        child = (CCSpriteBatchNode*)pObject

        if(!child)
            break

        child:getTexture():setAntiAliasTexParameters()
    end
    
    map:setAnchorPoint(ccp(0, 0))

    local  layer = map:layerNamed("Layer 0")
    CCSize s = layer:getLayerSize()
    
    CCSprite* sprite
    sprite = layer:tileAt(ccp(0,0))
    sprite:setScale(2)
    sprite = layer:tileAt(ccp(s.width-1,0))
    sprite:setScale(2)
    sprite = layer:tileAt(ccp(0,s.height-1))
    sprite:setScale(2)
    sprite = layer:tileAt(ccp(s.width-1,s.height-1))
    sprite:setScale(2)

    schedule( schedule_selector(TMXOrthoTest4:removeSprite), 2 )

end

void TMXOrthoTest4:removeSprite(float dt)

    unschedule(schedule_selector(TMXOrthoTest4:removeSprite))

    local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local  layer = map:layerNamed("Layer 0")
    CCSize s = layer:getLayerSize()

    local  sprite = layer:tileAt( ccp(s.width-1,0) )
    layer:removeChild(sprite, true)
end

std:string TMXOrthoTest4:title()

    return "TMX width/height test"
end

--------------------------------------------------------------------
--
-- TMXReadWriteTest
--
--------------------------------------------------------------------
enum

    SID_UPDATECOL = 100,
    SID_REPAINTWITHGID,
    SID_REMOVETILES
end

TMXReadWriteTest:TMXReadWriteTest()

    m_gid = 0
    
    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)

    
    local  layer = map:layerNamed("Layer 0")
    layer:getTexture():setAntiAliasTexParameters()

    map:setScale( 1 )

    local tile0 = layer:tileAt(ccp(1,63))
    local tile1 = layer:tileAt(ccp(2,63))
    local tile2 = layer:tileAt(ccp(3,62))--ccp(1,62))
    local tile3 = layer:tileAt(ccp(2,62))
    tile0:setAnchorPoint( ccp(0.5, 0.5) )
    tile1:setAnchorPoint( ccp(0.5, 0.5) )
    tile2:setAnchorPoint( ccp(0.5, 0.5) )
    tile3:setAnchorPoint( ccp(0.5, 0.5) )

    local  move = CCMoveBy:create(0.5, ccp(0,160))
    local  rotate = CCRotateBy:create(2, 360)
    local  scale = CCScaleBy:create(2, 5)
    local  opacity = CCFadeOut:create(2)
    local  fadein = CCFadeIn:create(2)
    local  scaleback = CCScaleTo:create(1, 1)
    local  finish = CCCallFuncN:create(this, callfuncN_selector(TMXReadWriteTest:removeSprite))
    local  seq0 = CCSequence:create(move, rotate, scale, opacity, fadein, scaleback, finish, NULL)
    local  seq1 = (CCActionInterval*)(seq0:copy():autorelease())
    local  seq2 = (CCActionInterval*)(seq0:copy():autorelease())
    local  seq3 = (CCActionInterval*)(seq0:copy():autorelease())
    
    tile0:runAction(seq0)
    tile1:runAction(seq1)
    tile2:runAction(seq2)
    tile3:runAction(seq3)
    
    
    m_gid = layer:tileGIDAt(ccp(0,63))
    --------CCLOG("Tile GID at:(0,63) is: %d", m_gid)

    schedule(schedule_selector(TMXReadWriteTest:updateCol), 2.0) 
    schedule(schedule_selector(TMXReadWriteTest:repaintWithGID), 2.05)
    schedule(schedule_selector(TMXReadWriteTest:removeTiles), 1.0) 

    --------CCLOG("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
    --------CCLOG("++++children: %d", layer:getChildren():count() )
    
    m_gid2 = 0
end

void TMXReadWriteTest:removeSprite(CCNode* sender)

    --------CCLOG("removing tile: %x", sender)
    local  p = ((CCNode*)sender):getParent()

    if (p)
    
        p:removeChild((CCNode*)sender, true)
    end    
    
    ----------CCLOG("atlas quantity: %d", p:textureAtlas():totalQuads())
end

void TMXReadWriteTest:updateCol(float dt)
    
    local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")

    --------CCLOG("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
    --------CCLOG("++++children: %d", layer:getChildren():count() )


    CCSize s = layer:getLayerSize()

    for( int y=0 y< s.height y++ ) 
    
        layer:setTileGID(m_gid2, ccp((float)3, (float)y))
    end
    
    m_gid2 = (m_gid2 + 1) % 80
end

void TMXReadWriteTest:repaintWithGID(float dt)

--    unschedule:_cmd)
    
    local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")
    
    CCSize s = layer:getLayerSize()
    for( int x=0 x<s.widthx++) 
    
        int y = (int)s.height-1
        unsigned int tmpgid = layer:tileGIDAt( ccp((float)x, (float)y) )
        layer:setTileGID(tmpgid+1, ccp((float)x, (float)y))
    end
end

void TMXReadWriteTest:removeTiles(float dt)

    unschedule(schedule_selector(TMXReadWriteTest:removeTiles))

    local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")
    CCSize s = layer:getLayerSize()

    for( int y=0 y< s.height y++ ) 
    
        layer:removeTileAt( ccp(5.0, (float)y) )
    end
end



std:string TMXReadWriteTest:title()

    return "TMX Read/Write test"
end

--------------------------------------------------------------------
--
-- TMXHexTest
--
--------------------------------------------------------------------
TMXHexTest:TMXHexTest()

    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    addChild(color, -1)
    
    local  map = CCTMXTiledMap:create("TileMaps/hexa-test.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
end

std:string TMXHexTest:title()

    return "TMX Hex tes"
end

--------------------------------------------------------------------
--
-- TMXIsoTest
--
--------------------------------------------------------------------
TMXIsoTest:TMXIsoTest()

    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    addChild(color, -1)
    
    local  map = CCTMXTiledMap:create("TileMaps/iso-test.tmx")
    addChild(map, 0, kTagTileMap)        
    
    -- move map to the center of the screen
    CCSize ms = map:getMapSize()
    CCSize ts = map:getTileSize()
    map:runAction( CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 )) ) 
end

std:string TMXIsoTest:title()

    return "TMX Isometric test 0"
end

--------------------------------------------------------------------
--
-- TMXIsoTest1
--
--------------------------------------------------------------------
TMXIsoTest1:TMXIsoTest1()

    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    addChild(color, -1)
    
    local map = CCTMXTiledMap:create("TileMaps/iso-test1.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    map:setAnchorPoint(ccp(0.5, 0.5))
end

std:string TMXIsoTest1:title()

    return "TMX Isometric test + anchorPoint"
end

--------------------------------------------------------------------
--
-- TMXIsoTest2
--
--------------------------------------------------------------------
TMXIsoTest2:TMXIsoTest2()

    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    addChild(color, -1)
    
    local map = CCTMXTiledMap:create("TileMaps/iso-test2.tmx")
    addChild(map, 0, kTagTileMap)    
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    -- move map to the center of the screen
    CCSize ms = map:getMapSize()
    CCSize ts = map:getTileSize()
    map:runAction( CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))
end

std:string TMXIsoTest2:title()

    return "TMX Isometric test 2"
end

--------------------------------------------------------------------
--
-- TMXUncompressedTest
--
--------------------------------------------------------------------
TMXUncompressedTest:TMXUncompressedTest()

    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    addChild(color, -1)
    
    local map = CCTMXTiledMap:create("TileMaps/iso-test2-uncompressed.tmx")
    addChild(map, 0, kTagTileMap)    
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    -- move map to the center of the screen
    CCSize ms = map:getMapSize()
    CCSize ts = map:getTileSize()
    map:runAction(CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))
    
    -- testing release map
    local  pChildrenArray = map:getChildren()
    CCTMXLayer* layer
    local  pObject = NULL
    CCARRAY_FOREACH(pChildrenArray, pObject)
    
        layer= (CCTMXLayer*)pObject

        if(!layer)
            break

        layer:releaseMap()
    end

end

std:string TMXUncompressedTest:title()

    return "TMX Uncompressed test"
end

--------------------------------------------------------------------
--
-- TMXTilesetTest
--
--------------------------------------------------------------------
TMXTilesetTest:TMXTilesetTest()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    CCTMXLayer* layer
    layer = map:layerNamed("Layer 0")
    layer:getTexture():setAntiAliasTexParameters()
    
    layer = map:layerNamed("Layer 1")
    layer:getTexture():setAntiAliasTexParameters()

    layer = map:layerNamed("Layer 2")
    layer:getTexture():setAntiAliasTexParameters()
end

std:string TMXTilesetTest:title()

    return "TMX Tileset test"
end

--------------------------------------------------------------------
--
-- TMXOrthoObjectsTest
--
--------------------------------------------------------------------
TMXOrthoObjectsTest:TMXOrthoObjectsTest()

    local map = CCTMXTiledMap:create("TileMaps/ortho-objects.tmx")
    addChild(map, -1, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    --------CCLOG("---: Iterating over all the group objets")
    local  group = map:objectGroupNamed("Object Group 1")
    local  objects = group:getObjects()

    local  dict = NULL
    local  pObj = NULL
    CCARRAY_FOREACH(objects, pObj)
    
        dict = (CCDictionary*)pObj--dynamic_cast<CCStringToStringDictionary*>(*it)

        if(!dict)
            break

        --------CCLOG("object: %x", dict)
    end
    
    --------CCLOG("---: Fetching 1 object by name")
    -- local  platform = group:objectNamed("platform")
    --------CCLOG("platform: %x", platform)
end

void TMXOrthoObjectsTest:draw()

    local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local  group = map:objectGroupNamed("Object Group 1")

    local  objects = group:getObjects()
    local  dict = NULL
    local  pObj = NULL
    CCARRAY_FOREACH(objects, pObj)
    
        dict = (CCDictionary*)pObj--dynamic_cast<CCStringToStringDictionary*>(*it)
        
        if(!dict)
            break
        const char* key = "x"
        int x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
        key = "y"
        int y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
        key = "width"
        int width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
        key = "height"
        int height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()
        
        glLineWidth(3)
        
        ccDrawLine( ccp((float)x, (float)y), ccp((float)(x+width), (float)y) )
        ccDrawLine( ccp((float)(x+width), (float)y), ccp((float)(x+width), (float)(y+height)) )
        ccDrawLine( ccp((float)(x+width), (float)(y+height)), ccp((float)x, (float)(y+height)) )
        ccDrawLine( ccp((float)x, (float)(y+height)), ccp((float)x, (float)y) )
        
        glLineWidth(1)
    end
end

std:string TMXOrthoObjectsTest:title()

    return "TMX Ortho object test"
end

std:string TMXOrthoObjectsTest:subtitle()

    return "You should see a white box around the 3 platforms"
end


--------------------------------------------------------------------
--
-- TMXIsoObjectsTest
--
--------------------------------------------------------------------

TMXIsoObjectsTest:TMXIsoObjectsTest()

    local  map = CCTMXTiledMap:create("TileMaps/iso-test-objectgroup.tmx")
    addChild(map, -1, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)

    local  group = map:objectGroupNamed("Object Group 1")

    --UxMutableArray* objects = group:objects()
    local  objects = group:getObjects()
    --UxMutableDictionary<std:string>* dict
    CCDictionary* dict
    local  pObj = NULL
    CCARRAY_FOREACH(objects, pObj)
    
        dict = (CCDictionary*)pObj

        if(!dict)
            break

        --------CCLOG("object: %x", dict)
    end        
end

void TMXIsoObjectsTest:draw()

    local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local group = map:objectGroupNamed("Object Group 1")

    local  objects = group:getObjects()
    CCDictionary* dict
    local  pObj = NULL
    CCARRAY_FOREACH(objects, pObj)
    
        dict = (CCDictionary*)pObj--dynamic_cast<CCStringToStringDictionary*>(*it)

        if(!dict)
            break
        const char* key = "x"
        int x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("x")):getNumber()
        key = "y"
        int y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
        key = "width"
        int width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
        key = "height"
        int height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()
        
        glLineWidth(3)
        
        ccDrawLine( ccp(x,y), ccp(x+width,y) )
        ccDrawLine( ccp(x+width,y), ccp(x+width,y+height) )
        ccDrawLine( ccp(x+width,y+height), ccp(x,y+height) )
        ccDrawLine( ccp(x,y+height), ccp(x,y) )
        
        glLineWidth(1)
    end
end

std:string TMXIsoObjectsTest:title()

    return "TMX Iso object test"
end

std:string TMXIsoObjectsTest:subtitle()

    return "You need to parse them manually. See bug #810"
end


--------------------------------------------------------------------
--
-- TMXResizeTest
--
--------------------------------------------------------------------

TMXResizeTest:TMXResizeTest()

    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)

    CCTMXLayer* layer
    layer = map:layerNamed("Layer 0")

    CCSize ls = layer:getLayerSize()
    for (unsigned int y = 0 y < ls.height y++) 
    
        for (unsigned int x = 0 x < ls.width x++) 
        
            layer:setTileGID(1, ccp( x, y ) )
        end
    end        
end

std:string TMXResizeTest:title()

    return "TMX resize test"
end

std:string TMXResizeTest:subtitle()

    return "Should not crash. Testing issue #740"
end


--------------------------------------------------------------------
--
-- TMXIsoZorder
--
--------------------------------------------------------------------
TMXIsoZorder:TMXIsoZorder()

    local map = CCTMXTiledMap:create("TileMaps/iso-test-zorder.tmx")
    addChild(map, 0, kTagTileMap)

    CCSize s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    map:setPosition(ccp(-s.width/2,0))
    
    m_tamara = CCSprite:create(s_pPathSister1)
    map:addChild(m_tamara, map:getChildren():count() )
    m_tamara:retain()
    int mapWidth = map:getMapSize().width * map:getTileSize().width
    m_tamara:setPosition(CC_POINT_PIXELS_TO_POINTS(ccp( mapWidth/2,0)))
    m_tamara:setAnchorPoint(ccp(0.5,0))

    
    local  move = CCMoveBy:create(10, ccp(300,250))
    local  back = move:reverse()
    local  seq = CCSequence:create(move, back,NULL)
    m_tamara:runAction( CCRepeatForever:create(seq) )
    
    schedule( schedule_selector(TMXIsoZorder:repositionSprite) )
end

TMXIsoZorder:~TMXIsoZorder()

    m_tamara:release()
end

void TMXIsoZorder:onExit()

    unschedule(schedule_selector(TMXIsoZorder:repositionSprite))
    TileDemo:onExit()
end

void TMXIsoZorder:repositionSprite(float dt)

    CCPoint p = m_tamara:getPosition()
    p = CC_POINT_POINTS_TO_PIXELS(p)
    local map = getChildByTag(kTagTileMap)
    
    -- there are only 4 layers. (grass and 3 trees layers)
    -- if tamara < 48, z=4
    -- if tamara < 96, z=3
    -- if tamara < 144,z=2
    
    int newZ = 4 - (p.y / 48)
    newZ = max(newZ,0)
    
    map:reorderChild(m_tamara, newZ)    
end

std:string TMXIsoZorder:title()

    return "TMX Iso Zorder"
end

std:string TMXIsoZorder:subtitle()

    return "Sprite should hide behind the trees"
end


--------------------------------------------------------------------
--
-- TMXOrthoZorder
--
--------------------------------------------------------------------
TMXOrthoZorder:TMXOrthoZorder()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-zorder.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    m_tamara = CCSprite:create(s_pPathSister1)
    map:addChild(m_tamara,  map:getChildren():count())
    m_tamara:retain()
    m_tamara:setAnchorPoint(ccp(0.5,0))

    
    local  move = CCMoveBy:create(10, ccp(400,450))
    local  back = move:reverse()
    local  seq = CCSequence:create(move, back,NULL)
    m_tamara:runAction( CCRepeatForever:create(seq))
    
    schedule( schedule_selector(TMXOrthoZorder:repositionSprite))
end

TMXOrthoZorder:~TMXOrthoZorder()

    m_tamara:release()
end

void TMXOrthoZorder:repositionSprite(float dt)

    CCPoint p = m_tamara:getPosition()
    p = CC_POINT_POINTS_TO_PIXELS(p)
    local  map = getChildByTag(kTagTileMap)
    
    -- there are only 4 layers. (grass and 3 trees layers)
    -- if tamara < 81, z=4
    -- if tamara < 162, z=3
    -- if tamara < 243,z=2

    -- -10: customization for this particular sample
    int newZ = 4 - ( (p.y-10) / 81)
    newZ = max(newZ,0)

    map:reorderChild(m_tamara, newZ)
end

std:string TMXOrthoZorder:title()

    return "TMX Ortho Zorder"
end

std:string TMXOrthoZorder:subtitle()

    return "Sprite should hide behind the trees"
end


--------------------------------------------------------------------
--
-- TMXIsoVertexZ
--
--------------------------------------------------------------------
TMXIsoVertexZ:TMXIsoVertexZ()

    local map = CCTMXTiledMap:create("TileMaps/iso-test-vertexz.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize s = map:getContentSize()
    map:setPosition( ccp(-s.width/2,0) )
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    -- can use any CCSprite and it will work OK.
    local  layer = map:layerNamed("Trees")
    m_tamara = layer:tileAt( ccp(29,29) )
    m_tamara:retain()
    
    local  move = CCMoveBy:create(10, ccpMult( ccp(300,250), 1/CC_CONTENT_SCALE_FACTOR() ) )
    local  back = move:reverse()
    local  seq = CCSequence:create(move, back,NULL)
    m_tamara:runAction( CCRepeatForever:create(seq) )
    
    schedule( schedule_selector(TMXIsoVertexZ:repositionSprite))
    
end

TMXIsoVertexZ:~TMXIsoVertexZ()

    m_tamara:release()
end

void TMXIsoVertexZ:repositionSprite(float dt)

    -- tile height is 64x32
    -- map size: 30x30
    CCPoint p = m_tamara:getPosition()
    p = CC_POINT_POINTS_TO_PIXELS(p)
    float newZ = -(p.y+32) /16
    m_tamara:setVertexZ( newZ )
end

void TMXIsoVertexZ:onEnter()

    TileDemo:onEnter()
    
    -- TIP: 2d projection should be used
    CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
end

void TMXIsoVertexZ:onExit()

    -- At exit use any other projection. 
    --    CCDirector:sharedDirector():setProjection:kCCDirectorProjection3D)
    TileDemo:onExit()
end

std:string TMXIsoVertexZ:title()

    return "TMX Iso VertexZ"
end

std:string TMXIsoVertexZ:subtitle()

    return "Sprite should hide behind the trees"
end


--------------------------------------------------------------------
--
-- TMXOrthoVertexZ
--
--------------------------------------------------------------------
TMXOrthoVertexZ:TMXOrthoVertexZ()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-vertexz.tmx")
    addChild(map, 0, kTagTileMap)
    
    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
    
    -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    -- can use any CCSprite and it will work OK.
    local  layer = map:layerNamed("trees")
    m_tamara = layer:tileAt(ccp(0,11))
    CCLOG("%p vertexZ: %f", m_tamara, m_tamara:getVertexZ())
    m_tamara:retain()

    local  move = CCMoveBy:create(10, ccpMult( ccp(400,450), 1/CC_CONTENT_SCALE_FACTOR()))
    local  back = move:reverse()
    local  seq = CCSequence:create(move, back,NULL)
    m_tamara:runAction( CCRepeatForever:create(seq))
    
    schedule(schedule_selector(TMXOrthoVertexZ:repositionSprite))
    
end

TMXOrthoVertexZ:~TMXOrthoVertexZ()

    m_tamara:release()
end

void TMXOrthoVertexZ:repositionSprite(float dt)

    -- tile height is 101x81
    -- map size: 12x12
    CCPoint p = m_tamara:getPosition()
    p = CC_POINT_POINTS_TO_PIXELS(p)
    m_tamara:setVertexZ( -( (p.y+81) /81) )
end

void TMXOrthoVertexZ:onEnter()

    TileDemo:onEnter()
    
    -- TIP: 2d projection should be used
    CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
end

void TMXOrthoVertexZ:onExit()

    -- At exit use any other projection. 
    --    CCDirector:sharedDirector():setProjection:kCCDirectorProjection3D)
    TileDemo:onExit()
end

std:string TMXOrthoVertexZ:title()

    return "TMX Ortho vertexZ"
end

std:string TMXOrthoVertexZ:subtitle()

    return "Sprite should hide behind the trees"
end


--------------------------------------------------------------------
--
-- TMXIsoMoveLayer
--
--------------------------------------------------------------------
TMXIsoMoveLayer:TMXIsoMoveLayer()

    local  map = CCTMXTiledMap:create("TileMaps/iso-test-movelayer.tmx")
    addChild(map, 0, kTagTileMap)
    
    map:setPosition(ccp(-700,-50))

    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
end

std:string TMXIsoMoveLayer:title()

    return "TMX Iso Move Layer"
end

std:string TMXIsoMoveLayer:subtitle()

    return "Trees should be horizontally aligned"
end


--------------------------------------------------------------------
--
-- TMXOrthoMoveLayer
--
--------------------------------------------------------------------
TMXOrthoMoveLayer:TMXOrthoMoveLayer()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-movelayer.tmx")
    addChild(map, 0, kTagTileMap)

    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s.width,s.height)
end

std:string TMXOrthoMoveLayer:title()

    return "TMX Ortho Move Layer"
end

std:string TMXOrthoMoveLayer:subtitle()

    return "Trees should be horizontally aligned"
end

--------------------------------------------------------------------
--
-- TMXTilePropertyTest
--
--------------------------------------------------------------------

TMXTilePropertyTest:TMXTilePropertyTest()

    local map = CCTMXTiledMap:create("TileMaps/ortho-tile-property.tmx")
    addChild(map ,0 ,kTagTileMap)

    for(int i=1i<=20i++)
        CCLog("GID:%i, Properties:%p", i, map:propertiesForGID(i))
    end
end

std:string TMXTilePropertyTest:title()

    return "TMX Tile Property Test"
end

std:string TMXTilePropertyTest:subtitle()

    return "In the console you should see tile properties"
end

--------------------------------------------------------------------
--
-- TMXOrthoFlipTest
--
--------------------------------------------------------------------

TMXOrthoFlipTest:TMXOrthoFlipTest()

    local map = CCTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
    addChild(map, 0, kTagTileMap)

    CCSize CC_UNUSED s = map:getContentSize()
    CCLog("ContentSize: %f, %f", s.width,s.height)

    local  pObj = NULL
    CCARRAY_FOREACH(map:getChildren(), pObj)
    
        local  child = (CCSpriteBatchNode*)pObj
        child:getTexture():setAntiAliasTexParameters()
    end

    local  action = CCScaleBy:create(2, 0.5)
    map:runAction(action)
end

std:string TMXOrthoFlipTest:title()

    return "TMX tile flip test"
end

--------------------------------------------------------------------
--
-- TMXOrthoFlipRunTimeTest
--
--------------------------------------------------------------------

TMXOrthoFlipRunTimeTest:TMXOrthoFlipRunTimeTest()

    local map = CCTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
    addChild(map, 0, kTagTileMap)

    CCSize s = map:getContentSize()
    CCLog("ContentSize: %f, %f", s.width,s.height)

    local  pObj = NULL
    CCARRAY_FOREACH(map:getChildren(), pObj)
    
        local  child = (CCSpriteBatchNode*)pObj
        child:getTexture():setAntiAliasTexParameters()
    end

    local  action = CCScaleBy:create(2, 0.5)
    map:runAction(action)

    schedule(schedule_selector(TMXOrthoFlipRunTimeTest:flipIt), 1.0)
end

std:string TMXOrthoFlipRunTimeTest:title()

    return "TMX tile flip run time test"
end

std:string TMXOrthoFlipRunTimeTest:subtitle()

    return "in 2 sec bottom left tiles will flip"
end

void TMXOrthoFlipRunTimeTest:flipIt(float dt)

    local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap") 
    local layer = map:layerNamed("Layer 0") 

    --blue diamond 
    CCPoint tileCoord = ccp(1,10)
    int flags
    unsigned int GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
    -- Vertical
    if( flags & kCCTMXTileVerticalFlag )
        flags &= ~kCCTMXTileVerticalFlag
    else
        flags |= kCCTMXTileVerticalFlag
    layer:setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags)


    tileCoord = ccp(1,8)    
    GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
    -- Vertical
    if( flags & kCCTMXTileVerticalFlag )
        flags &= ~kCCTMXTileVerticalFlag
    else
        flags |= kCCTMXTileVerticalFlag    
    layer:setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags)


    tileCoord = ccp(2,8)
    GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
    -- Horizontal
    if( flags & kCCTMXTileHorizontalFlag )
        flags &= ~kCCTMXTileHorizontalFlag
    else
        flags |= kCCTMXTileHorizontalFlag    
    layer:setTileGID(GID, tileCoord, (ccTMXTileFlags)flags)    
end
--------------------------------------------------------------------
--
-- TMXOrthoFromXMLTest
--
--------------------------------------------------------------------

TMXOrthoFromXMLTest:TMXOrthoFromXMLTest()

    string resources = "TileMaps"        -- partial paths are OK as resource paths.
    string file = resources + "/orthogonal-test1.tmx"

    local  str = CCString:createWithContentsOfFile(CCFileUtils:sharedFileUtils():fullPathForFilename(file.c_str()).c_str())
    CCAssert(str != NULL, "Unable to open file")

    local map = CCTMXTiledMap:createWithXML(str:getCString() ,resources.c_str())
    addChild(map, 0, kTagTileMap)

    CCSize s = map:getContentSize()
    CCLog("ContentSize: %f, %f", s.width,s.height)

    local  pObj = NULL
    CCARRAY_FOREACH(map:getChildren(), pObj)
    
        local  child = (CCSpriteBatchNode*)pObj
        child:getTexture():setAntiAliasTexParameters()
    end

    local  action = CCScaleBy:create(2, 0.5)
    map:runAction(action)
end

std:string TMXOrthoFromXMLTest:title()

    return "TMX created from XML test"
end

--------------------------------------------------------------------
--
-- TMXBug987
--
--------------------------------------------------------------------
TMXBug987:TMXBug987()

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test6.tmx")
    addChild(map, 0, kTagTileMap)

    CCSize CC_UNUSED s1 = map:getContentSize()
    CCLOG("ContentSize: %f, %f", s1.width,s1.height)

    local  childs = map:getChildren()
    CCTMXLayer* pNode
    local  pObject = NULL
    CCARRAY_FOREACH(childs, pObject)
    
        pNode = (CCTMXLayer*) pObject
        CC_BREAK_IF(!pNode)
        pNode:getTexture():setAntiAliasTexParameters()
    end

    map:setAnchorPoint(ccp(0, 0))
    local layer = map:layerNamed("Tile Layer 1")
    layer:setTileGID(3, ccp(2,2))
end

std:string TMXBug987:title()

    return "TMX Bug 987"
end

std:string TMXBug987:subtitle()

    return "You should see an square"
end

--------------------------------------------------------------------
--
-- TMXBug787
--
--------------------------------------------------------------------
TMXBug787:TMXBug787()

    local map = CCTMXTiledMap:create("TileMaps/iso-test-bug787.tmx")
    addChild(map, 0, kTagTileMap)

    map:setScale(0.25)
end

std:string TMXBug787:title()

    return "TMX Bug 787"
end

std:string TMXBug787:subtitle()

    return "You should see a map"
end

--------------------------------------------------------------------
--
-- TileDemo
--
--------------------------------------------------------------------

enum

    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
end

static int sceneIdx = -1 

#define MAX_LAYER    28

CCLayer* createTileMapLayer(int nIndex)

    switch(nIndex)
    
        case 0: return new TMXIsoZorder()
        case 1: return new TMXOrthoZorder()
        case 2: return new TMXIsoVertexZ()
        case 3: return new TMXOrthoVertexZ()    
        case 4: return new TMXOrthoTest()
        case 5: return new TMXOrthoTest2()
        case 6: return new TMXOrthoTest3()
        case 7: return new TMXOrthoTest4()
        case 8: return new TMXIsoTest()
        case 9: return new TMXIsoTest1()
        case 10: return new TMXIsoTest2()
        case 11: return new TMXUncompressedTest ()
        case 12: return new TMXHexTest()
        case 13: return new TMXReadWriteTest()
        case 14: return new TMXTilesetTest()
        case 15: return new TMXOrthoObjectsTest()
        case 16: return new TMXIsoObjectsTest()
        case 17: return new TMXResizeTest()
        case 18: return new TMXIsoMoveLayer()
        case 19: return new TMXOrthoMoveLayer()
        case 20: return new TMXOrthoFlipTest()
        case 21: return new TMXOrthoFlipRunTimeTest()
        case 22: return new TMXOrthoFromXMLTest()
        case 23: return new TileMapTest()
        case 24: return new TileMapEditTest()
        case 25: return new TMXBug987()
        case 26: return new TMXBug787()
        case 27: return new TMXGIDObjectsTest()
    end

    return NULL
end

CCLayer* nextTileMapAction()

    sceneIdx++
    sceneIdx = sceneIdx % MAX_LAYER

    local  pLayer = createTileMapLayer(sceneIdx)
    pLayer:autorelease()

    return pLayer
end

CCLayer* backTileMapAction()

    sceneIdx--
    int total = MAX_LAYER
    if( sceneIdx < 0 )
        sceneIdx += total    
    
    local  pLayer = createTileMapLayer(sceneIdx)
    pLayer:autorelease()

    return pLayer
end

CCLayer* restartTileMapAction()

    local  pLayer = createTileMapLayer(sceneIdx)
    pLayer:autorelease()

    return pLayer
end 


TileDemo:TileDemo(void)

    setTouchEnabled( true )

    CCSize s = CCDirector:sharedDirector():getWinSize()

    m_label = CCLabelTTF:create("", "Arial", 28)
    addChild(m_label, 1)
    m_label:setPosition( ccp(s.width/2, s.height-50) )
    m_label:retain()

    std:string strSubtitle = subtitle()
    if( ! strSubtitle.empty() ) 
    
        local  l = CCLabelTTF:create(strSubtitle.c_str(), "Thonburi", 16)
        addChild(l, 1)
        l:setPosition( ccp(s.width/2, s.height-80) )

        m_subtitle = l
        m_subtitle:retain()
    end    

    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2, this, menu_selector(TileDemo:backCallback) )
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2, this, menu_selector(TileDemo:restartCallback) )
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2, this, menu_selector(TileDemo:nextCallback) )

    local menu = CCMenu:create(item1, item2, item3, NULL)

    menu:setPosition( CCPointZero )
    item1:setPosition(ccp(VisibleRect:center().x - item2:getContentSize().width*2, VisibleRect:bottom().y+item2:getContentSize().height/2))
    item2:setPosition(ccp(VisibleRect:center().x, VisibleRect:bottom().y+item2:getContentSize().height/2))
    item3:setPosition(ccp(VisibleRect:center().x + item2:getContentSize().width*2, VisibleRect:bottom().y+item2:getContentSize().height/2))
    
    addChild(menu, 1)    
end

TileDemo:~TileDemo(void)

    m_label:release()
    m_subtitle:release()
end

std:string TileDemo:title()

    return "No title"
end

std:string TileDemo:subtitle()

    return "drag the screen"
end

void TileDemo:onEnter()

    CCLayer:onEnter()

    m_label:setString(title().c_str())
    m_subtitle:setString(subtitle().c_str())
end

void TileDemo:restartCallback(CCObject* pSender)

    local  s = new TileMapTestScene()
    s:addChild(restartTileMapAction()) 

    CCDirector:sharedDirector():replaceScene(s)
    s:release()
end

void TileDemo:nextCallback(CCObject* pSender)

    local  s = new TileMapTestScene()
    s:addChild( nextTileMapAction() )
    CCDirector:sharedDirector():replaceScene(s)
    s:release()
end

void TileDemo:backCallback(CCObject* pSender)

    local  s = new TileMapTestScene()
    s:addChild( backTileMapAction() )
    CCDirector:sharedDirector():replaceScene(s)
    s:release()
end 

void TileDemo:ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)

    local touch = tolua.cast(pTouches:anyObject(), "CCTouch")
    
    CCPoint diff = touch:getDelta()
    local node = getChildByTag(kTagTileMap)
    CCPoint currentPos = node:getPosition()
    node:setPosition( ccpAdd(currentPos, diff) )
end

void TileMapTestScene:runThisTest()

    local  pLayer = nextTileMapAction()
    addChild(pLayer)

    -- fix bug #486, #419. 
    -- "test" is the default value in CCDirector:setGLDefaultValues()
    -- but TransitionTest may setDepthTest(false), we should revert it here
    CCDirector:sharedDirector():setDepthTest(true)
    
    CCDirector:sharedDirector():replaceScene(this)
end

TMXGIDObjectsTest:TMXGIDObjectsTest()

    local map = CCTMXTiledMap:create("TileMaps/test-object-layer.tmx")
    addChild(map, -1, kTagTileMap)

    CCSize CC_UNUSED s = map:getContentSize()
    CCLOG("Contentsize: %f, %f", s.width, s.height)

    CCLOG("---: Iterating over all the group objets")
    --local group = map:objectGroupNamed("Object Layer 1")

end

void TMXGIDObjectsTest:draw()

    local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local group = map:objectGroupNamed("Object Layer 1")

    local array = group:getObjects()
    CCDictionary* dict
    local  pObj = NULL
    CCARRAY_FOREACH(array, pObj)
    
        dict = (CCDictionary*)pObj
        if(!dict)
        
            break
        end

        const char* key = "x"
        int x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
        key = "y"
        int y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
        key = "width"
        int width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
        key = "height"
        int height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()

        glLineWidth(3)

        ccDrawLine(ccp(x, y), ccp(x + width, y))
        ccDrawLine(ccp(x + width, y), ccp(x + width, y + height))
        ccDrawLine(ccp(x + width,y + height), ccp(x,y + height))
        ccDrawLine(ccp(x,y + height), ccp(x,y))

        glLineWidth(1)
    end
end

string TMXGIDObjectsTest:title()

    return "TMX GID objects"
end

string TMXGIDObjectsTest:subtitle()

    return "Tiles are created from an object group"
end
