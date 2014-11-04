--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestChangeZorder = class("TestChangeZorder", ArmatureTestLayer)

local scheduler = require("framework.scheduler")

function TestChangeZorder:ctor(index)
	TestChangeZorder.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestChangeZorder:onEnter()
    self.currentTag = -1

    local armature = ccs.Armature:create("Knight_f/Knight")
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(cc.p(display.cx, display.cy - 100 ))
    -- armature:setScale(0.6)
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():playWithIndex(0)
    armature:setScale(0.24)
    armature:setPosition(cc.p(display.cx, display.cy - 100))
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    armature = ccs.Armature:create("Dragon")
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(cc.p(display.cx, display.cy - 100))
    armature:setScale(0.6)
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    local function changeZorder()
        local node = self:getChildByTag(self.currentTag)
        node:setLocalZOrder(math.random(0,1) * 3)
        self.currentTag = (self.currentTag + 1) % 3
    end

    self.handle = scheduler.scheduleGlobal(changeZorder, 1.0)
end

function TestChangeZorder:onExit()
	scheduler.unscheduleGlobal(self.handle)
end

return TestChangeZorder