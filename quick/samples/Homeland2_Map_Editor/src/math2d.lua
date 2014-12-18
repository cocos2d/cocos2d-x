
local math2d = {}

--[[

radians: 弧度
radius: 半径
degrees: 角度
dist: 距离

--]]

-- 求两点间距离
local sqrt  = math.sqrt
local atan2 = math.atan2
local cos   = math.cos
local sin   = math.sin
local pi    = math.pi
local pi_d_180 = pi / 180
local pi_180_d = 180 / pi

function math2d.dist(ax, ay, bx, by)
    local dx, dy = bx - ax, by - ay
    return sqrt(dx * dx + dy * dy)
end

-- 求两点的夹角（弧度）
function math2d.radians4point(ax, ay, bx, by)
    return atan2(ay - by, bx - ax)
end

-- 求圆上一个点的位置
function math2d.pointAtCircle(px, py, radians, radius)
    return px + cos(radians) * radius, py - sin(radians) * radius
end

-- 求线段上与指定点距离最近的点
function math2d.pointAtLineToPoint(px, py, ax, ay, bx, by)
    local dx = bx - ax
    local dy = by - ay

    local som = dx * dx + dy * dy
    local u = ((px - ax) * dx + (py - ay) * dy) / som
    if u > 1 then
        u = 1
    elseif u < 0 then
        u = 0
    end

    return ax + u * dx, ay + u * dy
end

-- 角度转换为弧度
function math2d.degrees2radians(degrees)
    return degrees * pi_d_180
end

-- 弧度转换为角度
function math2d.radians2degrees(radians)
    return radians * pi_180_d
end

return math2d
