
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

function UIListView:ctor(param)
	self.listener = {}
	self.direction = param.direction or UIListView.DIRECTION_VERTICAL
	self.container = cc.Node:create()

	self:setViewRect(param.rect)
	self.container:setAnchorPoint(0, 0)
	self:addChild(self.container)

	self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function (event)
        return self:onTouch_(event)
    end)
end

function UIListView:setViewRect(rect)
	if not rect then
		return
	end

	self.viewRect = rect
	self:setClippingRegion(rect)
	print("htl UIListView setPos1:", rect.x, rect.y)
	self.container:setPosition(cc.p(rect.x, rect.y))
	print("htl UIListView setPos:", rect.x, rect.y)
	--self:setPosition(rect.x + rect.width/2, rect.y + rect.height/2)
end

function UIListView:getViewRect()
	return self.viewRect
end

function UIListView:setDirection(direction)
	self.direction = direction
end

function UIListView:registerHandler(listener, delegate)
	print("htl registerHandler")

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
		self:scrollTo(0, self.viewRect.height - height)
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
		self:scrollTo(0, 0)
	end
	self.container:setContentSize(width, height)
	print("htl container width:" .. width .. " height:" .. height)

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

	print("htl scrollTo:", x, y)

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

function UIListView:onTouch_(event)
	if "began" == event.name and not cc.rectContainsPoint(self.viewRect, cc.p(event.x, event.y)) then
		return false
	end

	-- dump(event, "UIListView event:")
	if "began" == event.name then
		self.touchX_ = event.x
		self.touchY_ = event.y
		return true
	elseif "moved" == event.name then
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
		self:scrollAuto()
	end
end


return UIListView
