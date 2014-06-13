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

创建和管理用户界面

]]
local ui = {}

ui.DEFAULT_TTF_FONT      = "Arial"
ui.DEFAULT_TTF_FONT_SIZE = 24

ui.TEXT_ALIGN_LEFT    = kCCTextAlignmentLeft
ui.TEXT_ALIGN_CENTER  = kCCTextAlignmentCenter
ui.TEXT_ALIGN_RIGHT   = kCCTextAlignmentRight
ui.TEXT_VALIGN_TOP    = kCCVerticalTextAlignmentTop
ui.TEXT_VALIGN_CENTER = kCCVerticalTextAlignmentCenter
ui.TEXT_VALIGN_BOTTOM = kCCVerticalTextAlignmentBottom

--[[--

创建一个文字输入框，并返回 CCEditBox 对象。

可用参数：

-   image: 输入框的图像，可以是图像名或者是 CCSprite9Scale 显示对象。用 display.newScale9Sprite() 创建 CCSprite9Scale 显示对象。
-   imagePressed: 输入状态时输入框显示的图像（可选）
-   imageDisabled: 禁止状态时输入框显示的图像（可选）
-   listener: 回调函数
-   size: 输入框的尺寸，用 CCSize(宽度, 高度) 创建
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
    size = CCSize(200, 40)
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

@return CCEditBox 文字输入框

]]
function ui.newEditBox(params)
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

    local editbox = CCEditBox:create(params.size, imageNormal, imagePressed, imageDisabled)

    if editbox then
        editbox:addEditBoxEventListener(params.listener)
        if params.x and params.y then
            editbox:setPosition(params.x, params.y)
        end
    end

    return editbox
end

--[[--

创建菜单，并返回 CCMenu 对象。

@param table items 菜单项的数组表

@return CCMenu CCMenu对象

]]
function ui.newMenu(items)
    local menu
    menu = CCMenu:create()

    for k, item in pairs(items) do
        if not tolua.isnull(item) then
            menu:addChild(item, 0, item:getTag())
        end
    end

    menu:setPosition(0, 0)
    return menu
end

--[[--

创建一个图像菜单项，并返回 CCMenuItemSprite 对象。

可用参数：

-    image: 正常状态的按钮图像
-    imageSelected: 按钮按下时的图像（可选）
-    imageDisabled: 按钮被禁用时的图像（可选）
-    listener: 回调函数
-    tag: 按钮的 Tag，会传入回调函数。多个按钮使用同一个回调函数时，可根据 Tag 区分哪一个按钮被按下（可选）
-    x, y: 坐标（可选）
-    sound: 按钮按下时播放什么音效（可选）

~~~ lua

local function onButtonClicked(tag)
    -- 按钮被按下
end

local item = ui.newImageMenuItem({
    image = "Button.png",
    imageSelected = "ButtonSelected.png",
    listener = onButtonClicked
})

-- 创建菜单并加入场景，否则菜单项不会工作
local menu = ui.newMenu({item})
scene:addChild(menu)

~~~

@param table params 参数表格对象

@return CCMenuItemSprite CCMenuItemSprite对象

]]
function ui.newImageMenuItem(params)
    local imageNormal   = params.image
    local imageSelected = params.imageSelected
    local imageDisabled = params.imageDisabled
    local listener      = params.listener
    local tag           = params.tag
    local x             = params.x
    local y             = params.y
    local sound         = params.sound

    if type(imageNormal) == "string" then
        imageNormal = display.newSprite(imageNormal)
    end
    if type(imageSelected) == "string" then
        imageSelected = display.newSprite(imageSelected)
    end
    if type(imageDisabled) == "string" then
        imageDisabled = display.newSprite(imageDisabled)
    end

    local item = CCMenuItemSprite:create(imageNormal, imageSelected, imageDisabled)
    if item then
        if type(listener) == "function" then
            item:addNodeEventListener(cc.MENU_ITEM_CLICKED_EVENT, function(tag)
                if sound then audio.playSound(sound) end
                listener(tag)
            end)
        end
        if x and y then item:setPosition(x, y) end
        if tag then item:setTag(tag) end
    end

    return item
end

