local    kTagNode = 0
local    kTagGrossini = 1
local    kTagSequence = 2

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
        m_pParent:removeChild(this, true)
        Helper.nextAction()
    end

    arr:addObject(CCCallFunc:create(removeThis))
    --After 1.5 second, self will be removed.
    ret:runAction( CCSequence:create(arr))
end


--------------------------------------------------------------------
--
-- Test2
--
--------------------------------------------------------------------
local function onEnter()

    ActionManagerTest:onEnter()

    local  grossini = CCSprite:create(s_pPathGrossini)
    addChild(grossini, 0, 2)
    grossini:setPosition(VisibleRect:center())

    grossini:runAction( CCSequence:create( 
                                                CCMoveBy:create(1, ccp(150,0)),
                                                CCCallFuncN:create(this, callfuncN_selector(LogicTest:bugMe)),
                                                NULL) 
                        )
end

local function bugMe(CCNode* node)

    node:stopAllActions() --After this stop next action not working, if remove this stop everything is working
    node:runAction(CCScaleTo:create(2, 2))
end

local function title()

    return "Logic test" 
end

--------------------------------------------------------------------
--
-- PauseTest
--
--------------------------------------------------------------------

local function onEnter()

    --
    -- This test MUST be done in 'onEnter' and not on 'init'
    -- otherwise the paused action will be resumed at 'onEnter' time
    --
    ActionManagerTest:onEnter()
    

    local  l = CCLabelTTF:create("After 5 seconds grossini should move", "Thonburi", 16)
    addChild(l)
    l:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y-75) )
    
    
    --
    -- Also, this test MUST be done, after [super onEnter]
    --
    local  grossini = CCSprite:create(s_pPathGrossini)
    addChild(grossini, 0, kTagGrossini)
    grossini:setPosition(VisibleRect:center() )
    
    local  action = CCMoveBy:create(1, ccp(150,0))

    local  pDirector = CCDirector:sharedDirector()
    pDirector:getActionManager():addAction(action, grossini, true)

    schedule( schedule_selector(PauseTest:unpause), 3) 
end

local function unpause(float dt)

    unschedule( schedule_selector(PauseTest:unpause) )
    local  node = getChildByTag( kTagGrossini )
    local  pDirector = CCDirector:sharedDirector()
    pDirector:getActionManager():resumeTarget(node)
end

local function title()

    return "Pause Test"
end

--------------------------------------------------------------------
--
-- RemoveTest
--
--------------------------------------------------------------------
local function onEnter()

    ActionManagerTest:onEnter()

    local  l = CCLabelTTF:create("Should not crash", "Thonburi", 16)
    addChild(l)
    l:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 75) )

    local  pMove = CCMoveBy:create(2, ccp(200, 0))
    local  pCallback = CCCallFunc:create(this, callfunc_selector(RemoveTest:stopAction))
    local  pSequence = CCSequence:create(pMove, pCallback, NULL)
    pSequence:setTag(kTagSequence)

    local  pChild = CCSprite:create(s_pPathGrossini)
    pChild:setPosition( VisibleRect:center() )

    addChild(pChild, 1, kTagGrossini)
    pChild:runAction(pSequence)
end

local function stopAction()

    local  pSprite = getChildByTag(kTagGrossini)
    pSprite:stopActionByTag(kTagSequence)
end

local function title()

    return "Remove Test"
end

--------------------------------------------------------------------
--
-- ResumeTest
--
--------------------------------------------------------------------
local function title()

    return "Resume Test"
end

local function onEnter()

    ActionManagerTest:onEnter()

    local  l = CCLabelTTF:create("Grossini only rotate/scale in 3 seconds", "Thonburi", 16)
    addChild(l)
    l:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 75))

    local  pGrossini = CCSprite:create(s_pPathGrossini)
    addChild(pGrossini, 0, kTagGrossini)
    pGrossini:setPosition(VisibleRect:center())

    pGrossini:runAction(CCScaleBy:create(2, 2))

    local  pDirector = CCDirector:sharedDirector()
    pDirector:getActionManager():pauseTarget(pGrossini)
    pGrossini:runAction(CCRotateBy:create(2, 360))

    this:schedule(schedule_selector(ResumeTest:resumeGrossini), 3.0)
end

local function resumeGrossini(float time)

    this:unschedule(schedule_selector(ResumeTest:resumeGrossini))

    local  pGrossini = getChildByTag(kTagGrossini)
    local  pDirector = CCDirector:sharedDirector()
    pDirector:getActionManager():resumeTarget(pGrossini)
end

function ActionManagerTestMain()
    cclog("ActionManagerTestMain")
    Helper.index = 1
    CCDirector:sharedDirector():setDepthTest(true)
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

