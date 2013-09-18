local function AccelerometerMainLayer()

    local function title()
      return "AccelerometerTest"
    end
    local layer = cc.Layer:create()

    layer:setAccelerometerEnabled(true)

    local label = cc.LabelTTF:create(title(), "Arial", 32)
    layer:addChild(label, 1)
    label:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 50) )

    local ball = cc.Sprite:create("Images/ball.png")
    ball:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))
    layer:addChild(ball)

    ball:retain()
    
    local function didAccelerate(x,y,z,timestamp)

      if nil == ball then
        return
      end

      local szBall  = ball:getContentSize()
      local ptNowX,ptNowY = ball:getPosition()

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
      
      ball:setPosition(cc.p(ptNowX, ptNowY ))
    end
    
    layer:registerScriptAccelerateHandler(didAccelerate)   
    
    return layer
end


function AccelerometerMain()
	cclog("AccelerometerMain")
	local scene = cc.Scene:create()
	scene:addChild(AccelerometerMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
