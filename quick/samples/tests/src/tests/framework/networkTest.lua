
local NetworkTestScene = game.createSceneClass("NetworkTestScene")

function NetworkTestScene:ctor()
    self.requestCount = 0

    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "createHTTPRequest",
        "createHTTPRequestBadDomain",
        "send data to server",
        "isLocalWiFiAvailable",
        "isInternetConnectionAvailable",
        "isHostNameReachable",
        "getInternetConnectionStatus",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function NetworkTestScene:onResponse(event, index, dumpResponse)
    local request = event.request
    printf("REQUEST %d - event.name = %s", index, event.name)
    if event.name == "completed" then
        printf("REQUEST %d - getResponseStatusCode() = %d", index, request:getResponseStatusCode())
        -- printf("REQUEST %d - getResponseHeadersString() =\n%s", index, request:getResponseHeadersString())

        if request:getResponseStatusCode() ~= 200 then
        else
            printf("REQUEST %d - getResponseDataLength() = %d", index, request:getResponseDataLength())
            print("dump:" .. tostring(dumpResponse))
            if dumpResponse then
                printf("REQUEST %d - getResponseString() =\n%s", index, request:getResponseString())
            end
        end
    elseif event.name ~= "progress" then
        -- printf("REQUEST %d - getErrorCode() = %d, getErrorMessage() = %s", index, request:getErrorCode(), request:getErrorMessage())
        print("ErrorCode:" .. tostring(request:getErrorCode()))
        print("ErrowMsg:" .. tostring(request:getErrorMessage()))
    end

    print("----------------------------------------")
end

function NetworkTestScene:createHTTPRequestTest()
    local url = "http://quick-x.com/feed/"
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        if tolua.isnull(self) then
            printf("REQUEST %d COMPLETED, BUT SCENE HAS QUIT", index)
            return
        end
        self:onResponse(event, index)
    end, url, "GET")
    printf("REQUEST START %d", index)
    request:start()
end

function NetworkTestScene:createHTTPRequestBadDomainTest()
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        if tolua.isnull(self) then
            printf("REQUEST %d COMPLETED, BUT SCENE HAS QUIT", index)
            return
        end
        self:onResponse(event, index)
    end, "http://quick-x.com.x.y.z.not/", "GET")
    printf("REQUEST START %d", index)
    request:start()
end



function NetworkTestScene:send_data_to_serverTest()
print("send data to server")
    self.requestCount = self.requestCount + 1
    local index = self.requestCount
    local request = network.createHTTPRequest(function(event)
        if tolua.isnull(self) then
            printf("REQUEST %d COMPLETED, BUT SCENE HAS QUIT", index)
            return
        end
        self:onResponse(event, index, true)

        if event.name == "completed" then
            local cookie = network.parseCookie(event.request:getCookieString())
            dump(cookie, "GET COOKIE FROM SERVER")
        end
    end, "http://quick-x.com/tests/http_request_tests.php", "POST")
    request:addPOSTValue("username", "dualface")
    request:setCookieString(network.makeCookieString({C1 = "V1", C2 = "V2"}))
    printf("REQUEST START %d", index)
    request:start()
end

function NetworkTestScene:isLocalWiFiAvailableTest()
    print("Is local wifi avaibable: ", network.isLocalWiFiAvailable())
end

function NetworkTestScene:isInternetConnectionAvailableTest()
    print("Is internet connection avaibable: ", network.isInternetConnectionAvailable())
end

function NetworkTestScene:isHostNameReachableTest()
    print("Is www.cocos2d-x.org reachable: ", network.isHostNameReachable("www.cocos2d-x.org"))
end

function NetworkTestScene:getInternetConnectionStatusTest()
    local status = {
        [cc.kCCNetworkStatusNotReachable]     = "无法访问互联网",
        [cc.kCCNetworkStatusReachableViaWiFi] = "通过 WIFI",
        [cc.kCCNetworkStatusReachableViaWWAN] = "通过 3G 网络",
    }

    printf("Internet Connection Status: %s", status[network.getInternetConnectionStatus()])
end

return NetworkTestScene
