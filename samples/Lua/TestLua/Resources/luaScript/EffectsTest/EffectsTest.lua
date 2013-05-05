require "luaScript/EffectsTest/EffectsName"


local ActionIdx = -1
local size = CCDirector:sharedDirector():getWinSize()
local kTagTextLayer  = 1
local kTagBackground = 1
local kTagLabel      = 2
local MAX_LAYER      = 22

local testLayer  = nil
local titleLabel = nil
local entry      = nil

local function checkAnim(dt)
    local s2 = testLayer:getChildByTag(kTagBackground)
    if s2 == nil then
        return
    end

    if s2:numberOfRunningActions() == 0 then
        if s2:getGrid() ~= nil then
            s2:setGrid(nil)
        end
    end
end

local function onEnterOrExit(tag)
    local scheduler = CCDirector:sharedDirector():getScheduler()
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

--------------------------------------
--  Shaky3DDemo
--------------------------------------
local function Shaky3DDemo(t)
    return CCShaky3D:create(t, CCSizeMake(15,10), 5, false);
end

--------------------------------------
--  Waves3DDemo
--------------------------------------
local function Waves3DDemo(t)
    return CCWaves3D:create(t, CCSizeMake(15,10), 5, 40);
end

--------------------------------------
--  FlipX3DDemo
--------------------------------------
local function FlipX3DDemo(t)
    local flipx  = CCFlipX3D:create(t)
    local flipx_back = flipx:reverse()
    local delay = CCDelayTime:create(2)

    local array = CCArray:create()
    array:addObject(flipx)
    array:addObject(flipx_back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  FlipY3DDemo
--------------------------------------
local function FlipY3DDemo(t)
    local flipy  = CCFlipY3D:create(t)
    local flipy_back = flipy:reverse()
    local delay = CCDelayTime:create(2)

    local array = CCArray:create()
    array:addObject(flipy)
    array:addObject(flipy_back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  Lens3DDemo
--------------------------------------
local function Lens3DDemo(t)
    return CCLens3D:create(t, CCSizeMake(15,10), ccp(size.width/2,size.height/2), 240);
end

--------------------------------------
--  Ripple3DDemo
--------------------------------------
local function Ripple3DDemo(t)
    return CCRipple3D:create(t, CCSizeMake(32,24), ccp(size.width/2,size.height/2), 240, 4, 160);
end

--------------------------------------
--  LiquidDemo
--------------------------------------
local function LiquidDemo(t)
    return CCLiquid:create(t, CCSizeMake(16,12), 4, 20);
end

--------------------------------------
--  WavesDemo
--------------------------------------
local function WavesDemo(t)
    return CCWaves:create(t, CCSizeMake(16,12), 4, 20, true, true);
end

--------------------------------------
--  TwirlDemo
--------------------------------------
local function TwirlDemo(t)
    return CCTwirl:create(t, CCSizeMake(12,8), ccp(size.width/2, size.height/2), 1, 2.5);
end

--------------------------------------
--  ShakyTiles3DDemo
--------------------------------------
local function ShakyTiles3DDemo(t)
    return CCShakyTiles3D:create(t, CCSizeMake(16,12), 5, false);
end

--------------------------------------
--  ShatteredTiles3DDemo
--------------------------------------
local function ShatteredTiles3DDemo(t)
    return CCShatteredTiles3D:create(t, CCSizeMake(16,12), 5, false);
end

--------------------------------------
--  ShuffleTilesDemo
--------------------------------------
local function ShuffleTilesDemo(t)
    local shuffle = CCShuffleTiles:create(t, CCSizeMake(16,12), 25);
    local shuffle_back = shuffle:reverse()
    local delay = CCDelayTime:create(2)

    local array = CCArray:create()
    array:addObject(shuffle)
    array:addObject(shuffle_back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  FadeOutTRTilesDemo
--------------------------------------
local function FadeOutTRTilesDemo(t)
    local fadeout = CCFadeOutTRTiles:create(t, CCSizeMake(16,12));
    local back = fadeout:reverse()
    local delay = CCDelayTime:create(0.5)

    local array = CCArray:create()
    array:addObject(fadeout)
    array:addObject(back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  FadeOutBLTilesDemo
--------------------------------------
local function FadeOutBLTilesDemo(t)
    local fadeout = CCFadeOutBLTiles:create(t, CCSizeMake(16,12));
    local back = fadeout:reverse()
    local delay = CCDelayTime:create(0.5)

    local array = CCArray:create()
    array:addObject(fadeout)
    array:addObject(back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  FadeOutUpTilesDemo
--------------------------------------
local function FadeOutUpTilesDemo(t)
    local fadeout = CCFadeOutUpTiles:create(t, CCSizeMake(16,12));
    local back = fadeout:reverse()
    local delay = CCDelayTime:create(0.5)

    local array = CCArray:create()
    array:addObject(fadeout)
    array:addObject(back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  FadeOutDownTilesDemo
--------------------------------------
local function FadeOutDownTilesDemo(t)
    local fadeout = CCFadeOutDownTiles:create(t, CCSizeMake(16,12));
    local back = fadeout:reverse()
    local delay = CCDelayTime:create(0.5)

    local array = CCArray:create()
    array:addObject(fadeout)
    array:addObject(back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  TurnOffTilesDemo
--------------------------------------
local function TurnOffTilesDemo(t)
    local fadeout = CCTurnOffTiles:create(t, CCSizeMake(48,32), 25);
    local back = fadeout:reverse()
    local delay = CCDelayTime:create(0.5)

    local array = CCArray:create()
    array:addObject(fadeout)
    array:addObject(back)
    array:addObject(delay)
    return CCSequence:create(array)
end

--------------------------------------
--  WavesTiles3DDemo
--------------------------------------
local function WavesTiles3DDemo(t)
    return CCWavesTiles3D:create(t, CCSizeMake(15,10), 4, 120);
end

--------------------------------------
--  JumpTiles3DDemo
--------------------------------------
local function JumpTiles3DDemo(t)
    return CCJumpTiles3D:create(t, CCSizeMake(15,10), 2, 30);
end

--------------------------------------
--  SplitRowsDemo
--------------------------------------
local function SplitRowsDemo(t)
    return CCSplitRows:create(t, 9);
end

--------------------------------------
--  SplitColsDemo
--------------------------------------
local function SplitColsDemo(t)
    return CCSplitCols:create(t, 9);
end

--------------------------------------
--  PageTurn3DDemo
--------------------------------------
local function PageTurn3DDemo(t)
    CCDirector:sharedDirector():setDepthTest(true)
    return CCPageTurn3D:create(t, CCSizeMake(15,10));
end

--------------------------------------
--  Effects Test
--------------------------------------
local function createEffect(idx, t)
    CCDirector:sharedDirector():setDepthTest(false)
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
    testLayer = CCLayerColor:create(ccc4(32,128,32,255))

    local x, y = size.width, size.height

    local node = CCNode:create()
    local effect = createEffect(ActionIdx, 3)
    node:runAction(effect)
    testLayer:addChild(node, 0, kTagBackground)

    local bg = CCSprite:create(s_back3)
    node:addChild(bg, 0)
    bg:setPosition(CCPointMake(size.width / 2, size.height / 2))

    local grossini = CCSprite:create(s_pPathSister2)
    node:addChild(grossini, 1)
    grossini:setPosition( CCPointMake(x / 3, y / 2) )
    local sc = CCScaleBy:create(2, 5)
    local sc_back = sc:reverse()
    grossini:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(sc, sc_back)))

    local tamara = CCSprite:create(s_pPathSister1)
    node:addChild(tamara, 1)
    tamara:setPosition(CCPointMake(2 * x / 3, y / 2))
    local sc2 = CCScaleBy:create(2, 5)
    local sc2_back = sc2:reverse()
    tamara:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(sc2, sc2_back)))

    titleLabel = CCLabelTTF:create(EffectsList[ActionIdx], "Marker Felt", 32)
    titleLabel:setPosition(x / 2, y - 80)
    testLayer:addChild(titleLabel)
    titleLabel:setTag(kTagLabel)

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
    item1:setPosition(CCPointMake(size.width/2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(size.width/2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(size.width/2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))

    testLayer:addChild(menu, 1)

    testLayer:registerScriptHandler(onEnterOrExit)

    return testLayer
end

function EffectsTest()
    local scene = CCScene:create()

    ActionIdx = -1
    scene:addChild(nextAction())
    scene:addChild(CreateBackMenuItem())

    return scene
end
