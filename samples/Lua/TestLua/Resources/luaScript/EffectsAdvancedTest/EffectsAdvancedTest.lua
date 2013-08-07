local kTagTextLayer = 1
local kTagSprite1 = 1
local kTagSprite2 = 2
local kTagBackground = 1
local kTagLabel = 2

local originCreateLayer = createTestLayer

local function createTestLayer(title, subtitle)
    local ret = originCreateLayer(title, subtitle)
    local bg = CCSprite:create("Images/background3.png")
    ret:addChild(bg, 0, kTagBackground)
    bg:setPosition( VisibleRect:center() )

    local  grossini = CCSprite:create("Images/grossinis_sister2.png")
    bg:addChild(grossini, 1, kTagSprite1)
    grossini:setPosition( ccp(VisibleRect:left().x+VisibleRect:getVisibleRect().size.width/3.0, VisibleRect:bottom().y+ 200) )
    local  sc = CCScaleBy:create(2, 5)
    local  sc_back = sc:reverse()
    local arr = CCArray:create()
    arr:addObject(sc)
    arr:addObject(sc_back)
    grossini:runAction( CCRepeatForever:create(CCSequence:create(arr)))

    local  tamara = CCSprite:create("Images/grossinis_sister1.png")
    bg:addChild(tamara, 1, kTagSprite2)
    tamara:setPosition( ccp(VisibleRect:left().x+2*VisibleRect:getVisibleRect().size.width/3.0,VisibleRect:bottom().y+200) )
    local  sc2 = CCScaleBy:create(2, 5)
    local  sc2_back = sc2:reverse()
    arr = CCArray:create()
    arr:addObject(sc2)
    arr:addObject(sc2_back)
    tamara:runAction( CCRepeatForever:create(CCSequence:create(arr)))

    return ret
end


--------------------------------------------------------------------
--
-- Effect1
--
--------------------------------------------------------------------
local function Effect1()
    local ret = createTestLayer("Lens + Waves3d and OrbitCamera")
    local  target = ret:getChildByTag(kTagBackground)

    -- To reuse a grid the grid size and the grid type must be the same.
    -- in this case:
    --     Lens3D is Grid3D and it's size is (15,10)
    --     Waves3D is Grid3D and it's size is (15,10)

    local size = CCDirector:sharedDirector():getWinSize()
    local  lens = CCLens3D:create(0.0, CCSizeMake(15,10), ccp(size.width/2,size.height/2), 240)
    local  waves = CCWaves3D:create(10, CCSizeMake(15,10), 18, 15)

    local  reuse = CCReuseGrid:create(1)
    local  delay = CCDelayTime:create(8)

    local  orbit = CCOrbitCamera:create(5, 1, 2, 0, 180, 0, -90)
    local  orbit_back = orbit:reverse()
    local arr = CCArray:create()
    arr:addObject(orbit)
    arr:addObject(orbit_back)
    target:runAction( CCRepeatForever:create( CCSequence:create(arr)))
    arr = CCArray:create()
    arr:addObject(lens)
    arr:addObject(delay)
    arr:addObject(reuse)
    arr:addObject(waves)
    target:runAction( CCSequence:create(arr))
    return ret
end

--------------------------------------------------------------------
--
-- Effect2
--
--------------------------------------------------------------------
local function Effect2()
    local ret = createTestLayer("ShakyTiles + ShuffleTiles + TurnOffTiles")
    local  target = ret:getChildByTag(kTagBackground)

    -- To reuse a grid the grid size and the grid type must be the same.
    -- in this case:
    --     ShakyTiles is TiledGrid3D and it's size is (15,10)
    --     Shuffletiles is TiledGrid3D and it's size is (15,10)
    --       TurnOfftiles is TiledGrid3D and it's size is (15,10)
    local  shaky = CCShakyTiles3D:create(5, CCSizeMake(15,10), 4, false)
    local  shuffle = CCShuffleTiles:create(0, CCSizeMake(15,10), 3)
    local  turnoff = CCTurnOffTiles:create(0, CCSizeMake(15,10), 3)
    local  turnon = turnoff:reverse()

    -- reuse 2 times:
    --   1 for shuffle
    --   2 for turn off
    --   turnon tiles will use a new grid
    local  reuse = CCReuseGrid:create(2)

    local  delay = CCDelayTime:create(1)

    local arr = CCArray:create()
    arr:addObject(shaky)
    arr:addObject(delay)
    arr:addObject(reuse)
    arr:addObject(shuffle)
    arr:addObject(tolua.cast(delay:copy():autorelease(), "CCAction"))
    arr:addObject(turnoff)
    arr:addObject(turnon)
    target:runAction(CCSequence:create(arr))
    return ret
end

