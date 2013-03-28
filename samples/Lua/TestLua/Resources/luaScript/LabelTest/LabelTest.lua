local size = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()

local kTagTileMap = 1
local kTagSpriteManager = 1
local kTagAnimation1 = 1
local kTagBitmapAtlas1 = 1
local kTagBitmapAtlas2 = 2
local kTagBitmapAtlas3 = 3
local kTagSprite1 = 0
local kTagSprite2 = 1
local kTagSprite3 = 2
local kTagSprite4 = 3
local kTagSprite5 = 4
local kTagSprite6 = 5
local kTagSprite7 = 6
local kTagSprite8 = 7

--------------------------------------------------------------------
--
-- LabelAtlasTest
--
--------------------------------------------------------------------

local LabelAtlasTest = {}
LabelAtlasTest.layer = nil
LabelAtlasTest.__index = LabelAtlasTest
local m_time = 0

function LabelAtlasTest.step(dt)
	m_time = m_time + dt
	local string = string.format("%2.2f Test", m_time)

	local label1_origin = LabelAtlasTest.layer:getChildByTag(kTagSprite1)
	local label1 = tolua.cast(label1_origin, "CCLabelAtlas")
	label1:setString(string)	--

	local label2_origin = LabelAtlasTest.layer:getChildByTag(kTagSprite2)
	local label2 = tolua.cast(label2_origin, "CCLabelAtlas")
	string = string.format("%d", m_time)

	label2:setString(string)
end

function LabelAtlasTest.onNodeEvent(tag)
   if tag == "exit" then
	  LabelAtlasTest.layer:unscheduleUpdate()
   end
end

function LabelAtlasTest.create()
    m_time = 0
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	LabelAtlasTest.layer = layer

	local label1 = CCLabelAtlas:create("123 Test", "fonts/tuffy_bold_italic-charmap.plist")
	layer:addChild(label1, 0, kTagSprite1)
	label1:setPosition( ccp(10,100) )
	label1:setOpacity( 200 )

	local label2 = CCLabelAtlas:create("0123456789", "fonts/tuffy_bold_italic-charmap.plist")
	layer:addChild(label2, 0, kTagSprite2)
	label2:setPosition( ccp(10,200) )
	label2:setOpacity( 32 )

	layer:scheduleUpdateWithPriorityLua(LabelAtlasTest.step, 0)

	Helper.titleLabel:setString("LabelAtlas")
	Helper.subtitleLabel:setString("Updating label should be fast")

	layer:registerScriptHandler(LabelAtlasTest.onNodeEvent)
	return layer
end

--------------------------------------------------------------------
--
-- LabelAtlasColorTest
--
--------------------------------------------------------------------

local LabelAtlasColorTest = {}
LabelAtlasColorTest.layer = nil
LabelAtlasColorTest.__index = LabelAtlasColorTest
local m_time = 0

function LabelAtlasColorTest.step(dt)
	m_time = m_time + dt
	local string = string.format("%2.2f Test", m_time)
	local label1_origin = LabelAtlasColorTest.layer:getChildByTag(kTagSprite1)
	local label1 = tolua.cast(label1_origin, "CCLabelAtlas")
	label1:setString(string)

	local label2_origin = LabelAtlasColorTest.layer:getChildByTag(kTagSprite2)
	local label2 = tolua.cast(label2_origin, "CCLabelAtlas")
	string = string.format("%d", m_time)

	label2:setString(string)
end

function LabelAtlasColorTest.actionFinishCallback()
   cclog("Action finished")
end

function LabelAtlasColorTest.onNodeEvent(tag)
   if tag == "exit" then
	  LabelAtlasColorTest.layer:unscheduleUpdate()
   end
end

