
require "CCBReaderLoad"

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

TestScrollViewLayer = TestScrollViewLayer or {}
ccb["TestScrollViewLayer"] = TestScrollViewLayer

TestTimelineLayer = TestTimelineLayer or {}
ccb["TestTimelineLayer"] = TestTimelineLayer

local function onMenuItemAClicked()
    if nil ~= TestMenusLayer["mMenuItemStatusLabelBMFont"] then
        local labelBmFt = tolua.cast(TestMenusLayer["mMenuItemStatusLabelBMFont"],"CCLabelBMFont")
        if nil ~= labelBmFt then
            labelBmFt:setString("Menu Item A clicked.");
        end
    end
end

local function onMenuItemBClicked()
    if nil ~= TestMenusLayer["mMenuItemStatusLabelBMFont"] then
        local labelBmFt = tolua.cast(TestMenusLayer["mMenuItemStatusLabelBMFont"],"CCLabelBMFont")
        if nil ~= labelBmFt then
            labelBmFt:setString("Menu Item B clicked.");
        end
    end
end

local function pressedC( ... )
    if nil ~= TestMenusLayer["mMenuItemStatusLabelBMFont"] then
        local labelBmFt = tolua.cast(TestMenusLayer["mMenuItemStatusLabelBMFont"],"CCLabelBMFont")
        if nil ~= labelBmFt then
            labelBmFt:setString("Menu Item C clicked.");
        end
    end
end
local function onMenuTestClicked()
    cclog("CCBMenuTest");
    local scene = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestMenus.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestMenus.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))); 
    end
end

TestMenusLayer["onMenuItemAClicked"] = onMenuItemAClicked
TestMenusLayer["onMenuItemBClicked"] = onMenuItemBClicked
TestMenusLayer["pressedC:"] = pressedC

local function onBackClicked()
    CCDirector:sharedDirector():popScene();
end

TestHeaderLayer["onBackClicked"] = onBackClicked

local function onSpriteTestClicked()
    cclog("CCBSpriteTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestSprites.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestSprites.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))); 
    end 
end

local function onButtonTestClicked()
    cclog("CCBButtionTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestButtons.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestButtons.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))); 
    end 
end

local function onCCControlButtonClicked(eventName,control,controlEvent)
    local labelTTF = tolua.cast(TestButtonsLayer["mCCControlEventLabel"],"CCLabelBMFont")

    if nil == labelTTF then
        return
    end

    if controlEvent == CCControlEventTouchDown  then      
        labelTTF:setString("Touch Down.")        
    elseif controlEvent == CCControlEventTouchDragInside then
        labelTTF:setString("Touch Drag Inside.") 
    elseif controlEvent == CCControlEventTouchDragOutside then
        labelTTF:setString("Touch Drag Outside.") 
    elseif controlEvent == CCControlEventTouchDragEnter then
        labelTTF:setString("Touch Drag Enter.") 
    elseif controlEvent == CCControlEventTouchDragExit then
        labelTTF:setString("Touch Drag Exit.") 
    elseif controlEvent == CCControlEventTouchUpInside then
        labelTTF:setString("Touch Up Inside.") 
    elseif controlEvent == CCControlEventTouchUpOutside then
        labelTTF:setString("Touch Up Outside.") 
    elseif controlEvent == CCControlEventTouchCancel then
        labelTTF:setString("Touch Cancel.") 
    elseif controlEvent == CCControlEventValueChanged  then
        labelTTF:setString("Value Changed.") 
    end
end

TestButtonsLayer["onCCControlButtonClicked"] = onCCControlButtonClicked



local function onAnimationsTestClicked()
    cclog("CCBAnimationsTestTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestAnimations.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestAnimations.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))); 
    end 
end

local function onParticleSystemTestClicked()
    cclog("CCBParticleSystemTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestParticleSystems.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestParticleSystems.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))); 
    end 
end

local function onCCControlButtonIdleClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = tolua.cast(TestAnimationsLayer["mAnimationManager"],"CCBAnimationManager")
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Idle", 0.3)
        end
    end
end

local function onCCControlButtonWaveClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = tolua.cast(TestAnimationsLayer["mAnimationManager"],"CCBAnimationManager")
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Wave", 0.3)
        end
    end
end

local function onCCControlButtonJumpClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = tolua.cast(TestAnimationsLayer["mAnimationManager"],"CCBAnimationManager")
        if nil ~= animationMgr then
            animationMgr:runAnimationsForSequenceNamedTweenDuration("Jump", 0.3)
        end
    end
end

local function onCCControlButtonFunkyClicked()
    if nil ~= TestAnimationsLayer["mAnimationManager"] then
        local animationMgr = tolua.cast(TestAnimationsLayer["mAnimationManager"],"CCBAnimationManager")
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
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestScrollViews.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestScrollViews.ccbi")
        end
    end

    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))) 
    end
end

local function onTimelineCallbackSoundClicked()
    cclog("CCBTimelineTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/ccb/TestTimelineCallback.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= HelloCocosBuilderLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(HelloCocosBuilderLayer["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestTimelineCallback.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))) 
    end 
end

function onCallback1()
    if nil ~= TestTimelineLayer["helloLabel"] then
        local ccLabelTTF = tolua.cast(TestTimelineLayer["helloLabel"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:runAction(CCRotateBy:create(1, 360))
            ccLabelTTF:setString("Callback 1");
        end
    end
end

function onCallback2()
    if nil ~= TestTimelineLayer["helloLabel"] then
        local ccLabelTTF = tolua.cast(TestTimelineLayer["helloLabel"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:runAction(CCRotateBy:create(2, 360))
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
    local  proxy = CCBProxy:create()
    local  node  = CCBuilderReaderLoad("cocosbuilderRes/ccb/HelloCocosBuilder.ccbi",proxy,HelloCocosBuilderLayer)
    local  layer = tolua.cast(node,"CCLayer")
    return layer
end

function runCocosBuilder()
    cclog("HelloCCBSceneTestMain")
    local scene = CCScene:create()
    scene:addChild(HelloCCBTestMainLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
