local size = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()

local kTagTileMap = 1


void TileDemo::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    
    CCPoint diff = touch->getDelta();
    CCNode *node = getChildByTag(kTagTileMap);
    CCPoint currentPos = node->getPosition();
    node->setPosition( ccpAdd(currentPos, diff) );
}

--------------------------------------------------------------------
--
-- TileMapTest
--
--------------------------------------------------------------------
local function TileMapTest()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("TileMapAtlas")
    Helper.subtitleLabel:setString("")

    local  map = CCTileMapAtlas:create(s_TilesPng,  s_LevelMapTga, 16, 16)
    -- Convert it to "alias" (GL_LINEAR filtering)
    map:getTexture():setAntiAliasTexParameters()
    
    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- If you are not going to use the Map, you can free it now
    -- NEW since v0.7
    map:releaseMap()
    
    layer:addChild(map, 0, kTagTileMap)
    
    map:setAnchorPoint( ccp(0, 0.5) )

    local scale = CCScaleBy:create(4, 0.8)
    local scaleBack = scale:reverse()
    local action_arr = CCArray:create()
    action_arr:addObject(scale)
    action_arr:addObject(scaleBack)

    local  seq = CCSequence:create(action_arr)

    map:runAction(CCRepeatForever:create(seq))

    return layer
end

--------------------------------------------------------------------
--
-- TileMapEditTest
--
--------------------------------------------------------------------
local function TileMapEditTest()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Editable TileMapAtlas")
    Helper.subtitleLabel:setString("")

    local  map = CCTileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
    -- Create an Aliased Atlas
    map:getTexture():setAliasTexParameters()
    
    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    
    -- If you are not going to use the Map, you can free it now
    -- [tilemap releaseMap)
    -- And if you are going to use, it you can access the data with:
    local function updateMap(dt)

        -- IMPORTANT
        --   The only limitation is that you cannot change an empty, or assign an empty tile to a tile
        --   The value 0 not rendered so don't assign or change a tile with value 0

        local  tilemap = tolua.cast(layer:getChildByTag(kTagTileMap), "CCTileMapAtlas")
        
        --
        -- For example you can iterate over all the tiles
        -- using this code, but try to avoid the iteration
        -- over all your tiles in every frame. It's very expensive
        --    for(int x=0 x < tilemap.tgaInfo:width x++) 
        --        for(int y=0 y < tilemap.tgaInfo:height y++) 
        --            ccColor3B c =[tilemap tileAt:local Make(x,y))
        --            if( c.r != 0 ) 
        --                --------cclog("%d,%d = %d", x,y,c.r)
        --            end
        --        end
        --    end
        
        -- NEW since v0.7
        local c = tilemap:tileAt(ccp(13,21))        
        c.r = c.r + 1
        c.r = c.r % 50

        if( c.r==0) then
            c.r=1
        end
        -- NEW since v0.7
        tilemap:setTile(c, ccp(13,21) )             
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(updateMap, 0.2, false)
        elseif event == "exit" then
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    layer:registerScriptHandler(onNodeEvent)
    
    layer:addChild(map, 0, kTagTileMap)
    
    map:setAnchorPoint( ccp(0, 0) )
    map:setPosition( ccp(-20,-200) )

    return layer
end


--------------------------------------------------------------------
--
-- TMXOrthoTest
--
--------------------------------------------------------------------
local function TMXOrthoTest()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("TMX Orthogonal test")
    Helper.subtitleLabel:setString("")

    --
    -- Test orthogonal with 3d camera and anti-alias textures
    --
    -- it should not flicker. No artifacts should appear
    --
    --local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    --addChild(color, -1)

    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
    layer:addChild(map, 0, kTagTileMap)
    
    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    
    local  pChildrenArray = map:getChildren()
    local  child = nil
    local  pObject = nil
    local i = 0
    local len = pChildrenArray:count()
    for i = 0, len-1, 1 do 
        pObject = pChildrenArray:objectAtIndex(i)
        child = tolua.cast(pObject, "CCSpriteBatchNode")

        if child == nil then
            break
        end

        child:getTexture():setAntiAliasTexParameters()
    end

    local x = 0
    local y = 0
    local z = 0
    x, y, z = map:getCamera():getEyeXYZ(x, y, z)
    cclog("before eye x="..x..",y="..y..",z="..z)
    map:getCamera():setEyeXYZ(x-200, y, z+300)
    x, y, z = map:getCamera():getEyeXYZ(x, y, z)
    cclog("after eye x="..x..",y="..y..",z="..z)


    local function onNodeEvent(event)
        if event == "enter" then
            CCDirector:sharedDirector():setProjection(kCCDirectorProjection3D)
        elseif event == "exit" then
            CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
        end
    end

    layer:registerScriptHandler(onNodeEvent)


    return layer
end

