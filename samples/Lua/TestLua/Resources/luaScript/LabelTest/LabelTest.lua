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
LabelAtlasTest.__index = LabelAtlasTest
local m_time = 0

function LabelAtlasTest.step(dt)
   if tolua.isnull(Helper.currentLayer) == true then
	  return
   end

    m_time = m_time + dt
    local string = string.format("%2.2f Test", m_time)

	local label1_origin = Helper.currentLayer:getChildByTag(kTagSprite1)
    local label1 = tolua.cast(label1_origin, "CCLabelAtlas")
    label1:setString(string)

	local label2_origin = Helper.currentLayer:getChildByTag(kTagSprite2)
    local label2 = tolua.cast(label2_origin, "CCLabelAtlas")
    string = string.format("%d", m_time)

    label2:setString(string)
end

function LabelAtlasTest.create()
    m_time = 0
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)

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

	return layer
end

--------------------------------------------------------------------
-- 
-- LabelAtlasColorTest
-- 
--------------------------------------------------------------------

local LabelAtlasColorTest = {}
LabelAtlasColorTest.__index = LabelAtlasColorTest
local m_time = 0

function LabelAtlasColorTest.step(dt)
   if tolua.isnull(Helper.currentLayer) == true then
	  return
   end

    m_time = m_time + dt
    local string = string.format("%2.2f Test", m_time)

	local label1_origin = Helper.currentLayer:getChildByTag(kTagSprite1)
    local label1 = tolua.cast(label1_origin, "CCLabelAtlas")
    label1:setString(string)

	local label2_origin = Helper.currentLayer:getChildByTag(kTagSprite2)
    local label2 = tolua.cast(label2_origin, "CCLabelAtlas")
    string = string.format("%d", m_time)

    label2:setString(string)
end

function LabelAtlasColorTest.create()
    m_time = 0
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local label1 = CCLabelAtlas:create("123 Test", "fonts/tuffy_bold_italic-charmap.plist")
	layer:addChild(label1, 0, kTagSprite1)
	label1:setPosition( ccp(10,100) )
	label1:setOpacity( 200 )

	local label2 = CCLabelAtlas:create("0123456789", "fonts/tuffy_bold_italic-charmap.plist")
	layer:addChild(label2, 0, kTagSprite2)
	label2:setPosition( ccp(10,200) )
	label2:setOpacity( 32 )
	layer:scheduleUpdateWithPriorityLua(LabelAtlasColorTest.step, 0)

	Helper.titleLabel:setString("LabelAtlas")
	Helper.subtitleLabel:setString("Updating label should be fast")

	return layer
end

--------------------------------------------------------------------
-- 
-- LabelAtlasColorTest
-- 
--------------------------------------------------------------------

local LabelAtlasColorTest = {}
LabelAtlasColorTest.__index = LabelAtlasColorTest
local m_time = 0

function LabelAtlasColorTest.step(dt)
   if tolua.isnull(Helper.currentLayer) == true then
	  return
   end

    m_time = m_time + dt
    local string = string.format("%2.2f Test", m_time)

	local label1_origin = Helper.currentLayer:getChildByTag(kTagSprite1)
    local label1 = tolua.cast(label1_origin, "CCLabelAtlas")
    label1:setString(string)

	local label2_origin = Helper.currentLayer:getChildByTag(kTagSprite2)
    local label2 = tolua.cast(label2_origin, "CCLabelAtlas")
    string = string.format("%d", m_time)

    label2:setString(string)
end

function LabelAtlasColorTest.actionFinishCallback()
   cclog("Action finished")
end

function LabelAtlasColorTest.create()
    m_time = 0
    local layer = CCLayer:create()
	Helper.initWithLayer(layer)

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
Atlas3.__index = Atlas3

function Atlas3.create()
    cclog("Atlas3.create")
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

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

    layer:scheduleUpdateWithPriorityLua(Atlas3.step, 0)

	Helper.titleLabel:setString( "CCLabelBMFont" )
	Helper.subtitleLabel:setString( "Testing alignment. Testing opacity + tint" )

	return layer
end

function Atlas3.step(dt)
    m_time = m_time + dt
	local string = string.format("%2.2f Test j", m_time)
    
    local label1 = tolua.cast(Helper.currentLayer:getChildByTag(kTagBitmapAtlas1), "CCLabelBMFont")
    label1:setString(string)
    
    local label2 = tolua.cast(Helper.currentLayer:getChildByTag(kTagBitmapAtlas2), "CCLabelBMFont")
    label2:setString(string)
    
    local label3 = tolua.cast(Helper.currentLayer:getChildByTag(kTagBitmapAtlas3), "CCLabelBMFont")
    label3:setString(string)
end


function LabelTest()
   cclog("LabelTest")
   m_time = 0
   local scene = CCScene:create()

   Helper.createFunctionTable = {
	  LabelAtlasTest.create,
	  LabelAtlasColorTest.create,
	  Atlas3.create
--	  Atlas4,			  
--	  Atlas5,			  
--	  Atlas6,			  
--	  AtlasBitmapColor,	  
--	  AtlasFastBitmap,	  
--	  BitmapFontMultiLine,
--	  LabelsEmpty,		  
--	  LabelBMFontHD,	  
--	  LabelAtlasHD,		  
--	  LabelGlyphDesigner, 
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
