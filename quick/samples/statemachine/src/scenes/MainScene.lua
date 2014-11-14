
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    -- create Finite State Machine
    self.fsm_ = {}
    cc.GameObject.extend(self.fsm_)
        :addComponent("components.behavior.StateMachine")
        :exportMethods()

    self.fsm_:setupState({
        events = {
            {name = "start", from = "none",   to = "green" },
            {name = "warn",  from = "green",  to = "yellow"},
            {name = "panic", from = "green",  to = "red"   },
            {name = "panic", from = "yellow", to = "red"   },
            {name = "calm",  from = "red",    to = "yellow"},
            {name = "clear", from = "red",    to = "green" },
            {name = "clear", from = "yellow", to = "green" },
        },

        callbacks = {
            onbeforestart = function(event) self:log("[FSM] STARTING UP") end,
            onstart       = function(event) self:log("[FSM] READY") end,
            onbeforewarn  = function(event) self:log("[FSM] START   EVENT: warn!", true) end,
            onbeforepanic = function(event) self:log("[FSM] START   EVENT: panic!", true) end,
            onbeforecalm  = function(event) self:log("[FSM] START   EVENT: calm!",  true) end,
            onbeforeclear = function(event) self:log("[FSM] START   EVENT: clear!", true) end,
            onwarn        = function(event) self:log("[FSM] FINISH  EVENT: warn!") end,
            onpanic       = function(event) self:log("[FSM] FINISH  EVENT: panic!") end,
            oncalm        = function(event) self:log("[FSM] FINISH  EVENT: calm!") end,
            onclear       = function(event) self:log("[FSM] FINISH  EVENT: clear!") end,
            onleavegreen  = function(event) self:log("[FSM] LEAVE   STATE: green") end,
            onleaveyellow = function(event) self:log("[FSM] LEAVE   STATE: yellow") end,
            onleavered    = function(event)
                self:log("[FSM] LEAVE   STATE: red")
                self:pending(event, 3)
                self:performWithDelay(function()
                    self:pending(event, 2)
                    self:performWithDelay(function()
                        self:pending(event, 1)
                        self:performWithDelay(function()
                            self.pendingLabel_:setString("")
                            event.transition()
                        end, 1)
                    end, 1)
                end, 1)
                return "async"
            end,
            ongreen       = function(event) self:log("[FSM] ENTER   STATE: green") end,
            onyellow      = function(event) self:log("[FSM] ENTER   STATE: yellow") end,
            onred         = function(event) self:log("[FSM] ENTER   STATE: red") end,
            onchangestate = function(event) self:log("[FSM] CHANGED STATE: " .. event.from .. " to " .. event.to) end,
        },
    })

    -- create UI
    display.newColorLayer(cc.c4b(255, 255, 255, 255))
        :addTo(self)

    cc.ui.UILabel.new({
        text = "Finite State Machine",
        size = 32,
        color = display.COLOR_BLACK
    })
    :align(display.CENTER, display.cx, display.top - 60)
    :addTo(self)

    self.pendingLabel_ = cc.ui.UILabel.new({
        text = "",
        size = 32,
        color = display.COLOR_BLACK,
        x = display.cx,
        y = display.top - 620,
    })
    :align(display.CENTER)
    :addTo(self)

    -- preload texture
    self.stateImage_ = display.newSprite("#GreenState.png")
        :pos(display.cx, display.top - 300)
        :scale(1.5)
        :addTo(self)

    self.clearButton_ =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "clear", size = 32, color = display.COLOR_BLACK}))
            :onButtonClicked(function()
                if self.fsm_:canDoEvent("clear") then
                    self.fsm_:doEvent("clear")
                end
            end)
            :align(display.CENTER, display.cx - 150, display.top - 540)
            :addTo(self)

    self.calmButton_ =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "calm", size = 32, color = display.COLOR_BLACK}))
            :onButtonClicked(function()
                if self.fsm_:canDoEvent("calm") then
                    self.fsm_:doEvent("calm")
                end
            end)
            :align(display.CENTER, display.cx - 50, display.top - 540)
            :addTo(self)


    self.warnButton_ =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "warn", size = 32, color = display.COLOR_BLACK}))
            :onButtonClicked(function()
                if self.fsm_:canDoEvent("warn") then
                    self.fsm_:doEvent("warn")
                end
            end)
            :align(display.CENTER, display.cx + 50, display.top - 540)
            :addTo(self)

    self.panicButton_ =
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "panic", size = 32, color = display.COLOR_BLACK}))
            :onButtonClicked(function()
                if self.fsm_:canDoEvent("panic") then
                    self.fsm_:doEvent("panic")
                end
            end)
            :align(display.CENTER, display.cx + 150, display.top - 540)
            :addTo(self)

    -- debug
    self.logCount_ = 0
end

function MainScene:pending(event, n)
    local msg = event.to .. " in ..." .. n
    self:log("[FSM] PENDING STATE: " .. msg)
    self.pendingLabel_:setString(msg)
end

function MainScene:log(msg, separate)
    if separate then self.logCount_ = self.logCount_ + 1 end
    if separate then print("") end
    printf("%d: %s", self.logCount_, msg)

    local state = self.fsm_:getState()
    if state == "green" then
        self.stateImage_:setSpriteFrame(display.newSpriteFrame("GreenState.png"))
    elseif state == "red" then
        self.stateImage_:setSpriteFrame(display.newSpriteFrame("RedState.png"))
    elseif state == "yellow" then
        self.stateImage_:setSpriteFrame(display.newSpriteFrame("YellowState.png"))
    end

    -- self.clearButton_:setEnabled(self.fsm_:canDoEvent("clear"))
    -- self.calmButton_:setEnabled(self.fsm_:canDoEvent("calm"))
    -- self.warnButton_:setEnabled(self.fsm_:canDoEvent("warn"))
    -- self.panicButton_:setEnabled(self.fsm_:canDoEvent("panic"))
end

function MainScene:onEnter()
    self.fsm_:doEvent("start")
end

return MainScene
