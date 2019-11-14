local size = cc.Director:getInstance():getWinSize()
local MATERIAL_DEFAULT = cc.PhysicsMaterial(0.1, 0.5, 0.5)
local curLayer = nil
local STATIC_COLOR = cc.c4f(1.0, 0.0, 0.0, 1.0)
local DRAG_BODYS_TAG = 0x80

local function range(from, to, step)
  step = step or 1
  return function(_, lastvalue)
    local nextvalue = lastvalue + step
    if step > 0 and nextvalue <= to or step < 0 and nextvalue >= to or
       step == 0
    then
      return nextvalue
    end
  end, nil, from - step
end

local function initWithLayer(layer, callback)
   curLayer = layer
   layer.spriteTexture = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 100):getTexture()

   local debug = false
   local function toggleDebugCallback(sender)
      debug = not debug
      cc.Director:getInstance():getRunningScene():getPhysicsWorld():setDebugDrawMask(debug and cc.PhysicsWorld.DEBUGDRAW_ALL or cc.PhysicsWorld.DEBUGDRAW_NONE)
   end

   layer.toggleDebug = function(self) toggleDebugCallback(nil) end
   cc.MenuItemFont:setFontSize(18)
   local item = cc.MenuItemFont:create("Toggle debug")
   item:registerScriptTapHandler(toggleDebugCallback)
   local menu = cc.Menu:create(item)
   layer:addChild(menu)
   menu:setPosition(size.width - 50, size.height - 10)
   Helper.initWithLayer(layer)

   local function onNodeEvent(event)
        if "enter" == event then
            callback()
        end
    end
    layer:registerScriptHandler(onNodeEvent)
end

local function addGrossiniAtPosition(layer, p, scale)
   scale = scale or 1.0

   local posx = math.random() * 200.0
   local posy = math.random() * 100.0
   posx = (math.floor(posx) % 4) * 85
   posy = (math.floor(posy) % 3) * 121

   local sp = cc.Sprite:createWithTexture(layer.spriteTexture, cc.rect(posx, posy, 85, 121))
   sp:setScale(scale)
   sp:setPhysicsBody(cc.PhysicsBody:createBox(cc.size(48.0, 108.0)))
   layer:addChild(sp)
   sp:setPosition(p)
   return sp
end

local function onTouchBegan(touch, event)
    local location = touch:getLocation()
    local arr = cc.Director:getInstance():getRunningScene():getPhysicsWorld():getShapes(location)
    
    local body
    for _, obj in ipairs(arr) do
        if bit.band(obj:getBody():getTag(), DRAG_BODYS_TAG) ~= 0 then
            body = obj:getBody()
            break
        end
    end
    
    if body then
        local mouse = cc.Node:create()
        local physicsBody = cc.PhysicsBody:create(PHYSICS_INFINITY, PHYSICS_INFINITY)
        mouse:setPhysicsBody(physicsBody)
        physicsBody:setDynamic(false)
        mouse:setPosition(location)
        curLayer:addChild(mouse)
        local joint = cc.PhysicsJointPin:construct(physicsBody, body, location)
        joint:setMaxForce(5000.0 * body:getMass())
        cc.Director:getInstance():getRunningScene():getPhysicsWorld():addJoint(joint)
        touch.mouse = mouse
        
        return true
    end
    
    return false
end

local function onTouchMoved(touch, event)
    if touch.mouse then
        touch.mouse:setPosition(touch:getLocation())
    end
end

local function onTouchEnded(touch, event)
    if touch.mouse then
        curLayer:removeChild(touch.mouse)
        touch.mouse = nil
    end
end

local function makeBall(layer, point, radius, material)
    material = material or MATERIAL_DEFAULT

    local ball
    if layer.ball then
       ball = cc.Sprite:createWithTexture(layer.ball:getTexture())
    else
       ball = cc.Sprite:create("Images/ball.png")
    end

    ball:setScale(0.13 * radius)

    local body = cc.PhysicsBody:createCircle(ball:getContentSize().width / 2, material)
    ball:setPhysicsBody(body)
    ball:setPosition(point)

    return ball
end

local function makeBox(point, size, color, material)
    material = material or MATERIAL_DEFAULT

    local yellow = false
    if color == 0 then
        yellow = math.random() > 0.5
    else
        yellow = color == 1
    end

    local box = yellow and cc.Sprite:create("Images/YellowSquare.png") or cc.Sprite:create("Images/CyanSquare.png")
    
    box:setScaleX(size.width/100.0)
    box:setScaleY(size.height/100.0)
    
    local body = cc.PhysicsBody:createBox(box:getContentSize(), material)
    box:setPhysicsBody(body)
    box:setPosition(cc.p(point.x, point.y))
    
    return box
end

local function makeTriangle(point, size, color, material)
    material = material or MATERIAL_DEFAULT

    local yellow = false
    if color == 0 then
        yellow = math.random() > 0.5
    else
        yellow = color == 1
    end
    local triangle = yellow and cc.Sprite:create("Images/YellowTriangle.png") or cc.Sprite:create("Images/CyanTriangle.png")
    
    if size.height == 0 then
        triangle:setScale(size.width/100.0)
    else
        triangle:setScaleX(size.width/50.0)
        triangle:setScaleY(size.height/43.5)
    end

    vers = { cc.p(0, triangle:getContentSize().height/2),
             cc.p(triangle:getContentSize().width/2, -triangle:getContentSize().height/2),
             cc.p(-triangle:getContentSize().width/2, -triangle:getContentSize().height/2)
           }

    local body = cc.PhysicsBody:createPolygon(vers, material)
    triangle:setPhysicsBody(body)
    triangle:setPosition(point)
    
    return triangle
end

local function PhysicsDemoClickAdd()
    local layer = cc.Layer:create()
    local function onEnter()
       local function onTouchEnded(touch, event)
	          local location = touch:getLocation()
	          addGrossiniAtPosition(layer, location)
       end
       
       local touchListener = cc.EventListenerTouchOneByOne:create()
       touchListener:registerScriptHandler(function() return true end, cc.Handler.EVENT_TOUCH_BEGAN) 
       touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
       local eventDispatcher = layer:getEventDispatcher()
       eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)

       addGrossiniAtPosition(layer, VisibleRect:center())
       
       local node = cc.Node:create()
       node:setPhysicsBody(cc.PhysicsBody:createEdgeBox(cc.size(VisibleRect:getVisibleRect().width, 
                                                                VisibleRect:getVisibleRect().height
                                                               )
                                                       )
                          )
       node:setPosition(VisibleRect:center())
       layer:addChild(node)
    end
    initWithLayer(layer, onEnter)
    Helper.titleLabel:setString("Grossini")
    Helper.subtitleLabel:setString("multi touch to add grossini")

    return layer
end

