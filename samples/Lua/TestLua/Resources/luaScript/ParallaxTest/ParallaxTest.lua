local    kTagNode = 0
local    kTagGrossini = 1

local function createParallaxLayer(title, subtitle)
    local layer = CCLayer:create()
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
    local  cocosImage = CCSprite:create(s_Power)
    -- scale the image (optional)
    cocosImage:setScale( 2.5 )
    -- change the transform anchor point to 0,0 (optional)
    cocosImage:setAnchorPoint( ccp(0,0) )


    -- Middle layer: a Tile map atlas
    local tilemap = CCTileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
    tilemap:releaseMap()

    -- change the transform anchor to 0,0 (optional)
    tilemap:setAnchorPoint( ccp(0, 0) )

    -- Anti Aliased images
    tilemap:getTexture():setAntiAliasTexParameters()


    -- background layer: another image
    local  background = CCSprite:create(s_back)
    -- scale the image (optional)
    background:setScale( 1.5 )
    -- change the transform anchor point (optional)
    background:setAnchorPoint( ccp(0,0) )


    -- create a void node, a parent node
    local  voidNode = CCParallaxNode:create()

    -- NOW add the 3 layers to the 'void' node

    -- background image is moved at a ratio of 0.4x, 0.5y
    voidNode:addChild(background, -1, ccp(0.4,0.5), ccp(0,0))

    -- tiles are moved at a ratio of 2.2x, 1.0y
    voidNode:addChild(tilemap, 1, ccp(2.2,1.0), ccp(0,-200) )

    -- top image is moved at a ratio of 3.0x, 2.5y
    voidNode:addChild(cocosImage, 2, ccp(3.0,2.5), ccp(200,800) )


    -- now create some actions that will move the 'void' node
    -- and the children of the 'void' node will move at different
    -- speed, thus, simulation the 3D environment
    local  goUp = CCMoveBy:create(4, ccp(0,-500) )
    local  goDown = goUp:reverse()
    local  go = CCMoveBy:create(8, ccp(-1000,0) )
    local  goBack = go:reverse()
    local arr = CCArray:create()
    arr:addObject(goUp)
    arr:addObject(go)
    arr:addObject(goDown)
    arr:addObject(goBack)
    local  seq = CCSequence:create(arr)
    voidNode:runAction( (CCRepeatForever:create(seq) ))

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
    ret:setTouchEnabled( true )

    -- Top Layer, a simple image
    local  cocosImage = CCSprite:create(s_Power)
    -- scale the image (optional)
    cocosImage:setScale( 2.5 )
    -- change the transform anchor point to 0,0 (optional)
    cocosImage:setAnchorPoint( ccp(0,0) )


    -- Middle layer: a Tile map atlas
    local  tilemap = CCTileMapAtlas:create(s_TilesPng, s_LevelMapTga, 16, 16)
    tilemap:releaseMap()

    -- change the transform anchor to 0,0 (optional)
    tilemap:setAnchorPoint( ccp(0, 0) )

    -- Anti Aliased images
    tilemap:getTexture():setAntiAliasTexParameters()


    -- background layer: another image
    local  background = CCSprite:create(s_back)
    -- scale the image (optional)
    background:setScale( 1.5 )
    -- change the transform anchor point (optional)
    background:setAnchorPoint( ccp(0,0) )


    -- create a void node, a parent node
    local  voidNode = CCParallaxNode:create()

    -- NOW add the 3 layers to the 'void' node

    -- background image is moved at a ratio of 0.4x, 0.5y
    voidNode:addChild(background, -1, ccp(0.4,0.5), ccp(0, 0))

    -- tiles are moved at a ratio of 1.0, 1.0y
    voidNode:addChild(tilemap, 1, ccp(1.0,1.0), ccp(0,-200) )

    -- top image is moved at a ratio of 3.0x, 2.5y
    voidNode:addChild( cocosImage, 2, ccp(3.0,2.5), ccp(200,1000) )
    ret:addChild(voidNode, 0, kTagNode)
    local prev = {x = 0, y = 0}
    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            prev.x = x
            prev.y = y
            return true
        elseif  eventType == "moved" then
            local node  = ret:getChildByTag(kTagNode)
            local newX  = node:getPositionX()
            local newY  = node:getPositionY()
            local diffX = x - prev.x
            local diffY = y - prev.y

            node:setPosition( ccpAdd(ccp(newX, newY), ccp(diffX, diffY)) )
            prev.x = x
            prev.y = y
        end
    end
    ret:registerScriptTouchHandler(onTouchEvent)

    return ret
end

function ParallaxTestMain()
    cclog("ParallaxMain")
    Helper.index = 1
    CCDirector:sharedDirector():setDepthTest(true)
    local scene = CCScene:create()

    Helper.createFunctionTable = {
        Parallax1,
        Parallax2
    }
    scene:addChild(Parallax1())
    scene:addChild(CreateBackMenuItem())
    return scene
end
