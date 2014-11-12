
local dp_initialized = false
local dp_shader      = nil
local dp_colorLocation = -1
local dp_color = { 1.0, 1.0, 1.0, 1.0 }
local dp_pointSizeLocation = -1
local dp_pointSize = 1.0

local SHADER_NAME_POSITION_U_COLOR = "ShaderPosition_uColor"

local targetPlatform = cc.Application:getInstance():getTargetPlatform()

local function lazy_init()
    if not dp_initialized then
        dp_shader = cc.ShaderCache:getInstance():getProgram(SHADER_NAME_POSITION_U_COLOR)
        --dp_shader:retain()
        if nil ~= dp_shader then
            dp_colorLocation = gl.getUniformLocation( dp_shader:getProgram(), "u_color")
            dp_pointSizeLocation = gl.getUniformLocation( dp_shader:getProgram(), "u_pointSize")
            dp_Initialized = true
        end
    end

    if nil == dp_shader then
        print("Error:dp_shader is nil!")
        return false
    end

    return true
end

local function setDrawProperty()
    gl.glEnableVertexAttribs( CCConstants.VERTEX_ATTRIB_FLAG_POSITION )
    dp_shader:use()
    dp_shader:setUniformsForBuiltins()
    dp_shader:setUniformLocationWith4fv(dp_colorLocation, dp_color, 1)
end

function ccDrawInit()
    lazy_init()
end

function ccDrawFree()
    dp_initialized = false
end

function ccDrawColor4f(r,g,b,a)
    dp_color[1] = r
    dp_color[2] = g
    dp_color[3] = b
    dp_color[4] = a
end

function ccPointSize(pointSize)
    dp_pointSize = pointSize * cc.Director:getInstance():getContentScaleFactor()
end

function ccDrawColor4B(r,g,b,a)
    dp_color[1] = r / 255.0
    dp_color[2] = g / 255.0
    dp_color[3] = b / 255.0
    dp_color[4] = a / 255.0
end

