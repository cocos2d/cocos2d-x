local TestUserScene = class("TestUserScene",function()
    return cc.Scene:create()
end)

function TestUserScene.create()
    local scene = TestUserScene.new()
    scene:addChild(scene:createLayerMenu())
    return scene
end

function TestUserScene:createLayerMenu()
    local back = cc.MenuItemFont:create("back")
    back:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    local login = cc.MenuItemFont:create("login")
    login:registerScriptTapHandler(function()
        local facebook = plugin.PluginManager:getInstance():loadPlugin("UserFacebook")
        facebook:login(function(code, mes)
            cclog("%d, %s", code, msg)
        end)
    end)
    login:setPosition(0, 50)
    return cc.Menu:create(back, login)
end

return TestUserScene
