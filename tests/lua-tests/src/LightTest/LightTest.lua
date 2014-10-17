local LightTest = class("LightTest",function()
    return cc.Layer:create()
end)

function LightTest:ctor()

  local function onNodeEvent(event)
      if event == "enter" then
          self:init()
      elseif event == "exit" then
          self:unscheduleUpdate()
      end
  end

  self:registerScriptHandler(onNodeEvent)
end

function LightTest:init()

    self:addSprite()
    self:addLights()

    local s = cc.Director:getInstance():getWinSize()
    local camera = cc.Camera:createPerspective(60, s.width/s.height, 1.0, 1000.0)
    camera:setCameraFlag(cc.CameraFlag.USER1)
    camera:setPosition3D(cc.vec3(0.0, 100, 100))
    camera:lookAt(cc.vec3(0.0, 0.0, 0.0), cc.vec3(0.0, 1.0, 0.0))
    self:addChild(camera)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 15

    local ambientLightLabel = cc.Label:createWithTTF(ttfConfig,"Ambient Light ON")
    local menuItem0 = cc.MenuItemLabel:create(ambientLightLabel)
    menuItem0:registerScriptTapHandler(function (tag, sender)
        local str = nil
        local isON = not self._ambientLight:isEnabled()
        if isON then
            str = "Ambient Light ON"
        else
            str = "Ambient Light OFF"
        end
        self._ambientLight:setEnabled(isON)
        menuItem0:setString(str)
    end)

 
    local directionalLightLabel = cc.Label:createWithTTF(ttfConfig,"Directional Light OFF")
    local menuItem1 = cc.MenuItemLabel:create(directionalLightLabel)
    menuItem1:registerScriptTapHandler(function (tag, sender)
        local str = nil
        local isON = not self._directionalLight:isEnabled()
        if isON then
            str = "Directional Light ON"
        else
            str = "Directional Light OFF"
        end
        self._directionalLight:setEnabled(isON)
        menuItem1:setString(str)
    end)


    local pointLightLabel = cc.Label:createWithTTF(ttfConfig,"Point Light OFF")
    local menuItem2 = cc.MenuItemLabel:create(pointLightLabel)
    menuItem2:registerScriptTapHandler(function (tag, sender)
        local str = nil
        local isON = not self._pointLight:isEnabled()
        if isON then
            str = "Point Light ON"
        else
            str = "Point Light OFF"
        end
        self._pointLight:setEnabled(isON)
        menuItem2:setString(str)
    end)

    local spotLightLabel = cc.Label:createWithTTF(ttfConfig,"Spot Light OFF")
    local menuItem3 = cc.MenuItemLabel:create(spotLightLabel)
    menuItem3:registerScriptTapHandler(function (tag, sender)
        local str = nil
        local isON = not self._spotLight:isEnabled()
        if isON then
            str = "Spot Light ON"
        else
            str = "Spot Light OFF"
        end
        self._spotLight:setEnabled(isON)
        menuItem3:setString(str)
    end)


    local menu = cc.Menu:create(menuItem0, menuItem1, menuItem2, menuItem3)
    menu:setPosition(cc.p(0, 0))
    menuItem0:setAnchorPoint(cc.p(0.0 ,1.0))
    menuItem0:setPosition( cc.p(VisibleRect:left().x, VisibleRect:top().y-50) )
    menuItem1:setAnchorPoint(cc.p(0.0, 1.0))
    menuItem1:setPosition( cc.p(VisibleRect:left().x, VisibleRect:top().y-100) )
    menuItem2:setAnchorPoint(cc.p(0.0, 1.0))
    menuItem2:setPosition( cc.p(VisibleRect:left().x, VisibleRect:top().y -150))
    menuItem3:setAnchorPoint(cc.p(0.0, 1.0))
    menuItem3:setPosition( cc.p(VisibleRect:left().x, VisibleRect:top().y -200))
    self:addChild(menu)

    local angleDelta = 0.0
    local function update(delta)
        if nil ~= self._directionalLight then
            self._directionalLight:setRotation3D(cc.vec3(-45.0, -angleDelta * 57.29577951, 0.0))
        end
    
        if nil ~= self._pointLight then
            self._pointLight:setPositionX(100.0 * math.cos(angleDelta + 2.0 * delta))
            self._pointLight:setPositionY(100.0)
            self._pointLight:setPositionZ(100.0 * math.sin(angleDelta + 2.0 * delta))
        end
    
        if nil ~= self._spotLight then
            self._spotLight:setPositionX(100.0 * math.cos(angleDelta + 4.0 * delta))
            self._spotLight:setPositionY(100.0)
            self._spotLight:setPositionZ(100.0 * math.sin(angleDelta + 4.0 * delta))
            self._spotLight:setDirection(cc.vec3(-math.cos(angleDelta + 4.0 * delta), -1.0, -math.sin(angleDelta + 4.0 * delta)))
        end
    
        angleDelta = angleDelta + delta
    end

    self:scheduleUpdateWithPriorityLua(update,0)
