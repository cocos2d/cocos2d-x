require('utils')
require('DragonBoneBullet')

local NORMAL_ANIMATION_GROUP = 'normal'
local AIM_ANIMATION_GROUP = 'aim'
local ATTACK_ANIMATION_GROUP = 'attack'
local JUMP_SPEED = -20
local NORMALIZE_MOVE_SPEED = 3.6
local MAX_MOVE_SPEED_FRONT = NORMALIZE_MOVE_SPEED * 1.4
local MAX_MOVE_SPEED_BACK = NORMALIZE_MOVE_SPEED * 1

local WEAPON_R_LIST = {'weapon_1502b_r', 'weapon_1005', 'weapon_1005b', 'weapon_1005c', 'weapon_1005d', 'weapon_1005e'}
local WEAPON_L_LIST = {'weapon_1502b_l', 'weapon_1005', 'weapon_1005b', 'weapon_1005c', 'weapon_1005d'}

local GROUND = 120
local G = -0.6

local TOUCH_EVENT_BEGAN = 0
local TOUCH_EVENT_ENDED = 2

local function generateAnimationEventHandler(target)
    return function(event)
               target:animationEventHandler(event)
           end
end

local function generateFrameEventHandler(target)
    return function(event)
               target:frameEventHandler(event)
           end
end

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
    self._weaponRIndex = 1
    self._weaponLIndex = 1
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
    self._bullets = {}

    self._armatureDisplay = findChild(scene, 'DragonBoneNode', 'ccdb.CCArmatureDisplay')
    self._armature = self._armatureDisplay:getArmature()

    self._armatureDisplay:addEvent(ccdb.EventObject.FADE_IN_COMPLETE, generateAnimationEventHandler(self))
    self._armatureDisplay:addEvent(ccdb.EventObject.FADE_OUT_COMPLETE, generateAnimationEventHandler(self))

    self._armature:getSlot('effects_1').displayController = NORMAL_ANIMATION_GROUP
    self._armature:getSlot('effects_2').displayController = NORMAL_ANIMATION_GROUP

    self._weaponR = self._armature:getSlot('weapon_r'):getChildArmature()
    self._weaponL = self._armature:getSlot('weapon_l'):getChildArmature()

    self._weaponR:getDisplay():addEvent(ccdb.EventObject.FRAME_EVENT, generateFrameEventHandler(self))
    self._weaponL:getDisplay():addEvent(ccdb.EventObject.FRAME_EVENT, generateFrameEventHandler(self))

    self:updateAnimation()

    -- up
    local button = findChild(scene, 'up', 'ccui.Button')
    button:addClickEventListener(function ()
    	self:jump()
    end)

    -- down
    button = findChild(scene, 'down', 'ccui.Button')
    button:addTouchEventListener(function (sender, type)
    	if type == TOUCH_EVENT_BEGAN then
    		self:squat(true)
    	elseif type == TOUCH_EVENT_ENDED then
    		self:squat(false)
    	end
    end)

    -- left
    button = findChild(scene, 'left', 'ccui.Button')
    button:addTouchEventListener(function (sender, type)
    	if type == TOUCH_EVENT_BEGAN then
    		self._left = true
    	elseif type == TOUCH_EVENT_ENDED then
    		self._left = false
    	end

    	self:updateMove(-1)
    end)

    -- right
    button = findChild(scene, 'right', 'ccui.Button')
    button:addTouchEventListener(function (sender, type)
    	if type == TOUCH_EVENT_BEGAN then
    		self._right = true
    	elseif type == TOUCH_EVENT_ENDED then
    		self._right = false
    	end

    	self:updateMove(-1)
    end)

    -- change weapon L
    button = findChild(scene, 'ChangeWeaponL', 'ccui.Button')
    button:addClickEventListener(function ()
    	self:switchWeaponL()
    end)

    -- change weapon R
    button = findChild(scene, 'ChangeWeaponR', 'ccui.Button')
    button:addClickEventListener(function ()
    	self:switchWeaponR()
    end)

    local scheduler = cc.Director:getInstance():getScheduler()
    self.scheduleEntry = scheduler:scheduleScriptFunc(function (dt)
        self:updatePosition()
        self:updateAnim()
        self:updateAttack()
        self:enterFrameHandler(dt)
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
        self:attack(true)
        return true
    end

    function onTouchMoved(touches, event)
        local touchloc = touches[1]:getLocation()
        self:aim(touchloc.x, touchloc.y)
    end

    function onTouchEnded(touches, event)
        self:attack(false)
    end

	local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCHES_BEGAN)
    listener:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCHES_MOVED)
    listener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self._armatureDisplay) 
end

function DragonBonesHandler:onExit()
	cc.Director:getInstance():getEventDispatcher():removeEventListenersForTarget(self._armatureDisplay)

    local scheduler = cc.Director:getInstance():getScheduler()
    scheduler:unscheduleScriptEntry(self.scheduleEntry)
end

