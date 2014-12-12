
local MapConstants = require("app.map.MapConstants")
local math2d       = require("math2d")

local BehaviorBase = require("app.map.behaviors.BehaviorBase")
local MovableBehavior = class("MovableBehavior", BehaviorBase)

MovableBehavior.MOVING_STATE_STOPPED   = 0
MovableBehavior.MOVING_STATE_SPEEDUP   = 1
MovableBehavior.MOVING_STATE_SPEEDDOWN = 2
MovableBehavior.MOVING_STATE_FULLSPEED = 3

MovableBehavior.SPEED_SCALE = 1.0 / 300

function MovableBehavior:ctor()
    MovableBehavior.super.ctor(self, "MovableBehavior", nil, 1)
end

function MovableBehavior:setNextPosition(object)
    local map = object.map_
    if not object.nextPathId_ then
        object.nextPathId_        = object.bindingPathId_
        object.nextPointIndex_    = object.bindingPointIndex_
        object.nextMovingForward_ = object.bindingMovingForward_
    end

    object.currentPathId_     = object.nextPathId_
    object.currentPointIndex_ = object.nextPointIndex_

    local nextPath,
          nextPointIndex,
          nextMovingForward = map:getNextPointIndexOnPath(object.currentPathId_,
                                                          object.currentPointIndex_,
                                                          object.nextMovingForward_,
                                                          true)

    object.nextPathId_           = nextPath:getId()
    object.nextPointIndex_       = nextPointIndex
    object.nextMovingForward_    = nextMovingForward
    object.nextX_, object.nextY_ = nextPath:getPoint(nextPointIndex)

    object.nextRadians_ = math2d.radians4point(object.x_, object.y_, object.nextX_, object.nextY_)
    object.nextDist_    = math2d.dist(object.x_, object.y_, object.nextX_, object.nextY_)
    object.currentDist_ = 0
end

