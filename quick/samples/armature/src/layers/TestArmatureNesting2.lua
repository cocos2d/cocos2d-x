--
-- Author: SunLightJuly
-- Date: 2014-07-29 16:56:47
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestArmatureNesting2 = class("TestArmatureNesting2", ArmatureTestLayer)

local Hero = require("layers.role.hero")

function TestArmatureNesting2:ctor(index)
	TestArmatureNesting2.super.ctor(self)
	self:creatTitleAndSubTitle(index)
end

function TestArmatureNesting2:onEnter()
    local function onTouchEnded(event)
        local location = cc.p(event.x, event.y)  
        local armature = self._hero._mount and self._hero._mount  or self._hero
        if location.x < armature:getPositionX() then
            armature:setScaleX(-1)
        else
            armature:setScaleX(1)
        end

        local move = cc.MoveTo:create(2, location)
        armature:stopAllActions()
        armature:runAction(cc.Sequence:create(move))
    end

    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
    	if event.name=='began' then
    		return true
    	elseif event.name=='ended' then
    		onTouchEnded(event)
    	end
    end)

    local function changeMountCallback()
        self._hero:stopAllActions()

        if nil ~= self._hero._mount then
            self._hero:changeMount(nil)
        else
            if cc.pGetDistance(cc.p(self._hero:getPosition()),cc.p(self._horse:getPosition())) < 20 then
                self._hero:changeMount(self._horse)
            elseif cc.pGetDistance(cc.p(self._hero:getPosition()),cc.p(self._horse2:getPosition())) < 20 then
                self._hero:changeMount(self._horse2)
            elseif cc.pGetDistance(cc.p(self._hero:getPosition()),cc.p(self._bear:getPosition())) < 30 then
                self._hero:changeMount(self._bear)
            end
        end
    end

    self._touchedMenu = false
    self.exitButton =     
        cc.ui.UIPushButton.new({})
        :setButtonLabel("normal", cc.Label:createWithTTF("Change Mount", ArmatureTestLayer.resPathes.s_arialPath, 24))
        :setButtonLabel("pressed", cc.Label:createWithTTF("Change Mount", ArmatureTestLayer.resPathes.s_arialPath, 30))
        :onButtonClicked(function()
            changeMountCallback()
        end)
        :pos(display.right - 240, 60)
        :addTo(self)

    self._hero = Hero.new()
    self._hero._layer = self
    self._hero:playWithIndex(0)
    self._hero:setPosition(display.left + 20, display.cy)
    self:addChild(self._hero)

    self._horse = self:createMount("horse", cc.p(display.cx, display.cy))

    self._horse2 = self:createMount("horse", cc.p(120, 200))
    self._horse2:setOpacity(200)

    self._bear = self:createMount("bear", cc.p(300,70))
end

function TestArmatureNesting2:createMount(name,pt)
    local armature = ccs.Armature:create(name)
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(pt)
    self:addChild(armature)
    return armature
end

return TestArmatureNesting2