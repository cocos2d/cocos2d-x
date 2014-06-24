
local Provider = class("Provider")


function Provider:ctor()
    self.interface_ = interface
end

--[[
args {
    command = "要执行的命令",
    providerName = "模块名字",
    args = "执行命令的参数"
}
]]
function Provider:doCommand(args)
	if args.command == "setAppVersion" then
		MobClickCppForLua:setAppVersion(args.args.appVersion)
    elseif args.command == "setCrashReportEnabled" then
    	MobClickCppForLua:setCrashReportEnabled(args.args.value)
    elseif args.command == "setLogEnabled" then
        MobClickCppForLua:setLogEnabled(args.args.value)
    elseif args.command == "startWithAppkey" then
        args.args.channelId = args.args.channelId or 0
        MobClickCppForLua:startWithAppkey(args.args.appKey, args.args.channelId)
    elseif args.command == "applicationDidEnterBackground" then
        MobClickCppForLua:applicationDidEnterBackground()
    elseif args.command == "applicationWillEnterForeground" then
        MobClickCppForLua:applicationWillEnterForeground()
    elseif args.command == "end" then
        MobClickCppForLua:endAnalytics()
    elseif args.command == "event" then
        args.args.label = args.args.label or 0
        MobClickCppForLua:event(args.args.eventId, args.args.label)
    elseif args.command == "eventCustom" then
        args.args.counter = args.args.counter or 0
        MobClickCppForLua:eventCustom(args.args.eventId, args.args.attributes, args.args.counter)
    elseif args.command == "beginEvent" then
        MobClickCppForLua:beginEvent(args.args.eventId)
    elseif args.command == "endEvent" then
        MobClickCppForLua:endEvent(args.args.eventId)
    elseif args.command == "beginEventWithLabel" then
        MobClickCppForLua:beginEventWithLabel(args.args.eventId, args.args.label)
    elseif args.command == "endEventWithLabel" then
        MobClickCppForLua:endEventWithLabel(args.args.eventId, args.args.label)
    elseif args.command == "beginEventWithAttributes" then
        MobClickCppForLua:beginEventWithAttributes(args.args.eventId, args.args.primarykey, args.args.attributes)
    elseif args.command == "endEventWithAttributes" then
        MobClickCppForLua:endEventWithAttributes(args.args.eventId, args.args.primarykey)
    elseif args.command == "beginLogPageView" then
        MobClickCppForLua:beginLogPageView(args.args.pageName)
    elseif args.command == "endLogPageView" then
        MobClickCppForLua:endLogPageView(args.args.pageName)
    elseif args.command == "checkUpdate" then
        MobClickCppForLua:checkUpdate()
    elseif args.command == "checkUpdateWithArgs" then
        MobClickCppForLua:checkUpdate(args.args.title, args.args.cancelTitle, args.args.otherTitle)
    elseif args.command == "setUpdateOnlyWifi" then
        MobClickCppForLua:setUpdateOnlyWifi(args.args.updateOnlyWifi)
    elseif args.command == "updateOnlineConfig" then
        MobClickCppForLua:updateOnlineConfig()
    elseif args.command == "getConfigParams" then
        return MobClickCppForLua:getConfigParams(args.args.key)
    elseif args.command == "setUserLevel" then
        MobClickCppForLua:setUserLevel(args.args.level)
    elseif args.command == "setUserInfo" then
        MobClickCppForLua:setUserInfo(args.args.userId, args.args.sex, args.args.age, args.args.platform)
    elseif args.command == "startLevel" then
        MobClickCppForLua:startLevel(args.args.level)
    elseif args.command == "finishLevel" then
        MobClickCppForLua:finishLevel(args.args.level)
    elseif args.command == "failLevel" then
        MobClickCppForLua:failLevel(args.args.level)
    elseif args.command == "payCoin" then
        MobClickCppForLua:pay(args.args.cash, args.args.source, args.args.coin)
    elseif args.command == "payItem" then
        MobClickCppForLua:pay(args.args.cash, args.args.source, args.args.item, args.args.amount, args.args.price)
    elseif args.command == "buy" then
        MobClickCppForLua:buy(args.args.item, args.args.amount, args.args.price)
    elseif args.command == "use" then
        MobClickCppForLua:use(args.args.item, args.args.amount, args.args.price)
    elseif args.command == "bonusCoin" then
        MobClickCppForLua:bonus(args.args.coin, args.args.source)
    elseif args.command == "bonusItem" then
        MobClickCppForLua:bonus(args.args.item, args.args.amount, args.args.price, args.args.source)
    elseif args.command == "beginScene" then
        MobClickCppForLua:beginScene(args.args.sceneName)
    elseif args.command == "endScene" then
        MobClickCppForLua:endScene(args.args.sceneName)
    else
        printError("cc.analytics.umenganalytics.Provider:doCommand() - not support command")
    end

end

return Provider
