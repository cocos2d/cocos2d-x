cc = cc or {}

--Point
function cc.p(_x,_y)
    return { x = _x, y = _y }
end

--Size
function cc.size( _width,_height )
    return { width = _width, height = _height }
end

--Rect
function cc.rect(_x,_y,_width,_height)
    return { x = _x, y = _y, width = _width, height = _height }
end

--Color3B
function cc.c3b( _r,_g,_b )
    return { r = _r, g = _g, b = _b }
end

--Color4B
function cc.c4b( _r,_g,_b,_a )
    return { r = _r, g = _g, b = _b, a = _a }
end


