
require("config")
require("framework.init")

local WelcomeApp = class("WelcomeApp", cc.mvc.AppBase)

function WelcomeApp:run()
    self.eventNode = cc.Node:create()

    CCFileUtils:getInstance():addSearchPath("res/")

    local evl = cc.EventListenerCustom:create("WELCOME_LIST_SAMPLES", function() self:enterSampleScene() end )
    self.eventNode:getEventDispatcher():addEventListenerWithFixedPriority(evl,1)
    -- cc.__NotificationCenter:getInstance():registerScriptObserver(self.eventNode, function() self:enterSampleScene() end, "WELCOME_LIST_SAMPLES")
    cc.__NotificationCenter:getInstance():registerScriptObserver(self.eventNode, function() self:enterMainFrame() end, "WELCOME_APP")
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
