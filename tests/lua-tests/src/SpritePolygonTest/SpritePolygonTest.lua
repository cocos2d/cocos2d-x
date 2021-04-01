local imageFileName = "Images/grossini.png"

local SpritePolygonTestDemo = class("SpritePolygonTestDemo", function()
    local layer = cc.Layer:create()
    return layer
end)

function SpritePolygonTestDemo:registerNodeEvent()
    local function onNodeEvent(event)
        if "enter" == event then
            self:onEnter()
        elseif "exit" == event then
            self:onExit()
        end
    end

    self:registerScriptHandler(onNodeEvent)
end

function SpritePolygonTestDemo:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonTestDemo:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
end

----------------------------------------
----SpritePolygonTest1
----------------------------------------
local SpritePolygonTest1 = class("SpritePolygonTest1", SpritePolygonTestDemo)

function SpritePolygonTest1:make2Sprites()
    -- body
end

function SpritePolygonTest1:ctor()

    local s = cc.Director:getInstance():getWinSize()
    local offset = cc.p(0.15 * s.width, 0)
    local filename = s_pPathGrossini
    local info =  cc.AutoPolygon:generatePolygon(filename)
    local spp  =  cc.Sprite:create(info)
    self:addChild(spp)
    spp:setPosition(cc.p(s.width / 2 + offset.x, s.height / 2 + offset.y))


    local sp = cc.Sprite:create(filename)
    self:addChild(sp)
    sp:setPosition(cc.p(s.width/2 - offset.x, s.height/2 - offset.y))

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 8

    local temp = "Sprite:\nPixels drawn: "
    local spSize = sp:getContentSize()
    local spArea = cc.Label:createWithTTF(ttfConfig, temp .. (spSize.width * spSize.height))
    sp:addChild(spArea)
    spArea:setAnchorPoint(cc.p(0, 1))

    temp = "SpritePolygon:\nPixels drawn: "
    local vertCount = "\nverts:" .. info:getVertCount()
    local sppArea = cc.Label:createWithTTF(ttfConfig, temp .. math.floor(info:getArea()) .. vertCount)
    spp:addChild(sppArea)
    sppArea:setAnchorPoint(cc.p(0, 1))

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self:registerNodeEvent()
end

function SpritePolygonTest1:title()
    return "SpritePolygon Creation"
end

function SpritePolygonTest1:subtitle()
    return "Sprite:create(AutoPolygon:generatePolygon(filename))"
end

----------------------------------------
----SpritePolygonTest2
----------------------------------------
local SpritePolygonTest2 = class("SpritePolygonTest2", SpritePolygonTestDemo)

function SpritePolygonTest2:make2Sprites()
    local s = cc.Director:getInstance():getWinSize()
    local offset = cc.p(0.15 * s.width, 0)
    local filename = s_pPathGrossini
    local head = cc.rect(30, 25, 25, 25)
    local info =  cc.AutoPolygon:generatePolygon(filename, head)
    self.spp  =  cc.Sprite:create(info)
    self:addChild(self.spp)
    self.spp:setPosition(cc.p(s.width / 2 + offset.x, s.height / 2 + offset.y))


    self.sp = cc.Sprite:create(filename,head)
    self:addChild(self.sp)
    self.sp:setPosition(cc.p(s.width/2 - offset.x, s.height/2 - offset.y))


    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 8

    local temp = "Sprite:\nPixels drawn: "
    local spSize = self.sp:getContentSize()
    local spArea = cc.Label:createWithTTF(ttfConfig, temp .. (spSize.width * spSize.height))
    self.sp:addChild(spArea)
    spArea:setAnchorPoint(cc.p(0, 1))

    temp = "SpritePolygon:\nPixels drawn: "
    local vertCount = "\nverts:" .. info:getVertCount()
    local sppArea = cc.Label:createWithTTF(ttfConfig, temp .. math.floor(info:getArea()) .. vertCount)
    self.spp:addChild(sppArea)
    sppArea:setAnchorPoint(cc.p(0, 1))
end

function SpritePolygonTest2:ctor()
    self:make2Sprites()

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self:registerNodeEvent()

end

function SpritePolygonTest2:title()
    return "SpritePolygon Creation with a rect"
end

function SpritePolygonTest2:subtitle()
    return "Sprite:create(AutoPolygon:generatePolygon(filename, rect))"
end

----------------------------------------
----SpritePolygonTest3
----------------------------------------
local SpritePolygonTest3 = class("SpritePolygonTest3", SpritePolygonTestDemo)