function DragonBonesHandler:animationEventHandler(event)
	if event.type == ccdb.EventObject.FADE_IN_COMPLETE then
		if event.animationState:getName() == 'jump_1' then
			self._isJumpingB = true
			self._speedY = self._speedY - JUMP_SPEED
			self._armature:getAnimation():fadeIn('jump_2', -1, -1, 0, NORMAL_ANIMATION_GROUP)
		elseif event.animationState:getName() == 'jump_4' then
			self:updateAnimation()
		end
	elseif event.type == ccdb.EventObject.FADE_OUT_COMPLETE then
        if event.animationState:getName() == 'attack_01' then
            self._isAttackingB = false
            self._attackState = nil
        end
	end
end

function DragonBonesHandler:updateAnimation()
	if self._isJumpingA then
        return
    end

    if self._isSquating then
        self._speedX = 0
        self._armature:getAnimation():fadeIn('squat', -1, -1, 0, NORMAL_ANIMATION_GROUP)
        self._walkState = nil
        return;
    end

    if self._moveDir == 0 then
        self._speedX = 0
        self._armature:getAnimation():fadeIn('idle', -1, -1, 0, NORMAL_ANIMATION_GROUP)
        self._walkState = nil
    else
        if not self._walkState then
            self._walkState = self._armature:getAnimation():fadeIn('walk', -1, -1, 0, NORMAL_ANIMATION_GROUP)
        end

        if self._moveDir * self._faceDir > 0 then
            self._walkState.timeScale = MAX_MOVE_SPEED_FRONT / NORMALIZE_MOVE_SPEED
            self._speedX = MAX_MOVE_SPEED_FRONT * self._faceDir
        else
            self._walkState.timeScale = -MAX_MOVE_SPEED_BACK / NORMALIZE_MOVE_SPEED
            self._speedX = -MAX_MOVE_SPEED_BACK * self._faceDir
        end
    end
end

function DragonBonesHandler:frameEventHandler(event)
	if event.animationState:getName() == 'fire_01' then
        local firePointBone = event.armature:getBone('firePoint')
        local localPoint = cc.p(firePointBone.global.x, -firePointBone.global.y)

        local display = event.armature:getDisplay()
        local globalPoint = display:convertToWorldSpace(localPoint)

        self:fire(globalPoint)
    end
end

function DragonBonesHandler:jump()
	if self._isJumpingA then
        return
    end

    self._isJumpingA = true
    self._armature:getAnimation():fadeIn('jump_1', -1, -1, 0, NORMAL_ANIMATION_GROUP)
    self._walkState = nil
end

function DragonBonesHandler:squat(isSquating)
	if isSquating == self._isSquating then
        return
    end

    self._isSquating = isSquating
    self:updateAnimation()
end

function DragonBonesHandler:updateMove(dir)
	if self._left and self._right then
        self:move(dir)
    elseif self._left then
        self:move(-1)
    elseif self._right then
        self:move(1)
    else
        self:move(0)
    end
end

function DragonBonesHandler:move(dir)
	if self._moveDir == dir then
        return
    end

    self._moveDir = dir
    self:updateAnimation()
end

function DragonBonesHandler:aim(x, y)
	if self._aimDir == 0 then
        self._aimDir = 10
    end

    self._target = self._armatureDisplay:getParent():convertToNodeSpace(cc.p(x, y))
end

function DragonBonesHandler:attack(isAttacking)
	if self._isAttackingA == isAttacking then
        return
    end

    self._isAttackingA = isAttacking
end

function DragonBonesHandler:updatePosition()
	if self._speedX ~= 0 then
        local armatureDisplayPosX, _ = self._armatureDisplay:getPosition()
        self._armatureDisplay:setPositionX(armatureDisplayPosX + self._speedX)
        local visibleRect = cc.Director:getInstance():getVisibleSize()
        local visibleOrigin = cc.Director:getInstance():getVisibleOrigin()
        local minX = visibleOrigin.x + 10
        local maxX = visibleRect.width + visibleOrigin.x
        if armatureDisplayPosX < minX then
            self._armatureDisplay:setPositionX(minx)
        elseif armatureDisplayPosX > maxX then
            self._armatureDisplay:setPositionX(maxX)
        end
    end

    if self._speedY ~= 0 then
        if self._speedY > 5 and (self._speedY + G) <= 5 then
            self._armature:getAnimation():fadeIn('jump_3', -1, -1, 0, NORMAL_ANIMATION_GROUP)
        end

        self._speedY = self._speedY + G;

        local _, armatureDisplayPosY = self._armatureDisplay:getPosition()
        self._armatureDisplay:setPositionY(armatureDisplayPosY + self._speedY)
        if armatureDisplayPosY < GROUND then
            self._armatureDisplay:setPositionY(GROUND)
            self._isJumpingA = false
            self._isJumpingB = false
            self._speedX = 0
            self._speedY = 0
            self._armature:getAnimation():fadeIn('jump_4', -1, -1, 0, NORMAL_ANIMATION_GROUP)
            if self._isSquating or self._moveDir then
                self:updateAnimation()
            end
        end
    end
