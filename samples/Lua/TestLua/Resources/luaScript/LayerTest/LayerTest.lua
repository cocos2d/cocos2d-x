local kTagLayer = 1,


--#pragma mark - Cascading support extensions

local function setEnableRecursiveCascading(node, enable)
    local  rgba = tolua.cast(node, "CCRGBAProtocol")
    if rgba ~= nil then
        rgba:setCascadeColorEnabled(enable)
        rgba:setCascadeOpacityEnabled(enable)
    end
    
    CCObject* obj
    local  children = node:getChildren()
    CCARRAY_FOREACH(children, obj)
    
        local  child = (CCNode*)obj
        setEnableRecursiveCascading(child, enable)
    end
end

-- LayerTestCascadingOpacityA
local function onEnter()

    LayerTest:onEnter()
    
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerRGBA:create()
    
    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.nt")
    
    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    this:addChild( layer1, 0, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, s.height/2))
    sister2:setPosition( ccp( s.width*2/3, s.height/2))
    label:setPosition( ccp( s.width/2, s.height/2))
    
    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCFadeTo:create(4, 0),
       CCFadeTo:create(4, 255),
       CCDelayTime:create(1),
       NULL)))
    
    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCFadeTo:create(2, 0),
       CCFadeTo:create(2, 255),
       CCFadeTo:create(2, 0),
       CCFadeTo:create(2, 255),
       CCDelayTime:create(1),
       NULL)))
    
    
    -- Enable cascading in scene
    setEnableRecursiveCascading(this, true)
end

local function title()

    return "LayerRGBA: cascading opacity"
end


--  LayerTestCascadingOpacityB
local function onEnter()

    LayerTest:onEnter()
        
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(192, 0, 0, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    
    layer1:setPosition( ccp(0, s.height/2))
    
    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.nt")
    
    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    this:addChild( layer1, 0, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))
    
    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCFadeTo:create(4, 0),
       CCFadeTo:create(4, 255),
       CCDelayTime:create(1),
       NULL)))
    
    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCFadeTo:create(2, 0),
       CCFadeTo:create(2, 255),
       CCFadeTo:create(2, 0),
       CCFadeTo:create(2, 255),
       CCDelayTime:create(1),
       NULL)))
    
    -- Enable cascading in scene
    setEnableRecursiveCascading(this, true)
end

local function title()

    return "CCLayerColor: cascading opacity"
end


-- LayerTestCascadingOpacityC
local function onEnter()

    LayerTest:onEnter()
    
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(192, 0, 0, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    layer1:setCascadeOpacityEnabled(false)
    
    layer1:setPosition( ccp(0, s.height/2))
    
    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.nt")
    
    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    this:addChild( layer1, 0, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))
    
    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCFadeTo:create(4, 0),
       CCFadeTo:create(4, 255),
       CCDelayTime:create(1),
       NULL)))
    
    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCFadeTo:create(2, 0),
       CCFadeTo:create(2, 255),
       CCFadeTo:create(2, 0),
       CCFadeTo:create(2, 255),
       CCDelayTime:create(1),
       NULL)))
end

local function title()

    return "CCLayerColor: non-cascading opacity"
end


--#pragma mark Example LayerTestCascadingColor

-- LayerTestCascadingColorA
local function onEnter()

    LayerTest:onEnter()
    
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerRGBA:create()
    
    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.nt")
    
    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    this:addChild( layer1, 0, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, s.height/2))
    sister2:setPosition( ccp( s.width*2/3, s.height/2))
    label:setPosition( ccp( s.width/2, s.height/2))
    
    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCTintTo:create(6, 255, 0, 255),
       CCTintTo:create(6, 255, 255, 255),
       CCDelayTime:create(1),
       NULL)))
    
    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCTintTo:create(2, 255, 255, 0),
       CCTintTo:create(2, 255, 255, 255),
       CCTintTo:create(2, 0, 255, 255),
       CCTintTo:create(2, 255, 255, 255),
       CCTintTo:create(2, 255, 0, 255),
       CCTintTo:create(2, 255, 255, 255),
       CCDelayTime:create(1),
       NULL)))
    
    -- Enable cascading in scene
    setEnableRecursiveCascading(this, true)
     
end

local function title()

    return "LayerRGBA: cascading color"
end


