
local SampleScene = class("SampleScene", function()
    return display.newScene("SampleScene")
end)

function SampleScene:ctor()
    self.samples     = dofile(__G__QUICK_PATH__ .. "/samples/samples.lua")
    self.sampleIndex = 1
    local bg         = CCLayerColor:create(cc.c4b(255, 255, 255, 255))
    self:addChild(bg)

    self:createLogo()
    self:createPageView()
    self:createCopyright()
end

function SampleScene:createLogo()
    cc.ui.UIPushButton.new("LogoBanner.png")
        :onButtonClicked(function() 
            local evt = cc.EventCustom:new("WELCOME_APP")
            self:getEventDispatcher():dispatchEvent(evt)
        end)
        :align(display.LEFT_TOP, display.left + 20, display.top - 4)
        :addTo(self, 1)
end

function SampleScene:createCopyright()
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

function SampleScene:createPageView()

    local originLeft  = display.left + 130
    local left        = originLeft
    local originTop   = display.top - 180
    local top         = originTop
    
    local vMargin     = 20
    local hMargin     = 30
    
    local imageWidth  = 200
    local imageHeight = 150

    local sampleCount = #self.samples
    local maxNum      = 12

    self.pageCount = math.ceil(sampleCount / maxNum)
    self.currentPageIndex = 1
    self.wallLayers = {}

    for pageCount = 1, self.pageCount do
        local wallLayer = display.newLayer()
        wallLayer:setTouchEnabled(false)
        wallLayer:setPosition(20, 25)
        wallLayer:setTag(1000 + pageCount)
        wallLayer:addTo(self)

        self.wallLayers[#self.wallLayers+1] = wallLayer

        top = originTop
        for i = 1, 3 do
            for j = 1, 4 do
                local sample = self.samples[self.sampleIndex]
                self.sampleIndex = self.sampleIndex + 1

                if sample ~= nil then
                    wallLayer:addChild(self:createDemoTitle(sample, left, top + 95))
                    wallLayer:addChild(self:createDemoDescription(sample ,left ,top + 75))
                    wallLayer:addChild(self:createDemoButton(sample, left, top))
                else
                    break
                end
                left = left + vMargin + imageWidth
            end

            left = originLeft
            top  = top - hMargin - imageHeight
        end
    end

    -- self:addChild(self.wallLayers[1])
    self:createBackButton()
    self:createLRButton()
    self:updateWall()
end

-- helper

function SampleScene:createDemoTitle(sample, x, y)
    local label = ui.newTTFLabel({
        text = sample.title,
        align = ui.TEXT_ALIGNMENT_CENTER,
        color = cc.c3b(144,144,144),
        size = 14,
        font = "Monaco",
    })
    label:setPosition(cc.p(x, y))
    return label
end

function SampleScene:createDemoDescription(sample, x, y)
    local label = ui.newTTFLabel({
        text = sample.title,
        align = ui.TEXT_ALIGNMENT_CENTER,
        color = cc.c3b(50,144,144),
        size = 12,
    })
    label:setPosition(cc.p(x, y))
    return label
end

function SampleScene:createDemoButton(sample, x, y)
    function onButtonClick()
        local configPath = __G__QUICK_PATH__ .. sample.path .. "/scripts/config.lua"
        dofile(configPath)
        local args = {
            "-workdir",
            __G__QUICK_PATH__ .. sample.path,
            "-size",
            CONFIG_SCREEN_WIDTH.."x"..CONFIG_SCREEN_HEIGHT,
            "-" .. CONFIG_SCREEN_ORIENTATION,
        }
        local projectPath = __G__QUICK_PATH__ .. sample.path
        local commandline = "-workdir," .. projectPath .. ",-size," .. CONFIG_SCREEN_WIDTH.."x"..CONFIG_SCREEN_HEIGHT .. ",-" .. CONFIG_SCREEN_ORIENTATION
    
        local evt = cc.EventCustom:new("WELCOME_OPEN_PROJECT_ARGS")
        evt:setDataString(commandline)
        self:getEventDispatcher():dispatchEvent(evt)
    end

    local demoImage = sample.image or "ListSamplesButton_zh.png"
    
    local button = cc.ui.UIPushButton.new(demoImage, {scale9 = true})
                        :onButtonClicked(onButtonClick)
                        :align(display.CENTER, x, y)
    return button
end

function SampleScene:createBackButton()
    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonSize(100, 50)
        :setButtonLabel(cc.ui.UILabel.new({text = "Back", size = 20, color = display.COLOR_BLACK}))
        :pos(display.width - 80, 30)
        :addTo(self)
        :onButtonClicked(function()
            app:backToMainScene()
        end)
end

function SampleScene:createLRButton()
    cc.ui.UIPushButton.new("arrow_left.png", {scale9 = true})
        :setButtonSize(50, 50)
        :pos(30, display.cy)
        :addTo(self, 0, 100)
        :onButtonClicked(function()
            self:goLeftWall()
            self:updateArrow()
        end)

    cc.ui.UIPushButton.new("arrow_right.png", {scale9 = true})
        :setButtonSize(50, 50)
        :pos(display.width - 30, display.cy)
        :addTo(self, 0, 101)
        :onButtonClicked(function()
            self:goRightWall()
            self:updateArrow()
        end)

    self:updateArrow()
end

function SampleScene:updateArrow()
    local pageIdx = self.currentPageIndex - 1
    if 0 == pageIdx then
        self:getChildByTag(100):setVisible(false)
        self:getChildByTag(101):setVisible(true)
    else
        self:getChildByTag(100):setVisible(true)
        self:getChildByTag(101):setVisible(false)
    end
end

function SampleScene:goLeftWall()
    if self.currentPageIndex > 1 then 
        self.currentPageIndex = self.currentPageIndex - 1 
    end
    self:updateWall()
end

function SampleScene:goRightWall()
    if self.currentPageIndex < self.pageCount then 
        self.currentPageIndex = self.currentPageIndex + 1 
    end
    self:updateWall()
end

function SampleScene:updateWall()
    for i,v in ipairs(self.wallLayers) do
        if i == self.currentPageIndex then
            v:setVisible(true)
            self:setLayerEnabled(v, true)
        else
            v:setVisible(false)
            self:setLayerEnabled(v, false)
        end
    end
end

-- helper

function SampleScene:setLayerEnabled(layer, isEnabled)
    for _,v in ipairs(layer:getChildren()) do
        v:setTouchEnabled(isEnabled)
    end
end

return SampleScene