local function PhysicsDemoLogoSmash()
    local layer = cc.Layer:create()

    local function onEnter()
       local logo_width = 188.0
       local logo_height = 35.0
       local logo_raw_length = 24.0
       local logo_image = {
	  15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-64,15,63,-32,-2,0,0,0,0,0,0,0,
	  0,0,0,0,0,0,0,0,0,0,0,31,-64,15,127,-125,-1,-128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	  0,0,0,127,-64,15,127,15,-1,-64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,-64,15,-2,
	  31,-1,-64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,-64,0,-4,63,-1,-32,0,0,0,0,0,0,
	  0,0,0,0,0,0,0,0,0,0,1,-1,-64,15,-8,127,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	  1,-1,-64,0,-8,-15,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-31,-1,-64,15,-8,-32,
	  -1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-15,-1,-64,9,-15,-32,-1,-32,0,0,0,0,0,
	  0,0,0,0,0,0,0,0,0,0,31,-15,-1,-64,0,-15,-32,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,
	  0,0,63,-7,-1,-64,9,-29,-32,127,-61,-16,63,15,-61,-1,-8,31,-16,15,-8,126,7,-31,
	  -8,31,-65,-7,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-2,63,-8,31,-4,-1,15,-13,
	  -4,63,-1,-3,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-2,63,-8,31,-4,-1,15,-13,
	  -2,63,-1,-3,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
	  -2,63,-33,-1,-1,-32,9,-25,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
	  -1,63,-33,-1,-1,-16,9,-25,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
	  -1,63,-49,-1,-1,-8,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
	  -1,-65,-49,-1,-1,-4,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
	  -1,-65,-57,-1,-1,-2,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
	  -1,-1,-57,-1,-1,-1,9,-57,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
	  -1,-61,-1,-1,-1,-119,-57,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
	  -1,-61,-1,-1,-1,-55,-49,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
	  -1,-63,-1,-1,-1,-23,-49,-32,127,-57,-1,-1,-97,-25,-1,-1,63,-1,-1,-4,-1,15,-13,
	  -1,-1,-63,-1,-1,-1,-16,-49,-32,-1,-25,-1,-1,-97,-25,-1,-1,63,-33,-5,-4,-1,15,
	  -13,-1,-1,-64,-1,-9,-1,-7,-49,-32,-1,-25,-8,127,-97,-25,-1,-1,63,-33,-5,-4,-1,
	  15,-13,-1,-1,-64,-1,-13,-1,-32,-49,-32,-1,-25,-8,127,-97,-25,-1,-2,63,-49,-13,
	  -4,-1,15,-13,-1,-1,-64,127,-7,-1,-119,-17,-15,-1,-25,-8,127,-97,-25,-1,-2,63,
	  -49,-13,-4,-1,15,-13,-3,-1,-64,127,-8,-2,15,-17,-1,-1,-25,-8,127,-97,-25,-1,
	  -8,63,-49,-13,-4,-1,15,-13,-3,-1,-64,63,-4,120,0,-17,-1,-1,-25,-8,127,-97,-25,
	  -8,0,63,-57,-29,-4,-1,15,-13,-4,-1,-64,63,-4,0,15,-17,-1,-1,-25,-8,127,-97,
	  -25,-8,0,63,-57,-29,-4,-1,-1,-13,-4,-1,-64,31,-2,0,0,103,-1,-1,-57,-8,127,-97,
	  -25,-8,0,63,-57,-29,-4,-1,-1,-13,-4,127,-64,31,-2,0,15,103,-1,-1,-57,-8,127,
	  -97,-25,-8,0,63,-61,-61,-4,127,-1,-29,-4,127,-64,15,-8,0,0,55,-1,-1,-121,-8,
	  127,-97,-25,-8,0,63,-61,-61,-4,127,-1,-29,-4,63,-64,15,-32,0,0,23,-1,-2,3,-16,
	  63,15,-61,-16,0,31,-127,-127,-8,31,-1,-127,-8,31,-128,7,-128,0,0
       }

       local function get_pixel(x, y)
	         return bit.band(bit.rshift(logo_image[bit.rshift(x, 3) + y*logo_raw_length + 1], bit.band(bit.bnot(x), 0x07)), 1)
       end

       cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0, 0))
       cc.Director:getInstance():getRunningScene():getPhysicsWorld():setUpdateRate(5.0)
       
       layer.ball = cc.SpriteBatchNode:create("Images/ball.png", #logo_image)
       layer:addChild(layer.ball)
       for y in range(0, logo_height-1) do
	         for x in range(0, logo_width-1) do
	             if get_pixel(x, y) == 1 then
                  local x_jitter = 0.05*math.random()
                  local y_jitter = 0.05*math.random()
                
                  local ball = makeBall(layer, 
                                        cc.p(2*(x - logo_width/2 + x_jitter) + VisibleRect:getVisibleRect().width/2,
					                                   2*(logo_height-y + y_jitter) + VisibleRect:getVisibleRect().height/2 - logo_height/2),
                                        0.95, 
                                        cc.PhysicsMaterial(0.01, 0.0, 0.0))
                  local physicsBody = ball:getPhysicsBody()
                  physicsBody:setMass(1.0)
                  physicsBody:setMoment(PHYSICS_INFINITY)

                  layer.ball:addChild(ball)
	              end
	          end
       end

       local bullet = makeBall(layer, cc.p(400, 0), 10, cc.PhysicsMaterial(PHYSICS_INFINITY, 0, 0))

       bullet:getPhysicsBody():setVelocity(cc.p(200, 0))
       bullet:setPosition(cc.p(-500, VisibleRect:getVisibleRect().height/2))
       layer.ball:addChild(bullet)
    end

    initWithLayer(layer, onEnter)
    Helper.titleLabel:setString("Logo Smash")
    
    return layer
end

local function PhysicsDemoJoints()
   local layer = cc.Layer:create()
   local function onEnter()
    layer:toggleDebug()
    
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN) 
    touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED) 
    touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
    
    local width = (VisibleRect:getVisibleRect().width - 10) / 4
    local height = (VisibleRect:getVisibleRect().height - 50) / 4
    
    local node = cc.Node:create()
    local box = cc.PhysicsBody:create()
    node:setPhysicsBody(box)
    box:setDynamic(false)
    node:setPosition(cc.p(0, 0))
    layer:addChild(node)

    local scene = cc.Director:getInstance():getRunningScene()
    for i in range(0, 3) do
       for j in range(0, 3) do
            local offset = cc.p(VisibleRect:leftBottom().x + 5 + j * width + width/2, 
                                VisibleRect:leftBottom().y + 50 + i * height + height/2)
            box:addShape(cc.PhysicsShapeEdgeBox:create(cc.size(width, height), 
                                                       cc.PHYSICSSHAPE_MATERIAL_DEFAULT,
                                                       1, 
                                                       offset)
                        )
            local index = i*4 + j

            if index == 0 then
	              local sp1 = makeBall(layer, cc.p(offset.x - 30, offset.y), 10)
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBall(layer, cc.p(offset.x + 30, offset.y), 10)
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                local joint = cc.PhysicsJointPin:construct(sp1PhysicsBody, sp2PhysicsBody, offset)
                cc.Director:getInstance():getRunningScene():getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif  index == 1 then
                local sp1 = makeBall(layer, cc.p(offset.x - 30, offset.y), 10)
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                local joint = cc.PhysicsJointFixed:construct(sp1PhysicsBody, sp2PhysicsBody, offset)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 2 then
                local sp1 = makeBall(layer, cc.p(offset.x - 30, offset.y), 10)
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                local joint = cc.PhysicsJointDistance:construct(sp1PhysicsBody, 
                                                                sp2PhysicsBody, 
                                                                cc.p(0, 0), 
                                                                cc.p(0, 0))
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 3 then
                local sp1 = makeBall(layer, cc.p(offset.x - 30, offset.y), 10)
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                local joint = cc.PhysicsJointLimit:construct(sp1PhysicsBody, 
                                                             sp2PhysicsBody, 
                                                             cc.p(0, 0), 
                                                             cc.p(0, 0), 
                                                             30.0, 
                                                             60.0)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 4 then
                local sp1 = makeBall(layer, cc.p(offset.x - 30, offset.y), 10)
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                local joint = cc.PhysicsJointSpring:construct(sp1PhysicsBody, 
                                                              sp2PhysicsBody, 
                                                              cc.p(0, 0), 
                                                              cc.p(0, 0), 
                                                              500.0, 
                                                              0.3)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 5 then
                local sp1 = makeBall(layer, cc.p(offset.x - 30, offset.y), 10)
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                local joint = cc.PhysicsJointGroove:construct(sp1PhysicsBody, 
                                                              sp2PhysicsBody, 
                                                              cc.p(30, 15), 
                                                              cc.p(30, -15), 
                                                              cc.p(-30, 0))
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 6 then
                local sp1 = makeBox(cc.p(offset.x - 30, offset.y), cc.size(30, 10))
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)

                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp1PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp1:getPosition())))
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp2PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp2:getPosition())))
                local joint = cc.PhysicsJointRotarySpring:construct(sp1PhysicsBody, 
                                                                    sp2PhysicsBody, 
                                                                    3000.0, 
                                                                    60.0)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 7 then
                local sp1 = makeBox(cc.p(offset.x - 30, offset.y), cc.size(30, 10))
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp1PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp1:getPosition())))
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp2PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp2:getPosition())))
                local joint = cc.PhysicsJointRotaryLimit:construct(sp1PhysicsBody, 
                                                                   sp2PhysicsBody, 
                                                                   0.0, 
                                                                   math.pi/2)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 8 then
                local sp1 = makeBox(cc.p(offset.x - 30, offset.y), cc.size(30, 10))
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp1PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp1:getPosition())))
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp2PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp2:getPosition())))
                local joint = cc.PhysicsJointRatchet:construct(sp1PhysicsBody, 
                                                               sp2PhysicsBody, 
                                                               0.0, 
                                                               math.pi/2)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 9 then
                local sp1 = makeBox(cc.p(offset.x - 30, offset.y), cc.size(30, 10))
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp1PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp1:getPosition())))
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp2PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp2:getPosition())))
                local joint = cc.PhysicsJointGear:construct(sp1PhysicsBody, sp2PhysicsBody, 0.0, 2.0)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            elseif index == 10 then
                local sp1 = makeBox(cc.p(offset.x - 30, offset.y), cc.size(30, 10))
                local sp1PhysicsBody = sp1:getPhysicsBody()
                sp1PhysicsBody:setTag(DRAG_BODYS_TAG)

                local sp2 = makeBox(cc.p(offset.x + 30, offset.y), cc.size(30, 10))
                local sp2PhysicsBody = sp2:getPhysicsBody()
                sp2PhysicsBody:setTag(DRAG_BODYS_TAG)
                    
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp1PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp1:getPosition())))
                scene:getPhysicsWorld():addJoint(cc.PhysicsJointPin:construct(sp2PhysicsBody, 
                                                                              box, 
                                                                              cc.p(sp2:getPosition())))
                local joint = cc.PhysicsJointMotor:construct(sp1PhysicsBody, sp2PhysicsBody, math.pi/2)
                scene:getPhysicsWorld():addJoint(joint)
                    
                layer:addChild(sp1)
                layer:addChild(sp2)
            end
          end
      end
  end

    initWithLayer(layer, onEnter)
    Helper.titleLabel:setString("Joints")
    return layer
