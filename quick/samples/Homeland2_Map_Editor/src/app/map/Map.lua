
--[[--

Map 对象的生命周期

Map.new() 创建 Map 对象实例
Map:init() 初始化 Map 对象
Map:createView() 创建 Map 对象的视图
Map:removeView() 删除 Map 对象的视图
Map:updateView() 更新 Map 对象的视图
Map:destroy() 销毁 Map 对象

Map:newObject() 创建新的地图子对象，并绑定行为
                如果此时视图已经创建，则调用子对象的 createView()

]]

local MapConstants  = require("app.map.MapConstants")
local MapCamera     = require("app.map.MapCamera")
local ObjectFactory = require("app.map.ObjectFactory")
local Path          = require("app.map.Path")

local Map = class("Map")

function Map:ctor(id, debug)
    self.id_               = id
    self.debug_            = debug
    self.debugViewEnabled_ = debug
    self.ready_            = false
    self.mapModuleName_    = string.format("maps.Map%sData", id)
    self.eventModuleName_  = string.format("maps.Map%sEvents", id)

    local ok, data = pcall(function() return require(self.mapModuleName_) end)
    if not ok or type(data) ~= "table" then
        data = {
            size    = {width = CONFIG_SCREEN_WIDTH, height = CONFIG_SCREEN_HEIGHT},
            objects = {},
        }
    end
    self.data_ = clone(data)
end

function Map:init()
    self.width_             = self.data_.size.width
    self.height_            = self.data_.size.height
    self.imageName_         = self.data_.imageName
    if not self.imageName_ then
        self.imageName_ = string.format("Map%sBg.png", self.id_)
    end

    self.bgSprite_          = nil
    self.batch_             = nil
    self.marksLayer_        = nil
    self.promptLayer_       = nil
    self.debugLayer_        = nil

    self.objects_           = {}
    self.objectsByClass_    = {}
    self.nextObjectIndex_   = 1

    -- 添加地图数据中的对象
    for id, state in pairs(self.data_.objects) do
        local classId = unpack(string.split(id, ":"))
        self:newObject(classId, state, id)
    end

    -- 验证所有的路径
    for i, path in pairs(self:getObjectsByClassId("path")) do
        path:validate()
        if not path:isValid() then
            echoInfo(string.format("Map:init() - invalid path %s", path:getId()))
            self:removeObject(path)
        end
    end

    -- 验证其他对象
    for id, object in pairs(self.objects_) do
        local classId = object:getClassId()
        if classId ~= "path" then
            object:validate()
            if not object:isValid() then
                echoInfo(string.format("Map:init() - invalid object %s", object:getId()))
                self:removeObject(object)
            end
        end
    end

    -- 计算地图位移限定值
    self.camera_ = MapCamera.new(self)
    self.camera_:resetOffsetLimit()

    -- 地图已经准备好
    self.ready_ = true
end

--[[--

返回地图的 Id

]]
function Map:getId()
    return self.id_
end

--[[--

返回地图尺寸

]]
function Map:getSize()
    return self.width_, self.height_
end

--[[--

返回摄像机对象

]]
function Map:getCamera()
    return self.camera_
end

--[[--

确认地图是否处于 Debug 模式

]]
function Map:isDebug()
    return self.debug_
end

--[[--

确认是否允许使用调试视图

]]
function Map:isDebugViewEnabled()
    return self.debugViewEnabled_
end

--[[--

设置地图调试模式

]]
function Map:setDebugViewEnabled(isDebugViewEnabled)
    self.debugViewEnabled_ = isDebugViewEnabled
    for id, object in pairs(self.objects_) do
        object:setDebugViewEnabled(isDebugViewEnabled)
    end
    if self:getDebugLayer() then
        self:getDebugLayer():setVisible(isDebugViewEnabled)
    end
end

--[[--

确认地图是否已经创建了视图

]]
function Map:isViewCreated()
    return self.batch_ ~= nil
end

