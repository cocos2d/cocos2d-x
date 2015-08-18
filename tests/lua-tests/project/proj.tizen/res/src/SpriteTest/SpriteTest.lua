local size = cc.Director:getInstance():getWinSize()
local kTagTileMap = 1
local kTagSpriteBatchNode = 1
local kTagNode = 2
local kTagAnimation1 = 1
local kTagSpriteLeft = 2
local kTagSpriteRight = 2

local kTagSprite1 = 0
local kTagSprite2 = 1
local kTagSprite3 = 2
local kTagSprite4 = 3
local kTagSprite5 = 4
local kTagSprite6 = 5
local kTagSprite7 = 6
local kTagSprite8 = 7

local testLayer  = nil
local entry      = nil

--------------------------------------------
---- test sprite1
--------------------------------------------
local Sprite1 = {}
Sprite1.__index = Sprite1

function Sprite1.addNewSpriteWithCoords(layer, point)
    local idx = math.floor(math.random() * 1400 / 100)
    local x = math.floor(math.mod(idx,5) * 85)
    local y = math.floor(idx / 5) * 121

    local sprite = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(x,y,85,121) )
    layer:addChild( sprite )

    sprite:setPosition( cc.p(point.x, point.y) )

    local action = nil
    local random = math.random()
    cclog("random = " .. random)
    if( random < 0.20 ) then
        action = cc.ScaleBy:create(3, 2)
    elseif(random < 0.40) then
        action = cc.RotateBy:create(3, 360)
    elseif( random < 0.60) then
        action = cc.Blink:create(1, 3)
    elseif( random < 0.8 ) then
        action = cc.TintBy:create(2, 0, -255, -255)
    else 
        action = cc.FadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = cc.Sequence:create( action, action_back)

    sprite:runAction( cc.RepeatForever:create(seq) )
end

function Sprite1.onTouchesEnd(touches, event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        Sprite1.addNewSpriteWithCoords(Helper.currentLayer, location)
    end
end

function Sprite1.create()
    cclog("sprite1")
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Sprite1.addNewSpriteWithCoords(layer, cc.p(size.width/2, size.height/2))

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(Sprite1.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    Helper.titleLabel:setString("Sprite (tap screen)")

    return layer
end

--------------------------------------------
---- test SpriteBatchNode
--------------------------------------------
local SpriteBatchNode1 = {}
SpriteBatchNode1.__index = SpriteBatchNode1

function SpriteBatchNode1.addNewSpriteWithCoords(layer, point)
    local BatchNode = layer:getChildByTag( kTagSpriteBatchNode )
    local idx = math.floor(math.random() * 1400 / 100)
    local x = math.floor(math.mod(idx,5) * 85)
    local y = math.floor(idx / 5) * 121

    local sprite = cc.Sprite:createWithTexture(BatchNode:getTexture(), cc.rect(x,y,85,121) )
    layer:addChild( sprite )

    sprite:setPosition( cc.p(point.x, point.y) )

    local action = nil
    local random = math.random()
    cclog("random = " .. random)
    if( random < 0.20 ) then
        action = cc.ScaleBy:create(3, 2)
    elseif(random < 0.40) then
        action = cc.RotateBy:create(3, 360)
    elseif( random < 0.60) then
        action = cc.Blink:create(1, 3)
    elseif( random < 0.8 ) then
        action = cc.TintBy:create(2, 0, -255, -255)
    else 
        action = cc.FadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = cc.Sequence:create( action, action_back)

    sprite:runAction( cc.RepeatForever:create(seq) )
end

function SpriteBatchNode1.onTouchesEnd(touches,event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        SpriteBatchNode1.addNewSpriteWithCoords(Helper.currentLayer, location)
    end
end

function SpriteBatchNode1.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    local BatchNode = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 50)
    layer:addChild(BatchNode, 0, kTagSpriteBatchNode)

    SpriteBatchNode1.addNewSpriteWithCoords(layer, cc.p(size.width/2, size.height/2))

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(Sprite1.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    Helper.titleLabel:setString("SpriteBatchNode (tap screen)")

    return layer
end

--------------------------------------
----  SpriteColorOpacity
--------------------------------------
local SpriteColorOpacity = {}
SpriteColorOpacity.__index = SpriteColorOpacity
SpriteColorOpacity.entry = nil

function SpriteColorOpacity.setLayerSprite(layer)
    local sprite1 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*0, 121*1, 85, 121))
    local sprite2 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*1, 121*1, 85, 121))
    local sprite3 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*2, 121*1, 85, 121))
    local sprite4 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*3, 121*1, 85, 121))
    
    local sprite5 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*0, 121*1, 85, 121))
    local sprite6 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*1, 121*1, 85, 121))
    local sprite7 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*2, 121*1, 85, 121))
    local sprite8 = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*3, 121*1, 85, 121))
    
    local s = cc.Director:getInstance():getWinSize()
    sprite1:setPosition( cc.p( (s.width/5)*1, (s.height/3)*1) )
    sprite2:setPosition( cc.p( (s.width/5)*2, (s.height/3)*1) )
    sprite3:setPosition( cc.p( (s.width/5)*3, (s.height/3)*1) )
    sprite4:setPosition( cc.p( (s.width/5)*4, (s.height/3)*1) )
    sprite5:setPosition( cc.p( (s.width/5)*1, (s.height/3)*2) )
    sprite6:setPosition( cc.p( (s.width/5)*2, (s.height/3)*2) )
    sprite7:setPosition( cc.p( (s.width/5)*3, (s.height/3)*2) )
    sprite8:setPosition( cc.p( (s.width/5)*4, (s.height/3)*2) )
    
    local action = cc.FadeIn:create(2)
    local action_back = action:reverse()
    local fade = cc.RepeatForever:create( cc.Sequence:create( action, action_back) )
    
    local tintred = cc.TintBy:create(2, 0, -255, -255)
    local tintred_back = tintred:reverse()
    local red = cc.RepeatForever:create( cc.Sequence:create( tintred, tintred_back) )
    
    local tintgreen = cc.TintBy:create(2, -255, 0, -255)
    local tintgreen_back = tintgreen:reverse()
    local green = cc.RepeatForever:create( cc.Sequence:create( tintgreen, tintgreen_back) )
    
    local tintblue = cc.TintBy:create(2, -255, -255, 0)
    local tintblue_back = tintblue:reverse()
    local blue = cc.RepeatForever:create( cc.Sequence:create( tintblue, tintblue_back) )
    
    sprite5:runAction(red)
    sprite6:runAction(green)
    sprite7:runAction(blue)
    sprite8:runAction(fade)
    
    layer:addChild(sprite1, 0, kTagSprite1)
    layer:addChild(sprite2, 0, kTagSprite2)
    layer:addChild(sprite3, 0, kTagSprite3)
    layer:addChild(sprite4, 0, kTagSprite4)
    layer:addChild(sprite5, 0, kTagSprite5)
    layer:addChild(sprite6, 0, kTagSprite6)
    layer:addChild(sprite7, 0, kTagSprite7)
    layer:addChild(sprite8, 0, kTagSprite8)
    
    layer:registerScriptHandler(SpriteColorOpacity.onEnterOrExit)
