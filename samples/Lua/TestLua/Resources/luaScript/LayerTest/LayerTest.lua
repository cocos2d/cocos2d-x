local scheduler = CCDirector:sharedDirector():getScheduler()
local kTagLayer = 1

local function createLayerDemoLayer(title, subtitle)
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    local titleStr = title == nil and "No title" or title
    local subTitleStr = subtitle  == nil and "" or subtitle
    Helper.titleLabel:setString(titleStr)
    Helper.subtitleLabel:setString(subTitleStr)

    -- local prev = {x = 0, y = 0}
    -- local function onTouchEvent(eventType, x, y)
    --     if eventType == "began" then
    --         prev.x = x
    --         prev.y = y
    --         return true
    --     elseif  eventType == "moved" then
    --         local node  = layer:getChildByTag(kTagTileMap)
    --         local newX  = node:getPositionX()
    --         local newY  = node:getPositionY()
    --         local diffX = x - prev.x
    --         local diffY = y - prev.y

    --         node:setPosition( ccpAdd(ccp(newX, newY), ccp(diffX, diffY)) )
    --         prev.x = x
    --         prev.y = y
    --     end
    -- end
    -- layer:setTouchEnabled(true)
    -- layer:registerScriptTouchHandler(onTouchEvent)
    return layer
end

--#pragma mark - Cascading support extensions

local function setEnableRecursiveCascading(node, enable)
    if node == nil then
        -- cclog("node == nil, return directly")
        return
    end

    if node.__CCRGBAProtocol__ ~= nil then
        node.__CCRGBAProtocol__:setCascadeColorEnabled(enable)
        node.__CCRGBAProtocol__:setCascadeOpacityEnabled(enable)
    end

    local obj = nil
    local children = node:getChildren()
    if children == nil then
        -- cclog("children is nil")
        return
    end

    local i = 0
    local len = children:count()
    for i = 0, len-1, 1 do
        local  child = tolua.cast(children:objectAtIndex(i), "CCNode")
        setEnableRecursiveCascading(child, enable)
    end
end

-- LayerTestCascadingOpacityA
local function LayerTestCascadingOpacityA()
    local ret = createLayerDemoLayer("LayerRGBA: cascading opacity")
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerRGBA:create()

    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.fnt")

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, s.height/2))
    sister2:setPosition( ccp( s.width*2/3, s.height/2))
    label:setPosition( ccp( s.width/2, s.height/2))

    local arr = CCArray:create()
    arr:addObject(CCFadeTo:create(4, 0))
    arr:addObject(CCFadeTo:create(4, 255))
    arr:addObject(CCDelayTime:create(1))
    layer1:runAction(CCRepeatForever:create(CCSequence:create(arr)))

    arr = CCArray:create()
    arr:addObject(CCFadeTo:create(2, 0))
    arr:addObject(CCFadeTo:create(2, 255))
    arr:addObject(CCFadeTo:create(2, 0))
    arr:addObject(CCFadeTo:create(2, 255))
    arr:addObject(CCDelayTime:create(1))
    sister1:runAction(CCRepeatForever:create(CCSequence:create(arr)))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingOpacityB
local function LayerTestCascadingOpacityB()
    local ret = createLayerDemoLayer("CCLayerColor: cascading opacity")

    local s = CCDirector:sharedDirector():getWinSize()
    local layer1 = CCLayerColor:create(ccc4(192, 0, 0, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)

    layer1:setPosition( ccp(0, s.height/2))

    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.fnt")

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))

    local arr = CCArray:create()
    arr:addObject(CCFadeTo:create(4, 0))
    arr:addObject(CCFadeTo:create(4, 255))
    arr:addObject(CCDelayTime:create(1))

    layer1:runAction(CCRepeatForever:create(CCSequence:create(arr)))

    arr = CCArray:create()
    arr:addObject(CCFadeTo:create(2, 0))
    arr:addObject(CCFadeTo:create(2, 255))
    arr:addObject(CCFadeTo:create(2, 0))
    arr:addObject(CCFadeTo:create(2, 255))
    arr:addObject(CCDelayTime:create(1))

    sister1:runAction(CCRepeatForever:create(CCSequence:create(arr)))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingOpacityC
local function LayerTestCascadingOpacityC()
    local ret = createLayerDemoLayer("CCLayerColor: non-cascading opacity")

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(192, 0, 0, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    layer1:setCascadeOpacityEnabled(false)

    layer1:setPosition( ccp(0, s.height/2))

    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.fnt")

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))

    local arr = CCArray:create()
    arr:addObject(CCFadeTo:create(4, 0))
    arr:addObject(CCFadeTo:create(4, 255))
    arr:addObject(CCDelayTime:create(1))

    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(arr
       )))

    arr = CCArray:create()
    arr:addObject(CCFadeTo:create(2, 0))
    arr:addObject(CCFadeTo:create(2, 255))
    arr:addObject(CCFadeTo:create(2, 0))
    arr:addObject(CCFadeTo:create(2, 255))
    arr:addObject(CCDelayTime:create(1))

    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(arr)))
    return ret
end

--#pragma mark Example LayerTestCascadingColor

-- LayerTestCascadingColorA
local function LayerTestCascadingColorA()
    local ret = createLayerDemoLayer("LayerRGBA: cascading color")

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerRGBA:create()

    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.fnt")

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, s.height/2))
    sister2:setPosition( ccp( s.width*2/3, s.height/2))
    label:setPosition( ccp( s.width/2, s.height/2))

    local arr = CCArray:create()
    arr:addObject(CCTintTo:create(6, 255, 0, 255))
    arr:addObject(CCTintTo:create(6, 255, 255, 255))
    arr:addObject(CCDelayTime:create(1))

    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(arr
       )))

    arr = CCArray:create()
    arr:addObject(CCTintTo:create(2, 255, 255, 0))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCTintTo:create(2, 0, 255, 255))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCTintTo:create(2, 255, 0, 255))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCDelayTime:create(1))

    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       arr)))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingColorB
local function LayerTestCascadingColorB()
    local ret = createLayerDemoLayer("CCLayerColor: cascading color")

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(255, 255, 255, 255), s.width, s.height/2)

    layer1:setPosition( ccp(0, s.height/2))

    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.fnt")

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))

    local arr = CCArray:create()
    arr:addObject(CCTintTo:create(6, 255, 0, 255))
    arr:addObject(CCTintTo:create(6, 255, 255, 255))
    arr:addObject(CCDelayTime:create(1))

    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       arr)))

    arr = CCArray:create()
    arr:addObject(CCTintTo:create(2, 255, 255, 0))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCTintTo:create(2, 0, 255, 255))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCTintTo:create(2, 255, 0, 255))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCDelayTime:create(1))

    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       arr)))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingColorC
local function LayerTestCascadingColorC()
    local ret = createLayerDemoLayer("CCLayerColor: non-cascading color")

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create(ccc4(255, 255, 255, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    layer1:setPosition( ccp(0, s.height/2))

    local sister1 = CCSprite:create("Images/grossinis_sister1.png")
    local sister2 = CCSprite:create("Images/grossinis_sister2.png")
    local label = CCLabelBMFont:create("Test", "fonts/bitmapFontTest.fnt")

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, 0))
    sister2:setPosition( ccp( s.width*2/3, 0))
    label:setPosition( ccp( s.width/2, 0))

    local arr = CCArray:create()
    arr:addObject(CCTintTo:create(6, 255, 0, 255))
    arr:addObject(CCTintTo:create(6, 255, 255, 255))
    arr:addObject(CCDelayTime:create(1))

    layer1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       arr)))

    arr = CCArray:create()
    arr:addObject(CCTintTo:create(2, 255, 255, 0))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCTintTo:create(2, 0, 255, 255))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCTintTo:create(2, 255, 0, 255))
    arr:addObject(CCTintTo:create(2, 255, 255, 255))
    arr:addObject(CCDelayTime:create(1))

    sister1:runAction(
     CCRepeatForever:create(
      CCSequence:create(
       arr)))
    return ret