end

local function PhysicsDemoPyramidStack()
    local layer = cc.Layer:create()

    local function onEnter()
       local touchListener = cc.EventListenerTouchOneByOne:create()
       touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
       touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
       touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
       local eventDispatcher = layer:getEventDispatcher()
       eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
       
       local node = cc.Node:create()
       node:setPhysicsBody(cc.PhysicsBody:createEdgeSegment(cc.p(VisibleRect:leftBottom().x, 
                                                                 VisibleRect:leftBottom().y + 50), 
                                                            cc.p(VisibleRect:rightBottom().x, 
                                                                 VisibleRect:rightBottom().y + 50)))
       layer:addChild(node)
       
       local ball = cc.Sprite:create("Images/ball.png")
       ball:setScale(1)
       ball:setPhysicsBody(cc.PhysicsBody:createCircle(10))
       ball:getPhysicsBody():setTag(DRAG_BODYS_TAG)
       ball:setPosition(cc.p(VisibleRect:bottom().x, VisibleRect:bottom().y + 60))
       layer:addChild(ball)

       ball:runAction(cc.Sequence:create(cc.DelayTime:create(3),
                                         cc.ScaleTo:create(0, 3)))
       
       for i in range(0, 13) do
	         for j in range(0, i) do
	             local x = VisibleRect:bottom().x + (i/2 - j) * 11
	             local y = VisibleRect:bottom().y + (14 - i) * 23 + 100
	             local sp = addGrossiniAtPosition(layer, cc.p(x, y), 0.2)
               sp:getPhysicsBody():setTag(DRAG_BODYS_TAG)
	         end
       end
    end

    initWithLayer(layer, onEnter)
    Helper.titleLabel:setString("Pyramid Stack")

    return layer
end

local function PhysicsDemoRayCast()
    local layer = cc.Layer:create()

    local function onEnter()
       local function onTouchEnded(touch, event)
	         local location = touch:getLocation()
	  
	         local r = math.random(3)
	         if r ==1 then
	             layer:addChild(makeBall(layer, location, 5 + math.random()*10))
	         elseif r == 2 then
	             layer:addChild(makeBox(location, cc.size(10 + math.random()*15, 10 + math.random()*15)))
	         elseif r == 3 then
	             layer:addChild(makeTriangle(location, cc.size(10 + math.random()*20, 10 + math.random()*20)))
	         end
       end
       
       local touchListener = cc.EventListenerTouchOneByOne:create()
       touchListener:registerScriptHandler(function() return true end, cc.Handler.EVENT_TOUCH_BEGAN)
       touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
       local eventDispatcher = layer:getEventDispatcher()
       eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
       
       cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0,0))
       
       local node = cc.DrawNode:create()
       node:setPhysicsBody(cc.PhysicsBody:createEdgeSegment(cc.p(VisibleRect:leftBottom().x, 
                                                                 VisibleRect:leftBottom().y + 50), 
                                                            cc.p(VisibleRect:rightBottom().x, 
                                                                 VisibleRect:rightBottom().y + 50)))
       node:drawSegment(cc.p(VisibleRect:leftBottom().x, VisibleRect:leftBottom().y + 50), 
                        cc.p(VisibleRect:rightBottom().x, VisibleRect:rightBottom().y + 50), 
                        1, 
                        STATIC_COLOR)
       layer:addChild(node)

       local mode = 0
       cc.MenuItemFont:setFontSize(18)
       local item = cc.MenuItemFont:create("Toggle debugChange Mode(any)")
       local function changeModeCallback(sender)
	         mode = (mode + 1) % 3
	  
	         if mode == 0 then
	             item:setString("Change Mode(any)")
	         elseif mode == 1 then
	             item:setString("Change Mode(nearest)")
	         elseif mode == 2 then
	         item:setString("Change Mode(multiple)")
	         end
       end
       
       item:registerScriptTapHandler(changeModeCallback)
       
       local menu = cc.Menu:create(item)
       layer:addChild(menu)
       menu:setPosition(cc.p(VisibleRect:left().x+100, VisibleRect:top().y-10))

       local angle = 0
       local drawNode = nil
       local function update(delta)
	         local L = 150.0
	         local point1 = VisibleRect:center()
	         local d = cc.p(L * math.cos(angle), L * math.sin(angle))
	         local point2 = cc.p(point1.x + d.x, point1.y + d.y)
    
          if drawNode then layer:removeChild(drawNode) end
          drawNode = cc.DrawNode:create()
          if mode == 0 then
	            local point3 = cc.p(point2.x, point2.y)
	            local function func(world, info)
		              point3 = info.contact
		              return false
	            end

              cc.Director:getInstance():getRunningScene():getPhysicsWorld():rayCast(func, point1, point2)
              drawNode:drawSegment(point1, point3, 1, STATIC_COLOR)
            
              if point2.x ~= point3.x or point2.y ~= point3.y then
	               drawNode:drawDot(point3, 2, cc.c4f(1.0, 1.0, 1.0, 1.0))
              end
              layer:addChild(drawNode)
	        elseif mode == 1 then
	            local point3 = cc.p(point2.x, point2.y)
              local friction = 1.0
              local function func(world, info)
                  if friction > info.fraction then
                      point3 = info.contact
                      friction = info.fraction
		              end
                  return true
              end
            
              cc.Director:getInstance():getRunningScene():getPhysicsWorld():rayCast(func, point1, point2)
              drawNode:drawSegment(point1, point3, 1, STATIC_COLOR)
            
              if point2.x ~= point3.x or point2.y ~= point3.y then
                  drawNode:drawDot(point3, 2, cc.c4f(1.0, 1.0, 1.0, 1.0))
              end
              layer:addChild(drawNode)
          elseif mode == 2 then
	            local points = {}
            
              local function func(world, info)
                  points[#points + 1] = info.contact
                  return true
              end
            
              cc.Director:getInstance():getRunningScene():getPhysicsWorld():rayCast(func, point1, point2)
              drawNode:drawSegment(point1, point2, 1, STATIC_COLOR)
            
              for _, p in ipairs(points) do
                  drawNode:drawDot(p, 2, cc.c4f(1.0, 1.0, 1.0, 1.0))
              end
            
              layer:addChild(drawNode)
          end
    
         angle = angle + 0.25 * math.pi / 180.0

      end

       layer:scheduleUpdateWithPriorityLua(update, 0)
    end

    initWithLayer(layer, onEnter)
    Helper.titleLabel:setString("Ray Cast")

    return layer
end

local function PhysicsDemoOneWayPlatform()
    local layer = cc.Layer:create()
    local function onEnter()

       local touchListener = cc.EventListenerTouchOneByOne:create()
       touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
       touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
       touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
       local eventDispatcher = layer:getEventDispatcher()
       eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)

      local ground = cc.Node:create()
      ground:setPhysicsBody(cc.PhysicsBody:createEdgeSegment(cc.p(VisibleRect:leftBottom().x, 
                                                                VisibleRect:leftBottom().y + 50), 
                                                           cc.p(VisibleRect:rightBottom().x, 
                                                                VisibleRect:rightBottom().y + 50)))
      layer:addChild(ground)
    
      local platform = makeBox(VisibleRect:center(), cc.size(200, 50))
      local platformPhysicsBody = platform:getPhysicsBody()
      platformPhysicsBody:setDynamic(false)
      platformPhysicsBody:setContactTestBitmask(0xFFFFFFFF)
      layer:addChild(platform)
    
      local ball = makeBall(layer, cc.p(VisibleRect:center().x, VisibleRect:center().y - 50), 20)
      local ballPhysicsBody = ball:getPhysicsBody()
      ballPhysicsBody:setVelocity(cc.p(0, 150))
      ballPhysicsBody:setTag(DRAG_BODYS_TAG)
      ballPhysicsBody:setMass(1.0)
      ballPhysicsBody:setContactTestBitmask(0xFFFFFFFF)
      layer:addChild(ball)

      local function onContactBegin(contact)
        return contact:getContactData().normal.y < 0
      end
      local contactListener = cc.EventListenerPhysicsContactWithBodies:create(platformPhysicsBody, ballPhysicsBody)
      contactListener:registerScriptHandler(onContactBegin, cc.Handler.EVENT_PHYSICS_CONTACT_BEGIN)
      eventDispatcher:addEventListenerWithSceneGraphPriority(contactListener, layer)
    end

    initWithLayer(layer, onEnter)
    Helper.titleLabel:setString("One Way Platform")

    return layer
