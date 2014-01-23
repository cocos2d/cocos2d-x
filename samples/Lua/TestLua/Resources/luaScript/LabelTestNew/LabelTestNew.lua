local size = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

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
-- LabelFNTColorAndOpacity
--
--------------------------------------------------------------------
local LabelFNTColorAndOpacity = {}
LabelFNTColorAndOpacity.layer = nil
LabelFNTColorAndOpacity.__index = LabelFNTColorAndOpacity

function LabelFNTColorAndOpacity.onNodeEvent(tag)
    if tag == "exit" then
        LabelFNTColorAndOpacity.layer:unscheduleUpdate()
    end
end

function LabelFNTColorAndOpacity.create()
    cclog("LabelFNTColorAndOpacity.create")
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    LabelFNTColorAndOpacity.layer = layer

    m_time = 0

    local col = cc.LayerColor:create( cc.c4b(128,128,128,255) )
    layer:addChild(col, -10)

    local label1 = cc.Label:createWithBMFont("fonts/bitmapFontTest2.fnt", "Test")

    -- testing anchors
    label1:setAnchorPoint( cc.p(0,0) )
    layer:addChild(label1, 0, kTagBitmapAtlas1)

    local fade = cc.FadeOut:create(1.0)
    local fade_in = fade:reverse()

    local seq = cc.Sequence:create(fade,fade_in)
    local repeatAction = cc.RepeatForever:create(seq)
    label1:runAction(repeatAction)

    local label2 = cc.Label:createWithBMFont("fonts/bitmapFontTest2.fnt", "Test")
    -- testing anchors
    label2:setAnchorPoint( cc.p(0.5, 0.5) )
    label2:setColor(cc.c3b(255, 0, 0 ))
    layer:addChild(label2, 0, kTagBitmapAtlas2)

    label2:runAction( tolua.cast(repeatAction:clone(), "cc.Action") )

    local label3 = cc.Label:createWithBMFont("fonts/bitmapFontTest2.fnt", "Test")
    -- testing anchors
    label3:setAnchorPoint( cc.p(1,1) )
    layer:addChild(label3, 0, kTagBitmapAtlas3)

    label1:setPosition( VisibleRect:leftBottom() )
    label2:setPosition( VisibleRect:center() )
    label3:setPosition( VisibleRect:rightTop() )

    layer:registerScriptHandler(LabelFNTColorAndOpacity.onNodeEvent)
    layer:scheduleUpdateWithPriorityLua(LabelFNTColorAndOpacity.step, 0)

    Helper.titleLabel:setString( "New Label + .FNT file" )
    Helper.subtitleLabel:setString( "Testing opacity + tint" )

    return layer
end

function LabelFNTColorAndOpacity.step(dt)
    m_time = m_time + dt
    local string = string.format("%2.2f Test j", m_time)

    local label1 = tolua.cast(LabelFNTColorAndOpacity.layer:getChildByTag(kTagBitmapAtlas1), "cc.Label")
    label1:setString(string)

    local label2 = tolua.cast(LabelFNTColorAndOpacity.layer:getChildByTag(kTagBitmapAtlas2), "cc.Label")
    label2:setString(string)

    local label3 = tolua.cast(LabelFNTColorAndOpacity.layer:getChildByTag(kTagBitmapAtlas3), "cc.Label")
    label3:setString(string)
end

--------------------------------------------------------------------
--
-- LabelFNTSpriteActions
--
--------------------------------------------------------------------
local LabelFNTSpriteActions = {}
LabelFNTSpriteActions.layer = nil
LabelFNTSpriteActions.__index = LabelFNTSpriteActions
LabelFNTSpriteActions.stepEntry = nil

function LabelFNTSpriteActions.onNodeEvent(tag)
    if tag == "enter" then
        LabelFNTSpriteActions.stepEntry = scheduler:scheduleScriptFunc(LabelFNTSpriteActions.step, 0.1, false)
    elseif tag == "exit" then
        scheduler:unscheduleScriptEntry(LabelFNTSpriteActions.stepEntry)
    end
end

function LabelFNTSpriteActions.create()
    cclog("LabelFNTSpriteActions.create")
    m_time = 0
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    LabelFNTSpriteActions.layer = layer

    -- Upper Label
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt", "Bitmap Font Atlas")
    layer:addChild(label)

    local s = cc.Director:getInstance():getWinSize()

    label:setPosition( cc.p(s.width/2, s.height/2) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )


    local BChar = label:getLetter(0)
    local FChar = label:getLetter(7)
    local AChar = label:getLetter(12)


    local rotate = cc.RotateBy:create(2, 360)
    local rot_4ever = cc.RepeatForever:create(rotate)

    local scale = cc.ScaleBy:create(2, 1.5)
    local scale_back = scale:reverse()

    local scale_seq = cc.Sequence:create(scale, scale_back)
    local scale_4ever = cc.RepeatForever:create(scale_seq)

    local jump = cc.JumpBy:create(0.5, cc.p(0, 0), 60, 1)
    local jump_4ever = cc.RepeatForever:create(jump)

    local fade_out = cc.FadeOut:create(1)
    local fade_in = cc.FadeIn:create(1)

    local seq = cc.Sequence:create(fade_out, fade_in)
    local fade_4ever = cc.RepeatForever:create(seq)

    BChar:runAction(rot_4ever)
    BChar:runAction(scale_4ever)
    FChar:runAction(jump_4ever)
    AChar:runAction(fade_4ever)


    -- Bottom Label
    local label2 = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt", "00.0")
    layer:addChild(label2, 0, kTagBitmapAtlas2)
    label2:setPosition( cc.p(s.width/2.0, 80) )

    local lastChar = label2:getLetter(3)
    lastChar:runAction(tolua.cast( rot_4ever:clone(), "cc.Action" ))

    layer:registerScriptHandler(LabelFNTSpriteActions.onNodeEvent)

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString( "Using fonts as Sprite objects. Some characters should rotate.")
    return layer
