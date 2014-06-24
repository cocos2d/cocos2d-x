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

]]

local c = cc
local DrawNode = c.DrawNode

function DrawNode:drawPol(points, params)
	PRINT_DEPRECATED("DrawNode.drawPol() is deprecated, please use DrawNode.drawPolygon()")
	return self:drawPolygon(points, params)
end

local drawPolygon = DrawNode.drawPolygon
function DrawNode:drawPolygon(points, params)
	local segments = #points
	fillColor = cc.c4f(1,1,1,1)
	borderWidth  = 0
	borderColor  = cc.c4f(0,0,0,1)
	if params then
		if params.fillColor then fillColor = params.fillColor end
		if params.borderWidth then borderWidth = params.borderWidth end
		if params.borderColor then borderColor = params.borderColor end
	end
	local pa = CCPointArray:create(segments)
	for i=1,segments do
		pa:add(cc.p(points[i][1], points[i][2]))
	end
	drawPolygon(self, pa:fetchPoints(), pa:count(), fillColor, borderWidth, borderColor)
	return self
end

function DrawNode:drawCircle(radius, params)
	local fillColor = cc.c4f(1,1,1,1)
	local borderColor = cc.c4f(1,1,1,1)
	local segments = 32
	local startRadian = 0
	local endRadian = math.pi*2
	local borderWidth = 0
	local posX = 0
	local posY = 0
	if params then
		if params.segments then segments = params.segments end
		if params.startAngle then
			startRadian = math.angle2Radian(params.startAngle)
		end
		if params.endAngle then
			endRadian = startRadian+math.angle2Radian(params.endAngle)
		end
		if params.fillColor then fillColor = params.fillColor end
		if params.borderColor then borderColor = params.borderColor end
		if params.borderWidth then borderWidth = params.borderWidth end
		if params.pos then
			posX =  params.pos[1]
			posY =  params.pos[2]
		end
	end
	local radianPerSegm = 2 * math.pi/segments
	local points = CCPointArray:create(segments)
	for i=1,segments do
		local radii = startRadian+i*radianPerSegm
		if radii > endRadian then break end
		points:add(cc.p(posX + radius * math.cos(radii), posY + radius * math.sin(radii)))
	end
	self:drawPolygon(points:fetchPoints(), points:count(), fillColor, borderWidth, borderColor)
	return self
end

local drawDot = DrawNode.drawDot
function DrawNode:drawDot(point, radius, color)
	drawDot(self, point, radius, color)
	-- getmetatable(self).drawDot(self, point, radius, color)
	return self
end

function DrawNode:drawRect(xywh, params)
	local points = {}
	local x = 0
	local y = 0
	local w = 100
	local h = 100
	-- Treat xywh as a table
	if type(xywh) == "table" then
		-- The table is {x=num, y=num, w=num, h=num}
		if xywh.x then
			x = xywh.x
			y = xywh.y
			w = xywh.w
			h = xywh.h
		-- The table is {x, y, w, h}
		else
			x = xywh[1]
			y = xywh[2]
			w = xywh[3]
			h = xywh[4]
		end
	-- Treat xywh as a CCRect
	else
		x = xywh.origin.x
		y = xywh.origin.y
		w = xywh.size.width
		h = xywh.size.height
	end
	points[1] = {x,y}
	points[2] = {x,y+h}
	points[3] = {x+w,y+h}
	points[4] = {x+w,y}
	self:drawPol(points, params)
	return self
end

function DrawNode:drawLine(from, to, radius, color)
	radius = radius or 1
	color = color or cc.c4f(0,0,0,1)
	assert(from or to, "Need a from point and a to point!")
	if type(from) == "table" then
		from = cc.p(from[1], from[2])
		to = cc.p(to[1], to[2])
	end
	self:drawSegment(from, to, radius, color)
	return self
end
