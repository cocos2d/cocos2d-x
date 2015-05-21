local visibleRect = cc.Director:getInstance():getOpenGLView():getVisibleRect()
local centerPos   = cc.p(visibleRect.x + visibleRect.width / 2,visibleRect.y + visibleRect.height /2)

local function VideoPlayerTest()
    local layer = cc.Layer:create() --createTestLayer("VideoPlayerTest", "")
    titleLabel = cc.Label:createWithTTF("VideoPlayerTest", s_arialPath, 28)
    titleLabel:setAnchorPoint(cc.p(0.5, 0.5))
    layer:addChild(titleLabel, 1)
    
    cc.MenuItemFont:setFontSize(16)

    widget = ccs.GUIReader:getInstance():widgetFromJsonFile("cocosui/UITest/UITest.json")
    layer:addChild(widget)

    local videoStateLabel = cc.Label:createWithSystemFont("IDLE","Arial",16)
    videoStateLabel:setAnchorPoint(cc.p(1, 0.5))
    videoStateLabel:setPosition(cc.p(visibleRect.x + visibleRect.width - 10,visibleRect.y + 200))
    layer:addChild(videoStateLabel)

    local function onVideoEventCallback(sener, eventType)
        if eventType == ccexp.VideoPlayerEvent.PLAYING then
            videoStateLabel:setString("PLAYING")
        elseif eventType == ccexp.VideoPlayerEvent.PAUSED then
            videoStateLabel:setString("PAUSED")
        elseif eventType == ccexp.VideoPlayerEvent.STOPPED then
            videoStateLabel:setString("STOPPED")
        elseif eventType == ccexp.VideoPlayerEvent.COMPLETED then
            videoStateLabel:setString("COMPLETED")
        end
    end
    local widgetSize = widget:getContentSize()
    local videoPlayer = ccexp.VideoPlayer:create()
    videoPlayer:setPosition(centerPos)
    videoPlayer:setAnchorPoint(cc.p(0.5, 0.5))
    videoPlayer:setContentSize(cc.size(widgetSize.width * 0.4,widgetSize.height * 0.4))
    videoPlayer:addEventListener(onVideoEventCallback)
    layer:addChild(videoPlayer)
        
    local screenSize = cc.Director:getInstance():getWinSize()
    local rootSize = widget:getContentSize()
    layer:setPosition(cc.p((screenSize.width - rootSize.width) / 2,(screenSize.height - rootSize.height) / 2))

    local function menuFullScreenCallback(tag, sender)
        if nil  ~= videoPlayer then
            videoPlayer:setFullScreenEnabled(not videoPlayer:isFullScreenEnabled())
        end
    end
    local fullSwitch = cc.MenuItemFont:create("FullScreenSwitch")
    fullSwitch:setAnchorPoint(cc.p(0.0, 0.0))
    fullSwitch:setPosition(cc.p(visibleRect.x + 10,visibleRect.y + 50))
    fullSwitch:registerScriptTapHandler(menuFullScreenCallback)

    local function menuPauseCallback(tag, sender)
        if nil  ~= videoPlayer then
            videoPlayer:pause()
        end
    end
    local pauseItem = cc.MenuItemFont:create("Pause")
    pauseItem:setAnchorPoint(cc.p(0.0, 0.0))
    pauseItem:setPosition(cc.p(visibleRect.x + 10,visibleRect.y + 100))
    pauseItem:registerScriptTapHandler(menuPauseCallback)

    local function menuResumeCallback(tag, sender)
        if nil  ~= videoPlayer then
            videoPlayer:resume()
        end
    end
    local resumeItem = cc.MenuItemFont:create("Resume")
    resumeItem:setAnchorPoint(cc.p(0.0, 0.0))
    resumeItem:setPosition(cc.p(visibleRect.x + 10,visibleRect.y + 150))
    resumeItem:registerScriptTapHandler(menuResumeCallback)

    local function menuStopCallback(tag, sender)
        if nil  ~= videoPlayer then
            videoPlayer:stop()
        end
    end
    local stopItem = cc.MenuItemFont:create("Stop")
    stopItem:setAnchorPoint(cc.p(0.0, 0.0))
    stopItem:setPosition(cc.p(visibleRect.x + 10,visibleRect.y + 200))
    stopItem:registerScriptTapHandler(menuStopCallback)

    local function menuHintCallback(tag, sender)
        if nil  ~= videoPlayer then
            videoPlayer:setVisible(not videoPlayer:isVisible())
        end
    end
    local hintItem = cc.MenuItemFont:create("Hint")
    hintItem:setAnchorPoint(cc.p(0.0, 0.0))
    hintItem:setPosition(cc.p(visibleRect.x + 10,visibleRect.y + 250))
    hintItem:registerScriptTapHandler(menuHintCallback)

    ------------------------------------------------------------
    local function menuResourceVideoCallback(tag, sender)
        if nil ~= videoPlayer then
            local videoFullPath = cc.FileUtils:getInstance():fullPathForFilename("cocosvideo.mp4")
            videoPlayer:setFileName(videoFullPath)   
            videoPlayer:play()
        end
    end

    local resourceVideo = cc.MenuItemFont:create("Play resource video")
    resourceVideo:setAnchorPoint(cc.p(1, 0.5))
    resourceVideo:setPosition(cc.p(visibleRect.x + visibleRect.width - 10,visibleRect.y + 50))
    resourceVideo:registerScriptTapHandler(menuResourceVideoCallback)

    local function menuOnlineVideoCallback(tag, sender)
        if nil ~= videoPlayer then
            videoPlayer:setURL("http://benchmark.cocos2d-x.org/cocosvideo.mp4")
            videoPlayer:play()
        end
    end
    local onlineVideo = cc.MenuItemFont:create("Play online video")
    onlineVideo:setAnchorPoint(cc.p(1, 0.5))
    onlineVideo:setPosition(cc.p(visibleRect.x + visibleRect.width - 10,visibleRect.y + 100))
    onlineVideo:registerScriptTapHandler(menuOnlineVideoCallback)

    local function menuRatioCallback(tag, sender)
        if nil ~= videoPlayer then
            videoPlayer:setKeepAspectRatioEnabled(not videoPlayer:isKeepAspectRatioEnabled())
        end
    end
    local ratioSwitch = cc.MenuItemFont:create("KeepRatioSwitch")
    ratioSwitch:setAnchorPoint(cc.p(1, 0.5))
    ratioSwitch:setPosition(cc.p(visibleRect.x + visibleRect.width - 10,visibleRect.y + 150))
    ratioSwitch:registerScriptTapHandler(menuRatioCallback)

    local menu = cc.Menu:create(fullSwitch, pauseItem, resumeItem, stopItem, hintItem, resourceVideo, onlineVideo, ratioSwitch)
    menu:setPosition(cc.p(0.0, 0.0))
    layer:addChild(menu)

    return layer
end



function VideoPlayerTestMain()
    Helper.index = 1
    local scene = cc.Scene:create()
    Helper.createFunctionTable = {
        VideoPlayerTest
    }
    scene:addChild(VideoPlayerTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end