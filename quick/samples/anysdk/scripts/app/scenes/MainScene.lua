
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    if device.platform ~= "android" then
    	self.ads = app.agentMgr:getAdsPlugin()
    	self.ads:setAdsListener(handler(self, self.adListener))
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
        	self.ads:showAds(0)
        end)
        :pos(display.cx/2, display.top - self.innerSpace*2)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "购买道具", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 使用金币购买了1个头盔，一个头盔价值 1000 金币
            cc.analytics:doCommand{command = "buy",
                    args = {item = "helmet", amount = 1, price = 1000}}
            -- MobClickCppForLua:buy("helmet", 1, 1000)
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*2)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "消耗道具", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 使用了2瓶魔法药水,每个需要50个虚拟币
            cc.analytics:doCommand{command = "use",
                    args = {item = "magic_bottle", amount = 2, price = 50}}
            -- MobClickCppForLua:use("magic_bottle", 2, 50)
        end)
        :pos(display.cx/2, display.top - self.innerSpace*3)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "额外奖励", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 连续5天登陆游戏奖励1000金币
            cc.analytics:doCommand{command = "bonusCoin",
                    args = {coin = 1000, source = 1}}
            -- MobClickCppForLua:bonus(1000, 1);
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*3)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "普通事件", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 统计微博应用中"转发"事件发生的次数
            cc.analytics:doCommand{command = "event",
                    args = {eventId = "forward"}}
            -- MobClickCppForLua:event("forward");
        end)
        :pos(display.cx/2, display.top - self.innerSpace*4)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "多属性(K-V)事件", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 电商应用中“购买”事件发生的次数，以及购买的商品类型及数量，那么在购买的函数里调用

            -- 注意这里的第二个参数 友盟原生要求传入map<string,string>
            -- 在lua中改为传字串，它的格式为 “k,v” 或 “k,v|k,v”
            -- 同时因为第二个参数类型的改变，会造成与普通事件的event函数有二义性，所以名字与原生也有变动
            -- 详情可参见$QUICK_COCOS2DX_ROOT/lib/sdk/umeng_analytics/include/MobClickCppForLua.h
            local attributes = "type,book|quantity,3"
            cc.analytics:doCommand{command = "eventCustom",
                    args = {eventId = "purchase", attributes = attributes}}
            -- MobClickCppForLua:eventCustom("purchase", attributes)
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*4)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "事件开始", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 跟踪播放音乐事件发生的总时间,音乐播放开始时调用
            cc.analytics:doCommand{command = "beginEvent",
                    args = {eventId = "music_play"}}
            -- MobClickCppForLua:beginEvent("music_play")
        end)
        :pos(display.cx/2, display.top - self.innerSpace*5)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "事件结束", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 跟踪播放音乐事件发生的总时间,音乐播放结束时调用
            cc.analytics:doCommand{command = "endEvent",
                    args = {eventId = "music_play"}}
            -- MobClickCppForLua:endEvent("music_play")
        end)
        :pos(display.cx + display.cx/2, display.top - self.innerSpace*5)
        :addTo(self)

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "在线参数", size = 22, color = display.COLOR_BLACK}))
        :setButtonSize(display.cx - 20, 60)
        :onButtonClicked(function()
            -- 跟踪播放音乐事件发生的总时间,音乐播放结束时调用
            local value = cc.analytics:doCommand{command = "getConfigParams",
                    args = {key = "author"}}
            -- local value = MobClickCppForLua:getConfigParams("author")
            if value then
                print("online config author:" .. value)
            else
                print("online config author: nil")
            end
        end)
        :pos(display.cx/2, display.top - self.innerSpace*6)
        :addTo(self)

end

function MainScene:adListener(pluginName, param)
	print("htl entry adlistener")
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
