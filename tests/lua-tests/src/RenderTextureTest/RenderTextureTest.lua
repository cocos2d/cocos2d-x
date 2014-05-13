-- Test #1 by Jason Booth (slipster216)
-- Test #3 by David Deaco (ddeaco)

--/**
--    * Impelmentation of RenderTextureSave
--*/
local function RenderTextureSave()
    local ret = createTestLayer("Touch the screen",
                                "Press 'Save Image' to create an snapshot of the render texture")
    local s = cc.Director:getInstance():getWinSize()
    local target = nil
    local counter = 0
    local brushes = {}
    local function clearImage(tag, pSender)
        target:clear(math.random(), math.random(), math.random(), math.random())
    end

    local function saveImage(tag, pSender)
        local png = string.format("image-%d.png", counter)
        local jpg = string.format("image-%d.jpg", counter)

        target:saveToFile(png, cc.IMAGE_FORMAT_PNG)
        target:saveToFile(jpg, cc.IMAGE_FORMAT_JPEG)

        local pImage = target:newImage()

        local tex = cc.Director:getInstance():getTextureCache():addUIImage(pImage, png)

        pImage:release()

        local sprite = cc.Sprite:createWithTexture(tex)

        sprite:setScale(0.3)
        ret:addChild(sprite)
        sprite:setPosition(cc.p(40, 40))
        sprite:setRotation(counter * 3)

        cclog("Image saved %s and %s", png, jpg)
        counter = counter + 1
    end

    local function onNodeEvent(event)
        if event == "exit" then
            target:release()
            cc.Director:getInstance():getTextureCache():removeUnusedTextures()
        end
    end

    ret:registerScriptHandler(onNodeEvent)

    -- create a render texture, this is what we are going to draw into
    target = cc.RenderTexture:create(s.width, s.height, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
    target:retain()
    target:setPosition(cc.p(s.width / 2, s.height / 2))

    -- note that the render texture is a cc.Node, and contains a sprite of its texture for convience,
    -- so we can just parent it to the scene like any other cc.Node
    ret:addChild(target, -1)

    local function onTouchesMoved(touches, event)
        local start = touches[1]:getLocation()
        local ended = touches[1]:getPreviousLocation()

        target:begin()

        local distance = cc.pGetDistance(start, ended)
        if distance > 1 then
            brushes = {}
            local d = distance
            local i = 0

            for i = 0,d -1 do
                -- create a brush image to draw into the texture with
                local sprite = cc.Sprite:create("Images/fire.png")
                sprite:setColor(cc.c3b(255, 0, 0))
                sprite:setOpacity(20)
                brushes[i + 1] = sprite
            end

            for i = 0,d -1 do
                local difx = ended.x - start.x
                local dify = ended.y - start.y
                local delta = i / distance
                brushes[i + 1]:setPosition(cc.p(start.x + (difx * delta), start.y + (dify * delta)))
                brushes[i + 1]:setRotation(math.random(0, 359))
                local r = math.random(0, 49) / 50.0 + 0.25
                brushes[i + 1]:setScale(r)

                -- Use cc.RANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
                brushes[i + 1]:setColor(cc.c3b(math.random(0, 126) + 128, 255, 255))
                -- Call visit to draw the brush, don't call draw..
                brushes[i + 1]:visit()
            end
        end

        -- finish drawing and return context back to the screen
        target:endToLua()
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
    local eventDispatcher = ret:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ret)
    -- Save Image menu
    cc.MenuItemFont:setFontSize(16)
    local item1 = cc.MenuItemFont:create("Save Image")
    item1:registerScriptTapHandler(saveImage)
    local item2 = cc.MenuItemFont:create("Clear")
    item2:registerScriptTapHandler(clearImage)
    local menu = cc.Menu:create(item1, item2)
    ret:addChild(menu)
    menu:alignItemsVertically()
    menu:setPosition(cc.p(VisibleRect:rightTop().x - 80, VisibleRect:rightTop().y - 30))
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
--     local background = cc.LayerColor:create(cc.c4b(200,200,200,255))
--     addChild(background)

