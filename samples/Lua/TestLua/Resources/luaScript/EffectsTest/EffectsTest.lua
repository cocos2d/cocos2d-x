require "luaScript/EffectsTest/EffectsName"


local ActionIdx = -1
local size = cc.Director:getInstance():getWinSize()
local kTagTextLayer  = 1
local kTagBackground = 1
local kTagLabel      = 2
local MAX_LAYER      = 22

local testLayer  = nil
local titleLabel = nil
local entry      = nil
local gridNodeTarget = nil

local function checkAnim(dt)

    if nil == gridNodeTarget then
        return
    end

    if gridNodeTarget:getNumberOfRunningActions() == 0 and nil ~=gridNodeTarget:getGrid() then
        gridNodeTarget:setGrid(nil)
    end
end

local function onEnterOrExit(tag)
    local scheduler = cc.Director:getInstance():getScheduler()
    if tag == "enter" then
        entry = scheduler:scheduleScriptFunc(checkAnim, 0, false)
    elseif tag == "exit" then
        scheduler:unscheduleScriptEntry(entry)
    end
end

local function backAction()
    ActionIdx = ActionIdx - 1
    if ActionIdx < 0 then
        ActionIdx = ActionIdx + MAX_LAYER
    end

    return CreateEffectsTestLayer()
end

local function restartAction()
    return CreateEffectsTestLayer()
end

local function nextAction()
    ActionIdx = ActionIdx + 1
    ActionIdx = math.mod(ActionIdx, MAX_LAYER)

    return CreateEffectsTestLayer()
end

local function backCallback(sender)
    local scene = cc.Scene:create()

    scene:addChild(backAction())
    scene:addChild(CreateBackMenuItem())

    cc.Director:getInstance():replaceScene(scene)
end

local function restartCallback(sender)
    local scene = cc.Scene:create()

    scene:addChild(restartAction())
    scene:addChild(CreateBackMenuItem())

    cc.Director:getInstance():replaceScene(scene)
end

local function nextCallback(sender)
    local scene = cc.Scene:create()

    scene:addChild(nextAction())
    scene:addChild(CreateBackMenuItem())

    cc.Director:getInstance():replaceScene(scene)
end

--------------------------------------
--  Shaky3DDemo
--------------------------------------
local function Shaky3DDemo(t)
    return cc.Shaky3D:create(t, cc.size(15,10), 5, false)
end

--------------------------------------
--  Waves3DDemo
--------------------------------------
local function Waves3DDemo(t)
    return cc.Waves3D:create(t, cc.size(15,10), 5, 40)
end

--------------------------------------
--  FlipX3DDemo
--------------------------------------
local function FlipX3DDemo(t)
    local flipx  = cc.FlipX3D:create(t)
    local flipx_back = flipx:reverse()
    local delay = cc.DelayTime:create(2)

    return cc.Sequence:create(flipx, flipx_back, delay)
end

--------------------------------------
--  FlipY3DDemo
--------------------------------------
local function FlipY3DDemo(t)
    local flipy  = cc.FlipY3D:create(t)
    local flipy_back = flipy:reverse()
    local delay = cc.DelayTime:create(2)

    return cc.Sequence:create(flipy, flipy_back, delay)
end

--------------------------------------
--  Lens3DDemo
--------------------------------------
local function Lens3DDemo(t)
    return cc.Lens3D:create(t, cc.size(15,10), cc.p(size.width/2,size.height/2), 240)
end

--------------------------------------
--  Ripple3DDemo
--------------------------------------
local function Ripple3DDemo(t)
    return cc.Ripple3D:create(t, cc.size(32,24), cc.p(size.width/2,size.height/2), 240, 4, 160)
end

--------------------------------------
--  LiquidDemo
--------------------------------------
local function LiquidDemo(t)
    return cc.Liquid:create(t, cc.size(16,12), 4, 20)
end

--------------------------------------
--  WavesDemo
--------------------------------------
local function WavesDemo(t)
    return cc.Waves:create(t, cc.size(16,12), 4, 20, true, true)
end

