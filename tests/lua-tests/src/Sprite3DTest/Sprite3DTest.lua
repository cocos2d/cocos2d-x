local size = cc.Director:getInstance():getWinSize()
local attributeNames = 
{
    "a_position",
    "a_color",
    "a_texCoord",
    "a_normal",
}


----------------------------------------
----Sprite3DBasicTest
----------------------------------------

local Sprite3DBasicTest = {}
Sprite3DBasicTest.__index = Sprite3DBasicTest

function Sprite3DBasicTest.onTouchesEnd(touches, event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        Sprite3DBasicTest.addNewSpriteWithCoords(Helper.currentLayer, location.x, location.y )
    end
end

function Sprite3DBasicTest.addNewSpriteWithCoords(parent,x,y)
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite:setScale(3.0)
    sprite:setTexture("Sprite3DTest/boss.png")

    parent:addChild(sprite)
    sprite:setPosition(cc.p(x,y))

    local random = math.random(0, 1)
    local action = nil
    if random < 0.2 then
        action = cc.ScaleBy:create(3,2)
    elseif random < 0.4 then
        action = cc.RotateBy:create(3, 360)
    elseif random < 0.6 then
        action = cc.Blink:create(1, 3)
    elseif random < 0.8 then
        action = cc.TintBy:create(2, 0, -255, -255)
    else
        action  = cc.FadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = cc.Sequence:create(action, action_back)

    sprite:runAction(cc.RepeatForever:create(seq))
end

function Sprite3DBasicTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D")
    Helper.subtitleLabel:setString("Tap screen to add more sprites")

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(Sprite3DBasicTest.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    Sprite3DBasicTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end

----------------------------------------
----Sprite3DEffectTest
----------------------------------------

local Effect3DOutline = class("Effect3DOutline")
Effect3DOutline.__index = Effect3DOutline

function Effect3DOutline:ctor()
    self.outlineWidth = 0.0
    self.outlineColor = { x = 1, y = 1, z = 1}
    self.glProgramState = nil
    self.vertShaderFile = "Shaders3D/OutLine.vert"
    self.fragShaderFile = "Shaders3D/OutLine.frag"
    self.keyInGLProgramCache = "Effect3DLibrary_Outline"

    if self:init() then
        return self
    else
        return nil
    end
end

function Effect3DOutline:getOrCreateProgram()

    local program = cc.GLProgramCache:getInstance():getGLProgram(self.keyInGLProgramCache)

    if nil == program then
        program = cc.GLProgram:createWithFilenames(self.vertShaderFile , self.fragShaderFile)
        cc.GLProgramCache:getInstance():addGLProgram(program, self.keyInGLProgramCache)
    end
    print(program)
    return program
end

function Effect3DOutline:init()
    local program = self:getOrCreateProgram()
    if nil == program then
        return false
    end

    self.glProgramState = cc.GLProgramState:create(program)
    if nil == self.glProgramState then
        return false
    end

    self.glProgramState:retain()
    self.glProgramState:setUniformVec3("OutLineColor", self.outlineColor)
    self.glProgramState:setUniformFloat("OutlineWidth", self.outlineWidth)

    return true
end


function Effect3DOutline:setOutlineColor(color)
    if self.outlineColor.x ~= color.x and self.outlineColor.y ~= color.y or self.outlineColor.z ~= color.z then
        self.outlineColor.x = color.x
        self.outlineColor.y = color.y
        self.outlineColor.z = color.z
        self.glProgramState:setUniformVec3("OutLineColor", self.outlineColor)
    end
end

function Effect3DOutline:setOutlineWidth(width)
    if self.outlineWidth ~= width then
        self.outlineWidth = width
        self.glProgramState:setUniformFloat("OutlineWidth", self.outlineWidth )
    end
end

function Effect3DOutline:drawWithSprite(sprite, transform)
    
    local mesh = sprite:getMesh()
    local offset = 0
    for i = 1, mesh:getMeshVertexAttribCount() do
        local meshvertexattrib = mesh:getMeshVertexAttribute(i - 1)
        self.glProgramState:setVertexAttribPointer(attributeNames[meshvertexattrib.vertexAttrib + 1], meshvertexattrib.size, meshvertexattrib.type, false, mesh:getVertexSizeInBytes(), offset)
        offset = offset + meshvertexattrib.attribSizeBytes
    end

    --draw
    gl.enable(gl.CULL_FACE)
    gl.cullFace(gl.FRONT)
    gl.enable(gl.DEPTH_TEST)

    local color = sprite:getDisplayedColor()
    color.a = sprite:getDisplayedOpacity() / 255.0
    self.glProgramState:setUniformVec4("u_color", {x = color.r / 255.0, y = color.g / 255.0, z = color.b / 255.0, w = 1.0})

    mesh = sprite:getMesh()
    gl.bindBuffer(gl.ARRAY_BUFFER, mesh:getVertexBuffer())
    self.glProgramState:apply(transform)
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, mesh:getIndexBuffer())
    gl.drawElements(mesh:getPrimitiveType(), mesh:getIndexCount(), mesh:getIndexFormat(), 0)
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, 0)
    gl.bindBuffer(gl.ARRAY_BUFFER, 0)
    gl.disable(gl.DEPTH_TEST)
    gl.cullFace(gl.BACK)
    gl.disable(gl.CULL_FACE)
