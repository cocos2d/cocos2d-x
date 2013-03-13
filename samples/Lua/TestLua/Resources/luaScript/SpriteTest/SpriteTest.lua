

local ActionIdx = 0
local createFunctionTable = nil
local size = CCDirector:sharedDirector():getWinSize()

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
local titleLabel = nil
local entry      = nil
local subtitleLabel = nil

local playerLayer = nil

local function onEnterOrExit(tag)
	local scheduler = CCDirector:sharedDirector():getScheduler()
	if tag == "enter" then
--  	entry = scheduler:scheduleScriptFunc(checkAnim, 0, false)
	elseif tag == "exit" then
--  	scheduler:unscheduleScriptEntry(entry)
	end
end

local function CreateSpriteTestLayer()
    local layer = createFunctionTable[ActionIdx]()

    playerLayer = layer
    return layer
end

local function backAction()
    ActionIdx = ActionIdx - 1
    if ActionIdx <= 0 then
        ActionIdx = table.getn(createFunctionTable)
    end

    return CreateSpriteTestLayer()
end

local function restartAction()
    return CreateSpriteTestLayer()
end

local function nextAction()
    ActionIdx = ActionIdx + 1
    if ActionIdx > table.getn(createFunctionTable) then
        ActionIdx = 1
    end

    return CreateSpriteTestLayer()
end

local function backCallback(sender)
    local scene = CCScene:create()

    scene:addChild(backAction())
    scene:addChild(CreateBackMenuItem())

    CCDirector:sharedDirector():replaceScene(scene)
end

local function restartCallback(sender)
    local scene = CCScene:create()

    scene:addChild(restartAction())
    scene:addChild(CreateBackMenuItem())

    CCDirector:sharedDirector():replaceScene(scene)
end

local function nextCallback(sender)
    local scene = CCScene:create()

    scene:addChild(nextAction())
    scene:addChild(CreateBackMenuItem())

    CCDirector:sharedDirector():replaceScene(scene)
end