--[[--

创建新的对象，并添加到地图中

]]
function Map:newObject(classId, state, id)
    if not id then
        id = string.format("%s:%d", classId, self.nextObjectIndex_)
        self.nextObjectIndex_ = self.nextObjectIndex_ + 1
    end

    local object = ObjectFactory.newObject(classId, id, state, self)
    object:setDebug(self.debug_)
    object:setDebugViewEnabled(self.debugViewEnabled_)
    object:resetAllBehaviors()

    -- validate max object index
    local index = object:getIndex()
    if index >= self.nextObjectIndex_ then
        self.nextObjectIndex_ = index + 1
    end

    -- add object
    self.objects_[id] = object
    if not self.objectsByClass_[classId] then
        self.objectsByClass_[classId] = {}
    end
    self.objectsByClass_[classId][id] = object

    -- validate object
    if self.ready_ then
        object:validate()
        if not object:isValid() then
            echoInfo(string.format("Map:newObject() - invalid object %s", id))
            self:removeObject(object)
            return nil
        end

        -- create view
        if self:isViewCreated() then
            object:createView(self.batch_, self.marksLayer_, self.debugLayer_)
            object:updateView()
        end
    end

    return object
end

--[[--

从地图中删除一个对象

]]
function Map:removeObject(object)
    local id = object:getId()
    assert(self.objects_[id] ~= nil, string.format("Map:removeObject() - object %s not exists", tostring(id)))

    self.objects_[id] = nil
    self.objectsByClass_[object:getClassId()][id] = nil
    if object:isViewCreated() then object:removeView() end
end

--[[--

从地图中删除指定 Id 的对象

]]
function Map:removeObjectById(objectId)
    self:removeObject(self:getObject(objectId))
end

--[[--

删除所有对象

]]
function Map:removeAllObjects()
    for id, object in pairs(self.objects_) do
        self:removeObject(object)
    end
    self.objects_           = {}
    self.objectsByClass_    = {}
    self.nextObjectIndex_   = 1
    self.crossPointsOnPath_ = {}
end

--[[--

检查指定的对象是否存在

]]
function Map:isObjectExists(id)
    return self.objects_[id] ~= nil
end

--[[--

返回指定 Id 的对象

]]
function Map:getObject(id)
    assert(self:isObjectExists(id), string.format("Map:getObject() - object %s not exists", tostring(id)))
    return self.objects_[id]
end

--[[--

返回地图中所有的对象

]]
function Map:getAllObjects()
    return self.objects_
end

--[[--

返回地图中特定类型的对象

]]
function Map:getObjectsByClassId(classId)
    -- dump(self.objectsByClass_[classId])
    return self.objectsByClass_[classId] or {}
end

--[[--

获取指定路径开始，下一个点的坐标

]]
function Map:getNextPointIndexOnPath(pathId, pointIndex, movingForward, reverseAtEnd)
    local path = self:getObject(pathId)

    if movingForward then
        pointIndex = pointIndex + 1
        local count = path:getPointsCount()
        if pointIndex > count then
            pointIndex = count
            if reverseAtEnd then
                pointIndex = pointIndex - 1
                movingForward = false
            end
        end
    else
        pointIndex = pointIndex - 1
        if pointIndex < 1 then
            pointIndex = 1
            if reverseAtEnd then
                pointIndex = 2
                movingForward = true
            end
        end
    end

    return path, pointIndex, movingForward
end

--[[--

建立地图的视图

]]
function Map:createView(parent)
    assert(self.batch_ == nil, "Map:createView() - view already created")

    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RG_B565)
    self.bgSprite_ = display.newSprite(self.imageName_)
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)

    self.bgSprite_:addNodeEventListener(cc.NODE_EVENT, function(event)
        -- 地图对象删除时，自动从缓存里卸载地图材质
        if event.name == "exit" then
            display.removeSpriteFrameByImageName(self.imageName_)
        end
    end)

    self.bgSprite_:align(display.LEFT_BOTTOM, 0, 0)
    parent:addChild(self.bgSprite_)

    -- self.batch_ = display.newBatchNode("SheetMapBattle.png", 1000)
    self.batch_ = display.newNode()
    parent:addChild(self.batch_)

    self.marksLayer_ = display.newNode()
    parent:addChild(self.marksLayer_)

    if self.debug_ then
        self.debugLayer_ = display.newNode()
        parent:addChild(self.debugLayer_)
    end

    for id, object in pairs(self.objects_) do
        object:createView(self.batch_, self.marksLayer_, self.debugLayer_)
        object:updateView()
    end

    self:setAllObjectsZOrder()
end

--[[--

删除视图

]]
function Map:removeView()
    assert(self.batch_ ~= nil, "Map:removeView() - view not exists")

    for id, object in pairs(self.objects_) do
        if object:isViewCreated() then object:removeView() end
    end

    self.bgSprite_:removeSelf()
    self.batch_:removeSelf()
    self.marksLayer_:removeSelf()
    if self.debugLayer_ then self.debugLayer_:removeSelf() end

    self.bgSprite_   = nil
    self.batch_      = nil
    self.marksLayer_ = nil
    self.debugLayer_ = nil
