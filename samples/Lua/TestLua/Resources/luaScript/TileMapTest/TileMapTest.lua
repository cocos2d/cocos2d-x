local size = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()

local kTagTileMap = 1


local function createTileDemoLayer(title, subtitle)
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    local titleStr = title == nil and "No title" or title
    local subTitleStr = subtitle  == nil and "drag the screen" or subtitle
    Helper.titleLabel:setString(titleStr)
    Helper.subtitleLabel:setString(subTitleStr)

    local prev = {x = 0, y = 0}
    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            prev.x = x
            prev.y = y
            return true
        elseif  eventType == "moved" then
            local node  = layer:getChildByTag(kTagTileMap)
            local newX  = node:getPositionX()
            local newY  = node:getPositionY()
            local diffX = x - prev.x
            local diffY = y - prev.y

            node:setPosition( ccpAdd(ccp(newX, newY), ccp(diffX, diffY)) )
            prev.x = x
            prev.y = y
        end
    end
    layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(onTouchEvent)
    return layer
end
--------------------------------------------------------------------
--
-- TileMapTest
--
--------------------------------------------------------------------
local function TileMapTest()
    local layer = createTileDemoLayer("TileMapAtlas")

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
    local layer = createTileDemoLayer("Editable TileMapAtlas")
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
    local layer = createTileDemoLayer("TMX Orthogonal test")
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
    local layer = createTileDemoLayer("TMX Ortho test2")

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
    local layer = createTileDemoLayer("TMX anchorPoint test")
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


--------------------------------------------------------------------
--
-- TMXOrthoTest4
--
--------------------------------------------------------------------
local function TMXOrthoTest4()
    local ret = createTileDemoLayer("TMX width/height test")
    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test4.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s1 = map:getContentSize()
    cclog("ContentSize: %f, %f", s1.width,s1.height)

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

    map:setAnchorPoint(ccp(0, 0))

    local layer  = map:layerNamed("Layer 0")
    local s      = layer:getLayerSize()

    local sprite = layer:tileAt(ccp(0,0))
    sprite:setScale(2)
    sprite       = layer:tileAt(ccp(s.width-1,0))
    sprite:setScale(2)
    sprite       = layer:tileAt(ccp(0,s.height-1))
    sprite:setScale(2)
    sprite       = layer:tileAt(ccp(s.width-1,s.height-1))
    sprite:setScale(2)

    local schedulerEntry = nil

    local function removeSprite(dt)
        scheduler:unscheduleScriptEntry(schedulerEntry)
        schedulerEntry = nil
        local map = tolua.cast(ret:getChildByTag(kTagTileMap), "CCTMXTiledMap")
        local  layer0 = map:layerNamed("Layer 0")
        local s = layer0:getLayerSize()

        local  sprite = layer0:tileAt( ccp(s.width-1,0) )
        layer0:removeChild(sprite, true)
    end


    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(removeSprite, 2, false)
        elseif event == "exit" and schedulerEntry ~= nil then
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end

--------------------------------------------------------------------
--
-- TMXReadWriteTest
--
--------------------------------------------------------------------
local SID_UPDATECOL      = 100
local SID_REPAINTWITHGID = 101
local SID_REMOVETILES    = 102

