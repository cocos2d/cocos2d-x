local function AccelerometerMainLayer()

	local function title()
		return "AccelerometerTest"
	end
	local pLayer = CCLayer:create()
	
	pLayer:setAccelerometerEnabled(true)
	
	local pLabel = CCLabelTTF:create(title(), "Arial", 32)
    pLayer:addChild(pLabel, 1)
    pLabel:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 50) )

    local pBall = CCSprite:create("Images/ball.png")
    pBall:setPosition(ccp(VisibleRect:center().x, VisibleRect:center().y))
    pLayer:addChild(pBall)

    pBall:retain()
    
    local function didAccelerate(x,y,z,timestamp)
    	local pDir = CCDirector:sharedDirector()

    	if nil == pBall then
    		return
    	end

    	local szBall  = pBall:getContentSize()

    	local ptNowX,ptNowY = pBall:getPosition()
    	
    	local ptTmp = pDir:convertToUI(CCPointMake(ptNowX,ptNowY))	
    	ptTmp.x   = ptTmp.x + x * 9.81
    	ptTmp.y   = ptTmp.y - y * 9.81


    	local ptNext = pDir:convertToGL(CCPointMake(ptTmp.x,ptTmp.y))
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
   		
    	pBall:setPosition(CCPointMake(ptNext.x,ptNext.y))
    	
    	
    end
    
    pLayer:registerScriptAccelerateHandler(didAccelerate)   
    
    return pLayer
end


function AccelerometerMain()
	cclog("AccelerometerMain")
	local scene = CCScene:create()
	scene:addChild(AccelerometerMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