function MovableBehavior:bind(object)
    object.movingLocked_         = 0
    object.bindingPathId_        = object.state_.bindingPathId
    object.bindingPointIndex_    = object.state_.bindingPointIndex
    object.bindingMovingForward_ = object.state_.bindingMovingForward
    if type(object.bindingMovingForward_) ~= "boolean" then
        object.bindingMovingForward_ = true
    end

    object.nextPathId_           = nil
    object.nextPointIndex_       = nil
    object.nextMovingForward_    = nil
    object.nextX_, object.nextY_ = nil
    object.nextRadians_          = nil
    object.nextDist_             = 0
    object.currentDist_          = 0

    local function isBinding(objec)
        return object.bindingPathId_ ~= nil
    end
    object:bindMethod(self, "isBinding", isBinding)

    local function getBindingPathId(object)
        return object.bindingPathId_
    end
    object:bindMethod(self, "getBindingPathId", getBindingPathId)

    local function getBindingPointIndex(object)
        return object.bindingPointIndex_
    end
    object:bindMethod(self, "getBindingPointIndex", getBindingPointIndex)

    local function getCurrentPathId(object)
        return object.currentPathId_
    end
    object:bindMethod(self, "getCurrentPathId", getCurrentPathId)

    local function getCurrentPointIndex(object)
        return object.currentPointIndex_
    end
    object:bindMethod(self, "getCurrentPointIndex", getCurrentPointIndex)

    local function isMovingForward(object)
        return object.bindingMovingForward_
    end
    object:bindMethod(self, "isMovingForward", isMovingForward)

    local function setMovingForward(object, movingForward)
        object.bindingMovingForward_ = movingForward
    end
    object:bindMethod(self, "setMovingForward", setMovingForward)

    local function isMovingLocked(object)
        return object.movingLocked_ > 0
    end
    object:bindMethod(self, "isMovingLocked", isMovingLocked)

    local function addMovingLock(object)
        object.movingLocked_ = object.movingLocked_ + 1
    end
    object:bindMethod(self, "addMovingLock", addMovingLock)

    local function removeMovingLock(object)
        object.movingLocked_ = object.movingLocked_ - 1
        assert(object.movingLocked_ >= 0, "MovableBehavior.removeMovingLock() - object.movingLocked_ must >= 0")
    end
    object:bindMethod(self, "removeMovingLock", removeMovingLock)

    local function bindPath(object, path, pathPointIndex)
        local pathId = path:getId()
        if object.bindingPathId_ ~= pathId and object.bindingPathId_ then
            object:unbindPath()
        end
        object.bindingPathId_     = pathId
        object.bindingPointIndex_ = pathPointIndex
        object:setPosition(path:getPoint(pathPointIndex))

        object.nextPathId_ = nil
        self:setNextPosition(object)
    end
    object:bindMethod(self, "bindPath", bindPath)

    local function unbindPath(object)
        object.bindingPathId_     = nil
        object.bindingPointIndex_ = nil
    end
    object:bindMethod(self, "unbindPath", unbindPath)

    local function validate(object)
        if not object.bindingPathId_ then return end
        if not object.map_:isObjectExists(object.bindingPathId_) then
            object:unbindPath()
            return
        end

        local path = object.map_:getObject(object.bindingPathId_)
        if object.bindingPointIndex_ < 1 or object.bindingPointIndex_ > path:getPointsCount() then
            object:unbindPath()
            return
        end

        object:setPosition(path:getPoint(object.bindingPointIndex_))
    end
    object:bindMethod(self, "validate", validate)

    local function startMoving(object)
        if not object.bindingPathId_ then return end

        if object.movingState_ == MovableBehavior.MOVING_STATE_STOPPED
                or object.movingState_ == MovableBehavior.MOVING_STATE_SPEEDDOWN then
            object.movingState_ = MovableBehavior.MOVING_STATE_SPEEDUP

            if not object.currentPathId_ then
                self:setNextPosition(object)
            end
        end
    end
    object:bindMethod(self, "startMoving", startMoving)

    local function stopMoving(object)
        if object.movingState_ == MovableBehavior.MOVING_STATE_FULLSPEED
                or object.movingState_ == MovableBehavior.MOVING_STATE_SPEEDUP then
            object.movingState_ = MovableBehavior.MOVING_STATE_SPEEDDOWN
        end
    end
    object:bindMethod(self, "stopMoving", stopMoving)

    local function stopMovingNow(object)
        object.movingState_ = MovableBehavior.MOVING_STATE_STOPPED
        object.currentSpeed_ = 0
    end
    object:bindMethod(self, "stopMovingNow", stopMovingNow)

    local function isMoving(object)
        return object.movingState_ == MovableBehavior.MOVING_STATE_FULLSPEED
                or object.movingState_ == MovableBehavior.MOVING_STATE_SPEEDUP
    end
    object:bindMethod(self, "isMoving", isMoving)

    local function tick(object, dt)
        if not object.play_ or object.movingLocked_ > 0 or not object.bindingPathId_ then return end

        local state = object.movingState_
        if state == MovableBehavior.MOVING_STATE_STOPPED then return end

        if state == MovableBehavior.MOVING_STATE_SPEEDUP
                or (state == MovableBehavior.MOVING_STATE_FULLSPEED
                    and object.currentSpeed_ < object.maxSpeed_) then
            object.currentSpeed_ = object.currentSpeed_ + object.speedIncr_
            if object.currentSpeed_ >= object.maxSpeed_ then
                object.currentSpeed_ = object.maxSpeed_
                object.movingState_ = MovableBehavior.MOVING_STATE_FULLSPEED
            end
        elseif state == MovableBehavior.MOVING_STATE_SPEEDDOWN then
            object.currentSpeed_ = object.currentSpeed_ - object.speedDecr_
            if object.currentSpeed_ <= 0 then
                object.currentSpeed_ = 0
                object.movingState_ = MovableBehavior.MOVING_STATE_STOPPED
            end
        elseif object.currentSpeed_ > object.maxSpeed_ then
            object.currentSpeed_ = object.currentSpeed_ - object.speedDecr_
            if object.currentSpeed_ < object.maxSpeed_ then
                object.currentSpeed_ = object.maxSpeed_
            end
        end

        local x, y = object.x_, object.y_
        local currentDist = object.currentDist_ + object.currentSpeed_
        if currentDist >= object.nextDist_ then
            object.x_, object.y_ = object.nextX_, object.nextY_
            currentDist = currentDist - object.nextDist_
            self:setNextPosition(object)
            x, y = math2d.pointAtCircle(object.x_, object.y_, object.nextRadians_, currentDist)
        else
            local ox, oy = math2d.pointAtCircle(0, 0, object.nextRadians_, object.currentSpeed_)
            x = x + ox
            y = y + oy
        end
        object.currentDist_ = currentDist

        if x < object.x_ then
            object.flipSprite_ = true
        elseif x > object.x_ then
            object.flipSprite_ = false
        end
        object.x_, object.y_ = x, y
    end
    object:bindMethod(self, "tick", tick)

    local function preparePlay(object)
        object.currentSpeed_       = 0
        object.movingState_ = MovableBehavior.MOVING_STATE_STOPPED
        object.nextPathId_  = nil
    end
    object:bindMethod(self, "preparePlay", preparePlay)

    local function getFuturePosition(object, time)
        local x, y = object.x_, object.y_
        if object.currentSpeed_ == 0 or not object.bindingPathId_ then
            return x, y
        end

        -- 到下一个路径点的距离、弧度，以及下一个路径点的位置
        local nextDist          = object.nextDist_
        local nextRadians       = object.nextRadians_
        local nextX, nextY      = object.nextX_, object.nextY_

        -- 从当前路径出发，time 时间后的距离
        local currentDist       = object.currentDist_ + object.currentSpeed_ * time * 60

        local map               = object.map_
        local currentPathId     = object.currentPathId_
        local currentPointIndex = object.currentPointIndex_
        local movingForward     = object.nextMovingForward_

        if currentDist < nextDist then
            currentDist = currentDist - object.currentDist_
        end

        while currentDist >= nextDist do
            x, y = nextX, nextY
            currentDist = currentDist - nextDist

            local nextPath,
                  nextPointIndex,
                  nextMovingForward = map:getNextPointIndexOnPath(currentPathId,
                                                                  currentPointIndex,
                                                                  movingForward,
                                                                  true)

            currentPathId     = nextPath:getId()
            currentPointIndex = nextPointIndex
            movingForward     = nextMovingForward
            nextX, nextY      = nextPath:getPoint(nextPointIndex)
            nextRadians       = math2d.radians4point(x, y, nextX, nextY)
            nextDist          = math2d.dist(x, y, nextX, nextY)
        end

        x, y = math2d.pointAtCircle(x, y, nextRadians, currentDist)
        return x, y
    end
    object:bindMethod(self, "getFuturePosition", getFuturePosition)

    local function setSpeed(object, maxSpeed)
        object.speed_ = checknumber(maxSpeed)
        if object.speed_ < 0 then object.speed_ = 0 end

        object.speedIncr_ = object.speed_ * 0.025 * MovableBehavior.SPEED_SCALE
        object.speedDecr_ = object.speed_ * 0.038 * MovableBehavior.SPEED_SCALE
        object.maxSpeed_  = object.speed_ * MovableBehavior.SPEED_SCALE
    end
    object:bindMethod(self, "setSpeed", setSpeed)

    local function vardump(object, state)
        state.bindingPathId        = object.bindingPathId_
        state.bindingPointIndex    = object.bindingPointIndex_
        state.bindingMovingForward = object.bindingMovingForward_
        return state
    end
    object:bindMethod(self, "vardump", vardump)

    self:reset(object)