end

function SpriteColorOpacity.onEnterOrExit(tag)
    if tag == "enter" then
        SpriteColorOpacity.onEnter()
    elseif tag == "exit" then
        SpriteColorOpacity.onExit()
    end
end

function SpriteColorOpacity.removeAndAddSprite(dt)
    local sprite = Helper.currentLayer:getChildByTag(kTagSprite5)    
    sprite:retain()
    
    Helper.currentLayer:removeChild(sprite, false)
    Helper.currentLayer:addChild(sprite, 0, kTagSprite5)
    
    sprite:release()
end

function SpriteColorOpacity.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    SpriteColorOpacity.setLayerSprite(layer)
    layer:registerScriptHandler(SpriteColorOpacity.onEnterOrExit)
    Helper.titleLabel:setString("Sprite: Color & Opacity")

    return layer
end

--------------------------------------
----  SpriteFrameTest
--------------------------------------
local SpriteFrameTest = {}
SpriteFrameTest.__index = SpriteFrameTest
SpriteFrameTest.entry = nil
SpriteFrameTest.m_pSprite1 = nil
SpriteFrameTest.m_pSprite2 = nil
SpriteFrameTest.m_nCounter = 0

function SpriteFrameTest.onEnter()
    local s = cc.Director:getInstance():getWinSize()
    local cache = cc.SpriteFrameCache:getInstance()

    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    cache:addSpriteFrames("animations/grossini_blue.plist", "animations/grossini_blue.png")

    SpriteFrameTest.m_pSprite1 = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
    SpriteFrameTest.m_pSprite1:setPosition( cc.p( s.width/2-80, s.height/2) )

    local spritebatch = cc.SpriteBatchNode:create("animations/grossini.png")
    spritebatch:addChild(SpriteFrameTest.m_pSprite1)
    Helper.currentLayer:addChild(spritebatch)

    local animFrames = {}
    for i = 1,14 do 
        local frame = cache:getSpriteFrame( string.format("grossini_dance_%02d.png", i) )
        animFrames[i] = frame
    end

    local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
    SpriteFrameTest.m_pSprite1:runAction( cc.RepeatForever:create( cc.Animate:create(animation) ) )

    SpriteFrameTest.m_pSprite1:setFlipX(false)
    SpriteFrameTest.m_pSprite1:setFlipY(false)

    SpriteFrameTest.m_pSprite2 = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
    SpriteFrameTest.m_pSprite2:setPosition( cc.p( s.width/2 + 80, s.height/2) )
    Helper.currentLayer:addChild(SpriteFrameTest.m_pSprite2)

    local moreFrames = {}
    for i = 1,14 do
        local frame = cache:getSpriteFrame(string.format("grossini_dance_gray_%02d.png",i))
        moreFrames[i] = frame
    end

    for i = 1,4 do
        local frame = cache:getSpriteFrame(string.format("grossini_blue_%02d.png",i))
        moreFrames[14 + i] = frame
    end

    --contact
    for i = 1, 14 do
        moreFrames[18 + i] =  animFrames[i]
    end

    
    local animMixed = cc.Animation:createWithSpriteFrames(moreFrames, 0.3)

    SpriteFrameTest.m_pSprite2:runAction(cc.RepeatForever:create( cc.Animate:create(animMixed) ) )

    SpriteFrameTest.m_pSprite2:setFlipX(false)
    SpriteFrameTest.m_pSprite2:setFlipY(false)


    performWithDelay(Helper.currentLayer,SpriteFrameTest.startIn05Secs, 0.5)
    SpriteFrameTest.m_nCounter = 0
