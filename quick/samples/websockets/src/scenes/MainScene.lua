
local WebSockets = require("WebSockets")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

local function bin2hex(binary)
    local t = {}
    for i = 1, string.len(binary) do
        t[#t + 1] = string.format("0x%02x", string.byte(binary, i))
    end
    return table.concat(t, " ")
end

function MainScene:ctor()
    local connectLabel =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "connect", size = 32}))
            :onButtonClicked(function()
                self:onConnectClicked()
            end)
            :align(display.CENTER, display.cx, display.top - 32)
            :addTo(self)

    local sendTextLabel =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "send text", size = 32}))
            :onButtonClicked(function()
                self:onSendTextClicked()
            end)
            :align(display.CENTER, display.cx, display.top - 64)
            :addTo(self)

    local sendBinaryLabel =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "send binary", size = 32}))
            :onButtonClicked(function()
                self:onSendBinaryClicked()
            end)
            :align(display.CENTER, display.cx, display.top - 96)
            :addTo(self)
end

function MainScene:onOpen(event)
    print("connected")
end

function MainScene:onMessage(event)
    if WebSockets.BINARY_MESSAGE == event.messageType then
        printf("receive binary msg: len = %s, binary = %s", string.len(event.message), bin2hex(event.message))
    else
        printf("receive text msg: %s", event.message)
    end
end

function MainScene:onClose(event)
    self.websocket = nil
end

function MainScene:onError(event)
    printf("error %s", event.error)
    self.websocket = nil
end

function MainScene:onConnectClicked()
    if self.websocket then return end
    self.websocket = WebSockets.new("ws://echo.websocket.org")
    self.websocket:addEventListener(WebSockets.OPEN_EVENT, handler(self, self.onOpen))
    self.websocket:addEventListener(WebSockets.MESSAGE_EVENT, handler(self, self.onMessage))
    self.websocket:addEventListener(WebSockets.CLOSE_EVENT, handler(self, self.onClose))
    self.websocket:addEventListener(WebSockets.ERROR_EVENT, handler(self, self.onError))
end

function MainScene:onSendTextClicked()
    if not self.websocket then
        print("not connected")
        return
    end

    local text = "hello " .. tostring(math.random())
    if self.websocket:send(text) then
        printf("send text msg: %s", text)
    end
end

function MainScene:onSendBinaryClicked()
    if not self.websocket then
        print("not connected")
        return
    end

    local t = {}
    for i = 1, math.random(4, 8) do
        t[#t + 1] = string.char(math.random(0, 31))
    end
    local binary = table.concat(t)
    if self.websocket:send(binary, WebSockets.BINARY_MESSAGE) then
        printf("send binary msg: len = %d, binary = %s", string.len(binary), bin2hex(binary))
    end
end

return MainScene
