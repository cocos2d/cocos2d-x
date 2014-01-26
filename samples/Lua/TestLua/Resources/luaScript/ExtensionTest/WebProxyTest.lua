 
 local function WebSocketTestLayer()
    local layer   = cc.Layer:create()
    local winSize = cc.Director:getInstance():getWinSize()
        
    local MARGIN = 40
    local SPACE  = 35

    local wsSendText   = nil
    local wsSendBinary = nil
    local wsError      = nil
    local sendTextStatus  = nil
    local sendBinaryStatus = nil
    local errorStatus  = nil
    local receiveTextTimes = 0
    local receiveBinaryTimes = 0
    
    local label = cc.LabelTTF:create("WebSocket Test", "Arial", 28)
    label:setPosition(cc.p( winSize.width / 2, winSize.height - MARGIN))
    layer:addChild(label, 0)

    local menuRequest = cc.Menu:create()
    menuRequest:setPosition(cc.p(0, 0))
    layer:addChild(menuRequest)

    --Send Text
    local function onMenuSendTextClicked()
        if nil ~= wsSendText then
            if cc.WEBSOCKET_STATE_OPEN == wsSendText:getReadyState() then
               sendTextStatus:setString("Send Text WS is waiting...")
               wsSendText:sendString("Hello WebSocket中文, I'm a text message.")
            else
                local warningStr = "send text websocket instance wasn't ready..."
                print(warningStr)
                sendTextStatus:setString(warningStr)
            end
        end
    end
    local labelSendText = cc.LabelTTF:create("Send Text", "Arial", 22)
    local itemSendText  = cc.MenuItemLabel:create(labelSendText)
    itemSendText:registerScriptTapHandler(onMenuSendTextClicked)
    itemSendText:setPosition(cc.p(winSize.width / 2, winSize.height - MARGIN - SPACE))
    menuRequest:addChild(itemSendText)

    --Send Binary
    local function onMenuSendBinaryClicked()
        if nil ~= wsSendBinary then
            if cc.WEBSOCKET_STATE_OPEN == wsSendBinary:getReadyState() then
               sendBinaryStatus:setString("Send Binary WS is waiting...")
               wsSendBinary:sendString("Hello WebSocket中文--,\0 I'm\0 a\0 binary\0 message\0.")
            else
                local warningStr = "send binary websocket instance wasn't ready..."
                sendBinaryStatus:setString(warningStr)
            end
        end
    end
    local labelSendBinary = cc.LabelTTF:create("Send Binary", "Arial", 22)
    local itemSendBinary = cc.MenuItemLabel:create(labelSendBinary)
    itemSendBinary:registerScriptTapHandler(onMenuSendBinaryClicked)
    itemSendBinary:setPosition(cc.p(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE))
    menuRequest:addChild(itemSendBinary)

    --Send Text Status Label
    sendTextStatus = cc.LabelTTF:create("Send Text WS is waiting...", "Arial", 14,cc.size(160, 100),cc.VERTICAL_TEXT_ALIGNMENT_CENTER,cc.VERTICAL_TEXT_ALIGNMENT_TOP)
    sendTextStatus:setAnchorPoint(cc.p(0, 0))
    sendTextStatus:setPosition(cc.p(0, 25))
    layer:addChild(sendTextStatus)

    --Send Binary Status Label
    sendBinaryStatus = cc.LabelTTF:create("Send Binary WS is waiting...", "Arial", 14, cc.size(160, 100), cc.VERTICAL_TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP)
    sendBinaryStatus:setAnchorPoint(cc.p(0, 0))
    sendBinaryStatus:setPosition(cc.p(160, 25))
    layer:addChild(sendBinaryStatus)

    --Error Label
    errorStatus = cc.LabelTTF:create("Error WS is waiting...", "Arial", 14, cc.size(160, 100), cc.VERTICAL_TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP)
    errorStatus:setAnchorPoint(cc.p(0, 0))
    errorStatus:setPosition(cc.p(320, 25))
    layer:addChild(errorStatus)

    local toMainMenu = cc.Menu:create()
    CreateExtensionsBasicLayerMenu(toMainMenu)
    toMainMenu:setPosition(cc.p(0, 0))
    layer:addChild(toMainMenu,10)

    wsSendText   = cc.WebSocket:create("ws://echo.websocket.org")
    wsSendBinary = cc.WebSocket:create("ws://echo.websocket.org")
    wsError      = cc.WebSocket:create("ws://invalid.url.com")

    local function wsSendTextOpen(strData)
        sendTextStatus:setString("Send Text WS was opened.")
    end

    local function wsSendTextMessage(strData)
        receiveTextTimes= receiveTextTimes + 1
        local strInfo= "response text msg: "..strData..", "..receiveTextTimes    
        sendTextStatus:setString(strInfo)
    end

    local function wsSendTextClose(strData)
        print("_wsiSendText websocket instance closed.")
        sendTextStatus = nil
        wsSendText = nil
    end

    local function wsSendTextError(strData)
        print("sendText Error was fired")
    end

    local function wsSendBinaryOpen(strData)
        sendBinaryStatus:setString("Send Binary WS was opened.")
    end

    local function wsSendBinaryMessage(paramTable)
        local length = table.getn(paramTable)
        local i = 1
        local strInfo = "response bin msg: "
        for i = 1,length do
            if 0 == paramTable[i] then
                strInfo = strInfo.."\'\\0\'"
            else
                strInfo = strInfo..string.char(paramTable[i])
            end 
        end
        receiveBinaryTimes = receiveBinaryTimes + 1
        strInfo = strInfo..receiveBinaryTimes
        sendBinaryStatus:setString(strInfo)
    end

    local function wsSendBinaryClose(strData)
        print("_wsiSendBinary websocket instance closed.")
        sendBinaryStatus = nil
        wsSendBinary = nil
    end

    local function wsSendBinaryError(strData)
        print("sendBinary Error was fired")
    end

    local function wsErrorOpen(strData)
    end

    local function wsErrorMessage(strData)

    end

    local function wsErrorError(strData)
        print("Error was fired")
        errorStatus:setString("an error was fired")
    end

    local function wsErrorClose(strData)
        print("_wsiError websocket instance closed.")
        errorStatus= nil
        wsError = nil
    end

    if nil ~= wsSendText then
        wsSendText:registerScriptHandler(wsSendTextOpen,cc.WEBSOCKET_OPEN)
        wsSendText:registerScriptHandler(wsSendTextMessage,cc.WEBSOCKET_MESSAGE)
        wsSendText:registerScriptHandler(wsSendTextClose,cc.WEBSOCKET_CLOSE)
        wsSendText:registerScriptHandler(wsSendTextError,cc.WEBSOCKET_ERROR)
    end

    if nil ~= wsSendBinary then
        wsSendBinary:registerScriptHandler(wsSendBinaryOpen,cc.WEBSOCKET_OPEN)
        wsSendBinary:registerScriptHandler(wsSendBinaryMessage,cc.WEBSOCKET_MESSAGE)
        wsSendBinary:registerScriptHandler(wsSendBinaryClose,cc.WEBSOCKET_CLOSE)
        wsSendBinary:registerScriptHandler(wsSendBinaryError,cc.WEBSOCKET_ERROR)
    end

    if nil ~= wsError then
        wsError:registerScriptHandler(wsErrorOpen,cc.WEBSOCKET_OPEN)
        wsError:registerScriptHandler(wsErrorMessage,cc.WEBSOCKET_MESSAGE)
        wsError:registerScriptHandler(wsErrorClose,cc.WEBSOCKET_CLOSE)
        wsError:registerScriptHandler(wsErrorError,cc.WEBSOCKET_ERROR)
    end

    local function OnExit(strEventName)
        if "exit" == strEventName then
            if nil ~= wsSendText  then
                wsSendText:close()
            end
            if nil ~= wsSendBinary then
                wsSendBinary:close()
            end
            if nil ~=  wsError     then
                wsError:close()
            end
        end
    end

    layer:registerScriptHandler(OnExit)

    return layer
end

 function runWebSocketTest()
    local scene = cc.Scene:create()
    scene:addChild(WebSocketTestLayer())
    return scene
end
