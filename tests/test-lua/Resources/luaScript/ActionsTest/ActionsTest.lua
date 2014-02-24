local size = cc.Director:getInstance():getWinSize()

local function initWithLayer(layer)
	grossini = cc.Sprite:create(s_pPathGrossini)
	tamara   = cc.Sprite:create(s_pPathSister1)
	kathia   = cc.Sprite:create(s_pPathSister2)

	layer:addChild(grossini, 1)
	layer:addChild(tamara, 2)
	layer:addChild(kathia, 3)

	grossini:setPosition(cc.p(size.width / 2, size.height / 3))
	tamara:setPosition(cc.p(size.width / 2, 2 * size.height / 3))
	kathia:setPosition(cc.p(size.width / 2, size.height / 2))

	Helper.initWithLayer(layer)
end


local function centerSprites(numberOfSprites)
	if numberOfSprites == 0 then
		tamara:setVisible(false)
		kathia:setVisible(false)
		grossini:setVisible(false)
	elseif numberOfSprites == 1 then
		tamara:setVisible(false)
		kathia:setVisible(false)
		grossini:setPosition(cc.p(size.width / 2, size.height / 2))
	elseif numberOfSprites == 2 then
		kathia:setPosition(cc.p(size.width / 3, size.height / 2))
		tamara:setPosition(cc.p(2 * size.width / 3, size.height / 2))
		grossini:setVisible(false)
	elseif numberOfSprites == 3 then
		grossini:setPosition(cc.p(size.width / 2, size.height / 2))
		tamara:setPosition(cc.p(size.width / 4, size.height / 2))
		kathia:setPosition(cc.p(3 * size.width / 4, size.height / 2))
	end
end

local function alignSpritesLeft(numberOfSprites)
	if numberOfSprites == 1 then
		tamara:setVisible(false)
		kathia:setVisible(false)
		grossini:setPosition(cc.p(60, size.height / 2))
	elseif numberOfSprites == 2 then
		kathia:setPosition(cc.p(60, size.height / 3))
		tamara:setPosition(cc.p(60, 2 * size.height / 3))
		grossini:setVisible(false)
	elseif numberOfSprites == 3 then
		grossini:setPosition(cc.p(60, size.height / 2))
		tamara:setPosition(cc.p(60, 2 * size.height / 3))
		kathia:setPosition(cc.p(60, size.height / 3))
	end
end


--------------------------------------
-- ActionManual
--------------------------------------
local function ActionManual()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	tamara:setScaleX(2.5)
	tamara:setScaleY(-1.0)
	tamara:setPosition(cc.p(100, 70))
	tamara:setOpacity(128)

	grossini:setRotation(120)
	grossini:setPosition(cc.p(size.width / 2, size.height / 2))
	grossini:setColor(cc.c3b(255, 0, 0))

	kathia:setPosition(cc.p(size.width - 100, size.height / 2))
	kathia:setColor(cc.c3b(0, 0, 255))

	Helper.subtitleLabel:setString("Manual Transformation")
	return layer
end

--------------------------------------
-- ActionMove
--------------------------------------
local function ActionMove()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)
	local actionBy = cc.MoveBy:create(2, cc.p(80, 80))
	local actionByBack = actionBy:reverse()

	tamara:runAction(cc.MoveTo:create(2, cc.p(size.width - 40, size.height - 40)))
	grossini:runAction(cc.Sequence:create(actionBy, actionByBack))
	kathia:runAction(cc.MoveTo:create(1, cc.p(40, 40)))

	Helper.subtitleLabel:setString("MoveTo / MoveBy")
	return layer
end

--------------------------------------
-- ActionScale
--------------------------------------
local function ActionScale()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

	local actionTo = cc.ScaleTo:create(2.0, 0.5)
	local actionBy = cc.ScaleBy:create(2.0, 1.0, 10.0)
	local actionBy2 = cc.ScaleBy:create(2.0, 5.0, 1.0)

	grossini:runAction(actionTo)
	tamara:runAction(cc.Sequence:create(actionBy, actionBy:reverse()))
	kathia:runAction(cc.Sequence:create(actionBy2, actionBy2:reverse()))

	Helper.subtitleLabel:setString("ScaleTo / ScaleBy")
	return layer
end

--------------------------------------
-- ActionRotate
--------------------------------------
local function ActionRotate()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

    local actionTo = cc.RotateTo:create( 2, 45)
    local actionTo2 = cc.RotateTo:create( 2, -45)
    local actionTo0 = cc.RotateTo:create(2 , 0)
    tamara:runAction(cc.Sequence:create(actionTo, actionTo0))

    local actionBy = cc.RotateBy:create(2 , 360)
    local actionByBack = actionBy:reverse()
    grossini:runAction(cc.Sequence:create(actionBy, actionByBack))

    local action0Retain = cc.RotateTo:create(2 , 0)

    kathia:runAction(cc.Sequence:create(actionTo2, action0Retain))

	Helper.subtitleLabel:setString("RotateTo / RotateBy")
	return layer