-- LayerTestCascadingColorB
local function onEnter()

    LayerTest:onEnter()
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(255, 255, 255, 255), s.width, s.height/2)
    
    layer1:setPosition( ccp(0, s.height/2))
    
    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.nt")
    
    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    this:addChild( layer1, 0, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))
    
    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCTintTo:create(6, 255, 0, 255),
       CCTintTo:create(6, 255, 255, 255),
       CCDelayTime:create(1),
       NULL)))
    
    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCTintTo:create(2, 255, 255, 0),
       CCTintTo:create(2, 255, 255, 255),
       CCTintTo:create(2, 0, 255, 255),
       CCTintTo:create(2, 255, 255, 255),
       CCTintTo:create(2, 255, 0, 255),
       CCTintTo:create(2, 255, 255, 255),
       CCDelayTime:create(1),
       NULL)))
    
    -- Enable cascading in scene
    setEnableRecursiveCascading(this, true)
end

local function title()

    return "CCLayerColor: cascading color"
end


-- LayerTestCascadingColorC
local function onEnter()

    LayerTest:onEnter()
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(255, 255, 255, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    layer1:setPosition( ccp(0, s.height/2))
    
    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.nt")
    
    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    this:addChild( layer1, 0, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))
    
    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCTintTo:create(6, 255, 0, 255),
       CCTintTo:create(6, 255, 255, 255),
       CCDelayTime:create(1),
       NULL)))
    
    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       CCTintTo:create(2, 255, 255, 0),
       CCTintTo:create(2, 255, 255, 255),
       CCTintTo:create(2, 0, 255, 255),
       CCTintTo:create(2, 255, 255, 255),
       CCTintTo:create(2, 255, 0, 255),
       CCTintTo:create(2, 255, 255, 255),
       CCDelayTime:create(1),
       NULL)))
end

local function title()

    return "CCLayerColor: non-cascading color"
end

--------------------------------------------------------------------
--
-- LayerTest1
--
--------------------------------------------------------------------
local function onEnter()

    LayerTest:onEnter()

    setTouchEnabled(true)
    
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer = CCLayerColor:create( ccc4(0xFF, 0x00, 0x00, 0x80), 200, 200) 
    
    layer:ignoreAnchorPointForPosition(false)
    layer:setPosition( ccp(s.width/2, s.height/2) )
    addChild(layer, 1, kTagLayer)
end

local function updateSize(CCPoint &touchLocation)
    
    local s = CCDirector:sharedDirector():getWinSize()
    
    local newSize = local Make( fabs(touchLocation.x - s.width/2)*2, fabs(touchLocation.y - s.height/2)*2)
    
    local  l = tolua.cast(getChildByTag(kTagLayer), "CCLayerColor")

    l:setContentSize( newSize )
end

local function ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)

    ccTouchesMoved(pTouches, pEvent)
end

local function ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)

    local touch = tolua.cast(pTouches:anyObject(), "CCTouch")
    local touchLocation = touch:getLocation()

    updateSize(touchLocation)
end

local function ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)

    ccTouchesMoved(pTouches, pEvent)
end

local function title()

    return "ColorLayer resize (tap & move)"
end

--------------------------------------------------------------------
--
-- LayerTest2
--
--------------------------------------------------------------------
local function onEnter()

    LayerTest:onEnter()

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create( ccc4(255, 255, 0, 80), 100, 300)
    layer1:setPosition(ccp(s.width/3, s.height/2))
    layer1:ignoreAnchorPointForPosition(false)
    addChild(layer1, 1)
    
    local  layer2 = CCLayerColor:create( ccc4(0, 0, 255, 255), 100, 300)
    layer2:setPosition(ccp((s.width/3)*2, s.height/2))
    layer2:ignoreAnchorPointForPosition(false)
    addChild(layer2, 1)
    
    local  actionTint = CCTintBy:create(2, -255, -127, 0)
    local  actionTintBack = actionTint:reverse()
    local  seq1 = CCSequence:create( actionTint, actionTintBack, NULL)
    layer1:runAction(seq1)

    local  actionFade = CCFadeOut:create(2.0)
    local  actionFadeBack = actionFade:reverse()
    local  seq2 = CCSequence:create(actionFade, actionFadeBack, NULL)        
    layer2:runAction(seq2)
end

local function title()

    return "ColorLayer: fade and tint"
end

--------------------------------------------------------------------
--
-- LayerTestBlend
--
--------------------------------------------------------------------

local function LayerTestBlend()

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create( ccc4(255, 255, 255, 80) )
    
    local  sister1 = CCSprite:create(s_pPathSister1)
    local  sister2 = CCSprite:create(s_pPathSister2)
    
    addChild(sister1)
    addChild(sister2)
    addChild(layer1, 100, kTagLayer)
    
    sister1:setPosition( ccp( s.width*1/3, s.height/2) )
    sister2:setPosition( ccp( s.width*2/3, s.height/2) )

    schedule( schedule_selector(LayerTestBlend:newBlend), 1.0)
