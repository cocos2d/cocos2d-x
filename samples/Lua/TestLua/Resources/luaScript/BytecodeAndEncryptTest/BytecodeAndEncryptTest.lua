local targetPlatform = CCApplication:sharedApplication():getTargetPlatform()
local isIOS64bit     = CCApplication:sharedApplication():isIOS64bit()
require("luaScript/BytecodeAndEncryptTest/EncryptFileTest")

if (kTargetWindows == targetPlatform) or (kTargetMacOS == targetPlatform) or (kTargetAndroid == targetPlatform) 
    or ((kTargetIphone == targetPlatform or kTargetIpad == targetPlatform) and isIOS64bit ~= true) then
require("luaScript/BytecodeAndEncryptTest/ByteCodeFileTest")
require("luaScript/BytecodeAndEncryptTest/ByteCodeAndEncryptFileTest")
end
 
local LINE_SPACE = 40
local ItemTagBasic = 1000

local ByteCodeEncryptEnum = 
{
    TEST_ENCRYPT  = 0,
    TEST_BYTECODE = 1,
    TEST_BYTECODE_ENCRYPT = 2,
    TEST_MAX_COUNT = 3,
}

local TestsName = 
{
    "EncryptFileTest",
    "ByteCodeFileTest",
    "ByteCodeAndEncryptFileTest",
}

local CreateByteCodeEncryptTestTable =
{
    runEncrypteFileTest,
    runByteCodeFileTest,
    runByteCodeAndEncryptFileTest,
}

local function byteCodeEncryptMainLayer()
    local size = CCDirector:sharedDirector():getWinSize()

    local function createByteCodeEncryptTestScene(index)
        local newScene = CreateByteCodeEncryptTestTable[index]()
        return newScene
    end

    local function menuCallback(tag, sender)
        local scene = nil
        local index = sender:getZOrder() - ItemTagBasic
        local byteCodeEncryptScene = createByteCodeEncryptTestScene(index)
        if nil ~= byteCodeEncryptScene then
            CCDirector:sharedDirector():replaceScene(byteCodeEncryptScene)
        end
    end

    local layer = CCLayer:create()
    local menu = CCMenu:create()
    menu:setPosition(0, 0)
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)

    for i = 1, ByteCodeEncryptEnum.TEST_MAX_COUNT do
        local item = CCMenuItemFont:create(TestsName[i])
        item:registerScriptTapHandler(menuCallback)
        item:setPosition(size.width / 2, size.height - i * LINE_SPACE)
        menu:addChild(item, ItemTagBasic + i)
        if (kTargetWindows == targetPlatform) or (kTargetMacOS == targetPlatform) or (kTargetAndroid == targetPlatform) 
          or ((kTargetIphone == targetPlatform or kTargetIpad == targetPlatform) and isIOS64bit ~= true) or 1 == i then
            item:setEnabled(true)
        else
            item:setEnabled(false)
        end
    end

    layer:addChild(menu)

    -- handling touch events
    local beginPos = {x = 0, y = 0}   
    local function onTouchMoved(tableArray)     
        local location = { x = tableArray[1], y = tableArray[2]}
        local nMoveY = location.y - beginPos.y 
        local curPosx, curPosy = menu:getPosition()
        local nextPosy = curPosy + nMoveY
        local winSize = CCDirector:sharedDirector():getWinSize()
        if nextPosy < 0 then
            menu:setPosition(0, 0)
            return
        end

        if nextPosy > ((ByteCodeEncryptEnum.TEST_MAX_COUNT + 1) * LINE_SPACE - winSize.height) then
            menu:setPosition(0, ((ByteCodeEncryptEnum.TEST_MAX_COUNT + 1) * LINE_SPACE - winSize.height))
            return
        end

        menu:setPosition(curPosx, nextPosy)
        beginPos = {x = location.x, y = location.y}
    end
    local function onTouchBegan(tableArray)
        beginPos.x = tableArray[1]
        beginPos.y = tableArray[2]
    end

    local function onTouch(eventType,tableArray)
        if eventType == "began" then
            return onTouchBegan(tableArray)
        elseif eventType == "moved" then
            return onTouchMoved(tableArray)
        end
    end

    layer:registerScriptTouchHandler(onTouch,true)

    return layer
end
-------------------------------------
--  ByteCodeEncrypt Test
-------------------------------------
function ByteCodeEncryptTestMain()
    local scene = CCScene:create()

    scene:addChild(byteCodeEncryptMainLayer())
    scene:addChild(CreateBackMenuItem())

    return scene
end
