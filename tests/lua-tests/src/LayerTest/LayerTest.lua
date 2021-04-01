local scheduler = cc.Director:getInstance():getScheduler()
local kTagLayer = 1

local function createLayerDemoLayer(title, subtitle)
    local layer = cc.Layer:create()
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

    --         node:setPosition( cc.p.__add(cc.p(newX, newY), cc.p(diffX, diffY)) )
    --         prev.x = x
    --         prev.y = y
    --     end
    -- end
    -- layer:setTouchEnabled(true)
    -- layer:registerScriptTouchHandler(onTouchEvent)
    return layer
end

-- Cascading support extensions

local function setEnableRecursiveCascading(node, enable)
    if node == nil then
        -- cclog("node == nil, return directly")
        return
    end

    if node.setCascadeColorEnabled ~= nil and node.setCascadeOpacityEnabled ~= nil then
        node:setCascadeColorEnabled(enable)
        node:setCascadeOpacityEnabled(enable)
    end

    local obj = nil
    local children = node:getChildren()
    if children == nil then
        -- cclog("children is nil")
        print("children is nil")
        return
    end

    local i = 0
    local len = table.getn(children)
    for i = 0, len-1, 1 do
        setEnableRecursiveCascading(children[i + 1], enable)
    end
end

-- LayerTestCascadingOpacityA
local function LayerTestCascadingOpacityA()
    local ret = createLayerDemoLayer("Layer: cascading opacity")
    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.Layer:create()

    local sister1 = cc.Sprite:create("Images/grossinis_sister1.png")
    local sister2 = cc.Sprite:create("Images/grossinis_sister2.png")
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt", "Test")
    label:setAnchorPoint(cc.p(0.5, 0.5))

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, s.height/2))
    sister2:setPosition( cc.p( s.width*2/3, s.height/2))
    label:setPosition( cc.p( s.width/2, s.height/2))

    layer1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(4, 0),
                                             cc.FadeTo:create(4, 255),
                                             cc.DelayTime:create(1) 
    )))


    sister1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(2, 0),
                                              cc.FadeTo:create(2, 255),
                                              cc.FadeTo:create(2, 0),
                                              cc.FadeTo:create(2, 255),
                                              cc.DelayTime:create(1)
                                              )))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingOpacityB
local function LayerTestCascadingOpacityB()
    local ret = createLayerDemoLayer("CCLayerColor: cascading opacity")

    local s = cc.Director:getInstance():getWinSize()
    local layer1 = cc.LayerColor:create(cc.c4b(192, 0, 0, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)

    layer1:setPosition( cc.p(0, s.height/2))

    local sister1 = cc.Sprite:create("Images/grossinis_sister1.png")
    local sister2 = cc.Sprite:create("Images/grossinis_sister2.png")
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt","Test")
    label:setAnchorPoint(cc.p(0.5, 0.5))

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, 0))
    sister2:setPosition( cc.p( s.width*2/3, 0))
    label:setPosition( cc.p( s.width/2, 0))

    layer1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(4, 0),cc.FadeTo:create(4, 255),cc.DelayTime:create(1))))

    sister1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(2, 0),cc.FadeTo:create(2, 255),cc.FadeTo:create(2, 0),cc.FadeTo:create(2, 255),cc.DelayTime:create(1))))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingOpacityC
local function LayerTestCascadingOpacityC()
    local ret = createLayerDemoLayer("LayerColor: non-cascading opacity")

    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.LayerColor:create(cc.c4b(192, 0, 0, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    layer1:setCascadeOpacityEnabled(false)

    layer1:setPosition( cc.p(0, s.height/2))

    local sister1 = cc.Sprite:create("Images/grossinis_sister1.png")
    local sister2 = cc.Sprite:create("Images/grossinis_sister2.png")
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt","Test")
    label:setAnchorPoint(cc.p(0.5, 0.5))

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, 0))
    sister2:setPosition( cc.p( s.width*2/3, 0))
    label:setPosition( cc.p( s.width/2, 0))

    layer1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(4, 0),
                    cc.FadeTo:create(4, 255),cc.DelayTime:create(1))))

    sister1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(2, 0),cc.FadeTo:create(2, 255),
                                              cc.FadeTo:create(2, 0),cc.FadeTo:create(2, 255),cc.DelayTime:create(1))))
    return ret
