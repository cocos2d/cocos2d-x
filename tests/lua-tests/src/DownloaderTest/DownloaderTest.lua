require("json")


local imgURI = "https://forum.cocos.com/images/logo.png"
local notExistURI = "https://www.cocos2d-x.org/attachments/1503/no_exist.txt"

local writablePath = cc.FileUtils:getInstance():getWritablePath()
local function DownloaderLayer()
    local layer = cc.Layer:create()
    local winSize = cc.Director:getInstance():getWinSize()
    local margin = 40
    local space  = 35

    local task1 = nil
    local task2 = nil

    local downloader = cc.Downloader.new()
    
    local function init()

        local label = cc.Label:createWithTTF("Downloader Test", s_arialPath, 28)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(winSize.width / 2, winSize.height - margin))
        layer:addChild(label, 0)

        --Response Code Label
        local labelStatusCode = cc.Label:createWithTTF("status", s_markerFeltFontPath, 20)
        labelStatusCode:setAnchorPoint(cc.p(0.5, 0.5))
        labelStatusCode:setPosition(cc.p(winSize.width / 2,  winSize.height - margin - 6 * space))
        layer:addChild(labelStatusCode)

        local menuRequest = cc.Menu:create()
        menuRequest:setPosition(cc.p(0,0))
        layer:addChild(menuRequest)

        --success
        local function onDownloadFileClicked()
            downloader:createDownloadFileTask(imgURI, writablePath .. "/2dx_icon_512_rounded.png", "task_img");
            labelStatusCode:setString("waiting...")
        end

        local labelGet  = cc.Label:createWithTTF("Test Download Image", s_arialPath, 22)
        labelGet:setAnchorPoint(cc.p(0.5, 0.5))
        local itemGet  =  cc.MenuItemLabel:create(labelGet)
        itemGet:registerScriptTapHandler(onDownloadFileClicked)
        itemGet:setPosition(cc.p(winSize.width / 2, winSize.height - margin - space))
        menuRequest:addChild(itemGet)

        --failure
        local function onDownloadTxtClicked()
            downloader:createDownloadFileTask(notExistURI, writablePath .. "/no_exists.txt", "task_no_exist");
            labelStatusCode:setString("waiting...")
        end

        local labelPost = cc.Label:createWithTTF("Test Download File Not Exists", s_arialPath, 22)
        labelPost:setAnchorPoint(cc.p(0.5, 0.5))
        local itemPost =  cc.MenuItemLabel:create(labelPost)
        itemPost:registerScriptTapHandler(onDownloadTxtClicked)
        itemPost:setPosition(cc.p(winSize.width / 2, winSize.height - margin - 2 * space))
        menuRequest:addChild(itemPost)

        local function onTaskSuccess(task)
            if task.identifier == "task_img" then
                labelStatusCode:setString("image download success")
            elseif task.identifier == "task_no_exist" then
                labelStatusCode:setString("txt download success")
            end
        end
        local function onProgress(task, bytesReceived, totalBytesReceived, totalBytesExpected)
            if task.identifier == "task_img" then
                labelStatusCode:setString("image download progress " .. tostring(math.floor(totalBytesReceived/totalBytesExpected*100)))
            elseif task.identifier == "task_no_exist" then
                labelStatusCode:setString("txt download progress " .. tostring(math.floor(totalBytesReceived/totalBytesExpected*100)))
            end
        end
        local function onTaskError(task, errorCode, errorCodeInternal, errorStr)
            if task.identifier == "task_img" then
                labelStatusCode:setString("image download error: "..errorStr)
            elseif task.identifier == "task_no_exist" then
                labelStatusCode:setString("txt download error: "..errorStr)
            end
        end
        downloader:setOnFileTaskSuccess(onTaskSuccess)
        downloader:setOnTaskProgress(onProgress)
        downloader:setOnTaskError(onTaskError)

    end

    local function onNodeEvent(eventName)
        if "enter" == eventName then
            init()
        end
    end

    layer:registerScriptHandler(onNodeEvent)

    return layer
end

function DownloaderTestMain()
    local scene = cc.Scene:create()
    scene:addChild(DownloaderLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
