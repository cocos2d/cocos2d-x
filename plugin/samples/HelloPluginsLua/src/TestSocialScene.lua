local TestSocialScene = class("TestSocialScene",function()
    return cc.Scene:create()
end)

function TestSocialScene.create()
    local scene = TestSocialScene.new()
    scene:addChild(scene:createLayerMenu())
    return scene
end

function TestSocialScene:createLayerMenu()
    local back = cc.MenuItemFont:create("back")
    back:registerScriptTapHandler(function()
        cc.Director:getInstance():replaceScene(require("HelloWorldScene").create())
    end)
    return cc.Menu:create(back)
end

return TestSocialScene