end

--------------------------------------------------------------------
--
-- LayerTest1
--
--------------------------------------------------------------------
local function LayerTest1()
    local ret = createLayerDemoLayer("ColorLayer resize (tap & move)")

    ret:setTouchEnabled(true)

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer = CCLayerColor:create( ccc4(0xFF, 0x00, 0x00, 0x80), 200, 200)

    layer:ignoreAnchorPointForPosition(false)
    layer:setPosition( ccp(s.width/2, s.height/2) )
    ret:addChild(layer, 1, kTagLayer)

    local function updateSize(x, y)
        local s = CCDirector:sharedDirector():getWinSize()

        local newSize = CCSizeMake( math.abs(x - s.width/2)*2, math.abs(y - s.height/2)*2)

        local  l = tolua.cast(ret:getChildByTag(kTagLayer), "CCLayerColor")

        l:setContentSize( newSize )
    end

    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            updateSize(x, y)
            return true
        else
            updateSize(x, y)
        end
    end
    ret:registerScriptTouchHandler(onTouchEvent)
    return ret
end

--------------------------------------------------------------------
--
-- LayerTest2
--
--------------------------------------------------------------------
local function LayerTest2()
    local ret = createLayerDemoLayer("ColorLayer: fade and tint")

    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create( ccc4(255, 255, 0, 80), 100, 300)
    layer1:setPosition(ccp(s.width/3, s.height/2))
    layer1:ignoreAnchorPointForPosition(false)
    ret:addChild(layer1, 1)

    local  layer2 = CCLayerColor:create( ccc4(0, 0, 255, 255), 100, 300)
    layer2:setPosition(ccp((s.width/3)*2, s.height/2))
    layer2:ignoreAnchorPointForPosition(false)
    ret:addChild(layer2, 1)

    local  actionTint = CCTintBy:create(2, -255, -127, 0)
    local  actionTintBack = actionTint:reverse()
    local arr = CCArray:create()
    arr:addObject(actionTint)
    arr:addObject(actionTintBack)
    local  seq1 = CCSequence:create(arr)
    layer1:runAction(seq1)

    local  actionFade = CCFadeOut:create(2.0)
    local  actionFadeBack = actionFade:reverse()
    arr = CCArray:create()
    arr:addObject(actionFade)
    arr:addObject(actionFadeBack)
    local  seq2 = CCSequence:create(arr)
    layer2:runAction(seq2)

    return ret
end

--------------------------------------------------------------------
--
-- LayerTestBlend
--
--------------------------------------------------------------------

local function LayerTestBlend()
    local ret = createLayerDemoLayer("ColorLayer: blend")
    local s = CCDirector:sharedDirector():getWinSize()
    local  layer1 = CCLayerColor:create( ccc4(255, 255, 255, 80) )

    local  sister1 = CCSprite:create(s_pPathSister1)
    local  sister2 = CCSprite:create(s_pPathSister2)

    ret:addChild(sister1)
    ret:addChild(sister2)
    ret:addChild(layer1, 100, kTagLayer)

    sister1:setPosition( ccp( s.width*1/3, s.height/2) )
    sister2:setPosition( ccp( s.width*2/3, s.height/2) )

    local function newBlend(dt)
        local layer = tolua.cast(ret:getChildByTag(kTagLayer), "CCLayerColor")

        local src = 0
        local dst = 0

        if  layer:getBlendFunc().dst == GL_ZERO then
            src = GL_SRC_ALPHA
            dst = GL_ONE_MINUS_SRC_ALPHA
        else
            src = GL_ONE_MINUS_DST_COLOR
            dst = GL_ZERO
        end

        local bf = ccBlendFunc()
        bf.src = src
        bf.dst = dst
        layer:setBlendFunc( bf )
    end


    local schedulerEntry = nil
    local function onNodeEvent(event)
        if event == "enter" then
            schedulerEntry = scheduler:scheduleScriptFunc(newBlend, 1.0, false)
        elseif event == "exit" then
            scheduler:unscheduleScriptEntry(schedulerEntry)
        end
    end

    ret:registerScriptHandler(onNodeEvent)
    return ret
