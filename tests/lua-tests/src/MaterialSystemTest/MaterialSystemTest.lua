
local function printProperties( properties, indent )
    --Print the name and ID of the current namespace.
    local spacename = properties:getNamespace()
    local id = properties:getId()
    local chindentTable = {}
    local  i = 1
    for i = 1, indent * 2  do
        chindentTable[i] = ' '
    end
    chindentTable[i] = '\0'
    local chindent = table.concat(chindentTable)

    print(string.format("%sNamespace: %s  ID: %s\n%s{", chindent, spacename, id, chindent))

    --Print all properties in this namespace.
    local name = properties:getNextProperty()
    local value = nil
    while name ~= nil do
        value = properties:getString(name)
        print(string.format("%s%s = %s", chindent, name, value))
        name = properties:getNextProperty()
    end

    local space = properties:getNextNamespace()
    while space ~= nil do
        printProperties(space, indent+1)
        space = properties:getNextNamespace()
    end

    print(string.format("%s}\n",chindent))
end

----------------------------------------
----MaterialSystemBaseTest
----------------------------------------
local MaterialSystemBaseTest = class("MaterialSystemBaseTest", function ()
    local layer = cc.Layer:create()
    return layer
end)

function MaterialSystemBaseTest:ctor()

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local function onNodeEvent(event)
        if "enter" == event then
            self:onEnter()
        elseif "exit" == event then
            self:onExit()
        end
    end

    self:registerScriptHandler(onNodeEvent)
end

function MaterialSystemBaseTest:title()
    return "Material System"
end

function MaterialSystemBaseTest:subtitle()
    return ""
end

function MaterialSystemBaseTest:onEnter()

end

function MaterialSystemBaseTest:onExit()

end

----------------------------------------
----Material_Sprite3DTest
----------------------------------------
local Material_Sprite3DTest = class("Material_Sprite3DTest", MaterialSystemBaseTest)

function Material_Sprite3DTest:subtitle()
    return "Material System on Sprite3D"
end

function Material_Sprite3DTest:onEnter()
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite:setScale(8.0)
    sprite:setTexture("Sprite3DTest/boss.png")
    self:addChild(sprite)
    sprite:setNormalizedPosition(cc.p(0.5,0.5))
end


----------------------------------------
----Material_MultipleSprite3D
----------------------------------------
local Material_MultipleSprite3D = class("Material_MultipleSprite3D", MaterialSystemBaseTest)

function Material_MultipleSprite3D:subtitle()
    return "Sprites with multiple meshes"
end

function Material_MultipleSprite3D:onEnter()
    local names = 
    {
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
    }

    local totalNames = #names

    local size = cc.Director:getInstance():getWinSize()

    for i = 1 , totalNames do
        local sprite = cc.Sprite3D:create(names[i])
        self:addChild(sprite)
        sprite:setPosition(cc.p((size.width/(totalNames+1)) * i, size.height/4))
        sprite:setScale(3)
    end
end

----------------------------------------
----Material_2DEffects
----------------------------------------
local Material_2DEffects = class("Material_2DEffects", MaterialSystemBaseTest)

function Material_2DEffects:subtitle()
    return "Testing effects on Sprite"
end

function Material_2DEffects:onEnter()
    local properties = cc.Properties:createNonRefCounted("Materials/2d_effects.material#sample")

    -- Print the properties of every namespace within this one.
    -- TODO
    printProperties(properties, 0)

    local mat1 = cc.Material:createWithProperties(properties)

    local spriteBlur = cc.Sprite:create("Images/grossini.png")
    spriteBlur:setNormalizedPosition(cc.p(0.2, 0.5))
    self:addChild(spriteBlur)
    spriteBlur:setGLProgramState(mat1:getTechniqueByName("blur"):getPassByIndex(0):getGLProgramState())

    local spriteOutline = cc.Sprite:create("Images/grossini.png")
    spriteOutline:setNormalizedPosition(cc.p(0.4, 0.5))
    self:addChild(spriteOutline)
    spriteOutline:setGLProgramState(mat1:getTechniqueByName("outline"):getPassByIndex(0):getGLProgramState())

    local spriteNoise = cc.Sprite:create("Images/grossini.png")
    spriteNoise:setNormalizedPosition(cc.p(0.6, 0.5))
    self:addChild(spriteNoise)
    spriteNoise:setGLProgramState(mat1:getTechniqueByName("noise"):getPassByIndex(0):getGLProgramState())

    local spriteEdgeDetect = cc.Sprite:create("Images/grossini.png")
    spriteEdgeDetect:setNormalizedPosition(cc.p(0.8, 0.5))
    self:addChild(spriteEdgeDetect)
    spriteEdgeDetect:setGLProgramState(mat1:getTechniqueByName("edge_detect"):getPassByIndex(0):getGLProgramState())
end

----------------------------------------
----Material_setTechnique
----------------------------------------
local Material_setTechnique = class("Material_setTechnique", MaterialSystemBaseTest)

function Material_setTechnique:subtitle()
    return "Testing setTechnique()"
end

