local imageFileName = "Images/grossini.png"

local function initDefaultSprite(filename, spp, layer)
    layer:addChild(spp)
    local s = cc.Director:getInstance():getWinSize()
    local offset = cc.p(0.15 * s.width, 0)
    spp:setPosition(s.width/2 + 0.15 * s.width, s.height/2)


    local sp = cc.Sprite:create(imageFileName)
    layer:addChild(sp)
    sp:setPosition(s.width/2 - 0.15 * s.width, s.height/2)

    local debugForNormalSprite = cc.DrawNode:create()
    sp:addChild(debugForNormalSprite)
    
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(function (touch, event)
        spp:showDebug(true)
        debugForNormalSprite:setVisible(true)
        return true
    end,cc.Handler.EVENT_TOUCH_BEGAN)

    touchListener:registerScriptHandler(function (touch, event)
        local pos = touch:getDelta()
        local newScale = cc.clampf(spp:getScale()+pos.x*0.01, 0.1, 2)
        spp:setScale(newScale)
        sp:setScale(newScale)
    end,cc.Handler.EVENT_TOUCH_MOVED)

    touchListener:registerScriptHandler(function (touch, event)
        spp:showDebug(false)
        debugForNormalSprite:setVisible(false)
    end,cc.Handler.EVENT_TOUCH_ENDED)

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, layer)


    local positions = {}
    local spSize = sp:getContentSize()
    positions[1] = cc.p(0, spSize.height)
    positions[2] = cc.p(spSize.width, spSize.height)
    positions[3] = cc.p(spSize.width, 0)
    positions[4] = cc.p(0,0)
    debugForNormalSprite:drawPoints(positions, 4, 8, cc.c4f(0.0,1.0,1.0,1.0))
    debugForNormalSprite:drawLine(positions[1], positions[2], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[2], positions[3], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[3], positions[4], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[4], positions[1], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[1], positions[3], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:setVisible(false)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 8
    local temp = "Sprite:\nPixels drawn: ".. spSize.width*spSize.height
    local spArea = cc.Label:createWithTTF(ttfConfig, temp)
    sp:addChild(spArea)
    spArea:setAnchorPoint(cc.p(0,1))
    
    temp = "SpritePolygon:\nPixels drawn: "
    local vertCount = "\nverts:" .. spp:getVertCount() 
    local sppArea = cc.Label:createWithTTF(ttfConfig, temp .. spp:getArea() .. vertCount)
    spp:addChild(sppArea)
    sppArea:setAnchorPoint(cc.p(0,1))

    Helper.initWithLayer(layer)
    Helper.titleLabel:setString(layer:title())
    Helper.subtitleLabel:setString(layer:subtitle())

    local function onNodeEvent(event)
        if "enter" == event then
            layer:onEnter()
        elseif "exit" == event then
            layer:onExit()
        end
    end

    layer:registerScriptHandler(onNodeEvent)
end

----------------------------------------
----SpritePolygonTest1
----------------------------------------
local SpritePolygonTest1 = class("SpritePolygonTest1", function ()
    local layer = cc.Layer:create()
    return layer
end)


function SpritePolygonTest1:ctor()
    cc.SpritePolygonCache:getInstance():removeAllSpritePolygonCache()
    local spp = ccexp.SpritePolygon:create(imageFileName)
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))

    self:addChild(spp)
    local s = cc.Director:getInstance():getWinSize()
    local offset = cc.p(0.15 * s.width, 0)
    spp:setPosition(s.width/2 + 0.15 * s.width, s.height/2)


    local sp = cc.Sprite:create(imageFileName)
    self:addChild(sp)
    sp:setPosition(s.width/2 - 0.15 * s.width, s.height/2)

    local debugForNormalSprite = cc.DrawNode:create()
    sp:addChild(debugForNormalSprite)
    
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(function (touch, event)
        spp:showDebug(true)
        debugForNormalSprite:setVisible(true)
        return true
    end,cc.Handler.EVENT_TOUCH_BEGAN)

    touchListener:registerScriptHandler(function (touch, event)
        local pos = touch:getDelta()
        local newScale = cc.clampf(spp:getScale()+pos.x*0.01, 0.1, 2)
        spp:setScale(newScale)
        sp:setScale(newScale)
    end,cc.Handler.EVENT_TOUCH_MOVED)

    touchListener:registerScriptHandler(function (touch, event)
        spp:showDebug(false)
        debugForNormalSprite:setVisible(false)
    end,cc.Handler.EVENT_TOUCH_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, self)


    local positions = {}
    local spSize = sp:getContentSize()
    positions[1] = cc.p(0, spSize.height)
    positions[2] = cc.p(spSize.width, spSize.height)
    positions[3] = cc.p(spSize.width, 0)
    positions[4] = cc.p(0,0)
    debugForNormalSprite:drawPoints(positions, 4, 8, cc.c4f(0.0,1.0,1.0,1.0))
    debugForNormalSprite:drawLine(positions[1], positions[2], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[2], positions[3], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[3], positions[4], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[4], positions[1], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:drawLine(positions[1], positions[3], cc.c4f(0.0,1.0,0.0,1.0))
    debugForNormalSprite:setVisible(false)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 8
    local temp = "Sprite:\nPixels drawn: ".. spSize.width*spSize.height
    local spArea = cc.Label:createWithTTF(ttfConfig, temp)
    sp:addChild(spArea)
    spArea:setAnchorPoint(cc.p(0,1))
    
    temp = "SpritePolygon:\nPixels drawn: "
    local vertCount = "\nverts:" .. spp:getVertCount() 
    local sppArea = cc.Label:createWithTTF(ttfConfig, temp .. spp:getArea() .. vertCount)
    spp:addChild(sppArea)
    sppArea:setAnchorPoint(cc.p(0,1))

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local function onNodeEvent(event)
        if "enter" == event then
            self:onEnter()
        elseif "exit" == event then
            self:onExit()
        end
    end

    self:registerScriptHandler(onNodeEvent)
end

function SpritePolygonTest1:title()
    return "SpritePolygon Creation"
end

function SpritePolygonTest1:subtitle()
    return "SpritePolygon:create(\"Images/grossini.png\")"
end

function SpritePolygonTest1:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonTest1:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
end

----------------------------------------
----SpritePolygonTest2
----------------------------------------
local SpritePolygonTest2 = class("SpritePolygonTest2", function ()
    local layer = cc.Layer:create()
    return layer
end)

function SpritePolygonTest2:ctor()
    local verts = {}
    verts[1]= cc.p(36.5, 242.0-128.5)
    verts[2]= cc.p(27.5, 242.0-133.5)
    verts[3]= cc.p(24.5, 242.0-145.5)
    verts[4]= cc.p(26.5, 242.0-161.5)
    verts[5]= cc.p(33.5, 242.0-168.5)
    verts[6]= cc.p(27.5, 242.0-168.5)
    verts[7]= cc.p(16.5, 242.0-179.5)
    verts[8]= cc.p(30.5, 242.0-197.5)
    verts[9]= cc.p(28.5, 242.0-237.5)
    verts[10]= cc.p(56.5, 242.0-237.5)
    verts[11]= cc.p(54.5, 242.0-197.5)
    verts[12]= cc.p(68.5, 242.0-184.5)
    verts[13]= cc.p(57.5, 242.0-168.5)
    verts[14]= cc.p(51.5, 242.0-168.5)
    verts[15]= cc.p(60.5, 242.0-154.5)
    verts[16]= cc.p(57.5, 242.0-133.5)
    verts[17]= cc.p(48.5, 242.0-127.5)
    verts[18]= cc.p(36.5, 242.0-127.5)

    cc.SpritePolygonCache:getInstance():removeAllSpritePolygonCache()
    local s = ccexp.SpritePolygon:create(imageFileName, verts)
    initDefaultSprite(imageFileName, s, self)
end

function SpritePolygonTest2:title()
    return "SpritePolygon Creation"
end

function SpritePolygonTest2:subtitle()
    return "SpritePolygon:create(\"Images/grossini.png\", verts)"
end

function SpritePolygonTest2:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonTest2:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
end


----------------------------------------
----SpritePolygonTest3
----------------------------------------
local SpritePolygonTest3 = class("SpritePolygonTest3", function ()
    local layer = cc.Layer:create()
    return layer
end)

function SpritePolygonTest3:ctor()
    local verts = {}
    verts[1] = cc.p(33.500000, 73.500000)
    verts[2] = cc.p(27.500000, 73.500000)
    verts[3] = cc.p(16.500000, 62.500000)
    verts[4] = cc.p(30.500000, 44.500000)
    verts[5] = cc.p(54.500000, 44.500000)
    verts[6] = cc.p(51.500000, 73.500000)
    verts[7] = cc.p(60.500000, 87.500000)
    verts[8] = cc.p(26.500000, 80.500000)
    verts[9] = cc.p(24.500000, 96.500000)
    verts[10] = cc.p(57.500000, 108.500000)
    verts[11] = cc.p(36.500000, 113.500000)
    verts[12] = cc.p(48.500000, 114.500000)
    verts[13] = cc.p(36.500000, 114.500000)
    verts[14] = cc.p(27.500000, 108.500000)
    verts[15] = cc.p(68.500000, 57.500000)
    verts[16] = cc.p(57.500000, 73.500000)
    verts[17] = cc.p(56.500000, 4.500000)
    verts[18] = cc.p(28.500000, 4.500000)

    local indices = {0, 1, 2, 3, 0, 2, 4, 0, 3, 5, 0, 4, 5, 6, 0, 0, 6, 7, 8, 7, 6, 6, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10, 8, 10, 13, 14, 5, 4, 15, 5, 14, 4, 3, 16, 3, 17, 16}


    cc.SpritePolygonCache:getInstance():removeAllSpritePolygonCache()
    local s = ccexp.SpritePolygon:create(imageFileName, verts, indices)
    initDefaultSprite(imageFileName, s, self)
end

function SpritePolygonTest3:title()
    return "SpritePolygon Creation"
end

function SpritePolygonTest3:subtitle()
    return "SpritePolygon::create(\"Images/grossini.png\", verts, indices)"
end

function SpritePolygonTest3:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonTest3:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
end


----------------------------------------
----SpritePolygonTest4
----------------------------------------
local SpritePolygonTest4 = class("SpritePolygonTest4", function ()
    local layer = cc.Layer:create()
    return layer
end)

function SpritePolygonTest4:ctor()
    local poss = {
    cc.vec3(33.500000, 73.500000,0),
    cc.vec3(27.500000, 73.500000,0),
    cc.vec3(16.500000, 62.500000,0),
    cc.vec3(30.500000, 44.500000,0),
    cc.vec3(54.500000, 44.500000,0),
    cc.vec3(51.500000, 73.500000,0),
    cc.vec3(60.500000, 87.500000,0),
    cc.vec3(26.500000, 80.500000,0),
    cc.vec3(24.500000, 96.500000,0),
    cc.vec3(57.500000, 108.500000,0),
    cc.vec3(36.500000, 113.500000,0),
    cc.vec3(48.500000, 114.500000,0),
    cc.vec3(36.500000, 114.500000,0),
    cc.vec3(27.500000, 108.500000,0),
    cc.vec3(68.500000, 57.500000,0),
    cc.vec3(57.500000, 73.500000,0),
    cc.vec3(56.500000, 4.500000,0),
    cc.vec3(28.500000, 4.50000, 0),
    }

    local indices = {0, 1, 2, 3, 0, 2, 4, 0, 3, 5, 0, 4, 5, 6, 0, 0, 6, 7, 8, 7, 6, 6, 9, 8, 9, 10, 8, 9, 11, 10, 11, 12, 10, 8, 10, 13, 14, 5, 4, 15, 5, 14, 4, 3, 16, 3, 17, 16}

    local t2f = {
        cc.tex2F(0.394118, 0.392562),
        cc.tex2F(0.323529, 0.392562),
        cc.tex2F(0.194118, 0.483471),
        cc.tex2F(0.358824, 0.632231),
        cc.tex2F(0.641176, 0.632231),
        cc.tex2F(0.605882, 0.392562),
        cc.tex2F(0.711765, 0.276859),
        cc.tex2F(0.311765, 0.334711),
        cc.tex2F(0.288235, 0.202479),
        cc.tex2F(0.676471, 0.103306),
        cc.tex2F(0.429412, 0.061983),
        cc.tex2F(0.570588, 0.053719),
        cc.tex2F(0.429412, 0.053719),
        cc.tex2F(0.323529, 0.103306),
        cc.tex2F(0.805882, 0.524793),
        cc.tex2F(0.676471, 0.392562),
        cc.tex2F(0.664706, 0.962810),
        cc.tex2F(0.335294, 0.962810),
    }

    local v3f_c4b_t2f_table = {
        { vertices = poss[1], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[1]},
        { vertices = poss[2], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[2]},
        { vertices = poss[3], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[3]},
        { vertices = poss[4], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[4]},
        { vertices = poss[5], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[5]},
        { vertices = poss[6], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[6]},
        { vertices = poss[7], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[7]},
        { vertices = poss[8], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[8]},
        { vertices = poss[9], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[9]},
        { vertices = poss[10], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[10]},
        { vertices = poss[11], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[11]},
        { vertices = poss[12], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[12]},
        { vertices = poss[13], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[13]},
        { vertices = poss[14], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[14]},
        { vertices = poss[15], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[15]},
        { vertices = poss[16], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[16]},
        { vertices = poss[17], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[17]},
        { vertices = poss[18], colors = cc.c4b(255, 255, 255, 255), texCoords = t2f[18]},
    }

    cc.SpritePolygonCache:getInstance():removeAllSpritePolygonCache()
    local s = ccexp.SpritePolygon:create(imageFileName, v3f_c4b_t2f_table, indices)
    initDefaultSprite(imageFileName, s, self)
end

function SpritePolygonTest4:title()
    return "SpritePolygon Creation"
end

function SpritePolygonTest4:subtitle()
    return "SpritePolygon::create(\"Images/grossini.png\", vector<V3F_C4B_T2F> v, vector<unsigned short> indices)"
end

function SpritePolygonTest4:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonTest4:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
end

function SpritePolygonTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        SpritePolygonTest1.create,
        SpritePolygonTest2.create,
        SpritePolygonTest3.create,
        SpritePolygonTest4.create,
    }

    scene:addChild(SpritePolygonTest1.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end