end

--// Example LayerTestCascadingColor

-- LayerTestCascadingColorA
local function LayerTestCascadingColorA()
    local ret = createLayerDemoLayer("Layer: cascading color")

    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.Layer:create()

    local sister1 = cc.Sprite:create("Images/grossinis_sister1.png")
    local sister2 = cc.Sprite:create("Images/grossinis_sister2.png")
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt","Test")
    label:setAnchorPoint(cc.p(0.5, 0.5))

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, s.height/2))
    sister2:setPosition( cc.p( s.width*2/3, s.height/2))
    label:setPosition( cc.p( s.width/2, s.height/2))

    layer1:runAction(
     cc.RepeatForever:create(
      cc.Sequence:create(cc.TintTo:create(6, 255, 0, 255),
                         cc.TintTo:create(6, 255, 255, 255),
                         cc.DelayTime:create(1)
       )))


    sister1:runAction(
     cc.RepeatForever:create(
      cc.Sequence:create(cc.TintTo:create(2, 255, 255, 0),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.TintTo:create(2, 0, 255, 255),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.TintTo:create(2, 255, 0, 255),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.DelayTime:create(1)
       )))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingColorB
local function LayerTestCascadingColorB()
    local ret = createLayerDemoLayer("LayerColor: cascading color")

    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.LayerColor:create(cc.c4b(255, 255, 255, 255), s.width, s.height/2)

    layer1:setPosition( cc.p(0, s.height/2))

    local sister1 = cc.Sprite:create("Images/grossinis_sister1.png")
    local sister2 = cc.Sprite:create("Images/grossinis_sister2.png")
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt","Test")
    label:setAnchorPoint(cc.p(0.5, 0.5))

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, 0))
    sister2:setPosition( cc.p( s.width*2/3, 0))
    label:setPosition( cc.p( s.width/2, 0))

    layer1:runAction(
     cc.RepeatForever:create(
      cc.Sequence:create(cc.TintTo:create(6, 255, 0, 255),
                         cc.TintTo:create(6, 255, 255, 255),
                         cc.DelayTime:create(1)
       )))

    sister1:runAction(
     cc.RepeatForever:create(
      cc.Sequence:create(cc.TintTo:create(2, 255, 255, 0),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.TintTo:create(2, 0, 255, 255),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.TintTo:create(2, 255, 0, 255),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.DelayTime:create(1)
       )))

    -- Enable cascading in scene
    setEnableRecursiveCascading(ret, true)
    return ret
end

-- LayerTestCascadingColorC
local function LayerTestCascadingColorC()
    local ret = createLayerDemoLayer("LayerColor: non-cascading color")

    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.LayerColor:create(cc.c4b(255, 255, 255, 255), s.width, s.height/2)
    layer1:setCascadeColorEnabled(false)
    layer1:setPosition( cc.p(0, s.height/2))

    local sister1 = cc.Sprite:create("Images/grossinis_sister1.png")
    local sister2 = cc.Sprite:create("Images/grossinis_sister2.png")
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt","Test")
    label:setAnchorPoint(cc.p(0.5, 0.5))

    layer1:addChild(sister1)
    layer1:addChild(sister2)
    layer1:addChild(label)
    ret:addChild( layer1, 0, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, 0))
    sister2:setPosition( cc.p( s.width*2/3, 0))
    label:setPosition( cc.p( s.width/2, 0))

    layer1:runAction(
     cc.RepeatForever:create(
      cc.Sequence:create(cc.TintTo:create(6, 255, 0, 255),
                         cc.TintTo:create(6, 255, 255, 255),
                         cc.DelayTime:create(1)
       )))

    sister1:runAction(
     cc.RepeatForever:create(
      cc.Sequence:create(cc.TintTo:create(2, 255, 255, 0),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.TintTo:create(2, 0, 255, 255),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.TintTo:create(2, 255, 0, 255),
                         cc.TintTo:create(2, 255, 255, 255),
                         cc.DelayTime:create(1)
       )))
    return ret