local function initWithLayer(layer)
    titleLabel = CCLabelTTF:create("", "Arial", 28)
    layer:addChild(titleLabel, 1)
    titleLabel:setPosition(size.width / 2, size.height - 50)

    subtitleLabel = CCLabelTTF:create("", "Thonburi", 16)
    layer:addChild(subtitleLabel, 1)
    subtitleLabel:setPosition(size.width / 2, size.height - 80)

    -- menu
    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    item1:registerScriptTapHandler(backCallback)
    item2:registerScriptTapHandler(restartCallback)
    item3:registerScriptTapHandler(nextCallback)

    local menu = CCMenu:create()
    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)
    menu:setPosition(CCPointMake(0, 0))
    item1:setPosition(CCPointMake(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(size.width / 2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    layer:addChild(menu, 1)

    local background = CCLayer:create()
    layer:addChild(background, -10)
end

--------------------------------------------
---- test sprite1
--------------------------------------------
local Sprite1 = {}
Sprite1.__index = Sprite1

function Sprite1.addNewSpriteWithCoords(layer, point)
    local idx = math.floor(math.random() * 1400 / 100)
    local x = math.floor(math.mod(idx,5) * 85)
    local y = math.floor(idx / 5 * 121)

    local sprite = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(x,y,85,121) )
    layer:addChild( sprite )

    sprite:setPosition( ccp(point.x, point.y) )

    local action = nil
    local random = math.random()
    cclog("random = " .. random)
    if( random < 0.20 ) then
        action = CCScaleBy:create(3, 2)
    elseif(random < 0.40) then
        action = CCRotateBy:create(3, 360)
    elseif( random < 0.60) then
        action = CCBlink:create(1, 3)
    elseif( random < 0.8 ) then
        action = CCTintBy:create(2, 0, -255, -255)
    else 
        action = CCFadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = CCSequence:createWithTwoActions( action, action_back)

    sprite:runAction( CCRepeatForever:create(seq) )
end

function Sprite1.onTouch(event, x, y)
    if event == "began" then
        return true
    elseif event == "ended" then
        Sprite1.addNewSpriteWithCoords(playerLayer, ccp(x,y))
        return true
    end
end

function Sprite1.create()
    cclog("sprite1")
    local layer = CCLayer:create()
    initWithLayer(layer)
    Sprite1.addNewSpriteWithCoords(layer, ccp(size.width/2, size.height/2))
    layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(Sprite1.onTouch)

    titleLabel:setString("Sprite (tap screen)")

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
    local y = math.floor(idx / 5 * 121)

    local sprite = CCSprite:createWithTexture(BatchNode:getTexture(), CCRectMake(x,y,85,121) )
    layer:addChild( sprite )

    sprite:setPosition( ccp(point.x, point.y) )

    local action = nil
    local random = math.random()
    cclog("random = " .. random)
    if( random < 0.20 ) then
        action = CCScaleBy:create(3, 2)
    elseif(random < 0.40) then
        action = CCRotateBy:create(3, 360)
    elseif( random < 0.60) then
        action = CCBlink:create(1, 3)
    elseif( random < 0.8 ) then
        action = CCTintBy:create(2, 0, -255, -255)
    else 
        action = CCFadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = CCSequence:createWithTwoActions( action, action_back)

    sprite:runAction( CCRepeatForever:create(seq) )
end

function SpriteBatchNode1.onTouch(event, x, y)
    if event == "began" then
        return true
    elseif event == "ended" then
        SpriteBatchNode1.addNewSpriteWithCoords(playerLayer, ccp(x,y))
        return true
    end
end

function SpriteBatchNode1.create()
    local layer = CCLayer:create()
    initWithLayer(layer)
    local BatchNode = CCSpriteBatchNode:create("Images/grossini_dance_atlas.png", 50)
    layer:addChild(BatchNode, 0, kTagSpriteBatchNode)

    SpriteBatchNode1.addNewSpriteWithCoords(layer, ccp(size.width/2, size.height/2))

    layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(SpriteBatchNode1.onTouch)

    titleLabel:setString("SpriteBatchNode (tap screen)")

    return layer
end

--------------------------------------
----  SpriteColorOpacity
--------------------------------------
local SpriteColorOpacity = {}
SpriteColorOpacity.__index = SpriteColorOpacity
SpriteColorOpacity.entry = nil

function SpriteColorOpacity.setLayerSprite(layer)
    local sprite1 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121))
    local sprite2 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121))
    local sprite3 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*2, 121*1, 85, 121))
    local sprite4 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*1, 85, 121))
    
    local sprite5 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*0, 121*1, 85, 121))
    local sprite6 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*1, 121*1, 85, 121))
    local sprite7 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*2, 121*1, 85, 121))
    local sprite8 = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*3, 121*1, 85, 121))
    
    local s = CCDirector:sharedDirector():getWinSize()
    sprite1:setPosition( ccp( (s.width/5)*1, (s.height/3)*1) )
    sprite2:setPosition( ccp( (s.width/5)*2, (s.height/3)*1) )
    sprite3:setPosition( ccp( (s.width/5)*3, (s.height/3)*1) )
    sprite4:setPosition( ccp( (s.width/5)*4, (s.height/3)*1) )
    sprite5:setPosition( ccp( (s.width/5)*1, (s.height/3)*2) )
    sprite6:setPosition( ccp( (s.width/5)*2, (s.height/3)*2) )
    sprite7:setPosition( ccp( (s.width/5)*3, (s.height/3)*2) )
    sprite8:setPosition( ccp( (s.width/5)*4, (s.height/3)*2) )
    
    local action = CCFadeIn:create(2)
    local action_back = action:reverse()
    local fade = CCRepeatForever:create( CCSequence:createWithTwoActions( action, action_back) )
    
    local tintred = CCTintBy:create(2, 0, -255, -255)
    local tintred_back = tintred:reverse()
    local red = CCRepeatForever:create( CCSequence:createWithTwoActions( tintred, tintred_back) )
    
    local tintgreen = CCTintBy:create(2, -255, 0, -255)
    local tintgreen_back = tintgreen:reverse()
    local green = CCRepeatForever:create( CCSequence:createWithTwoActions( tintgreen, tintgreen_back) )
    
    local tintblue = CCTintBy:create(2, -255, -255, 0)
    local tintblue_back = tintblue:reverse()
    local blue = CCRepeatForever:create( CCSequence:createWithTwoActions( tintblue, tintblue_back) )
    
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
    local schedule = CCDirector:sharedDirector():getScheduler()
    if tag == "enter" then
        SpriteColorOpacity.entry = scheduler:scheduleScriptFunc(SpriteColorOpacity.removeAndAddSprite, 0, false)
    elseif tag == "exit" then
        scheduler:unscheduleScriptEntry(SpriteColorOpacity.entry)
    end
