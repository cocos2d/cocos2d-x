local    MAX_COUNT = 9
local    LINE_SPACE = 40
local    kItemTagBasic = 5432

local Winsize = cc.Director:getInstance():getWinSize()

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
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local pMenuItemFont = cc.MenuItemFont:create("Back")
    pMenuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    local function menuCallback()
        local pScene = BugsTestMain()
        if pScene ~= nil then
            cc.Director:getInstance():replaceScene(pScene)
        end
    end
    pMenuItemFont:registerScriptTapHandler(menuCallback)
    local pMenu = cc.Menu:create()
    pMenu:addChild(pMenuItemFont)
    pMenu:setPosition(cc.p(0, 0))
    pLayer:addChild(pMenu)
end

--BugTest350
local function BugTest350()
    local pLayer = cc.Layer:create()
    local pBackground = cc.Sprite:create("Hello.png")
    pBackground:setPosition(cc.p(Winsize.width/2, Winsize.height/2))
    pLayer:addChild(pBackground)
    return pLayer
end

--BugTest422
local nLocalTag = 0
local function BugTest422()
    local function reset(pResetLayer)
        nLocalTag = nLocalTag + 1
        local pNode = pResetLayer:getChildByTag(nLocalTag - 1)
        if nil ~= pNode then
           --userdata per
           local strLog = "Menu:"..nLocalTag
           print(strLog)
        end

        pResetLayer:removeChild(pNode, false)
        
        local function menuCallback(tag,pMenuItem)
            if nil ~= pMenuItem then
                local pCallbackLayer = pMenuItem:getParent():getParent()
                reset(pCallbackLayer)
            end
        end
        cc.MenuItemFont:setFontName("Arial")
        cc.MenuItemFont:setFontSize(24)
        local pMenuItem1 = cc.MenuItemFont:create("One")
        pMenuItem1:registerScriptTapHandler(menuCallback)
        local pMenuItem2 = cc.MenuItemFont:create("Two")
        pMenuItem2:registerScriptTapHandler(menuCallback)
        local pMenu = cc.Menu:create(pMenuItem1, pMenuItem2)
        pMenu:alignItemsVertically()
        local fX = math.random() * 50
        local fY = math.random() * 50
        local menuPosX ,menuPosY = pMenu:getPosition()
        pMenu:setPosition(cc.p(menuPosX + fX,menuPosY + fY))
        pResetLayer:addChild(pMenu,0,nLocalTag)
    end
    
    local pLayer = cc.Layer:create()
    reset(pLayer)
    return pLayer
end

--BugTest458
local nColorFlag = 0
local function BugTest458()
    local pLayer = cc.Layer:create()
    
    local function InitQuestionContainerSprite(pSprite)
        --Add label
        local pLabel = cc.LabelTTF:create("Answer 1", "Arial", 12)
        pLabel:setTag(100)
        
        --Add the background
        local pCorner = cc.Sprite:create("Images/bugs/corner.png")
        local nWidth = Winsize.width * 0.9 - (pCorner:getContentSize().width * 2)
        local nHeight = Winsize.height * 0.15  - (pCorner:getContentSize().height * 2)
        local pColorLayer = cc.LayerColor:create(cc.c4b(255, 255, 255, 255 * .75), nWidth, nHeight)
        pColorLayer:setPosition(cc.p(-nWidth / 2, -nHeight / 2))
        --First button is blue,Second is red,Used for testing - change later
        if (0 == nColorFlag) then
            pLabel:setColor(cc.c3b(0,0,255))
        else
            print("Color changed")
            pLabel:setColor(cc.c3b(255,0,0))
        end
        nColorFlag = nColorFlag + 1
        pSprite:addChild(pColorLayer)
        
        pCorner:setPosition(cc.p(-(nWidth / 2 + pCorner:getContentSize().width / 2), -(nHeight / 2 + pCorner:getContentSize().height / 2)))
        pSprite:addChild(pCorner)
		
		local nX,nY = pCorner:getPosition()
        local pCorner2 = cc.Sprite:create("Images/bugs/corner.png")
        pCorner2:setPosition(cc.p(-nX, nY))
        pCorner2:setFlipX(true)
        pSprite:addChild(pCorner2)

        local pCorner3 = cc.Sprite:create("Images/bugs/corner.png")
        pCorner3:setPosition(cc.p(nX, -nY))
        pCorner3:setFlipY(true)
        pSprite:addChild(pCorner3)

        local pCorner4 = cc.Sprite:create("Images/bugs/corner.png")
        pCorner4:setPosition(cc.p(-nX, -nY))
        pCorner4:setFlipX(true)
        pCorner4:setFlipY(true)
        pSprite:addChild(pCorner4)

        local pEdge = cc.Sprite:create("Images/bugs/edge.png")
        pEdge:setScaleX(nWidth)
        pEdge:setPosition(cc.p(nX + (pCorner:getContentSize().width / 2) + (nWidth / 2), nY))
        pSprite:addChild(pEdge)
        
        local pEdge2 = cc.Sprite:create("Images/bugs/edge.png")
        pEdge2:setScaleX(nWidth)
        pEdge2:setPosition(cc.p(nX + (pCorner:getContentSize().width / 2) + (nWidth / 2), -nY))
        pEdge2:setFlipY(true)
        pSprite:addChild(pEdge2)

        local pEdge3 = cc.Sprite:create("Images/bugs/edge.png")
        pEdge3:setRotation(90)
        pEdge3:setScaleX(nHeight)
        pEdge3:setPosition(cc.p(nX, nY + (pCorner:getContentSize().height / 2) + (nHeight / 2)))
        pSprite:addChild(pEdge3)

        local pEdge4 = cc.Sprite:create("Images/bugs/edge.png")
        pEdge4:setRotation(270)
        pEdge4:setScaleX(nHeight)
        pEdge4:setPosition(cc.p(-nX, nY + (pCorner:getContentSize().height / 2) + (nHeight / 2)))
        pSprite:addChild(pEdge4)

        pSprite:addChild(pLabel)
    end
    
    local pQuestion1 = cc.Sprite:create()
    InitQuestionContainerSprite(pQuestion1)
    local pQuestion2 = cc.Sprite:create()
    InitQuestionContainerSprite(pQuestion2)
    
    local function menuCallback()
        print("Selected")
    end
    local pMenuItemSprite = cc.MenuItemSprite:create(pQuestion1,pQuestion2)
    pMenuItemSprite:registerScriptTapHandler(menuCallback)
    local pLayerColor1 = cc.LayerColor:create(cc.c4b(0,0,255,255), 100, 100)
