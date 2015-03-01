local SliderEx = class("SliderEx", function()
    local slider = cc.Sprite:create("cocosui/sliderTrack.png")
    return slider
end)

SliderEx.TouchEventDown = 0
SliderEx.TouchEventMove = 1
SliderEx.TouchEventUp = 2
SliderEx.TouchEventCancel = 3

function SliderEx:create()
    local slider = SliderEx:new()
    slider:registerScriptHandler(function(tag)
        if "enter" == tag then
            slider:onEnter()
        elseif "exit" == tag then
        end
    end)
    return slider
end

function SliderEx:onEnter()
    self._ratio = 0
    self._thumbX = 0

    local progressBar = cc.Sprite:create("cocosui/sliderProgress.png")
    progressBar:setAnchorPoint(cc.p(0,0))
    self:addChild(progressBar)

    local sliderSize = self:getContentSize()
    self._width = sliderSize.width
    self._thumb = cc.Sprite:create("cocosui/sliderThumb.png")
    self._thumb:setPosition(cc.p(0,sliderSize.height/2))
    self:addChild(self._thumb)

    local thumbSize = self._thumb:getContentSize()
    self._thumbRect = cc.rect(0, 0, thumbSize.width, thumbSize.height)

    local  listenner = cc.EventListenerTouchOneByOne:create()
    listenner:setSwallowTouches(true)
    listenner:registerScriptHandler(function(touch, event)
        local location = touch:getLocation()
        local locationInNode = self._thumb:convertToNodeSpace(location)
        if not cc.rectContainsPoint(self._thumbRect, locationInNode) then
            return false
        end

        self._touchBeganX = self:convertToNodeSpace(location).x
        self._thumbBeganX = self._thumbX
        if self._callback then
            self._callback(self,self._ratio,SliderEx.TouchEventDown)
        end
        return true
    end, cc.Handler.EVENT_TOUCH_BEGAN )

    listenner:registerScriptHandler(function(touch, event)
        local locationInNodeX = self:convertToNodeSpace(touch:getLocation()).x
        self:setThumbPosX(self._thumbBeganX + locationInNodeX - self._touchBeganX)

        if self._callback then
            self._callback(self,self._ratio,SliderEx.TouchEventMove)
        end
    end, cc.Handler.EVENT_TOUCH_MOVED )

    listenner:registerScriptHandler(function(touch, event)
        local locationInNodeX = self:convertToNodeSpace(touch:getLocation()).x
        self:setThumbPosX(self._thumbBeganX + locationInNodeX - self._touchBeganX)

        if self._callback then
            self._callback(self,self._ratio,SliderEx.TouchEventUp)
        end
    end, cc.Handler.EVENT_TOUCH_ENDED )

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listenner, self)
end

function SliderEx:setThumbPosX(newX)
    self._thumbX = newX
    if self._thumbX < 0 then
        self._thumbX = 0
    elseif self._thumbX > self._width then
        self._thumbX = self._width
    end

    self._ratio = self._thumbX / self._width
    self._thumb:setPositionX(self._thumbX)
end

function SliderEx:addRatioListener(callback)
    self._callback = callback
end

function SliderEx:setRatio(ratio)
    if ratio < 0 then
        ratio = 0
    elseif ratio > 1.0 then
        ratio = 1.0
    end

    self._ratio = ratio
    self._thumbX = self._ratio * self._width
    self._thumb:setPositionX(self._thumbX)
end

------------------------------------------------------------------------
local VibrateControlTest = {}

function VibrateControlTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("vibrate control test")
    -- Helper.subtitleLabel:setString("subtitleLabel")
    local layerSize = layer:getContentSize()

    VibrateControlTest._duration = 0.1

    local isSupported = "NO"
    if cc.Device:isVibrateSupported() then
        isSupported = "YES"
    end
    local supportedLabel = cc.Label:createWithTTF("supported: " .. isSupported,"fonts/arial.ttf", 20)
    supportedLabel:setAnchorPoint(cc.p(0.5,0.5))
    supportedLabel:setPosition(cc.p(layerSize.width * 0.5, layerSize.height * 0.7))
    layer:addChild(supportedLabel)

    ------playItem
    local function onStartVibrate(tag, sender)
        cc.Device:startVibrate(VibrateControlTest._duration)
    end

    local vibrateItem = cc.MenuItemFont:create("vibrate")
    vibrateItem:setPosition(cc.p(layerSize.width * 0.3,layerSize.height * 0.55))
    vibrateItem:registerScriptTapHandler(onStartVibrate)

    ------stopItem
    local function onStopVibrate(tag, sender)
        cc.Device:stopVibrate()
    end

    local stopItem = cc.MenuItemFont:create("stop")
    stopItem:setPosition(cc.p(layerSize.width * 0.7,layerSize.height * 0.55))
    stopItem:registerScriptTapHandler(onStopVibrate)

    local menu = cc.Menu:create()
    menu:addChild(vibrateItem)
    menu:addChild(stopItem)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)

    local function durationSliderChangedEvent(sender,eventType)
        -- from 0.1ms to 1s
        VibrateControlTest._duration = (sender:getPercent() / 100.0) * 0.9 + 0.1
    end
    local durationSlider = ccui.Slider:create()
    durationSlider:setPercent(0)
    durationSlider:setTouchEnabled(true)
    durationSlider:loadBarTexture("cocosui/sliderTrack.png")
    durationSlider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    durationSlider:loadProgressBarTexture("cocosui/sliderProgress.png")
    durationSlider:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * 0.35))
    durationSlider:addEventListener(durationSliderChangedEvent)
    layer:addChild(durationSlider)

    local durationSliderSize = durationSlider:getContentSize()
    local durationLabel = cc.Label:createWithTTF("duration:  ","fonts/arial.ttf", 20)
    durationLabel:setAnchorPoint(cc.p(1.0,0.5))
    durationLabel:setPosition(cc.p((layerSize.width - durationSliderSize.width)/2, layerSize.height * 0.35))
    layer:addChild(durationLabel)

    function onNodeEvent(tag)
        if tag == "exit" then
            cc.Device:stopVibrate()
        end
    end
    layer:registerScriptHandler(onNodeEvent)

    return layer
end
------------------------------------------------------------------------
function VibrateTestMain()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        VibrateControlTest.create
    }
    scene:addChild(VibrateControlTest.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end