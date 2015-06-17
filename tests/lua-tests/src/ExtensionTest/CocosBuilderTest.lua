HelloCocosBuilderLayer = HelloCocosBuilderLayer or {}
ccb["HelloCocosBuilderLayer"] = HelloCocosBuilderLayer

TestMenusLayer = TestMenusLayer or {}
ccb["TestMenusLayer"] = TestMenusLayer

TestButtonsLayer  = TestButtonsLayer or {}
ccb["TestButtonsLayer"] = TestButtonsLayer

TestHeaderLayer = TestHeaderLayer or {}
ccb["TestHeaderLayer"] = TestHeaderLayer

TestSpritesLayer = TestSpritesLayer or {}
ccb["TestSpritesLayer"] = TestSpritesLayer

TestParticleSystemsLayer = TestParticleSystemsLayer or {}
ccb["TestParticleSystemsLayer"] = TestParticleSystemsLayer

TestAnimationsLayer = TestAnimationsLayer or {}
ccb["TestAnimationsLayer"] = TestAnimationsLayer

TestTimelineLayer = TestTimelineLayer or {}
ccb["TestTimelineLayer"] = TestTimelineLayer

TestScrollViewsLayer = TestScrollViewsLayer or {}
ccb["TestScrollViewsLayer"] = TestScrollViewsLayer

local function onMenuItemAClicked()
    if nil ~= TestMenusLayer["mMenuItemStatusLabelBMFont"] then
        local labelBmFt = TestMenusLayer["mMenuItemStatusLabelBMFont"]
        if nil ~= labelBmFt then
            labelBmFt:setString("Menu Item A clicked.");
        end
    end
end

local function onMenuItemBClicked()
    if nil ~= TestMenusLayer["mMenuItemStatusLabelBMFont"] then
        local labelBmFt = TestMenusLayer["mMenuItemStatusLabelBMFont"]
        if nil ~= labelBmFt then
            labelBmFt:setString("Menu Item B clicked.");
        end
    end
end

local function pressedC( ... )
    if nil ~= TestMenusLayer["mMenuItemStatusLabelBMFont"] then
        local labelBmFt = TestMenusLayer["mMenuItemStatusLabelBMFont"]
        if nil ~= labelBmFt then
            labelBmFt:setString("Menu Item C clicked.");
        end
    end
end
local function onMenuTestClicked()
    cclog("CCBMenuTest");
    local scene = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestMenus.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestMenus.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end
end

TestMenusLayer["onMenuItemAClicked"] = onMenuItemAClicked
TestMenusLayer["onMenuItemBClicked"] = onMenuItemBClicked
TestMenusLayer["pressedC:"] = pressedC

local function onBackClicked()
    cc.Director:getInstance():popScene();
end

TestHeaderLayer["onBackClicked"] = onBackClicked

local function onSpriteTestClicked()
    cclog("CCBSpriteTest");
    local scene  = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestSprites.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestSprites.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end 
end

local function onButtonTestClicked()
    cclog("CCBButtionTest");
    local scene  = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestButtons.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestButtons.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end 
end

local function onCCControlButtonClicked(sender,controlEvent)
    local labelTTF = TestButtonsLayer["mCCControlEventLabel"]

    if nil == labelTTF then
        return
    end
    
    if controlEvent == cc.CONTROL_EVENTTYPE_TOUCH_DOWN  then      
        labelTTF:setString("Touch Down.")        
    elseif controlEvent == cc.CONTROL_EVENTTYPE_DRAG_INSIDE then
        labelTTF:setString("Touch Drag Inside.") 
    elseif controlEvent == cc.CONTROL_EVENTTYPE_DRAG_OUTSIDE then
        labelTTF:setString("Touch Drag Outside.") 
    elseif controlEvent == cc.CONTROL_EVENTTYPE_DRAG_ENTER then
        labelTTF:setString("Touch Drag Enter.") 
    elseif controlEvent == cc.CONTROL_EVENTTYPE_DRAG_EXIT then
        labelTTF:setString("Touch Drag Exit.") 
    elseif controlEvent == cc.CONTROL_EVENTTYPE_TOUCH_UP_INSIDE then
        labelTTF:setString("Touch Up Inside.") 
    elseif controlEvent == cc.CONTROL_EVENTTYPE_TOUCH_UP_OUTSIDE then
        labelTTF:setString("Touch Up Outside.") 
    elseif controlEvent == cc.CONTROL_EVENTTYPE_TOUCH_CANCEL then
        labelTTF:setString("Touch Cancel.") 
    elseif controlEvent == cc.CONTROL_EVENT_VALUECHANGED  then
        labelTTF:setString("Value Changed.") 
    end