function SpritePolygonTest3:makeSprite(filename, pos)
    local quadSize = cc.Sprite:create(filename):getContentSize()
    local originalSize = quadSize.width * quadSize.height
    local info = cc.AutoPolygon:generatePolygon(filename)
    local ret = cc.Sprite:create(info)
    ret:setPosition(pos)
    
    local spArea = cc.Label:createWithTTF(self._ttfConfig, filename .. "\nVerts: " .. info:getVertCount() .. "\nPixels: " .. math.floor(info:getArea() / originalSize * 100)  .. "%")
    ret:addChild(spArea)
    spArea:setAnchorPoint(cc.p(0,1))
    ret:setName(filename)
    ret:setAnchorPoint(cc.p(0.5, 0))
    return ret 
end

function SpritePolygonTest3:makeSprites(list, count, y)
    local vsize = cc.Director:getInstance():getVisibleSize()
    local offset = (vsize.width - 100) / (count - 1)
    for i = 1, count do
        local sp = self:makeSprite(list[i], cc.p(50 + offset * (i - 1), y))
        self:addChild(sp)
    end
end

function SpritePolygonTest3:updateLabel(sprite, polygonInfo)
    local label = sprite:getChildren()[1]
    local filename = sprite:getName()
    local scaleFactor = cc.Director:getInstance():getContentScaleFactor()
    local size = cc.size(polygonInfo.rect.width / scaleFactor , polygonInfo.rect.height / scaleFactor )
    local labelInfo = filename .. "\nVerts: " .. polygonInfo:getVertCount() .. "\nPixels: " .. math.floor(polygonInfo:getArea() / (size.width*size.height)*100) .. "%"
    label:setString(labelInfo)
end

function SpritePolygonTest3:ctor()
    self._ttfConfig = {}
    self._ttfConfig.fontFilePath = "fonts/arial.ttf"
    self._ttfConfig.fontSize = 8

    local vsize = cc.Director:getInstance():getVisibleSize()

    local slider = ccui.Slider:create()
    slider:loadBarTexture("cocosui/sliderTrack.png")
    slider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosui/sliderProgress.png")
    slider:setPosition(cc.p(vsize.width/2, vsize.height/4))
    

        local function percentChangedEvent(sender,eventType)
        if eventType == ccui.SliderEventType.percentChanged then
            local slider = sender
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setString(percent)
        end
    end 

    slider:addEventListener(function(sender, eventType)
        local epsilon = math.pow(sender:getPercent() / 100.0 , 2) * 19.0 + 1.0
        local children = self:getChildren()
        for i = 1, #children do
            local child = children[i]
            if child:getName() ~= nil and child:getName() ~= "" then
                local file = child:getName()
                local info = cc.AutoPolygon:generatePolygon(file, cc.rect(0, 0, 0, 0), epsilon)
                child:setPolygonInfo(info)
                self:updateLabel(child, info)
            end

        end
        self._epsilonLabel:setString("Epsilon: " .. epsilon)
    end)
    slider:setPercent(math.sqrt(1.0 /19.0 )*100)
    
    self._epsilonLabel = cc.Label:createWithTTF(self._ttfConfig, "Epsilon: 2.0")
    self:addChild(self._epsilonLabel)
    self._epsilonLabel:setPosition(cc.p(vsize.width/2, vsize.height/4 + 15))
    self:addChild(slider)

    local list = {
        "Images/arrows.png",
        "Images/CyanTriangle.png",
        s_pPathB2,
        "Images/elephant1_Diffuse.png"
    }
    local count = 4
    self:makeSprites(list, count, vsize.height / 2)

    self:registerNodeEvent()

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())
end

function SpritePolygonTest3:title()
    return "Optimization Value (default:2.0)"
end

function SpritePolygonTest3:subtitle()
    return ""
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
local SpritePolygonTest4 = class("SpritePolygonTest4", SpritePolygonTestDemo)

function SpritePolygonTest4:ctor()
    self._ttfConfig = {}
    self._ttfConfig.fontFilePath = "fonts/arial.ttf"
    self._ttfConfig.fontSize = 8

    local vsize = cc.Director:getInstance():getVisibleSize()

    local slider = ccui.Slider:create()
    slider:loadBarTexture("cocosui/sliderTrack.png")
    slider:loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "")
    slider:loadProgressBarTexture("cocosui/sliderProgress.png")
    slider:setPosition(cc.p(vsize.width/2, vsize.height/4))
    

        local function percentChangedEvent(sender,eventType)
        if eventType == ccui.SliderEventType.percentChanged then
            local slider = sender
            local percent = "Percent " .. slider:getPercent()
            self._displayValueLabel:setString(percent)
        end
    end 

    slider:addEventListener(function(sender, eventType)
        local epsilon = math.pow(sender:getPercent() / 100.0 , 2) * 19.0 + 1.0
        local children = self:getChildren()
        for i = 1, #children do
            local child = children[i]
            if child:getName() ~= nil and child:getName() ~= "" then
                local file = child:getName()
                local info = cc.AutoPolygon:generatePolygon(file, cc.rect(0, 0, 0, 0), epsilon)
                child:setPolygonInfo(info)
                self:updateLabel(child, info)
            end

        end
        self._epsilonLabel:setString("Epsilon: " .. epsilon)
    end)
    slider:setPercent(math.sqrt(1.0 /19.0 )*100)
    
    self._epsilonLabel = cc.Label:createWithTTF(self._ttfConfig, "Epsilon: 2.0")
    self:addChild(self._epsilonLabel)
    self._epsilonLabel:setPosition(cc.p(vsize.width/2, vsize.height/4 + 15))
    self:addChild(slider)

    local list = {
        imageFileName,
        "Images/grossinis_sister1.png",
        "Images/grossinis_sister2.png",
    }
    local count = 3
    self:makeSprites(list, count, vsize.height / 2)

    self:registerNodeEvent()

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())
end

