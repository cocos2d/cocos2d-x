
local TestUISliderScene = class("TestUISliderScene", function()
    return display.newScene("TestUISliderScene")
end)

TestUISliderScene.SLIDER_IMAGES = {
    bar = "SliderBar.png",
    button = "SliderButton.png",
}

function TestUISliderScene:ctor()
    app:createGrid(self)

    self:createSliderGroup1()
    self:createSliderGroup2()

    app:createTitle(self, "Test UISlider")
    app:createNextButton(self)
end

function TestUISliderScene:createSliderGroup1()
    local barHeight = 40
    local barWidth = 400
    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + barWidth + 60, display.top - 60)
        :addTo(self)
    cc.ui.UISlider.new(display.LEFT_TO_RIGHT, TestUISliderScene.SLIDER_IMAGES, {scale9 = true})
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderSize(barWidth, barHeight)
        :setSliderValue(75)
        :align(display.LEFT_BOTTOM, display.left + 40, display.top - 80)
        :addTo(self)
    cc.ui.UILabel.new({text = "align LEFT_BOTTOM", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + 40, display.top - 30)
        :addTo(self)


    local barWidth = 280
    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + barWidth + 60, display.top - 140)
        :addTo(self)
    cc.ui.UISlider.new(display.LEFT_TO_RIGHT, TestUISliderScene.SLIDER_IMAGES, {scale9 = true})
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderSize(barWidth, barHeight)
        :setSliderValue(75)
        :align(display.CENTER, display.left + barWidth / 2 + 40, display.top - 160 + barHeight / 2)
        :addTo(self)
    cc.ui.UILabel.new({text = "align CENTER", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + 40, display.top - 110)
        :addTo(self)


    local barWidth = 340
    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + barWidth + 60, display.top - 220)
        :addTo(self)
    cc.ui.UISlider.new(display.LEFT_TO_RIGHT, TestUISliderScene.SLIDER_IMAGES, {scale9 = true})
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderSize(barWidth, barHeight)
        :setSliderValue(75)
        :align(display.RIGHT_TOP, display.left + barWidth + 40, display.top - 180 - barHeight / 2)
        :addTo(self)
    cc.ui.UILabel.new({text = "align RIGHT_TOP", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + 40, display.top - 190)
        :addTo(self)


    local barWidth = 360
    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + barWidth + 60, display.top - 300)
        :addTo(self)
    cc.ui.UISlider.new(display.RIGHT_TO_LEFT, TestUISliderScene.SLIDER_IMAGES, {scale9 = true})
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderSize(barWidth, barHeight)
        :setSliderValue(75)
        :align(display.LEFT_TOP, display.left + 40, display.top - 280)
        :addTo(self)
    cc.ui.UILabel.new({text = "RIGHT_TO_LEFT, align LEFT_TOP", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + 40, display.top - 270)
        :addTo(self)


    local barWidth = 240
    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + barWidth + 60, display.top - 380)
        :addTo(self)
    cc.ui.UISlider.new(display.LEFT_TO_RIGHT, {
            bar = "SliderBarFixed.png",
            button = "SliderButton.png",
        })
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderValue(75)
        :align(display.LEFT_TOP, display.left + 40, display.top - 360)
        :addTo(self)
    cc.ui.UILabel.new({text = "fixed size image, align LEFT_TOP", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.left + 40, display.top - 350)
        :addTo(self)
end

function TestUISliderScene:createSliderGroup2()
    local barWidth = 40
    local barHeight = 240
    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.cx + barWidth + 160, display.top - 60)
        :addTo(self)
    cc.ui.UISlider.new(display.TOP_TO_BOTTOM, TestUISliderScene.SLIDER_IMAGES, {scale9 = true})
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderSize(barWidth, barHeight)
        :setSliderButtonRotation(90)
        :setSliderValue(75)
        :align(display.CENTER_TOP, display.cx + 160, display.top - 40)
        :addTo(self)
    cc.ui.UILabel.new({text = "TOP_TO_BOTTOM, align CENTER_TOP", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.cx + 140, display.top - 30)
        :addTo(self)


    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.cx + barWidth + 260, display.top - 180)
        :addTo(self)
    cc.ui.UISlider.new(display.BOTTOM_TO_TOP, TestUISliderScene.SLIDER_IMAGES, {scale9 = true})
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderSize(barWidth, barHeight)
        :setSliderButtonRotation(90)
        :setSliderValue(75)
        :align(display.CENTER_BOTTOM, display.cx + 260, display.top - 380)
        :addTo(self)
    cc.ui.UILabel.new({text = "BOTTOM_TO_TOP,\nalign CENTER_BOTTOM", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.cx + 240, display.top - 120)
        :addTo(self)


    local valueLabel = cc.ui.UILabel.new({text = "", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.cx + barWidth + 60, display.top - 420)
        :addTo(self)
    cc.ui.UISlider.new(display.TOP_TO_BOTTOM, {
            bar = "SliderBarFixedV.png",
            button = "SliderButton.png",
        })
        :onSliderValueChanged(function(event)
            valueLabel:setString(string.format("value = %0.2f", event.value))
        end)
        :setSliderButtonRotation(90)
        :setSliderValue(75)
        :align(display.CENTER_TOP, display.cx + 60, display.cy - 40)
        :addTo(self)
    cc.ui.UILabel.new({text = "TOP_TO_BOTTOM,\nfixed size image,\nalign CENTER_TOP", size = 14, color = display.COLOR_BLACK})
        :align(display.LEFT_CENTER, display.cx + 60, display.top - 330)
        :addTo(self)
end

return TestUISliderScene
