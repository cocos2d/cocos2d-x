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

local storagePaths = 
{
    "LuaTests/AssetsManagerExTest/scene1",
    "LuaTests/AssetsManagerExTest/scene2", 
    "LuaTests/AssetsManagerExTest/scene3",
}

local backgroundPaths = 
{
    "Images/assetMgrBackground1.jpg",
    "Images/assetMgrBackground2.png",
    "Images/assetMgrBackground3.png"
}

-------------------------------------
--  AssetsManagerEx1 Test
-------------------------------------
local AMTestScene1 = {}
AMTestScene1.__index = AMTestScene1

function AMTestScene1.create()

    local layer  = cc.Layer:create()

    local am = nil

    local function onEnter()

        Helper.initWithLayer(layer)
        Helper.titleLabel:setString("AssetsManagerExTest1")

        local sprite = cc.Sprite:create("Images/Icon.png")
        layer:addChild(sprite)
        sprite:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))

        local ttfConfig = {}
        ttfConfig.fontFilePath = "fonts/arial.ttf"
        ttfConfig.fontSize = 40

        local  progress = cc.Label:createWithTTF(ttfConfig, "0%", cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
        progress:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y + 50))
        layer:addChild(progress)
        am = cc.AssetsManagerEx:create(sceneManifests[1], cc.FileUtils:getInstance():getWritablePath() .. storagePaths[1])
        am:retain()

        if not am:getLocalManifest():isLoaded() then
            print("Fail to update assets, step skipped.")
            local background = cc.Sprite:create(backgroundPaths[1])
            layer:addChild(background, 1)
            background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
        else
            local function onUpdateEvent(event)
                local eventCode = event:getEventCode()
                if eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_NO_LOCAL_MANIFEST then
                    print("No local manifest file found, skip assets update.")
                    local background = cc.Sprite:create(backgroundPaths[1])
                    layer:addChild(background, 1)
                    background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif  eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_PROGRESSION then
                    local assetId = event:getAssetId()
                    local percent = event:getPercent()
                    local strInfo = ""

                    if assetId == cc.AssetsManagerExStatic.VERSION_ID then
                        strInfo = string.format("Version file: %d%%", percent)
                    elseif assetId == cc.AssetsManagerExStatic.MANIFEST_ID then
                        strInfo = string.format("Manifest file: %d%%", percent)
                    else
                        strInfo = string.format("%d%%", percent)
                    end
                    progress:setString(strInfo)
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_DOWNLOAD_MANIFEST or 
                       eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_PARSE_MANIFEST then
                    print("Fail to download manifest file, update skipped.")
                    local background = cc.Sprite:create(backgroundPaths[1])
                    layer:addChild(background, 1)
                    background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ALREADY_UP_TO_DATE or 
                       eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_FINISHED then
                        print("Update finished.")
                        local background = cc.Sprite:create(backgroundPaths[1])
                        layer:addChild(background, 1)
                        background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_UPDATING then
                        print("Asset ", event:getAssetId(), ", ", event:getMessage())
                        local background = cc.Sprite:create(backgroundPaths[1])
                        layer:addChild(background, 1)
                        background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                end
            end
            local listener = cc.EventListenerAssetsManagerEx:create(am,onUpdateEvent)
            cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, 1)
            
            am:update()
        end
    end

    local function onNodeEvent(event)
        if "enter" == event then
            onEnter()
        elseif "exit" == event then
            am:release()
        end
    end
    layer:registerScriptHandler(onNodeEvent)

    return layer
end


-------------------------------------
--  AssetsManagerEx2 Test
-------------------------------------
local AMTestScene2 = {}
AMTestScene2.__index = AMTestScene2

