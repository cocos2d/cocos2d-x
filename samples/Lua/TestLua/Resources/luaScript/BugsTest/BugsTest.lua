local    MAX_COUNT = 9;
local    LINE_SPACE = 40;
local    kItemTagBasic = 5432;

local Winsize = CCDirector:sharedDirector():getWinSize();

local testNames = {
    "Bug-350",
    "Bug-422",
    "Bug-458",
    "Bug-624",
    "Bug-886",
    "Bug-899",
    "Bug-914",
    "Bug-1159",
    "Bug-1174"
}

local function CreateBugsTestBackMenuItem(pLayer)
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24);
    local pMenuItemFont = CCMenuItemFont:create("Back");
    pMenuItemFont:setPosition(ccp(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    local function menuCallback()
        local pScene = BugsTestMain()
        if pScene ~= nil then
            CCDirector:sharedDirector():replaceScene(pScene)
        end
    end
    pMenuItemFont:registerScriptTapHandler(menuCallback)
    local pMenu = CCMenu:create()
    pMenu:addChild(pMenuItemFont)
    pMenu:setPosition(ccp(0, 0))
    pLayer:addChild(pMenu)
end

--BugTest350
local function BugTest350()
    local pLayer = CCLayer:create()
    local pBackground = CCSprite:create("Hello.png");
    pBackground:setPosition(ccp(Winsize.width/2, Winsize.height/2));
    pLayer:addChild(pBackground);
    return pLayer
end

--BugTest422
local nLocalTag = 0
local function BugTest422()
    local function reset(pResetLayer)
        nLocalTag = nLocalTag + 1
        local pNode = pResetLayer:getChildByTag(nLocalTag - 1)
        if nil ~= pNode then
           --userdata pointer
           local strLog = "Menu:"..nLocalTag
           print(strLog)
        end

        pResetLayer:removeChild(pNode, false);
        
        local function menuCallback(tag,pMenuItem)
            if nil ~= pMenuItem then
                local pCallbackLayer = pMenuItem:getParent():getParent()
                reset(pCallbackLayer)
            end
        end
        CCMenuItemFont:setFontName("Arial")
        CCMenuItemFont:setFontSize(24);
        local pMenuItem1 = CCMenuItemFont:create("One")
        pMenuItem1:registerScriptTapHandler(menuCallback)
        local pMenuItem2 = CCMenuItemFont:create("Two")
        pMenuItem2:registerScriptTapHandler(menuCallback)
        local arr = CCArray:create()
        arr:addObject(pMenuItem1)
        arr:addObject(pMenuItem2)
        local pMenu = CCMenu:createWithArray(arr)
        pMenu:alignItemsVertically()
        local fX = math.random() * 50
        local fY = math.random() * 50
        pMenu:setPosition(ccpAdd(ccp(pMenu:getPosition()),ccp(fX,fY)))
        pResetLayer:addChild(pMenu,0,nLocalTag)
    end
    
    local pLayer = CCLayer:create()
    reset(pLayer)
    return pLayer
end

--BugTest458
local nColorFlag = 0
local function BugTest458()
    local pLayer = CCLayer:create()
    
    local function InitQuestionContainerSprite(pSprite)
        --Add label
        local pLabel = CCLabelTTF:create("Answer 1", "Arial", 12);
        pLabel:setTag(100);
        
        --Add the background
        local pCorner = CCSprite:create("Images/bugs/corner.png");
        local nWidth = Winsize.width * 0.9 - (pCorner:getContentSize().width * 2);
        local nHeight = Winsize.height * 0.15  - (pCorner:getContentSize().height * 2);
        local pColorLayer = CCLayerColor:create(ccc4(255, 255, 255, 255 * .75), nWidth, nHeight);
        pColorLayer:setPosition(ccp(-nWidth / 2, -nHeight / 2));
        --First button is blue,Second is red,Used for testing - change later
        if (0 == nColorFlag) then
            pLabel:setColor(ccc3(0,0,255))
        else
            print("Color changed")
            pLabel:setColor(ccc3(255,0,0))
        end
        nColorFlag = nColorFlag + 1;
        pSprite:addChild(pColorLayer);
        
        pCorner:setPosition(ccp(-(nWidth / 2 + pCorner:getContentSize().width / 2), -(nHeight / 2 + pCorner:getContentSize().height / 2)));
        pSprite:addChild(pCorner);
		
		local nX,nY = pCorner:getPosition()
        local pCorner2 = CCSprite:create("Images/bugs/corner.png");
        pCorner2:setPosition(ccp(-nX, nY));
        pCorner2:setFlipX(true);
        pSprite:addChild(pCorner2);

        local pCorner3 = CCSprite:create("Images/bugs/corner.png");
        pCorner3:setPosition(ccp(nX, -nY));
        pCorner3:setFlipY(true);
        pSprite:addChild(pCorner3);

        local pCorner4 = CCSprite:create("Images/bugs/corner.png");
        pCorner4:setPosition(ccp(-nX, -nY));
        pCorner4:setFlipX(true);
        pCorner4:setFlipY(true);
        pSprite:addChild(pCorner4);

        local pEdge = CCSprite:create("Images/bugs/edge.png");
        pEdge:setScaleX(nWidth);
        pEdge:setPosition(ccp(nX + (pCorner:getContentSize().width / 2) + (nWidth / 2), nY));
        pSprite:addChild(pEdge);
        
        local pEdge2 = CCSprite:create("Images/bugs/edge.png");
        pEdge2:setScaleX(nWidth);
        pEdge2:setPosition(ccp(nX + (pCorner:getContentSize().width / 2) + (nWidth / 2), -nY));
        pEdge2:setFlipY(true);
        pSprite:addChild(pEdge2);

        local pEdge3 = CCSprite:create("Images/bugs/edge.png");
        pEdge3:setRotation(90);
        pEdge3:setScaleX(nHeight);
        pEdge3:setPosition(ccp(nX, nY + (pCorner:getContentSize().height / 2) + (nHeight / 2)));
        pSprite:addChild(pEdge3);

        local pEdge4 = CCSprite:create("Images/bugs/edge.png");
        pEdge4:setRotation(270);
        pEdge4:setScaleX(nHeight);
        pEdge4:setPosition(ccp(-nX, nY + (pCorner:getContentSize().height / 2) + (nHeight / 2)));
        pSprite:addChild(pEdge4);

        pSprite:addChild(pLabel);
    end
    
    local pQuestion1 = CCSprite:create()
    InitQuestionContainerSprite(pQuestion1)
    local pQuestion2 = CCSprite:create()
    InitQuestionContainerSprite(pQuestion2)
    
    local function menuCallback()
        print("Selected")
    end
    local pMenuItemSprite = CCMenuItemSprite:create(pQuestion1,pQuestion2)
    pMenuItemSprite:registerScriptTapHandler(menuCallback)
    local pLayerColor1 = CCLayerColor:create(ccc4(0,0,255,255), 100, 100);
--  question->release();
--  question2->release();

    local pLayerColor2 = CCLayerColor:create(ccc4(255,0,0,255), 100, 100);
    local pMenuItemSprite2 = CCMenuItemSprite:create(pLayerColor1, pLayerColor2);   
    pMenuItemSprite2:registerScriptTapHandler(menuCallback) 

    local arr = CCArray:create()
    arr:addObject(pMenuItemSprite)
    arr:addObject(pMenuItemSprite2)
    local pMenu = CCMenu:createWithArray(arr)
    pMenu:alignItemsVerticallyWithPadding(100);
    pMenu:setPosition(ccp(Winsize.width / 2, Winsize.height / 2));

    -- add the label as a child to this Layer
    pLayer:addChild(pMenu);

    return pLayer
end

--BugTest624
local BugTest624_entry = nil
local BugTest624_2_entry = nil

local function BugTest624()
    local pLayer = CCLayer:create()
    
    local pLabel = CCLabelTTF:create("Layer1", "Marker Felt", 36);
    pLabel:setPosition(ccp(Winsize.width / 2, Winsize.height / 2));
    pLayer:addChild(pLabel);
    pLayer:setAccelerometerEnabled(true);
--  schedule(schedule_selector(Bug624Layer::switchLayer), 5.0f);
	
	local function BugTest624_SwitchLayer()
		local scheduler = CCDirector:sharedDirector():getScheduler()
		scheduler:unscheduleScriptEntry(BugTest624_entry)
			
		local pScene = CCScene:create(); 
		local pNewPlayer = BugTest624_2()
		CreateBugsTestBackMenuItem(pNewPlayer)   
        pScene:addChild(pNewPlayer);   
        CCDirector:sharedDirector():replaceScene(CCTransitionFade:create(2.0, pScene, ccc3(255,255,255))); 
	end
	
	
    local function BugTest624_OnEnterOrExit(tag)
    	local scheduler = CCDirector:sharedDirector():getScheduler()
		if tag == "enter" then
			BugTest624_entry = scheduler:scheduleScriptFunc(BugTest624_SwitchLayer, 5.0, false)
		elseif tag == "exit" then
			scheduler:unscheduleScriptEntry(BugTest624_entry)
		end
    end 
    pLayer:registerScriptHandler(BugTest624_OnEnterOrExit)
    
    local function didAccelerate(x,y,z,timestamp)
    	print("Layer1 accel")
    end
    pLayer:registerScriptAccelerateHandler(didAccelerate)
    
    return pLayer 
end

function BugTest624_2()
	local pLayer = CCLayer:create()
	
	local pLabel = CCLabelTTF:create("Layer2", "Marker Felt", 36);
	pLabel:setPosition(ccp(Winsize.width / 2, Winsize.height / 2));
    pLayer:addChild(pLabel);
    pLayer:setAccelerometerEnabled(true);
    
    local function BugTest624_2_SwitchLayer()
		local scheduler = CCDirector:sharedDirector():getScheduler()
		scheduler:unscheduleScriptEntry(BugTest624_2_entry)
			
		local pScene = CCScene:create(); 
		local pNewPlayer = BugTest624()
		CreateBugsTestBackMenuItem(pNewPlayer)   
        pScene:addChild(pNewPlayer);
        CCDirector:sharedDirector():replaceScene(CCTransitionFade:create(2.0, pScene, ccc3(255,0,0))); 
	end
	
	local function BugTest624_2_OnEnterOrExit(tag)
    	local scheduler = CCDirector:sharedDirector():getScheduler()
		if tag == "enter" then
			BugTest624_2_entry = scheduler:scheduleScriptFunc(BugTest624_2_SwitchLayer, 5.0, false)
		elseif tag == "exit" then
			scheduler:unscheduleScriptEntry(BugTest624_2_entry)
		end
    end    
    pLayer:registerScriptHandler(BugTest624_2_OnEnterOrExit)
    
    local function didAccelerate(x,y,z,timestamp)
    	print("Layer2 accel")
    end
    
    pLayer:registerScriptAccelerateHandler(didAccelerate)
	return pLayer
end

--BugTest886
local function BugTest886()
    local pLayer = CCLayer:create()
    
    local pSprite1 = CCSprite:create("Images/bugs/bug886.jpg")
    pSprite1:setAnchorPoint(ccp(0, 0))
    pSprite1:setPosition(ccp(0, 0))
    pSprite1:setScaleX(0.6)
    pLayer:addChild(pSprite1)
    
    local pSprite2 = CCSprite:create("Images/bugs/bug886.jpg")
    pSprite2:setAnchorPoint(ccp(0, 0))
    pSprite2:setScaleX(0.6)
    pSprite2:setPosition(ccp(pSprite1:getContentSize().width * 0.6 + 10, 0))
    pLayer:addChild(pSprite2)
    
    return pLayer
end

--BugTest899
local function BugTest899()
    local pLayer = CCLayer:create()
    
    local pBg = CCSprite:create("Images/bugs/RetinaDisplay.jpg")
    pLayer:addChild(pBg,0)
    pBg:setAnchorPoint(ccp(0, 0))

    return pLayer
end

--BugTest914
local function BugTest914()
    local pLayer = CCLayer:create()
    
    pLayer:setTouchEnabled(true);
    
    local pLayerColor = nil
    
    for i = 0, 4 do
       pLayerColor = CCLayerColor:create(ccc4(i*20, i*20, i*20,255))
       pLayerColor:setContentSize(CCSizeMake(i*100, i*100));
       pLayerColor:setPosition(ccp(Winsize.width/2, Winsize.height/2))
       pLayerColor:setAnchorPoint(ccp(0.5, 0.5));
       pLayerColor:ignoreAnchorPointForPosition(false);
       pLayer:addChild(pLayerColor, -1-i);
    end
    
    --create and initialize a Label
    local function restart()
       local pScene = CCScene:create()
       local pLayer = BugTest914()
       CreateBugsTestBackMenuItem(pLayer)
       pScene:addChild(pLayer);
       CCDirector:sharedDirector():replaceScene(pScene)
	end

    local label = CCLabelTTF:create("Hello World", "Marker Felt", 64)
    --position the label on the center of the screen
    label:setPosition(ccp( Winsize.width /2 , Winsize.height/2 ));
    pLayer:addChild(label);
    
    local item1 = CCMenuItemFont:create("restart")
    item1:registerScriptTapHandler(restart)
    --Bug914Layer::restart));
    
    local menu = CCMenu:create()
    menu:addChild(item1)
    menu:alignItemsVertically()
    menu:setPosition(ccp(Winsize.width/2, 100))
    pLayer:addChild(menu)
    
    -- handling touch events   
    local function onTouchMoved(tableArray)		
		local nCount = table.getn(tableArray)	
		nCount = math.floor(nCount / 3)
		print(nCount)
    end
    local function onTouchBegan(tableArray)
		onTouchMoved(tableArray)
    end
    

    local function onTouch(eventType,tableArray)
        if eventType == "began" then
            return onTouchBegan(tableArray)
        elseif eventType == "moved" then
            return onTouchMoved(tableArray)
        end
    end
    pLayer:registerScriptTouchHandler(onTouch,true)
    return pLayer
