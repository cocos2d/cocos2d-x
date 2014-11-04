--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

为图像创造效果

]]
local transition = {}

local ACTION_EASING = {}
ACTION_EASING["BACKIN"]           = {cc.EaseBackIn, 1}
ACTION_EASING["BACKINOUT"]        = {cc.EaseBackInOut, 1}
ACTION_EASING["BACKOUT"]          = {cc.EaseBackOut, 1}
ACTION_EASING["BOUNCE"]           = {cc.EaseBounce, 1}
ACTION_EASING["BOUNCEIN"]         = {cc.EaseBounceIn, 1}
ACTION_EASING["BOUNCEINOUT"]      = {cc.EaseBounceInOut, 1}
ACTION_EASING["BOUNCEOUT"]        = {cc.EaseBounceOut, 1}
ACTION_EASING["ELASTIC"]          = {cc.EaseElastic, 2, 0.3}
ACTION_EASING["ELASTICIN"]        = {cc.EaseElasticIn, 2, 0.3}
ACTION_EASING["ELASTICINOUT"]     = {cc.EaseElasticInOut, 2, 0.3}
ACTION_EASING["ELASTICOUT"]       = {cc.EaseElasticOut, 2, 0.3}
ACTION_EASING["EXPONENTIALIN"]    = {cc.EaseExponentialIn, 1}
ACTION_EASING["EXPONENTIALINOUT"] = {cc.EaseExponentialInOut, 1}
ACTION_EASING["EXPONENTIALOUT"]   = {cc.EaseExponentialOut, 1}
ACTION_EASING["IN"]               = {cc.EaseIn, 2, 1}
ACTION_EASING["INOUT"]            = {cc.EaseInOut, 2, 1}
ACTION_EASING["OUT"]              = {cc.EaseOut, 2, 1}
ACTION_EASING["RATEACTION"]       = {cc.EaseRateAction, 2, 1}
ACTION_EASING["SINEIN"]           = {cc.EaseSineIn, 1}
ACTION_EASING["SINEINOUT"]        = {cc.EaseSineInOut, 1}
ACTION_EASING["SINEOUT"]          = {cc.EaseSineOut, 1}

local actionManager = cc.Director:getInstance():getActionManager()

--[[--

创建一个缓动效果

@param Action action     动作对象
@param string easingName 缓冲效果的名字, 具体参考 transition.execute() 方法
@param mixed  more       创建缓冲效果的参数

@return mixed 结果

]]
function transition.newEasing(action, easingName, more)
    local key = string.upper(tostring(easingName))
    if string.sub(key, 1, 6) == "CCEASE" then
        key = string.sub(key, 7)
    end
    local easing
    if ACTION_EASING[key] then
        local cls, count, default = unpack(ACTION_EASING[key])
        if count == 2 then
            easing = cls:create(action, more or default)
        else
            easing = cls:create(action)
        end
    end
    return easing or action
end