end

function SpriteColorOpacity.removeAndAddSprite(dt)
    local sprite = playerLayer:getChildByTag(kTagSprite5)    
    sprite:retain()
    
    playerLayer:removeChild(sprite, false)
    playerLayer:addChild(sprite, 0, kTagSprite5)
    
    sprite:release()
end

function SpriteColorOpacity.create()
    local layer = CCLayer:create()
    initWithLayer(layer)
    SpriteColorOpacity.setLayerSprite(layer)
    titleLabel:setString("Sprite: Color & Opacity")

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
    local s = CCDirector:sharedDirector():getWinSize()
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()

    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")
    cache:addSpriteFramesWithFile("animations/grossini_blue.plist", "animations/grossini_blue.png")

    SpriteFrameTest.m_pSprite1 = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
    SpriteFrameTest.m_pSprite1:setPosition( ccp( s.width/2-80, s.height/2) )

    local spritebatch = CCSpriteBatchNode:create("animations/grossini.png")
    spritebatch:addChild(SpriteFrameTest.m_pSprite1)
    playerLayer:addChild(spritebatch)

    local animFrames = CCArray:createWithCapacity(15)
    for i = 1,14 do 
        local frame = cache:spriteFrameByName( string.format("grossini_dance_%02d.png", i) )
        animFrames:addObject(frame)
    end

    local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
    SpriteFrameTest.m_pSprite1:runAction( CCRepeatForever:create( CCAnimate:create(animation) ) )

    SpriteFrameTest.m_pSprite1:setFlipX(false)
    SpriteFrameTest.m_pSprite1:setFlipY(false)

    SpriteFrameTest.m_pSprite2 = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
    SpriteFrameTest.m_pSprite2:setPosition( ccp( s.width/2 + 80, s.height/2) )
    playerLayer:addChild(SpriteFrameTest.m_pSprite2)

    local moreFrames = CCArray:createWithCapacity(20)
    for i = 1,14 do
        local frame = cache:spriteFrameByName(string.format("grossini_dance_gray_%02d.png",i))
        moreFrames:addObject(frame)
    end

    for i = 1,4 do
        local frame = cache:spriteFrameByName(string.format("grossini_blue_%02d.png",i))
        moreFrames:addObject(frame)
    end

    moreFrames:addObjectsFromArray(animFrames)
    local animMixed = CCAnimation:createWithSpriteFrames(moreFrames, 0.3)

    SpriteFrameTest.m_pSprite2:runAction(CCRepeatForever:create( CCAnimate:create(animMixed) ) )

    SpriteFrameTest.m_pSprite2:setFlipX(false)
    SpriteFrameTest.m_pSprite2:setFlipY(false)


    performWithDelay(playerLayer,SpriteFrameTest.startIn05Secs, 0.5)
    SpriteFrameTest.m_nCounter = 0

    local scheduler = CCDirector:sharedDirector():getScheduler()
    scheduler:unscheduleScriptEntry(SpriteFrameTest.entry)

end

function SpriteFrameTest.onExit()
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:removeSpriteFramesFromFile("animations/grossini.plist")
    cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
    cache:removeSpriteFramesFromFile("animations/grossini_blue.plist")
end

