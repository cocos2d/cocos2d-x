-- enable log


local function doTest()
    cclog("********************** init value ***********************")

    -- set default value

    cc.UserDefault:getInstance():setStringForKey("string", "value1")
    cc.UserDefault:getInstance():setIntegerForKey("integer", 10)
    cc.UserDefault:getInstance():setFloatForKey("float", 2.3)
    cc.UserDefault:getInstance():setDoubleForKey("double", 2.4)
    cc.UserDefault:getInstance():setBoolForKey("bool", true)

    -- print value

    local ret = cc.UserDefault:getInstance():getStringForKey("string")
    cclog("string is %s", ret)

    local d = cc.UserDefault:getInstance():getDoubleForKey("double")
    cclog("double is %f", d)

    local i = cc.UserDefault:getInstance():getIntegerForKey("integer")
    cclog("integer is %d", i)

    local f = cc.UserDefault:getInstance():getFloatForKey("float")
    cclog("float is %f", f)

    local b = cc.UserDefault:getInstance():getBoolForKey("bool")
    if b == true then
        cclog("bool is true")
    else
        cclog("bool is false")
    end

    --cc.UserDefault:getInstance():flush()

    cclog("********************** after change value ***********************")

    -- change the value

    cc.UserDefault:getInstance():setStringForKey("string", "value2")
    cc.UserDefault:getInstance():setIntegerForKey("integer", 11)
    cc.UserDefault:getInstance():setFloatForKey("float", 2.5)
    cc.UserDefault:getInstance():setDoubleForKey("double", 2.6)
    cc.UserDefault:getInstance():setBoolForKey("bool", false)

    cc.UserDefault:getInstance():flush()

    -- print value

    ret = cc.UserDefault:getInstance():getStringForKey("string")
    cclog("string is %s", ret)

    d = cc.UserDefault:getInstance():getDoubleForKey("double")
    cclog("double is %f", d)

    i = cc.UserDefault:getInstance():getIntegerForKey("integer")
    cclog("integer is %d", i)

    f = cc.UserDefault:getInstance():getFloatForKey("float")
    cclog("float is %f", f)

    b = cc.UserDefault:getInstance():getBoolForKey("bool")
    if b == true then
        cclog("bool is true")
    else
        cclog("bool is false")
    end
end

function UserDefaultTestMain()
    local ret = cc.Scene:create()
    local s = cc.Director:getInstance():getWinSize()
    local  label = cc.Label:createWithTTF("UserDefault test see log", s_arialPath, 28)
    ret:addChild(label, 0)
    label:setAnchorPoint(cc.p(0.5, 0.5))
    label:setPosition( cc.p(s.width/2, s.height-50) )
    ret:addChild(CreateBackMenuItem())
    doTest()
    return ret
end
