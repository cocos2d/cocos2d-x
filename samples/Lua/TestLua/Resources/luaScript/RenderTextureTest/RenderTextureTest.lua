-- Test #1 by Jason Booth (slipster216)
-- Test #3 by David Deaco (ddeaco)

--/**
--    * Impelmentation of RenderTextureSave
--*/
local function RenderTextureSave()
    local ret = createTestLayer("Touch the screen",
                                "Press 'Save Image' to create an snapshot of the render texture")
    local s = CCDirector:sharedDirector():getWinSize()
    local m_pTarget = nil
    local m_pBrush = nil
    local m_pTarget = nil
    local counter = 0
    local function clearImage(tag, pSender)
        m_pTarget:clear(math.random(), math.random(), math.random(), math.random())
    end

    local function saveImage(tag, pSender)
        local png = string.format("image-%d.png", counter)
        local jpg = string.format("image-%d.jpg", counter)

        m_pTarget:saveToFile(png, kCCImageFormatPNG)
        m_pTarget:saveToFile(jpg, kCCImageFormatJPEG)

        local pImage = m_pTarget:newCCImage()

        local tex = CCTextureCache:sharedTextureCache():addUIImage(pImage, png)

        pImage:release()

        local sprite = CCSprite:createWithTexture(tex)

        sprite:setScale(0.3)
        ret:addChild(sprite)
        sprite:setPosition(ccp(40, 40))
        sprite:setRotation(counter * 3)

        cclog("Image saved %s and %s", png, jpg)
        counter = counter + 1
    end

    local function onNodeEvent(event)
        if event == "exit" then
            m_pBrush:release()
            m_pTarget:release()
            CCTextureCache:sharedTextureCache():removeUnusedTextures()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    -- create a render texture, this is what we are going to draw into
    m_pTarget = CCRenderTexture:create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888)
    m_pTarget:retain()
    m_pTarget:setPosition(ccp(s.width / 2, s.height / 2))

    -- note that the render texture is a CCNode, and contains a sprite of its texture for convience,
    -- so we can just parent it to the scene like any other CCNode
    ret:addChild(m_pTarget, -1)

    -- create a brush image to draw into the texture with
    m_pBrush = CCSprite:create("Images/fire.png")
    m_pBrush:retain()
    m_pBrush:setColor(ccc3(255, 0, 0))
    m_pBrush:setOpacity(20)


    local prev = {x = 0, y = 0}
    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            prev.x = x
            prev.y = y
            return true
        elseif  eventType == "moved" then
            local diffX = x - prev.x
            local diffY = y - prev.y

            local startP = ccp(x, y)
            local endP = ccp(prev.x, prev.y)

            -- begin drawing to the render texture
            m_pTarget:begin()

            -- for extra points, we'll draw this smoothly from the last position and vary the sprite's
            -- scale/rotation/offset
            local distance = ccpDistance(startP, endP)
            if distance > 1 then
                local d = distance
                local i = 0
                for i = 0, d-1 do
                    local difx = endP.x - startP.x
                    local dify = endP.y - startP.y
                    local delta = i / distance
                    m_pBrush:setPosition(ccp(startP.x + (difx * delta), startP.y + (dify * delta)))
                    m_pBrush:setRotation(math.random(0, 359))
                    local r = math.random(0, 49) / 50.0 + 0.25
                    m_pBrush:setScale(r)

                    -- Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
                    m_pBrush:setColor(ccc3(math.random(0, 126) + 128, 255, 255))
                    -- Call visit to draw the brush, don't call draw..
                    m_pBrush:visit()
                end
            end

            -- finish drawing and return context back to the screen
            m_pTarget:endToLua()
        end

            prev.x = x
            prev.y = y
    end

    ret:setTouchEnabled(true)
    ret:registerScriptTouchHandler(onTouchEvent)
    -- Save Image menu
    CCMenuItemFont:setFontSize(16)
    local item1 = CCMenuItemFont:create("Save Image")
    item1:registerScriptTapHandler(saveImage)
    local item2 = CCMenuItemFont:create("Clear")
    item2:registerScriptTapHandler(clearImage)
    local arr = CCArray:create()
    arr:addObject(item1)
    arr:addObject(item2)
    local menu = CCMenu:createWithArray(arr)
    ret:addChild(menu)
    menu:alignItemsVertically()
    menu:setPosition(ccp(VisibleRect:rightTop().x - 80, VisibleRect:rightTop().y - 30))
    return ret
