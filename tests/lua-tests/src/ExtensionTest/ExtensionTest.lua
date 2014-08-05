require "src/ExtensionTest/CocosBuilderTest"
require "src/ExtensionTest/WebProxyTest"

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
    TEST_SCROLLVIEW         = 6,
    TEST_MAX_COUNT          = 7,
}

local testsName =
{
    "NotificationCenterTest",
    "CCControlButtonTest",
    "CocosBuilderTest",
    "WebSocketTest",
    "EditBoxTest",
    "TableViewTest",
    "ScrollViewTest",
}


--Create toMainLayr MenuItem
function CreateExtensionsBasicLayerMenu(pMenu)
	if nil == pMenu then
		return
	end
	local function toMainLayer()
       local pScene = ExtensionsTestMain()
       if pScene ~= nil then
           cc.Director:getInstance():replaceScene(pScene)
       end
    end	
    --Create BackMneu
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
   	local pMenuItemFont = cc.MenuItemFont:create("Back")
    pMenuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
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
		
		local pNewScene = cc.Scene:create()
		local pNewLayer = cc.Layer:create()
		local function BaseInitSceneLayer(pLayer)
		if nil == pLayer then
			return
		end
		local s = cc.Director:getInstance():getWinSize()
    	
    	local function toggleSwitch(tag,menuItem)
    		local toggleItem = menuItem
    		local nIndex     = toggleItem:getSelectedIndex()
    		local selectedItem = toggleItem:getSelectedItem()
    		if 0 == nIndex  then
    			selectedItem = nil
    		end
    		cc.NotificationCenter:getInstance():postNotification(NotificationCenterParam.MSG_SWITCH_STATE,selectedItem)
    	end
    	
    	local switchlabel1 = cc.Label:createWithSystemFont("switch off", "Marker Felt", 26)
    	local switchlabel2 = cc.Label:createWithSystemFont("switch on", "Marker Felt", 26)
    	local switchitem1  = cc.MenuItemLabel:create(switchlabel1)
    	local switchitem2 = cc.MenuItemLabel:create(switchlabel2)
    	local switchitem = cc.MenuItemToggle:create(switchitem1)
    	switchitem:addSubItem(switchitem2)
    	switchitem:registerScriptTapHandler(toggleSwitch)
    	--turn on
    	switchitem:setSelectedIndex(1)
        local menu = cc.Menu:create()
        menu:addChild(switchitem)
    	menu:setPosition(cc.p(s.width/2+100, s.height/2))
   		pLayer:addChild(menu)

    	local menuConnect = cc.Menu:create()
    	menuConnect:setPosition(cc.p(0,0))
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
    		if bConnect then
    			cc.NotificationCenter:getInstance():registerScriptObserver(pLight, switchStateChanged,NotificationCenterParam.MSG_SWITCH_STATE)
    		else
    			cc.NotificationCenter:getInstance():unregisterScriptObserver(pLight,NotificationCenterParam.MSG_SWITCH_STATE)
    		end
    		updateLightState()
    	end
    	

    	for  i = 1, 3 do 		   	
        	lightArray[i] = cc.Sprite:create("Images/Pea.png")
       		lightArray[i]:setTag(NotificationCenterParam.kTagLight + i)
        	lightArray[i]:setPosition(cc.p(100, s.height / 4 * i) )
        	pLayer:addChild(lightArray[i])
			
        	local connectlabel1 = cc.Label:createWithSystemFont("not connected", "Marker Felt", 26)
        	
        	local connectlabel2 = cc.Label:createWithSystemFont("connected", "Marker Felt", 26)
        	local connectitem1 = cc.MenuItemLabel:create(connectlabel1)
        	local connectitem2 = cc.MenuItemLabel:create(connectlabel2)
        	local connectitem = cc.MenuItemToggle:create(connectitem1)
        	connectitem:addSubItem(connectitem2)
        
        	connectitem:setTag(NotificationCenterParam.kTagConnect+i)
        	
        	local function connectToSwitch(tag,menuItem)
    		   local connectMenuitem = menuItem
    		   local bConnected = true
    		   if connectMenuitem:getSelectedIndex() == 0 then
    		   	   bConnected = false
    		   end
    		   local nIdx = connectMenuitem:getTag()-NotificationCenterParam.kTagConnect 
    		   setIsConnectToSwitch(lightArray[nIdx],bConnected,nIdx)
    		end
    		
        	connectitem:registerScriptTapHandler(connectToSwitch)
        	local nX,nY = lightArray[i]:getPosition()
        	connectitem:setPosition(cc.p(nX,nY+50))
            
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
    	local toggleSelectedItem = switchitem:getSelectedItem()
    	if 0 == toggleSelectIndex  then
    		toggleSelectedItem = nil
    	end
    	cc.NotificationCenter:getInstance():postNotification(NotificationCenterParam.MSG_SWITCH_STATE, toggleSelectedItem)
    	
    	--for testing removeAllObservers */
    	local function doNothing()
    	end
    	cc.NotificationCenter:getInstance():registerScriptObserver(pNewLayer,doNothing, "random-observer1")
    	cc.NotificationCenter:getInstance():registerScriptObserver(pNewLayer,doNothing, "random-observer2")
    	cc.NotificationCenter:getInstance():registerScriptObserver(pNewLayer,doNothing, "random-observer3")
    	
    	local function CreateToMainMenu(pMenu)
		     if nil == pMenu then
				return
			 end
			 local function toMainLayer()
				local numObserversRemoved = cc.NotificationCenter:getInstance():removeAllObservers(pNewLayer)
				if 3 ~= numObserversRemoved then
					print("All observers were not removed!")
				end
				
				for i = 1 , 3 do					 
					 if bConnectArray[i] then
					 	cc.NotificationCenter:getInstance():unregisterScriptObserver(lightArray[i],NotificationCenterParam.MSG_SWITCH_STATE)
					 end   		    			
				end
				
       			local pScene = ExtensionsTestMain()
       			if pScene ~= nil then
           			cc.Director:getInstance():replaceScene(pScene)
       			end
    		 end	
    		 --Create BackMneu
    		 cc.MenuItemFont:setFontName("Arial")
    		 cc.MenuItemFont:setFontSize(24)
   			 local pMenuItemFont = cc.MenuItemFont:create("Back")
    		 pMenuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    		 pMenuItemFont:registerScriptTapHandler(toMainLayer)
    		 pMenu:addChild(pMenuItemFont)
	   end
	   --Add Menu
	   local pToMainMenu = cc.Menu:create()
       CreateToMainMenu(pToMainMenu)
       pToMainMenu:setPosition(cc.p(0, 0))
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
    
    local pNewScene = cc.Scene:create()
    
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
   				
    	local size = cc.Director:getInstance():getWinSize()
    	local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
    	item1:registerScriptTapHandler(backCallback)
    	pMenu:addChild(item1,kItemTagBasic)
    	local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
    	item2:registerScriptTapHandler(restartCallback)
    	pMenu:addChild(item2,kItemTagBasic)
    	local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
    	pMenu:addChild(item3,kItemTagBasic) 
    	item3:registerScriptTapHandler(nextCallback)
    			
    	local size = cc.Director:getInstance():getWinSize()
    	item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    	item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
    	item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    		 
	end
	
	local function BaseInitSceneLayer(pLayer,pStrTitle)
		if nil == pLayer then
			return
		end
		--Add Menu
		local pToMainMenu = cc.Menu:create()
    	CreateExtensionsBasicLayerMenu(pToMainMenu)
    	pToMainMenu:setPosition(cc.p(0, 0))
    	pLayer:addChild(pToMainMenu,10)
    	
    	--Add the generated background
        local pBackground = cc.Sprite:create("extensions/background.png")
        pBackground:setPosition(VisibleRect:center())
        pLayer:addChild(pBackground)
        
        --Add the ribbon
        local pRibbon = cc.Scale9Sprite:create("extensions/ribbon.png", cc.rect(1, 1, 48, 55))
        pRibbon:setContentSize(cc.size(VisibleRect:getVisibleRect().width, 57))
        pRibbon:setPosition(cc.p(VisibleRect:center().x, VisibleRect:top().y - pRibbon:getContentSize().height / 2.0))
        pLayer:addChild(pRibbon)
        
        --Add the title
        pSceneTitleLabel = cc.Label:createWithSystemFont("Title", "Arial", 12)
        pSceneTitleLabel:setPosition(cc.p (VisibleRect:center().x, VisibleRect:top().y - pSceneTitleLabel:getContentSize().height / 2 - 5))
        pLayer:addChild(pSceneTitleLabel, 1)
        pSceneTitleLabel:setString(pStrTitle)
    	
    	local pOperateMenu = cc.Menu:create()
    	CreateBasicMenu(pOperateMenu)
    	pOperateMenu:setPosition(cc.p(0, 0))
		pLayer:addChild(pOperateMenu,1)		
	end
	
	local function InitSliderTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()
		--Add a label in which the slider value will be displayed
		local pDisplayValueLabel = cc.Label:createWithSystemFont("Move the slider thumb!\nThe lower slider is restricted." ,"Marker Felt", 32)
        pDisplayValueLabel:retain()
        pDisplayValueLabel:setAnchorPoint(cc.p(0.5, -1.0))
        pDisplayValueLabel:setPosition(cc.p(screenSize.width / 1.7, screenSize.height / 2.0))
        pLayer:addChild(pDisplayValueLabel)
        
        local function valueChanged(pSender)
        	if nil == pSender or nil == pDisplayValueLabel then
        		return
        	end       	
        	local pControl = pSender
        	local strFmt = nil
        	if pControl:getTag() == 1 then
        		strFmt = string.format("Upper slider value = %.02f",pControl:getValue())
        	elseif pControl:getTag() == 2 then
        		strFmt = string.format("Lower slider value = %.02f",pControl:getValue())
        	end
        	
        	if nil ~= strFmt then
        		pDisplayValueLabel:setString(strFmt)
        	end       	
        end
        --Add the slider
        local pSlider = cc.ControlSlider:create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png")
        pSlider:setAnchorPoint(cc.p(0.5, 1.0))
        pSlider:setMinimumValue(0.0) 
        pSlider:setMaximumValue(5.0) 
        pSlider:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0 + 16))
		pSlider:setTag(1)
        
        --When the value of the slider will change, the given selector will be call
        pSlider:registerControlEventHandler(valueChanged, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
		
		local pRestrictSlider = cc.ControlSlider:create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png")
        pRestrictSlider:setAnchorPoint(cc.p(0.5, 1.0))
        pRestrictSlider:setMinimumValue(0.0) 
        pRestrictSlider:setMaximumValue(5.0) 
		pRestrictSlider:setMaximumAllowedValue(4.0)
		pRestrictSlider:setMinimumAllowedValue(1.5)
		pRestrictSlider:setValue(3.0)
        pRestrictSlider:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0 - 24))
		pRestrictSlider:setTag(2)		
		--same with restricted
		pRestrictSlider:registerControlEventHandler(valueChanged, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
	    pLayer:addChild(pSlider)    
		pLayer:addChild(pRestrictSlider)
	end
	
	--ColourPickerTest
	local function InitColourPickerTest(pLayer)
		if nil == pLayer then
			return
		end
		local screenSize = cc.Director:getInstance():getWinSize()
		local pColorLabel = nil

        local pNode  = cc.Node:create()
        pNode:setPosition(cc.p (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0

        --Create the colour picker,pStrEventName not use
        local function colourValueChanged(pSender)
        	if nil == pSender or nil == pColorLabel then
        		return
        	end
        	
        	local pPicker = pSender
        	local strFmt  = string.format("#%02X%02X%02X",pPicker:getColor().r, pPicker:getColor().g, pPicker:getColor().b)
        	pColorLabel:setString(strFmt)       	
        end
        local pColourPicker = cc.ControlColourPicker:create()
        pColourPicker:setColor(cc.c3b(37, 46, 252))
        pColourPicker:setPosition(cc.p (pColourPicker:getContentSize().width / 2, 0))
        pColourPicker:registerControlEventHandler(colourValueChanged, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
        pNode:addChild(pColourPicker)     
	
	    dLayer_width = dLayer_width + pColourPicker:getContentSize().width
	    
	   --Add the black background for the text
        local pBackground = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(cc.size(150, 50))
        pBackground:setPosition(cc.p(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        pColorLabel = cc.Label:createWithSystemFont("#color", "Marker Felt", 30)
        pColorLabel:retain()
		pColorLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pColorLabel)
        
        --Set the layer size
        pNode:setContentSize(cc.size(dLayer_width, 0))
        pNode:setAnchorPoint(cc.p (0.5, 0.5))

        --Update the color text
	    colourValueChanged(pColourPicker)
	end
	
	--SwitchTest
	local function InitSwitchTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()
        
        local pNode = cc.Node:create()
        pNode:setPosition(cc.p (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0
        
        --Add the black background for the text
        local pBackground = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(cc.size(80, 50))
        pBackground:setPosition(cc.p(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)       
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        local pDisplayValueLabel  = cc.Label:createWithSystemFont("#color" ,"Marker Felt" ,30)
        pDisplayValueLabel:retain()

        pDisplayValueLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pDisplayValueLabel)
        
        --Create the switch
        local function valueChanged(pSender)
        	if nil == pDisplayValueLabel or nil == pSender then
        		return
        	end
        	
        	local pControl = pSender
        	if pControl:isOn() then
        		pDisplayValueLabel:setString("On")
        	else
        		pDisplayValueLabel:setString("Off")
        	end
        end
        local pSwitchControl = cc.ControlSwitch:create(
                cc.Sprite:create("extensions/switch-mask.png"),
                cc.Sprite:create("extensions/switch-on.png"),
                cc.Sprite:create("extensions/switch-off.png"),
                cc.Sprite:create("extensions/switch-thumb.png"),
                cc.Label:createWithSystemFont("On", "Arial-BoldMT", 16),
                cc.Label:createWithSystemFont("Off", "Arial-BoldMT", 16)
            )
        pSwitchControl:setPosition(cc.p (dLayer_width + 10 + pSwitchControl:getContentSize().width / 2, 0))
        pNode:addChild(pSwitchControl)
        pSwitchControl:registerControlEventHandler(valueChanged, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
        
        --Set the layer size
        pNode:setContentSize(cc.size(dLayer_width, 0))
        pNode:setAnchorPoint(cc.p (0.5, 0.5))
        
        --Update the value label
        valueChanged(pSwitchControl)
	end
	
	--Hvs:HelloVariableSize
	local function HvsStandardButtonWithTitle(pStrTitle)
	    -- Creates and return a button with a default background and title color. 
    	local pBackgroundButton = cc.Scale9Sprite:create("extensions/button.png")
    	local pBackgroundHighlightedButton = cc.Scale9Sprite:create("extensions/buttonHighlighted.png")
    
    	pTitleButton = cc.Label:createWithSystemFont(pStrTitle, "Marker Felt", 30)

    	pTitleButton:setColor(cc.c3b(159, 168, 176))
    
    	local pButton = cc.ControlButton:create(pTitleButton, pBackgroundButton)
    	pButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, cc.CONTROL_STATE_HIGH_LIGHTED )
    	pButton:setTitleColorForState(cc.c3b(255,255,255), cc.CONTROL_STATE_HIGH_LIGHTED )
    
    	return pButton
	end
	
	local function InitHelloVariableSize(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()
		local strArray   = {"Hello", "Variable", "Size", "!"}
		
		local pNode = cc.Node:create()
		pLayer:addChild(pNode,1)
		local dTotalWidth = 0
		local dHeight     = 0
		local pObj        = nil
		
		local i = 0
    	local nLen = table.getn(strArray)
    	for i = 0, nLen - 1 do
        	--Creates a button with pLayer string as title
            local pButton = HvsStandardButtonWithTitle(strArray[i + 1])	
            pButton:setPosition(cc.p (dTotalWidth + pButton:getContentSize().width / 2, pButton:getContentSize().height / 2))
            pNode:addChild(pButton)
            
            --Compute the size of the layer
            dHeight = pButton:getContentSize().height
            dTotalWidth = dTotalWidth + pButton:getContentSize().width
    	end
		
		pNode:setAnchorPoint(cc.p (0.5, 0.5))
        pNode:setContentSize(cc.size(dTotalWidth, dHeight))
        pNode:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        
        --Add the black background
        local pBackground = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(cc.size(dTotalWidth + 14, dHeight + 14))
        pBackground:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pBackground)
	end
	
	local function StylingStandardButtonWithTitle(pStrTitle)
    	local pBackgroundButton = cc.Scale9Sprite:create("extensions/button.png")
    	pBackgroundButton:setPreferredSize(cc.size(45, 45)) 
    	local pBackgroundHighlightedButton = cc.Scale9Sprite:create("extensions/buttonHighlighted.png")
    	pBackgroundHighlightedButton:setPreferredSize(cc.size(45, 45)) 
    
        local pTitleButton = cc.Label:createWithSystemFont(pStrTitle, "Marker Felt", 30)

    	pTitleButton:setColor(cc.c3b(159, 168, 176))
    
    	local pButton = cc.ControlButton:create(pTitleButton, pBackgroundButton)
        pButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, cc.CONTROL_STATE_HIGH_LIGHTED )
    	pButton:setTitleColorForState(cc.c3b(255,255,255), cc.CONTROL_STATE_HIGH_LIGHTED )
    
        return pButton
	end
	
	local function InitStyling(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()

        local pNode = cc.Node:create()
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
                local pButton = StylingStandardButtonWithTitle(strFmt)
                pButton:setAdjustBackgroundImage(false)                                                  
                pButton:setPosition(cc.p (pButton:getContentSize().width / 2 + (pButton:getContentSize().width + nSpace) * i,
                                         pButton:getContentSize().height / 2 + (pButton:getContentSize().height + nSpace) * j))
                
                pNode:addChild(pButton)
                
                nMax_w = math.max(pButton:getContentSize().width * (i + 1) + nSpace  * i, nMax_w)
                nMax_h = math.max(pButton:getContentSize().height * (j + 1) + nSpace * j, nMax_h)
          end
        end

        
        pNode:setAnchorPoint(cc.p (0.5, 0.5))
        pNode:setContentSize(cc.size(nMax_w, nMax_h))
        pNode:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        
        --Add the black background
        local pBackgroundButton = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        pBackgroundButton:setContentSize(cc.size(nMax_w + 14, nMax_h + 14))
        pBackgroundButton:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pBackgroundButton)
	end
	
	local function InitButtonTestEvent(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()

        --Add a label in which the button events will be displayed
        local pDisplayValueLabel = nil
        pDisplayValueLabel = cc.Label:createWithSystemFont("No Event", "Marker Felt", 32)
        pDisplayValueLabel:setAnchorPoint(cc.p(0.5, -1))
       	pDisplayValueLabel:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pDisplayValueLabel, 1)
        
        --Add the button
        local pBackgroundButton            = cc.Scale9Sprite:create("extensions/button.png")
        local pBackgroundHighlightedButton = cc.Scale9Sprite:create("extensions/buttonHighlighted.png")
        
        local pTitleButtonLabel = cc.Label:createWithSystemFont("Touch Me!", "Marker Felt", 30)
        pTitleButtonLabel:setColor(cc.c3b(159, 168, 176))
        
        local pControlButton = cc.ControlButton:create(pTitleButtonLabel, pBackgroundButton)
        local function touchDownAction()
        	if nil == pDisplayValueLabel then
        		return
        	end       	
        	pDisplayValueLabel:setString("Touch Down" )
        end
        
        local function touchDragInsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Drag Inside")
        end
        
        local function touchDragOutsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Drag Outside")
        end
        
        local function touchDragEnterAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Drag Enter")
        end
        
        local function touchDragExitAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Drag Exit")
        end
        
        local function touchUpInsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Touch Up Inside.")
        end
        
        local function touchUpOutsideAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Touch Up Outside.")
        end
        
        local function touchCancelAction()
        	if nil == pDisplayValueLabel then
        		return
        	end 
        	pDisplayValueLabel:setString("Touch Cancel")
        end
        
        
        
        pControlButton:setBackgroundSpriteForState(pBackgroundHighlightedButton, cc.CONTROL_STATE_HIGH_LIGHTED )
        pControlButton:setTitleColorForState(cc.c3b(255, 255, 255), cc.CONTROL_STATE_HIGH_LIGHTED )
        pControlButton:setAnchorPoint(cc.p(0.5, 1))
        pControlButton:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        pControlButton:registerControlEventHandler(touchDownAction,cc.CONTROL_EVENTTYPE_TOUCH_DOWN )
        pControlButton:registerControlEventHandler(touchDragInsideAction,cc.CONTROL_EVENTTYPE_DRAG_INSIDE)
        pControlButton:registerControlEventHandler(touchDragOutsideAction,cc.CONTROL_EVENTTYPE_DRAG_OUTSIDE)
        pControlButton:registerControlEventHandler(touchDragEnterAction,cc.CONTROL_EVENTTYPE_DRAG_ENTER)
        pControlButton:registerControlEventHandler(touchDragExitAction,cc.CONTROL_EVENTTYPE_DRAG_EXIT)
        pControlButton:registerControlEventHandler(touchUpInsideAction,cc.CONTROL_EVENTTYPE_TOUCH_UP_INSIDE)
        pControlButton:registerControlEventHandler(touchUpOutsideAction,cc.CONTROL_EVENTTYPE_TOUCH_UP_OUTSIDE)
        pControlButton:registerControlEventHandler(touchCancelAction,cc.CONTROL_EVENTTYPE_TOUCH_CANCEL)
        pLayer:addChild(pControlButton, 1)
		
		--Add the black background
        local pBackgroundButton = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        pBackgroundButton:setContentSize(cc.size(300, 170))
        pBackgroundButton:setPosition(cc.p(screenSize.width / 2.0, screenSize.height / 2.0))
        pLayer:addChild(pBackgroundButton)
	end
	--PotentiometerTest
	local function InitPotentiometerTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()
        
        local pNode = cc.Node:create()
        pNode:setPosition(cc.p (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local dLayer_width = 0
        
        -- Add the black background for the text
        local pBackground  = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        pBackground:setContentSize(cc.size(80, 50))
        pBackground:setPosition(cc.p(dLayer_width + pBackground:getContentSize().width / 2.0, 0))
        pNode:addChild(pBackground)
        
        dLayer_width = dLayer_width + pBackground:getContentSize().width
        
        local pDisplayValueLabel = cc.Label:createWithSystemFont("", "HelveticaNeue-Bold", 30)
        pDisplayValueLabel:setPosition(pBackground:getPosition())
        pNode:addChild(pDisplayValueLabel)
		
        -- Add the slider
        local function valueChanged(pSender)
        	if nil == pSender then
        		return
        	end
        	
        	local pControl = pSender
        	local strFmt = string.format("%0.2f",pControl:getValue())
        	pDisplayValueLabel:setString(strFmt )
        end
        local pPotentiometer = cc.ControlPotentiometer:create("extensions/potentiometerTrack.png","extensions/potentiometerProgress.png"
                                                                               ,"extensions/potentiometerButton.png")
        pPotentiometer:setPosition(cc.p (dLayer_width + 10 + pPotentiometer:getContentSize().width / 2, 0))

        -- When the value of the slider will change, the given selector will be call
        pPotentiometer:registerControlEventHandler(valueChanged, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
        
		pNode:addChild(pPotentiometer)
        
        dLayer_width = dLayer_width + pPotentiometer:getContentSize().width
        
        -- Set the layer size
        pNode:setContentSize(cc.size(dLayer_width, 0))
        pNode:setAnchorPoint(cc.p (0.5, 0.5))
        
        -- Update the value label
        valueChanged(pPotentiometer)
	end
	
	local function InitStepperTest(pLayer)
		if nil == pLayer then
			return
		end
		
		local screenSize = cc.Director:getInstance():getWinSize()
        
        local pNode = cc.Node:create()
        pNode:setPosition(cc.p (screenSize.width / 2, screenSize.height / 2))
        pLayer:addChild(pNode, 1)
        
        local layer_width          = 0
        
        -- Add the black background for the text
        local background  = cc.Scale9Sprite:create("extensions/buttonBackground.png")
        background:setContentSize(cc.size(100, 50))
        background:setPosition(cc.p(layer_width + background:getContentSize().width / 2.0, 0))
        pNode:addChild(background)
        
        local pDisplayValueLabel =  cc.Label:createWithSystemFont("0", "HelveticaNeue-Bold", 30)

        pDisplayValueLabel:setPosition(background:getPosition())
        pNode:addChild(pDisplayValueLabel)
        
        layer_width   = layer_width + background:getContentSize().width
        
        local minusSprite       = cc.Sprite:create("extensions/stepper-minus.png")
    	local plusSprite        = cc.Sprite:create("extensions/stepper-plus.png")
    
    	local function valueChanged(pSender)
    		if nil == pDisplayValueLabel or nil == pSender then
    			return
    		end
    		
    		local pControl = pSender
    		local strFmt   = string.format("%0.02f",pControl:getValue() )
    		pDisplayValueLabel:setString(strFmt )
    	end
        local stepper   = cc.ControlStepper:create(minusSprite, plusSprite)
        stepper:setPosition(cc.p (layer_width + 10 + stepper:getContentSize().width / 2, 0))
        stepper:registerControlEventHandler(valueChanged, cc.CONTROL_EVENTTYPE_VALUE_CHANGED)
        pNode:addChild(stepper)
        
        layer_width  = layer_width + stepper:getContentSize().width
        
        -- Set the layer size
        pNode:setContentSize(cc.size(layer_width, 0))
        pNode:setAnchorPoint(cc.p (0.5, 0.5))
        
        -- Update the value label
        valueChanged(stepper)
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
		pNewScene = cc.Scene:create()
		local pNewLayer = cc.Layer:create()
    	BaseInitSceneLayer(pNewLayer,GetControlExtensionsTitle())
    	InitSpecialSceneLayer(pNewLayer)
		pNewScene:addChild(pNewLayer)
		if nil ~= pNewScene then
		    cc.Director:getInstance():replaceScene(pNewScene)
		end
		
    end
    
    local pNewLayer = cc.Layer:create()
    BaseInitSceneLayer(pNewLayer,GetControlExtensionsTitle())
    InitSpecialSceneLayer(pNewLayer)
	pNewScene:addChild(pNewLayer)
	
	return pNewScene
end

local function runEditBoxTest()
	local newScene = cc.Scene:create()
	local newLayer = cc.Layer:create()
	local visibleOrigin = cc.Director:getInstance():getVisibleOrigin()
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    
    local pBg = cc.Sprite:create("Images/HelloWorld.png")
    pBg:setPosition(cc.p(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2))
    newLayer:addChild(pBg)
    
    local TTFShowEditReturn = cc.Label:createWithSystemFont("No edit control return!", "", 30)
    TTFShowEditReturn:setPosition(cc.p(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y + visibleSize.height - 50))
    newLayer:addChild(TTFShowEditReturn)
    
    -- Back Menu
	local pToMainMenu = cc.Menu:create()
    CreateExtensionsBasicLayerMenu(pToMainMenu)
    pToMainMenu:setPosition(cc.p(0, 0))
    newLayer:addChild(pToMainMenu,10)
    
    local editBoxSize = cc.size(visibleSize.width - 100, 60)
    local EditName = nil
    local EditPassword = nil
    local EditEmail = nil
	
	local function editBoxTextEventHandle(strEventName,pSender)
		local edit = pSender
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
    EditName = cc.EditBox:create(editBoxSize, cc.Scale9Sprite:create("extensions/green_edit.png"))
    EditName:setPosition(cc.p(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4))
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if kTargetIphone == targetPlatform or kTargetIpad == targetPlatform then
	   EditName:setFontName("Paint Boy")
	else
		EditName:setFontName("fonts/Paint Boy.ttf")
	end
    EditName:setFontSize(25)
    EditName:setFontColor(cc.c3b(255,0,0))
    EditName:setPlaceHolder("Name:")
    EditName:setPlaceholderFontColor(cc.c3b(255,255,255))
    EditName:setMaxLength(8)
    EditName:setReturnType(cc.KEYBOARD_RETURNTYPE_DONE )
	--Handler
	EditName:registerScriptEditBoxHandler(editBoxTextEventHandle)
    newLayer:addChild(EditName)
   
    --middle
    EditPassword = cc.EditBox:create(editBoxSize, cc.Scale9Sprite:create("extensions/orange_edit.png"))
    EditPassword:setPosition(cc.p(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2))
	if kTargetIphone == targetPlatform or kTargetIpad == targetPlatform then
		EditPassword:setFont("American Typewriter", 30)
	else
		EditPassword:setFont("fonts/American Typewriter.ttf", 30)
	end
	

    EditPassword:setFontColor(cc.c3b(0,255,0))
    EditPassword:setPlaceHolder("Password:")
    EditPassword:setMaxLength(6)
    EditPassword:setInputFlag(cc.EDITBOX_INPUT_FLAG_PASSWORD)
    EditPassword:setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE)
	EditPassword:registerScriptEditBoxHandler(editBoxTextEventHandle)
    newLayer:addChild(EditPassword)
     
    --bottom
    EditEmail = cc.EditBox:create(cc.size(editBoxSize.width, editBoxSize.height), cc.Scale9Sprite:create("extensions/yellow_edit.png"))
    EditEmail:setPosition(cc.p(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4))
    EditEmail:setAnchorPoint(cc.p(0.5, 1.0))
    EditEmail:setPlaceHolder("Email:")
    EditEmail:setInputMode(cc.EDITBOX_INPUT_MODE_EMAILADDR)
    EditEmail:registerScriptEditBoxHandler(editBoxTextEventHandle)
    newLayer:addChild(EditEmail)   
    newLayer:setPosition(cc.p(10, 20))
    
	
	newScene:addChild(newLayer)
	return newScene
end

local TableViewTestLayer = class("TableViewTestLayer")
TableViewTestLayer.__index = TableViewTestLayer

function TableViewTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TableViewTestLayer)
    return target
end

function TableViewTestLayer.scrollViewDidScroll(view)
    print("scrollViewDidScroll")
end

function TableViewTestLayer.scrollViewDidZoom(view)
    print("scrollViewDidZoom")
end

function TableViewTestLayer.tableCellTouched(table,cell)
    print("cell touched at index: " .. cell:getIdx())
end

function TableViewTestLayer.cellSizeForTable(table,idx) 
    return 60,60
end

function TableViewTestLayer.tableCellAtIndex(table, idx)
    local strValue = string.format("%d",idx)
    local cell = table:dequeueCell()
    local label = nil
    if nil == cell then
        cell = cc.TableViewCell:new()
        local sprite = cc.Sprite:create("Images/Icon.png")
        sprite:setAnchorPoint(cc.p(0,0))
        sprite:setPosition(cc.p(0, 0))
        cell:addChild(sprite)

        label = cc.Label:createWithSystemFont(strValue, "Helvetica", 20.0)
        label:setPosition(cc.p(0,0))
        label:setAnchorPoint(cc.p(0,0))
        label:setTag(123)
        cell:addChild(label)
    else
        label = cell:getChildByTag(123)
        if nil ~= label then
            label:setString(strValue)
        end
    end

    return cell
end

function TableViewTestLayer.numberOfCellsInTableView(table)
   return 25
end

function TableViewTestLayer:init()

    local winSize = cc.Director:getInstance():getWinSize()

    local tableView = cc.TableView:create(cc.size(600,60))
    tableView:setDirection(cc.SCROLLVIEW_DIRECTION_HORIZONTAL)
    tableView:setPosition(cc.p(20, winSize.height / 2 - 150))
    tableView:setDelegate()
    self:addChild(tableView)
    --registerScriptHandler functions must be before the reloadData funtion
    tableView:registerScriptHandler(TableViewTestLayer.numberOfCellsInTableView,cc.NUMBER_OF_CELLS_IN_TABLEVIEW)  
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidScroll,cc.SCROLLVIEW_SCRIPT_SCROLL)
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidZoom,cc.SCROLLVIEW_SCRIPT_ZOOM)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellTouched,cc.TABLECELL_TOUCHED)
    tableView:registerScriptHandler(TableViewTestLayer.cellSizeForTable,cc.TABLECELL_SIZE_FOR_INDEX)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellAtIndex,cc.TABLECELL_SIZE_AT_INDEX)
    tableView:reloadData()

    tableView = cc.TableView:create(cc.size(60, 350))
    tableView:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
    tableView:setPosition(cc.p(winSize.width - 150, winSize.height / 2 - 150))
    tableView:setDelegate()
    tableView:setVerticalFillOrder(cc.TABLEVIEW_FILL_TOPDOWN)
    self:addChild(tableView)
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidScroll,cc.SCROLLVIEW_SCRIPT_SCROLL)
    tableView:registerScriptHandler(TableViewTestLayer.scrollViewDidZoom,cc.SCROLLVIEW_SCRIPT_ZOOM)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellTouched,cc.TABLECELL_TOUCHED)
    tableView:registerScriptHandler(TableViewTestLayer.cellSizeForTable,cc.TABLECELL_SIZE_FOR_INDEX)
    tableView:registerScriptHandler(TableViewTestLayer.tableCellAtIndex,cc.TABLECELL_SIZE_AT_INDEX)
    tableView:registerScriptHandler(TableViewTestLayer.numberOfCellsInTableView,cc.NUMBER_OF_CELLS_IN_TABLEVIEW)
    tableView:reloadData()
    
    -- Back Menu
    local pToMainMenu = cc.Menu:create()
    CreateExtensionsBasicLayerMenu(pToMainMenu)
    pToMainMenu:setPosition(cc.p(0, 0))
    self:addChild(pToMainMenu,10)

    return true
end

function TableViewTestLayer.create()
    local layer = TableViewTestLayer.extend(cc.Layer:create())
    if nil ~= layer then
        layer:init()
    end

    return layer
end

local function runTableViewTest()
    local newScene = cc.Scene:create()
    local newLayer = TableViewTestLayer.create()
    newScene:addChild(newLayer)
    return newScene
end

local function runScrollViewTest()
    local newScene = cc.Scene:create()
    local newLayer = cc.Layer:create()

    -- Back Menu
    local pToMainMenu = cc.Menu:create()
    CreateExtensionsBasicLayerMenu(pToMainMenu)
    pToMainMenu:setPosition(cc.p(0, 0))
    newLayer:addChild(pToMainMenu,10)

    local layerColor = cc.LayerColor:create(cc.c4b(128,64,0,255))
    newLayer:addChild(layerColor)

    local scrollView1 = cc.ScrollView:create()
    local screenSize = cc.Director:getInstance():getWinSize()
    local function scrollView1DidScroll()
        print("scrollView1DidScroll")
    end
    local function scrollView1DidZoom()
        print("scrollView1DidZoom")
    end
    if nil ~= scrollView1 then
        scrollView1:setViewSize(cc.size(screenSize.width / 2,screenSize.height))
        scrollView1:setPosition(cc.p(0,0))
        scrollView1:setScale(1.0)
        scrollView1:ignoreAnchorPointForPosition(true)
        local flowersprite1 =  cc.Sprite:create("ccb/flower.jpg")
        if nil ~= flowersprite1 then
            scrollView1:setContainer(flowersprite1)
            scrollView1:updateInset()
        end
        scrollView1:setDirection(cc.SCROLLVIEW_DIRECTION_BOTH )
        scrollView1:setClippingToBounds(true)
        scrollView1:setBounceable(true)
        scrollView1:setDelegate()
        scrollView1:registerScriptHandler(scrollView1DidScroll,cc.SCROLLVIEW_SCRIPT_SCROLL)
        scrollView1:registerScriptHandler(scrollView1DidZoom,cc.SCROLLVIEW_SCRIPT_ZOOM)
    end
    newLayer:addChild(scrollView1)

    local scrollView2 = cc.ScrollView:create()
    local function scrollView2DidScroll()
        print("scrollView2DidScroll")
    end
    local function scrollView2DidZoom()
        print("scrollView2DidZoom")
    end
    if nil ~= scrollView2 then
        scrollView2:setViewSize(cc.size(screenSize.width / 2,screenSize.height))
        scrollView2:setPosition(cc.p(screenSize.width / 2,0))
        scrollView2:setScale(1.0)
        scrollView2:ignoreAnchorPointForPosition(true)
        local flowersprite2 =  cc.Sprite:create("ccb/flower.jpg")
        if nil ~= flowersprite2 then
            scrollView2:setContainer(flowersprite2)
            scrollView2:updateInset()
        end
        scrollView2:setDirection(cc.SCROLLVIEW_DIRECTION_BOTH )
        scrollView2:setClippingToBounds(true)
        scrollView2:setBounceable(true)
        scrollView2:setDelegate()
        scrollView2:registerScriptHandler(scrollView2DidScroll,cc.SCROLLVIEW_SCRIPT_SCROLL)
        scrollView2:registerScriptHandler(scrollView2DidZoom,cc.SCROLLVIEW_SCRIPT_ZOOM)
    end
    newLayer:addChild(scrollView2)

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
    runScrollViewTest,
}