end

--------------------------------------------------------------------
--
-- LayerTest1
--
--------------------------------------------------------------------
local function LayerTest1()
    local ret = createLayerDemoLayer("ColorLayer resize (tap & move)")

    local s = cc.Director:getInstance():getWinSize()
    local  layer = cc.LayerColor:create( cc.c4b(0xFF, 0x00, 0x00, 0x80), 200, 200)

    layer:setIgnoreAnchorPointForPosition(false)
    layer:setPosition( cc.p(s.width/2, s.height/2) )
    ret:addChild(layer, 1, kTagLayer)

    local function updateSize(x, y)
        local s = cc.Director:getInstance():getWinSize()

        local newSize = cc.size( math.abs(x - s.width/2)*2, math.abs(y - s.height/2)*2)

        local  l = ret:getChildByTag(kTagLayer)

        l:setContentSize( newSize )
    end

    local function onTouchesMoved(touches, event)
        local touchLocation = touches[1]:getLocation()

        updateSize(touchLocation.x, touchLocation.y)
    end

    local function onTouchesBegan(touches, event)
        onTouchesMoved(touches, event)
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()    
    listener:registerScriptHandler(onTouchesBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )

    local eventDispatcher = ret:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ret)

    return ret
end

--------------------------------------------------------------------
--
-- LayerTest2
--
--------------------------------------------------------------------
local function LayerTest2()
    local ret = createLayerDemoLayer("ColorLayer: fade and tint")

    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.LayerColor:create( cc.c4b(255, 255, 0, 80), 100, 300)
    layer1:setPosition(cc.p(s.width/3, s.height/2))
    layer1:setIgnoreAnchorPointForPosition(false)
    ret:addChild(layer1, 1)

    local  layer2 = cc.LayerColor:create( cc.c4b(0, 0, 255, 255), 100, 300)
    layer2:setPosition(cc.p((s.width/3)*2, s.height/2))
    layer2:setIgnoreAnchorPointForPosition(false)
    ret:addChild(layer2, 1)

    local  actionTint = cc.TintBy:create(2, -255, -127, 0)
    local  actionTintBack = actionTint:reverse()
    local  seq1 = cc.Sequence:create(actionTint,actionTintBack)
    layer1:runAction(seq1)

    local  actionFade = cc.FadeOut:create(2.0)
    local  actionFadeBack = actionFade:reverse()
    local  seq2 = cc.Sequence:create(actionFade,actionFadeBack)
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
    local s = cc.Director:getInstance():getWinSize()
    local  layer1 = cc.LayerColor:create( cc.c4b(255, 255, 255, 80) )

    local  sister1 = cc.Sprite:create(s_pPathSister1)
    local  sister2 = cc.Sprite:create(s_pPathSister2)

    ret:addChild(sister1)
    ret:addChild(sister2)
    ret:addChild(layer1, 100, kTagLayer)

    sister1:setPosition( cc.p( s.width*1/3, s.height/2) )
    sister2:setPosition( cc.p( s.width*2/3, s.height/2) )

    local blend = true

    local function newBlend(dt)
        local layer = ret:getChildByTag(kTagLayer)

        local src = 0
        local dst = 0

        if  blend  then
            src = ccb.BlendFactor.SRC_ALPHA 
            dst = ccb.BlendFactor.ONE_MINUS_SRC_ALPHA 
        else
            src = ccb.BlendFactor.ONE_MINUS_DST_COLOR
            dst = ccb.BlendFactor.ZERO
        end

        layer:setBlendFunc(cc.blendFunc(src, dst))
        blend = not blend
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
    local  layer1 = cc.LayerGradient:create(cc.c4b(255,0,0,255), cc.c4b(0,255,0,255), cc.p(0.9, 0.9))
    ret:addChild(layer1, 0, kTagLayer)

    local label1 = cc.Label:createWithTTF("Compressed Interpolation: Enabled", s_markerFeltFontPath, 26)
    label1:setAnchorPoint(cc.p(0.5, 0.5))
    local label2 = cc.Label:createWithTTF("Compressed Interpolation: Disabled", s_markerFeltFontPath, 26)
    label2:setAnchorPoint(cc.p(0.5, 0.5))
    local item1 = cc.MenuItemLabel:create(label1)
    local item2 = cc.MenuItemLabel:create(label2)
    local item = cc.MenuItemToggle:create(item1)
    item:addSubItem(item2)

    local function toggleItem(sender)
        -- cclog("toggleItem")
        local gradient = ret:getChildByTag(kTagLayer)
        gradient:setCompressedInterpolation(not gradient:isCompressedInterpolation())
    end

    item:registerScriptTapHandler(toggleItem)

    local menu = cc.Menu:create(item)
    ret:addChild(menu)
    local s = cc.Director:getInstance():getWinSize()
    menu:setPosition(cc.p(s.width / 2, 100))

    local function onTouchesMoved(touches, event)
        local s = cc.Director:getInstance():getWinSize()
        local start = touches[1]:getLocation()
        local movingPos = cc.p(s.width/2,s.height/2)
        local diff = cc.p(movingPos.x - start.x, movingPos.y - start.y)
        diff = cc.pNormalize(diff)

        local gradient = ret:getChildByTag(1)
        gradient:setVector(diff)
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()    
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )

    local eventDispatcher = ret:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ret)

    return ret