end



--/**
--    * Impelmentation of RenderTextureIssue937
--*/

-- local function RenderTextureIssue937()

--     /*
--         *     1    2
--         * A: A1   A2
--         *
--         * B: B1   B2
--         *
--         *  A1: premulti sprite
--         *  A2: premulti render
--         *
--         *  B1: non-premulti sprite
--         *  B2: non-premulti render
--     */
--     local background = CCLayerColor:create(ccc4(200,200,200,255))
--     addChild(background)

--     local spr_premulti = CCSprite:create("Images/fire.png")
--     spr_premulti:setPosition(ccp(16,48))

--     local spr_nonpremulti = CCSprite:create("Images/fire.png")
--     spr_nonpremulti:setPosition(ccp(16,16))




--     /* A2 & B2 setup */
--     local rend = CCRenderTexture:create(32, 64, kCCTexture2DPixelFormat_RGBA8888)

--     if (NULL == rend)

--     return
-- end

-- -- It's possible to modify the RenderTexture blending function by
-- --        [[rend sprite] setBlendFunc:(ccBlendFunc) GL_ONE, GL_ONE_MINUS_SRC_ALPHAend]

-- rend:begin()
-- spr_premulti:visit()
-- spr_nonpremulti:visit()
-- rend:end()

-- local s = CCDirector:sharedDirector():getWinSize()

-- --/* A1: setup */
-- spr_premulti:setPosition(ccp(s.width/2-16, s.height/2+16))
-- --/* B1: setup */
-- spr_nonpremulti:setPosition(ccp(s.width/2-16, s.height/2-16))

-- rend:setPosition(ccp(s.width/2+16, s.height/2))

-- addChild(spr_nonpremulti)
-- addChild(spr_premulti)
-- addChild(rend)
-- end

-- local function title()

--     return "Testing issue #937"
-- end

-- local function subtitle()

--     return "All images should be equal..."
-- end

-- local function runThisTest()

--     local  pLayer = nextTestCase()
--     addChild(pLayer)

--     CCDirector:sharedDirector():replaceScene(this)
-- end

-- --/**
-- --    * Impelmentation of RenderTextureZbuffer
-- --*/

-- local function RenderTextureZbuffer()

--     this:setTouchEnabled(true)
--     local size = CCDirector:sharedDirector():getWinSize()
--     local label = CCLabelTTF:create("vertexZ = 50", "Marker Felt", 64)
--     label:setPosition(ccp(size.width / 2, size.height * 0.25))
--     this:addChild(label)

--     local label2 = CCLabelTTF:create("vertexZ = 0", "Marker Felt", 64)
--     label2:setPosition(ccp(size.width / 2, size.height * 0.5))
--     this:addChild(label2)

--     local label3 = CCLabelTTF:create("vertexZ = -50", "Marker Felt", 64)
--     label3:setPosition(ccp(size.width / 2, size.height * 0.75))
--     this:addChild(label3)

--     label:setVertexZ(50)
--     label2:setVertexZ(0)
--     label3:setVertexZ(-50)

--     CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile("Images/bugs/circle.plist")
--     mgr = CCSpriteBatchNode:create("Images/bugs/circle.png", 9)
--     this:addChild(mgr)
--     sp1 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp2 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp3 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp4 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp5 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp6 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp7 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp8 = CCSprite:createWithSpriteFrameName("circle.png")
--     sp9 = CCSprite:createWithSpriteFrameName("circle.png")

