local function ComponentTestLayer()

    local layer = cc.Layer:create()

    -- set background color
    local bgLayer = cc.LayerColor:create(cc.c4b(0, 128, 255, 255));
    layer:addChild(bgLayer);

    -- create game scene
    local sceneLuaComponent = cc.ComponentLua:create("src/ComponentTest/scene.lua");
    sceneLuaComponent:setName("sceneLuaComponent");
    layer:addComponent(sceneLuaComponent);

    -- add player
    local player = cc.Sprite:create("components/Player.png", cc.rect(0, 0, 27, 40));
    local visibleSize = cc.Director:getInstance():getVisibleSize();
    local origin = cc.Director:getInstance():getVisibleOrigin();
    player:setPosition(origin.x + player:getContentSize().width/2,
                       origin.y + visibleSize.height/2);
    local playerComponent = cc.ComponentLua:create("src/ComponentTest/player.lua");
    player:addComponent(playerComponent);
    layer:addChild(player);

    local function onEvent(event)
        ccexp.AudioEngine:stopAll()
        local scene = cc.Scene:create()

        scene:addChild(ComponentTestLayer())
        scene:addChild(CreateBackMenuItem())
        cc.Director:getInstance():replaceScene(scene);
    end

    layer._listener1 = cc.EventListenerCustom:create("component game over", onEvent)
    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    eventDispatcher:addEventListenerWithFixedPriority(layer._listener1, 1)

    return layer
end


function ComponentTestMain()

    cclog("ComponentTestMain")
    local scene = cc.Scene:create()
    scene:addChild(ComponentTestLayer())
    scene:addChild(CreateBackMenuItem())
    return scene

end