end


local EffectSprite3D = class("EffectSprite3D")
EffectSprite3D.__index = EffectSprite3D

function EffectSprite3D.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, EffectSprite3D)
    return target
end

function EffectSprite3D:init()
    self.effects = {}
    self.defaultEffect = nil
end

function EffectSprite3D.createFromObjFileAndTexture(objFilePath, textureFilePath)
    local sprite = EffectSprite3D.extend(cc.Sprite3D:create(objFilePath))
    sprite:setTexture(textureFilePath)
    return sprite
end


local Sprite3DEffectTest = {}
Sprite3DEffectTest.__index = Sprite3DEffectTest

function Sprite3DEffectTest.onTouchesEnd(touches, event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        Sprite3DEffectTest.addNewSpriteWithCoords(Helper.currentLayer, location.x, location.y )
    end
end

function Sprite3DEffectTest.addNewSpriteWithCoords(layer, x, y)
    local sprite = EffectSprite3D.createFromObjFileAndTexture("Sprite3DTest/boss1.obj", "Sprite3DTest/boss.png")
    sprite:setScale(6.0)
    layer:addChild(sprite)
    sprite:setPosition(cc.p(x, y))

    local effect = Effect3DOutline.new()
    effect:setOutlineColor({x = 1, y = 0, z =0})
    effect:setOutlineWidth(0.1)
    local effect2 = Effect3DOutline.new()
    effect2:setOutlineWidth(0.02)
    effect2:setOutlineColor({x = 1, y = 1, z =0})


    local function onDraw(transform, transformUpdated)
        effect:drawWithSprite(sprite, transform)
        effect2:drawWithSprite(sprite, transform)
    end

    local random = math.random(0, 1)
    local action = nil
    if random < 0.2 then
        action = cc.ScaleBy:create(3,2)
    elseif random < 0.4 then
        action = cc.RotateBy:create(3, 360)
    elseif random < 0.6 then
        action = cc.Blink:create(1, 3)
    elseif random < 0.8 then
        action = cc.TintBy:create(2, 0, -255, -255)
    else
        action  = cc.FadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = cc.Sequence:create(action, action_back)

    sprite:runAction(cc.RepeatForever:create(seq))

    local glNode  = gl.glNodeCreate()
    glNode:setContentSize(cc.size(size.width, size.height))
    glNode:setAnchorPoint(cc.p(0.5, 0.5))
    glNode:setPosition( size.width / 2, size.height / 2)
    glNode:registerScriptDrawHandler(onDraw)
    layer:addChild(glNode,-10)

end

function Sprite3DEffectTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D")
    Helper.subtitleLabel:setString("Sprite3d with effects")

    Sprite3DEffectTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end

function Sprite3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Sprite3DBasicTest.create,
        Sprite3DEffectTest.create,
    }

    scene:addChild(Sprite3DBasicTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