--[[--

创建一个动作效果

@param Action action 动作对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.create(action, args)
    args = checktable(args)
    if args.easing then
        if type(args.easing) == "table" then
            action = transition.newEasing(action, unpack(args.easing))
        else
            action = transition.newEasing(action, args.easing)
        end
    end

    local actions = {}
    local delay = checknumber(args.delay)
    if delay > 0 then
        actions[#actions + 1] = cc.DelayTime:create(delay)
    end
    actions[#actions + 1] = action

    local onComplete = args.onComplete
    if type(onComplete) ~= "function" then onComplete = nil end
    if onComplete then
        actions[#actions + 1] = cc.CallFunc:create(onComplete)
    end

    if #actions > 1 then
        return transition.sequence(actions)
    else
        return actions[1]
    end
end

--[[--

执行一个动作效果

~~~ lua

-- 等待 1.0 后开始移动对象
-- 耗时 1.5 秒，将对象移动到屏幕中央
-- 移动使用 backout 缓动效果
-- 移动结束后执行函数，显示 move completed
transition.execute(sprite, MoveTo:create(1.5, cc.p(display.cx, display.cy)), {
    delay = 1.0,
    easing = "backout",
    onComplete = function()
        print("move completed")
    end,
})

~~~

transition.execute() 是一个强大的工具，可以为原本单一的动作添加各种附加特性。

transition.execute() 的参数表格支持下列参数：

-    delay: 等待多长时间后开始执行动作
-    easing: 缓动效果的名字及可选的附加参数，效果名字不区分大小写
-    onComplete: 动作执行完成后要调用的函数
-    time: 执行动作需要的时间

transition.execute() 支持的缓动效果：

-    backIn
-    backInOut
-    backOut
-    bounce
-    bounceIn
-    bounceInOut
-    bounceOut
-    elastic, 附加参数默认为 0.3
-    elasticIn, 附加参数默认为 0.3
-    elasticInOut, 附加参数默认为 0.3
-    elasticOut, 附加参数默认为 0.3
-    exponentialIn, 附加参数默认为 1.0
-    exponentialInOut, 附加参数默认为 1.0
-    exponentialOut, 附加参数默认为 1.0
-    In, 附加参数默认为 1.0
-    InOut, 附加参数默认为 1.0
-    Out, 附加参数默认为 1.0
-    rateaction, 附加参数默认为 1.0
-    sineIn
-    sineInOut
-    sineOut

@param cc.Node target 显示对象
@param Action action 动作对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.execute(target, action, args)
    assert(not tolua.isnull(target), "transition.execute() - target is not cc.Node")
    local action = transition.create(action, args)
    target:runAction(action)
    return action
end

--[[--

将显示对象旋转到指定角度，并返回 Action 动作对象。

~~~ lua

-- 耗时 0.5 秒将 sprite 旋转到 180 度
transition.rotateTo(sprite, {rotate = 180, time = 0.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.rotateTo(target, args)
    assert(not tolua.isnull(target), "transition.rotateTo() - target is not cc.Node")
    -- local rotation = args.rotate
    local action = cc.RotateTo:create(args.time, args.rotate)
    return transition.execute(target, action, args)
end

--[[--

将显示对象移动到指定位置，并返回 Action 动作对象。

~~~ lua

-- 移动到屏幕中心
transition.moveTo(sprite, {x = display.cx, y = display.cy, time = 1.5})
-- 移动到屏幕左边，不改变 y
transition.moveTo(sprite, {x = display.left, time = 1.5})
-- 移动到屏幕底部，不改变 x
transition.moveTo(sprite, {y = display.bottom, time = 1.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.moveTo(target, args)
    assert(not tolua.isnull(target), "transition.moveTo() - target is not cc.Node")
    local tx, ty = target:getPosition()
    local x = args.x or tx
    local y = args.y or ty
    local action = cc.MoveTo:create(args.time, cc.p(x, y))
    return transition.execute(target, action, args)
end

--[[--

将显示对象移动一定距离，并返回 Action 动作对象。

~~~ lua

-- 向右移动 100 点，向上移动 100 点
transition.moveBy(sprite, {x = 100, y = 100, time = 1.5})
-- 向左移动 100 点，不改变 y
transition.moveBy(sprite, {x = -100, time = 1.5})
-- 向下移动 100 点，不改变 x
transition.moveBy(sprite, {y = -100, time = 1.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.moveBy(target, args)
    assert(not tolua.isnull(target), "transition.moveBy() - target is not cc.Node")
    local x = args.x or 0
    local y = args.y or 0
    local action = cc.MoveBy:create(args.time, cc.p(x, y))
    return transition.execute(target, action, args)
end

--[[--

淡入显示对象，并返回 Action 动作对象。

fadeIn 操作会首先将对象的透明度设置为 0（0%，完全透明），然后再逐步增加为 255（100%，完全不透明）。

如果不希望改变对象当前的透明度，应该用 fadeTo()。

~~~ lua

action = transition.fadeIn(sprite, {time = 1.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.fadeIn(target, args)
    assert(not tolua.isnull(target), "transition.fadeIn() - target is not cc.Node")
    local action = cc.FadeIn:create(args.time)
    return transition.execute(target, action, args)
end

--[[--

淡出显示对象，并返回 Action 动作对象。

fadeOut 操作会首先将对象的透明度设置为 255（100%，完全不透明），然后再逐步减少为 0（0%，完全透明）。

如果不希望改变对象当前的透明度，应该用 fadeTo()。

~~~ lua

action = transition.fadeOut(sprite, {time = 1.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.fadeOut(target, args)
    assert(not tolua.isnull(target), "transition.fadeOut() - target is not cc.Node")
    local action = cc.FadeOut:create(args.time)
    return transition.execute(target, action, args)
end

--[[--

将显示对象的透明度改变为指定值，并返回 Action 动作对象。

~~~ lua

-- 不管显示对象当前的透明度是多少，最终设置为 128
transition.fadeTo(sprite, {opacity = 128, time = 1.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.fadeTo(target, args)
    assert(not tolua.isnull(target), "transition.fadeTo() - target is not cc.Node")
    local opacity = checkint(args.opacity)
    if opacity < 0 then
        opacity = 0
    elseif opacity > 255 then
        opacity = 255
    end
    local action = cc.FadeTo:create(args.time, opacity)
    return transition.execute(target, action, args)
end

--[[--

将显示对象缩放到指定比例，并返回 Action 动作对象。

~~~ lua

-- 整体缩放为 50%
transition.scaleTo(sprite, {scale = 0.5, time = 1.5})
-- 单独水平缩放
transition.scaleTo(sprite, {scaleX = 0.5, time = 1.5})
-- 单独垂直缩放
transition.scaleTo(sprite, {scaleY = 0.5, time = 1.5})

~~~

@param cc.Node target 显示对象
@param table args 参数表格对象

@return mixed 结果

]]
function transition.scaleTo(target, args)
    assert(not tolua.isnull(target), "transition.scaleTo() - target is not cc.Node")
    local action
    if args.scale then
        action = cc.ScaleTo:create(checknumber(args.time), checknumber(args.scale))
    elseif args.scaleX or args.scaleY then
        local scaleX, scaleY
        if args.scaleX then
            scaleX = checknumber(args.scaleX)
        else
            scaleX = target:getScaleX()
        end
        if args.scaleY then
            scaleY = checknumber(args.scaleY)
        else
            scaleY = target:getScaleY()
        end
        action = cc.ScaleTo:create(checknumber(args.time), scaleX, scaleY)
    end
    return transition.execute(target, action, args)
end

--[[--

创建一个动作序列对象。

~~~ lua

local sequence = transition.sequence({
    cc.MoveTo:create(0.5, cc.p(display.cx, display.cy)),
    cc.FadeOut:create(0.2),
    cc.DelayTime:create(0.5),
    cc.FadeIn:create(0.3),
})
sprite:runAction(sequence)

~~~

@param table args 动作的表格对象

@return Sequence 动作序列对象

]]
function transition.sequence(actions)
    if #actions < 1 then return end
    if #actions < 2 then return actions[1] end

    local prev = actions[1]
    for i = 2, #actions do
        prev = cc.Sequence:create(prev, actions[i])
    end
    return prev
end

--[[--

在显示对象上播放一次动画，并返回 Action 动作对象。

~~~ lua

local frames = display.newFrames("Walk%04d.png", 1, 20)
local animation = display.newAnimation(frames, 0.5 / 20) -- 0.5s play 20 frames
transition.playAnimationOnce(sprite, animation)

~~~

还可以用 Sprite 对象的 playAnimationOnce() 方法来直接播放动画：

~~~ lua

local frames = display.newFrames("Walk%04d.png", 1, 20)
local animation = display.newAnimation(frames, 0.5 / 20) -- 0.5s play 20 frames
sprite:playAnimationOnce(animation)

~~~

playAnimationOnce() 提供了丰富的功能，例如在动画播放完成后就删除用于播放动画的 Sprite 对象。例如一个爆炸效果：

~~~ lua

local frames = display.newFrames("Boom%04d.png", 1, 8)
local boom = display.newSprite(frames[1])

-- playAnimationOnce() 第二个参数为 true 表示动画播放完后删除 boom 这个 Sprite 对象
-- 这样爆炸动画播放完毕，就自动清理了不需要的显示对象
boom:playAnimationOnce(display.newAnimation(frames, 0.3/ 8), true)

~~~

此外，playAnimationOnce() 还允许在动画播放完成后执行一个指定的函数，以及播放动画前等待一段时间。合理运用这些功能，可以大大简化我们的游戏代码。

@param cc.Node target 显示对象
@param cc.Node animation 动作对象
@param boolean removeWhenFinished 播放完成后删除显示对象
@param function onComplete 播放完成后要执行的函数
@param number delay 播放前等待的时间

@return table 动作表格对象

]]
function transition.playAnimationOnce(target, animation, removeWhenFinished, onComplete, delay)
    local actions = {}
    if type(delay) == "number" and delay > 0 then
        target:setVisible(false)
        actions[#actions + 1] = cc.DelayTime:create(delay)
        actions[#actions + 1] = cc.Show:create()
    end

    actions[#actions + 1] = cc.Animate:create(animation)

    if removeWhenFinished then
        actions[#actions + 1] = cc.RemoveSelf:create()
    end
    if onComplete then
        actions[#actions + 1] = cc.CallFunc:create(onComplete)
    end

    local action
    if #actions > 1 then
        action = transition.sequence(actions)
    else
        action = actions[1]
    end
    target:runAction(action)
    return action
end

--[[--

在显示对象上循环播放动画，并返回 Action 动作对象。

~~~ lua

local frames = display.newFrames("Walk%04d.png", 1, 20)
local animation = display.newAnimation(frames, 0.5 / 20) -- 0.5s play 20 frames
sprite:playAnimationForever(animation)

~~~

@param cc.Node target 显示对象
@param cc.Node animation 动作对象
@param number delay 播放前等待的时间

@return table 动作表格对象

]]
function transition.playAnimationForever(target, animation, delay)
    local animate = cc.Animate:create(animation)
    local action
    if type(delay) == "number" and delay > 0 then
        target:setVisible(false)
        local sequence = transition.sequence({
            cc.DelayTime:create(delay),
            cc.Show:create(),
            animate,
        })
        action = cc.RepeatForever:create(sequence)
    else
        action = cc.RepeatForever:create(animate)
    end
    target:runAction(action)
    return action
end

--[[--

停止一个正在执行的动作

~~~ lua

-- 开始移动
local action = transition.moveTo(sprite, {time = 2.0, x = 100, y = 100})
....
transition.removeAction(action) -- 停止移动

~~~

@param mixed target

]]
function transition.removeAction(action)
    if not tolua.isnull(action) then
        actionManager:removeAction(action)
    end
end

--[[--

停止一个显示对象上所有正在执行的动作

~~~ lua

-- 开始移动
transition.moveTo(sprite, {time = 2.0, x = 100, y = 100})
transition.fadeOut(sprite, {time = 2.0})
....
transition.stopTarget(sprite)

~~~

注意:显示对象的 performWithDelay() 方法是用动作来实现延时回调操作的，所以如果停止显示对象上的所有动作，会清除该对象上的延时回调操作。

@param mixed target

]]
function transition.stopTarget(target)
    if not tolua.isnull(target) then
        actionManager:removeAllActionsFromTarget(target)
    end
end

--[[--

暂停显示对象上所有正在执行的动作

@param mixed target

]]
function transition.pauseTarget(target)
    if not tolua.isnull(target) then
        actionManager:pauseTarget(target)
    end
end

--[[--

恢复显示对象上所有暂停的动作

@param mixed target

]]
function transition.resumeTarget(target)
    if not tolua.isnull(target) then
        actionManager:resumeTarget(target)
    end
end

return transition