local function TMXReadWriteTest()
    local ret = createTileDemoLayer("TMX Read/Write test")
    local m_gid  = 0
    local m_gid2 = 0
    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)


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

    local function removeSprite(tag, sender)
        --------cclog("removing tile: %x", sender)
        local node = tolua.cast(sender, "CCNode");
        local p = node:getParent()

        if p ~= nil then
            p:removeChild(node, true)
        end
        ----------cclog("atlas quantity: %d", p:textureAtlas():totalQuads())
    end


    local  finish = CCCallFuncN:create(removeSprite)
    local arr = CCArray:create()
    arr:addObject(move)
    arr:addObject(rotate)
    arr:addObject(scale)
    arr:addObject(opacity)
    arr:addObject(fadein)
    arr:addObject(scaleback)
    arr:addObject(finish)
    local  seq0 = CCSequence:create(arr)
    local  seq1 = tolua.cast(seq0:copy():autorelease(), "CCAction")
    local  seq2 = tolua.cast(seq0:copy():autorelease(), "CCAction")
    local  seq3 = tolua.cast(seq0:copy():autorelease(), "CCAction")

    tile0:runAction(seq0)
    tile1:runAction(seq1)
    tile2:runAction(seq2)
    tile3:runAction(seq3)


    m_gid = layer:tileGIDAt(ccp(0,63))
    --------cclog("Tile GID at:(0,63) is: %d", m_gid)
    local updateColScheduler     = nil
    local repainWithGIDScheduler = nil
    local removeTilesScheduler   = nil

    local function updateCol(dt)

        local  map = tolua.cast(ret:getChildByTag(kTagTileMap), "CCTMXTiledMap")
        local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")

        --------cclog("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
        --------cclog("++++children: %d", layer:getChildren():count() )


        local s = layer:getLayerSize()
        local y = 0
        for y=0, s.height-1, 1 do
            layer:setTileGID(m_gid2, ccp(3, y))
        end

        m_gid2 = (m_gid2 + 1) % 80
    end

    local function repaintWithGID(dt)
        --    unschedule:_cmd)
        local  map = tolua.cast(ret:getChildByTag(kTagTileMap), "CCTMXTiledMap")
        local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")

        local s = layer:getLayerSize()
        local x = 0
        for x=0, s.width-1, 1 do
            local y = s.height-1
            local tmpgid = layer:tileGIDAt( ccp(x, y) )
            layer:setTileGID(tmpgid+1, ccp(x, y))
        end
    end

    local function removeTiles(dt)
        scheduler:unscheduleScriptEntry(removeTilesScheduler)
        removeTilesScheduler = nil
        local  map = tolua.cast(ret:getChildByTag(kTagTileMap), "CCTMXTiledMap")
        local layer = tolua.cast(map:getChildByTag(0), "CCTMXLayer")
        local s = layer:getLayerSize()
        local y = 0
        for y=0, s.height-1, 1 do
            layer:removeTileAt( ccp(5.0, y) )
        end
    end

    local function onNodeEvent(event)
        if event == "enter" then
            updateColScheduler = scheduler:scheduleScriptFunc(updateCol, 2, false)
            repainWithGIDScheduler = scheduler:scheduleScriptFunc(repaintWithGID, 2.05, false)
            removeTilesScheduler = scheduler:scheduleScriptFunc(removeTiles, 1.0, false)
        elseif event == "exit" then
            if updateColScheduler ~= nil then
                scheduler:unscheduleScriptEntry(updateColScheduler)
            end

            if repainWithGIDScheduler ~= nil then
                scheduler:unscheduleScriptEntry(repainWithGIDScheduler)
            end

            if removeTilesScheduler ~= nil then
                scheduler:unscheduleScriptEntry(removeTilesScheduler)
            end

        end
    end

    ret:registerScriptHandler(onNodeEvent)
    --------cclog("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
    --------cclog("++++children: %d", layer:getChildren():count() )

    m_gid2 = 0
    return ret
end


--------------------------------------------------------------------
--
-- TMXHexTest
--
--------------------------------------------------------------------
local function TMXHexTest()
    local ret = createTileDemoLayer("TMX Hex tes")
    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    ret:addChild(color, -1)

    local  map = CCTMXTiledMap:create("TileMaps/hexa-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoTest
--
--------------------------------------------------------------------
local function TMXIsoTest()
    local ret = createTileDemoLayer("TMX Isometric test 0")
    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    ret:addChild(color, -1)

    local  map = CCTMXTiledMap:create("TileMaps/iso-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    -- move map to the center of the screen
    local ms = map:getMapSize()
    local ts = map:getTileSize()
    map:runAction( CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 )) )
    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoTest1
--
--------------------------------------------------------------------
local function TMXIsoTest1()
    local ret = createTileDemoLayer("TMX Isometric test + anchorPoint")
    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    ret:addChild(color, -1)

    local map = CCTMXTiledMap:create("TileMaps/iso-test1.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    map:setAnchorPoint(ccp(0.5, 0.5))
    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoTest2
--
--------------------------------------------------------------------
local function TMXIsoTest2()
    local ret = createTileDemoLayer("TMX Isometric test 2")
    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    ret:addChild(color, -1)

    local map = CCTMXTiledMap:create("TileMaps/iso-test2.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- move map to the center of the screen
    local ms = map:getMapSize()
    local ts = map:getTileSize()
    map:runAction( CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))
    return ret
end

--------------------------------------------------------------------
--
-- TMXUncompressedTest
--
--------------------------------------------------------------------
local function TMXUncompressedTest()
    local ret = createTileDemoLayer("TMX Uncompressed test")
    local  color = CCLayerColor:create( ccc4(64,64,64,255) )
    ret:addChild(color, -1)

    local map = CCTMXTiledMap:create("TileMaps/iso-test2-uncompressed.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- move map to the center of the screen
    local ms = map:getMapSize()
    local ts = map:getTileSize()
    map:runAction(CCMoveTo:create(1.0, ccp( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))

    -- testing release map
    local  pChildrenArray = map:getChildren()
    local layer = nil
    local i = 0
    local len = pChildrenArray:count()
    for i = 0, len-1, 1 do
        layer = tolua.cast(pChildrenArray:objectAtIndex(i), "CCTMXLayer")
        if layer == nil then
            break
        end
        layer:releaseMap()
    end
    return ret
end

--------------------------------------------------------------------
--
-- TMXTilesetTest
--
--------------------------------------------------------------------
local function TMXTilesetTest()
    local ret = createTileDemoLayer("TMX Tileset test")
    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local layer = map:layerNamed("Layer 0")
    layer:getTexture():setAntiAliasTexParameters()

    layer = map:layerNamed("Layer 1")
    layer:getTexture():setAntiAliasTexParameters()

    layer = map:layerNamed("Layer 2")
    layer:getTexture():setAntiAliasTexParameters()
    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoObjectsTest
--
--------------------------------------------------------------------
local function TMXOrthoObjectsTest()
    local ret = createTileDemoLayer("TMX Ortho object test", "You should see a white box around the 3 platforms")
    local map = CCTMXTiledMap:create("TileMaps/ortho-objects.tmx")
    ret:addChild(map, -1, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    --------cclog("---: Iterating over all the group objets")
    local  group   = map:objectGroupNamed("Object Group 1")
    local  objects = group:getObjects()

    local  dict    = nil
    local  i       = 0
    local  len     = objects:count()

    for i = 0, len-1, 1 do
        dict = tolua.cast(objects:objectAtIndex(i), "CCDictionary")

        if dict == nil then
            break
        end
        --------cclog("object: %x", dict)
    end

    --------cclog("---: Fetching 1 object by name")
    -- local  platform = group:objectNamed("platform")
    --------cclog("platform: %x", platform)
    return ret
end

local function draw()

    local  map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local  group = map:objectGroupNamed("Object Group 1")

    local  objects = group:getObjects()
    local  dict = nil
    local  i = 0
    local  len = objects:count()
    for i = 0, len-1, 1 do
        dict = tolua.cast(objects:objectAtIndex(i), "CCDictionary")

        if dict == nil then
            break
        end

        local key = "x"
        local x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()
        key = "y"
        local y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
        key = "width"
        local width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
        key = "height"
        local height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()

        glLineWidth(3)

        ccDrawLine( ccp(x, y), ccp((x+width), y) )
        ccDrawLine( ccp((x+width), y), ccp((x+width), (y+height)) )
        ccDrawLine( ccp((x+width), (y+height)), ccp(x, (y+height)) )
        ccDrawLine( ccp(x, (y+height)), ccp(x, y) )

        glLineWidth(1)
    end
end

--------------------------------------------------------------------
--
-- TMXIsoObjectsTest
--
--------------------------------------------------------------------

local function TMXIsoObjectsTest()
    local ret = createTileDemoLayer("TMX Iso object test", "You need to parse them manually. See bug #810")
    local  map = CCTMXTiledMap:create("TileMaps/iso-test-objectgroup.tmx")
    ret:addChild(map, -1, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  group = map:objectGroupNamed("Object Group 1")

    --UxMutableArray* objects = group:objects()
    local  objects = group:getObjects()
    --UxMutableDictionary<std:string>* dict
    local  dict = nil
    local  i = 0
    local  len = objects:count()
    for i = 0, len-1, 1 do
        dict = tolua.cast(objects:objectAtIndex(i), "CCDictionary")

        if dict == nil then
            break
        end
        --------cclog("object: %x", dict)
    end
    return ret
end

local function draw()

    local map = tolua.cast(getChildByTag(kTagTileMap), "CCTMXTiledMap")
    local group = map:objectGroupNamed("Object Group 1")

    local  objects = group:getObjects()
    local  dict = nil
    local  i = 0
    local  len = objects:count()
    for i = 0, len-1, 1 do
        dict = tolua.cast(objects:objectAtIndex(i), "CCDictionary")

        if dict == nil then
            break
        end

        local key = "x"
        local x = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("x")):getNumber()
        key = "y"
        local y = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
        key = "width"
        local width = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
        key = "height"
        local height = (tolua.cast(dict:objectForKey(key), "CCString")):intValue()--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()

        glLineWidth(3)

        ccDrawLine( ccp(x,y), ccp(x+width,y) )
        ccDrawLine( ccp(x+width,y), ccp(x+width,y+height) )
        ccDrawLine( ccp(x+width,y+height), ccp(x,y+height) )
        ccDrawLine( ccp(x,y+height), ccp(x,y) )

        glLineWidth(1)
    end
end

--------------------------------------------------------------------
--
-- TMXResizeTest
--
--------------------------------------------------------------------

local function TMXResizeTest()
    local ret = createTileDemoLayer("TMX resize test", "Should not crash. Testing issue #740")
    local  map = CCTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local layer = map:layerNamed("Layer 0")
    local ls = layer:getLayerSize()
    local x = 0
    local y = 0
    for y = 0, ls.height-1, 1 do
        for  x = 0, ls.width-1, 1 do
            layer:setTileGID(1, ccp( x, y ) )
        end
    end
    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoZorder
--
--------------------------------------------------------------------
local function TMXIsoZorder()
    local m_tamara = nil
    local ret = createTileDemoLayer("TMX Iso Zorder", "Sprite should hide behind the trees")
    local map = CCTMXTiledMap:create("TileMaps/iso-test-zorder.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    map:setPosition(ccp(-s.width/2,0))

    m_tamara = CCSprite:create(s_pPathSister1)
    map:addChild(m_tamara, map:getChildren():count() )
    m_tamara:retain()
    local mapWidth = map:getMapSize().width * map:getTileSize().width
    m_tamara:setPosition(CC_POINT_PIXELS_TO_POINTS(ccp( mapWidth/2,0)))
    m_tamara:setAnchorPoint(ccp(0.5,0))

    local  move = CCMoveBy:create(10, ccp(300,250))
    local  back = move:reverse()
    local  arr  = CCArray:create()
    arr:addObject(move)
    arr:addObject(back)
    local  seq = CCSequence:create(arr)
    m_tamara:runAction( CCRepeatForever:create(seq) )

    local function repositionSprite(dt)
        local x,y = m_tamara:getPosition()
        local p = ccp(x, y)
        p = CC_POINT_POINTS_TO_PIXELS(p)
        local map = ret:getChildByTag(kTagTileMap)

        -- there are only 4 layers. (grass and 3 trees layers)
        -- if tamara < 48, z=4
        -- if tamara < 96, z=3
        -- if tamara < 144,z=2

        local newZ = 4 - (p.y / 48)
        newZ = math.max(newZ,0)

        map:reorderChild(m_tamara, newZ)
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(repositionSprite, 0, false)
        elseif event == "exit" then
            if m_tamara ~= nil then
                m_tamara:release()
            end
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoZorder
--
--------------------------------------------------------------------
local function TMXOrthoZorder()
    local m_tamara = nil
    local ret = createTileDemoLayer("TMX Ortho Zorder", "Sprite should hide behind the trees")
    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-zorder.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    m_tamara = CCSprite:create(s_pPathSister1)
    map:addChild(m_tamara,  map:getChildren():count())
    m_tamara:retain()
    m_tamara:setAnchorPoint(ccp(0.5,0))


    local  move = CCMoveBy:create(10, ccp(400,450))
    local  back = move:reverse()
    local  arr = CCArray:create()
    arr:addObject(move)
    arr:addObject(back)
    local  seq = CCSequence:create(arr)
    m_tamara:runAction( CCRepeatForever:create(seq))

    local function repositionSprite(dt)
        local x, y = m_tamara:getPosition()
        local p = ccp(x, y)
        p = CC_POINT_POINTS_TO_PIXELS(p)
        local  map = ret:getChildByTag(kTagTileMap)

        -- there are only 4 layers. (grass and 3 trees layers)
        -- if tamara < 81, z=4
        -- if tamara < 162, z=3
        -- if tamara < 243,z=2

        -- -10: customization for this particular sample
        local newZ = 4 - ( (p.y-10) / 81)
        newZ = math.max(newZ,0)
        map:reorderChild(m_tamara, newZ)
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(repositionSprite, 0, false)
        elseif event == "exit" then
            if m_tamara ~= nil then
                m_tamara:release()
            end
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoVertexZ
--
--------------------------------------------------------------------
local function TMXIsoVertexZ()
    local m_tamara = nil
    local ret = createTileDemoLayer("TMX Iso VertexZ", "Sprite should hide behind the trees")
    local map = CCTMXTiledMap:create("TileMaps/iso-test-vertexz.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    map:setPosition( ccp(-s.width/2,0) )
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    -- can use any CCSprite and it will work OK.
    local  layer = map:layerNamed("Trees")
    m_tamara = layer:tileAt( ccp(29,29) )
    m_tamara:retain()

    local  move = CCMoveBy:create(10, ccpMult( ccp(300,250), 1/CC_CONTENT_SCALE_FACTOR() ) )
    local  back = move:reverse()
    local  arr  = CCArray:create()
    arr:addObject(move)
    arr:addObject(back)
    local  seq = CCSequence:create(arr)
    m_tamara:runAction( CCRepeatForever:create(seq) )
    local function repositionSprite(dt)

        -- tile height is 64x32
        -- map size: 30x30
        local x, y = m_tamara:getPosition()
        local p = ccp(x, y)
        p = CC_POINT_POINTS_TO_PIXELS(p)
        local newZ = -(p.y+32) /16
        m_tamara:setVertexZ( newZ )
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            -- TIP: 2d projection should be used
            CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
            schedulerEntry = scheduler:scheduleScriptFunc(repositionSprite, 0, false)
        elseif event == "exit" then
            -- At exit use any other projection.
            --    CCDirector:sharedDirector():setProjection:kCCDirectorProjection3D)

            if m_tamara ~= nil then
                m_tamara:release()
            end
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoVertexZ
--
--------------------------------------------------------------------
local function TMXOrthoVertexZ()
    local m_tamara = nil
    local ret = createTileDemoLayer("TMX Ortho vertexZ", "Sprite should hide behind the trees")
    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-vertexz.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    -- can use any CCSprite and it will work OK.
    local  layer = map:layerNamed("trees")
    m_tamara = layer:tileAt(ccp(0,11))
    cclog("vertexZ:"..m_tamara:getVertexZ())
    m_tamara:retain()

    local  move = CCMoveBy:create(10, ccpMult( ccp(400,450), 1/CC_CONTENT_SCALE_FACTOR()))
    local  back = move:reverse()
    local  arr  = CCArray:create()
    arr:addObject(move)
    arr:addObject(back)
    local  seq = CCSequence:create(arr)
    m_tamara:runAction( CCRepeatForever:create(seq))

    local function repositionSprite(dt)
        -- tile height is 101x81
        -- map size: 12x12
        local x, y = m_tamara:getPosition()
        local p = ccp(x, y)
        p = CC_POINT_POINTS_TO_PIXELS(p)
        m_tamara:setVertexZ( -( (p.y+81) /81) )
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            -- TIP: 2d projection should be used
            CCDirector:sharedDirector():setProjection(kCCDirectorProjection2D)
            schedulerEntry = scheduler:scheduleScriptFunc(repositionSprite, 0, false)
        elseif event == "exit" then
            -- At exit use any other projection.
            --    CCDirector:sharedDirector():setProjection:kCCDirectorProjection3D)
            if m_tamara ~= nil then
                m_tamara:release()
            end
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoMoveLayer
--
--------------------------------------------------------------------
local function TMXIsoMoveLayer()
    local ret = createTileDemoLayer("TMX Iso Move Layer", "Trees should be horizontally aligned")
    local  map = CCTMXTiledMap:create("TileMaps/iso-test-movelayer.tmx")
    ret:addChild(map, 0, kTagTileMap)

    map:setPosition(ccp(-700,-50))

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    return ret
end


--------------------------------------------------------------------
--
-- TMXOrthoMoveLayer
--
--------------------------------------------------------------------
local function TMXOrthoMoveLayer()
    local ret = createTileDemoLayer("TMX Ortho Move Layer", "Trees should be horizontally aligned")
    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test-movelayer.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    return ret
end

--------------------------------------------------------------------
--
-- TMXTilePropertyTest
--
--------------------------------------------------------------------

local function TMXTilePropertyTest()
    local ret = createTileDemoLayer("TMX Tile Property Test", "In the console you should see tile properties")
    local map = CCTMXTiledMap:create("TileMaps/ortho-tile-property.tmx")
    ret:addChild(map ,0 ,kTagTileMap)
    local i = 0
    for i=1, 20, 1 do
        cclog("GID:%i, Properties:", i)--, map:propertiesForGID(i))
    end
    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoFlipTest
--
--------------------------------------------------------------------

local function TMXOrthoFlipTest()
    local ret = createTileDemoLayer("TMX tile flip test")
    local map = CCTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local i = 0
    for i = 0, map:getChildren():count()-1, 1 do
        local  child = tolua.cast(map:getChildren():objectAtIndex(i), "CCSpriteBatchNode")
        child:getTexture():setAntiAliasTexParameters()
    end

    local  action = CCScaleBy:create(2, 0.5)
    map:runAction(action)
    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoFlipRunTimeTest
--
--------------------------------------------------------------------

local function TMXOrthoFlipRunTimeTest()
    local ret = createTileDemoLayer("TMX tile flip run time test", "in 2 sec bottom left tiles will flip")
    local map = CCTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local i = 0
    for i = 0, map:getChildren():count()-1, 1 do
        local child = tolua.cast(map:getChildren():objectAtIndex(i), "CCSpriteBatchNode")
        child:getTexture():setAntiAliasTexParameters()
    end

    local  action = CCScaleBy:create(2, 0.5)
    map:runAction(action)
    local function flipIt(dt)

        -- local map = tolua.cast(ret:getChildByTag(kTagTileMap), "CCTMXTiledMap")
        -- local layer = map:layerNamed("Layer 0")

        -- --blue diamond
        -- local tileCoord = ccp(1,10)
        -- local flags = 0
        -- local GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
        -- -- Vertical
        -- if( flags & kCCTMXTileVerticalFlag )
        -- flags &= ~kCCTMXTileVerticalFlag
        -- else
        --     flags |= kCCTMXTileVerticalFlag
        --     layer:setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags)


        --     tileCoord = ccp(1,8)
        --     GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
        --     -- Vertical
        --     if( flags & kCCTMXTileVerticalFlag )
        --     flags &= ~kCCTMXTileVerticalFlag
        --     else
        --         flags |= kCCTMXTileVerticalFlag
        --         layer:setTileGID(GID ,tileCoord, (ccTMXTileFlags)flags)


        --         tileCoord = ccp(2,8)
        --         GID = layer:tileGIDAt(tileCoord, (ccTMXTileFlags*)&flags)
        --         -- Horizontal
        --         if( flags & kCCTMXTileHorizontalFlag )
        --         flags &= ~kCCTMXTileHorizontalFlag
        --         else
        --             flags |= kCCTMXTileHorizontalFlag
        --             layer:setTileGID(GID, tileCoord, (ccTMXTileFlags)flags)
    end
    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(flipIt, 1.0, false)
        elseif event == "exit" then
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end
    return ret
end


--------------------------------------------------------------------
--
-- TMXOrthoFromXMLTest
--
--------------------------------------------------------------------

local function TMXOrthoFromXMLTest()
    local ret = createTileDemoLayer("TMX created from XML test")
    local resources = "TileMaps"        -- partial paths are OK as resource paths.
    local file = resources.."/orthogonal-test1.tmx"

    local  str = CCString:createWithContentsOfFile(CCFileUtils:sharedFileUtils():fullPathForFilename(file)):getCString()
    --    CCAssert(str != NULL, "Unable to open file")
    if (str == nil) then
        cclog("Unable to open file")
    end

    local map = CCTMXTiledMap:createWithXML(str ,resources)
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local i = 0
    local len = map:getChildren():count()
    for i = 0, len-1, 1 do
        local  child = tolua.cast(map:getChildren():objectAtIndex(i), "CCSpriteBatchNode")
        child:getTexture():setAntiAliasTexParameters()
    end

    local  action = CCScaleBy:create(2, 0.5)
    map:runAction(action)
    return ret
end

--------------------------------------------------------------------
--
-- TMXBug987
--
--------------------------------------------------------------------
local function TMXBug987()
    local ret = createTileDemoLayer("TMX Bug 987", "You should see an square")
    local map = CCTMXTiledMap:create("TileMaps/orthogonal-test6.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s1 = map:getContentSize()
    cclog("ContentSize: %f, %f", s1.width,s1.height)

    local  childs = map:getChildren()

    local i = 0
    local len = childs:count()
    local pNode = nil
    for i = 0, len-1, 1 do
        pNode = tolua.cast(childs:objectAtIndex(i), "CCTMXLayer")
        if pNode == nil then
            break
        end
        pNode:getTexture():setAntiAliasTexParameters()
    end

    map:setAnchorPoint(ccp(0, 0))
    local layer = map:layerNamed("Tile Layer 1")
    layer:setTileGID(3, ccp(2,2))
    return ret
end

--------------------------------------------------------------------
--
-- TMXBug787
--
--------------------------------------------------------------------
local function TMXBug787()
    local ret = createTileDemoLayer("TMX Bug 787", "You should see a map")
    local map = CCTMXTiledMap:create("TileMaps/iso-test-bug787.tmx")
    ret:addChild(map, 0, kTagTileMap)
    map:setScale(0.25)
    return ret
end

function TileMapTestMain()
    cclog("TileMapTestMain")
    Helper.index = 1
    CCDirector:sharedDirector():setDepthTest(true)
    local scene = CCScene:create()

    Helper.createFunctionTable = {
        TileMapTest,
        TileMapEditTest,
        TMXOrthoTest,
        TMXOrthoTest2,
        TMXOrthoTest3,
        TMXOrthoTest4,
        TMXReadWriteTest,
        TMXHexTest,
        TMXIsoTest,
        TMXIsoTest1,
        TMXIsoTest2,
        TMXUncompressedTest,
        TMXTilesetTest,
        TMXOrthoObjectsTest,
        TMXIsoObjectsTest,
        TMXResizeTest,
        TMXIsoZorder,
        TMXOrthoZorder,
        TMXIsoVertexZ,
        TMXOrthoVertexZ,
        TMXIsoMoveLayer,
        TMXOrthoMoveLayer,
        TMXTilePropertyTest,
        TMXOrthoFlipTest,
        TMXOrthoFlipRunTimeTest,
        TMXOrthoFromXMLTest,
        TMXBug987,
        TMXBug787
    }
    scene:addChild(TileMapTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end