--------------------------------------------------------------------
--
-- Effect3
--
--------------------------------------------------------------------
local function Effect3()
    local ret = createTestLayer("Effects on 2 sprites")
    local  bg = ret:getChildByTag(kTagBackground)
    local  target1 = bg:getChildByTag(kTagSprite1)
    local  target2 = bg:getChildByTag(kTagSprite2)

    local  waves = CCWaves:create(5, CCSizeMake(15,10), 5, 20, true, false)
    local  shaky = CCShaky3D:create(5, CCSizeMake(15,10), 4, false)

    target1:runAction( CCRepeatForever:create( waves ) )
    target2:runAction( CCRepeatForever:create( shaky ) )

    -- moving background. Testing issue #244
    local  move = CCMoveBy:create(3, ccp(200,0) )
    local arr = CCArray:create()
    arr:addObject(move)
    arr:addObject(move:reverse())
    bg:runAction(CCRepeatForever:create( CCSequence:create(arr)))
    return ret
end

--------------------------------------------------------------------
--
-- Effect4
--
--------------------------------------------------------------------

-- class Lens3DTarget : public CCNode

-- public:
-- virtual void setPosition(const CCPoint& var)

-- m_pLens3D:setPosition(var)
-- end

-- virtual const CCPoint& getPosition()

-- return m_pLens3D:getPosition()
-- end

-- static Lens3DTarget* create(CCLens3D* pAction)

-- Lens3DTarget* pRet = new Lens3DTarget()
-- pRet:m_pLens3D = pAction
-- pRet:autorelease()
-- return pRet
-- end
-- private:

-- Lens3DTarget()
-- : m_pLens3D(NULL)
-- {}

-- CCLens3D* m_pLens3D
-- end

local function Effect4()
    local ret = createTestLayer("Jumpy Lens3D")
    local  lens = CCLens3D:create(10, CCSizeMake(32,24), ccp(100,180), 150)
    local  move = CCJumpBy:create(5, ccp(380,0), 100, 4)
    local  move_back = move:reverse()
    local arr = CCArray:create()
    arr:addObject(move)
    arr:addObject(move_back)
    local  seq = CCSequence:create( arr)

    --    /* In cocos2d-iphone, the type of action's target is 'id', so it supports using the instance of 'CCLens3D' as its target.
    --        While in cocos2d-x, the target of action only supports CCNode or its subclass,
    --        so we make an encapsulation for CCLens3D to achieve that.
    --    */

    local  director = CCDirector:sharedDirector()
    -- local  pTarget = Lens3DTarget:create(lens)
    -- -- Please make sure the target been added to its parent.
    -- ret:addChild(pTarget)

    -- director:getActionManager():addAction(seq, pTarget, false)
    ret:runAction( lens )
    return ret
end

--------------------------------------------------------------------
--
-- Effect5
--
--------------------------------------------------------------------
local function Effect5()
    local ret = createTestLayer("Test Stop-Copy-Restar")

    local  effect = CCLiquid:create(2, CCSizeMake(32,24), 1, 20)
    local arr = CCArray:create()
    arr:addObject(effect)
    arr:addObject(CCDelayTime:create(2))
    arr:addObject(CCStopGrid:create())

    local  stopEffect = CCSequence:create(arr)
    local  bg = ret:getChildByTag(kTagBackground)
    bg:runAction(stopEffect)
    local function onNodeEvent(event)
        if event == "exit" then
            CCDirector:sharedDirector():setProjection(kCCDirectorProjection3D)
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    return ret
end

--------------------------------------------------------------------
--
-- Issue631
--
--------------------------------------------------------------------
local function Issue631()
    local ret = createTestLayer("Testing Opacity",
                       "Effect image should be 100% opaque. Testing issue #631")
    local arr = CCArray:create()
    arr:addObject(CCDelayTime:create(2.0))
    arr:addObject(CCShaky3D:create(5.0, CCSizeMake(5, 5), 16, false))
    local  effect = CCSequence:create(arr)

    -- cleanup
    local  bg = ret:getChildByTag(kTagBackground)
    ret:removeChild(bg, true)

    -- background
    local  layer = CCLayerColor:create( ccc4(255,0,0,255) )
    ret:addChild(layer, -10)
    local  sprite = CCSprite:create("Images/grossini.png")
    sprite:setPosition( ccp(50,80) )
    layer:addChild(sprite, 10)

    -- foreground
    local  layer2 = CCLayerColor:create(ccc4( 0, 255,0,255 ) )
    local  fog = CCSprite:create("Images/Fog.png")

    local bf = ccBlendFunc()
    bf.src = GL_SRC_ALPHA
    bf.dst = GL_ONE_MINUS_SRC_ALPHA

    fog:setBlendFunc(bf)
    layer2:addChild(fog, 1)
    ret:addChild(layer2, 1)

    layer2:runAction( CCRepeatForever:create(effect) )
    return ret
end

function EffectAdvancedTestMain()
    cclog("EffectAdvancedTestMain")
    Helper.index = 1

    local scene = CCScene:create()
    Helper.createFunctionTable = {
        Effect3,
        Effect2,
        Effect1,
        Effect4,
        Effect5,
        Issue631
    }
    scene:addChild(Effect3())
    scene:addChild(CreateBackMenuItem())
    return scene
end
