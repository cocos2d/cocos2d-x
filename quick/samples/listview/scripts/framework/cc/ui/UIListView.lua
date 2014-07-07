
local UIListView = class("UIListView", function()
	return cc.Node:create()
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
	self.viewRect = param.rect
	self.direction = param.direction or UIListView.DIRECTION_VERTICAL
	dump(param, "htl param:")
	self:setContentSize(param.rect.width, param.rect.height)
	self.container = cc.Node:create()
	print("htl ctor1")
	self.container:setAnchorPoint(0, 0)
	print("htl ctor2")
	self:addChild(self.container)
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
	local width,height = 0,0
	local count = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG)
	if count and 0 == count then
		printInfo("UIListView - count is 0")
		return
	end

	if self.direction == UIListView.DIRECTION_VERTICAL then
		width = self.viewSize.width
		local w,h = 0, 0
		local item
		for i = 1, count do
			w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
			w = w or 0
			h = h or 0

			item = self.listener[UIListView.DELEGATE](self, UIListView.CELL_TAG)
			item:setPosition(w/2, height + h/2)
			self.container:addChild(item)

			height = height + h
		end
		self.container:setPosition(0, self.viewSize.height - height)
	else
		height = self.viewSize.height
		local w,h = 0, 0
		local item
		for i = 1, count do
			w,h = self.listener[UIListView.DELEGATE](self, UIListView.CELL_SIZE_TAG, i)
			w = w or 0
			h = h or 0

			item = self.listener[UIListView.DELEGATE](self, UIListView.CELL_TAG)
			item:setPosition(width + w/2, height/2)
			self.container:addChild(item)

			width = width + w
		end
		self.container:setPosition(0, 0)
	end

	self.container:setContentSize(width, height)
end


return UIListView
