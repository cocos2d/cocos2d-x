local targetPlatform = cc.Application:getInstance():getTargetPlatform()

-------------------------------------
--  AssetsManager Test
-------------------------------------
function AssetsManagerTestMain()
    local scene = cc.Scene:create()
    scene:addChild(cc.Layer:create())
    scene:addChild(CreateBackMenuItem())
    return scene
end
