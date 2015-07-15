------------------------------------------------------------------------
local VibrateControlTest = {}

function VibrateControlTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("vibrate control test")
    -- Helper.subtitleLabel:setString("subtitleLabel")
    local layerSize = layer:getContentSize()

    VibrateControlTest._duration = 0.1

    ------playItem
    local function onStartVibrate(tag, sender)
        cc.Device:vibrate(VibrateControlTest._duration)
    end

    local vibrateItem = cc.MenuItemFont:create("vibrate")
    vibrateItem:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * 0.7))
    vibrateItem:registerScriptTapHandler(onStartVibrate)

    local menu = cc.Menu:create()
    menu:addChild(vibrateItem)
    menu:setPosition(cc.p(0, 0))
    layer:addChild(menu)

    VibrateControlTest._durationLabel = cc.Label:createWithTTF("duration: "..string.format("%.3f", VibrateControlTest._duration).."s", "fonts/arial.ttf", 20)
    VibrateControlTest._durationLabel:setPosition(cc.p(layerSize.width * 0.5,layerSize.height * 0.5))
    layer:addChild(VibrateControlTest._durationLabel)

    local function durationSliderChangedEvent(sender,eventType)
        VibrateControlTest._duration = (sender:getPercent() / 100.0) * 1.9 + 0.1  -- from 0.1ms to 2s
        VibrateControlTest._durationLabel:setString("duration: "..string.format("%.3f", VibrateControlTest._duration).."s")
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

    function onNodeEvent(tag)
        if tag == "exit" then
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