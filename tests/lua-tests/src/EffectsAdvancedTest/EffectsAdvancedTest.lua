local kTagTextLayer = 1
local kTagSprite1 = 1
local kTagSprite2 = 2
local kTagBackground = 1
local kTagLabel = 2

local originCreateLayer = createTestLayer

local function createTestLayer(title, subtitle)
    local ret = originCreateLayer(title, subtitle)
    local bgNode = cc.NodeGrid:create()
    bgNode:setAnchorPoint(cc.p(0.5,0.5))
    ret:addChild(bgNode,0,kTagBackground)

    local bg = cc.Sprite:create("Images/background3.png")
    bg:setPosition( VisibleRect:center())
    bgNode:addChild(bg)

    local target1 = cc.NodeGrid:create()
    target1:setAnchorPoint(cc.p(0.5,0.5))
    local  grossini = cc.Sprite:create("Images/grossinis_sister2.png")
    target1:addChild(grossini)
    bgNode:addChild(target1,1,kTagSprite1)
    target1:setPosition(cc.p(VisibleRect:left().x+VisibleRect:getVisibleRect().width/3.0, VisibleRect:bottom().y+ 200) )
    local  sc = cc.ScaleBy:create(2, 5)
    local  sc_back = sc:reverse()
    target1:runAction( cc.RepeatForever:create(cc.Sequence:create(sc, sc_back)))

    local  target2 = cc.NodeGrid:create()
    target2:setAnchorPoint(cc.p(0.5,0.5))
    local  tamara = cc.Sprite:create("Images/grossinis_sister1.png")
    target2:addChild(tamara)
    bgNode:addChild(target2,1,kTagSprite2)
    target2:setPosition( cc.p(VisibleRect:left().x+2*VisibleRect:getVisibleRect().width/3.0,VisibleRect:bottom().y+200) )
    local  sc2 = cc.ScaleBy:create(2, 5)
    local  sc2_back = sc2:reverse()
    target2:runAction( cc.RepeatForever:create(cc.Sequence:create(sc2, sc2_back)))

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

    local size = cc.Director:getInstance():getWinSize()
    local  lens = cc.Lens3D:create(0.0, cc.size(15,10), cc.p(size.width/2,size.height/2), 240)
    local  waves = cc.Waves3D:create(10, cc.size(15,10), 18, 15)

    local  reuse = cc.ReuseGrid:create(1)
    local  delay = cc.DelayTime:create(8)

    -- local  orbit = cc.OrbitCamera:create(5, 1, 2, 0, 180, 0, -90)
    -- local  orbit_back = orbit:reverse()
    -- target:runAction( cc.RepeatForever:create( cc.Sequence:create(orbit, orbit_back)))
    target:runAction( cc.Sequence:create(lens, delay, reuse, waves))
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
    local  shaky = cc.ShakyTiles3D:create(5, cc.size(15,10), 4, false)
    local  shuffle = cc.ShuffleTiles:create(0, cc.size(15,10), 3)
    local  turnoff = cc.TurnOffTiles:create(0, cc.size(15,10), 3)
    local  turnon = turnoff:reverse()

    -- reuse 2 times:
    --   1 for shuffle
    --   2 for turn off
    --   turnon tiles will use a new grid
    local  reuse = cc.ReuseGrid:create(2)

    local  delay = cc.DelayTime:create(1)

    target:runAction(cc.Sequence:create(shaky, delay ,reuse, shuffle, delay:clone(), turnoff, turnon))
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

    local  waves = cc.Waves:create(5, cc.size(15,10), 5, 20, true, false)
    local  shaky = cc.Shaky3D:create(5, cc.size(15,10), 4, false)

    target1:runAction( cc.RepeatForever:create( waves ) )
    target2:runAction( cc.RepeatForever:create( shaky ) )

    -- moving background. Testing issue #244
    local  move = cc.MoveBy:create(3, cc.p(200,0) )
    bg:runAction(cc.RepeatForever:create( cc.Sequence:create(move, move:reverse())))
    return ret
