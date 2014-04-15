

local function drawPrimitivesMainLayer()
    local kItemTagBasic = 1000
    local testCount = 2
    local maxCases = testCount
    local curCase  = 0
    local size = cc.Director:getInstance():getWinSize()
    local curLayer = nil

    local  function orderCallbackMenu()
        local function backCallback()
            curCase = curCase - 1
            if curCase < 0 then
                curCase = curCase + maxCases
            end
            showCurrentTest()
        end
    
        local function restartCallback()
            showCurrentTest()
        end
    
        local function nextCallback()
            curCase = curCase + 1
            curCase = curCase % maxCases
            showCurrentTest()
        end

        local ordercallbackmenu = cc.Menu:create()
        local size = cc.Director:getInstance():getWinSize()
        local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
        item1:registerScriptTapHandler(backCallback)
        ordercallbackmenu:addChild(item1,kItemTagBasic)
        local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
        item2:registerScriptTapHandler(restartCallback)
        ordercallbackmenu:addChild(item2,kItemTagBasic)
        local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
        ordercallbackmenu:addChild(item3,kItemTagBasic) 
        item3:registerScriptTapHandler(nextCallback)
                
        item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
        item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
        item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
        
        ordercallbackmenu:setPosition(cc.p(0, 0))

        return ordercallbackmenu
    end

    local function GetTitle()
        if 0 == curCase then
            return "Draw primitives"
        elseif 1 == curCase then
            return "Test DrawNode"
        end
    end
    
    local function GetSubTitle()
        if 0 == curCase then
            return "Drawing Primitives by call gl funtions"
        elseif 1 == curCase then
            return "Testing DrawNode - batched draws. Concave polygons are BROKEN"
        end
    end

    local function InitTitle(layer)
        --Title
        local lableTitle = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        layer:addChild(lableTitle, 15)
        lableTitle:setAnchorPoint(cc.p(0.5, 0.5))
        lableTitle:setPosition(cc.p(size.width / 2, size.height - 32))
        lableTitle:setColor(cc.c3b(255, 255, 40))
        --SubTitle
        local subLabelTitle = cc.Label:createWithTTF(GetSubTitle(), s_thonburiPath, 16)
        layer:addChild(subLabelTitle, 15)
        subLabelTitle:setAnchorPoint(cc.p(0.5, 0.5))
        subLabelTitle:setPosition(cc.p(size.width / 2, size.height - 80)) 
    end

    local function createDrawPrimitivesEffect()
        local layer = cc.Layer:create()

        InitTitle(layer)

        local glNode  = gl.glNodeCreate()
        glNode:setContentSize(cc.size(size.width, size.height))
        glNode:setAnchorPoint(cc.p(0.5, 0.5))

        local function primitivesDraw(transform, transformUpdated)

            kmGLPushMatrix()
            kmGLLoadMatrix(transform)

            cc.DrawPrimitives.drawLine(VisibleRect:leftBottom(), VisibleRect:rightTop() )

            gl.lineWidth( 5.0 )
            cc.DrawPrimitives.drawColor4B(255,0,0,255)
            cc.DrawPrimitives.drawLine( VisibleRect:leftTop(), VisibleRect:rightBottom() )



            cc.DrawPrimitives.setPointSize(64)
            cc.DrawPrimitives.drawColor4B(0, 0, 255, 128)
            cc.DrawPrimitives.drawPoint(VisibleRect:center())

            local points = {cc.p(60,60), cc.p(70,70), cc.p(60,70), cc.p(70,60) }
            cc.DrawPrimitives.setPointSize(4)
            cc.DrawPrimitives.drawColor4B(0,255,255,255)
            cc.DrawPrimitives.drawPoints(points,4)

            gl.lineWidth(16)
            cc.DrawPrimitives.drawColor4B(0, 255, 0, 255)
            cc.DrawPrimitives.drawCircle( VisibleRect:center(), 100, 0, 10, false)

            gl.lineWidth(2)
            cc.DrawPrimitives.drawColor4B(0, 255, 255, 255)
            cc.DrawPrimitives.drawCircle( VisibleRect:center(), 50, math.pi / 2, 50, true)

            gl.lineWidth(2)
            cc.DrawPrimitives.drawColor4B(255, 0, 255, 255)
            cc.DrawPrimitives.drawSolidCircle( cc.p(VisibleRect:center().x + 140 ,VisibleRect:center().y), 40, math.rad(90), 50, 1.0, 1.0)

            gl.lineWidth(10)
            cc.DrawPrimitives.drawColor4B(255, 255, 0, 255)
            local yellowPoints = { cc.p(0,0), cc.p(50,50), cc.p(100,50), cc.p(100,100), cc.p(50,100)}
            cc.DrawPrimitives.drawPoly( yellowPoints, 5, false)

            gl.lineWidth(1)
            local filledVertices = { cc.p(0,120), cc.p(50,120), cc.p(50,170), cc.p(25,200), cc.p(0,170) }
            cc.DrawPrimitives.drawSolidPoly(filledVertices, 5, cc.c4f(0.5, 0.5, 1, 1))

            gl.lineWidth(2)
            cc.DrawPrimitives.drawColor4B(255, 0, 255, 255)
            local closePoints= { cc.p(30,130), cc.p(30,230), cc.p(50,200) }
            cc.DrawPrimitives.drawPoly( closePoints, 3, true)

            cc.DrawPrimitives.drawQuadBezier(VisibleRect:leftTop(), VisibleRect:center(), VisibleRect:rightTop(), 50)

            cc.DrawPrimitives.drawCubicBezier(VisibleRect:center(), cc.p(VisibleRect:center().x + 30, VisibleRect:center().y + 50), cc.p(VisibleRect:center().x + 60,VisibleRect:center().y - 50), VisibleRect:right(), 100)

            local solidvertices = {cc.p(60,160), cc.p(70,190), cc.p(100,190), cc.p(90,160)}
            cc.DrawPrimitives.drawSolidPoly( solidvertices, 4, cc.c4f(1, 1, 0, 1) )

            local array = {
                cc.p(0, 0),
                cc.p(size.width / 2 - 30, 0),
                cc.p(size.width / 2 - 30, size.height - 80),
                cc.p(0, size.height - 80),
                cc.p(0, 0),
            }
            cc.DrawPrimitives.drawCatmullRom( array, 5)

            cc.DrawPrimitives.drawCardinalSpline( array, 0,100)

            gl.lineWidth(1)
            cc.DrawPrimitives.drawColor4B(255,255,255,255)
            cc.DrawPrimitives.setPointSize(1)

            kmGLPopMatrix()
        end

        glNode:registerScriptDrawHandler(primitivesDraw)
        layer:addChild(glNode,-10)
        glNode:setPosition( size.width / 2, size.height / 2)

        return layer
    end

    local function createDrawNodeTest()
        local layer = cc.Layer:create()

        InitTitle(layer)

        local draw = cc.DrawNode:create()
        layer:addChild(draw, 10)

        --Draw 10 circles
        for i=1, 10 do
            draw:drawDot(cc.p(size.width/2, size.height/2), 10*(10-i), cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 1))
        end

        --Draw polygons
        points = { cc.p(size.height/4, 0), cc.p(size.width, size.height / 5), cc.p(size.width / 3 * 2, size.height) }
        draw:drawPolygon(points, table.getn(points), cc.c4f(1,0,0,0.5), 4, cc.c4f(0,0,1,1))

        local o = 80
        local w = 20
        local h = 50
        local star1 = { cc.p( o + w, o - h), cc.p(o + w * 2, o), cc.p(o + w * 2 + h, o + w), cc.p(o + w * 2, o + w * 2) }
        
        draw:drawPolygon(star1, table.getn(star1), cc.c4f(1,0,0,0.5), 1, cc.c4f(0,0,1,1))

        o = 180
        w = 20
        h = 50
        local star2 = {
            cc.p(o, o), cc.p(o + w, o - h), cc.p(o + w * 2, o),        --lower spike
            cc.p(o + w * 2 + h, o + w ), cc.p(o + w * 2, o + w * 2),      --right spike
            cc.p(o + w, o + w * 2 + h), cc.p(o, o + w * 2),               --top spike
            cc.p(o - h, o + w),                                              --left spike
        };
        
        draw:drawPolygon(star2, table.getn(star2), cc.c4f(1,0,0,0.5), 1, cc.c4f(0,0,1,1))

        draw:drawSegment(cc.p(20,size.height), cc.p(20,size.height/2), 10, cc.c4f(0, 1, 0, 1))

        draw:drawSegment(cc.p(10,size.height/2), cc.p(size.width/2, size.height/2), 40, cc.c4f(1, 0, 1, 0.5))

        return layer
    end

    local function createLayerByCurCase(curCase)
        if 0 == curCase then
            return createDrawPrimitivesEffect()
        elseif 1 == curCase then
            return createDrawNodeTest()
        end
    end

    function showCurrentTest()    
        local curScene = cc.Scene:create()
        if nil ~= curScene then
            curLayer = createLayerByCurCase(curCase)
            if nil ~= curLayer then
                curScene:addChild(curLayer)
                curLayer:addChild(orderCallbackMenu(),15)
                curScene:addChild(CreateBackMenuItem())
                cc.Director:getInstance():replaceScene(curScene)
            end            
        end 
    end

    curLayer = createLayerByCurCase(curCase)
    curLayer:addChild(orderCallbackMenu(),15)
    return curLayer
end

function DrawPrimitivesTest()
    local scene = cc.Scene:create()
    scene:addChild(drawPrimitivesMainLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end