--     local spr_premulti = cc.Sprite:create("Images/fire.png")
--     spr_premulti:setPosition(cc.p(16,48))

--     local spr_nonpremulti = cc.Sprite:create("Images/fire.png")
--     spr_nonpremulti:setPosition(cc.p(16,16))




--     /* A2 & B2 setup */
--     local rend = cc.RenderTexture:create(32, 64, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)

--     if (NULL == rend)

--     return
-- end

-- -- It's possible to modify the RenderTexture blending function by
-- --        [[rend sprite] setBlendFunc:(BlendFunc) GL_ONE, GL_ONE_MINUS_SRC_ALPHAend]

-- rend:begin()
-- spr_premulti:visit()
-- spr_nonpremulti:visit()
-- rend:end()

-- local s = cc.Director:getInstance():getWinSize()

-- --/* A1: setup */
-- spr_premulti:setPosition(cc.p(s.width/2-16, s.height/2+16))
-- --/* B1: setup */
-- spr_nonpremulti:setPosition(cc.p(s.width/2-16, s.height/2-16))

-- rend:setPosition(cc.p(s.width/2+16, s.height/2))

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

--     cc.Director:getInstance():replaceScene(this)
-- end

-- --/**
-- --    * Impelmentation of RenderTextureZbuffer
-- --*/

-- local function RenderTextureZbuffer()

--     this:setTouchEnabled(true)
--     local size = cc.Director:getInstance():getWinSize()
--     local label = cc.LabelTTF:create("vertexZ = 50", "Marker Felt", 64)
--     label:setPosition(cc.p(size.width / 2, size.height * 0.25))
--     this:addChild(label)

--     local label2 = cc.LabelTTF:create("vertexZ = 0", "Marker Felt", 64)
--     label2:setPosition(cc.p(size.width / 2, size.height * 0.5))
--     this:addChild(label2)

--     local label3 = cc.LabelTTF:create("vertexZ = -50", "Marker Felt", 64)
--     label3:setPosition(cc.p(size.width / 2, size.height * 0.75))
--     this:addChild(label3)

--     label:setVertexZ(50)
--     label2:setVertexZ(0)
--     label3:setVertexZ(-50)

--     cc.SpriteFrameCache:getInstance():addSpriteFramesWithFile("Images/bugs/circle.plist")
--     mgr = cc.SpriteBatchNode:create("Images/bugs/circle.png", 9)
--     this:addChild(mgr)
--     sp1 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp2 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp3 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp4 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp5 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp6 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp7 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp8 = cc.Sprite:createWithSpriteFrameName("circle.png")
--     sp9 = cc.Sprite:createWithSpriteFrameName("circle.png")

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
--     sp9:setColor(cc.c3b::YELLOW)
-- end

-- local function title()

--     return "Testing Z Buffer in Render Texture"
-- end

-- local function subtitle()

--     return "Touch screen. It should be green"
-- end

-- local function ccTouchesBegan(cocos2d:cc.Set *touches, cocos2d:cc.Event *event)

--     cc.SetIterator iter
--     cc.Touch *touch
--     for (iter = touches:begin() iter != touches:end() ++iter)

-- touch = (cc.Touch *)(*iter)
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

-- local function ccTouchesMoved(cc.const std::vector<Touch*>& touches, cc.Event* event)

--     cc.SetIterator iter
--     cc.Touch *touch
--     for (iter = touches:begin() iter != touches:end() ++iter)

-- touch = (cc.Touch *)(*iter)
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

-- local function ccTouchesEnded(cc.const std::vector<Touch*>& touches, cc.Event* event)

--     this:renderScreenShot()
-- end

-- local function renderScreenShot()

--     local texture = cc.RenderTexture:create(512, 512)
--     if (NULL == texture)

--     return
-- end
-- texture:setAnchorPoint(cc.p(0, 0))
-- texture:begin()

-- this:visit()

-- texture:end()

