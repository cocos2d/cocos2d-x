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

----------------------------------------
----CSSprite3DTest
----------------------------------------

local CSSprite3DTest = {}
CSSprite3DTest.__index = CSSprite3DTest

function CSSprite3DTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Node3D")

    local node = cc.CSLoader:createNode("CocosStudio3DTest/Sprite3D.csb");

    local sprite3D = node:getChildByTag(8);
    local size = cc.Director:getInstance():getWinSize();

    sprite3D:setPosition(size.width / 2, size.height / 2 - 50);
    sprite3D:setColor(cc.c3b(255, 255, 255));
    sprite3D:setOpacity(255);

    layer:addChild(node);

return layer
end

function CocosStudio3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        CSNode3DTest.create,
        CSSprite3DTest.create
    }

    scene:addChild(CSNode3DTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
