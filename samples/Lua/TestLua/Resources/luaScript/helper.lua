CC_CONTENT_SCALE_FACTOR = function()
    return CCDirector:sharedDirector():getContentScaleFactor()
end


CC_POINT_PIXELS_TO_POINTS = function(pixels)
    return ccp(pixels.x/CC_CONTENT_SCALE_FACTOR(), pixels.y/CC_CONTENT_SCALE_FACTOR())
end

CC_POINT_POINTS_TO_PIXELS = function(points)
    return ccp(points.x*CC_CONTENT_SCALE_FACTOR(), points.y*CC_CONTENT_SCALE_FACTOR())
end


-- cclog
cclog = function(...)
    print(string.format(...))
end

-- change table to enum type
function CreateEnumTable(tbl, index)
    local enumTable = {}
    local enumIndex = index or -1
    for i, v in ipairs(tbl) do
        enumTable[v] = enumIndex + i
    end
    return enumTable
end

-- back menu callback
local function MainMenuCallback()
    local scene = CCScene:create()
    scene:addChild(CreateTestMenu())

    CCDirector:sharedDirector():replaceScene(scene)
end

-- add the menu item for back to main menu
function CreateBackMenuItem()
    local label = CCLabelTTF:create("MainMenu", "Arial", 20)
    local MenuItem = CCMenuItemLabel:create(label)
    MenuItem:registerScriptTapHandler(MainMenuCallback)

    local s = CCDirector:sharedDirector():getWinSize()
    local Menu = CCMenu:create()
    Menu:addChild(MenuItem)
    Menu:setPosition(0, 0)
    MenuItem:setPosition(s.width - 50, 25)

    return Menu
end

Helper = {
    index = 1,
    createFunctioinTable = nil,
    currentLayer = nil,
    titleLabel = nil,
    subtitleLabel = nil
}
function Helper.nextAction()
    Helper.index = Helper.index + 1
    if Helper.index > table.getn(Helper.createFunctionTable) then
        Helper.index = 1
    end

    return Helper.newScene()
end

function  Helper.backAction()
    Helper.index = Helper.index - 1
    if Helper.index == 0 then
        Helper.index = table.getn(Helper.createFunctionTable)
    end

    return Helper.newScene()
end

function Helper.restartAction()
    return Helper.newScene()
end

function Helper.newScene()
    local scene = CCScene:create()
    Helper.currentLayer = Helper.createFunctionTable[Helper.index]()
    scene:addChild(Helper.currentLayer)
    scene:addChild(CreateBackMenuItem())

    CCDirector:sharedDirector():replaceScene(scene)
end

function Helper.initWithLayer(layer)
    Helper.currentLayer = layer

    local size = CCDirector:sharedDirector():getWinSize()
    Helper.titleLabel = CCLabelTTF:create("", "Arial", 28)
    layer:addChild(Helper.titleLabel, 1)
    Helper.titleLabel:setPosition(size.width / 2, size.height - 50)

    Helper.subtitleLabel = CCLabelTTF:create("", "Thonburi", 16)
    layer:addChild(Helper.subtitleLabel, 1)
    Helper.subtitleLabel:setPosition(size.width / 2, size.height - 80)

    -- menu
    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    item1:registerScriptTapHandler(Helper.backAction)
    item2:registerScriptTapHandler(Helper.restartAction)
    item3:registerScriptTapHandler(Helper.nextAction)

    local menu = CCMenu:create()
    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)
    menu:setPosition(CCPointMake(0, 0))
    item1:setPosition(CCPointMake(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(size.width / 2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    layer:addChild(menu, 1)

    local background = CCLayer:create()
    layer:addChild(background, -10)
end

function createTestLayer(title, subtitle)
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    local titleStr = title == nil and "No title" or title
    local subTitleStr = subtitle  == nil and "" or subtitle
    Helper.titleLabel:setString(titleStr)
    Helper.subtitleLabel:setString(subTitleStr)
    return layer
end