--------------------------------------------------------------------
--
-- TMXOrthoTest2
--
--------------------------------------------------------------------
local function TMXOrthoTest2()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("TMX Ortho test2")
    Helper.subtitleLabel:setString("")

    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test1.tmx")
    layer:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  pChildrenArray = map:getChildren()
    local  child          = nil
    local  pObject        = nil
    local  i              = 0
    local  len            = pChildrenArray:count()

    for i = 0, len-1, 1 do
        child = tolua.cast(pChildrenArray:objectAtIndex(i), "CCSpriteBatchNode")

        if child == nil then
            break
        end
        child:getTexture():setAntiAliasTexParameters()
    end

    map:runAction( CCScaleBy:create(2, 0.5) )
    return layer
end

--------------------------------------------------------------------
--
-- TMXOrthoTest3
--
--------------------------------------------------------------------
local function TMXOrthoTest3()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("TMX anchorPoint test")
    Helper.subtitleLabel:setString("")

    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test3.tmx")
    layer:addChild(map, 0, kTagTileMap)
    
    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  pChildrenArray = map:getChildren()
    local  child          = nil
    local  pObject        = nil
    local  i              = 0
    local  len            = pChildrenArray:count()

    for i = 0, len-1, 1 do
        child = tolua.cast(pChildrenArray:objectAtIndex(i), "CCSpriteBatchNode")

        if child == nil then
            break
        end
        child:getTexture():setAntiAliasTexParameters()
    end
    
    map:setScale(0.2)
    map:setAnchorPoint( ccp(0.5, 0.5) )
    return layer
end


-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoTest4
-- --
-- --------------------------------------------------------------------
-- function TMXOrthoTest4()

--     local map = CCTMXTiledMap:create("TileMaps/orthogonal-test4.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s1 = map:getContentSize()
--     cclog("ContentSize: %f, %f", s1.width,s1.height)
    
--     local  pChildrenArray = map:getChildren()
--     local  child = NULL
--     local  pObject = NULL
--     CCARRAY_FOREACH(pChildrenArray, pObject)
    
--         child = (CCSpriteBatchNode*)pObject

--         if(!child)
--             break

--         child:getTexture():setAntiAliasTexParameters()
--     end
    
--     map:setAnchorPoint(ccp(0, 0))

--     local  layer = map:layerNamed("Layer 0")
--     local s = layer:getLayerSize()
    
--     CCSprite* sprite
--     sprite = layer:tileAt(ccp(0,0))
--     sprite:setScale(2)
--     sprite = layer:tileAt(ccp(s.width-1,0))
--     sprite:setScale(2)
--     sprite = layer:tileAt(ccp(0,s.height-1))
--     sprite:setScale(2)
--     sprite = layer:tileAt(ccp(s.width-1,s.height-1))
--     sprite:setScale(2)

--     schedule( schedule_selector(TMXOrthoTest4:removeSprite), 2 )

-- end

-- function removeSprite(float dt)

--     unschedule(schedule_selector(TMXOrthoTest4:removeSprite))

--     local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local  layer = map:layerNamed("Layer 0")
--     local s = layer:getLayerSize()

--     local  sprite = layer:tileAt( ccp(s.width-1,0) )
--     layer:removeChild(sprite, true)
-- end

-- function title()

--     return "TMX width/height test"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXReadWriteTest
-- --
-- --------------------------------------------------------------------
-- enum

--     SID_UPDATECOL = 100,
--     SID_REPAINTWITHGID,
--     SID_REMOVETILES
-- end

-- function TMXReadWriteTest()

--     m_gid = 0
    
--     local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)

    
--     local  layer = map:layerNamed("Layer 0")
--     layer:getTexture():setAntiAliasTexParameters()

--     map:setScale( 1 )

--     local tile0 = layer:tileAt(ccp(1,63))
--     local tile1 = layer:tileAt(ccp(2,63))
--     local tile2 = layer:tileAt(ccp(3,62))--ccp(1,62))
--     local tile3 = layer:tileAt(ccp(2,62))
--     tile0:setAnchorPoint( ccp(0.5, 0.5) )
--     tile1:setAnchorPoint( ccp(0.5, 0.5) )
--     tile2:setAnchorPoint( ccp(0.5, 0.5) )
--     tile3:setAnchorPoint( ccp(0.5, 0.5) )

--     local  move = CCMoveBy:create(0.5, ccp(0,160))
--     local  rotate = CCRotateBy:create(2, 360)
--     local  scale = CCScaleBy:create(2, 5)
--     local  opacity = CCFadeOut:create(2)
--     local  fadein = CCFadeIn:create(2)
--     local  scaleback = CCScaleTo:create(1, 1)
--     local  finish = CCCallFuncN:create(this, callfuncN_selector(TMXReadWriteTest:removeSprite))
--     local  seq0 = CCSequence:create(move, rotate, scale, opacity, fadein, scaleback, finish, NULL)
--     local  seq1 = (CCActionInterval*)(seq0:copy():autorelease())
--     local  seq2 = (CCActionInterval*)(seq0:copy():autorelease())
--     local  seq3 = (CCActionInterval*)(seq0:copy():autorelease())
    
--     tile0:runAction(seq0)
--     tile1:runAction(seq1)
--     tile2:runAction(seq2)
--     tile3:runAction(seq3)
    
    
--     m_gid = layer:tileGIDAt(ccp(0,63))
--     --------cclog("Tile GID at:(0,63) is: %d", m_gid)