end

function LabelFNTSpriteActions.draw()
    local s = cc.Director:getInstance():getWinSize()
    cc.DrawPrimitives.drawLine( cc.p(0, s.height/2), cc.p(s.width, s.height/2) )
    cc.DrawPrimitives.drawLine( cc.p(s.width/2, 0), cc.p(s.width/2, s.height) )
end

function LabelFNTSpriteActions.step(dt)
    m_time = m_time + dt

    local string = string.format("%04.1f", m_time)

    local label1 = LabelFNTSpriteActions.layer:getChildByTag(kTagBitmapAtlas2)
    label1:setString(string)
end


--------------------------------------------------------------------
--
-- LabelFNTPadding
--
--------------------------------------------------------------------

local LabelFNTPadding = {}
LabelFNTPadding.layer = nil
function LabelFNTPadding:create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    LabelFNTPadding.layer = layer

    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest4.fnt", "abcdefg")
    layer:addChild(label)

    local s = cc.Director:getInstance():getWinSize()

    label:setPosition( cc.p(s.width/2, s.height/2) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("Testing padding")
    return layer
end

--------------------------------------------------------------------
--
-- LabelFNTOffset
--
--------------------------------------------------------------------
local LabelFNTOffset = {}
LabelFNTOffset.layer = nil

function LabelFNTOffset:create()
    cclog("LabelFNTOffset:create")
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    LabelFNTOffset.layer = layer

    local s = cc.Director:getInstance():getWinSize()
    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest5.fnt", "FaFeFiFoFu")
    layer:addChild(label)
    label:setPosition( cc.p(s.width/2, s.height/2+50) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )

    label = cc.Label:createWithBMFont("fonts/bitmapFontTest5.fnt", "fafefifofu")
    layer:addChild(label)
    label:setPosition( cc.p(s.width/2, s.height/2) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )

    label = cc.Label:createWithBMFont("fonts/bitmapFontTest5.fnt", "aeiou")
    layer:addChild(label)
    label:setPosition( cc.p(s.width/2, s.height/2-50) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("Rendering should be OK. Testing offset")
    return layer
end

--------------------------------------------------------------------
--
-- LabelFNTColor
--
--------------------------------------------------------------------
local LabelFNTColor = { layer= nil }
function LabelFNTColor:create()
    local layer = cc.Layer:create()
    LabelFNTColor.layer = layer
    Helper.initWithLayer(layer)

    local s = cc.Director:getInstance():getWinSize()

    local label = cc.Label:createWithBMFont("fonts/bitmapFontTest5.fnt", "Blue")
    label:setColor( cc.c3b(0, 0, 255 ))
    layer:addChild(label)
    label:setPosition( cc.p(s.width/2, s.height/4) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )

    label = cc.Label:createWithBMFont("fonts/bitmapFontTest5.fnt", "Red")
    layer:addChild(label)
    label:setPosition( cc.p(s.width/2, 2*s.height/4) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )
    label:setColor( cc.c3b(255, 0, 0) )

    label = cc.Label:createWithBMFont("fonts/bitmapFontTest5.fnt", "Green")
    layer:addChild(label)
    label:setPosition( cc.p(s.width/2, 3*s.height/4) )
    label:setAnchorPoint( cc.p(0.5, 0.5) )
    label:setColor( cc.c3b(0, 255, 0 ))
    label:setString("Green")

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("Testing color")
    return layer
end


--------------------------------------------------------------------
--
-- LabelTTFColor
--
--------------------------------------------------------------------
local LabelTTFColor = { layer= nil }
function LabelTTFColor:create()
    local layer = cc.Layer:create()
    LabelTTFColor.layer = layer
    Helper.initWithLayer(layer)

    local s = cc.Director:getInstance():getWinSize()
    local ttfConfig = {}
    ttfConfig.fontFilePath="fonts/arial.ttf"
    ttfConfig.fontSize=35

    local label1 = cc.Label:createWithTTF(ttfConfig,"Green", cc.VERTICAL_TEXT_ALIGNMENT_CENTER, s.width)
    label1:setColor( cc.c3b(0, 255, 0 ))
    layer:addChild(label1)
    label1:setPosition( cc.p(s.width/2, s.height/5 * 1.5) )
    label1:setAnchorPoint( cc.p(0.5, 0.5) )

    local label2 = cc.Label:createWithTTF(ttfConfig, "Red", cc.VERTICAL_TEXT_ALIGNMENT_CENTER, s.width)
    layer:addChild(label2)
    label2:setPosition( cc.p(s.width/2, s.height/5 * 2.0) )
    label2:setAnchorPoint( cc.p(0.5, 0.5) )
    label2:setColor( cc.c3b(255, 0, 0) )

    local label3 = cc.Label:createWithTTF(ttfConfig, "Blue", cc.VERTICAL_TEXT_ALIGNMENT_CENTER, s.width)
    layer:addChild(label3)
    label3:setPosition( cc.p(s.width/2, s.height/5 * 2.5) )
    label3:setAnchorPoint( cc.p(0.5, 0.5) )
    label3:setColor( cc.c3b(0, 0, 255 ))

    Helper.titleLabel:setString("New Label + .TTF")
    Helper.subtitleLabel:setString("Uses the new Label with TTF. Testing Color")
    return layer
end

--------------------------------------------------------------------
--
-- LabelFNTHundredLabels
--
--------------------------------------------------------------------

local LabelFNTHundredLabels = { layer = nil }
function LabelFNTHundredLabels:create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    LabelFNTHundredLabels.layer = layer

    math.randomseed(os.time())
    -- Upper Label
    local i = 0
    for i = 0, 100, 1 do
        local str = string.format("-%d-", i)
        local label = cc.Label:createWithBMFont("fonts/bitmapFontTest.fnt", str)
        layer:addChild(label)

        local s = cc.Director:getInstance():getWinSize()

        local p = cc.p( math.random() * s.width, math.random() * s.height)
        label:setPosition( p )
        label:setAnchorPoint(cc.p(0.5, 0.5))
    end

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("Creating several Labels using the same FNT file should be fast")
    return layer
end

--------------------------------------------------------------------
--
-- LabelFNTMultiLine
--
--
--------------------------------------------------------------------
local LabelFNTMultiLine = {}

function LabelFNTMultiLine:create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    local s = nil

    -- Left
    local label1 = cc.Label:createWithBMFont("fonts/bitmapFontTest3.fnt", " Multi line\nLeft")
    label1:setAnchorPoint(cc.p(0,0))
    layer:addChild(label1, 0, kTagBitmapAtlas1)

    s = label1:getContentSize()
    cclog("content size: %.2fx%.2f", s.width, s.height)


    -- Center
    local label2 = cc.Label:createWithBMFont("fonts/bitmapFontTest3.fnt", "Multi line\nCenter")
    label2:setAnchorPoint(cc.p(0.5, 0.5))
    layer:addChild(label2, 0, kTagBitmapAtlas2)

    s= label2:getContentSize()
    cclog("content size: %.2fx%.2f", s.width, s.height)

    -- right
    local label3 = cc.Label:createWithBMFont("fonts/bitmapFontTest3.fnt", "Multi line\nRight\nThree lines Three")
    label3:setAnchorPoint(cc.p(1, 1))
    layer:addChild(label3, 0, kTagBitmapAtlas3)

    s = label3:getContentSize()
    cclog("content size: %.2fx%.2f", s.width, s.height)

    label1:setPosition(VisibleRect:leftBottom())
    label2:setPosition(VisibleRect:center())
    label3:setPosition(VisibleRect:rightTop())
    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("Multiline + anchor point")
    return layer
end

--------------------------------------------------------------------
--
-- LabelFNTandTTFEmpty
--
--------------------------------------------------------------------

local LabelFNTandTTFEmpty = {}
LabelFNTandTTFEmpty.layer = nil
LabelFNTandTTFEmpty.setEmpty = false
LabelFNTandTTFEmpty.updateEntry = nil

function LabelFNTandTTFEmpty.onNodeEvent(tag)
    if tag == "enter" then
        LabelFNTandTTFEmpty.updateEntry = scheduler:scheduleScriptFunc(LabelFNTandTTFEmpty.updateStrings, 1.0, false)
    elseif tag == "exit" then
        scheduler:unscheduleScriptEntry(LabelFNTandTTFEmpty.updateEntry)
    end
end


function LabelFNTandTTFEmpty.create()
    cclog("LabelFNTandTTFEmpty.create")

    local layer = cc.Layer:create()
    LabelFNTandTTFEmpty.layer = layer
    Helper.initWithLayer(layer)

    local s = cc.Director:getInstance():getWinSize()

    -- cc.LabelBMFont
    local label1 = cc.Label:createWithBMFont("fonts/bitmapFontTest3.fnt", "", cc.TEXT_ALIGNMENT_CENTER,s.width)
    layer:addChild(label1, 0, kTagBitmapAtlas1)
    label1:setPosition(cc.p(s.width/2, s.height-100))

    -- cc.LabelTTF
    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize     = 48
    local label2 = cc.Label:createWithTTF(ttfConfig, "", cc.TEXT_ALIGNMENT_CENTER, s.width)
    layer:addChild(label2, 0, kTagBitmapAtlas2)
    label2:setAnchorPoint(cc.p(0.5, 0.5))
    label2:setPosition(cc.p(s.width/2, s.height/2))

    layer:registerScriptHandler(LabelFNTandTTFEmpty.onNodeEvent)

    LabelFNTandTTFEmpty.setEmpty = false
    Helper.titleLabel:setString("New Label : .FNT file & .TTF file")
    Helper.subtitleLabel:setString("2 empty labels: new Label + .FNT and new Label + .TTF")
    return layer
end

function LabelFNTandTTFEmpty.updateStrings(dt)
    local label1 = LabelFNTandTTFEmpty.layer:getChildByTag(kTagBitmapAtlas1)
    local label2 = LabelFNTandTTFEmpty.layer:getChildByTag(kTagBitmapAtlas2)

    if( LabelFNTandTTFEmpty.setEmpty == false) then
        label1:setString("not empty")
        label2:setString("not empty")
        LabelFNTandTTFEmpty.setEmpty = true
    else
        label1:setString("")
        label2:setString("")
        LabelFNTandTTFEmpty.setEmpty = false
    end
end

--------------------------------------------------------------------
--
-- LabelFNTRetina
--
--------------------------------------------------------------------
local LabelFNTRetina = {
    
}

function LabelFNTRetina.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    local s = cc.Director:getInstance():getWinSize()

    -- cc.LabelBMFont
    local label1 = cc.Label:createWithBMFont("fonts/konqa32.fnt", "TESTING RETINA DISPLAY")
    label1:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label1)
    label1:setPosition(cc.p(s.width/2, s.height/2))

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("loading arista16 or arista16-hd")
    return layer
end

--------------------------------------------------------------------
--
-- LabelFNTGlyphDesigner
--
--------------------------------------------------------------------
local LabelFNTGlyphDesigner = {}
function LabelFNTGlyphDesigner.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    local s = cc.Director:getInstance():getWinSize()

    local label1 = cc.Label:createWithBMFont("fonts/futura-48.fnt", "TESTING RETINA DISPLAY")
    label1:setAnchorPoint(cc.p(0.5, 0.5))

    layer:addChild(label1)
    label1:setPosition(cc.p(s.width/2, s.height/2))

    Helper.titleLabel:setString("New Label + .FNT file")
    Helper.subtitleLabel:setString("Testing Glyph Designer: you should see a font with shawdows and outline")
    return layer
end

--/ LabelTTFUnicodeChinese
local LabelTTFUnicodeChinese = {}
function LabelTTFUnicodeChinese.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .TTF file Chinese")
    Helper.subtitleLabel:setString("Testing new Label + TTF with Chinese character")

    local s = cc.Director:getInstance():getWinSize()
    local ttfConfig = {}
    ttfConfig.fontFilePath="fonts/wt021.ttf"
    ttfConfig.fontSize=55
    ttfConfig.glyphs=cc.GLYPHCOLLECTION_CUSTOM
    ttfConfig.customGlyphs="美好的一天啊"

    local label1 = cc.Label:createWithTTF(ttfConfig,"美好的一天啊", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label1:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label1)
    label1:setPosition(cc.p(s.width/2, s.height/2))

    return layer
end

------------
-- LabelFNTUnicodeChinese
------------

local LabelFNTUnicodeChinese = {}
function LabelFNTUnicodeChinese.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)

    local size = cc.Director:getInstance():getWinSize()
    local lable = cc.Label:createWithBMFont("fonts/bitmapFontChinese.fnt", "中国")
    lable:setAnchorPoint(cc.p(0.5,0.5))
    lable:setPosition(cc.p(size.width / 2, size.height /2))
    layer:addChild(lable)

    Helper.titleLabel:setString("New Label + .FNT file Chinese")
    Helper.subtitleLabel:setString("Testing new Label + FNT with Chinese character")

    return layer