end

--------------------------------------
-- ActionSkew
--------------------------------------
local function ActionSkew()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

    local actionTo = cc.SkewTo:create(2, 37.2, -37.2)
    local actionToBack = cc.SkewTo:create(2, 0, 0)
    local actionBy = cc.SkewBy:create(2, 0.0, -90.0)
    local actionBy2 = cc.SkewBy:create(2, 45.0, 45.0)
    local actionByBack = actionBy:reverse()

    tamara:runAction(cc.Sequence:create(actionTo, actionToBack))
    grossini:runAction(cc.Sequence:create(actionBy, actionByBack))
    kathia:runAction(cc.Sequence:create(actionBy2, actionBy2:reverse()))

	Helper.subtitleLabel:setString("SkewTo / SkewBy")
	return layer
end

--ActionRotationalSkewVSStandardSkew
local function ActionRotationalSkewVSStandardSkew()

    local layer = cc.Layer:create()
	initWithLayer(layer)

    tamara:removeFromParent(true);
    grossini:removeFromParent(true);
    kathia:removeFromParent(true);

    local s = cc.Director:getInstance():getWinSize();
    local boxSize = cc.size(100.0, 100.0);
    local box = cc.LayerColor:create(cc.c4b(255,255,0,255));
    box:setAnchorPoint(cc.p(0.5,0.5));
    box:setContentSize( boxSize );
    box:ignoreAnchorPointForPosition(false);
    box:setPosition(cc.p(s.width/2, s.height - 100 - box:getContentSize().height/2));
    layer:addChild(box);
    local label = cc.LabelTTF:create("Standard cocos2d Skew", "Marker Felt", 16);
    label:setPosition(cc.p(s.width/2, s.height - 100 + label:getContentSize().height));
    layer:addChild(label);
    local actionTo = cc.SkewBy:create(2, 360, 0);
    local actionToBack = cc.SkewBy:create(2, -360, 0);
    local seq = cc.Sequence:create(actionTo, actionToBack)

    box:runAction(seq);

    box = cc.LayerColor:create(cc.c4b(255,255,0,255));
    box:setAnchorPoint(cc.p(0.5,0.5));
    box:setContentSize(boxSize);
    box:ignoreAnchorPointForPosition(false);
    box:setPosition(cc.p(s.width/2, s.height - 250 - box:getContentSize().height/2));
    layer:addChild(box);
    label = cc.LabelTTF:create("Rotational Skew", "Marker Felt", 16);
    label:setPosition(cc.p(s.width/2, s.height - 250 + label:getContentSize().height/2));
    layer:addChild(label);
    local actionTo2 = cc.RotateBy:create(2, 360);
    local actionToBack2 = cc.RotateBy:create(2, -360);
    seq = cc.Sequence:create(actionTo2, actionToBack2)
    box:runAction(seq);

    Helper.subtitleLabel:setString("Skew Comparison")
    return layer;
end

--------------------------------------
-- ActionSkewRotate
--------------------------------------
local function ActionSkewRotate()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	tamara:removeFromParent(true)
    grossini:removeFromParent(true)
    kathia:removeFromParent(true)

    local boxSize = cc.size(100.0, 100.0)

    local box = cc.LayerColor:create(cc.c4b(255, 255, 0, 255))
    box:setAnchorPoint(cc.p(0, 0))
    box:setPosition(190, 110)
    box:setContentSize(boxSize)

	local markrside = 10.0
    local uL = cc.LayerColor:create(cc.c4b(255, 0, 0, 255))
    box:addChild(uL)
    uL:setContentSize(cc.size(markrside, markrside))
    uL:setPosition(0, boxSize.height - markrside)
    uL:setAnchorPoint(cc.p(0, 0))

    local uR = cc.LayerColor:create(cc.c4b(0, 0, 255, 255))
    box:addChild(uR)
    uR:setContentSize(cc.size(markrside, markrside))
    uR:setPosition(boxSize.width - markrside, boxSize.height - markrside)
    uR:setAnchorPoint(cc.p(0, 0))
    layer:addChild(box)

    local actionTo = cc.SkewTo:create(2, 0, 2)
    local rotateTo = cc.RotateTo:create(2, 61.0)
    local actionScaleTo = cc.ScaleTo:create(2, -0.44, 0.47)

    local actionScaleToBack = cc.ScaleTo:create(2, 1.0, 1.0)
    local rotateToBack = cc.RotateTo:create(2, 0)
    local actionToBack = cc.SkewTo:create(2, 0, 0)

    box:runAction(cc.Sequence:create(actionTo, actionToBack))
    box:runAction(cc.Sequence:create(rotateTo, rotateToBack))
    box:runAction(cc.Sequence:create(actionScaleTo, actionScaleToBack))

	Helper.subtitleLabel:setString("Skew + Rotate + Scale")
	return layer
end

