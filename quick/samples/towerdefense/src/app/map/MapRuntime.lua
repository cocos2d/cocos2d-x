
local MapEvent     = require("app.map.MapEvent")
local MapConstants = require("app.map.MapConstants")
local Decoration   = require("app.map.Decoration")
local ObjectBase   = require("app.map.ObjectBase")
local math2d       = require("math2d")

local MapRuntime = class("MapRuntime", function()
    return display.newNode()
end)

local MAP_EVENT_COLLISION_BEGAN = 1
local MAP_EVENT_COLLISION_ENDED = 2
local MAP_EVENT_FIRE            = 3
local MAP_EVENT_NO_FIRE_TARGET  = 4

local CLASS_INDEX_PATH   = ObjectBase.CLASS_INDEX_PATH
local CLASS_INDEX_RANGE  = ObjectBase.CLASS_INDEX_RANGE
local CLASS_INDEX_STATIC = ObjectBase.CLASS_INDEX_STATIC

function MapRuntime:ctor(map)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()

    self.debug_                = map:isDebug()
    self.map_                  = map
    self.batch_                = map:getBatchLayer()
    self.camera_               = map:getCamera()
    self.starting_             = false
    self.over_                 = false
    self.paused_               = false
    self.promptTarget_         = nil -- 战场提示
    self.time_                 = 0 -- 地图已经运行的时间
    self.lastSecond_           = 0 -- 用于触发 OBJECT_IN_RANGE 事件
    self.dispatchCloseHelp_    = 0
    self.towers_               = {} -- 所有的塔，在玩家触摸时显示开火范围
    self.bullets_              = {} -- 所有的子弹对象
    self.skills_               = {} -- 所有的上帝技能对象
    self.racePersonnel_        = {}
    self.raceRank_             = {}
    self.disableList_          = {{}, {}, {}, {}, {}}
    self.decreaseCooldownRate_ = 1 -- 减少上帝技能冷却时间百分比
    self.skillCoolDown_        = {0, 0, 0, 0, 0}
    self.skillNeedTime_        = {0, 0, 0, 0, 0}
    self.colls_                = {} -- 用于跟踪碰撞状态

    local eventHandlerModuleName = string.format("maps.Map%sEvents", map:getId())
    local eventHandlerModule = require(eventHandlerModuleName)
    self.handler_ = eventHandlerModule.new(self, map)

    -- 创建物理调试视图
    -- self.debugView_ = self:createDebugNode()
    -- self.debugView_:setVisible(false)
    -- self:addChild(self.debugView_)

    -- 启用节点事件，确保 onExit 时停止
    -- self:setNodeEventEnabled(true)
end

function MapRuntime:onExit()
    self:stopPlay()
end

function MapRuntime:preparePlay()
    self.handler_:preparePlay()
    self:dispatchEvent({name = MapEvent.MAP_PREPARE_PLAY})

    for id, object in pairs(self.map_:getAllObjects()) do
        object:validate()
        object:preparePlay()
        object:updateView()
    end

    self.camera_:setOffset(0, 0)

    self.time_          = 0
    self.lastSecond_    = 0
end

--[[--

开始运行地图

]]
function MapRuntime:startPlay()
    -- self.debugView_:setVisible(true)

    self.starting_    = true
    self.over_        = false
    self.paused_      = false
    self.towers_ = {}

    for id, object in pairs(self.map_:getAllObjects()) do
        object:startPlay()
        object.updated__ = true

        if object.classIndex_ == CLASS_INDEX_STATIC and object:hasBehavior("TowerBehavior") then
            self.towers_[id] = {
                object.x_ + object.radiusOffsetX_,
                object.y_ + object.radiusOffsetY_,
                object.radius_ + 20,
            }
        end
    end

    self.handler_:startPlay(state)
    self:dispatchEvent({name = MapEvent.MAP_START_PLAY})

    -- self:start() -- start physics world
end

--[[--

停止运行地图

]]
function MapRuntime:stopPlay()
    -- self.debugView_:setVisible(false)
    -- self:stop() -- stop physics world

    for id, object in pairs(self.map_:getAllObjects()) do
        object:stopPlay()
    end

    self.handler_:stopPlay()
    self:dispatchEvent({name = MapEvent.MAP_STOP_PLAY})
    self:removeAllEventListeners()

    self.starting_ = false
end

function MapRuntime:onTouch(event, x, y)
    if self.over_ or self.paused_ or event ~= "began" then return end

    -- 将触摸的屏幕坐标转换为地图坐标
    local x, y = self.camera_:convertToMapPosition(x, y)
    local minDist = 999999

    -- 检查是否选中了某个塔
    local selectedTowerId
    for id, tower in pairs(self.towers_) do
        local dist = math2d.dist(x, y, tower[1], tower[2])
        if dist < minDist and dist <= tower[3] then
            minDist = dist
            selectedTowerId = id
        end
    end

    if selectedTowerId then
        -- 对选中的塔做操作
    end
