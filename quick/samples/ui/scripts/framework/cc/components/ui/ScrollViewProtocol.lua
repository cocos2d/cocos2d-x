
local Component = import("..Component")
local ScrollViewProtocol = class("ScrollViewProtocol", Component)

ScrollViewProtocol.DIRECTION_BOTH			= 0
ScrollViewProtocol.DIRECTION_VERTICAL		= 1
ScrollViewProtocol.DIRECTION_HORIZONTAL		= 2

ScrollViewProtocol.CONTENT_TAG 				= 1

function ScrollViewProtocol:ctor()
    ScrollViewProtocol.super.ctor(self, "ScrollViewProtocol")
    self.direction = ScrollViewProtocol.DIRECTION_BOTH
end

function ScrollViewProtocol:regScrollListener(listener)
	self.scrollListener_ = listener
    return self.target_
end

function ScrollViewProtocol:setViewRect(rect)
	self.viewRect_ = rect
	return self.target_
end

function ScrollViewProtocol:setDirection(dir)
	self.direction = dir
end

function ScrollViewProtocol:applyTo(parent, ...)
	local node = cc.ClippingRegionNode:create()
	node:addChild(self.target_, ...)
	parent:addChild(node)

	self.scrollNode = node
	return self.target_
end

function ScrollViewProtocol:addChild(parent, ...)
	local node = cc.ClippingRegionNode:create()
	node:addChild(self.target_, ...)
	parent:addChild(node)

	self.scrollNode = node
	return self.target_
end

function ScrollViewProtocol:apply()
	if not self.viewRect_ then
		self.viewRect_ = self.target_:getCascadeBoundingBox()
	end
	self.scrollNode:setClippingRegion(self.viewRect_)

	self.target_:setTouchEnabled(true)
	self.target_:addNodeEventListener(cc.NODE_TOUCH_EVENT, function (event)
        return self:onTouch_(event)
    end)

    self:calcScrollRange()

    return self.target_
end

-- private

function ScrollViewProtocol:exportMethods()
    self:exportMethods_({
        "regScrollListener",
        "setViewRect",
        "setDirection",
        "apply",
        "applyTo",
        "addTo",
        "addChild"
    })
    return self.target_
end

function ScrollViewProtocol:onTouch_(event)
	-- print("ScrollViewProtocol - onTouch_:" .. event.name)

	if "began" == event.name and not cc.rectContainsPoint(self.viewRect_, cc.p(event.x, event.y)) then
		printInfo("#DEBUG touch didn't in viewRect")
		return false
	end

	if "began" == event.name then
		self.prevX_ = event.x
		self.prevY_ = event.y
		self.bDrag_ = false
		local x,y = self.target_:getPosition()
		self.position_ = {x = x, y = y}

		transition.stopTarget(self.target_)
		self:callListener_{name = "began"}
		return true
	elseif "moved" == event.name then
		self.bDrag_ = true
		local disX = event.x - event.prevX
		local disY = event.y - event.prevY
		print("ScrollViewProtocol - moved x:" .. disX .. " y:" .. disY)
		local newx, newy = self.position_.x, self.position_.y
		if self.direction == ScrollViewProtocol.DIRECTION_VERTICAL then
			newy = self.position_.y + disY
		elseif self.direction == ScrollViewProtocol.DIRECTION_HORIZONTAL then
			newx = self.position_.x + disX
		else
			newx = self.position_.x + disX
			newy = self.position_.y + disY
		end

		self:scrollTo(newx, newy)
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

function ScrollViewProtocol:calcScrollRange()
	--先计算出container的position x,y方向上的可变范围,后面拖动时可以直接用
	--拖动时是可以大于或小于这个范围的，只是拖动结束自动回到这个范围中来，回到哪一边的值，最近原则

	self.rect = self.target_:getCascadeBoundingBox()
	self.positionRange_ = {}
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
	local anchor = self.target_:getAnchorPoint()
	local size = self.target_:getContentSize()
	self.positionRange_.minX = self.positionRange_.minX + anchor.x * size.width
	self.positionRange_.maxX = self.positionRange_.maxX + anchor.x * size.width
	self.positionRange_.minY = self.positionRange_.minY + anchor.y * size.height
	self.positionRange_.maxY = self.positionRange_.maxY + anchor.y * size.height

	dump(self.positionRange_, "positionRange:")
end

function ScrollViewProtocol:scrollTo(p, y)
	local x_, y_
	if "table" == type(p) then
		x_ = p.x or 0
		y_ = p.y or 0
	else
		x_ = p
		y_ = y
	end

	self.position_ = cc.p(x_, y_)
	self.target_:setPosition(self.position_)
end

function ScrollViewProtocol:scrollAuto()
	-- print("htl scrollAuto:", self.position_.x, self.positionRange_.minX)
	local newX, newY = self.position_.x, self.position_.y
	if self.position_.x < self.positionRange_.minX then
		-- self:scrollTo(self.positionRange_.minX, self.position_.y)
		newX = self.positionRange_.minX
	elseif self.position_.x > self.positionRange_.maxX then
		-- self:scrollTo(self.positionRange_.maxX, self.position_.y)
		newX = self.positionRange_.maxX
	else
		--do nothing
	end

	if self.position_.y < self.positionRange_.minY then
		-- self:scrollTo(self.position_.x, self.positionRange_.minY)
		newY = self.positionRange_.minY
	elseif self.position_.y > self.positionRange_.maxY then
		-- self:scrollTo(self.position_.x, self.positionRange_.maxY)
		newY = self.positionRange_.maxY
	else
		-- do nothing
	end
	transition.moveTo(self.target_,
		{x = newX, y = newY, time = 0.3,
		easing = "backout",
		onComplete = function()
			self:callListener_{name = "scrollEnd"}
		end})
end

function ScrollViewProtocol:callListener_(event)
	if not self.scrollListener_ then
		return
	end

	self.scrollListener_(event)
end

return ScrollViewProtocol
