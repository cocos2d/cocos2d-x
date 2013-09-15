require "OpenglConstants"

gl = gl or {}

--Create functions
function  gl.createTexture()
    local retTable = {}
    retTable.texture_id = gl._createTexture()
    return retTable
end

function gl.createBuffer()
    local retTable = {}
    retTable.buffer_id = gl._createBuffer()
    return retTable
end

function gl.createRenderbuffer()
    local retTable = {}
    retTable.renderbuffer_id = gl._createRenderuffer()
    return retTable
end

function gl.createFramebuffer( )
    local retTable = {}
    retTable.framebuffer_id = gl._createFramebuffer()
    return retTable
end

function gl.createProgram()
    local retTable = {}
    retTable.program_id = gl._createProgram()
    return retTable
end

function gl.createShader(shaderType)
    local retTable = {}
    retTable.shader_id = gl._createShader(shaderType)
    return retTable
end

--Delete Fun
function gl.deleteTexture(texture)
    local texture_id = 0
    if "number" == type(texture) then
        texture_id = texture
    elseif "table" == type(texture) then
        texture_id = texture.texture_id
    end
    gl._deleteTexture(texture_id)
end

function gl.deleteBuffer(buffer)
    local buffer_id = 0
    if "number" == type(buffer) then
        buffer_id = buffer
    elseif "table" == type(buffer) then
        buffer_id = buffer.buffer_id
    end
    gl._deleteBuffer(buffer_id)
end

function gl.deleteRenderbuffer(buffer)
    local renderbuffer_id = 0
    if "number" == type(buffer) then
        renderbuffer_id = buffer
    elseif "table" == type(buffer) then
        renderbuffer_id = buffer.renderbuffer_id
    end
    gl._deleteRenderbuffer(renderbuffer_id)
end

function gl.deleteFramebuffer(buffer)
    local framebuffer_id = 0
    if "number" == type(buffer) then
        framebuffer_id = buffer
    elseif "table" == type(buffer) then
        framebuffer_id = buffer.framebuffer_id
    end
    gl._deleteFramebuffer(framebuffer_id)
end

function gl.deleteProgram( program )
    local program_id = 0
    if "number" == type(buffer) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    gl._deleteProgram(program_id)
end

function gl.deleteShader(shader)
    local shader_id = 0
    if "number" == type(shader) then
        shader_id = shader
    elseif "table" == type(shader) then
        shader_id = shader.shader_id
    end

    gl._deleteShader(shader_id)
end

--Bind Related
function gl.bindTexture(target, texture)
    local texture_id = 0
    if "number" == type(texture) then
        texture_id = texture
    elseif "table" == type(texture) then
        texture_id = texture.texture_id
    end

    gl._bindTexture(target,texture_id)
end 

function gl.bindBuffer( target,buffer )
    local buffer_id = 0
    if "number" == type(buffer) then
        buffer_id = buffer
    elseif "table" == type(buffer) then
        buffer_id = buffer.buffer_id
    end

    gl._bindBuffer(target, buffer_id)
end

function gl.bindRenderBuffer(target, buffer)
    local buffer_id = 0

    if "number" == type(buffer) then
        buffer_id = buffer;
    elseif "table" == type(buffer) then
        buffer_id = buffer.buffer_id
    end

    gl._bindRenderbuffer(target, buffer_id)
end

function gl.bindFramebuffer(target, buffer)
    local buffer_id = 0

    if "number" == type(buffer) then
        buffer_id = buffer
    elseif "table" == type(buffer) then
        buffer_id = buffer.buffer_id
    end

    gl._bindFramebuffer(target, buffer_id)
end

--Uniform related
function gl.getUniform(program, location)
    local program_id = 0
    local location_id = 0

    if "number" == type(program) then
        program_id = program
    else
        program_id = program.program_id
    end

    if "number" == type(location) then
        location_id = location
    else
        location_id = location.location_id
    end

    return gl._getUniform(program_id, location_id)
end

--shader related
function gl.compileShader(shader)
    gl._compileShader( shader.shader_id)
end

function gl.shaderSource(shader, source)
    gl._shaderSource(shader.shader_id, source)
end

function gl.getShaderParameter(shader, e)
    return gl._getShaderParameter(shader.shader_id,e)
end

function gl.getShaderInfoLog( shader )
    return gl._getShaderInfoLog(shader.shader_id)
end

--program related
function gl.attachShader( program, shader )
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    gl._attachShader(program_id, shader.shader_id)
end

function gl.linkProgram( program )
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    gl._linkProgram(program_id)
end

function gl.getProgramParameter(program, e) 
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    return gl._getProgramParameter(program_id, e)
end

function gl.useProgram(program)
    local program_id = 0
    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    gl._useProgram (program_id)
end

function gl.getAttribLocation(program, name )
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    return gl._getAttribLocation(program_id, name)
end

function gl.getUniformLocation( program, name )
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    return gl._getUniformLocation(program_id,name)
end

function gl.getActiveAttrib( program, index )
    local program_id = 0
    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    return gl._getActiveAttrib(program_id, index);
end

function gl.getActiveUniform( program, index )
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    return gl._getActiveUniform(program_id, index)
end

function gl.getAttachedShaders(program)
    local program_id = 0

    if "number" == type(program) then
        program_id = program
    elseif "table" == type(program) then
        program_id = program.program_id
    end

    return gl._getAttachedShaders(program_id)
end

function gl.glNodeCreate()
    return cc.GLNode:create()
end