-- local sprite = cc.Sprite:createWithTexture(texture:getSprite():getTexture())

-- sprite:setPosition(cc.p(256, 256))
-- sprite:setOpacity(182)
-- sprite:setFlipY(1)
-- this:addChild(sprite, 999999)
-- sprite:setColor(cc.c3b::GREEN)

-- sprite:runAction(cc.Sequence:create(cc.FadeTo:create(2, 0),
--                                    cc.Hide:create(),
--                                    NULL))
-- end

-- -- RenderTextureTestDepthStencil

-- local function RenderTextureTestDepthStencil()

--     local s = cc.Director:getInstance():getWinSize()

--     local sprite = cc.Sprite:create("Images/fire.png")
--     sprite:setPosition(cc.p(s.width * 0.25, 0))
--     sprite:setScale(10)
--     local rend = cc.RenderTexture:create(s.width, s.height, kcc.Texture2DPixelFormat_RGBA4444, GL_DEPTH24_STENCIL8)

--     glStencilMask(0xFF)
--     rend:beginWithClear(0, 0, 0, 0, 0, 0)

--     --! mark sprite quad into stencil buffer
--     glEnable(GL_STENCIL_TEST)
--     glStencilFunc(GL_ALWAYS, 1, 0xFF)
--     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)
--     glColorMask(0, 0, 0, 1)
--     sprite:visit()

--     --! move sprite half width and height, and draw only where not marked
--     sprite:setPosition(cc.p__add(sprite:getPosition(), cc.p__mul(cc.p(sprite:getContentSize().width * sprite:getScale(), sprite:getContentSize().height * sprite:getScale()), 0.5)))
--     glStencilFunc(GL_NOTEQUAL, 1, 0xFF)
--     glColorMask(1, 1, 1, 1)
--     sprite:visit()

--     rend:end()

-- glDisable(GL_STENCIL_TEST)

-- rend:setPosition(cc.p(s.width * 0.5, s.height * 0.5))

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
--     local background = cc.LayerColor:create(cc.c4b(40,40,40,255))
--     addChild(background)

--     -- sprite 1
--     sprite1 = cc.Sprite:create("Images/fire.png")

--     -- sprite 2
--     sprite2 = cc.Sprite:create("Images/fire_rgba8888.pvr")

--     local s = cc.Director:getInstance():getWinSize()

--     /* Create the render texture */
--     local renderTexture = cc.RenderTexture:create(s.width, s.height, kcc.Texture2DPixelFormat_RGBA4444)
--     this:renderTexture = renderTexture

--     renderTexture:setPosition(cc.p(s.width/2, s.height/2))
--     renderTexture:setScale(2.0)

--     /* add the sprites to the render texture */
--     renderTexture:addChild(sprite1)
--     renderTexture:addChild(sprite2)
--     renderTexture:setClearColor(cc.c4f(0, 0, 0, 0))
--     renderTexture:setClearFlags(GL_COLOR_BUFFER_BIT)

--     /* add the render texture to the scene */
--     addChild(renderTexture)

--     renderTexture:setAutoDraw(true)

--     scheduleUpdate()

--     -- Toggle clear on / off
--     local item = cc.MenuItemFont:create("Clear On/Off", this, menu_selector(RenderTextureTargetNode:touched))
--     local menu = cc.Menu:create(item, NULL)
--     addChild(menu)

--     menu:setPosition(cc.p(s.width/2, s.height/2))
-- end

-- local function touched(cc.Object* sender)

--     if (renderTexture:getClearFlags() == 0)

--     renderTexture:setClearFlags(GL_COLOR_BUFFER_BIT)
-- end
-- else

--     renderTexture:setClearFlags(0)
--     renderTexture:setClearColor(cc.c4f( cc.RANDOM_0_1(), cc.RANDOM_0_1(), cc.RANDOM_0_1(), 1))
--     end
-- end

-- local function update(float dt)

--     static float time = 0
--     float r = 80
--     sprite1:setPosition(cc.p(cosf(time * 2) * r, sinf(time * 2) * r))
--     sprite2:setPosition(cc.p(sinf(time * 2) * r, cosf(time * 2) * r))