end

local function newBlend(float dt)

     local layer = tolua.cast(getChildByTag(kTagLayer), "CCLayerColor")

    GLenum src
    GLenum dst

    if( layer:getBlendFunc().dst == GL_ZERO )
    
        src = GL_SRC_ALPHA
        dst = GL_ONE_MINUS_SRC_ALPHA
    end
    else
    
        src = GL_ONE_MINUS_DST_COLOR
        dst = GL_ZERO
    end

    ccBlendFunc bf = src, dstend
    layer:setBlendFunc( bf )
end


local function title()

    return "ColorLayer: blend"
end

--------------------------------------------------------------------
--
-- LayerGradient
--
--------------------------------------------------------------------
local function LayerGradient()

    local  layer1 = CCLayerGradient:create(ccc4(255,0,0,255), ccc4(0,255,0,255), ccp(0.9, 0.9))
    addChild(layer1, 0, kTagLayer)

    setTouchEnabled(true)

    local label1 = CCLabelTTF:create("Compressed Interpolation: Enabled", "Marker Felt", 26)
    local label2 = CCLabelTTF:create("Compressed Interpolation: Disabled", "Marker Felt", 26)
    local item1 = CCMenuItemLabel:create(label1)
    local item2 = CCMenuItemLabel:create(label2)
    local item = CCMenuItemToggle:createWithTarget(this, menu_selector(LayerGradient:toggleItem), item1, item2, NULL)

    local menu = CCMenu:create(item, NULL)
    addChild(menu)
    local s = CCDirector:sharedDirector():getWinSize()
    menu:setPosition(ccp(s.width / 2, 100))
end

local function toggleItem(CCObject *sender)

    local gradient = tolua.cast(getChildByTag(kTagLayer), "CCLayerGradient")
    gradient:setCompressedInterpolation(! gradient:isCompressedInterpolation())
end

local function ccTouchesMoved(CCSet * touches, CCEvent *event)

    local s = CCDirector:sharedDirector():getWinSize()

    CCSetIterator it = touches:begin()
    local  touch = (CCTouch*)(*it)
    local start = touch:getLocation()    

    local diff = ccpSub( ccp(s.width/2,s.height/2), start)    
    diff = ccpNormalize(diff)

    local gradient = tolua.cast(getChildByTag(1), "CCLayerGradient")
    gradient:setVector(diff)
end

local function title()

    return "LayerGradient"
end

local function subtitle()

    return "Touch the screen and move your finger"
end

-- LayerIgnoreAnchorPointPos

#define kLayerIgnoreAnchorPoint  1000

local function onEnter()

    LayerTest:onEnter()

    local s = CCDirector:sharedDirector():getWinSize()

    local l = CCLayerColor:create(ccc4(255, 0, 0, 255), 150, 150)

    l:setAnchorPoint(ccp(0.5, 0.5))
    l:setPosition(ccp( s.width/2, s.height/2))

    local move = CCMoveBy:create(2, ccp(100,2))
    local  back = tolua.cast(move:reverse(), "CCMoveBy")
    local seq = CCSequence:create(move, back, NULL)
    l:runAction(CCRepeatForever:create(seq))
    this:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local child = CCSprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(ccp(lsize.width/2, lsize.height/2))

    local item = CCMenuItemFont:create("Toggle ignore anchor point", this, menu_selector(LayerIgnoreAnchorPointPos:onToggle))

    local menu = CCMenu:create(item, NULL)
    this:addChild(menu)

    menu:setPosition(ccp(s.width/2, s.height/2))
end

local function onToggle(CCObject* pObject)

    local  pLayer = this:getChildByTag(kLayerIgnoreAnchorPoint)
    bool ignore = pLayer:isIgnoreAnchorPointForPosition()
    pLayer:ignoreAnchorPointForPosition(! ignore)
end

local function title()

    return "IgnoreAnchorPoint - Position"
end

local function subtitle()

    return "Ignoring Anchor Point for position"
end

-- LayerIgnoreAnchorPointRot

local function onEnter()

    LayerTest:onEnter()
    local s = CCDirector:sharedDirector():getWinSize()

    local l = CCLayerColor:create(ccc4(255, 0, 0, 255), 200, 200)

    l:setAnchorPoint(ccp(0.5, 0.5))
    l:setPosition(ccp( s.width/2, s.height/2))

    this:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local rot = CCRotateBy:create(2, 360)
    l:runAction(CCRepeatForever:create(rot))


    local child = CCSprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(ccp(lsize.width/2, lsize.height/2))

    local item = CCMenuItemFont:create("Toogle ignore anchor point", this, menu_selector(LayerIgnoreAnchorPointRot:onToggle))

    local menu = CCMenu:create(item, NULL)
    this:addChild(menu)

    menu:setPosition(ccp(s.width/2, s.height/2))
