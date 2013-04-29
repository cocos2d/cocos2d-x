local size = CCDirector:sharedDirector():getWinSize()
local layer = nil
local kTagSprite = 1

local function initWithLayer()
    local sprite = CCSprite:create(s_pPathGrossini)

    local bgLayer = CCLayerColor:create(ccc4(255,255,0,255))
    layer:addChild(bgLayer, -1)

    layer:addChild(sprite, 0, kTagSprite)
    sprite:setPosition(CCPointMake(20,150))

    sprite:runAction(CCJumpTo:create(4, CCPointMake(300,48), 100, 4))

    bgLayer:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
                                                 CCFadeIn:create(1),
                                                 CCFadeOut:create(1))))

    local function onTouchEnded(x, y)
        local s = layer:getChildByTag(kTagSprite)
        s:stopAllActions()
        s:runAction(CCMoveTo:create(1, CCPointMake(x, y)))
        local posX, posY = s:getPosition()
        local o = x - posX
        local a = y - posY
        local at = math.atan(o / a) / math.pi * 180.0

        if a < 0 then
            if o < 0 then
                at = 180 + math.abs(at)
            else
                at = 180 - math.abs(at)
            end
        end
        s:runAction(CCRotateTo:create(1, at))
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return true
        elseif eventType == "ended" then
            return onTouchEnded(x, y)
        end
    end

    layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(onTouch)

    return layer
end

--------------------------------
-- Click And Move Test
--------------------------------
function ClickAndMoveTest()
    cclog("ClickAndMoveTest")
    local scene = CCScene:create()
    layer = CCLayer:create()

    initWithLayer()

    scene:addChild(CreateBackMenuItem())
    scene:addChild(layer)

    return scene
end
