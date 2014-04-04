local size = cc.Director:getInstance():getWinSize()
local layer = nil
local kTagSprite = 1

local function initWithLayer()
    local sprite = cc.Sprite:create(s_pPathGrossini)

    local bgLayer = cc.LayerColor:create(cc.c4b(255,255,0,255))
    layer:addChild(bgLayer, -1)

    layer:addChild(sprite, 0, kTagSprite)
    sprite:setPosition(cc.p(20,150))

    sprite:runAction(cc.JumpTo:create(4, cc.p(300,48), 100, 4))

    bgLayer:runAction(cc.RepeatForever:create(cc.Sequence:create(
                                                 cc.FadeIn:create(1),
                                                 cc.FadeOut:create(1))))

    local function onTouchBegan(touch, event)
        return true
    end

    local function onTouchEnded(touch, event)
        
        local location = touch:getLocation()

        local s = layer:getChildByTag(kTagSprite)
        s:stopAllActions()
        s:runAction(cc.MoveTo:create(1, cc.p(location.x, location.y)))
        local posX, posY = s:getPosition()
        local o = location.x - posX
        local a = location.y - posY
        local at = math.atan(o / a) / math.pi * 180.0

        if a < 0 then
            if o < 0 then
                at = 180 + math.abs(at)
            else
                at = 180 - math.abs(at)
            end
        end
        s:runAction(cc.RotateTo:create(1, at))
    end

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    return layer
end

--------------------------------
-- Click And Move Test
--------------------------------
function ClickAndMoveTest()
    cclog("ClickAndMoveTest")
    local scene = cc.Scene:create()
    layer = cc.Layer:create()

    initWithLayer()
    scene:addChild(layer)
    scene:addChild(CreateBackMenuItem())
    

    return scene
end
