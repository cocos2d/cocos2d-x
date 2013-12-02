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
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/FishJoy2.json")
    if nil == node then
        return
    end
    self._curNode = node

    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale = winSize.height / 320
    self._curNode:setScale(scale)
    self._curNode:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    local function menuCloseCallback( sender )
        SceneReader:sharedSceneReader():purgeSceneReader()
        ActionManager:purgeActionManager()
        local scene = CocoStudioTest()
        if scene ~= nil then
            CCDirector:sharedDirector():replaceScene(scene)
        end
    end

    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    local itemBack = CCMenuItemFont:create("Back")
    itemBack:setColor(ccc3(255, 255, 255))
    itemBack:setPosition( ccp(430,30) )
    itemBack:registerScriptTapHandler(menuCloseCallback)
    local menuBack = CCMenu:create()
    menuBack:setPosition(ccp(0.0, 0.0))
    menuBack:setZOrder(4)
    menuBack:addChild(itemBack)

    node:addChild(menuBack)

    ActionManager:shareManager():playActionByName("startMenu_1.json","Animation1")

    return node
end

function SceneEditorTestLayer.create()
    local scene = CCScene:create()
    local layer = SceneEditorTestLayer.extend(CCLayerColor:create())
    layer:addChild(layer:createGameScene(), 0, 1)
    scene:addChild(layer)
    return scene   
end

function runCocosSceneTestScene()
   local scene = SceneEditorTestLayer.create()
   CCDirector:sharedDirector():replaceScene(scene)
end
