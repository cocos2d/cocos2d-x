--
-- Author: SunLightJuly
-- Date: 2014-07-29 11:04:34
--
local ArmatureTestLayer = require("layers.ArmatureTestLayer")
local TestAsynchronousLoading = class("TestAsynchronousLoading", ArmatureTestLayer)

function TestAsynchronousLoading:ctor()
	TestAsynchronousLoading.super.ctor(self)
end

function TestAsynchronousLoading:onEnter()
    self.prevButton:setButtonEnabled(false)
    self.restartButton:setButtonEnabled(false)
    self.nextButton:setButtonEnabled(false)

    local title = cc.Label:createWithTTF(self.title(1), self.resPathes.s_arialPath, 18)
    title:setColor(cc.c3b(0,0,0))
    self:addChild(title, 1, 10000)
    title:setAnchorPoint(cc.p(0.5, 0.5))
    title:setPosition( display.cx, display.top - 30 )
    local subInfo = self.subTitle(1)
    if "" ~= subInfo then
        subInfo  = subInfo .. 0.0
        local subTitle = cc.Label:createWithTTF(subInfo, self.resPathes.s_arialPath, 18)
        subTitle:setColor(cc.c3b(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setAnchorPoint(cc.p(0.5, 0.5))
        subTitle:setPosition( display.cx, display.top - 60 )
    end

    local function dataLoaded(percent)
        local label = self:getChildByTag(10001)
        if nil ~= label then
            local subInfo = self.subTitle(1) .. (percent * 100)
            label:setString(subInfo)
        end
        if percent >= 1 and self.prevButton and self.restartButton and self.nextButton then
            self.prevButton:setButtonEnabled(true)
            self.restartButton:setButtonEnabled(true)
            self.nextButton:setButtonEnabled(true)
        end
    end

    local manager = ccs.ArmatureDataManager:getInstance()
    manager:addArmatureFileInfoAsync("armature/knight.png", "armature/knight.plist", "armature/knight.xml", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/robot.png", "armature/robot.plist", "armature/robot.xml", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/Cowboy.ExportJson", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/hero.ExportJson", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/horse.ExportJson", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/bear.ExportJson", dataLoaded)
    manager:addArmatureFileInfoAsync("armature/HeroAnimation.ExportJson", dataLoaded)

end

return TestAsynchronousLoading