function LabelAtlasColorTest.create()
    m_time = 0
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	LabelAtlasColorTest.layer = layer

	local label1 = CCLabelAtlas:create("123 Test", "fonts/tuffy_bold_italic-charmap.plist")
	layer:addChild(label1, 0, kTagSprite1)
	label1:setPosition( ccp(10,100) )
	label1:setOpacity( 200 )

	local label2 = CCLabelAtlas:create("0123456789", "fonts/tuffy_bold_italic-charmap.plist")
	layer:addChild(label2, 0, kTagSprite2)
	label2:setPosition( ccp(10,200) )
	label2:setColor(ccc3(255, 0, 0))

	local fade = CCFadeOut:create(1.0)
	local fade_in = fade:reverse()

    local cb = CCCallFunc:create(LabelAtlasColorTest.actionFinishCallback)
	local actionArr = CCArray:create()
	actionArr:addObject(fade)
	actionArr:addObject(fade_in)
	actionArr:addObject(cb)

    local seq = CCSequence:create(actionArr)
    local repeatAction = CCRepeatForever:create( seq )
    label2:runAction( repeatAction )

	layer:registerScriptHandler(LabelAtlasColorTest.onNodeEvent)
	layer:scheduleUpdateWithPriorityLua(LabelAtlasColorTest.step, 0)

	Helper.titleLabel:setString("LabelAtlas")
	Helper.subtitleLabel:setString("Opacity + Color should work at the same time")

	return layer
end

--------------------------------------------------------------------
--
-- Atlas3
--
-- Use any of these editors to generate BMFonts:
-- 	 http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
-- 	 http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
-- 	 http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
-- 	 http://www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------
local Atlas3 = {}
Atlas3.layer = nil
Atlas3.__index = Atlas3

function Atlas3.onNodeEvent(tag)
   if tag == "exit" then
	  Atlas3.layer:unscheduleUpdate()
   end
end

function Atlas3.create()
    cclog("Atlas3.create")
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	Atlas3.layer = layer

    m_time = 0

    local col = CCLayerColor:create( ccc4(128,128,128,255) )
    layer:addChild(col, -10)

    local label1 = CCLabelBMFont:create("Test",  "fonts/bitmapFontTest2.fnt")

    -- testing anchors
    label1:setAnchorPoint( ccp(0,0) )
    layer:addChild(label1, 0, kTagBitmapAtlas1)

	local fade = CCFadeOut:create(1.0)
    local fade_in = fade:reverse()

	local actionArr = CCArray:create()
	actionArr:addObject(fade)
	actionArr:addObject(fade_in)
	local seq = CCSequence:create(actionArr)
    local repeatAction = CCRepeatForever:create(seq)
    label1:runAction(repeatAction)

    --VERY IMPORTANT
    --color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
    --If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
    --Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
    local label2 = CCLabelBMFont:create("Test", "fonts/bitmapFontTest2.fnt")

    -- testing anchors
    label2:setAnchorPoint( ccp(0.5, 0.5) )
    label2:setColor(ccc3(255, 0, 0 ))
	layer:addChild(label2, 0, kTagBitmapAtlas2)

    label2:runAction( tolua.cast(repeatAction:copy():autorelease(), "CCAction") )

    local label3 = CCLabelBMFont:create("Test", "fonts/bitmapFontTest2.fnt")
    -- testing anchors
    label3:setAnchorPoint( ccp(1,1) )
    layer:addChild(label3, 0, kTagBitmapAtlas3)

    label1:setPosition( VisibleRect:leftBottom() )
    label2:setPosition( VisibleRect:center() )
    label3:setPosition( VisibleRect:rightTop() )

	layer:registerScriptHandler(Atlas3.onNodeEvent)
    layer:scheduleUpdateWithPriorityLua(Atlas3.step, 0)

	Helper.titleLabel:setString( "CCLabelBMFont" )
	Helper.subtitleLabel:setString( "Testing alignment. Testing opacity + tint" )

	return layer
end

function Atlas3.step(dt)
	m_time = m_time + dt
	local string = string.format("%2.2f Test j", m_time)

	local label1 = tolua.cast(Atlas3.layer:getChildByTag(kTagBitmapAtlas1), "CCLabelBMFont")
	label1:setString(string)

	local label2 = tolua.cast(Atlas3.layer:getChildByTag(kTagBitmapAtlas2), "CCLabelBMFont")
	label2:setString(string)

	local label3 = tolua.cast(Atlas3.layer:getChildByTag(kTagBitmapAtlas3), "CCLabelBMFont")
	label3:setString(string)
end

--------------------------------------------------------------------
--
-- Atlas4
--
-- Use any of these editors to generate BMFonts:
--     http:--glyphdesigner.71squared.com/ (Commercial, Mac OS X)
--     http:--www.n4te.com/hiero/hiero.jnlp (Free, Java)
--     http:--slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
--     http:--www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------
local Atlas4 = {}
Atlas4.layer = nil
Atlas4.__index = Atlas4
Atlas4.stepEntry = nil