end

function MapRuntime:tick(dt)
    if not self.starting_ or self.paused_ then return end

    local handler = self.handler_

    self.time_ = self.time_ + dt
    local secondsDelta = self.time_ - self.lastSecond_
    if secondsDelta >= 1.0 then
        self.lastSecond_ = self.lastSecond_ + secondsDelta
        if not self.over_ then
            handler:time(self.time_, secondsDelta)
        end
    end

    -- 更新所有对象后
    local maxZOrder = MapConstants.MAX_OBJECT_ZORDER
    for i, object in pairs(self.map_.objects_) do
        if object.tick then
            local lx, ly = object.x_, object.y_
            object:tick(dt)
            object.updated__ = lx ~= object.x_ or ly ~= object.y_

            -- 只有当对象的位置发生变化时才调整对象的 ZOrder
            if object.updated__ and object.sprite_ and object.viewZOrdered_ then
                self.batch_:reorderChild(object.sprite_, maxZOrder - (object.y_ + object.offsetY_))
            end
        end

        if object.fastUpdateView then
            object:fastUpdateView()
        end
    end

    -- 通过碰撞引擎获得事件
    local events = self:tickCollider(self.map_.objects_, self.colls_, dt)
    if self.over_ then
        events = {}
    end

    if events and #events > 0 then
        for i, t in ipairs(events) do
            local event, object1, object2 = t[1], t[2], t[3]
            if event == MAP_EVENT_COLLISION_BEGAN then
                if object2.classIndex_ == CLASS_INDEX_RANGE then
                    handler:objectEnterRange(object1, object2)
                    self:dispatchEvent({name = MapEvent.OBJECT_ENTER_RANGE, object = object1, range = object2})
                else
                    handler:objectCollisionBegan(object1, object2)
                    self:dispatchEvent({
                        name = MapEvent.OBJECT_COLLISION_BEGAN,
                        object1 = object1,
                        object2 = object2,
                    })
                end
            elseif event == MAP_EVENT_COLLISION_ENDED then
                if object2.classIndex_ == CLASS_INDEX_RANGE then
                    handler:objectExitRange(object1, object2)
                    self:dispatchEvent({name = MapEvent.OBJECT_EXIT_RANGE, object = object1, range = object2})
                else
                    handler:objectCollisionEnded(object1, object2)
                    self:dispatchEvent({
                        name = MapEvent.OBJECT_COLLISION_ENDED,
                        object1 = object1,
                        object2 = object2,
                    })
                end
            elseif event == MAP_EVENT_FIRE then
                handler:fire(object1, object2)
            elseif event == MAP_EVENT_NO_FIRE_TARGET then
                handler:noTarget(object1)
            end
        end
    end

    -- 更新所有的子弹对象
    for i = #self.bullets_, 1, -1 do
        local bullet = self.bullets_[i]
        bullet:tick(dt)
        if bullet:isOver() then
            if bullet:checkHit() then
                handler:hit(bullet.source_, bullet.target_, bullet, self.time_)
            else
                handler:miss(bullet.source_, bullet.target_, bullet)
            end
            bullet:removeView()
            table.remove(self.bullets_, i)
        end
    end
end

function MapRuntime:getMap()
    return self.map_
end

function MapRuntime:getCamera()
    return self.map_:getCamera()
end

function MapRuntime:getTime()
    return self.time_
end

--[[--

用于运行时创建新对象并放入地图

]]
function MapRuntime:newObject(classId, state, id)
    local object = self.map_:newObject(classId, state, id)
    object:preparePlay()
    if self.starting_ then object:startPlay() end

    if object.sprite_ and object.viewZOrdered_ then
        self.batch_:reorderChild(object.sprite_, MapConstants.MAX_OBJECT_ZORDER - (object.y_ + object.offsetY_))
    end
    object:updateView()

    return object
end

--[[--

删除对象及其视图

]]
function MapRuntime:removeObject(object, delay)
    if delay then
        object:getView():performWithDelay(function()
            self.map_:removeObject(object)
        end, delay)
    else
        self.map_:removeObject(object)
    end
end

--[[--

创建一个装饰对象并放入地图

]]
function MapRuntime:newDecoration(decorationName, target, x, y)
    local decoration = Decoration.new(decorationName)
    decoration:createView(self.batch_)

    local view = decoration:getView()
    if target then
        local targetView = target:getView()
        self.batch_:reorderChild(view, targetView:getLocalZOrder() + decoration.zorder_)
        local ox, oy = checknumber(x), checknumber(y)
        x, y = target:getPosition()
        x = math.floor(x)
        y = math.floor(y)
        view:setPosition(x + ox + decoration.offsetX_, y + oy + decoration.offsetY_)
        view:setScaleX(targetView:getScaleY() * decoration.scale_)
    else
        view:setPosition(x + decoration.offsetX_, y + decoration.offsetY_)
        view:setScaleX(decoration.scale_)
    end

    return decoration
