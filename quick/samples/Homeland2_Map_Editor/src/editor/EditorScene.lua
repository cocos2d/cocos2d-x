
local scheduler = require("framework.scheduler")

local LEVEL_ID = "A0002"

local EditorConstants = require("editor.EditorConstants")

--[[--

编辑器场景

]]
local EditorScene = class("EditorScene", function()
    return display.newScene("EditorScene")
end)

function EditorScene:ctor()
    -- 根据设备类型确定工具栏的缩放比例
    self.toolbarLines = 1
    self.editorUIScale = 1
    self.statusCount_ = 1
    self.totalScore_ = 0
    if (device.platform == "ios" and device.model == "iphone") or device.platform == "android" then
        self.editorUIScale = 2
        self.toolbarLines = 2
    end

    local bg = display.newTilesSprite("EditorBg.png")
    self:addChild(bg)

    -- mapLayer 包含地图的整个视图
    self.mapLayer_ = display.newNode()
    self.mapLayer_:align(display.LEFT_BOTTOM, 0, 0)
    self:addChild(self.mapLayer_)

    -- touchLayer 用于接收触摸事件
    self.touchLayer_ = display.newLayer()
    self:addChild(self.touchLayer_)

    -- uiLayer 用于显示编辑器的 UI（工具栏等）
    self.uiLayer_ = display.newNode()
    self.uiLayer_:setPosition(display.cx, display.cy)
    self:addChild(self.uiLayer_)

    -- 创建地图对象
    self.map_ = require("app.map.Map").new(LEVEL_ID, true) -- 参数：地图ID, 是否是编辑器模式
    self.map_:init()
    self.map_:createView(self.mapLayer_)

    -- 创建工具栏
    self.toolbar_ = require("editor.Toolbar").new(self.map_)
    self.toolbar_:addTool(require("editor.GeneralTool").new(self.toolbar_, self.map_))
    self.toolbar_:addTool(require("editor.ObjectTool").new(self.toolbar_, self.map_))
    self.toolbar_:addTool(require("editor.PathTool").new(self.toolbar_, self.map_))
    self.toolbar_:addTool(require("editor.RangeTool").new(self.toolbar_, self.map_))

    -- 创建工具栏的视图
    self.toolbarView_ = self.toolbar_:createView(self.uiLayer_, "#ToolbarBg.png", EditorConstants.TOOLBAR_PADDING, self.editorUIScale, self.toolbarLines)
    self.toolbarView_:setPosition(display.c_left, display.c_bottom)
    self.toolbar_:setDefaultTouchTool("GeneralTool")
    self.toolbar_:selectButton("GeneralTool", 1)

    -- 创建对象信息面板
    local objectInspectorScale = 1
    -- if self.editorUIScale > 1 then
    --     objectInspectorScale = 1.5
    -- end
    self.objectInspector_ = require("editor.ObjectInspector").new(self.map_, objectInspectorScale, self.toolbarLines)
    self.objectInspector_:addEventListener("UPDATE_OBJECT", function(event)
        self.toolbar_:dispatchEvent(event)
    end)
    self.objectInspector_:createView(self.uiLayer_)

    -- 创建地图名称文字标签
    self.mapNameLabel_ = cc.ui.UILabel.new({
        text  = string.format("module: %s, image: %s", self.map_.mapModuleName_, self.map_.imageName_),
        size  = 16 * self.editorUIScale,
        align = ui.TEXT_ALIGN_LEFT,
        x     = display.left + 10,
        y     = display.bottom + EditorConstants.MAP_TOOLBAR_HEIGHT * self.editorUIScale * self.toolbarLines + 20,
    }):align(display.CENTER)
    self.mapNameLabel_:enableOutline(cc.c4b(255, 0, 0), 2)
    self.mapLayer_:addChild(self.mapNameLabel_)

    -- 注册工具栏事件
    self.toolbar_:addEventListener("SELECT_OBJECT", function(event)
        self.objectInspector_:setObject(event.object)
    end)
    self.toolbar_:addEventListener("UPDATE_OBJECT", function(event)
        self.objectInspector_:setObject(event.object)
    end)
    self.toolbar_:addEventListener("UNSELECT_OBJECT", function(event)
        self.objectInspector_:removeObject()
    end)
    self.toolbar_:addEventListener("PLAY_MAP", function()
        self:playMap()
    end)

    -- 创建运行地图时的工具栏
    self.playToolbar_ = display.newNode()
    cc.ui.UIPushButton.new({normal = "#ToggleDebugButton.png", pressed = "#ToggleDebugButtonSelected.png"})
        :onButtonClicked(function(event)
            self.map_:setDebugViewEnabled(not self.map_:isDebugViewEnabled())
        end)
        :align(display.CENTER, display.left + 32 * self.editorUIScale, display.top - 32 * self.editorUIScale)
        :addTo(self.playToolbar_)
        :setScale(self.editorUIScale)

    cc.ui.UIPushButton.new({normal = "#StopMapButton.png", pressed = "#StopMapButtonSelected.png"})
        :onButtonClicked(function(event)
            self:editMap()
        end)
        :align(display.CENTER, display.left + 88 * self.editorUIScale, display.top - 32 * self.editorUIScale)
        :addTo(self.playToolbar_)
        :setScale(self.editorUIScale)

    self.recordBtn_ = cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
        :setButtonLabel(cc.ui.UILabel.new({text = "统计运行状态", size = 20, color = display.COLOR_BLACK}))
        :setButtonSize(130, 40)
        :align(display.CENTER, display.left + 190 * self.editorUIScale, display.top - 32 * self.editorUIScale)
        :addTo(self.playToolbar_)  
        :onButtonClicked(function()
            self:showStatusCurve()
            self:statusTimerBegin()
        end)

    -- local toggleDebugButton = ui.newImageMenuItem({
    --     image         = "#ToggleDebugButton.png",
    --     imageSelected = "#ToggleDebugButtonSelected.png",
    --     x             = display.left + 32 * self.editorUIScale,
    --     y             = display.top - 32 * self.editorUIScale,
    --     listener      = function()
    --         self.map_:setDebugViewEnabled(not self.map_:isDebugViewEnabled())
    --     end
    -- })
    -- toggleDebugButton:setScale(self.editorUIScale)

    -- local stopMapButton = ui.newImageMenuItem({
    --     image         = "#StopMapButton.png",
    --     imageSelected = "#StopMapButtonSelected.png",
    --     x             = display.left + 88 * self.editorUIScale,
    --     y             = display.top - 32 * self.editorUIScale,
    --     listener      = function() self:editMap() end
    -- })
    -- stopMapButton:setScale(self.editorUIScale)

    -- self.playToolbar_ = ui.newMenu({toggleDebugButton, stopMapButton})
    self.playToolbar_:setVisible(false)
    self:addChild(self.playToolbar_)

    if (device.platform == "windows" or device.platform == "ios" or device.platform == "android") then
        self:playMap()
    else
        self:editMap()
    end