function Atlas4.onNodeEvent(tag)
   if tag == "enter" then
	  Atlas4.stepEntry = scheduler:scheduleScriptFunc(Atlas4.step, 0.1, false)
   elseif tag == "exit" then
	  scheduler:unscheduleScriptEntry(Atlas4.stepEntry)
   end
end

function Atlas4.create()
   cclog("Atlas4.create")
    m_time = 0
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	Atlas4.layer = layer

    -- Upper Label
    local label = CCLabelBMFont:create("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt")
    layer:addChild(label)

    local s = CCDirector:sharedDirector():getWinSize()

    label:setPosition( ccp(s.width/2, s.height/2) )
    label:setAnchorPoint( ccp(0.5, 0.5) )


    local BChar = label:getChildByTag(0)
    local FChar = label:getChildByTag(7)
    local AChar = label:getChildByTag(12)


    local rotate = CCRotateBy:create(2, 360)
    local rot_4ever = CCRepeatForever:create(rotate)

    local scale = CCScaleBy:create(2, 1.5)
    local scale_back = scale:reverse()
	local action_arr = CCArray:create()
	action_arr:addObject(scale)
	action_arr:addObject(scale_back)

    local scale_seq = CCSequence:create(action_arr)
    local scale_4ever = CCRepeatForever:create(scale_seq)

    local jump = CCJumpBy:create(0.5, ccp(0, 0), 60, 1)
    local jump_4ever = CCRepeatForever:create(jump)

    local fade_out = CCFadeOut:create(1)
    local fade_in = CCFadeIn:create(1)

	local action_arr2 = CCArray:create()
	action_arr2:addObject(fade_out)
	action_arr2:addObject(fade_in)
    local seq = CCSequence:create(action_arr2)
    local fade_4ever = CCRepeatForever:create(seq)

    BChar:runAction(rot_4ever)
    BChar:runAction(scale_4ever)
    FChar:runAction(jump_4ever)
    AChar:runAction(fade_4ever)


    -- Bottom Label
    local label2 = CCLabelBMFont:create("00.0", "fonts/bitmapFontTest.fnt")
    layer:addChild(label2, 0, kTagBitmapAtlas2)
    label2:setPosition( ccp(s.width/2.0, 80) )

    local lastChar = label2:getChildByTag(3)
    lastChar:runAction(tolua.cast( rot_4ever:copy():autorelease(), "CCAction" ))

	layer:registerScriptHandler(Atlas4.onNodeEvent)

	Helper.titleLabel:setString("CCLabelBMFont")
	Helper.subtitleLabel:setString( "Using fonts as CCSprite objects. Some characters should rotate.")
	return layer
end

function Atlas4.draw()
    local s = CCDirector:sharedDirector():getWinSize()
    ccDrawLine( ccp(0, s.height/2), ccp(s.width, s.height/2) )
    ccDrawLine( ccp(s.width/2, 0), ccp(s.width/2, s.height) )
end

function Atlas4.step(dt)
    m_time = m_time + dt

	local string = string.format("%04.1f", m_time)

    local label1 = tolua.cast(Atlas4.layer:getChildByTag(kTagBitmapAtlas2), "CCLabelBMFont")
    label1:setString(string)
end


--------------------------------------------------------------------
--
-- Atlas5
--
-- Use any of these editors to generate BMFonts:
--	   http:--glyphdesigner.71squared.com/ (Commercial, Mac OS X)
--	   http:--www.n4te.com/hiero/hiero.jnlp (Free, Java)
--	   http:--slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
--	   http:--www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------

local Atlas5 = {}
Atlas5.layer = nil
function Atlas5:create()
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	Atlas5.layer = layer

	local label = CCLabelBMFont:create("abcdefg", "fonts/bitmapFontTest4.fnt")
	layer:addChild(label)

	local s = CCDirector:sharedDirector():getWinSize()

	label:setPosition( ccp(s.width/2, s.height/2) )
	label:setAnchorPoint( ccp(0.5, 0.5) )

	Helper.titleLabel:setString("CCLabelBMFont")
	Helper.subtitleLabel:setString("Testing padding")
	return layer
end