--------------------------------------
--  TwirlDemo
--------------------------------------
local function TwirlDemo(t)
    return cc.Twirl:create(t, cc.size(12,8), cc.p(size.width/2, size.height/2), 1, 2.5)
end

--------------------------------------
--  ShakyTiles3DDemo
--------------------------------------
local function ShakyTiles3DDemo(t)
    return cc.ShakyTiles3D:create(t, cc.size(16,12), 5, false)
end

--------------------------------------
--  ShatteredTiles3DDemo
--------------------------------------
local function ShatteredTiles3DDemo(t)
    return cc.ShatteredTiles3D:create(t, cc.size(16,12), 5, false)
end

--------------------------------------
--  ShuffleTilesDemo
--------------------------------------
local function ShuffleTilesDemo(t)
    local shuffle = cc.ShuffleTiles:create(t, cc.size(16,12), 25)
    local shuffle_back = shuffle:reverse()
    local delay = cc.DelayTime:create(2)

    return cc.Sequence:create(shuffle, shuffle_back, delay)
end

--------------------------------------
--  FadeOutTRTilesDemo
--------------------------------------
local function FadeOutTRTilesDemo(t)
    local fadeout = cc.FadeOutTRTiles:create(t, cc.size(16,12))
    local back = fadeout:reverse()
    local delay = cc.DelayTime:create(0.5)

    return cc.Sequence:create(fadeout, back, delay)
end

--------------------------------------
--  FadeOutBLTilesDemo
--------------------------------------
local function FadeOutBLTilesDemo(t)
    local fadeout = cc.FadeOutBLTiles:create(t, cc.size(16,12))
    local back = fadeout:reverse()
    local delay = cc.DelayTime:create(0.5)

    return cc.Sequence:create(fadeout, back, delay)
end

--------------------------------------
--  FadeOutUpTilesDemo
--------------------------------------
local function FadeOutUpTilesDemo(t)
    local fadeout = cc.FadeOutUpTiles:create(t, cc.size(16,12))
    local back = fadeout:reverse()
    local delay = cc.DelayTime:create(0.5)

    return cc.Sequence:create(fadeout, back, delay)
end

--------------------------------------
--  FadeOutDownTilesDemo
--------------------------------------
local function FadeOutDownTilesDemo(t)
    local fadeout = cc.FadeOutDownTiles:create(t, cc.size(16,12))
    local back = fadeout:reverse()
    local delay = cc.DelayTime:create(0.5)

    return cc.Sequence:create(fadeout, back, delay)
end

--------------------------------------
--  TurnOffTilesDemo
--------------------------------------
local function TurnOffTilesDemo(t)
    local fadeout = cc.TurnOffTiles:create(t, cc.size(48,32), 25)
    local back = fadeout:reverse()
    local delay = cc.DelayTime:create(0.5)

    return cc.Sequence:create(fadeout, back, delay)
end

--------------------------------------
--  WavesTiles3DDemo
--------------------------------------
local function WavesTiles3DDemo(t)
    return cc.WavesTiles3D:create(t, cc.size(15,10), 4, 120)
end

--------------------------------------
--  JumpTiles3DDemo
--------------------------------------
local function JumpTiles3DDemo(t)
    return cc.JumpTiles3D:create(t, cc.size(15,10), 2, 30)
end

--------------------------------------
--  SplitRowsDemo
--------------------------------------
local function SplitRowsDemo(t)
    return cc.SplitRows:create(t, 9)
end

--------------------------------------
--  SplitColsDemo
--------------------------------------
local function SplitColsDemo(t)
    return cc.SplitCols:create(t, 9)
end

--------------------------------------
--  PageTurn3DDemo
--------------------------------------
local function PageTurn3DDemo(t)
    cc.Director:getInstance():setDepthTest(true)
    return cc.PageTurn3D:create(t, cc.size(15,10))
end