end

function MovableBehavior:unbind(object)
    object.bindingPathId_        = nil
    object.bindingPointIndex_    = nil
    object.bindingMovingForward_ = nil

    object:unbindMethod(self, "isBinding")
    object:unbindMethod(self, "getBindingPathId")
    object:unbindMethod(self, "getBindingPointIndex")
    object:unbindMethod(self, "isMovingForward")
    object:unbindMethod(self, "setMovingForward")
    object:unbindMethod(self, "isMovingLocked")
    object:unbindMethod(self, "addMovingLock")
    object:unbindMethod(self, "removeMovingLock")
    object:unbindMethod(self, "bindPath")
    object:unbindMethod(self, "unbindPath")
    object:unbindMethod(self, "validate")
    object:unbindMethod(self, "startMoving")
    object:unbindMethod(self, "stopMoving")
    object:unbindMethod(self, "stopMovingNow")
    object:unbindMethod(self, "isMoving")
    object:unbindMethod(self, "tick")
    object:unbindMethod(self, "preparePlay")
    object:unbindMethod(self, "getFuturePosition")
    object:unbindMethod(self, "setSpeed")
    object:unbindMethod(self, "vardump")
end

function MovableBehavior:reset(object)
    object:setSpeed(checknumber(object.state_.speed))
    object.currentSpeed_ = 0
    object.movingState_  = MovableBehavior.MOVING_STATE_STOPPED
end

return MovableBehavior