end

--BugTest1159
local function BugTest1159()
    local pLayer = CCLayer:create()
    
    CCDirector:sharedDirector():setDepthTest(true)

    local background = CCLayerColor:create(ccc4(255, 0, 255, 255))
    pLayer:addChild(background)

    local sprite_a   = CCLayerColor:create(ccc4(255, 0, 0, 255), 700, 700)
    sprite_a:setAnchorPoint(ccp(0.5, 0.5))
    sprite_a:ignoreAnchorPointForPosition(false)
    sprite_a:setPosition(ccp(0.0, Winsize.height/2))
    pLayer:addChild(sprite_a)


	local arr = CCArray:create()
	arr:addObject(CCMoveTo:create(1.0, ccp(1024.0, 384.0)))
	arr:addObject(CCMoveTo:create(1.0, ccp(0.0, 384.0)))
    local seq = CCSequence:create(arr)     
    sprite_a:runAction(CCRepeatForever:create(seq))

    local sprite_b = CCLayerColor:create(ccc4(0, 0, 255, 255), 400, 400);
    sprite_b:setAnchorPoint(ccp(0.5, 0.5))
    sprite_b:ignoreAnchorPointForPosition(false);
    sprite_b:setPosition(ccp(Winsize.width/2, Winsize.height/2));
    pLayer:addChild(sprite_b);

	local function menuCallback()
	   local pScene = CCScene:create()
       local pLayer = BugTest1159()
       CreateBugsTestBackMenuItem(pLayer)
       pScene:addChild(pLayer);
       CCDirector:sharedDirector():replaceScene(CCTransitionPageTurn:create(1.0, pScene, false))
	end
    local label = CCMenuItemLabel:create(CCLabelTTF:create("Flip Me", "Helvetica", 24));
    label:registerScriptTapHandler(menuCallback)
    local menu = CCMenu:create();
    menu:addChild(label)
    menu:setPosition(ccp(Winsize.width - 200.0, 50.0));
    pLayer:addChild(menu);
    
    local function onNodeEvent(event)
        if event == "exit" then
        --[[
            if schedulerEntry ~= nil then
                scheduler:unscheduleScriptEntry(schedulerEntry)
            end
            ]]--
            CCDirector:sharedDirector():setDepthTest(false)
        end
    end

    pLayer:registerScriptHandler(onNodeEvent)

	return pLayer
