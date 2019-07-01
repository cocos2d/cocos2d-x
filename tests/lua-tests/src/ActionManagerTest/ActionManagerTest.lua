local    kTagNode = 0
local    kTagGrossini = 1
local    kTagSequence = 2
local    scheduler = cc.Director:getInstance():getScheduler()
--------------------------------------------------------------------
--
-- Test1
--
--------------------------------------------------------------------

local function CrashTest()
    local ret = createTestLayer("Test 1. Should not crash")

    local  child = cc.Sprite:create(s_pPathGrossini)
    child:setPosition( 200,200 )
    ret:addChild(child, 1)

    --Sum of all action's duration is 1.5 second.
    child:runAction(cc.RotateBy:create(1.5, 90))
    child:runAction(cc.Sequence:create(cc.DelayTime:create(1.4),cc.FadeOut:create(1.1)))
    
    local function removeThis()
        ret:getParent():removeChild(ret, true)
        Helper.nextAction()
    end

    --After 1.5 second, self will be removed.
    ret:runAction( cc.Sequence:create(cc.DelayTime:create(1.4),cc.CallFunc:create(removeThis)))
    return ret
end


--------------------------------------------------------------------
--
-- LogicTest
--
--------------------------------------------------------------------
local function LogicTest()
    local ret = createTestLayer("Logic test")
    local  grossini = cc.Sprite:create(s_pPathGrossini)
    ret:addChild(grossini, 0, 2)
    grossini:setPosition(200,200)
    local function bugMe(node)
        node:stopAllActions() --After this stop next action not working, if remove this stop everything is working
        node:runAction(cc.ScaleTo:create(2, 2))
    end
    grossini:runAction( cc.Sequence:create(cc.MoveBy:create(1, cc.p(150,0)) ,cc.CallFunc:create(bugMe)))
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
        local  pDirector = cc.Director:getInstance()
        pDirector:getActionManager():resumeTarget(node)
    end

    local function onNodeEvent(event)
        if event == "enter" then
            local  s = cc.Director:getInstance():getWinSize()
            local  l = cc.Label:createWithTTF("After 3 seconds grossini should move", "fonts/Thonburi.ttf", 16)
            ret:addChild(l)
            l:setAnchorPoint(cc.p(0.5, 0.5))
            l:setPosition( cc.p(s.width / 2, 245) )
            
            local  grossini = cc.Sprite:create(s_pPathGrossini)
            ret:addChild(grossini, 0, kTagGrossini)
            grossini:setPosition(cc.p(200,200))
            
            local  action = cc.MoveBy:create(1, cc.p(150,0))

            local  pDirector = cc.Director:getInstance()
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
    local  l = cc.Label:createWithTTF("Should not crash", "fonts/Thonburi.ttf", 16)
    local  s = cc.Director:getInstance():getWinSize()
    ret:addChild(l)
    l:setAnchorPoint(cc.p(0.5, 0.5))
    l:setPosition( cc.p(s.width / 2, 245))

    local  pMove = cc.MoveBy:create(2, cc.p(200, 0))
    local function stopAction()
        local  pSprite = ret:getChildByTag(kTagGrossini)
        pSprite:stopActionByTag(kTagSequence)
    end

    local callfunc = cc.CallFunc:create(stopAction)
    local  pSequence = cc.Sequence:create(pMove,callfunc)
    pSequence:setTag(kTagSequence)

    local  pChild = cc.Sprite:create(s_pPathGrossini)
    pChild:setPosition( 200, 200 )

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
        local  pDirector = cc.Director:getInstance()
        pDirector:getActionManager():resumeTarget(pGrossini)
    end


    local function onNodeEvent(event)
        if event == "enter" then
            local  l = cc.Label:createWithTTF("Grossini only rotate/scale in 3 seconds", "fonts/Thonburi.ttf", 16)
            ret:addChild(l)
            local  s = cc.Director:getInstance():getWinSize()
            l:setAnchorPoint(cc.p(0.5, 0.5))
            l:setPosition( s.width / 2, 245)

            local  pGrossini = cc.Sprite:create(s_pPathGrossini)
            ret:addChild(pGrossini, 0, kTagGrossini)
            pGrossini:setPosition(200,200)

            pGrossini:runAction(cc.ScaleBy:create(2, 2))

            local  pDirector = cc.Director:getInstance()
            pDirector:getActionManager():pauseTarget(pGrossini)
            pGrossini:runAction(cc.RotateBy:create(2, 360))

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
    cc.Director:getInstance():getRenderer():setDepthTest(true)
    local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        CrashTest,
        LogicTest,
        PauseTest,
        RemoveTest,
        ResumeTest
    }
    Helper.index = 1
    
    scene:addChild(CrashTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end