--     time += dt
-- end

-- local function title()

--     return "Testing Render Target Node"
-- end

-- local function subtitle()

--     return "Sprites should be equal and move with each frame"
-- end

-- -- SpriteRenderTextureBug

-- local function SimpleSprite() : rt(nullptr) {}

--     local function SimpleSprite* SpriteRenderTextureBug:SimpleSprite:create(const char* filename, const cc.rect &rect)

--         SimpleSprite *sprite = new SimpleSprite()
--         if (sprite && sprite:initWithFile(filename, rect))

--         sprite:autorelease()
--     end
--     else

--         cc._SAFE_DELETE(sprite)
--         end

-- return sprite
-- end

-- local function SimpleSprite:draw()

--     if (rt == NULL)

--     local s = cc.Director:getInstance():getWinSize()
--     rt = new cc.RenderTexture()
--     rt:initWithWidthAndHeight(s.width, s.height, cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
-- end
-- rt:beginWithClear(0.0, 0.0, 0.0, 1.0)
-- rt:end()

-- cc._NODE_DRAW_SETUP()

-- BlendFunc blend = getBlendFunc()
-- ccGLBlendFunc(blend.src, blend.dst)

-- ccGLBindTexture2D(getTexture():getName())

-- --
-- -- Attributes
-- --

-- ccGLEnableVertexAttribs(kcc.VertexAttribFlag_PosColorTex)

-- #define kQuadSize sizeof(m_sQuad.bl)
-- long offset = (long)&m_sQuad

-- -- vertex
-- int diff = offsetof( V3F_C4B_T2F, vertices)
-- glVertexAttribPointer(kcc.VertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff))

-- -- texCoods
-- diff = offsetof( V3F_C4B_T2F, texCoords)
-- glVertexAttribPointer(kcc.VertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff))

-- -- color
-- diff = offsetof( V3F_C4B_T2F, colors)
-- glVertexAttribPointer(kcc.VertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff))

-- glDrawArrays(GL_TRIANGLE_STRIP, 0, 4)
-- end

-- local function SpriteRenderTextureBug()

--     setTouchEnabled(true)

--     local s = cc.Director:getInstance():getWinSize()
--     addNewSpriteWithCoords(cc.p(s.width/2, s.height/2))
-- end

-- local function SimpleSprite* SpriteRenderTextureBug:addNewSpriteWithCoords(const cc.p& p)

--     int idx = cc.RANDOM_0_1() * 1400 / 100
--     int x = (idx%5) * 85
--     int y = (idx/5) * 121

--     SpriteRenderTextureBug:SimpleSprite *sprite = SpriteRenderTextureBug:SimpleSprite:create("Images/grossini_dance_atlas.png",
--                                                                                              cc.rect(x,y,85,121))
--     addChild(sprite)

--     sprite:setPosition(p)

--     local action = NULL
--     float rd = cc.RANDOM_0_1()

--     if (rd < 0.20)
--     action = cc.ScaleBy:create(3, 2)
--     else if (rd < 0.40)
--         action = cc.RotateBy:create(3, 360)
--         else if (rd < 0.60)
--             action = cc.Blink:create(1, 3)
--             else if (rd < 0.8 )
--                 action = cc.TintBy:create(2, 0, -255, -255)
--                 else
--                     action = cc.FadeOut:create(2)

--                     local action_back = action:reverse()
--                     local seq = cc.Sequence:create(action, action_back, NULL)

--                     sprite:runAction(cc.RepeatForever:create(seq))

--                     --return sprite
--                     return NULL
--                     end

-- local function ccTouchesEnded(cc.const std::vector<Touch*>& touches, cc.Event* event)

--     cc.SetIterator iter = touches:begin()
--     for( iter != touches:end() ++iter)

-- local location = ((cc.Touch*)(*iter)):getLocation()
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
    local scene = cc.Scene:create()
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