end

--BugTest1174
local function BugTest1174()
    local pLayer = CCLayer:create()
    
    local function check_for_error(p1,p2,p3,p4,s,t)
        local p4_p3 = ccpSub(p4,p3)
        local p4_p3_t = ccpMult(p4_p3,t)
        local hitPoint1 = ccpAdd(p3,p4_p3_t)
        
        local p2_p1 = ccpSub(p2,p1)
        local p2_p1_s = ccpMult(p2_p1,s)
        local hitPoint2 = ccpAdd(p1,p2_p1_s)
        
        if math.abs(hitPoint1.x - hitPoint2.x ) > 0.1 or math.abs(hitPoint1.y - hitPoint2.y) > 0.1 then
        	local strErr = "ERROR: ("..hitPoint1.x..","..hitPoint1.y..") != ("..hitPoint2.x..","..hitPoint2.y..")"
            print(strErr)
        	return 1
        end
        return 0
    end
    local A,B,C,D,p1,p2,p3,p4
    local s = 0.0
    local t = 0.0
    local err = 0
    local ok  = 0
    local bRet = false
    
    print("Test1 - Start")
    local i = 0;
    for i = 0, 9999 do
        --[[
        A|b
        -----
        c|d
        ]]--
        local ax = math.random() * -5000
        local ay = math.random() * 5000
        --[[
        a|b
        -----
        c|D 
        ]]--      
        local dx = math.random() * 5000
        local dy = math.random() * -5000
        
        --[[
        a|B
        -----
        c|d 
        ]]--
        local bx = math.random() * 5000
        local by = math.random() * 5000
        
        --[[
        a|b
        -----
        C|d
        ]]--
        local cx = math.random() * -5000
        local cy = math.random() * -5000
        
        A = ccp(ax,ay)
        B = ccp(bx,by)
        C = ccp(cx,cy)
        D = ccp(dx,dy)
       
        bRet,s,t = ccpLineIntersect( A, D, B, C, s, t)
        if true == bRet then
            if 1 == check_for_error(A,D,B,C,s,t) then
                err = err + 1
            else
                ok = ok + 1
            end
        end
    end
    local strLog = "Test1 - End. OK="..ok..", Err="..err
    print(strLog)
    --------
    --Test 2
    --------
    print("Test2 - Start")
        
    p1 = ccp(220,480);
    p2 = ccp(304,325);
    p3 = ccp(264,416);
    p4 = ccp(186,416);
    s  = 0.0;
    t  = 0.0;
    bRet,s,t = ccpLineIntersect( p1, p2, p3, p4, s, t)
    if true == bRet then
    	check_for_error(p1, p2, p3, p4, s, t)
    end
    print("Test2 - End")
    
    ------
    --Test 3
    ------
    print("Test3 - Start")
        
    ok=0
    err=0
    for i = 0 , 9999 do
        -- A | b
        -- -----
        -- c | d
        local ax = math.random() * -500
        local ay = math.random() * 500
        p1 = ccp(ax,ay);
        -- a | b
        -- -----
        -- c | D
        local dx = math.random() * 500
        local dy = math.random() * -500
        p2 = ccp(dx,dy)
        
        -------
            
        local y = ay - ((ay - dy) / 2.0)
        
        -- a | b
        -- -----
        -- C | d
        local cx = math.random() * -500
        p3 = ccp(cx,y)
            
        -- a | B
        -- -----
        -- c | d
        local bx = math.random() * 500
        p4 = ccp(bx,y)
        
        s = 0.0
        t = 0.0
        bRet,s,t = ccpLineIntersect(p1, p2, p3, p4, s, t)
        if true == bRet then 
          if 1 == check_for_error(p1, p2, p3, p4, s,t ) then
             err = err + 1
          else
             ok = ok + 1
          end
        end
    end
    strLog = "Test3 - End. OK="..ok..", Err="..err
    print(strLog)
    
    return pLayer
