--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestFrameEvent = class("TestFrameEvent", ArmatureTestLayer)

local scheduler = require("framework.scheduler")
local frameEventActionTag = 10000

function TestFrameEvent:ctor(index)
	TestFrameEvent.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestFrameEvent:onEnter()
    local gridNode = cc.NodeGrid:create()

    local armature = ccs.Armature:create("HeroAnimation")
    armature:getAnimation():play("attack")
    armature:getAnimation():setSpeedScale(0.5)
    armature:setPosition(cc.p(display.cx - 50, display.cy -100))

    local function onFrameEvent( bone,evt,originFrameIndex,currentFrameIndex)
        if (not gridNode:getActionByTag(frameEventActionTag)) or (not gridNode:getActionByTag(frameEventActionTag):isDone()) then
            gridNode:stopAllActions()

            local action =  cc.ShatteredTiles3D:create(0.2, cc.size(16,12), 5, false)
            action:setTag(frameEventActionTag)
            gridNode:runAction(action)
        end
    end

    armature:getAnimation():setFrameEventCallFunc(onFrameEvent)
    gridNode:addChild(armature)

    self:addChild(gridNode)

    local function checkAction(dt)
        if gridNode:getNumberOfRunningActions() == 0 and gridNode:getGrid() ~= nil then
            gridNode:setGrid(nil)
        end
    end

    self.handle = scheduler.scheduleUpdateGlobal(checkAction)
end

function TestFrameEvent:onExit()
	scheduler.unscheduleGlobal(self.handle)
end

return TestFrameEvent