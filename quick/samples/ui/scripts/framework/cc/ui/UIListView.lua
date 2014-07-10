
local UIListView = class("UIListView", function()
	local node = cc.ClippingRegionNode:create()
	node:setAnchorPoint(0.5, 0.5)
	node:setContentSize(display.width, display.height)
	node:setPosition(display.cx, display.cy)
	return node
end)

UIListView.DELEGATE					= "ListView_delegate"
UIListView.TOUCH_DELEGATE			= "ListView_Touch_delegate"
UIListView.DIRECTION_HORIZONTAL		= 1
UIListView.DIRECTION_VERTICAL		= 0

UIListView.CELL_TAG					= "Cell"
UIListView.CELL_SIZE_TAG			= "CellSize"
UIListView.COUNT_TAG				= "Count"
UIListView.CLICKED_TAG				= "Clicked"

function UIListView:ctor(param)
	self.listener = {}
	self.direction = param.direction or UIListView.DIRECTION_VERTICAL
	self.container = cc.Node:create()

	self:addBgColorIf(param.bgColor)
	self:addBgIf(param)
	self:setViewRect(param.rect)
	self.container:setAnchorPoint(0, 0)
	self:addChild(self.container)

	self:addScrollBarIf(param)

	self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function (event)
        return self:onTouch_(event)
    end)
end

function UIListView:addBgColorIf(bgColor)
	if not bgColor then
		return
	end

	display.newColorLayer(bgColor):addTo(self)
end

function UIListView:addBgIf(param)
	if not param.bg then
		return
	end

	display.newScale9Sprite(param.bg)
		:size(param.rect.width, param.rect.height)
		:pos(param.rect.x + param.rect.width/2,
			param.rect.y + param.rect.height/2)
		:addTo(self)
end

function UIListView:addScrollBarIf(param)
	if not param.showScrollBar then
		return
	end

	param.scrollWidth = param.scrollWidth or 5
	if UIListView.DIRECTION_VERTICAL == self.direction then
		cc.ui.UISlider.new(display.TOP_TO_BOTTOM,
				{bar = param.scrollBar, button = param.scrollButton},
				{scale9 = true})
	        :onSliderValueChanged(handler(self, self.scrollBar_))
	        :setSliderValue(0)
	        :addTo(self)
			:setSliderSize(param.scrollWidth, param.rect.height)
			:align(display.CENTER,
				param.rect.x + param.rect.width - param.scrollWidth/2,
				param.rect.y + param.rect.height/2)
	else
		cc.ui.UISlider.new(display.LEFT_TO_RIGHT,
				{bar = param.scrollBar, button = param.scrollButton},
				{scale9 = true})
	        :onSliderValueChanged(handler(self, self.scrollBar_))
	        :setSliderValue(0)
	        :addTo(self)
			:setSliderSize(param.rect.width, param.scrollWidth)
			:align(display.CENTER,
				param.rect.x + param.rect.width/2,
				param.rect.y + param.scrollWidth/2)
	end
end

function UIListView:setViewRect(rect)
	if not rect then
		return
	end

	self.viewRect = rect
	self:setClippingRegion(rect)
	self.container:setPosition(cc.p(rect.x, rect.y))
end

function UIListView:getViewRect()
	return self.viewRect
end

function UIListView:setContentSize()
	printInfo("UIListView - needn't setContentSize")
end

function UIListView:setDirection(direction)
	self.direction = direction
end

function UIListView:registerHandler(listener, delegate)
	self.listener[delegate] = listener
	return self
end

