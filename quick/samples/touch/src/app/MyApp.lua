
require("config")
require("framework.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

local TESTS_LIST = {
    "TestSingleTouch1Scene",
    "TestSingleTouch2Scene",
    "TestSingleTouch3Scene",
    "TestSingleTouch4Scene",
    "TestMultiTouches1Scene",
    "TestMultiTouches2Scene",
    "TestMultiTouches3Scene",
}

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    self:enterNextScene()
end

function MyApp:enterScene(sceneName, ...)
    self.currentSceneName_ = sceneName
    MyApp.super.enterScene(self, sceneName, ...)
end

function MyApp:enterNextScene()
    local index = 1
    while index <= #TESTS_LIST do
        if TESTS_LIST[index] == self.currentSceneName_ then
            break
        end
        index = index + 1
    end
    index = index + 1
    if index > #TESTS_LIST then index = 1 end
    self:enterScene(TESTS_LIST[index])
end

function MyApp:createTitle(scene, title)
    cc.ui.UILabel.new({text = "-- " .. title .. " --", size = 24})
        :align(display.CENTER, display.cx, display.top - 20)
        :addTo(scene)
end

function MyApp:createNextButton(scene)
    cc.ui.UIPushButton.new("BlueButton.png", {scale9 = true})
        :setButtonSize(160, 60)
        :setButtonLabel(cc.ui.UILabel.new({text = "Next", size = 32}))
        :onButtonClicked(function(event)
            self:enterNextScene()
        end)
        :align(display.RIGHT_BOTTOM, display.right - 20, display.bottom + 20)
        :addTo(scene)
end

return MyApp
