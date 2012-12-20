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
