local TestAdsScene = class("TestAdsScene",function()
    return cc.Scene:create()
end)

function TestAdsScene.create()
    local scene = TestAdsScene.new()
    scene:addChild(scene:createLayerMenu())
    return scene
end

function TestAdsScene:ctor()
    self.admob = plugin.PluginManager:getInstance():loadPlugin("AdsAdmob")
    self.admob:configDeveloperInfo({AdmobID = "ca-app-pub-3940256099942544/2934735716"})
    self.admob:setDebugMode(true)
    self.admob:setCallback(function(code, info)
        cclog("%d, %s", code, info)
    end)
    self.admob:getCallback()(777, "getCallback test")
end

function TestAdsScene:createLayerMenu()
    local back = cc.MenuItemFont:create("back")
    back:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    local showAds = cc.MenuItemFont:create("showAds")
    showAds:registerScriptTapHandler(function()
        self.admob:showAds({AdmobType = "1", AdmobSizeEnum = "1"})
    end)
    showAds:setPosition(0, 100)
    local hideAds = cc.MenuItemFont:create("hideAds")
    hideAds:registerScriptTapHandler(function()
        self.admob:hideAds({AdmobType = "1"})
    end)
    hideAds:setPosition(0, 50)
    return cc.Menu:create(back, showAds, hideAds)
end

return TestAdsScene
