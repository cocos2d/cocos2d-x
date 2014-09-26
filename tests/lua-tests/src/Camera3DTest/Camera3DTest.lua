--------------------------------
-- Camera3DTest
--------------------------------
local State = 
{
    None = 0,
    Idle = 0x01,
    Move = 0x02,
    Rotate = 0x04,
    Speak = 0x08,
    MeleeAttack = 0x10,
    RemoteAttack = 0x20,
    Attack = 0x40,
}

local CameraType = 
{
    FreeCamera = 0,
    FirstCamera = 1,
    ThirdCamera = 2,
}

local Camera3DTestDemo = class("", function ()
    return cc.Layer:create()
end)

function Camera3DTestDemo:ctor()
    -- body
    self._title = ""
    self._layer3D = nil
    self._sprite3D = nil
    self._targetPos = nil
    self._cameraType = 0
    self._incRot = nil
    self._decRot = nil
    self._curState = 0
    self._camera = nil
    self._moveAction = nil
    self:init()
end

function Camera3DTestDemo:addNewSpriteWithCoords(vec3, filename, ...)
    
end

function Camera3DTestDemo:scaleCameraCallback(sender, value)
    
end

function Camera3DTestDemo:rotateCameraCallback( sender,value)
    -- body
end

function Camera3DTestDemo:SwitchViewCallback(sender, value)
    if self._cameraType == value then
        return
    end

    self._cameraType = value

    if self._cameraType == CameraType.FreeCamera then
        local pos3D = self._sprite3D:getPosition3D()
        self._camera:setPosition3D(cc.vec3(0 + pos3D.x, 130 + pos3D.y, 130 + pos3D.z))
        self._camera:lookAt(self._sprite3D:getPosition3D(), cc.vec3(0,1,0))
        self._incRot:setEnabled(true)
        self._decRot:setEnabled(true)

    elseif self._cameraType == CameraType.FirstCamera then
        local newFaceDir = {}
        local transform = self._sprite3D:getWorldToNodeTransform()
        newFaceDir.x = -transform[9]
        newFaceDir.y = -transform[10]
        newFaceDir.z = -transform[11]
        newFaceDir = cc.vec3normalize(newFaceDir)
        local pos3D = self._sprite3D:getPosition3D()

    elseif self._cameraType == CameraType.ThirdCamera then

    end

end

function Camera3DTestDemo:update(ft)
    -- body
end

function Camera3DTestDemo:title()
    return "Testing Camera"
end

function Camera3DTestDemo:subtitle()
    return ""
end

function Camera3DTestDemo:onEnter()
    self._sprite3D = nil
    local s = cc.Director:getInstance():getWinSize()
    local listener = cc.EventListenerTouchAllAtOnce:create()

    listener:registerScriptHandler(function(touches, event)
        -- body
    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function(touches, event)
        -- body
    end, cc.Handler.EVENT_TOUCHES_MOVED)

    listener:registerScriptHandler(function(touches, event)
        -- body
    end, cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local layer3D = cc.Layer:create()
    self:addChild(layer3D,0)
    self._layer3D = layer3D
    self._curState = State.None
    self:addNewSpriteWithCoords(cc.vec3(0, 0, 0), "Sprite3DTest/girl.c3b", true, 0.2, true)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 20

    local label1 = cc.Label:createWithTTF(ttfConfig,"zoom out")
    local menuItem1 = cc.MenuItemLabel:create(label1)
    menuItem1:registerScriptTapHandler(function (tag, sender ) -- zoom out

    end)

    local label2 = cc.Label:createWithTTF(ttfConfig,"zoom in")
    local menuItem2 = cc.MenuItemLabel:create(label2)
    menuItem2:registerScriptTapHandler(function (tag, sender ) -- zoom in

    end)

    local label3 = cc.Label:createWithTTF(ttfConfig,"rotate+")
    local menuItem3 = cc.MenuItemLabel:create(label3)
    menuItem3:registerScriptTapHandler(function (tag, sender ) -- rotate +

    end)

    local label4 = cc.Label:createWithTTF(ttfConfig,"rotate-")
    local menuItem4 = cc.MenuItemLabel:create(label4)
    menuItem4:registerScriptTapHandler(function (tag, sender ) -- rotate -

    end)

    local label5 = cc.Label:createWithTTF(ttfConfig,"free")
    local menuItem5 = cc.MenuItemLabel:create(label5)
    menuItem5:registerScriptTapHandler(function (tag, sender ) -- free

    end)

    local label6 = cc.Label:createWithTTF(ttfConfig,"third person")
    local menuItem6 = cc.MenuItemLabel:create(label6)
    menuItem6:registerScriptTapHandler(function (tag, sender ) -- third person

    end)

    local label7 = cc.Label:createWithTTF(ttfConfig,"third person")
    local menuItem7 = cc.MenuItemLabel:create(label7)
    menuItem7:registerScriptTapHandler(function (tag, sender ) -- first person

    end)

    local menu = cc.Menu:create(menuItem1,menuItem2,menuItem3,menuItem4,menuItem5,menuItem6,menuItem7)
    menu:setPosition(cc.p(0, 0))
    menuItem1:setPosition(s.width-50, VisibleRect:top().y-50 )
    menuItem2:setPosition(s.width-50, VisibleRect:top().y-100)
    menuItem3:setPosition(s.width-50, VisibleRect:top().y-150)
    menuItem4:setPosition(s.width-50, VisibleRect:top().y-200)
    menuItem5:setPosition(VisibleRect:left().x+100, VisibleRect:top().y-50)
    menuItem6:setPosition(VisibleRect:left().x+100, VisibleRect:top().y -100)
    menuItem7:setPosition(VisibleRect:left().x+100, VisibleRect:top().y -150)
    self:addChild(menu, 0)

    if self._camera == nil then
        self._camera = cc.Camera:createPerspective(60, s.width / s.height, 1, 1000)
        self._camera:setCameraFlag(cc.CameraFlag.USER1)
        self._layer3D:addChild(self._camera)
    end


end

function Camera3DTestDemo:onExit()
    -- body
end

function Camera3DTestDemo:onNodeEvent(event)
    if event == "enter" then
    elseif event == "exit" then
    end
end

function Camera3DTestDemo:init()
    self:registerScriptHandler(self.onNodeEvent)
end

function Camera3DTestMain()
    cclog("Camera3DTestMain")
    local scene = cc.Scene:create()
    scene:addChild(Camera3DTestDemo.new())
    scene:addChild(CreateBackMenuItem())
    

    return scene
end
