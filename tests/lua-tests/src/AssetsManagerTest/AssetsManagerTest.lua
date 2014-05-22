local targetPlatform = cc.Application:getInstance():getTargetPlatform()

local sceneID = 
{
    "AMTestScene1", 
    "AMTestScene2", 
    "AMTestScene3",
}

local sceneManifests = 
{
    "Manifests/AMTestScene1/project.manifest", 
    "Manifests/AMTestScene2/project.manifest", 
    "Manifests/AMTestScene3/project.manifest"
}

--UNCHECK
local storagePaths = 
{
    "LuaTests/AssetsManagerTest/scene1",
    "LuaTests/AssetsManagerTest/scene2", 
    "LuaTests/AssetsManagerTest/scene3",
}

local backgroundPaths = 
{
    "Images/background1.jpg", 
    "Images/background2.jpg", 
    "Images/background3.png"
}

-------------------------------------
--  AssetsManager Test
-------------------------------------
local AMTestScene1 = {}
AMTestScene1.__index = AMTestScene1

function AMTestScene1.create()
    local sprite = cc.Sprite:create("Images/Icon.png")
    local layer  = cc.Layer:create()

    layer:addChild(sprite)
    sprite:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 40

    local  progress = cc.Label:createWithTTF(ttfConfig, "0%", cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
    progress:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y + 50))
    layer:addChild(progress)

    local am = cc.AssetsManager:create("AMTestScene1", "Manifests/AMTestScene1/project.manifest", "LuaTests/AssetsManagerTest/scene1")
    am:retain()

    if not am:getLocalManifest():isLoaded() then
        print("Fail to update assets, step skipped.")
        --AssetsManagerTestScene *scene = new AssetsManagerTestScene(backgroundPaths[currentId])
        --cc.Director:getInstance():replaceScene(scene)
        local background = cc.Sprite:create(backgroundPaths[1])
        layer:addChild(background, 1)
        background:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))

    else
        local function onUpdate(event)
            
        end
        am:addUpdateEventListener(onUpdate)
    end

    return layer
end

-------------------------------------
--  AssetsManager Test
-------------------------------------
function AssetsManagerTestMain()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        AMTestScene1.create,
    }

    scene:addChild(AMTestScene1.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end