end

local function PhysicsDemoActions()
  local layer = cc.Layer:create()
  local function onEnter()
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN) 
    touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED) 
    touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
    
    local node = cc.Node:create()
    node:setPhysicsBody(cc.PhysicsBody:createEdgeBox(cc.size(VisibleRect:getVisibleRect().width, 
                                                             VisibleRect:getVisibleRect().height)))
    node:setPosition(VisibleRect:center())
    layer:addChild(node)
    
    local sp1 = addGrossiniAtPosition(layer, VisibleRect:center())
    local sp2 = addGrossiniAtPosition(layer, cc.p(VisibleRect:left().x + 50, VisibleRect:left().y))
    local sp3 = addGrossiniAtPosition(layer, cc.p(VisibleRect:right().x - 20, VisibleRect:right().y))
    local sp4 = addGrossiniAtPosition(layer, cc.p(VisibleRect:leftTop().x + 50, VisibleRect:leftTop().y-50))
    sp4:getPhysicsBody():setGravityEnable(false)
    
    
    local actionTo = cc.JumpTo:create(2, cc.p(100,100), 50, 4)
    local actionBy = cc.JumpBy:create(2, cc.p(300,0), 50, 4)
    local actionUp = cc.JumpBy:create(2, cc.p(0,50), 80, 4)
    local actionByBack = actionBy:reverse()
    local rotateBy = cc.RotateBy:create(2, 180)
    local rotateByBack = cc.RotateBy:create(2, -180)
    
    sp1:runAction(cc.RepeatForever:create(actionUp))
    sp2:runAction(cc.RepeatForever:create(cc.Sequence:create(actionBy, actionByBack)))
    sp3:runAction(actionTo)
    sp4:runAction(cc.RepeatForever:create(cc.Sequence:create(rotateBy, rotateByBack)))
  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Actions")

  return layer
end

local function PhysicsDemoPump()
  local layer = cc.Layer:create()
  local function onEnter()
    layer:toggleDebug()

    local distance = 0.0
    local rotationV = 0.0
    local function onTouchBeganEx(touch, event)
      onTouchBegan(touch, event)
      distance = touch:getLocation().x - VisibleRect:center().x
      return true
    end

    local function onTouchMovedEx(touch, event)
      onTouchMoved(touch, event)
      distance = touch:getLocation().x - VisibleRect:center().x
    end

    local function onTouchEndedEx(touch, event)
      onTouchEnded(touch, event)
      distance = 0
    end
    
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(onTouchBeganEx, cc.Handler.EVENT_TOUCH_BEGAN) 
    touchListener:registerScriptHandler(onTouchMovedEx, cc.Handler.EVENT_TOUCH_MOVED) 
    touchListener:registerScriptHandler(onTouchEndedEx, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
    
    local function update()
      for _, body in ipairs(cc.Director:getInstance():getRunningScene():getPhysicsWorld():getAllBodies()) do
        if body:getTag() == DRAG_BODYS_TAG and body:getPosition().y < 0.0 then
            body:getNode():setPosition(cc.p(VisibleRect:leftTop().x + 75, 
                                            VisibleRect:leftTop().y + math.random() * 90))
            body:setVelocity(cc.p(0, 0))
        end
      end
      
      local gear = cc.Director:getInstance():getRunningScene():getPhysicsWorld():getBody(1)
      if gear then
          if distance ~= 0.0 then
            rotationV = rotationV + distance/2500.0
          end
          if rotationV > 30 then rotationV = 30.0 end
          if rotationV < -30 then rotationV = -30.0 end
          
          gear:setAngularVelocity(rotationV)
          rotationV = rotationV * 0.995
      end
    end

    layer:scheduleUpdateWithPriorityLua(update, 0)
    
    local node = cc.Node:create()
    local body = cc.PhysicsBody:create()
    body:setDynamic(false)
    
    local staticMaterial = cc.PhysicsMaterial(cc.PHYSICS_INFINITY, 0, 0.5)
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 50, 
                                                         VisibleRect:leftTop().y), 
                                                    cc.p(VisibleRect:leftTop().x + 50, 
                                                        VisibleRect:leftTop().y-130),
                                                    staticMaterial, 
                                                    2.0))
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 190, 
                                                         VisibleRect:leftTop().y), 
                                                    cc.p(VisibleRect:leftTop().x + 100, 
                                                         VisibleRect:leftTop().y-50), 
                                                    staticMaterial, 
                                                    2.0))
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 100, 
                                                         VisibleRect:leftTop().y-50), 
                                                    cc.p(VisibleRect:leftTop().x + 100, 
                                                         VisibleRect:leftTop().y-90), 
                                                    staticMaterial, 
                                                    2.0))
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 50, 
                                                         VisibleRect:leftTop().y-130), 
                                                    cc.p(VisibleRect:leftTop().x + 100, 
                                                         VisibleRect:leftTop().y-145), 
                                                    staticMaterial, 
                                                    2.0))
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 100, 
                                                         VisibleRect:leftTop().y-145), 
                                                    cc.p(VisibleRect:leftBottom().x + 100, 
                                                        VisibleRect:leftBottom().y + 80), 
                                                    staticMaterial, 
                                                    2.0))
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 150, 
                                                         VisibleRect:leftTop().y-80), 
                                                    cc.p(VisibleRect:leftBottom().x + 150, 
                                                         VisibleRect:leftBottom().y + 80), 
                                                    staticMaterial, 
                                                    2.0))
    body:addShape(cc.PhysicsShapeEdgeSegment:create(cc.p(VisibleRect:leftTop().x + 150, 
                                                         VisibleRect:leftTop().y-80), 
                                                    cc.p(VisibleRect:rightTop().x -100, 
                                                         VisibleRect:rightTop().y-150), 
                                                    staticMaterial, 
                                                    2.0))
    
    body:setCategoryBitmask(1)
    
    for _ in range(1, 6) do
        local ball = makeBall(layer, 
                              cc.p(VisibleRect:leftTop().x + 75 + math.random() * 90, 
                                   VisibleRect:leftTop().y), 
                              22, 
                              cc.PhysicsMaterial(0.05, 0.0, 0.1))
        ball:getPhysicsBody():setTag(DRAG_BODYS_TAG)
        layer:addChild(ball)
    end
    
    node:setPhysicsBody(body)
    layer:addChild(node)
    
    local vec =
    {
        cc.p(VisibleRect:leftTop().x + 102, VisibleRect:leftTop().y-148),
        cc.p(VisibleRect:leftTop().x + 148, VisibleRect:leftTop().y-161),
        cc.p(VisibleRect:leftBottom().x + 148, VisibleRect:leftBottom().y + 20),
        cc.p(VisibleRect:leftBottom().x + 102, VisibleRect:leftBottom().y + 20)
    }
    
    local world = cc.Director:getInstance():getRunningScene():getPhysicsWorld()
    
    -- small gear
    local sgear = cc.Node:create()
    local sgearB = cc.PhysicsBody:createCircle(44)
    sgear:setPhysicsBody(sgearB)
    sgear:setPosition(cc.p(VisibleRect:leftBottom().x + 125, VisibleRect:leftBottom().y))
    layer:addChild(sgear)
    sgearB:setCategoryBitmask(4)
    sgearB:setCollisionBitmask(4)
    sgearB:setTag(1)
    world:addJoint(cc.PhysicsJointPin:construct(body, sgearB, cc.p(sgear:getPosition())))
    
    
    -- big gear
    local bgear = cc.Node:create()
    local bgearB = cc.PhysicsBody:createCircle(100)
    bgear:setPhysicsBody(bgearB)
    bgear:setPosition(cc.p(VisibleRect:leftBottom().x + 275, VisibleRect:leftBottom().y))
    layer:addChild(bgear)
    bgearB:setCategoryBitmask(4)
    world:addJoint(cc.PhysicsJointPin:construct(body, bgearB, cc.p(bgear:getPosition())))
    
    
    -- pump
    local pump = cc.Node:create()
    local center = cc.PhysicsShape:getPolygonCenter(vec)
    pump:setPosition(center)
    local pumpB = cc.PhysicsBody:createPolygon(vec, 
                                               cc.PHYSICSBODY_MATERIAL_DEFAULT, 
                                               cc.p(-center.x, -center.y))
    pump:setPhysicsBody(pumpB)
    layer:addChild(pump)
    pumpB:setCategoryBitmask(2)
    pumpB:setGravityEnable(false)
    world:addJoint(cc.PhysicsJointDistance:construct(pumpB, sgearB, cc.p(0, 0), cc.p(0, -44)))
    
    -- plugger
    local seg = {cc.p(VisibleRect:leftTop().x + 75, VisibleRect:leftTop().y-120), 
                 cc.p(VisibleRect:leftBottom().x + 75, VisibleRect:leftBottom().y-100)}
    local segCenter = cc.p((seg[2].x + seg[1].x)/2, (seg[2].y + seg[1].y)/2)
    seg[2] = cc.p(seg[2].x - segCenter.x, seg[2].y - segCenter.y)
    seg[1] = cc.p(seg[1].x - segCenter.x, seg[1].y - segCenter.y)
    local plugger = cc.Node:create()
    local pluggerB = cc.PhysicsBody:createEdgeSegment(seg[1], 
                                                      seg[2], 
                                                      cc.PhysicsMaterial(0.01, 0.0, 0.5), 
                                                      20)
    pluggerB:setDynamic(true)
    pluggerB:setMass(30)
    pluggerB:setMoment(100000)
    plugger:setPhysicsBody(pluggerB)
    plugger:setPosition(segCenter)
    layer:addChild(plugger)
    pluggerB:setCategoryBitmask(2)
    sgearB:setCollisionBitmask(5)
    world:addJoint(cc.PhysicsJointPin:construct(body, 
                                                pluggerB, 
                                                cc.p(VisibleRect:leftBottom().x + 75, 
                                                     VisibleRect:leftBottom().y-90)))
    world:addJoint(cc.PhysicsJointDistance:construct(pluggerB, 
                                                     sgearB, 
                                                     pluggerB:world2Local(cc.p(0,0)), 
                                                     cc.p(44, 0)))
  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Pump")
  Helper.subtitleLabel:setString("touch screen on left or right")

  return layer
