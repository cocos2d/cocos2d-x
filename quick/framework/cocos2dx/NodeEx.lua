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

local flagNodeTouchInCocos = false
if Node.removeTouchEvent then flagNodeTouchInCocos = true end

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

--[[--

测试一个点是否在当前结点区域中

@param tabel point cc.p的点位置,世界坐标
@param boolean bCascade 是否用结点的所有子结点共同区域计算还是只用本身的区域

@return boolean 是否在结点区域中

]]
function Node:hitTest(point, bCascade)
    local nsp = self:convertToNodeSpace(point)
    local rect
    if bCascade then
        rect = self:getCascadeBoundingBox()
    else
        rect = self:getBoundingBox()
    end

    if cc.rectContainsPoint(rect, nsp) then
        return true
    end
    return false
end

function Node:removeSelf()
    self:removeFromParent(true)
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

function Node:setTouchEnabled(enable)
    local func = tolua.getcfunction(self, "setTouchEnabled")
    func(self, enable)
    if not flagNodeTouchInCocos then
        return self
    end
    
    self:setBaseNodeEventListener()
    return self
end

function Node:setTouchMode(mode)
    local func = tolua.getcfunction(self, "setTouchMode")
    func(self, mode)
    if not flagNodeTouchInCocos then
        return self
    end
    
    self:setBaseNodeEventListener()
    return self
end

function Node:setTouchSwallowEnabled(enable)
    local func = tolua.getcfunction(self, "setTouchSwallowEnabled")
    func(self, enable)
    if not flagNodeTouchInCocos then
        return self
    end
    
    self:setBaseNodeEventListener()
    return self
end

function Node:setTouchCaptureEnabled(enable)
    local func = tolua.getcfunction(self, "setTouchCaptureEnabled")
    func(self, enable)
    if not flagNodeTouchInCocos then
        return self
    end
    
    self:setBaseNodeEventListener()
    return self
end

function Node:setKeypadEnabled(enable)
    if not flagNodeTouchInCocos then
        self:setKeyboardEnabled(enable)
        return self
    end
    
    _enable = self._keyboardEnabled or false
    if enable == _enable then
        return self
    end

    self._keyboardEnabled = enable

    if self.__key_event_handle__ then
        local eventDispatcher = self:getEventDispatcher()
        eventDispatcher:removeEventListener(self.__key_event_handle__)
        self.__key_event_handle__ = nil
    end

    if enable then
        local onKeyPressed = function ( keycode, event )
            return self:EventDispatcher(c.KEYPAD_EVENT, {keycode, event, "Pressed"})
        end

        local onKeyReleased = function ( keycode, event )
            return self:EventDispatcher(c.KEYPAD_EVENT, {keycode, event, "Released"})
        end

        local listener = cc.EventListenerKeyboard:create()
        listener:registerScriptHandler(onKeyPressed, cc.Handler.EVENT_KEYBOARD_PRESSED )
        listener:registerScriptHandler(onKeyReleased, cc.Handler.EVENT_KEYBOARD_RELEASED )
        local eventDispatcher = self:getEventDispatcher()
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
        self.__key_event_handle__ = listener
    end

    return self
end

function Node:isKeypadEnabled()
    if not flagNodeTouchInCocos then
        return self:isKeyboardEnabled()
    end
    enable = self._keyboardEnabled or false
    return enable
end

function Node:scheduleUpdate()
    if not flagNodeTouchInCocos then
        tolua.getcfunction(self, "scheduleUpdate")(self)
        return self
    end

    local listener = function (dt)
        self:EventDispatcher(c.NODE_ENTER_FRAME_EVENT, dt)
    end

    self:scheduleUpdateWithPriorityLua(listener, 0) 
    return self
end

function Node:setBaseNodeEventListener()
    if self._baseNodeEventListener_ then return end
    self._baseNodeEventListener_ = function(evt)
            self:EventDispatcher(c.NODE_EVENT, evt)
    end
    self:registerScriptHandler(self._baseNodeEventListener_)
end

