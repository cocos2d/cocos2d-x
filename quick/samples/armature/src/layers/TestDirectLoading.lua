--
-- Author: SunLightJuly
-- Date: 2014-07-29 11:04:34
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestDirectLoading = class("TestDirectLoading", ArmatureTestLayer)

function TestDirectLoading:ctor(index)
	TestDirectLoading.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestDirectLoading:onEnter()
    local manager = ccs.ArmatureDataManager:getInstance()
    manager:removeArmatureFileInfo("armature/bear.ExportJson")
    manager:addArmatureFileInfo("armature/bear.ExportJson")
    local armature = ccs.Armature:create("bear")
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(cc.p(display.cx, display.cy))
    self:addChild(armature)
end

return TestDirectLoading