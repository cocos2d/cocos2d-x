local cca = {}
_G.cca = cca -- make it global

function cc.Action:addTo(node)
   node:runAction(self)
   return self
end

function cc.Node:buildAction(...)
   local builder = cca.builder(...)
   builder.target = self
   return builder
end

-- instant

function cca.show()
   return cc.Show:create()
end

function cca.hide()
   return cc.Hide:create()
end

function cca.toggle()
   return cc.ToggleVisibility:create()
end

function cca.removeSelf()
   return cc.RemoveSelf:create()
end

function cca.flipX(x)
   return cc.FlipX:create(x)
end

function cca.flipY(y)
   return cc.FlipY:create(y)
end

function cca.place(x, y)
   return cc.Place:create(cc.p(x, y))
end

function cca.callFunc(cb)
   if cb then return cc.CallFunc:create(cb) end
   return false
end

function cca.callFuncN(cb)
   if cb then return cc.CallFuncN:create(cb) end
   return false
end


-- interval

function cca.rotateTo(dt, ...)
   return cc.RotateTo:create(dt, ...)
end

function cca.rotateBy(dt, ...)
   return cc.RotateBy:create(dt, ...)
end

function cca.moveTo(dt, x, y)
   if y then x = cc.p(x, y) end
   return cc.MoveTo:create(dt, x)
end

function cca.moveBy(dt, dx, dy)
   if dy then dx = cc.p(dx, dy) end
   return cc.MoveBy:create(dt, dx)
end

function cca.skewTo(dt, x, y)
   if y then x = cc.p(x, y) end
   return cc.SkewTo:create(dt, x)
end

function cca.skewBy(dt, dx, dy)
   if dy then dx = cc.p(dx, dy) end
   return cc.SkewBy:create(dt, dx)
end

function cca.jumpTo(dt, x, y, height, count)
   if y then x = cc.p(x, y) end
   return cc.JumpTo:create(dt, x, height, count)
end

function cca.jumpBy(dt, x, y, height, count)
   if y then x = cc.p(x, y) end
   return cc.JumpBy:create(dt, x, height, count)
end

function cca.bezierTo(dt, c1, c2, p2)
   self[1] = c1
   self[2] = c2
   self[3] = p2
   return cc.BezierTo:create(dt, self)
end

function cca.bezierBy(dt, c1, c2, p2)
   self[1] = c1
   self[2] = c2
   self[3] = p2
   return cc.BezierBy:create(dt, self)
end

function cca.splineTo(dt, points)
   return cc.CardinalSplineTo:create(dt, points)
end

function cca.splineBy(dt, points)
   return cc.CardinalSplineBy:create(dt, points)
end

function cca.romTo(dt, points)
   return cc.CardinalRomBy:create(dt, points)
end

function cca.romBy(dt, points)
   return cc.CardinalRomBy:create(dt, points)
end

function cca.scaleTo(dt, ...)
   return cc.ScaleTo:create(dt, ...)
end

function cca.scaleBy(dt, ...)
   return cc.ScaleBy:create(dt, ...)
end

function cca.blink(dt, count)
   return cc.Blink:create(dt, count)
end

function cca.fadeTo(dt, opacity)
   return cc.FadeTo:create(dt, opacity*255)
end

function cca.fadeIn(dt)
   return cc.FadeIn:create(dt)
end

function cca.fadeOut(dt)
   return cc.FadeOut:create(dt)
end

function cca.tintTo(dt, r, g, b)
   return cc.TintTo:create(dt, r*255, g*255, b*255)
end

function cca.tintBy(dt, dr, dg, db)
   return cc.TintBy:create(dt, dr*255, dg*255, db*255)
end

function cca.delay(dt)
   return cc.DelayTime:create(dt)
end

function cca.animate(ani)
   return cc.Animate:create(ani)
end

function cca.progressTo(dt, progress)
   return cc.ProgressTo:create(dt, progress)
end

function cca.progressFromTo(dt, from, to)
   return cc.ProgressFromTo:create(dt, from, to)
end


-- compose: compose can used together with cca.builder, as compose
-- always use act(s) for it's first arguments, and only take one extra
-- argument. compose can be the 'cmd' arg of builder, used like this:
-- cca.builder 'spawn' -- cca.spawn
--    :blink(10, 10)
--    :begin 'seq' -- cca.seq
--       :moveTo(5, display.cx, display.cy)
--       :rotateBy(5, 360)
--    :done()
--    :begin('rep', 4) -- compose with a argument
--       :scaleBy(2.5, 3.0)
--    :done()
-- :done 'bounce'
--

local function checkaction(act)
   if not act then
      error("action required!!!")
   end
   if act.build then return act:build() end
   return act
