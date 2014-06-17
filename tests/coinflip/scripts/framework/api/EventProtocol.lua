
local EventProtocol = {}

function EventProtocol.extend(object)
    PRINT_DEPRECATED("module api.EventProtocol is deprecated, please use cc.components.behavior.EventProtocol")

    object.listeners_ = {}
    object.listenerHandleIndex_ = 0

    function object:addEventListener(eventName, listener, target)
        eventName = string.upper(eventName)
        if object.listeners_[eventName] == nil then
            object.listeners_[eventName] = {}
        end

        local ttarget = type(target)
        if ttarget == "table" or ttarget == "userdata" then
            PRINT_DEPRECATED("api.EventProtocol.addEventListener(eventName, listener, target) is deprecated, please use api.EventProtocol.addEventListener(eventName, handler(target, listener))")
            listener = handler(target, listener)
            tag = ""
        end

        object.listenerHandleIndex_ = object.listenerHandleIndex_ + 1
        local handle = string.format("HANDLE_%d", object.listenerHandleIndex_)
        object.listeners_[eventName][handle] = listener
        return handle
    end

    function object:dispatchEvent(event)
        event.name = string.upper(event.name)
        local eventName = event.name
        if object.listeners_[eventName] == nil then return end
        event.target = object
        for handle, listener in pairs(object.listeners_[eventName]) do
            local ret = listener(event, a)
            if ret == false then
                break
            elseif ret == "__REMOVE__" then
                object.listeners_[eventName][handle] = nil
            end
        end
    end

    function object:removeEventListener(eventName, key)
        eventName = string.upper(eventName)
        if object.listeners_[eventName] == nil then return end

        for handle, listener in pairs(object.listeners_[eventName]) do
            if key == handle or key == listener then
                object.listeners_[eventName][handle] = nil
                break
            end
        end
    end

    function object:removeAllEventListenersForEvent(eventName)
        object.listeners_[string.upper(eventName)] = nil
    end

    function object:removeAllEventListeners()
        object.listeners_ = {}
    end

    return object
end

return EventProtocol
