local    MID_PUSHSCENE        = 100
local    MID_PUSHSCENETRAN    = 101
local    MID_QUIT             = 102
local    MID_REPLACESCENE     = 103
local    MID_REPLACESCENETRAN = 104
local    MID_GOBACK           = 105

local SceneTestLayer1 = nil
local SceneTestLayer2 = nil
local SceneTestLayer3 = nil

--------------------------------------------------------------------
--
-- SceneTestLayer1
--
--------------------------------------------------------------------

SceneTestLayer1 = function()
    local ret = CCLayer:create()

    local function onPushScene(tag, pSender)
        local scene = CCScene:create()
        local  layer = SceneTestLayer2()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene( scene )
    end

    local function onPushSceneTran(tag, pSender)
        local scene = CCScene:create()
        local  layer = SceneTestLayer2()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene( CCTransitionSlideInT:create(1, scene) )
    end


    local function onQuit(tag, pSender)
        cclog("onQuit")
    end

    local  item1 = CCMenuItemFont:create( "Test pushScene")
    item1:registerScriptTapHandler(onPushScene)
    local  item2 = CCMenuItemFont:create( "Test pushScene w/transition")
    item2:registerScriptTapHandler(onPushSceneTran)
    local  item3 = CCMenuItemFont:create( "Quit")
    item3:registerScriptTapHandler(onQuit)

    local arr = CCArray:create()
    arr:addObject(item1)
    arr:addObject(item2)
    arr:addObject(item3)
    local  menu = CCMenu:createWithArray(arr)
    menu:alignItemsVertically()

    ret:addChild( menu )

    local s = CCDirector:sharedDirector():getWinSize()
    local  sprite = CCSprite:create(s_pPathGrossini)
    ret:addChild(sprite)
    sprite:setPosition( ccp(s.width-40, s.height/2) )
    local  rotate = CCRotateBy:create(2, 360)
    local  repeatAction = CCRepeatForever:create(rotate)
    sprite:runAction(repeatAction)

    local function onNodeEvent(event)
        if event == "enter" then
            cclog("SceneTestLayer1#onEnter")
        elseif event == "enterTransitionFinish" then
            cclog("SceneTestLayer1#onEnterTransitionDidFinish")
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end

--------------------------------------------------------------------
--
-- SceneTestLayer2
--
--------------------------------------------------------------------

SceneTestLayer2 = function()
    local ret = CCLayer:create()
    local m_timeCounter = 0

    local function onGoBack(tag, pSender)
        CCDirector:sharedDirector():popScene()
    end

    local function onReplaceScene(tag, pSender)
        local scene = CCScene:create()
        local  layer = SceneTestLayer3()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():replaceScene( scene )
    end


    local function onReplaceSceneTran(tag, pSender)
        local scene = CCScene:create()
        local  layer = SceneTestLayer3()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():replaceScene( CCTransitionFlipX:create(2, scene) )
    end

    local  item1 = CCMenuItemFont:create( "replaceScene")
    item1:registerScriptTapHandler(onReplaceScene)
    local  item2 = CCMenuItemFont:create( "replaceScene w/transition")
    item2:registerScriptTapHandler(onReplaceSceneTran)
    local  item3 = CCMenuItemFont:create( "Go Back")
    item3:registerScriptTapHandler(onGoBack)
    local arr = CCArray:create()
    arr:addObject(item1)
    arr:addObject(item2)
    arr:addObject(item3)
    local  menu = CCMenu:createWithArray(arr)
    menu:alignItemsVertically()

    ret:addChild( menu )

    local s = CCDirector:sharedDirector():getWinSize()
    local  sprite = CCSprite:create(s_pPathGrossini)
    ret:addChild(sprite)
    sprite:setPosition( ccp(s.width-40, s.height/2) )
    local  rotate = CCRotateBy:create(2, 360)
    local  repeat_action = CCRepeatForever:create(rotate)
    sprite:runAction(repeat_action)

    return ret
end

--------------------------------------------------------------------
--
-- SceneTestLayer3
--
--------------------------------------------------------------------

SceneTestLayer3 = function()
    local ret = CCLayerColor:create(ccc4(0,0,255,255))
    local s = CCDirector:sharedDirector():getWinSize()

    local function item0Clicked(tag, pSender)
        local newScene = CCScene:create()
        newScene:addChild(SceneTestLayer3())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, newScene, ccc3(0,255,255)))
    end

    local function item1Clicked(tag, pSender)
        CCDirector:sharedDirector():popScene()
    end

    local function item2Clicked(tag, pSender)
        CCDirector:sharedDirector():popToRootScene()
    end

    local item0 = CCMenuItemFont:create("Touch to pushScene (self)")
    item0:registerScriptTapHandler(item0Clicked)
    local item1 = CCMenuItemFont:create("Touch to popScene")
    item1:registerScriptTapHandler(item1Clicked)
    local item2 = CCMenuItemFont:create("Touch to popToRootScene")
    item2:registerScriptTapHandler(item2Clicked)

    local arr = CCArray:create()
    arr:addObject(item0)
    arr:addObject(item1)
    arr:addObject(item2)

    local menu = CCMenu:createWithArray(arr)
    ret:addChild(menu)
    menu:alignItemsVertically()

    local  sprite = CCSprite:create(s_pPathGrossini)
    ret:addChild(sprite)
    sprite:setPosition( ccp(s.width/2, 40) )
    local  rotate = CCRotateBy:create(2, 360)
    local  repeatAction = CCRepeatForever:create(rotate)
    sprite:runAction(repeatAction)
    return ret
end



function SceneTestMain()
    cclog("SceneTestMain")
    local scene = CCScene:create()
    local  layer = SceneTestLayer1()
    scene:addChild(layer, 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
