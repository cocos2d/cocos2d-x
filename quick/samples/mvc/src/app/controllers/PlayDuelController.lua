
local Hero = import("..models.Hero")

local PlayDuelController = class("PlayDuelController", function()
    return display.newNode()
end)

function PlayDuelController:ctor()
    if not app:isObjectExists("player") then
        -- player 对象只有一个，不需要每次进入场景都创建
        local player = Hero.new({
            id = "player",
            nickname = "dualface",
            level = 1,
        })
        app:setObject("player", player)
        print("create player")
    end
    self.player = app:getObject("player")

    self.enemy = Hero.new({
        id = "enemy",
        nickname = "lurenjia",
        level = 1,
    })

    self.views_ = {}
    self.bullets_ = {}

    self.views_[self.player] = app:createView("HeroView", self.player)
        :pos(display.cx - 300, display.cy)
        :addTo(self)

    self.views_[self.enemy] = app:createView("HeroView", self.enemy)
        :pos(display.cx + 300, display.cy)
        :flipX(true)
        :addTo(self)

    ----

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonSize(160, 80)
        :setButtonLabel(cc.ui.UILabel.new({text = "fire"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.1)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function()
            self:fire(self.player, self.enemy)
        end)
        :pos(display.cx - 300, display.bottom + 100)
        :addTo(self)


    cc.ui.UIPushButton.new("Button02.png", {scale9 = true})
        :setButtonSize(160, 80)
        :setButtonLabel(cc.ui.UILabel.new({text = "fire"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.1)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function()
            self:fire(self.enemy, self.player)
        end)
        :pos(display.cx + 300, display.bottom + 100)
        :addTo(self)

    -- 注册帧事件
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, handler(self, self.tick))
    self:scheduleUpdate()

    -- 在视图清理后，检查模型上注册的事件，看看是否存在内存泄露
    self:addNodeEventListener(cc.NODE_EVENT, function(event)
        if event.name == "exit" then
            self.player:getComponent("components.behavior.EventProtocol"):dumpAllEventListeners()
        end
    end)
end

function PlayDuelController:fire(attacker, target)
    if not attacker:canFire() then return end

    attacker:fire() -- 开火后，需要冷却一定时间才能再次开火

    -- 创建子弹图像，并设置起始位置和飞行方向
    local bullet = display.newSprite("#Bullet.png"):addTo(self)
    local view = self.views_[attacker]
    local x, y = view:getPosition()
    y = y + 12
    if view:isFlipX() then
        x = x - 44
        bullet.speed = -5
    else
        x = x + 44
        bullet.speed = 5
    end
    bullet:pos(x, y)

    bullet.attacker = attacker
    bullet.target = target
    self.bullets_[#self.bullets_ + 1] = bullet

    self:InterfaceTest()
end

-- 只是单纯为了检查接口用,与样例功能无关
function PlayDuelController:InterfaceTest()
    local proper = self.player:getProperties({"hp", "level"})
    dump(proper, "proper:")
    local id = self.player:getId()
    print("id:" .. id)
    local bValid = self.player:isValidId()
    print("valid id:" .. tostring(bValid))
end

function PlayDuelController:hit(attacker, target, bullet)
    if not target:isDead() then
        local damage = attacker:hit(target)
        if damage <= 0 then
            local miss = display.newSprite("#Miss.png")
                :pos(bullet:getPosition())
                :addTo(self, 1000)
            transition.moveBy(miss, {y = 100, time = 1.5, onComplete = function()
                miss:removeSelf()
            end})
        end
        return damage > 0
    else
        return false
    end
end

-- 求两点间距离
local function dist(ax, ay, bx, by)
    local dx, dy = bx - ax, by - ay
    return math.sqrt(dx * dx + dy * dy)
end

function PlayDuelController:tick(dt)
    for index = #self.bullets_, 1, -1 do
        local bullet = self.bullets_[index]
        local x, y = bullet:getPosition()
        x = x + bullet.speed
        bullet:setPositionX(x)

        if x < display.left - 100 or x > display.right + 100 then
            bullet:removeSelf()
            table.remove(self.bullets_, index)
        elseif bullet.target then
            local targetView = self.views_[bullet.target]
            local tx, ty = targetView:getPosition()
            if dist(x, y, tx, ty) <= 30 then
                if self:hit(bullet.attacker, bullet.target, bullet) then
                    bullet:removeSelf()
                    table.remove(self.bullets_, index)
                else
                    bullet.target = nil
                end
            end
        end
    end
end

return PlayDuelController
