
require("config")
require("framework.init")

local WelcomeApp = class("WelcomeApp", cc.mvc.AppBase)

function WelcomeApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    cc.FileUtils:getInstance():addSearchPath("res/hd")
    display.addSpriteFrames("Images_hd.plist", "Images_hd.png")

    -- set default font of label
    if device.platform == "windows" then
        cc.ui.UILabel.DEFAULT_TTF_FONT = "NotoSansHans-Light.otf"
    elseif device.platform == "mac" then
        cc.ui.UILabel.DEFAULT_TTF_FONT = "Monaco"
    end

    local evl = cc.EventListenerCustom:create("WELCOME_LIST_SAMPLES", function() self:enterSampleScene() end )
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(evl,1)

    evl = cc.EventListenerCustom:create("WELCOME_APP", function() self:enterMainFrame() end )
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(evl,1)

    self:enterScene("WelcomeScene")
end

function WelcomeApp:enterMainFrame()
    self:enterScene("WelcomeScene", nil, "slideInL", 0.3, display.COLOR_WHITE)
end

function WelcomeApp:enterSampleScene()
    self:enterScene("SampleScene", nil, "pageTurn", 0.5, false)
end

function WelcomeApp:backToMainScene()
    self:enterScene("WelcomeScene", nil, "pageTurn", 0.5, true)
end

return WelcomeApp