end

function SpriteFrameTest.onExit()
    local cache = cc.SpriteFrameCache:getInstance()
    cache:removeSpriteFramesFromFile("animations/grossini.plist")
    cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    cache:removeSpriteFramesFromFile("animations/grossini_blue.plist")
end

function SpriteFrameTest.startIn05Secs(dt)
    schedule(Helper.currentLayer,SpriteFrameTest.flipSprites, 1)
end

function SpriteFrameTest.flipSprites(dt)
    SpriteFrameTest.m_nCounter = SpriteFrameTest.m_nCounter  + 1

    local fx = false
    local fy = false
    local i  = math.mod(SpriteFrameTest.m_nCounter, 4)

    if(i == 0) then
        fx = false
        fy = false
    elseif i == 1 then
        fx = true
        fy = false
    elseif i == 2 then
        fx = false
        fy = true
    elseif i == 3 then
        fx = true
        fy = true
    end

    SpriteFrameTest.m_pSprite1:setFlipX(fx)
    SpriteFrameTest.m_pSprite1:setFlipY(fy)
    SpriteFrameTest.m_pSprite2:setFlipX(fx)
    SpriteFrameTest.m_pSprite2:setFlipY(fy)
end


function SpriteFrameTest.onEnterOrExit(tag)
	if tag == "enter" then
		SpriteFrameTest.onEnter()
	elseif tag == "exit" then
		SpriteFrameTest.onExit()
	end
end

function SpriteFrameTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    layer:registerScriptHandler(SpriteFrameTest.onEnterOrExit)
    Helper.titleLabel:setString("Sprite vs. SpriteBatchNode animation")

    return layer
end

---------------------------------------------------------------------
--
-- SpriteFrameAliasNameTest
--
--------------------------------------------------------------------
local SpriteFrameAliasNameTest = {}
SpriteFrameAliasNameTest.__index = SpriteFrameAliasNameTest

function SpriteFrameAliasNameTest.onEnter()
    local s = cc.Director:getInstance():getWinSize()

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini-aliases.plist", "animations/grossini-aliases.png")

    local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
    sprite:setPosition(cc.p(s.width * 0.5, s.height * 0.5))

    local spriteBatch = cc.SpriteBatchNode:create("animations/grossini-aliases.png")
    cclog("spriteBatch = " .. tostring(tolua.isnull(spriteBatch)))
    cclog("sprite = " .. tostring(tolua.isnull(sprite)))
    spriteBatch:addChild(sprite)
    Helper.currentLayer:addChild(spriteBatch)

    local animFrames = {}
    for i = 1,14 do
        local frame = cache:getSpriteFrame(string.format("dance_%02d", i))
        animFrames[i] = frame
    end

    local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
    -- 14 frames * 1sec = 14 seconds
    sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
end

function SpriteFrameAliasNameTest.onExit()
    cc.SpriteFrameCache:getInstance():removeSpriteFramesFromFile("animations/grossini-aliases.plist")
end

function SpriteFrameAliasNameTest.onEnterOrExit(tag)
	if tag == "enter" then
		SpriteFrameAliasNameTest.onEnter()
	elseif tag == "exit" then
		SpriteFrameAliasNameTest.onExit()
	end
end

function SpriteFrameAliasNameTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    layer:registerScriptHandler(SpriteFrameAliasNameTest.onEnterOrExit)
    Helper.titleLabel:setString("SpriteFrame Alias Name")
    Helper.subtitleLabel:setString("SpriteFrames are obtained using the alias name")

    return layer
