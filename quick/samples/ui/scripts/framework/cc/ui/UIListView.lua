
local UIScrollView = import(".UIScrollView")
local UIListView = class("UIListView", UIScrollView)

local UIListViewItem = import(".UIListViewItem")


UIListView.DELEGATE					= "ListView_delegate"
UIListView.TOUCH_DELEGATE			= "ListView_Touch_delegate"

UIListView.CELL_TAG					= "Cell"
UIListView.CELL_SIZE_TAG			= "CellSize"
UIListView.COUNT_TAG				= "Count"
UIListView.CLICKED_TAG				= "Clicked"

UIListView.BG_ZORDER 				= -1
UIListView.CONTENT_ZORDER			= 10

function UIListView:ctor(params)
	self.items_ = {}
	self.direction = params.direction or UIScrollView.DIRECTION_VERTICAL
	self.container = cc.Node:create()

	self:setDirection(params.direction)
	self:setViewRect(params.viewRect)
	self:addScrollNode(self.container)
	self:onScroll(handler(self, self.scrollListener))

	self:addBgColorIf(params.bgColor)
	self:addBgIf(params)
end

function UIListView:addBgColorIf(bgColor)
	if not bgColor then
		return
	end

	display.newColorLayer(bgColor):addTo(self, UIListView.BG_ZORDER)
end

function UIListView:addBgIf(params)
	if not params.bg then
		return
	end

	display.newScale9Sprite(params.bg)
		:size(params.viewRect_.width, params.viewRect_.height)
		:pos(params.viewRect_.x + params.viewRect_.width/2,
			params.viewRect_.y + params.viewRect_.height/2)
		:addTo(self, UIListView.BG_ZORDER)
end

function UIListView:onTouch(listener)
	self.touchListener_ = listener

	return self
end

function UIListView:newItem(item)
	item = UIListViewItem.new(item)

	return item
end

function UIListView:scrollListener(event)
	-- print("TestUIScrollViewScene - scrollListener:" .. event.name)
end

function UIListView:addItem(listItem, pos)
	if pos then
		table.insert(self.items_, pos, listItem)
	else
		table.insert(self.items_, listItem)
	end
	self.container:addChild(listItem)

	return self
end

function UIListView:removeItem(listItem)
	self.container:removeChild(listItem)

	local pos = self:getItemPos(listItem)
	if pos then
		table.remove(self.items_, pos)
	end

	return self
end

function UIListView:modifyItem(listItem)
	self.container:removeChild(listItem)

	local pos = self:getItemPos(listItem)
	if pos then
		table.remove(self.items_, pos)
	end
	self:addItem(listItem, pos)

	return self
end

function UIListView:getItemPos(listItem)
	for i,v in ipairs(self.items_) do
		if v == listItem then
			return i
		end
	end
end

function UIListView:layout_()
	local width, height = 0, 0
	local itemW, itemH = 0, 0

	-- calcate whole width height
	if UIScrollView.DIRECTION_VERTICAL == self.direction then
		width = self.viewRect_.width

		for i,v in ipairs(self.items_) do
			itemW, itemH = v:getItemSize()
			itemW = itemW or 0
			itemH = itemH or 0

			height = height + itemH
		end
	else
		height = self.viewRect_.height

		for i,v in ipairs(self.items_) do
			itemW, itemH = v:getItemSize()
			itemW = itemW or 0
			itemH = itemH or 0

			width = width + itemW
		end
	end
	self:setActualRect({x = self.viewRect_.x,
		y = self.viewRect_.y,
		width = width,
		height = height})
	dump(self.container:getCascadeBoundingBox(), "UIListView container bound:")

	print("UIListView - w,h", width, height)

	local tempWidth, tempHeight = width, height
	if UIScrollView.DIRECTION_VERTICAL == self.direction then
		itemW, itemH = 0, 0

		local content
		for i,v in ipairs(self.items_) do
			itemW, itemH = v:getItemSize()
			itemW = itemW or 0
			itemH = itemH or 0

			tempHeight = tempHeight - itemH
			content = v:getContent()
			content:setAnchorPoint(0.5, 0.5)
			content:setPosition(self.viewRect_.x + tempWidth/2,
				self.viewRect_.y + tempHeight + itemH/2)
			-- print("UIListView - layout_:" .. tempWidth/2 .. " " .. tempHeight + itemH/2)
			-- HDrawRect(content:getBoundingBox(), v, cc.c4f(0, 1, 0, 1))
			-- dump(content:getCascadeBoundingBox(), "item Rect:")
		end
	else
		itemW, itemH = 0, 0
		tempWidth = 0

		for i,v in ipairs(self.items_) do
			itemW, itemH = v:getItemSize()
			itemW = itemW or 0
			itemH = itemH or 0

			v:setAnchorPoint(0.5, 0.5)
			v:setPosition(self.viewRect_.x + tempWidth + itemW/2,
				self.viewRect_.y + tempHeight/2)
			tempWidth = tempWidth + itemW
		end
	end

	dump(self.container:getCascadeBoundingBox(), "UIListView container bound:")
	-- local bound = self.container:getCascadeBoundingBox()
	-- dump(bound, "bound:")
	-- HDrawRect(bound, self, cc.c4f(0, 1, 0, 1))

end

function UIListView:reload()
	self:layout_()

	return self
end

function UIListView:notifyItem(point)
	local count = self.listener[UIListView.DELEGATE](self, UIListView.COUNT_TAG)
	local temp = (self.direction == UIListView.DIRECTION_VERTICAL and self.container:getContentSize().height) or 0
	local w,h = 0, 0
	local tag = 0

	for i = 1, count do
		w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
		if self.direction == UIListView.DIRECTION_VERTICAL then
			temp = temp - h
			if point.y > temp then
				point.y = point.y - temp
				tag = i
				break
			end
		else
			temp = temp + w
			if point.x < temp then
				point.x = point.x + w - temp
				tag = i
				break
			end
		end
	end

	if 0 == tag then
		printInfo("UIListView - didn't found item")
		return
	end

	local item = self.container:getChildByTag(tag)
	self.listener[UIListView.DELEGATE](self, UIListView.CLICKED_TAG, tag, point)
end

return UIListView
