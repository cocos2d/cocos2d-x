local AssetManagerModule = {}

function AssetManagerModule.newScene(backfunc)

    local winSize = cc.Director:getInstance():getWinSize()
    
    local newScene = cc.Scene:create()
    local layer    = cc.Layer:create()

    local function backToUpdate()
        local scene = backfunc()
        if scene ~= nil then
            cc.Director:getInstance():replaceScene(scene)
        end
    end

    --Create BackMneu
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local backMenuItem = cc.MenuItemFont:create("Back")
    backMenuItem:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    backMenuItem:registerScriptTapHandler(backToUpdate)

    local backMenu = cc.Menu:create()
    backMenu:setPosition(0, 0)
    backMenu:addChild(backMenuItem)
    layer:addChild(backMenu,6)

    local helloLabel =  cc.Label:createWithTTF("Hello World", s_arialPath, 38)
    helloLabel:setAnchorPoint(cc.p(0.5, 0.5))
    helloLabel:setPosition(cc.p(winSize.width / 2, winSize.height - 40))
    layer:addChild(helloLabel, 5)

    local sprite = cc.Sprite:create("Images/background.png")
    sprite:setAnchorPoint(cc.p(0.5, 0.5))
    sprite:setPosition(cc.p(winSize.width / 2, winSize.height / 2))
    layer:addChild(sprite, 0)

    newScene:addChild(layer)
    cc.Director:getInstance():replaceScene(newScene)
end


return AssetManagerModule