--     mgr:addChild(sp1, 9)
--     mgr:addChild(sp2, 8)
--     mgr:addChild(sp3, 7)
--     mgr:addChild(sp4, 6)
--     mgr:addChild(sp5, 5)
--     mgr:addChild(sp6, 4)
--     mgr:addChild(sp7, 3)
--     mgr:addChild(sp8, 2)
--     mgr:addChild(sp9, 1)

--     sp1:setVertexZ(400)
--     sp2:setVertexZ(300)
--     sp3:setVertexZ(200)
--     sp4:setVertexZ(100)
--     sp5:setVertexZ(0)
--     sp6:setVertexZ(-100)
--     sp7:setVertexZ(-200)
--     sp8:setVertexZ(-300)
--     sp9:setVertexZ(-400)

--     sp9:setScale(2)
--     sp9:setColor(ccYELLOW)
-- end

-- local function title()

--     return "Testing Z Buffer in Render Texture"
-- end

-- local function subtitle()

--     return "Touch screen. It should be green"
-- end

-- local function ccTouchesBegan(cocos2d:CCSet *touches, cocos2d:CCEvent *event)

--     CCSetIterator iter
--     CCTouch *touch
--     for (iter = touches:begin() iter != touches:end() ++iter)

-- touch = (CCTouch *)(*iter)
-- local location = touch:getLocation()

-- sp1:setPosition(location)
-- sp2:setPosition(location)
-- sp3:setPosition(location)
-- sp4:setPosition(location)
-- sp5:setPosition(location)
-- sp6:setPosition(location)
-- sp7:setPosition(location)
-- sp8:setPosition(location)
-- sp9:setPosition(location)
-- end
-- end

-- local function ccTouchesMoved(CCSet* touches, CCEvent* event)

--     CCSetIterator iter
--     CCTouch *touch
--     for (iter = touches:begin() iter != touches:end() ++iter)

-- touch = (CCTouch *)(*iter)
-- local location = touch:getLocation()

-- sp1:setPosition(location)
-- sp2:setPosition(location)
-- sp3:setPosition(location)
-- sp4:setPosition(location)
-- sp5:setPosition(location)
-- sp6:setPosition(location)
-- sp7:setPosition(location)
-- sp8:setPosition(location)
-- sp9:setPosition(location)
-- end
-- end

-- local function ccTouchesEnded(CCSet* touches, CCEvent* event)

--     this:renderScreenShot()
-- end

-- local function renderScreenShot()

--     local texture = CCRenderTexture:create(512, 512)
--     if (NULL == texture)

--     return
-- end
-- texture:setAnchorPoint(ccp(0, 0))
-- texture:begin()

-- this:visit()

-- texture:end()

-- local sprite = CCSprite:createWithTexture(texture:getSprite():getTexture())

-- sprite:setPosition(ccp(256, 256))
-- sprite:setOpacity(182)
-- sprite:setFlipY(1)
-- this:addChild(sprite, 999999)
-- sprite:setColor(ccGREEN)

-- sprite:runAction(CCSequence:create(CCFadeTo:create(2, 0),
--                                    CCHide:create(),
--                                    NULL))
-- end

-- -- RenderTextureTestDepthStencil

-- local function RenderTextureTestDepthStencil()

--     local s = CCDirector:sharedDirector():getWinSize()

--     local sprite = CCSprite:create("Images/fire.png")
--     sprite:setPosition(ccp(s.width * 0.25, 0))
--     sprite:setScale(10)
--     local rend = CCRenderTexture:create(s.width, s.height, kCCTexture2DPixelFormat_RGBA4444, GL_DEPTH24_STENCIL8)

--     glStencilMask(0xFF)
--     rend:beginWithClear(0, 0, 0, 0, 0, 0)

