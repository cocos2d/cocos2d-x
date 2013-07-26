-- enable log


local function doTest()
    cclog("********************** init value ***********************")

    -- set default value

    CCUserDefault:getInstance():setStringForKey("string", "value1")
    CCUserDefault:getInstance():setIntegerForKey("integer", 10)
    CCUserDefault:getInstance():setFloatForKey("float", 2.3)
    CCUserDefault:getInstance():setDoubleForKey("double", 2.4)
    CCUserDefault:getInstance():setBoolForKey("bool", true)

    -- print value

    local ret = CCUserDefault:getInstance():getStringForKey("string")
    cclog("string is %s", ret)

    local d = CCUserDefault:getInstance():getDoubleForKey("double")
    cclog("double is %f", d)

    local i = CCUserDefault:getInstance():getIntegerForKey("integer")
    cclog("integer is %d", i)

    local f = CCUserDefault:getInstance():getFloatForKey("float")
    cclog("float is %f", f)

    local b = CCUserDefault:getInstance():getBoolForKey("bool")
    if b == true then
        cclog("bool is true")
    else
        cclog("bool is false")
    end

    --CCUserDefault:getInstance():flush()

    cclog("********************** after change value ***********************")

    -- change the value

    CCUserDefault:getInstance():setStringForKey("string", "value2")
    CCUserDefault:getInstance():setIntegerForKey("integer", 11)
    CCUserDefault:getInstance():setFloatForKey("float", 2.5)
    CCUserDefault:getInstance():setDoubleForKey("double", 2.6)
    CCUserDefault:getInstance():setBoolForKey("bool", false)

    CCUserDefault:getInstance():flush()

    -- print value

    ret = CCUserDefault:getInstance():getStringForKey("string")
    cclog("string is %s", ret)

    d = CCUserDefault:getInstance():getDoubleForKey("double")
    cclog("double is %f", d)

    i = CCUserDefault:getInstance():getIntegerForKey("integer")
    cclog("integer is %d", i)

    f = CCUserDefault:getInstance():getFloatForKey("float")
    cclog("float is %f", f)

    b = CCUserDefault:getInstance():getBoolForKey("bool")
    if b == true then
        cclog("bool is true")
    else
        cclog("bool is false")
    end
end

function UserDefaultTestMain()
    local ret = CCScene:create()
    local s = CCDirector:getInstance():getWinSize()
    local  label = CCLabelTTF:create("CCUserDefault test see log", "Arial", 28)
    ret:addChild(label, 0)
    label:setPosition( CCPoint(s.width/2, s.height-50) )
    doTest()
    return ret
end
