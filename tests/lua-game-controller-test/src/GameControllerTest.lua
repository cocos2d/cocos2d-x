
local ControllerHolder = class("ControllerHolder")

function ControllerHolder:ctor()
    self.controller  = nil
    self._holderNode = nil

    self._leftJoystick = nil
    self._rightJoystick = nil

    self._dpadLeft = nil
    self._dpadRight = nil
    self._dpadUp = nil
    self._dpadDown = nil

    self._buttonX = nil
    self._buttonY = nil
    self._buttonA = nil
    self._buttonB = nil

    self._buttonL1 = nil
    self._buttonR1 = nil
    self._buttonL2 = nil
    self._buttonR2 = nil

    self.deviceLabel = nil
    self.externalKeyLabel = nil
end


local GameControllerTest = class("GameControllerTest", function()
    return cc.Layer:create()
end)

function GameControllerTest:ctor()
    self:init()
end

function GameControllerTest:createControllerSprite(holder)

    holder._holderNode = cc.Node:create()
    holder._holderNode:setContentSize(cc.size(998,1000))

    local controllerBg1 = cc.Sprite:create("controller-1.png")
    controllerBg1:setPosition(cc.p(0, 0))
    controllerBg1:setAnchorPoint(cc.p(0, 0))
    holder._holderNode:addChild(controllerBg1)

    local controllerBg2 = cc.Sprite:create("controller-2.png")
    controllerBg2:setPosition(cc.p(499,1000))
    controllerBg2:setAnchorPoint(cc.p(0.5, 1.0))
    holder._holderNode:addChild(controllerBg2)

    holder._leftJoystick = cc.Sprite:create("joystick.png")
    holder._leftJoystick:setPosition(cc.p(238,460))
    holder._holderNode:addChild(holder._leftJoystick)

    holder._rightJoystick = cc.Sprite:create("joystick.png")
    holder._rightJoystick:setPosition(cc.p(606,293))
    holder._holderNode:addChild(holder._rightJoystick)

    holder._deviceLabel = cc.Label:createWithTTF("Disconnected","fonts/Marker Felt.ttf",36)
    holder._deviceLabel:setPosition(cc.p(499,650))
    holder._deviceLabel:setTextColor(cc.c4b(255,   0,   0, 255))
    holder._holderNode:addChild(holder._deviceLabel)

    holder._externalKeyLabel = cc.Label:createWithTTF("Key event","fonts/Marker Felt.ttf",36)
    holder._externalKeyLabel:setPosition(cc.p(499,500))
    holder._externalKeyLabel:setTextColor(cc.c4b(255,   0,   0, 255))
    holder._holderNode:addChild(holder._externalKeyLabel)
    -------------------------------------------------------------------
    local dPadTexture = cc.Director:getInstance():getTextureCache():addImage("dPad.png")

    local dPadCenter = cc.Sprite:createWithTexture(dPadTexture,cc.rect(60,60,68,68))
    dPadCenter:setPosition(cc.p(371,294))
    holder._holderNode:addChild(dPadCenter)

    holder._dpadLeft = cc.Sprite:createWithTexture(dPadTexture,cc.rect(0,60,60,60))
    holder._dpadLeft:setPosition(cc.p(371 - 64,296))
    holder._holderNode:addChild(holder._dpadLeft)

    holder._dpadRight = cc.Sprite:createWithTexture(dPadTexture,cc.rect(128,60,60,60))
    holder._dpadRight:setPosition(cc.p(371 + 64,296))
    holder._holderNode:addChild(holder._dpadRight)

    holder._dpadUp = cc.Sprite:createWithTexture(dPadTexture,cc.rect(60,0,60,60))
    holder._dpadUp:setPosition(cc.p(369,294 + 64))
    holder._holderNode:addChild(holder._dpadUp)

    holder._dpadDown = cc.Sprite:createWithTexture(dPadTexture,cc.rect(60,128,60,60))
    holder._dpadDown:setPosition(cc.p(369,294 - 64))
    holder._holderNode:addChild(holder._dpadDown)
    -------------------------------------------------------------------
    holder._buttonL1 = cc.Sprite:create("L1.png")
    holder._buttonL1:setPosition(cc.p(290,792))
    holder._holderNode:addChild(holder._buttonL1)

    holder._buttonR1 = cc.Sprite:create("R1.png")
    holder._buttonR1:setPosition(cc.p(998 - 290,792))
    holder._holderNode:addChild(holder._buttonR1)

    local buttonL2 = cc.Sprite:create("L2.png")
    buttonL2:setPosition(cc.p(220,910))
    holder._holderNode:addChild(buttonL2)

    local buttonR2 = cc.Sprite:create("R2.png")
    buttonR2:setPosition(cc.p(998-220,910))
    holder._holderNode:addChild(buttonR2)

    holder._buttonL2 = cc.Sprite:create("L2.png")
    holder._buttonL2:setOpacity(0)
    holder._buttonL2:setColor(cc.c3b(255,0,0))
    holder._buttonL2:setPosition(cc.p(220,910))
    holder._holderNode:addChild(holder._buttonL2)

    holder._buttonR2 = cc.Sprite:create("R2.png")
    holder._buttonR2:setOpacity(0)
    holder._buttonR2:setColor(cc.c3b(255,0,0))
    holder._buttonR2:setPosition(cc.p(998-220,910))
    holder._holderNode:addChild(holder._buttonR2)
    -------------------------------------------------------------------
    holder._buttonX = cc.Sprite:create("X.png")
    holder._buttonX:setPosition(cc.p(750 - 70,460))
    holder._holderNode:addChild(holder._buttonX)

    holder._buttonY = cc.Sprite:create("Y.png")
    holder._buttonY:setPosition(cc.p(750,460 + 70))
    holder._holderNode:addChild(holder._buttonY)

    holder._buttonA = cc.Sprite:create("A.png")
    holder._buttonA:setPosition(cc.p(750,460 - 70))
    holder._holderNode:addChild(holder._buttonA)

    holder._buttonB = cc.Sprite:create("B.png")
    holder._buttonB:setPosition(cc.p(750 + 70,460))
    holder._holderNode:addChild(holder._buttonB)