--[[--

创建一个文字标签菜单项，并返回 CCMenuItemLabel 对象。

可用参数：

-   listener: 回调函数
-   tag: 按钮的 Tag，会传入回调函数。多个按钮使用同一个回调函数时，可根据 Tag 区分哪一个按钮被按下（可选）
-   x, y: 坐标（可选）
-   sound: 按钮按下时播放什么音效（可选）

以及所有可以用于 ui.newTTFLabel() 的参数。

@param table params 参数表格对象

@return CCMenuItemLabel CCMenuItemLabel对象

]]

function ui.newTTFLabelMenuItem(params)
    local p = clone(params)
    p.x, p.y = nil, nil
    local label = ui.newTTFLabel(p)

    local listener = params.listener
    local tag      = params.tag
    local x        = params.x
    local y        = params.y
    local sound    = params.sound

    local item = CCMenuItemLabel:create(label)
    if item then
        if type(listener) == "function" then
            item:addNodeEventListener(cc.MENU_ITEM_CLICKED_EVENT, function(tag)
                if sound then audio.playSound(sound) end
                listener(tag)
            end)
        end
        if x and y then item:setPosition(x, y) end
        if tag then item:setTag(tag) end
    end

    return item
end

--[[--

用位图字体创建文本显示对象，并返回 CCLabelBMFont 对象。

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

@param table params 参数表格对象

@return CCLabelBMFont CCLabelBMFont对象

]]
function ui.newBMFontLabel(params)
    assert(type(params) == "table",
           "[framework.ui] newBMFontLabel() invalid params")

    local text      = tostring(params.text)
    local font      = params.font
    local textAlign = params.align or ui.TEXT_ALIGN_CENTER
    local x, y      = params.x, params.y
    assert(font ~= nil, "ui.newBMFontLabel() - not set font")

    local label = CCLabelBMFont:create(text, font, kCCLabelAutomaticWidth, textAlign)
    if not label then return end

    if type(x) == "number" and type(y) == "number" then
        label:setPosition(x, y)
    end

    if textAlign == ui.TEXT_ALIGN_LEFT then
        label:align(display.LEFT_CENTER)
    elseif textAlign == ui.TEXT_ALIGN_RIGHT then
        label:align(display.RIGHT_CENTER)
    else
        label:align(display.CENTER)
    end

    return label
end

--[[--

使用 TTF 字体创建文字显示对象，并返回 CCLabelTTF 对象。

可用参数：

-    text: 要显示的文本
-    font: 字体名，如果是非系统自带的 TTF 字体，那么指定为字体文件名
-    size: 文字尺寸，因为是 TTF 字体，所以可以任意指定尺寸
-    color: 文字颜色（可选），用 ccc3() 指定，默认为白色
-    align: 文字的水平对齐方式（可选）
-    valign: 文字的垂直对齐方式（可选），仅在指定了 dimensions 参数时有效
-    dimensions: 文字显示对象的尺寸（可选），使用 CCSize() 指定
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
    color = ccc3(255, 0, 0), -- 使用纯红色
    align = ui.TEXT_ALIGN_LEFT,
    valign = ui.TEXT_VALIGN_TOP,
    dimensions = CCSize(400, 200)
})

~~~

@param table params 参数表格对象

@return CCLabelTTF CCLabelTTF对象

]]
function ui.newTTFLabel(params)
    assert(type(params) == "table",
           "[framework.ui] newTTFLabel() invalid params")

    local text       = tostring(params.text)
    local font       = params.font or ui.DEFAULT_TTF_FONT
    local size       = params.size or ui.DEFAULT_TTF_FONT_SIZE
    local color      = params.color or display.COLOR_WHITE
    local textAlign  = params.align or ui.TEXT_ALIGN_LEFT
    local textValign = params.valign or ui.TEXT_VALIGN_CENTER
    local x, y       = params.x, params.y
    local dimensions = params.dimensions

    assert(type(size) == "number",
           "[framework.ui] newTTFLabel() invalid params.size")

    local label
    if dimensions then
        label = CCLabelTTF:create(text, font, size, dimensions, textAlign, textValign)
    else
        label = CCLabelTTF:create(text, font, size)
    end

    if label then
        label:setColor(color)

        function label:realign(x, y)
            if textAlign == ui.TEXT_ALIGN_LEFT then
                label:setPosition(math.round(x + label:getContentSize().width / 2), y)
            elseif textAlign == ui.TEXT_ALIGN_RIGHT then
                label:setPosition(x - math.round(label:getContentSize().width / 2), y)
            else
                label:setPosition(x, y)
            end
        end

        if x and y then label:realign(x, y) end
    end

    return label