--     schedule(schedule_selector(TMXReadWriteTest:updateCol), 2.0) 
--     schedule(schedule_selector(TMXReadWriteTest:repaintWithGID), 2.05)
--     schedule(schedule_selector(TMXReadWriteTest:removeTiles), 1.0) 

--     --------cclog("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
--     --------cclog("++++children: %d", layer:getChildren():count() )
    
--     m_gid2 = 0
-- end

-- function removeSprite(CCNode* sender)

--     --------cclog("removing tile: %x", sender)
--     local  p = ((CCNode*)sender):getParent()

--     if (p)
    
--         p:removeChild((CCNode*)sender, true)
--     end    
    
--     ----------cclog("atlas quantity: %d", p:textureAtlas():totalQuads())
-- end

-- function updateCol(float dt)
    
--     local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")

--     --------cclog("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
--     --------cclog("++++children: %d", layer:getChildren():count() )


--     local s = layer:getLayerSize()

--     for( int y=0 y< s.height y++ ) 
    
--         layer:setTileGID(m_gid2, ccp((float)3, (float)y))
--     end
    
--     m_gid2 = (m_gid2 + 1) % 80
-- end

-- function repaintWithGID(float dt)

-- --    unschedule:_cmd)
    
--     local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")
    
--     local s = layer:getLayerSize()
--     for( int x=0 x<s.widthx++) 
    
--         int y = (int)s.height-1
--         unsigned int tmpgid = layer:tileGIDAt( ccp((float)x, (float)y) )
--         layer:setTileGID(tmpgid+1, ccp((float)x, (float)y))
--     end
-- end

-- function removeTiles(float dt)

--     unschedule(schedule_selector(TMXReadWriteTest:removeTiles))

--     local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")
--     local s = layer:getLayerSize()

--     for( int y=0 y< s.height y++ ) 
    
--         layer:removeTileAt( ccp(5.0, (float)y) )
--     end
-- end



-- function title()

--     return "TMX Read/Write test"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXHexTest
-- --
-- --------------------------------------------------------------------
-- function TMXHexTest()

--     local  color = CCLayerColor:create( ccc4(64,64,64,255) )
--     addChild(color, -1)
    
--     local  map = CCTMXTiledMap:create("TileMaps/hexa-test.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
-- end

-- function title()

--     return "TMX Hex tes"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXIsoTest
-- --
-- --------------------------------------------------------------------
-- function TMXIsoTest()

--     local  color = CCLayerColor:create( ccc4(64,64,64,255) )
--     addChild(color, -1)
    
--     local  map = CCTMXTiledMap:create("TileMaps/iso-test.tmx")
--     addChild(map, 0, kTagTileMap)        
    
--     -- move map to the center of the screen
--     local ms = map:getMapSize()
--     local ts = map:getTileSize()
--     map:runAction( CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 )) ) 
-- end

-- function title()

--     return "TMX Isometric test 0"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXIsoTest1
-- --
-- --------------------------------------------------------------------
-- function TMXIsoTest1()

--     local  color = CCLayerColor:create( ccc4(64,64,64,255) )
--     addChild(color, -1)
    
--     local map = CCTMXTiledMap:create("TileMaps/iso-test1.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     map:setAnchorPoint(ccp(0.5, 0.5))
-- end

-- function title()

--     return "TMX Isometric test + anchorPoint"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXIsoTest2
-- --
-- --------------------------------------------------------------------
-- function TMXIsoTest2()

--     local  color = CCLayerColor:create( ccc4(64,64,64,255) )
--     addChild(color, -1)
    
--     local map = CCTMXTiledMap:create("TileMaps/iso-test2.tmx")
--     addChild(map, 0, kTagTileMap)    
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     -- move map to the center of the screen
--     local ms = map:getMapSize()
--     local ts = map:getTileSize()
--     map:runAction( CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))
-- end

-- function title()

--     return "TMX Isometric test 2"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXUncompressedTest
-- --
-- --------------------------------------------------------------------
-- function TMXUncompressedTest()

--     local  color = CCLayerColor:create( ccc4(64,64,64,255) )
--     addChild(color, -1)
    
--     local map = CCTMXTiledMap:create("TileMaps/iso-test2-uncompressed.tmx")
--     addChild(map, 0, kTagTileMap)    
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     -- move map to the center of the screen
--     local ms = map:getMapSize()
--     local ts = map:getTileSize()
--     map:runAction(CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))
    
--     -- testing release map
--     local  pChildrenArray = map:getChildren()
--     CCTMXLayer* layer
--     local  pObject = NULL
--     CCARRAY_FOREACH(pChildrenArray, pObject)
    
--         layer= (CCTMXLayer*)pObject

--         if(!layer)
--             break

--         layer:releaseMap()
--     end

-- end

-- function title()

--     return "TMX Uncompressed test"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXTilesetTest
-- --
-- --------------------------------------------------------------------
-- function TMXTilesetTest()

--     local map = CCTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     CCTMXLayer* layer
--     layer = map:layerNamed("Layer 0")
--     layer:getTexture():setAntiAliasTexParameters()
    
--     layer = map:layerNamed("Layer 1")
--     layer:getTexture():setAntiAliasTexParameters()