end

-- 开始运行地图
function EditorScene:playMap()
    cc.Director:getInstance():setDisplayStats(true)

    -- 隐藏编辑器界面
    self.toolbar_:getView():setVisible(false)

    -- 保存地图当前状态
    self.mapState_ = self.map_:vardump()
    self.playToolbar_:setVisible(true)
    self.mapNameLabel_:setVisible(false)

    self.map_:setDebugViewEnabled(false)
    self.map_:getBackgroundLayer():setVisible(true)
    self.map_:getBackgroundLayer():setOpacity(255)

    local camera = self.map_:getCamera()
    camera:setMargin(0, 0, 0, 0)
    camera:setOffset(0, 0)

    -- 强制垃圾回收
    collectgarbage()
    collectgarbage()

    -- 开始执行地图
    self.mapRuntime_ = require("app.map.MapRuntime").new(self.map_)
    self.mapRuntime_:preparePlay()
    self.mapRuntime_:startPlay()
    self:addChild(self.mapRuntime_)
end

-- 开始编辑地图
function EditorScene:editMap()
    cc.Director:getInstance():setDisplayStats(false)

    if self.mapRuntime_ then
        self.mapRuntime_:stopPlay()
        self.mapRuntime_:removeSelf()
        self.mapRuntime_ = nil
    end

    self.map_:setDebugViewEnabled(true)
    if self.mapState_ then
        -- 重置地图状态
        self.map_:reset(self.mapState_)
        self.map_:createView(self.mapLayer_)
        self.mapState_ = nil
    end

    self.toolbar_:getView():setVisible(true)
    self.playToolbar_:setVisible(false)
    self.mapNameLabel_:setVisible(true)

    local camera = self.map_:getCamera()
    camera:setMargin(EditorConstants.MAP_PADDING,
                     EditorConstants.MAP_PADDING,
                     EditorConstants.MAP_PADDING + EditorConstants.MAP_TOOLBAR_HEIGHT * self.editorUIScale * self.toolbarLines + 20,
                     EditorConstants.MAP_PADDING)
    camera:setScale(1)
    camera:setOffset(0, 0)

    -- 强制垃圾回收
    collectgarbage()
    collectgarbage()
