local TestShareScene = class("TestShareScene",function()
    return cc.Scene:create()
end)

function TestShareScene.create()
    local scene = TestShareScene.new()
    scene:addChild(scene:createLayerMenu())
    return scene
end

function TestShareScene:ctor()
    self.twttr = plugin.PluginManager:getInstance():loadPlugin("ShareTwitter")
    self.twttr:setDebugMode(true)
    self.twttr:configDeveloperInfo({TwitterKey = "YOUR_KEY", TwitterSecret = "YOUR_SECRET"})
end

function TestShareScene:createLayerMenu()
    local back = cc.MenuItemFont:create("back")
    back:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    local share = cc.MenuItemFont:create("share")
    share:registerScriptTapHandler(function()
        self.twttr:share({SharedText = "hello"}, function(code, info)
            cclog(info)
        end)
    end)
    share:setPosition(0, 50)
    return cc.Menu:create(back, share)
end

return TestShareScene
