
local EventProxy = class("EventProxy")

function EventProxy:ctor(eventDispatcher, view)
    self.eventDispatcher_ = eventDispatcher
    self.handles_ = {}

    if view then
        cc(view):addNodeEventListener(cc.NODE_EVENT, function(event)
            if event.name == "exit" then
                self:removeAllEventListeners()
            end
        end)
    end
end

function EventProxy:addEventListener(eventName, listener, data)
    local handle = self.eventDispatcher_:addEventListener(eventName, listener, data)
    self.handles_[#self.handles_ + 1] = {eventName, handle}
    return self
end

function EventProxy:removeEventListener(eventName, key1, key2)
    local removeHandle = self.eventDispatcher_:removeEventListener(eventName, key1, key2)
    for index, handle in ipairs(self.handles_) do
        if handle[2] == removeHandle then
            table.remove(self.handles_, index)
            break
        end
    end
    return self
end

function EventProxy:removeAllEventListenersForEvent(eventName)
    for key, handle in pairs(self.handles_) do
        if handle[1] == eventName then
            self.eventDispatcher_:removeEventListener(handle[1], handle[2])
            self.handles_[key] = nil
        end
    end
    return self
end

function EventProxy:removeAllEventListeners()
    for _, handle in ipairs(self.handles_) do
        self.eventDispatcher_:removeEventListener(handle[2])
    end
    self.handles_ = {}
    return self
end

return EventProxy
