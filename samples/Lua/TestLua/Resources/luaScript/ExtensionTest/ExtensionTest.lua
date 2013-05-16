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
    local nCurCase  = ControlExtensionsTestEnum.kCCControlSliderTest
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
 			CurrentControlScene()
    	end
    
    	local function restartCallback()
			CurrentControlScene()
    	end
    
    	local function nextCallback()
    		  nCurCase = nCurCase + 1
    		  --No check nMaxCases
    		  nCurCase = nCurCase % nMaxCases
			  CurrentControlScene()
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
	
	local function InitSliderTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = CCDirector:sharedDirector():getWinSize()
		--Add a label in which the slider value will be displayed
		local pDisplayValueLabel = CCLabelTTF:create("Move the slider thumb!\nThe lower slider is restricted." ,"Marker Felt", 32)
        pDisplayValueLabel:retain()
        pDisplayValueLabel:setAnchorPoint(ccp(0.5, -1.0))
        pDisplayValueLabel:setPosition(ccp(screenSize.width / 1.7, screenSize.height / 2.0))
        pLayer:addChild(pDisplayValueLabel)
        
        --Add the slider
        local pSlider = CCControlSlider:create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png")
        pSlider:setAnchorPoint(ccp(0.5, 1.0))
        pSlider:setMinimumValue(0.0) 
        pSlider:setMaximumValue(5.0) 
        pSlider:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0 + 16))
		pSlider:setTag(1)
        
        --When the value of the slider will change, the given selector will be call
        --slider:addTargetWithActionForControlEvents(pLayer, cccontrol_selector(CCControlSliderTest:valueChanged), CCControlEventValueChanged)
		
		local pRestrictSlider = CCControlSlider:create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png")
        pRestrictSlider:setAnchorPoint(ccp(0.5, 1.0))
        pRestrictSlider:setMinimumValue(0.0) 
        pRestrictSlider:setMaximumValue(5.0) 
		pRestrictSlider:setMaximumAllowedValue(4.0)
		pRestrictSlider:setMinimumAllowedValue(1.5)
		pRestrictSlider:setValue(3.0)
        pRestrictSlider:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0 - 24))
		pRestrictSlider:setTag(2)
		
		--same with restricted
		--restrictSlider:addTargetWithActionForControlEvents(pLayer, cccontrol_selector(CCControlSliderTest:valueChanged), CCControlEventValueChanged)
	    pLayer:addChild(pSlider)    
		pLayer:addChild(pRestrictSlider)
	end
	
	--ColourPickerTest
	local function InitColourPickerTest(pLayer)
		if nil == pLayer then
			return
		end
		local screenSize = CCDirector:sharedDirector():getWinSize()

        local pNode  = CCNode:create()
        pNode:setPosition(ccp (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0

        --Create the colour picker
        local pColourPicker = CCControlColourPicker:create()
        pColourPicker:setColor(ccc3(37, 46, 252))
        pColourPicker:setPosition(ccp (pColourPicker:getContentSize().width / 2, 0))
        pNode:addChild(pColourPicker)
        
        --Add the target-action pair
        --colourPicker:addTargetWithActionForControlEvents(pLayer, cccontrol_selector(CCControlColourPickerTest:colourValueChanged), CCControlEventValueChanged)
	
	    dLayer_width = dLayer_width + pColourPicker:getContentSize().width
	    
	   --Add the black background for the text
        local pBackground = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(CCSizeMake(150, 50))
        pBackground:setPosition(ccp(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        local pColorLabel = CCLabelTTF:create("#color", "Marker Felt", 30)
        pColorLabel:retain()
		pColorLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pColorLabel)
        
        --Set the layer size
        pNode:setContentSize(CCSizeMake(dLayer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))

        --Update the color text
--      colourValueChanged(pColourPicker, CCControlEventValueChanged)
	end
	
	--SwitchTest
	local function InitSwitchTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = CCDirector:sharedDirector():getWinSize()
        
        local pNode = CCNode:create()
        pNode:setPosition(ccp (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0
        
        --Add the black background for the text
        local pBackground = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(CCSizeMake(80, 50))
        pBackground:setPosition(ccp(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)       
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        local pDisplayValueLabel  = CCLabelTTF:create("#color" ,"Marker Felt" ,30)
        pDisplayValueLabel:retain()

        pDisplayValueLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pDisplayValueLabel)
        
        --Create the switch
        local pSwitchControl = CCControlSwitch:create(
                CCSprite:create("extensions/switch-mask.png"),
                CCSprite:create("extensions/switch-on.png"),
                CCSprite:create("extensions/switch-off.png"),
                CCSprite:create("extensions/switch-thumb.png"),
                CCLabelTTF:create("On", "Arial-BoldMT", 16),
                CCLabelTTF:create("Off", "Arial-BoldMT", 16)
            )
        pSwitchControl:setPosition(ccp (dLayer_width + 10 + pSwitchControl:getContentSize().width / 2, 0))
        pNode:addChild(pSwitchControl)

 --     pSwitchControl:addTargetWithActionForControlEvents(pLayer, cccontrol_selector(CCControlSwitchTest:valueChanged), CCControlEventValueChanged)
        
        --Set the layer size
        pNode:setContentSize(CCSizeMake(dLayer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        
        --Update the value label
        --valueChanged(switchControl, CCControlEventValueChanged)
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
    	pButton:setTitleColorForState(ccc3(255,255,255), CCControlStateHighlighted)
    
    	return pButton
	end
	
	local function InitHelloVariableSize(pLayer)
		if nil == pLayer then
			return
		end
		
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
        	--Creates a button with pLayer string as title
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
	
	local function StylingStandardButtonWithTitle(pStrTitle)
    	local pBackgroundButton = CCScale9Sprite:create("extensions/button.png")
    	pBackgroundButton:setPreferredSize(CCSizeMake(45, 45)) 
    	local pBackgroundHighlightedButton = CCScale9Sprite:create("extensions/buttonHighlighted.png")
    	pBackgroundHighlightedButton:setPreferredSize(CCSizeMake(45, 45)) 
    
        local pTitleButton = CCLabelTTF:create(pStrTitle, "Marker Felt", 30)

    	pTitleButton:setColor(ccc3(159, 168, 176))
    
    	local pButton = CCControlButton:create(pTitleButton, pBackgroundButton)
        pButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, CCControlStateHighlighted)
    	pButton:setTitleColorForState(ccc3(255,255,255), CCControlStateHighlighted)
    
        return pButton
	end
	
	local function InitStyling(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = CCDirector:sharedDirector():getWinSize()

        local pNode = CCNode:create()
        pLayer:addChild(pNode, 1)
        
        local nSpace = 10 
        
        local nMax_w = 0
        local nMax_h = 0
        local i = 0
        local j = 0
        for i = 0, 2 do
          for j = 0, 2 do
          	    --Add the buttons
          	    local strFmt = string.format("%d",math.random(0,32767) % 30)
                local pButton = StylingStandardButtonWithTitle(CCString:create(strFmt):getCString())
                pButton:setAdjustBackgroundImage(false)                                                  
                pButton:setPosition(ccp (pButton:getContentSize().width / 2 + (pButton:getContentSize().width + nSpace) * i,
                                         pButton:getContentSize().height / 2 + (pButton:getContentSize().height + nSpace) * j))
                
                pNode:addChild(pButton)
                
                nMax_w = math.max(pButton:getContentSize().width * (i + 1) + nSpace  * i, nMax_w)
                nMax_h = math.max(pButton:getContentSize().height * (j + 1) + nSpace * j, nMax_h)
          end
        end

        
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        pNode:setContentSize(CCSizeMake(nMax_w, nMax_h))
        pNode:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        
        --Add the black background
        local pBackgroundButton = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackgroundButton:setContentSize(CCSizeMake(nMax_w + 14, nMax_h + 14))
        pBackgroundButton:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pBackgroundButton)
	end
	
	local function InitButtonTestEvent(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = CCDirector:sharedDirector():getWinSize()

        --Add a label in which the button events will be displayed
        local pDisplayValueLabel = nil
        pDisplayValueLabel = CCLabelTTF:create("No Event", "Marker Felt", 32)
        pDisplayValueLabel:setAnchorPoint(ccp(0.5, -1))
       	pDisplayValueLabel:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pDisplayValueLabel, 1)
        
        --Add the button
        local pBackgroundButton            = CCScale9Sprite:create("extensions/button.png")
        local pBackgroundHighlightedButton = CCScale9Sprite:create("extensions/buttonHighlighted.png")
        
        local pTitleButtonLabel = CCLabelTTF:create("Touch Me!", "Marker Felt", 30)
        pTitleButtonLabel:setColor(ccc3(159, 168, 176))
        
        local pControlButton = CCControlButton:create(pTitleButtonLabel, pBackgroundButton)
        pControlButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, CCControlStateHighlighted)
        pControlButton:setTitleColorForState(ccc3(255, 255, 255), CCControlStateHighlighted)
        
        pControlButton:setAnchorPoint(ccp(0.5, 1))
        pControlButton:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pControlButton, 1)
		
		--Add the black background
        local pBackgroundButton = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackgroundButton:setContentSize(CCSizeMake(300, 170))
        pBackgroundButton:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pBackgroundButton)
	end
	--PotentiometerTest
	local function InitPotentiometerTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = CCDirector:sharedDirector():getWinSize()
        
        local pNode = CCNode:create()
        pNode:setPosition(ccp (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0
        
        -- Add the black background for the text
        local pBackground  = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(CCSizeMake(80, 50))
        pBackground:setPosition(ccp(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)
        
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        local pDisplayValueLabel = CCLabelTTF:create("", "HelveticaNeue-Bold", 30)
        pDisplayValueLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pDisplayValueLabel)
		
        -- Add the slider
        local pPotentiometer = CCControlPotentiometer:create("extensions/potentiometerTrack.png","extensions/potentiometerProgress.png"
                                                                               ,"extensions/potentiometerButton.png")
        pPotentiometer:setPosition(ccp (dLayer_width + 10 + pPotentiometer:getContentSize().width / 2, 0))

        -- When the value of the slider will change, the given selector will be call
--        pPotentiometer:addTargetWithActionForControlEvents(pLayer, cccontrol_selector(CCControlPotentiometerTest:valueChanged), CCControlEventValueChanged)
        
		pNode:addChild(pPotentiometer)
        
        dLayer_width = dLayer_width + pPotentiometer:getContentSize().width
        
        -- Set the layer size
        pNode:setContentSize(CCSizeMake(dLayer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        
        -- Update the value label
        --pLayer:valueChanged(potentiometer, CCControlEventValueChanged)
	end
	
	local function InitStepperTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = CCDirector:sharedDirector():getWinSize()
        
        local pNode = CCNode:create()
        pNode:setPosition(ccp (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local layer_width          = 0
        
        -- Add the black background for the text
        local background  = CCScale9Sprite:create("extensions/buttonBackground.png")
        background:setContentSize(CCSizeMake(100, 50))
        background:setPosition(ccp(layer_width + background:getContentSize().width / 2.0, 0))
        pNode:addChild(background)
        
        local pDisplayValueLabel =  CCLabelTTF:create("0", "HelveticaNeue-Bold", 30)

        pDisplayValueLabel:setPosition(background:getPosition())
        pNode:addChild(pDisplayValueLabel)
        
        layer_width   = layer_width + background:getContentSize().width
        
        local minusSprite       = CCSprite:create("extensions/stepper-minus.png")
    	local plusSprite        = CCSprite:create("extensions/stepper-plus.png")
    
        local stepper   = CCControlStepper:create(minusSprite, plusSprite)
        stepper:setPosition(ccp (layer_width + 10 + stepper:getContentSize().width / 2, 0))
--        stepper:addTargetWithActionForControlEvents(pLayer, cccontrol_selector(CCControlStepperTest:valueChanged), CCControlEventValueChanged)
        pNode:addChild(stepper)
        
        layer_width  = layer_width + stepper:getContentSize().width
        
        -- Set the layer size
        pNode:setContentSize(CCSizeMake(layer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        
        -- Update the value label
--      pLayer:valueChanged(stepper, CCControlEventValueChanged)
	end
	
	local function InitSpecialSceneLayer(pLayer)
		if ControlExtensionsTestEnum.kCCControlSliderTest == nCurCase then
			   InitSliderTest(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlColourPickerTest == nCurCase then
    		   InitColourPickerTest(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlSwitchTest == nCurCase then
    	       InitSwitchTest(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_HelloVariableSize == nCurCase then
    		   InitHelloVariableSize(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_Event == nCurCase then
    		   InitButtonTestEvent(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlButtonTest_Styling == nCurCase then
    		   InitStyling(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlPotentiometerTest == nCurCase then
    		   InitPotentiometerTest(pLayer)
    	elseif ControlExtensionsTestEnum.kCCControlStepperTest == nCurCase then
    	       InitStepperTest(pLayer)
    	end
	end
    
    function CurrentControlScene()
    	pNewScene = nil
		pNewScene = CCScene:create()
		local pNewLayer = CCLayer:create()
    	BaseInitSceneLayer(pNewLayer,GetControlExtensionsTitle())
    	InitSpecialSceneLayer(pNewLayer)
		pNewScene:addChild(pNewLayer)
		if nil ~= pNewScene then
		    CCDirector:sharedDirector():replaceScene(pNewScene)
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
