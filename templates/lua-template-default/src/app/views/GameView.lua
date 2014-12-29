
-- GameView is a combination of view and controller
local GameView = class("GameView", cc.load("mvc").ViewBase)

local BugBase   = import("..models.BugBase")
local BugAnt    = import("..models.BugAnt")
local BugSpider = import("..models.BugSpider")

local BugSprite = import(".BugSprite")
local DeadBugSprite = import(".DeadBugSprite")

GameView.HOLE_POSITION = cc.p(display.cx - 30, display.cy - 75)
GameView.INIT_LIVES = 5
GameView.ADD_BUG_INTERVAL_MIN = 1
GameView.ADD_BUG_INTERVAL_MAX = 3

GameView.IMAGE_FILENAMES = {}
GameView.IMAGE_FILENAMES[BugBase.BUG_TYPE_ANT] = "BugAnt.png"
GameView.IMAGE_FILENAMES[BugBase.BUG_TYPE_SPIDER] = "BugSpider.png"

GameView.BUG_ANIMATION_TIMES = {}
GameView.BUG_ANIMATION_TIMES[BugBase.BUG_TYPE_ANT] = 0.15
GameView.BUG_ANIMATION_TIMES[BugBase.BUG_TYPE_SPIDER] = 0.1

GameView.ZORDER_BUG = 100
GameView.ZORDER_DEAD_BUG = 50

GameView.events = {
    PLAYER_DEAD_EVENT = "PLAYER_DEAD_EVENT",
}

function GameView:start()
    self:scheduleUpdate(handler(self, self.step))
    return self
end

function GameView:stop()
    self:unscheduleUpdate()
    return self
end

function GameView:step(dt)
    if self.lives_ <= 0 then return end

    self.addBugInterval_ = self.addBugInterval_ - dt
    if self.addBugInterval_ <= 0 then
        self.addBugInterval_ = math.random(GameView.ADD_BUG_INTERVAL_MIN, GameView.ADD_BUG_INTERVAL_MAX)
        self:addBug()
    end

    for _, bug in pairs(self.bugs_) do
        bug:step(dt)
        if bug:getModel():getDist() <= 0 then
            self:bugEnterHole(bug)
        end
    end

    return self
end

function GameView:getLives()
    return self.lives_
end

function GameView:getKills()
    return self.kills_
end

function GameView:addBug()
    local bugType = BugBase.BUG_TYPE_ANT
    if math.random(1, 2) % 2 == 0 then
        bugType = BugBase.BUG_TYPE_SPIDER
    end

    local bugModel
    if bugType == BugBase.BUG_TYPE_ANT then
        bugModel = BugAnt:create()
    else
        bugModel = BugSpider:create()
    end

    local bug = BugSprite:create(GameView.IMAGE_FILENAMES[bugType], bugModel)
        :start(GameView.HOLE_POSITION)
        :addTo(self.bugsNode_, GameView.ZORDER_BUG)

    self.bugs_[bug] = bug
    return self
end

function GameView:bugEnterHole(bug)
    self.bugs_[bug] = nil

    bug:fadeOut({time = 0.5, removeSelf = true})
        :scaleTo({time = 0.5, scale = 0.3})
        :rotateTo({time = 0.5, rotation = math.random(360, 720)})

    self.lives_ = self.lives_ - 1
    self.livesLabel_:setString(self.lives_)
    audio.playSound("BugEnterHole.wav")

    if self.lives_ <= 0 then
        self:dispatchEvent({name = GameView.events.PLAYER_DEAD_EVENT})
    end

    return self
end

function GameView:bugDead(bug)
    local imageFilename = GameView.IMAGE_FILENAMES[bug:getModel():getType()]
    DeadBugSprite:create(imageFilename)
        :fadeOut({time = 2.0, delay = 0.5, removeSelf = true})
        :move(bug:getPosition())
        :rotate(bug:getRotation() + 120)
        :addTo(self.bugsNode_, GameView.ZORDER_DEAD_BUG)

    self.bugs_[bug] = nil
    bug:removeSelf()

    self.kills_ = self.kills_ + 1
    audio.playSound("BugDead.wav")

    return self
end

function GameView:onCreate()
    self.lives_ = GameView.INIT_LIVES
    self.kills_ = 0
    self.bugs_ = {}
    self.addBugInterval_ = 0

    -- add touch layer
    display.newLayer()
        :onTouch(handler(self, self.onTouch))
        :addTo(self)

    -- add background image
    display.newSprite("PlaySceneBg.jpg")
        :move(display.center)
        :addTo(self)

    -- add bugs node
    self.bugsNode_ = display.newNode():addTo(self)

    -- add lives icon and label
    display.newSprite("Star.png")
        :move(display.left + 50, display.top - 50)
        :addTo(self)
    self.livesLabel_ = cc.Label:createWithSystemFont(self.lives_, "Arial", 32)
        :move(display.left + 90, display.top - 50)
        :addTo(self)

    -- create animation for bugs
    for bugType, filename in pairs(GameView.IMAGE_FILENAMES) do
        -- load image
        local texture = display.loadImage(filename)
        local frameWidth = texture:getPixelsWide() / 3
        local frameHeight = texture:getPixelsHigh()

        -- create sprite frame based on image
        local frames = {}
        for i = 0, 1 do
            local frame = display.newSpriteFrame(texture, cc.rect(frameWidth * i, 0, frameWidth, frameHeight))
            frames[#frames + 1] = frame
        end

        -- create animation
        local animation = display.newAnimation(frames, GameView.BUG_ANIMATION_TIMES[bugType])
        -- caching animation
        display.setAnimationCache(filename, animation)
    end

    -- bind the "event" component
    cc.bind(self, "event")
end

function GameView:onTouch(event)
    if event.name ~= "began" then return end
    local x, y = event.x, event.y
    for _, bug in pairs(self.bugs_) do
        if bug:getModel():checkTouch(x, y) then
            self:bugDead(bug)
        end
    end
end

function GameView:onCleanup()
    self:removeAllEventListeners()
end

return GameView