end

--------------------------------------------------------------------
--
-- LayerGradient
--
--------------------------------------------------------------------
local function LayerGradient()
    local ret = createLayerDemoLayer("LayerGradient", "Touch the screen and move your finger")
    local  layer1 = CCLayerGradient:create(ccc4(255,0,0,255), ccc4(0,255,0,255), ccp(0.9, 0.9))
    ret:addChild(layer1, 0, kTagLayer)

    ret:setTouchEnabled(true)

    local label1 = CCLabelTTF:create("Compressed Interpolation: Enabled", "Marker Felt", 26)
    local label2 = CCLabelTTF:create("Compressed Interpolation: Disabled", "Marker Felt", 26)
    local item1 = CCMenuItemLabel:create(label1)
    local item2 = CCMenuItemLabel:create(label2)
    local item = CCMenuItemToggle:create(item1)
    item:addSubItem(item2)

    local function toggleItem(sender)
        -- cclog("toggleItem")
        local gradient = tolua.cast(ret:getChildByTag(kTagLayer), "CCLayerGradient")
        gradient:setCompressedInterpolation(not gradient:isCompressedInterpolation())
    end

    item:registerScriptTapHandler(toggleItem)

    local menu = CCMenu:createWithItem(item)
    ret:addChild(menu)
    local s = CCDirector:sharedDirector():getWinSize()
    menu:setPosition(ccp(s.width / 2, 100))

    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            return true
        elseif eventType == "moved" then
            local s = CCDirector:sharedDirector():getWinSize()
            local start = ccp(x, y)

            local diff = ccpSub( ccp(s.width/2,s.height/2), start)
            diff = ccpNormalize(diff)

            local gradient = tolua.cast(ret:getChildByTag(1), "CCLayerGradient")
            gradient:setVector(diff)
        end
    end

    ret:registerScriptTouchHandler(onTouchEvent)
    return ret
end


-- LayerIgnoreAnchorPointPos

local kLayerIgnoreAnchorPoint = 1000

local function LayerIgnoreAnchorPointPos()
    local ret = createLayerDemoLayer("IgnoreAnchorPoint - Position", "Ignoring Anchor Point for position")

    local s = CCDirector:sharedDirector():getWinSize()

    local l = CCLayerColor:create(ccc4(255, 0, 0, 255), 150, 150)

    l:setAnchorPoint(ccp(0.5, 0.5))
    l:setPosition(ccp( s.width/2, s.height/2))

    local move = CCMoveBy:create(2, ccp(100,2))
    local  back = tolua.cast(move:reverse(), "CCMoveBy")
    local arr = CCArray:create()
    arr:addObject(move)
    arr:addObject(back)
    local seq = CCSequence:create(arr)
    l:runAction(CCRepeatForever:create(seq))
    ret:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local child = CCSprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(ccp(lsize.width/2, lsize.height/2))

    local function onToggle(pObject)
        local  pLayer = ret:getChildByTag(kLayerIgnoreAnchorPoint)
        local ignore = pLayer:isIgnoreAnchorPointForPosition()
        pLayer:ignoreAnchorPointForPosition(not ignore)
    end

    local item = CCMenuItemFont:create("Toggle ignore anchor point")
    item:registerScriptTapHandler(onToggle)

    local menu = CCMenu:createWithItem(item)
    ret:addChild(menu)

    menu:setPosition(ccp(s.width/2, s.height/2))
    return ret
end

-- LayerIgnoreAnchorPointRot

