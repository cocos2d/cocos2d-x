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
c.TouchesAllAtOnce              = kCCTouchesAllAtOnce
c.TouchesOneByOne               = kCCTouchesOneByOne
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
        CCDelayTime:create(interval),
        CCCallFunc:create(callback),
    })
    local action = CCRepeatForever:create(seq)
    self:runAction(action)
    return action
end

function Node:performWithDelay(callback, delay)
    local action = transition.sequence({
        CCDelayTime:create(delay),
        CCCallFunc:create(callback),
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

function Node:isTouchEnabled()
    return self._isTouchEnabled_
end

function Node:setTouchEnabled( isEnable )
    if self._isTouchEnabled_ and self._isTouchEnabled_==isEnable then return end
    self._isTouchEnabled_ = isEnable

    local evt = c.NODE_TOUCH_EVENT
    if self._scriptEventListeners_ and self._scriptEventListeners_[evt] then
        local eventDispatcher = self:getEventDispatcher()

        local regFunc
        if isEnable then
            regFunc = function ( regHanler, obj )
                eventDispatcher:addEventListenerWithSceneGraphPriority(regHanler, obj)
            end
        else
            regFunc = function ( regHanler )
                eventDispatcher:removeEventListener(regHanler)
            end
        end
        
        for i,v in ipairs(self._scriptEventListeners_[evt]) do
            if v.regHanler and v.mode==self._TouchMode_ then
                regFunc(v.regHanler, self)
            end
        end
    end
end

function Node:setTouchSwallowEnabled( isEnable )
    if self._isTouchSwallowEnabled_ and self._isTouchSwallowEnabled_==isEnable then return end
    self._isTouchSwallowEnabled_ = isEnable
    local evt = c.NODE_TOUCH_EVENT
    if self._scriptEventListeners_ and self._scriptEventListeners_[evt] then
        for i,v in ipairs(self._scriptEventListeners_[evt]) do
            if v.regHanler then v.regHanler:setSwallowTouches(isEnable) end
        end
    end
end

function Node:setTouchMode(mode)
    if self._TouchMode_ ~= mode then
      self._TouchMode_ = mode
      if not self._isTouchEnabled_ then return end
      self:setTouchEnabled(false)   --unregister old listeners
      self:setTouchEnabled(true)
    end
end

function Node:getTouchMode()
    return self._TouchMode_
end

function Node:isSwallowsTouches()
    return self._isTouchSwallowEnabled_
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

-- function Node.handleUpdate(dt)
--     -- print("----Node:handleUpdate   "..dt)
--     NodeEventDispatcher()
-- end

function Node:addNodeEventListener( evt, hdl, tag, priority )
    -- print("----Node:addNodeEventListener")
    priority = priority or 0
    self._scriptEventListeners_ = self._scriptEventListeners_ or {}
    local idx = self._nextScriptEventHandleIndex_ or 0
    idx = idx + 1
    self._nextScriptEventHandleIndex_ = idx
    self._scriptEventListeners_[evt] = self._scriptEventListeners_[evt] or {}
    local lis = {
            index_ = idx,
            listener_ = hdl,
            tag_ = tag,
            priority_ = priority,
            enable_ = true,
        }
    if evt==c.NODE_ENTER_FRAME_EVENT then
        self._scriptEventListeners_[evt][1] = lis
    else
        table.insert(self._scriptEventListeners_[evt], lis)
    end

    if evt==c.NODE_ENTER_FRAME_EVENT then
        local func = tolua.getcfunction(self, "scheduleUpdateWithPriorityLua")
        -- print("=============func:")
        if func then 
            local listener = function (dt)
                NodeEventDispatcher(self, c.NODE_ENTER_FRAME_EVENT, dt)
            end
            func(self, listener, priority) 
        end
    elseif evt==c.NODE_TOUCH_EVENT then
        local onTouchBegan = function (touch, event)
            return NodeEventDispatcher(event:getCurrentTarget(), c.NODE_TOUCH_EVENT, {touch, event, "began"})
        end

        local onTouchMoved = function (touch, event)
            return NodeEventDispatcher(event:getCurrentTarget(), c.NODE_TOUCH_EVENT, {touch, event, "moved"})
        end

        local onTouchEnded = function (touch, event)
            return NodeEventDispatcher(event:getCurrentTarget(), c.NODE_TOUCH_EVENT, {touch, event, "ended"})
        end

        self._isTouchSwallowEnabled_ = self._isTouchSwallowEnabled_ or true
        local isSwallow = self._isTouchSwallowEnabled_
        local listener
        self._TouchMode_ = self._TouchMode_ or c.EVENT_TOUCH_ONE_BY_ONE
        local mode = self._TouchMode_
        if mode==c.TOUCH_MODE_ALL_AT_ONCE then
            -- print("====TOUCH_MODE_ALL_AT_ONCE listener")
            listener = cc.EventListenerTouchAllAtOnce:create()
            listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
            -- listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
            listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCHES_ENDED )
        else
            -- print("====EVENT_TOUCH_ONE_BY_ONE listener")
            listener = cc.EventListenerTouchOneByOne:create()
            listener:setSwallowTouches(isSwallow)
            listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
            listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
            listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
        end
        local eventDispatcher = self:getEventDispatcher()
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
        lis.regHanler = listener
        lis.regHanler:retain()
        lis.mode = mode
        if nil==self._isTouchEnabled_ then self._isTouchEnabled_=true end
    end

    return self._nextScriptEventHandleIndex_
end

function Node:removeNodeEventListenersByEvent( evt )
    if self._scriptEventListeners_ and self._scriptEventListeners_[evt] then
        local eventDispatcher = self:getEventDispatcher()
        if evt==c.NODE_TOUCH_EVENT then
            for i,v in ipairs(self._scriptEventListeners_[evt]) do
                    if v.regHanler then
                        eventDispatcher:removeEventListener(v.regHanler)
                        v.regHanler:release()
                    end
            end
        elseif evt==c.NODE_ENTER_FRAME_EVENT then
            self:unscheduleUpdate()
        end

        self._scriptEventListeners_[evt] = nil
    end
end

function Node:removeAllNodeEventListeners()
    self:removeNodeEventListenersByEvent(c.NODE_ENTER_FRAME_EVENT)
    self:removeNodeEventListenersByEvent(c.NODE_TOUCH_EVENT)
end

function NodeEventDispatcher( obj, idx, data )
    -- print("-----Entry NodeEventDispatcher: "..idx)
    local flagNodeCleanup = false
    local event
    if idx==c.NODE_EVENT then
        event = { name=data }
        if data=="cleanup" then
            flagNodeCleanup = true
        end
    elseif idx==c.NODE_ENTER_FRAME_EVENT then
        event = data
    elseif idx==c.NODE_TOUCH_EVENT then
        -- print("-----c.NODE_TOUCH_EVENT ")
        if not obj._isTouchEnabled_ then return false end
        local touch = data[1]
        local evt = data[2]
        local ename = data[3]

        if obj._TouchMode_==c.EVENT_TOUCH_ONE_BY_ONE then
            -- print("-----c.EVENT_TOUCH_ONE_BY_ONE ")
            local p1 = touch:getLocation()
            local p2 = touch:getPreviousLocation()
            local rc = obj:getCascadeBoundingBox()
            local rect = cc.rect(rc.x, rc.y, rc.width, rc.height)
            if not obj:getCascadeBoundingBox():containsPoint(p1) then
                return false
            end

            event = {
                mode = c.EVENT_TOUCH_ONE_BY_ONE,
                name = ename,
                x = p1.x,
                y = p1.y,
                prevX = p2.x,
                prevY = p2.y,
            }
        else
            -- print("-----c.TOUCH_MODE_ALL_AT_ONCE ")
            -- dump(touch)
            -- if touch[1] then
            --     local p1 = touch[1]:getLocation()
            --     local rc = obj:getCascadeBoundingBox()
            --     local rect = cc.rect(rc.x, rc.y, rc.width, rc.height)
            --     if not obj:getCascadeBoundingBox():containsPoint(p1) then
            --         return false
            --     end
            -- end
            local pts = {}
            for i,v in ipairs(touch) do
                local pt = {}
                local p = v:getLocation()
                pt.x = p.x
                pt.y = p.y
                pt.id = v:getId()
                pts[#pts+1] = pt
            end

            event = {
                mode = c.TOUCH_MODE_ALL_AT_ONCE,
                name = ename,
                points = pts,
            }
        end
    end

    local rnval = false
    if obj._scriptEventListeners_ and obj._scriptEventListeners_[idx] then
        for i,v in ipairs(obj._scriptEventListeners_[idx]) do
            rnval = rnval or v.listener_(event)
        end
    end

    if flagNodeCleanup then obj:removeAllNodeEventListeners() end

    return rnval
end

