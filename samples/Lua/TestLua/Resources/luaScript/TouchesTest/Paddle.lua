require "extern"
require "luaScript/VisibleRect"

Paddle = class("Paddle", function(texture)
    return cc.Sprite:createWithTexture(texture)
end)

Paddle.__index = Paddle

local kPaddleStateGrabbed = 0
local kPaddleStateUngrabbed = 1

Paddle._state = kPaddleStateGrabbed


function Paddle:rect()
    local  s = self:getTexture():getContentSize()
    return cc.rect(-s.width / 2, -s.height / 2, s.width, s.height)
end

function Paddle:containsTouchLocation(x,y)
    local position = cc.p(self:getPosition())
    local  s = self:getTexture():getContentSize()
    local touchRect = cc.rect(-s.width / 2 + position.x, -s.height / 2 + position.y, s.width, s.height)
    local b = cc.rectContainsPoint(touchRect, cc.p(x,y))
    return b
end

function Paddle:paddleWithTexture(aTexture)
    local pPaddle = Paddle.new(aTexture)
    pPaddle._state = kPaddleStateUngrabbed
    pPaddle:registerScriptHandler(function(tag)
    if "enter" == tag then
        pPaddle:onEnter()
    elseif "exit" == tag then
    end
end)
    return pPaddle
end

function Paddle:onEnter()
    local  listenner = cc.EventListenerTouchOneByOne:create()
    listenner:setSwallowTouches(true)
    listenner:registerScriptHandler(function(touch, event)
            print(string.format("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch:getId(), touch:getLocation().x, touch:getLocation().y))
            if (self._state ~= kPaddleStateUngrabbed) then 
                return false
            end

            if not self:containsTouchLocation(touch:getLocation().x,touch:getLocation().y) then
                return false
            end

            self._state = kPaddleStateGrabbed
            return true
        end,cc.Handler.EVENT_TOUCH_BEGAN )
    listenner:registerScriptHandler(function(touch, event)
            print(string.format("Paddle::onTouchMoved id = %d, x = %f, y = %f", touch:getId(), touch:getLocation().x, touch:getLocation().y))
            assert(self._state == kPaddleStateGrabbed, "Paddle - Unexpected state!")
            local touchPoint = touch:getLocation()
            local curPosX,curPosY = self:getPosition()
            self:setPosition(cc.p(touchPoint.x,curPosY))
        end,cc.Handler.EVENT_TOUCH_MOVED )
    listenner:registerScriptHandler(function(touch, event)
            assert(self._state == kPaddleStateGrabbed, "Paddle - Unexpected state!")
            self._state = kPaddleStateUngrabbed
        end,cc.Handler.EVENT_TOUCH_ENDED )
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listenner, self)
end