end

function LightTest:addSprite()
    local s = cc.Director:getInstance():getWinSize()

    local fileName = "Sprite3DTest/orc.c3b"
    local sprite1 = cc.Sprite3D:create(fileName)
    sprite1:setRotation3D(cc.vec3(0.0, 180.0, 0.0))
    sprite1:setPosition(cc.p(0.0, 0.0))
    sprite1:setScale(2.0)
    local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
    sprite1:getAttachNode("Bip001 R Hand"):addChild(sp)
    local animation = cc.Animation3D:create(fileName)
    if nil ~=animation then
        local animate = cc.Animate3D:create(animation)
        sprite1:runAction(cc.RepeatForever:create(animate))
    end
    self:addChild(sprite1)
    sprite1:setCameraMask(2)

    local fileName = "Sprite3DTest/sphere.c3b"
    local sprite2 = cc.Sprite3D:create(fileName)
    sprite2:setPosition(cc.p(30.0, 0.0))
    self:addChild(sprite2)
    sprite2:setCameraMask(2)

    
    local fileName = "Sprite3DTest/sphere.c3b"
    local sprite3   = cc.Sprite3D:create(fileName)
    sprite3:setScale(0.5)
    sprite3:setPosition(cc.p(-50.0, 0.0))
    self:addChild(sprite3)
    sprite3:setCameraMask(2)
    
    local fileName = "Sprite3DTest/sphere.c3b"
    local sprite4 = cc.Sprite3D:create(fileName)
    sprite4:setScale(0.5)
    sprite4:setPosition(cc.p(-30.0, 10.0))
    self:addChild(sprite4)
    sprite4:setCameraMask(2)
end

function LightTest:addLights()
    local s = cc.Director:getInstance():getWinSize()
    self._ambientLight = cc.AmbientLight:create(cc.c3b(200, 200, 200))
    self._ambientLight:setEnabled(true)
    self:addChild(self._ambientLight)
    self._ambientLight:setCameraMask(2)

    self._directionalLight = cc.DirectionLight:create(cc.vec3(-1.0, -1.0, 0.0), cc.c3b(200, 200, 200))
    self._directionalLight:setEnabled(false)
    self:addChild(self._directionalLight)
    self._directionalLight:setCameraMask(2)

    self._pointLight = cc.PointLight:create(cc.vec3(0.0, 0.0, 0.0), cc.c3b(200, 200, 200), 10000.0)
    self._pointLight:setEnabled(false)
    self:addChild(self._pointLight)
    self._pointLight:setCameraMask(2)

    self._spotLight = cc.SpotLight:create(cc.vec3(-1.0, -1.0, 0.0), cc.vec3(0.0, 0.0, 0.0), cc.c3b(200, 200, 200), 0.0, 0.5, 10000.0)
    self._spotLight:setEnabled(false)
    self:addChild(self._spotLight)
    self._spotLight:setCameraMask(2)

    local tintto1 = cc.TintTo:create(4, 0, 0, 255)
    local tintto2 = cc.TintTo:create(4, 0, 255, 0)
    local tintto3 = cc.TintTo:create(4, 255, 0, 0)
    local tintto4 = cc.TintTo:create(4, 255, 255, 255)
    local seq = cc.Sequence:create(tintto1,tintto2, tintto3, tintto4)
    self._ambientLight:runAction(cc.RepeatForever:create(seq))

    tintto1 = cc.TintTo:create(4, 255, 0, 0)
    tintto2 = cc.TintTo:create(4, 0, 255, 0)
    tintto3 = cc.TintTo:create(4, 0, 0, 255)
    tintto4 = cc.TintTo:create(4, 255, 255, 255)
    seq = cc.Sequence:create(tintto1,tintto2, tintto3, tintto4)
    self._directionalLight:runAction(cc.RepeatForever:create(seq))


    tintto1 = cc.TintTo:create(4, 255, 0, 0)
    tintto2 = cc.TintTo:create(4, 0, 255, 0)
    tintto3 = cc.TintTo:create(4, 0, 0, 255)
    tintto4 = cc.TintTo:create(4, 255, 255, 255)
    seq = cc.Sequence:create(tintto2, tintto1, tintto3, tintto4)
    self._pointLight:runAction(cc.RepeatForever:create(seq))

    tintto1 = cc.TintTo:create(4, 255, 0, 0)
    tintto2 = cc.TintTo:create(4, 0, 255, 0)
    tintto3 = cc.TintTo:create(4, 0, 0, 255)
    tintto4 = cc.TintTo:create(4, 255, 255, 255)
    seq = cc.Sequence:create(tintto3, tintto2, tintto1, tintto4)
    self._spotLight:runAction(cc.RepeatForever:create(seq))
end

function LightTest.create( ... )
    local layer = LightTest.new()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Light Test")
    return layer
end

function LightTestMain()
    cclog("LightTestMain")
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        LightTest.create,
    }

    scene:addChild(LightTest.create(), 0)
    scene:addChild(CreateBackMenuItem())
    return scene
end