end


-- LayerIgnoreAnchorPointPos

local kLayerIgnoreAnchorPoint = 1000

local function LayerIgnoreAnchorPointPos()
    local ret = createLayerDemoLayer("IgnoreAnchorPoint - Position", "Ignoring Anchor Point for position")

    local s = cc.Director:getInstance():getWinSize()

    local l = cc.LayerColor:create(cc.c4b(255, 0, 0, 255), 150, 150)

    l:setAnchorPoint(cc.p(0.5, 0.5))
    l:setPosition(cc.p( s.width/2, s.height/2))

    local move = cc.MoveBy:create(2, cc.p(100,2))
    local  back = move:reverse()
    local seq = cc.Sequence:create(move, back)
    l:runAction(cc.RepeatForever:create(seq))
    ret:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local child = cc.Sprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(cc.p(lsize.width/2, lsize.height/2))

    local function onToggle(pObject)
        local  pLayer = ret:getChildByTag(kLayerIgnoreAnchorPoint)
        local ignore = pLayer:isIgnoreAnchorPointForPosition()
        pLayer:setIgnoreAnchorPointForPosition(not ignore)
    end

    local item = cc.MenuItemFont:create("Toggle ignore anchor point")
    item:registerScriptTapHandler(onToggle)

    local menu = cc.Menu:create(item)
    ret:addChild(menu)

    menu:setPosition(cc.p(s.width/2, s.height/2))
    return ret
end

-- LayerIgnoreAnchorPointRot