end

---------------------------------------------------------------------
--
-- SpriteAnchorPoint
--
--------------------------------------------------------------------
local SpriteAnchorPoint = {}
SpriteAnchorPoint.__index = SpriteAnchorPoint

function SpriteAnchorPoint.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()
    
    local rotate = cc.RotateBy:create(10, 360)
    local action = cc.RepeatForever:create(rotate)
    
    for i = 0, 2 do
        local sprite = cc.Sprite:create("Images/grossini_dance_atlas.png", cc.rect(85*i, 121*1, 85, 121) )
        sprite:setPosition( cc.p( s.width/4*(i+1), s.height/2) )
        
        local point = cc.Sprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( sprite:getPosition() )
        layer:addChild(point, 10)
        
        if i == 0 then
            sprite:setAnchorPoint( cc.p(0, 0) )
        elseif i == 1 then
            sprite:setAnchorPoint( cc.p(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( cc.p(1,1) )
        end
        point:setPosition( sprite:getPosition() )
        
        local copy = action:clone()
        sprite:runAction(copy)
        layer:addChild(sprite, i)
    end        

    return layer
end

function SpriteAnchorPoint.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    layer = SpriteAnchorPoint.initLayer(layer)
    Helper.titleLabel:setString("Sprite: anchor point")
    Helper.subtitleLabel:setString("")
    return layer
end

--------------------------------------------------------------------
-- SpriteBatchNodeAnchorPoint
--------------------------------------------------------------------
local SpriteBatchNodeAnchorPoint = {}
SpriteBatchNodeAnchorPoint.__index = SpriteBatchNodeAnchorPoint

function SpriteBatchNodeAnchorPoint.initLayer(layer)
    -- small capacity. Testing resizing.
    -- Don't use capacity=1 in your real game. It is expensive to resize the capacity
    local batch = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 1)
    layer:addChild(batch, 0, kTagSpriteBatchNode)        

    local s = cc.Director:getInstance():getWinSize()

    local rotate = cc.RotateBy:create(10, 360)
    local action = cc.RepeatForever:create(rotate)
    for i=0,2 do
        local sprite = cc.Sprite:createWithTexture(batch:getTexture(), cc.rect(85*i, 121*1, 85, 121))
        sprite:setPosition( cc.p( s.width/4*(i+1), s.height/2) )

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( cc.p(sprite:getPosition()) )
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint( cc.p(0,0) )
        elseif i == 1 then
            sprite:setAnchorPoint( cc.p(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( cc.p(1,1) )
        end

        point:setPosition( cc.p(sprite:getPosition()) )

        local copy = action:clone()
        sprite:runAction(copy)
        batch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeAnchorPoint.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    layer = SpriteBatchNodeAnchorPoint.initLayer(layer)
    Helper.titleLabel:setString("SpriteBatchNode: anchor point")
    Helper.subtitleLabel:setString("")

    return layer
end

--------------------------------------------------------------------
--
-- SpriteOffsetAnchorRotation
--
--------------------------------------------------------------------
local SpriteOffsetAnchorRotation = {}
SpriteOffsetAnchorRotation.__index = SpriteOffsetAnchorRotation

function SpriteOffsetAnchorRotation.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()        
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    for i=0,2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p( s.width/4*(i+1), s.height/2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( sprite:getPosition() )
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint( cc.p(0, 0) )
        elseif i == 1 then
            sprite:setAnchorPoint( cc.p(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( cc.p(1,1) )
        end

        point:setPosition( cc.p(sprite:getPosition()) )

        local animFrames = {}
        
        for i = 0, 13 do 
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png",(i+1)))
            animFrames[i + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create( cc.Animate:create(animation) ) )            
        sprite:runAction(cc.RepeatForever:create(cc.RotateBy:create(10, 360) ) )

        layer:addChild(sprite, 0)
    end        

    return layer
end

function SpriteOffsetAnchorRotation.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteOffsetAnchorRotation.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorRotation.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteOffsetAnchorRotation.initLayer(layer)
    Helper.titleLabel:setString("Sprite offset + anchor + rot")
    Helper.subtitleLabel:setString("")

    return layer
end

--------------------------------------------------------------------
--
-- SpriteBatchNodeOffsetAnchorRotation
--
--------------------------------------------------------------------
local SpriteBatchNodeOffsetAnchorRotation = {}
SpriteBatchNodeOffsetAnchorRotation.__index = SpriteBatchNodeOffsetAnchorRotation

function SpriteBatchNodeOffsetAnchorRotation.initLayer(layer)

    local s = cc.Director:getInstance():getWinSize() 

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    local spritebatch = cc.SpriteBatchNode:create("animations/grossini.png")
    cclog("1")
    layer:addChild(spritebatch)

    cclog("2")
    for i = 0,2 do
        --
        -- Animation using Sprite BatchNode
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition( cc.p( s.width/4*(i+1), s.height/2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( cc.p(sprite:getPosition()) )
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint( cc.p(0,0) )
        elseif i == 1 then
            sprite:setAnchorPoint( cc.p(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( cc.p(1,1) )
        end

        point:setPosition( cc.p(sprite:getPosition()) )

        local animFrames = {}
        for k = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png",(k+1)))
            animFrames[k + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create( cc.Animate:create(animation) ))
        sprite:runAction(cc.RepeatForever:create(cc.RotateBy:create(10, 360) ))
        spritebatch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorRotation.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteBatchNodeOffsetAnchorRotation.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorRotation.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteBatchNodeOffsetAnchorRotation.initLayer(layer)
    Helper.titleLabel:setString("SpriteBatchNode offset + anchor + rot")
    Helper.subtitleLabel:setString("")

    return layer
end

--------------------------------------------------------------------
--
-- SpriteOffsetAnchorScale
--
--------------------------------------------------------------------
local SpriteOffsetAnchorScale = {}
SpriteOffsetAnchorScale.__index = SpriteOffsetAnchorScale

function SpriteOffsetAnchorScale.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()   
    
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    for i = 0,2 do
        --
        -- Animation using Sprite BatchNode
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition( cc.p( s.width/4*(i+1), s.height/2) )
        
        local point = cc.Sprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( sprite:getPosition() )
        layer:addChild(point, 1)
        
        if i == 0 then
            sprite:setAnchorPoint( cc.p(0, 0) )
        elseif i == 1 then
            sprite:setAnchorPoint( cc.p(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( cc.p(1,1) )
        end
        
        point:setPosition( cc.p(sprite:getPosition()) )
        
        local animFrames = {}

        for i = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png",(i+1)))
            animFrames[i + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create( cc.Animate:create(animation) ))            
        
        local scale = cc.ScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = cc.Sequence:create(scale, scale_back)
        sprite:runAction(cc.RepeatForever:create(seq_scale))
        
        layer:addChild(sprite, 0)
    end

    return layer
end

function SpriteOffsetAnchorScale.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteOffsetAnchorScale.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorScale.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteOffsetAnchorScale.initLayer(layer)
    Helper.titleLabel:setString("Sprite offset + anchor + scale")
    Helper.subtitleLabel:setString("")

    return layer
end

--------------------------------------------------------------------
--
-- SpriteBatchNodeOffsetAnchorScale
--
--------------------------------------------------------------------
local SpriteBatchNodeOffsetAnchorScale = {}

function SpriteBatchNodeOffsetAnchorScale.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    local spritesheet = cc.SpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritesheet)

    for i = 0,2 do
        -- Animation using Sprite BatchNode
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width/4*(i+1), s.height/2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        else
            sprite:setAnchorPoint(cc.p(1, 1))
        end

        point:setPosition(sprite:getPosition())

        local animFrames = {}
        local str
        for k = 0, 13 do
            str = string.format("grossini_dance_%02d.png", (k+1))
            local frame = cache:getSpriteFrame(str)
            animFrames[k + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))

        local scale = cc.ScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = cc.Sequence:create(scale, scale_back)
        sprite:runAction(cc.RepeatForever:create(seq_scale))

        spritesheet:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorScale.onExit()
    local cache = cc.SpriteFrameCache:getInstance()
    cache:removeSpriteFramesFromFile("animations/grossini.plist")
    cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
end

function SpriteBatchNodeOffsetAnchorScale.eventHandler(tag)
    if tag == "exit" then
        SpriteBatchNodeOffsetAnchorScale.onExit()
    end
end

function SpriteBatchNodeOffsetAnchorScale.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorScale.eventHandler)

    layer = SpriteBatchNodeOffsetAnchorScale.initLayer(layer)
    Helper.titleLabel:setString("SpriteBatchNode offset + anchor + scale")
    Helper.subtitleLabel:setString("")

    return layer
end

--------------------------------------------------------------------
--
-- SpriteOffsetAnchorSkew
--
--------------------------------------------------------------------
local SpriteOffsetAnchorSkew = {}
SpriteOffsetAnchorSkew.__index = SpriteOffsetAnchorSkew

function SpriteOffsetAnchorSkew.initLayer(layer)

    local s = cc.Director:getInstance():getWinSize()
    
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width / 4 * (i + 1), s.height / 2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(cc.p(1, 1))
        end

        point:setPosition(sprite:getPosition())

        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", j + 1))
            animFrames[j + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))

        local skewX = cc.SkewBy:create(2, 45, 0)
        local skewX_back = skewX:reverse()
        local skewY = cc.SkewBy:create(2, 0, 45)
        local skewY_back = skewY:reverse()

        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))

        layer:addChild(sprite, 0)
    end       

    return layer
end

function SpriteOffsetAnchorSkew.eventHandler(tag)
     if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
     end
end

function SpriteOffsetAnchorSkew.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorSkew.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteOffsetAnchorSkew.initLayer(layer)
    Helper.titleLabel:setString("SpriteBatchNode offset + anchor + scale")
    Helper.subtitleLabel:setString("")

    return layer
end
------------------------------------------------------------
-- SpriteOffsetAnchorRotationalSkew
------------------------------------------------------------
local SpriteOffsetAnchorRotationalSkew = {}
SpriteOffsetAnchorRotationalSkew.__index = SpriteOffsetAnchorRotationalSkew

function SpriteOffsetAnchorRotationalSkew.initLayer(layer)

    local s = cc.Director:getInstance():getWinSize()
    
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width/4*(i+1), s.height/2))
        
        local point = cc.Sprite:create("Images/r1.png")
                            
        point:setScale(0.25)
        point:setPosition(cc.p(sprite:getPosition()))
        layer:addChild(point, 1)
        
        if i == 0 then
            sprite:setAnchorPoint(cc.p(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(cc.p(1,1))
        end
        
        point:setPosition(cc.p(sprite:getPosition()))
        
        local animFrames = {}
        for i = 0,13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", (i+1)))
            animFrames[i + 1] = frame
        end
        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
        
        local skewX = cc.RotateBy:create(2, 45)
        local skewX_back = skewX:reverse()
        local skewY = cc.RotateBy:create(2, -45)
        local skewY_back = skewY:reverse()
        
        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))
        
        layer:addChild(sprite, 0)
    end
    return layer
end

function SpriteOffsetAnchorRotationalSkew.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteOffsetAnchorRotationalSkew.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorRotationalSkew.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteOffsetAnchorRotationalSkew.initLayer(layer)
    Helper.titleLabel:setString("Sprite offset + anchor + rotational skew")
    Helper.subtitleLabel:setString("")

    return layer
end


------------------------------------------------------------
-- SpriteBatchNodeOffsetAnchorSkew
------------------------------------------------------------
local SpriteBatchNodeOffsetAnchorSkew = {}
SpriteBatchNodeOffsetAnchorSkew.__index = SpriteBatchNodeOffsetAnchorSkew

function SpriteBatchNodeOffsetAnchorSkew.initLayer(layer)

    local s = cc.Director:getInstance():getWinSize()
    
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    local spritebatch = cc.SpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritebatch)

    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width / 4 * (i + 1), s.height / 2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(cc.p(sprite:getPosition()))
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(cc.p(1, 1))
        end

        point:setPosition(cc.p(sprite:getPosition()))
        
        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", j + 1))
            animFrames[j + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))

        local skewX = cc.SkewBy:create(2, 45, 0)
        local skewX_back = skewX:reverse()
        local skewY = cc.SkewBy:create(2, 0, 45)
        local skewY_back = skewY:reverse()

        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))

        spritebatch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorSkew.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteBatchNodeOffsetAnchorSkew.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorSkew.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteBatchNodeOffsetAnchorSkew.initLayer(layer)
    Helper.titleLabel:setString("SpriteBatchNode offset + anchor + skew")
    Helper.subtitleLabel:setString("")

    return layer