--------------------------------------------------------------------
--
-- Atlas6
--
-- Use any of these editors to generate BMFonts:
--	   http:--glyphdesigner.71squared.com/ (Commercial, Mac OS X)
--	   http:--www.n4te.com/hiero/hiero.jnlp (Free, Java)
--	   http:--slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
--	   http:--www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------
local Atlas6 = {}
Atlas6.layer = nil

function Atlas6:create()
    cclog("Atlas6:create")
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	Atlas6.layer = layer

	local s = CCDirector:sharedDirector():getWinSize()
	local label = CCLabelBMFont:create("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt")
	layer:addChild(label)
	label:setPosition( ccp(s.width/2, s.height/2+50) )
	label:setAnchorPoint( ccp(0.5, 0.5) )

  	label = CCLabelBMFont:create("fafefifofu", "fonts/bitmapFontTest5.fnt")
  	layer:addChild(label)
  	label:setPosition( ccp(s.width/2, s.height/2) )
  	label:setAnchorPoint( ccp(0.5, 0.5) )

	label = CCLabelBMFont:create("aeiou", "fonts/bitmapFontTest5.fnt")
	layer:addChild(label)
	label:setPosition( ccp(s.width/2, s.height/2-50) )
	label:setAnchorPoint( ccp(0.5, 0.5) )

	Helper.titleLabel:setString("CCLabelBMFont")
	Helper.subtitleLabel:setString("Rendering should be OK. Testing offset")
	return layer
end

--------------------------------------------------------------------
--
-- AtlasBitmapColor
--
-- Use any of these editors to generate BMFonts:
--     http:--glyphdesigner.71squared.com/ (Commercial, Mac OS X)
--     http:--www.n4te.com/hiero/hiero.jnlp (Free, Java)
--     http:--slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
--     http:--www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------
local AtlasBitmapColor = { layer= nil }
function AtlasBitmapColor:create()
    local layer = CCLayer:create()
	AtlasBitmapColor.layer = layer
	Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()

	local label = CCLabelBMFont:create("Blue", "fonts/bitmapFontTest5.fnt")
    label:setColor( ccc3(0, 0, 255 ))
	layer:addChild(label)
    label:setPosition( ccp(s.width/2, s.height/4) )
    label:setAnchorPoint( ccp(0.5, 0.5) )

    label = CCLabelBMFont:create("Red", "fonts/bitmapFontTest5.fnt")
    layer:addChild(label)
    label:setPosition( ccp(s.width/2, 2*s.height/4) )
    label:setAnchorPoint( ccp(0.5, 0.5) )
    label:setColor( ccc3(255, 0, 0) )

    label = CCLabelBMFont:create("G", "fonts/bitmapFontTest5.fnt")
    layer:addChild(label)
    label:setPosition( ccp(s.width/2, 3*s.height/4) )
    label:setAnchorPoint( ccp(0.5, 0.5) )
    label:setColor( ccc3(0, 255, 0 ))
    label:setString("Green")

	Helper.titleLabel:setString("CCLabelBMFont")
	Helper.subtitleLabel:setString("Testing color")
	return layer
end

--------------------------------------------------------------------
--
-- AtlasFastBitmap
--
-- Use any of these editors to generate BMFonts:
--     http:--glyphdesigner.71squared.com/ (Commercial, Mac OS X)
--     http:--www.n4te.com/hiero/hiero.jnlp (Free, Java)
--     http:--slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
--     http:--www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------

local AtlasFastBitmap = { layer = nil }
function AtlasFastBitmap:create()
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)
	AtlasFastBitmap.layer = layer

	math.randomseed(os.time())
        -- Upper Label
    local i = 0
	for i = 0, 100, 1 do
	    local str = string.format("-%d-", i)
		local label = CCLabelBMFont:create(str, "fonts/bitmapFontTest.fnt")
		layer:addChild(label)

		local s = CCDirector:sharedDirector():getWinSize()

		local p = ccp( math.random() * s.width, math.random() * s.height)
		label:setPosition( p )
		label:setAnchorPoint(ccp(0.5, 0.5))
	end

	Helper.titleLabel:setString("CCLabelBMFont")
	Helper.subtitleLabel:setString("Creating several CCLabelBMFont with the same .fnt file should be fast")
	return layer
end

