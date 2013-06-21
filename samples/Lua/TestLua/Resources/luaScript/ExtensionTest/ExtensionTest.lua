require "luaScript/ExtensionTest/CocosBuilderTest"
require "luaScript/ExtensionTest/WebProxyTest"

local LINE_SPACE = 40
local kItemTagBasic = 1000

local ExtensionTestEnum = 
{
    TEST_NOTIFICATIONCENTER = 0,
    TEST_CCCONTROLBUTTON    = 1,
    TEST_COCOSBUILDER       = 2,
    TEST_WEBSOCKET          = 3,
    TEST_EDITBOX            = 4,
	TEST_TABLEVIEW          = 5,
    TEST_MAX_COUNT          = 6,
}

local testsName =
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "CocosBuilderTest",
    "WebSocketTest",
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
--Notification Center Test
-------------------------------------
local NotificationCenterParam =
{
	kTagLight   = 100,
    kTagConnect =  200,

	MSG_SWITCH_STATE = "SwitchState"
}
local function runNotificationCenterTest()
		
		local pNewScene = CCScene:create()
		local pNewLayer = CCLayer:create()
		local function BaseInitSceneLayer(pLayer)
		  if nil == pLayer then
			  return
		  end
		  local s = CCDirector:sharedDirector():getWinSize()
    	
    	local function toggleSwitch(tag,menuItem)
    		local toggleItem = tolua.cast(menuItem,"CCMenuItemToggle")
    		local nIndex     = toggleItem:getSelectedIndex()
    		local selectedItem = toggleItem:selectedItem()
    		if 0 == nIndex  then
    			selectedItem = nil
    		end
    		CCNotificationCenter:sharedNotificationCenter():postNotification(NotificationCenterParam.MSG_SWITCH_STATE,selectedItem)
    	end
    	
    	local switchlabel1 = CCLabelTTF:create("switch off", "Marker Felt", 26)
    	local switchlabel2 = CCLabelTTF:create("switch on", "Marker Felt", 26)
    	local switchitem1  = CCMenuItemLabel:create(switchlabel1)
    	local switchitem2 = CCMenuItemLabel:create(switchlabel2)
    	local switchitem = CCMenuItemToggle:create(switchitem1)
    	switchitem:addSubItem(switchitem2)
    	switchitem:registerScriptTapHandler(toggleSwitch)
    	--turn on
    	switchitem:setSelectedIndex(1)
        local menu = CCMenu:create()
        menu:addChild(switchitem)
    	menu:setPosition(ccp(s.width/2+100, s.height/2))
   		pLayer:addChild(menu)

    	local menuConnect = CCMenu:create()
    	menuConnect:setPosition(ccp(0,0))
    	pLayer:addChild(menuConnect)
    	local i = 1
    	local bSwitchOn = false
    	local bConnectArray = 
    	{
    		false,
    		false,
    		false
    	}
    	
    	local lightArray = {}
    	
    	local function updateLightState()
    		for i = 1, 3 do 
    			if bSwitchOn and bConnectArray[i] then
    			    lightArray[i]:setOpacity(255)
    			else
        			lightArray[i]:setOpacity(50)
        		end
    		end
    	end
    	
    	local function switchStateChanged()
    		local nIndex = switchitem:getSelectedIndex()
    		
    		if 0 == nIndex then
    			bSwitchOn = false 
    		else
    			bSwitchOn = true 
    		end   		
    		updateLightState()
    	end
    		
    	local function setIsConnectToSwitch(pLight,bConnect,nIdx)
    		bConnectArray[nIdx]  = bConnect
    		print("come in")
    		if bConnect then
    			CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(pLight, switchStateChanged,NotificationCenterParam.MSG_SWITCH_STATE)
    		else
    			CCNotificationCenter:sharedNotificationCenter():unregisterScriptObserver(pLight,NotificationCenterParam.MSG_SWITCH_STATE)
    		end
    		updateLightState()
    	end
    	

    	for  i = 1, 3 do 		   	
        	lightArray[i] = CCSprite:create("Images/Pea.png")
       		lightArray[i]:setTag(NotificationCenterParam.kTagLight + i)
        	lightArray[i]:setPosition(ccp(100, s.height / 4 * i) )
        	pLayer:addChild(lightArray[i])
			
        	local connectlabel1 = CCLabelTTF:create("not connected", "Marker Felt", 26)
        	
        	local connectlabel2 = CCLabelTTF:create("connected", "Marker Felt", 26)
        	local connectitem1 = CCMenuItemLabel:create(connectlabel1)
        	local connectitem2 = CCMenuItemLabel:create(connectlabel2)
        	local connectitem = CCMenuItemToggle:create(connectitem1)
        	connectitem:addSubItem(connectitem2)
        
        	connectitem:setTag(NotificationCenterParam.kTagConnect+i)
        	
        	local function connectToSwitch(tag,menuItem)
    		   local connectMenuitem = tolua.cast(menuItem,"CCMenuItemToggle")
    		   local bConnected = true
    		   if connectMenuitem:getSelectedIndex() == 0 then
    		   	   bConnected = false
    		   end
    		   local nIdx = connectMenuitem:getTag()-NotificationCenterParam.kTagConnect 
    		   setIsConnectToSwitch(lightArray[nIdx],bConnected,nIdx)
    		end
    		
        	connectitem:registerScriptTapHandler(connectToSwitch)
        	local nX,nY = lightArray[i]:getPosition()
        	connectitem:setPosition(ccp(nX,nY+50))
            
            menuConnect:addChild(connectitem, 0,connectitem:getTag())
           
       		if  i == 2 then
            	connectitem:setSelectedIndex(1)
            end
            bConnectArray[i]   = false	
           	if 1 == connectitem:getSelectedIndex() then
           		bConnectArray[i]  = true 
           	end 	
    	end
    	
    	for i = 1, 3 do
    	   setIsConnectToSwitch(lightArray[i],bConnectArray[i],i)  
    	end
    	local toggleSelectIndex  = switchitem:getSelectedIndex()
    	local toggleSelectedItem = switchitem:selectedItem()
    	if 0 == toggleSelectIndex  then
    		toggleSelectedItem = nil
    	end
    	CCNotificationCenter:sharedNotificationCenter():postNotification(NotificationCenterParam.MSG_SWITCH_STATE, toggleSelectedItem)
    	
    	--for testing removeAllObservers */
    	local function doNothing()
    	end
    	CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(pNewLayer,doNothing, "random-observer1")
    	CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(pNewLayer,doNothing, "random-observer2")
    	CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(pNewLayer,doNothing, "random-observer3")
    	
    	local function CreateToMainMenu(pMenu)
		     if nil == pMenu then
				return
			 end
			 local function toMainLayer()
				local numObserversRemoved = CCNotificationCenter:sharedNotificationCenter():removeAllObservers(pNewLayer)
				if 3 ~= numObserversRemoved then
					print("All observers were not removed!")
				end
				
				for i = 1 , 3 do					 
					 if bConnectArray[i] then
					 	CCNotificationCenter:sharedNotificationCenter():unregisterScriptObserver(lightArray[i],NotificationCenterParam.MSG_SWITCH_STATE)
					 end   		    			
				end
				
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
	   --Add Menu
	   local pToMainMenu = CCMenu:create()
       CreateToMainMenu(pToMainMenu)
       pToMainMenu:setPosition(ccp(0, 0))
       pLayer:addChild(pToMainMenu,10)    	
	   end
    
    BaseInitSceneLayer(pNewLayer)
	pNewScene:addChild(pNewLayer)
	
	return pNewScene
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
        
        local function valueChanged(strEventName,pSender)
        	if nil == pSender or nil == pDisplayValueLabel then
        		return
        	end       	
        	local pControl = tolua.cast(pSender,"CCControlSlider")
        	local strFmt = nil
        	if pControl:getTag() == 1 then
        		strFmt = string.format("Upper slider value = %.02f",pControl:getValue())
        	elseif pControl:getTag() == 2 then
        		strFmt = string.format("Lower slider value = %.02f",pControl:getValue())
        	end
        	
        	if nil ~= strFmt then
        		pDisplayValueLabel:setString(CCString:create(strFmt):getCString())
        	end       	
        end
        --Add the slider
        local pSlider = CCControlSlider:create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png")
        pSlider:setAnchorPoint(ccp(0.5, 1.0))
        pSlider:setMinimumValue(0.0) 
        pSlider:setMaximumValue(5.0) 
        pSlider:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0 + 16))
		pSlider:setTag(1)
        
        --When the value of the slider will change, the given selector will be call
        pSlider:addHandleOfControlEvent(valueChanged, CCControlEventValueChanged)
		
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
		pRestrictSlider:addHandleOfControlEvent(valueChanged, CCControlEventValueChanged)
	    pLayer:addChild(pSlider)    
		pLayer:addChild(pRestrictSlider)
	end
	
	--ColourPickerTest
	local function InitColourPickerTest(pLayer)
		if nil == pLayer then
			return
		end
		local screenSize = CCDirector:sharedDirector():getWinSize()
		local pColorLabel = nil

        local pNode  = CCNode:create()
        pNode:setPosition(ccp (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0

        --Create the colour picker,pStrEventName not use
        local function colourValueChanged(pStrEventName,pSender)
        	if nil == pSender or nil == pColorLabel then
        		return
        	end
        	
        	local pPicker = tolua.cast(pSender,"CCControlColourPicker")
        	local strFmt  = string.format("#%02X%02X%02X",pPicker:getColor().r, pPicker:getColor().g, pPicker:getColor().b)
        	pColorLabel:setString(CCString:create(strFmt):getCString())       	
        end
        local pColourPicker = CCControlColourPicker:create()
        pColourPicker:setColor(ccc3(37, 46, 252))
        pColourPicker:setPosition(ccp (pColourPicker:getContentSize().width / 2, 0))
        pColourPicker:addHandleOfControlEvent(colourValueChanged, CCControlEventValueChanged)
        pNode:addChild(pColourPicker)     
	
	    dLayer_width = dLayer_width + pColourPicker:getContentSize().width
	    
	   --Add the black background for the text
        local pBackground = CCScale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(CCSizeMake(150, 50))
        pBackground:setPosition(ccp(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        pColorLabel = CCLabelTTF:create("#color", "Marker Felt", 30)
        pColorLabel:retain()
		pColorLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pColorLabel)
        
        --Set the layer size
        pNode:setContentSize(CCSizeMake(dLayer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))

        --Update the color text
	    colourValueChanged("", pColourPicker)
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
        local function valueChanged(strEventName,pSender)
        	if nil == pDisplayValueLabel or nil == pSender then
        		return
        	end
        	
        	local pControl = tolua.cast(pSender,"CCControlSwitch")
        	if pControl:isOn() then
        		pDisplayValueLabel:setString("On")
        	else
        		pDisplayValueLabel:setString("Off")
        	end
        end
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
        pSwitchControl:addHandleOfControlEvent(valueChanged, CCControlEventValueChanged)
        
        --Set the layer size
        pNode:setContentSize(CCSizeMake(dLayer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        
        --Update the value label
        valueChanged("", pSwitchControl)
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
        local function touchDownAction()
        	if nil == pDisplayValueLabel then
        		return
        	end       	
        	pDisplayValueLabel:setString(CCString:create("Touch Down"):getCString())
        end
        
        local function touchDragInsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Drag Inside"):getCString())
        end
        
        local function touchDragOutsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Drag Outside"):getCString())
        end
        
        local function touchDragEnterAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Drag Enter"):getCString())
        end
        
        local function touchDragExitAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Drag Exit"):getCString())
        end
        
        local function touchUpInsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Touch Up Inside."):getCString())
        end
        
        local function touchUpOutsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Touch Up Outside."):getCString())
        end
        
        local function touchCancelAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString(CCString:create("Touch Cancel"):getCString())
        end
        
        
        
        pControlButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, CCControlStateHighlighted)
        pControlButton:setTitleColorForState(ccc3(255, 255, 255), CCControlStateHighlighted)
        pControlButton:setAnchorPoint(ccp(0.5, 1))
        pControlButton:setPosition(ccp(screenSize.width / 2.0, screenSize.height / 2.0))
        pControlButton:addHandleOfControlEvent(touchDownAction,CCControlEventTouchDown)
        pControlButton:addHandleOfControlEvent(touchDragInsideAction,CCControlEventTouchDragInside)
        pControlButton:addHandleOfControlEvent(touchDragOutsideAction,CCControlEventTouchDragOutside)
        pControlButton:addHandleOfControlEvent(touchDragEnterAction,CCControlEventTouchDragEnter)
        pControlButton:addHandleOfControlEvent(touchDragExitAction,CCControlEventTouchDragExit)
        pControlButton:addHandleOfControlEvent(touchUpInsideAction,CCControlEventTouchUpInside)
        pControlButton:addHandleOfControlEvent(touchUpOutsideAction,CCControlEventTouchUpOutside)
        pControlButton:addHandleOfControlEvent(touchCancelAction,CCControlEventTouchCancel)
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
        local function valueChanged(strEventName,pSender)
        	if nil == pSender then
        		return
        	end
        	
        	local pControl = tolua.cast(pSender,"CCControlPotentiometer")
        	local strFmt = string.format("%0.2f",pControl:getValue())
        	pDisplayValueLabel:setString(CCString:create(strFmt):getCString())
        end
        local pPotentiometer = CCControlPotentiometer:create("extensions/potentiometerTrack.png","extensions/potentiometerProgress.png"
                                                                               ,"extensions/potentiometerButton.png")
        pPotentiometer:setPosition(ccp (dLayer_width + 10 + pPotentiometer:getContentSize().width / 2, 0))

        -- When the value of the slider will change, the given selector will be call
        pPotentiometer:addHandleOfControlEvent(valueChanged, CCControlEventValueChanged)
        
		pNode:addChild(pPotentiometer)
        
        dLayer_width = dLayer_width + pPotentiometer:getContentSize().width
        
        -- Set the layer size
        pNode:setContentSize(CCSizeMake(dLayer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        
        -- Update the value label
        valueChanged("", pPotentiometer)
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
    
    	local function valueChanged(strEventName,pSender)
    		if nil == pDisplayValueLabel or nil == pSender then
    			return
    		end
    		
    		local pControl = tolua.cast(pSender,"CCControlStepper")
    		local strFmt   = string.format("%0.02f",pControl:getValue() )
    		pDisplayValueLabel:setString(CCString:create(strFmt):getCString())
    	end
        local stepper   = CCControlStepper:create(minusSprite, plusSprite)
        stepper:setPosition(ccp (layer_width + 10 + stepper:getContentSize().width / 2, 0))
        stepper:addHandleOfControlEvent(valueChanged, CCControlEventValueChanged)
        pNode:addChild(stepper)
        
        layer_width  = layer_width + stepper:getContentSize().width
        
        -- Set the layer size
        pNode:setContentSize(CCSizeMake(layer_width, 0))
        pNode:setAnchorPoint(ccp (0.5, 0.5))
        
        -- Update the value label
        valueChanged("", stepper)
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

local function runEditBoxTest()
	local newScene = CCScene:create()
	local newLayer = CCLayer:create()
	local visibleOrigin = CCEGLView:sharedOpenGLView():getVisibleOrigin()
    local visibleSize = CCEGLView:sharedOpenGLView():getVisibleSize()
    
    local pBg = CCSprite:create("Images/HelloWorld.png")
    pBg:setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2))
    newLayer:addChild(pBg)
    
    local TTFShowEditReturn = CCLabelTTF:create("No edit control return!", "", 30)
    TTFShowEditReturn:setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50))
    newLayer:addChild(TTFShowEditReturn)
    
    -- Back Menu
	local pToMainMenu = CCMenu:create()
    CreateExtensionsBasicLayerMenu(pToMainMenu)
    pToMainMenu:setPosition(ccp(0, 0))
    newLayer:addChild(pToMainMenu,10)
    
    local editBoxSize = CCSizeMake(visibleSize.width - 100, 60)
    local EditName = nil
    local EditPassword = nil
    local EditEmail = nil
	
	local function editBoxTextEventHandle(strEventName,pSender)
		local edit = tolua.cast(pSender,"CCEditBox")
		local strFmt 
		if strEventName == "began" then
			strFmt = string.format("editBox %p DidBegin !", edit)
			print(strFmt)
		elseif strEventName == "ended" then
			strFmt = string.format("editBox %p DidEnd !", edit)
			print(strFmt)
		elseif strEventName == "return" then
			strFmt = string.format("editBox %p was returned !",edit)
			if edit == EditName then
				TTFShowEditReturn:setString("Name EditBox return !")
			elseif edit == EditPassword then
				TTFShowEditReturn:setString("Password EditBox return !")
			elseif edit == EditEmail then
				TTFShowEditReturn:setString("Email EditBox return !")
			end
			print(strFmt)
		elseif strEventName == "changed" then
			strFmt = string.format("editBox %p TextChanged, text: %s ", edit, edit:getText())
			print(strFmt)
		end
	end
    -- top
    EditName = CCEditBox:create(editBoxSize, CCScale9Sprite:create("extensions/green_edit.png"))
    EditName:setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4))
    local targetPlatform = CCApplication:sharedApplication():getTargetPlatform()
    if kTargetIphone == targetPlatform or kTargetIpad == targetPlatform then
	   EditName:setFontName("Paint Boy")
	else
		EditName:setFontName("fonts/Paint Boy.ttf")
	end
    EditName:setFontSize(25)
    EditName:setFontColor(ccc3(255,0,0))
    EditName:setPlaceHolder("Name:")
    EditName:setPlaceholderFontColor(ccc3(255,255,255))
    EditName:setMaxLength(8)
    EditName:setReturnType(kKeyboardReturnTypeDone)
	--Handler
	EditName:registerScriptEditBoxHandler(editBoxTextEventHandle)
    newLayer:addChild(EditName)
   
    --middle
    EditPassword = CCEditBox:create(editBoxSize, CCScale9Sprite:create("extensions/orange_edit.png"))
    EditPassword:setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2))
	if kTargetIphone == targetPlatform or kTargetIpad == targetPlatform then
		EditPassword:setFont("American Typewriter", 30)
	else
		EditPassword:setFont("fonts/American Typewriter.ttf", 30)
	end
	

    EditPassword:setFontColor(ccc3(0,255,0))
    EditPassword:setPlaceHolder("Password:")
    EditPassword:setMaxLength(6)
    EditPassword:setInputFlag(kEditBoxInputFlagPassword)
    EditPassword:setInputMode(kEditBoxInputModeSingleLine)
	EditPassword:registerScriptEditBoxHandler(editBoxTextEventHandle)
    newLayer:addChild(EditPassword)
     
    --bottom
    EditEmail = CCEditBox:create(CCSizeMake(editBoxSize.width, editBoxSize.height), CCScale9Sprite:create("extensions/yellow_edit.png"))
    EditEmail:setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4))
    EditEmail:setAnchorPoint(ccp(0.5, 1.0))
    EditEmail:setPlaceHolder("Email:")
    EditEmail:setInputMode(kEditBoxInputModeEmailAddr)
    EditEmail:registerScriptEditBoxHandler(editBoxTextEventHandle)
    newLayer:addChild(EditEmail)   
    newLayer:setPosition(ccp(10, 20))
    
	
	newScene:addChild(newLayer)
	return newScene