end

function EditorScene:tick(dt)
    if self.mapRuntime_ then
        self.mapRuntime_:tick(dt)
    end
end

function EditorScene:onTouch(event, x, y)
    if self.mapRuntime_ then
        -- 如果正在运行地图，将触摸事件传递到地图
        if self.mapRuntime_:onTouch(event, x, y, map) == true then
            return true
        end

        if event == "began" then
            self.drag = {
                startX  = x,
                startY  = y,
                lastX   = x,
                lastY   = y,
                offsetX = 0,
                offsetY = 0,
            }
            return true
        end

        if event == "moved" then
            self.drag.offsetX = x - self.drag.lastX
            self.drag.offsetY = y - self.drag.lastY
            self.drag.lastX = x
            self.drag.lastY = y
            self.map_:getCamera():moveOffset(self.drag.offsetX, self.drag.offsetY)

        else -- "ended" or CCTOUCHCANCELLED
            self.drag = nil
        end

        return
    end

    -- 如果没有运行地图，则将事件传递到工具栏
    x, y = math.round(x), math.round(y)
    if event == "began" then
        if self.objectInspector_:getView():isVisible() and self.objectInspector_:checkPointIn(x, y) then
            return self.objectInspector_:onTouch(event, x, y)
        end
    end

    return self.toolbar_:onTouch(event, x, y)
end

function EditorScene:onEnter()
    self.touchLayer_:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
    self.touchLayer_:setTouchEnabled(true)
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, handler(self, self.tick))
    self:scheduleUpdate()
end

function EditorScene:onExit()
    if self.mapRuntime_ then
        self.mapRuntime_:stopPlay()
    end

    self.objectInspector_:removeAllEventListeners()
    self.toolbar_:removeAllEventListeners()
end