function ccDrawPoint(point)
    if not lazy_init() then
        return
    end

    local vertexBuffer = { }

    local function initBuffer()
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
        local vertices = { point.x,point.y}
        gl.bufferData(gl.ARRAY_BUFFER,2,vertices,gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    dp_shader:setUniformLocationWith1f(dp_pointSizeLocation, dp_pointSize)

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.POINTS,0,1)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawPoints(points,numOfPoint)
    if not lazy_init() then
        return
    end

    local vertexBuffer = {}
    local i = 1

    local function initBuffer()
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        local vertices = {}
        for i = 1, numOfPoint do
            vertices[2 * i - 1] = points[i].x
            vertices[2 * i]     = points[i].y
        end
        gl.bufferData(gl.ARRAY_BUFFER, numOfPoint * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    dp_shader:setUniformLocationWith1f(dp_pointSizeLocation, dp_pointSize)

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.POINTS,0,numOfPoint)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawLine(origin,destination)
    if not lazy_init() then
        return
    end

    local vertexBuffer = {}

    local function initBuffer()
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        local vertices = { origin.x, origin.y, destination.x, destination.y}
        gl.bufferData(gl.ARRAY_BUFFER,4,vertices,gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.LINES ,0,2)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawPoly(points,numOfPoints,closePolygon)
    if not lazy_init() then
        return
    end

    local vertexBuffer = {}
    local i = 1

    local function initBuffer()
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        local vertices = {}
        for i = 1, numOfPoints do
            vertices[2 * i - 1] = points[i].x
            vertices[2 * i]     = points[i].y
        end
        gl.bufferData(gl.ARRAY_BUFFER, numOfPoints * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    if closePolygon then
        gl.drawArrays(gl.LINE_LOOP , 0, numOfPoints)
    else
        gl.drawArrays(gl.LINE_STRIP, 0, numOfPoints)
    end
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawSolidPoly(points,numOfPoints,color)
    if not lazy_init() then
        return
    end

    local vertexBuffer = {}
    local i = 1

    local function initBuffer()
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        local vertices = {}
        for i = 1, numOfPoints do
            vertices[2 * i - 1] = points[i].x
            vertices[2 * i]     = points[i].y

        end
        gl.bufferData(gl.ARRAY_BUFFER, numOfPoints * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    gl.glEnableVertexAttribs( CCConstants.VERTEX_ATTRIB_FLAG_POSITION )
    dp_shader:use()
    dp_shader:setUniformsForBuiltins()
    dp_shader:setUniformLocationWith4fv(dp_colorLocation, color, 1)

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.TRIANGLE_FAN , 0, numOfPoints)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawRect(origin,destination)
    ccDrawLine(CCPoint:__call(origin.x, origin.y), CCPoint:__call(destination.x, origin.y))
    ccDrawLine(CCPoint:__call(destination.x, origin.y), CCPoint:__call(destination.x, destination.y))
    ccDrawLine(CCPoint:__call(destination.x, destination.y), CCPoint:__call(origin.x, destination.y))
    ccDrawLine(CCPoint:__call(origin.x, destination.y), CCPoint:__call(origin.x, origin.y))
end

function ccDrawSolidRect( origin,destination,color )
    local vertices = { origin, CCPoint:__call(destination.x, origin.y) , destination, CCPoint:__call(origin.x, destination.y) }
    ccDrawSolidPoly(vertices,4,color)
end

function ccDrawCircleScale( center, radius, angle, segments,drawLineToCenter,scaleX,scaleY)
    if not lazy_init() then
        return
    end

    local additionalSegment = 1
    if drawLineToCenter then
        additionalSegment = additionalSegment + 1
    end

    local vertexBuffer = { }

    local function initBuffer()
        local coef = 2.0 * math.pi / segments
        local i = 1
        local vertices = {}
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        for i = 1, segments + 1 do
            local rads = (i - 1) * coef
            local j    = radius * math.cos(rads + angle) * scaleX + center.x
            local k    = radius * math.sin(rads + angle) * scaleY + center.y
            vertices[i * 2 - 1] = j
            vertices[i * 2]     = k
         end
        vertices[(segments + 2) * 2 - 1] = center.x
        vertices[(segments + 2) * 2]     = center.y

        gl.bufferData(gl.ARRAY_BUFFER, (segments + 2) * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.LINE_STRIP , 0, segments + additionalSegment)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawCircle(center, radius, angle, segments, drawLineToCenter)
    ccDrawCircleScale(center, radius, angle, segments, drawLineToCenter, 1.0, 1.0)
end

function ccDrawSolidCircle(center, radius, angle, segments,scaleX,scaleY)
    if not lazy_init() then
        return
    end

    local vertexBuffer = { }

    local function initBuffer()
        local coef = 2.0 * math.pi / segments
        local i = 1
        local vertices = {}
        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        for i = 1, segments + 1 do
            local rads = (i - 1) * coef
            local j    = radius * math.cos(rads + angle) * scaleX + center.x
            local k    = radius * math.sin(rads + angle) * scaleY + center.y
            vertices[i * 2 - 1] = j
            vertices[i * 2]     = k
         end
        vertices[(segments + 2) * 2 - 1] = center.x
        vertices[(segments + 2) * 2]     = center.y

        gl.bufferData(gl.ARRAY_BUFFER, (segments + 2) * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.TRIANGLE_FAN , 0, segments + 1)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawQuadBezier(origin, control, destination, segments)
    if not lazy_init() then
        return
    end

    local vertexBuffer = { }

    local function initBuffer()
        local vertices = { }
        local i = 1
        local t = 0.0

        for i = 1, segments do
            vertices[2 * i - 1] = math.pow(1 - t,2) * origin.x + 2.0 * (1 - t) * t * control.x + t * t * destination.x
            vertices[2 * i]     = math.pow(1 - t,2) * origin.y + 2.0 * (1 - t) * t * control.y + t * t * destination.y
            t = t + 1.0 / segments
        end

        vertices[2 * (segments + 1) - 1] = destination.x
        vertices[2 * (segments + 1)]     = destination.y

        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        gl.bufferData(gl.ARRAY_BUFFER, (segments + 1) * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.LINE_STRIP , 0, segments + 1)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end

function ccDrawCubicBezier(origin, control1, control2, destination, segments)
    if not lazy_init then
        return
    end

    local vertexBuffer = { }

    local function initBuffer()
        local vertices = { }
        local t = 0
        local i = 1

        for i = 1, segments do
            vertices[2 * i - 1] = math.pow(1 - t,3) * origin.x + 3.0 * math.pow(1 - t, 2) * t * control1.x + 3.0 * (1 - t) * t * t * control2.x + t * t * t * destination.x
            vertices[2 * i]     = math.pow(1 - t,3) * origin.y + 3.0 * math.pow(1 - t, 2) * t * control1.y + 3.0 * (1 - t) * t * t * control2.y + t * t * t * destination.y
            t = t + 1.0 / segments
        end

        vertices[2 * (segments + 1) - 1] = destination.x
        vertices[2 * (segments + 1)]     = destination.y

        vertexBuffer.buffer_id = gl.createBuffer()
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer.buffer_id)
        gl.bufferData(gl.ARRAY_BUFFER, (segments + 1) * 2, vertices, gl.STATIC_DRAW)
        gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    end

    initBuffer()

    setDrawProperty()

    gl.bindBuffer(gl.ARRAY_BUFFER,vertexBuffer.buffer_id)
    gl.vertexAttribPointer(CCConstants.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)
    gl.drawArrays(gl.LINE_STRIP , 0, segments + 1)
    gl.bindBuffer(gl.ARRAY_BUFFER,0)
end
