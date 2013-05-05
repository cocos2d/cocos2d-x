local    kTagMenu = 1
local    kTagMenu0 = 0
local    kTagMenu1 = 1

local MID_CALLBACK     = 1000
local MID_CALLBACK2    = 1001
local MID_DISABLED     = 1002
local MID_ENABLE       = 1003
local MID_CONFIG       = 1004
local MID_QUIT         = 1005
local MID_OPACITY      = 1006
local MID_ALIGN        = 1007
local MID_CALLBACK3    = 1008
local MID_BACKCALLBACK = 1009

--------------------------------------------------------------------
--
-- MenuLayerMainMenu
--
--------------------------------------------------------------------
local function MenuLayerMainMenu()
    local m_disabledItem = nil

    local ret = CCLayer:create()
    ret:setTouchEnabled(true)
    ret:setTouchPriority(kCCMenuHandlerPriority + 1)
    ret:setTouchMode(kCCTouchesOneByOne)

    -- Font Item
    local  spriteNormal = CCSprite:create(s_MenuItem, CCRectMake(0,23*2,115,23))
    local  spriteSelected = CCSprite:create(s_MenuItem, CCRectMake(0,23*1,115,23))
    local  spriteDisabled = CCSprite:create(s_MenuItem, CCRectMake(0,23*0,115,23))

    local  item1 = CCMenuItemSprite:create(spriteNormal, spriteSelected, spriteDisabled)

    local function menuCallback(sender)
        cclog("menuCallback...")
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(1)
    end

    item1:registerScriptTapHandler(menuCallback)
    -- Image Item
    local function menuCallback2(sender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(2)
    end

    local  item2 = CCMenuItemImage:create(s_SendScore, s_PressSendScore)
    item2:registerScriptTapHandler(menuCallback2)


    local schedulerEntry = nil

    local function allowTouches(dt)
        local  pDirector = CCDirector:sharedDirector()
        pDirector:getTouchDispatcher():setPriority(kCCMenuHandlerPriority+1, ret)
        scheduler:unscheduleScriptEntry(schedulerEntry)
        cclog("TOUCHES ALLOWED AGAIN")
    end


    local function menuCallbackDisabled(sender)
        -- hijack all touch events for 5 seconds
        local  pDirector = CCDirector:sharedDirector()
        pDirector:getTouchDispatcher():setPriority(kCCMenuHandlerPriority-1, ret)
        schedulerEntry = scheduler:scheduleScriptFunc(allowTouches, 5, false)
        cclog("TOUCHES DISABLED FOR 5 SECONDS")
    end

    -- Label Item (LabelAtlas)
    local  labelAtlas = CCLabelAtlas:create("0123456789", "fonts/labelatlas.png", 16, 24, string.byte('.'))
    local  item3 = CCMenuItemLabel:create(labelAtlas)
    item3:registerScriptTapHandler(menuCallbackDisabled)
    item3:setDisabledColor( ccc3(32,32,64) )
    item3:setColor( ccc3(200,200,255) )

    local function menuCallbackEnable(sender)
        m_disabledItem:setEnabled(not m_disabledItem:isEnabled() )
    end

    -- Font Item
    local item4 = CCMenuItemFont:create("I toggle enable items")
    item4:registerScriptTapHandler(menuCallbackEnable)

    item4:setFontSizeObj(20)
    CCMenuItemFont:setFontName("Marker Felt")

    local function menuCallbackConfig(sender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(3)
    end

    -- Label Item (CCLabelBMFont)
    local  label = CCLabelBMFont:create("configuration", "fonts/bitmapFontTest3.fnt")
    local  item5 = CCMenuItemLabel:create(label)
    item5:registerScriptTapHandler(menuCallbackConfig)

    -- Testing issue #500
    item5:setScale( 0.8 )

    local function menuCallbackPriorityTest(pSender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(4)
    end

    -- Events
    CCMenuItemFont:setFontName("Marker Felt")
    local item6 = CCMenuItemFont:create("Priority Test")
    item6:registerScriptTapHandler(menuCallbackPriorityTest)

    local function menuCallbackBugsTest(pSender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(5)
    end

    -- Bugs Item
    local item7 = CCMenuItemFont:create("Bugs")
    item7:registerScriptTapHandler(menuCallbackBugsTest)

    local function onQuit(sender)
        cclog("onQuit item is clicked.")
    end

    -- Font Item
    local  item8 = CCMenuItemFont:create("Quit")
    item8:registerScriptTapHandler(onQuit)

    local function menuMovingCallback(pSender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(6)
    end

    local  item9 = CCMenuItemFont:create("Remove menu item when moving")
    item9:registerScriptTapHandler(menuMovingCallback)

    local  color_action = CCTintBy:create(0.5, 0, -255, -255)
    local  color_back = color_action:reverse()
    local arr = CCArray:create()
    arr:addObject(color_action)
    arr:addObject(color_back)
    local  seq = CCSequence:create(arr)
    item8:runAction(CCRepeatForever:create(seq))

    local  menu = CCMenu:create()

    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)
    menu:addChild(item4)
    menu:addChild(item5)
    menu:addChild(item6)
    menu:addChild(item7)
    menu:addChild(item8)
    menu:addChild(item9)

    menu:alignItemsVertically()

    -- elastic effect
    local s = CCDirector:sharedDirector():getWinSize()

    local i        = 0
    local child    = nil
    local pArray   = menu:getChildren()
    local len      = pArray:count()
    local pObject  = nil
    for i = 0, len-1 do
        pObject = pArray:objectAtIndex(i)
        if pObject == nil then
            break
        end
        child = tolua.cast(pObject, "CCNode")

        local dstPointX, dstPointY = child:getPosition()
        local offset = s.width/2 + 50
        if  i % 2 == 0 then
            offset = 0-offset
        end
        child:setPosition( ccp( dstPointX + offset, dstPointY) )
        child:runAction( CCEaseElasticOut:create(CCMoveBy:create(2, ccp(dstPointX - offset,0)), 0.35) )
    end

    m_disabledItem = item3
    item3:retain()

    m_disabledItem:setEnabled( false )

    ret:addChild(menu)
    menu:setPosition(ccp(s.width/2, s.height/2))

    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "exit" then
            if (schedulerEntry ~= nil) then
                scheduler:unscheduleScriptEntry(schedulerEntry)
            end
            if m_disabledItem ~= nil then
                m_disabledItem:release()
            end
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- MenuLayer2
--
--------------------------------------------------------------------
local function MenuLayer2()
    local ret = CCLayer:create()
    local m_centeredMenu = nil
    local m_alignedH = false

    local function alignMenusH()
        local i = 0
        for i=0, 1 do
            local menu = tolua.cast(ret:getChildByTag(100+i), "CCMenu")
            menu:setPosition( m_centeredMenu )
            if i==0 then
                -- TIP: if no padding, padding = 5
                menu:alignItemsHorizontally()
                local x, y = menu:getPosition()
                menu:setPosition( ccpAdd(ccp(x, y), ccp(0,30)) )
            else
                -- TIP: but padding is configurable
                menu:alignItemsHorizontallyWithPadding(40)
                local x, y = menu:getPosition()
                menu:setPosition( ccpSub(ccp(x, y), ccp(0,30)) )
            end
        end
    end

    local function alignMenusV()
        local i = 0
        for i=0, 1 do
            local menu = tolua.cast(ret:getChildByTag(100+i), "CCMenu")
            menu:setPosition( m_centeredMenu )
            if i==0 then
                -- TIP: if no padding, padding = 5
                menu:alignItemsVertically()
                local x, y = menu:getPosition()
                menu:setPosition( ccpAdd(ccp(x, y), ccp(100,0)) )
            else
                -- TIP: but padding is configurable
                menu:alignItemsVerticallyWithPadding(40)
                local x, y = menu:getPosition()
                menu:setPosition( ccpSub(ccp(x, y), ccp(100,0)) )
            end
        end
    end

    local function menuCallback(sender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(0)
    end

    local function menuCallbackOpacity(tag, sender)
        local menu = tolua.cast(sender:getParent(), "CCMenu")
        local opacity = menu:getOpacity()
        if opacity == 128 then
            menu:setOpacity(255)
        else
            menu:setOpacity(128)
        end
    end

    local function menuCallbackAlign(sender)
        m_alignedH = not m_alignedH

        if m_alignedH then
            alignMenusH()
        else
            alignMenusV()
        end
    end

    local i = 0
    for i=0, 1 do
        local  item1 = CCMenuItemImage:create(s_PlayNormal, s_PlaySelect)
        item1:registerScriptTapHandler(menuCallback)

        local  item2 = CCMenuItemImage:create(s_HighNormal, s_HighSelect)
        item2:registerScriptTapHandler(menuCallbackOpacity)

        local  item3 = CCMenuItemImage:create(s_AboutNormal, s_AboutSelect)
        item3:registerScriptTapHandler(menuCallbackAlign)

        item1:setScaleX( 1.5 )
        item2:setScaleX( 0.5 )
        item3:setScaleX( 0.5 )

        local  menu = CCMenu:create()

        menu:addChild(item1)
        menu:addChild(item2)
        menu:addChild(item3)

        local s = CCDirector:sharedDirector():getWinSize()
        menu:setPosition(ccp(s.width/2, s.height/2))

        menu:setTag( kTagMenu )

        ret:addChild(menu, 0, 100+i)

        local x, y = menu:getPosition()
        m_centeredMenu = ccp(x, y)
    end

    m_alignedH = true
    alignMenusH()

    return ret
end

--------------------------------------------------------------------
--
-- MenuLayer3
--
--------------------------------------------------------------------
local function MenuLayer3()
    local m_disabledItem = nil
    local ret = CCLayer:create()
    local function menuCallback(sender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(0)
    end

    local function menuCallback2(sender)
        cclog("Label clicked. Toogling AtlasSprite")
        m_disabledItem:setEnabled( not m_disabledItem:isEnabled() )
        m_disabledItem:stopAllActions()
    end

    local function menuCallback3(sender)
        cclog("MenuItemSprite clicked")
    end

    CCMenuItemFont:setFontName("Marker Felt")
    CCMenuItemFont:setFontSize(28)

    local  label = CCLabelBMFont:create("Enable AtlasItem", "fonts/bitmapFontTest3.fnt")
    local  item1 = CCMenuItemLabel:create(label)
    item1:registerScriptTapHandler(menuCallback2)

    local  item2 = CCMenuItemFont:create("--- Go Back ---")
    item2:registerScriptTapHandler(menuCallback)

    local spriteNormal   = CCSprite:create(s_MenuItem,  CCRectMake(0,23*2,115,23))
    local spriteSelected = CCSprite:create(s_MenuItem,  CCRectMake(0,23*1,115,23))
    local spriteDisabled = CCSprite:create(s_MenuItem,  CCRectMake(0,23*0,115,23))


    local  item3 = CCMenuItemSprite:create(spriteNormal, spriteSelected, spriteDisabled)
    item3:registerScriptTapHandler(menuCallback3)
    m_disabledItem = item3
    item3:retain()
    m_disabledItem:setEnabled( false )

    local menu = CCMenu:create()

    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)

    menu:setPosition( ccp(0,0) )

    local s = CCDirector:sharedDirector():getWinSize()

    item1:setPosition( ccp(s.width/2 - 150, s.height/2) )
    item2:setPosition( ccp(s.width/2 - 200, s.height/2) )
    item3:setPosition( ccp(s.width/2, s.height/2 - 100) )

    local  jump = CCJumpBy:create(3, ccp(400,0), 50, 4)
    local arr = CCArray:create()
    arr:addObject(jump)
    arr:addObject(jump:reverse())
    item2:runAction( CCRepeatForever:create(CCSequence:create( arr)))

    local  spin1 = CCRotateBy:create(3, 360)
    local  spin2 = tolua.cast(spin1:copy():autorelease(), "CCActionInterval")
    local  spin3 = tolua.cast(spin1:copy():autorelease(), "CCActionInterval")

    item1:runAction( CCRepeatForever:create(spin1) )
    item2:runAction( CCRepeatForever:create(spin2) )
    item3:runAction( CCRepeatForever:create(spin3) )

    ret:addChild( menu )

    menu:setPosition(ccp(0,0))

    local function onNodeEvent(event)
        if event == "exit" then
            if m_disabledItem ~= nil then
                m_disabledItem:release()
            end
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end


--------------------------------------------------------------------
--
-- MenuLayer4
--
--------------------------------------------------------------------
local function MenuLayer4()
    local ret = CCLayer:create()
    CCMenuItemFont:setFontName("American Typewriter")
    CCMenuItemFont:setFontSize(18)
    local title1 = CCMenuItemFont:create("Sound")
    title1:setEnabled(false)
    CCMenuItemFont:setFontName( "Marker Felt" )
    CCMenuItemFont:setFontSize(34)
    local  item1 = CCMenuItemToggle:create(CCMenuItemFont:create( "On" ))

    local function menuCallback(tag, sender)
        cclog("selected item: tag: %d, index:%d", tag, tolua.cast(sender, "CCMenuItemToggle"):getSelectedIndex() )
    end

    local function backCallback(tag, sender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(0)
    end

    item1:registerScriptTapHandler(menuCallback)
    item1:addSubItem(CCMenuItemFont:create( "Off"))

    CCMenuItemFont:setFontName( "American Typewriter" )
    CCMenuItemFont:setFontSize(18)
    local  title2 = CCMenuItemFont:create( "Music" )
    title2:setEnabled(false)
    CCMenuItemFont:setFontName( "Marker Felt" )
    CCMenuItemFont:setFontSize(34)
    local item2 = CCMenuItemToggle:create(CCMenuItemFont:create( "On" ))
    item2:registerScriptTapHandler(menuCallback)
    item2:addSubItem(CCMenuItemFont:create( "Off"))

    CCMenuItemFont:setFontName( "American Typewriter" )
    CCMenuItemFont:setFontSize(18)
    local  title3 = CCMenuItemFont:create( "Quality" )
    title3:setEnabled( false )
    CCMenuItemFont:setFontName( "Marker Felt" )
    CCMenuItemFont:setFontSize(34)
    local item3 = CCMenuItemToggle:create(CCMenuItemFont:create( "High" ))
    item3:registerScriptTapHandler(menuCallback)
    item3:addSubItem(CCMenuItemFont:create( "Low" ))

    CCMenuItemFont:setFontName( "American Typewriter" )
    CCMenuItemFont:setFontSize(18)
    local  title4 = CCMenuItemFont:create( "Orientation" )
    title4:setEnabled(false)
    CCMenuItemFont:setFontName( "Marker Felt" )
    CCMenuItemFont:setFontSize(34)
    local item4 = CCMenuItemToggle:create(CCMenuItemFont:create( "Off" ))
    item4:registerScriptTapHandler(menuCallback)

    item4:getSubItems():addObject( CCMenuItemFont:create( "33%" ) )
    item4:getSubItems():addObject( CCMenuItemFont:create( "66%" ) )
    item4:getSubItems():addObject( CCMenuItemFont:create( "100%" ) )

    -- you can change the one of the items by doing this
    item4:setSelectedIndex( 2 )

    CCMenuItemFont:setFontName( "Marker Felt" )
    CCMenuItemFont:setFontSize( 34 )

    local label = CCLabelBMFont:create( "go back", "fonts/bitmapFontTest3.fnt" )
    local  back = CCMenuItemLabel:create(label)
    back:registerScriptTapHandler(backCallback)

    local menu = CCMenu:create()

    menu:addChild(title1)
    menu:addChild(title2)
    menu:addChild(item1 )
    menu:addChild(item2 )
    menu:addChild(title3)
    menu:addChild(title4)
    menu:addChild(item3 )
    menu:addChild(item4 )
    menu:addChild(back  )

    -- FIXME:tolua++ doesn't support valist argument.
    -- menu:alignItemsInColumns(2, 2, 2, 2, 1, NULL)

    ret:addChild( menu )

    local s = CCDirector:sharedDirector():getWinSize()
    menu:setPosition(ccp(s.width/2, s.height/2))
    return ret
end

local function MenuLayerPriorityTest()
    local ret = CCLayer:create()
    local m_bPriority = false
    -- Testing empty menu
    local m_pMenu1 = CCMenu:create()
    local m_pMenu2 = CCMenu:create()

    local function menuCallback(tag, pSender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(0)
    end

    local function enableMenuCallback()
        m_pMenu1:setEnabled(true)
    end

    local function disableMenuCallback(tag, pSender)
        m_pMenu1:setEnabled(false)
        local wait = CCDelayTime:create(5)
        local enable = CCCallFunc:create(enableMenuCallback)
        local arr = CCArray:create()
        arr:addObject(wait)
        arr:addObject(enable)
        local  seq = CCSequence:create(arr)
        m_pMenu1:runAction(seq)
    end

    local function togglePriorityCallback(tag, pSender)
        if m_bPriority then
            m_pMenu2:setHandlerPriority(kCCMenuHandlerPriority + 20)
            m_bPriority = false
        else
            m_pMenu2:setHandlerPriority(kCCMenuHandlerPriority - 20)
            m_bPriority = true
        end
    end

    -- Menu 1
    CCMenuItemFont:setFontName("Marker Felt")
    CCMenuItemFont:setFontSize(18)
    local item1 = CCMenuItemFont:create("Return to Main Menu")
    item1:registerScriptTapHandler(menuCallback)
    local item2 = CCMenuItemFont:create("Disable menu for 5 seconds")
    item2:registerScriptTapHandler(disableMenuCallback)

    m_pMenu1:addChild(item1)
    m_pMenu1:addChild(item2)

    m_pMenu1:alignItemsVerticallyWithPadding(2)

    ret:addChild(m_pMenu1)

    -- Menu 2
    m_bPriority = true
    CCMenuItemFont:setFontSize(48)
    item1 = CCMenuItemFont:create("Toggle priority")
    item2:registerScriptTapHandler(togglePriorityCallback)
    item1:setColor(ccc3(0,0,255))
    m_pMenu2:addChild(item1)
    ret:addChild(m_pMenu2)
    return ret
end


-- BugsTest
local function BugsTest()
    local ret = CCLayer:create()
    local function issue1410MenuCallback(tag, pSender)
        local menu = tolua.cast(pSender:getParent(), "CCMenu")
        menu:setTouchEnabled(false)
        menu:setTouchEnabled(true)
        cclog("NO CRASHES")
    end

    local function issue1410v2MenuCallback(tag, pSender)
        local menu = tolua.cast(pSender:getParent(), "CCMenu")
        menu:setTouchEnabled(true)
        menu:setTouchEnabled(false)
        cclog("NO CRASHES. AND MENU SHOULD STOP WORKING")
    end

    local function backMenuCallback(tag, pSender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(0)
    end


    local issue1410 = CCMenuItemFont:create("Issue 1410")
    issue1410:registerScriptTapHandler(issue1410MenuCallback)
    local issue1410_2 = CCMenuItemFont:create("Issue 1410 #2")
    issue1410_2:registerScriptTapHandler(issue1410v2MenuCallback)
    local back = CCMenuItemFont:create("Back")
    back:registerScriptTapHandler(backMenuCallback)

    local menu = CCMenu:create()
    menu:addChild(issue1410)
    menu:addChild(issue1410_2)
    menu:addChild(back)
    ret:addChild(menu)
    menu:alignItemsVertically()

    local s = CCDirector:sharedDirector():getWinSize()
    menu:setPosition(ccp(s.width/2, s.height/2))
    return ret
end


local function RemoveMenuItemWhenMove()
    local ret = CCLayer:create()
    local s = CCDirector:sharedDirector():getWinSize()

    local  label = CCLabelTTF:create("click item and move, should not crash", "Arial", 20)
    label:setPosition(ccp(s.width/2, s.height - 30))
    ret:addChild(label)

    local item = CCMenuItemFont:create("item 1")
    item:retain()

    local back = CCMenuItemFont:create("go back")
    local function goBack(tag, pSender)
        tolua.cast(ret:getParent(), "CCLayerMultiplex"):switchTo(0)
    end

    back:registerScriptTapHandler(goBack)

    local menu = CCMenu:create()
    menu:addChild(item)
    menu:addChild(back)

    ret:addChild(menu)
    menu:alignItemsVertically()

    menu:setPosition(ccp(s.width/2, s.height/2))

    ret:setTouchEnabled(true)

    local function onNodeEvent(event)
        if event == "enter" then
            CCDirector:sharedDirector():getTouchDispatcher():addTargetedDelegate(ret, -129, false)
        elseif event == "exit" then
            item:release()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            return true
        elseif  eventType == "moved" then
            if item ~= nil then
                item:removeFromParentAndCleanup(true)
                item:release()
                item = nil
            end
        end
    end

    ret:registerScriptTouchHandler(onTouchEvent)
    return ret
end

function MenuTestMain()
    cclog("MenuTestMain")
    local scene = CCScene:create()

    local  pLayer1 = MenuLayerMainMenu()
    local  pLayer2 = MenuLayer2()

    local  pLayer3 = MenuLayer3()
    local  pLayer4 = MenuLayer4()
    local  pLayer5 = MenuLayerPriorityTest()
    local  pLayer6 = BugsTest()
    local  pLayer7 = RemoveMenuItemWhenMove()


    local arr = CCArray:create()
    arr:addObject(pLayer1)
    arr:addObject(pLayer2)
    arr:addObject(pLayer3)
    arr:addObject(pLayer4)
    arr:addObject(pLayer5)
    arr:addObject(pLayer6)
    arr:addObject(pLayer7)

    local  layer = CCLayerMultiplex:createWithArray(arr)

    scene:addChild(layer, 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
