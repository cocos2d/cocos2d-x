
--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--------------------------------
-- @module UIListViewItem

--[[--

quick UIListViewItem控件

]]

local UIScrollView = import(".UIScrollView")

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
	self.margin_ = {left = 0, right = 0, top = 0, bottom = 0}
	UIListViewItem.ID_COUNTER = UIListViewItem.ID_COUNTER + 1
	self.id = UIListViewItem.ID_COUNTER
	self:setTag(self.id)
	self:addContent(item)
end

-- start --

--------------------------------
-- 将要内容加到列表控件项中
-- @function [parent=#UIListViewItem] addContent
-- @param node content 显示内容

-- end --

function UIListViewItem:addContent(content)
	if not content then
		return
	end

	self:addChild(content, UIListViewItem.CONTENT_Z_ORDER, UIListViewItem.CONTENT_TAG)
end

-- start --

--------------------------------
-- 获取列表控件项中的内容
-- @function [parent=#UIListViewItem] getContent
-- @return node#node 

-- end --

function UIListViewItem:getContent()
	return self:getChildByTag(UIListViewItem.CONTENT_TAG)
end

-- start --

--------------------------------
-- 设置列表项中的大小
-- @function [parent=#UIListViewItem] setItemSize
-- @param number w 列表项宽度
-- @param number h 列表项高度
-- @param boolean bNoMargin 是否不使用margin margin可调用setMargin赋值

-- end --

function UIListViewItem:setItemSize(w, h, bNoMargin)
	if not bNoMargin then
		if UIScrollView.DIRECTION_VERTICAL == self.lvDirection_ then
			h = h + self.margin_.top + self.margin_.bottom
		else
			w = w + self.margin_.left + self.margin_.right
		end
	end

	-- print("UIListViewItem - setItemSize w:" .. w .. " h:" .. h)

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

--[[--

设置列表项中的大小

@return number width
@return number height

]]
function UIListViewItem:getItemSize()
	return self.width, self.height
end

function UIListViewItem:setMargin(margin)
	self.margin_ = margin

	-- dump(self.margin_, "set margin:")
end

function UIListViewItem:getMargin()
	return self.margin_
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

-- just for listview invoke
function UIListViewItem:setDirction(dir)
	self.lvDirection_ = dir
end

return UIListViewItem