end

-- LabelFNTMultiLineAlignment

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

local LabelFNTMultiLineAlignment = {
    _pLabelShouldRetain = nil,
    _pArrowsBarShouldRetain = nil,
    _pArrowsShouldRetain = nil,
    _pLastSentenceItem = nil,
    _drag = false,
}

function LabelFNTMultiLineAlignment.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    -- ask director the the window size
    local size = cc.Director:getInstance():getWinSize()

    -- create and initialize a Label
    LabelFNTMultiLineAlignment._pLabelShouldRetain = cc.Label:createWithBMFont("fonts/markerFelt.fnt", LongSentencesExample, cc.TEXT_ALIGNMENT_CENTER, size.width/1.5)
    LabelFNTMultiLineAlignment._pLabelShouldRetain:setAnchorPoint(cc.p(0.5, 0.5))
    LabelFNTMultiLineAlignment._pLabelShouldRetain:retain()

    LabelFNTMultiLineAlignment._pArrowsBarShouldRetain = cc.Sprite:create("Images/arrowsBar.png")
    LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:retain()
    LabelFNTMultiLineAlignment._pArrowsShouldRetain = cc.Sprite:create("Images/arrows.png")
    LabelFNTMultiLineAlignment._pArrowsShouldRetain:retain()

    cc.MenuItemFont:setFontSize(20)
    local longSentences = cc.MenuItemFont:create("Long Flowing Sentences")
    longSentences:registerScriptTapHandler(LabelFNTMultiLineAlignment.stringChanged)
    local lineBreaks    = cc.MenuItemFont:create("Short Sentences With Intentional Line Breaks")
    lineBreaks:registerScriptTapHandler(LabelFNTMultiLineAlignment.stringChanged)
    local mixed         = cc.MenuItemFont:create("Long Sentences Mixed With Intentional Line Breaks")
    mixed:registerScriptTapHandler(LabelFNTMultiLineAlignment.stringChanged)
    local stringMenu    = cc.Menu:create()
    stringMenu:addChild(longSentences)
    stringMenu:addChild(lineBreaks)
    stringMenu:addChild(mixed)
    stringMenu:alignItemsVertically()

    longSentences:setColor(cc.c3b(255, 0, 0))
    LabelFNTMultiLineAlignment._pLastSentenceItem = longSentences

    longSentences:setTag(LongSentences)
    lineBreaks:setTag(LineBreaks)
    mixed:setTag(Mixed)

    cc.MenuItemFont:setFontSize(30)

    local left          = cc.MenuItemFont:create("Left")
    left:registerScriptTapHandler(LabelFNTMultiLineAlignment.alignmentChanged)
    local center        = cc.MenuItemFont:create("Center")
    center:registerScriptTapHandler(LabelFNTMultiLineAlignment.alignmentChanged)
    local right         = cc.MenuItemFont:create("Right")
    right:registerScriptTapHandler(LabelFNTMultiLineAlignment.alignmentChanged)

    local alignmentMenu = cc.Menu:create()
    alignmentMenu:addChild(left)
    alignmentMenu:addChild(center)
    alignmentMenu:addChild(right)

    alignmentMenu:alignItemsHorizontallyWithPadding(alignmentItemPadding)

    center:setColor(cc.c3b(255, 0, 0))
    LabelFNTMultiLineAlignment._pLastAlignmentItem = center
    left:setTag(LeftAlign)
    center:setTag(CenterAlign)
    right:setTag(RightAlign)

    -- position the label on the center of the screen
    LabelFNTMultiLineAlignment._pLabelShouldRetain:setPosition(cc.p(size.width/2, size.height/2))

    LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:setVisible(false)

    local arrowsWidth = (ArrowsMax - ArrowsMin) * size.width
    LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:setScaleX(arrowsWidth / LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:getContentSize().width)
    LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:setPosition( ((ArrowsMax + ArrowsMin) / 2) * size.width, LabelFNTMultiLineAlignment._pLabelShouldRetain:getPositionY() )

    LabelFNTMultiLineAlignment.snapArrowsToEdge()

    stringMenu:setPosition(cc.p(size.width/2, size.height - menuItemPaddingCenter))
    alignmentMenu:setPosition(cc.p(size.width/2, menuItemPaddingCenter+15))

    layer:addChild(LabelFNTMultiLineAlignment._pLabelShouldRetain)
    layer:addChild(LabelFNTMultiLineAlignment._pArrowsBarShouldRetain)
    layer:addChild(LabelFNTMultiLineAlignment._pArrowsShouldRetain)
    layer:addChild(stringMenu)
    layer:addChild(alignmentMenu)
    layer:registerScriptHandler(LabelFNTMultiLineAlignment.onNodeEvent)

    local function onTouchesBegan(touches, event)
        local location = touches[1]:getLocationInView()
        if cc.rectContainsPoint(LabelFNTMultiLineAlignment._pArrowsShouldRetain:getBoundingBox(), cc.p(location.x, location.y)) then
            LabelFNTMultiLineAlignment._drag = true
            LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:setVisible(true)
        end
    end

    local function onTouchesMoved(touches, event)
       if LabelFNTMultiLineAlignment._drag == false then
            return
        end

        local winSize = cc.Director:getInstance():getWinSize()
        local location = touches[1]:getLocationInView()

        LabelFNTMultiLineAlignment._pArrowsShouldRetain:setPosition(
            math.max(math.min(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
            LabelFNTMultiLineAlignment._pArrowsShouldRetain:getPositionY())

        local labelWidth = math.abs(LabelFNTMultiLineAlignment._pArrowsShouldRetain:getPositionX() - LabelFNTMultiLineAlignment._pLabelShouldRetain:getPositionX()) * 2

        LabelFNTMultiLineAlignment._pLabelShouldRetain:setWidth(labelWidth)
    end

    local  function onTouchesEnded(touch, event)
        LabelFNTMultiLineAlignment._drag = false
        LabelFNTMultiLineAlignment.snapArrowsToEdge()
        LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:setVisible(false)
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()    
    listener:registerScriptHandler(onTouchesBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
    listener:registerScriptHandler(onTouchesEnded,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    return layer
end

function LabelFNTMultiLineAlignment.onNodeEvent(tag)
    if tag == "onexit" then
        LabelFNTMultiLineAlignment._pLabelShouldRetain:release()
        LabelFNTMultiLineAlignment._pArrowsBarShouldRetain:release()
        LabelFNTMultiLineAlignment._pArrowsShouldRetain:release()
    end
end



function LabelFNTMultiLineAlignment.stringChanged(tag, sender)
    local item = tolua.cast(sender, "cc.MenuItemFont")
    item:setColor(cc.c3b(255, 0, 0))
    LabelFNTMultiLineAlignment._pLastAlignmentItem:setColor(cc.c3b(255, 255, 255))
    LabelFNTMultiLineAlignment._pLastAlignmentItem = item

    if item:getTag() == LongSentences then
        LabelFNTMultiLineAlignment._pLabelShouldRetain:setString(LongSentencesExample)
    elseif item:getTag() == LineBreaks then
        LabelFNTMultiLineAlignment._pLabelShouldRetain:setString(LineBreaksExample)
    elseif item:getTag() == Mixed then
        LabelFNTMultiLineAlignment._pLabelShouldRetain:setString(MixedExample)
    end

    LabelFNTMultiLineAlignment.snapArrowsToEdge()
end

function LabelFNTMultiLineAlignment.alignmentChanged(tag, sender)
    -- cclog("LabelFNTMultiLineAlignment.alignmentChanged, tag:"..tag)
    local item = tolua.cast(sender, "cc.MenuItemFont")
    item:setColor(cc.c3b(255, 0, 0))
    LabelFNTMultiLineAlignment._pLastAlignmentItem:setColor(cc.c3b(255, 255, 255))
    LabelFNTMultiLineAlignment._pLastAlignmentItem = item

    if tag == LeftAlign then
        cclog("LeftAlign")
        LabelFNTMultiLineAlignment._pLabelShouldRetain:setAlignment(cc.TEXT_ALIGNMENT_LEFT)
    elseif tag == CenterAlign then
        LabelFNTMultiLineAlignment._pLabelShouldRetain:setAlignment(cc.TEXT_ALIGNMENT_CENTER)
    elseif tag == RightAlign then
        LabelFNTMultiLineAlignment._pLabelShouldRetain:setAlignment(cc.TEXT_ALIGNMENT_RIGHT)
    end

    LabelFNTMultiLineAlignment.snapArrowsToEdge()
end

function LabelFNTMultiLineAlignment.snapArrowsToEdge()
    LabelFNTMultiLineAlignment._pArrowsShouldRetain:setPosition(
        LabelFNTMultiLineAlignment._pLabelShouldRetain:getPositionX() + LabelFNTMultiLineAlignment._pLabelShouldRetain:getContentSize().width/2, LabelFNTMultiLineAlignment._pLabelShouldRetain:getPositionY()
    )
end

------------------------------------
----- LabelFNTUNICODELanguages
------------------------------------
local LabelFNTUNICODELanguages = {}
function LabelFNTUNICODELanguages.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .FNT + UNICODE")
    Helper.subtitleLabel:setString("You should see 3 differnt labels:\nIn Spanish, Chinese, and Japanese")

    local s = cc.Director:getInstance():getWinSize()
    
    local label1 = cc.Label:createWithBMFont("fonts/arial-unicode-26.fnt", "Buen día", cc.TEXT_ALIGNMENT_CENTER, 200)
    label1:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label1)
    label1:setPosition(cc.p(s.width/2, s.height/4*3))
    
    local label2 = cc.Label:createWithBMFont("fonts/arial-unicode-26.fnt", "美好的一天")
    label2:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label2)
    label2:setPosition(cc.p(s.width/2, s.height/4*2))
    
    local label3 = cc.Label:createWithBMFont("fonts/arial-unicode-26.fnt", "良い一日を")
    label3:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label3)
    label3:setPosition(cc.p(s.width/2, s.height/4*1))

    return layer
end

----------------------------------------------------------
----- LabelTTFAlignmentNew
----------------------------------------------------------
local LabelTTFAlignmentNew = {}
function LabelTTFAlignmentNew.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + TTF")
    Helper.subtitleLabel:setString("Tests alignment values")

    local s = cc.Director:getInstance():getWinSize()
    local ttfConfig = {}
    ttfConfig.fontFilePath="fonts/tahoma.ttf"
    ttfConfig.fontSize=32
    local ttf0 = cc.Label:createWithTTF(ttfConfig, "Alignment 0\nnew line", cc.TEXT_ALIGNMENT_LEFT)
    ttf0:setPosition(cc.p(s.width/2,(s.height/6)*2 - 30))
    ttf0:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(ttf0)
    
    local ttf1 = cc.Label:createWithTTF(ttfConfig, "Alignment 1\nnew line", cc.TEXT_ALIGNMENT_CENTER)
    ttf1:setPosition(cc.p(s.width/2,(s.height/6)*3 - 30))
    ttf1:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(ttf1)
    
    local ttf2 = cc.Label:createWithTTF(ttfConfig, "Alignment 2\nnew line", cc.TEXT_ALIGNMENT_RIGHT)
    ttf2:setPosition(cc.p(s.width/2,(s.height/6)*4 - 30))
    ttf2:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(ttf2)

    return layer
end


-------------------------------------
----- LabelTTFUnicodeNew
-------------------------------------
local LabelTTFUnicodeNew = {}
function LabelTTFUnicodeNew.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + TTF unicode")
    Helper.subtitleLabel:setString("Uses the new Label with TTF. Testing unicode")

    local s = cc.Director:getInstance():getWinSize()
    local vStep = s.height/9
    local vSize = s.height

    local ttfConfig = {}
    ttfConfig.fontFilePath="fonts/arial.ttf"
    ttfConfig.fontSize=45
    ttfConfig.glyphs=cc.GLYPHCOLLECTION_ASCII
    
    local label1 =  cc.Label:createWithTTF(ttfConfig,"Buen día, ¿cómo te llamas?", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label1:setAnchorPoint(cc.p(0.5,0.5))
    label1:setPosition(cc.p(s.width/2, vSize - vStep * 4.5))
    layer:addChild(label1)
    
    local label2 = cc.Label:createWithTTF(ttfConfig, "In welcher Straße haben Sie gelebt?", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label2:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label2)
    label2:setPosition(cc.p(s.width/2, vSize - vStep * 5.5))
    
    ttfConfig.fontFilePath = "fonts/wt021.ttf"
    ttfConfig.glyphs = cc.GLYPHCOLLECTION_CUSTOM
    ttfConfig.customGlyphs = "美好的一天"
    local label3 = cc.Label:createWithTTF(ttfConfig, "美好的一天", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label3:setAnchorPoint(cc.p(0.5,0.5))
    layer:addChild(label3)
    label3:setPosition(cc.p(s.width/2, vSize - vStep * 6.5))

    return layer
end


----------------------------------
--
--LabelFNTBounds
--
----------------------------------
local LabelFNTBounds = {}
function LabelFNTBounds.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .FNT + Bounds")
    Helper.subtitleLabel:setString("You should see string enclosed by a box")
    
    local s = cc.Director:getInstance():getWinSize()
    
    local colorlayer = cc.LayerColor:create(cc.c4b(128,128,128,255))
    layer:addChild(colorlayer, -10)
    
    -- cc.LabelBMFont
    local label1 = cc.Label:createWithBMFont("fonts/boundsTestFont.fnt", "Testing Glyph Designer", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label1:setAnchorPoint(cc.p(0.5, 0.5))
    
    layer:addChild(label1)
    label1:setPosition(cc.p(s.width/2, s.height/2))
    return layer
end

function LabelFNTBounds.draw()
    -- cc.size labelSize = label1:getContentSize()
    -- cc.size origin = cc.Director:getInstance():getWinSize()
    
    -- origin.width = origin.width / 2 - (labelSize.width / 2)
    -- origin.height = origin.height / 2 - (labelSize.height / 2)
    
    -- cc.p vertices[4]=
    
    --     cc.p(origin.width, origin.height),
    --     cc.p(labelSize.width + origin.width, origin.height),
    --     cc.p(labelSize.width + origin.width, labelSize.height + origin.height),
    --     cc.p(origin.width, labelSize.height + origin.height)
    -- end
    -- ccDrawPoly(vertices, 4, true)
end


--------------------------------------------------------
----- LabelTTFLongLineWrapping
--------------------------------------------------------
local LabelTTFLongLineWrapping = {}
function LabelTTFLongLineWrapping.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .TTF")
    Helper.subtitleLabel:setString("Uses the new Label with TTF. Testing auto-wrapping")

    local s = cc.Director:getInstance():getWinSize()
    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 28
    local label1 = cc.Label:createWithTTF(ttfConfig, LongSentencesExample, cc.TEXT_ALIGNMENT_LEFT, s.width)
    label1:setAnchorPoint(cc.p(0.5,1.0))
    label1:setPosition(cc.p(s.width/2, s.height/2))
    layer:addChild(label1)
    return layer
end

--------------------------------------------------------------------
--
-- LabelTTFDynamicAlignment
--
--------------------------------------------------------------------

local LabelTTFDynamicAlignment = {
    _layer       = nil,
    _label      = nil,
    _eHorizAlign = cc.TEXT_ALIGNMENT_LEFT,
}

function LabelTTFDynamicAlignment.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    LabelTTFDynamicAlignment._layer       = layer
    LabelTTFDynamicAlignment._label       = nil
    LabelTTFDynamicAlignment._eHorizAlign = cc.TEXT_ALIGNMENT_LEFT

    local s = cc.Director:getInstance():getWinSize()
    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 45
    LabelTTFDynamicAlignment._label = cc.Label:createWithTTF(ttfConfig, LongSentencesExample, cc.TEXT_ALIGNMENT_CENTER, s.width)
    LabelTTFDynamicAlignment._label:setPosition( cc.p(s.width/2, s.height/2) )
    LabelTTFDynamicAlignment._label:setAnchorPoint(cc.p(0.5, 0.5))
    layer:addChild(LabelTTFDynamicAlignment._label)

    cc.MenuItemFont:setFontSize(30)
    local item1 = cc.MenuItemFont:create("Left")
    item1:registerScriptTapHandler(LabelTTFDynamicAlignment.setAlignmentLeft)
    local item2 = cc.MenuItemFont:create("Center")
    item2:registerScriptTapHandler(LabelTTFDynamicAlignment.setAlignmentCenter)
    local item3 = cc.MenuItemFont:create("Right")
    item3:registerScriptTapHandler(LabelTTFDynamicAlignment.setAlignmentRight)

    local menu = cc.Menu:create()
    menu:addChild(item1)
    menu:addChild(item2)
    menu:addChild(item3)
    menu:alignItemsVerticallyWithPadding(4)
    menu:setPosition(cc.p(50, s.height / 4))
    layer:addChild(menu)

    Helper.titleLabel:setString("New Label + .TTF")
    Helper.subtitleLabel:setString("Uses the new Label with TTF. Testing alignment")

    LabelTTFDynamicAlignment.updateAlignment()

    return layer
end

function LabelTTFDynamicAlignment.updateAlignment()
    local s = cc.Director:getInstance():getWinSize()
    LabelTTFDynamicAlignment._label:setAlignment(LabelTTFDynamicAlignment._eHorizAlign)
end

function LabelTTFDynamicAlignment.setAlignmentLeft(pSender)
    LabelTTFDynamicAlignment._eHorizAlign = cc.TEXT_ALIGNMENT_LEFT
    LabelTTFDynamicAlignment.updateAlignment()
end

function LabelTTFDynamicAlignment.setAlignmentCenter(pSender)
    LabelTTFDynamicAlignment._eHorizAlign = cc.TEXT_ALIGNMENT_CENTER
    LabelTTFDynamicAlignment.updateAlignment()
end

function LabelTTFDynamicAlignment.setAlignmentRight(pSender)
    LabelTTFDynamicAlignment._eHorizAlign = cc.TEXT_ALIGNMENT_RIGHT
    LabelTTFDynamicAlignment.updateAlignment()
end


--------------------------------------------------------
----- LabelTTFFontsTestNew
--------------------------------------------------------
local LabelTTFFontsTestNew = {}
function LabelTTFFontsTestNew.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + TTF")
    Helper.subtitleLabel:setString("")

    local s = cc.Director:getInstance():getWinSize()

    local ttfPaths = 
    {
        "fonts/A Damn Mess.ttf",
        "fonts/Abberancy.ttf",
        "fonts/Abduction.ttf",
        "fonts/American Typewriter.ttf",
        "fonts/Paint Boy.ttf",
        "fonts/Schwarzwald Regular.ttf",
        "fonts/Scissor Cuts.ttf",
    }
    local ttfConfig = {}
    ttfConfig.fontFilePath = ttfPaths[0]
    ttfConfig.fontSize = 40
    for i=1, table.getn(ttfPaths) do
        ttfConfig.fontFilePath = ttfPaths[i]
        local label = cc.Label:createWithTTF( ttfConfig, ttfPaths[i], cc.TEXT_ALIGNMENT_CENTER, 0)
        if nil ~= label then
            label:setPosition( cc.p(s.width/2, ((s.height * 0.6)/table.getn(ttfPaths) * (i -1)) + (s.height/5)))
            layer:addChild(label)
            
            label:setAnchorPoint(cc.p(0.5, 0.5))
        else
            print(string.format("ERROR: Cannot load: %s",ttfPaths[i]))
        end
    end
    
    return layer
end


--------------------------------------------------------
----- LabelBMFontTestNew
--------------------------------------------------------
local LabelBMFontTestNew = {}
function LabelBMFontTestNew.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + FNT")
    Helper.subtitleLabel:setString("Uses the new Label with .FNT file")

    local s = cc.Director:getInstance():getWinSize()
    
    local label1 = cc.Label:createWithBMFont("fonts/bitmapFontTest2.fnt", "Hello World, this is testing the new Label using fnt file", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label1:setAnchorPoint(cc.p(0.5,0.5))
    label1:setPosition(cc.p(s.width/2, s.height/2))
    layer:addChild(label1)
    return layer
end


--------------------------------------------------------
----- LabelTTFDistanceField
--------------------------------------------------------
local LabelTTFDistanceField = {}
function LabelTTFDistanceField.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .TTF")
    Helper.subtitleLabel:setString("Testing rendering base on DistanceField")

    local s = cc.Director:getInstance():getWinSize()
    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 80
    ttfConfig.glyphs   = cc.GLYPHCOLLECTION_DYNAMIC
    ttfConfig.customGlyphs = nil
    ttfConfig.distanceFieldEnabled = true
    
    local label1 = cc.Label:createWithTTF(ttfConfig,"Distance Field",cc.TEXT_ALIGNMENT_CENTER,s.width)
    label1:setAnchorPoint(cc.p(0.5,0.5))
    label1:setPosition(cc.p(s.width/2, s.height/2))
    label1:setColor( cc.c3b(0, 255, 0) )
    local action = cc.Sequence:create(cc.DelayTime:create(1.0),
        cc.ScaleTo:create(6.0,5.0,5.0),
        cc.ScaleTo:create(6.0,1.0,1.0))
    label1:runAction(cc.RepeatForever:create(action))
    layer:addChild(label1)

    local label2 = cc.Label:createWithTTF(ttfConfig,"Distance Field",cc.TEXT_ALIGNMENT_CENTER,s.width)
    label2:setPosition( cc.p(s.width/2, s.height/5) )
    label2:setColor( cc.c3b(255, 0, 0))
    label2:setAnchorPoint(cc.p(0.5, 0.5))
    layer:addChild(label2)

    return layer
end

--------------------------------------------------------
----- LabelTTFDistanceFieldEffect
--------------------------------------------------------
local LabelTTFDistanceFieldEffect = {}
function LabelTTFDistanceFieldEffect.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .TTF")
    Helper.subtitleLabel:setString("Testing effect base on DistanceField")

    local s = cc.Director:getInstance():getWinSize()

    local col = cc.LayerColor:create( cc.c4b(200, 191, 231, 255))
    layer:addChild(col)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 80
    ttfConfig.glyphs   = cc.GLYPHCOLLECTION_DYNAMIC
    ttfConfig.customGlyphs = nil
    ttfConfig.distanceFieldEnabled = true
    
    local label1 = cc.Label:createWithTTF(ttfConfig,"Glow",cc.TEXT_ALIGNMENT_CENTER,s.width)
    label1:setAnchorPoint(cc.p(0.5,0.5))
    label1:setPosition(cc.p(s.width/2, s.height/2))
    label1:setColor( cc.c3b(0, 255, 0) )
    label1:setLabelEffect(cc.LabelEffect.GLOW, cc.c3b(255, 255, 0))
    layer:addChild(label1)

    local label2 = cc.Label:createWithTTF(ttfConfig,"Outline",cc.TEXT_ALIGNMENT_CENTER,s.width)
    label2:setPosition( cc.p(s.width/2, s.height * 0.375))
    label2:setColor( cc.c3b(255, 0, 0))
    label2:setAnchorPoint(cc.p(0.5, 0.5))
    label2:setLabelEffect(cc.LabelEffect.OUTLINE, cc.c3b(0, 0, 255))
    layer:addChild(label2)

    local label3 = cc.Label:createWithTTF(ttfConfig,"Shadow",cc.TEXT_ALIGNMENT_CENTER,s.width)
    label3:setPosition( cc.p(s.width/2, s.height * 0.25))
    label3:setColor( cc.c3b(255, 0, 0))
    label3:setAnchorPoint(cc.p(0.5, 0.5))
    label3:setLabelEffect(cc.LabelEffect.SHADOW, cc.c3b(0, 0, 0))
    layer:addChild(label3)

    return layer
end


--------------------------------------------------------------------
--
-- LabelCharMapTest
--
--------------------------------------------------------------------
local LabelCharMapTest = {}

function LabelCharMapTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + char map file")
    Helper.subtitleLabel:setString("Updating label should be fast.")

    time = 0

    local label1 = cc.Label:createWithCharMap("fonts/tuffy_bold_italic-charmap.plist")
    layer:addChild(label1, 0, kTagSprite1)
    label1:setPosition( cc.p(10,100) )
    label1:setOpacity( 200 )

    local label2 = cc.Label:createWithCharMap("fonts/tuffy_bold_italic-charmap.plist")
    layer:addChild(label2, 0, kTagSprite2)
    label2:setPosition( cc.p(10,160) )
    label2:setOpacity( 32 )

    local label3 = cc.Label:createWithCharMap("fonts/tuffy_bold_italic-charmap.png", 48, 64, 32)--32 means Space key
    label3:setString("123 Test")
    layer:addChild(label3, 0, kTagSprite3)
    label3:setPosition(cc.p(10,220))

    local function step(dt)
        time = time + dt
        local info = string.format("%2.2f Test", time)

        local label1 = layer:getChildByTag(kTagSprite1)
        label1:setString(info)

        local label2 = layer:getChildByTag(kTagSprite2)
        info = string.format("%d",time)
        label2:setString(info)
    end

    layer:scheduleUpdateWithPriorityLua(step, 0)

    function onNodeEvent(tag)
        if tag == "exit" then
            layer:unscheduleUpdate()
        end
    end

    layer:registerScriptHandler(onNodeEvent)

    return layer
end


--------------------------------------------------------
----- LabelCrashTest
--------------------------------------------------------
local LabelCrashTest = {}
function LabelCrashTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("New Label + .TTF")
    Helper.subtitleLabel:setString("Testing rendering base on DistanceField")

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize     = 80
    ttfConfig.glyphs       = cc.GLYPHCOLLECTION_DYNAMIC
    ttfConfig.customGlyphs = nil
    ttfConfig.distanceFieldEnabled = true
    local s = cc.Director:getInstance():getWinSize()
    local label1 = cc.Label:createWithTTF(ttfConfig,"Test崩溃123", cc.TEXT_ALIGNMENT_CENTER, s.width)
    label1:setPosition( cc.p(s.width/2, s.height/2) )
    label1:setAnchorPoint(cc.p(0.5, 0.5))
    layer:addChild(label1)

    return layer
end

------------
function LabelTestNew()
    cclog("LabelTestNew")
    m_time = 0
    local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        LabelFNTColorAndOpacity.create,
        LabelFNTSpriteActions.create,
        LabelFNTPadding.create,
        LabelFNTOffset.create,
        LabelFNTColor.create,
        LabelTTFColor.create,
        LabelFNTHundredLabels.create,
        LabelFNTMultiLine.create,
        LabelFNTandTTFEmpty.create,
        LabelFNTRetina.create,
        LabelFNTGlyphDesigner.create,
        LabelTTFUnicodeChinese.create,
        LabelFNTUnicodeChinese.create,
        LabelFNTMultiLineAlignment.create,
        LabelFNTUNICODELanguages.create,
        LabelTTFUnicodeNew.create,
        LabelTTFAlignmentNew.create,
        LabelFNTBounds.create,
        LabelTTFLongLineWrapping.create,
        LabelTTFDynamicAlignment.create,
        LabelTTFFontsTestNew.create,
        LabelBMFontTestNew.create,
        LabelTTFDistanceField.create,
        LabelTTFDistanceFieldEffect.create,
        LabelCharMapTest.create,
        LabelCrashTest.create,
    }
    scene:addChild(LabelFNTColorAndOpacity.create())
    scene:addChild(CreateBackMenuItem())
    return scene
end
