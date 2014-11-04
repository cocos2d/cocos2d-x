--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestAnimationEvent = class("TestAnimationEvent", ArmatureTestLayer)

function TestAnimationEvent:ctor(index)
	TestAnimationEvent.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestAnimationEvent:onEnter()
    local armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():play("Fire")
    armature:setScaleX(-0.24)
    armature:setScaleY(0.24)
    armature:setPosition(cc.p(display.left + 50, display.cy))

    local function callback1()
        armature:runAction(cc.ScaleTo:create(0.3, 0.24, 0.24))
        armature:getAnimation():play("FireMax", 10)
    end

    local function callback2()
        armature:runAction(cc.ScaleTo:create(0.3, -0.24, 0.24))
        armature:getAnimation():play("Fire", 10)
    end

    local function animationEvent(armatureBack,movementType,movementID)
        local id = movementID
        if movementType == ccs.MovementEventType.loopComplete then
            if id == "Fire" then
                local actionToRight = cc.MoveTo:create(2, cc.p(display.right - 50, display.cy))
                armatureBack:stopAllActions()
                armatureBack:runAction(cc.Sequence:create(actionToRight,cc.CallFunc:create(callback1)))
                armatureBack:getAnimation():play("Walk")
            elseif id == "FireMax" then
                local actionToLeft = cc.MoveTo:create(2, cc.p(display.left + 50, display.cy))
                armatureBack:stopAllActions()
                armatureBack:runAction(cc.Sequence:create(actionToLeft, cc.CallFunc:create(callback2)))
                armatureBack:getAnimation():play("Walk")
            end
        end
    end

    armature:getAnimation():setMovementEventCallFunc(animationEvent)

    self:addChild(armature)
end

return TestAnimationEvent