local function LayerIgnoreAnchorPointRot()
    local ret = createLayerDemoLayer("IgnoreAnchorPoint - Rotation", "Ignoring Anchor Point for rotations")

    local s = CCDirector:sharedDirector():getWinSize()

    local l = CCLayerColor:create(ccc4(255, 0, 0, 255), 200, 200)

    l:setAnchorPoint(ccp(0.5, 0.5))
    l:setPosition(ccp( s.width/2, s.height/2))

    ret:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local rot = CCRotateBy:create(2, 360)
    l:runAction(CCRepeatForever:create(rot))


    local child = CCSprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(ccp(lsize.width/2, lsize.height/2))

    local function onToggle(pObject)
        local  pLayer = ret:getChildByTag(kLayerIgnoreAnchorPoint)
        local ignore = pLayer:isIgnoreAnchorPointForPosition()
        pLayer:ignoreAnchorPointForPosition(not ignore)
    end

    local item = CCMenuItemFont:create("Toogle ignore anchor point")
    item:registerScriptTapHandler(onToggle)

    local menu = CCMenu:createWithItem(item)
    ret:addChild(menu)

    menu:setPosition(ccp(s.width/2, s.height/2))
    return ret
end

-- LayerIgnoreAnchorPointScale
local function LayerIgnoreAnchorPointScale()
    local ret = createLayerDemoLayer("IgnoreAnchorPoint - Scale", "Ignoring Anchor Point for scale")
    local s = CCDirector:sharedDirector():getWinSize()

    local l = CCLayerColor:create(ccc4(255, 0, 0, 255), 200, 200)

    l:setAnchorPoint(ccp(0.5, 1.0))
    l:setPosition(ccp( s.width/2, s.height/2))


    local scale = CCScaleBy:create(2, 2)
    local  back = tolua.cast(scale:reverse(), "CCScaleBy")
    local arr = CCArray:create()
    arr:addObject(scale)
    arr:addObject(back)
    local seq = CCSequence:create(arr)

    l:runAction(CCRepeatForever:create(seq))

    ret:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local child = CCSprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(ccp(lsize.width/2, lsize.height/2))

    local function onToggle(pObject)
        local  pLayer = ret:getChildByTag(kLayerIgnoreAnchorPoint)
        local ignore = pLayer:isIgnoreAnchorPointForPosition()
        pLayer:ignoreAnchorPointForPosition(not ignore)
        return ret
    end

    local item = CCMenuItemFont:create("Toogle ignore anchor point")
    item:registerScriptTapHandler(onToggle)

    local menu = CCMenu:createWithItem(item)
    ret:addChild(menu)

    menu:setPosition(ccp(s.width/2, s.height/2))
    return ret
end


local function LayerExtendedBlendOpacityTest()
    local ret = createLayerDemoLayer("Extended Blend & Opacity", "You should see 3 layers")
    local  layer1 = CCLayerGradient:create(ccc4(255, 0, 0, 255), ccc4(255, 0, 255, 255))
    layer1:setContentSize(CCSizeMake(80, 80))
    layer1:setPosition(ccp(50,50))
    ret:addChild(layer1)

    local  layer2 = CCLayerGradient:create(ccc4(0, 0, 0, 127), ccc4(255, 255, 255, 127))
    layer2:setContentSize(CCSizeMake(80, 80))
    layer2:setPosition(ccp(100,90))
    ret:addChild(layer2)

    local  layer3 = CCLayerGradient:create()
    layer3:setContentSize(CCSizeMake(80, 80))
    layer3:setPosition(ccp(150,140))
    layer3:setStartColor(ccc3(255, 0, 0))
    layer3:setEndColor(ccc3(255, 0, 255))
    layer3:setStartOpacity(255)
    layer3:setEndOpacity(255)
    local blend = ccBlendFunc()
    blend.src = GL_SRC_ALPHA
    blend.dst = GL_ONE_MINUS_SRC_ALPHA
    layer3:setBlendFunc(blend)
    ret:addChild(layer3)
    return ret
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
