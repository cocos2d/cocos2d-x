

cc.c4fFromc4b = function (c4b)
	return cc.c4f(c4b.r/255.0, c4b.g/255.0, c4b.b/255.0, c4b.a/255.0)
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
		drawNode:drawCircle(cc.p(posX, posY), radius, borderColor)

		return drawNode
	else
		return display.drawCircle(radius, params)
	end
end
