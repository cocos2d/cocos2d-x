

local function drawPrimitivesMainLayer()
    local kItemTagBasic = 1000
    local testCount = 1
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
        return "Test DrawNode"
    end
    
    local function GetSubTitle()
        return "Testing DrawNode - batched draws. Concave polygons are BROKEN"
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

    local function createDrawNodeTest()
        local layer = cc.Layer:create()

        InitTitle(layer)

        local draw = cc.DrawNode:create()
        layer:addChild(draw, 10)

        --draw 1 point
        draw:drawPoint(cc.p(60,60), 4, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 1))

        --draw 4 small points
        local fourpoints = { cc.p(60,60), cc.p(70,70), cc.p(60,70), cc.p(70,60) }
        draw:drawPoints(fourpoints, 4, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 1))

        --draw a line
        draw:drawLine(cc.p(0,0), cc.p(size.width, size.height), cc.c4f(0,1,0,1))
        
        --draw a rectangle
        draw:drawRect(cc.p(23,23), cc.p(7,7), cc.c4f(1,1,0,1))

        --draw a solid polygon
        local vertices3 = { cc.p(60,160), cc.p(70,190), cc.p(100,190), cc.p(90,160) }
        draw:drawSolidPoly( vertices3, 4, cc.c4f(0,0,1,1) )
    
        --draw a solid rectangle
        draw:drawSolidRect(cc.p(10,10), cc.p(20,20), cc.c4f(1,1,0,1))

        --draw a solid circle
        draw:drawSolidCircle(cc.p(VisibleRect:center().x + 140 ,VisibleRect:center().y), 100, math.pi/2, 50, 1.0, 2.0, cc.c4f(1,0,0,0.2))
        
        --draw open random color poly
        local vertices = { cc.p(0,0), cc.p(50,50), cc.p(100,50), cc.p(100,100), cc.p(50,100) }
        draw:drawPoly( vertices, 5, false, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 1))
        
        --draw closed random color poly
        local vertices2 = { cc.p(30,130), cc.p(30,230), cc.p(50,200) }
        draw:drawPoly( vertices2, 3, true, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 1))
        
        --draw two circle
        draw:drawCircle(cc.p(VisibleRect:center().x + 140 ,VisibleRect:center().y), 110, math.pi/2, 50, true, 1.0, 2.0, cc.c4f(1.0, 0.0, 0.0, 0.5))
    
        draw:drawCircle(cc.p(VisibleRect:center().x - 140 ,VisibleRect:center().y), 50, math.pi/2, 30, false, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 1))
        
        --draw some beziers
        draw:drawQuadBezier(cc.p(size.width - 150, size.height - 150), cc.p(size.width - 70, size.height - 10), cc.p(size.width - 10, size.height - 10), 10, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 0.5))
    
        draw:drawQuadBezier(cc.p(0, size.height), cc.p(size.width/2, size.height/2), cc.p(size.width, size.height), 50, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 0.5))
    
        draw:drawCubicBezier(cc.p(VisibleRect:center()), cc.p(VisibleRect:center().x+30,VisibleRect:center().y+50), cc.p(VisibleRect:center().x+60,VisibleRect:center().y-50),VisibleRect:right(),100, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 0.5))

        --draw Cardinal spline and catmullrom
        local array = {
                cc.p(0, 0),
                cc.p(size.width / 2 - 30, 0),
                cc.p(size.width / 2 - 30, size.height - 80),
                cc.p(0, size.height - 80),
                cc.p(0, 0) }
        draw:drawCardinalSpline(array, 0.5, 50, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 0.5))

        local array2 = {
                cc.p(size.width / 2, 30),
                cc.p(size.width - 80, 30),
                cc.p(size.width - 80, size.height - 80),
                cc.p(size.width / 2, size.height - 80),
                cc.p(size.width / 2, 30) }
        draw:drawCatmullRom(array2, 50, cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 0.5))

        --Draw 10 circles
        for i=1, 10 do
            draw:drawDot(cc.p(size.width/2, size.height/2), 10*(10-i), cc.c4f(math.random(0,1), math.random(0,1), math.random(0,1), 0.5))
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
        return createDrawNodeTest()
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

