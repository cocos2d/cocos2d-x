local function AccelerometerMainLayer()

	local function title()
		return "AccelerometerTest"
	end
	local pLayer = cc.Layer:create()
	
	pLayer:setAccelerometerEnabled(true)
	
	local pLabel = cc.LabelTTF:create(title(), "Arial", 32)
    pLayer:addChild(pLabel, 1)
    pLabel:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 50) )

    local pBall = cc.Sprite:create("Images/ball.png")
    pBall:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))
    pLayer:addChild(pBall)

    pBall:retain()
    
    local function didAccelerate(x,y,z,timestamp)
    	local pDir = cc.Director:getInstance()

    	if nil == pBall then
    		return
    	end

    	local szBall  = pBall:getContentSize()
    	local ptNowX,ptNowY = pBall:getPosition()
    	
    	local ptTmp = pDir:convertToUI(cc.p(ptNowX,ptNowY))	
    	ptTmp.x   = ptTmp.x + x * 9.81
    	ptTmp.y   = ptTmp.y - y * 9.81


    	local ptNext = pDir:convertToGL(cc.p(ptTmp.x,ptTmp.y))
    	local nMinX  = math.floor(VisibleRect:left().x + szBall.width / 2.0)
    	local nMaxX  = math.floor(VisibleRect:right().x - szBall.width / 2.0)
   		if ptNext.x <   nMinX then
   			ptNext.x = nMinX
   		elseif ptNext.x > nMaxX then
   			ptNext.x = nMaxX
   		end
   		
   		local nMinY  = math.floor(VisibleRect:bottom().y + szBall.height / 2.0)
    	local nMaxY  = math.floor(VisibleRect:top().y   - szBall.height / 2.0)
   		if ptNext.y <   nMinY then
   			ptNext.y = nMinY
   		elseif ptNext.y > nMaxY then
   			ptNext.y = nMaxY
   		end
   		
    	pBall:setPosition(cc.p(ptNext.x,ptNext.y))
    	
    	
    end
    
    pLayer:registerScriptAccelerateHandler(didAccelerate)   
    
    return pLayer
end


function AccelerometerMain()
	cclog("AccelerometerMain")
	local scene = cc.Scene:create()
	scene:addChild(AccelerometerMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
