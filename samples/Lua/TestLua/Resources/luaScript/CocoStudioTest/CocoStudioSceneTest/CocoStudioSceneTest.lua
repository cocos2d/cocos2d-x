local SceneEditorTestLayer = class("SceneEditorTestLayer")
SceneEditorTestLayer._curNode = nil

function SceneEditorTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SceneEditorTestLayer)
    return target
end

function SceneEditorTestLayer:createGameScene()
    local node = ccs.SceneReader:getInstance():createNodeWithSceneFile("scenetest/FishJoy2.json")
    if nil == node then
        return
    end
    self._curNode = node

    local function menuCloseCallback( sender )
        ccs.SceneReader:getInstance():destroySceneReader()
        ccs.ActionManagerEx:destroyActionManager()
        local scene = CocoStudioTestMain()
        if scene ~= nil then
            cc.Director:getInstance():replaceScene(scene)
        end
    end

    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local itemBack = cc.MenuItemFont:create("Back")
    itemBack:setColor(cc.c3b(255, 255, 255))
    itemBack:setPosition( cc.p(430,30) )
    itemBack:registerScriptTapHandler(menuCloseCallback)
    local menuBack = cc.Menu:create()
    menuBack:setPosition(cc.p(0.0, 0.0))
    menuBack:setZOrder(4)
    menuBack:addChild(itemBack)

    node:addChild(menuBack)

    ccs.ActionManagerEx:getInstance():playActionByName("startMenu_1.json","Animation1")

    return node
end

function SceneEditorTestLayer.create()
    local scene = cc.Scene:create()
    local layer = SceneEditorTestLayer.extend(cc.LayerColor:create())
    layer:addChild(layer:createGameScene(), 0, 1)
    scene:addChild(layer)
    return scene   
end

function runCocosSceneTestScene()
   local scene = SceneEditorTestLayer.create()
   cc.Director:getInstance():replaceScene(scene)
end