--------------------------------------------------------------------
--
-- BitmapFontMultiLine
--
-- Use any of these editors to generate BMFonts:
--     http:--glyphdesigner.71squared.com/ (Commercial, Mac OS X)
--     http:--www.n4te.com/hiero/hiero.jnlp (Free, Java)
--     http:--slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
--     http:--www.angelcode.com/products/bmfont/ (Free, Windows only)
--
--------------------------------------------------------------------
local BitmapFontMultiLine = {}

function BitmapFontMultiLine:create()
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)
    local s = nil

    -- Left
    local label1 = CCLabelBMFont:create(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt")
    label1:setAnchorPoint(ccp(0,0))
    layer:addChild(label1, 0, kTagBitmapAtlas1)

    s = label1:getContentSize()
    cclog("content size: %.2fx%.2f", s.width, s.height)


    -- Center
    local label2 = CCLabelBMFont:create("Multi line\nCenter", "fonts/bitmapFontTest3.fnt")
    label2:setAnchorPoint(ccp(0.5, 0.5))
    layer:addChild(label2, 0, kTagBitmapAtlas2)

    s= label2:getContentSize()
    cclog("content size: %.2fx%.2f", s.width, s.height)

    -- right
    local label3 = CCLabelBMFont:create("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt")
    label3:setAnchorPoint(ccp(1, 1))
    layer:addChild(label3, 0, kTagBitmapAtlas3)

    s = label3:getContentSize()
    cclog("content size: %.2fx%.2f", s.width, s.height)

    label1:setPosition(VisibleRect:leftBottom())
    label2:setPosition(VisibleRect:center())
    label3:setPosition(VisibleRect:rightTop())
	Helper.titleLabel:setString("CCLabelBMFont")
	Helper.subtitleLabel:setString("Multiline + anchor point")
        return layer
end

--------------------------------------------------------------------
--
-- LabelsEmpty
--
--------------------------------------------------------------------

local LabelsEmpty = {}
LabelsEmpty.layer = nil
LabelsEmpty.setEmpty = false
LabelsEmpty.updateEntry = nil

function LabelsEmpty.onNodeEvent(tag)
   if tag == "enter" then
      LabelsEmpty.updateEntry = scheduler:scheduleScriptFunc(LabelsEmpty.updateStrings, 1.0, false)
   elseif tag == "exit" then
      scheduler:unscheduleScriptEntry(LabelsEmpty.updateEntry)
   end
end


function LabelsEmpty.create()
    cclog("LabelsEmpty.create")

    local layer = CCLayer:create()
    LabelsEmpty.layer = layer
    Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()

    -- CCLabelBMFont
    local label1 = CCLabelBMFont:create("", "fonts/bitmapFontTest3.fnt")
    layer:addChild(label1, 0, kTagBitmapAtlas1)
    label1:setPosition(ccp(s.width/2, s.height-100))

    -- CCLabelTTF
    local label2 = CCLabelTTF:create("", "Arial", 24)
    layer:addChild(label2, 0, kTagBitmapAtlas2)
    label2:setPosition(ccp(s.width/2, s.height/2))

    -- CCLabelAtlas
    local label3 = CCLabelAtlas:create("", "fonts/tuffy_bold_italic-charmap.png", 48, 64,  string.byte(" "))
    layer:addChild(label3, 0, kTagBitmapAtlas3)
    label3:setPosition(ccp(s.width/2, 0+100))

    layer:registerScriptHandler(LabelsEmpty.onNodeEvent)

    LabelsEmpty.setEmpty = false
    Helper.titleLabel:setString("Testing empty labels")
    Helper.subtitleLabel:setString("3 empty labels: LabelAtlas, LabelTTF and LabelBMFont")
    return layer
end

function LabelsEmpty.updateStrings(dt)
    local label1 = tolua.cast(LabelsEmpty.layer:getChildByTag(kTagBitmapAtlas1), "CCLabelBMFont")
    local label2 = tolua.cast(LabelsEmpty.layer:getChildByTag(kTagBitmapAtlas2), "CCLabelTTF")
    local label3 = tolua.cast(LabelsEmpty.layer:getChildByTag(kTagBitmapAtlas3), "CCLabelAtlas")

    if( LabelsEmpty.setEmpty == false) then
        label1:setString("not empty")
        label2:setString("not empty")
        label3:setString("hi")
        LabelsEmpty.setEmpty = true
    else
        label1:setString("")
        label2:setString("")
        label3:setString("")
        LabelsEmpty.setEmpty = false
    end
end

--------------------------------------------------------------------
--
-- LabelBMFontHD
--
--------------------------------------------------------------------
local LabelBMFontHD = {
   
}

function LabelBMFontHD.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()

    -- CCLabelBMFont
    local label1 = CCLabelBMFont:create("TESTING RETINA DISPLAY", "fonts/konqa32.fnt")
    layer:addChild(label1)
    label1:setPosition(ccp(s.width/2, s.height/2))

    Helper.titleLabel:setString("Testing Retina Display BMFont")
    Helper.subtitleLabel:setString("loading arista16 or arista16-hd")
    return layer
end

--------------------------------------------------------------------
--
-- LabelAtlasHD
--
--------------------------------------------------------------------
local LabelAtlasHD = {}
function LabelAtlasHD.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()

    -- CCLabelBMFont
    local label1 = CCLabelAtlas:create("TESTING RETINA DISPLAY", "fonts/larabie-16.plist")
    label1:setAnchorPoint(ccp(0.5, 0.5))

    layer:addChild(label1)
    label1:setPosition(ccp(s.width/2, s.height/2))

    Helper.titleLabel:setString("LabelAtlas with Retina Display")
    Helper.subtitleLabel:setString("loading larabie-16 / larabie-16-hd")
    return layer
end

--------------------------------------------------------------------
--
-- LabelGlyphDesigner
--
--------------------------------------------------------------------

local LabelGlyphDesigner = {}
function LabelGlyphDesigner.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()

    local colorlayer = CCLayerColor:create(ccc4(128,128,128,255))
    layer:addChild(colorlayer, -10)

    -- CCLabelBMFont
    local label1 = CCLabelBMFont:create("Testing Glyph Designer", "fonts/futura-48.fnt")
    layer:addChild(label1)
    label1:setPosition(ccp(s.width/2, s.height/2))
    Helper.titleLabel:setString("Testing Glyph Designer")
    Helper.subtitleLabel:setString("You should see a font with shawdows and outline")

    return layer
end

--------------------------------------------------------------------
--
-- LabelTTFTest
--
--------------------------------------------------------------------

local LabelTTFTest = {
    _layer = nil,
    _plabel = nil,
    _eHorizAlign = kCCTextAlignmentLeft,
    _eVertAlign = kCCVerticalTextAlignmentTop
}

function LabelTTFTest.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    LabelTTFTest._layer = layer

    local blockSize = CCSizeMake(200, 160)
    local s = CCDirector:sharedDirector():getWinSize()

    local colorLayer = CCLayerColor:create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height)
    colorLayer:setAnchorPoint(ccp(0,0))
    colorLayer:setPosition(ccp((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2))

    layer:addChild(colorLayer)

    CCMenuItemFont:setFontSize(30)
    local item1 = CCMenuItemFont:create("Left")
    item1:registerScriptTapHandler(LabelTTFTest.setAlignmentLeft)
    local item2 = CCMenuItemFont:create("Center")
    item2:registerScriptTapHandler(LabelTTFTest.setAlignmentCenter)
    local item3 = CCMenuItemFont:create("Right")
    item3:registerScriptTapHandler(LabelTTFTest.setAlignmentRight)

    local menu = CCMenu:create()
    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)
    menu:alignItemsVerticallyWithPadding(4)
    menu:setPosition(ccp(50, s.height / 2 - 20))
    layer:addChild(menu)

    menu = CCMenu:create()

    item1 = CCMenuItemFont:create("Top")
    item1:registerScriptTapHandler(LabelTTFTest.setAlignmentTop)
    item2 = CCMenuItemFont:create("Middle")
    item2:registerScriptTapHandler(LabelTTFTest.setAlignmentMiddle)
    item3 = CCMenuItemFont:create("Bottom")
    item3:registerScriptTapHandler(LabelTTFTest.setAlignmentBottom)

    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)

    menu:alignItemsVerticallyWithPadding(4)
    menu:setPosition(ccp(s.width - 50, s.height / 2 - 20))
    layer:addChild(menu)

    layer:updateAlignment()
    
    layer:registerScriptHandler(LabelTTFTest.onNodeEvent)

    Helper.titleLabel:setString("Testing CCLabelTTF")
    Helper.subtitleLabel:setString("Select the buttons on the sides to change alignment")

    return layer
