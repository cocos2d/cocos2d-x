require "src/testResource"
require "src/TouchesTest/Ball"
require "src/TouchesTest/Paddle"
require "src/VisibleRect"

local kHighPlayer = 0
local kLowPlayer = 1

local kStatusBarHeight = 0.0
 
local kSpriteTag = 0

local m_ball = nil
local m_ballStartingVelocity = nil
local m_paddles = {}
local layer = nil

local function backCallback(sender)
	local scene = cc.Scene:create()
	scene:addChild(CreateBackMenuItem())
	cc.Director:getInstance():replaceScene(scene)
end


local function resetAndScoreBallForPlayer(player)
    m_ballStartingVelocity = cc.pMul(m_ballStartingVelocity, -1.1);
    m_ball:setVelocity( m_ballStartingVelocity );
    m_ball:setPosition( VisibleRect:center() );
end

local function doStep(delta)
    m_ball:move(delta);

    for _,paddle in ipairs(m_paddles) do

        if(paddle == nil) then
            break
        end
        m_ball:collideWithPaddle( paddle );
    end

    local ballPosition = cc.p(m_ball:getPosition())
    if (ballPosition.y > VisibleRect:top().y - kStatusBarHeight + m_ball:radius()) then
        resetAndScoreBallForPlayer( kLowPlayer );
    elseif (ballPosition.y < VisibleRect:bottom().y-m_ball:radius()) then
        resetAndScoreBallForPlayer( kHighPlayer );
    end
    m_ball:draw();
end

local function CreateTouchesLayer()
    layer = cc.Layer:create()

    m_ballStartingVelocity = cc.p(20.0, -100.0);
    local mgr = cc.Director:getInstance():getTextureCache()
    local texture = mgr:addImage(s_Ball)
    m_ball = Ball.ballWithTexture(texture);

    m_ball:setPosition( VisibleRect:center() );
    m_ball:setVelocity( m_ballStartingVelocity );
    layer:addChild( m_ball );
    m_ball:retain();
    
    local paddleTexture = cc.Director:getInstance():getTextureCache():addImage(s_Paddle);
    
    local paddlesM = {}
    
    local paddle = Paddle:paddleWithTexture(paddleTexture);
    paddle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:bottom().y + 15) );
    paddlesM[#paddlesM+1] = paddle
    
    paddle = Paddle:paddleWithTexture( paddleTexture );
    paddle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - kStatusBarHeight - 15) );
    paddlesM[#paddlesM+1] = paddle
    
    paddle = Paddle:paddleWithTexture( paddleTexture );
    paddle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:bottom().y + 100) );
    paddlesM[#paddlesM+1] = paddle
    
    paddle = Paddle:paddleWithTexture( paddleTexture );
    paddle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - kStatusBarHeight - 100) );
    paddlesM[#paddlesM+1] = paddle

    m_paddles = paddlesM

    for i = 1,#paddlesM do
        paddle = paddlesM[i]

        if(paddle == nil) then
            break
        end

        layer:addChild(paddle);
    end

    -- schedule
    layer:scheduleUpdateWithPriorityLua(doStep, 0)
    return layer
end

local function nextAction()
    return CreateTouchesLayer()
end

function TouchesTest()
    local scene = cc.Scene:create()
    scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())
    return scene
end

