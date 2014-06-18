
local c = cc
local Layer = c.Layer

function Layer:addKeypadEventListener(listener)
    PRINT_DEPRECATED("Layer.addKeypadEventListener() is deprecated, please use Layer.addNodeEventListener()")
    self:addNodeEventListener(c.KEYPAD_EVENT, function(event)
        listener(event.key)
    end)
end

function Layer:registerScriptKeypadHandler(listener)
    PRINT_DEPRECATED("Layer.registerScriptKeypadHandler() is deprecated, please use Layer.addNodeEventListener()")
    self:addNodeEventListener(c.KEYPAD_EVENT, function(event)
        listener(event.key)
    end)
end

function Layer:addAccelerateEventListener(listener)
    PRINT_DEPRECATED("Layer.addAccelerateEventListener() is deprecated, please use Layer.addNodeEventListener()")
    self:addNodeEventListener(c.ACCELERATE_EVENT, function(event)
        listener(event.x, event.y, event.z, event.timestamp)
    end)
end

function Layer:registerScriptAccelerateHandler(listener)
    PRINT_DEPRECATED("Layer.registerScriptAccelerateHandler() is deprecated, please use Layer.addNodeEventListener()")
    self:addNodeEventListener(c.ACCELERATE_EVENT, function(event)
        listener(event.x, event.y, event.z, event.timestamp)
    end)
end

function Layer:isTouchEnabled()
    return cc.Node.isTouchEnabled(self)
end

function Layer:setTouchEnabled( isEnable )
    return cc.Node.setTouchEnabled(self, isEnable)
end

function Layer:setTouchMode( mode )
    return cc.Node.setTouchMode(self, mode)
end

function Layer:setSwallowsTouches( isEnable )
    return cc.Node.setTouchSwallowEnabled(self, isEnable)
end

function Layer:getTouchMode()
    return cc.Node.getTouchMode(self)
end

function Layer:isSwallowsTouches()
    return cc.Node.isSwallowsTouches(self)
end