
local TestUIPageViewScene = class("TestUIPageViewScene", function()
    return display.newScene("TestUIPageViewScene")
end)

function TestUIPageViewScene:ctor()
    app:createGrid(self)

    self:createPageView()

    app:createTitle(self, "Test UIPageView")
    app:createNextButton(self)
end

function TestUIPageViewScene:createPageView()
    self.pv = cc.ui.UIPageView.new {
        -- bgColor = cc.c4b(200, 200, 200, 120),
        -- bg = "sunset.png",
        viewRect = cc.rect(80, 80, 780, 480),
        column = 3, row = 3,
        padding = {left = 20, right = 20, top = 20, bottom = 20},
        columnSpace = 10, rowSapce = 10}
        :onTouch(handler(self, self.touchListener))
        :addTo(self)

    -- add items
    for i=1,18 do
        local item = self.pv:newItem()
        local content

        -- content = cc.ui.UILabel.new(
        --             {text = "item"..i,
        --             size = 20,
        --             align = cc.ui.TEXT_ALIGN_CENTER,
        --             color = display.COLOR_BLACK})
        content = display.newColorLayer(
            cc.c4b(math.random(250),
                math.random(250),
                math.random(250),
                250))
        content:setContentSize(240, 140)
        content:setTouchEnabled(false)
        item:addChild(content)
        self.pv:addItem(item)        
    end
    self.pv:reload()
end

function TestUIPageViewScene:touchListener(event)
    dump(event, "TestUIPageViewScene - event:")
    local listView = event.listView
    if 3 == event.itemPos then
        listView:removeItem(event.item, true)
    else
        -- event.item:setItemSize(120, 80)
    end
end

return TestUIPageViewScene