--  question->release()
--  question2->release()

    local pLayerColor2 = cc.LayerColor:create(cc.c4b(255,0,0,255), 100, 100)
    local pMenuItemSprite2 = cc.MenuItemSprite:create(pLayerColor1, pLayerColor2)   
    pMenuItemSprite2:registerScriptTapHandler(menuCallback) 
    local pMenu = cc.Menu:create(pMenuItemSprite, pMenuItemSprite2)
    pMenu:alignItemsVerticallyWithPadding(100)
    pMenu:setPosition(cc.p(Winsize.width / 2, Winsize.height / 2))

    -- add the label as a child to this Layer
    pLayer:addChild(pMenu)

    return pLayer
end

--BugTest624
local BugTest624_entry = nil
local BugTest624_2_entry = nil

local function BugTest624()
    local pLayer = cc.Layer:create()
    
    local pLabel = cc.LabelTTF:create("Layer1", "Marker Felt", 36)
    pLabel:setPosition(cc.p(Winsize.width / 2, Winsize.height / 2))
    pLayer:addChild(pLabel)
    pLayer:setAccelerometerEnabled(true)
--  schedule(schedule_selector(Bug624Layer::switchLayer), 5.0f)
	
	local function BugTest624_SwitchLayer()
		local scheduler = cc.Director:getInstance():getScheduler()
		scheduler:unscheduleScriptEntry(BugTest624_entry)
			
		local pScene = cc.Scene:create() 
		local pNewPlayer = BugTest624_2()
		CreateBugsTestBackMenuItem(pNewPlayer)   
        pScene:addChild(pNewPlayer)   
        cc.Director:getInstance():replaceScene(cc.TransitionFade:create(2.0, pScene, cc.c3b(255,255,255))) 
	end
	
	
    local function BugTest624_OnEnterOrExit(tag)
    	local scheduler = cc.Director:getInstance():getScheduler()
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
	local pLayer = cc.Layer:create()
	
	local pLabel = cc.LabelTTF:create("Layer2", "Marker Felt", 36)
	pLabel:setPosition(cc.p(Winsize.width / 2, Winsize.height / 2))
    pLayer:addChild(pLabel)
    pLayer:setAccelerometerEnabled(true)
    
    local function BugTest624_2_SwitchLayer()
		local scheduler = cc.Director:getInstance():getScheduler()
		scheduler:unscheduleScriptEntry(BugTest624_2_entry)
			
		local pScene = cc.Scene:create() 
		local pNewPlayer = BugTest624()
		CreateBugsTestBackMenuItem(pNewPlayer)   
        pScene:addChild(pNewPlayer)
        cc.Director:getInstance():replaceScene(cc.TransitionFade:create(2.0, pScene, cc.c3b(255,0,0))) 
	end
	
	local function BugTest624_2_OnEnterOrExit(tag)
    	local scheduler = cc.Director:getInstance():getScheduler()
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
    local pLayer = cc.Layer:create()
    
    local pSprite1 = cc.Sprite:create("Images/bugs/bug886.jpg")
    pSprite1:setAnchorPoint(cc.p(0, 0))
    pSprite1:setPosition(cc.p(0, 0))
    pSprite1:setScaleX(0.6)
    pLayer:addChild(pSprite1)
    
    local pSprite2 = cc.Sprite:create("Images/bugs/bug886.jpg")
    pSprite2:setAnchorPoint(cc.p(0, 0))
    pSprite2:setScaleX(0.6)
    pSprite2:setPosition(cc.p(pSprite1:getContentSize().width * 0.6 + 10, 0))
    pLayer:addChild(pSprite2)
    
    return pLayer