end

local function PhysicsDemoSlice()
    local layer = cc.Layer:create()
    local function onEnter()
      layer:toggleDebug()
      local sliceTag = 1

      local function clipPoly(shape, normal, distance)
        local body = shape:getBody()
        local count = shape:getPointsCount()
        local points = {}
    
        local j = count - 1
        for i in range(0, count-1) do
          local a = body:local2World(shape:getPoint(j))
          local aDist = cc.pDot(a, normal) - distance
        
          if aDist < 0.0 then
            points[#points + 1] = a
          end
        
          local b = body:local2World(shape:getPoint(i))
          local bDist = cc.pDot(b, normal) - distance
          
          if aDist*bDist < 0.0 then
              local t = math.abs(aDist)/(math.abs(aDist) + math.abs(bDist))
              points[#points + 1] = cc.pLerp(a, b, t)
          end
          j = i
        end
    
        local center = cc.PhysicsShape:getPolygonCenter(points)
        local node = cc.Node:create()
        local polygon = cc.PhysicsBody:createPolygon(points, 
                                                     cc.PHYSICSBODY_MATERIAL_DEFAULT, 
                                                     cc.p(-center.x, -center.y))
        node:setPosition(center)
        node:setPhysicsBody(polygon)
        polygon:setVelocity(body:getVelocityAtWorldPoint(center))
        polygon:setAngularVelocity(body:getAngularVelocity())
        polygon.tag = sliceTag
        layer:addChild(node)
      end


      local function slice(world, info)
        if info.shape:getBody().tag ~= sliceTag then
          return true
         end
    
        if not info.shape:containsPoint(info.start) and not info.shape:containsPoint(info.ended) then
          local normal = cc.p(info.ended.x - info.start.x, info.ended.y - info.start.y)
          normal = cc.pNormalize(cc.pPerp(normal))
          local dist = cc.pDot(info.start, normal)
        
          clipPoly(info.shape, normal, dist)
          clipPoly(info.shape, cc.p(-normal.x, -normal.y), -dist)
        
          info.shape:getBody():removeFromWorld()
        end
        return true
      end

      local function onTouchEnded(touch, event)
        cc.Director:getInstance():getRunningScene():getPhysicsWorld():rayCast(slice, 
                                                                              touch:getStartLocation(), 
                                                                              touch:getLocation())
      end

      local touchListener = cc.EventListenerTouchOneByOne:create()
      touchListener:registerScriptHandler(function() return true end, cc.Handler.EVENT_TOUCH_BEGAN)
      touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
      local eventDispatcher = layer:getEventDispatcher()
      eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
    
      local ground = cc.Node:create()
      ground:setPhysicsBody(cc.PhysicsBody:createEdgeSegment(cc.p(VisibleRect:leftBottom().x, 
                                                                VisibleRect:leftBottom().y + 50), 
                                                           cc.p(VisibleRect:rightBottom().x, 
                                                                VisibleRect:rightBottom().y + 50)))
      layer:addChild(ground)
    
      local box = cc.Node:create()
      local points = {cc.p(-100, -100), cc.p(-100, 100), cc.p(100, 100), cc.p(100, -100)}
      box:setPhysicsBody(cc.PhysicsBody:createPolygon(points))
      box:setPosition(VisibleRect:center())
      box:getPhysicsBody().tag = sliceTag
      layer:addChild(box)
    end
  
  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Slice")
  Helper.subtitleLabel:setString("click and drag to slice up the block")

  return layer
end


local function PhysicsDemoBug3988()
    local layer = cc.Layer:create()
    local function onEnter()
      layer:toggleDebug()
      cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0, 0))

      local ball  = cc.Sprite:create("Images/YellowSquare.png")
      ball:setPosition(cc.p(VisibleRect:center().x-100, VisibleRect:center().y))
      ball:setRotation(30.0)
      layer:addChild(ball)

      local physicsBall = makeBox(cc.p(VisibleRect:center().x+100, 
                                       VisibleRect:center().y), 
                                  cc.size(100, 100))
      physicsBall:setRotation(30.0)
      layer:addChild(physicsBall)
    end
  
  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Bug3988")
  Helper.subtitleLabel:setString("All the Rectangles should have same rotation angle")

  return layer
end