end

local CreateExtensionsTestTable = 
{
	runNotificationCenterTest,
	runCCControlTest,
	runCocosBuilder,
	runWebSocketTest,
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
    local targetPlatform = CCApplication:sharedApplication():getTargetPlatform()
    local bSupportWebSocket = false
    if (kTargetIphone == targetPlatform) or (kTargetIpad == targetPlatform) or (kTargetAndroid == targetPlatform) or (kTargetWindows == targetPlatform) then
        bSupportWebSocket = true
    end
    local bSupportEdit = false
    if (kTargetIphone == targetPlatform) or (kTargetIpad == targetPlatform) or 
        (kTargetAndroid == targetPlatform) or (kTargetWindows == targetPlatform) or 
        (kTargetMacOS == targetPlatform) or (kTargetTizen == targetPlatform) then
        bSupportEdit = true
    end
    for i = 1, ExtensionTestEnum.TEST_MAX_COUNT do
		local item = CCMenuItemFont:create(testsName[i])
	    item:registerScriptTapHandler(menuCallback)
        item:setPosition(s.width / 2, s.height - i * LINE_SPACE)
        menu:addChild(item, kItemTagBasic + i)
        if ((i == ExtensionTestEnum.TEST_WEBSOCKET + 1) and (false == bSupportWebSocket))
        or ((i == ExtensionTestEnum.TEST_EDITBOX + 1) and (false == bSupportEdit)) then
            item:setEnabled(false)
        end
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