--     --! mark sprite quad into stencil buffer
--     glEnable(GL_STENCIL_TEST)
--     glStencilFunc(GL_ALWAYS, 1, 0xFF)
--     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)
--     glColorMask(0, 0, 0, 1)
--     sprite:visit()

--     --! move sprite half width and height, and draw only where not marked
--     sprite:setPosition(ccpAdd(sprite:getPosition(), ccpMult(ccp(sprite:getContentSize().width * sprite:getScale(), sprite:getContentSize().height * sprite:getScale()), 0.5)))
--     glStencilFunc(GL_NOTEQUAL, 1, 0xFF)
--     glColorMask(1, 1, 1, 1)
--     sprite:visit()

--     rend:end()

-- glDisable(GL_STENCIL_TEST)

-- rend:setPosition(ccp(s.width * 0.5, s.height * 0.5))

-- this:addChild(rend)
-- end

-- local function title()

--     return "Testing depthStencil attachment"
-- end

-- local function subtitle()

--     return "Circle should be missing 1/4 of its region"
-- end

-- -- RenderTextureTest
-- local function RenderTextureTargetNode()

--     /*
--         *     1    2
--         * A: A1   A2
--         *
--         * B: B1   B2
--         *
--         *  A1: premulti sprite
--         *  A2: premulti render
--         *
--         *  B1: non-premulti sprite
--         *  B2: non-premulti render
--     */
--     local background = CCLayerColor:create(ccc4(40,40,40,255))
--     addChild(background)

--     -- sprite 1
--     sprite1 = CCSprite:create("Images/fire.png")

--     -- sprite 2
--     sprite2 = CCSprite:create("Images/fire_rgba8888.pvr")

--     local s = CCDirector:sharedDirector():getWinSize()

--     /* Create the render texture */
--     local renderTexture = CCRenderTexture:create(s.width, s.height, kCCTexture2DPixelFormat_RGBA4444)
--     this:renderTexture = renderTexture

--     renderTexture:setPosition(ccp(s.width/2, s.height/2))
--     --          [renderTexture setPosition:ccp(s.width, s.height)]
--     --          renderTexture.scale = 2

--     /* add the sprites to the render texture */
--     renderTexture:addChild(sprite1)
--     renderTexture:addChild(sprite2)
--     renderTexture:setClearColor(ccc4f(0, 0, 0, 0))
--     renderTexture:setClearFlags(GL_COLOR_BUFFER_BIT)

--     /* add the render texture to the scene */
--     addChild(renderTexture)

--     renderTexture:setAutoDraw(true)

--     scheduleUpdate()

--     -- Toggle clear on / off
--     local item = CCMenuItemFont:create("Clear On/Off", this, menu_selector(RenderTextureTargetNode:touched))
--     local menu = CCMenu:create(item, NULL)
--     addChild(menu)

--     menu:setPosition(ccp(s.width/2, s.height/2))
-- end

-- local function touched(CCObject* sender)

--     if (renderTexture:getClearFlags() == 0)

--     renderTexture:setClearFlags(GL_COLOR_BUFFER_BIT)
-- end
-- else

--     renderTexture:setClearFlags(0)
--     renderTexture:setClearColor(ccc4f( CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1))
--     end
-- end

-- local function update(float dt)

--     static float time = 0
--     float r = 80
--     sprite1:setPosition(ccp(cosf(time * 2) * r, sinf(time * 2) * r))
--     sprite2:setPosition(ccp(sinf(time * 2) * r, cosf(time * 2) * r))

--     time += dt
-- end

-- local function title()

--     return "Testing Render Target Node"
-- end

-- local function subtitle()

--     return "Sprites should be equal and move with each frame"
-- end

-- -- SpriteRenderTextureBug

-- local function SimpleSprite() : rt(NULL) {}

--     local function SimpleSprite* SpriteRenderTextureBug:SimpleSprite:create(const char* filename, const CCRect &rect)

