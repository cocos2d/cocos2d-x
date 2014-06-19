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

与显示图像、场景有关的功能

<br />

display 模块封装了绝大部分与显示有关的功能，并负责根据 config.lua 中定义的分辨率设定计算屏幕的设计分辨率。

<br />

框架初始化后，display 模块提供下列属性：

-   display.sizeInPixels.width,
-   display.sizeInPixels.height 屏幕的像素分辨率
-   display.widthInPixels,
-   display.heightInPixels 屏幕的像素分辨率
-   display.contentScaleFactor 内容缩放因子
-   display.size.width,
-   display.size.height 屏幕的设计分辨率
-   display.width,
-   display.height 屏幕的设计分辨率
-   display.cx,
-   display.cy 屏幕中央的 x 坐标和 y 坐标
-   display.left,
-   display.top,
-   display.right,
-   display.bottom 屏幕四边的坐标
-   display.c_left,
-   display.c_top,
-   display.c_right,
-   display.c_bottom 当父对象在屏幕中央时，屏幕四边的坐标

<br />

颜色：

-   display.COLOR_WHITE 白色, cc.c3b(255, 255, 255)
-   display.COLOR_BLACK 黑色, cc.c3b(0, 0, 0)

]]
local display = {}

local sharedDirector         = cc.Director:getInstance()
local sharedTextureCache     = cc.Director:getInstance():getTextureCache()
local sharedSpriteFrameCache = cc.SpriteFrameCache:getInstance()
local sharedAnimationCache   = cc.AnimationCache:getInstance()

-- check device screen size
local glview = sharedDirector:getOpenGLView()
local size = glview:getFrameSize()
display.sizeInPixels = {width = size.width, height = size.height}

local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

if CONFIG_SCREEN_WIDTH == nil or CONFIG_SCREEN_HEIGHT == nil then
    CONFIG_SCREEN_WIDTH = w
    CONFIG_SCREEN_HEIGHT = h
end

if not CONFIG_SCREEN_AUTOSCALE then
    if w > h then
        CONFIG_SCREEN_AUTOSCALE = "FIXED_HEIGHT"
    else
        CONFIG_SCREEN_AUTOSCALE = "FIXED_WIDTH"
    end
else
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
end

local scale, scaleX, scaleY

if CONFIG_SCREEN_AUTOSCALE then
    if type(CONFIG_SCREEN_AUTOSCALE_CALLBACK) == "function" then
        scaleX, scaleY = CONFIG_SCREEN_AUTOSCALE_CALLBACK(w, h, device.model)
    end

    if not scaleX or not scaleY then
        scaleX, scaleY = w / CONFIG_SCREEN_WIDTH, h / CONFIG_SCREEN_HEIGHT
    end

    if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
        scale = scaleX
        CONFIG_SCREEN_HEIGHT = h / scale
    elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
        scale = scaleY
        CONFIG_SCREEN_WIDTH = w / scale
    else
        scale = 1.0
        printError(string.format("display - invalid CONFIG_SCREEN_AUTOSCALE \"%s\"", CONFIG_SCREEN_AUTOSCALE))
    end

    glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, kResolutionNoBorder)
end

local winSize = sharedDirector:getWinSize()
display.contentScaleFactor = scale
display.size               = {width = winSize.width, height = winSize.height}
display.width              = display.size.width
display.height             = display.size.height
display.cx                 = display.width / 2
display.cy                 = display.height / 2
display.c_left             = -display.width / 2
display.c_right            = display.width / 2
display.c_top              = display.height / 2
display.c_bottom           = -display.height / 2
display.left               = 0
display.right              = display.width
display.top                = display.height
display.bottom             = 0
display.widthInPixels      = display.sizeInPixels.width
display.heightInPixels     = display.sizeInPixels.height

