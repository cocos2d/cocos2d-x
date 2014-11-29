
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local btn
    btn = cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "call Java - showAlertDialog()", size = 64}))
            :onButtonClicked(function()
                if device.platform ~= "android" then
                    print("please run this on android device")
                    btn:setButtonLabel(cc.ui.UILabel.new({text = "please run this on android device", size = 32}))
                    return
                end
                
                -- call Java method
                local javaClassName = "org/cocos2dx/lua/AppActivity"
                local javaMethodName = "showAlertDialog"
                local javaParams = {
                    "How are you ?",
                    "I'm great !",
                    function(event)
                        local str = "Java method callback value is [" .. event .. "]"
                        btn:setButtonLabel(cc.ui.UILabel.new({text = str, size = 32}))
                    end
                }
                local javaMethodSig = "(Ljava/lang/String;Ljava/lang/String;I)V"
                luaj.callStaticMethod(javaClassName, javaMethodName, javaParams, javaMethodSig)
            end)
            :align(display.CENTER, display.cx, display.cy)
            :addTo(self)

    btn:setKeypadEnabled(true)
    btn:addNodeEventListener(cc.KEYPAD_EVENT, function (event)
        dump(event)
        local str = "event.key is [ " .. event.key .. " ]"
                        btn:setButtonLabel(cc.ui.UILabel.new({text = str, size = 32}))
        if event.key == "back" then
            print("back")
            cc.Director:getInstance():endToLua()
            if device.platform == "windows" or device.platform == "mac" then
                os.exit()
            end
        elseif event.key == "menu" then
            print("menu")
        end
    end)
end

function MainScene:onEnter()
end

return MainScene
