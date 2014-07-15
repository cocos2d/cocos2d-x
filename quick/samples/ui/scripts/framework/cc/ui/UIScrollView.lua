
local UIScrollView = class("UIScrollView", function()
	return cc.ClippingRegionNode:create()
end)

UIScrollView.DIRECTION_BOTH			= 0
UIScrollView.DIRECTION_VERTICAL		= 1
UIScrollView.DIRECTION_HORIZONTAL	= 2

function UIScrollView:ctor(params)
	self.direction = UIScrollView.DIRECTION_BOTH
	if not params then
		return
	end

	if params.viewRect then
		self:setViewRect(params.viewRect)
	end
	if not params.direction then
		self:setDirection(params.direction)
	end
end

function UIScrollView:setViewRect(rect)
	self:setClippingRegion(rect)
	self.viewRect_ = rect

	return self
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

function UIScrollView:onTouch_(event)
	-- print("UIScrollView - onTouch_:" .. event.name)

	if "began" == event.name and not cc.rectContainsPoint(self.viewRect_, cc.p(event.x, event.y)) then
		printInfo("#DEBUG touch didn't in viewRect")
		return false
	end

	if "began" == event.name then
		self.prevX_ = event.x
		self.prevY_ = event.y
		self.bDrag_ = false
		local x,y = self.scrollNode:getPosition()
		self.position_ = {x = x, y = y}

		transition.stopTarget(self.scrollNode)
		self:callListener_{name = "began"}
		return true
	elseif "moved" == event.name then
		self.bDrag_ = true
		local disX = event.x - event.prevX
		local disY = event.y - event.prevY

		if self.direction == UIScrollView.DIRECTION_VERTICAL then
			disX = 0
		elseif self.direction == UIScrollView.DIRECTION_HORIZONTAL then
			disY = 0
		else
			-- do nothing
		end

		self:scrollBy(disX, disY)
		self:callListener_{name = "moved", disX = disX, disY = disY}
	elseif "ended" == event.name then
		if self.bDrag_ then
			self:scrollAuto()

			self:callListener_{name = "ended", disX = disX, disY = disY}
		else
			-- self:notifyItem(
			-- 	self.container:convertToNodeSpace(cc.p(event.x, event.y)))
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
	local cascadeBound = self.actualRect_ or self.scrollNode:getCascadeBoundingBox()
	local disX, dixY = 0, 0

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

	transition.moveBy(self.scrollNode,
		{x = disX, y = disY, time = 0.3,
		easing = "backout",
		onComplete = function()
			self:callListener_{name = "scrollEnd"}
		end})
end

function UIScrollView:callListener_(event)
	if not self.scrollListener_ then
		return
	end

	self.scrollListener_(event)
end

return UIScrollView