function Node:addNodeEventListener( evt, hdl, tag, priority )
    if not flagNodeTouchInCocos then
        return tolua.getcfunction(self, "addNodeEventListener")(self, evt, hdl, tag, priority)
    end

    priority = priority or 0

    if not self._scriptEventListeners_ then
        self._scriptEventListeners_ = {}
        self:setBaseNodeEventListener()
    end
    local luaListeners_ = self._scriptEventListeners_

    local idx = self._nextScriptEventHandleIndex_ or 0
    idx = idx + 1
    self._nextScriptEventHandleIndex_ = idx

    if not luaListeners_[evt] then
        luaListeners_[evt] = {}
    end
    local eventListeners_ = luaListeners_[evt]
    local lis = {
            index_ = idx,
            listener_ = hdl,
            tag_ = tag,
            priority_ = priority,
            enable_ = true,
            removed_ = false,
        }
    if evt==c.NODE_ENTER_FRAME_EVENT then
        eventListeners_[1] = lis
    else
        table.insert(eventListeners_, lis)
    end

    return self._nextScriptEventHandleIndex_
end

function Node:removeNodeEventListener(listener)
    if not flagNodeTouchInCocos then
        local func = tolua.getcfunction(self, "removeNodeEventListener")
        if func then return func(self, listener) end
        return
    end

    if not self._scriptEventListeners_ then return end

    for evt,liss in pairs(self._scriptEventListeners_) do
        for i,v in ipairs(liss) do
            if v.index_==listener then
                table.remove(liss, i)
                if #liss==0 then
                    self:removeNodeEventListenersByEvent(evt)
                end
                return
            end
        end
    end
end

function Node:removeNodeEventListenersByEvent( evt )
    if not flagNodeTouchInCocos then
        tolua.getcfunction(self, "removeNodeEventListenersByEvent")(self, evt)
        return
    end

    if self._scriptEventListeners_ and self._scriptEventListeners_[evt] then
        if evt==c.KEYPAD_EVENT then
            self:setKeypadEnabled(false)
        elseif evt==c.NODE_ENTER_FRAME_EVENT then
            self:unscheduleUpdate()
        elseif evt==c.NODE_TOUCH_EVENT then
            self:removeTouchEvent()
        elseif evt==c.NODE_TOUCH_CAPTURE_EVENT then
            self:removeTouchEvent()
        end

        self._scriptEventListeners_[evt] = nil
    end
end

function Node:removeAllNodeEventListeners()
    if not flagNodeTouchInCocos then
        tolua.getcfunction(self, "removeAllNodeEventListeners")(self)
        return
    end

    self:removeNodeEventListenersByEvent(c.NODE_EVENT)
    self:removeNodeEventListenersByEvent(c.NODE_ENTER_FRAME_EVENT)
    self:removeNodeEventListenersByEvent(c.NODE_TOUCH_EVENT)
    self:removeNodeEventListenersByEvent(c.NODE_TOUCH_CAPTURE_EVENT)
    self:removeNodeEventListenersByEvent(c.KEYPAD_EVENT)
end

local function KeypadEventCodeConvert( code )
    local key
    if code==6 then
        key = "back"
    elseif code==16 then
        key = "menu"
    else
        key = tostring(code)
    end
    return key
end

