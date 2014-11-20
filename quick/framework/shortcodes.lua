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
-- @module shortcodes

--[[--
shortcode
]]

local c = cc
local Node = c.Node

--------------------------------
-- @module Node

-- start --

--------------------------------
-- 在当前结点中加入一个子结点
-- @function [parent=#Node] add
-- @param node child 要加入的结点
-- @param number zorder 要加入结点的Z值
-- @param number tag 要加入结点的tag
-- @return Node#Node  当前结点

-- end --

function Node:add(child, zorder, tag)
    self:addChild(child, zorder or child:getLocalZOrder(), tag or child:getTag())

    return self
end

-- start --

--------------------------------
-- 把当前结点作为一个子结点加到target中
-- @function [parent=#Node] addTo
-- @param node target 想作为其子结点的结点
-- @param number zorder 当前结点的Z值
-- @param number tag 当前结点的tag
-- @return Node#Node  当前结点

-- end --

function Node:addTo(target, zorder, tag)
    target:addChild(self, zorder or self:getLocalZOrder(), tag or self:getTag())

    return self
end

-- start --

--------------------------------
-- 显示当前结点,让当前结点可显示
-- @function [parent=#Node] show
-- @return Node#Node  当前结点

-- end --

function Node:show()
    self:setVisible(true)
    return self
end

-- start --

--------------------------------
-- 隐藏当前结点,让当前结点不可显示
-- @function [parent=#Node] hide
-- @return Node#Node  当前结点

-- end --

function Node:hide()
    self:setVisible(false)
    return self
end

-- start --

--------------------------------
-- 设置当前结点的位置
-- @function [parent=#Node] pos
-- @param number x X值
-- @param number y Y值
-- @return Node#Node  当前结点

-- end --

function Node:pos(x, y)
    self:setPosition(x, y)
    return self
end

-- start --

--------------------------------
-- 设置当前结点在屏幕的中心
-- @function [parent=#Node] center
-- @return Node#Node  当前结点

-- end --

function Node:center()
    self:setPosition(display.cx, display.cy)
    return self
end

-- start --

--------------------------------
-- 设置当前结点的缩放值
-- @function [parent=#Node] scale
-- @param number scale 要缩放的值
-- @return Node#Node  当前结点

-- end --

function Node:scale(scale)
    self:setScale(scale)
    return self
end

-- start --

--------------------------------
-- 设置当前结点的旋转角度值
-- @function [parent=#Node] rotation
-- @param number r 旋转角度
-- @return Node#Node  当前结点

-- end --

function Node:rotation(r)
    self:setRotation(r)
    return self
end

-- start --

--------------------------------
-- 设置当前结点的大小
-- @function [parent=#Node] size
-- @param mixed width 宽度或cc.size表
-- @param number height 高度
-- @return Node#Node  当前结点

-- end --

function Node:size(width, height)
    if type(width) == "table" then
        self:setContentSize(width)
    else
        self:setContentSize(cc.size(width, height))
    end
    return self
end

-- start --

--------------------------------
-- 设置当前结点的透明度, 0到255,0为完全透明
-- @function [parent=#Node] opacity
-- @param number opacity 透明度
-- @return Node#Node  当前结点

-- end --

function Node:opacity(opacity)
    self:setOpacity(opacity)
    return self
end

-- start --

--------------------------------
-- 设置当前结点z值
-- @function [parent=#Node] zorder
-- @param number z z值
-- @return Node#Node  当前结点

-- end --

function Node:zorder(z)
    self:setLocalZOrder(z)
    return self
end


--------------------------------
-- @module Sprite

local Sprite = c.Sprite

Sprite.playOnce = Sprite.playAnimationOnce
Sprite.playForever = Sprite.playAnimationForever

-- start --

--------------------------------
-- 设置当前精灵的显示帧
-- @function [parent=#Sprite] displayFrame
-- @param mixed frame 要显示的图片名或图片帧的frame
-- @return Sprite#Sprite  当前精灵

-- end --

function Sprite:displayFrame(frame)
    self:setSpriteFrame(frame)
    return self
end

-- start --

--------------------------------
-- 在X方向上翻转当前精灵
-- @function [parent=#Sprite] flipX
-- @param boolean b 是否翻转
-- @return Sprite#Sprite  当前精灵

-- end --

function Sprite:flipX(b)
    self:setFlippedX(b)
    return self
end

-- start --

--------------------------------
-- 在Y方向上翻转当前精灵
-- @function [parent=#Sprite] flipY
-- @param boolean b 是否翻转
-- @return Sprite#Sprite  当前精灵

-- end --

function Sprite:flipY(b)
    self:setFlippedY(b)
    return self
end


--------------------------------
-- @module Layer

-- Layer

local Layer = c.Layer

-- start --

--------------------------------
-- 在层上注册触摸监听
-- @function [parent=#Layer] onTouch
-- @param function listener 监听函数
-- @return Layer#Layer  当前层

--[[--

在层上注册触摸监听

]]
-- end --

function Layer:onTouch(listener)
    if USE_DEPRECATED_EVENT_ARGUMENTS then
        self:addNodeEventListener(c.NODE_TOUCH_EVENT, function(event)
            return listener(event.name, event.x, event.y, event.prevX, event.prevY)
        end)
    else
        self:addNodeEventListener(c.NODE_TOUCH_EVENT, listener)
    end
    return self
end

-- start --

--------------------------------
-- 设置层的触摸是否打开
-- @function [parent=#Layer] enableTouch
-- @param boolean enabled 是否打开触摸
-- @return Layer#Layer  当前层

-- end --

function Layer:enableTouch(enabled)
    self:setTouchEnabled(enabled)
    return self
end

-- start --

--------------------------------
-- 在层上注册键盘监听
-- @function [parent=#Layer] onKeypad
-- @param function listener 监听函数
-- @return Layer#Layer  当前层

-- end --

function Layer:onKeypad(listener)
    if USE_DEPRECATED_EVENT_ARGUMENTS then
        self:addNodeEventListener(c.KEYPAD_EVENT, function(event)
            return listener(event.name)
        end)
    else
        self:addNodeEventListener(c.KEYPAD_EVENT, listener)
    end
    return self
end

-- start --

--------------------------------
-- 设置层的键盘事件是否打开
-- @function [parent=#Layer] enableKeypad
-- @param boolean enabled 是否打开键盘事件
-- @return Layer#Layer  当前层

-- end --

function Layer:enableKeypad(enabled)
    self:setKeypadEnabled(enabled)
    return self
end

-- start --

--------------------------------
-- 在层上注册重力感应监听
-- @function [parent=#Layer] onAccelerate
-- @param function listener 监听函数
-- @return Layer#Layer  当前层

-- end --

function Layer:onAccelerate(listener)
    if USE_DEPRECATED_EVENT_ARGUMENTS then
        self:addNodeEventListener(c.ACCELERATE_EVENT, function(event)
            return listener(event.x, event.y, event.z, event.timestamp)
        end)
    else
        self:addNodeEventListener(c.ACCELERATE_EVENT, listener)
    end
    return self
end

-- start --

--------------------------------
-- 设置层的重力感应事件是否打开
-- @function [parent=#Layer] enableAccelerometer
-- @param boolean enabled 是否打开加速度事件
-- @return Layer#Layer  当前层

-- end --

function Layer:enableAccelerometer(enabled)
    self:setAccelerometerEnabled(enabled)
    return self
end


-- actions

-- start --

--------------------------------
-- 停止结点的所有动作
-- @function [parent=#Node] stop
-- @return Node#Node  当前结点

-- end --

function Node:stop()
    self:stopAllActions()
    return self
end

-- start --

--------------------------------
-- 渐显动画
-- @function [parent=#Node] fadeIn
-- @param number time 渐显时间
-- @return Node#Node  当前结点

-- end --

function Node:fadeIn(time)
    self:runAction(cc.FadeIn:create(time))
    return self
end

-- start --

--------------------------------
-- 渐隐动画
-- @function [parent=#Node] fadeOut
-- @param number time 渐隐时间
-- @return Node#Node  当前结点

-- end --

function Node:fadeOut(time)
    self:runAction(cc.FadeOut:create(time))
    return self
end

-- start --

--------------------------------
-- 渐变到一个固定透明度
-- @function [parent=#Node] fadeTo
-- @param number time 渐变时间
-- @param number opacity 最终的透明度
-- @return Node#Node  当前结点

-- end --

function Node:fadeTo(time, opacity)
    self:runAction(cc.FadeTo:create(time, opacity))
    return self
end

-- start --

--------------------------------
-- 在一段时间内移动结点到特定位置
-- @function [parent=#Node] moveTo
-- @param number time 移动时间
-- @param number x 要移动到的X点
-- @param number y 要移动到的Y点
-- @return Node#Node  当前结点

-- end --

function Node:moveTo(time, x, y)
    self:runAction(cc.MoveTo:create(time, cc.p(x or self:getPositionX(), y or self:getPositionY())))
    return self
end

-- start --

--------------------------------
-- 在一段时间内移动相对位置
-- @function [parent=#Node] moveBy
-- @param number time 移动时间
-- @param number x 要移动的相对X值
-- @param number y 要移动的相对Y值
-- @return Node#Node  当前结点

-- end --

function Node:moveBy(time, x, y)
    self:runAction(cc.MoveBy:create(time, cc.p(x or 0, y or 0)))
    return self
end

-- start --

--------------------------------
-- 在一段时间内旋转的角度
-- @function [parent=#Node] rotateTo
-- @param number time 移动时间
-- @param number rotation 旋转的角度
-- @return Node#Node  当前结点

-- end --

function Node:rotateTo(time, rotation)
    self:runAction(cc.RotateTo:create(time, rotation))
    return self
end

-- start --

--------------------------------
-- 在一段时间内旋转的相对角度
-- @function [parent=#Node] rotateBy
-- @param number time 移动时间
-- @param number rotation 旋转的相对角度
-- @return Node#Node  当前结点

-- end --

function Node:rotateBy(time, rotation)
    self:runAction(cc.RotateBy:create(time, rotation))
    return self
end

-- start --

--------------------------------
-- 在一段时间内缩放
-- @function [parent=#Node] scaleTo
-- @param number time 移动时间
-- @param number scale 缩放的值
-- @return Node#Node  当前结点

-- end --

function Node:scaleTo(time, scale)
    self:runAction(cc.ScaleTo:create(time, scale))
    return self
end

-- start --

--------------------------------
-- 在一段时间内的相对缩放
-- @function [parent=#Node] scaleBy
-- @param number time 移动时间
-- @param number scale 相对缩放的值
-- @return Node#Node  当前结点

-- end --

function Node:scaleBy(time, scale)
    self:runAction(cc.ScaleBy:create(time, scale))
    return self
end

-- start --

--------------------------------
-- 在一段时间内倾斜的大小
-- @function [parent=#Node] skewTo
-- @param number time 移动时间
-- @param number sx 倾斜的X值
-- @param number sy 倾斜的Y值
-- @return Node#Node  当前结点

-- end --

function Node:skewTo(time, sx, sy)
    self:runAction(cc.SkewTo:create(time, sx or self:getSkewX(), sy or self:getSkewY()))
    return self
end

-- start --

--------------------------------
-- 在一段时间内倾斜的相对大小
-- @function [parent=#Node] skewBy
-- @param number time 移动时间
-- @param number sx 倾斜的相对X值
-- @param number sy 倾斜的相对Y值
-- @return Node#Node  当前结点

-- end --

function Node:skewBy(time, sx, sy)
    self:runAction(cc.SkewBy:create(time, sx or 0, sy or 0))
    return self
end

-- start --

--------------------------------
-- 在一段时间内染色
-- @function [parent=#Node] tintTo
-- @param number time 移动时间
-- @param number r 染色的R值
-- @param number g 染色的G值
-- @param number b 染色的B值
-- @return Node#Node  当前结点

-- end --

function Node:tintTo(time, r, g, b)
    self:runAction(cc.TintTo:create(time, r or 0, g or 0, b or 0))
    return self
end


-- start --

--------------------------------
-- 在一段时间内相对染色
-- @function [parent=#Node] tintBy
-- @param number time 移动时间
-- @param number r 染色的相对R值
-- @param number g 染色的相对G值
-- @param number b 染色的相对B值
-- @return Node#Node  当前结点

-- end --

function Node:tintBy(time, r, g, b)
    self:runAction(cc.TintBy:create(time, r or 0, g or 0, b or 0))
    return self
end