local function LayerIgnoreAnchorPointRot()
    local ret = createLayerDemoLayer("IgnoreAnchorPoint - Rotation", "Ignoring Anchor Point for rotations")

    local s = cc.Director:getInstance():getWinSize()

    local l = cc.LayerColor:create(cc.c4b(255, 0, 0, 255), 200, 200)

    l:setAnchorPoint(cc.p(0.5, 0.5))
    l:setPosition(cc.p( s.width/2, s.height/2))

    ret:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local rot = cc.RotateBy:create(2, 360)
    l:runAction(cc.RepeatForever:create(rot))


    local child = cc.Sprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(cc.p(lsize.width/2, lsize.height/2))

    local function onToggle(pObject)
        local  pLayer = ret:getChildByTag(kLayerIgnoreAnchorPoint)
        local ignore = pLayer:isIgnoreAnchorPointForPosition()
        pLayer:setIgnoreAnchorPointForPosition(not ignore)
    end

    local item = cc.MenuItemFont:create("Toggle ignore anchor point")
    item:registerScriptTapHandler(onToggle)

    local menu = cc.Menu:create(item)
    ret:addChild(menu)

    menu:setPosition(cc.p(s.width/2, s.height/2))
    return ret
end

-- LayerIgnoreAnchorPointScale
local function LayerIgnoreAnchorPointScale()
    local ret = createLayerDemoLayer("IgnoreAnchorPoint - Scale", "Ignoring Anchor Point for scale")
    local s = cc.Director:getInstance():getWinSize()

    local l = cc.LayerColor:create(cc.c4b(255, 0, 0, 255), 200, 200)

    l:setAnchorPoint(cc.p(0.5, 1.0))
    l:setPosition(cc.p( s.width/2, s.height/2))


    local scale = cc.ScaleBy:create(2, 2)
    local  back = scale:reverse()
    local seq = cc.Sequence:create(scale, back)

    l:runAction(cc.RepeatForever:create(seq))

    ret:addChild(l, 0, kLayerIgnoreAnchorPoint)

    local child = cc.Sprite:create("Images/grossini.png")
    l:addChild(child)
    local lsize = l:getContentSize()
    child:setPosition(cc.p(lsize.width/2, lsize.height/2))

    local function onToggle(pObject)
        local  pLayer = ret:getChildByTag(kLayerIgnoreAnchorPoint)
        local ignore = pLayer:isIgnoreAnchorPointForPosition()
        pLayer:setIgnoreAnchorPointForPosition(not ignore)
        return ret
    end

    local item = cc.MenuItemFont:create("Toggle ignore anchor point")
    item:registerScriptTapHandler(onToggle)

    local menu = cc.Menu:create(item)
    ret:addChild(menu)

    menu:setPosition(cc.p(s.width/2, s.height/2))
    return ret
end


local function LayerExtendedBlendOpacityTest()
    local ret = createLayerDemoLayer("Extended Blend & Opacity", "You should see 3 layers")
    local  layer1 = cc.LayerGradient:create(cc.c4b(255, 0, 0, 255), cc.c4b(255, 0, 255, 255))
    layer1:setContentSize(cc.size(80, 80))
    layer1:setPosition(cc.p(50,50))
    ret:addChild(layer1)

    local  layer2 = cc.LayerGradient:create(cc.c4b(0, 0, 0, 127), cc.c4b(255, 255, 255, 127))
    layer2:setContentSize(cc.size(80, 80))
    layer2:setPosition(cc.p(100,90))
    ret:addChild(layer2)

    local  layer3 = cc.LayerGradient:create()
    layer3:setContentSize(cc.size(80, 80))
    layer3:setPosition(cc.p(150,140))
    layer3:setStartColor(cc.c3b(255, 0, 0))
    layer3:setEndColor(cc.c3b(255, 0, 255))
    layer3:setStartOpacity(255)
    layer3:setEndOpacity(255)
    layer3:setBlendFunc(cc.blendFunc(ccb.BlendFactor.SRC_ALPHA, ccb.BlendFactor.ONE_MINUS_SRC_ALPHA))
    ret:addChild(layer3)
    return ret
end

function LayerTestMain()
    cclog("LayerTestMain")
    Helper.index = 1
    local scene = cc.Scene:create()

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
    Helper.index = 1
    
    scene:addChild(LayerTestCascadingOpacityA())
    scene:addChild(CreateBackMenuItem())
    return scene
end
