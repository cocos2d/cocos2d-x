
local UIScrollView = class("UIScrollView", function()
	return cc.ClippingRegionNode:create()
end)

UIScrollView.DIRECTION_BOTH			= 0
UIScrollView.DIRECTION_VERTICAL		= 1
UIScrollView.DIRECTION_HORIZONTAL	= 2

function UIScrollView:ctor(params)
	self.direction = UIScrollView.DIRECTION_BOTH
	self.layoutPadding = {left = 0, right = 0, top = 0, bottom = 0}
	self.speed = {x = 0, y = 0}

	if not params then
		return
	end

	if params.viewRect then
		self:setViewRect(params.viewRect)
	end
	if not params.direction then
		self:setDirection(params.direction)
	end
	if params.scrollbarImgH then
		self.sbH = display.newScale9Sprite(params.scrollbarImgH, 100):addTo(self)
	end
	if params.scrollbarImgV then
		self.sbV = display.newScale9Sprite(params.scrollbarImgV, 100):addTo(self)
	end

	self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(...)
			self:update_(...)
		end)
end

function UIScrollView:setViewRect(rect)
	self:setClippingRegion(rect)
	self.viewRect_ = rect

	return self
end

function UIScrollView:setLayoutPadding(top, right, bottom, left)
	if not self.layoutPadding then
		self.layoutPadding = {}
	end
	self.layoutPadding.top = top
	self.layoutPadding.right = right
	self.layoutPadding.bottom = bottom
	self.layoutPadding.left = left
end

function UIScrollView:setActualRect(rect)
	self.actualRect_ = rect
end

function UIScrollView:setDirection(dir)
	self.direction = dir

	return self
end

function UIScrollView:addScrollNode(node)
	self:addChild(node)
	self.scrollNode = node

	if not self.viewRect_ then
		self.viewRect_ = self.scrollNode:getCascadeBoundingBox()
		self:setViewRect(self.viewRect_)
	end
	node:setTouchSwallowEnabled(true)
	node:setTouchEnabled(true)
	node:addNodeEventListener(cc.NODE_TOUCH_EVENT, function (event)
        return self:onTouch_(event)
    end)

    return self
end

function UIScrollView:onScroll(listener)
	self.scrollListener_ = listener

    return self
end

-- private

function UIScrollView:calcLayoutPadding()
	local boundBox = self.scrollNode:getCascadeBoundingBox()

	self.layoutPadding.left = boundBox.x - self.actualRect_.x
	self.layoutPadding.right =
		self.actualRect_.x + self.actualRect_.width - boundBox.x - boundBox.width
	self.layoutPadding.top = boundBox.y - self.actualRect_.y
	self.layoutPadding.bottom =
		self.actualRect_.y + self.actualRect_.height - boundBox.y - boundBox.height
end

function UIScrollView:update_(dt)
	self:drawScrollBar()
end

function UIScrollView:onTouch_(event)
	-- print("UIScrollView - onTouch_:" .. event.name)

	if "began" == event.name and not cc.rectContainsPoint(self.viewRect_, cc.p(event.x, event.y)) then
		printInfo("#DEBUG touch didn't in viewRect")
		return false
	end

	if "began" == event.name then
		-- self:calcLayoutPadding()
		self.prevX_ = event.x
		self.prevY_ = event.y
		self.bDrag_ = false
		local x,y = self.scrollNode:getPosition()
		self.position_ = {x = x, y = y}

		transition.stopTarget(self.scrollNode)
		self:callListener_{name = "began", x = event.x, y = event.y}

		self:enableScrollBar()

		return true
	elseif "moved" == event.name then
		self.bDrag_ = true
		self.speed.x = event.x - event.prevX
		self.speed.y = event.y - event.prevY

		if self.direction == UIScrollView.DIRECTION_VERTICAL then
			self.speed.x = 0
		elseif self.direction == UIScrollView.DIRECTION_HORIZONTAL then
			self.speed.y = 0
		else
			-- do nothing
		end

		self:scrollBy(self.speed.x, self.speed.y)
		self:callListener_{name = "moved", x = event.x, y = event.y}
	elseif "ended" == event.name then
		if self.bDrag_ then
			self.bDrag_ = false
			self:scrollAuto()

			self:callListener_{name = "ended", x = event.x, y = event.y}

			self:disableScrollBar()
		else
			self:callListener_{name = "clicked", x = event.x, y = event.y}
		end
	end
end

function UIScrollView:scrollTo(p, y)
	local x_, y_
	if "table" == type(p) then
		x_ = p.x or 0
		y_ = p.y or 0
	else
		x_ = p
		y_ = y
	end

	self.position_ = cc.p(x_, y_)
	self.scrollNode:setPosition(self.position_)
end

function UIScrollView:scrollBy(x, y)
	self.position_.x = self.position_.x + x
	self.position_.y = self.position_.y + y
	self.scrollNode:setPosition(self.position_)

	if self.actualRect_ then
		self.actualRect_.x = self.actualRect_.x + x
		self.actualRect_.y = self.actualRect_.y + y
	end
