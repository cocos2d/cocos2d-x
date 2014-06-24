
local ProviderBase = class("ProviderBase")

local errors = import("..errors")
local events = import("..events")

local SDK_ERRORS = {}
SDK_ERRORS["1000"] = errors.SERVICE     -- 服务未开启
SDK_ERRORS["1001"] = errors.NETWORK     -- http 方法错误
SDK_ERRORS["1002"] = errors.SERVICE     -- 参数错误
SDK_ERRORS["1003"] = errors.NETWORK     -- POST 数据错误
SDK_ERRORS["1004"] = errors.SERVICE     -- 事件关闭
SDK_ERRORS["1005"] = errors.SERVICE     -- punchbox 关闭
SDK_ERRORS["1006"] = errors.NETWORK     -- 无广告适合的广告组
SDK_ERRORS["1007"] = errors.NO_MORE_AD  -- 无广告创意可用
SDK_ERRORS["1008"] = errors.NETWORK     -- 创意 URL 不存在
SDK_ERRORS["1009"] = errors.NETWORK     -- 广告模板不存在
SDK_ERRORS["1010"] = errors.SERVICE     -- App 关闭
SDK_ERRORS["1011"] = errors.VERSION     -- App 版本关闭
SDK_ERRORS["1012"] = errors.SERVICE     -- 未支持的广告类型
SDK_ERRORS["1013"] = errors.NETWORK     -- 频繁的请求
SDK_ERRORS["1014"] = errors.NETWORK     -- 地域开关关闭
SDK_ERRORS["1015"] = errors.SERVICE     -- 作弊请求
SDK_ERRORS["2000"] = errors.NETWORK     -- 手机没有网络连接。网络错误,如超时或无法连接到服务器
SDK_ERRORS["2002"] = errors.NETWORK     -- 服务器返回内容为空
SDK_ERRORS["2003"] = errors.VERSION     -- Android SDK 版本太低, 广告将不做响应,建议 Android SDK 版本最低 2.2
SDK_ERRORS["2004"] = errors.NETWORK     -- http 错误(http 状态码非 200)
SDK_ERRORS["2005"] = errors.SERVICE     -- 广告开关关闭或者没有调 用 loadAd 方法
SDK_ERRORS["2006"] = errors.SERVICE     -- 广告还未加载完成
SDK_ERRORS["2007"] = errors.SERVICE     -- 广告显示比例相对于屏幕的比例不在范围内,必须大于 0.5,小于等于 1.0
SDK_ERRORS["2008"] = errors.SERVICE     -- 传递的 Context 对象不是 Activity 类型
SDK_ERRORS["2009"] = errors.SERVICE     -- Context 对象已被销毁
SDK_ERRORS["2010"] = errors.NETWORK     -- 广告素材加载超时
SDK_ERRORS["9999"] = errors.UNKNOWN     -- 未知错误

function ProviderBase:ctor(interface, options)
    self.interface_ = interface
    self.options_ = options
end

function ProviderBase:callback_(event)
    event, errcode = unpack(string.split(string.lower(event), ","))
    printInfo("cc.ad.punchbox CALLBACK, event %s", event)
    local evt = {provider = "ad.PunchBox"}
    if event == "received" then
        evt.name = events.RECEIVED
    elseif event == "present" then
        evt.name = events.PRESENT
    elseif event == "dismiss" then
        evt.name = events.DISMISS
    elseif event == "failed" then
        evt.name = events.FAILED
        evt.error = SDK_ERRORS[errcode] or errors.UNKNOWN
        evt.errorCode = errcode
    else
        evt.name = string.upper(event)
    end
    self.interface_:dispatchEvent(evt)
end

function ProviderBase:doCommand(args)
    if args.command == "banner" or args.command == "interstitial" or args.command == "moregame" then
        self:show(args.command, args.args)
    else
        printError("cc.ad.punchbox.ProviderBase:doCommand() - invaild command:" .. args.command)
    end
end

return ProviderBase