end

TestButtonsLayer["onCCControlButtonClicked"] = onCCControlButtonClicked



local function onAnimationsTestClicked()
    cclog("CCBAnimationsTestTest");
    local scene  = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestAnimations.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestAnimations.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end 
end

local function onParticleSystemTestClicked()
    cclog("CCBParticleSystemTest");
    local scene  = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestParticleSystems.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestParticleSystems.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end 
end

local function onCCControlButtonIdleClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = TestAnimationsLayer["mAnimationManager"]
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Idle", 0.3)
        end
    end
end

local function onCCControlButtonWaveClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = TestAnimationsLayer["mAnimationManager"]
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Wave", 0.3)
        end
    end
end

local function onCCControlButtonJumpClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = TestAnimationsLayer["mAnimationManager"]
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Jump", 0.3)
        end
    end
end

local function onCCControlButtonFunkyClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = TestAnimationsLayer["mAnimationManager"]
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Funky", 0.3)
        end
    end
end

TestAnimationsLayer["onCCControlButtonIdleClicked"] = onCCControlButtonIdleClicked
TestAnimationsLayer["onCCControlButtonWaveClicked"] = onCCControlButtonWaveClicked
TestAnimationsLayer["onCCControlButtonJumpClicked"] = onCCControlButtonJumpClicked
TestAnimationsLayer["onCCControlButtonFunkyClicked"] = onCCControlButtonFunkyClicked


local function onScrollViewTestClicked()
    local scene  = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestScrollViews.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestScrollViews.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end
end

local function onTimelineCallbackSoundClicked()
    cclog("CCBTimelineTest");
    local scene  = cc.Scene:create()
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestTimelineCallback.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = HelloCocosBuilderLayer["mTestTitleLabelTTF"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestTimelineCallback.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():pushScene(cc.TransitionFade:create(0.5, scene, cc.c3b(0,0,0))); 
    end 
end

function onCallback1()
    if nil ~= TestTimelineLayer["helloLabel"] then
        local ccLabelTTF = TestTimelineLayer["helloLabel"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:runAction(cc.RotateBy:create(1, 360))
            ccLabelTTF:setString("Callback 1");
        end
    end
end

function onCallback2()
    if nil ~= TestTimelineLayer["helloLabel"] then
        local ccLabelTTF = TestTimelineLayer["helloLabel"]
        if nil ~= ccLabelTTF then
            ccLabelTTF:runAction(cc.RotateBy:create(2, 360))
            ccLabelTTF:setString("Callback 2");
        end
    end
end
TestTimelineLayer["onCallback1"] = onCallback1
TestTimelineLayer["onCallback2"] = onCallback2

HelloCocosBuilderLayer["onMenuTestClicked"] = onMenuTestClicked
HelloCocosBuilderLayer["onSpriteTestClicked"] = onSpriteTestClicked
HelloCocosBuilderLayer["onButtonTestClicked"] = onButtonTestClicked
HelloCocosBuilderLayer["onAnimationsTestClicked"] = onAnimationsTestClicked
HelloCocosBuilderLayer["onParticleSystemTestClicked"] = onParticleSystemTestClicked
HelloCocosBuilderLayer["onScrollViewTestClicked"] = onScrollViewTestClicked
HelloCocosBuilderLayer["onTimelineCallbackSoundClicked"] = onTimelineCallbackSoundClicked



local function HelloCCBTestMainLayer()
    print(type(cc.Scene))
    local  proxy = cc.CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/HelloCocosBuilder.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = node
    return layer
end

function runCocosBuilder()
    cclog("HelloCCBSceneTestMain")
    local scene = cc.Scene:create()
    scene:addChild(HelloCCBTestMainLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