--------------------------------------
-- ActionJump
--------------------------------------
local function ActionJump()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

    local actionTo = cc.JumpTo:create(2, cc.p(300,300), 50, 4)
    local actionBy = cc.JumpBy:create(2, cc.p(300,0), 50, 4)
    local actionUp = cc.JumpBy:create(2, cc.p(0,0), 80, 4)
    local actionByBack = actionBy:reverse()

    tamara:runAction(actionTo)
    grossini:runAction(cc.Sequence:create(actionBy, actionByBack))
    kathia:runAction(cc.RepeatForever:create(actionUp))

	Helper.subtitleLabel:setString("JumpTo / JumpBy")
	return layer
end

--------------------------------------
-- ActionCardinalSpline
--------------------------------------
local function ActionCardinalSpline()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)
    local array = {
           cc.p(0, 0),
           cc.p(size.width / 2 - 30, 0),
           cc.p(size.width / 2 - 30, size.height - 80),
           cc.p(0, size.height - 80),
           cc.p(0, 0),
    }
	local action = cc.CardinalSplineBy:create(3, array, 0)
	local reverse = action:reverse()
	local seq = cc.Sequence:create(action, reverse)

	tamara:setPosition(cc.p(50, 50))
	tamara:runAction(seq)

	local action2 = cc.CardinalSplineBy:create(3, array, 1)
	local reverse2 = action2:reverse()
	local seq2 = cc.Sequence:create(action2, reverse2)

	kathia:setPosition(cc.p(size.width / 2, 50))
	kathia:runAction(seq2)
--[[
    local function drawCardinalSpline()
        kmGLPushMatrix()
        kmGLTranslatef(50, 50, 0)
        cc.DrawPrimitives.drawCardinalSpline(array, 0, 100)
        kmGLPopMatrix()

        kmGLPushMatrix()
        kmGLTranslatef(size.width / 2, 50, 0)
        cc.DrawPrimitives.drawCardinalSpline(array, 1, 100)
        kmGLPopMatrix()
    end

    array:retain()
    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(size.width, size.height))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:registerScriptDrawHandler(drawCardinalSpline)
    layer:addChild(glNode,-10)
    glNode:setPosition( size.width / 2, size.height / 2)
]]--
	Helper.titleLabel:setString("CardinalSplineBy / CardinalSplineAt")
	Helper.subtitleLabel:setString("Cardinal Spline paths.\nTesting different tensions for one array")
	return layer
end

--------------------------------------
-- ActionCatmullRom
--------------------------------------
local function ActionCatmullRom()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

	tamara:setPosition(cc.p(50, 50))
    local array = {
           cc.p(0, 0),
           cc.p(80, 80),
           cc.p(size.width - 80, 80),
           cc.p(size.width - 80, size.height - 80),
           cc.p(80, size.height - 80),
           cc.p(80, 80),
           cc.p(size.width / 2, size.height / 2),
    }

    local action = cc.CatmullRomBy:create(3, array)
    local reverse = action:reverse()
    local seq = cc.Sequence:create(action, reverse)
	tamara:runAction(seq)

    local array2 = {
           cc.p(size.width / 2, 30),
           cc.p(size.width  -80, 30),
           cc.p(size.width - 80, size.height - 80),
           cc.p(size.width / 2, size.height - 80),
           cc.p(size.width / 2, 30),
    }

    local action2 = cc.CatmullRomTo:create(3, array2)
    local reverse2 = action2:reverse()
    local seq2 = cc.Sequence:create(action2, reverse2)
    kathia:runAction(seq2)
--[[
    local function drawCatmullRom()
        kmGLPushMatrix()
        kmGLTranslatef(50, 50, 0)
        cc.DrawPrimitives.drawCatmullRom(array, 50)
        kmGLPopMatrix()

        cc.DrawPrimitives.drawCatmullRom(array2,50)
    end

    array:retain()
    array2:retain()
    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(size.width, size.height))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:registerScriptDrawHandler(drawCatmullRom)
    layer:addChild(glNode,-10)
    glNode:setPosition( size.width / 2, size.height / 2)
    ]]--

    Helper.titleLabel:setString("CatmullRomBy / CatmullRomTo")
    Helper.subtitleLabel:setString("Catmull Rom spline paths. Testing reverse too")
	return layer
end

