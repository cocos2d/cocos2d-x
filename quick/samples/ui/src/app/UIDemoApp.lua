
require("config")
require("framework.init")
require("framework.shortcodes")
require("framework.cc.init")

local UIDemoApp = class("UIDemoApp", cc.mvc.AppBase)

function UIDemoApp:ctor()
    UIDemoApp.super.ctor(self)
    self.scenes_ = {
        "TestUIPageViewScene",
        "TestUIListViewScene",
        "TestUIScrollViewScene",
        "TestUIImageScene",
        "TestUIButtonScene",
        "TestUISliderScene",
    }
end

function UIDemoApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    self:enterNextScene()
end

function UIDemoApp:enterScene(sceneName, ...)
    self.currentSceneName_ = sceneName
    UIDemoApp.super.enterScene(self, sceneName, ...)
end

function UIDemoApp:enterNextScene()
    local index = 1
    while index <= #self.scenes_ do
        if self.scenes_[index] == self.currentSceneName_ then
            break
        end
        index = index + 1
    end
    index = index + 1
    if index > #self.scenes_ then index = 1 end
    self:enterScene(self.scenes_[index])
end

function UIDemoApp:createTitle(scene, title)
    cc.ui.UILabel.new({text = "-- " .. title .. " --", size = 24, color = display.COLOR_BLACK})
        :align(display.CENTER, display.cx, display.top - 20)
        :addTo(scene)
end

function UIDemoApp:createGrid(scene)
    display.newColorLayer(cc.c4b(255, 255, 255, 255)):addTo(scene)

    for y = display.bottom, display.top, 40 do
        display.newLine(
            {{display.left, y}, {display.right, y}},
            {borderColor = cc.c4f(0.9, 0.9, 0.9, 1.0)})
        :addTo(scene)
    end

    for x = display.left, display.right, 40 do
        display.newLine(
            {{x, display.top}, {x, display.bottom}},
            {borderColor = cc.c4f(0.9, 0.9, 0.9, 1.0)})
        :addTo(scene)
    end

    display.newLine(
        {{display.left, display.cy + 1}, {display.right, display.cy + 1}},
        {borderColor = cc.c4f(1.0, 0.75, 0.75, 1.0)})
    :addTo(scene)

    display.newLine(
        {{display.cx, display.top}, {display.cx, display.bottom}},
        {borderColor = cc.c4f(1.0, 0.75, 0.75, 1.0)})
    :addTo(scene)
end

function UIDemoApp:createNextButton(scene)
    cc.ui.UIPushButton.new("NextButton.png")
        :onButtonPressed(function(event)
            event.target:setScale(1.2)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function(event)
            self:enterNextScene()
        end)
        :align(display.RIGHT_BOTTOM, display.right - 20, display.bottom + 20)
        :addTo(scene)
end

function HDrawRect(rect, parent, color)
    local left, bottom, width, height = rect.x, rect.y, rect.width, rect.height
    local points = {
        {left, bottom},
        {left + width, bottom},
        {left + width, bottom + height},
        {left, bottom + height},
        {left, bottom},
    }
    local box = display.newPolygon(points, {borderColor = color})
    parent:addChild(box)
end

return UIDemoApp
