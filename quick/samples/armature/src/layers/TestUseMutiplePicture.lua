--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestUseMutiplePicture = class("TestUseMutiplePicture", ArmatureTestLayer)

function TestUseMutiplePicture:ctor(index)
	TestUseMutiplePicture.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestUseMutiplePicture:onEnter()
    self.displayIndex = 1

    self.armature = ccs.Armature:create("Knight_f/Knight")
    self.armature:getAnimation():playWithIndex(0)
    self.armature:setPosition(cc.p(display.left + 70, display.cy))
    self.armature:setScale(1.2)
    self:addChild(self.armature)

    local weapon =
    {
        "weapon_f-sword.png",
        "weapon_f-sword2.png",
        "weapon_f-sword3.png",
        "weapon_f-sword4.png",
        "weapon_f-sword5.png",
        "weapon_f-knife.png",
        "weapon_f-hammer.png",
    }

    local i = 1
    for i = 1,table.getn(weapon) do
        local skin = ccs.Skin:createWithSpriteFrameName(weapon[i])
        self.armature:getBone("weapon"):addDisplay(skin, i - 1)
    end

    local function onTouchEnded(touches, event)     
        self.displayIndex = (self.displayIndex + 1) % (table.getn(weapon) - 1)
        self.armature:getBone("weapon"):changeDisplayWithIndex(self.displayIndex, true)
    end

    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
    	if event.name=='began' then
    		return true
    	elseif event.name=='ended' then
    		onTouchEnded()
    	end
    end)
end

return TestUseMutiplePicture