printInfo(string.format("# CONFIG_SCREEN_AUTOSCALE      = %s", CONFIG_SCREEN_AUTOSCALE))
printInfo(string.format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
printInfo(string.format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
printInfo(string.format("# display.widthInPixels        = %0.2f", display.widthInPixels))
printInfo(string.format("# display.heightInPixels       = %0.2f", display.heightInPixels))
printInfo(string.format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
printInfo(string.format("# display.width                = %0.2f", display.width))
printInfo(string.format("# display.height               = %0.2f", display.height))
printInfo(string.format("# display.cx                   = %0.2f", display.cx))
printInfo(string.format("# display.cy                   = %0.2f", display.cy))
printInfo(string.format("# display.left                 = %0.2f", display.left))
printInfo(string.format("# display.right                = %0.2f", display.right))
printInfo(string.format("# display.top                  = %0.2f", display.top))
printInfo(string.format("# display.bottom               = %0.2f", display.bottom))
printInfo(string.format("# display.c_left               = %0.2f", display.c_left))
printInfo(string.format("# display.c_right              = %0.2f", display.c_right))
printInfo(string.format("# display.c_top                = %0.2f", display.c_top))
printInfo(string.format("# display.c_bottom             = %0.2f", display.c_bottom))
printInfo("#")

display.COLOR_WHITE = cc.c3b(255, 255, 255)
display.COLOR_BLACK = cc.c3b(0, 0, 0)
display.COLOR_RED   = cc.c3b(255, 0, 0)
display.COLOR_GREEN = cc.c3b(0, 255, 0)
display.COLOR_BLUE  = cc.c3b(0, 0, 255)

display.AUTO_SIZE      = 0
display.FIXED_SIZE     = 1
display.LEFT_TO_RIGHT  = 0
display.RIGHT_TO_LEFT  = 1
display.TOP_TO_BOTTOM  = 2
display.BOTTOM_TO_TOP  = 3

display.CENTER        = 1
display.LEFT_TOP      = 2; display.TOP_LEFT      = 2
display.CENTER_TOP    = 3; display.TOP_CENTER    = 3
display.RIGHT_TOP     = 4; display.TOP_RIGHT     = 4
display.CENTER_LEFT   = 5; display.LEFT_CENTER   = 5
display.CENTER_RIGHT  = 6; display.RIGHT_CENTER  = 6
display.BOTTOM_LEFT   = 7; display.LEFT_BOTTOM   = 7
display.BOTTOM_RIGHT  = 8; display.RIGHT_BOTTOM  = 8
display.BOTTOM_CENTER = 9; display.CENTER_BOTTOM = 9

display.ANCHOR_POINTS = {
    cc.p(0.5, 0.5),  -- CENTER
    cc.p(0, 1),      -- TOP_LEFT
    cc.p(0.5, 1),    -- TOP_CENTER
    cc.p(1, 1),      -- TOP_RIGHT
    cc.p(0, 0.5),    -- CENTER_LEFT
    cc.p(1, 0.5),    -- CENTER_RIGHT
    cc.p(0, 0),      -- BOTTOM_LEFT
    cc.p(1, 0),      -- BOTTOM_RIGHT
    cc.p(0.5, 0),    -- BOTTOM_CENTER
}

display.SCENE_TRANSITIONS = {
    CROSSFADE       = {cc.TransitionCrossFade, 2},
    FADE            = {cc.TransitionFade, 3, cc.c3b(0, 0, 0)},
    FADEBL          = {cc.TransitionFadeBL, 2},
    FADEDOWN        = {cc.TransitionFadeDown, 2},
    FADETR          = {cc.TransitionFadeTR, 2},
    FADEUP          = {cc.TransitionFadeUp, 2},
    FLIPANGULAR     = {cc.TransitionFlipAngular, 3, kCCTransitionOrientationLeftOver},
    FLIPX           = {cc.TransitionFlipX, 3, kCCTransitionOrientationLeftOver},
    FLIPY           = {cc.TransitionFlipY, 3, kCCTransitionOrientationUpOver},
    JUMPZOOM        = {cc.TransitionJumpZoom, 2},
    MOVEINB         = {cc.TransitionMoveInB, 2},
    MOVEINL         = {cc.TransitionMoveInL, 2},
    MOVEINR         = {cc.TransitionMoveInR, 2},
    MOVEINT         = {cc.TransitionMoveInT, 2},
    PAGETURN        = {cc.TransitionPageTurn, 3, false},
    ROTOZOOM        = {cc.TransitionRotoZoom, 2},
    SHRINKGROW      = {cc.TransitionShrinkGrow, 2},
    SLIDEINB        = {cc.TransitionSlideInB, 2},
    SLIDEINL        = {cc.TransitionSlideInL, 2},
    SLIDEINR        = {cc.TransitionSlideInR, 2},
    SLIDEINT        = {cc.TransitionSlideInT, 2},
    SPLITCOLS       = {cc.TransitionSplitCols, 2},
    SPLITROWS       = {cc.TransitionSplitRows, 2},
    TURNOFFTILES    = {cc.TransitionTurnOffTiles, 2},
    ZOOMFLIPANGULAR = {cc.TransitionZoomFlipAngular, 2},
    ZOOMFLIPX       = {cc.TransitionZoomFlipX, 3, kCCTransitionOrientationLeftOver},
    ZOOMFLIPY       = {cc.TransitionZoomFlipY, 3, kCCTransitionOrientationUpOver},
}

display.TEXTURES_PIXEL_FORMAT = {}

--[[--

创建一个新场景，并返回 Scene 场景对象。

指定场景名称方便调试。

@param string name 场景名称

@return Scene 场景对象

@see Scene

]]
function display.newScene(name)
    local scene = cc.Scene:create()
    scene:setNodeEventEnabled(true)
    scene:setAutoCleanupEnabled()
    scene.name = name or "<unknown-scene>"
    return scene
end

--[[--

创建一个新场景，并返回 Scene 场景对象。

指定场景名称方便调试。

@param string name 场景名称

@return Scene 场景对象

@see Scene

]]
function display.newPhysicsScene(name)
    local scene = cc.Scene:createWithPhysics()
    scene:setNodeEventEnabled(true)
    scene:setAutoCleanupEnabled()
    scene.name = name or "<unknown-scene>"
    return scene
end

--[[--

用场景切换过渡效果包装场景对象，并返回场景过渡对象。

~~~ lua

-- 创建一个新场景
local nextScene = display.newScene("NextScene")
-- 包装过渡效果
local transition = display.wrapSceneWithTransition(nextScene, "fade", 0.5)
-- 切换到新场景
display.replaceScene(nextScene)

~~~

可用的过渡效果有：

-   crossFade 淡出当前场景的同时淡入下一个场景
-   fade 淡出当前场景到指定颜色，默认颜色为 cc.c3b(0, 0, 0)，可用 wrapSceneWithTransition() 的最后一个参数指定颜色
-   fadeBL 从左下角开始淡出场景
-   fadeDown 从底部开始淡出场景
-   fadeTR 从右上角开始淡出场景
-   fadeUp 从顶部开始淡出场景
-   flipAngular 当前场景倾斜后翻转成下一个场景，默认从左边开始翻转，可以指定为：
    -   kCCTransitionOrientationLeftOver 从左边开始
    -   kCCTransitionOrientationRightOver 从右边开始
    -   kCCTransitionOrientationUpOver 从顶部开始
    -   kCCTransitionOrientationDownOver 从底部开始
-   flipX 水平翻转，默认从左往右翻转，可用的附加参数同上
-   flipY 垂直翻转，默认从上往下翻转，可用的附加参数同上
-   zoomFlipAngular 倾斜翻转的同时放大，可用的附加参数同上
-   zoomFlipX 水平翻转的同时放大，可用的附加参数同上
-   zoomFlipY 垂直翻转的同时放大，可用的附加参数同上
-   jumpZoom 跳跃放大切换场景
-   moveInB 新场景从底部进入，现有场景同时从顶部退出
-   moveInL 新场景从左侧进入，现有场景同时从右侧退出
-   moveInR 新场景从右侧进入，现有场景同时从左侧退出
-   moveInT 新场景从顶部进入，现有场景同时从底部退出
-   pageTurn 翻页效果，如果指定附加参数为 true，则表示从左侧往右翻页
-   rotoZoom 旋转放大切换场景
-   shrinkGrow 收缩交叉切换场景
-   slideInB 新场景从底部进入，直接覆盖现有场景
-   slideInL 新场景从左侧进入，直接覆盖现有场景
-   slideInR 新场景从右侧进入，直接覆盖现有场景
-   slideInT 新场景从顶部进入，直接覆盖现有场景
-   splitCols 分成多列切换入新场景
-   splitRows 分成多行切换入新场景，类似百叶窗
-   turnOffTiles 当前场景分成多个块，逐渐替换为新场景

@param Scene scene 场景对象
@param string transitionType 过渡效果名
@param number time 过渡时间
@param string more 过渡效果附加参数

@return Scene 场景对象

]]
function display.wrapSceneWithTransition(scene, transitionType, time, more)
    local key = string.upper(tostring(transitionType))
    if string.sub(key, 1, 12) == "CCTRANSITION" then
        key = string.sub(key, 13)
    end

    if key == "RANDOM" then
        local keys = table.keys(display.SCENE_TRANSITIONS)
        key = keys[math.random(1, #keys)]
    end

    if display.SCENE_TRANSITIONS[key] then
        local cls, count, default = unpack(display.SCENE_TRANSITIONS[key])
        time = time or 0.2

        if count == 3 then
            scene = cls:create(time, scene, more or default)
        else
            scene = cls:create(time, scene)
        end
    else
        printError("display.wrapSceneWithTransition() - invalid transitionType %s", tostring(transitionType))
    end
    return scene
end

--[[--

切换到新场景

~~~ lua

-- 使用红色做过渡色
display.replaceScene(nextScene, "fade", 0.5, cc.c3b(255, 0, 0))

~~~

@param Scene newScene 场景对象
@param string transitionType 过渡效果名
@param number time 过渡时间
@param mixed more 过渡效果附加参数

]]
function display.replaceScene(newScene, transitionType, time, more)
    if sharedDirector:getRunningScene() then
        if transitionType then
            newScene = display.wrapSceneWithTransition(newScene, transitionType, time, more)
        end
        sharedDirector:replaceScene(newScene)
    else
        sharedDirector:runWithScene(newScene)
    end
end

--[[--

返回当前正在运行的场景对象

@return Scene 场景对象

]]
function display.getRunningScene()
    return sharedDirector:getRunningScene()
end

--[[--

暂停当前场景

]]
function display.pause()
    sharedDirector:pause()
end

--[[--

恢复当前暂停的场景

]]
function display.resume()
    sharedDirector:resume()
end

--[[--

创建并返回一个 Layer 层对象

Layer 对象提供了触摸事件、重力感应、Android 按键检测等功能，具体请参考 Layer。

@see Layer

]]
function display.newLayer()
    return cc.Layer:create()
end

--[[--

创建一个颜色填充层

LayerColor 对象使用指定的颜色填充。

@param ccColor3B color

@return LayerColor

@see LayerColor

]]
function display.newColorLayer(color)
    return cc.LayerColor:create(color)
end

--[[--

创建并返回一个 Node 对象

Node 对象并不能显示对象，但可以作为其他显示对象的容器（起到群组的作用）。具体请参考 Node 。

~~~ lua

local group = display.newNode()     -- 创建一个容器
group:addChild(sprite1)             -- 添加显示对象到容器中
group:addChild(sprite2)             -- 添加显示对象到容器中

-- 移动容器时，其中包含的子对象也会同时移动
transition.moveBy(group, {time = 2.0, x = 100})

~~~

@return Node Node对象

@see Node

]]
function display.newNode()
    return cc.Node:create()
end

--[[--

创建并返回一个 ClippingRegionNode 对象。

创建 ClippingRegionNode 对象时需要指定一个屏幕区域，然后在显示时，所以加入 ClippingRegionNode 对象的内容都会进行剪裁，超出指定区域的内容不会显示。

~~~ lua

-- 剪裁区域从屏幕左下角靠内 100 点，到屏幕右上角
local rect = cc.rect(display.left + 100,
                    display.bottom + 100,
                    display.width - 200,
                    display.height - 200)
local clipnode = display.newClippingRegionNode(rect)

clipnode:addChild(sprite1)
clipnode:addChild(sprite2)

scene:addChild(clipnode)

~~~

注意：ClippingRegionNode 的父对象其坐标必须是 0, 0。

@param table rect 指定的区域

@return ClippingRegionNode ClippingRegionNode对象

]]
function display.newClippingRegionNode(rect)
    return cc.ClippingRegionNode:create(rect)
end

--[[--

创建并返回一个 Sprite 显示对象。

display.newSprite() 有三种方式创建显示对象：

-   从图片文件创建
-   从缓存的图像帧创建
-   从 SpriteFrame 对象创建

~~~ lua

-- 从图片文件创建显示对象
local sprite1 = display.newSprite("hello1.png")

-- 从缓存的图像帧创建显示对象
-- 图像帧的名字就是图片文件名，但为了和图片文件名区分，所以此处需要在文件名前添加 “#” 字符
-- 添加 “#” 的规则适用于所有需要区分图像和图像帧的地方
local sprite2 = display.newSprite("#frame0001.png")

-- 从 SpriteFrame 对象创建
local frame = display.newFrame("frame0002.png")
local sprite3 = display.newSprite(frame)

~~~

如果指定了 x,y 参数，那么创建显示对象后会调用对象的 setPosition() 方法设置对象位置。

@param mixed 图像名或SpriteFrame对象
@param number x
@param number y
@param table params

@return Sprite

@see Sprite

]]
function display.newSprite(filename, x, y, params)
    local spriteClass = nil
    local size = nil

    if params then
        spriteClass = params.class
        size = params.size
    end
    if not spriteClass then spriteClass = cc.Sprite end

    local t = type(filename)
    if t == "userdata" then t = tolua.type(filename) end
    local sprite

    if not filename then
        sprite = spriteClass:create()
    elseif t == "string" then
        if string.byte(filename) == 35 then -- first char is #
            local frame = display.newSpriteFrame(string.sub(filename, 2))
            if frame then
                sprite = spriteClass:createWithSpriteFrame(frame)
            end
        else
            if display.TEXTURES_PIXEL_FORMAT[filename] then
                cc.Texture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[filename])
                sprite = spriteClass:create(filename)
                cc.Texture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
            else
                sprite = spriteClass:create(filename)
            end
        end
    elseif t == "SpriteFrame" then
        sprite = spriteClass:createWithSpriteFrame(filename)
	elseif t == "Texture2D" then
		sprite = spriteClass:createWithTexture(filename)
    else
        printError("display.newSprite() - invalid filename value type")
        sprite = spriteClass:create()
    end

    if sprite then
        if x and y then sprite:setPosition(x, y) end
        if size then sprite:setContentSize(size) end
    else
        printError("display.newSprite() - create sprite failure, filename %s", tostring(filename))
        sprite = spriteClass:create()
    end

    return sprite
end

--[[--

创建并返回一个 Sprite9Scale 显示对象。

格式：

sprite = display.newScale9Sprite(图像名, [x, y], [size 对象])

Sprite9Scale 就是通常所說的“九宫格”图像。一个矩形图像会被分为 9 部分，然后根据要求拉伸图像，同时保证拉伸后的图像四边不变形。

~~~ lua

-- 创建一个 Scale9 图像，并拉伸到 400, 300 点大小
local sprite = display.newScale9Sprite("Box.png", 0, 0, cc.size(400, 300))

~~~

@param string filename 图像名
@param integer x
@param integer y
@param table size

@return Sprite9Scale Sprite9Scale显示对象

]]
function display.newScale9Sprite(filename, x, y, size)
	return display.newSprite(filename, x, y, {class = cc.Scale9Sprite, size = size})
end

--[[--

]]
function display.newTilesSprite(filename, rect)
    if not rect then
        rect = cc.rect(0, 0, display.width, display.height)
    end
    local sprite = cc.Sprite:create(filename, rect)
    if not sprite then
        printError("display.newTilesSprite() - create sprite failure, filename %s", tostring(filename))
        return
    end

    local tp = ccTexParams()
    tp.minFilter = 9729
    tp.magFilter = 9729
    tp.wrapS = 10497
    tp.wrapT = 10497
    sprite:getTexture():setTexParameters(tp)

    display.align(sprite, display.LEFT_BOTTOM, 0, 0)

    return sprite
end

--[[--

create a tiled SpriteBatchNode, the image can not a POT file.

@param mixed filename As same a the first parameter for display.newSprite
@param string plistFile Texture(plist) image filename, filename must be a part of the texture.
@param size size The tiled node size, use cc.size create it please.
@param integer hPadding Horizontal padding, it will display 1 px gap on moving the node, set padding for fix it.
@param integer vPadding Vertical padding.

@return A SpriteBatchNode

]]
function display.newTiledBatchNode(filename, plistFile, size, hPadding, vPadding)
	size = size or cc.size(display.width, display.height)
	hPadding = hPadding or 0
	vPadding = vPadding or 0
	local __sprite = display.newSprite(filename)
	local __sliceSize = __sprite:getContentSize()
	__sliceSize.width = __sliceSize.width - hPadding
	__sliceSize.height = __sliceSize.height - vPadding
	local __xRepeat = math.ceil(size.width/__sliceSize.width)
	local __yRepeat = math.ceil(size.height/__sliceSize.height)
	-- How maney sprites we need to fill in tiled node?
	local __capacity = __xRepeat * __yRepeat
	local __batch = display.newBatchNode(plistFile, __capacity)
	local __newSize = cc.size(0,0)
	--printf("newTileNode xRepeat:%u, yRepeat:%u", __xRepeat, __yRepeat)
	for y=0,__yRepeat-1 do
		for x=0,__xRepeat-1 do
			__newSize.width = __newSize.width + __sliceSize.width
			__sprite = display.newSprite(filename)
				:align(display.LEFT_BOTTOM,x*__sliceSize.width, y*__sliceSize.height)
				:addTo(__batch)
				--print("newTileNode:", x*__sliceSize.width, y*__sliceSize.height)
		end
		__newSize.height = __newSize.height + __sliceSize.height
	end
	__batch:setContentSize(__newSize)
	return __batch, __newSize.width, __newSize.height
end

--[[--

Create a masked sprite

]]
function display.newMaskedSprite(__mask, __pic)
	local __mb = ccBlendFunc()
	__mb.src = GL_ONE
	__mb.dst = GL_ZERO

	local __pb = ccBlendFunc()
	__pb.src = GL_DST_ALPHA
	__pb.dst = GL_ZERO

	local __maskSprite = display.newSprite(__mask):align(display.LEFT_BOTTOM, 0, 0)
	__maskSprite:setBlendFunc(__mb)

	local __picSprite = display.newSprite(__pic):align(display.LEFT_BOTTOM, 0, 0)
	__picSprite:setBlendFunc(__pb)

	local __maskSize = __maskSprite:getContentSize()
	local __canva = cc.RenderTexture:create(__maskSize.width,__maskSize.height)
	__canva:begin()
	__maskSprite:visit()
	__picSprite:visit()
	__canva:endToLua()

	local __resultSprite = cc.Sprite:createWithTexture(__canva:getSprite():getTexture())
    __resultSprite:setFlipY(true)
	return __resultSprite
end

--[[--

Create a Filtered Sprite

@param mixed filename As same a the first parameter for display.newSprite
@param mixed filters One of the following:

- A Filter name;
- More Filter names(in a table);
- An instance of Filter;
- Some instances of Filter(in a table);
- A Array inclueds some instances of Filter.

@param table params A or some parameters for Filter.

@return An instance of FilteredSprite

]]
function display.newFilteredSprite(filename, filters, params)
	local __one = {class=cc.FilteredSpriteWithOne}
	local __multi = {class=cc.FilteredSpriteWithMulti}
	if not filters then return display.newSprite(filtename, nil,nil , __one) end
	local __sp = nil
	local __type = type(filters)
    if __type == "userdata" then __type = tolua.type(filters) end
	--print("display.newFSprite type:", __type)
	if __type == "string" then
		__sp = display.newSprite(filename, nil, nil, __one)
		filters = filter.newFilter(filters, params)
		__sp:setFilter(filters)
	elseif __type == "table" then
		assert(#filters > 1, "display.newFilteredSprite() - Please give me 2 or more filters!")
		__sp = display.newSprite(filename, nil, nil, __multi)
		-- treat filters as {"FILTER_NAME", "FILTER_NAME"}
		if type(filters[1]) == "string" then
			__sp:setFilters(filter.newFilters(filters, params))
		else
			-- treat filters as {Filter, Filter , ...}
			local __filters = cc.Array:create()
			for i in ipairs(filters) do
				__filters:addObject(filters[i])
			end
			__sp:setFilters(__filters)
		end
	elseif __type == "Array" then
		-- treat filters as Array(Filter, Filter, ...)
		__sp = display.newSprite(filename, nil, nil, __multi)
		__sp:setFilters(filters)
	else
		-- treat filters as Filter
		__sp = display.newSprite(filename, nil, nil, __one)
		__sp:setFilter(filters)
	end
	return __sp
end

--[[--

Create a Gray Sprite by FilteredSprite

@param mixed filename As same a the first parameter for display.newSprite
@param table params As same as the third parameter for display.newFilteredSprite

@return An instance of FilteredSprite

]]
function display.newGraySprite(filename, params)
	return display.newFilteredSprite(filename, "GRAY", params)
end

function display.newDrawNode()
	return cc.DrawNode:create()
end

--[[--

Create a circle or a sector or a pie by DrawNode

Creation: 2014-03-11

@author zrong(zengrong.net)

@param mixed filename As same a the first parameter for display.newSprite
@param table params As same as the third parameter for display.newFilteredSprite

@return An instance of FilteredSprite

]]
function display.newSolidCircle(radius, params)
	local circle = display.newDrawNode()
	circle:drawCircle(radius, params)
	local x,y = 0,0
	if params then
		x = params.x or x
		y = params.y or y
	end
	circle:pos(x,y)
	return circle
end

--[[--

创建并返回一个 CircleShape （圆）对象。

@param number radius

@return CircleShape

@see ShapeNode

]]
function display.newCircle(radius, params)
    local circle = cc.CircleShape:create(radius)
	local x,y = 0,0
	local align=display.CENTER
	if params then
		x = params.x or x
		y = params.y or y
		align = params.align or align
		if params.fill then circle:setFill(params.fill) end
		if params.color then circle:setLineColor(params.color) end
		if params.strippleEnabled then circle:setLineStippleEnabled(params.strippleEnabled) end
		if params.lineStripple then circle:setLineStipple(params.lineStripple) end
		local lineWidth = params.lineWidth or params.borderWidth
		if lineWidth then circle:setLineWidth(lineWidth) end
	end
	circle:setContentSize(cc.size(radius*2,radius*2))
	circle:align(align, x,y)
	return circle
end

--[[--

创建并返回一个 RectShape （矩形）对象。

格式：

shape = display.newRect(宽度, 高度 | Rect | Size)

~~~ lua

-- 下面两行代码都创建一个宽度 200，高度 100 的矩形
local shape1 = display.newRect(200, 100)
local shape2 = display.newRect(cc.size(200, 100))

-- 创建一个宽度 200，高度 100 的矩形，并且定位于 50, 80
local shape3 = display.newRect(cc.rect(50, 80, 200, 100))

~~~

@param [mixed ...] 宽度，高度 或 Rect 或 Size

@return RectShape

@see ShapeNode

]]
function display.newRect(width, height, params)
    local x, y = 0, 0
    if type(width) == "userdata" then
        local t = tolua.type(width)
        if t == "Rect" then
            x = width.origin.x
            y = width.origin.y
            height = width.size.height
            width = width.size.width
        elseif t == "Size" then
            height = width.height
            width = width.width
        else
            printError("display.newRect() - invalid parameters")
            return
        end
    end

    local rect = cc.RectShape:create(cc.size(width, height))
	local align=display.CENTER
	if type(height) == "table" then params = hight end
	if type(params) == "table" then
		x = params.x or x
		y = params.y or y
		align = params.align or align
		if params.color then rect:setLineColor(params.color) end
		if params.strippleEnabled then rect:setLineStippleEnabled(params.strippleEnabled) end
		if params.lineStripple then rect:setLineStipple(params.lineStripple) end
		if params.fill then rect:setFill(params.fill) end
		local lineWidth = params.lineWidth or params.borderWidth
		if lineWidth then rect:setLineWidth(lineWidth) end
	end
	rect:setContentSize(cc.size(width, height))
	rect:align(align, x,y)
    return rect
end

--[[--

创建并返回一个 PolygonShape （多边形）对象。

~~~ lua

local points = {
    {10, 10},  -- point 1
    {50, 50},  -- point 2
    {100, 10}, -- point 3
}
local polygon = display.newPolygon(points)
polygon:setClose(true) -- 将第一个点和最后一个点相连

~~~

@param table points 包含多边形每一个点坐标的表格对象
@param number scale 缩放比例

@return PolygonShape PolygonShape对象

@see ShapeNode

]]
-- function display.newPolygon(points, scale)
--     if type(scale) ~= "number" then scale = 1 end
--     local arr = cc.PointArray:create(#points)
--     local ccp = cc.p
--     for i, p in ipairs(points) do
--         p = ccp(p[1] * scale, p[2] * scale)
--         arr:add(p)
--     end

--     return cc.PolygonShape:create(arr)
-- end

--[[--

将指定的显示对象按照特定锚点对齐。

格式：

display.align(显示对象, 锚点位置, [x, y])

显示对象锚点位置：

-   display.CENTER 图像中央
-   display.LEFT_TOP,
-   display.TOP_LEFT 图像左上角
-   display.CENTER_TOP,
-   display.TOP_CENTER 图像顶部的中间
-   display.RIGHT_TOP,
-   display.TOP_RIGHT 图像顶部的中间
-   display.CENTER_LEFT,
-   display.LEFT_CENTER 图像左边的中间
-   display.CENTER_RIGHT,
-   display.RIGHT_CENTER 图像右边的中间
-   display.BOTTOM_LEFT,
-   display.LEFT_BOTTOM 图像左边的底部
-   display.BOTTOM_RIGHT,
-   display.RIGHT_BOTTOM 图像右边的底部
-   display.BOTTOM_CENTER,
-   display.CENTER_BOTTOM 图像中间的底部

~~~ lua

-- 将图像按左上角对齐，并放置在屏幕左上角
display.align(sprite, display.LEFT_TOP, 0, 0)

~~~

@param Sprite target 显示对象
@param integer anchorPoint 锚点位置
@param integer x
@param integer y

]]
function display.align(target, anchorPoint, x, y)
    target:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then target:setPosition(x, y) end
end

function display.addImageAsync(imagePath, callback)
    sharedTextureCache:addImageAsync(imagePath, callback)
end

--[[--

将指定的 Sprite Sheets 材质文件及其数据文件载入图像帧缓存。

格式：

display.addSpriteFrames(数据文件名, 材质文件名)

~~~ lua

display.addSpriteFrames("Sprites.plist", "Sprites.png")

~~~

Sprite Sheets 通俗一点解释就是包含多张图片的集合。Sprite Sheets 材质文件由多张图片组成，而数据文件则记录了图片在材质文件中的位置等信息。

@param string plistFilename 数据文件名
@param string image 材质文件名

@see Sprite Sheets

]]
function display.addSpriteFrames(plistFilename, image, handler)
	local async = type(handler) == "function"
	local asyncHandler = nil
	if async then
		asyncHandler = function()
			-- printf("%s, %s async done.", plistFilename, image)
			local texture = sharedTextureCache:textureForKey(image)
			assert(texture, string.format("The texture %s, %s is unavailable.", plistFilename, image))
			sharedSpriteFrameCache:addSpriteFrames(plistFilename, texture)
			handler(plistFilename, image)
		end
	end

    if display.TEXTURES_PIXEL_FORMAT[image] then
        cc.Texture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[image])
		if async then
			sharedTextureCache:addImageAsync(image, asyncHandler)
		else
			sharedSpriteFrameCache:addSpriteFrames(plistFilename, image)
		end
        cc.Texture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888)
    else
		if async then
			sharedTextureCache:addImageAsync(image, asyncHandler)
		else
			sharedSpriteFrameCache:addSpriteFrames(plistFilename, image)
		end
    end
end

--[[--

从内存中卸载 Sprite Sheets 材质和数据文件

@param string plistFilename 数据文件名
@param string image 材质文件名

]]
function display.removeSpriteFramesWithFile(plistFilename, imageName)
    sharedSpriteFrameCache:removeSpriteFramesFromFile(plistFilename)
    if imageName then
        display.removeSpriteFrameByImageName(imageName)
    end
end

--[[--

设置材质格式。


为了节约内存，我们会使用一些颜色品质较低的材质格式，例如针对背景图使用 kCCTexture2DPixelFormat_RGB565 格式。

display.setTexturePixelFormat() 可以指定材质文件的材质格式，这样在加载材质文件时就会使用指定的格式。

@param string filename 材质文件名
@param integer format 材质格式

@see Texture Pixel Format

]]
function display.setTexturePixelFormat(filename, format)
    display.TEXTURES_PIXEL_FORMAT[filename] = format
end

--[[--

从图像帧缓存中删除一个图像。

有时候，某些图像仅在特定场景中使用，例如背景图。那么在场景退出时，就可以用 display.removeSpriteFrameByImageName() 从缓存里删除不再使用的图像数据。

此外，Scene 提供了 markAutoCleanupImage() 接口，可以指定场景退出时需要自动清理的图像，推荐使用。

@param string imageName 图像文件名

]]
function display.removeSpriteFrameByImageName(imageName)
    sharedSpriteFrameCache:removeSpriteFrameByName(imageName)
    cc.Director:getInstance():getTextureCache():removeTextureForKey(imageName)
end

--[[--

从指定的图像文件创建并返回一个批量渲染对象。

~~~ lua

local imageName = "Sprites.png"
display.addSpriteFrames("Sprites.plist", imageName) -- 载入图像到帧缓存

-- 下面的代码绘制 100 个图像只用了 1 次 OpenGL draw call
local batch = display.newBatch(imageName)
for i = 1, 100 do
    local sprite = display.newSprite("#Sprite0001.png")
    batch:addChild(sprite)
end

-- 下面的代码绘制 100 个图像则要使用 100 次 OpenGL draw call
local group = display.newNode()
for i = 1, 100 do
    local sprite = display.newSprite("#Sprite0001.png")
    group:addChild(sprite)
end

~~~

@param string image 图像文件名
@param integer capacity

@return SpriteBatchNode

@see Batch Node

]]
function display.newBatchNode(image, capacity)
    return cc.SpriteBatchNode:create(image, capacity or 100)
end

--[[--

创建并返回一个图像帧对象。

~~~ lua

display.addSpriteFrames("Sprites.plist", "Sprites.png")

-- 创建一个 Sprite
local sprite = display.newSprite("#Yes.png")

-- 创建一个图像帧
local frameNo = display.newSpriteFrame("No.png")

-- 在需要时，修改 Sprite 的显示内容
sprite:setDisplayFrame(frameNo)

~~~

@param string 图像帧名称

@return SpriteFrameCache

]]
function display.newSpriteFrame(frameName)
    local frame = sharedSpriteFrameCache:getSpriteFrame(frameName)
    if not frame then
        printError("display.newSpriteFrame() - invalid frameName %s", tostring(frameName))
    end
    return frame
end

--[[--

以特定模式创建一个包含多个图像帧对象的数组。

~~~ lua

-- 创建一个数组，包含 Walk0001.png 到 Walk0008.png 的 8 个图像帧对象
local frames = display.newFrames("Walk%04d.png", 1, 8)

-- 创建一个数组，包含 Walk0008.png 到 Walk0001.png 的 8 个图像帧对象
local frames = display.newFrames("Walk%04d.png", 1, 8, true)

~~~

@param string pattern 模式字符串
@param integer begin 起始索引
@param integer length 长度
@param boolean isReversed 是否是递减索引

@return table 图像帧数组

]]
function display.newFrames(pattern, begin, length, isReversed)
    local frames = {}
    local step = 1
    local last = begin + length - 1
    if isReversed then
        last, begin = begin, last
        step = -1
    end

    for index = begin, last, step do
        local frameName = string.format(pattern, index)
        local frame = sharedSpriteFrameCache:getSpriteFrame(frameName)
        if not frame then
            printError("display.newFrames() - invalid frame, name %s", tostring(frameName))
            return
        end

        frames[#frames + 1] = frame
    end
    return frames
end

--[[--

以包含图像帧的数组创建一个动画对象。

~~~ lua

local frames = display.newFrames("Walk%04d.png", 1, 8)
local animation = display.newAnimation(frames, 0.5 / 8) -- 0.5 秒播放 8 桢
sprite:playAnimationOnce(animation) -- 播放一次动画

~~~

@param table frames 图像帧的数组
@param number time 每一桢动画之间的间隔时间


@return Animation Animation对象

]]
function display.newAnimation(frames, time)
    local count = #frames
    -- local array = Array:create()
    -- for i = 1, count do
    --     array:addObject(frames[i])
    -- end
    time = time or 1.0 / count
    return cc.Animation:createWithSpriteFrames(frames, time)
end

--[[

以指定名字缓存创建好的动画对象，以便后续反复使用。

~~~ lua

local frames = display.newFrames("Walk%04d.png", 1, 8)
local animation = display.newAnimation(frames, 0.5 / 8) -- 0.5 秒播放 8 桢
display.setAnimationCache("Walk", animation)

-- 在需要使用 Walk 动画的地方
sprite:playAnimationOnce(display.getAnimationCache("Walk")) -- 播放一次动画

~~~

@param string name 名字
@param Animation animation 动画对象


]]
function display.setAnimationCache(name, animation)
    sharedAnimationCache:addAnimation(animation, name)
end

--[[--

取得以指定名字缓存的动画对象，如果不存在则返回 nil。

@param string name

@return Animation

]]
function display.getAnimationCache(name)
    return sharedAnimationCache:getAnimation(name)
end

--[[--

删除指定名字缓存的动画对象。

@param string name

]]
function display.removeAnimationCache(name)
    sharedAnimationCache:removeAnimationByName(name)
end

function display.removeUnusedSpriteFrames()
    sharedSpriteFrameCache:removeUnusedSpriteFrames()
    sharedTextureCache:removeUnusedTextures()
end

display.PROGRESS_TIMER_BAR = kCCProgressTimerTypeBar
display.PROGRESS_TIMER_RADIAL = kCCProgressTimerTypeRadial

function display.newProgressTimer(image, progresssType)
    if type(image) == "string" then
        image = display.newSprite(image)
    end

    local progress = cc.ProgressTimer:create(image)
    progress:setType(progresssType)
    return progress
end

-- Get a screenshot of a Node
-- @author zrong(zengrong.net)
-- Creation: 2014-04-10
-- @param node A node to print.
-- @param args
-- @return An instance of Sprite or FilteredSprite.
function display.printscreen(node, args)
	local sp = true
	local file = nil
	local filters = nil
	local filterParams = nil
	if args then
		if args.sprite ~= nil then sp = args.sprite end
		file = args.file
		filters = args.filters
		filterParams = args.filterParams
	end
	local size = node:getContentSize()
	local canvas = cc.RenderTexture:create(size.width,size.height)
	canvas:begin()
	node:visit()
	canvas:endToLua()

	if sp then
		local texture = canvas:getSprite():getTexture()
		if filters then
			sp = display.newFilteredSprite(texture, filters, filterParams)
		else
			sp = display.newSprite(texture)
		end
		sp:flipY(true)
	end
	if file and device.platform ~= "mac" then
		canvas:saveToFile(file)
	end
	return sp, file
end

return display