end

function UIScrollView:calcScrollRange()
	--先计算出container的position x,y方向上的可变范围,后面拖动时可以直接用
	--拖动时是可以大于或小于这个范围的，只是拖动结束自动回到这个范围中来，回到哪一边的值，最近原则

	self.rect = self.scrollNode:getCascadeBoundingBox()
	-- self.rect = self.scrollNode:getBoundingBox()
	dump(self.rect, "UIScrollView scrollNode BoundingBox:")
	-- HDrawRect(self.rect, self, cc.c4f(0, 1, 0, 1))
	print("UIScrollView - calcScrollRange child count:" .. self.scrollNode:getChildrenCount())
	-- dump(self.viewRect_, "viewRect:")
	if not self.positionRange_ then
		self.positionRange_ = {}
	end
	if self.viewRect_.width < self.rect.width then
		self.positionRange_.minX = self.viewRect_.width - self.rect.width
		self.positionRange_.maxX = 0
	else
		self.positionRange_.minX = 0
		self.positionRange_.maxX = 0
	end
	if self.viewRect_.height < self.rect.height then
		self.positionRange_.minY = self.viewRect_.height - self.rect.height
		self.positionRange_.maxY = 0
	else
		self.positionRange_.minY = self.viewRect_.height - self.rect.height
		self.positionRange_.maxY = self.viewRect_.height - self.rect.height
	end
	self.positionRange_.minX = self.positionRange_.minX + self.viewRect_.x
	self.positionRange_.maxX = self.positionRange_.maxX + self.viewRect_.x
	self.positionRange_.minY = self.positionRange_.minY + self.viewRect_.y
	self.positionRange_.maxY = self.positionRange_.maxY + self.viewRect_.y

	-- anchorpoint
	local anchor = self.scrollNode:getAnchorPoint()
	local size = self.scrollNode:getCascadeBoundingBox()
	self.positionRange_.minX = self.positionRange_.minX + anchor.x * size.width
	self.positionRange_.maxX = self.positionRange_.maxX + anchor.x * size.width
	self.positionRange_.minY = self.positionRange_.minY + anchor.y * size.height
	self.positionRange_.maxY = self.positionRange_.maxY + anchor.y * size.height

	dump(anchor, "anchor:")
	-- dump(self.viewRect_, "viewRect_:")
	-- dump(self.positionRange_, "positionRange:")
end

function UIScrollView:scrollAuto1()
	self:calcScrollRange()

	local newX, newY = self.position_.x, self.position_.y
	if self.position_.x < self.positionRange_.minX then
		newX = self.positionRange_.minX
	elseif self.position_.x > self.positionRange_.maxX then
		newX = self.positionRange_.maxX
	else
		--do nothing
	end

	if self.position_.y < self.positionRange_.minY then
		newY = self.positionRange_.minY
	elseif self.position_.y > self.positionRange_.maxY then
		newY = self.positionRange_.maxY
	else
		-- do nothing
	end
	print("UIScrollView - scrollAuto: x:" .. newX .. " y:" .. newY)
	transition.moveTo(self.scrollNode,
		{x = newX, y = newY, time = 0.3,
		easing = "backout",
		onComplete = function()
			self:callListener_{name = "scrollEnd"}
		end})
end

function UIScrollView:scrollAuto()
	if self:twiningScroll() then
		return
	end
	self:elasticScroll()
end

function UIScrollView:twiningScroll()
	if self:isSideShow() then
		printInfo("UIScrollView - side is show, so elastic scroll")
		return false
	end

	if math.abs(self.speed.x) < 10 and math.abs(self.speed.y) < 10 then
		printInfo("#DEBUG, UIScrollView - isn't twinking scroll:"
			.. self.speed.x .. " " .. self.speed.y)
		return false
	end

	transition.moveBy(self.scrollNode,
		{x = self.speed.x*5, y = self.speed.y*5, time = 0.3,
		easing = "sineOut",
		onComplete = function()
			self:elasticScroll()
		end})
end

function UIScrollView:elasticScroll()
	local cascadeBound = self:getScrollNodeRect()
	local disX, disY = 0, 0

	-- dump(cascadeBound, "UIScrollView - cascBoundingBox:")
	-- dump(self.scrollNode:getBoundingBox(), "UIScrollView - BoundingBox:")

	if cascadeBound.x > self.viewRect_.x then
		disX = self.viewRect_.x - cascadeBound.x
	elseif cascadeBound.x + cascadeBound.width < self.viewRect_.x + self.viewRect_.width then
		disX = self.viewRect_.x + self.viewRect_.width - cascadeBound.x - cascadeBound.width
	end
	if cascadeBound.y > self.viewRect_.y then
		disY = self.viewRect_.y - cascadeBound.y
	elseif cascadeBound.y + cascadeBound.height < self.viewRect_.y + self.viewRect_.height then
		disY = self.viewRect_.y + self.viewRect_.height - cascadeBound.y - cascadeBound.height
	end

	-- dump(self.viewRect_, "viewRect:")
	-- dump(cascadeBound, "cascadeRect:")
	-- print("UIScrollView disY:" .. disY)
	if 0 == disX and 0 == disY then
		return
	end

	print("htl disY:" .. disY)
	transition.moveBy(self.scrollNode,
		{x = disX, y = disY, time = 0.3,
		easing = "backout",
		onComplete = function()
			self:callListener_{name = "scrollEnd"}
		end})
