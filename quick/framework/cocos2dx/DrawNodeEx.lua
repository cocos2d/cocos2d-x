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
    drawPolygon(self, points, #points, fillColor, borderWidth, borderColor)
    return self
end

local drawDot = DrawNode.drawDot
function DrawNode:drawDot(point, radius, color)
    drawDot(self, point, radius, color)
    return self
end