end

--------------------------------------------------------------------
--
-- Effect4
--
--------------------------------------------------------------------

-- class Lens3DTarget : public cc.Node

-- public:
-- virtual void setPosition(const CCPoint& var)

-- m_pLens3D:setPosition(var)
-- end

-- virtual const CCPoint& getPosition()

-- return m_pLens3D:getPosition()
-- end

-- static Lens3DTarget* create(cc.Lens3D* pAction)

-- Lens3DTarget* pRet = new Lens3DTarget()
-- pRet:m_pLens3D = pAction
-- pRet:autorelease()
-- return pRet
-- end
-- private:

-- Lens3DTarget()
-- : m_pLens3D(nullptr)
-- {}

-- cc.Lens3D* m_pLens3D
-- end

local function Effect4()
    local ret = createTestLayer("Jumpy Lens3D")
    local  lens = cc.Lens3D:create(10, cc.size(32,24), cc.p(100,180), 150)
    local  move = cc.JumpBy:create(5, cc.p(380,0), 100, 4)
    local  move_back = move:reverse()
    local  seq = cc.Sequence:create( move, move_back)

    --    /* In cocos2d-iphone, the type of action's target is 'id', so it supports using the instance of 'cc.Lens3D' as its target.
    --        While in cocos2d-x, the target of action only supports cc.Node or its subclass,
    --        so we make an encapsulation for cc.Lens3D to achieve that.
    --    */

    local  director = cc.Director:getInstance()
    -- local  pTarget = Lens3DTarget:create(lens)
    -- -- Please make sure the target been added to its parent.
    -- ret:addChild(pTarget)

    -- director:getActionManager():addAction(seq, pTarget, false)
    local  bg = ret:getChildByTag(kTagBackground)
    bg:runAction( lens )
    return ret
end

--------------------------------------------------------------------
--
-- Effect5
--
--------------------------------------------------------------------
local function Effect5()
    local ret = createTestLayer("Test Stop-Copy-Restar")

    local  effect = cc.Liquid:create(2, cc.size(32,24), 1, 20)

    local  stopEffect = cc.Sequence:create(effect, cc.DelayTime:create(2), cc.StopGrid:create())
    local  bg = ret:getChildByTag(kTagBackground)
    bg:runAction(stopEffect)
    local function onNodeEvent(event)
        if event == "exit" then
            cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION_3D)
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

    local  effect = cc.Sequence:create(cc.DelayTime:create(2.0),cc.Shaky3D:create(5.0, cc.size(5, 5), 16, false))

    -- cleanup
    local  bg = ret:getChildByTag(kTagBackground)
    ret:removeChild(bg, true)

    -- background
    local  layer = cc.LayerColor:create( cc.c4b(255,0,0,255) )
    ret:addChild(layer, -10)
    local  sprite = cc.Sprite:create("Images/grossini.png")
    sprite:setPosition( cc.p(50,80) )
    layer:addChild(sprite, 10)

    -- foreground
    local  layer2BaseGrid = cc.NodeGrid:create()
    local  layer2 = cc.LayerColor:create(cc.c4b( 0, 255,0,255 ) )
    local  fog = cc.Sprite:create("Images/Fog.png")

    --local bf = BlendFunc()
    --bf.src = GL_SRC_ALPHA
    --bf.dst = GL_ONE_MINUS_SRC_ALPHA

    fog:setBlendFunc(gl.SRC_ALPHA , gl.ONE_MINUS_SRC_ALPHA )
    layer2:addChild(fog, 1)
    ret:addChild(layer2BaseGrid, 1)
    layer2BaseGrid:addChild(layer2)

    layer2BaseGrid:runAction( cc.RepeatForever:create(effect) )
    return ret
end

function EffectAdvancedTestMain()
    cclog("EffectAdvancedTestMain")
    Helper.index = 1

    local scene = cc.Scene:create()
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
