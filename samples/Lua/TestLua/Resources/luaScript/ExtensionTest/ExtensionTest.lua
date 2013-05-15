local LINE_SPACE = 40
local kItemTagBasic = 1000

local ExtensionTestEnum = 
{
    TEST_NOTIFICATIONCENTER = 0,
    TEST_CCCONTROLBUTTON    = 1,
    TEST_COCOSBUILDER       = 2,
    TEST_HTTPCLIENT         = 3,
    --TRAGET_PLATFORM
    TEST_EDITBOX            = 4,
	TEST_TABLEVIEW          = 5,
    TEST_MAX_COUNT          = 6,
}

local testsName =
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "CocosBuilderTest",
    "HttpClientTest",
    "EditBoxTest",
    "TableViewTest",
}

--Create toMainLayr MenuItem
function CreateExtensionsBasicLayerMenu(pMenu)
	if nil == pMenu then
		return
	end
	local function toMainLayer()
       local pScene = ExtensionsTestMain()
       if pScene ~= nil then
           CCDirector:sharedDirector():replaceScene(pScene)
       end
    end	
    --Create BackMneu
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
   	local pMenuItemFont = CCMenuItemFont:create("Back")
    pMenuItemFont:setPosition(ccp(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    pMenuItemFont:registerScriptTapHandler(toMainLayer)
    pMenu:addChild(pMenuItemFont)
end

-------------------------------------
--  Control Extensions Test
-------------------------------------
local ControlExtensionsTestEnum = 
{
    kCCControlSliderTest 			= 0,
    kCCControlColourPickerTest		= 1,
    kCCControlSwitchTest			= 2,
    kCCControlButtonTest_HelloVariableSize = 3,
    kCCControlButtonTest_Event		= 4,
    kCCControlButtonTest_Styling    = 5,
    kCCControlPotentiometerTest		= 6,
    kCCControlStepperTest			= 7,
    kCCControlTestMax               = 8
}

local ControlExtensionsTestArray = 
{
	"CCControlSliderTest",
    "ControlColourPickerTest",
    "ControlSwitchTest",
    "ControlButtonTest_HelloVariableSize",
    "ControlButtonTest_Event",
    "ControlButtonTest_Styling",
    "ControlPotentiometerTest",
    "CCControlStepperTest",
}
local function runCCControlTest()
	local nMaxCases = ControlExtensionsTestEnum.kCCControlTestMax
	--kCCControlSliderTest
    local nCurCase  = ControlExtensionsTestEnum.kCCControlButtonTest_HelloVariableSize
    local pSceneTitleLabel = nil
    
    local function GetSceneTitleLabel()
    	return pSceneTitleLabel
    end
    
    local function SetSceneTitleLabel(pLabel)
    	pSceneTitleLabel = pLabel
    end
    
    local function GetControlExtensionsTitle()
    	return ControlExtensionsTestArray[nCurCase + 1]
    end
    
    local pNewScene = CCScene:create()
    
	local function CreateBasicMenu(pMenu)
		if nil == pMenu then
			return
		end
  
    	local function backCallback()
    		nCurCase = nCurCase - 1
    		if nCurCase < 0 then
    			nCurCase = nCurCase + nMaxCases
    		end
 --   				ShowCurrentTest()
    	end
    
    	local function restartCallback()
--    		 ShowCurrentTest()
    	end
    
    	local function nextCallback()
    		  nCurCase = nCurCase + 1
    		  --No check nMaxCases
    		  nCurCase = nCurCase % nMaxCases
--    		  ShowCurrentTest()
   		end
   				
    	local size = CCDirector:sharedDirector():getWinSize()
    	local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    	item1:registerScriptTapHandler(backCallback)
    	pMenu:addChild(item1,kItemTagBasic)
    	local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    	item2:registerScriptTapHandler(restartCallback)
    	pMenu:addChild(item2,kItemTagBasic)
    	local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    	pMenu:addChild(item3,kItemTagBasic) 
    	item3:registerScriptTapHandler(nextCallback)
    			
    	local size = CCDirector:sharedDirector():getWinSize()
    	item1:setPosition(CCPointMake(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    	item2:setPosition(CCPointMake(size.width / 2, item2:getContentSize().height / 2))
    	item3:setPosition(CCPointMake(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    		 
	end
	
	local function BaseInitSceneLayer(pLayer,pStrTitle)
		if nil == pLayer then
			return
		end
		--Add Menu
		local pToMainMenu = CCMenu:create()
    	CreateExtensionsBasicLayerMenu(pToMainMenu)
    	pToMainMenu:setPosition(ccp(0, 0))
    	pLayer:addChild(pToMainMenu,10)
    	
    	--Add the generated background
        local pBackground = CCSprite:create("extensions/background.png")
        pBackground:setPosition(VisibleRect:center())
        pLayer:addChild(pBackground)
        
        --Add the ribbon
        local pRibbon = CCScale9Sprite:create("extensions/ribbon.png", CCRectMake(1, 1, 48, 55))
        pRibbon:setContentSize(CCSizeMake(VisibleRect:getVisibleRect().size.width, 57))
        pRibbon:setPosition(ccp(VisibleRect:center().x, VisibleRect:top().y - pRibbon:getContentSize().height / 2.0))
        pLayer:addChild(pRibbon)
        
        --Add the title
        pSceneTitleLabel = CCLabelTTF:create("Title", "Arial", 12)
        pSceneTitleLabel:setPosition(ccp (VisibleRect:center().x, VisibleRect:top().y - pSceneTitleLabel:getContentSize().height / 2 - 5))
        pLayer:addChild(pSceneTitleLabel, 1)
        pSceneTitleLabel:setString(pStrTitle)
    	
    	local pOperateMenu = CCMenu:create()
    	CreateBasicMenu(pOperateMenu)
    	pOperateMenu:setPosition(ccp(0, 0))
		pLayer:addChild(pOperateMenu,1)		
	end
	--Hvs:HelloVariableSize
	local function HvsStandardButtonWithTitle(pStrTitle)
	    -- Creates and return a button with a default background and title color. 
    	local pBackgroundButton = CCScale9Sprite:create("extensions/button.png")
    	local pBackgroundHighlightedButton = CCScale9Sprite:create("extensions/buttonHighlighted.png")
    
    	pTitleButton = CCLabelTTF:create(pStrTitle, "Marker Felt", 30)

    	pTitleButton:setColor(ccc3(159, 168, 176))
    
    	local pButton = CCControlButton:create(pTitleButton, pBackgroundButton)
    	pButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, CCControlStateHighlighted)
    	print(CCControlStateHighlighted)
    	print(pButton:getZOrder()) 
    	pButton:setTitleColorForState(ccc3(255,255,255), CCControlStateHighlighted)
    
    	return pButton
	end
	
	local function InitHelloVariableSize(pLayer)
		local screenSize = CCDirector:sharedDirector():getWinSize()
		local strArray   = CCArray:create()
		strArray:addObject(CCString:create("Hello"))
		strArray:addObject(CCString:create("Variable"))
		strArray:addObject(CCString:create("Size"))
		strArray:addObject(CCString:create("!"))
		
		local pNode = CCNode:create()
		pLayer:addChild(pNode,1)
		local dTotalWidth = 0
		local dHeight     = 0
		local pObj        = nil
		
		local i = 0
    	local nLen = strArray:count()
    	for i = 0, nLen - 1 do
        	pObj = tolua.cast(strArray:objectAtIndex(i), "CCString")
        	--Creates a button with this string as title
            local pButton = HvsStandardButtonWithTitle(pObj:getCString())	
            pButton:setPosition(ccp (dTotalWidth + pButton:getContentSize().width / 2, pButton:getContentSize().height / 2))
            pNode:addChild(pButton)
            
            --Compute the size of the layer
            dHeight = pButton:getContentSize().height
            dTotalWidth = dTotalWidth + pButton:getContentSize().width
    	end
		
		pNode:setAnchorPoint(ccp (0.5, 0.5))
        pNode:setContentSize(CCSizeMake(dTotalWidth, dHeight))
        pNode:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        
        --Add the black background
        local pBackground = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(CCSizeMake(dTotalWidth + 14, dHeight + 14))
        pBackground:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pBackground)
	end
	
	local function InitSpecialSceneLayer(pLayer)
		if ControlExtensionsTestEnum.kCCControlSliderTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlColourPickerTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlSwitchTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_HelloVariableSize == nCurCase then
    		   InitHelloVariableSize(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_Event == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_Styling == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlPotentiometerTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlStepperTest == nCurCase then
    	end
	end
    
    local function CurrentControlScene()
    	if ControlExtensionsTestEnum.kCCControlSliderTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlColourPickerTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlSwitchTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_HelloVariableSize == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_Event == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_Styling == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlPotentiometerTest == nCurCase then
    	elseif ControlExtensionsTestEnum.kCCControlStepperTest == nCurCase then
    	end
    end
    
    local pNewLayer = CCLayer:create()
    BaseInitSceneLayer(pNewLayer,GetControlExtensionsTitle())
    InitSpecialSceneLayer(pNewLayer)
	pNewScene:addChild(pNewLayer)
	
	return pNewScene
end

local CreateExtensionsTestTable = 
{
	runNotificationCenterTest,
	runCCControlTest,
	runCocosBuilder,
	runHttpClientTest,
	runEditBoxTest,
	runTableViewTest,	
}

local s = CCDirector:sharedDirector():getWinSize()

local function ExtensionsMainLayer()
	
	local function CreateExtensionsTestScene(nPerformanceNo)
	  	local pNewscene = CreateExtensionsTestTable[nPerformanceNo]()
  		return pNewscene
	end
	
	local function menuCallback(tag, pMenuItem)
		local scene = nil
    	local nIdx = pMenuItem:getZOrder() - kItemTagBasic
		local ExtensionsTestScene = CreateExtensionsTestScene(nIdx)
    	if nil ~= ExtensionsTestScene then
         	CCDirector:sharedDirector():replaceScene(ExtensionsTestScene)
    	end
	end
	
	local layer = CCLayer:create()
	local menu = CCMenu:create()
    menu:setPosition(CCPointMake(0, 0))
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    for i = 1, ExtensionTestEnum.TEST_MAX_COUNT do
		local item = CCMenuItemFont:create(testsName[i])
	    item:registerScriptTapHandler(menuCallback)
        item:setPosition(s.width / 2, s.height - i * LINE_SPACE)
        menu:addChild(item, kItemTagBasic + i)
	end

    layer:addChild(menu)

	return layer
end

-------------------------------------
--  Extensions Test
-------------------------------------
function ExtensionsTestMain()
	local scene = CCScene:create()

	scene:addChild(ExtensionsMainLayer())
	scene:addChild(CreateBackMenuItem())

	return scene
end