end

--[[--

调用地图中所有对象的 updateView()

]]
function Map:updateView()
    assert(self.batch_ ~= nil, "Map:removeView() - view not exists")

    for id, object in pairs(self.objects_) do
        object:updateView()
    end
end

--[[--

按照 Y 坐标重新排序所有可视对象

]]
function Map:setAllObjectsZOrder()
    local batch = self.batch_
    for id, object in pairs(self.objects_) do
        local view = object:getView()
        if view then
            if object.viewZOrdered_ then
                batch:reorderChild(view, MapConstants.MAX_OBJECT_ZORDER - object.y_)
            elseif type(object.zorder_) == "number" then
                batch:reorderChild(view, object.zorder_)
            else
                batch:reorderChild(view, MapConstants.DEFAULT_OBJECT_ZORDER)
            end
            object:updateView()
        end
    end
end

--[[--

返回背景图

]]
function Map:getBackgroundLayer()
    return self.bgSprite_
end

--[[--

返回地图的批量渲染层

]]
function Map:getBatchLayer()
    return self.batch_
end

--[[--

返回用于显示地图标记的层

]]
function Map:getMarksLayer()
    return self.marksLayer_
end

--[[--

放回用于编辑器的批量渲染层

]]
function Map:getDebugLayer()
    return self.debugLayer_
end

--[[--

返回地图的数据

]]
function Map:vardump()
    local state = {
        objects   = {},
        size      = {width = self.width_, height = self.height_},
        imageName = self.imageName_,
    }
    for id, object in pairs(self.objects_) do
        state.objects[id] = object:vardump()
    end
    return state
end

--[[--

导出地图数据

]]
function Map:dump()
    local lines = {}

    lines[#lines + 1] = ""
    lines[#lines + 1] = string.format("------------ MAP %s ------------", self.id_)
    lines[#lines + 1] = ""
    lines[#lines + 1] = "local map = {}"
    lines[#lines + 1] = ""
    lines[#lines + 1] = string.format("map.size = {width = %d, height = %d}", self.width_, self.height_)
    lines[#lines + 1] = string.format("map.imageName = \"%s\"", self.imageName_)
    lines[#lines + 1] = ""

    -- objects
    local allid = table.keys(self.objects_)
    table.sort(allid)
    lines[#lines + 1] = "local objects = {}"
    for i, id in ipairs(allid) do
        lines[#lines + 1] = ""
        lines[#lines + 1] = self.objects_[id]:dump("local object")
        lines[#lines + 1] = string.format("objects[\"%s\"] = object", id)
        lines[#lines + 1] = ""
        lines[#lines + 1] = "----"
    end
    lines[#lines + 1] = ""
    lines[#lines + 1] = "map.objects = objects"
    lines[#lines + 1] = ""
    lines[#lines + 1] = "return map"
    lines[#lines + 1] = ""
    return table.concat(lines, "\n")
end

--[[--

从 package.path 中查找指定模块的文件名，如果失败返回 false。

@param string moduleName
@return string

]]
function Map:findModulePath(moduleName)
    local filename = string.gsub(moduleName, "%.", "/") .. ".lua"
    local paths = string.split(package.path, ";")
    for i, path in ipairs(paths) do
        if string.sub(path, -5) == "?.lua" then
            path = string.sub(path, 1, -6)
            if not string.find(path, "?", 1, true) then
                local fullpath = path .. filename
                if io.exists(fullpath) then
                    return fullpath
                end
            end
        end
    end
    return false
end

--[[--

导出地图数据到文件

]]
function Map:dumpToFile()
    local contents = self:dump()
    local path = self:findModulePath(self.mapModuleName_)
    if path then
        printf("save data filename \"%s\" [%s]", path, os.date("%Y-%m-%d %H:%M:%S"))
        io.writefile(path, contents)
        return true
    else
        printf("not found module file, dump [%s]", os.date("%Y-%m-%d %H:%M:%S"))
        echo("\n\n" .. contents .. "\n")
        return false
    end
end

--[[--

重置地图状态

]]
function Map:reset(state)
    self:removeAllObjects()
    if self:isViewCreated() then self:removeView() end

    self.data_ = clone(state)
    self.ready_ = false
    self:init()
end

return Map