function SpritePolygonTest4:title()
    return "Optimization Value (default:2.0)"
end

function SpritePolygonTest4:subtitle()
    return ""
end

function SpritePolygonTest4:updateLabel(sprite, polygonInfo)
    local label = sprite:getChildren()[1]
    local filename = sprite:getName()
    local rectSize = cc.size(polygonInfo.rect.width, polygonInfo.rect.height)
    local size = cc.size(rectSize.width / cc.Director:getInstance():getContentScaleFactor(), rectSize.height / cc.Director:getInstance():getContentScaleFactor())
    local labelInfo = filename .. "\nVerts: " .. polygonInfo:getVertCount() .. "\nPixels: " .. math.floor(polygonInfo:getArea() / (size.width*size.height)*100) .. "%"
    label:setString(labelInfo)
end

function SpritePolygonTest4:makeSprite(filename, pos)
    local quadSize = cc.Sprite:create(filename):getContentSize()
    local originalSize = quadSize.width * quadSize.height
    local info = cc.AutoPolygon:generatePolygon(filename)
    local ret = cc.Sprite:create(info)
    ret:setPosition(pos)
    
    local spArea = cc.Label:createWithTTF(self._ttfConfig, filename .. "\nVerts: " .. info:getVertCount() .. "\nPixels: " .. math.floor(info:getArea() / originalSize * 100)  .. "%")
    ret:addChild(spArea)
    spArea:setAnchorPoint(cc.p(0,1))
    ret:setName(filename)
    ret:setAnchorPoint(cc.p(0.5, 0))
    return ret 
end

function SpritePolygonTest4:makeSprites(list, count, y)
    local vsize = cc.Director:getInstance():getVisibleSize()
    local offset = (vsize.width - 100) / (count - 1)
    for i = 1, count do
        local sp = self:makeSprite(list[i], cc.p(50 + offset * (i - 1), y))
        self:addChild(sp)
    end
end

function SpritePolygonTest4:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonTest4:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
end


----------------------------------------
----SpritePolygonPerformance
----------------------------------------
local SpritePolygonPerformance = class("SpritePolygonPerformance", SpritePolygonTestDemo)


function SpritePolygonPerformance:ctor()
    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self:init()
    self:initExtend()

    self:registerNodeEvent()
end

function SpritePolygonPerformance:title()
    return "SpritePolygonPerformance"
end

function SpritePolygonPerformance:subtitle()
    return ""
end

function SpritePolygonPerformance:updateLabel()
    local temp = "Nodes: " .. self._spriteCount .. " Triangles: " .. self._triCount .. "\nPixels: " .. self._pixelCount .. " Vertices: " .. self._vertCount
    if not self.ended then
        local labelInfo = "Nodes: " .. self._spriteCount .. "   Triangles: " .. self._triCount .. "\nPixels: " .. self._pixelCount .. "   Vertices: " .. self._vertCount
        self._perfLabel:setString(labelInfo)
    end
end

function SpritePolygonPerformance:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(102.0/255, 184.0/255, 204.0/255, 255.0))
end

function SpritePolygonPerformance:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0.0, 0.0, 0.0, 1.0))
    self:unscheduleUpdate()
end