function Material_setTechnique:onEnter()
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite:setScale(6)
    self:addChild(sprite)
    sprite:setNormalizedPosition(cc.p(0.5,0.5))

    local mat = cc.Material:createWithFilename("Materials/3d_effects.material")
    sprite:setMaterial(mat)

    --lights
    local light1 = cc.AmbientLight:create(cc.c3b(255, 0, 0))
    self:addChild(light1)

    local light2 = cc.DirectionLight:create(cc.vec3(-1,1,0), cc.c3b(0, 255, 0))
    self:addChild(light2)
    local techniqueState = 0
    local scheduler = cc.Director:getInstance():getScheduler()
    self._schedulerEntry = scheduler:scheduleScriptFunc(function(dt)
        if 0 == techniqueState then
            sprite:getMaterial(0):setTechnique("lit")
        elseif 1 == techniqueState then
            sprite:getMaterial(0):setTechnique("normal")
        elseif 2 == techniqueState then
            sprite:getMaterial(0):setTechnique("outline")
        end

        techniqueState = techniqueState + 1
        if techniqueState > 2 then
            techniqueState = 0
        end
    end, 1, false)
    

    local rot = cc.RotateBy:create(5, cc.vec3(30,60,270))
    local repeatAction = cc.RepeatForever:create(rot)
    sprite:runAction(repeatAction)
end

function Material_setTechnique:onExit()
    local scheduler = cc.Director:getInstance():getScheduler()
    scheduler:unscheduleScriptEntry(self._schedulerEntry)
end

----------------------------------------
----Material_clone
----------------------------------------
local Material_clone = class("Material_clone", MaterialSystemBaseTest)

function Material_clone:subtitle()
    return "Testing material:clone()"
end

function Material_clone:onEnter()
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite:setScale(3)
    self:addChild(sprite)
    sprite:setNormalizedPosition(cc.p(0.25, 0.5))

    local mat = cc.Material:createWithFilename("Materials/3d_effects.material")
    sprite:setMaterial(mat)

    local rot = cc.RotateBy:create(5, cc.vec3(360,240,120))
    local repeatAction = cc.RepeatForever:create(rot)
    sprite:runAction(repeatAction)

    -- sprite 2... using same material
    local sprite2 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite2:setScale(3)
    self:addChild(sprite2)
    sprite2:setNormalizedPosition(cc.p(0.5, 0.5))
    sprite2:setMaterial(mat)
    sprite2:runAction(repeatAction:clone())

    -- sprite 3... using cloned material
    local sprite3 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite3:setScale(3)
    self:addChild(sprite3)
    sprite3:setNormalizedPosition(cc.p(0.75, 0.5))
    local mat2 = mat:clone()
    sprite3:setMaterial(mat2)
    sprite3:runAction(repeatAction:clone())

    -- testing clone
    -- should affect both sprite 1 and sprite 2
    mat:setTechnique("outline")
end

----------------------------------------
----Material_clone
----------------------------------------
local Material_clone = class("Material_clone", MaterialSystemBaseTest)

function Material_clone:subtitle()
    return "Testing material->clone()"
end

function Material_clone:onEnter()
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite:setScale(3)
    self:addChild(sprite)
    sprite:setNormalizedPosition(cc.p(0.25, 0.5))

    local mat = cc.Material:createWithFilename("Materials/3d_effects.material")
    sprite:setMaterial(mat)

    local rot = cc.RotateBy:create(5, cc.vec3(360,240,120))
    local repeatAction = cc.RepeatForever:create(rot)
    sprite:runAction(repeatAction)

    -- sprite 2... using same material
    local sprite2 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite2:setScale(3)
    self:addChild(sprite2)
    sprite2:setNormalizedPosition(cc.p(0.5, 0.5))
    sprite2:setMaterial(mat)
    sprite2:runAction(repeatAction:clone())

    -- sprite 3... using cloned material
    local sprite3 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite3:setScale(3)
    self:addChild(sprite3)
    sprite3:setNormalizedPosition(cc.p(0.75, 0.5))
    local mat2 = mat:clone()
    sprite3:setMaterial(mat2)
    sprite3:runAction(repeatAction:clone())

    -- testing clone
    -- should affect both sprite 1 and sprite 2
    mat:setTechnique("outline")
end

----------------------------------------
----Material_parsePerformance
----------------------------------------
local Material_parsePerformance = class("Material_parsePerformance", MaterialSystemBaseTest)

function Material_parsePerformance:subtitle()
    return "Testing parsing performance"
end

function Material_parsePerformance:onEnter()
    local begin = os.clock()

    for i = 1,5000 do
        cc.Material:createWithFilename("Materials/2d_effects.material")
        cc.Material:createWithFilename("Materials/3d_effects.material")
    end

    print("Parsing took: ", os.clock() - begin)
end

----------------------------------------
----Material_clone
----------------------------------------
function MaterialSystemTest()
    
    local scene = cc.Scene:createWithPhysics()

    Helper.createFunctionTable = 
    {
        Material_2DEffects.create,
        Material_setTechnique.create,
        Material_clone.create,
        Material_MultipleSprite3D.create,
        Material_Sprite3DTest.create,
        Material_parsePerformance.create,
    }

    scene:addChild(Material_2DEffects.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end