local function PhysicsContactTest()
    local layer = cc.Layer:create()
    local function onEnter()
      cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0, 0))
      local s = cc.size(VisibleRect:getVisibleRect().width, VisibleRect:getVisibleRect().height)
      
      layer.yellowBoxNum = 50
      layer.blueBoxNum = 50
      layer.yellowTriangleNum = 50
      layer.blueTriangleNum = 50

      local function onContactBegin(contact)
        local a = contact:getShapeA():getBody()
        local b = contact:getShapeB():getBody()
        local body = (a:getCategoryBitmask() == 4 or a:getCategoryBitmask() == 8) and a or b
        
        assert(body:getCategoryBitmask() == 4 or body:getCategoryBitmask() == 8, "physics contact fail")
        
        return true
      end
      
      local function resetTest()
        layer:removeChildByTag(10)
        local root = cc.Node:create()
        root:setTag(10)
        layer:addChild(root)
        
        local s = cc.size(VisibleRect:getVisibleRect().width, VisibleRect:getVisibleRect().height)
        local subtitleLabelPosX, subtitleLabelPosY = Helper.subtitleLabel:getPosition()
        local restartTestItemPosX, restartTestItemPosY = Helper.restartTestItem:getPosition()
        local prevMenuPos = subtitleLabelPosY -  Helper.subtitleLabel:getContentSize().height;
        local menuStep = (subtitleLabelPosY  -restartTestItemPosY) * 0.25;

        local label = cc.Label:createWithTTF(tostring(layer.yellowBoxNum), s_arialPath, 32)
        root:addChild(label, 1)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(s.width/2, prevMenuPos))
        
        prevMenuPos = prevMenuPos - menuStep
        label = cc.Label:createWithTTF(tostring(layer.blueBoxNum), s_arialPath, 32)
        root:addChild(label, 1)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(s.width/2, prevMenuPos))
        
        prevMenuPos = prevMenuPos - menuStep
        label = cc.Label:createWithTTF(tostring(layer.yellowTriangleNum), s_arialPath, 32)
        root:addChild(label, 1)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(s.width/2, prevMenuPos))
        
        prevMenuPos = prevMenuPos - menuStep
        label = cc.Label:createWithTTF(tostring(layer.blueTriangleNum), s_arialPath, 32)
        root:addChild(label, 1)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(s.width/2, prevMenuPos))
        
        local wall = cc.Node:create()
        wall:setPhysicsBody(cc.PhysicsBody:createEdgeBox(s, cc.PhysicsMaterial(0.1, 1, 0.0)))
        wall:setPosition(VisibleRect:center())
        root:addChild(wall)
        
        -- yellow box, will collide with itself and blue box.
        for i = 1, layer.yellowBoxNum do
            local size = cc.size(10 + math.random()*10, 10 + math.random()*10)
            local winSize = cc.size(VisibleRect:getVisibleRect().width, 
                                    VisibleRect:getVisibleRect().height)
            local position = cc.p(winSize.width - size.width, winSize.height - size.height)
            position.x = position.x * math.random()
            position.y = position.y * math.random()
            position = cc.p(VisibleRect:leftBottom().x + position.x + size.width/2, 
                            VisibleRect:leftBottom().y + position.y + size.height/2)
            local velocity = cc.p((math.random() - 0.5)*200, (math.random() - 0.5)*200)
            local box = makeBox(position, size, 1, cc.PhysicsMaterial(0.1, 1, 0.0))
            local boxPhysicsBody = box:getPhysicsBody()
            boxPhysicsBody:setVelocity(velocity)
            boxPhysicsBody:setCategoryBitmask(1)    -- 0001
            boxPhysicsBody:setContactTestBitmask(4) -- 0100
            boxPhysicsBody:setCollisionBitmask(3)   -- 0011
            root:addChild(box)
        end
        
        -- blue box, will collide with blue box.
        for i = 1, layer.blueBoxNum do
            local size = cc.size(10 + math.random()*10, 10 + math.random()*10)
            local winSize = cc.size(VisibleRect:getVisibleRect().width, VisibleRect:getVisibleRect().height)
            local position = cc.p(winSize.width - size.width, winSize.height - size.height)
            position.x = position.x * math.random()
            position.y = position.y * math.random()
            position = cc.p(VisibleRect:leftBottom().x + position.x + size.width/2, 
                            VisibleRect:leftBottom().y + position.y + size.height/2)
            local velocity = cc.p((math.random() - 0.5)*200, (math.random() - 0.5)*200)
            local box = makeBox(position, size, 2, cc.PhysicsMaterial(0.1, 1, 0.0))
            local boxPhysicsBody = box:getPhysicsBody()
            boxPhysicsBody:setVelocity(velocity)
            boxPhysicsBody:setCategoryBitmask(2)    -- 0010
            boxPhysicsBody:setContactTestBitmask(8) -- 1000
            boxPhysicsBody:setCollisionBitmask(1)   -- 0001
            root:addChild(box)
        end
        
        -- yellow triangle, will collide with itself and blue box.
        for i = 1, layer.yellowTriangleNum do
            local size = cc.size(10 + math.random()*10, 10 + math.random()*10)
            local winSize = cc.size(VisibleRect:getVisibleRect().width, 
                                    VisibleRect:getVisibleRect().height)
            local position = cc.p(winSize.width - size.width, winSize.height - size.height)
            position.x = position.x * math.random()
            position.y = position.y * math.random()
            position = cc.p(VisibleRect:leftBottom().x + position.x + size.width/2, 
                            VisibleRect:leftBottom().y + position.y + size.height/2)
            local velocity = cc.p((math.random() - 0.5)*200, (math.random() - 0.5)*200)
            local triangle = makeTriangle(position, size, 1, cc.PhysicsMaterial(0.1, 1, 0.0))
            local trianglePhysicsBody = triangle:getPhysicsBody()
            trianglePhysicsBody:setVelocity(velocity)
            trianglePhysicsBody:setCategoryBitmask(4)    -- 0100
            trianglePhysicsBody:setContactTestBitmask(1) -- 0001
            trianglePhysicsBody:setCollisionBitmask(6)   -- 0110
            root:addChild(triangle)
        end
        
        -- blue triangle, will collide with yellow box.
        for i = 1, layer.blueTriangleNum do
            local size = cc.size(10 + math.random()*10, 10 + math.random()*10)
            local winSize = cc.size(VisibleRect:getVisibleRect().width, 
                                    VisibleRect:getVisibleRect().height)
            local position = cc.p(winSize.width - size.width, winSize.height - size.height)
            position.x = position.x * math.random()
            position.y = position.y * math.random()
            position = cc.p(VisibleRect:leftBottom().x + position.x + size.width/2, 
                            VisibleRect:leftBottom().y + position.y + size.height/2)
            local velocity = cc.p((math.random() - 0.5)*200, (math.random() - 0.5)*200)
            local triangle = makeTriangle(position, size, 2, cc.PhysicsMaterial(0.1, 1, 0.0))
            local trianglePhysicsBody = triangle:getPhysicsBody()
            trianglePhysicsBody:setVelocity(velocity)
            trianglePhysicsBody:setCategoryBitmask(8)    -- 1000
            trianglePhysicsBody:setContactTestBitmask(2) -- 0010
            trianglePhysicsBody:setCollisionBitmask(1)   -- 0001
            root:addChild(triangle)
        end
      end

      local function onDecrease(tag, sender)
        if tag == 1 then
          if layer.yellowBoxNum > 0 then layer.yellowBoxNum = layer.yellowBoxNum - 50 end
        elseif tag == 2 then
          if layer.blueBoxNum > 0 then layer.blueBoxNum = layer.blueBoxNum - 50 end
        elseif tag == 3 then
          if layer.yellowTriangleNum > 0 then layer.yellowTriangleNum = layer.yellowTriangleNum - 50 end
        elseif tag == 4 then
          if layer.blueTriangleNum > 0 then layer.blueTriangleNum = layer.blueTriangleNum - 50 end
        end

        resetTest()
      end

      local function onIncrease(tag, sender)
        if tag == 1 then
          layer.yellowBoxNum = layer.yellowBoxNum + 50
        elseif tag == 2 then
          layer.blueBoxNum = layer.blueBoxNum + 50
        elseif tag == 3 then
          layer.yellowTriangleNum = layer.yellowTriangleNum + 50
        elseif tag == 4 then
          layer.blueTriangleNum = layer.blueTriangleNum + 50
        end

        resetTest()
      end

      local subtitleLabelPosX, subtitleLabelPosY = Helper.subtitleLabel:getPosition()
      local restartTestItemPosX, restartTestItemPosY = Helper.restartTestItem:getPosition()
      local prevMenuPos = subtitleLabelPosY -  Helper.subtitleLabel:getContentSize().height;
      local menuStep = (subtitleLabelPosY  -restartTestItemPosY) * 0.25;

      cc.MenuItemFont:setFontSize(30)
      local decrease1 = cc.MenuItemFont:create(" - ")
      decrease1:setColor(cc.c3b(0,200,20))
      local increase1 = cc.MenuItemFont:create(" + ")
      increase1:setColor(cc.c3b(0,200,20))
      decrease1:setTag(1)
      increase1:setTag(1)
      decrease1:registerScriptTapHandler(onDecrease)
      increase1:registerScriptTapHandler(onIncrease)
      
      local menu1 = cc.Menu:create(decrease1, increase1)
      menu1:alignItemsHorizontally()
      menu1:setPosition(cc.p(s.width/2, prevMenuPos))
      layer:addChild(menu1, 1)
      
      local label = cc.Label:createWithTTF("yellow box", s_arialPath, 32)
      layer:addChild(label, 1)
      label:setAnchorPoint(cc.p(0.5, 0.5))
      label:setPosition(cc.p(s.width/2 - 150, prevMenuPos))
      
      local decrease2 = cc.MenuItemFont:create(" - ")
      decrease2:setColor(cc.c3b(0,200,20))
      local increase2 = cc.MenuItemFont:create(" + ")
      increase2:setColor(cc.c3b(0,200,20))
      decrease2:setTag(2)
      increase2:setTag(2)
      decrease2:registerScriptTapHandler(onDecrease)
      increase2:registerScriptTapHandler(onIncrease)
      
      prevMenuPos = prevMenuPos - menuStep
      local menu2 = cc.Menu:create(decrease2, increase2)
      menu2:alignItemsHorizontally()
      menu2:setPosition(cc.p(s.width/2,  prevMenuPos))
      layer:addChild(menu2, 1)
      
      label = cc.Label:createWithTTF("blue box", s_arialPath, 32)
      layer:addChild(label, 1)
      label:setAnchorPoint(cc.p(0.5, 0.5))
      label:setPosition(cc.p(s.width/2 - 150, prevMenuPos))
      
      local decrease3 = cc.MenuItemFont:create(" - ")
      decrease3:setColor(cc.c3b(0,200,20))
      local increase3 = cc.MenuItemFont:create(" + ")
      increase3:setColor(cc.c3b(0,200,20))
      decrease3:setTag(3)
      increase3:setTag(3)
      decrease3:registerScriptTapHandler(onDecrease)
      increase3:registerScriptTapHandler(onIncrease)
      
      prevMenuPos = prevMenuPos - menuStep
      local menu3 = cc.Menu:create(decrease3, increase3)
      menu3:alignItemsHorizontally()
      menu3:setPosition(cc.p(s.width/2, prevMenuPos))
      layer:addChild(menu3, 1)
      
      label = cc.Label:createWithTTF("yellow triangle", s_arialPath, 32)
      layer:addChild(label, 1)
      label:setAnchorPoint(cc.p(0.5, 0.5))
      label:setPosition(cc.p(s.width/2 - 150, prevMenuPos))
      
      local decrease4 = cc.MenuItemFont:create(" - ")
      decrease4:setColor(cc.c3b(0,200,20))
      local increase4 = cc.MenuItemFont:create(" + ")
      increase4:setColor(cc.c3b(0,200,20))
      decrease4:setTag(4)
      increase4:setTag(4)
      decrease4:registerScriptTapHandler(onDecrease)
      increase4:registerScriptTapHandler(onIncrease)
      
      prevMenuPos = prevMenuPos - menuStep
      local menu4 = cc.Menu:create(decrease4, increase4)
      menu4:alignItemsHorizontally()
      menu4:setPosition(cc.p(s.width/2, prevMenuPos))
      layer:addChild(menu4, 1)
      
      label = cc.Label:createWithTTF("blue triangle", s_arialPath, 32)
      layer:addChild(label, 1)
      label:setAnchorPoint(cc.p(0.5, 0.5))
      label:setPosition(cc.p(s.width/2 - 150, prevMenuPos))


      local contactListener = cc.EventListenerPhysicsContact:create()
      contactListener:registerScriptHandler(onContactBegin, cc.Handler.EVENT_PHYSICS_CONTACT_BEGIN)
      local eventDispatcher = layer:getEventDispatcher()
      eventDispatcher:addEventListenerWithSceneGraphPriority(contactListener, layer)
    
      resetTest()
    end
  
  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Contact Test")

  return layer