end

function GameControllerTest:registerControllerListener()

    local function resetControllerHolderState(holder)
        holder._buttonA:setColor(cc.c3b(255, 255, 255))
        holder._buttonB:setColor(cc.c3b(255, 255, 255))
        holder._buttonX:setColor(cc.c3b(255, 255, 255))
        holder._buttonY:setColor(cc.c3b(255, 255, 255))
        holder._dpadUp:setColor(cc.c3b(255, 255, 255))
        holder._dpadDown:setColor(cc.c3b(255, 255, 255))
        holder._dpadLeft:setColor(cc.c3b(255, 255, 255))
        holder._dpadRight:setColor(cc.c3b(255, 255, 255))
        holder._buttonL1:setColor(cc.c3b(255, 255, 255))
        holder._buttonR1:setColor(cc.c3b(255, 255, 255))

        holder._leftJoystick:setPosition(cc.p(238,460))
        holder._rightJoystick:setPosition(cc.p(606,293))
        holder._deviceLabel:setString("Disconnected")
    end

    local function onConnectController(controller, event)
        if controller == nil or controller == self._firstHolder.controller or controller == self._secondHolder.controller then
            return
        end

        local targetPlatform = cc.Application:getInstance():getTargetPlatform()
        if targetPlatform == cc.PLATFORM_OS_ANDROID then
            --do sth
            -- //receive back key
            -- controller:receiveExternalKeyEvent(4,true)
            -- //receive menu key
            -- controller:receiveExternalKeyEvent(82,true)
        end

        local deviceInfo = string.format("%s id:%d", controller:getDeviceName(), controller:getDeviceId())
        print(deviceInfo)


        if self._firstHolder.controller == nil and self._secondHolder.controller == nil then
            if self._firstHolder._holderNode then
                self._firstHolder.controller = controller
                self._firstHolder._deviceLabel:setString(deviceInfo)
            else
                self._secondHolder.controller = controller
                self._secondHolder._deviceLabel:setString(deviceInfo)
            end
        elseif self._secondHolder.controller == nil then
            self._secondHolder.controller = controller
            if self._secondHolder._holderNode == nil then
                createControllerSprite(self._secondHolder)

                self._firstHolder._holderNode:runAction(cc.ScaleTo:create(0.3, 0.5, 0.5))
                self._firstHolder._holderNode:runAction(cc.MoveTo:create(0.3,cc.p(self._visibleQuarterX, self_visibleCentreY)))

                self._secondHolder._holderNode:setAnchorPoint(cc.p(0.5, 0.5))
                self._secondHolder._holderNode:setScale(0.1)
                self._secondHolder._holderNode:runAction(cc.ScaleTo:create(0.3, 0.5, 0.5))
                self._secondHolder._holderNode:setPosition(cc.p(self._visibleThreeQuarterX, self._visibleCentreY))
                self:addChild(self._secondHolder._holderNode)
            end

            self._secondHolder._deviceLabel:setString(deviceInfo)
        else
            self._firstHolder.controller = controller
            if self._firstHolder._holderNode == nil then
                createControllerSprite(self._firstHolder)

                self._secondHolder._holderNode:runAction(cc.ScaleTo:create(0.3, 0.5, 0.5))
                self._secondHolder._holderNode:runAction(cc.MoveTo:create(0.3, cc.p(self._visibleQuarterX, self._visibleCentreY)))

                self._firstHolder._holderNode:setAnchorPoint(cc.p(0.5, 0.5))
                self._firstHolder._holderNode:setScale(0.1)
                self._firstHolder._holderNode:runAction(cc.ScaleTo:create(0.3, 0.5,0.5))
                self._firstHolder._holderNode:setPosition(cc.p(self._visibleThreeQuarterX, self._visibleCentreY))
                self:addChild(self._firstHolder._holderNode)
            end

            self._firstHolder._deviceLabel:setString(deviceInfo)
        end
    end

    local function onDisconnectedController(controller, event)
        print("onDisconnectedController:",controller:getDeviceId())
        if self._firstHolder.controller == controller then
            self._firstHolder.controller = nil

            if self._secondHolder.controller ~= nil then
                self._firstHolder._holderNode:runAction(cc.MoveBy:create(0.3,cc.p(0,self._visibleSize.height)))

                self._secondHolder._holderNode:runAction(cc.MoveTo:create(0.3, cc.p(self._visibleCentreX, self._visibleCentreY) ))
                self._secondHolder._holderNode:runAction(cc.ScaleTo:create(0.3, 1.0,1.0))
            else
                resetControllerHolderState(self._firstHolder)
            end
        elseif self._secondHolder.controller == controller then
            self._secondHolder.controller = nil

            if self._firstHolder.controller ~= nil then
                self._secondHolder._holderNode:runAction(cc.MoveBy:create(0.3, cc.p(0, self._visibleSize.height)))

                self._firstHolder._holderNode:runAction(cc.MoveTo:create(0.3, cc.p(self._visibleCentreX, self._visibleCentreY)))
                self._firstHolder._holderNode:runAction(cc.ScaleTo:create(0.3, 1.0,1.0))
            else
                resetControllerHolderState(self._secondHolder)
            end
        end
    end

    local function showButtonState(controller, keyCode, isPressed)
        onConnectController(controller, nil)
        local holder = nil

        if controller == self._firstHolder.controller then
            holder = self._firstHolder
        elseif controller == self._secondHolder.controller then
            holder = self._secondHolder
        else
            return
        end

        if isPressed then
            if keyCode == cc.ControllerKey.BUTTON_A then
                holder._buttonA:setColor(cc.c3b(250,103,93))
            elseif keyCode == cc.ControllerKey.BUTTON_B then
                holder._buttonB:setColor(cc.c3b(92,214,183))
            elseif keyCode == cc.ControllerKey.BUTTON_X then
                holder._buttonX:setColor(cc.c3b(96,113,192))
            elseif keyCode == cc.ControllerKey.BUTTON_Y then
                holder._buttonY:setColor(cc.c3b(199,222,118))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_UP then
                holder._dpadUp:setColor(cc.c3b(0,115,158))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_DOWN then
                holder._dpadDown:setColor(cc.c3b(0,115,158))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_LEFT then
                holder._dpadLeft:setColor(cc.c3b(170,216,0))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_RIGHT then
                holder._dpadRight:setColor(cc.c3b(170,216,0))
            elseif keyCode == cc.ControllerKey.BUTTON_LEFT_SHOULDER then
                holder._buttonL1:setColor(cc.c3b(19,231,238))
            elseif keyCode == cc.ControllerKey.BUTTON_RIGHT_SHOULDER then
                holder._buttonR1:setColor(cc.c3b(19,231,238))
            elseif keyCode == cc.ControllerKey.BUTTON_LEFT_THUMBSTICK then
                holder._leftJoystick:setColor(cc.c3b(19,231,238))
            elseif keyCode == cc.ControllerKey.BUTTON_RIGHT_THUMBSTICK then
                holder._rightJoystick:setColor(cc.c3b(19,231,238))
            else
                local ketStatus = string.format("Key Down:%d",keyCode)
                holder._externalKeyLabel:setString(ketStatus)
            end
        else
            if keyCode == cc.ControllerKey.BUTTON_A then
                holder._buttonA:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_B then
                holder._buttonB:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_X then
                holder._buttonX:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_Y then
                holder._buttonY:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_UP then
                holder._dpadUp:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_DOWN then
                holder._dpadDown:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_LEFT then
                holder._dpadLeft:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_DPAD_RIGHT then
                holder._dpadRight:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_LEFT_SHOULDER then
                holder._buttonL1:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_RIGHT_SHOULDER then
                holder._buttonR1:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_LEFT_THUMBSTICK then
                holder._leftJoystick:setColor(cc.c3b(250,255,255))
            elseif keyCode == cc.ControllerKey.BUTTON_RIGHT_THUMBSTICK then
                holder._rightJoystick:setColor(cc.c3b(250,255,255))
            else
                local ketStatus = string.format("Key Up:%d",keyCode)
                holder._externalKeyLabel:setString(ketStatus)
            end

        end
    end

    local function onKeyDown(controller, keyCode, event)
        showButtonState(controller, keyCode, true)
    end

    local function onKeyUp(controller, keyCode, event)
        showButtonState(controller, keyCode, false)
    end

    local function onAxisEvent(controller, keyCode, event)
        local holder = nil

        if controller == self._firstHolder.controller then
            holder = self._firstHolder
        elseif controller == self._secondHolder.controller then
            holder = self._secondHolder
        else
            return
        end

        local ketStatus = controller:getKeyStatus(keyCode)
        if keyCode == cc.ControllerKey.JOYSTICK_LEFT_X then
            holder._leftJoystick:setPositionX(238 + ketStatus.value * 24)
        elseif keyCode == cc.ControllerKey.JOYSTICK_LEFT_Y then
            holder._leftJoystick:setPositionY(460 - ketStatus.value * 24)
        elseif keyCode == cc.ControllerKey.JOYSTICK_RIGHT_X then
            holder._rightJoystick:setPositionX(606 + ketStatus.value * 24)
        elseif keyCode == cc.ControllerKey.JOYSTICK_RIGHT_Y then
            holder._rightJoystick:setPositionY(293 - ketStatus.value * 24)
        elseif keyCode == cc.ControllerKey.AXIS_LEFT_TRIGGER then
            holder._buttonL2:setOpacity(200 * controller:getKeyStatus(keyCode).value)
        elseif keyCode == cc.ControllerKey.AXIS_RIGHT_TRIGGER then
            holder._buttonR2:setOpacity(200 * controller:getKeyStatus(keyCode).value)
        else
            --do nothing
        end
    end

    -- body
    self._listener = cc.EventListenerController:create()
    self._listener:registerScriptHandler(onConnectController, cc.Handler.EVENT_CONTROLLER_CONNECTED)
    self._listener:registerScriptHandler(onDisconnectedController, cc.Handler.EVENT_CONTROLLER_DISCONNECTED)

    self._listener:registerScriptHandler(onKeyDown, cc.Handler.EVENT_CONTROLLER_KEYDOWN)
    self._listener:registerScriptHandler(onKeyUp, cc.Handler.EVENT_CONTROLLER_KEYUP)
    self._listener:registerScriptHandler(onAxisEvent, cc.Handler.EVENT_CONTROLLER_AXIS)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(self._listener, self)

    cc.Controller:startDiscoveryController()