end

local function onToggle(CCObject* pObject)

    local  pLayer = this:getChildByTag(kLayerIgnoreAnchorPoint)
    bool ignore = pLayer:isIgnoreAnchorPointForPosition()
    pLayer:ignoreAnchorPointForPosition(! ignore)
end

local function title()

    return "IgnoreAnchorPoint - Rotation"
end

local function subtitle()

    return "Ignoring Anchor Point for rotations"
end

-- LayerIgnoreAnchorPointScale
local function onEnter()

    LayerTest:onEnter()
    
    local s = CCDirector:sharedDirector():getWinSize()

    local l = CCLayerColor:create(ccc4(255, 0, 0, 255), 200, 200)

    l:setAnchorPoint(ccp(0.5, 1.0))
    l:setPosition(ccp( s.width/2, s.height/2))


    local scale = CCScaleBy:create(2, 2)
    local  back = tolua.cast(scale:reverse(), "CCScaleBy")
    local seq = CCSequence:create(scale, back, NULL)

    l:runAction(CCRepeatForever:create(seq))

    this:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local child = CCSprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(ccp(lsize.width/2, lsize.height/2))

    local item = CCMenuItemFont:create("Toogle ignore anchor point", this, menu_selector(LayerIgnoreAnchorPointScale:onToggle))

    local menu = CCMenu:create(item, NULL)
    this:addChild(menu)

    menu:setPosition(ccp(s.width/2, s.height/2))
end

local function onToggle(CCObject* pObject)

    local  pLayer = this:getChildByTag(kLayerIgnoreAnchorPoint)
    bool ignore = pLayer:isIgnoreAnchorPointForPosition()
    pLayer:ignoreAnchorPointForPosition(! ignore)
end

local function title()

    return "IgnoreAnchorPoint - Scale"
end

local function subtitle()

    return "Ignoring Anchor Point for scale"
end

local function runThisTest()

    sceneIdx = -1
    local  pLayer = nextAction()
    addChild(pLayer)

    CCDirector:sharedDirector():replaceScene(this)
end

local function LayerExtendedBlendOpacityTest()

    local  layer1 = CCLayerGradient:create(ccc4(255, 0, 0, 255), ccc4(255, 0, 255, 255))
    layer1:setContentSize(local Make(80, 80))
    layer1:setPosition(ccp(50,50))
    addChild(layer1)
    
    local  layer2 = CCLayerGradient:create(ccc4(0, 0, 0, 127), ccc4(255, 255, 255, 127))
    layer2:setContentSize(local Make(80, 80))
    layer2:setPosition(ccp(100,90))
    addChild(layer2)
    
    local  layer3 = CCLayerGradient:create()
    layer3:setContentSize(local Make(80, 80))
    layer3:setPosition(ccp(150,140))
    layer3:setStartColor(ccc3(255, 0, 0))
    layer3:setEndColor(ccc3(255, 0, 255))
    layer3:setStartOpacity(255)
    layer3:setEndOpacity(255)
    ccBlendFunc blend
    blend.src = GL_SRC_ALPHA
    blend.dst = GL_ONE_MINUS_SRC_ALPHA
    layer3:setBlendFunc(blend)
    addChild(layer3)
end

local function title()

    return "Extended Blend & Opacity"
end

local function subtitle()

    return "You should see 3 layers"
end

function LayerTestMain()
    cclog("LayerTestMain")
    Helper.index = 1
    CCDirector:sharedDirector():setDepthTest(true)
    local scene = CCScene:create()

    Helper.createFunctionTable = {
        LayerTestCascadingOpacityA,
        LayerTestCascadingOpacityB,
        LayerTestCascadingOpacityC,
        LayerTestCascadingColorA,
        LayerTestCascadingColorB,
        LayerTestCascadingColorC,
        LayerTest1,
        LayerTest2,
        LayerTestBlend,
        LayerGradient,
        LayerIgnoreAnchorPointPos,
        LayerIgnoreAnchorPointRot,
        LayerIgnoreAnchorPointScale,
        LayerExtendedBlendOpacityTest
    }
    scene:addChild(LayerTestCascadingOpacityA())
    scene:addChild(CreateBackMenuItem())
    return scene
end
