local function AccelerometerMainLayer()

    local function title()
      return "AccelerometerTest"
    end
    local layer = cc.Layer:create()

    local function onEnter()
        layer:setAccelerometerEnabled(true)
        local label = cc.Label:createWithTTF(title(), "fonts/arial.ttf", 32)
        layer:addChild(label, 1)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 50) )

        local ball = cc.Sprite:create("Images/ball.png")
        ball:setPosition(cc.p(VisibleRect:center().x, VisibleRect:center().y))
        layer:addChild(ball)

        local function accelerometerListener(event,x,y,z,timestamp)
            local target  = event:getCurrentTarget()
            local ballSize = target:getContentSize()
            local ptNowX,ptNowY    = target:getPosition()
            ptNowX = ptNowX + x * 9.81
            ptNowY = ptNowY + y * 9.81

            local minX  = math.floor(VisibleRect:left().x + ballSize.width / 2.0)
            local maxX  = math.floor(VisibleRect:right().x - ballSize.width / 2.0)
            if ptNowX <   minX then
                ptNowX = minX
            elseif ptNowX > maxX then
                ptNowX = maxX
            end
      
            local minY  = math.floor(VisibleRect:bottom().y + ballSize.height / 2.0)
            local maxY  = math.floor(VisibleRect:top().y   - ballSize.height / 2.0)
            if ptNowY <   minY then
                ptNowY = minY
            elseif ptNowY > maxY then
                ptNowY = maxY
            end

            target:setPosition(cc.p(ptNowX , ptNowY))
        end

        local listerner  = cc.EventListenerAcceleration:create(accelerometerListener)
        layer:getEventDispatcher():addEventListenerWithSceneGraphPriority(listerner,ball)
    end

    local function onExit()
        layer:setAccelerometerEnabled(false)
    end

    local function onNodeEvent(event)
        if "enter" == event then
            onEnter()
        elseif "exit" == event then
            onExit()
        end
    end

    layer:registerScriptHandler(onNodeEvent)
    
    return layer
end


function AccelerometerMain()
	cclog("AccelerometerMain")
	local scene = cc.Scene:create()
	scene:addChild(AccelerometerMainLayer())
	scene:addChild(CreateBackMenuItem())
	return scene
end
