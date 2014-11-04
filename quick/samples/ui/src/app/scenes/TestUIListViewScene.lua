
local TestUIListViewScene = class("TestUIListViewScene", function()
    return display.newScene("TestUIListViewScene")
end)

function TestUIListViewScene:ctor()
    app:createGrid(self)

    self:createListView5()
    self:createListView6()
    self:createListView7()
    self:createListView8()
    self:createListView9()

    app:createTitle(self, "Test UIListView")
    app:createNextButton(self)
end

function TestUIListViewScene:createListView5()
    cc.ui.UILabel.new(
        {text = "vertical listView",
        size = 24,
        color = display.COLOR_BLACK})
        :align(display.CENTER, 120, 520)
        :addTo(self)
    self.lv = cc.ui.UIListView.new {
        -- bgColor = cc.c4b(200, 200, 200, 120),
        bg = "sunset.png",
        bgScale9 = true,
        viewRect = cc.rect(40, 80, 120, 400),
        direction = cc.ui.UIScrollView.DIRECTION_VERTICAL,
        scrollbarImgV = "bar.png"}
        :onTouch(handler(self, self.touchListener))
        :addTo(self)

    -- add items
    for i=1,20 do
        local item = self.lv:newItem()
        local content
        if 1 == i then
            content = cc.ui.UILabel.new(
                    {text = "item"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
        elseif 2 == i then
            content = cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
                :setButtonSize(120, 40)
                :setButtonLabel(cc.ui.UILabel.new({text = "点击大小改变" .. i, size = 16, color = display.COLOR_BLUE}))
                :onButtonPressed(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_RED)
                end)
                :onButtonRelease(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_BLUE)
                end)
                :onButtonClicked(function(event)
                    -- if not self.lv:isItemInViewRect(item) then
                    --     print("TestUIListViewScene item not in view rect")
                    --     return
                    -- end

                    if self.bListViewMove then
                        print("TestUIListViewScene is scroll, not click")
                        return
                    end

                    print("TestUIListViewScene buttonclicked")
                    local _,h = item:getItemSize()
                    if 40 == h then
                        item:setItemSize(120, 80)
                    else
                        item:setItemSize(120, 40)
                    end
                end)
            content:setTouchSwallowEnabled(false)
        elseif 3 == i then
            content = cc.ui.UILabel.new(
                    {text = "点击删除它"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
        elseif 4 == i then
            content = cc.ui.UILabel.new(
                    {text = "有背景图"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
            item:setBg("YellowBlock.png")
        else
            content = cc.ui.UILabel.new(
                    {text = "item"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
        end
        item:addContent(content)
        item:setItemSize(120, 40)

        self.lv:addItem(item)
    end
    self.lv:reload()

end

function TestUIListViewScene:touchListener(event)
    local listView = event.listView
    if "clicked" == event.name then
        if 3 == event.itemPos then
            listView:removeItem(event.item, true)
        else
            -- event.item:setItemSize(120, 80)
        end
    elseif "moved" == event.name then
        self.bListViewMove = true
    elseif "ended" == event.name then
        self.bListViewMove = false
    else
        print("event name:" .. event.name)
    end
end

function TestUIListViewScene:createListView6()
    cc.ui.UILabel.new(
        {text = "horizontal listView",
        size = 24,
        color = display.COLOR_BLACK})
        :align(display.CENTER, 640, 260)
        :addTo(self)
    self.lvH = cc.ui.UIListView.new {
        bgColor = cc.c4b(200, 200, 200, 120),
        -- bg = "sunset.png",
        viewRect = cc.rect(360, 160, 560, 80),
        direction = cc.ui.UIScrollView.DIRECTION_HORIZONTAL,
        scrollbarImgH = "barH.png"}
        :onTouch(handler(self, self.touchListener))
        :addTo(self)

    -- add items
    for i=1,10 do
        local item = self.lvH:newItem()
        local content
        if 1 == i then
            content = cc.ui.UILabel.new(
                    {text = "item"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
        elseif 2 == i then
            content = cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
                :setButtonSize(120, 40)
                :setButtonLabel(cc.ui.UILabel.new({text = "点击大小改变" .. i, size = 16, color = display.COLOR_BLUE}))
                :onButtonPressed(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_RED)
                end)
                :onButtonRelease(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_BLUE)
                end)
                :onButtonClicked(function(event)
                    print("TestUIListViewScene buttonclicked")
                    local w, _ = item:getItemSize()
                    if 120 == w then
                        item:setItemSize(160, 80)
                    else
                        item:setItemSize(120, 80)
                    end
                end)
        elseif 3 == i then
            content = cc.ui.UILabel.new(
                    {text = "点击删除它"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
        elseif 4 == i then
            content = cc.ui.UILabel.new(
                    {text = "有背景图"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
            item:setBg("YellowBlock.png")
        else
            content = cc.ui.UILabel.new(
                    {text = "item"..i,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_BLACK})
        end
        item:addContent(content)
        item:setItemSize(120, 80)

        self.lvH:addItem(item)
    end
    self.lvH:reload()
end

function TestUIListViewScene:createListView7()
    cc.ui.UILabel.new(
        {text = "grid in fact it's a listView",
        size = 24,
        color = display.COLOR_BLACK})
        :align(display.CENTER, 680, 560)
        :addTo(self)
    self.lvGrid = cc.ui.UIListView.new {
        -- bgColor = cc.c4b(200, 200, 200, 120),
        -- bg = "sunset.png",
        viewRect = cc.rect(560, 280, 240, 240),
        direction = cc.ui.UIScrollView.DIRECTION_VERTICAL}
        :onTouch(handler(self, self.touchListener7))
        :addTo(self)

    -- add items
    for i=1,3 do
        local item = self.lvGrid:newItem()
        local content

        content = display.newNode()
        for count = 1, 3 do
            local idx = (i-1)*3 + count
            cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
                :setButtonSize(80, 80)
                :setButtonLabel(cc.ui.UILabel.new({text = "Button" .. idx, size = 16, color = display.COLOR_BLUE}))
                :onButtonPressed(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_RED)
                end)
                :onButtonRelease(function(event)
                    event.target:getButtonLabel():setColor(display.COLOR_BLUE)
                end)
                :onButtonClicked(function(event)
                    print("TestUIListViewScene - Button " .. idx .. " clicked, jude in botton call back")
                end)
                :align(display.CENTER, 80*count - 40, 40)
                :addTo(content)
                :setTouchSwallowEnabled(false)
        end
        content:setContentSize(240, 80)
        item:addContent(content)
        item:setItemSize(240, 80)

        self.lvGrid:addItem(item)
    end
    self.lvGrid:reload()

    -- HDrawRect(self.lv:getCascadeBoundingBox(), self, cc.c4f(0, 1, 0, 1))
end

function TestUIListViewScene:touchListener7(event)
    print("TestUIListViewScene - event:" .. event.name)
    if "clicked" == event.name then
        local column = math.ceil(event.point.x/80)
        local idx = (event.itemPos - 1)*3 + column
        print("TestUIListViewScene - Boutton " .. idx .. " clicked, judge in list touch listener")
    end
end

--这是一个listview的异步加载方式
function TestUIListViewScene:createListView8()
    cc.ui.UILabel.new(
        {text = "vertical listView",
        size = 24,
        color = display.COLOR_BLACK})
        :align(display.CENTER, 120, 520)
        :addTo(self)
    self.lv = cc.ui.UIListView.new {
        -- bgColor = cc.c4b(200, 200, 200, 120),
        bg = "sunset.png",
        bgScale9 = true,
        async = true, --异步加载
        viewRect = cc.rect(200, 80, 120, 400),
        direction = cc.ui.UIScrollView.DIRECTION_VERTICAL,
        scrollbarImgV = "bar.png"}
        :onTouch(handler(self, self.touchListener8))
        :addTo(self)

    self.lv:setDelegate(handler(self, self.sourceDelegate))

    self.lv:reload()
end

function TestUIListViewScene:sourceDelegate(listView, tag, idx)
    -- print(string.format("TestUIListViewScene tag:%s, idx:%s", tostring(tag), tostring(idx)))
    if cc.ui.UIListView.COUNT_TAG == tag then
        return 50
    elseif cc.ui.UIListView.CELL_TAG == tag then
        local item
        local content

        item = self.lv:dequeueItem()
        if not item then
            item = self.lv:newItem()
            content = cc.ui.UILabel.new(
                    {text = "item"..idx,
                    size = 20,
                    align = cc.ui.TEXT_ALIGN_CENTER,
                    color = display.COLOR_WHITE})
            item:addContent(content)
        else
            content = item:getContent()
        end
        content:setString("item:" .. idx)
        item:setItemSize(120, 80)

        return item
    else
    end
end

function TestUIListViewScene:touchListener8(event)
    local listView = event.listView
    if "clicked" == event.name then
        print("async list view clicked idx:" .. event.itemPos)
    end
end

function TestUIListViewScene:createListView9()
    self.lv = cc.ui.UIListView.new {
        -- bgColor = cc.c4b(200, 200, 200, 120),
        bg = "sunset.png",
        bgScale9 = true,
        async = true,
        viewRect = cc.rect(360, 40, 400, 80),
        direction = cc.ui.UIScrollView.DIRECTION_HORIZONTAL,
        scrollbarImgV = "barH.png"}
        :onTouch(handler(self, self.touchListener8))
        :addTo(self)

    self.lv:setDelegate(handler(self, self.sourceDelegate))

    self.lv:reload()
end

return TestUIListViewScene