--     layer = map:layerNamed("Layer 2")
--     layer:getTexture():setAntiAliasTexParameters()
-- end

-- function title()

--     return "TMX Tileset test"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoObjectsTest
-- --
-- --------------------------------------------------------------------
-- function TMXOrthoObjectsTest()

--     local map = CCTMXTiledMap:create("TileMaps/ortho-objects.tmx")
--     addChild(map, -1, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     --------cclog("---: Iterating over all the group objets")
--     local  group = map:objectGroupNamed("Object Group 1")
--     local  objects = group:getObjects()

--     local  dict = NULL
--     local  pObj = NULL
--     CCARRAY_FOREACH(objects, pObj)
    
--         dict = (CCDictionary*)pObj--dynamic_cast<CCStringToStringDictionary*>(*it)

--         if(!dict)
--             break

--         --------cclog("object: %x", dict)
--     end
    
--     --------cclog("---: Fetching 1 object by name")
--     -- local  platform = group:objectNamed("platform")
--     --------cclog("platform: %x", platform)
-- end

-- function draw()

--     local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local  group = map:objectGroupNamed("Object Group 1")

--     local  objects = group:getObjects()
--     local  dict = NULL
--     local  pObj = NULL
--     CCARRAY_FOREACH(objects, pObj)
    
--         dict = (CCDictionary*)pObj--dynamic_cast<CCStringToStringDictionary*>(*it)
        
--         if(!dict)
--             break
--         const char* key = "x"
--         int x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
--         key = "y"
--         int y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
--         key = "width"
--         int width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
--         key = "height"
--         int height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()
        
--         glLineWidth(3)
        
--         ccDrawLine( ccp((float)x, (float)y), ccp((float)(x+width), (float)y) )
--         ccDrawLine( ccp((float)(x+width), (float)y), ccp((float)(x+width), (float)(y+height)) )
--         ccDrawLine( ccp((float)(x+width), (float)(y+height)), ccp((float)x, (float)(y+height)) )
--         ccDrawLine( ccp((float)x, (float)(y+height)), ccp((float)x, (float)y) )
        
--         glLineWidth(1)
--     end
-- end

-- function title()

--     return "TMX Ortho object test"
-- end

-- function subtitle()

--     return "You should see a white box around the 3 platforms"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXIsoObjectsTest
-- --
-- --------------------------------------------------------------------

-- function TMXIsoObjectsTest()

--     local  map = CCTMXTiledMap:create("TileMaps/iso-test-objectgroup.tmx")
--     addChild(map, -1, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)

--     local  group = map:objectGroupNamed("Object Group 1")

--     --UxMutableArray* objects = group:objects()
--     local  objects = group:getObjects()
--     --UxMutableDictionary<std:string>* dict
--     CCDictionary* dict
--     local  pObj = NULL
--     CCARRAY_FOREACH(objects, pObj)
    
--         dict = (CCDictionary*)pObj

--         if(!dict)
--             break

--         --------cclog("object: %x", dict)
--     end        
-- end

-- function draw()

--     local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local group = map:objectGroupNamed("Object Group 1")

--     local  objects = group:getObjects()
--     CCDictionary* dict
--     local  pObj = NULL
--     CCARRAY_FOREACH(objects, pObj)
    
--         dict = (CCDictionary*)pObj--dynamic_cast<CCStringToStringDictionary*>(*it)

--         if(!dict)
--             break
--         const char* key = "x"
--         int x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("x")):getNumber()
--         key = "y"
--         int y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
--         key = "width"
--         int width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
--         key = "height"
--         int height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()
        
--         glLineWidth(3)
        
--         ccDrawLine( ccp(x,y), ccp(x+width,y) )
--         ccDrawLine( ccp(x+width,y), ccp(x+width,y+height) )
--         ccDrawLine( ccp(x+width,y+height), ccp(x,y+height) )
--         ccDrawLine( ccp(x,y+height), ccp(x,y) )
        
--         glLineWidth(1)
--     end
-- end

-- function title()

--     return "TMX Iso object test"
-- end

-- function subtitle()

--     return "You need to parse them manually. See bug #810"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXResizeTest
-- --
-- --------------------------------------------------------------------

-- function TMXResizeTest()

--     local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)

--     CCTMXLayer* layer
--     layer = map:layerNamed("Layer 0")

--     local ls = layer:getLayerSize()
--     for (unsigned int y = 0 y < ls.height y++) 
    
--         for (unsigned int x = 0 x < ls.width x++) 
        
--             layer:setTileGID(1, ccp( x, y ) )
--         end
--     end        
-- end

-- function title()

--     return "TMX resize test"
-- end

-- function subtitle()

--     return "Should not crash. Testing issue #740"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXIsoZorder
-- --
-- --------------------------------------------------------------------
-- function TMXIsoZorder()

--     local map = CCTMXTiledMap:create("TileMaps/iso-test-zorder.tmx")
--     addChild(map, 0, kTagTileMap)

--     local s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
--     map:setPosition(ccp(-s.width/2,0))
    
