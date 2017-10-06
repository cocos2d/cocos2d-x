require('utils')

local JUMP_SPEED = -20
local NORMAL_ANIMATION_GROUP = 'normal'

DragonBonesHandler = class("DragonBonesHandler", function ()
    local node = cc.Node:create()
    return node
end)

function DragonBonesHandler:ctor(scene)
    -- body
    self._scene = scene
    self._left = false
    self._right = false
    self._isJumpingA = false
    self._isJumpingB = false
    self._isAttackingA = false
    self._isAttackingB = false
    self._isSquating = false
    self._weaponRIndex = 0
    self._weaponLIndex = 0
    self._faceDir = 1
    self._aimDir = 0
    self._moveDir = 0
    self._animRadian = 0
    self._speedX = 0
    self._speedY = 0
    self._animState = nil
    self._walkState = nil
    self._attackState = nil
    self._target = nil

    self._armatureDisplay = findChild(scene, 'DragonBoneNode', 'ccdb.CCArmatureDisplay')
    self._armature = self._armatureDisplay:getArmature()


    self._armatureDisplay:addEvent(ccdb.EventObject.FADE_IN_COMPLETE, self.animationEventHandler)
    self._armatureDisplay:addEvent(ccdb.EventObject.FADE_OUT_COMPLETE, self.animationEventHandler)

    self._armature:getSlot('effects_1').displayController = NORMAL_ANIMATION_GROUP
    self._armature:getSlot('effects_2').displayController = NORMAL_ANIMATION_GROUP

    self._weaponR = self._armature:getSlot('weapon_r'):getChildArmature()
    self._weaponL = self._armature:getSlot('weapon_l'):getChildArmature()

    self._weaponR:getDisplay():addEvent(ccdb.EventObject.FRAME_EVENT, self.frameEventHandler)
    self._weaponL:getDisplay():addEvent(ccdb.EventObject.FRAME_EVENT, self.frameEventHandler)

    self.updateAnimation()

    -- up
    local button = findChild(scene, 'up', 'ccui.Button')
    button:addClickEventListener(function ()
    	self.jump()
    end)

    -- down
    button = findChild(scene, 'down', 'ccui.Button')
    button:addTouchEventListener(function (sender, type)
    	if type == ccui.TouchEventType.begin then
    		self.squat(true)
    	elseif type == ccui.TouchEventType.ended then
    		self.squat(false)
    	end
    end)

    -- left
    button = findChild(scene, 'left', 'ccui.Button')
    button:addTouchEventListener(function (sender, type)
    	if type == ccui.TouchEventType.begin then
    		self._left = true
    	elseif type == ccui.TouchEventType.ended then
    		self._left = false
    	end

    	self.updateMove(-1)
    end)

    -- right
    button = findChild(scene, 'right', 'ccui.Button')
    button:addTouchEventListener(function (sender, type)
    	if type == ccui.TouchEventType.begin then
    		self._right = true
    	elseif type == ccui.TouchEventType.ended then
    		self._right = false
    	end

    	self.updateMove(-1)
    end)

    -- change weapon L
    button = findChild(scene, 'ChangeWeaponL', 'ccui.Button')
    button:addClickEventListener(function ()
    	self.switchWeaponL()
    end)

    -- change weapon R
    button = findChild(scene, 'ChangeWeaponR', 'ccui.Button')
    button:addClickEventListener(function ()
    	self.switchWeaponR()
    end)

    local scheduler = cc.Director:getInstance():getScheduler()
    scheduler:scheduleScriptFunc(function (dt)
        self.updatePosition()
        self.updateAnim()
        self.updateAttack()
        self.enterFrameHandler(dt)
    end, 0, false)

    self:registerScriptHandler(function(tag)
        if "enter" == tag then
            self:onEnter()
        elseif "exit" == tag then
        	self:onExit()
        end
    end)
end

function DragonBonesHandler:onEnter()

    function onTouchBegan(touches, event)
        self.attack()
        return true
    end

    function onTouchMoved(touches, event)
        local touchloc = touches[1]:getLocation()
        self.aim(touchloc.x, touchloc.y)
    end

    function onTouchEnded(touches, event)
        self.attack(false)
    end

	local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCHES_BEGAN)
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCHES_MOVED)
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self._armatureDisplay) 
end

function DragonBonesHandler:onExit()
	cc.Director:getInstance():getEventDispatcher():removeEventListenersForTarget(self._armatureDisplay)
end

function DragonBonesHandler:animationEventHandler(event)
	print('callback.........')
	if event.type == ccdb.EventObject.FADE_IN_COMPLETE then
		if event.animationState:getName() == 'jump_1' then
			self._isJumpingB = true
			self._speedY = self._speedY - JUMP_SPEED
			self._armature:getAnimation():fadeIn('jump_2', -1, -1, 0, NORMAL_ANIMATION_GROUP)
		elseif event.animationState:getName() == 'jump_4' then
			self.updateAnimation()
		end
	elseif event.type == ccdb.EventObject.FADE_OUT_COMPLETE then
	end
end

function DragonBonesHandler:updateAnimation()
	if self._isJumpingA then
        return
    end

    if self._isSquating then
        self._speedX = 0
        --TODO: add binding for getAnimation
        self._armature:getAnimation():fadeIn('squat', -1, -1, 0, NORMAL_ANIMATION_GROUP)
        self._walkState = nil
        return;
    end

    if self._moveDir == 0 then
    else
    end
end

function DragonBonesHandler:frameEventHandler(event)
	-- body
end

function DragonBonesHandler:updateAnimation()
	-- body
end

function DragonBonesHandler:jump()
	-- body
end

function DragonBonesHandler:squat(isSquating)
	-- body
end

function DragonBonesHandler:updateMove(dir)
	-- body
end

function DragonBonesHandler:move(dir)
	-- body
end

function DragonBonesHandler:aim(x, y)
	-- body
end

function DragonBonesHandler:attack(isAttacking)
	-- body
end

function DragonBonesHandler:updatePosition()
	-- body
end

function DragonBonesHandler:updateAnim()
	-- body
end

function DragonBonesHandler:updateAttack()
	-- body
end

function DragonBonesHandler:enterFrameHandler(dt)
	-- body
end

function DragonBonesHandler:switchWeaponL()
	-- body
end

function DragonBonesHandler:switchWeaponR()
	-- body

end

function DragonBonesHandler:fire(pos)
	-- body
end

function DragonBonesHandler:addBullet(bullet)
	-- body
end
