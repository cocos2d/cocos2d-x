local size = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

local kTagTileMap = 1


local function createTileDemoLayer(title, subtitle)
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    local titleStr = title == nil and "No title" or title
    local subTitleStr = subtitle  == nil and "drag the screen" or subtitle
    Helper.titleLabel:setString(titleStr)
    Helper.subtitleLabel:setString(subTitleStr)

    local function onTouchesMoved(touches, event )
        local diff = touches[1]:getDelta()
        local node = layer:getChildByTag(kTagTileMap)
        local currentPosX, currentPosY= node:getPosition()
        node:setPosition(cc.p(currentPosX + diff.x, currentPosY + diff.y))
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    return layer
end
--------------------------------------------------------------------
--
-- TileMapTest
--
--------------------------------------------------------------------
local function TileMapTest()
    local layer = createTileDemoLayer("TileMapAtlas")

    local  map = cc.TileMapAtlas:create(s_TilesPng,  s_LevelMapTga, 16, 16)
    -- Convert it to "alias" (GL_LINEAR filtering)
    map:getTexture():setAntiAliasTexParameters()

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- If you are not going to use the Map, you can free it now
    -- NEW since v0.7
    map:releaseMap()

    layer:addChild(map, 0, kTagTileMap)

    map:setAnchorPoint( cc.p(0, 0.5) )

    local scale = cc.ScaleBy:create(4, 0.8)
    local scaleBack = scale:reverse()

    local  seq = cc.Sequence:create(scale, scaleBack)

    map:runAction(cc.RepeatForever:create(seq))

    return layer
end

--------------------------------------------------------------------
--
-- TileMapEditTest
--
--------------------------------------------------------------------
local function TileMapEditTest()
    local layer = createTileDemoLayer("Editable TileMapAtlas")
    local  map = cc.TileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
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

        local  tilemap = layer:getChildByTag(kTagTileMap)

        --
        -- For example you can iterate over all the tiles
        -- using this code, but try to avoid the iteration
        -- over all your tiles in every frame. It's very expensive
        --    for(int x=0 x < tilemap.tgaInfo:width x++)
        --        for(int y=0 y < tilemap.tgaInfo:height y++)
        --            Color3B c =[tilemap getTileAt:local Make(x,y))
        --            if( c.r != 0 )
        --                --------cclog("%d,%d = %d", x,y,c.r)
        --            end
        --        end
        --    end

        -- NEW since v0.7
        local c = tilemap:getTileAt(cc.p(13,21))
        c.r = c.r + 1
        c.r = c.r % 50

        if( c.r==0) then
            c.r=1
        end
        -- NEW since v0.7
        tilemap:setTile(c, cc.p(13,21) )
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

    map:setAnchorPoint( cc.p(0, 0) )
    map:setPosition( cc.p(-20,-200) )

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
    --local  color = cc.LayerColor:create( cc.c4b(64,64,64,255) )
    --addChild(color, -1)

    local  map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
    layer:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  scale = cc.ScaleBy:create(10, 0.1)
    local  back  = scale:reverse()
    local  seq   = cc.Sequence:create(scale, back)
    local  repeatAction = cc.RepeatForever:create(seq)
    map:runAction(repeatAction)

    local function onNodeEvent(event)
        if event == "enter" then
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION3_D )
        elseif event == "exit" then
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION_DEFAULT )
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

    local  map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test1.tmx")
    layer:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    map:runAction( cc.ScaleBy:create(2, 0.5) )
    return layer
end

--------------------------------------------------------------------
--
-- TMXOrthoTest3
--
--------------------------------------------------------------------
local function TMXOrthoTest3()
    local layer = createTileDemoLayer("TMX anchorPoint test")
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test3.tmx")
    layer:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    map:setScale(0.2)
    map:setAnchorPoint( cc.p(0.5, 0.5) )
    return layer
end