end

function LabelTTFTest.onNodeEvent(tag)
   if tag == "exit" then
      if LabelTTFTest._plabel != nil then
         LabelTTFTest._plabel:release()
      end
   end
end

function LabelTTFTest.updateAlignment()
    local blockSize = CCSizeMake(200, 160)
    local s = CCDirector:sharedDirector():getWinSize()

    if (LabelTTFTest._plabel)
    {
        LabelTTFTest._plabel:removeFromParentAndCleanup(true)
        LabelTTFTest._plabel:release()
    }

    LabelTTFTest._plabel = CCLabelTTF:create(this:getCurrentAlignment(), "Marker Felt", 32,
                                  blockSize, LabelTTFTest._eHorizAlign, LabelTTFTest._eVertAlign)
    LabelTTFTest._plabel:retain()

    LabelTTFTest._plabel:setAnchorPoint(ccp(0,0))
    LabelTTFTest._plabel:setPosition(ccp((s.width - blockSize.width) / 2, (s.height - blockSize.height)/2 ))

    LabelTTFTest._layer:addChild(LabelTTFTest._plabel)
end

function LabelTTFTest.setAlignmentLeft(pSender)
    LabelTTFTest._eHorizAlign = kCCTextAlignmentLeft
    LabelTTFTest.updateAlignment()