--         SimpleSprite *sprite = new SimpleSprite()
--         if (sprite && sprite:initWithFile(filename, rect))

--         sprite:autorelease()
--     end
--     else

--         CC_SAFE_DELETE(sprite)
--         end

-- return sprite
-- end

-- local function SimpleSprite:draw()

--     if (rt == NULL)

--     local s = CCDirector:sharedDirector():getWinSize()
--     rt = new CCRenderTexture()
--     rt:initWithWidthAndHeight(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888)
-- end
-- rt:beginWithClear(0.0, 0.0, 0.0, 1.0)
-- rt:end()

-- CC_NODE_DRAW_SETUP()

-- ccBlendFunc blend = getBlendFunc()
-- ccGLBlendFunc(blend.src, blend.dst)

-- ccGLBindTexture2D(getTexture():getName())

-- --
-- -- Attributes
-- --

-- ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex)

-- #define kQuadSize sizeof(m_sQuad.bl)
-- long offset = (long)&m_sQuad

-- -- vertex
-- int diff = offsetof( ccV3F_C4B_T2F, vertices)
-- glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff))

-- -- texCoods
-- diff = offsetof( ccV3F_C4B_T2F, texCoords)
-- glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff))

-- -- color
-- diff = offsetof( ccV3F_C4B_T2F, colors)
-- glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff))

-- glDrawArrays(GL_TRIANGLE_STRIP, 0, 4)
-- end

-- local function SpriteRenderTextureBug()

--     setTouchEnabled(true)

--     local s = CCDirector:sharedDirector():getWinSize()
--     addNewSpriteWithCoords(ccp(s.width/2, s.height/2))
-- end

-- local function SimpleSprite* SpriteRenderTextureBug:addNewSpriteWithCoords(const CCPoint& p)

--     int idx = CCRANDOM_0_1() * 1400 / 100
--     int x = (idx%5) * 85
--     int y = (idx/5) * 121

--     SpriteRenderTextureBug:SimpleSprite *sprite = SpriteRenderTextureBug:SimpleSprite:create("Images/grossini_dance_atlas.png",
--                                                                                              CCRectMake(x,y,85,121))
--     addChild(sprite)

--     sprite:setPosition(p)

--     local action = NULL
--     float rd = CCRANDOM_0_1()

--     if (rd < 0.20)
--     action = CCScaleBy:create(3, 2)
--     else if (rd < 0.40)
--         action = CCRotateBy:create(3, 360)
--         else if (rd < 0.60)
--             action = CCBlink:create(1, 3)
--             else if (rd < 0.8 )
--                 action = CCTintBy:create(2, 0, -255, -255)
--                 else
--                     action = CCFadeOut:create(2)

--                     local action_back = action:reverse()
--                     local seq = CCSequence:create(action, action_back, NULL)

--                     sprite:runAction(CCRepeatForever:create(seq))

--                     --return sprite
--                     return NULL
--                     end

-- local function ccTouchesEnded(CCSet* touches, CCEvent* event)

--     CCSetIterator iter = touches:begin()
--     for( iter != touches:end() ++iter)

-- local location = ((CCTouch*)(*iter)):getLocation()
-- addNewSpriteWithCoords(location)
-- end
-- end

-- local function title()

--     return "SpriteRenderTextureBug"
-- end

-- local function subtitle()

--     return "Touch the screen. Sprite should appear on under the touch"
-- end

function RenderTextureTestMain()
    cclog("RenderTextureTestMain")
    Helper.index = 1
    local scene = CCScene:create()
    Helper.createFunctionTable = {

        RenderTextureSave,
        -- RenderTextureIssue937,
        -- RenderTextureZbuffer,
        -- RenderTextureTestDepthStencil,
        -- RenderTextureTargetNode,
        -- SpriteRenderTextureBug
    }
    scene:addChild(RenderTextureSave())
    scene:addChild(CreateBackMenuItem())
    return scene
end
