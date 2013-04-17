
require "luaScript/extern"
require "luaScript/VisibleRect"
require "luaScript/TouchesTest/Paddle"

Ball = class("Ball", function(texture)
    return CCSprite:createWithTexture(texture)
end)

Ball.__index = Ball

Ball.m_velocity = ccp(0,0)

local M_PI = 3.1415926

function Ball:radius()
    local  size = self:getTexture():getContentSize()
    return size.width/2
end

function Ball:move(delta)
    local getPosition = ccp(self:getPosition())
    local position = ccpMult(self.m_velocity, delta)
    self:setPosition( ccpAdd(getPosition, position) );
    
    if (getPosition.x > VisibleRect:right().x - self:radius()) then
        self:setPosition( ccp( VisibleRect:right().x - self:radius(), getPosition.y) );
        self.m_velocity.x = self.m_velocity.x * -1;
    elseif (getPosition.x < VisibleRect:left().x + self:radius()) then
        self:setPosition( ccp(VisibleRect:left().x + self:radius(), getPosition.y) );
        self.m_velocity.x = self.m_velocity.x * -1;
    end
end

function Ball:collideWithPaddle(paddle)
    local paddleRect = paddle:rect()
    local paddleGetPosition = ccp(paddle:getPosition())
    local selfGetPosition = ccp(self:getPosition())

    paddleRect.origin.x = paddleRect.origin.x + paddleGetPosition.x;
    paddleRect.origin.y = paddleRect.origin.y + paddleGetPosition.y;

    local lowY  = paddleRect:getMinY();
    local midY  = paddleRect:getMidY();
    local highY = paddleRect:getMaxY();

    local leftX  = paddleRect:getMinX();
    local rightX = paddleRect:getMaxX();

    if (selfGetPosition.x > leftX and selfGetPosition.x < rightX)  then

        local hit = false;
        local angleOffset = 0.0; 

        if (selfGetPosition.y > midY and selfGetPosition.y <= highY + self:radius()) then
            self:setPosition( ccp(selfGetPosition.x, highY + self:radius()) );
            hit = true;
            angleOffset = M_PI / 2;
        elseif (selfGetPosition.y < midY and selfGetPosition.y >= lowY - self:radius()) then
            self:setPosition( ccp(selfGetPosition.x, lowY - self:radius()) );
            hit = true;
            angleOffset = -M_PI / 2;
        end

        if (hit) then
            local hitAngle = ccpToAngle(ccpSub(paddleGetPosition, paddleGetPosition)) + angleOffset;

            local scalarVelocity = ccpLength(self.m_velocity) * 1.05;
            local velocityAngle = -ccpToAngle(self.m_velocity) + 0.5 * hitAngle;

            self.m_velocity = ccpMult(ccpForAngle(velocityAngle), scalarVelocity);
        end
    end   

end

function Ball:setVelocity(velocity)
    self.m_velocity = velocity
end

function Ball:getVelocity()
    return self.m_velocity
end

function Ball.ballWithTexture(aTexture)

    if(aTexture == nil) then
        cclog("in ballWithTexture aTexture == nil")
    end

    local ball = Ball.new(aTexture)
    ball:autorelease()
    return ball
end

