local RADIAN_TO_ANGLE = 180 / math.pi

DragonBoneBullet = class("DragonBoneBullet")

function DragonBoneBullet:ctor(parent, armature, effect, radian, speed, position)
	self._speedX = math.cos(radian) * speed
	self._speedY = -math.sin(radian) * speed
	local thePos = parent:convertToNodeSpace(position)

	self._armature = armature
	self._armatureDisplay = self._armature:getDisplay()
	self._armatureDisplay:setPosition(thePos)
	self._armatureDisplay:setRotation(radian * RADIAN_TO_ANGLE)
	self._armature:getAnimation():play('idle')

	if effect then
		self._effect = effect
		local effectDisplay = self._effect:getDisplay()
		effectDisplay:setRotation(radian * RADIAN_TO_ANGLE)
		effectDisplay:setPosition(thePos)
		effectDisplay:setScaleX(1 + math.random())
		effectDisplay:setScaleY(1 + math.random() * 0.5)
		if math.random() < 0.5 then
			effectDisplay:setScaleY(effectDisplay:getScaleY() * -1)
		end

		self._effect:getAnimation():play('idle')
		ccdb.WorldClock.clock:add(self._effect)
		parent:addChild(effectDisplay)
	end

	ccdb.WorldClock.clock:add(self._armature)
	parent:addChild(self._armatureDisplay)
end

function DragonBoneBullet:update()
	local x, y = self._armatureDisplay:getPosition()
	self._armatureDisplay:setPosition(x + self._speedX, y + self._speedY)

	local worldPos = self._armatureDisplay:getParent():convertToWorldSpace(cc.p(x, y))
	local visibleRect = cc.Director:getInstance():getVisibleSize()
	local visibleOrigin = cc.Director:getInstance():getVisibleOrigin()
	if worldPos.x < visibleOrigin.x or worldPos.x >= visibleOrigin.x + visibleRect.width or
	   worldPos.y < visibleOrigin.y or worldPos.y >= visibleOrigin.y + visibleRect.height then

	   self:doClean()
	   return true
	end

	return false
end

function DragonBoneBullet:doClean()
	ccdb.WorldClock.clock:remove(self._armature)
	self._armatureDisplay:removeFromParent()
	self._armature:dispose()

	if self._effect then
		ccdb.WorldClock.clock:remove(self._effect)
		self._effect:getDisplay():removeFromParent()
		self._effect:dispose()
	end
end