end

--[[--

创建带阴影的 TTF 文字显示对象，并返回 CCLabelTTF 对象。

相比 ui.newTTFLabel() 增加一个参数：

-   shadowColor: 阴影颜色（可选），用 ccc3() 指定，默认为黑色

@param table params 参数表格对象

@return CCLabelTTF CCLabelTTF对象

]]
function ui.newTTFLabelWithShadow(params)
    assert(type(params) == "table",
           "[framework.ui] newTTFLabelWithShadow() invalid params")

    local color       = params.color or display.COLOR_WHITE
    local shadowColor = params.shadowColor or display.COLOR_BLACK
    local x, y        = params.x, params.y

    local g = display.newNode()
    params.size = params.size
    params.color = shadowColor
    params.x, params.y = 0, 0
    g.shadow1 = ui.newTTFLabel(params)
    local offset = 1 / (display.widthInPixels / display.width)
    g.shadow1:realign(offset, -offset)
    g:addChild(g.shadow1)

    params.color = color
    g.label = ui.newTTFLabel(params)
    g.label:realign(0, 0)
    g:addChild(g.label)

    function g:setString(text)
        g.shadow1:setString(text)
        g.label:setString(text)
    end

    function g:realign(x, y)
        g:setPosition(x, y)
    end

    function g:getContentSize()
        return g.label:getContentSize()
    end

    function g:setColor(...)
        g.label:setColor(...)
    end

    function g:setShadowColor(...)
        g.shadow1:setColor(...)
    end

    function g:setOpacity(opacity)
        g.label:setOpacity(opacity)
        g.shadow1:setOpacity(opacity)
    end

    if x and y then
        g:setPosition(x, y)
    end

    return g
end

--[[--

创建带描边效果的 TTF 文字显示对象，并返回 CCLabelTTF 对象。

相比 ui.newTTFLabel() 增加一个参数：

    outlineColor: 描边颜色（可选），用 ccc3() 指定，默认为黑色

@param table params 参数表格对象

@return CCLabelTTF CCLabelTTF对象

]]
function ui.newTTFLabelWithOutline(params)
    assert(type(params) == "table",
           "[framework.ui] newTTFLabelWithShadow() invalid params")

    local color        = params.color or display.COLOR_WHITE
    local outlineColor = params.outlineColor or display.COLOR_BLACK
    local x, y         = params.x, params.y

    local g = display.newNode()
    params.size  = params.size
    params.color = outlineColor
    params.x, params.y = 0, 0
    g.shadow1 = ui.newTTFLabel(params)
    g.shadow1:realign(1, 0)
    g:addChild(g.shadow1)
    g.shadow2 = ui.newTTFLabel(params)
    g.shadow2:realign(-1, 0)
    g:addChild(g.shadow2)
    g.shadow3 = ui.newTTFLabel(params)
    g.shadow3:realign(0, -1)
    g:addChild(g.shadow3)
    g.shadow4 = ui.newTTFLabel(params)
    g.shadow4:realign(0, 1)
    g:addChild(g.shadow4)

    params.color = color
    g.label = ui.newTTFLabel(params)
    g.label:realign(0, 0)
    g:addChild(g.label)

    function g:setString(text)
        g.shadow1:setString(text)
        g.shadow2:setString(text)
        g.shadow3:setString(text)
        g.shadow4:setString(text)
        g.label:setString(text)
    end

    function g:getContentSize()
        return g.label:getContentSize()
    end

    function g:setColor(...)
        g.label:setColor(...)
    end

    function g:setOutlineColor(...)
        g.shadow1:setColor(...)
        g.shadow2:setColor(...)
        g.shadow3:setColor(...)
        g.shadow4:setColor(...)
    end

    function g:setOpacity(opacity)
        g.label:setOpacity(opacity)
        g.shadow1:setOpacity(opacity)
        g.shadow2:setOpacity(opacity)
        g.shadow3:setOpacity(opacity)
        g.shadow4:setOpacity(opacity)
    end

    if x and y then
        g:setPosition(x, y)
    end

    return g
end

return ui
