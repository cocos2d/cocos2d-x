
local UIPageViewItem = import(".UIPageViewItem")

local UIPageView = class("UIPageView", function()
	return display.newNode()
end)

function UIPageView:ctor(params)
	self.items_ = {}
	self.viewRect_ = params.viewRect or cc.rect(0, 0, display.width, display.height)
	self.column_ = params.column or 1
	self.row_ = params.row or 1
	self.columnSpace_ = params.columnSpace or 0
	self.rowSpace_ = params.rowSpace or 0
	self.padding_ = params.padding or {left = 0, right = 0, top = 0, bottom = 0}

	-- self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(...)
	-- 		self:update_(...)
	-- 	end)
	self:setTouchEnabled(true)
	self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function (event)
        	return self:onTouch_(event)
    	end)
end

function UIPageView:newItem()
	local item = UIPageViewItem.new()
	item:setContentSize(self.viewRect_.width/self.column_, self.viewRect_.height/self.row_)

	return item
end

function UIPageView:addItem(item)
	table.insert(self.items_, item)

	return self
end

function UIPageView:onTouch(listener)
	self.touchListener = listener

	return self
end

function UIPageView:reload()
	local page
	self.pages_ = {}
	for i = 1, self:getMaxPage() do
		page = self:createPage_(i)
		page:setVisible(false)
		table.insert(self.pages_, page)
		self:addChild(page)
	end

	self.curPageIdx_ = 1
	self.pages_[1]:setVisible(true)
	self.pages_[1]:setPosition(
		self.viewRect_.x, self.viewRect_.y)

	return self
end

-- private

function UIPageView:createPage_(pageNo)
	local page = display.newNode()
	local item
	local beginIdx = self.row_*self.column_*(pageNo-1) + 1
	local itemW, itemH

	itemW = (self.viewRect_.width - self.padding_.left - self.padding_.right
				- self.columnSpace_*(self.column_ - 1)) / self.column_
	itemH = (self.viewRect_.height - self.padding_.top - self.padding_.bottom
				- self.rowSpace_*(self.row_ - 1)) / self.row_
	local bBreak = false
	for row=1,self.row_ do
		for column=1,self.column_ do
			item = self.items_[beginIdx]
			beginIdx = beginIdx + 1
			if not item then
				bBreak = true
				break
			end
			page:addChild(item)

			item:setAnchorPoint(cc.p(0.5, 0.5))
			item:setPosition(
				self.padding_.left + (column - 1)*self.columnSpace_ + column*itemW - itemW/2,
				self.viewRect_.height - self.padding_.top - (row - 1)*self.rowSpace_ - row*itemH + itemH/2)
				-- self.padding_.bottom + (row - 1)*self.rowSpace_ + row*itemH - itemH/2)
		end
		if bBreak then
			break
		end
	end

	return page
end

function UIPageView:getMaxPage()
	return math.ceil(table.nums(self.items_)/(self.column_*self.row_))
end

function UIPageView:onTouch_(event)
	print("UIPageView - onTouch_:" .. event.x .. " " .. event.y)
	if "began" == event.name
		and not cc.rectContainsPoint(self.viewRect_, cc.p(event.x, event.y)) then
		printInfo("UIPageView - touch didn't in viewRect")
		return false
	end

	if "began" == event.name then
		self:resetLRPage()
		self.bDrag_ = false
	elseif "moved" == event.name then
		self.bDrag_ = true
		self.speed = event.x - event.prevX
		self:scroll(self.speed)
	elseif "ended" == event.name then
		if self.bDrag_ then
			self:scrollAuto()
		else
			self:onClick_(event)
		end
	end

	return true
end

function UIPageView:resetLRPage()
	local pageIdx = self.curPageIdx_
	local page

	self:stopAllTransition()
	-- left page
	page = self.pages_[self.curPageIdx_ - 1]
	if page then
		print("UIPageView - set left page visible")
		page:setVisible(true)
		page:setPosition(-self.viewRect_.width, self.viewRect_.y)
	end

	-- right page
	page = self.pages_[self.curPageIdx_ + 1]
	if page then
		print("UIPageView - set right page visible")
		page:setVisible(true)
		page:setPosition(display.width, self.viewRect_.y)
	end
