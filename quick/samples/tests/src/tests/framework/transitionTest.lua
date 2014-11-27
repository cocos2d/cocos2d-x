
local TransitionTestScene = game.createSceneClass("TransitionTestScene")

function TransitionTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "transiton test"
    })

    local items = {
        "Start",
        "Stop",
        "Pause",
        "Resume",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    self:init()
end

function TransitionTestScene:init()
    display.addSpriteFrames("grossini_blue.plist", "grossini_blue.png")
end

function TransitionTestScene:createCoins()

    if self.coins_ then
        for i,v in ipairs(self.coins_) do
            v:removeSelf()
        end
        self.coins_ = nil
    end

    if self.animates_ then
        for i,v in ipairs(self.animates_) do
            v:removeSelf()
        end
        self.animates_ = nil
    end

    local coins = {}
    local coinsCount = 10

    for i=1, coinsCount do
        coins[i] = display.newSprite("Coin0001.png"):addTo(self)
        coins[i]:setPositionX(display.width/coinsCount * (i - 0.5))
    end

    self.coins_ = coins

end

function TransitionTestScene:StartTest()
    self:createCoins()

    transition.execute(self.coins_[1], cc.MoveTo:create(1.5, cc.p(display.cx, display.cy)), {
        delay = 1.0,
        easing = "backout",
        onComplete = function()
            print("move completed")
        end,
    })

    -- 耗时 0.5 秒将 sprite 旋转到 180 度
    transition.rotateTo(self.coins_[2], {rotate = 180, time = 3})

    -- 移动到屏幕上边，不改变 x
    transition.moveTo(self.coins_[3], {y = display.top, time = 3})

    -- 向右移动 100 点，向上移动 100 点
    transition.moveBy(self.coins_[4], {x = 200, y = 400, time = 3})

    self.coins_[5]:setOpacity(0)
    transition.fadeIn(self.coins_[5], {time = 3})

    transition.fadeOut(self.coins_[6], {time = 3})

    -- 不管显示对象当前的透明度是多少，最终设置为 128
    transition.fadeTo(self.coins_[7], {opacity = 128, time = 3})

    -- 整体缩放为 50%
    transition.scaleTo(self.coins_[8], {scale = 0.5, time = 3})

    local sequence = transition.sequence({
        cc.MoveTo:create(1.0, cc.p(display.cx, display.cy)),
        cc.FadeOut:create(0.8),
        cc.DelayTime:create(0.2),
        cc.FadeIn:create(1.0)
    })
    self.coins_[9]:runAction(sequence)

    local action = transition.moveTo(self.coins_[10], {time = 4.0, x = 100, y = 300})
    local scheduler = require("framework.scheduler")
    scheduler.performWithDelayGlobal(
        function()
            transition.removeAction(action)
            print("action removed")
        end,
        2)

    local frames = display.newFrames("grossini_blue_%02d.png", 1, 4)
    local man = display.newSprite(frames[1])
                    :pos(300, 350)
                    :addTo(self)
    -- playAnimationOnce() 第二个参数为 true 表示动画播放完后删除 boom 这个 Sprite 对象
    man:playAnimationOnce(display.newAnimation(frames, 0.3/ 4))

    frames = display.newFrames("grossini_blue_%02d.png", 1, 4)
    local manForver = display.newSprite(frames[1])
                    :pos(400, 350)
                    :addTo(self)
    manForver:playAnimationForever(display.newAnimation(frames, 0.5 / 4))

    self.animates_ = {}
    self.animates_[1] = man
    self.animates_[2] = manForver


end

function TransitionTestScene:StopTest()
    for i,v in ipairs(self.coins_) do
        transition.stopTarget(v)
    end

    for i,v in ipairs(self.animates_) do
        transition.stopTarget(v)
    end
end

function TransitionTestScene:PauseTest()
    for i,v in ipairs(self.coins_) do
        transition.pauseTarget(v)
    end

    for i,v in ipairs(self.animates_) do
        transition.pauseTarget(v)
    end
end

function TransitionTestScene:ResumeTest()
    for i,v in ipairs(self.coins_) do
        transition.resumeTarget(v)
    end

    for i,v in ipairs(self.animates_) do
        transition.resumeTarget(v)
    end
end


return TransitionTestScene
