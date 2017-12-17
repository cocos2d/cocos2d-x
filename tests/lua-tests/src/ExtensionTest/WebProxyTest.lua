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
    
    local label = cc.Label:createWithTTF("WebSocket Test", s_arialPath, 28)
    label:setAnchorPoint(cc.p(0.5, 0.5))
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
    local labelSendText = cc.Label:createWithTTF("Send Text", s_arialPath, 22)
    labelSendText:setAnchorPoint(0.5, 0.5)
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
    local labelSendBinary = cc.Label:createWithTTF("Send Binary", s_arialPath, 22)
    labelSendBinary:setAnchorPoint(cc.p(0.5, 0.5))
    local itemSendBinary = cc.MenuItemLabel:create(labelSendBinary)
    itemSendBinary:registerScriptTapHandler(onMenuSendBinaryClicked)
    itemSendBinary:setPosition(cc.p(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE))
    menuRequest:addChild(itemSendBinary)

    --Send Text Status Label
    sendTextStatus = cc.Label:createWithTTF("Send Text WS is waiting...", s_arialPath, 14,cc.size(160, 100),cc.VERTICAL_TEXT_ALIGNMENT_CENTER,cc.VERTICAL_TEXT_ALIGNMENT_TOP)
    sendTextStatus:setAnchorPoint(cc.p(0, 0))
    sendTextStatus:setPosition(cc.p(0, 25))
    layer:addChild(sendTextStatus)

    --Send Binary Status Label
    sendBinaryStatus = cc.Label:createWithTTF("Send Binary WS is waiting...", s_arialPath, 14, cc.size(160, 100), cc.VERTICAL_TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP)
    sendBinaryStatus:setAnchorPoint(cc.p(0, 0))
    sendBinaryStatus:setPosition(cc.p(160, 25))
    layer:addChild(sendBinaryStatus)

    --Error Label
    errorStatus = cc.Label:createWithTTF("Error WS is waiting...", s_arialPath, 14, cc.size(160, 100), cc.VERTICAL_TEXT_ALIGNMENT_CENTER, cc.VERTICAL_TEXT_ALIGNMENT_TOP)
    errorStatus:setAnchorPoint(cc.p(0, 0))
    errorStatus:setPosition(cc.p(320, 25))
    layer:addChild(errorStatus)

    local toMainMenu = cc.Menu:create()
    CreateExtensionsBasicLayerMenu(toMainMenu)
    toMainMenu:setPosition(cc.p(0, 0))
    layer:addChild(toMainMenu,10)

    wsSendText   = cc.WebSocket:create("wss://echo.websocket.org", {"myprotocol_1", "myprotocol_2"}, "cacert.pem")
    wsSendBinary = cc.WebSocket:create("ws://echo.websocket.org", {"hello"}, "cacert.pem")
    wsError      = cc.WebSocket:create("ws://invalid.url.com", {"invalid_protocol"})

    local function wsSendTextOpen(strData)
        if sendTextStatus ~= nil then
            sendTextStatus:setString("Send Text WS was opened, url:" .. wsSendText.url .. ", protocol: " .. wsSendText.protocol)
        end
    end

    local function wsSendTextMessage(strData)
        receiveTextTimes= receiveTextTimes + 1
        local strInfo= "response text msg: "..strData..", "..receiveTextTimes
        if sendTextStatus ~= nil then
            sendTextStatus:setString(strInfo)
        end
    end

    local function wsSendTextClose(strData)
        print("_wsiSendText websocket instance closed.")
        sendTextStatus = nil
        wsSendText = nil
    end

    local function wsSendTextError(strData)
        print("sendText Error was fired")
        if sendTextStatus ~= nil then
            sendTextStatus:setString("sendText Error was fired")
        end
    end

    local function wsSendBinaryOpen(strData)
        if sendBinaryStatus ~= nil then
            sendBinaryStatus:setString("Send Binary WS was opened, url:" .. wsSendBinary.url .. ", protocol: " .. wsSendBinary.protocol)
        end
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
        if sendBinaryStatus ~= nil then
            sendBinaryStatus:setString(strInfo)
        end
    end

    local function wsSendBinaryClose(strData)
        print("_wsiSendBinary websocket instance closed.")
        sendBinaryStatus = nil
        wsSendBinary = nil
    end

    local function wsSendBinaryError(strData)
        print("sendBinary Error was fired")
        if sendBinaryStatus ~= nil then
            sendBinaryStatus:setString("sendBinary Error was fired")
        end
    end

    local function wsErrorOpen(strData)
    end

    local function wsErrorMessage(strData)

    end

    local function wsErrorError(strData)
        print("Error was fired")
        if errorStatus ~= nil then
            errorStatus:setString("an error was fired")
        end
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
                sendTextStatus = nil
                wsSendText:close()
            end
            if nil ~= wsSendBinary then
                sendBinaryStatus = nil
                wsSendBinary:close()
            end
            if nil ~=  wsError     then
                errorStatus = nil
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