end



function GameControllerTest:init()
    self._currControllerCount = 0
    self._visibleSize   = cc.Director:getInstance():getVisibleSize()
    self._visibleOrigin = cc.Director:getInstance():getVisibleOrigin()

    local tmpPos = cc.p(self._visibleSize.width / 2 + self._visibleOrigin.x, self._visibleSize.height / 2 + self._visibleOrigin.y)

    self._visibleCentreX = self._visibleOrigin.x + self._visibleSize.width / 2
    self._visibleCentreY = self._visibleOrigin.y + self._visibleSize.height / 2
    self._visibleQuarterX = self._visibleOrigin.x + self._visibleSize.width / 4
    self._visibleThreeQuarterX = self._visibleOrigin.x + self._visibleSize.width * 0.75

    self._firstHolder   = ControllerHolder.new()
    self._secondHolder = ControllerHolder.new()
    self._firstHolder.controller = nil
    self._secondHolder.controller = nil

    self:createControllerSprite(self._firstHolder)
    self._firstHolder._holderNode:setAnchorPoint(cc.p(0.5, 0.5))
    self._firstHolder._holderNode:setPosition(tmpPos)
    self:addChild(self._firstHolder._holderNode)

    self:registerControllerListener()

    -- local function menuCloseCallback(tag, sender)
        
    -- end
    -- local closeItem = cc.MenuItemImage:create("CloseNormal.png", "CloseSelected.png")
    -- closeItem:setPosition(cc.p(self._visibleOrigin.x + self._visibleSize.width - closeItem:getContentSize().width / 2, self._visibleOrigin.y + self._visibleSize.height - closeItem:getContentSize().height / 2))

    -- local menu = cc.Menu:create()
    -- menu:addChild(closeItem)


end


return GameControllerTest