function UIListView:reload()
	local width,height = 0,0 --container width height
	local count = self.listener[UIListView.DELEGATE](self, UIListView.COUNT_TAG)
	if count and 0 == count then
		printInfo("UIListView - count is 0")
		return
	end

	--calcate container width height
	if self.direction == UIListView.DIRECTION_VERTICAL then
		width = self.viewRect.width
		local w,h = 0, 0
		for i = 1, count do
			w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
			w = w or 0
			h = h or 0

			height = height + h
		end
		self:scrollTo(self.viewRect.x + 0, self.viewRect.y + self.viewRect.height - height)
	else
		height = self.viewRect.height
		local w,h = 0, 0
		local item
		for i = 1, count do
			w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
			w = w or 0
			h = h or 0

			width = width + w
		end
		self:scrollTo(self.viewRect.x, self.viewRect.y)
	end
	self.container:setContentSize(width, height)

	local tempWidth, tempHeight = width, height
	if self.direction == UIListView.DIRECTION_VERTICAL then
		local w,h = 0, 0
		local item
		for i = 1, count do
			w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
			w = w or 0
			h = h or 0

			item = self.listener[UIListView.DELEGATE](self, UIListView.CELL_TAG, i)
			item:setPosition(width/2, tempHeight - h/2)
			item:setTag(i)
			self.container:addChild(item)

			tempHeight = tempHeight -h
			HDrawRect({x = 0, y = tempHeight, width = tempWidth, height = h},
				self.container, cc.c4f(0, 1, 0, 1))
		end
	else
		local w,h = 0, 0
		local item
		tempWidth = 0
		for i = 1, count do
			w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
			w = w or 0
			h = h or 0

			item = self.listener[UIListView.DELEGATE](self, UIListView.CELL_TAG, i)
			item:setPosition(tempWidth + w/2, height/2)
			item:setTag(i)
			self.container:addChild(item)

			HDrawRect({x = tempWidth, y = 0, width = w, height = height},
				self.container, cc.c4f(0, 1, 0, 1))
			tempWidth = tempWidth + w
		end
	end

	--先计算出container的position x,y方向上的可变范围,后面拖动时可以直接用
	--拖动时是可以大于或小于这个范围的，只是拖动结束自动回到这个范围中来，回到哪一边的值，最近原则
	self.positionRange_ = {}
	if self.viewRect.width < width then
		self.positionRange_.minX = self.viewRect.width - width
		self.positionRange_.maxX = 0
	else
		self.positionRange_.minX = 0
		self.positionRange_.maxX = 0
	end
	if self.viewRect.height < height then
		self.positionRange_.minY = self.viewRect.height - height
		self.positionRange_.maxY = 0
	else
		self.positionRange_.minY = self.viewRect.height - height
		self.positionRange_.maxY = self.viewRect.height - height
	end
	self.positionRange_.minX = self.positionRange_.minX + self.viewRect.x
	self.positionRange_.maxX = self.positionRange_.maxX + self.viewRect.x
	self.positionRange_.minY = self.positionRange_.minY + self.viewRect.y
	self.positionRange_.maxY = self.positionRange_.maxY + self.viewRect.y

	return self
end

--自已保存一份position数据，就不用通用binding从C代码中取
function UIListView:scrollTo(p, y)
	local x_, y_
	if "table" == type(p) then
		x_ = p.x or 0
		y_ = p.y or 0
	else
		x_ = p
		y_ = y
	end

	self.position_ = cc.p(x_, y_)
	self.container:setPosition(self.position_)
end

function UIListView:scrollAuto()
	print("htl scrollAuto:", self.position_.x, self.positionRange_.minX)
	if self.position_.x < self.positionRange_.minX then
		self:scrollTo(self.positionRange_.minX, self.position_.y)
	elseif self.position_.x > self.positionRange_.maxX then
		self:scrollTo(self.positionRange_.minY, self.position_.y)
	else
		--do nothing
	end

	if self.position_.y < self.positionRange_.minY then
		self:scrollTo(self.position_.x, self.positionRange_.minY)
	elseif self.position_.y > self.positionRange_.maxY then
		self:scrollTo(self.position_.x, self.positionRange_.maxY)
	else
		-- do nothing
	end
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

function UIListView:onTouch_(event)
	if "began" == event.name and not cc.rectContainsPoint(self.viewRect, cc.p(event.x, event.y)) then
		return false
	end

	if "began" == event.name then
		self.touchX_ = event.x
		self.touchY_ = event.y
		self.bDrag_ = false
		return true
	elseif "moved" == event.name then
		self.bDrag_ = true
		local disX = event.x - event.prevX
		local disY = event.y - event.prevY
		local newx, newy = self.position_.x, self.position_.y
		if self.direction == UIListView.DIRECTION_VERTICAL then
			newy = self.position_.y + disY
		else
			newx = self.position_.x + disX
		end
		self:scrollTo(newx, newy)
	elseif "ended" == event.name then
		if self.bDrag_ then
			self:scrollAuto()
		else
			self:notifyItem(
				self.container:convertToNodeSpace(cc.p(event.x, event.y)))
		end
	end
end

function UIListView:scrollBar_(event)
	-- event.value
end


return UIListView
