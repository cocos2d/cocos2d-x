--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestCSWithSkeleton = class("TestCSWithSkeleton", ArmatureTestLayer)

function TestCSWithSkeleton:ctor(index)
	TestCSWithSkeleton.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestCSWithSkeleton:onEnter()
    local armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():playWithIndex(0)
    armature:setScale(0.2)
    armature:setAnchorPoint(cc.p(0.5, 0.5))
    armature:setPosition(cc.p(display.cx, display.cy))
    self:addChild(armature)
end

return TestCSWithSkeleton