function Node:EventDispatcher( idx, data )
    -- if idx~=1 then
    --     print("-----Entry Node:EventDispatcher: "..idx)
    -- end
    local obj = self
    local flagNodeCleanup = false
    local event
    local touch_event = nil
    if idx==c.NODE_EVENT then
        event = { name=data }
        if data=="cleanup" then
            flagNodeCleanup = true
        end
    elseif idx==c.NODE_ENTER_FRAME_EVENT then
        event = data
    elseif idx==c.KEYPAD_EVENT then
        local code = data[1]
        -- local evt = data[2]
        local ename = data[3]
        if ename~='Released' then return true end
        event = { code=code, key=KeypadEventCodeConvert(code), }
    else
        event = data
        -- dump(event)
        touch_event = event
    end

    local rnval = false
    if idx==cc.NODE_TOUCH_CAPTURE_EVENT then
        rnval = true
    end
    local flagNeedClean = false
    local listener
    if obj._scriptEventListeners_ then
        listener = obj._scriptEventListeners_[idx]
    end
    if listener then
        for i,v in ipairs(listener) do
            if v.removed_ then
                flagNeedClean = true
            else
                if touch_event and touch_event.name=="began" then
                    v.enable_ = true
                end

                if v.enable_ then
                    local listenerRet = v.listener_(event)
                    if not listenerRet then
                        if idx==cc.NODE_TOUCH_CAPTURE_EVENT then
                            local evtname  = event.name
                            if (evtname=="began") or (evtname=="moved") then
                                rnval = false
                            end
                        elseif idx==cc.NODE_TOUCH_EVENT then
                            if event.name=="began" then
                                v.enable_ = false
                            end
                            rnval = rnval or listenerRet
                        else
                            rnval = rnval or listenerRet
                        end
                    end 
                end
            end
        end
    end

    if flagNodeCleanup then
        obj:setTouchEnabled(false)
        obj:removeAllNodeEventListeners()
        obj:removeTouchEvent()
        obj:unregisterScriptHandler()
    end

    return rnval
end

-- clone related

function Node:clone()
    local cloneNode = self:createCloneInstance_()

    cloneNode:copyProperties_(self)
    cloneNode:copySpecialPeerVal_(self)
    cloneNode:copyClonedWidgetChildren_(self)

    return cloneNode
end

function Node:createCloneInstance_()
    local nodeType = tolua.type(self)
    local cloneNode

    if "cc.Sprite" == nodeType then
        cloneNode = cc.Sprite:create()
    elseif "ccui.Scale9Sprite" == nodeType then
        cloneNode = ccui.Scale9Sprite:create()
    elseif "cc.LayerColor" == nodeType then
        local clr = self:getColor()
        clr.a = self:getOpacity()
        cloneNode = cc.LayerColor:create(clr)
    else
        cloneNode = display.newNode()
        if "cc.Node" ~= nodeType then
            print("WARING! treat " .. nodeType .. " as cc.Node")
        end
    end

    return cloneNode
end

function Node:copyClonedWidgetChildren_(node)
    local children = node:getChildren()
    if not children or 0 == #children then
        return
    end

    for i, child in ipairs(children) do
        local cloneChild = child:clone()
        if cloneChild then
            self:addChild(cloneChild)
        end
    end
end

function Node:copySpecialProperties_(node)
    local nodeType = tolua.type(self)

    if "cc.Sprite" == nodeType then
        self:setSpriteFrame(node:getSpriteFrame())
    elseif "ccui.Scale9Sprite" == nodeType then
        self:setSpriteFrame(node:getSprite():getSpriteFrame())
    elseif "cc.LayerColor" == nodeType then
        self:setTouchEnabled(false)
    end

    -- copy peer
    local peer = tolua.getpeer(node)
    if peer then
        local clonePeer = clone(peer)
        tolua.setpeer(self, clonePeer)
    end
    
end

function Node:copyProperties_(node)
    self:setVisible(node:isVisible())
    self:setTouchEnabled(node:isTouchEnabled())
    self:setLocalZOrder(node:getLocalZOrder())
    self:setTag(node:getTag())
    self:setName(node:getName())
    self:setContentSize(node:getContentSize())
    self:setPosition(node:getPosition())
    self:setAnchorPoint(node:getAnchorPoint())
    self:setScaleX(node:getScaleX())
    self:setScaleY(node:getScaleY())
    self:setRotation(node:getRotation())
    self:setRotationSkewX(node:getRotationSkewX())
    self:setRotationSkewY(node:getRotationSkewY())
    if self.isFlippedX and node.isFlippedX then
        self:setFlippedX(node:isFlippedX())
        self:setFlippedY(node:isFlippedY())
    end
    self:setColor(node:getColor())
    self:setOpacity(node:getOpacity())

    self:copySpecialProperties_(node)
end

-- 拷贝特殊的peer值
function Node:copySpecialPeerVal_(node)
    if node.name then
        self.name = node.name
    end
end
