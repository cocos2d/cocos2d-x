local TestIAPScene = class("TestIAPScene",function()
    return cc.Scene:create()
end)

function TestIAPScene.create()
    local scene = TestIAPScene.new()
    scene:addChild(scene:createLayerMenu())
    return scene
end

function TestIAPScene:ctor()
    self.iap = plugin.PluginManager:getInstance():loadPlugin("IOSIAP")
    self.iap:setDebugMode(true)
    self.iap:callFuncWithParam("requestProducts", "YOUR_PRODUCT_ID")
end

function TestIAPScene:createLayerMenu()
    local back = cc.MenuItemFont:create("back")
    back:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    local pay = cc.MenuItemFont:create("pay")
    pay:setPositionY(50)
    pay:registerScriptTapHandler(function()
        self.iap:payForProduct({productId = "YOUR_PRODUCT_ID"}, function(ret, products)
            cclog("%d, %s", ret, products)
        end)
    end)
    return cc.Menu:create(back, pay)
end

return TestIAPScene
