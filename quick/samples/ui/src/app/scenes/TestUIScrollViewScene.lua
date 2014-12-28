
local TestUIScrollViewScene = class("TestUIScrollViewScene", function()
    return display.newScene("TestUIScrollViewScene")
end)

function TestUIScrollViewScene:ctor()
	app:createGrid(self)

    self:createScrollView1()
    self:createScrollView2()

    app:createTitle(self, "Test UIScrollView & DraggableComponent")
    app:createNextButton(self)
end

function TestUIScrollViewScene:createScrollView1()
    cc.ui.UILabel.new({text = "原始图", size = 24, color = display.COLOR_BLACK})
        :align(display.CENTER, 240, 480)
        :addTo(self)
	local sp1 = display.newScale9Sprite("sunset.png")
	sp1:setContentSize(380, 285)
	sp1:pos(240, 300)
	sp1:addTo(self)

    cc.ui.UILabel.new({text = "可滚动的图", size = 24, color = display.COLOR_BLACK})
        :align(display.CENTER, 720, 580)
        :addTo(self)
    local sp2 = display.newScale9Sprite("sunset.png")
    sp2:setContentSize(300, 200)
    sp2:pos(720, 460)

    local emptyNode = cc.Node:create()
    emptyNode:addChild(sp2)
    sp2.testPeer = "origin"

    local bound = sp2:getBoundingBox()
    bound.width = 300
    bound.height = 200

    local sv = cc.ui.UIScrollView.new({viewRect = bound})
        :addScrollNode(emptyNode)
        -- :setDirection(cc.ui.UIScrollView.DIRECTION_HORIZONTAL)
        :onScroll(handler(self, self.scrollListener))
        :addTo(self)

	-- sp2:setDirection(0) --支持横向，纵向滑动，默认
	-- sp2:setDirection(1) --只支持纵向滑动
    -- sp2:setDirection(2) --只支持横向滑动

    -- sp2:regScrollListener(handler(self, self.scrollListener))

    cc.ui.UILabel.new({text = "可拖动的图", size = 24, color = display.COLOR_BLACK})
        :align(display.CENTER, 720, 300)
        :addTo(self)
    local sp3 = display.newScale9Sprite("sunset.png")
    sp3:setContentSize(300, 200)
    sp3:pos(720, 180)
    sp3:addTo(self)

    cc(sp3):addComponent("components.ui.DraggableProtocol")
        :exportMethods()
        :setDraggableEnable(true)

    -- local cloneSV = sv:clone()
    -- if cloneSV then
    --     cloneSV:addTo(self)

    --     local cloneSN = cloneSV:getScrollNode()
    --     local cloneSP = cloneSN:getChildren()[1]
    --     print("origin peer:" .. sp2.testPeer)
    --     print("clone peer:" .. cloneSP.testPeer)
    --     cloneSP.testPeer = "clone"
    --     print("origin peer:" .. sp2.testPeer)
    --     print("clone peer:" .. cloneSP.testPeer)
    -- end

end

function TestUIScrollViewScene:scrollListener(event)
	-- print("TestUIScrollViewScene - scrollListener:" .. event.name)
end

function TestUIScrollViewScene:createScrollView2()

end

return TestUIScrollViewScene
