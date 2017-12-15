local HelloWorldScene = class("HelloWorldScene",function()
    return cc.Scene:create()
end)

function HelloWorldScene.create()
    local scene = HelloWorldScene.new()
    scene:addChild(scene:createLayerMenu())
    return scene
end

function HelloWorldScene:createLayerMenu()
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local menu = cc.Menu:create()
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(20)
    for i, plugin in ipairs({"IAP", "Ads", "Share", "FBShare", "User", "FBUser", "Social"}) do
        local item = cc.MenuItemFont:create(plugin)
        item:setPosition(0, visibleSize.height / 2 - i * 40)
        item:registerScriptTapHandler(function()
            local sceneName = string.format("Test%sScene", plugin)
            local scene = require(sceneName).create()
            cc.Director:getInstance():replaceScene(scene)
        end)
        menu:addChild(item)
    end
    return menu
end

return HelloWorldScene