--------------------------------------
-- ActionBezier
--------------------------------------
local function ActionBezier()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

	-- sprite 1
    --[[
    local bezier = ccBezierConfig()
    bezier.controlPoint_1 = cc.p(0, size.height / 2)
    bezier.controlPoint_2 = cc.p(300, - size.height / 2)
    bezier.endPosition = cc.p(300, 100)
    ]]--
    local bezier = {
        cc.p(0, size.height / 2),
        cc.p(300, - size.height / 2),
        cc.p(300, 100),
    }
    local bezierForward = cc.BezierBy:create(3, bezier)
    local bezierBack = bezierForward:reverse()
    local rep = cc.RepeatForever:create(cc.Sequence:create(bezierForward, bezierBack))

    -- sprite 2
    tamara:setPosition(cc.p(80,160))
    --[[
    local bezier2 = ccBezierConfig()
    bezier2.controlPoint_1 = cc.p(100, size.height / 2)
    bezier2.controlPoint_2 = cc.p(200, - size.height / 2)
    bezier2.endPosition = cc.p(240, 160)
    ]]--
    local bezier2 ={
        cc.p(100, size.height / 2),
        cc.p(200, - size.height / 2),
        cc.p(240, 160)
    }

    local bezierTo1 = cc.BezierTo:create(2, bezier2)

    -- sprite 3
    kathia:setPosition(cc.p(400,160))
    local bezierTo2 = cc.BezierTo:create(2, bezier2)

    grossini:runAction(rep)
    tamara:runAction(bezierTo1)
    kathia:runAction(bezierTo2)

	Helper.subtitleLabel:setString("BezierTo / BezierBy")
	return layer
end

--------------------------------------
-- ActionBlink
--------------------------------------
local function ActionBlink()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

	local action1 = cc.Blink:create(2, 10)
    local action2 = cc.Blink:create(2, 5)

    tamara:runAction(action1)
    kathia:runAction(action2)

	Helper.subtitleLabel:setString("Blink")

	return layer
end

--------------------------------------
-- ActionFade
--------------------------------------
local function ActionFade()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

	tamara:setOpacity(0)
    local action1 = cc.FadeIn:create(1)
    local action1Back = action1:reverse()

    local action2 = cc.FadeOut:create(1)
    local action2Back = action2:reverse()

    tamara:runAction(cc.Sequence:create( action1, action1Back))
    kathia:runAction(cc.Sequence:create( action2, action2Back))

	Helper.subtitleLabel:setString("FadeIn / FadeOut")

	return layer
end

--------------------------------------
-- ActionTint
--------------------------------------
local function ActionTint()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

    local action1 = cc.TintTo:create(2, 255, 0, 255)
    local action2 = cc.TintBy:create(2, -127, -255, -127)
    local action2Back = action2:reverse()

    tamara:runAction(action1)
    kathia:runAction(cc.Sequence:create(action2, action2Back))

	Helper.subtitleLabel:setString("TintTo / TintBy")

	return layer
end

--------------------------------------
-- ActionAnimate
--------------------------------------
local function ActionAnimate()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

    local animation = cc.Animation:create()
	local number, name
    for i = 1, 14 do
		if i < 10 then
			number = "0"..i
		else
			number = i
		end
        name = "Images/grossini_dance_"..number..".png"
        animation:addSpriteFrameWithFile(name)
    end
    -- should last 2.8 seconds. And there are 14 frames.
    animation:setDelayPerUnit(2.8 / 14.0)
    animation:setRestoreOriginalFrame(true)

    local action = cc.Animate:create(animation)
    grossini:runAction(cc.Sequence:create(action, action:reverse()))

    local cache = cc.AnimationCache:getInstance()
    cache:addAnimations("animations/animations-2.plist")
    local animation2 = cache:getAnimation("dance_1")

    local action2 = cc.Animate:create(animation2)
    tamara:runAction(cc.Sequence:create(action2, action2:reverse()))

	local animation3 = animation2:clone()
	-- problem
    tolua.cast(animation3,"cc.Animation"):setLoops(4)

    local action3 = cc.Animate:create(animation3)
    kathia:runAction(action3)

	Helper.titleLabel:setString("Animation")
	Helper.subtitleLabel:setString("Center: Manual animation. Border: using file format animation")

	return layer
end

--------------------------------------
-- ActionSequence
--------------------------------------
local function ActionSequence()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local action = cc.Sequence:create(
        cc.MoveBy:create(2, cc.p(240,0)),
        cc.RotateBy:create(2, 540))

    grossini:runAction(action)

	Helper.subtitleLabel:setString("Sequence: Move + Rotate")

	return layer
end

--------------------------------------
-- ActionSequence2
--------------------------------------
local actionSequenceLayer = nil

local function ActionSequenceCallback1()
	local label = cc.LabelTTF:create("callback 1 called", "Marker Felt", 16)
    label:setPosition(size.width / 4, size.height / 2)

    actionSequenceLayer:addChild(label)
end

local function ActionSequenceCallback2(sender)
	local label = cc.LabelTTF:create("callback 2 called", "Marker Felt", 16)
    label:setPosition(cc.p(size.width / 4 * 2, size.height / 2))

    actionSequenceLayer:addChild(label)
end

local function ActionSequenceCallback3(sender)
	local label = cc.LabelTTF:create("callback 3 called", "Marker Felt", 16)
    label:setPosition(cc.p(size.width / 4 * 3, size.height / 2))

    actionSequenceLayer:addChild(label)
end

