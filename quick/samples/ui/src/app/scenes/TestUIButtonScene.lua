
local TestUIButtonScene = class("TestUIButtonScene", function()
    return display.newScene("TestUIButtonScene")
end)

TestUIButtonScene.CHECKBOX_BUTTON_IMAGES = {
    off = "CheckBoxButtonOff.png",
    off_pressed = "CheckBoxButtonOffPressed.png",
    off_disabled = "CheckBoxButtonOffDisabled.png",
    on = "CheckBoxButtonOn.png",
    on_pressed = "CheckBoxButtonOnPressed.png",
    on_disabled = "CheckBoxButtonOnDisabled.png",
}

TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES = {
    off = "CheckBoxButton2Off.png",
    on = "CheckBoxButton2On.png",
}

TestUIButtonScene.PUSH_BUTTON_IMAGES = {
    normal = "Button01.png",
    pressed = "Button01Pressed.png",
    disabled = "Button01Disabled.png",
}

TestUIButtonScene.RADIO_BUTTON_IMAGES = {
    off = "RadioButtonOff.png",
    off_pressed = "RadioButtonOffPressed.png",
    off_disabled = "RadioButtonOffDisabled.png",
    on = "RadioButtonOn.png",
    on_pressed = "RadioButtonOnPressed.png",
    on_disabled = "RadioButtonOnDisabled.png",
}

function TestUIButtonScene:ctor()
    app:createGrid(self)

    self:createButtonGroup1()
    self:createButtonGroup2()
    self:createButtonGroup3()

    app:createTitle(self, "Test UIButton")
    app:createNextButton(self)
end

function TestUIButtonScene:createButtonGroup1()
    local checkBoxButton1, checkBoxButton2

    local function updateCheckBoxButtonLabel(checkbox)
        local state = ""
        if checkbox:isButtonSelected() then
            state = "on"
        else
            state = "off"
        end
        if not checkbox:isButtonEnabled() then
            state = state .. " (disabled)"
        end
        checkbox:setButtonLabelString(string.format("state is %s", state))
    end

    checkBoxButton1 = cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 22,  color = cc.c3b(255, 96, 255)}))
        :setButtonLabelOffset(0, -40)
        :setButtonLabelAlignment(display.CENTER)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :align(display.LEFT_CENTER, display.left + 40, display.top - 80)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton1)

    checkBoxButton2 = cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON_IMAGES)
        :setButtonSelected(true)
        :setButtonLabel(cc.ui.UILabel.new({text = "", size = 22, color = cc.c3b(96, 200, 96)}))
        :setButtonLabelOffset(0, -40)
        :setButtonLabelAlignment(display.CENTER)
        :onButtonStateChanged(function(event)
            updateCheckBoxButtonLabel(event.target)
        end)
        :align(display.LEFT_CENTER, display.left + 260, display.top - 80)
        :addTo(self)
    updateCheckBoxButtonLabel(checkBoxButton2)

    cc.ui.UIPushButton.new(TestUIButtonScene.PUSH_BUTTON_IMAGES, {scale9 = true})
        :setButtonSize(240, 60)
        :setButtonLabel("normal", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "This is a PushButton",
            size = 18
        }))
        :setButtonLabel("pressed", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "Button Pressed",
            size = 18,
            color = cc.c3b(255, 64, 64)
        }))
        :setButtonLabel("disabled", cc.ui.UILabel.new({
            UILabelType = 2,
            text = "Button Disabled",
            size = 18,
            color = cc.c3b(0, 0, 0)
        }))
        :onButtonClicked(function(event)
            if math.random(0, 1) == 0 then
                checkBoxButton1:setButtonEnabled(not checkBoxButton1:isButtonEnabled())
            else
                checkBoxButton2:setButtonEnabled(not checkBoxButton2:isButtonEnabled())
            end

            local button = event.target
            button:setButtonEnabled(false)
            button:setButtonLabelString("disabled", "Button Enable after 1s")
            self:performWithDelay(function()
                button:setButtonLabelString("disabled", "Button Disabled")
                button:setButtonEnabled(true)
            end, 1.0)
        end)
        :align(display.LEFT_CENTER, display.left + 480, display.top - 80)
        :addTo(self)
end

function TestUIButtonScene:createButtonGroup2()
    local group = cc.ui.UICheckBoxButtonGroup.new(display.TOP_TO_BOTTOM)
        :addButton(cc.ui.UICheckBoxButton.new(TestUIButtonScene.RADIO_BUTTON_IMAGES)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 1", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(TestUIButtonScene.RADIO_BUTTON_IMAGES)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 2", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(TestUIButtonScene.RADIO_BUTTON_IMAGES)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 3", color = display.COLOR_BLACK}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(TestUIButtonScene.RADIO_BUTTON_IMAGES)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 4 disabled", color = display.COLOR_BLACK}))
            :setButtonEnabled(false)
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :setButtonsLayoutMargin(10, 10, 10, 10)
        :onButtonSelectChanged(function(event)
            printf("Option %d selected, Option %d unselected", event.selected, event.last)
        end)
        :align(display.LEFT_TOP, display.left + 40, display.top - 240)
        :addTo(self)
    group:getButtonAtIndex(4):setButtonSelected(true)

    cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
        :setButtonSize(160, 40)
        :setButtonLabel(cc.ui.UILabel.new({text = "Remove option 2", size = 16, color = display.COLOR_BLUE}))
        :onButtonPressed(function(event)
            event.target:getButtonLabel():setColor(display.COLOR_RED)
        end)
        :onButtonRelease(function(event)
            event.target:getButtonLabel():setColor(display.COLOR_BLUE)
        end)
        :onButtonClicked(function(event)
            if group:getButtonsCount() == 4 then
                group:removeButtonAtIndex(2)
                event.target:removeSelf()
            end
        end)
        :align(display.LEFT_CENTER, display.left + 200, display.top - 210)
        :addTo(self)
end

function TestUIButtonScene:createButtonGroup3()
    local x = display.left + 80
    local y = display.top - 400
    cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 1", size = 16,  color = display.COLOR_BLUE}))
        :setButtonLabelOffset(40, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.LEFT_CENTER, x, y)
        :addTo(self)

    y = y - 60
    cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 2", size = 16,  color = display.COLOR_BLUE}))
        :setButtonLabelOffset(40, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.CENTER, x, y)
        :addTo(self)

    y = y - 60
    cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 3", size = 16,  color = display.COLOR_BLUE}))
        :setButtonLabelOffset(40, 0)
        :setButtonLabelAlignment(display.LEFT_CENTER)
        :align(display.RIGHT_CENTER, x, y)
        :addTo(self)

    ----

    x = x + 280
    cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 4", size = 16,  color = display.COLOR_BLUE}))
        :setButtonLabelOffset(-40, 0)
        :setButtonLabelAlignment(display.RIGHT_CENTER)
        :align(display.CENTER, x, y)
        :addTo(self)

    x = x + 120
    cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 5", size = 16,  color = display.COLOR_BLUE}))
        :setButtonLabelOffset(0, 40)
        :setButtonLabelAlignment(display.CENTER)
        :align(display.CENTER, x, y)
        :addTo(self)

    x = x + 120
    cc.ui.UICheckBoxButton.new(TestUIButtonScene.CHECKBOX_BUTTON2_IMAGES)
        :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 6", size = 16,  color = display.COLOR_BLUE}))
        :setButtonLabelOffset(0, -40)
        :setButtonLabelAlignment(display.CENTER)
        :align(display.CENTER, x, y)
        :addTo(self)
end

return TestUIButtonScene
