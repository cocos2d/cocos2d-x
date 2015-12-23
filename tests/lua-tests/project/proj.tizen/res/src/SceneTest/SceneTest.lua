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
    local ret = cc.Layer:create()

    local function onPushScene(tag, pSender)
        local scene = cc.Scene:create()
        local  layer = SceneTestLayer2()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene( scene )
    end

    local function onPushSceneTran(tag, pSender)
        local scene = cc.Scene:create()
        local  layer = SceneTestLayer2()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene( cc.TransitionSlideInT:create(1, scene) )
    end


    local function onQuit(tag, pSender)
        cclog("onQuit")
    end

    local  item1 = cc.MenuItemFont:create( "Test pushScene")
    item1:registerScriptTapHandler(onPushScene)
    local  item2 = cc.MenuItemFont:create( "Test pushScene w/transition")
    item2:registerScriptTapHandler(onPushSceneTran)
    local  item3 = cc.MenuItemFont:create( "Quit")
    item3:registerScriptTapHandler(onQuit)

    local  menu = cc.Menu:create(item1, item2, item3)
    menu:alignItemsVertically()

    ret:addChild( menu )

    local s = cc.Director:getInstance():getWinSize()
    local  sprite = cc.Sprite:create(s_pPathGrossini)
    ret:addChild(sprite)
    sprite:setPosition( cc.p(s.width-40, s.height/2) )
    local  rotate = cc.RotateBy:create(2, 360)
    local  repeatAction = cc.RepeatForever:create(rotate)
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
    local ret = cc.Layer:create()
    local m_timeCounter = 0

    local function onGoBack(tag, pSender)
        cc.Director:getInstance():popScene()
    end

    local function onReplaceScene(tag, pSender)
        local scene = cc.Scene:create()
        local  layer = SceneTestLayer3()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():replaceScene( scene )
    end


    local function onReplaceSceneTran(tag, pSender)
        local scene = cc.Scene:create()
        local  layer = SceneTestLayer3()
        scene:addChild(layer, 0)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():replaceScene( cc.TransitionFlipX:create(2, scene) )
    end

    local  item1 = cc.MenuItemFont:create( "replaceScene")
    item1:registerScriptTapHandler(onReplaceScene)
    local  item2 = cc.MenuItemFont:create( "replaceScene w/transition")
    item2:registerScriptTapHandler(onReplaceSceneTran)
    local  item3 = cc.MenuItemFont:create( "Go Back")
    item3:registerScriptTapHandler(onGoBack)
    local  menu = cc.Menu:create(item1, item2, item3)
    menu:alignItemsVertically()

    ret:addChild( menu )

    local s = cc.Director:getInstance():getWinSize()
    local  sprite = cc.Sprite:create(s_pPathGrossini)
    ret:addChild(sprite)
    sprite:setPosition( cc.p(s.width-40, s.height/2) )
    local  rotate = cc.RotateBy:create(2, 360)
    local  repeat_action = cc.RepeatForever:create(rotate)
    sprite:runAction(repeat_action)

    return ret
end

--------------------------------------------------------------------
--
-- SceneTestLayer3
--
--------------------------------------------------------------------

SceneTestLayer3 = function()
    local ret = cc.LayerColor:create(cc.c4b(0,0,255,255))
    local s = cc.Director:getInstance():getWinSize()

    local function item0Clicked(tag, pSender)
        local newScene = cc.Scene:create()
        newScene:addChild(SceneTestLayer3())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, newScene, cc.c3b(0,255,255)))
    end

    local function item1Clicked(tag, pSender)
        cc.Director:getInstance():popScene()
    end

    local function item2Clicked(tag, pSender)
        cc.Director:getInstance():popToRootScene()
    end

    local item0 = cc.MenuItemFont:create("Touch to pushScene (self)")
    item0:registerScriptTapHandler(item0Clicked)
    local item1 = cc.MenuItemFont:create("Touch to popScene")
    item1:registerScriptTapHandler(item1Clicked)
    local item2 = cc.MenuItemFont:create("Touch to popToRootScene")
    item2:registerScriptTapHandler(item2Clicked)

    local menu = cc.Menu:create(item0, item1, item2)
    ret:addChild(menu)
    menu:alignItemsVertically()

    local  sprite = cc.Sprite:create(s_pPathGrossini)
    ret:addChild(sprite)
    sprite:setPosition( cc.p(s.width/2, 40) )
    local  rotate = cc.RotateBy:create(2, 360)
    local  repeatAction = cc.RepeatForever:create(rotate)
    sprite:runAction(repeatAction)
    return ret
end



function SceneTestMain()
    cclog("SceneTestMain")
    local scene = cc.Scene:create()
    local  layer = SceneTestLayer1()
    scene:addChild(layer, 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
