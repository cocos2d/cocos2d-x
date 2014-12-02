
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    cc.ui.UILabel.new({
        UILabelType = 2, text = "请确保\nAppController::registerScriptHandler\nAppController::payForCoins \n的实现", size = 24})
    :align(display.CENTER_TOP, display.cx, display.top)
    :addTo(self)

    local btn
    btn = cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "LuaObjcBridge (Click Me): please run this on ios/mac", size = 24}))
            :onButtonClicked(function()
                if not luaoc then
                    btn:setButtonLabel(cc.ui.UILabel.new({text = "please run this on ios/mac", size = 32}))
                    return
                end
                
                local function callback(event)
                    if event == "SDK_LEAVE_PLATFORM" then
                        print("充值正在进行中，稍候您就能收到金币啦")
                    elseif event == "SDK_PAYMENT_DONE" then
                        device.showAlert("充值完成", "恭喜你充值完成", {"YES"})
                    end
                end
                luaoc.callStaticMethod("AppController", "registerScriptHandler", {listener = callback})

                local args = {
                orderId = "order-00001001001",
                coins = 1000,
                }
                local ok, ret = luaoc.callStaticMethod("AppController", "payForCoins", args)
                if ok then
                    dump(ret)
                end

            end)
            :align(display.CENTER, display.cx, display.cy)
            :addTo(self)
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
