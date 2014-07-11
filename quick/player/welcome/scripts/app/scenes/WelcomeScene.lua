local scheduler = require(cc.PACKAGE_NAME .. ".scheduler")

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

    __G__OPEN_RECENTS__ = {}
    for _,v in ipairs(cc.player.settings.PLAYER_OPEN_RECTNS) do
        __G__OPEN_RECENTS__[#__G__OPEN_RECENTS__+1] = v.title
    end

    local recents = __G__OPEN_RECENTS__
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
            local recent = cc.player.settings.PLAYER_OPEN_RECTNS [i]
            local commandline = table.concat(recent.args, ",")

            table.remove(cc.player.settings.PLAYER_OPEN_RECTNS , i)
            table.insert(cc.player.settings.PLAYER_OPEN_RECTNS, 1, recent)

            cc.player.saveSetting()

            local evt = cc.EventCustom:new("WELCOME_OPEN_PROJECT_ARGS")
            evt:setDataString(commandline)
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
    self.bannerAds_ = {{img="BannerAd_01.png",link="http://open.cocoachina.com/service/ad"},
                       {img="BannerAd_02.png",link="http://open.cocoachina.com/service/push"},
                       -- {img="BannerAd_03.png",link="http://open.cocoachina.com/service/push"},
                    }

    self.currenBannerIndex = 1    
    self.bannerSize = {w=920,h=248}

    -- draw banner
    self.banner = self:createBannerButton(self.bannerAds_[self.currenBannerIndex], display.cx) 


    -- auto scroll banner
    local nextBanner = function() self:nextBanner() end
    local autoScrollHandler = scheduler.scheduleGlobal(nextBanner, 5.0)

    local listener = function(event)
        if event.name == "exit" then
            scheduler.unscheduleGlobal(autoScrollHandler)
        end
    end
    self:addNodeEventListener(cc.NODE_EVENT, listener)


    -- left button
    -- cc.ui.UIPushButton.new("arrow_left.png", {scale9 = true})
    -- :setButtonSize(50, 50)
    -- :pos(30, display.top - 150)
    -- :addTo(self, 1, 100)
    -- :onButtonClicked(function()
    --     scheduler.unscheduleGlobal(autoScrollHandler)
    --     self:nextBanner()
    --     autoScrollHandler = scheduler.scheduleGlobal(nextBanner, 5.0)
    -- end)


    -- right button
    -- cc.ui.UIPushButton.new("arrow_right.png", {scale9 = true})
    --     :setButtonSize(50, 50)
    --     :pos(display.width - 30, display.top - 150)
    --     :addTo(self, 1, 100)
    --     :onButtonClicked(function()
    --         scheduler.unscheduleGlobal(autoScrollHandler)
    --         self:preBanner()
    --         autoScrollHandler = scheduler.scheduleGlobal(nextBanner, 5.0)
    --     end)


    -- prompt
    self:setAdPrompt()
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
            cc.__NotificationCenter:getInstance():postNotification("WELCOME_OPEN_COMMUNITY")
        end)
        :pos(left, top - 140)
        :addTo(self)

    local openDocumentsButton = cc.ui.UIPushButton.new("OpenDocumentsButton_zh.png")
        :onButtonClicked(function()
            cc.__NotificationCenter:getInstance():postNotification("WELCOME_OPEN_DOCUMENTS")
        end)
        :pos(left + 200, top - 140)
        :addTo(self)
end

function WelcomeScene:createCopyright()
    local label = ui.newTTFLabel({
        text = " Copyright 2012-2014 Chukong Technologies, Inc. Licensed under MIT License.",
        size = 14,
        color = cc.c3b(144, 144, 144),
        x = display.cx,
        y = display.bottom + 24,
        align = ui.TEXT_ALIGN_CENTER,
    })
    self:addChild(label)
end

-- ad helper 

function WelcomeScene:setAdPrompt()
    self.hintNode = self.hintNode or display.newDrawNode():addTo(self, 100)
    self.hintNode:clear()

    local hintLength = 30
    local x = (self.bannerSize.w - #self.bannerAds_ * hintLength - (#self.bannerAds_ -1) * 4) / 2
    for i=1,#self.bannerAds_ do
        local color = cc.c4f(1,1,1,0.5)
        if i == self.currenBannerIndex then
            color = cc.c4f(1,1,1,1)
        end

        self.hintNode:drawSegment(cc.p(x,display.top-280), cc.p(x+hintLength, display.top-280), 3, color)
        self.hintNode.info = {from=cc.p(x,display.top-280), to=cc.p(x+hintLength,display.top-280), r=3}
        x = x + hintLength + 10
    end
end

function WelcomeScene:nextBanner() 
    self.currenBannerIndex = self.currenBannerIndex +1 
    if self.currenBannerIndex > #self.bannerAds_ then self.currenBannerIndex = 1 end

    local fadeOutBanner = self.banner
    fadeOutBanner:runAction(cc.Sequence:create(
        cc.CallFunc:create(function() fadeOutBanner:setTouchEnabled(false) end),
        cc.FadeOut:create(0.5),
        cc.CallFunc:create(function() fadeOutBanner:removeFromParent() end)
        ))

    self.banner = self:createBannerButton(self.bannerAds_[self.currenBannerIndex], 3* display.cx) 
    self:setAdPrompt()
    transition.moveTo(self.banner, {x = display.cx, y = display.top - self.bannerSize.h / 2 - 50, time = 0.3})
end

function WelcomeScene:preBanner()
    self.currenBannerIndex = self.currenBannerIndex -1
    if self.currenBannerIndex < 1 then self.currenBannerIndex = #self.bannerAds_  end

    local fadeOutBanner = self.banner
    fadeOutBanner:runAction(cc.Sequence:create(
        cc.CallFunc:create(function() fadeOutBanner:setTouchEnabled(false) end),
        cc.FadeOut:create(0.5),
        cc.CallFunc:create(function() fadeOutBanner:removeFromParent() end)
        ))

    self.banner = self:createBannerButton(self.bannerAds_[self.currenBannerIndex], -display.cx) 
    self:setAdPrompt()
    transition.moveTo(self.banner, {x = display.cx, y = self.banner:getPositionY(), time = 0.3})
end

function WelcomeScene:createBannerButton( AD, x)
    local banner = cc.ui.UIPushButton.new(AD.img, {scale9 = true})
                    :setButtonSize(self.bannerSize.w, self.bannerSize.h)
                    :pos(x, display.top - self.bannerSize.h / 2 - 50)
                    :addTo(self)
                    :onButtonClicked(function() device.openURL(AD.link) end)
    return banner
end

return WelcomeScene
