local CloneTestScene = game.createSceneClass("CloneTestScene")

function CloneTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "the left widget is clone from right"
    })

    self:cloneTest()
end

function CloneTestScene:cloneTest()
    self:cloneButton()
    self:cloneCheckBox()
    self:cloneImage()
    self:cloneSlider()
end

function CloneTestScene:cloneButton()
    local images = {
        normal = "Button01.png",
        pressed = "Button01Pressed.png",
        disabled = "Button01Disabled.png",
    }

    local node = cc.ui.UIPushButton.new(images, {scale9 = true})
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
            print("cloneTest.lua button clicked")
            -- dump(event, "event:")
            -- local button = event.target
            -- button:setButtonEnabled(false)
            -- button:setButtonLabelString("disabled", "Button Enable after 1s")
            -- self:performWithDelay(function()
            --     button:setButtonLabelString("disabled", "Button Disabled")
            --     button:setButtonEnabled(true)
            -- end, 1.0)
        end)
        :align(display.LEFT_CENTER, display.left + 50, display.top - 100)
        :addTo(self)

    local cloneNode = node:clone() -- cc.uiloader:clone(node)
    if cloneNode then
        cloneNode:pos(display.left + 50, display.top - 170):addTo(self)
            :onButtonClicked(function(event)
                print("cloneTest.lua clone button clicked")
            end)
    else
        print("clone button fail")
    end
end

function CloneTestScene:cloneCheckBox()
    local checkboxImages = {
        off = "RadioButtonOff.png",
        off_pressed = "RadioButtonOffPressed.png",
        off_disabled = "RadioButtonOffDisabled.png",
        on = "RadioButtonOn.png",
        on_pressed = "RadioButtonOnPressed.png",
        on_disabled = "RadioButtonOnDisabled.png",
    }

    local group = cc.ui.UICheckBoxButtonGroup.new(display.TOP_TO_BOTTOM)
        :addButton(cc.ui.UICheckBoxButton.new(checkboxImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 1", color = display.COLOR_WHITE}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(checkboxImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 2", color = display.COLOR_WHITE}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(checkboxImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 3", color = display.COLOR_WHITE}))
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :addButton(cc.ui.UICheckBoxButton.new(checkboxImages)
            :setButtonLabel(cc.ui.UILabel.new({text = "option 4 disabled", color = display.COLOR_WHITE}))
            :setButtonEnabled(false)
            :setButtonLabelOffset(20, 0)
            :align(display.LEFT_CENTER))
        :setButtonsLayoutMargin(10, 10, 10, 10)
        :onButtonSelectChanged(function(event)
            printf("Option %d selected, Option %d unselected", event.selected, event.last)
        end)
        :align(display.LEFT_TOP, display.left + 50, display.top - 300)
        :addTo(self)
    group:getButtonAtIndex(4):setButtonSelected(true)

    local cloneNode = group:clone() -- cc.uiloader:clone(node)
    if cloneNode then
        cloneNode:align(display.LEFT_TOP, display.left + 50, display.top - 400)
        :addTo(self):setButtonsLayoutMargin(10, 10, 10, 10)
    else
        print("clone button fail")
    end
end

function CloneTestScene:cloneImage()
    local image = cc.ui.UIImage.new("PinkScale9Block.png", {scale9 = true})
        :setLayoutSize(100, 50)
        :align(display.LEFT_CENTER, display.right - 300, display.top - 100)
        :addTo(self)

    local cloneNode = image:clone()
    if cloneNode then
        cloneNode:align(display.LEFT_CENTER, display.right - 100, display.top - 100)
        :addTo(self)
    else
        print("clone button fail")
    end
end

function CloneTestScene:cloneSlider()
    local sliderImages = {
        bar = "SliderBar.png",
        button = "SliderButton.png",
    }
    local slider = cc.ui.UISlider.new(display.LEFT_TO_RIGHT, sliderImages, {scale9 = true})
        :setSliderSize(200, 40)
        :setSliderValue(75)
        :align(display.CENTER, display.right - 100, display.top - 150)
        :addTo(self)

    local cloneNode = slider:clone()
    if cloneNode then
        cloneNode:pos(display.right - 100, display.top - 200):addTo(self)
    else
        print("clone slider fail")
    end
end

return CloneTestScene
