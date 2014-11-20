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
-- @module ui

--[[--

创建和管理用户界面

]]

local ui = {}

ui.DEFAULT_TTF_FONT      = "Arial"
ui.DEFAULT_TTF_FONT_SIZE = 24

ui.TEXT_ALIGN_LEFT    = cc.TEXT_ALIGNMENT_LEFT
ui.TEXT_ALIGN_CENTER  = cc.TEXT_ALIGNMENT_CENTER
ui.TEXT_ALIGN_RIGHT   = cc.TEXT_ALIGNMENT_RIGHT
ui.TEXT_VALIGN_TOP    = cc.VERTICAL_TEXT_ALIGNMENT_TOP
ui.TEXT_VALIGN_CENTER = cc.VERTICAL_TEXT_ALIGNMENT_CENTER
ui.TEXT_VALIGN_BOTTOM = cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM

-- start --

--------------------------------
-- 创建一个文字输入框，并返回 EditBox 对象。
-- @function [parent=#ui] newEditBox
-- @param table params 参数表格对象
-- @return EditBox#EditBox  文字输入框

--[[--

创建一个文字输入框，并返回 EditBox 对象。

可用参数：

-   image: 输入框的图像，可以是图像名或者是 Sprite9Scale 显示对象。用 display.newScale9Sprite() 创建 Sprite9Scale 显示对象。
-   imagePressed: 输入状态时输入框显示的图像（可选）
-   imageDisabled: 禁止状态时输入框显示的图像（可选）
-   listener: 回调函数
-   size: 输入框的尺寸，用 cc.size(宽度, 高度) 创建
-   x, y: 坐标（可选）

~~~ lua

local function onEdit(event, editbox)
    if event == "began" then
        -- 开始输入
    elseif event == "changed" then
        -- 输入框内容发生变化
    elseif event == "ended" then
        -- 输入结束
    elseif event == "return" then
        -- 从输入框返回
    end
end

local editbox = ui.newEditBox({
    image = "EditBox.png",
    listener = onEdit,
    size = cc.size(200, 40)
})

~~~

注意: 使用setInputFlag(0) 可设为密码输入框。

注意：构造输入框时，请使用setPlaceHolder来设定初始文本显示。setText为出现输入法后的默认文本。

注意：事件触发机制，player模拟器上与真机不同，请使用真机实测(不同ios版本貌似也略有不同)。

注意：changed事件中，需要条件性使用setText（如trim或转化大小写等），否则在某些ios版本中会造成死循环。

~~~ lua

--错误，会造成死循环

editbox:setText(string.trim(editbox:getText()))

~~~

~~~ lua

--正确，不会造成死循环
local _text = editbox:getText()
local _trimed = string.trim(_text)
if _trimed ~= _text then
    editbox:setText(_trimed)
end

~~~

]]
-- end --

function ui.newEditBox(params)
    PRINT_DEPRECATED(string.format("%s() is deprecated, please use %s()", "ui.newEditBox", "cc.ui.UIInput"))

    if params then
        params.UIInputType = 1
    end
    return cc.ui.UIInput.new(params)
end

function ui.newTextField(params)
    PRINT_DEPRECATED(string.format("%s() is deprecated, please use %s()", "ui.newTextField", "cc.ui.UIInput"))

    if not params then
        params = {}
    end
    if params then
        params.UIInputType = 2
    end
    return cc.ui.UIInput.new(params)
end

-- start --

--------------------------------
-- 用位图字体创建文本显示对象，并返回 LabelBMFont 对象。
-- @function [parent=#ui] newBMFontLabel
-- @param table params 参数表格对象
-- @return LabelBMFont#LabelBMFont  LabelBMFont对象

--[[--

用位图字体创建文本显示对象，并返回 LabelBMFont 对象。

BMFont 通常用于显示英文内容，因为英文字母加数字和常用符号也不多，生成的 BMFont 文件较小。如果是中文，应该用 TTFLabel。

可用参数：

-    text: 要显示的文本
-    font: 字体文件名
-    align: 文字的水平对齐方式（可选）
-    x, y: 坐标（可选）

~~~ lua

local label = ui.newBMFontLabel({
    text = "Hello",
    font = "UIFont.fnt",
})

~~~

]]
-- end --

function ui.newBMFontLabel(params)
    PRINT_DEPRECATED(string.format("%s() is deprecated, please use %s()", "ui.newBMFontLabel", "cc.ui.UILabel"))

    return cc.ui.UILabel.newBMFontLabel_(params)
end

-- start --

--------------------------------
-- 使用 TTF 字体创建文字显示对象，并返回 LabelTTF 对象。
-- @function [parent=#ui] newTTFLabel
-- @param table params 参数表格对象
-- @return LabelTTF#LabelTTF  LabelTTF对象

--[[--

使用 TTF 字体创建文字显示对象，并返回 LabelTTF 对象。

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

-    ui.TEXT_ALIGN_LEFT 左对齐
-    ui.TEXT_ALIGN_CENTER 水平居中对齐
-    ui.TEXT_ALIGN_RIGHT 右对齐
-    ui.TEXT_VALIGN_TOP 垂直顶部对齐
-    ui.TEXT_VALIGN_CENTER 垂直居中对齐
-    ui.TEXT_VALIGN_BOTTOM 垂直底部对齐

~~~ lua

-- 创建一个居中对齐的文字显示对象
local label = ui.newTTFLabel({
    text = "Hello, World",
    font = "Marker Felt",
    size = 64,
    align = ui.TEXT_ALIGN_CENTER -- 文字内部居中对齐
})

-- 左对齐，并且多行文字顶部对齐
local label = ui.newTTFLabel({
    text = "Hello, World\n您好，世界",
    font = "Arial",
    size = 64,
    color = cc.c3b(255, 0, 0), -- 使用纯红色
    align = ui.TEXT_ALIGN_LEFT,
    valign = ui.TEXT_VALIGN_TOP,
    dimensions = cc.size(400, 200)
})

~~~

]]
-- end --

function ui.newTTFLabel(params)
    PRINT_DEPRECATED(string.format("%s() is deprecated, please use %s()", "ui.newTTFLabel", "cc.ui.UILabel"))

    return cc.ui.UILabel.newTTFLabel_(params)
end

-- start --

--------------------------------
-- 创建带阴影的 TTF 文字显示对象，并返回 LabelTTF 对象。
-- @function [parent=#ui] newTTFLabelWithShadow
-- @param table params 参数表格对象
-- @return LabelTTF#LabelTTF  LabelTTF对象

--[[--

创建带阴影的 TTF 文字显示对象，并返回 LabelTTF 对象。

相比 ui.newTTFLabel() 增加一个参数：

-   shadowColor: 阴影颜色（可选），用 cc.c4b() 指定，默认为黑色

]]
-- end --

function ui.newTTFLabelWithShadow(params)
    PRINT_DEPRECATED(string.format("%s() is deprecated, please use %s()", "ui.newTTFLabelWithShadow", "cc.ui.UILabel"))

    local label = cc.ui.UILabel.newTTFLabel_(params)
    label:enableShadow(params.shadowColor, cc.size(2,-2))

    return label
end

-- start --

--------------------------------
-- 创建带描边效果的 TTF 文字显示对象，并返回 LabelTTF 对象。
-- @function [parent=#ui] newTTFLabelWithOutline
-- @param table params 参数表格对象
-- @return LabelTTF#LabelTTF  LabelTTF对象

--[[--

创建带描边效果的 TTF 文字显示对象，并返回 LabelTTF 对象。

相比 ui.newTTFLabel() 增加一个参数：

    outlineColor: 描边颜色（可选），用 cc.c4b() 指定，默认为黑色

]]
-- end --

function ui.newTTFLabelWithOutline(params)
    PRINT_DEPRECATED(string.format("%s() is deprecated, please use %s()", "ui.newTTFLabelWithOutline", "cc.ui.UILabel"))
    
    local label = cc.ui.UILabel.newTTFLabel_(params)
    label:enableOutline(params.outlineColor, 2);

    return label
end

return ui
