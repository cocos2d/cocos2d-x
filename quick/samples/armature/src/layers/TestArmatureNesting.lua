--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestArmatureNesting = class("TestArmatureNesting", ArmatureTestLayer)

function TestArmatureNesting:ctor(index)
	TestArmatureNesting.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestArmatureNesting:onEnter()
    self.weaponIndex = 0

    self.armature = ccs.Armature:create("cyborg")
    self.armature:getAnimation():playWithIndex(1)
    self.armature:setPosition(display.cx, display.cy)
    self.armature:setScale(1.2)
    self.armature:getAnimation():setSpeedScale(0.4)
    self:addChild(self.armature)

    local function onTouchEnded(touches, event)     
        self.weaponIndex = (self.weaponIndex + 1) % 4
        self.armature:getBone("armInside"):getChildArmature():getAnimation():playWithIndex(self.weaponIndex)
        self.armature:getBone("armOutside"):getChildArmature():getAnimation():playWithIndex(self.weaponIndex)
    end

    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
    	if event.name=='began' then
    		return true
    	elseif event.name=='ended' then
    		onTouchEnded()
    	end
    end)
end

return TestArmatureNesting