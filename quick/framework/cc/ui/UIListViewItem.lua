
local UIListViewItem = class("UIListViewItem", function()
	return cc.Node:create()
end)

UIListViewItem.BG_TAG = 1
UIListViewItem.BG_Z_ORDER = 1
UIListViewItem.CONTENT_TAG = 11
UIListViewItem.CONTENT_Z_ORDER = 11
UIListViewItem.ID_COUNTER = 0

function UIListViewItem:ctor(item)
	self.width = 0
	self.height = 0
	UIListViewItem.ID_COUNTER = UIListViewItem.ID_COUNTER + 1
	self.id = UIListViewItem.ID_COUNTER
	self:setTag(self.id)
	self:addContent(item)
end

function UIListViewItem:addContent(content)
	if not content then
		return
	end

	self:addChild(content, UIListViewItem.CONTENT_Z_ORDER, UIListViewItem.CONTENT_TAG)
end

function UIListViewItem:getContent()
	return self:getChildByTag(UIListViewItem.CONTENT_TAG)
end

function UIListViewItem:setItemSize(w, h)
	local oldSize = {width = self.width, height = self.height}
	local newSize = {width = w, height = h}

	self.width = w or 0
	self.height = h or 0
	self:setContentSize(w, h)

	local bg = self:getChildByTag(UIListViewItem.BG_TAG)
	if bg then
		bg:setContentSize(w, h)
		bg:setPosition(cc.p(w/2, h/2))
	end

	self.listener(self, newSize, oldSize)
end

function UIListViewItem:getItemSize()
	return self.width, self.height
end

function UIListViewItem:setBg(bg)
	local sp = display.newScale9Sprite(bg)
	sp:setAnchorPoint(cc.p(0.5, 0.5))
	sp:setPosition(cc.p(self.width/2, self.height/2))
	self:addChild(sp, UIListViewItem.BG_Z_ORDER, UIListViewItem.BG_TAG)
end

function UIListViewItem:onSizeChange(listener)
	self.listener = listener

	return self
end

return UIListViewItem
