
local UIListView = class("UIListView", function()
	local node = cc.Node:create()
	node:setAnchorPoint(0.5, 0.5)
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
	dump(param, "htl param:")
	self:setViewRect(param.rect)
	self.container = cc.Node:create()
	print("htl ctor1")
	self.container:setAnchorPoint(0, 0)
	print("htl ctor2")
	self:addChild(self.container)
end

function UIListView:setViewRect(rect)
	if not rect then
		return
	end

	self.viewRect = rect
	self:setContentSize(rect.width, rect.height)
	self:setPosition(rect.x + rect.width/2, rect.y + rect.height/2)
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
		self.container:setPosition(0, self.viewRect.height - height)
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
		self.container:setPosition(0, 0)
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
		self.container:setPosition(0, 0)
	end

	

	return self
end


return UIListView