--     m_tamara = CCSprite:create(s_pPathSister1)
--     map:addChild(m_tamara, map:getChildren():count() )
--     m_tamara:retain()
--     int mapWidth = map:getMapSize().width * map:getTileSize().width
--     m_tamara:setPosition(CC_POINT_PIXELS_TO_POINTS(ccp( mapWidth/2,0)))
--     m_tamara:setAnchorPoint(ccp(0.5,0))

    
--     local  move = CCMoveBy:create(10, ccp(300,250))
--     local  back = move:reverse()
--     local  seq = CCSequence:create(move, back,NULL)
--     m_tamara:runAction( CCRepeatForever:create(seq) )
    
--     schedule( schedule_selector(TMXIsoZorder:repositionSprite) )
-- end

-- function ~TMXIsoZorder()

--     m_tamara:release()
-- end

-- function onExit()

--     unschedule(schedule_selector(TMXIsoZorder:repositionSprite))
--     TileDemo:onExit()
-- end

-- function repositionSprite(float dt)

--     local p = m_tamara:getPosition()
--     p = CC_POINT_POINTS_TO_PIXELS(p)
--     local map = getChildByTag(kTagTileMap)
    
--     -- there are only 4 layers. (grass and 3 trees layers)
--     -- if tamara < 48, z=4
--     -- if tamara < 96, z=3
--     -- if tamara < 144,z=2
    
--     int newZ = 4 - (p.y / 48)
--     newZ = max(newZ,0)
    
--     map:reorderChild(m_tamara, newZ)    
-- end

-- function title()

--     return "TMX Iso Zorder"
-- end

-- function subtitle()

--     return "Sprite should hide behind the trees"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoZorder
-- --
-- --------------------------------------------------------------------
-- function TMXOrthoZorder()

--     local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-zorder.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     m_tamara = CCSprite:create(s_pPathSister1)
--     map:addChild(m_tamara,  map:getChildren():count())
--     m_tamara:retain()
--     m_tamara:setAnchorPoint(ccp(0.5,0))

    
--     local  move = CCMoveBy:create(10, ccp(400,450))
--     local  back = move:reverse()
--     local  seq = CCSequence:create(move, back,NULL)
--     m_tamara:runAction( CCRepeatForever:create(seq))
    
--     schedule( schedule_selector(TMXOrthoZorder:repositionSprite))
-- end

-- function ~TMXOrthoZorder()

--     m_tamara:release()
-- end

-- function repositionSprite(float dt)

--     local p = m_tamara:getPosition()
--     p = CC_POINT_POINTS_TO_PIXELS(p)
--     local  map = getChildByTag(kTagTileMap)
    
--     -- there are only 4 layers. (grass and 3 trees layers)
--     -- if tamara < 81, z=4
--     -- if tamara < 162, z=3
--     -- if tamara < 243,z=2

--     -- -10: customization for this particular sample
--     int newZ = 4 - ( (p.y-10) / 81)
--     newZ = max(newZ,0)

--     map:reorderChild(m_tamara, newZ)
-- end

-- function title()

--     return "TMX Ortho Zorder"
-- end

-- function subtitle()

--     return "Sprite should hide behind the trees"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXIsoVertexZ
-- --
-- --------------------------------------------------------------------
-- function TMXIsoVertexZ()

--     local map = CCTMXTiledMap:create("TileMaps/iso-test-vertexz.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local s = map:getContentSize()
--     map:setPosition( ccp(-s.width/2,0) )
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
--     -- can use any CCSprite and it will work OK.
--     local  layer = map:layerNamed("Trees")
--     m_tamara = layer:tileAt( ccp(29,29) )
--     m_tamara:retain()
    
--     local  move = CCMoveBy:create(10, ccpMult( ccp(300,250), 1/CC_CONTENT_SCALE_FACTOR() ) )
--     local  back = move:reverse()
--     local  seq = CCSequence:create(move, back,NULL)
--     m_tamara:runAction( CCRepeatForever:create(seq) )
    
--     schedule( schedule_selector(TMXIsoVertexZ:repositionSprite))
    
-- end

-- function ~TMXIsoVertexZ()

--     m_tamara:release()
-- end

-- function repositionSprite(float dt)

--     -- tile height is 64x32
--     -- map size: 30x30
--     local p = m_tamara:getPosition()
--     p = CC_POINT_POINTS_TO_PIXELS(p)
--     float newZ = -(p.y+32) /16
--     m_tamara:setVertexZ( newZ )
-- end

-- function onEnter()

--     TileDemo:onEnter()
    
--     -- TIP: 2d projection should be used
--     CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
-- end

-- function onExit()

--     -- At exit use any other projection. 
--     --    CCDirector:sharedDirector():setProjection:kCCDirectorProjection3D)
--     TileDemo:onExit()
-- end

-- function title()

--     return "TMX Iso VertexZ"
-- end

-- function subtitle()

--     return "Sprite should hide behind the trees"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoVertexZ
-- --
-- --------------------------------------------------------------------
-- function TMXOrthoVertexZ()

--     local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-vertexz.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
    
--     -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
--     -- can use any CCSprite and it will work OK.
--     local  layer = map:layerNamed("trees")
--     m_tamara = layer:tileAt(ccp(0,11))
--     cclog("%p vertexZ: %f", m_tamara, m_tamara:getVertexZ())
--     m_tamara:retain()