local function ActionSequence2()
    actionSequenceLayer = cc.Layer:create()
    initWithLayer(actionSequenceLayer)

    alignSpritesLeft(1)

    grossini:setVisible(false)
    local action = cc.Sequence:create(cc.Place:create(cc.p(200,200)),cc.Show:create(),cc.MoveBy:create(1, cc.p(100,0)), cc.CallFunc:create(ActionSequenceCallback1),cc.CallFunc:create(ActionSequenceCallback2),cc.CallFunc:create(ActionSequenceCallback3))

    grossini:runAction(action)

    Helper.subtitleLabel:setString("Sequence of InstantActions")
    return actionSequenceLayer
end

--------------------------------------
-- ActionSpawn
--------------------------------------
local function ActionSpawn()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local action = cc.Spawn:create(
		cc.JumpBy:create(2, cc.p(300,0), 50, 4),
		cc.RotateBy:create( 2,  720))

    grossini:runAction(action)

	Helper.subtitleLabel:setString("Spawn: Jump + Rotate")

	return layer
end

--------------------------------------
-- ActionReverse
--------------------------------------
local function ActionReverse()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local jump = cc.JumpBy:create(2, cc.p(300,0), 50, 4)
    local action = cc.Sequence:create(jump, jump:reverse())

    grossini:runAction(action)

	Helper.subtitleLabel:setString("Reverse an action")

	return layer
end

--------------------------------------
-- ActionDelaytime
--------------------------------------
local function ActionDelaytime()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local move = cc.MoveBy:create(1, cc.p(150,0))
	local action = cc.Sequence:create(move, cc.DelayTime:create(2), move)

    grossini:runAction(action)

	Helper.subtitleLabel:setString("DelayTime: m + delay + m")
	return layer
end

--------------------------------------
-- ActionRepeat
--------------------------------------
local function ActionRepeat()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(2)

    local a1 = cc.MoveBy:create(1, cc.p(150,0))
    local action1 = cc.Repeat:create(cc.Sequence:create(cc.Place:create(cc.p(60,60)), a1), 3)

    local a2 = cc.MoveBy:create(1, cc.p(150,0))
    local action2 = cc.RepeatForever:create(cc.Sequence:create(a2, a1:reverse()))

    kathia:runAction(action1)
    tamara:runAction(action2)

	Helper.subtitleLabel:setString("Repeat / RepeatForever actions")
	return layer
end

--------------------------------------
-- ActionRepeatForever
--------------------------------------
local function repeatForever(sender)
	local repeatAction = cc.RepeatForever:create(cc.RotateBy:create(1.0, 360))

    sender:runAction(repeatAction)
end

local function ActionRepeatForever()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(1)

    local action = cc.Sequence:create(
        cc.DelayTime:create(1),
        cc.CallFunc:create(repeatForever) )

    grossini:runAction(action)

	Helper.subtitleLabel:setString("CallFuncN + RepeatForever")
	return layer
end

--------------------------------------
-- ActionRotateToRepeat
--------------------------------------
local function ActionRotateToRepeat()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

    local act1 = cc.RotateTo:create(1, 90)
    local act2 = cc.RotateTo:create(1, 0)
    local seq  = cc.Sequence:create(act1, act2)
    local rep1 = cc.RepeatForever:create(seq)
    local rep2 = cc.Repeat:create(tolua.cast(seq:clone(), "cc.Sequence"), 10)

    tamara:runAction(rep1)
    kathia:runAction(rep2)

	Helper.subtitleLabel:setString("Repeat/RepeatForever + RotateTo")

	return layer
end

--------------------------------------
-- ActionRotateJerk
--------------------------------------
local function ActionRotateJerk()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

    local seq = cc.Sequence:create(
        cc.RotateTo:create(0.5, -20),
        cc.RotateTo:create(0.5, 20))

    local rep1 = cc.Repeat:create(seq, 10)

    local seq2 = cc.Sequence:create(
        cc.RotateTo:create(0.5, -20),
        cc.RotateTo:create(0.5, 20))

    local rep2 = cc.RepeatForever:create(seq2)

    tamara:runAction(rep1)
    kathia:runAction(rep2)

	Helper.subtitleLabel:setString("RepeatForever / Repeat + Rotate")
	return layer
end

--------------------------------------
-- ActionCallFunc
--------------------------------------
local callFuncLayer = nil

local function CallFucnCallback1()
	local label = cc.LabelTTF:create("callback 1 called", "Marker Felt", 16)
    label:setPosition(size.width / 4, size.height / 2)

    callFuncLayer:addChild(label)
end

local function CallFucnCallback2(sender)
	local label = cc.LabelTTF:create("callback 2 called", "Marker Felt", 16)
    label:setPosition(size.width / 4 * 2, size.height / 2)

    callFuncLayer:addChild(label)
end

local function CallFucnCallback3(sender)
	local label = cc.LabelTTF:create("callback 3 called", "Marker Felt", 16)
    label:setPosition(size.width / 4 * 3, size.height / 2)

    callFuncLayer:addChild(label)
end