end

local function PhysicsPositionRotationTest()
    local layer = cc.Layer:create()
    local function onEnter()
      layer:toggleDebug()

      cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0, 0))
        
      local touchListener = cc.EventListenerTouchOneByOne:create()
      touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN) 
      touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED) 
      touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
      local eventDispatcher = layer:getEventDispatcher()
      eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)
      
      local wall = cc.Node:create()
      wall:setPhysicsBody(cc.PhysicsBody:createEdgeBox(VisibleRect:getVisibleRect()))
      wall:setPosition(VisibleRect:center())
      layer:addChild(wall)
      
      -- anchor test
      local anchorNode = cc.Sprite:create("Images/YellowSquare.png")
      anchorNode:setAnchorPoint(cc.p(0.1, 0.9))
      anchorNode:setPosition(100, 100)
      anchorNode:setScale(0.25)
      anchorNode:setPhysicsBody(cc.PhysicsBody:createBox(anchorNode:getContentSize()))
      anchorNode:getPhysicsBody():setTag(DRAG_BODYS_TAG)
      layer:addChild(anchorNode)
      
      --parent test
      local parent = cc.Sprite:create("Images/YellowSquare.png")
      parent:setPosition(200, 100)
      parent:setScale(0.25)
      local parentPhysicsBody = cc.PhysicsBody:createBox(anchorNode:getContentSize())
      parent:setPhysicsBody(parentPhysicsBody)
      parentPhysicsBody:setTag(DRAG_BODYS_TAG)
      layer:addChild(parent)
      
      local leftBall = cc.Sprite:create("Images/ball.png")
      leftBall:setPosition(-30, 0)
      leftBall:setScale(2)
      leftBall:setPhysicsBody(cc.PhysicsBody:createCircle(leftBall:getContentSize().width / 2))
      leftBall:getPhysicsBody():setTag(DRAG_BODYS_TAG)
      parent:addChild(leftBall)
      
      -- offset position rotation test
      local offsetPosNode = cc.Sprite:create("Images/YellowSquare.png")
      offsetPosNode:setPosition(100, 200)
      local offsetPosNodePhysicsBody = cc.PhysicsBody:createBox(cc.size(offsetPosNode:getContentSize().width/2, 
                                                                        offsetPosNode:getContentSize().height/2))
      offsetPosNode:setPhysicsBody(offsetPosNodePhysicsBody)
      offsetPosNodePhysicsBody:setPositionOffset(cc.p(-offsetPosNode:getContentSize().width/2, 
                                                      -offsetPosNode:getContentSize().height/2))
      offsetPosNodePhysicsBody:setRotationOffset(45)
      offsetPosNodePhysicsBody:setTag(DRAG_BODYS_TAG)
      layer:addChild(offsetPosNode)
    end
  
  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Position/Rotation Test")

  return layer
end

local function PhysicsSetGravityEnableTest()
  local layer = cc.Layer:create()
  local function onEnter()

    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
    touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)

    local wall = cc.Node:create()
    wall:setPhysicsBody(cc.PhysicsBody:createEdgeBox(cc.size(VisibleRect:getVisibleRect().width, 
                                                             VisibleRect:getVisibleRect().height),
                                                     cc.PhysicsMaterial(0.1, 1.0, 0.0)))
    wall:setPosition(VisibleRect:center());
    layer:addChild(wall)

    local commonBox = makeBox(cc.p(100, 100), cc.size(50, 50), 1)
    commonBox:getPhysicsBody():setTag(DRAG_BODYS_TAG)
    layer:addChild(commonBox)

    local box = makeBox(cc.p(200, 100), cc.size(50, 50), 2)
    local boxBody = box:getPhysicsBody()
    boxBody:setMass(20)
    boxBody:setTag(DRAG_BODYS_TAG)
    boxBody:setGravityEnable(false)
    layer:addChild(box)

    local ball = makeBall(layer,cc.p(200,200),50)
    ball:setTag(2)
    local ballBody = ball:getPhysicsBody()
    ballBody:setTag(DRAG_BODYS_TAG)
    ballBody:setGravityEnable(false)
    ballBody:setMass(50)
    layer:addChild(ball)

    local function onScheduleOnce()
      cclog("onScheduleOnce")
      local ball = layer:getChildByTag(2)
      ball:getPhysicsBody():setMass(200)
      cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0, 98))
    end
    --layer:scheduleOnce(onScheduleOnce,1.0)
    local action = cc.Sequence:create(cc.DelayTime:create(1.0),
                                      cc.CallFunc:create(onScheduleOnce))
    layer:runAction(action)
  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Set Gravity Enable Test")
  Helper.subtitleLabel:setString("only yellow box drop down")
  return layer
end

local function PhysicsDemoBug5482()
  local layer = cc.Layer:create()
  local function onEnter()
    layer:toggleDebug()
    local _bodyInA = false

    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    touchListener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
    touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)

    -- wall
    local wall = cc.Node:create()
    wall:addComponent(cc.PhysicsBody:createEdgeBox(cc.size(VisibleRect:getVisibleRect().width, 
                                                             VisibleRect:getVisibleRect().height),
                                                     cc.PhysicsMaterial(0.1, 1.0, 0.0)))
    wall:setPosition(VisibleRect:center());
    layer:addChild(wall)

    local _nodeA = cc.Sprite:create("Images/YellowSquare.png")
    _nodeA:setPosition(cc.p(VisibleRect:center().x-150,100))
    layer:addChild(_nodeA)

    local _nodeB = cc.Sprite:create("Images/YellowSquare.png")
    _nodeB:setPosition(cc.p(VisibleRect:center().x+150,100))
    layer:addChild(_nodeB)

    local _body = cc.PhysicsBody:createBox(_nodeA:getContentSize())
    _body:setTag(DRAG_BODYS_TAG)
    _body:retain()

    local _button = nil
    local function changeBodyCallback(sender)
    	local node = nil
    	if _bodyInA then
    		node = _nodeB
        _button:setString("Set Body To A")
    		cclog("_nodeB")
    	else
    		node = _nodeA
        _button:setString("Set Body To B")
    		cclog("_nodeA")
    	end
      local owner = _body:getOwner()
      if owner ~= nil then
        owner:removeComponent(_body)
      end

    	node:addComponent(_body)
    	_bodyInA = not _bodyInA
   	end
    
    cc.MenuItemFont:setFontSize(18)
    _button = cc.MenuItemFont:create("Set Body To A");
    _button:registerScriptTapHandler(changeBodyCallback)

    local menu = cc.Menu:create(_button)
    layer:addChild(menu)
  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("bug 5482: setPhysicsBodyTest")
  Helper.subtitleLabel:setString("change physics body to the other.")
  return layer
