
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
            rect = cc.rect(10, 50, display.width - 20, display.height - 100),
            -- bgColor = cc.c4b(250, 0, 0, 255),
            bg = "YellowBlock.png",
            showScrollBar = true,
            scrollBar = "SliderBar.png",
            scrollButton = "SliderButton.png",
            scrollWidth = 10}
        :registerHandler(self.listViewDelegate, cc.ui.UIListView.DELEGATE)
        :addTo(self)
        :reload()
end

function TestUIListViewScene:listViewDelegate(name, idx, param)
    -- print("htl listview delegate:" .. name, idx)

    if name == cc.ui.UIListView.CELL_TAG then
        local i = math.random(3)
        local item

        if 1 == i then
            item = cc.ui.UILabel.new(
                {text = "text"..idx, size = 20,
                align = cc.ui.TEXT_ALIGN_CENTER,
                color = display.COLOR_WHITE})
        elseif 2 == i then
            item = cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
                :setButtonSize(160, 40)
                :setButtonLabel(cc.ui.UILabel.new({text = "Remove option 2", size = 16, color = display.COLOR_BLUE}))
                :onButtonPressed(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_RED)
                end)
                :onButtonRelease(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_BLUE)
                end)
                :onButtonClicked(function(event)
                    print("htl button2 clicked")
                end)
        elseif 3 == i then
            item = cc.Node:create()
            cc.ui.UICheckBoxButton.new({off = "CheckBoxButton2Off.png", on = "CheckBoxButton2On.png",})
                :setButtonLabel(cc.ui.UILabel.new({text = "checkbox 6", size = 16,  color = display.COLOR_BLUE}))
                :setButtonLabelOffset(0, -40)
                :setButtonLabelAlignment(display.CENTER)
                :align(display.CENTER, 60, 20)
                :addTo(item)
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
                    print("htl button3 clicked")
                end)
                :align(display.CENTER, 200, 20)
                :addTo(item)
        end
        return item
    elseif name == cc.ui.UIListView.CELL_SIZE_TAG then
        if 1 == idx%2 then
            return 300, 40
        else
            return 240, 60
        end
    elseif name == cc.ui.UIListView.COUNT_TAG then
        return 10
    elseif name == cc.ui.UIListView.CLICKED_TAG then
        print("htl clicked on " .. idx .. " point:(" .. param.x .. " ," .. param.y .. ")")
    end
end

return TestUIListViewScene
