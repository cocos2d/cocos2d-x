require "DrawPrimitives"

local function drawPrimitivesMainLayer()
    local kItemTagBasic = 1000
    local testCount = 1
    local maxCases = testCount
    local curCase  = 0
    local size = CCDirector:getInstance():getWinSize()
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

        local ordercallbackmenu = CCMenu:create()
        local size = CCDirector:getInstance():getWinSize()
        local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
        item1:registerScriptTapHandler(backCallback)
        ordercallbackmenu:addChild(item1,kItemTagBasic)
        local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
        item2:registerScriptTapHandler(restartCallback)
        ordercallbackmenu:addChild(item2,kItemTagBasic)
        local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
        ordercallbackmenu:addChild(item3,kItemTagBasic) 
        item3:registerScriptTapHandler(nextCallback)
                
        item1:setPosition(CCPoint(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
        item2:setPosition(CCPoint(size.width / 2, item2:getContentSize().height / 2))
        item3:setPosition(CCPoint(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
        
        ordercallbackmenu:setPosition(CCPoint(0, 0))

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
        local lableTitle = CCLabelTTF:create(GetTitle(), "Arial", 40)
        layer:addChild(lableTitle, 15)
        lableTitle:setPosition(CCPoint(size.width / 2, size.height - 32))
        lableTitle:setColor(Color3B(255, 255, 40))
        --SubTitle
        local subLabelTitle = CCLabelTTF:create(GetSubTitle(), "Thonburi", 16)
        layer:addChild(subLabelTitle, 15)
        subLabelTitle:setPosition(CCPoint(size.width / 2, size.height - 80)) 
    end

    local function createDrawPrimitivesEffect()
        local layer = CCLayer:create()

        InitTitle(layer)

        local glNode  = gl.glNodeCreate()
        glNode:setContentSize(CCSize(size.width, size.height))
        glNode:setAnchorPoint(CCPoint(0.5, 0.5))

        local function primitivesDraw()
            ccDrawLine(VisibleRect:leftBottom(), VisibleRect:rightTop() )

            gl.lineWidth( 5.0 )
            ccDrawColor4B(255,0,0,255)
            ccDrawLine( VisibleRect:leftTop(), VisibleRect:rightBottom() )

            ccPointSize(64)
            ccDrawColor4B(0, 0, 255, 128)
            ccDrawPoint(VisibleRect:center())

            local points = {CCPoint(60,60), CCPoint(70,70), CCPoint(60,70), CCPoint(70,60) }
            ccPointSize(4)
            ccDrawColor4B(0,255,255,255)
            ccDrawPoints(points,4)

            gl.lineWidth(16)
            ccDrawColor4B(0, 255, 0, 255)
            ccDrawCircle( VisibleRect:center(), 100, 0, 10, false)

            gl.lineWidth(2)
            ccDrawColor4B(0, 255, 255, 255)
            ccDrawCircle( VisibleRect:center(), 50, math.pi / 2, 50, true)
            
            gl.lineWidth(2)
            ccDrawColor4B(255, 0, 255, 255)
            ccDrawSolidCircle( VisibleRect:center() + CCPoint(140,0), 40, math.rad(90), 50, 1.0, 1.0)


            ccDrawColor4B(255, 255, 0, 255)
            gl.lineWidth(10)
            local yellowPoints = { CCPoint(0,0), CCPoint(50,50), CCPoint(100,50), CCPoint(100,100), CCPoint(50,100)}
            ccDrawPoly( yellowPoints, 5, false)

            gl.lineWidth(1)
            local filledVertices = { CCPoint(0,120), CCPoint(50,120), CCPoint(50,170), CCPoint(25,200), CCPoint(0,170) }
            local colorFilled = { 0.5, 0.5, 1, 1 } 
            ccDrawSolidPoly(filledVertices, 5, colorFilled)

            ccDrawColor4B(255, 0, 255, 255)
            gl.lineWidth(2)
            local closePoints= { CCPoint(30,130), CCPoint(30,230), CCPoint(50,200) }
            ccDrawPoly( closePoints, 3, true)

            ccDrawQuadBezier(VisibleRect:leftTop(), VisibleRect:center(), VisibleRect:rightTop(), 50)

            ccDrawCubicBezier(VisibleRect:center(), CCPoint(VisibleRect:center().x + 30, VisibleRect:center().y + 50), CCPoint(VisibleRect:center().x + 60,VisibleRect:center().y - 50), VisibleRect:right(), 100)

            local solidvertices = {CCPoint(60,160), CCPoint(70,190), CCPoint(100,190), CCPoint(90,160)}
            local colorsolid= { 1, 1, 0, 1 }
            ccDrawSolidPoly( solidvertices, 4, colorsolid )

            gl.lineWidth(1)
            ccDrawColor4B(255,255,255,255)
            ccPointSize(1)
        end

        glNode:registerScriptDrawHandler(primitivesDraw)
        layer:addChild(glNode,-10)
        glNode:setPosition( size.width / 2, size.height / 2)

        return layer
    end

    local function createLayerByCurCase(curCase)
        if 0 == curCase then
            return createDrawPrimitivesEffect()
        end
    end

    function showCurrentTest()    
        local curScene = CCScene:create()
        if nil ~= curScene then
            curLayer = createLayerByCurCase(curCase)
            if nil ~= curLayer then
                curScene:addChild(curLayer)
                curLayer:addChild(orderCallbackMenu(),15)
                curScene:addChild(CreateBackMenuItem())
                CCDirector:getInstance():replaceScene(curScene)
            end            
        end 
    end

    curLayer = createLayerByCurCase(curCase)
    curLayer:addChild(orderCallbackMenu(),15)
    return curLayer
end

function DrawPrimitivesTest()
    local scene = CCScene:create()
    scene:addChild(drawPrimitivesMainLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end