end

local function PhysicsFixedUpdate()
  local layer = cc.Layer:create()
  local function onEnter()
    cc.Director:getInstance():getRunningScene():getPhysicsWorld():setDebugDrawMask(cc.PhysicsWorld.DEBUGDRAW_ALL)
    cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0, 0))

    local function addBall()
    	local ball = cc.Sprite:create("Images/ball.png")
    	ball:setPosition(cc.p(100,100))
    	ball:setPhysicsBody(cc.PhysicsBody:createCircle(ball:getContentSize().width/2, cc.PhysicsMaterial(0.1, 1, 0.0)))
    	ball:getPhysicsBody():setTag(DRAG_BODYS_TAG)
    	ball:getPhysicsBody():setVelocity(cc.p(1000,20))
    	layer:addChild(ball)
    end

    local  function update(delta)
    	for i=1,3 do
    		cc.Director:getInstance():getRunningScene():getPhysicsWorld():step(1/180.0)
    	end
    end

    local function updateStart(delta)
    	addBall()
    	cc.Director:getInstance():getRunningScene():getPhysicsWorld():setAutoStep(false)
    	layer:scheduleUpdateWithPriorityLua(update, 0)
    end

    -- wall
    local wall = cc.Node:create()
    wall:setPhysicsBody(cc.PhysicsBody:createEdgeBox(cc.size(VisibleRect:getVisibleRect().width, 
                                                             VisibleRect:getVisibleRect().height),
                                                     cc.PhysicsMaterial(0.1, 1.0, 0.0)))
    wall:setPosition(VisibleRect:center());
    layer:addChild(wall)

    addBall()
    layer:runAction(cc.Sequence:create(cc.DelayTime:create(2.0),
                                      cc.CallFunc:create(updateStart)))

  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Fixed Update Test")
  Helper.subtitleLabel:setString("The second ball should not run across the wall")
  return layer
end

local function PhysicsTransformTest()
  local layer = cc.Layer:create()
  local function onEnter()
    layer:toggleDebug()
    cc.Director:getInstance():getRunningScene():getPhysicsWorld():setGravity(cc.p(0,0))
    
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)

    local _rootLayer = cc.Layer:create()
    layer:addChild(_rootLayer)

    local wall = cc.Node:create()
    wall:setPhysicsBody(cc.PhysicsBody:createEdgeBox(cc.size(VisibleRect:getVisibleRect().width, 
                                                             VisibleRect:getVisibleRect().height),
                                                     cc.PhysicsMaterial(0.1, 1.0, 0.0)))
    wall:setPosition(VisibleRect:center());
    _rootLayer:addChild(wall)
    
    local _parentSprite = cc.Sprite:create("Images/YellowSquare.png")
    _parentSprite:setPosition(cc.p(200,100))
    _parentSprite:setScale(0.25)
    _parentSprite:setPhysicsBody(cc.PhysicsBody:createBox(_parentSprite:getContentSize(),cc.PhysicsMaterial(0.1, 1.0, 0.0)))
    _parentSprite:getPhysicsBody():setTag(DRAG_BODYS_TAG)
    _parentSprite:setTag(1)
    _rootLayer:addChild(_parentSprite)

    local leftBall = cc.Sprite:create("Images/ball.png")
    leftBall:setPosition(cc.p(-30,0))
    leftBall:setScale(2)
    leftBall:setPhysicsBody(cc.PhysicsBody:createCircle(leftBall:getContentSize().width/2,cc.PhysicsMaterial(0.1,1.0,0.0)))
    leftBall:getPhysicsBody():setTag(DRAG_BODYS_TAG)
    _parentSprite:addChild(leftBall)

    local scaleTo = cc.ScaleTo:create(2.0,0.5)
    local scaleBack = cc.ScaleTo:create(2.0,1.0)
    _parentSprite:runAction(cc.RepeatForever:create(cc.Sequence:create(scaleTo,scaleBack)))

    local normal = cc.Sprite:create("Images/YellowSquare.png")
    normal:setPosition(cc.p(300,100))
    normal:setScale(0.25,0.5)
    normal:setPhysicsBody(cc.PhysicsBody:createBox(normal:getContentSize(),cc.PhysicsMaterial(0.1,1.0,0.0)))
    normal:getPhysicsBody():setTag(DRAG_BODYS_TAG)
    _rootLayer:addChild(normal)

    local  bullet = cc.Sprite:create("Images/ball.png")
    bullet:setPosition(cc.p(200,200))
    bullet:setPhysicsBody(cc.PhysicsBody:createCircle(bullet:getContentSize().width/2,cc.PhysicsMaterial(0.1,1.0,0.0)))
    bullet:getPhysicsBody():setVelocity(cc.p(100,100))
    _rootLayer:addChild(bullet)

    local move = cc.MoveBy:create(2.0,cc.p(100,100))
    local move2 = cc.MoveBy:create(2.0,cc.p(-200,0))
    local move3 = cc.MoveBy:create(2.0,cc.p(100,-100))
    local scale = cc.ScaleTo:create(3.0,0.3)
    local scale2 = cc.ScaleTo:create(3.0,1.0)
    local rotate = cc.RotateBy:create(6.0,360)

    _rootLayer:runAction(cc.RepeatForever:create(cc.Sequence:create(move,move2,move3)))
    _rootLayer:runAction(cc.RepeatForever:create(cc.Sequence:create(scale,scale2)))
    _rootLayer:runAction(cc.RepeatForever:create(cc.Sequence:create(rotate)))
  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Physics transform test")
  return layer
end

local function PhysicsIssue9959()
  local layer = cc.Layer:create()
  local function onEnter()
    local origin = cc.Director:getInstance():getVisibleOrigin()
    local visibleSize = cc.Director:getInstance():getVisibleSize()

    local scale9Sprite1 = ccui.Scale9Sprite:create("Images/ball.png")
    scale9Sprite1:setPosition(cc.p(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2))
    layer:addChild(scale9Sprite1)
    scale9Sprite1:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.MoveBy:create(2.0,cc.p(100.0,0.0)),
    																   cc.MoveBy:create(2.0,cc.p(-100,0.0)))))

    local scale9Sprite2 = ccui.Scale9Sprite:create("Images/ball.png")
    scale9Sprite2:setPosition(cc.p(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+50))
    layer:addChild(scale9Sprite2)
    scale9Sprite2:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.ScaleTo:create(2.0,1.5),
    																   cc.ScaleTo:create(2.0,1.0))))

    local scale9Sprite3 = ccui.Scale9Sprite:create("Images/ball.png")
    scale9Sprite3:setPosition(cc.p(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2-50))
    layer:addChild(scale9Sprite3)
    scale9Sprite3:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.RotateBy:create(2.0,360))))
  end

  initWithLayer(layer, onEnter)
  Helper.titleLabel:setString("Reorder issue #9959")
  Helper.subtitleLabel:setString("Test Scale9Sprite run scale/move/rotation action in physics scene")
  return layer
end

function PhysicsTest()
  cclog("PhysicsTest")
  local scene = cc.Scene:createWithPhysics()


   Helper.usePhysics = true
   Helper.createFunctionTable = {
      PhysicsDemoLogoSmash,
      PhysicsDemoPyramidStack,
      PhysicsDemoClickAdd,
      PhysicsDemoRayCast,
      PhysicsDemoJoints,
      PhysicsDemoActions,
      PhysicsDemoPump,
      PhysicsDemoOneWayPlatform,
      PhysicsDemoSlice,
      PhysicsDemoBug3988,
      PhysicsContactTest,
      PhysicsPositionRotationTest,
      PhysicsSetGravityEnableTest,
      PhysicsDemoBug5482,
      PhysicsFixedUpdate,
      PhysicsTransformTest,
      PhysicsIssue9959
   }
   Helper.index = 1

   scene:addChild(Helper.createFunctionTable[1]())
   scene:addChild(CreateBackMenuItem())
   return scene
end
