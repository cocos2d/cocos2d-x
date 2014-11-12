--
-- Author: SunLightJuly
-- Date: 2014-07-29 10:31:17
--

local ArmatureTestLayer = class("ArmatureTestLayer", function()
    return display.newLayer()
end)

local resPathes = 
{
	s_pPathB1             = "Images/b1.png",
	s_pPathB2             = "Images/b2.png",
	s_pPathR1             = "Images/r1.png",
	s_pPathR2             = "Images/r2.png",
	s_pPathF1             = "Images/f1.png",
	s_pPathF2             = "Images/f2.png",

	s_arialPath            = "fonts/arial.ttf"
}
ArmatureTestLayer.resPathes = resPathes

local ArmatureTestIndex =
{
    TEST_ASYNCHRONOUS_LOADING     = 1,
    TEST_DIRECT_LOADING           = 2,
    TEST_COCOSTUDIO_WITH_SKELETON = 3,
    TEST_DRAGON_BONES_2_0 = 4,
    TEST_PERFORMANCE = 5,
    TEST_CHANGE_ZORDER = 6,
    TEST_ANIMATION_EVENT = 7,
    TEST_FRAME_EVENT     = 8,
    TEST_PARTICLE_DISPLAY = 9,
    TEST_USE_DIFFERENT_PICTURE = 10,
    TEST_ANCHORPOINT = 11,
    TEST_ARMATURE_NESTING = 12,
    TEST_ARMATURE_NESTING_2 = 13,
}

function ArmatureTestLayer:ctor()
    self.restartButton = 
        cc.ui.UIPushButton.new({normal = resPathes.s_pPathR1, pressed = resPathes.s_pPathR2})
        :onButtonClicked(function()
            game.test()
        end)
        :addTo(self)
    local sz = self.restartButton:getCascadeBoundingBox().size
    local w = sz.width * 2
    local h = sz.height / 2
    self.restartButton:setPosition(display.cx, h)

    self.prevButton = 
        cc.ui.UIPushButton.new({normal = resPathes.s_pPathB1, pressed = resPathes.s_pPathB2})
        :onButtonClicked(function()
            game.prevTest()
        end)
        :pos(display.cx - w, h)
        :addTo(self)

    self.nextButton = 
        cc.ui.UIPushButton.new({normal = resPathes.s_pPathF1, pressed = resPathes.s_pPathF2})
        :onButtonClicked(function()
            game.nextTest()
        end)
        :pos(display.cx + w, h)
        :addTo(self)

    self.exitButton =     
        cc.ui.UIPushButton.new({})
        :setButtonLabel("normal", cc.Label:createWithTTF("Exit", resPathes.s_arialPath, 24))
        :setButtonLabel("pressed", cc.Label:createWithTTF("Exit", resPathes.s_arialPath, 30))
        :onButtonClicked(function()
            game.exit()
        end)
        :pos(display.right - 120, 30)
        :addTo(self)
end

function ArmatureTestLayer:onEnter()
	-- override me
end

function ArmatureTestLayer.title(idx)
    if ArmatureTestIndex.TEST_ASYNCHRONOUS_LOADING == idx then
        return "Test Asynchronous Loading"
    elseif ArmatureTestIndex.TEST_DIRECT_LOADING   == idx then
        return "Test Direct Loading"
    elseif ArmatureTestIndex.TEST_COCOSTUDIO_WITH_SKELETON == idx then
        return "Test Export From CocoStudio With Skeleton Effect"
    elseif ArmatureTestIndex.TEST_DRAGON_BONES_2_0 == idx then
        return "Test Export From DragonBones version 2.0"
    elseif ArmatureTestIndex.TEST_PERFORMANCE == idx then
        return "Test Performance"
    elseif ArmatureTestIndex.TEST_CHANGE_ZORDER == idx then
        return "Test Change ZOrder Of Different Armature"
    elseif ArmatureTestIndex.TEST_ANIMATION_EVENT == idx then
        return "Test Armature Animation Event"
    elseif ArmatureTestIndex.TEST_FRAME_EVENT == idx then
        return "Test Frame Event"
    elseif ArmatureTestIndex.TEST_PARTICLE_DISPLAY == idx then
        return "Test Particle Display"
    elseif ArmatureTestIndex.TEST_USE_DIFFERENT_PICTURE == idx then
        return "Test One Armature Use Different Picture"
    elseif ArmatureTestIndex.TEST_ANCHORPOINT == idx then
        return "Test Set AnchorPoint"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING == idx then
        return "Test Armature Nesting"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING_2 == idx then
        return "Test Armature Nesting 2"
    end
end

function ArmatureTestLayer.subTitle(idx)
    if ArmatureTestIndex.TEST_ASYNCHRONOUS_LOADING == idx then
        return "current percent :"
    elseif ArmatureTestIndex.TEST_PERFORMANCE == idx then
        return "Current Armature Count : "
    elseif ArmatureTestIndex.TEST_PARTICLE_DISPLAY == idx then
        return "Touch to change animation"
    elseif ArmatureTestIndex.TEST_USE_DIFFERENT_PICTURE == idx then
        return "weapon and armature are in different picture"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING_2 == idx then
        return "Move to a mount and press the ChangeMount Button."
    else
        return ""
    end
end

function ArmatureTestLayer:creatTitleAndSubTitle(idx)
    local title = cc.Label:createWithTTF(ArmatureTestLayer.title(idx), resPathes.s_arialPath, 18)
    title:setColor(cc.c3b(0,0,0))
    self:addChild(title, 1, 10000)
    title:setAnchorPoint(cc.p(0.5, 0.5))
    title:setPosition( display.cx, display.top - 30 )
    local subTitle = nil
    if "" ~= ArmatureTestLayer.subTitle(idx) then
        local subTitle = cc.Label:createWithTTF(ArmatureTestLayer.subTitle(idx), resPathes.s_arialPath, 18)
        subTitle:setColor(cc.c3b(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setAnchorPoint(cc.p(0.5, 0.5))
        subTitle:setPosition( display.cx, display.top - 60 )
    end
end

return ArmatureTestLayer