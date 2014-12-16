
local NVGDrawNodeScene = game.createSceneClass("NVGDrawNodeScene")

function NVGDrawNodeScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "Please check console output"
    })

    -- local items = {
    --     "Timer"
    -- }
    -- self:addChild(game.createMenu(items, handler(self, self.runTest)))
    self:draw()
end

function NVGDrawNodeScene:draw()
	local quarLB = cc.p(display.cx/2, display.cy/2)
	local quarRT = cc.p(display.width - quarLB.x, display.height - quarLB.y)

	local drawNode1 = cc.NVGDrawNode:create()
	self:addChild(drawNode1)
	drawNode1:drawPoint(cc.p(display.cx - 100, display.cy), cc.c4f(1, 0, 0, 1))

	local points = {}
	for i=1,10 do
		points[i] = cc.p(display.width/10*i, 10)
	end
	local drawNode2 = cc.NVGDrawNode:create():addTo(self)
	drawNode2:drawPoints(points, 10, cc.c4f(0, 1, 0, 1))

    local drawNode3 = cc.NVGDrawNode:create()
	self:addChild(drawNode3)
    drawNode3:drawLine(quarLB, quarRT, cc.c4f(0, 0, 1, 1))
    
    local drawNode4 = cc.NVGDrawNode:create()
	self:addChild(drawNode4)
    drawNode4:drawRect(quarLB, quarRT, cc.c4f(1, 1, 0, 1))

	points = {}
	points[1] = cc.p(100, 200)
	points[2] = cc.p(100, 100)
	points[3] = cc.p(200, 100)
	points[4] = cc.p(300, 150)
	local drawNode5 = cc.NVGDrawNode:create()
	self:addChild(drawNode5)
    drawNode5:drawPolygon(points, 4, true, cc.c4f(0, 1, 1, 1))
    
	local drawNode6 = cc.NVGDrawNode:create()
	self:addChild(drawNode6)
	drawNode6:drawCircle(cc.p(display.cx, display.cy), 20, cc.c4f(1, 0, 1, 1))

    local drawNode7 = cc.NVGDrawNode:create()
	self:addChild(drawNode7)
    drawNode7:drawQuadBezier(quarLB, cc.p(quarRT.x, quarLB.y), quarRT, cc.c4f(1, 1, 1,1))

	local drawNode8 = cc.NVGDrawNode:create()
	self:addChild(drawNode8)
    drawNode8:drawCubicBezier(cc.p(300, 400), cc.p(350, 500), cc.p(500, 300), cc.p(600, 400), cc.c4f(0.5, 0, 0, 1))
    
    local drawNode9 = cc.NVGDrawNode:create()
	self:addChild(drawNode9)
    drawNode9:drawDot(cc.p(display.cx, display.cy), 5, cc.c4f(0, 0.5, 0, 1))
    
    local drawNode10 = cc.NVGDrawNode:create()
	self:addChild(drawNode10)
	drawNode10:setColor(cc.c4f(1, 1, 1, 1))
    drawNode10:drawSolidRect(cc.p(330, 120), cc.p(430, 220), cc.c4f(0, 0, 0.5, 1))

    points = {}
	points[1] = cc.p(500, 400)
	points[2] = cc.p(600, 400)
	points[3] = cc.p(550, 500)
	local drawNode11 = cc.NVGDrawNode:create()
	self:addChild(drawNode11)
    drawNode11:drawSolidPolygon(points, 3, cc.c4f(0.5, 0.5, 0, 1))
    
    local drawNode12 = cc.NVGDrawNode:create()
	self:addChild(drawNode12)
	drawNode12:setFill(true)
	drawNode12:setFillColor(cc.c4f(1, 1, 1, 1))
    drawNode12:drawArc(cc.p(50, 200), 50, 30, 200, 1, cc.c4f(0, 0.5, 0.5, 1))

	local points = {}
	points[1] = cc.p(10, 300)
	points[2] = cc.p(200, 320)
	points[3] = cc.p(180, 350)
	points[4] = cc.p(220, 410)
	local drawNode13 = cc.NVGDrawNode:create()
	self:addChild(drawNode13)
    drawNode13:setLineWidth(4)
    drawNode13:setColor(cc.c4f(0, 0.5, 0.5, 1))
    drawNode13:drawSolidPolygon(points, 4, cc.c4f(0.5, 0, 0.5, 1))

end


return NVGDrawNodeScene
