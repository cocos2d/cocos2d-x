
require("config")
require("framework.init")

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")

    -- init anysdk
    self:initAnySDK()

    self:enterScene("MainScene")
end

function MyApp:enterScene(sceneName, args, transitionType, time, more)
	local scenePackageName = self. packageRoot .. ".scenes." .. sceneName
    local sceneClass = require(scenePackageName)
    self.curScene = sceneClass.new(unpack(checktable(args)))
    display.replaceScene(self.curScene, transitionType, time, more)
end

function MyApp:initAnySDK()
	if device.platform ~= "android" then
	end

	self.agentMgr = anysdk.AgentManager:getInstance()
	self.agentMgr:init(ANYSDK_APPKEY, ANYSDK_SECRET, ANYSDK_PRIVATE_KEY, ANYSDK_OAUTH_LOGIN_SERVER)
	self.agentMgr:loadALLPlugin()

	--register listener
	if self.agentMgr:getUserPlugin() then
		self.agentMgr:getUserPlugin():setActionListener(handler(self, self.sdkListener))
	end
	if self.agentMgr:getSharePlugin() then
		self.agentMgr:getSharePlugin():setResultListener(handler(self, self.sdkListener))
	end
	if self.agentMgr:getSocialPlugin() then
		self.agentMgr:getSocialPlugin():setListener(handler(self, self.sdkListener))
	end
	if self.agentMgr:getAdsPlugin() then
		self.agentMgr:getAdsPlugin():setAdsListener(handler(self, self.sdkListener))
	end
	if self.agentMgr:getPushPlugin() then
		self.agentMgr:getPushPlugin():setActionListener(handler(self, self.sdkListener))
	end
	if self.agentMgr:getIAPPlugin() then
		local iaps = self.agentMgr:getIAPPlugin()
		for i,v in ipairs(iaps) do
			v:setActionListener(handler(self, self.sdkListener))
		end
	end
end

function MyApp:sdkListener(protocol, param)
	print("htl protocol:" .. protocol)
	if "ads" == protocol then
	elseif "iap" == protocol then
	elseif "share" == protocol then
	elseif "social" == protocol then
	elseif "user" == protocol then
	elseif "push" == protocol then
	end

	if self.curScene.sdkListener then
		param = json.decode(param)
		self.curScene:sdkListener(protocol, param)
	end
end

function MyApp:onEnterBackground()
	if self.agentMgr:getAnalyticsPlugin() then
		self.agentMgr:getAnalyticsPlugin():startSession()
	end
end

function MyApp:onEnterForeground()
    if self.agentMgr:getAnalyticsPlugin() then
    	self.agentMgr:getAnalyticsPlugin():stopSession()
	end
end

return MyApp
