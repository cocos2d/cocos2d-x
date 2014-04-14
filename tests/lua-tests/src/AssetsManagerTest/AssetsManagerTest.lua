local targetPlatform = cc.Application:getInstance():getTargetPlatform()

local lineSpace = 40
local itemTagBasic = 1000
local menuItemNames =
{
    "enter",
    "reset",
    "update",
}

local winSize = cc.Director:getInstance():getWinSize()

local function updateLayer()
    local layer = cc.Layer:create()

    local support  = false
    if (cc.PLATFORM_OS_IPHONE == targetPlatform) or (cc.PLATFORM_OS_IPAD == targetPlatform) 
        or (cc.PLATFORM_OS_WINDOWS == targetPlatform) or (cc.PLATFORM_OS_ANDROID == targetPlatform) 
        or (cc.PLATFORM_OS_MAC  == targetPlatform) then
        support = true
    end

    if not support then
        print("Platform is not supported!")
        return layer
    end

    local isUpdateItemClicked = false
    local assetsManager       = nil
    local pathToSave          = ""

    local menu = cc.Menu:create()
    menu:setPosition(cc.p(0, 0))
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)

    local progressLable = cc.Label:createWithTTF("",s_arialPath,30)
    progressLable:setAnchorPoint(cc.p(0.5, 0.5))
    progressLable:setPosition(cc.p(140,50))
    layer:addChild(progressLable)

    pathToSave = createDownloadDir()

    local function onError(errorCode)
        if errorCode == cc.ASSETSMANAGER_NO_NEW_VERSION then
            progressLable:setString("no new version")
        elseif errorCode == cc.ASSETSMANAGER_NETWORK then
            progressLable:setString("network error")
        end
    end

    local function onProgress( percent )
        local progress = string.format("downloading %d%%",percent)
        progressLable:setString(progress)
    end

    local function onSuccess()
        progressLable:setString("downloading ok")
    end

    local function getAssetsManager()
        if nil == assetsManager then
            assetsManager = cc.AssetsManager:new("https://raw.github.com/samuele3hu/AssetsManagerTest/master/package.zip",
                                           "https://raw.github.com/samuele3hu/AssetsManagerTest/master/version",
                                           pathToSave)
            assetsManager:retain()
            assetsManager:setDelegate(onError, cc.ASSETSMANAGER_PROTOCOL_ERROR )
            assetsManager:setDelegate(onProgress, cc.ASSETSMANAGER_PROTOCOL_PROGRESS)
            assetsManager:setDelegate(onSuccess, cc.ASSETSMANAGER_PROTOCOL_SUCCESS )
            assetsManager:setConnectionTimeout(3)
        end

        return assetsManager
    end

    local function update(sender)
        progressLable:setString("")

        getAssetsManager():update()
    end

    local function reset(sender)
        progressLable:setString("")

        deleteDownloadDir(pathToSave)

        getAssetsManager():deleteVersion()

        createDownloadDir()
    end

    local function reloadModule( moduleName )

        package.loaded[moduleName] = nil

        return require(moduleName)
    end

    local function enter(sender)

        if not isUpdateItemClicked then
            local realPath = pathToSave .. "/package"
            addSearchPath(realPath,true)
        end

        assetsManagerModule = reloadModule("src/AssetsManagerTest/AssetsManagerModule")

        assetsManagerModule.newScene(AssetsManagerTestMain)
    end

    local callbackFuncs =
    {
        enter,
        reset,
        update,
    }

    local function menuCallback(tag, menuItem)
        local scene = nil
        local nIdx = menuItem:getLocalZOrder() - itemTagBasic
        local ExtensionsTestScene = CreateExtensionsTestScene(nIdx)
        if nil ~= ExtensionsTestScene then
            cc.Director:getInstance():replaceScene(ExtensionsTestScene)
        end
    end

    for i = 1, table.getn(menuItemNames) do
        local item = cc.MenuItemFont:create(menuItemNames[i])
        item:registerScriptTapHandler(callbackFuncs[i])
        item:setPosition(winSize.width / 2, winSize.height - i * lineSpace)
        if not support then
            item:setEnabled(false)
        end
        menu:addChild(item, itemTagBasic + i)
    end

    local function onNodeEvent(msgName)
        if nil ~= assetsManager then
            assetsManager:release()
            assetsManager = nil
        end
    end

    layer:registerScriptHandler(onNodeEvent)

    layer:addChild(menu)

    return layer
end

-------------------------------------
--  AssetsManager Test
-------------------------------------
function AssetsManagerTestMain()
    local scene = cc.Scene:create()
    scene:addChild(updateLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
