
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
-- @module UILoadingBar

--[[--

quick 进度控件

]]

local UILoadingBar = class("UILoadingBar", function()
	local node = cc.ClippingRegionNode:create()
	return node
end)

UILoadingBar.DIRECTION_LEFT_TO_RIGHT = 0
UILoadingBar.DIRECTION_RIGHT_TO_LEFT = 1

-- start --

--------------------------------
-- 进度控件构建函数
-- @function [parent=#UILoadingBar] new
-- @param table params 参数

--[[--

进度控件构建函数

可用参数有：

-   scale9 是否缩放
-   capInsets 缩放的区域
-   image 图片
-   viewRect 显示区域
-   percent 进度值 0到100
-	direction 方向，默认值从左到右

]]
-- end --

function UILoadingBar:ctor(params)
	if params.scale9 then
		self.scale9 = true
		local scale9sp = ccui.Scale9Sprite or cc.Scale9Sprite
		if string.byte(params.image) == 35 then
			self.bar = scale9sp:createWithSpriteFrameName(
				string.sub(params.image, 2), params.capInsets);
		else
			self.bar = scale9sp:create(
				params.capInsets, params.image)
		end
		self:setClippingRegion(cc.rect(0, 0, params.viewRect.width, params.viewRect.height))
	else
		self.bar = display.newSprite(params.image)
	end

	self.direction_ = params.direction or UILoadingBar.DIRECTION_LEFT_TO_RIGHT

	self:setViewRect(params.viewRect)
	self.bar:setAnchorPoint(cc.p(0, 0))
	self.bar:setPosition(0, 0)
	self:setPercent(params.percent or 0)
	self:addChild(self.bar)
end

-- start --

--------------------------------
-- 设置进度控件的进度
-- @function [parent=#UILoadingBar] setPercent
-- @param number percent 进度值 0到100
-- @return UILoadingBar#UILoadingBar 

-- end --

function UILoadingBar:setPercent(percent)
	local rect = cc.rect(self.viewRect_.x, self.viewRect_.y,
		self.viewRect_.width, self.viewRect_.height)
	local newWidth = rect.width*percent/100

	rect.x = 0
	rect.y = 0
	if self.scale9 then
		self.bar:setPreferredSize(cc.size(newWidth, rect.height))
		if UILoadingBar.DIRECTION_LEFT_TO_RIGHT ~= self.direction_ then
			self.bar:setPosition(rect.width - newWidth,	0)
		end
	else
		if UILoadingBar.DIRECTION_LEFT_TO_RIGHT == self.direction_ then
			rect.width = newWidth
			self:setClippingRegion(cc.rect(rect.x, rect.y, rect.width, rect.height))
		else
			rect.x = rect.x + rect.width - newWidth
			rect.width = newWidth
			self:setClippingRegion(cc.rect(rect.x, rect.y, rect.width, rect.height))
		end
	end

	return self
end

-- start --

--------------------------------
-- 设置进度控件的方向
-- @function [parent=#UILoadingBar] setDirction
-- @param integer dir 进度的方向
-- @return UILoadingBar#UILoadingBar 

-- end --

function UILoadingBar:setDirction(dir)
	self.direction_ = dir
	if UILoadingBar.DIRECTION_LEFT_TO_RIGHT ~= self.direction_ then
		if self.bar.setFlippedX then
			self.bar:setFlippedX(true)
		end
	end

	return self
end

-- start --

--------------------------------
-- 设置进度控件的显示区域
-- @function [parent=#UILoadingBar] setViewRect
-- @param table rect 显示区域
-- @return UILoadingBar#UILoadingBar 

-- end --

function UILoadingBar:setViewRect(rect)
	self.viewRect_ = rect
	self.bar:setContentSize(rect.width, rect.height)

	return self
end

return UILoadingBar