--     local  move = CCMoveBy:create(10, ccpMult( ccp(400,450), 1/CC_CONTENT_SCALE_FACTOR()))
--     local  back = move:reverse()
--     local  seq = CCSequence:create(move, back,NULL)
--     m_tamara:runAction( CCRepeatForever:create(seq))
    
--     schedule(schedule_selector(TMXOrthoVertexZ:repositionSprite))
    
-- end

-- function ~TMXOrthoVertexZ()

--     m_tamara:release()
-- end

-- function repositionSprite(float dt)

--     -- tile height is 101x81
--     -- map size: 12x12
--     local p = m_tamara:getPosition()
--     p = CC_POINT_POINTS_TO_PIXELS(p)
--     m_tamara:setVertexZ( -( (p.y+81) /81) )
-- end

-- function onEnter()

--     TileDemo:onEnter()
    
--     -- TIP: 2d projection should be used
--     CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
-- end

-- function onExit()

--     -- At exit use any other projection. 
--     --    CCDirector:sharedDirector():setProjection:kCCDirectorProjection3D)
--     TileDemo:onExit()
-- end

-- function title()

--     return "TMX Ortho vertexZ"
-- end

-- function subtitle()

--     return "Sprite should hide behind the trees"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXIsoMoveLayer
-- --
-- --------------------------------------------------------------------
-- function TMXIsoMoveLayer()

--     local  map = CCTMXTiledMap:create("TileMaps/iso-test-movelayer.tmx")
--     addChild(map, 0, kTagTileMap)
    
--     map:setPosition(ccp(-700,-50))

--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
-- end

-- function title()

--     return "TMX Iso Move Layer"
-- end

-- function subtitle()

--     return "Trees should be horizontally aligned"
-- end


-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoMoveLayer
-- --
-- --------------------------------------------------------------------
-- function TMXOrthoMoveLayer()

--     local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-movelayer.tmx")
--     addChild(map, 0, kTagTileMap)

--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)
-- end

-- function title()

--     return "TMX Ortho Move Layer"
-- end

-- function subtitle()

--     return "Trees should be horizontally aligned"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXTilePropertyTest
-- --
-- --------------------------------------------------------------------

-- function TMXTilePropertyTest()

--     local map = CCTMXTiledMap:create("TileMaps/ortho-tile-property.tmx")
--     addChild(map ,0 ,kTagTileMap)

--     for(int i=1i<=20i++)
--         cclog("GID:%i, Properties:%p", i, map:propertiesForGID(i))
--     end
-- end

-- function title()

--     return "TMX Tile Property Test"
-- end

-- function subtitle()

--     return "In the console you should see tile properties"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoFlipTest
-- --
-- --------------------------------------------------------------------

-- function TMXOrthoFlipTest()

--     local map = CCTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
--     addChild(map, 0, kTagTileMap)

--     local  s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)

--     local  pObj = NULL
--     CCARRAY_FOREACH(map:getChildren(), pObj)
    
--         local  child = (CCSpriteBatchNode*)pObj
--         child:getTexture():setAntiAliasTexParameters()
--     end

--     local  action = CCScaleBy:create(2, 0.5)
--     map:runAction(action)
-- end

-- function title()

--     return "TMX tile flip test"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoFlipRunTimeTest
-- --
-- --------------------------------------------------------------------

-- function TMXOrthoFlipRunTimeTest()

--     local map = CCTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
--     addChild(map, 0, kTagTileMap)

--     local s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)

--     local  pObj = NULL
--     CCARRAY_FOREACH(map:getChildren(), pObj)
    
--         local  child = (CCSpriteBatchNode*)pObj
--         child:getTexture():setAntiAliasTexParameters()
--     end

--     local  action = CCScaleBy:create(2, 0.5)
--     map:runAction(action)

--     schedule(schedule_selector(TMXOrthoFlipRunTimeTest:flipIt), 1.0)
-- end

-- function title()

--     return "TMX tile flip run time test"
-- end

-- function subtitle()

--     return "in 2 sec bottom left tiles will flip"
-- end

-- function flipIt(float dt)

--     local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap") 
--     local layer = map:layerNamed("Layer 0") 

--     --blue diamond 
--     local tileCoord = ccp(1,10)
--     int flags
--     unsigned int GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
--     -- Vertical
--     if( flags & kCCTMXTileVerticalFlag )
--         flags &= ~kCCTMXTileVerticalFlag
--     else
--         flags |= kCCTMXTileVerticalFlag
--     layer:setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags)


--     tileCoord = ccp(1,8)    
--     GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
--     -- Vertical
--     if( flags & kCCTMXTileVerticalFlag )
--         flags &= ~kCCTMXTileVerticalFlag
--     else
--         flags |= kCCTMXTileVerticalFlag    
--     layer:setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags)


--     tileCoord = ccp(2,8)
--     GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
--     -- Horizontal
--     if( flags & kCCTMXTileHorizontalFlag )
--         flags &= ~kCCTMXTileHorizontalFlag
--     else
--         flags |= kCCTMXTileHorizontalFlag    
--     layer:setTileGID(GID, tileCoord, (ccTMXTileFlags)flags)    
-- end
-- --------------------------------------------------------------------
-- --
-- -- TMXOrthoFromXMLTest
-- --
-- --------------------------------------------------------------------