end

--BugTest899
local function BugTest899()
    local pLayer = cc.Layer:create()
    
    local pBg = cc.Sprite:create("Images/bugs/RetinaDisplay.jpg")
    pLayer:addChild(pBg,0)
    pBg:setAnchorPoint(cc.p(0, 0))

    return pLayer
end

--BugTest914
local function BugTest914()
    local layer = cc.Layer:create()
    
    local layerColor = nil
    
    for i = 0, 4 do
       layerColor = cc.LayerColor:create(cc.c4b(i*20, i*20, i*20,255))
       layerColor:setContentSize(cc.size(i*100, i*100))
       layerColor:setPosition(cc.p(Winsize.width/2, Winsize.height/2))
       layerColor:setAnchorPoint(cc.p(0.5, 0.5))
       layerColor:ignoreAnchorPointForPosition(false)
       layer:addChild(layerColor, -1-i)
    end
    
    --create and initialize a Label
    local function restart()
       local scene = cc.Scene:create()
       local newLayer = BugTest914()
       CreateBugsTestBackMenuItem(newLayer)
       scene:addChild(newLayer)
       cc.Director:getInstance():replaceScene(scene)
	end

    local label = cc.LabelTTF:create("Hello World", "Marker Felt", 64)
    --position the label on the center of the screen
    label:setPosition(cc.p( Winsize.width /2 , Winsize.height/2 ))
    layer:addChild(label)
    
    local item1 = cc.MenuItemFont:create("restart")
    item1:registerScriptTapHandler(restart)
    
    local menu = cc.Menu:create()
    menu:addChild(item1)
    menu:alignItemsVertically()
    menu:setPosition(cc.p(Winsize.width/2, 100))
    layer:addChild(menu)
    
    -- handling touch events   
    local function onTouchMoved(touches, event)		
		local count = table.getn(touches)	
		print("Number of touches: ",count)
    end
    local function onTouchBegan(touches, event)
		onTouchMoved(touches, event)
    end
    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCHES_MOVED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    return layer
end

--BugTest1159
local function BugTest1159()
    local pLayer = cc.Layer:create()
    
    cc.Director:getInstance():setDepthTest(true)

    local background = cc.LayerColor:create(cc.c4b(255, 0, 255, 255))
    pLayer:addChild(background)

    local sprite_a   = cc.LayerColor:create(cc.c4b(255, 0, 0, 255), 700, 700)
    sprite_a:setAnchorPoint(cc.p(0.5, 0.5))
    sprite_a:ignoreAnchorPointForPosition(false)
    sprite_a:setPosition(cc.p(0.0, Winsize.height/2))
    pLayer:addChild(sprite_a)
    local seq = cc.Sequence:create(cc.MoveTo:create(1.0, cc.p(1024.0, 384.0)), cc.MoveTo:create(1.0, cc.p(0.0, 384.0)))     
    sprite_a:runAction(cc.RepeatForever:create(seq))

    local sprite_b = cc.LayerColor:create(cc.c4b(0, 0, 255, 255), 400, 400)
    sprite_b:setAnchorPoint(cc.p(0.5, 0.5))
    sprite_b:ignoreAnchorPointForPosition(false)
    sprite_b:setPosition(cc.p(Winsize.width/2, Winsize.height/2))
    pLayer:addChild(sprite_b)

	local function menuCallback()
	   local pScene = cc.Scene:create()
       local pLayer = BugTest1159()
       CreateBugsTestBackMenuItem(pLayer)
       pScene:addChild(pLayer)
       cc.Director:getInstance():replaceScene(cc.TransitionPageTurn:create(1.0, pScene, false))
	end
    local label = cc.MenuItemLabel:create(cc.LabelTTF:create("Flip Me", "Helvetica", 24))
    label:registerScriptTapHandler(menuCallback)
    local menu = cc.Menu:create()
    menu:addChild(label)
    menu:setPosition(cc.p(Winsize.width - 200.0, 50.0))
    pLayer:addChild(menu)
    
    local function onNodeEvent(event)
        if event == "exit" then
        --[[
            if schedulerEntry ~= nil then
                scheduler:unscheduleScriptEntry(schedulerEntry)
            end
            ]]--
            cc.Director:getInstance():setDepthTest(false)
        end
    end

    pLayer:registerScriptHandler(onNodeEvent)

	return pLayer
