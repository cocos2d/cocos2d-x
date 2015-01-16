
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
-- @module UIInput

--[[--

quick 输入控件

]]

local UIInput
UIInput = class("UIInput", function(options)
    local inputLabel

	if not options or not options.UIInputType or 1 == options.UIInputType then
		inputLabel = UIInput.newEditBox_(options)
        inputLabel.UIInputType = 1
	elseif 2 == options.UIInputType then
		inputLabel = UIInput.newTextField_(options)
        inputLabel.UIInputType = 2
	else
	end

    return inputLabel
end)

-- start --

--------------------------------
-- 输入构建函数
-- @function [parent=#UIInput] new
-- @param table params 参数表格对象
-- @return mixed#mixed  editbox/textfield文字输入框

--[[--

输入构建函数

创建一个文字输入框，并返回 EditBox/textfield 对象。

options参灵敏:
-   UIInputType: 1或nil 表示创建editbox输入控件
-   UIInputType: 2 表示创建textfield输入控件

]]
-- end --

function UIInput:ctor(options)

    -- make editbox and textfield have same getText function
    if 2 == options.UIInputType then
        self.getText = self.getStringValue
    end

    self.args_ = options
end



-- private

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

@param table params 参数表格对象

@return EditBox 文字输入框

]]
function UIInput.newEditBox_(params)
    local imageNormal = params.image
    local imagePressed = params.imagePressed
    local imageDisabled = params.imageDisabled

    if type(imageNormal) == "string" then
        imageNormal = display.newScale9Sprite(imageNormal)
    end
    if type(imagePressed) == "string" then
        imagePressed = display.newScale9Sprite(imagePressed)
    end
    if type(imageDisabled) == "string" then
        imageDisabled = display.newScale9Sprite(imageDisabled)
    end

    local editboxCls
    if cc.bPlugin_ then
        editboxCls = ccui.EditBox
    else
        editboxCls = cc.EditBox
    end
    local editbox = editboxCls:create(params.size, imageNormal, imagePressed, imageDisabled)

    if editbox then
        if params.listener then
            editbox:registerScriptEditBoxHandler(params.listener)
        end
        if params.x and params.y then
            editbox:setPosition(params.x, params.y)
        end
    end

    return editbox
end

--[[--

创建一个文字输入框，并返回 Textfield 对象。

可用参数：

-   listener: 回调函数
-   size: 输入框的尺寸，用 cc.size(宽度, 高度) 创建
-   x, y: 坐标（可选）
-   placeHolder: 占位符(可选)
-   text: 输入文字(可选)
-   font: 字体
-   fontSize: 字体大小
-   maxLength:
-   passwordEnable:开启密码模式
-   passwordChar:密码代替字符

~~~ lua

local function onEdit(textfield, eventType)
    if event == 0 then
        -- ATTACH_WITH_IME
    elseif event == 1 then
        -- DETACH_WITH_IME
    elseif event == 2 then
        -- INSERT_TEXT
    elseif event == 3 then
        -- DELETE_BACKWARD
    end
end

local textfield = UIInput.new({
    UIInputType = 2,
    listener = onEdit,
    size = cc.size(200, 40)
})

~~~

@param table params 参数表格对象

@return Textfield 文字输入框

]]
function UIInput.newTextField_(params)
    local textfieldCls
    if cc.bPlugin_ then
        textfieldCls = ccui.TextField
    else
        textfieldCls = cc.TextField
    end
    local editbox = textfieldCls:create()
    editbox:setPlaceHolder(params.placeHolder)
    if params.x and params.y then
        editbox:setPosition(params.x, params.y)
    end
    if params.listener then
        editbox:addEventListener(params.listener)
    end
    if params.size then
        editbox:setTextAreaSize(params.size)
    end
    if params.text then
        if editbox.setString then
            editbox:setString(params.text)
        else
            editbox:setText(params.text)
        end
    end
    if params.font then
        editbox:setFontName(params.font)
    end
    if params.fontSize then
        editbox:setFontSize(params.fontSize)
    end
    if params.maxLength and 0 ~= params.maxLength then
        editbox:setMaxLengthEnabled(true)
        editbox:setMaxLength(params.maxLength)
    end
    if params.passwordEnable then
        editbox:setPasswordEnabled(true)
    end
    if params.passwordChar then
        editbox:setPasswordStyleText(params.passwordChar)
    end

    return editbox
end

function UIInput:createcloneInstance_()
    return UIInput.new(unpack(self.args_))
end

return UIInput
