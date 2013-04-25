-- enable log


local function doTest()
    cclog("********************** init value ***********************")

    -- set default value

    CCUserDefault:sharedUserDefault():setStringForKey("string", "value1")
    CCUserDefault:sharedUserDefault():setIntegerForKey("integer", 10)
    CCUserDefault:sharedUserDefault():setFloatForKey("float", 2.3)
    CCUserDefault:sharedUserDefault():setDoubleForKey("double", 2.4)
    CCUserDefault:sharedUserDefault():setBoolForKey("bool", true)

    -- print value

    local ret = CCUserDefault:sharedUserDefault():getStringForKey("string")
    cclog("string is %s", ret)

    local d = CCUserDefault:sharedUserDefault():getDoubleForKey("double")
    cclog("double is %f", d)

    local i = CCUserDefault:sharedUserDefault():getIntegerForKey("integer")
    cclog("integer is %d", i)

    local f = CCUserDefault:sharedUserDefault():getFloatForKey("float")
    cclog("float is %f", f)

    local b = CCUserDefault:sharedUserDefault():getBoolForKey("bool")
    if b == true then
        cclog("bool is true")
    else
        cclog("bool is false")
    end

    --CCUserDefault:sharedUserDefault():flush()

    cclog("********************** after change value ***********************")

    -- change the value

    CCUserDefault:sharedUserDefault():setStringForKey("string", "value2")
    CCUserDefault:sharedUserDefault():setIntegerForKey("integer", 11)
    CCUserDefault:sharedUserDefault():setFloatForKey("float", 2.5)
    CCUserDefault:sharedUserDefault():setDoubleForKey("double", 2.6)
    CCUserDefault:sharedUserDefault():setBoolForKey("bool", false)

    CCUserDefault:sharedUserDefault():flush()

    -- print value

    ret = CCUserDefault:sharedUserDefault():getStringForKey("string")
    cclog("string is %s", ret)

    d = CCUserDefault:sharedUserDefault():getDoubleForKey("double")
    cclog("double is %f", d)

    i = CCUserDefault:sharedUserDefault():getIntegerForKey("integer")
    cclog("integer is %d", i)

    f = CCUserDefault:sharedUserDefault():getFloatForKey("float")
    cclog("float is %f", f)

    b = CCUserDefault:sharedUserDefault():getBoolForKey("bool")
    if b == true then
        cclog("bool is true")
    else
        cclog("bool is false")
    end
end

function UserDefaultTestMain()
    local ret = CCScene:create()
    local s = CCDirector:sharedDirector():getWinSize()
    local  label = CCLabelTTF:create("CCUserDefault test see log", "Arial", 28)
    ret:addChild(label, 0)
    label:setPosition( ccp(s.width/2, s.height-50) )
    doTest()
    return ret
end
