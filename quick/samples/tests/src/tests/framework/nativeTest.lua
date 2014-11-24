
local NativeTestScene = game.createSceneClass("NativeTestScene")

function NativeTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "activityIndicator",
        "showAlert",
        "openWebBrowser",
        "callme",
        "sendEmail",
        "getInputText",
        "vibrate",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    print("")
    print("The device name is: ", cc.Native:getDeviceName())
    print("The device uuid is: ", device.getOpenUDID())
    print("")
end

function NativeTestScene:vibrateTest()
    cc.Native:vibrate()
end

function NativeTestScene:openWebBrowserTest()
    device.openURL("http://dualface.github.com")
end

function NativeTestScene:callmeTest()
    device.openURL("tel:123-456-7890")
end

function NativeTestScene:sendEmailTest()
    -- 打开设备上的邮件程序，并创建新邮件，填入收件人地址
    -- device.openURL("mailto:nobody@mycompany.com")

    -- 增加主题和内容
    local subject = string.urlencode("Hello")
    local body = string.urlencode("How are you ?")
    device.openURL(string.format("mailto:nobody@mycompany.com?subject=%s&body=%s", subject, body))
end

function NativeTestScene:showAlertTest()
    local function onButtonClicked(event)
        if event.buttonIndex == 1 then
            print("玩家选择了 YES 按钮")
        else
            print("玩家选择了 NO 按钮")
        end
    end

    device.showAlert("Confirm Exit", "Are you sure exit game ?", {"YES", "NO"}, onButtonClicked)
end

function NativeTestScene:activityIndicatorTest()
    print("Hide activity indicator after 2s.")
    device.showActivityIndicator()

    local scheduler = require(cc.PACKAGE_NAME .. ".scheduler")
    function onTimer(dt)
        device.hideActivityIndicator()
        if self.handle then 
            scheduler.unscheduleGlobal(self.handle)
        end
    end
    self.handle = scheduler.scheduleGlobal(onTimer, 2.0, false)
end

function NativeTestScene:getInputTextTest()
    cc.Native:getInputText("Information", "How weight are you (KG)", "60")
end

return NativeTestScene
