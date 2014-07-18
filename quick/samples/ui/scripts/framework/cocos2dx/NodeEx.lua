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

针对 cc.Node 的扩展

]]

local c = cc
local Node = c.Node

-- touch
c.TouchesAllAtOnce              = cc.TOUCHES_ALL_AT_ONCE
c.TouchesOneByOne               = cc.TOUCHES_ONE_BY_ONE
c.TOUCH_MODE_ALL_AT_ONCE        = c.TouchesAllAtOnce
c.TOUCH_MODE_ONE_BY_ONE         = c.TouchesOneByOne

local function isPointIn( rc, pt )
    local rect = cc.rect(rc.x, rc.y, rc.width, rc.height)
    return cc.rectContainsPoint(rect, pt)
end

function Node:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
    return self
end

function Node:schedule(callback, interval)
    local seq = transition.sequence({
        cc.DelayTime:create(interval),
        cc.CallFunc:create(callback),
    })
    local action = cc.RepeatForever:create(seq)
    self:runAction(action)
    return action
end

function Node:performWithDelay(callback, delay)
    local action = transition.sequence({
        cc.DelayTime:create(delay),
        cc.CallFunc:create(callback),
    })
    self:runAction(action)
    return action
end

function Node:getCascadeBoundingBox()
    local rc
    local func = tolua.getcfunction(self, "getCascadeBoundingBox")
    if func then
        rc = func(self)
    end

    rc.origin = {x=rc.x, y=rc.y}
    rc.size = {width=rc.width, height=rc.height}
    rc.containsPoint = isPointIn
    return rc
end

function Node:removeSelf()
    -- body
end

function Node:onEnter()
end

function Node:onExit()
end

function Node:onEnterTransitionFinish()
end

function Node:onExitTransitionStart()
end

function Node:onCleanup()
end

function Node:setNodeEventEnabled(enabled, listener)
    if enabled then
        if self.__node_event_handle__ then
            self:removeNodeEventListener(self.__node_event_handle__)
            self.__node_event_handle__ = nil
        end

        if not listener then
            listener = function(event)
                local name = event.name
                if name == "enter" then
                    self:onEnter()
                elseif name == "exit" then
                    self:onExit()
                elseif name == "enterTransitionFinish" then
                    self:onEnterTransitionFinish()
                elseif name == "exitTransitionStart" then
                    self:onExitTransitionStart()
                elseif name == "cleanup" then
                    self:onCleanup()
                end
            end
        end
        self.__node_event_handle__ = self:addNodeEventListener(c.NODE_EVENT, listener)
    elseif self.__node_event_handle__ then
        self:removeNodeEventListener(self.__node_event_handle__)
        self.__node_event_handle__ = nil
    end
    return self
end

function Node:removeScriptEventListenersByEvent(event)
    PRINT_DEPRECATED("Node.removeScriptEventListenersByEvent() is deprecated, please use c.node):removeNodeEventListenersByEvent()")
    self:removeNodeEventListenersByEvent(event)
end

function Node:registerScriptHandler(listener)
    PRINT_DEPRECATED("Node.registerScriptHandler() is deprecated, please use Node.addNodeEventListener()")
    return self:addNodeEventListener(c.NODE_EVENT, function(event)
        listener(event.name)
    end)
end

function Node:unregisterScriptHandler()
    PRINT_DEPRECATED("Node.unregisterScriptHandler() is deprecated, please use Node.removeAllNodeEventListeners()")
    return self:removeAllNodeEventListeners()
end

function Node:addTouchEventListener(handler)
    PRINT_DEPRECATED("Node.addTouchEventListener() is deprecated, please use Node.addNodeEventListener()")
    return self:addNodeEventListener(c.NODE_TOUCH_EVENT, function(event)
        return handler(event.name, event.x, event.y, event.prevX, event.prevY)
    end)
end

function Node:registerScriptTouchHandler(handler, isMultiTouches)
    PRINT_DEPRECATED("Node.registerScriptTouchHandler() is deprecated, please use Node.addNodeEventListener()")
    if isMultiTouches then
        self:setTouchMode(c.TOUCH_MODE_ALL_AT_ONCE)
    else
        self:setTouchMode(c.TOUCH_MODE_ONE_BY_ONE)
    end
    return self:addNodeEventListener(c.NODE_TOUCH_EVENT, function(event)
        if event.mode == c.TOUCH_MODE_ALL_AT_ONCE then
            local points = {}
            for id, p in pairs(event.points) do
                points[#points + 1] = p.x
                points[#points + 1] = p.y
                points[#points + 1] = p.id
            end
            return handler(event.name, points)
        else
            return handler(event.name, event.x, event.y, event.prevX, event.prevY)
        end
    end)
end

function Node:scheduleUpdate(handler)
    PRINT_DEPRECATED("Node.scheduleUpdate(handler) is deprecated, please use Node.addNodeEventListener()")
    if not handler then
        handler = function(dt) self:onEnterFrame(dt) end
    end
    self:addNodeEventListener(c.NODE_ENTER_FRAME_EVENT, handler)
end

function Node:scheduleUpdateWithPriorityLua(handler)
    PRINT_DEPRECATED("Node.scheduleUpdateWithPriorityLua() is deprecated, please use Node.addNodeEventListener()")
    self:addNodeEventListener(c.NODE_ENTER_FRAME_EVENT, handler)
end

function Node:setTouchPriority()
    PRINT_DEPRECATED("Node.setTouchPriority() is deprecated, remove it")
end

function Node:setKeypadEnabled(enable)
    print("···Node:setKeypadEnabled")
    self:setKeyboardEnabled(enable)
end

function Node:isKeypadEnabled()
    return self:isKeyboardEnabled()
end