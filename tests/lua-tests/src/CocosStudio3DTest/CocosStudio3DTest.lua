----------------------------------------
----CSNode3DTest
----------------------------------------

local CSNode3DTest = {}
CSNode3DTest.__index = CSNode3DTest

function CSNode3DTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Node3D")

    local node = cc.CSLoader:createNode("CocosStudio3DTest/Node3D.csb");
    layer:addChild(node);

    return layer
end

function CocosStudio3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        CSNode3DTest.create
    }

    scene:addChild(CSNode3DTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