--------------------------------------
--  Effects Test
--------------------------------------
local function createEffect(idx, t)
    cc.Director:getInstance():setDepthTest(false)
    local action = nil

    if idx == 0 then
        action = Shaky3DDemo(t)
    elseif idx == 1 then
        action = Waves3DDemo(t)
    elseif idx == 2 then
        action = FlipX3DDemo(t)
    elseif idx == 3 then
        action = FlipY3DDemo(t)
    elseif idx == 4 then
        action = Lens3DDemo(t)
    elseif idx == 5 then
        action = Ripple3DDemo(t)
    elseif idx == 6 then
        action = LiquidDemo(t)
    elseif idx == 7 then
        action = WavesDemo(t)
    elseif idx == 8 then
        action = TwirlDemo(t)
    elseif idx == 9 then
        action = ShakyTiles3DDemo(t)
    elseif idx == 10 then
        action = ShatteredTiles3DDemo(t)
    elseif idx == 11 then
        action = ShuffleTilesDemo(t)
    elseif idx == 12 then
        action = FadeOutTRTilesDemo(t)
    elseif idx == 13 then
        action = FadeOutBLTilesDemo(t)
    elseif idx == 14 then
        action = FadeOutUpTilesDemo(t)
    elseif idx == 15 then
        action = FadeOutDownTilesDemo(t)
    elseif idx == 16 then
        action = TurnOffTilesDemo(t)
    elseif idx == 17 then
        action = WavesTiles3DDemo(t)
    elseif idx == 18 then
        action = JumpTiles3DDemo(t)
    elseif idx == 19 then
        action = SplitRowsDemo(t)
    elseif idx == 20 then
        action = SplitColsDemo(t)
    elseif idx == 21 then
        action = PageTurn3DDemo(t)
    end

    return action
end

function CreateEffectsTestLayer()
    testLayer = cc.LayerColor:create(cc.c4b(32,128,32,255))


    gridNodeTarget = cc.NodeGrid:create()
    local effect = createEffect(ActionIdx, 3)
    gridNodeTarget:runAction(effect)
    testLayer:addChild(gridNodeTarget, 0, kTagBackground)
    
    local bg = cc.Sprite:create(s_back3)
    gridNodeTarget:addChild(bg, 0)
    bg:setPosition(VisibleRect:center())

    local grossini = cc.Sprite:create(s_pPathSister2)
    gridNodeTarget:addChild(grossini, 1)
    grossini:setPosition( cc.p(VisibleRect:left().x+VisibleRect:getVisibleRect().width/3,VisibleRect:center().y) )
    local sc = cc.ScaleBy:create(2, 5)
    local sc_back = sc:reverse()
    grossini:runAction( cc.RepeatForever:create(cc.Sequence:create(sc, sc_back) ) )

    local tamara = cc.Sprite:create(s_pPathSister1)
    gridNodeTarget:addChild(tamara, 1)
    tamara:setPosition( cc.p(VisibleRect:left().x+2*VisibleRect:getVisibleRect().width/3,VisibleRect:center().y) )
    local sc2 = cc.ScaleBy:create(2, 5)
    local sc2_back = sc2:reverse()
    tamara:runAction( cc.RepeatForever:create(cc.Sequence:create(sc2, sc2_back)) )

    local x, y = size.width, size.height

    titleLabel = cc.LabelTTF:create(EffectsList[ActionIdx], "Marker Felt", 32)
    titleLabel:setPosition(x / 2, y - 80)
    testLayer:addChild(titleLabel)
    titleLabel:setTag(kTagLabel)

    local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
    item1:registerScriptTapHandler(backCallback)
    item2:registerScriptTapHandler(restartCallback)
    item3:registerScriptTapHandler(nextCallback)

    local menu = cc.Menu:create()
    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)

    menu:setPosition(cc.p(0, 0))
    item1:setPosition(cc.p(size.width/2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(cc.p(size.width/2, item2:getContentSize().height / 2))
    item3:setPosition(cc.p(size.width/2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))

    testLayer:addChild(menu, 1)

    testLayer:registerScriptHandler(onEnterOrExit)

    return testLayer
end

function EffectsTest()
    local scene = cc.Scene:create()

    ActionIdx = -1
    scene:addChild(nextAction())
    scene:addChild(CreateBackMenuItem())

    return scene
end
