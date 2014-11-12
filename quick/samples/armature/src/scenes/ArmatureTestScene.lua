
local ArmatureTestScene = class("ArmatureTestScene", function()
    return display.newScene("ArmatureTestScene")
end)

local armatureSceneName =
{
    "TestAsynchronousLoading",
    "TestDirectLoading",
    "TestCSWithSkeleton",
    "TestDragonBones20",
    "TestPerformance",
    --"TestPerformanceBatchNode",
    "TestChangeZorder",
    "TestAnimationEvent",
    "TestFrameEvent",
    "TestParticleDisplay",
    "TestUseMutiplePicture",
    "TestAnchorPoint",
    "TestArmatureNesting",
    "TestArmatureNesting2",
}
game.numArmatureScenes = #armatureSceneName

function ArmatureTestScene:exit()
    game.exit()
end

function ArmatureTestScene:ctor(index)
    local bg = display.newSprite("armature/bg.jpg", display.cx, display.cy)
    local scaleX = display.width / bg:getContentSize().width
    local scaleY = display.height / bg:getContentSize().height
    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)
    self:addChild(bg)

    self.layer = require("layers."..armatureSceneName[index]).new(index)
    self:addChild(self.layer)
end

function ArmatureTestScene:onEnterFrame(dt)
end

function ArmatureTestScene:onEnter()
    self.layer:onEnter()
end

function ArmatureTestScene:onExit()
    self.layer:onExit()
end

return ArmatureTestScene
