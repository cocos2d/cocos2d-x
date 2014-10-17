--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--functions of WebSocket will be deprecated begin
local targetPlatform = CCApplication:getInstance():getTargetPlatform()
if (kTargetIphone == targetPlatform) or (kTargetIpad == targetPlatform) or (kTargetAndroid == targetPlatform) or (kTargetWindows == targetPlatform) then
    local WebSocketDeprecated = { }
    function WebSocketDeprecated.sendTextMsg(self, string)
        deprecatedTip("WebSocket:sendTextMsg","WebSocket:sendString")
        return self:sendString(string)
    end
    WebSocket.sendTextMsg = WebSocketDeprecated.sendTextMsg

    function WebSocketDeprecated.sendBinaryMsg(self, table,tablesize)
        deprecatedTip("WebSocket:sendBinaryMsg","WebSocket:sendString")
        string.char(unpack(table))
        return self:sendString(string.char(unpack(table)))
    end
    WebSocket.sendBinaryMsg = WebSocketDeprecated.sendBinaryMsg
end
--functions of WebSocket will be deprecated end
