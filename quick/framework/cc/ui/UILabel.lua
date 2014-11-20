
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
-- @module UILabel

--[[--

quick UILabel控件

]]

local UILabel
UILabel = class("UILabel", function(options)
	if not options then
		return
	end

	if 1 == options.UILabelType then
		return UILabel.newBMFontLabel_(options)
	elseif not options.UILabelType or 2 == options.UILabelType then
		return UILabel.newTTFLabel_(options)
	else
		printInfo("UILabel unkonw UILabelType")
	end
end)

UILabel.LABEL_TYPE_BM					= 1
UILabel.LABEL_TYPE_TTF 					= 2


-- start --

--------------------------------
-- UILabel构建函数
-- @function [parent=#UILabel] new
-- @param table options 参数表

-- end --

function UILabel:ctor(options)
    makeUIControl_(self)
    self:setLayoutSizePolicy(display.FIXED_SIZE, display.FIXED_SIZE)

    self:align(display.LEFT_CENTER)
end

-- start --

--------------------------------
-- UILabel设置控件大小
-- @function [parent=#UILabel] setLayoutSize
-- @param number width 宽度
-- @param number height 高度
-- @return UILabel#UILabel  自身

-- end --

function UILabel:setLayoutSize(width, height)
    self:getComponent("components.ui.LayoutProtocol"):setLayoutSize(width, height)
    return self
end


-- private

--[[--

用位图字体创建文本显示对象，并返回 LabelBMFont 对象。

BMFont 通常用于显示英文内容，因为英文字母加数字和常用符号也不多，生成的 BMFont 文件较小。如果是中文，应该用 TTFLabel。

可用参数：

-    text: 要显示的文本
-    font: 字体文件名
-    align: 文字的水平对齐方式（可选）
-    x, y: 坐标（可选）

~~~ lua

local label = UILabel:newBMFontLabel({
    text = "Hello",
    font = "UIFont.fnt",
})

~~~

@param table params 参数表格对象

@return LabelBMFont LabelBMFont对象

]]
function UILabel.newBMFontLabel_(params)
    return display.newBMFontLabel(params)
end

--[[--

使用 TTF 字体创建文字显示对象，并返回 Label 对象。

可用参数：

-    text: 要显示的文本
-    font: 字体名，如果是非系统自带的 TTF 字体，那么指定为字体文件名
-    size: 文字尺寸，因为是 TTF 字体，所以可以任意指定尺寸
-    color: 文字颜色（可选），用 cc.c3b() 指定，默认为白色
-    align: 文字的水平对齐方式（可选）
-    valign: 文字的垂直对齐方式（可选），仅在指定了 dimensions 参数时有效
-    dimensions: 文字显示对象的尺寸（可选），使用 cc.size() 指定
-    x, y: 坐标（可选）

align 和 valign 参数可用的值：

-    cc.ui.TEXT_ALIGN_LEFT 左对齐
-    cc.ui.TEXT_ALIGN_CENTER 水平居中对齐
-    cc.ui.TEXT_ALIGN_RIGHT 右对齐
-    cc.ui.TEXT_VALIGN_TOP 垂直顶部对齐
-    cc.ui.TEXT_VALIGN_CENTER 垂直居中对齐
-    cc.ui.TEXT_VALIGN_BOTTOM 垂直底部对齐

~~~ lua

-- 创建一个居中对齐的文字显示对象
local label = UILabel:newTTFLabel({
    text = "Hello, World",
    font = "Marker Felt",
    size = 64,
    align = cc.ui.TEXT_ALIGN_CENTER -- 文字内部居中对齐
})

-- 左对齐，并且多行文字顶部对齐
local label = UILabel:newTTFLabel({
    text = "Hello, World\n您好，世界",
    font = "Arial",
    size = 64,
    color = cc.c3b(255, 0, 0), -- 使用纯红色
    align = cc.ui.TEXT_ALIGN_LEFT,
    valign = cc.ui.TEXT_VALIGN_TOP,
    dimensions = cc.size(400, 200)
})

~~~

@param table params 参数表格对象

@return LabelTTF LabelTTF对象

]]
function UILabel.newTTFLabel_(params)
    return display.newTTFLabel(params)
end

return UILabel
