require("json")

local function XMLHttpRequestLayer()
    local layer = cc.Layer:create()
    local winSize = cc.Director:getInstance():getWinSize()
    local margin = 40
    local space  = 35

    local function init()
        local label = cc.Label:createWithTTF("XML Http Request Test", s_arialPath, 28)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(winSize.width / 2, winSize.height - margin))
        layer:addChild(label, 0)

        --Response Code Label
        local labelStatusCode = cc.Label:createWithTTF("HTTP Status Code", s_markerFeltFontPath, 20)
        labelStatusCode:setAnchorPoint(cc.p(0.5, 0.5))
        labelStatusCode:setPosition(cc.p(winSize.width / 2,  winSize.height - margin - 6 * space))
        layer:addChild(labelStatusCode)

        local menuRequest = cc.Menu:create()
        menuRequest:setPosition(cc.p(0,0))
        layer:addChild(menuRequest)

        --Get
        local function onMenuGetClicked()
            local xhr = cc.XMLHttpRequest:new()
            xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_STRING
            xhr:open("GET", "http://httpbin.org/get")

            local function onReadyStateChanged()
                if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
                    print(xhr.response)
                    if not tolua.isnull(labelStatusCode) then
                        labelStatusCode:setString("Http Status Code:" .. xhr.statusText)
                    else
                        print("ERROR: labelStatusCode is invalid!")
                    end
                else
                    print("xhr.readyState is:", xhr.readyState, "xhr.status is: ",xhr.status)
                end
                xhr:unregisterScriptHandler()
            end

            xhr:registerScriptHandler(onReadyStateChanged)
            xhr:send()

            labelStatusCode:setString("waiting...")
        end

        local labelGet  = cc.Label:createWithTTF("Test Get", s_arialPath, 22)
        labelGet:setAnchorPoint(cc.p(0.5, 0.5))
        local itemGet  =  cc.MenuItemLabel:create(labelGet)
        itemGet:registerScriptTapHandler(onMenuGetClicked)
        itemGet:setPosition(cc.p(winSize.width / 2, winSize.height - margin - space))
        menuRequest:addChild(itemGet)

        --Post
        local function onMenuPostClicked()
            local xhr = cc.XMLHttpRequest:new()
            xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_STRING
            xhr:open("POST", "http://httpbin.org/post")
            local function onReadyStateChanged()
                if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
                    if not tolua.isnull(labelStatusCode) then
                        labelStatusCode:setString("Http Status Code:" .. xhr.statusText)
                    else
                        print("ERROR: labelStatusCode is invalid!")
                    end
                    print(xhr.response)
                else
                    print("xhr.readyState is:", xhr.readyState, "xhr.status is: ",xhr.status)
                end
                xhr:unregisterScriptHandler()
            end
            xhr:registerScriptHandler(onReadyStateChanged)
            xhr:send()

            labelStatusCode:setString("waiting...")
        end

        local labelPost = cc.Label:createWithTTF("Test Post", s_arialPath, 22)
        labelPost:setAnchorPoint(cc.p(0.5, 0.5))
        local itemPost =  cc.MenuItemLabel:create(labelPost)
        itemPost:registerScriptTapHandler(onMenuPostClicked)
        itemPost:setPosition(cc.p(winSize.width / 2, winSize.height - margin - 2 * space))
        menuRequest:addChild(itemPost)

        --Post Binary
        local function onMenuPostBinaryClicked()
            local xhr = cc.XMLHttpRequest:new()
            xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_ARRAY_BUFFER
            xhr:open("POST", "http://httpbin.org/post")

            local function onReadyStateChanged()
                if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
                    local response   = xhr.response
                    local size     = table.getn(response)
                    local strInfo = ""

                    for i = 1,size do
                        if 0 == response[i] then
                            strInfo = strInfo.."\'\\0\'"
                        else
                            strInfo = strInfo..string.char(response[i])
                        end
                    end

                    if not tolua.isnull(labelStatusCode) then
                        labelStatusCode:setString("Http Status Code:" .. xhr.statusText)
                    else
                        print("ERROR: labelStatusCode is invalid!")
                    end

                    print(strInfo)
                else
                    print("xhr.readyState is:", xhr.readyState, "xhr.status is: ",xhr.status)
                end
                xhr:unregisterScriptHandler()
            end

            xhr:registerScriptHandler(onReadyStateChanged)
            xhr:send()

            labelStatusCode:setString("waiting...")
        end

        local labelPostBinary = cc.Label:createWithTTF("Test Post Binary", s_arialPath, 22)
        labelPostBinary:setAnchorPoint(cc.p(0.5, 0.5))
        local itemPostBinary = cc.MenuItemLabel:create(labelPostBinary)
        itemPostBinary:registerScriptTapHandler(onMenuPostBinaryClicked)
        itemPostBinary:setPosition(cc.p(winSize.width / 2, winSize.height - margin - 3 * space))
        menuRequest:addChild(itemPostBinary)

        --Post Json

        local function onMenuPostJsonClicked()
            local xhr = cc.XMLHttpRequest:new()
            xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_JSON
            xhr:open("POST", "http://httpbin.org/post")

            local function onReadyStateChanged()
                if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
                    if not tolua.isnull(labelStatusCode) then
                        labelStatusCode:setString("Http Status Code:" .. xhr.statusText)
                    else
                        print("ERROR: labelStatusCode is invalid!")
                    end
                    local response   = xhr.response
                    local output = json.decode(response,1)
                    table.foreach(output,function(i, v) print (i, v) end)
                    print("headers are")
                    table.foreach(output.headers,print)
                else
                    print("xhr.readyState is:", xhr.readyState, "xhr.status is: ",xhr.status)
                end
                xhr:unregisterScriptHandler()
            end

            xhr:registerScriptHandler(onReadyStateChanged)
            xhr:send()

            labelStatusCode:setString("waiting...")
        end

        local labelPostJson = cc.Label:createWithTTF("Test Post Json", s_arialPath, 22)
        labelPostJson:setAnchorPoint(cc.p(0.5, 0.5))
        local itemPostJson = cc.MenuItemLabel:create(labelPostJson)
        itemPostJson:registerScriptTapHandler(onMenuPostJsonClicked)
        itemPostJson:setPosition(cc.p(winSize.width / 2, winSize.height - margin - 4 * space))
        menuRequest:addChild(itemPostJson)
    end

    local function onNodeEvent(eventName)
        if "enter" == eventName then
            init()
        end
    end

    layer:registerScriptHandler(onNodeEvent)

    return layer
end

function XMLHttpRequestTestMain()
    local scene = cc.Scene:create()
    scene:addChild(XMLHttpRequestLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