--------------------------------------------------------------------
--
-- TMXOrthoTest4
--
--------------------------------------------------------------------
local function TMXOrthoTest4()
    local ret = createTileDemoLayer("TMX width/height test")
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test4.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s1 = map:getContentSize()
    cclog("ContentSize: %f, %f", s1.width,s1.height)

    map:setAnchorPoint(cc.p(0, 0))

    local layer  = map:getLayer("Layer 0")
    local s      = layer:getLayerSize()

    local sprite = layer:getTileAt(cc.p(0,0))
    sprite:setScale(2)
    sprite       = layer:getTileAt(cc.p(s.width-1,0))
    sprite:setScale(2)
    sprite       = layer:getTileAt(cc.p(0,s.height-1))
    sprite:setScale(2)
    sprite       = layer:getTileAt(cc.p(s.width-1,s.height-1))
    sprite:setScale(2)

    local schedulerEntry = nil

    local function removeSprite(dt)
        scheduler:unscheduleScriptEntry(schedulerEntry)
        schedulerEntry = nil
        local map = ret:getChildByTag(kTagTileMap)
        local  layer0 = map:getLayer("Layer 0")
        local s = layer0:getLayerSize()

        local  sprite = layer0:getTileAt(cc.p(s.width-1,0))
        layer0:removeChild(sprite, true)
        local  sprite2 = layer0:getTileAt(cc.p(s.width-1, s.height - 1))
        local  sprite3 = layer0:getTileAt(cc.p(2, s.height - 1))
        layer0:removeChild(sprite3, true)
        layer0:removeChild(sprite2, true)
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
    local  map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test2.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)


    local  layer = map:getLayer("Layer 0")
    map:setScale( 1 )

    local tile0 = layer:getTileAt(cc.p(1,63))
    local tile1 = layer:getTileAt(cc.p(2,63))
    local tile2 = layer:getTileAt(cc.p(3,62))--cc.p(1,62))
    local tile3 = layer:getTileAt(cc.p(2,62))
    tile0:setAnchorPoint( cc.p(0.5, 0.5) )
    tile1:setAnchorPoint( cc.p(0.5, 0.5) )
    tile2:setAnchorPoint( cc.p(0.5, 0.5) )
    tile3:setAnchorPoint( cc.p(0.5, 0.5) )

    local  move = cc.MoveBy:create(0.5, cc.p(0,160))
    local  rotate = cc.RotateBy:create(2, 360)
    local  scale = cc.ScaleBy:create(2, 5)
    local  opacity = cc.FadeOut:create(2)
    local  fadein = cc.FadeIn:create(2)
    local  scaleback = cc.ScaleTo:create(1, 1)

    local function removeSprite(sender)
        --------cclog("removing tile: %x", sender)
        local node = sender
        if nil == node then
            print("Errro node is nil")
        end
        local p = node:getParent()

        if p ~= nil then
            p:removeChild(node, true)
        end
        ----------cclog("atlas quantity: %d", p:textureAtlas():totalQuads())
    end

    local finish = cc.CallFunc:create(removeSprite)
    local  seq0 = cc.Sequence:create(move, rotate, scale, opacity, fadein, scaleback, finish)
    local  seq1 = seq0:clone()
    local  seq2 = seq0:clone()
    local  seq3 = seq0:clone()

    tile0:runAction(seq0)
    tile1:runAction(seq1)
    tile2:runAction(seq2)
    tile3:runAction(seq3)


    m_gid = layer:getTileGIDAt(cc.p(0,63))
    --------cclog("Tile GID at:(0,63) is: %d", m_gid)
    local updateColScheduler     = nil
    local repainWithGIDScheduler = nil
    local removeTilesScheduler   = nil

    local function updateCol(dt)

        local  map = ret:getChildByTag(kTagTileMap)
        local layer = map:getChildByTag(0)

        --------cclog("++++atlas quantity: %d", layer:textureAtlas():getTotalQuads())
        --------cclog("++++children: %d", layer:getChildren():count() )


        local s = layer:getLayerSize()
        local y = 0
        for y=0, s.height-1, 1 do
            layer:setTileGID(m_gid2, cc.p(3, y))
        end

        m_gid2 = (m_gid2 + 1) % 80
    end

    local function repaintWithGID(dt)
        --    unschedule:_cmd)
        local  map = ret:getChildByTag(kTagTileMap)
        local layer = map:getChildByTag(0)

        local s = layer:getLayerSize()
        local x = 0
        for x=0, s.width-1, 1 do
            local y = s.height-1
            local tmpgid = layer:getTileGIDAt( cc.p(x, y) )
            layer:setTileGID(tmpgid+1, cc.p(x, y))
        end
    end

    local function removeTiles(dt)
        scheduler:unscheduleScriptEntry(removeTilesScheduler)
        removeTilesScheduler = nil
        local  map = ret:getChildByTag(kTagTileMap)
        local layer = map:getChildByTag(0)
        local s = layer:getLayerSize()
        local y = 0
        for y=0, s.height-1, 1 do
            layer:removeTileAt( cc.p(5.0, y) )
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
    local  color = cc.LayerColor:create( cc.c4b(64,64,64,255) )
    ret:addChild(color, -1)

    local  map = cc.TMXTiledMap:create("TileMaps/hexa-test.tmx")
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
    local  color = cc.LayerColor:create( cc.c4b(64,64,64,255) )
    ret:addChild(color, -1)

    local  map = cc.FastTMXTiledMap:create("TileMaps/iso-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    -- move map to the center of the screen
    local ms = map:getMapSize()
    local ts = map:getTileSize()
    map:runAction( cc.MoveTo:create(1.0, cc.p( -ms.width * ts.width/2, -ms.height * ts.height/2 )) )
    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoTest1
--
--------------------------------------------------------------------
local function TMXIsoTest1()
    local ret = createTileDemoLayer("TMX Isometric test + anchorPoint")
    local  color = cc.LayerColor:create( cc.c4b(64,64,64,255) )
    ret:addChild(color, -1)

    local map = cc.FastTMXTiledMap:create("TileMaps/iso-test1.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    map:setAnchorPoint(cc.p(0.5, 0.5))
    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoTest2
--
--------------------------------------------------------------------
local function TMXIsoTest2()
    local ret = createTileDemoLayer("TMX Isometric test 2")
    local  color = cc.LayerColor:create( cc.c4b(64,64,64,255) )
    ret:addChild(color, -1)

    local map = cc.FastTMXTiledMap:create("TileMaps/iso-test2.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- move map to the center of the screen
    local ms = map:getMapSize()
    local ts = map:getTileSize()
    map:runAction( cc.MoveTo:create(1.0, cc.p( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))
    return ret
end

--------------------------------------------------------------------
--
-- TMXUncompressedTest
--
--------------------------------------------------------------------
local function TMXUncompressedTest()
    local ret = createTileDemoLayer("TMX Uncompressed test")
    local  color = cc.LayerColor:create( cc.c4b(64,64,64,255) )
    ret:addChild(color, -1)

    local map = cc.FastTMXTiledMap:create("TileMaps/iso-test2-uncompressed.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- move map to the center of the screen
    local ms = map:getMapSize()
    local ts = map:getTileSize()
    map:runAction(cc.MoveTo:create(1.0, cc.p( -ms.width * ts.width/2, -ms.height * ts.height/2 ) ))

    return ret
end

--------------------------------------------------------------------
--
-- TMXTilesetTest
--
--------------------------------------------------------------------
local function TMXTilesetTest()
    local ret = createTileDemoLayer("TMX Tileset test")
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoObjectsTest
--
--------------------------------------------------------------------
local function TMXOrthoObjectsTest()
    local ret = createTileDemoLayer("TMX Ortho object test", "You should see a white box around the 3 platforms")
    local map = cc.FastTMXTiledMap:create("TileMaps/ortho-objects.tmx")
    ret:addChild(map, -1, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    
    local drawNode = cc.DrawNode:create()
    map:addChild(drawNode, 10)

    --------cclog("---: Iterating over all the group objects")
    local  group   = map:getObjectGroup("Object Group 1")
    local  objects = group:getObjects()

    local  dict    = nil
    local  i       = 0
    local  len     = table.getn(objects)

    for i = 0, len-1, 1 do
        dict = objects[i + 1]

        if dict == nil then
            break
        end
        --------cclog("object: %x", dict)
        
        local key = "x"
        local x = dict["x"]
        key = "y"
        local y = dict["y"]--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
        key = "width"
        local width = dict["width"]--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
        key = "height"
        local height = dict["height"]--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()
        
        local color = cc.c4f(1,1,1,1)
        drawNode:drawLine( cc.p(x, y), cc.p((x+width), y), color)
        drawNode:drawLine( cc.p((x+width), y), cc.p((x+width), (y+height)), color)
        drawNode:drawLine( cc.p((x+width), (y+height)), cc.p(x, (y+height)), color)
        drawNode:drawLine( cc.p(x, (y+height)), cc.p(x, y), color)
    end

    --------cclog("---: Fetching 1 object by name")
    -- local  platform = group:objectNamed("platform")
    --------cclog("platform: %x", platform)
    
    

    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoObjectsTest
--
--------------------------------------------------------------------

local function TMXIsoObjectsTest()
    local ret = createTileDemoLayer("TMX Iso object test", "You need to parse them manually. See bug #810")
    local  map = cc.FastTMXTiledMap:create("TileMaps/iso-test-objectgroup.tmx")
    ret:addChild(map, -1, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    
    local drawNode = cc.DrawNode:create()
    map:addChild(drawNode, 10)

    local  group = map:getObjectGroup("Object Group 1")

    --UxMutableArray* objects = group:objects()
    local  objects = group:getObjects()
    --UxMutableDictionary<std:string>* dict
    local  dict = nil
    local  i = 0
    local  len = table.getn(objects)
    for i = 0, len-1, 1 do
        dict = tolua.cast(objects[i + 1], "cc.Dictionary")

        if dict == nil then
            break
        end
        --------cclog("object: %x", dict)
        
        local key = "x"
        local x = dict["x"]
        key = "y"
        local y = dict["y"]--dynamic_cast<NSNumber*>(dict:objectForKey("y")):getNumber()
        key = "width"
        local width = dict["width"]--dynamic_cast<NSNumber*>(dict:objectForKey("width")):getNumber()
        key = "height"
        local height = dict["height"]--dynamic_cast<NSNumber*>(dict:objectForKey("height")):getNumber()
        
        local color = cc.c4f(1,1,1,1)
        drawNode:drawLine( cc.p(x, y), cc.p((x+width), y), color)
        drawNode:drawLine( cc.p((x+width), y), cc.p((x+width), (y+height)), color)
        drawNode:drawLine( cc.p((x+width), (y+height)), cc.p(x, (y+height)), color)
        drawNode:drawLine( cc.p(x, (y+height)), cc.p(x, y), color)
    end
    return ret
end

--------------------------------------------------------------------
--
-- TMXResizeTest
--
--------------------------------------------------------------------

local function TMXResizeTest()
    local ret = createTileDemoLayer("TMX resize test", "Should not crash. Testing issue #740")
    local  map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test5.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local layer = map:getLayer("Layer 0")
    local ls = layer:getLayerSize()
    local x = 0
    local y = 0
    for y = 0, ls.height-1, 1 do
        for  x = 0, ls.width-1, 1 do
            layer:setTileGID(1, cc.p( x, y ) )
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
    local map = cc.FastTMXTiledMap:create("TileMaps/iso-test-zorder.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)
    map:setPosition(cc.p(-s.width/2,0))

    m_tamara = cc.Sprite:create(s_pPathSister1)
    map:addChild(m_tamara, table.getn(map:getChildren()))
    m_tamara:retain()
    local mapWidth = map:getMapSize().width * map:getTileSize().width
    m_tamara:setPosition(CC_POINT_PIXELS_TO_POINTS(cc.p( mapWidth/2,0)))
    m_tamara:setAnchorPoint(cc.p(0.5,0))

    local  move = cc.MoveBy:create(10, cc.p(300,250))
    local  back = move:reverse()
    local  seq = cc.Sequence:create(move, back)
    m_tamara:runAction( cc.RepeatForever:create(seq) )

    local function repositionSprite(dt)
        local p = cc.p(m_tamara:getPosition())
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
            cc.Director:getInstance():getRenderer():setDepthTest(false)
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
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test-zorder.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    m_tamara = cc.Sprite:create(s_pPathSister1)
    map:addChild(m_tamara,  table.getn(map:getChildren()))
    m_tamara:retain()
    m_tamara:setAnchorPoint(cc.p(0.5,0))


    local  move = cc.MoveBy:create(10, cc.p(400,450))
    local  back = move:reverse()
    local  seq = cc.Sequence:create(move, back)
    m_tamara:runAction( cc.RepeatForever:create(seq))

    local function repositionSprite(dt)
        local p = cc.p(m_tamara:getPosition())
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
    local map = cc.FastTMXTiledMap:create("TileMaps/iso-test-vertexz.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    map:setPosition( cc.p(-s.width/2,0) )
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    -- can use any cc.Sprite and it will work OK.
    local  layer = map:getLayer("Trees")
    m_tamara = layer:getTileAt( cc.p(29,29) )
    m_tamara:retain()

    local  move = cc.MoveBy:create(10, cc.pMul( cc.p(300,250), 1/CC_CONTENT_SCALE_FACTOR() ) )
    local  back = move:reverse()
    local  seq = cc.Sequence:create(move, back)
    m_tamara:runAction( cc.RepeatForever:create(seq) )
    local function repositionSprite(dt)

        -- tile height is 64x32
        -- map size: 30x30
        local p = cc.p(m_tamara:getPosition())
        p = CC_POINT_POINTS_TO_PIXELS(p)
        local newZ = -(p.y+32) /16
        m_tamara:setPositionZ( newZ )
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            -- TIP: 2d projection should be used
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION2_D )
            schedulerEntry = scheduler:scheduleScriptFunc(repositionSprite, 0, false)
            cc.Director:getInstance():getRenderer():setDepthTest(true)
            cc.Director:getInstance():getRenderer():setDepthWrite(true)
        elseif event == "exit" then
            -- At exit use any other projection.
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION_DEFAULT )
            if m_tamara ~= nil then
                m_tamara:release()
            end
            scheduler:unscheduleScriptEntry(schedulerEntry)
            cc.Director:getInstance():getRenderer():setDepthTest(false)
            cc.Director:getInstance():getRenderer():setDepthWrite(false)
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
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test-vertexz.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    -- because I'm lazy, I'm reusing a tile as an sprite, but since this method uses vertexZ, you
    -- can use any cc.Sprite and it will work OK.
    local  layer = map:getLayer("trees")
    m_tamara = layer:getTileAt(cc.p(0,11))
    cclog("vertexZ:"..m_tamara:getPositionZ())
    m_tamara:retain()

    local  move = cc.MoveBy:create(10, cc.pMul( cc.p(400,450), 1/CC_CONTENT_SCALE_FACTOR()))
    local  back = move:reverse()
    local  seq = cc.Sequence:create(move, back)
    m_tamara:runAction( cc.RepeatForever:create(seq))

    local function repositionSprite(dt)
        -- tile height is 101x81
        -- map size: 12x12
        local p = cc.p(m_tamara:getPosition())
        p = CC_POINT_POINTS_TO_PIXELS(p)
        m_tamara:setPositionZ( -( (p.y+81) /81) )
    end

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            -- TIP: 2d projection should be used
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION2_D )
            schedulerEntry = scheduler:scheduleScriptFunc(repositionSprite, 0, false)
            cc.Director:getInstance():getRenderer():setDepthTest(true)
            cc.Director:getInstance():getRenderer():setDepthWrite(true)
        elseif event == "exit" then
            -- At exit use any other projection.
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION_DEFAULT )
            if m_tamara ~= nil then
                m_tamara:release()
            end
            scheduler:unscheduleScriptEntry(schedulerEntry)
            cc.Director:getInstance():getRenderer():setDepthTest(false)
            cc.Director:getInstance():getRenderer():setDepthWrite(false)
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- TMXIsoMoveLayer
--
--------------------------------------------------------------------
local function TMXIsoMoveLayer()
    local ret = createTileDemoLayer("TMX Iso Move Layer", "Trees should be horizontally aligned")
    local  map = cc.FastTMXTiledMap:create("TileMaps/iso-test-movelayer.tmx")
    ret:addChild(map, 0, kTagTileMap)

    map:setPosition(cc.p(-700,-50))

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
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test-movelayer.tmx")
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
    local map = cc.TMXTiledMap:create("TileMaps/ortho-tile-property.tmx")
    ret:addChild(map ,0 ,kTagTileMap)
    local i = 0
    for i=1, 20, 1 do
        cclog("GID:%i, Properties:", i)--, map:getPropertiesForGID(i))
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
    local map = cc.FastTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  action = cc.ScaleBy:create(2, 0.5)
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
    local map = cc.FastTMXTiledMap:create("TileMaps/ortho-rotation-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  action = cc.ScaleBy:create(2, 0.5)
    map:runAction(action)
    local function flipIt(dt)

        local map = ret:getChildByTag(kTagTileMap)
        local layer = map:getLayer("Layer 0")
        
        local tileCoord = cc.p(1, 10)
        local flags = 0
        local GID, flags = layer:getTileGIDAt(tileCoord, flags)
        if 0 ~= bit._and(flags, cc.TMX_TILE_VERTICAL_FLAG) then
            flags = bit._and(flags, bit._not(cc.TMX_TILE_VERTICAL_FLAG))
        else
            flags = bit._or(flags, cc.TMX_TILE_VERTICAL_FLAG)
        end
        layer:setTileGID(GID, tileCoord, flags)

        tileCoord = cc.p(1,8)    
        GID, flags = layer:getTileGIDAt(tileCoord, flags)
        if 0 ~= bit._and(flags, cc.TMX_TILE_VERTICAL_FLAG) then 
            flags = bit._and(flags, bit._not(cc.TMX_TILE_VERTICAL_FLAG))
        else
            flags = bit._or(flags, cc.TMX_TILE_VERTICAL_FLAG)
        end 
        layer:setTileGID(GID ,tileCoord, flags)

        tileCoord = cc.p(2,8)
        GID, flags = layer:getTileGIDAt(tileCoord, flags)
        -- Horizontal
        if 0~= bit._and(flags, cc.TMX_TILE_HORIZONTAL_FLAG) then
            flags = bit._and(flags, bit._not(cc.TMX_TILE_HORIZONTAL_FLAG))
        else
            flags = bit._or(flags, cc.TMX_TILE_HORIZONTAL_FLAG)
        end 
        layer:setTileGID(GID, tileCoord, flags) 
    end
    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(flipIt, 1.0, false)
        elseif event == "exit" then
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    ret:registerScriptHandler(onNodeEvent)

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

    local  str = cc.FileUtils:getInstance():getStringFromFile(file)
    --    cc.ASSERT(str != NULL, "Unable to open file")
    if (str == nil) then
        cclog("Unable to open file")
    end

    local map = cc.FastTMXTiledMap:createWithXML(str ,resources)
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    local  action = cc.ScaleBy:create(2, 0.5)
    map:runAction(action)
    return ret
end

--------------------------------------------------------------------
--
-- TMXOrthoXMLFormatTest
--
--------------------------------------------------------------------

local function TMXOrthoXMLFormatTest()
    local ret = createTileDemoLayer("you should see blue, green and yellow in console.")

    local map = cc.FastTMXTiledMap:create("TileMaps/xml-test.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local s = map:getContentSize()
    cclog("ContentSize: %f, %f", s.width,s.height)

    for i = 24, 26 do
        cclog("GID:%d, Properties:%s", i,  map:getPropertiesForGID(i)["name"])
    end

    local  action = cc.ScaleBy:create(2, 0.5)
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
    local map = cc.FastTMXTiledMap:create("TileMaps/orthogonal-test6.tmx")
    ret:addChild(map, 0, kTagTileMap)

    local  s1 = map:getContentSize()
    cclog("ContentSize: %f, %f", s1.width,s1.height)

    map:setAnchorPoint(cc.p(0, 0))
    local layer = map:getLayer("Tile Layer 1")
    layer:setTileGID(3, cc.p(2,2))
    return ret
end

--------------------------------------------------------------------
--
-- TMXBug787
--
--------------------------------------------------------------------
local function TMXBug787()
    local ret = createTileDemoLayer("TMX Bug 787", "You should see a map")
    local map = cc.FastTMXTiledMap:create("TileMaps/iso-test-bug787.tmx")
    ret:addChild(map, 0, kTagTileMap)
    map:setScale(0.25)
    return ret
end

function FastTiledMapTestMain()
    cclog("FastTiledMapTestMain")
    Helper.index = 1
    local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        TMXIsoZorder,
        TMXOrthoZorder,
        TMXIsoVertexZ,
        TMXOrthoVertexZ,
        TMXOrthoTest,
        TMXOrthoTest2,
        TMXOrthoTest3,
        TMXOrthoTest4,
        TMXIsoTest,
        TMXIsoTest1,
        TMXIsoTest2,
        TMXUncompressedTest,
     -- TMXHexTest,
        TMXReadWriteTest,
        TMXTilesetTest,
        TMXOrthoObjectsTest,
        TMXIsoObjectsTest,
        TMXResizeTest,
        TMXIsoMoveLayer,
        TMXOrthoMoveLayer,
        TMXOrthoFlipTest,
        TMXOrthoFlipRunTimeTest,
        TMXOrthoFromXMLTest,
        TMXOrthoXMLFormatTest,
     -- TileMapTest,
     -- TileMapEditTest,
        TMXBug987,
        TMXBug787,
     -- TMXGIDObjectsTestNew,
    }
    Helper.index = 1
    
    scene:addChild(TMXIsoZorder())
    scene:addChild(CreateBackMenuItem())
    return scene
end
