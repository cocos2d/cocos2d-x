
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    if device.platform == "android" then
    	self.ads = app.agentMgr:getAdsPlugin()
        if self.ads then
    	   self.ads:setAdsListener(handler(self, self.adListener))
        end
        self:show()
    else
        self:showNotSupport()
    end
end

function MainScene:showNotSupport()
    cc.ui.UILabel.new({text = "AnySDK demo\n\nPlease run this demo on Android device.",
            size = 24,
            align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.cy)
        :align(display.CENTER)
        :addTo(self)
end

function MainScene:show()
    self.innerSpace = 70

    cc.ui.UILabel.new({text = "AnySDK demo", size = 48, align = cc.ui.TEXT_ALIGN_CENTER})
        :pos(display.cx, display.top - self.innerSpace*1)
        :align(display.CENTER)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "显示广告", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local ads = app.agentMgr:getAdsPlugin()
        	if ads then
                ads:showAds(0)
                print("ads sdk version:", ads:getSDKVersion())
            end
        end)
        :pos(display.cx/2, display.top - self.innerSpace*2)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "记录事件", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local analy = app.agentMgr:getAnalyticsPlugin()
            if analy then
                analy:logEvent("pressSecondBtn", {pos = 2, info = "第二个按钮被按下了"})
            end
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*2)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "设置推送标签", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local push = app.agentMgr:getPushPlugin()
            if push then
                push:setTags({"normalUser", "vip"})
            end
        end)
        :pos(display.cx/2, display.top - self.innerSpace*3)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "分享功能", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local share = app.agentMgr:getSharePlugin()
            if share then
                -- 具体有哪些参数，请见anysdk官网的文档说明
                -- http://docs.anysdk.com/ShareSystem
                share:share({title = "quick分享",
                    titleUrl = "http://quick.cocos.org/",
                    site = "quick引挈",
                    siteUrl = "http://quick.cocos.org/",
                    text = "quick开发引挈提供一个快捷方便的开发框架",
                    comment = "quick真是好"})
            end
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*3)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "社交功能", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local social = app.agentMgr:getSocialPlugin()
            if social then
                social:unlockAchievement({key1 = "val1",
                    key2 = "val2"})
            end
        end)
        :pos(display.cx/2, display.top - self.innerSpace*4)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "用户模块", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local user = app.agentMgr:getUserPlugin()
            if user then
                user:login()

                --调用扩展功能
                if user:isSupportFunction("function1") then
                    --PluginProtocol中的callFuncWithParam方法只导出了传多个参数的方法(原生C代码支持传多个参数或传一个vector)
                    --除第一个外，后续参数不分先后，会自动全部转为PluginParam类型再传到AnySDK中
                    user:callFuncWithParam("function1", 12, true, "infos1", {key1 = "val11", key2 = "val2"})
                end
            end
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*4)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "支付模块", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            local iaps = app.agentMgr:getIAPPlugin()
            dump(iaps, "IAPs:")
            if iaps then
                --从iaps中选一个来支付，具体返回有哪些，要看anysk打包集成了哪些
                local iap = iaps.alipay
                if not iap then
                    print("IAP is nil")
                    return
                end

                --payForProduct有哪些参数及其含意，参见
                --http://docs.anysdk.com/IAPSystem
                iap:payForProduct({Product_Id = 1,
                                Product_Name = "蓝药水",
                                Product_Price = "10",
                                Product_Count = 3,
                                Role_Id = 1001,
                                Role_Name = "天之林",
                                Role_Grade = 11,
                                Server_Id = 1})
            end
        end)
        :pos(display.cx/2, display.top - self.innerSpace*5)
        :addTo(self)

    self.textLable = cc.ui.UILabel.new({text = "-", size = 22, color = display.COLOR_WHITE})
        :pos(display.cx, display.top - self.innerSpace*6)
        :align(display.CENTER)
        :addTo(self)
end

function MainScene:sdkListener(protocol, param)
    dump(param, "sdk callback param:")
    self.textLable:setString(json.encode(param))
    if "ads" == protocol then
    elseif "iap" == protocol then
    elseif "share" == protocol then
    elseif "social" == protocol then
    elseif "user" == protocol then
    elseif "push" == protocol then
    end
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
