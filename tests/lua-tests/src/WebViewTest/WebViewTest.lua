
----------------------------------------
----WebViewTest
----------------------------------------
local WebViewTest = class("WebViewTest", function ()
    local layer = cc.Layer:create()

    return layer
end)

function WebViewTest:ctor()
    self:init()
end

function WebViewTest:init()
    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local winSize = cc.Director:getInstance():getVisibleSize()
    self._webView = ccexp.WebView:create()
    self._webView:setPosition(winSize.width / 2, winSize.height / 2)
    self._webView:setContentSize(winSize.width / 2,  winSize.height / 2)
    self._webView:loadURL("https://www.baidu.com")
    self._webView:setScalesPageToFit(true)

    self._webView:setOnShouldStartLoading(function(sender, url)
        print("onWebViewShouldStartLoading, url is ", url)
        return true
    end)
    self._webView:setOnDidFinishLoading(function(sender, url)
        print("onWebViewDidFinishLoading, url is ", url)
    end)
    self._webView:setOnDidFailLoading(function(sender, url)
        print("onWebViewDidFinishLoading, url is ", url)
    end)

    self:addChild(self._webView)

    local urlTextField = ccui.TextField:create("Input a URL here", "Arial", 20)
    urlTextField:setPlaceHolderColor(cc.c4b(255, 0, 0,  255))
    urlTextField:setPosition(winSize.width/2 - 80, winSize.height/2 + self._webView:getContentSize().height/2 + urlTextField:getContentSize().height/2 + 10)
    self:addChild(urlTextField)
    
    local httpLabel = ccui.Text:create("https:// ", "Arial", 20)
    httpLabel:setTextColor(cc.c4b(0, 255,   0, 255))
    httpLabel:setAnchorPoint(cc.p(1.0,0.5))
    local x,y = urlTextField:getPosition()
    httpLabel:setPosition( x - urlTextField:getContentSize().width / 2, y)
    self:addChild(httpLabel)

    local resetBtn = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    resetBtn:setTitleText("Visit URL")
    resetBtn:setPosition(winSize.width / 2 + 80 , winSize.height / 2 + self._webView:getContentSize().height / 2 + resetBtn:getContentSize().height / 2 + 10)
    resetBtn:addClickEventListener(function(sender)
        if urlTextField:getString() ~=  nil then
            self._webView:loadURL("https://" .. urlTextField:getString())
        end    
    end)
    self:addChild(resetBtn)

    local reloadBtn = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    reloadBtn:setTitleText("Reload")
    reloadBtn:setPosition(winSize.width / 2 + self._webView:getContentSize().width / 2 + reloadBtn:getContentSize().width / 2 + 10, winSize.height / 2 + 50)
    reloadBtn:addClickEventListener(function(sender)
        self._webView:reload()
    end)
    self:addChild(reloadBtn)

    local forwardBtn = ccui.Button:create("cocosui/animationbuttonnormal.png","cocosui/animationbuttonpressed.png")
    forwardBtn:setTitleText("Forward")
    forwardBtn:setPosition(winSize.width / 2 + self._webView:getContentSize().width / 2 + forwardBtn:getContentSize().width / 2 + 10,winSize.height / 2)
    forwardBtn:addClickEventListener(function(sender)
        self._webView:goForward()
    end)
    self:addChild(forwardBtn)

    local backBtn = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    backBtn:setTitleText("Back")
    backBtn:setPosition(winSize.width / 2 + self._webView:getContentSize().width/2 + backBtn:getContentSize().width/2 + 10, winSize.height - 10)
    backBtn:addClickEventListener(function(sender)
        self._webView:goBack()
    end)
    self:addChild(backBtn)

    local loadFileBtn = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    loadFileBtn:setTitleText("Load FILE")
    loadFileBtn:setPosition(winSize.width / 2 - self._webView:getContentSize().width/2 - loadFileBtn:getContentSize().width/2 - 30, winSize.height / 2 + 50)
    loadFileBtn:addClickEventListener(function(sender)
        self._webView:loadFile("Test.html")
    end)
    self:addChild(loadFileBtn)
    
    local loadHTMLBtn = ccui.Button:create("cocosui/animationbuttonnormal.png","cocosui/animationbuttonpressed.png")
    loadHTMLBtn:setTitleText("Load Data")
    loadHTMLBtn:setPosition(winSize.width / 2 - self._webView:getContentSize().width/2 - loadHTMLBtn:getContentSize().width/2 - 30, winSize.height / 2)
    loadHTMLBtn:addClickEventListener(function(sender)
        self._webView:loadHTMLString("<body style=\"font-size:50px\">Hello World <img src=\"Icon.png\"/> </body>","Images/")
    end)
    self:addChild(loadHTMLBtn)
    
    local evalJsBtn = ccui.Button:create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png")
    evalJsBtn:setTitleText("Evaluate JS")
    evalJsBtn:setPosition(winSize.width / 2 - self._webView:getContentSize().width/2 - evalJsBtn:getContentSize().width/2 - 30, winSize.height / 2 - 50)
    evalJsBtn:addClickEventListener(function(sender)
        self._webView:evaluateJS("setTimeout(function(){alert(\"hello\");}, 0);")
    end)
    self:addChild(evalJsBtn)
end

function WebViewTest:title()
    return ""
end

function WebViewTest:subtitle()
    return ""
end

function WebViewTestMain()
    Helper.createFunctionTable =
    {
        WebViewTest.create,
    }
    Helper.index = 1

    local scene = cc.Scene:create()
    scene:addChild(WebViewTest.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end