function SpritePolygonPerformance:init()
    local ttfConfig  = { fontFilePath = "fonts/arial.ttf",  fontSize = 8 }
    self._perfLabel = cc.Label:createWithTTF(ttfConfig, "performance test")
    self:addChild(self._perfLabel)
    self._perfLabel:setPosition(cc.Director:getInstance():getVisibleSize().width / 2, 80)

    self._spriteCount, self._vertCount, self._triCount, self._pixelCount, self._continuousLowDt = 0,0,0,0,0
    
    local size = cc.Director:getInstance():getVisibleSize()
    self._elapsedTime = 0
    self._posX,self._leftX = size.width * 0.15, size.width * 0.15
    self._rightX = size.width*0.85
    self._posY = size.height/2
    self._prevDt = 0.016
    self._goRight = true
    self._ended = false
    self._continuousHighDtTime = 0.0
    self._waitingTime = 0.0

    self:scheduleUpdateWithPriorityLua(function (dt)
        dt = dt * 0.3 + self._prevDt * 0.7
        self._prevDt = dt
        self._elapsedTime = self._elapsedTime + dt
        local loops = math.floor((0.025 - dt)*1000)
        if dt < 0.025 and loops > 0 then
            self._continuousHighDtTime = cc.clampf(self._continuousHighDtTime-dt*2, 0.0, 1.0)
            self._waitingTime = cc.clampf(self._waitingTime-dt, 0.0, 5.0)
            self._continuousLowDt = self._continuousLowDt + 1
        else
            self._continuousHighDtTime = self._continuousHighDtTime + dt
            self._continuousLowDt = 0
        end

        if self._continuousLowDt >= 5 and loops > 0 then
            for i = 1, loops do
                if self._posX >= self._rightX then
                    self._goRight = false
                elseif self._posX <= self._leftX then
                    self._goRight = true
                end


                local s = self:makeSprite()
                self:addChild(s)
                s:setPosition(self._posX, self._posY)
                if self._goRight then
                    self._posX = self._posX + 1
                else
                    self._posX = self._posX - 1
                end
                self:incrementStats()
            end

            self:updateLabel()
        elseif self._continuousHighDtTime >= 0.5 or self._waitingTime > 3.0 then
            self._ended = true
            self:unscheduleUpdate()
            local labelInfo = "Test ended in" .. self._elapsedTime .. " seconds\nNodes: " .. self._spriteCount .. "   Triangles: " .. self._triCount .. "\nPixels: " .. self._pixelCount .. "   Vertices: " .. self._vertCount
            self._perfLabel:setString(labelInfo)
            Helper.subtitleLabel:setString("Test ended")
        else
            self._waitingTime = self._waitingTime + dt
        end
    end, 0)
end

function SpritePolygonPerformance:initExtend()

end

function SpritePolygonPerformance:makeSprite()
    return cc.Node:create()
end

function SpritePolygonPerformance:incrementStats()
    self._spriteCount = self._spriteCount + 1
    self._vertCount   = self._vertCount + self._incVert
    self._triCount    = self._triCount  + self._incTri
    self._pixelCount  = self._pixelCount + self._incPix
end


----------------------------------------
----SpritePolygonPerformanceTestDynamic
----------------------------------------
local SpritePolygonPerformanceTestDynamic = class("SpritePolygonPerformanceTestDynamic", SpritePolygonPerformance)

function SpritePolygonPerformanceTestDynamic:makeSprite()
    local ret = cc.Sprite:create(self._info)
    ret:runAction(cc.RepeatForever:create(cc.RotateBy:create(1.0,360.0)))
    return ret
end

function SpritePolygonPerformanceTestDynamic:initExtend()
    self._info = cc.AutoPolygon:generatePolygon(imageFileName)
    self:initIncrementStats()
end

function SpritePolygonPerformanceTestDynamic:title()
    return "Dynamic SpritePolygon Performance"
end

function SpritePolygonPerformanceTestDynamic:subtitle()
    return "Test running, please wait until it ends"
end

function SpritePolygonPerformanceTestDynamic:initIncrementStats()
    self._incVert = self._info:getVertCount()
    self._incTri  = self._info:getTrianglesCount()
    self._incPix  = self._info:getArea()
end

----------------------------------------
----SpritePerformanceTestDynamic
----------------------------------------
local SpritePerformanceTestDynamic = class("SpritePerformanceTestDynamic", SpritePolygonPerformance)

function SpritePerformanceTestDynamic:initExtend()
    -- self._info = cc.AutoPolygon:generatePolygon(imageFileName)
    self:initIncrementStats()
end

function SpritePerformanceTestDynamic:title()
    return "Dynamic Sprite Performance"
end

function SpritePerformanceTestDynamic:subtitle()
    return "Test running, please wait until it ends"
end

function SpritePerformanceTestDynamic:initIncrementStats()
    local t = cc.Sprite:create(imageFileName)
    self._incVert = 4
    self._incTri = 2
    self._incPix = t:getContentSize().width * t:getContentSize().height
end

function SpritePerformanceTestDynamic:makeSprite()
    local ret =  cc.Sprite:create(imageFileName)
    ret:runAction(cc.RepeatForever:create(cc.RotateBy:create(1.0,360.0)))
    return ret
end


----------------------------------------
----SpritePolygonTest
----------------------------------------
function SpritePolygonTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        SpritePolygonTest1.create,
        SpritePolygonTest2.create,
        SpritePolygonTest3.create,
        SpritePolygonTest4.create,
        SpritePolygonPerformanceTestDynamic.create,
        SpritePerformanceTestDynamic.create,
    }
    Helper.index = 1

    scene:addChild(SpritePolygonTest1.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
