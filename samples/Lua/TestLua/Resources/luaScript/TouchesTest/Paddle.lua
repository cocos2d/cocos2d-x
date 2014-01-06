require "extern"
require "luaScript/VisibleRect"

Paddle = class("Paddle", function(texture)
    return cc.Sprite:createWithTexture(texture)
end)

Paddle.__index = Paddle

local kPaddleStateGrabbed = 0
local kPaddleStateUngrabbed = 1

Paddle.m_state = kPaddleStateGrabbed


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

function Paddle:ccTouchBegan(x, y)
    if (self.m_state ~= kPaddleStateUngrabbed) then 
        return false
    end
    
    self.m_state = kPaddleStateGrabbed;
    return true;
end

function Paddle:ccTouchMoved(x, y)
    self:setPosition( cc.p(x,y) );
end

function Paddle:ccTouchEnded(x, y)
    self.m_state = kPaddleStateUngrabbed;
end

function Paddle:onTouch(eventType, x, y)
	if eventType == "began" then
		return self:ccTouchBegan(x,y)
    elseif eventType == "moved" then
        return self:ccTouchMoved(x,y)
    elseif eventType == "ended" then
        return self:ccTouchEnded(x, y)
    end
end

function Paddle:paddleWithTexture(aTexture)
    local pPaddle = Paddle.new(aTexture);
    self.m_state = kPaddleStateUngrabbed;
    return pPaddle;
end


