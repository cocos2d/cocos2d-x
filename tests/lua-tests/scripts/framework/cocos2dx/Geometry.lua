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

定义用于 cc.Point 结算的辅助函数

]]

local c = cc

--[[--

创建并返回一个 CCPoint 对象

~~~ lua

local point = c.p(100, 50)
-- point 是一个 CCPoint 对象
print(point.x, point.y)
-- 输出 100 50

~~~

@param number x
@param number y

@return CCPoint

]]
c.p = CCPoint
c.point = CCPoint

--[[--

创建并返回一个 CCSize 对象

~~~ lua

local size = c.size(200, 80)
-- size 是一个 CCSize 对象
print(size.width, size.height)
-- 输出 200 80

~~~

@param number width
@param number height

@return CCSize

]]
c.size = CCSize

--[[--

创建并返回一个 CCRect 对象

~~~ lua

local rect = c.rect(100, 50, 200, 80)
-- rect 是一个 CCRect 对象
-- rect.origin 是一个 CCPoint 对象
-- rect.size 是一个 CCSize 对象
print(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height)
-- 输出 100 50 200 80

~~~

@param number x
@param number y
@param number width
@param number height

@return CCRect

]]
c.rect = CCRect

--[[--

将 CCPoint 对象转换为一个 Lua 表格

~~~ lua

local point = c.p(100, 50)
local res = c.point2t(point)
-- res = {x = 100, y = 50}

~~~

@param CCPoint point

@return table

@see c.t2point

]]
c.point2t = function(point)
    return {x = point.x, y = point.y}
end

--[[--

将 CCSzie 对象转换为一个 Lua 表格

~~~ lua

local size = c.size(200, 80)
local res = c.size2t(size)
-- res = {width = 200, height = 80}

~~~

@param CCSzie size

@return table

@see c.t2size

]]
c.size2t = function(size)
    return {width = size.width, height = size.height}
end

--[[--

将 CCRect 对象转换为一个 Lua 表格

~~~ lua

local rect = c.rect(100, 50, 200, 80)
local res = c.rect2t(rect)
-- res = {origin = {x = 100, y = 50}, size = {width = 200, height = 80}}

~~~

@param CCRect rect

@return table

@see c.t2rect

]]
c.rect2t = function(rect)
    return {origin = c.point2t(rect.origin), size = c.size2t(rect.size)}
end

--[[--

将一个 Lua 表格转换为 CCPoint 对象

~~~ lua

local input = {width = 200, height = 80}
local res = c.t2size(input)
-- res 是一个 CCSize 对象
-- res = CCSize(200, 80)

~~~

@param table t

@return CCSize

@see c.size2t

]]
c.t2point = function(t)
    return CCPoint(t.x, t.y)
end

--[[--

将一个 Lua 表格转换为 CCSize 对象

~~~ lua

local t = {width = 200, height = 80}
local res = c.t2size(t)
-- res 是一个 CCSize 对象

~~~

@param table t

@return CCSize

@see c.size2t

]]
c.t2size = function(t)
    return CCSize(t.width, t.height)
end

--[[--

将一个 Lua 表格转换为 CCRect 对象

~~~ lua

local t = {origin = {x = 100, y = 50}, size = {width = 200, height = 80}}
local res = c.t2rect(t)
-- res 是一个 CCRect 对象

~~~

@param table t

@return CCRect

@see c.rect2t

]]
c.t2rect = function(t)
    return CCRect(t.origin.x, t.origin.y, t.size.width, t.size.height)
end

c.PointNeg              = ccpNeg
c.PointAdd              = ccpAdd
c.PointSub              = ccpSub
c.PointMult             = ccpMult
c.PointMidpoint         = ccpMidpoint
c.PointDot              = ccpDot
c.PointCross            = ccpCross
c.PointPerp             = ccpPerp
c.PointRPerp            = ccpRPerp
c.PointProject          = ccpProject
c.PointRotate           = ccpRotate
c.PointUnrotate         = ccpUnrotate
c.PointLengthSQ         = ccpLengthSQ
c.PointDistanceSQ       = ccpDistanceSQ
c.PointLength           = ccpLength
c.PointDistance         = ccpDistance
c.PointNormalize        = ccpNormalize
c.PointForAngle         = ccpForAngle
c.PointToAngle          = ccpToAngle
c.PointClamp            = ccpClamp
c.PointFromSize         = ccpFromSize
c.PointLerp             = ccpLerp
c.PointFuzzyEqual       = ccpFuzzyEqual
c.PointCompMult         = ccpCompMult
c.PointAngleSigned      = ccpAngleSigned
c.PointAngle            = ccpAngle
c.PointRotateByAngle    = ccpRotateByAngle
c.PointLineIntersect    = ccpLineIntersect
c.PointSegmentIntersect = ccpSegmentIntersect
c.PointIntersectPoint   = ccpIntersectPoint

c.PointFromString       = CCPointFromString
c.SizeFromString        = CCSizeFromString
c.RectFromString        = CCRectFromString
c.PointMake             = CCPointMake
c.SizeMake              = CCSizeMake
c.RectMake              = CCRectMake
