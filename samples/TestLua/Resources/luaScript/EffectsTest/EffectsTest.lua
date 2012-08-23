require "EffectsTest/EffectsName"


local ActionIdx = 0
local size = CCDirector:sharedDirector():getWinSize()
local kTagTextLayer  = 1
local kTagBackground = 1
local kTagLabel      = 2

function initWithLayer(layer)

end


--------------------------------------
-- Entrance
--------------------------------------
function EffectsTest()
	cclog("EffectsTest")
	local scene = CCScene:create()
	local layer = CCLayerColor:create(ccc4(32,128,32,255))

	initWithLayer(layer)

	scene:addChild(CreateBackMenuItem())
	scene:addChild(layer)

	return scene
end
