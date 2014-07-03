
require("config")
require("framework.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")

    -- init anysdk
    if device.platform == "android" then
    	self.agentMgr = anysdk.AgentManager:getInstance()
    	self.agentMgr:init(ANYSDK_APPKEY, ANYSDK_SECRET, ANYSDK_PRIVATE_KEY, ANYSDK_OAUTH_LOGIN_SERVER)
    	self.agentMgr:loadALLPlugin()
	end

    self:enterScene("MainScene")
end

return MyApp
