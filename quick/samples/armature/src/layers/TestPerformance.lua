--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestPerformance = class("TestPerformance", ArmatureTestLayer)

local armaturePerformanceTag = 20000

function TestPerformance:ctor(index)
	TestPerformance.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestPerformance:refreshTitle()
    local subTitleInfo = self.subTitle(5) .. self._armatureCount
    local label        = self:getChildByTag(10001)
    label:setString(subTitleInfo)
end

function TestPerformance:addArmatureToParent(armature)
    self:addChild(armature, 0, armaturePerformanceTag + self._armatureCount)
end

function TestPerformance:removeArmatureFromParent(tag)
    self:removeChildByTag(armaturePerformanceTag + self._armatureCount, true)
end

function TestPerformance:addArmature(num)
    for i = 1, num do
        self._armatureCount = self._armatureCount + 1
        local armature = ccs.Armature:create("Knight_f/Knight")
        armature:getAnimation():playWithIndex(0)
        armature:setPosition(50 + self._armatureCount * 2, 150)
        armature:setScale(0.6)
        self:addArmatureToParent(armature)
    end

    self:refreshTitle()
end

function TestPerformance:onEnter()
    local function onIncrease(sender)
        self:addArmature(20)
    end

    local function onDecrease(sender)
        if self._armatureCount == 0 then
            return
        end

        for i = 1, 20 do
            self:removeArmatureFromParent(armaturePerformanceTag + self._armatureCount)
            self._armatureCount = self._armatureCount - 1
            self:refreshTitle()
        end
    end

    cc.ui.UIPushButton.new({})
        :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "-",
            size = 65,
            color = cc.c3b(0,200,20)
        }))
        :setButtonLabel("pressed", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "-",
            size = 80,
            color = cc.c3b(0,200,20)
        }))
        :onButtonClicked(onDecrease)
        :pos(display.cx - 40, display.top - 140)
        :addTo(self)

    cc.ui.UIPushButton.new({})
        :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "+",
            size = 65,
            color = cc.c3b(0,200,20)
        }))
        :setButtonLabel("pressed", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "+",
            size = 80,
            color = cc.c3b(0,200,20)
        }))
        :onButtonClicked(onIncrease)
        :pos(display.cx + 40, display.top - 140)
        :addTo(self)

    self._armatureCount = 0
    self._frames        = 0
    self._times         = 0
    self._lastTimes     = 0
    self._generated     = false

    self:addArmature(100)
end

return TestPerformance