end

--
-- SpriteBatchNodeOffsetAnchorRotationalSkew
-- 
local SpriteBatchNodeOffsetAnchorRotationalSkew = {}
SpriteBatchNodeOffsetAnchorRotationalSkew.__index = SpriteBatchNodeOffsetAnchorRotationalSkew

function SpriteBatchNodeOffsetAnchorRotationalSkew.initLayer(layer)

    local s = cc.Director:getInstance():getWinSize()
    
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    local spritebatch = cc.SpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritebatch)
    
    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width/4*(i+1), s.height/2))
        
        local point = cc.Sprite:create("Images/r1.png")
        
        point:setScale(0.25)
        point:setPosition(cc.p(sprite:getPosition()))
        layer:addChild(point, 200)
        
        if i == 0 then
            sprite:setAnchorPoint(cc.p(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(cc.p(1,1))
        end
        
        point:setPosition(cc.p(sprite:getPosition()))
        
        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", (j+1)))
            animFrames[j + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
        
        local skewX = cc.RotateBy:create(2, 45)
        local skewX_back = skewX:reverse()
        local skewY = cc.RotateBy:create(2, -45)
        local skewY_back = skewY:reverse()
        
        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))
        
        spritebatch:addChild(sprite, i)
    end

    return layer
end

-- remove resources
function SpriteBatchNodeOffsetAnchorRotationalSkew.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteBatchNodeOffsetAnchorRotationalSkew.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorRotationalSkew.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteBatchNodeOffsetAnchorRotationalSkew.initLayer(layer)
    Helper.titleLabel:setString("SSpriteBatchNode offset + anchor + rot skew")
    Helper.subtitleLabel:setString("")

    return layer
end

--
-- SpriteOffsetAnchorSkewScale
-- 
local SpriteOffsetAnchorSkewScale = {}

function SpriteOffsetAnchorSkewScale.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    for i = 0, 2 do
        -- Animation using Sprite batch
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width / 4 * (i + 1), s.height / 2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        else
            sprite:setAnchorPoint(cc.p(1, 1))
        end

        point:setPosition(sprite:getPosition())

        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", j+1))
            animFrames[j + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))

        -- Skew
        local skewX = cc.SkewBy:create(2, 45, 0)
        local skewX_back = skewX:reverse()
        local skewY = cc.SkewBy:create(2, 0, 45)
        local skewY_back = skewY:reverse()

        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))

        -- Scale
        local scale = cc.ScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = cc.Sequence:create(scale, scale_back)
        sprite:runAction(cc.RepeatForever:create(seq_scale))

        layer:addChild(sprite, 0)
    end

    return layer