function AMTestScene2.create()

    local layer  = cc.Layer:create()

    local am = nil

    local function onEnter()

        Helper.initWithLayer(layer)
        Helper.titleLabel:setString("AssetsManagerExTest2")

        local sprite = cc.Sprite:create("Images/Icon.png")
        layer:addChild(sprite)
        sprite:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))

        local ttfConfig = {}
        ttfConfig.fontFilePath = "fonts/arial.ttf"
        ttfConfig.fontSize = 40

        local  progress = cc.Label:createWithTTF(ttfConfig, "0%", cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
        progress:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y + 50))
        layer:addChild(progress)

        am = cc.AssetsManagerEx:create(sceneManifests[2], cc.FileUtils:getInstance():getWritablePath() .. storagePaths[2])
        am:retain()

        if not am:getLocalManifest():isLoaded() then
            print("Fail to update assets, step skipped.")
            local background = cc.Sprite:create(backgroundPaths[2])
            layer:addChild(background, 1)
            background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
        else
            local function onUpdateEvent(event)
                local eventCode = event:getEventCode()
                if eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_NO_LOCAL_MANIFEST then
                    print("No local manifest file found, skip assets update.")
                    local background = cc.Sprite:create(backgroundPaths[2])
                    layer:addChild(background, 1)
                    background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif  eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_PROGRESSION then
                    local assetId = event:getAssetId()
                    local percent = event:getPercent()
                    local strInfo = ""

                    if assetId == cc.AssetsManagerExStatic.VERSION_ID then
                        strInfo = string.format("Version file: %d%%", percent)
                    elseif assetId == cc.AssetsManagerExStatic.MANIFEST_ID then
                        strInfo = string.format("Manifest file: %d%%", percent)
                    else
                        strInfo = string.format("%d%%", percent)
                    end
                    progress:setString(strInfo)
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_DOWNLOAD_MANIFEST or 
                       eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_PARSE_MANIFEST then
                    print("Fail to download manifest file, update skipped.")
                    local background = cc.Sprite:create(backgroundPaths[2])
                    layer:addChild(background, 1)
                    background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ALREADY_UP_TO_DATE or 
                       eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_FINISHED then
                        print("Update finished.")
                        local background = cc.Sprite:create(backgroundPaths[2])
                        layer:addChild(background, 1)
                        background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_UPDATING then
                        print("Asset ", event:getAssetId(), ", ", event:getMessage())
                        local background = cc.Sprite:create(backgroundPaths[2])
                        layer:addChild(background, 1)
                        background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                end
            end
            local listener = cc.EventListenerAssetsManagerEx:create(am,onUpdateEvent)
            cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, 1)
            
            am:update()
        end
    end

    local function onNodeEvent(event)
        if "enter" == event then
            onEnter()
        elseif "exit" == event then
            am:release()
        end
    end
    layer:registerScriptHandler(onNodeEvent)

    return layer
end

-------------------------------------
--  AssetsManagerEx3 Test
-------------------------------------
local AMTestScene3 = {}
AMTestScene3.__index = AMTestScene3

function AMTestScene3.create()

    local layer  = cc.Layer:create()

    local am = nil

    local function onEnter()

        Helper.initWithLayer(layer)
        Helper.titleLabel:setString("AssetsManagerExTest3")

        local sprite = cc.Sprite:create("Images/Icon.png")
        layer:addChild(sprite)
        sprite:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))

        local ttfConfig = {}
        ttfConfig.fontFilePath = "fonts/arial.ttf"
        ttfConfig.fontSize = 40

        local  progress = cc.Label:createWithTTF(ttfConfig, "0%", cc.VERTICAL_TEXT_ALIGNMENT_CENTER)
        progress:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y + 50))
        layer:addChild(progress)

        am = cc.AssetsManagerEx:create(sceneManifests[3], cc.FileUtils:getInstance():getWritablePath() .. storagePaths[3])
        am:retain()

        if not am:getLocalManifest():isLoaded() then
            print("Fail to update assets, step skipped.")
            local background = cc.Sprite:create("Images/background3.png")
            layer:addChild(background, 1)
            background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
        else
            local function onUpdateEvent(event)
                local eventCode = event:getEventCode()
                if eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_NO_LOCAL_MANIFEST then
                    print("No local manifest file found, skip assets update.")
                    local background = cc.Sprite:create(backgroundPaths[3])
                    layer:addChild(background, 1)
                    background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif  eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_PROGRESSION then
                    local assetId = event:getAssetId()
                    local percent = event:getPercent()
                    local strInfo = ""

                    if assetId == cc.AssetsManagerExStatic.VERSION_ID then
                        strInfo = string.format("Version file: %d%%", percent)
                    elseif assetId == cc.AssetsManagerExStatic.MANIFEST_ID then
                        strInfo = string.format("Manifest file: %d%%", percent)
                    else
                        strInfo = string.format("%d%%", percent)
                    end
                    progress:setString(strInfo)
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_DOWNLOAD_MANIFEST or 
                       eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_PARSE_MANIFEST then
                    print("Fail to download manifest file, update skipped.")
                    local background = cc.Sprite:create(backgroundPaths[3])
                    layer:addChild(background, 1)
                    background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ALREADY_UP_TO_DATE or 
                       eventCode == cc.EventAssetsManagerEx.EventCode.UPDATE_FINISHED then
                        print("Update finished.")
                        local background = cc.Sprite:create(backgroundPaths[3])
                        layer:addChild(background, 1)
                        background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                elseif eventCode == cc.EventAssetsManagerEx.EventCode.ERROR_UPDATING then
                        print("Asset ", event:getAssetId(), ", ", event:getMessage())
                        local background = cc.Sprite:create(backgroundPaths[3])
                        layer:addChild(background, 1)
                        background:setPosition( cc.p(VisibleRect:center().x, VisibleRect:center().y ))
                end
            end
            local listener = cc.EventListenerAssetsManagerEx:create(am,onUpdateEvent)
            cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, 1)
            
            am:update()
        end
    end

    local function onNodeEvent(event)
        if "enter" == event then
            onEnter()
        elseif "exit" == event then
            am:release()
        end
    end
    layer:registerScriptHandler(onNodeEvent)

    return layer
end

-------------------------------------
--  AssetsManagerEx Test
-------------------------------------
function AssetsManagerExTestMain()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        AMTestScene1.create,
        AMTestScene2.create,
        AMTestScene3.create,
    }

    scene:addChild(AMTestScene1.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end