local function ExtensionsMainLayer()

	local s = cc.Director:getInstance():getWinSize()

	local function CreateExtensionsTestScene(nPerformanceNo)
	  	local pNewscene = CreateExtensionsTestTable[nPerformanceNo]()
  		return pNewscene
	end
	
	local function menuCallback(tag, pMenuItem)
		local scene = nil
    	local nIdx = pMenuItem:getLocalZOrder() - kItemTagBasic
		local ExtensionsTestScene = CreateExtensionsTestScene(nIdx)
    	if nil ~= ExtensionsTestScene then
         	cc.Director:getInstance():replaceScene(ExtensionsTestScene)
    	end
	end
	
	local layer = cc.Layer:create()
	local menu = cc.Menu:create()
    menu:setPosition(cc.p(0, 0))
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    local bSupportWebSocket = false
    if (cc.PLATFORM_OS_IPHONE == targetPlatform) or (cc.PLATFORM_OS_IPAD == targetPlatform) or (cc.PLATFORM_OS_ANDROID == targetPlatform) or (cc.PLATFORM_OS_WINDOWS == targetPlatform) then
        bSupportWebSocket = true
    end
    local bSupportEdit = false
    if (cc.PLATFORM_OS_IPHONE == targetPlatform) or (cc.PLATFORM_OS_IPAD == targetPlatform) or 
        (cc.PLATFORM_OS_ANDROID == targetPlatform) or (cc.PLATFORM_OS_WINDOWS == targetPlatform) or 
        (cc.PLATFORM_OS_MAC == targetPlatform) or (cc.PLATFORM_OS_TIZEN  == targetPlatform) then
        bSupportEdit = true
    end
    for i = 1, ExtensionTestEnum.TEST_MAX_COUNT do
		local item = cc.MenuItemFont:create(testsName[i])
	    item:registerScriptTapHandler(menuCallback)
        item:setPosition(s.width / 2, s.height - i * LINE_SPACE)
        menu:addChild(item, kItemTagBasic + i)
        if ((i == ExtensionTestEnum.TEST_WEBSOCKET + 1) and (false == bSupportWebSocket))
        or ((i == ExtensionTestEnum.TEST_EDITBOX + 1) and (false == bSupportEdit)) 
        or (i == ExtensionTestEnum.TEST_NOTIFICATIONCENTER + 1)then
            item:setEnabled(false)
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

        if nextPosy > ((ExtensionTestEnum.TEST_MAX_COUNT + 1) * LINE_SPACE - winSize.height) then
            menu:setPosition(0, ((ExtensionTestEnum.TEST_MAX_COUNT + 1) * LINE_SPACE - winSize.height))
            return
        end

        menu:setPosition(curPosx, nextPosy)
        beginPos = {x = location.x, y = location.y}
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

	return layer
end

-------------------------------------
--  Extensions Test
-------------------------------------
function ExtensionsTestMain()
	local scene = cc.Scene:create()

	scene:addChild(ExtensionsMainLayer())
	scene:addChild(CreateBackMenuItem())

	return scene
end
