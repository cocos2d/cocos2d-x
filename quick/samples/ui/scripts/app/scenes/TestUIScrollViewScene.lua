
local TestUIScrollViewScene = class("TestUIScrollViewScene", function()
    return display.newScene("TestUIScrollViewScene")
end)

function TestUIScrollViewScene:ctor()
	app:createGrid(self)

    self:createScrollView1()
    self:createScrollView2()

    app:createTitle(self, "Test UIScrollView")
    app:createNextButton(self)
end

function TestUIScrollViewScene:createScrollView1()
	local sp1 = display.newScale9Sprite("sunset.png")
	sp1:setContentSize(380, 285)
	sp1:pos(200, 440)
	sp1:addTo(self)

    local sp2 = display.newScale9Sprite("sunset.png")
    sp2:setContentSize(300, 200)
    sp2:pos(200, 180)

    local bound = sp2:getBoundingBox()
    bound.width = 150
    bound.height = 100

    cc.ui.UIScrollView.new({viewRect = bound})
        :addScrollNode(sp2)
        :setDirection(cc.ui.UIScrollView.DIRECTION_HORIZONTAL)
        :onScroll(handler(self, self.scrollListener))
        :addTo(self)

	-- sp2:setDirection(0) --支持横向，纵向滑动，默认
	-- sp2:setDirection(1) --只支持纵向滑动
    -- sp2:setDirection(2) --只支持横向滑动

    -- sp2:regScrollListener(handler(self, self.scrollListener))
end

function TestUIScrollViewScene:scrollListener(event)
	-- print("TestUIScrollViewScene - scrollListener:" .. event.name)
end

function TestUIScrollViewScene:createScrollView2()

end

return TestUIScrollViewScene