end

--BugTest1174
local function BugTest1174()
    local pLayer = cc.Layer:create()
    
    local function check_for_error(p1,p2,p3,p4,s,t)
        local p4_p3 = cc.pSub(p4,p3)
        local p4_p3_t = cc.pMul(p4_p3,t)
        local hitp1 = cc.pAdd(p3,p4_p3_t)
        
        local p2_p1 = cc.pSub(p2,p1)
        local p2_p1_s = cc.pMul(p2_p1,s)
        local hitp2 = cc.pAdd(p1,p2_p1_s)
        
        if math.abs(hitp1.x - hitp2.x ) > 0.1 or math.abs(hitp1.y - hitp2.y) > 0.1 then
        	local strErr = "ERROR: ("..hitp1.x..","..hitp1.y..") != ("..hitp2.x..","..hitp2.y..")"
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
    local i = 0
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
        
        A = cc.p(ax,ay)
        B = cc.p(bx,by)
        C = cc.p(cx,cy)
        D = cc.p(dx,dy)
       
        bRet,s,t = cc.pIsLineIntersect( A, D, B, C, s, t)
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
        
    p1 = cc.p(220,480)
    p2 = cc.p(304,325)
    p3 = cc.p(264,416)
    p4 = cc.p(186,416)
    s  = 0.0
    t  = 0.0
    bRet,s,t = cc.pIsLineIntersect( p1, p2, p3, p4, s, t)
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
        p1 = cc.p(ax,ay)
        -- a | b
        -- -----
        -- c | D
        local dx = math.random() * 500
        local dy = math.random() * -500
        p2 = cc.p(dx,dy)
        
        -------
            
        local y = ay - ((ay - dy) / 2.0)
        
        -- a | b
        -- -----
        -- C | d
        local cx = math.random() * -500
        p3 = cc.p(cx,y)
            
        -- a | B
        -- -----
        -- c | d
        local bx = math.random() * 500
        p4 = cc.p(bx,y)
        
        s = 0.0
        t = 0.0
        bRet,s,t = cc.pIsLineIntersect(p1, p2, p3, p4, s, t)
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
  local pNewscene = cc.Scene:create()
  local pLayer = CreateBugsTestTable[nBugNo]()
  CreateBugsTestBackMenuItem(pLayer)
  pNewscene:addChild(pLayer)
  cc.Director:getInstance():replaceScene(pNewscene)
--pLayer:autorelease()
end


local function BugsTestMainLayer()
	local ret = cc.Layer:create() 
    
    --menu callback
    local function menuCallback(tag, pMenuItem)
        local nIdx = pMenuItem:getLocalZOrder() - kItemTagBasic
        local BugTestScene = CreateBugsTestScene(nIdx)
        if nil ~= testScene then
            cc.Director:getInstance():replaceScene(testScene)
        end
    end
	
	-- add menu items for tests
    local pItemMenu = cc.Menu:create()
    local nTestCount = table.getn(testNames)
    
    local i = 1
    for  i = 1, nTestCount do
        local  label = cc.LabelTTF:create(testNames[i], "Arial", 24)
        local  pMenuItem = cc.MenuItemLabel:create(label)
        pMenuItem:registerScriptTapHandler(menuCallback)
        pItemMenu:addChild(pMenuItem, i + kItemTagBasic)
       pMenuItem:setPosition( cc.p( VisibleRect:center().x, (VisibleRect:top().y - i * LINE_SPACE) ))
    end
    
    pItemMenu:setPosition(cc.p(0, 0))   
    ret:addChild(pItemMenu)
    
    -- handling touch events
    local ptBeginPos = {x = 0, y = 0}
    local ptCurPos  = {x = 0, y = 0}

    -- handling touch events   
    local function onTouchMoved(touches, event) 
        local touchLocation = touches[1]:getLocation()   
        local nMoveY = touchLocation.y - ptBeginPos.y
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
        ptBeginPos = touchLocation
        ptCurPos = {x = curPosx, y = nextPosy}
    end
    local function onTouchBegan(touches, event)
        ptBeginPos = touches[1]:getLocation()
    end
    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCHES_MOVED )

    local eventDispatcher = ret:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ret) 
    
    return ret
end
function BugsTestMain()
	cclog("BugsTestMain")
	local scene = cc.Scene:create()
	scene:addChild(BugsTestMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
