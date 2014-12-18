

cc.c4fFromc4b = function (c4b)
	return cc.c4f(c4b.r/255.0, c4b.g/255.0, c4b.b/255.0, c4b.a/255.0)
end

-- SpriteBatchNode
cc.Node.reorderChild = function(self, sp, zorder)
	sp:setLocalZOrder(zorder)
end

utils = {}

if cc.NVGDrawNode then
	utils.useNVGDrawNode = true
end

function utils.drawCircle(radius, params)
	if utils.useNVGDrawNode then
		params = params or {}
		local posX = params.x or 0
        local posY = params.y or 0
        local borderColor = params.borderColor or cc.c4f(1, 1, 1, 1)

		local drawNode = cc.NVGDrawNode:create()
		drawNode:setLineWidth(0.5)
		drawNode:drawCircle(cc.p(posX, posY), radius, borderColor)

		return drawNode
	else
		return display.newCircle(radius, params)
	end
end

function utils.drawRect(rect, params)
	if not rect then
	end

	if utils.useNVGDrawNode then
		params = params or {}
        local borderColor = params.borderColor or cc.c4f(1, 1, 1, 1)

		local drawNode = cc.NVGDrawNode:create()
		if params.borderWidth then
			drawNode:setLineColor(params.borderWidth)
		end
		if params.fillColor then
			drawNode:setFillColor(params.fillColor)
			drawNode:setFill(true)
		end
		drawNode:drawRect(cc.p(rect.x, rect.y),
			cc.p(rect.x, rect.y + rect.height),
			cc.p(rect.x + rect.width, rect.y + rect.height),
			cc.p(rect.x + rect.width, rect.y),
			borderColor)

		return drawNode
	else
		return display.newRect(radius, params)
	end
end

function utils.drawPolygon(points)
	if utils.useNVGDrawNode then
		local path = {}

		for _, v in ipairs(points) do
			table.insert(path, cc.p(v[1], v[2]))
		end

		params = params or {}
        local borderColor = params.borderColor or cc.c4f(1, 1, 1, 1)

		local drawNode = cc.NVGDrawNode:create()
		drawNode:setLineWidth(0.5)
		drawNode:drawPolygon(path, #path, false, borderColor);

		return drawNode
	else
		return display.newPolygon(points)
	end
end

