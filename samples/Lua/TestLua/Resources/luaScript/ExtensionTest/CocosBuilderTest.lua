
require "CCBReaderLoad"

HelloCocosBuilderLayer = HelloCocosBuilderLayer or {}
ccb["HelloCocosBuilderLayer"] = HelloCocosBuilderLayer

HelloCocosBuilderLayerOwner = HelloCocosBuilderLayerOwner or {}
ccb["HelloCocosBuilderLayerOwner"] = HelloCocosBuilderLayerOwner

TestMenusLayer = TestMenusLayer or {}
ccb["TestMenusLayer"] = TestMenusLayer

TestMenusLayerOwner = TestMenusLayerOwner or {}
ccb["TestMenusLayerOwner"] = TestMenusLayerOwner

TestButtonsLayer  = TestButtonsLayer or {}
ccb["TestButtonsLayer"] = TestButtonsLayer

TestButtonsLayerOwner  = TestButtonsLayerOwner or {}
ccb["TestButtonsLayerOwner"] = TestButtonsLayerOwner

TestHeaderLayer = TestHeaderLayer or {}
ccb["TestHeaderLayer"] = TestHeaderLayer

TestHeaderLayerOwner = TestHeaderLayerOwner or {}
ccb["TestHeaderLayerOwner"] = TestHeaderLayerOwner

TestSpritesLayer = TestSpritesLayer or {}
ccb["TestSpritesLayer"] = TestSpritesLayer

TestSpritesLayerOwner = TestSpritesLayerOwner or {}
ccb["TestSpritesLayerOwner"] = TestSpritesLayerOwner

TestParticleSystemsLayer = TestParticleSystemsLayer or {}
ccb["TestParticleSystemsLayer"] = TestParticleSystemsLayer

TestParticleSystemsOwner = TestParticleSystemsOwner or {}
ccb["TestParticleSystemsLayerOwner"] = TestParticleSystemsLayerOwner

TestAnimationsLayer = TestAnimationsLayer or {}
ccb["TestAnimationsLayer"] = TestAnimationsLayer

TestAnimationsLayerOwner = TestAnimationsLayerOwner or {}
ccb["TestAnimationsLayerOwner"] = TestAnimationsLayerOwner

TestTimelineLayer = TestTimelineLayer or {}
ccb["TestTimelineLayer"] = TestTimelineLayer

TestTimelineLayerOwner = TestTimelineLayerOwner or {}
ccb["TestTimelineLayerOwner"] = TestTimelineLayerOwner

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
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestMenus.ccbi",proxy,true,"TestMenusLayerOwner")
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= TestMenusLayerOwner["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(TestMenusLayerOwner["mTestTitleLabelTTF"],"CCLabelTTF")
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
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestSprites.ccbi",proxy,true,"TestSpritesLayerOwner")
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= TestSpritesLayerOwner["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(TestSpritesLayerOwner["mTestTitleLabelTTF"],"CCLabelTTF")
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
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestButtons.ccbi",proxy,true,"TestButtonsLayerOwner")
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= TestButtonsLayerOwner["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(TestButtonsLayerOwner["mTestTitleLabelTTF"],"CCLabelTTF")
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

local function onCCControlButtonClicked()
    --print("cc")
end

TestButtonsLayer["onCCControlButtonClicked"] = onCCControlButtonClicked



local function onAnimationsTestClicked()
    cclog("CCBAnimationsTestTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestAnimations.ccbi",proxy,true,"TestAnimationsLayerOwner")
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= TestAnimationsLayerOwner["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(TestAnimationsLayerOwner["mTestTitleLabelTTF"],"CCLabelTTF")
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
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestParticleSystems.ccbi",proxy,true,"TestParticleSystemsLayer")
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= TestParticleSystemsLayer["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(TestParticleSystemsLayer["mTestTitleLabelTTF"],"CCLabelTTF")
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
    print("onScrollViewTestClicked")
end

local function onTimelineCallbackSoundClicked()
    cclog("CCBTimelineTest");
    local scene  = CCScene:create()
    local  proxy = CCBProxy:create()
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/ccb/TestTimelineCallback.ccbi",proxy,true,"TestTimelineLayerOwner")
    local  layer = tolua.cast(node,"CCLayer")
    if nil ~= TestTimelineLayerOwner["mTestTitleLabelTTF"] then
        local ccLabelTTF = tolua.cast(TestTimelineLayerOwner["mTestTitleLabelTTF"],"CCLabelTTF")
        if nil ~= ccLabelTTF then
            ccLabelTTF:setString("ccb/ccb/TestTimelineCallback.ccbi")
        end
    end
    if nil ~= scene then
        scene:addChild(layer)
        scene:addChild(CreateBackMenuItem())
        CCDirector:sharedDirector():pushScene(CCTransitionFade:create(0.5, scene, ccc3(0,0,0))); 
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
    local  node  = CCBReaderLoad("cocosbuilderRes/ccb/HelloCocosBuilder.ccbi",proxy,true,"HelloCocosBuilderLayerOwner")
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
