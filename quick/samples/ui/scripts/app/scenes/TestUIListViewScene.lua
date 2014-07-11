
local TestUIListViewScene = class("TestUIListViewScene", function()
    return display.newScene("TestUIListViewScene")
end)

function TestUIListViewScene:ctor()
    app:createGrid(self)

    self:createListView1()

    app:createTitle(self, "Test UIListView")
    app:createNextButton(self)
end

function TestUIListViewScene:createListView1()
    self.listview = cc.ui.UIListView.new{
            viewRect = cc.rect(20, 80, 200, display.height - 150),
            -- bgColor = cc.c4b(250, 0, 0, 255),
            bg = "YellowBlock.png",
            showScrollBar = false,
            scrollWidth = 10}
        :registerHandler(self.listViewDelegate, cc.ui.UIListView.DELEGATE)
        :addTo(self)
        :reload()
end

function TestUIListViewScene:listViewDelegate(name, idx, param)
    -- print("htl listview delegate:" .. name, idx)

    if name == cc.ui.UIListView.CELL_TAG then
        local i = math.random(4)
        local item

        if 1 == i then
            item = cc.ui.UILabel.new(
                {text = "text"..idx, size = 20,
                align = cc.ui.TEXT_ALIGN_CENTER,
                color = display.COLOR_WHITE})
        elseif 2 == i then
            item = cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
                :setButtonSize(160, 40)
                :setButtonLabel(cc.ui.UILabel.new({text = "Button" .. idx, size = 16, color = display.COLOR_BLUE}))
                :onButtonPressed(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_RED)
                end)
                :onButtonRelease(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_BLUE)
                end)
                :onButtonClicked(function(event)
                    print("TestUIListViewScene - Button" .. idx .. " clicked")
                end)
        elseif 4 == i then
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

            item = cc.ui.UICheckBoxButton.new({off = "CheckBoxButton2Off.png", on = "CheckBoxButton2On.png",})
                :setButtonLabel(cc.ui.UILabel.new({text = "CheckBox" .. idx, size = 14,  color = display.COLOR_BLUE}))
                :setButtonLabelOffset(20, 0)
                :setButtonLabelAlignment(display.LEFT_CENTER)
                onButtonClicked(function(event)
                    print("TestUIListViewScene - CheckBox" .. idx .. " clicked")
                end)
        elseif 3 == i then
            item = cc.Node:create()
            cc.ui.UICheckBoxButton.new({off = "CheckBoxButton2Off.png", on = "CheckBoxButton2On.png",})
                :setButtonLabel(cc.ui.UILabel.new({text = "Checkbox" .. idx, size = 16,  color = display.COLOR_BLUE}))
                :setButtonLabelOffset(70, 0)
                :setButtonLabelAlignment(display.CENTER)
                :align(display.CENTER, 40, 30)
                :addTo(item)
            cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
                :setButtonSize(60, 40)
                :setButtonLabel(cc.ui.UILabel.new({text = "Button" .. idx, size = 16, color = display.COLOR_BLUE}))
                :onButtonPressed(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_RED)
                end)
                :onButtonRelease(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_BLUE)
                end)
                :onButtonClicked(function(event)
                    print("TestUIListViewScene - Button" .. idx .. " clicked")
                end)
                :align(display.CENTER, 160, 20)
                :addTo(item)
        end
        return item
    elseif name == cc.ui.UIListView.CELL_SIZE_TAG then
        if 1 == idx%2 then
            return 200, 40
        else
            return 200, 60
        end
    elseif name == cc.ui.UIListView.COUNT_TAG then
        return 10
    elseif name == cc.ui.UIListView.CLICKED_TAG then
        print("htl clicked on " .. idx .. " point:(" .. param.x .. " ," .. param.y .. ")")
    end
end

return TestUIListViewScene