end

function UIPageView:stopAllTransition()
	for i,v in ipairs(self.pages_) do
		transition.stopTarget(v)
	end
end

function UIPageView:disablePage()
	local pageIdx = self.curPageIdx_
	local page

	for i,v in ipairs(self.pages_) do
		if i ~= self.curPageIdx_ then
			v:setVisible(false)
		end
	end
end

function UIPageView:scroll(dis)
	local page
	local posX, posY
	local idx = self.curPageIdx_ - 2

	-- left, current, right page
	for i=1,3 do
		page = self.pages_[idx + i]
		if page then
			posX, posY = page:getPosition()
			posX = posX + dis
			page:setPosition(posX, posY)
			-- print("UIPageView - setPos x:" .. posX .. " " .. i)
		end
	end
end

function UIPageView:scrollAuto()
	local page = self.pages_[self.curPageIdx_]
	local pageL = self.pages_[self.curPageIdx_ - 1]
	local pageR = self.pages_[self.curPageIdx_ + 1]
	local bChange = false
	local posX, posY = page:getPosition()
	local dis = posX - self.viewRect_.x

	if (dis > self.viewRect_.width/2 or self.speed > 10)
		and self.curPageIdx_ > 1 then
		bChange = true
	elseif (-dis > self.viewRect_.width/2 or -self.speed > 10)
		and self.curPageIdx_ < self:getMaxPage() then
		bChange = true
	end

	if dis > 0 then
		if bChange then
			transition.moveTo(page,
				{x = display.width, y = posY, time = 0.3,
				onComplete = function()
					self.curPageIdx_ = self.curPageIdx_ - 1
					self:disablePage()
				end})
			transition.moveTo(self.pages_[self.curPageIdx_ - 1],
				{x = self.viewRect_.x, y = posY, time = 0.3})
		else
			transition.moveTo(page,
				{x = self.viewRect_.x, y = posY, time = 0.3,
				onComplete = function()
					self:disablePage()
				end})
			if self.pages_[self.curPageIdx_ - 1] then
				transition.moveTo(self.pages_[self.curPageIdx_ - 1],
					{x = -self.viewRect_.width, y = posY, time = 0.3})
			end
		end
	else
		if bChange then
			transition.moveTo(page,
				{x = -self.viewRect_.width, y = posY, time = 0.3,
				onComplete = function()
					self.curPageIdx_ = self.curPageIdx_ + 1
					self:disablePage()
				end})
			transition.moveTo(self.pages_[self.curPageIdx_ + 1],
				{x = self.viewRect_.x, y = posY, time = 0.3})
		else
			transition.moveTo(page,
				{x = self.viewRect_.x, y = posY, time = 0.3,
				onComplete = function()
					self:disablePage()
				end})
			if self.pages_[self.curPageIdx_ + 1] then
				transition.moveTo(self.pages_[self.curPageIdx_ + 1],
					{x = display.width, y = posY, time = 0.3})
			end
		end
	end
end

function UIPageView:onClick_(event)
	local itemW, itemH

	itemW = (self.viewRect_.width - self.padding_.left - self.padding_.right
				- self.columnSpace_*(self.column_ - 1)) / self.column_
	itemH = (self.viewRect_.height - self.padding_.top - self.padding_.bottom
				- self.rowSpace_*(self.row_ - 1)) / self.row_

	local x, y = event.x, event.y
	x = x - self.viewRect_.x
	y = y - self.viewRect_.y
	local itemRect = {width = itemW, height = itemH}

	local clickIdx
	for row = 1, self.row_ do
		itemRect.y = self.viewRect_.height - self.padding_.top - row*itemH - (row - 1)*self.rowSpace_
		for column = 1, self.column_ do
			itemRect.x = self.padding_.left + (column - 1)*(itemW + self.columnSpace_)

			if cc.rectContainsPoint(itemRect, cc.p(x,y)) then
				clickIdx = (row - 1)*self.column_ + column
				break
			end
		end
		if clickIdx then
			break
		end
	end

	self.touchListener{pageView = self, name = "clicked",
		item = self.items_[clickIdx],
		itemIdx = clickIdx,
		pageIdx = self.curPageIdx_}
end

return UIPageView
