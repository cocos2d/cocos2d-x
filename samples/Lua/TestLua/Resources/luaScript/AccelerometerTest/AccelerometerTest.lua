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
    	
    	ptNowX  = ptNowX - x 
    	ptNowY  = ptNowY - y 


    	local minX  = math.floor(VisibleRect:left().x + szBall.width / 2.0)
    	local maxX  = math.floor(VisibleRect:right().x - szBall.width / 2.0)
   		if ptNowX <   minX then
   			ptNowX = minX
   		elseif ptNowX > maxX then
   			ptNowX = maxX
   		end
   		
   		local minY  = math.floor(VisibleRect:bottom().y + szBall.height / 2.0)
    	local maxY  = math.floor(VisibleRect:top().y   - szBall.height / 2.0)
   		if ptNowY <   minY then
   			ptNowY = minY
   		elseif ptNowY > maxY then
   			ptNowY = maxY
   		end
   		
    	pBall:setPosition(cc.p(ptNowX, ptNowY ))
    	
    	
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
