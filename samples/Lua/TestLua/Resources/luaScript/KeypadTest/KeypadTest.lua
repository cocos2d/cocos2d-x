local function KeypadMainLayer()	
	local pLayer = CCLayer:create()   
	
	local  s = CCDirector:sharedDirector():getWinSize()
    local  label = CCLabelTTF:create("Keypad Test", "Arial", 28)
    pLayer:addChild(label, 0)
    label:setPosition( ccp(s.width/2, s.height-50) )

    pLayer:setKeypadEnabled(true)

    -- create a label to display the tip string
    local pLabelTip = CCLabelTTF:create("Please press any key...", "Arial", 22)
    pLabelTip:setPosition(ccp(s.width / 2, s.height / 2))
    pLayer:addChild(pLabelTip, 0)
    
    pLabelTip:retain()
    
    local function KeypadHandler(strEvent)
    	if "backClicked" == strEvent then
    		pLabelTip:setString("BACK clicked!");
    	elseif "menuClicked" == strEvent then
    		pLabelTip:setString("MENU clicked!");
    	end
    end
    
    pLayer:registerScriptKeypadHandler(KeypadHandler)
    
    return pLayer
end


function KeypadTestMain()
	cclog("KeypadTestMain")
	local scene = CCScene:create()
	scene:addChild(KeypadMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