local function ActionCallFunc()
	callFuncLayer = cc.Layer:create()
	initWithLayer(callFuncLayer)

	centerSprites(3)

	local action = cc.Sequence:create(
        cc.MoveBy:create(2, cc.p(200,0)),
        cc.CallFunc:create(CallFucnCallback1) )
    local action2 = cc.Sequence:create(cc.ScaleBy:create(2, 2),cc.FadeOut:create(2),cc.CallFunc:create(CallFucnCallback2))
    local action3 = cc.Sequence:create(cc.RotateBy:create(3 , 360),cc.FadeOut:create(2),cc.CallFunc:create(CallFucnCallback3))

    grossini:runAction(action)
	tamara:runAction(action2)
    kathia:runAction(action3)

	Helper.subtitleLabel:setString("Callbacks: CallFunc and friends")
	return callFuncLayer
end

--------------------------------------
-- ActionCallFuncND *
--   problem: the current luaEngine doesn't support
--   passing more than one param to lua script
--------------------------------------
local function ActionCallFuncND()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(1)

    local function doRemoveFromParentAndCleanup(sender,table)
        grossini:removeFromParentAndCleanup(table[1])
    end

    local action = cc.Sequence:create(
        cc.MoveBy:create(2, cc.p(200,0)),
        cc.CallFunc:create(doRemoveFromParentAndCleanup,{true}))

    grossini:runAction(action)

	Helper.titleLabel:setString("CallFuncND + auto remove")
	Helper.subtitleLabel:setString("CallFuncND + removeFromParent. Grossini dissapears in 2s")
	return layer
end

--------------------------------------
-- ActionReverseSequence
--------------------------------------
local function ActionReverseSequence()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local move1  = cc.MoveBy:create(1, cc.p(250,0))
    local move2  = cc.MoveBy:create(1, cc.p(0,50))
    local seq    = cc.Sequence:create(move1, move2, move1:reverse())
    local action = cc.Sequence:create(seq, seq:reverse())

    grossini:runAction(action)

	Helper.subtitleLabel:setString("Reverse a sequence")
	return layer
end

--------------------------------------
-- ActionReverseSequence2
--------------------------------------
local function ActionReverseSequence2()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	alignSpritesLeft(2)

	-- Test:
    -- Sequence should work both with IntervalAction and InstantActions
	local move1  = cc.MoveBy:create(1, cc.p(250,0))
    local move2  = cc.MoveBy:create(1, cc.p(0,50))
	local tog1 = cc.ToggleVisibility:create()
    local tog2 = cc.ToggleVisibility:create()
    local seq = cc.Sequence:create(move1, tog1, move2, tog2, move1:reverse())
    local action = cc.Repeat:create(cc.Sequence:create(seq, seq:reverse()), 3)

    -- Test:
    -- Also test that the reverse of Hide is Show, and vice-versa
    kathia:runAction(action)

    local move_tamara = cc.MoveBy:create(1, cc.p(100,0))
    local move_tamara2 = cc.MoveBy:create(1, cc.p(50,0))
    local hide = cc.Hide:create()

    local seq_tamara = cc.Sequence:create(move_tamara, hide, move_tamara2)
    local seq_back = seq_tamara:reverse()
    tamara:runAction(cc.Sequence:create(seq_tamara, seq_back))

	Helper.subtitleLabel:setString("Reverse a sequence2")
	return layer
end

--------------------------------------
-- ActionOrbit
--------------------------------------
local function ActionOrbit()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(3)

	local orbit1 = cc.OrbitCamera:create(2,1, 0, 0, 180, 0, 0)
    local action1 = cc.Sequence:create(orbit1, orbit1:reverse())

    local orbit2 = cc.OrbitCamera:create(2,1, 0, 0, 180, -45, 0)
    local action2 = cc.Sequence:create(orbit2, orbit2:reverse())

    local orbit3 = cc.OrbitCamera:create(2,1, 0, 0, 180, 90, 0)
    local action3 = cc.Sequence:create(orbit3, orbit3:reverse())

    kathia:runAction(cc.RepeatForever:create(action1))
    tamara:runAction(cc.RepeatForever:create(action2))
    grossini:runAction(cc.RepeatForever:create(action3))

    local move = cc.MoveBy:create(3, cc.p(100,-100))
    local move_back = move:reverse()
    local seq = cc.Sequence:create(move, move_back)
    local rfe = cc.RepeatForever:create(seq)
    kathia:runAction(rfe)
    tamara:runAction(tolua.cast(rfe:clone(), "cc.ActionInterval"))
    grossini:runAction(tolua.cast(rfe:clone(), "cc.ActionInterval"))


	Helper.subtitleLabel:setString("OrbitCamera action")
	return layer
end

