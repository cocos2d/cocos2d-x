
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

--[[--

quick UIImage控件

]]

local UIImage = class("UIImage", function(filename, options)
    if options and options.scale9 then
        return display.newScale9Sprite(filename, nil, nil, nil, options.capInsets)
    else
        return display.newSprite(filename)
    end
end)

--[[--

UIImage构建函数

@param string filename 图片文件名
@param table options 参数表

]]
function UIImage:ctor(filename, options)
    makeUIControl_(self)
    self:align(display.LEFT_BOTTOM)
    local contentSize = self:getContentSize()
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(contentSize.width, contentSize.height)
    self.isScale9_ = options and options.scale9
    if self.isScale9_ then
        self:setLayoutSizePolicy(display.AUTO_SIZE, display.AUTO_SIZE)
    end
end


--[[--

UIImage设置控件大小

@param number width 宽度
@param number height 高度

@return UIImage 自身

]]
function UIImage:setLayoutSize(width, height)
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    local width, height = self:getLayoutSize()
    local top, right, bottom, left = self:getLayoutPadding()
    width = width - left - right
    height = height - top - bottom

    if self.isScale9_ then
        self:setContentSize(cc.size(width, height))
    else
        local boundingSize = self:getBoundingBox()
        local sx = width / (boundingSize.width / self:getScaleX())
        local sy = height / (boundingSize.height / self:getScaleY())
        if sx > 0 and sy > 0 then
            self:setScaleX(sx)
            self:setScaleY(sy)
        end
    end

    if self.layout_ then
        self:setLayout(self.layout_)
    end

    return self
end

return UIImage
