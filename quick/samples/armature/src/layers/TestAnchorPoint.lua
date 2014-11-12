--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestAnchorPoint = class("TestAnchorPoint", ArmatureTestLayer)

function TestAnchorPoint:ctor(index)
	TestAnchorPoint.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestAnchorPoint:onEnter()
    for  i = 1 , 5 do
        local armature = ccs.Armature:create("Cowboy")
        armature:getAnimation():playWithIndex(0)
        armature:setPosition(display.cx, display.cy)
        armature:setScale(0.2)
        self:addChild(armature, 0, i)
    end

    self:getChildByTag(1):setAnchorPoint(cc.p(0,0))
    self:getChildByTag(2):setAnchorPoint(cc.p(0,1))
    self:getChildByTag(3):setAnchorPoint(cc.p(1,0))
    self:getChildByTag(4):setAnchorPoint(cc.p(1,1))
    self:getChildByTag(5):setAnchorPoint(cc.p(0.5,0.5))
end

return TestAnchorPoint