end

function cca.seq(acts)
   return cc.Sequence:create(acts)
end

function cca.spawn(acts)
   return cc.Spawn:create(acts)
end

function cca.repeatForever(act)
   return cc.RepeatForever:create(checkaction(act))
end

function cca.reverse(act)
   return cc.ReverseTime:create(checkaction(act))
end

function cca.speed(act, speed)
   return cc.Speed:create(checkaction(act), speed)
end

function cca.rep(act, times)
   return cc.Repeat:create(checkaction(act), times)
end

function cca.targeted(act, node)
   return cc.TargetedAction:create(node, checkaction(act))
end


-- follow is neither a interval action nor instant aciton :(
-- it can not use together with cca.builder
function cca.follow(node, rect)
   return cc.Follow:create(node, rect)
end


-- eases

local function EaseAction(name, dft)
   local cls = "Ease"..name:gsub("^%w", string.upper)
   local f
   if dft then
      f = function(act, rate)
         return cc[cls]:create(checkaction(act), rate or dft)
      end
   else
      f = function(act)
         return cc[cls]:create(checkaction(act))
      end
   end
   cca[name] = f
   cca[name:upper()] = f
end

EaseAction("backIn")
EaseAction("backOut")
EaseAction("backinOut")
EaseAction("bounce")
EaseAction("bounceIn")
EaseAction("bounceInOut")
EaseAction("bounceOut")
EaseAction("elastic", 0.3)
EaseAction("elasticIn", 0.3)
EaseAction("elasticInOut", 0.3)
EaseAction("elasticOut", 0.3)
EaseAction("exponentialIn")
EaseAction("exponentialInOut")
EaseAction("exponentialOut")
EaseAction("in", 1.0)
EaseAction("inOut", 1.0)
EaseAction("out", 1.0)
EaseAction("rateAction", 1.0)
EaseAction("sineIn")
EaseAction("sineInOut")
EaseAction("sineOut")


-- shortcodes

cca.cb = cca.callFunc
cca.ani = cca.animate
cca.loop = cca.repeatForever
cca.to = cca.targeted


-- ActionBuilder implement

local ActionBuilder = {}
ActionBuilder.__class = "ActionBuilder"
ActionBuilder.__index = ActionBuilder

function cca.builder(cmd, parent)
   local self = setmetatable({}, ActionBuilder)
   self.cur = self
   self.cur.parent = parent or self
   self.cur.cmd = cmd or "seq"
   self.target = nil
   if not cca[self.cur.cmd] then
      error("cmd '"..(cmd or "nil").."' not found")
   end
   return self
end

function ActionBuilder:clear()
   for i = 1, #self.cur do
      self.cur[i] = nil
   end
   return self
end

function ActionBuilder:clone(other)
   self:clear()
   for i = 1, #other.cur do
      self.cur[i] = other.cur[i]
   end
   return self
end

function ActionBuilder:begin(cmd, args)
   self.cur = cca.builder(cmd, self.cur)
   self.cur.args = args
   self.cur.target = self.target
   return self
end

function ActionBuilder:done(ease, ...)
   local parent = self.cur.parent
   local acts = self.cur
   local cmd = self.cur.cmd
   local args = self.cur.args
   if cmd ~= 'seq' and cmd ~= 'spawn' then
      acts = cca.seq(acts)
   end
   local act = cca[cmd](acts, args)
   if ease and type(ease) == 'string' then
      ease = cca[ease:upper()]
      if ease then act = ease(act, ...) end
   end
   self.cur = parent
   self.cur[#self.cur+1] = act
   return self, act
end

function ActionBuilder:action()
   local self, act = self:done()
   return act
end

function ActionBuilder:add(act)
   self.cur[#self.cur+1] = act
   return self
end

function ActionBuilder:addTo(target)
   target = target or self.target
   assert(not tolua.isnull(target), "ActionBuilder.addTo() - target is not cc.Node")
   local self, act = self:done()
   return act:addTo(target)
end

-- shortcode
ActionBuilder.run = ActionBuilder.addTo
ActionBuilder.build = ActionBuilder.done


for k,v in pairs(cca) do
   ActionBuilder[k] = function(self, ...)
      local act = v(...)
      if act then
         self.cur[#self.cur+1] = act
      end
      return self
   end
end

-- some patch to standard actions

local builder_moveTo = ActionBuilder.moveTo
function ActionBuilder:moveTo(dt, x, y)
   if self.target then
      x = x or self.target:getPositionX()
      if not y and type(x) == "number" then
         y = self.target:getPositionY()
      end
   end
   return builder_moveTo(self, dt, x, y)
end

return cca
