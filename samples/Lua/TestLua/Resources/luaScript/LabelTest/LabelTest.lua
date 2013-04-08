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
    _layer       = nil,
    _plabel      = nil,
    _eHorizAlign = kCCTextAlignmentLeft,
    _eVertAlign  = kCCVerticalTextAlignmentTop
}

function LabelTTFTest.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    LabelTTFTest._layer       = layer
    LabelTTFTest._plabel      = nil
    LabelTTFTest._eHorizAlign = kCCTextAlignmentLeft
    LabelTTFTest._eVertAlign  = kCCVerticalTextAlignmentTop

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

    LabelTTFTest.updateAlignment()
    
    layer:registerScriptHandler(LabelTTFTest.onNodeEvent)

    Helper.titleLabel:setString("Testing CCLabelTTF")
    Helper.subtitleLabel:setString("Select the buttons on the sides to change alignment")

    return layer
end

function LabelTTFTest.onNodeEvent(tag)
    if tag == "exit" then
        if LabelTTFTest._plabel ~= nil then
            LabelTTFTest._plabel:release()
        end
    end
end

function LabelTTFTest.updateAlignment()
    local blockSize = CCSizeMake(200, 160)
    local s = CCDirector:sharedDirector():getWinSize()

    if LabelTTFTest._plabel ~= nil then
        LabelTTFTest._plabel:removeFromParentAndCleanup(true)
        LabelTTFTest._plabel:release()
    end

    LabelTTFTest._plabel = CCLabelTTF:create(LabelTTFTest.getCurrentAlignment(), "Marker Felt", 32,
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

function LabelTTFTest.setAlignmentRight(pSender)
    LabelTTFTest._eHorizAlign = kCCTextAlignmentRight
    LabelTTFTest.updateAlignment()
end

function LabelTTFTest.setAlignmentTop(pSender)
    LabelTTFTest._eVertAlign = kCCVerticalTextAlignmentTop
    LabelTTFTest.updateAlignment()
end

function LabelTTFTest.setAlignmentMiddle(pSender)
    LabelTTFTest._eVertAlign = kCCVerticalTextAlignmentCenter
    LabelTTFTest.updateAlignment()
end

function LabelTTFTest.setAlignmentBottom(pSender)
    LabelTTFTest._eVertAlign = kCCVerticalTextAlignmentBottom
    LabelTTFTest.updateAlignment()
end

function LabelTTFTest.getCurrentAlignment()
    local vertical = nil
    local horizontal = nil
    if LabelTTFTest._eVertAlign == kCCVerticalTextAlignmentTop then
        vertical = "Top"
    elseif LabelTTFTest._eVertAlign ==  kCCVerticalTextAlignmentCenter then
        vertical = "Middle"
    elseif LabelTTFTest._eVertAlign ==  kCCVerticalTextAlignmentBottom then
        vertical = "Bottom"
    end

    if LabelTTFTest._eHorizAlign == kCCTextAlignmentLeft then
        horizontal = "Left"
    elseif LabelTTFTest._eHorizAlign == kCCTextAlignmentCenter then
        horizontal = "Center"
    elseif LabelTTFTest._eHorizAlign == kCCTextAlignmentRight then
        horizontal = "Right"
    end

    return string.format("Alignment %s %s", vertical, horizontal)
end

--------------------------------------------------------------------
--
-- Atlas1
--
--------------------------------------------------------------------
--Atlas1:Atlas1()
--{ 
--    m_textureAtlas = CCTextureAtlas:create(s_AtlasTest, 3); m_textureAtlas:retain();
--    
--    CCSize s = CCDirector:sharedDirector():getWinSize();
--  
--    --
--    -- Notice: u,v tex coordinates are inverted
--    --
--    ccV3F_C4B_T2F_Quad quads[] = 
--    {
--        {
--            {{0,0,0},ccc4(0,0,255,255),{0.0f,1.0f},},                -- bottom left
--            {{s.width,0,0},ccc4(0,0,255,0),{1.0f,1.0f},},            -- bottom right
--            {{0,s.height,0},ccc4(0,0,255,0),{0.0f,0.0f},},            -- top left
--            {{s.width,s.height,0},{0,0,255,255},{1.0f,0.0f},},    -- top right
--        },        
--        {
--            {{40,40,0},ccc4(255,255,255,255),{0.0f,0.2f},},            -- bottom left
--            {{120,80,0},ccc4(255,0,0,255),{0.5f,0.2f},},            -- bottom right
--            {{40,160,0},ccc4(255,255,255,255),{0.0f,0.0f},},        -- top left
--            {{160,160,0},ccc4(0,255,0,255),{0.5f,0.0f},},            -- top right
--        },
--  
--        {
--            {{s.width/2,40,0},ccc4(255,0,0,255),{0.0f,1.0f},},        -- bottom left
--            {{s.width,40,0},ccc4(0,255,0,255),{1.0f,1.0f},},        -- bottom right
--            {{s.width/2-50,200,0},ccc4(0,0,255,255),{0.0f,0.0f},},        -- top left
--            {{s.width,100,0},ccc4(255,255,0,255),{1.0f,0.0f},},        -- top right
--        },
--        
--    };
--    
--    
--    for( int i=0;i<3;i++) 
--    {
--        m_textureAtlas:updateQuad(&quads[i], i);
--    }
--} 
--  
--Atlas1:~Atlas1()
--{ 
--    m_textureAtlas:release();
--} 
--  
--void Atlas1:draw()
--{ 
--    -- GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
--    -- GL_TEXTURE_2D
--  
--    m_textureAtlas:drawQuads();
--  
----    [textureAtlas drawNumberOfQuads:3];
--    
--} 
--  
--std:string Atlas1:title()
--{ 
--    return "CCTextureAtlas";
--} 
--  
--std:string Atlas1:subtitle()
--{ 
--    return "Manual creation of CCTextureAtlas";
--} 

local LabelTTFMultiline = {
    layer = nil
}

function LabelTTFMultiline.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    
    local s = CCDirector:sharedDirector():getWinSize()

    local center = CCLabelTTF:create("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
                                     "Paint Boy",
                                     32,
                                     CCSizeMake(s.width/2,200),
                                     kCCTextAlignmentCenter,
                                     kCCVerticalTextAlignmentTop)

    center:setPosition(ccp(s.width / 2, 150))

    layer:addChild(center)
    Helper.titleLabel:setString("Testing CCLabelTTF Word Wrap")
    Helper.subtitleLabel:setString("Word wrap using CCLabelTTF and a custom TTF font")

    return layer
end

local LabelTTFChinese = {}

function LabelTTFChinese.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    local size = CCDirector:sharedDirector():getWinSize()
    local pLable = CCLabelTTF:create("中国", "Marker Felt", 30)
    pLable:setPosition(ccp(size.width / 2, size.height /2))
    layer:addChild(pLable)
    Helper.titleLabel:setString("Testing CCLabelTTF with Chinese character")
    return layer
end

local LabelBMFontChinese = {}
function LabelBMFontChinese.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    local size = CCDirector:sharedDirector():getWinSize()
    local pLable = CCLabelBMFont:create("中国", "fonts/bitmapFontChinese.fnt")
    pLable:setPosition(ccp(size.width / 2, size.height /2))
    layer:addChild(pLable)

    Helper.titleLabel:setString("Testing CCLabelBMFont with Chinese character")
    return layer
end

-- BitmapFontMultiLineAlignment

local  LongSentencesExample =  "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
local  LineBreaksExample    = "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
local  MixedExample         = "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

local  ArrowsMax             = 0.95
local  ArrowsMin             = 0.7

local  LeftAlign             = 0
local  CenterAlign           = 1
local  RightAlign            = 2

local  LongSentences         = 0
local  LineBreaks            = 1
local  Mixed                 = 2

local  alignmentItemPadding  = 50
local  menuItemPaddingCenter = 50

local BitmapFontMultiLineAlignment = {
    _pLabelShouldRetain = nil,
    _pArrowsBarShouldRetain = nil,
    _pArrowsShouldRetain = nil,
    _pLastSentenceItem = nil,
    _drag = false,
}

function BitmapFontMultiLineAlignment.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    layer:setTouchEnabled(true)

    -- ask director the the window size
    local size = CCDirector:sharedDirector():getWinSize()

    -- create and initialize a Label
    BitmapFontMultiLineAlignment._pLabelShouldRetain = CCLabelBMFont:create(LongSentencesExample, "fonts/markerFelt.fnt", size.width/1.5, kCCTextAlignmentCenter)
    BitmapFontMultiLineAlignment._pLabelShouldRetain:retain()

    BitmapFontMultiLineAlignment._pArrowsBarShouldRetain = CCSprite:create("Images/arrowsBar.png")
    BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:retain()
    BitmapFontMultiLineAlignment._pArrowsShouldRetain = CCSprite:create("Images/arrows.png")
    BitmapFontMultiLineAlignment._pArrowsShouldRetain:retain()

    CCMenuItemFont:setFontSize(20)
    local longSentences = CCMenuItemFont:create("Long Flowing Sentences")
    longSentences:registerScriptTapHandler(BitmapFontMultiLineAlignment.stringChanged)
    local lineBreaks    = CCMenuItemFont:create("Short Sentences With Intentional Line Breaks")
    lineBreaks:registerScriptTapHandler(BitmapFontMultiLineAlignment.stringChanged)
    local mixed         = CCMenuItemFont:create("Long Sentences Mixed With Intentional Line Breaks")
    mixed:registerScriptTapHandler(BitmapFontMultiLineAlignment.stringChanged)
    local stringMenu    = CCMenu:create()
    stringMenu:addChild(longSentences)
    stringMenu:addChild(lineBreaks)
    stringMenu:addChild(mixed)
    stringMenu:alignItemsVertically()

    longSentences:setColor(ccc3(255, 0, 0))
    BitmapFontMultiLineAlignment._pLastSentenceItem = longSentences

    longSentences:setTag(LongSentences)
    lineBreaks:setTag(LineBreaks)
    mixed:setTag(Mixed)

    CCMenuItemFont:setFontSize(30)

    local left          = CCMenuItemFont:create("Left")
    left:registerScriptTapHandler(BitmapFontMultiLineAlignment.alignmentChanged)
    local center        = CCMenuItemFont:create("Center")
    center:registerScriptTapHandler(BitmapFontMultiLineAlignment.alignmentChanged)
    local right         = CCMenuItemFont:create("Right")
    right:registerScriptTapHandler(BitmapFontMultiLineAlignment.alignmentChanged)

    local alignmentMenu = CCMenu:create()
    alignmentMenu:addChild(left)
    alignmentMenu:addChild(center)
    alignmentMenu:addChild(right)

    alignmentMenu:alignItemsHorizontallyWithPadding(alignmentItemPadding)

    center:setColor(ccc3(255, 0, 0))
    BitmapFontMultiLineAlignment._pLastAlignmentItem = center
    left:setTag(LeftAlign)
    center:setTag(CenterAlign)
    right:setTag(RightAlign)

    -- position the label on the center of the screen
    BitmapFontMultiLineAlignment._pLabelShouldRetain:setPosition(ccp(size.width/2, size.height/2))

    BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:setVisible(false)

    local arrowsWidth = (ArrowsMax - ArrowsMin) * size.width
    BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:setScaleX(arrowsWidth / BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:getContentSize().width)
    BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:setPosition( ((ArrowsMax + ArrowsMin) / 2) * size.width, BitmapFontMultiLineAlignment._pLabelShouldRetain:getPositionY() )

    BitmapFontMultiLineAlignment.snapArrowsToEdge()

    stringMenu:setPosition(ccp(size.width/2, size.height - menuItemPaddingCenter))
    alignmentMenu:setPosition(ccp(size.width/2, menuItemPaddingCenter+15))

    layer:addChild(BitmapFontMultiLineAlignment._pLabelShouldRetain)
    layer:addChild(BitmapFontMultiLineAlignment._pArrowsBarShouldRetain)
    layer:addChild(BitmapFontMultiLineAlignment._pArrowsShouldRetain)
    layer:addChild(stringMenu)
    layer:addChild(alignmentMenu)
    layer:registerScriptHandler(BitmapFontMultiLineAlignment.onNodeEvent)
    layer:registerScriptTouchHandler(BitmapFontMultiLineAlignment.onTouchEvent)
    return layer
end

function BitmapFontMultiLineAlignment.onNodeEvent(tag)
    if tag == "onexit" then
        BitmapFontMultiLineAlignment._pLabelShouldRetain:release()
        BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:release()
        BitmapFontMultiLineAlignment._pArrowsShouldRetain:release()
    end
end



function BitmapFontMultiLineAlignment.stringChanged(tag, sender)
    local item = tolua.cast(sender, "CCMenuItemFont")
    item:setColor(ccc3(255, 0, 0))
    BitmapFontMultiLineAlignment._pLastAlignmentItem:setColor(ccc3(255, 255, 255))
    BitmapFontMultiLineAlignment._pLastAlignmentItem = item

    if item:getTag() == LongSentences then
        BitmapFontMultiLineAlignment._pLabelShouldRetain:setString(LongSentencesExample)
    elseif item:getTag() == LineBreaks then
        BitmapFontMultiLineAlignment._pLabelShouldRetain:setString(LineBreaksExample)
    elseif item:getTag() == Mixed then
        BitmapFontMultiLineAlignment._pLabelShouldRetain:setString(MixedExample)
    end

    BitmapFontMultiLineAlignment.snapArrowsToEdge()
end

function BitmapFontMultiLineAlignment.alignmentChanged(tag, sender)
    -- cclog("BitmapFontMultiLineAlignment.alignmentChanged, tag:"..tag)
    local item = tolua.cast(sender, "CCMenuItemFont")
    item:setColor(ccc3(255, 0, 0))
    BitmapFontMultiLineAlignment._pLastAlignmentItem:setColor(ccc3(255, 255, 255))
    BitmapFontMultiLineAlignment._pLastAlignmentItem = item

    if tag == LeftAlign then
        cclog("LeftAlign")
        BitmapFontMultiLineAlignment._pLabelShouldRetain:setAlignment(kCCTextAlignmentLeft)
    elseif tag == CenterAlign then
        BitmapFontMultiLineAlignment._pLabelShouldRetain:setAlignment(kCCTextAlignmentCenter)
    elseif tag == RightAlign then
        BitmapFontMultiLineAlignment._pLabelShouldRetain:setAlignment(kCCTextAlignmentRight)
    end

    BitmapFontMultiLineAlignment.snapArrowsToEdge()
end

function BitmapFontMultiLineAlignment.onTouchEvent(eventType, x, y)
    -- cclog("type:"..eventType.."["..x..","..y.."]")
    if eventType == "began" then
        if BitmapFontMultiLineAlignment._pArrowsShouldRetain:boundingBox():containsPoint(ccp(x, y)) then
            BitmapFontMultiLineAlignment._drag = true
            BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:setVisible(true)
            return true
        end
    elseif eventType == "ended" then
        BitmapFontMultiLineAlignment._drag = false
        BitmapFontMultiLineAlignment.snapArrowsToEdge()
        BitmapFontMultiLineAlignment._pArrowsBarShouldRetain:setVisible(false)
    elseif eventType == "moved" then
        if BitmapFontMultiLine._drag == false then
            return
        end

        local winSize = CCDirector:sharedDirector():getWinSize()
        BitmapFontMultiLineAlignment._pArrowsShouldRetain:setPosition(
            math.max(math.min(x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
            BitmapFontMultiLineAlignment._pArrowsShouldRetain:getPositionY())

        local labelWidth = math.abs(BitmapFontMultiLineAlignment._pArrowsShouldRetain:getPositionX() - BitmapFontMultiLineAlignment._pLabelShouldRetain:getPositionX()) * 2

        BitmapFontMultiLineAlignment._pLabelShouldRetain:setWidth(labelWidth)
        
    end
end

function BitmapFontMultiLineAlignment.snapArrowsToEdge()
    BitmapFontMultiLineAlignment._pArrowsShouldRetain:setPosition(
        BitmapFontMultiLineAlignment._pLabelShouldRetain:getPositionX() + BitmapFontMultiLineAlignment._pLabelShouldRetain:getContentSize().width/2, BitmapFontMultiLineAlignment._pLabelShouldRetain:getPositionY()
    )
end

--/ LabelTTFA8Test

local LabelTTFA8Test = {}

function LabelTTFA8Test.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()

    local colorlayer = CCLayerColor:create(ccc4(128, 128, 128, 255))
    layer:addChild(colorlayer, -10)

    -- CCLabelBMFont
    local label1 = CCLabelTTF:create("Testing A8 Format", "Marker Felt", 48)
    layer:addChild(label1)
    label1:setColor(ccc3(255, 0, 0))
    label1:setPosition(ccp(s.width/2, s.height/2))

    local fadeOut = CCFadeOut:create(2)
    local fadeIn = CCFadeIn:create(2)
    local arr = CCArray:create()
    arr:addObject(fadeOut)
    arr:addObject(fadeIn)

    local seq = CCSequence:create(arr)
    local forever = CCRepeatForever:create(seq)
    label1:runAction(forever)

    Helper.titleLabel:setString("Testing A8 Format")
    Helper.subtitleLabel:setString("RED label, fading In and Out in the center of the screen")
    return layer
end

--/ BMFontOneAtlas
local BMFontOneAtlas = {}
function BMFontOneAtlas.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)

    local s = CCDirector:sharedDirector():getWinSize()
    
    local label1 = CCLabelBMFont:create("This is Helvetica", "fonts/helvetica-32.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft, ccp(0, 0))
    layer:addChild(label1)
    label1:setPosition(ccp(s.width/2, s.height/3*2))
    
    local label2 = CCLabelBMFont:create("And this is Geneva", "fonts/geneva-32.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft, ccp(0, 128))
    layer:addChild(label2)
    label2:setPosition(ccp(s.width/2, s.height/3*1))
    Helper.titleLabel:setString("CCLabelBMFont with one texture")
    Helper.subtitleLabel:setString("Using 2 .fnt definitions that share the same texture atlas.")
    return layer
end

--/ BMFontUnicode
local BMFontUnicode = {}
function BMFontUnicode.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("CCLabelBMFont with Unicode support")
    Helper.subtitleLabel:setString("You should see 3 differnt labels: In Spanish, Chinese and Korean")

    local s = CCDirector:sharedDirector():getWinSize()
    
    local label1 = CCLabelBMFont:create("Buen día", "fonts/arial-unicode-26.fnt", 200, kCCTextAlignmentLeft)
    layer:addChild(label1)
    label1:setPosition(ccp(s.width/2, s.height/4*3))
    
    local label2 = CCLabelBMFont:create("美好的一天", "fonts/arial-unicode-26.fnt")
    layer:addChild(label2)
    label2:setPosition(ccp(s.width/2, s.height/4*2))
    
    local label3 = CCLabelBMFont:create("良い一日を", "fonts/arial-unicode-26.fnt")
    layer:addChild(label3)
    label3:setPosition(ccp(s.width/2, s.height/4*1))

    return layer
end

--BMFontInit

local BMFontInit = {}
function BMFontInit.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("CCLabelBMFont init")
    Helper.subtitleLabel:setString("Test for support of init method without parameters.")
    
    local s = CCDirector:sharedDirector():getWinSize()
    
    local bmFont = CCLabelBMFont:new()
    bmFont:init()
    bmFont:autorelease()
    --CCLabelBMFont* bmFont = [CCLabelBMFont create:@"Foo" fntFile:@"arial-unicode-26.fnt"]
    bmFont:setFntFile("fonts/helvetica-32.fnt")
    bmFont:setString("It is working!")
    layer:addChild(bmFont)
    bmFont:setPosition(ccp(s.width/2,s.height/4*2))
    return layer
end


-- TTFFontInit

local TTFFontInit = {}
function TTFFontInit.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("CCLabelTTF init")
    Helper.subtitleLabel:setString("Test for support of init method without parameters.")
    
    local s = CCDirector:sharedDirector():getWinSize()
    
    local font = CCLabelTTF:new()
    font:init()
    font:autorelease()
    font:setFontName("Marker Felt")
    font:setFontSize(48)
    font:setString("It is working!")
    layer:addChild(font)
    font:setPosition(ccp(s.width/2,s.height/4*2))
    return layer
end

-- Issue1343

local Issue1343 = {}
function Issue1343.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Issue 1343")
    Helper.subtitleLabel:setString("You should see: ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'")
    
    local s = CCDirector:sharedDirector():getWinSize()
    
    local bmFont = CCLabelBMFont:new()
    bmFont:init()
    bmFont:setFntFile("fonts/font-issue1343.fnt")
    bmFont:setString("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'")
    layer:addChild(bmFont)
    bmFont:release()
    bmFont:setScale(0.3)
    
    bmFont:setPosition(ccp(s.width/2,s.height/4*2))
    return layer
end

local LabelBMFontBounds = {}
function LabelBMFontBounds.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing LabelBMFont Bounds")
    Helper.subtitleLabel:setString("You should see string enclosed by a box")
    
    local s = CCDirector:sharedDirector():getWinSize()
    
    local colorlayer = CCLayerColor:create(ccc4(128,128,128,255))
    layer:addChild(colorlayer, -10)
    
    -- CCLabelBMFont
    local label1 = CCLabelBMFont:create("Testing Glyph Designer", "fonts/boundsTestFont.fnt")
    
    
    layer:addChild(label1)
    label1:setPosition(ccp(s.width/2, s.height/2))
    return layer
end


function LabelBMFontBounds.draw()
    -- CCSize labelSize = label1:getContentSize()
    -- CCSize origin = CCDirector:sharedDirector():getWinSize()
    
    -- origin.width = origin.width / 2 - (labelSize.width / 2)
    -- origin.height = origin.height / 2 - (labelSize.height / 2)
    
    -- CCPoint vertices[4]=
    
    --     ccp(origin.width, origin.height),
    --     ccp(labelSize.width + origin.width, origin.height),
    --     ccp(labelSize.width + origin.width, labelSize.height + origin.height),
    --     ccp(origin.width, labelSize.height + origin.height)
    -- end
    -- ccDrawPoly(vertices, 4, true)
end

--------------------------------------------------------------------
--
-- LabelTTFAlignment
--
--------------------------------------------------------------------
local LabelTTFAlignment = {}
function LabelTTFAlignment.create()
    local layer = CCLayer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("CCLabelTTF alignment")
    Helper.subtitleLabel:setString("Tests alignment values")
    
    local s = CCDirector:sharedDirector():getWinSize()

    local ttf0 = CCLabelTTF:create("Alignment 0\nnew line", "Helvetica", 12,
                                   CCSizeMake(256, 32), kCCTextAlignmentLeft)
    ttf0:setPosition(ccp(s.width/2,(s.height/6)*2))
    ttf0:setAnchorPoint(ccp(0.5,0.5))
    layer:addChild(ttf0)

    local ttf1 = CCLabelTTF:create("Alignment 1\nnew line", "Helvetica", 12,
                                   CCSizeMake(245, 32), kCCTextAlignmentCenter)
    ttf1:setPosition(ccp(s.width/2,(s.height/6)*3))
    ttf1:setAnchorPoint(ccp(0.5,0.5))
    layer:addChild(ttf1)

    local ttf2 = CCLabelTTF:create("Alignment 2\nnew line", "Helvetica", 12,
                                   CCSizeMake(245, 32), kCCTextAlignmentRight)
    ttf2:setPosition(ccp(s.width/2,(s.height/6)*4))
    ttf2:setAnchorPoint(ccp(0.5,0.5))
    layer:addChild(ttf2)
    return layer
end

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
        LabelTTFTest.create,
        LabelTTFMultiline.create,
        LabelTTFChinese.create,
        LabelBMFontChinese.create,
        BitmapFontMultiLineAlignment.create,
        LabelTTFA8Test.create,
        BMFontOneAtlas.create,
        BMFontUnicode.create,
        BMFontInit.create,
        TTFFontInit.create,
        Issue1343.create,
        LabelTTFAlignment.create,
        LabelBMFontBounds.create
    }
    scene:addChild(LabelAtlasTest.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end
