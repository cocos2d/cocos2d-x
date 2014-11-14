-- 主场景类
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

local Timer = require("utils.Timer")

--[[
构造函数
]]
function MainScene:ctor()
    -- 创建背景层
    local sprite = display.newTilesSprite("bgTile.png")
    self:addChild(sprite)

    -- touchLayer 用于接收触摸事件
    self.touchLayer = display.newLayer()
    self:addChild(self.touchLayer)

    -- 最大zOrder
    self.MAX_ZORDER = 99999

    -- topBar背景
    local topBarBg = display.newSprite("topBarBg.png", display.left, display.top - 10)
    topBarBg:setScaleX((display.width / topBarBg:getContentSize().width) * 2)
    self:addChild(topBarBg, self.MAX_ZORDER - 1)

    -- topBar标签
    local label = cc.LabelTTF:create("loading...", "Courier New", 16);
    label:setColor(cc.c3b(255, 255, 255))
    label:setPosition(display.cx, display.top - 10)
    self:addChild(label, self.MAX_ZORDER)
    self.label = label

    -- 创建stage批渲染结点
    self.stageNode = display.newBatchNode("stage.png", 100)
    self:addChild(self.stageNode)

    -- 创建player批渲染结点
    self.playerNode = display.newBatchNode("player.png", 100000)
    self:addChild(self.playerNode)

    self.resIds = {
        "player_f0006","player_f0015","player_f0016","player_f0018","player_f0021",
        "player_f0025","player_f0026","player_f0032","player_f0033","player_f0037",
        "player_f0038","player_f0046","player_f0057","player_f0067","player_f0068",
        "player_f0069","player_f0070","player_f0073","player_f0208","player_f0209",
    }
    self.actionNames = {"dance_a_1", "dance_a_2", "stand_1", "stand_2", "walk_1", "walk_2"}
    self.actionNums = {8, 8, 4, 4, 8, 8}
    self.objs = {}
    self.frame = 0
    self.VERSION = require("version")
end

--[[
生成Object
@param resId
@param actionId
@param x
@param y
@param isFixed
]]
function MainScene:genObject(resId, actionId, x, y, isFixed)
    local frames = display.newFrames(resId .. "_" .. self.actionNames[actionId] .."_%02d.png", 1, self.actionNums[actionId])
    local sprite = display.newSprite(frames[1], x, y)
    -- 一定概率水平翻转
    if math.random(1, 2) == 1 then
        sprite:setFlippedX(true)
    end
    if isFixed == nil then
        self.objs[#self.objs + 1] = sprite
    end
    -- 添加到player批渲染结点
    self.playerNode:addChild(sprite, self.MAX_ZORDER - y);
    -- 创建动画
    local animation = display.newAnimation(frames, math.random(1, 2) / 15)
    -- 播放动画
    sprite:playAnimationForever(animation)
end

--[[
生成对象
@param num
]]
function MainScene:genObjects(num)
    for i = 1, num do
        local rand1 = math.random(1, #self.resIds)
        local actionId = math.random(1, #self.actionNames)
        local x = math.random(15, display.width - 15)
        local y = math.random(120, display.height - 75)
        self:genObject(self.resIds[rand1], actionId, x, y)
    end
end

--[[
移动对象
@param x
@param y
]]
function MainScene:moveObjects(x, y)
    for k, v in pairs(self.objs) do
        if math.random(1, 5) == 1 then
            local action = cc.MoveTo:create(math.random(1, 5), cc.p(x, y))
            v:runAction(action)
        end
    end
end

--[[
后成舞台对象
@param x
@param y
]]
function MainScene:genStageObject(x, y)
    local frames = display.newFrames("bg%02d.png", 1, 4);
    local sprite = display.newSprite(frames[1], x, y)
    self.stageNode:addChild(sprite);
    local animation = display.newAnimation(frames, math.random(1, 2) / 10)
    sprite:playAnimationForever(animation)
end

--[[
生成初始对象
]]
function MainScene:genInitObjects()
    local ofstX = 58
    local ofstY = 112
    for i = 0, 8 do
        self:genStageObject(ofstX + i * 105, ofstY)
        local rand1 = math.random(1, #self.resIds)
        self:genObject(self.resIds[rand1], 1, ofstX + i * 105, ofstY - 15, true)
    end
end

--[[
touch事件处理函数
@param event
@param x
@param y
]]
function MainScene:onTouch(event, x, y)
    if y > display.top - 20 then
        self:genObjects(100)
        return false
    end
    self:moveObjects(x, y)
    return false
end

--[[
帧事件处理函数
@param dt
]]
function MainScene:updateFrame(dt)
    self.frame = self.frame + 1
    if self.frame % 5 == 0 then -- 更新top bar文字
        local str = "Object=%d FPS=%0.2f DT=%0.6f (Touch top bar to increase object) - Version %s"
        self.label:setString(string.format(str, self.playerNode:getChildrenCount(), 1 / dt, dt, self.VERSION))
        self.label:setPosition(display.cx, display.top - 10)
    end

    for k, v in pairs(self.objs) do -- 更改显示层级
        self.playerNode:reorderChild(v, self.MAX_ZORDER - v:getPositionY())
    end
end

--[[
进入场景
]]
function MainScene:onEnter()
    Timer:runOnce(function()
        -- 播放背景音乐
        audio.playMusic(MUSIC.backgroundMusic, true)
        -- 加载plist
        display.addSpriteFrames("stage.plist", "stage.png")
        display.addSpriteFrames("player.plist", "player.png")
        -- 创建object
        self:genInitObjects()
        self:genObjects(91)
        -- 注册touch事件处理函数
        self.touchLayer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
            return self:onTouch(event.name, event.x, event.y)
        end)
        self.touchLayer:setTouchEnabled(true)
        -- 注册帧事件处理函数
        self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt) self:updateFrame(dt) end)
        self:scheduleUpdate()

    end)
end

return MainScene