--------------------------------------
-- ActionFollow
--------------------------------------
local function ActionFollow()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(1)

	grossini:setPosition(cc.p(-200, size.height / 2))
    local move = cc.MoveBy:create(2, cc.p(size.width * 3, 0))
    local move_back = move:reverse()
    local seq = cc.Sequence:create(move, move_back)
    local rep = cc.RepeatForever:create(seq)

    grossini:runAction(rep)

    layer:runAction(cc.Follow:create(grossini, cc.rect(0, 0, size.width * 2 - 100, size.height)))

    local function draw()
        local winSize = cc.Director:getInstance():getWinSize()
        local x = winSize.width * 2 - 100
        local y = winSize.height
        local vertices = { cc.p(5, 5), cc.p(x - 5, 5), cc.p(x - 5,y - 5), cc.p(5,y - 5) }
        cc.DrawPrimitives.drawPoly(vertices, 4, true)
    end

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(size.width, size.height))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:registerScriptDrawHandler(draw)
    layer:addChild(glNode,-10)
    glNode:setPosition( size.width / 2, size.height / 2)

	Helper.subtitleLabel:setString("Follow action")
	return layer
end

--------------------------------------
-- ActionTargeted
--------------------------------------
local function ActionTargeted()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

	local jump1 = cc.JumpBy:create(2, cc.p(0, 0), 100, 3)
    local jump2 = cc.JumpBy:create(2, cc.p(0, 0), 100, 3)
    local rot1  = cc.RotateBy:create(1, 360)
    local rot2  = cc.RotateBy:create(1, 360)

    local t1 = cc.TargetedAction:create(kathia, jump2)
    local t2 = cc.TargetedAction:create(kathia, rot2)
    local seq = cc.Sequence:create(jump1, t1, rot1, t2)
    local always = cc.RepeatForever:create(seq)

    tamara:runAction(always)

	Helper.titleLabel:setString("ActionTargeted")
	Helper.subtitleLabel:setString("Action that runs on another target. Useful for sequences")
	return layer
end

--------------------------------------
-- PauseResumeActions *
--   problem: schedule feature is constructing
--------------------------------------
local pausedTargets = nil
local PauseResumeActions_pauseEntry = nil
local PauseResumeActions_resumeEntry = nil

local function ActionPause(dt)
	cclog("Pausing")

	local scheduler = cc.Director:getInstance():getScheduler()
	scheduler:unscheduleScriptEntry(PauseResumeActions_pauseEntry)

	local director = cc.Director:getInstance()
    pausedTargets = director:getActionManager():pauseAllRunningActions()
end

local function ActionResume(dt)
	cclog("Resuming")

	local scheduler = cc.Director:getInstance():getScheduler()
	scheduler:unscheduleScriptEntry(PauseResumeActions_resumeEntry)

	local director = cc.Director:getInstance()
	if pausedTargets ~= nil then
		-- problem: will crash here. Try fixing me!
		director:getActionManager():resumeTargets(pausedTargets)
	end
end

