
local WebSockets = class("WebSockets")

WebSockets.TEXT_MESSAGE = 0
WebSockets.BINARY_MESSAGE = 1
WebSockets.BINARY_ARRAY_MESSAGE = 2

WebSockets.OPEN_EVENT    = "open"
WebSockets.MESSAGE_EVENT = "message"
WebSockets.CLOSE_EVENT   = "close"
WebSockets.ERROR_EVENT   = "error"

function WebSockets:ctor(url)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.socket = cc.WebSocket:create(url)

    if self.socket then
        self.socket:registerScriptHandler(handler(self, self.onOpen_), cc.WEBSOCKET_OPEN)
        self.socket:registerScriptHandler(handler(self, self.onMessage_), cc.WEBSOCKET_MESSAGE)
        self.socket:registerScriptHandler(handler(self, self.onClose_), cc.WEBSOCKET_CLOSE)
        self.socket:registerScriptHandler(handler(self, self.onError_), cc.WEBSOCKET_ERROR)
    end
end

function WebSockets:isReady()
    return self.socket and self.socket:getReadyState() == cc.WEBSOCKET_STATE_OPEN
end

function WebSockets:send(data, messageType)
    if not self:isReady() then
        printError("WebSockets:send() - socket is't ready")
        return false
    end

    messageType = checkint(messageType)
    self.messageType = messageType
    if messageType == WebSockets.TEXT_MESSAGE then
        self.socket:sendString(tostring(data))
    elseif messageType == WebSockets.BINARY_ARRAY_MESSAGE then
        data = checktable(data)
        self.socket:sendString(data, table.nums(data))
    else
        self.socket:sendString(tostring(data))
    end
    return true
end

function WebSockets:close()
    if self.socket then
        self.socket:close()
        self.socket = nil
    end
    self:removeAllEventListeners()
end

function WebSockets:onOpen_()
    self:dispatchEvent({name = WebSockets.OPEN_EVENT})
end

function WebSockets:onMessage_(message)
    local params = {
        name = WebSockets.MESSAGE_EVENT,
        message = message,
        messageType = self.messageType
    }

    self:dispatchEvent(params)
end

function WebSockets:onClose_()
    self:dispatchEvent({name = WebSockets.CLOSE_EVENT})
    self:close()
end

function WebSockets:onError_(error)
    self:dispatchEvent({name = WebSockets.ERROR_EVENT, error = error})
end

return WebSockets
