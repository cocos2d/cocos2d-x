--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestDragonBones20 = class("TestDragonBones20", ArmatureTestLayer)

function TestDragonBones20:ctor(index)
	TestDragonBones20.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestDragonBones20:onEnter()
    local armature = ccs.Armature:create("Dragon")
    armature:getAnimation():playWithIndex(1)
    armature:getAnimation():setSpeedScale(0.4)
    armature:setPosition(cc.p(display.cx, display.cy * 0.3))
    armature:setScale(0.6)
    self:addChild(armature)
end

return TestDragonBones20