end

function SpriteOffsetAnchorSkewScale.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteOffsetAnchorSkewScale.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorSkewScale.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteOffsetAnchorSkewScale.initLayer(layer)
    Helper.titleLabel:setString("Sprite anchor + skew + scale")

    return layer
end

--
-- SpriteOffsetAnchorRotationalSkewScale
--
local SpriteOffsetAnchorRotationalSkewScale = {}

function SpriteOffsetAnchorRotationalSkewScale.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    for i = 0, 2 do
        -- Animation using Sprite batch
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width/4*(i+1), s.height/2))
        
        local point = cc.Sprite:create("Images/r1.png")

        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        else
            sprite:setAnchorPoint(cc.p(1, 1))
        end
        
        point:setPosition(sprite:getPosition())

        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", (j+1)))
            animFrames[j + 1] = frame
        end
        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
        
        -- Skew
        local skewX = cc.RotateBy:create(2, 45, 0)
        local skewX_back = skewX:reverse()
        local skewY = cc.RotateBy:create(2, 0, 45)
        local skewY_back = skewY:reverse()

        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))
        
        -- Scale
        local scale = cc.ScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = cc.Sequence:create(scale, scale_back)
        sprite:runAction(cc.RepeatForever:create(seq_scale))

        layer:addChild(sprite, i)
    end

    return layer