end

function LabelTTFTest.setAlignmentCenter(pSender)
    LabelTTFTest._eHorizAlign = kCCTextAlignmentCenter
    LabelTTFTest.updateAlignment()
end

void LabelTTFTest:setAlignmentRight(CCObject* pSender)
{
    m_eHorizAlign = kCCTextAlignmentRight
    this:updateAlignment()
}

void LabelTTFTest:setAlignmentTop(CCObject* pSender)
{
    m_eVertAlign = kCCVerticalTextAlignmentTop
    this:updateAlignment()
}

void LabelTTFTest:setAlignmentMiddle(CCObject* pSender)
{
    m_eVertAlign = kCCVerticalTextAlignmentCenter
    this:updateAlignment()
}

void LabelTTFTest:setAlignmentBottom(CCObject* pSender)
{
    m_eVertAlign = kCCVerticalTextAlignmentBottom
    this:updateAlignment()
}

const char* LabelTTFTest:getCurrentAlignment()
{
    const char* vertical = NULL
    const char* horizontal = NULL
    switch (m_eVertAlign) {
        case kCCVerticalTextAlignmentTop:
            vertical = "Top"
            break
        case kCCVerticalTextAlignmentCenter:
            vertical = "Middle"
            break
        case kCCVerticalTextAlignmentBottom:
            vertical = "Bottom"
            break
    }
    switch (m_eHorizAlign) {
        case kCCTextAlignmentLeft:
            horizontal = "Left"
            break
        case kCCTextAlignmentCenter:
            horizontal = "Center"
            break
        case kCCTextAlignmentRight:
            horizontal = "Right"
            break
    }

    return CCString:createWithFormat("Alignment %s %s", vertical, horizontal):getCString()
}




function LabelTest()
   cclog("LabelTest")
   m_time = 0
   local scene = CCScene:create()

   Helper.createFunctionTable = {
	  LabelAtlasTest.create,
	  LabelAtlasColorTest.create,
	  Atlas3.create,
	  Atlas4.create,
	  Atlas5.create,
	  Atlas6.create,
	  AtlasBitmapColor.create,
	  AtlasFastBitmap.create,
	  BitmapFontMultiLine.create,
	  LabelsEmpty.create,
	  LabelBMFontHD.create,
	  LabelAtlasHD.create,
	  LabelGlyphDesigner.create,
--	  Atlas1,
--	  LabelTTFTest,
--	  LabelTTFMultiline,
--	  LabelTTFChinese,
--	  LabelBMFontChinese,
--	  BitmapFontMultiLineAlignment,
--	  LabelTTFA8Test,
--	  BMFontOneAtlas,
--	  BMFontUnicode,
--	  BMFontInit,
--	  TTFFontInit,
--	  Issue1343,
--	  LabelTTFAlignment,
--	  LabelBMFontBounds
   }
   scene:addChild(LabelAtlasTest.create())
   scene:addChild(CreateBackMenuItem())
   return scene
end