function EditorScene:showStatusCurve()
    if not self.bgStatus_ then
        self.bgStatus_ = cc.LayerColor:create(cc.c4b(255, 255, 255, 80))
        self.bgStatus_:setContentSize(display.width, 60)
        self.bgStatus_:setTouchEnabled(false)
        self:addChild(self.bgStatus_)
    end
    self.bgStatus_:setVisible(true)

    self.fps_ = self.fps_ or {}
    if 0 == #self.fps_ then
        table.insert(self.fps_, cc.p(0, 0))
    end

    if not self.statusDraw_ then
        self.statusDraw_ = cc.NVGDrawNode:create():addTo(self.bgStatus_)
        self.statusDraw_:drawPolygon(self.fps_, #self.fps_, false, cc.c4f(1, 0, 0, 1))
    end
    self.statusDraw_:setVisible(true)

    self.objectsCount_ = self.objectsCount_ or {}
    if 0 == #self.objectsCount_ then
        table.insert(self.objectsCount_, cc.p(0, 0))
    end

    if not self.objectsDraw_ then
        self.objectsDraw_ = cc.NVGDrawNode:create():addTo(self.bgStatus_)
        self.objectsDraw_:drawPolygon(self.objectsCount_, #self.objectsCount_, false, cc.c4f(0, 0, 1, 1))
    end
    self.objectsDraw_:setVisible(true)

    if not self.statusLabel_ then
        self.statusLabel_ = cc.ui.UILabel.new({text = " ", size = 10, color = display.COLOR_BLACK})
        :align(display.CENTER_RIGHT, display.right - 10, 10)
        :addTo(self)
    end

    self.statusLabel_:setVisible(true)

    self.recordBtn_:setButtonLabel(cc.ui.UILabel.new({text = "统计中", size = 20, color = display.COLOR_BLACK}))
end

function EditorScene:disableStatus()
    if self.bgStatus_ then
        self.bgStatus_:setVisible(false)
    end
    if self.statusDraw_ then
        self.statusDraw_:setVisible(false)
    end
    if self.objectsDraw_ then
        self.objectsDraw_:setVisible(false)
    end
end

function EditorScene:addFPS()
    self.statusCount_ = self.statusCount_ + 1
    local deltaTime = cc.Director:getInstance():getDeltaTime()
    local fps = 1/deltaTime

    self.totalScore_ = self.totalScore_ + fps

    -- print(string.format("deltaTime:%f, fps:%d", deltaTime, fps))

    local pos = cc.p(display.left + display.width/60 * self.statusCount_, fps)
    table.insert(self.fps_, pos)
    self.statusDraw_:addPoint(pos)

    local count = table.nums(self.map_.objects_)
    pos = cc.p(display.left + display.width/60 * self.statusCount_, count)
    table.insert(self.objectsCount_, pos)
    self.objectsDraw_:addPoint(pos)

    self.statusLabel_:setString(string.format("Object:%d,FPS:%d", count, fps))

    if self.statusCount_ > 60 then
        self:statusTimerEnd()
    end
end

function EditorScene:statusTimerBegin()
    self.statusTimer_ = scheduler.scheduleGlobal(handler(self, self.addFPS), 1)
end

function EditorScene:statusTimerEnd()
    if not self.statusTimer_ then
        return
    end

    scheduler.unscheduleGlobal(self.statusTimer_)
    self.statusTimer_ = nil

    self:showResult()
end

--显示统计结果
function EditorScene:showResult()
    self.recordBtn_:setButtonLabel(cc.ui.UILabel.new({text = "统计运行状态", size = 20, color = display.COLOR_BLACK}))

    local dialogSize = cc.size(display.width/2, display.height/2)
    local bg = cc.LayerColor:create(cc.c4b(128, 128, 128, 200))
                :pos((display.width - dialogSize.width)/2, (display.height - dialogSize.height)/2)
                :addTo(self)
    bg:setContentSize(dialogSize.width, dialogSize.height)

    cc.ui.UILabel.new({text = "总分:", size = 24, color = display.COLOR_BLACK})
        :align(display.CENTER_RIGHT, dialogSize.width/2 - 10, dialogSize.height - 20)
        :addTo(bg)
    cc.ui.UILabel.new({text = string.format("%d", self.totalScore_), size = 24, color = display.COLOR_RED})
        :align(display.CENTER_LEFT, dialogSize.width/2 + 10, dialogSize.height - 20)
        :addTo(bg)

    self.resultDialog_ = bg
end

function EditorScene:disabelResult()
    self.resultDialog_:removeFromParent()
    self.resultDialog_ = nil
end

return EditorScene