function SpriteFrameTest.startIn05Secs(dt)
    schedule(playerLayer,SpriteFrameTest.flipSprites, 1)
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
	local scheduler = CCDirector:sharedDirector():getScheduler()
	if tag == "enter" then
		SpriteFrameTest.entry = scheduler:scheduleScriptFunc(SpriteFrameTest.onEnter, 0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(SpriteFrameTest.entry)
	end
end

function SpriteFrameTest.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer:registerScriptHandler(SpriteFrameTest.onEnterOrExit)
    titleLabel:setString("Sprite vs. SpriteBatchNode animation")

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
    local s = CCDirector:sharedDirector():getWinSize()

    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini-aliases.plist", "animations/grossini-aliases.png")

    local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
    sprite:setPosition(ccp(s.width * 0.5, s.height * 0.5))

    local spriteBatch = CCSpriteBatchNode:create("animations/grossini-aliases.png")
    cclog("spriteBatch = " .. tostring(tolua.isnull(spriteBatch)))
    cclog("sprite = " .. tostring(tolua.isnull(sprite)))
    spriteBatch:addChild(sprite)
    playerLayer:addChild(spriteBatch)

    local animFrames = CCArray:createWithCapacity(15)
    for i = 1,14 do
        local frame = cache:spriteFrameByName(string.format("dance_%02d", i))
        animFrames:addObject(frame)
    end

    local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
    -- 14 frames * 1sec = 14 seconds
    sprite:runAction(CCRepeatForever:create(CCAnimate:create(animation)))

    local scheduler = CCDirector:sharedDirector():getScheduler()
    scheduler:unscheduleScriptEntry(SpriteFrameAliasNameTest.entry)
end

function SpriteFrameAliasNameTest.onExit()
    CCSpriteFrameCache:sharedSpriteFrameCache():removeSpriteFramesFromFile("animations/grossini-aliases.plist")
end

function SpriteFrameAliasNameTest.onEnterOrExit(tag)
	local scheduler = CCDirector:sharedDirector():getScheduler()
	if tag == "enter" then
		SpriteFrameAliasNameTest.entry = scheduler:scheduleScriptFunc(SpriteFrameAliasNameTest.onEnter, 0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(SpriteFrameAliasNameTest.entry)
	end
end

function SpriteFrameAliasNameTest.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer:registerScriptHandler(SpriteFrameAliasNameTest.onEnterOrExit)
    titleLabel:setString("SpriteFrame Alias Name")
    subtitleLabel:setString("SpriteFrames are obtained using the alias name")

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
    local s = CCDirector:sharedDirector():getWinSize()
    
    local rotate = CCRotateBy:create(10, 360)
    local action = CCRepeatForever:create(rotate)
    
    for i = 0, 2 do
        local sprite = CCSprite:create("Images/grossini_dance_atlas.png", CCRectMake(85*i, 121*1, 85, 121) )
        sprite:setPosition( ccp( s.width/4*(i+1), s.height/2) )
        
        local point = CCSprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( sprite:getPosition() )
        layer:addChild(point, 10)
        
        if i == 0 then
            sprite:setAnchorPoint( ccp(0, 0) )
        elseif i == 1 then
            sprite:setAnchorPoint( ccp(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( ccp(1,1) )
        end
        point:setPosition( sprite:getPosition() )
        
        local copy = tolua.cast(action:copy():autorelease(), "CCAction")
        sprite:runAction(copy)
        layer:addChild(sprite, i)
    end        

    return layer
end

function SpriteAnchorPoint.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteAnchorPoint.initLayer(layer)
    titleLabel:setString("Sprite: anchor point")
    subtitleLabel:setString("")
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
    local batch = CCSpriteBatchNode:create("Images/grossini_dance_atlas.png", 1)
    layer:addChild(batch, 0, kTagSpriteBatchNode)        

    local s = CCDirector:sharedDirector():getWinSize()

    local rotate = CCRotateBy:create(10, 360)
    local action = CCRepeatForever:create(rotate)
    for i=0,2 do
        local sprite = CCSprite:createWithTexture(batch:getTexture(), CCRectMake(85*i, 121*1, 85, 121))
        sprite:setPosition( ccp( s.width/4*(i+1), s.height/2) )

        local point = CCSprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( ccp(sprite:getPosition()) )
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint( ccp(0,0) )
        elseif i == 1 then
            sprite:setAnchorPoint( ccp(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( ccp(1,1) )
        end

        point:setPosition( ccp(sprite:getPosition()) )

        local copy = tolua.cast(action:copy():autorelease(), "CCAction")
        sprite:runAction(copy)
        batch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeAnchorPoint.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteBatchNodeAnchorPoint.initLayer(layer)
    titleLabel:setString("SpriteBatchNode: anchor point")
    subtitleLabel:setString("")

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
    local s = CCDirector:sharedDirector():getWinSize()        
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")

    for i=0,2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(ccp( s.width/4*(i+1), s.height/2))

        local point = CCSprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( sprite:getPosition() )
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint( ccp(0, 0) )
        elseif i == 1 then
            sprite:setAnchorPoint( ccp(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( ccp(1,1) )
        end

        point:setPosition( ccp(sprite:getPosition()) )

        local animFrames = CCArray:createWithCapacity(14)
        
        for i = 0, 13 do 
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png",(i+1)))
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create( CCAnimate:create(animation) ) )            
        sprite:runAction(CCRepeatForever:create(CCRotateBy:create(10, 360) ) )

        layer:addChild(sprite, 0)
    end        

    return layer
end

function SpriteOffsetAnchorRotation.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteOffsetAnchorRotation.initLayer(layer)
    titleLabel:setString("Sprite offset + anchor + rot")
    subtitleLabel:setString("")

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

    local s = CCDirector:sharedDirector():getWinSize() 

    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")

    local spritebatch = CCSpriteBatchNode:create("animations/grossini.png")
    cclog("1")
    layer:addChild(spritebatch)

    cclog("2")
    for i = 0,2 do
        --
        -- Animation using Sprite BatchNode
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition( ccp( s.width/4*(i+1), s.height/2))

        local point = CCSprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( ccp(sprite:getPosition()) )
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint( ccp(0,0) )
        elseif i == 1 then
            sprite:setAnchorPoint( ccp(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( ccp(1,1) )
        end

        point:setPosition( ccp(sprite:getPosition()) )

        local animFrames = CCArray:createWithCapacity(14)
        for k = 0, 13 do
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png",(k+1)))
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create( CCAnimate:create(animation) ))
        sprite:runAction(CCRepeatForever:create(CCRotateBy:create(10, 360) ))
        spritebatch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorRotation.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteBatchNodeOffsetAnchorRotation.initLayer(layer)
    titleLabel:setString("SpriteBatchNode offset + anchor + rot")
    subtitleLabel:setString("")

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
    local s = CCDirector:sharedDirector():getWinSize()   
    
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    for i = 0,2 do
        --
        -- Animation using Sprite BatchNode
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition( ccp( s.width/4*(i+1), s.height/2) )
        
        local point = CCSprite:create("Images/r1.png")
        point:setScale( 0.25 )
        point:setPosition( sprite:getPosition() )
        layer:addChild(point, 1)
        
        if i == 0 then
            sprite:setAnchorPoint( ccp(0, 0) )
        elseif i == 1 then
            sprite:setAnchorPoint( ccp(0.5, 0.5) )
        elseif i == 2 then
            sprite:setAnchorPoint( ccp(1,1) )
        end
        
        point:setPosition( ccp(sprite:getPosition()) )
        
        local animFrames = CCArray:createWithCapacity(14)

        for i = 0, 13 do
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png",(i+1)))
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create( CCAnimate:create(animation) ))            
        
        local scale = CCScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = CCSequence:createWithTwoActions(scale, scale_back)
        sprite:runAction(CCRepeatForever:create(seq_scale))
        
        layer:addChild(sprite, 0)
    end

    return layer
end

function SpriteOffsetAnchorScale.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteOffsetAnchorScale.initLayer(layer)
    titleLabel:setString("Sprite offset + anchor + scale")
    subtitleLabel:setString("")

    return layer
end

--------------------------------------------------------------------
--
-- SpriteBatchNodeOffsetAnchorScale
--
--------------------------------------------------------------------
local SpriteBatchNodeOffsetAnchorScale = {}

function SpriteBatchNodeOffsetAnchorScale.initLayer(layer)
    local s = CCDirector:sharedDirector():getWinSize()

    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")

    local spritesheet = CCSpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritesheet)

    for i = 0,2 do
        -- Animation using Sprite BatchNode
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(ccp(s.width/4*(i+1), s.height/2))

        local point = CCSprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint(CCPointMake(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(ccp(0.5, 0.5))
        else
            sprite:setAnchorPoint(ccp(1, 1))
        end

        point:setPosition(sprite:getPosition())

        local animFrames = CCArray:createWithCapacity(14)
        local str
        for k = 0, 13 do
            str = string.format("grossini_dance_%02d.png", (k+1))
            local frame = cache:spriteFrameByName(str)
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create(CCAnimate:create(animation)))

        local scale = CCScaleBy:create(2, 2)
        local scale_back = scale:reverse()
        local seq_scale = CCSequence:createWithTwoActions(scale, scale_back)
        sprite:runAction(CCRepeatForever:create(seq_scale))

        spritesheet:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorScale.onExit()
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:removeSpriteFramesFromFile("animations/grossini.plist")
    cache:removeSpriteFramesFromFile("animations/grossini_gray.plist")
end

function SpriteBatchNodeOffsetAnchorScale.eventHandler(tag)
    if tag == "exit" then
        SpriteBatchNodeOffsetAnchorScale.onExit()
    end
end

function SpriteBatchNodeOffsetAnchorScale.create()
    local layer = CCLayer:create()
    initWithLayer(layer)
    layer:registerScriptHandler(SpriteBatchNodeOffsetAnchorScale.eventHandler)

    layer = SpriteBatchNodeOffsetAnchorScale.initLayer(layer)
    titleLabel:setString("SpriteBatchNode offset + anchor + scale")
    subtitleLabel:setString("")

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

    local s = CCDirector:sharedDirector():getWinSize()
    
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")

    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(ccp(s.width / 4 * (i + 1), s.height / 2))

        local point = CCSprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        layer:addChild(point, 1)

        if i == 0 then
            sprite:setAnchorPoint(ccp(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(ccp(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(ccp(1, 1))
        end

        point:setPosition(sprite:getPosition())

        local animFrames = CCArray:create()
        for j = 0, 13 do
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png", j + 1))
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create(CCAnimate:create(animation)))

        local actionArray = CCArray:create()
        local skewX = CCSkewBy:create(2, 45, 0)
        actionArray:addObject(skewX)
        local skewX_back = skewX:reverse()
        actionArray:addObject(skewX_back)
        local skewY = CCSkewBy:create(2, 0, 45)
        actionArray:addObject(skewY)
        local skewY_back = skewY:reverse()
        actionArray:addObject(skewY_back)

        local seq_skew = CCSequence:create(actionArray)
        sprite:runAction(CCRepeatForever:create(seq_skew))

        layer:addChild(sprite, 0)
    end       

    return layer
end


function SpriteOffsetAnchorSkew.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteOffsetAnchorSkew.initLayer(layer)
    titleLabel:setString("SpriteBatchNode offset + anchor + scale")
    subtitleLabel:setString("")

    return layer
end
------------------------------------------------------------
-- SpriteOffsetAnchorRotationalSkew
------------------------------------------------------------
local SpriteOffsetAnchorRotationalSkew = {}
SpriteOffsetAnchorRotationalSkew.__index = SpriteOffsetAnchorRotationalSkew

function SpriteOffsetAnchorRotationalSkew.initLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()
    
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(ccp(s.width/4*(i+1), s.height/2))
        
        local point = CCSprite:create("Images/r1.png")
                            
        point:setScale(0.25)
        point:setPosition(ccp(sprite:getPosition()))
        layer:addChild(point, 1)
        
        if i == 0 then
            sprite:setAnchorPoint(ccp(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(ccp(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(ccp(1,1))
        end
        
        point:setPosition(ccp(sprite:getPosition()))
        
        local animFrames = CCArray:create()
        for i = 0,13 do
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png", (i+1)))
            animFrames:addObject(frame)
        end
        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create(CCAnimate:create(animation)))
        
        local actionArray = CCArray:create()
        local skewX = CCRotateBy:create(2, 45)
        actionArray:addObject(skewX)
        local skewX_back = skewX:reverse()
        actionArray:addObject(skewX_back)
        local skewY = CCRotateBy:create(2, -45)
        actionArray:addObject(skewY)
        local skewY_back = skewY:reverse()
        actionArray:addObject(skewY_back)
        
        local seq_skew = CCSequence:create(actionArray)
        sprite:runAction(CCRepeatForever:create(seq_skew))
        
        layer:addChild(sprite, 0)
    end
    return layer
end

function SpriteOffsetAnchorRotationalSkew.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteOffsetAnchorRotationalSkew.initLayer(layer)
    titleLabel:setString("Sprite offset + anchor + rotational skew")
    subtitleLabel:setString("")

    return layer
end


------------------------------------------------------------
-- SpriteOffsetAnchorRotationalSkew
------------------------------------------------------------
local SpriteBatchNodeOffsetAnchorSkew = {}
SpriteBatchNodeOffsetAnchorSkew.__index = SpriteBatchNodeOffsetAnchorSkew

function SpriteBatchNodeOffsetAnchorSkew.initLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()
    
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    local spritebatch = CCSpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritebatch)

    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(ccp(s.width / 4 * (i + 1), s.height / 2))

        local point = CCSprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(ccp(sprite:getPosition()))
        layer:addChild(point, 200)

        if i == 0 then
            sprite:setAnchorPoint(ccp(0, 0))
        elseif i == 1 then
            sprite:setAnchorPoint(ccp(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(ccp(1, 1))
        end

        point:setPosition(ccp(sprite:getPosition()))
        
        local animFrames = CCArray:create()
        for j = 0, 13 do
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png", j + 1))
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create(CCAnimate:create(animation)))

        local actionArray = CCArray:create()
        local skewX = CCSkewBy:create(2, 45, 0)
        actionArray:addObject(skewX)
        local skewX_back = skewX:reverse()
        actionArray:addObject(skewX_back)
        local skewY = CCSkewBy:create(2, 0, 45)
        actionArray:addObject(skewY)
        local skewY_back = skewY:reverse()
        actionArray:addObject(skewY_back)

        local seq_skew = CCSequence:create(actionArray)
        sprite:runAction(CCRepeatForever:create(seq_skew))

        spritebatch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorSkew.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteBatchNodeOffsetAnchorSkew.initLayer(layer)
    titleLabel:setString("SpriteBatchNode offset + anchor + skew")
    subtitleLabel:setString("")

    return layer
end

--
-- SpriteBatchNodeOffsetAnchorRotationalSkew
-- 
local SpriteBatchNodeOffsetAnchorRotationalSkew = {}
SpriteBatchNodeOffsetAnchorRotationalSkew.__index = SpriteBatchNodeOffsetAnchorRotationalSkew

function SpriteBatchNodeOffsetAnchorRotationalSkew.initLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()
    
    local cache = CCSpriteFrameCache:sharedSpriteFrameCache()
    cache:addSpriteFramesWithFile("animations/grossini.plist")
    cache:addSpriteFramesWithFile("animations/grossini_gray.plist", "animations/grossini_gray.png")
    
    local spritebatch = CCSpriteBatchNode:create("animations/grossini.png")
    layer:addChild(spritebatch)
    
    for i = 0, 2 do
        --
        -- Animation using Sprite batch
        --
        local sprite = CCSprite:createWithSpriteFrameName("grossini_dance_01.png")
        sprite:setPosition(ccp(s.width/4*(i+1), s.height/2))
        
        local point = CCSprite:create("Images/r1.png")
        
        point:setScale(0.25)
        point:setPosition(ccp(sprite:getPosition()))
        layer:addChild(point, 200)
        
        if i == 0 then
            sprite:setAnchorPoint(ccp(0,0))
        elseif i == 1 then
            sprite:setAnchorPoint(ccp(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(ccp(1,1))
        end
        
        point:setPosition(ccp(sprite:getPosition()))
        
        local animFrames = CCArray:create()
        for j = 0, 13 do
            local frame = cache:spriteFrameByName(string.format("grossini_dance_%02d.png", (j+1)))
            animFrames:addObject(frame)
        end

        local animation = CCAnimation:createWithSpriteFrames(animFrames, 0.3)
        sprite:runAction(CCRepeatForever:create(CCAnimate:create(animation)))
        
        local actionArray = CCArray:create()
        local skewX = CCRotateBy:create(2, 45)
        actionArray:addObject(skewX)
        local skewX_back = skewX:reverse()
        actionArray:addObject(skewX_back)
        local skewY = CCRotateBy:create(2, -45)
        actionArray:addObject(skewY)
        local skewY_back = skewY:reverse()
        actionArray:addObject(skewY_back)
        
        local seq_skew = CCSequence:create(actionArray)
        sprite:runAction(CCRepeatForever:create(seq_skew))
        
        spritebatch:addChild(sprite, i)
    end

    return layer
end

function SpriteBatchNodeOffsetAnchorRotationalSkew.create()
    local layer = CCLayer:create()
    initWithLayer(layer)

    layer = SpriteBatchNodeOffsetAnchorRotationalSkew.initLayer(layer)
    titleLabel:setString("SSpriteBatchNode offset + anchor + rot skew")
    subtitleLabel:setString("")

    return layer
end

function SpriteTest()
	local scene = CCScene:create()
	
	createFunctionTable = {
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
        SpriteBatchNodeOffsetAnchorRotationalSkew.create
    }

	ActionIdx = 0
	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	return scene
end
