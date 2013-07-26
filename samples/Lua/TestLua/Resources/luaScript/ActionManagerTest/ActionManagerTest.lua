local    kTagNode = 0
local    kTagGrossini = 1
local    kTagSequence = 2
local scheduler = CCDirector:getInstance():getScheduler()
--------------------------------------------------------------------
--
-- Test1
--
--------------------------------------------------------------------

local function CrashTest()
    local ret = createTestLayer("Test 1. Should not crash")

    local  child = CCSprite:create(s_pPathGrossini)
    child:setPosition( VisibleRect:center() )
    ret:addChild(child, 1)

    --Sum of all action's duration is 1.5 second.
    child:runAction(CCRotateBy:create(1.5, 90))
    local arr = CCArray:create()
    arr:addObject(CCDelayTime:create(1.4))
    arr:addObject(CCFadeOut:create(1.1))
    child:runAction(CCSequence:create(arr))
    
    arr = CCArray:create()
    arr:addObject(CCDelayTime:create(1.4))

    local function removeThis()
        ret:getParent():removeChild(ret, true)
        Helper.nextAction()
    end
    local callfunc = CCCallFunc:create(removeThis)
    arr:addObject(callfunc)
    --After 1.5 second, self will be removed.
    ret:runAction( CCSequence:create(arr))
    return ret
end


--------------------------------------------------------------------
--
-- LogicTest
--
--------------------------------------------------------------------
local function LogicTest()
    local ret = createTestLayer("Logic test")
    local  grossini = CCSprite:create(s_pPathGrossini)
    ret:addChild(grossini, 0, 2)
    grossini:setPosition(VisibleRect:center())

    local arr = CCArray:create()
    arr:addObject(CCMoveBy:create(1, CCPoint(150,0)))

    local function bugMe(node)
        node:stopAllActions() --After this stop next action not working, if remove this stop everything is working
        node:runAction(CCScaleTo:create(2, 2))
    end

    local callfunc = CCCallFunc:create(bugMe)
    arr:addObject(callfunc)
    grossini:runAction( CCSequence:create(arr));
    return ret
end

--------------------------------------------------------------------
--
-- PauseTest
--
--------------------------------------------------------------------

local function PauseTest()
    local ret = createTestLayer("Pause Test")
    local schedulerEntry = nil
    local function unpause(dt)
        scheduler:unscheduleScriptEntry(schedulerEntry)
        schedulerEntry = nil
        local  node = ret:getChildByTag( kTagGrossini )
        local  pDirector = CCDirector:getInstance()
        pDirector:getActionManager():resumeTarget(node)
    end

    local function onNodeEvent(event)
        if event == "enter" then
            local  l = CCLabelTTF:create("After 3 seconds grossini should move", "Thonburi", 16)
            ret:addChild(l)
            l:setPosition( CCPoint(VisibleRect:center().x, VisibleRect:top().y-75) )
            
            local  grossini = CCSprite:create(s_pPathGrossini)
            ret:addChild(grossini, 0, kTagGrossini)
            grossini:setPosition(VisibleRect:center() )
            
            local  action = CCMoveBy:create(1, CCPoint(150,0))

            local  pDirector = CCDirector:getInstance()
            pDirector:getActionManager():addAction(action, grossini, true)

            schedulerEntry = scheduler:scheduleScriptFunc(unpause, 3.0, false)

        elseif event == "exit" then
            if schedulerEntry ~= nil then
                scheduler:unscheduleScriptEntry(schedulerEntry)
            end
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end

--------------------------------------------------------------------
--
-- RemoveTest
--
--------------------------------------------------------------------
local function RemoveTest()
    local ret = createTestLayer("Remove Test")
    local  l = CCLabelTTF:create("Should not crash", "Thonburi", 16)
    ret:addChild(l)
    l:setPosition( CCPoint(VisibleRect:center().x, VisibleRect:top().y - 75) )

    local  pMove = CCMoveBy:create(2, CCPoint(200, 0))
    local function stopAction()
        local  pSprite = ret:getChildByTag(kTagGrossini)
        pSprite:stopActionByTag(kTagSequence)
    end

    local callfunc = CCCallFunc:create(stopAction)
    local arr = CCArray:create()
    arr:addObject(pMove)
    arr:addObject(callfunc)
    local  pSequence = CCSequence:create(arr)
    pSequence:setTag(kTagSequence)

    local  pChild = CCSprite:create(s_pPathGrossini)
    pChild:setPosition( VisibleRect:center() )

    ret:addChild(pChild, 1, kTagGrossini)
    pChild:runAction(pSequence)
    return ret
end


--------------------------------------------------------------------
--
-- ResumeTest
--
--------------------------------------------------------------------
local function ResumeTest()
    local ret = createTestLayer("Resume Test")

    local schedulerEntry = nil
    local function resumeGrossini(time)
        scheduler:unscheduleScriptEntry(schedulerEntry)
        schedulerEntry = nil
        local  pGrossini = ret:getChildByTag(kTagGrossini)
        local  pDirector = CCDirector:getInstance()
        pDirector:getActionManager():resumeTarget(pGrossini)
    end


    local function onNodeEvent(event)
        if event == "enter" then
            local  l = CCLabelTTF:create("Grossini only rotate/scale in 3 seconds", "Thonburi", 16)
            ret:addChild(l)
            l:setPosition( CCPoint(VisibleRect:center().x, VisibleRect:top().y - 75))

            local  pGrossini = CCSprite:create(s_pPathGrossini)
            ret:addChild(pGrossini, 0, kTagGrossini)
            pGrossini:setPosition(VisibleRect:center())

            pGrossini:runAction(CCScaleBy:create(2, 2))

            local  pDirector = CCDirector:getInstance()
            pDirector:getActionManager():pauseTarget(pGrossini)
            pGrossini:runAction(CCRotateBy:create(2, 360))

            schedulerEntry = scheduler:scheduleScriptFunc(resumeGrossini, 3.0, false)
        elseif event == "exit" then
            if schedulerEntry ~= nil then
                scheduler:unscheduleScriptEntry(schedulerEntry)
            end
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end


function ActionManagerTestMain()
    cclog("ActionManagerTestMain")
    Helper.index = 1
    CCDirector:getInstance():setDepthTest(true)
    local scene = CCScene:create()

    Helper.createFunctionTable = {
        CrashTest,
        LogicTest,
        PauseTest,
        RemoveTest,
        ResumeTest
    }
    scene:addChild(CrashTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end

