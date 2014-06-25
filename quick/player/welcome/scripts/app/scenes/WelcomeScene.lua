    
local WelcomeScene = class("WelcomeScene", function()
    return display.newScene("WelcomeScene")
end)

function WelcomeScene:ctor()
    local bg = cc.LayerColor:create(cc.c4b(255, 255, 255, 255))
    self:addChild(bg)

    self:createLogo()
    self:createBannderAds()
    self:createButtons()
    self:createLine()
    self:createCopyright()

    local recents = __G__OPEN_RECENTS__
    -- __G__OPEN_RECENTS__ = nil
    if type(recents) ~= "table" then
        recents = {}
    end
    self:createOpenRecents(recents)
end

local function stripPath(path, maxLen)
    local l = string.len(path)
    if l <= maxLen then
        return path
    else
        local arr = string.split(path, device.directorySeparator)
        return arr[#arr - 1]
        -- return "... " .. string.sub(path, l - maxLen)
    end
end

function WelcomeScene:createOpenRecents(recents)
    local label = cc.ui.UILabel.new({
        text = "最近打开的项目:",
        align = ui.TEXT_ALIGN_LEFT,
        color = cc.c3b(48, 48, 48),
        size = 18,
    })
    label:align(display.LEFT_TOP, display.left + 660, display.top - 330)
    label:addTo(self)

    for i, path in ipairs(recents) do
        if i > 8 then break end
        local label = cc.ui.UILabel.new({
            text = stripPath(path, 36),
            font = "Monaco",
            align = ui.TEXT_ALIGN_LEFT,
            color = cc.c3b(48, 48, 48),
            size = 14,
        })
        label:align(display.LEFT_TOP, display.left + 680, display.top - 360 - 28 * (i - 1))
        label:addTo(self)


        -- touch event
        label:setTouchEnabled(true)
        label:addNodeEventListener(cc.NODE_TOUCH_EVENT, function ( event )
            local evt = cc.EventCustom:new("WELCOME_OPEN_RECENT")
            evt:setDataString(i-1)
            self:getEventDispatcher():dispatchEvent(evt)
        end)
    end
end

function WelcomeScene:createLogo()
    display.newSprite("LogoBanner.png")
        :align(display.LEFT_TOP, display.left + 20, display.top - 4)
        :addTo(self)
end

function WelcomeScene:createBannderAds()
    self.bannerAds_ = {}

    local banner = display.newSprite("BannerAd_01.png")
    local size = banner:getContentSize()
    banner:pos(display.cx, display.top - size.height / 2 - 50)
        :addTo(self)
end

function WelcomeScene:createLine()
    local line = cc.LayerColor:create(cc.c4b(153, 153, 153, 255), 1, 240)
    line:setPosition(display.left + 640, display.top - 580)
    self:addChild(line)
end

function WelcomeScene:createButtons()
    local left = display.left + 114
    local top = display.top - 386

    local newProjectButton = cc.ui.UIPushButton.new("NewProjectButton_zh.png")
        :onButtonClicked(function()
            cc.__NotificationCenter:getInstance():postNotification("WELCOME_NEW_PROJECT")
        end)
        :pos(left, top)
        :addTo(self)

    local openProjectButton = cc.ui.UIPushButton.new("OpenProjectButton_zh.png")
        :onButtonClicked(function()
            cc.__NotificationCenter:getInstance():postNotification("WELCOME_OPEN_PROJECT")
        end)
        :pos(left + 200, top)
        :addTo(self)

    local listSamplesButton = cc.ui.UIPushButton.new("ListSamplesButton_zh.png")
        :onButtonClicked(function()
            local evt = cc.EventCustom:new("WELCOME_LIST_SAMPLES")
            self:getEventDispatcher():dispatchEvent(evt)

        end)
        :pos(left + 400, top)
        :addTo(self)

    local openCommunityButton = cc.ui.UIPushButton.new("OpenCommunityButton_zh.png")
        :onButtonClicked(function()
            print("community")
            cc.__NotificationCenter:getInstance():postNotification("WELCOME_OPEN_COMMUNITY")
        end)
        :pos(left, top - 140)
        :addTo(self)

    local openDocumentsButton = cc.ui.UIPushButton.new("OpenDocumentsButton_zh.png")
        :onButtonClicked(function()
            print("documents")
            cc.__NotificationCenter:getInstance():postNotification("WELCOME_OPEN_DOCUMENTS")
        end)
        :pos(left + 200, top - 140)
        :addTo(self)
end

function WelcomeScene:createCopyright()
    local label = ui.newTTFLabel({
        text = "Copyright (c) 2012-2014 chukong-inc.com, licensed under MIT.",
        size = 14,
        color = cc.c3b(144, 144, 144),
        x = display.cx,
        y = display.bottom + 24,
        align = ui.TEXT_ALIGN_CENTER,
    })
    self:addChild(label)
end

return WelcomeScene
