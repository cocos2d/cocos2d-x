----------------------------------------
----CSNode3DTest
----------------------------------------

local CSNode3DTest = {}
CSNode3DTest.__index = CSNode3DTest

function CSNode3DTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Node3DReader Test")

    local node = cc.CSLoader:createNode("ccs-res/CocosStudio3DTest/Node3D.csb");
    layer:addChild(node);

    return layer;
end

----------------------------------------
----CSSprite3DTest
----------------------------------------

local CSSprite3DTest = {}
CSSprite3DTest.__index = CSSprite3DTest

function CSSprite3DTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Sprite3DReader Test")

    local node = cc.CSLoader:createNode("ccs-res/CocosStudio3DTest/Sprite3D.csb")

    local sprite3D = node:getChildByTag(8)
    local size = cc.Director:getInstance():getWinSize()

    sprite3D:setPosition(size.width / 2, size.height / 2 - 50)
    sprite3D:setColor(cc.c3b(255, 255, 255))
    sprite3D:setOpacity(255)

    layer:addChild(node)

    return layer
end

----------------------------------------
----CSUserCameraTest
----------------------------------------

local CSUserCameraTest = {}
CSUserCameraTest.__index = CSUserCameraTest

function CSUserCameraTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("UserCameraReader Test")

    local node = cc.CSLoader:createNode("ccs-res/CocosStudio3DTest/UserCamera.csb")

    local sprite3D = cc.Sprite3D:create("ccs-res/CocosStudio3DTest/dragon/dragon.c3b")
    sprite3D:setPosition3D(cc.vec3(100, 95, 80))
    sprite3D:setCameraMask(cc.CameraFlag.USER1)

    layer:addChild(node)
    layer:addChild(sprite3D)

    return layer
end

----------------------------------------
----CSParticle3DTest
----------------------------------------

local CSParticle3DTest = {}
CSParticle3DTest.__index = CSParticle3DTest

function CSParticle3DTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Particle3DReader Test")

    local node = cc.CSLoader:createNode("ccs-res/CocosStudio3DTest/Particle3D.csb")

    layer:addChild(node)

    return layer
end

function CocosStudio3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        CSNode3DTest.create,
        CSSprite3DTest.create,
        CSUserCameraTest.create,
        CSParticle3DTest.create
    }

    scene:addChild(CSNode3DTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