end

function SpriteOffsetAnchorRotationalSkewScale.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteOffsetAnchorRotationalSkewScale.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorRotationalSkewScale.eventHandler)
    Helper.initWithLayer(layer)

    layer = SpriteOffsetAnchorRotationalSkewScale.initLayer(layer)
    Helper.titleLabel:setString("Sprite anchor + rot skew + scale")

    return layer
end

--
-- SpriteBatchNodeOffsetAnchorSkewScale
--
local SpriteBatchNodeOffsetAnchorSkewScale = {}

function SpriteBatchNodeOffsetAnchorSkewScale.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    local spritebatch = cc.SpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritebatch)

    for i = 0, 2 do
        -- Animation using Sprite batch

        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width / 4 * (i + 1), s.height / 2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        else
            sprite:setAnchorPoint(cc.p(1, 1)) 
        end

        point:setPosition(sprite:getPosition())       

        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", (j+1)))
            animFrames[j + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))

        -- skew
        local skewX = cc.SkewBy:create(2, 45, 0)
        local skewX_back = skewX:reverse()
        local skewY = cc.SkewBy:create(2, 0, 45)
        local skewY_back = skewY:reverse()

        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))


        -- scale 
        local scale = cc.ScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = cc.Sequence:create(scale, scale_back)
        sprite:runAction(cc.RepeatForever:create(seq_scale))

        spritebatch:addChild(sprite, i)
    end
end

function SpriteBatchNodeOffsetAnchorSkewScale.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteBatchNodeOffsetAnchorSkewScale.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorSkewScale.eventHandler)
    Helper.initWithLayer(layer)

    SpriteBatchNodeOffsetAnchorSkewScale.initLayer(layer)
    Helper.titleLabel:setString("SpriteBatchNode anchor + skew + scale")

    return layer
end

