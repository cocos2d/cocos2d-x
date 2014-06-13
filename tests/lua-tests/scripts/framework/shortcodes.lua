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

]]

local c = cc
local Node = c.Node

-- Node

function Node:add(child, zorder, tag)
    self:addChild(child, zorder or 0, tag or 0)
    return self
end

function Node:addTo(target, zorder, tag)
    target:addChild(self, zorder or 0, tag or 0)
    return self
end

function Node:show()
    self:setVisible(true)
    return self
end

function Node:hide()
    self:setVisible(false)
    return self
end

function Node:pos(x, y)
    self:setPosition(x, y)
    return self
end

function Node:center()
    self:setPosition(display.cx, display.cy)
    return self
end

function Node:scale(scale)
    self:setScale(scale)
    return self
end

function Node:rotation(r)
    self:setRotation(r)
    return self
end

function Node:size(width, height)
    if type(width) == "userdata" then
        self:setContentSize(width)
    else
        self:setContentSize(CCSize(width, height))
    end
    return self
end

function Node:opacity(opacity)
    self:setOpacity(opacity)
    return self
end

function Node:zorder(z)
    self:setZOrder(z)
    return self
end


-- Sprite

local Sprite = c.Sprite

Sprite.playOnce = Sprite.playAnimationOnce
Sprite.playForever = Sprite.playAnimationForever

function Sprite:displayFrame(frame, index)
    if type(frame) == "string" then
        self:setDisplayFrame(frame, index or 0)
    else
        self:setDisplayFrame(frame)
    end
    return self
end

function Sprite:flipX(b)
    self:setFlipX(b)
    return self
end

function Sprite:flipY(b)
    self:setFlipY(b)
    return self
end


-- Layer

local Layer = c.Layer

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

function Layer:enableTouch(enabled)
    self:setTouchEnabled(enabled)
    return self
end

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

function Layer:enableKeypad(enabled)
    self:setKeypadEnabled(enabled)
    return self
end

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

function Layer:enableAccelerometer(enabled)
    self:setAccelerometerEnabled(enabled)
    return self
end


-- actions

function Node:stop()
    self:stopAllActions()
    return self
end

function Node:fadeIn(time)
    self:runAction(CCFadeIn:create(time))
    return self
end

function Node:fadeOut(time)
    self:runAction(CCFadeOut:create(time))
    return self
end

function Node:fadeTo(time, opacity)
    self:runAction(CCFadeTo:create(time, opacity))
    return self
end

function Node:moveTo(time, x, y)
    self:runAction(CCMoveTo:create(time, CCPoint(x or self:getPositionX(), y or self:getPositionY())))
    return self
end

function Node:moveBy(time, x, y)
    self:runAction(CCMoveBy:create(time, CCPoint(x or 0, y or 0)))
    return self
end

function Node:rotateTo(time, rotation)
    self:runAction(CCRotateTo:create(time, rotation))
    return self
end

function Node:rotateBy(time, rotation)
    self:runAction(CCRotateBy:create(time, rotation))
    return self
end

function Node:scaleTo(time, scale)
    self:runAction(CCScaleTo:create(time, scale))
    return self
end

function Node:scaleBy(time, scale)
    self:runAction(CCScaleBy:create(time, scale))
    return self
end

function Node:skewTo(time, sx, sy)
    self:runAction(CCSkewTo:create(time, sx or self:getSkewX(), sy or self:getSkewY()))
end

function Node:skewBy(time, sx, sy)
    self:runAction(CCSkewBy:create(time, sx or 0, sy or 0))
end

function Node:tintTo(time, r, g, b)
    self:runAction(CCTintTo:create(time, r or 0, g or 0, b or 0))
    return self
end

function Node:tintBy(time, r, g, b)
    self:runAction(CCTintBy:create(time, r or 0, g or 0, b or 0))
    return self
end