end

function DragonBonesHandler:updateAnim()
	if self._aimDir == 0 then
        return
    end

    local x, y = self._armatureDisplay:getPosition()
    if self._target.x > x then
        self._faceDir = 1
    else
        self._faceDir = -1
    end
    if self._armatureDisplay:getScaleX() * self._faceDir < 0 then
        self._armatureDisplay:setScaleX(self._armatureDisplay:getScaleX() * -1)
        if self._moveDir then
            self:updateAnimation()
        end
    end

    local animOffsetY = self._armature:getBone('chest').global.y * self._armatureDisplay:getScaleY();
    if self._faceDir > 0 then
        self._animRadian = math.atan2(-(self._target.y - y + animOffsetY), self._target.x - x)
    else
        self._animRadian = math.pi - math.atan2(-(self._target.y - y + animOffsetY), self._target.x - x)
        if self._animRadian > math.pi then
            self._animRadian = self._animRadian - math.pi * 2
        end
    end

    local aimDir = 0
    if self._animRadian > 0 then
        aimDir = -1
    else
        aimDir = 1
    end

    if self._aimDir ~= aimDir then
        self._aimDir = aimDir

        if self._aimDir >= 0 then
            self._animState = self._armature:getAnimation():fadeIn('aimUp', 0, 1, 0, AIM_ANIMATION_GROUP, ccdb.AnimationFadeOutMode.SameGroup)
        else
            self._animState = self._armature:getAnimation():fadeIn('aimDown', 0, 1, 0, AIM_ANIMATION_GROUP, ccdb.AnimationFadeOutMode.SameGroup)
        end
    end

    self._animState.weight = math.abs(self._animRadian / math.pi * 2)
    self._armature:invalidUpdate()
end

function DragonBonesHandler:updateAttack()
	if not self._isAttackingA or self._isAttackingB then
        return
    end

    self._isAttackingB = true

    self._attackState = self._armature:getAnimation():fadeIn('attack_01', -1, -1, 0, ATTACK_ANIMATION_GROUP, ccdb.AnimationFadeOutMode.SameGroup)

    self._attackState.autoFadeOutTime = self._attackState.fadeTotalTime;
    self._attackState:addBoneMask('pelvis')
end

function DragonBonesHandler:enterFrameHandler(dt)
	for i = #self._bullets, 1, -1 do
        local bullet = self._bullets[i]
        if bullet:update() then
            table.remove(self._bullets, i)
        end
    end

    ccdb.WorldClock.clock:advanceTime(dt)
end

function DragonBonesHandler:switchWeaponL()
	self._weaponL:getDisplay():removeEvent(ccdb.EventObject.FRAME_EVENT)

    self._weaponLIndex = (self._weaponLIndex + 1) % (#WEAPON_L_LIST + 1)
    if self._weaponLIndex == 0 then
        self._weaponLIndex = 1
    end
    local newWeaponName = WEAPON_L_LIST[self._weaponLIndex]
    self._weaponL = ccdb.CCFactory.factory:buildArmature(newWeaponName)
    self._armature:getSlot('weapon_l'):setChildArmature(self._weaponL)

    self._weaponL:getDisplay():addEvent(ccdb.EventObject.FRAME_EVENT, generateFrameEventHandler(self))
end

function DragonBonesHandler:switchWeaponR()
    self._weaponR:getDisplay():removeEvent(ccdb.EventObject.FRAME_EVENT)

    self._weaponRIndex = (self._weaponRIndex + 1) % (#WEAPON_R_LIST + 1)
    if self._weaponRIndex == 0 then
        self._weaponRIndex = 1
    end
    local newWeaponName = WEAPON_R_LIST[self._weaponRIndex]
    self._weaponR = ccdb.CCFactory.factory:buildArmature(newWeaponName)
    self._armature:getSlot('weapon_r'):setChildArmature(self._weaponR)

    self._weaponR:getDisplay():addEvent(ccdb.EventObject.FRAME_EVENT, generateFrameEventHandler(self))
end

function DragonBonesHandler:fire(pos)
	local firePoint = pos
    firePoint.x = firePoint.x + math.random() * 2 - 1
    firePoint.y = firePoint.y + math.random() * 2 - 1

    local armature = ccdb.CCFactory.factory:buildArmature('bullet_01')
    local effect = ccdb.CCFactory.factory:buildArmature('fireEffect_01')

    local radian = nil
    if self._faceDir < 0 then
        radian = math.pi - self._animRadian
    else
        radian = self._animRadian
    end

    local bullet = DragonBoneBullet.new(self:getParent(), armature, effect, radian + math.random() * 0.02 - 0.01, 40, firePoint)
    self:addBullet(bullet)
end

function DragonBonesHandler:addBullet(bullet)
	table.insert(self._bullets, bullet)
end