-- function TMXOrthoFromXMLTest()

--     string resources = "TileMaps"        -- partial paths are OK as resource paths.
--     string file = resources + "/orthogonal-test1.tmx"

--     local  str = CCString:createWithContentsOfFile(CCFileUtils:sharedFileUtils():fullPathForFilename(file.c_str()).c_str())
--     CCAssert(str != NULL, "Unable to open file")

--     local map = CCTMXTiledMap:createWithXML(str:getCString() ,resources.c_str())
--     addChild(map, 0, kTagTileMap)

--     local s = map:getContentSize()
--     cclog("ContentSize: %f, %f", s.width,s.height)

--     local  pObj = NULL
--     CCARRAY_FOREACH(map:getChildren(), pObj)
    
--         local  child = (CCSpriteBatchNode*)pObj
--         child:getTexture():setAntiAliasTexParameters()
--     end

--     local  action = CCScaleBy:create(2, 0.5)
--     map:runAction(action)
-- end

-- function title()

--     return "TMX created from XML test"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXBug987
-- --
-- --------------------------------------------------------------------
-- function TMXBug987()

--     local map = CCTMXTiledMap:create("TileMaps/orthogonal-test6.tmx")
--     addChild(map, 0, kTagTileMap)

--     local  s1 = map:getContentSize()
--     cclog("ContentSize: %f, %f", s1.width,s1.height)

--     local  childs = map:getChildren()
--     CCTMXLayer* pNode
--     local  pObject = NULL
--     CCARRAY_FOREACH(childs, pObject)
    
--         pNode = (CCTMXLayer*) pObject
--         CC_BREAK_IF(!pNode)
--         pNode:getTexture():setAntiAliasTexParameters()
--     end

--     map:setAnchorPoint(ccp(0, 0))
--     local layer = map:layerNamed("Tile Layer 1")
--     layer:setTileGID(3, ccp(2,2))
-- end

-- function title()

--     return "TMX Bug 987"
-- end

-- function subtitle()

--     return "You should see an square"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TMXBug787
-- --
-- --------------------------------------------------------------------
-- function TMXBug787()

--     local map = CCTMXTiledMap:create("TileMaps/iso-test-bug787.tmx")
--     addChild(map, 0, kTagTileMap)

--     map:setScale(0.25)
-- end

-- function title()

--     return "TMX Bug 787"
-- end

-- function subtitle()

--     return "You should see a map"
-- end

-- --------------------------------------------------------------------
-- --
-- -- TileDemo
-- --
-- --------------------------------------------------------------------

-- enum

--     IDC_NEXT = 100,
--     IDC_BACK,
--     IDC_RESTART
-- end

-- static int sceneIdx = -1 

-- #define MAX_LAYER    28

-- CCLayer* createTileMapLayer(int nIndex)

--     switch(nIndex)
    
--         case 0: return new TMXIsoZorder()
--         case 1: return new TMXOrthoZorder()
--         case 2: return new TMXIsoVertexZ()
--         case 3: return new TMXOrthoVertexZ()    
--         case 4: return new TMXOrthoTest()
--         case 5: return new TMXOrthoTest2()
--         case 6: return new TMXOrthoTest3()
--         case 7: return new TMXOrthoTest4()
--         case 8: return new TMXIsoTest()
--         case 9: return new TMXIsoTest1()
--         case 10: return new TMXIsoTest2()
--         case 11: return new TMXUncompressedTest ()
--         case 12: return new TMXHexTest()
--         case 13: return new TMXReadWriteTest()
--         case 14: return new TMXTilesetTest()
--         case 15: return new TMXOrthoObjectsTest()
--         case 16: return new TMXIsoObjectsTest()
--         case 17: return new TMXResizeTest()
--         case 18: return new TMXIsoMoveLayer()
--         case 19: return new TMXOrthoMoveLayer()
--         case 20: return new TMXOrthoFlipTest()
--         case 21: return new TMXOrthoFlipRunTimeTest()
--         case 22: return new TMXOrthoFromXMLTest()
--         case 23: return new TileMapTest()
--         case 24: return new TileMapEditTest()
--         case 25: return new TMXBug987()
--         case 26: return new TMXBug787()
--         case 27: return new TMXGIDObjectsTest()
--     end

--     return NULL
-- end

-- CCLayer* nextTileMapAction()

--     sceneIdx++
--     sceneIdx = sceneIdx % MAX_LAYER

--     local  pLayer = createTileMapLayer(sceneIdx)
--     pLayer:autorelease()

--     return pLayer
-- end

-- CCLayer* backTileMapAction()

--     sceneIdx--
--     int total = MAX_LAYER
--     if( sceneIdx < 0 )
--         sceneIdx += total    
    
--     local  pLayer = createTileMapLayer(sceneIdx)
--     pLayer:autorelease()

--     return pLayer
-- end

-- CCLayer* restartTileMapAction()

--     local  pLayer = createTileMapLayer(sceneIdx)
--     pLayer:autorelease()

