--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestParticleDisplay = class("TestParticleDisplay", ArmatureTestLayer)

function TestParticleDisplay:ctor(index)
	TestParticleDisplay.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestParticleDisplay:onEnter()
    self.animationID = 0

    self.armature = ccs.Armature:create("robot")
    self.armature:getAnimation():playWithIndex(0)
    self.armature:setPosition(display.cx, display.cy)
    self.armature:setScale(0.48)
    self:addChild(self.armature)

    local p1 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
    local p2 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")

    local bone  = ccs.Bone:create("p1")
    bone:addDisplay(p1, 0)
    bone:changeDisplayWithIndex(0, true)
    bone:setIgnoreMovementBoneData(true)
    bone:setLocalZOrder(100)
    bone:setScale(1.2)
    self.armature:addBone(bone, "bady-a3")

    bone  = ccs.Bone:create("p2")
    bone:addDisplay(p2, 0)
    bone:changeDisplayWithIndex(0, true)
    bone:setIgnoreMovementBoneData(true)
    bone:setLocalZOrder(100)
    bone:setScale(1.2)
    self.armature:addBone(bone, "bady-a30")

    local function onTouchEnded()     
        self.animationID = (self.animationID + 1) % self.armature:getAnimation():getMovementCount()
        self.armature:getAnimation():playWithIndex(self.animationID)
    end

    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
    	if event.name=='began' then
    		return true
    	elseif event.name=='ended' then
    		onTouchEnded()
    	end
    end)
end

return TestParticleDisplay