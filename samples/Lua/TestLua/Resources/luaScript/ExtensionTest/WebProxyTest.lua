 
 local function WebSocketTestLayer()
    local layer   = CCLayer:create()
    local winSize = CCDirector:sharedDirector():getWinSize()
        
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
    
    local label = CCLabelTTF:create("WebSocket Test", "Arial", 28)
    label:setPosition(ccp( winSize.width / 2, winSize.height - MARGIN))
    layer:addChild(label, 0)

    local menuRequest = CCMenu:create()
    menuRequest:setPosition(ccp(0, 0))
    layer:addChild(menuRequest)

    --Send Text
    local function onMenuSendTextClicked()
        if nil ~= wsSendText then
            if kStateOpen == wsSendText:getReadyState() then
               sendTextStatus:setString("Send Text WS is waiting...")
               wsSendText:sendTextMsg("Hello WebSocket中文, I'm a text message.")
            else
                local warningStr = "send text websocket instance wasn't ready..."
                print(warningStr)
                sendTextStatus:setString(warningStr)
            end
        end
    end
    local labelSendText = CCLabelTTF:create("Send Text", "Arial", 22)
    local itemSendText  = CCMenuItemLabel:create(labelSendText)
    itemSendText:registerScriptTapHandler(onMenuSendTextClicked)
    itemSendText:setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - SPACE))
    menuRequest:addChild(itemSendText)

    --Send Binary
    local function onMenuSendBinaryClicked()
        if nil ~= wsSendBinary then
            if kStateOpen == wsSendBinary:getReadyState() then
               sendBinaryStatus:setString("Send Binary WS is waiting...")
               local buf = "Hello WebSocket中文--,\0 I'm\0 a\0 binary\0 message\0."
               local nLength = string.len(buf)
               t = {string.byte(buf,1,-1)}
               --[[print(t)
               print(table.getn(t))
               print(string.char(unpack(t)))]]--
               wsSendBinary:sendBinaryMsg(t,table.getn(t))
            else
                local warningStr = "send binary websocket instance wasn't ready..."
                sendBinaryStatus:setString(warningStr)
            end
        end
    end
    local labelSendBinary = CCLabelTTF:create("Send Binary", "Arial", 22)
    local itemSendBinary = CCMenuItemLabel:create(labelSendBinary)
    itemSendBinary:registerScriptTapHandler(onMenuSendBinaryClicked)
    itemSendBinary:setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE))
    menuRequest:addChild(itemSendBinary)

    --Send Text Status Label
    sendTextStatus = CCLabelTTF:create("Send Text WS is waiting...", "Arial", 14,CCSizeMake(160, 100),kCCVerticalTextAlignmentCenter,kCCVerticalTextAlignmentTop)
    sendTextStatus:setAnchorPoint(ccp(0, 0))
    sendTextStatus:setPosition(ccp(0, 25))
    layer:addChild(sendTextStatus)

    --Send Binary Status Label
    sendBinaryStatus = CCLabelTTF:create("Send Binary WS is waiting...", "Arial", 14, CCSizeMake(160, 100), kCCVerticalTextAlignmentCenter, kCCVerticalTextAlignmentTop)
    sendBinaryStatus:setAnchorPoint(ccp(0, 0))
    sendBinaryStatus:setPosition(ccp(160, 25))
    layer:addChild(sendBinaryStatus)

    --Error Label
    errorStatus = CCLabelTTF:create("Error WS is waiting...", "Arial", 14, CCSizeMake(160, 100), kCCVerticalTextAlignmentCenter, kCCVerticalTextAlignmentTop)
    errorStatus:setAnchorPoint(ccp(0, 0))
    errorStatus:setPosition(ccp(320, 25))
    layer:addChild(errorStatus)

    local toMainMenu = CCMenu:create()
    CreateExtensionsBasicLayerMenu(toMainMenu)
    toMainMenu:setPosition(ccp(0, 0))
    layer:addChild(toMainMenu,10)

    wsSendText   = WebSocket:create("ws://echo.websocket.org")
    wsSendBinary = WebSocket:create("ws://echo.websocket.org")
    wsError      = WebSocket:create("ws://invalid.url.com")

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
        wsSendText:registerScriptHandler(wsSendTextOpen,kWebSocketScriptHandlerOpen)
        wsSendText:registerScriptHandler(wsSendTextMessage,kWebSocketScriptHandlerMessage)
        wsSendText:registerScriptHandler(wsSendTextClose,kWebSocketScriptHandlerClose)
        wsSendText:registerScriptHandler(wsSendTextError,kWebSocketScriptHandlerError)
    end

    if nil ~= wsSendBinary then
        wsSendBinary:registerScriptHandler(wsSendBinaryOpen,kWebSocketScriptHandlerOpen)
        wsSendBinary:registerScriptHandler(wsSendBinaryMessage,kWebSocketScriptHandlerMessage)
        wsSendBinary:registerScriptHandler(wsSendBinaryClose,kWebSocketScriptHandlerClose)
        wsSendBinary:registerScriptHandler(wsSendBinaryError,kWebSocketScriptHandlerError)
    end

    if nil ~= wsError then
        wsError:registerScriptHandler(wsErrorOpen,kWebSocketScriptHandlerOpen)
        wsError:registerScriptHandler(wsErrorMessage,kWebSocketScriptHandlerMessage)
        wsError:registerScriptHandler(wsErrorClose,kWebSocketScriptHandlerClose)
        wsError:registerScriptHandler(wsErrorError,kWebSocketScriptHandlerError)
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
    local scene = CCScene:create()
    scene:addChild(WebSocketTestLayer())
    return scene
end