--     return pLayer
-- end 


-- function TileDemo(void)

--     setTouchEnabled( true )

--     local s = CCDirector:sharedDirector():getWinSize()

--     m_label = CCLabelTTF:create("", "Arial", 28)
--     addChild(m_label, 1)
--     m_label:setPosition( ccp(s.width/2, s.height-50) )
--     m_label:retain()

--     std:string strSubtitle = subtitle()
--     if( ! strSubtitle.empty() ) 
    
--         local  l = CCLabelTTF:create(strSubtitle.c_str(), "Thonburi", 16)
--         addChild(l, 1)
--         l:setPosition( ccp(s.width/2, s.height-80) )

--         m_subtitle = l
--         m_subtitle:retain()
--     end    

--     local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2, this, menu_selector(TileDemo:backCallback) )
--     local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2, this, menu_selector(TileDemo:restartCallback) )
--     local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2, this, menu_selector(TileDemo:nextCallback) )

--     local menu = CCMenu:create(item1, item2, item3, NULL)

--     menu:setPosition( local Zero )
--     item1:setPosition(ccp(VisibleRect:center().x - item2:getContentSize().width*2, VisibleRect:bottom().y+item2:getContentSize().height/2))
--     item2:setPosition(ccp(VisibleRect:center().x, VisibleRect:bottom().y+item2:getContentSize().height/2))
--     item3:setPosition(ccp(VisibleRect:center().x + item2:getContentSize().width*2, VisibleRect:bottom().y+item2:getContentSize().height/2))
    
--     addChild(menu, 1)    
-- end

-- function ~TileDemo(void)

--     m_label:release()
--     m_subtitle:release()
-- end

-- function title()

--     return "No title"
-- end

-- function subtitle()

--     return "drag the screen"
-- end

-- function onEnter()

--     CCLayer:onEnter()

--     m_label:setString(title().c_str())
--     m_subtitle:setString(subtitle().c_str())
-- end

-- function restartCallback(CCObject* pSender)

--     local  s = new TileMapTestScene()
--     s:addChild(restartTileMapAction()) 

--     CCDirector:sharedDirector():replaceScene(s)
--     s:release()
-- end

-- function nextCallback(CCObject* pSender)

--     local  s = new TileMapTestScene()
--     s:addChild( nextTileMapAction() )
--     CCDirector:sharedDirector():replaceScene(s)
--     s:release()
-- end

-- function backCallback(CCObject* pSender)

--     local  s = new TileMapTestScene()
--     s:addChild( backTileMapAction() )
--     CCDirector:sharedDirector():replaceScene(s)
--     s:release()
-- end 

-- function ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)

--     local touch = tolua.cast(pTouches:anyObject(), "CCTouch")
    
--     local diff = touch:getDelta()
--     local node = getChildByTag(kTagTileMap)
--     local currentPos = node:getPosition()
--     node:setPosition( ccpAdd(currentPos, diff) )
-- end

-- function runThisTest()

--     local  pLayer = nextTileMapAction()
--     addChild(pLayer)

--     -- fix bug #486, #419. 
--     -- "test" is the default value in CCDirector:setGLDefaultValues()
--     -- but TransitionTest may setDepthTest(false), we should revert it here
--     CCDirector:sharedDirector():setDepthTest(true)
    
--     CCDirector:sharedDirector():replaceScene(this)
-- end

-- function TMXGIDObjectsTest()

--     local map = CCTMXTiledMap:create("TileMaps/test-object-layer.tmx")
--     addChild(map, -1, kTagTileMap)

--     local  s = map:getContentSize()
--     cclog("Contentsize: %f, %f", s.width, s.height)

--     cclog("---: Iterating over all the group objets")
--     --local group = map:objectGroupNamed("Object Layer 1")

-- end

-- function draw()

--     local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
--     local group = map:objectGroupNamed("Object Layer 1")

--     local array = group:getObjects()
--     CCDictionary* dict
--     local  pObj = NULL
--     CCARRAY_FOREACH(array, pObj)
    
--         dict = (CCDictionary*)pObj
--         if(!dict)
        
--             break
--         end

--         const char* key = "x"
--         int x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
--         key = "y"
--         int y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
--         key = "width"
--         int width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
--         key = "height"
--         int height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()

--         glLineWidth(3)

--         ccDrawLine(ccp(x, y), ccp(x + width, y))
--         ccDrawLine(ccp(x + width, y), ccp(x + width, y + height))
--         ccDrawLine(ccp(x + width,y + height), ccp(x,y + height))
--         ccDrawLine(ccp(x,y + height), ccp(x,y))

--         glLineWidth(1)
--     end
-- end

-- function title()

--     return "TMX GID objects"
-- end

-- function subtitle()

--     return "Tiles are created from an object group"
-- end

function TileMapTestMain()
    cclog("TileMapTestMain")
    m_time = 0
    local scene = CCScene:create()

    Helper.createFunctionTable = {
        TileMapTest,
        TileMapEditTest,
        TMXOrthoTest,
        TMXOrthoTest2,
        TMXOrthoTest3,
    }
    scene:addChild(TileMapTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end