end

function UIScrollView:getScrollNodeRect()
	local bound = self.scrollNode:getCascadeBoundingBox()
	-- bound.x = bound.x - self.layoutPadding.left
	-- bound.y = bound.y - self.layoutPadding.bottom
	-- bound.width = bound.width + self.layoutPadding.left + self.layoutPadding.right
	-- bound.height = bound.height + self.layoutPadding.bottom + self.layoutPadding.top

	return bound
end

-- 是否显示到边缘
function UIScrollView:isSideShow()
	local bound = self.scrollNode:getCascadeBoundingBox()
	if bound.x > self.viewRect_.x
		or bound.y > self.viewRect_.y
		or bound.x + bound.width < self.viewRect_.x + self.viewRect_.width
		or bound.y + bound.height < self.viewRect_.y + self.viewRect_.height then
		return true
	end

	return false
end

function UIScrollView:callListener_(event)
	if not self.scrollListener_ then
		return
	end

	self.scrollListener_(event)
end

function UIScrollView:enableScrollBar()
	print("UIScrollView - enableScrollBar")

	local bound = self.scrollNode:getCascadeBoundingBox()
	if self.sbV then
		self.sbV:setVisible(false)
		transition.stopTarget(self.sbV)
		self.sbV:setOpacity(128)
		local size = self.sbV:getContentSize()
		if self.viewRect_.height < bound.height then
			-- dump(self.viewRect_, "viewRect_:")
			-- dump(bound, "bound:")
			local barH = self.viewRect_.height*self.viewRect_.height/bound.height
			if barH < size.width then
				-- 保证bar不会太小
				barH = size.width
			end
			self.sbV:setContentSize(size.width, barH)
			self.sbV:setPosition(
				self.viewRect_.x + self.viewRect_.width - size.width/2, self.viewRect_.y + barH/2)
		end
	end
	if self.sbH then
		self.sbH:setVisible(false)
		transition.stopTarget(self.sbH)
		self.sbH:setOpacity(128)
		local size = self.sbH:getContentSize()
		if self.viewRect_.width < bound.width then
			local barW = self.viewRect_.width*self.viewRect_.width/bound.width
			if barW < size.height then
				barw = size.height
			end
			self.sbH:setContentSize(barW, size.height)
			self.sbH:setPosition(self.viewRect_.x + barW/2,
				self.viewRect_.y + size.height/2)
		end
	end
end

function UIScrollView:disableScrollBar()
	print("UIScrollView - disableScrollBar")
	if self.sbV then
		transition.fadeOut(self.sbV,
			{time = 0.3,
			onComplete = function()
				self.sbV:setOpacity(128)
				self.sbV:setVisible(false)
			end})
	end
	if self.sbH then
		transition.fadeOut(self.sbH,
			{time = 1.5,
			onComplete = function()
				self.sbH:setOpacity(128)
				self.sbH:setVisible(false)
			end})
	end
end

function UIScrollView:drawScrollBar()
	if not self.bDrag_ then
		return
	end
	if not self.sbV and not self.sbH then
		return
	end

	-- print("UIScrollView - drawScrollBar")
	local bound = self.scrollNode:getCascadeBoundingBox()
	if self.sbV then
		self.sbV:setVisible(true)
		local size = self.sbV:getContentSize()

		local posY = (self.viewRect_.y - bound.y)*(self.viewRect_.height - size.height)/(bound.height - self.viewRect_.height)
			+ self.viewRect_.y + size.height/2
		local x, y = self.sbV:getPosition()
		self.sbV:setPosition(x, posY)
		-- print("htl x, y:" .. x .. "," .. posY)
	end
	if self.sbH then
		self.sbH:setVisible(true)
		local size = self.sbH:getContentSize()

		local posX = (self.viewRect_.x - bound.x)*(self.viewRect_.width - size.width)/(bound.width - self.viewRect_.width)
			+ self.viewRect_.x + size.width/2
		local x, y = self.sbH:getPosition()
		self.sbH:setPosition(posX, y)
		print("UIScrollView - x,y " .. x .. "," .. y)
	end
end

function UIScrollView:addScrollBarIf()

	if not self.sb then
		self.sb = cc.DrawNode:create():addTo(self)
	end

drawNode = cc.DrawNode:create()
    drawNode:drawSegment(points[1], points[2], radius, borderColor)
end

return UIScrollView
