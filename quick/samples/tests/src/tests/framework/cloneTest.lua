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
            local button = event.target
            button:setButtonEnabled(false)
            button:setButtonLabelString("disabled", "Button Enable after 1s")
            self:performWithDelay(function()
                button:setButtonLabelString("disabled", "Button Disabled")
                button:setButtonEnabled(true)
            end, 1.0)
        end)
        :align(display.LEFT_CENTER, display.left + 50, display.top - 100)
        :addTo(self)

    local cloneNode = cc.uiloader:clone(node)
    if cloneNode then
        cloneNode:pos(display.left + 200, display.top - 100):addTo(self)
    else
        print("clone fail")
    end
end

return CloneTestScene