end

function MapRuntime:addBullet(bullet)
    self.bullets_[#self.bullets_ + 1] = bullet
end

function MapRuntime:winGame(player)
    if self.over_ then return end
    self.over_ = true
    self:dispatchEvent({name = MapEvent.MAP_WIN})
    self:pausePlay()
end

function MapRuntime:loseGame(player)
    if self.over_ then return end
    self.over_ = true
    self:dispatchEvent({name = MapEvent.MAP_LOSE})
    self:pausePlay()
end

function MapRuntime:pausePlay()
    if not self.paused_ then
        self:dispatchEvent({name = MapEvent.MAP_PAUSE_PLAY})
    end
    self.paused_ = true
end

function MapRuntime:resumePlay()
    if self.paused_ then
        self:dispatchEvent({name = MapEvent.MAP_RESUME_PLAY})
    end
    self.paused_ = false
end

local function checkStiaticObjectCollisionEnabled(obj)
    return obj.classIndex_ == CLASS_INDEX_STATIC
        and (not obj.destroyed_)
        and obj.collisionEnabled_
        and obj.collisionLock_ <= 0
end

function MapRuntime:tickCollider(objects, colls, dt)
    local dists = {}
    local sqrt = math.sqrt

    -- 遍历所有对象，计算静态对象与其他静态对象或 Range 对象之间的距离
    for id1, obj1 in pairs(objects) do
        while true do
            if not checkStiaticObjectCollisionEnabled(obj1) then
                break
            end

            local x1, y1 = obj1.x_ + checknumber(obj1.radiusOffsetX_), obj1.y_ + checknumber(obj1.radiusOffsetY_)
            local campId1 = checkint(obj1.campId_)
            dists[obj1] = {}

            for id2, obj2 in pairs(objects) do
                while true do
                    if obj1 == obj2 then break end

                    local ci = obj2.classIndex_
                    if ci ~= CLASS_INDEX_STATIC and ci ~= CLASS_INDEX_RANGE then break end
                    if ci == CLASS_INDEX_STATIC and not checkStiaticObjectCollisionEnabled(obj2) then break end
                    if campId1 ~= 0 and campId1 == obj2.campId_ then break end

                    local x2, y2 = obj2.x_ + checknumber(obj2.radiusOffsetX_), obj2.y_ + checknumber(obj2.radiusOffsetY_)
                    local dx = x2 - x1
                    local dy = y2 - y1
                    local dist = sqrt(dx * dx + dy * dy)
                    dists[obj1][obj2] = dist

                    break -- stop while
                end
            end -- for id2, obj2 in pairs(objects) do

            break -- stop while
        end
    end -- for id1, obj1 in pairs(objects) do

    -- 检查碰撞和开火
    local events = {}
    for obj1, obj1targets in pairs(dists) do
        local fireRange1 = checknumber(obj1.fireRange_)
        local radius1 = checknumber(obj1.radius_)
        local checkFire1 = obj1.fireEnabled_ and checknumber(obj1.fireLock_) <= 0 and fireRange1 > 0 and checknumber(obj1.fireCooldown_) <= 0

        -- 从 obj1 的目标中查找距离最近的
        local minTargetDist = 999999
        local fireTarget = nil

        -- 初始化碰撞目标数组
        if not colls[obj1] then colls[obj1] = {} end
        local obj1colls = colls[obj1]

        -- 检查 obj1 和 obj2 的碰撞关系
        for obj2, dist1to2 in pairs(obj1targets) do
            local radius2 = obj2.radius_
            local isCollision = dist1to2 - radius1 - radius2 <= 0

            local event = 0
            local obj2CollisionWithObj1 = obj1colls[obj2]
            if isCollision and not obj2CollisionWithObj1 then
                -- obj1 和 obj2 开始碰撞
                event = MAP_EVENT_COLLISION_BEGAN
                obj1colls[obj2] = true
            elseif not isCollision and obj2CollisionWithObj1 then
                -- obj1 和 obj2 结束碰撞
                event = MAP_EVENT_COLLISION_ENDED
                obj1colls[obj2] = nil
            end

            if event ~= 0 then
                -- 记录事件
                events[#events + 1] = {event, obj1, obj2}
            end

            -- 检查 obj1 是否可以对 obj2 开火
            if checkFire1 and obj2.classIndex_ == CLASS_INDEX_STATIC then
                local dist = dist1to2 - fireRange1 - radius2
                if dist <= 0 and dist < minTargetDist then
                    minTargetDist = dist
                    fireTarget = obj2
                end
            end
        end

        if fireTarget then
            events[#events + 1] = {MAP_EVENT_FIRE, obj1, fireTarget}
        elseif checkFire1 then
            events[#events + 1] = {MAP_EVENT_NO_FIRE_TARGET, obj1}
        end
    end

    return events
end

return MapRuntime