end

local CreateBugsTestTable = {
   BugTest350,
   BugTest422,
   BugTest458,
   BugTest624,
   BugTest886,
   BugTest899,
   BugTest914,
   BugTest1159,
   BugTest1174,
}

local function CreateBugsTestScene(nBugNo)
  local pNewscene = CCScene:create()
  local pLayer = CreateBugsTestTable[nBugNo]()
  CreateBugsTestBackMenuItem(pLayer)
  pNewscene:addChild(pLayer)
  CCDirector:sharedDirector():replaceScene(pNewscene)
--pLayer:autorelease()
end


local function BugsTestMainLayer()
	local ret = CCLayer:create(); 
    
    --menu callback
    local function menuCallback(tag, pMenuItem)
        local nIdx = pMenuItem:getZOrder() - kItemTagBasic
        local BugTestScene = CreateBugsTestScene(nIdx)
        if nil ~= testScene then
            CCDirector:sharedDirector():replaceScene(testScene)
        end
    end
	
	-- add menu items for tests
    local pItemMenu = CCMenu:create();
    local nTestCount = table.getn(testNames);
    
    local i = 1
    for  i = 1, nTestCount do
        local  label = CCLabelTTF:create(testNames[i], "Arial", 24)
        local  pMenuItem = CCMenuItemLabel:create(label)
        pMenuItem:registerScriptTapHandler(menuCallback)
        pItemMenu:addChild(pMenuItem, i + kItemTagBasic)
       pMenuItem:setPosition( ccp( VisibleRect:center().x, (VisibleRect:top().y - i * LINE_SPACE) ))
    end
    
    pItemMenu:setPosition(ccp(0, 0))   
    ret:addChild(pItemMenu)
    ret:setTouchEnabled(true)
    
    -- handling touch events
    local ptBeginPos = {x = 0, y = 0}
    local ptCurPos  = {x = 0, y = 0}
    local function onTouchBegan(x, y)
        ptBeginPos = {x = x, y = y}
        -- CCTOUCHBEGAN event must return true
        return true
    end
    
    local function onTouchMoved(x, y)
        local nMoveY = y - ptBeginPos.y
        local curPosx, curPosy = pItemMenu:getPosition()
        local nextPosy = curPosy + nMoveY
        if nextPosy < 0 then
            pItemMenu:setPosition(0, 0)
            return
        end

        if nextPosy > ((nTestCount + 1) * LINE_SPACE - Winsize.height) then
            pItemMenu:setPosition(0, ((nTestCount + 1) * LINE_SPACE - Winsize.height))
            return
        end

        pItemMenu:setPosition(curPosx, nextPosy)
        ptBeginPos = {x = x, y = y}
        ptCurPos = {x = curPosx, y = nextPosy}
    end
    
    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return onTouchBegan(x, y)
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        end
    end

    ret:registerScriptTouchHandler(onTouch)
    
    return ret
end
function BugsTestMain()
	cclog("BugsTestMain");
	local scene = CCScene:create();
	scene:addChild(BugsTestMainLayer());
	scene:addChild(CreateBackMenuItem());
	return scene;
end