--
-- SpriteBatchNodeOffsetAnchorRotationalSkewScale
-- 
local SpriteBatchNodeOffsetAnchorRotationalSkewScale = {}
function SpriteBatchNodeOffsetAnchorRotationalSkewScale.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()
    
    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    local spritebatch = cc.SpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritebatch)
    
    for i = 0, 2 do
        -- Animation using Sprite batch
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width/4*(i+1), s.height/2))

        local point = cc.Sprite:create("Images/r1.png")

        point:setScale(0.25)
        point:setPosition(sprite:getPosition())

        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        else
            sprite:setAnchorPoint(cc.p(1, 1))
        end
        
        point:setPosition(sprite:getPosition())

        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", j+1))
            animFrames[j + 1] = frame
        end
        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))
        
        -- Skew
        local skewX = cc.RotateBy:create(2, 45, 0)
        local skewX_back = skewX:reverse()
        local skewY = cc.RotateBy:create(2, 0, 45)
        local skewY_back = skewY:reverse()

        local seq_skew = cc.Sequence:create(skewX, skewX_back, skewY, skewY_back)
        sprite:runAction(cc.RepeatForever:create(seq_skew))
        
        -- Scale
        local scale = cc.ScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = cc.Sequence:create(scale, scale_back)
        sprite:runAction(cc.RepeatForever:create(seq_scale))
        
        spritebatch:addChild(sprite, i)
    end
end

function SpriteBatchNodeOffsetAnchorRotationalSkewScale.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteBatchNodeOffsetAnchorRotationalSkewScale.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorRotationalSkewScale.eventHandler)
    Helper.initWithLayer(layer)
    SpriteBatchNodeOffsetAnchorRotationalSkewScale.initLayer(layer)

    Helper.titleLabel:setString("SpriteBatchNode anchor + rot skew + scale")

    return layer
end

--
-- SpriteOffsetAnchorFlip
--
local SpriteOffsetAnchorFlip = {}
function SpriteOffsetAnchorFlip.initLayer(layer)
    local s = cc.Director:getInstance():getWinSize()

    local cache = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("animations/grossini.plist")
    cache:addSpriteFrames("animations/grossini_gray.plist", "animations/grossini_gray.png")

    for i = 0, 2 do
        -- Animation using Sprite batch
        local sprite = cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(cc.p(s.width / 4 * (i + 1), s.height / 2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint(cc.p(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        else
            sprite:setAnchorPoint(cc.p(1, 1))
        end

        point:setPosition(sprite:getPosition())

        local animFrames = {}
        for j = 0, 13 do
            local frame = cache:getSpriteFrame(string.format("grossini_dance_%02d.png", j+1))
            animFrames[j + 1] = frame
        end

        local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(cc.RepeatForever:create(cc.Animate:create(animation)))

        local flip = cc.FlipY:create(true)
        local flip_back = cc.FlipY:create(false)
        local delay = cc.DelayTime:create(1)
        local delay2 = cc.DelayTime:create(1)

        local seq = cc.Sequence:create(delay, flip, delay2, flip_back)
        sprite:runAction(cc.RepeatForever:create(seq))

        layer:addChild(sprite, 0)
    end
end

function SpriteOffsetAnchorFlip.eventHandler(tag)
    if tag == "exit" then
        local cache = cc.SpriteFrameCache:getInstance()
        cache:removeSpriteFramesFromFile("animations/grossini.plist")
        cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    end
end

function SpriteOffsetAnchorFlip.create()
    local layer = cc.Layer:create()
    layer:registerScriptHandler(SpriteOffsetAnchorFlip.eventHandler)
    Helper.initWithLayer(layer)

    SpriteOffsetAnchorFlip.initLayer(layer)
    Helper.titleLabel:setString("Sprite offset + anchor + flip")
    Helper.subtitleLabel:setString("issue #1078")

    return layer
end


function SpriteTest()
	local scene = cc.Scene:create()
	
	Helper.createFunctionTable = {
        Sprite1.create,
        SpriteBatchNode1.create,
        SpriteFrameTest.create,
        SpriteFrameAliasNameTest.create,
        SpriteAnchorPoint.create,
        SpriteBatchNodeAnchorPoint.create,
        SpriteOffsetAnchorRotation.create,
        SpriteBatchNodeOffsetAnchorRotation.create,
        SpriteOffsetAnchorScale.create,
        SpriteBatchNodeOffsetAnchorScale.create,
        SpriteOffsetAnchorSkew.create,
        SpriteOffsetAnchorRotationalSkew.create,
        SpriteBatchNodeOffsetAnchorSkew.create,
        SpriteBatchNodeOffsetAnchorRotationalSkew.create,
        SpriteOffsetAnchorSkewScale.create,
        SpriteOffsetAnchorRotationalSkewScale.create,
        SpriteBatchNodeOffsetAnchorSkewScale.create,
        SpriteBatchNodeOffsetAnchorRotationalSkewScale.create,
        SpriteOffsetAnchorFlip.create
    }

	scene:addChild(Sprite1.create())
	scene:addChild(CreateBackMenuItem())

	return scene
end