local function PauseResumeActions_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		PauseResumeActions_pauseEntry = scheduler:scheduleScriptFunc(ActionPause, 3, false)
		PauseResumeActions_resumeEntry = scheduler:scheduleScriptFunc(ActionResume, 5, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(PauseResumeActions_pauseEntry)
		scheduler:unscheduleScriptEntry(PauseResumeActions_resumeEntry)
	end
end

local function PauseResumeActions()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(2)

    tamara:runAction(cc.RepeatForever:create(cc.RotateBy:create(3, 360)))
    kathia:runAction(cc.RepeatForever:create(cc.RotateBy:create(3, 360)))

	layer:registerScriptHandler(PauseResumeActions_onEnterOrExit)

	Helper.titleLabel:setString("PauseResumeActions")
	Helper.subtitleLabel:setString("All actions pause at 3s and resume at 5s")
	return layer
end

--------------------------------------
-- ActionIssue1305
--------------------------------------
local spriteTmp = nil
local Issue1305_entry = nil
local Issue1305_layer = nil

local function Issue1305_log(sender)
	cclog("This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE")
end

local function addSprite(dt)
	local scheduler = cc.Director:getInstance():getScheduler()
	scheduler:unscheduleScriptEntry(Issue1305_entry)

	spriteTmp:setPosition(cc.p(250, 250))
    Issue1305_layer:addChild(spriteTmp)
end

local function Issue1305_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		Issue1305_entry = scheduler:scheduleScriptFunc(addSprite, 2, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Issue1305_entry)
	end
end

local function ActionIssue1305()
	Issue1305_layer = cc.Layer:create()
	initWithLayer(Issue1305_layer)

	centerSprites(0)

    spriteTmp = cc.Sprite:create("Images/grossini.png")
    spriteTmp:runAction(cc.CallFunc:create(Issue1305_log))

    Issue1305_layer:registerScriptHandler(Issue1305_onEnterOrExit)

	Helper.titleLabel:setString("Issue 1305")
	Helper.subtitleLabel:setString("In two seconds you should see a message on the console. NOT BEFORE.")
	return Issue1305_layer
end

--------------------------------------
-- ActionIssue1305_2
--------------------------------------
local function Issue1305_2_log1()
    cclog("1st block")
end

local function Issue1305_2_log2()
    cclog("2nd block")
end

local function Issue1305_2_log3()
    cclog("3rd block")
end

local function Issue1305_2_log4()
    cclog("4th block")
end

local function ActionIssue1305_2()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = cc.Sprite:create("Images/grossini.png")
    spr:setPosition(cc.p(200,200))
    layer:addChild(spr)

    local act1 = cc.MoveBy:create(2 ,cc.p(0, 100))
    local act2 = cc.CallFunc:create(Issue1305_2_log1)
    local act3 = cc.MoveBy:create(2, cc.p(0, -100))
    local act4 = cc.CallFunc:create(Issue1305_2_log2)
    local act5 = cc.MoveBy:create(2, cc.p(100, -100))
    local act6 = cc.CallFunc:create(Issue1305_2_log3)
    local act7 = cc.MoveBy:create(2, cc.p(-100, 0))
    local act8 = cc.CallFunc:create(Issue1305_2_log4)
    local actF = cc.Sequence:create(act1, act2, act3, act4, act5, act6, act7, act8)

    cc.Director:getInstance():getActionManager():addAction(actF ,spr, false)

	Helper.titleLabel:setString("Issue 1305 #2")
	Helper.subtitleLabel:setString("See console. You should only see one message for each block")
	return layer
end

--------------------------------------
-- ActionIssue1288
--------------------------------------
local function ActionIssue1288()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = cc.Sprite:create("Images/grossini.png")
    spr:setPosition(cc.p(100, 100))
    layer:addChild(spr)

    local act1 = cc.MoveBy:create(0.5, cc.p(100, 0))
    local act2 = act1:reverse()
    local act3 = cc.Sequence:create(act1, act2)
    local act4 = cc.Repeat:create(act3, 2)

    spr:runAction(act4)

	Helper.titleLabel:setString("Issue 1288")
	Helper.subtitleLabel:setString("Sprite should end at the position where it started.")
	return layer
end

--------------------------------------
-- ActionIssue1288_2
--------------------------------------
local function ActionIssue1288_2()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = cc.Sprite:create("Images/grossini.png")
    spr:setPosition(cc.p(100, 100))
    layer:addChild(spr)

    local act1 = cc.MoveBy:create(0.5, cc.p(100, 0))
    spr:runAction(cc.Repeat:create(act1, 1))

	Helper.titleLabel:setString("Issue 1288 #2")
	Helper.subtitleLabel:setString("Sprite should move 100 pixels, and stay there")
	return layer
end

--------------------------------------
-- ActionIssue1327
--------------------------------------
local function logSprRotation(sender)
	cclog(""..sender:getRotation())
end

local function ActionIssue1327()
	local layer = cc.Layer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = cc.Sprite:create("Images/grossini.png")
    spr:setPosition(cc.p(100, 100))
    layer:addChild(spr)

    local act1 = cc.CallFunc:create(logSprRotation)
    local act2 = cc.RotateBy:create(0.25, 45)
    local act3 = cc.CallFunc:create(logSprRotation)
    local act4 = cc.RotateBy:create(0.25, 45)
    local act5 = cc.CallFunc:create(logSprRotation)
    local act6 = cc.RotateBy:create(0.25, 45)
    local act7 = cc.CallFunc:create(logSprRotation)
    local act8 = cc.RotateBy:create(0.25, 45)
    local act9 = cc.CallFunc:create(logSprRotation)
    spr:runAction(cc.Sequence:create(act1, act2, act3, act4, act5, act6, act7,act8, act9))

	Helper.titleLabel:setString("Issue 1327")
	Helper.subtitleLabel:setString("See console: You should see: 0, 45, 90, 135, 180")
	return layer
end

function ActionsTest()
	cclog("ActionsTest")
	local scene = cc.Scene:create()

	Helper.createFunctionTable = {
		ActionManual,
		ActionMove,
		ActionScale,
		ActionRotate,
		ActionSkew,
        ActionRotationalSkewVSStandardSkew,
		ActionSkewRotate,
		ActionJump,
		ActionCardinalSpline,
		ActionCatmullRom,
		ActionBezier,
		ActionBlink,
		ActionFade,
        ActionTint,
		ActionAnimate,
        ActionSequence,
		ActionSequence2,
		ActionSpawn,
        ActionReverse,
        ActionDelaytime,
        ActionRepeat,
        ActionRepeatForever,
        ActionRotateToRepeat,
        ActionRotateJerk,
        ActionCallFunc,
        ActionCallFuncND,
        ActionReverseSequence,
        ActionReverseSequence2,
		ActionOrbit,
		ActionFollow,    
		ActionTargeted,
		PauseResumeActions,    
		ActionIssue1305,    
		ActionIssue1305_2,    
		ActionIssue1288,   
		ActionIssue1288_2,  
		ActionIssue1327
    }

	scene:addChild(ActionManual())
	scene:addChild(CreateBackMenuItem())

	return scene
end
