local    kTagNode = 0
local    kTagGrossini = 1

local function createParallaxLayer(title, subtitle)
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    local titleStr = title == nil and "No title" or title
    local subTitleStr = subtitle  == nil and "" or subtitle
    Helper.titleLabel:setString(titleStr)
    Helper.subtitleLabel:setString(subTitleStr)
    return layer
end

--------------------------------------------------------------------
--
-- Parallax1
--
--------------------------------------------------------------------

local function Parallax1()
    local ret = createParallaxLayer("Parallax: parent and 3 children")
    -- Top Layer, a simple image
    local  cocosImage = cc.Sprite:create(s_Power)
    -- scale the image (optional)
    cocosImage:setScale( 2.5 )
    -- change the transform anchor point to 0,0 (optional)
    cocosImage:setAnchorPoint( cc.p(0,0) )


    -- Middle layer: a Tile map atlas
    local tilemap = cc.TileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
    tilemap:releaseMap()

    -- change the transform anchor to 0,0 (optional)
    tilemap:setAnchorPoint( cc.p(0, 0) )

    -- Anti Aliased images
    tilemap:getTexture():setAntiAliasTexParameters()


    -- background layer: another image
    local  background = cc.Sprite:create(s_back)
    -- scale the image (optional)
    background:setScale( 1.5 )
    -- change the transform anchor point (optional)
    background:setAnchorPoint( cc.p(0,0) )


    -- create a void node, a parent node
    local  voidNode = cc.ParallaxNode:create()

    -- NOW add the 3 layers to the 'void' node

    -- background image is moved at a ratio of 0.4x, 0.5y
    voidNode:addChild(background, -1, cc.p(0.4,0.5), cc.p(0,0))

    -- tiles are moved at a ratio of 2.2x, 1.0y
    voidNode:addChild(tilemap, 1, cc.p(2.2,1.0), cc.p(0,-200) )

    -- top image is moved at a ratio of 3.0x, 2.5y
    voidNode:addChild(cocosImage, 2, cc.p(3.0,2.5), cc.p(200,800) )


    -- now create some actions that will move the 'void' node
    -- and the children of the 'void' node will move at different
    -- speed, thus, simulation the 3D environment
    local  goUp = cc.MoveBy:create(4, cc.p(0,-500) )
    local  goDown = goUp:reverse()
    local  go = cc.MoveBy:create(8, cc.p(-1000,0) )
    local  goBack = go:reverse()
    local  seq = cc.Sequence:create(goUp, go, goDown, goBack)
    voidNode:runAction( (cc.RepeatForever:create(seq) ))

    ret:addChild( voidNode )
    return ret
end

--------------------------------------------------------------------
--
-- Parallax2
--
--------------------------------------------------------------------

local function Parallax2()
    local ret = createParallaxLayer("Parallax: drag screen")

    -- Top Layer, a simple image
    local  cocosImage = cc.Sprite:create(s_Power)
    -- scale the image (optional)
    cocosImage:setScale( 2.5 )
    -- change the transform anchor point to 0,0 (optional)
    cocosImage:setAnchorPoint( cc.p(0,0) )


    -- Middle layer: a Tile map atlas
    local  tilemap = cc.TileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
    tilemap:releaseMap()

    -- change the transform anchor to 0,0 (optional)
    tilemap:setAnchorPoint( cc.p(0, 0) )

    -- Anti Aliased images
    tilemap:getTexture():setAntiAliasTexParameters()


    -- background layer: another image
    local  background = cc.Sprite:create(s_back)
    -- scale the image (optional)
    background:setScale( 1.5 )
    -- change the transform anchor point (optional)
    background:setAnchorPoint( cc.p(0,0) )


    -- create a void node, a parent node
    local  voidNode = cc.ParallaxNode:create()

    -- NOW add the 3 layers to the 'void' node

    -- background image is moved at a ratio of 0.4x, 0.5y
    voidNode:addChild(background, -1, cc.p(0.4,0.5), cc.p(0, 0))

    -- tiles are moved at a ratio of 1.0, 1.0y
    voidNode:addChild(tilemap, 1, cc.p(1.0,1.0), cc.p(0,-200) )

    -- top image is moved at a ratio of 3.0x, 2.5y
    voidNode:addChild( cocosImage, 2, cc.p(3.0,2.5), cc.p(200,1000) )
    ret:addChild(voidNode, 0, kTagNode)

    local function onTouchesMoved(touches, event)
        local diff = touches[1]:getDelta()
    
        local node = ret:getChildByTag(kTagNode)
        local currentPosX, currentPosY = node:getPosition()
        node:setPosition(cc.p(currentPosX + diff.x, currentPosY + diff.y))
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
    local eventDispatcher = ret:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ret)

    return ret
end

function ParallaxTestMain()
    cclog("ParallaxMain")
    Helper.index = 1
    local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        Parallax1,
        Parallax2
    }
    scene:addChild(Parallax1())
    scene:addChild(CreateBackMenuItem())
    return scene
end
