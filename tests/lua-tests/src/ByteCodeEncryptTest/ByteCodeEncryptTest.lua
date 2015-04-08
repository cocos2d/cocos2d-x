local targetPlatform = cc.Application:getInstance():getTargetPlatform()
local is64BitIOSDevice     = cc.Application:getInstance():is64BitIOSDevice()

if cc.PLATFORM_OS_LINUX ~= targetPlatform and is64BitIOSDevice ~= true then
require("ByteCodeEncryptTest/ByteCodeTest")
require("ByteCodeEncryptTest/ByteCodeAndEncryptTest")
end

if (cc.PLATFORM_OS_IPHONE == targetPlatform or cc.PLATFORM_OS_IPAD == targetPlatform) and is64BitIOSDevice == true then
require("ByteCodeEncryptTest/ByteCodeAndEncryptTest-arm64")
require("ByteCodeEncryptTest/ByteCodeTest-arm64")
end

local LINE_SPACE = 40
local ItemTagBasic = 1000

local ByteCodeEncryptEnum = 
{
    TEST_BYTECODE = 0,
    TEST_BYTECODE_ENCRYPT = 1,
    TEST_MAX_COUNT = 2,
}

local TestsName = 
{
    "ByteCodeFileTest",
    "ByteCodeAndEncryptFileTest",
}

local CreateByteCodeEncryptTestTable =
{
    runByteCodeFileTest,
    runByteCodeAndEncryptFileTest,
}

local function byteCodeEncryptMainLayer()
    local size = cc.Director:getInstance():getWinSize()

    local function createByteCodeEncryptTestScene(index)
        local newScene = CreateByteCodeEncryptTestTable[index]()
        return newScene
    end

    local function menuCallback(tag, sender)
        local scene = nil
        local index = sender:getLocalZOrder() - ItemTagBasic
        local byteCodeEncryptScene = createByteCodeEncryptTestScene(index)
        if nil ~= byteCodeEncryptScene then
            cc.Director:getInstance():replaceScene(byteCodeEncryptScene)
        end
    end

    local layer = cc.Layer:create()
    local menu = cc.Menu:create()
    menu:setPosition(cc.p(0, 0))
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)

    for i = 1, ByteCodeEncryptEnum.TEST_MAX_COUNT do
        local item = cc.MenuItemFont:create(TestsName[i])
        item:registerScriptTapHandler(menuCallback)
        item:setPosition(size.width / 2, size.height - i * LINE_SPACE)
        menu:addChild(item, ItemTagBasic + i)
        if cc.PLATFORM_OS_LINUX == targetPlatform or is64BitIOSDevice == true then -- isIOS64bit
            item:setEnabled(false)
        end

        if (cc.PLATFORM_OS_IPHONE == targetPlatform or cc.PLATFORM_OS_IPAD == targetPlatform) and is64BitIOSDevice == true then
            item:setEnabled(true)
        end
    end

    layer:addChild(menu)

    -- handling touch events
    local beginPos = {x = 0, y = 0} 
    local function onTouchesBegan(touches, event)     
         beginPos = touches[1]:getLocation()
    end

    local function onTouchesMoved(touches, event)
        local location = touches[1]:getLocation()

        local nMoveY = location.y - beginPos.y
        local curPosx, curPosy = menu:getPosition()
        local nextPosy = curPosy + nMoveY
        local winSize = cc.Director:getInstance():getWinSize()
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

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCH_MOVED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    return layer
end
-------------------------------------
--  ByteCodeEncrypt Test
-------------------------------------
function ByteCodeEncryptTestMain()
    local scene = cc.Scene:create()

    scene:addChild(byteCodeEncryptMainLayer())
    scene:addChild(CreateBackMenuItem())

    return scene
end
