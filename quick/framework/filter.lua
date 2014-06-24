--- create some filters to build a CCFilteredSprite
-- @author zrong(zengrong.net)
-- Creation 2014-03-31

--[[--

滤镜功能

]]

local filter = {}

local FILTERS = {
-- colors
GRAY =			{CCGrayFilter},  				-- {r 0.299, g 0.587, b 0.114, a 0.0} or no parameters
RGB = 			{CCRGBFilter, 3, {1, 1, 1}}, 	-- {0.0~1.0, 0.0~1.0, 0.0~1.0}
HUE = 			{CCHueFilter, 1, {0}}, 			-- {-180~ 180} see photoshop
BRIGHTNESS = 	{CCBrightnessFilter, 1, {0}}, 	-- {-1.0~1.0}
SATURATION = 	{CCSaturationFilter, 1, {1}}, 	-- {0.0~2.0}
CONTRAST = 		{CCContrastFilter, 1, {1}},		-- {0.0~4.0}
EXPOSURE = 		{CCExposureFilter, 1, {0}},		-- {-10.0, 10.0}
GAMMA = 		{CCGammaFilter, 1, {1}}, 		-- {0.0, 3.0}
HAZE = 			{CCHazeFilter, 2, {0, 0}}, 		-- {distance -0.5~0.5, slope -0.5~0.5}
SEPIA = 		{CCSepiaFilter}, 				-- {no parameters}
-- blurs
GAUSSIAN_VBLUR = 	{CCGaussianVBlurFilter, 1, {0}}, 		-- {pixel}
GAUSSIAN_HBLUR = 	{CCGaussianHBlurFilter, 1, {0}}, 		-- {pixel}
ZOOM_BLUR = 		{CCZoomBlurFilter, 3, {1, 0.5, 0.5}}, 	-- {size, centerX, centerY}
MOTION_BLUR = 		{CCMotionBlurFilter, 2, {1, 0}}, 		-- {size, angle}
-- others
SHARPEN = 		{CCSharpenFilter, 2, {0, 0}}, 	-- {sharpness, amount}
MASK = 			{CCMaskFilter, 1}, 				-- {DO NOT USE IT}
DROP_SHADOW = 	{CCDropShadowFilter, 1}, 		-- {DO NOT USE IT}
}

local MULTI_FILTERS = {
GAUSSIAN_BLUR = {},
}

--[[--

创建一个滤镜效果，并返回 CCFilter 场景对象。

@param string __filterName 滤镜名称
@param table __param

@return CCFilter的子类

]]
function filter.newFilter(__filterName, __param)
	local __filterData = FILTERS[__filterName]
	assert(__filterData, "filter.newFilter() - filter "..__filterName.." is not found.")
	local __cls, __count, __default = unpack(__filterData)
	local __paramCount = (__param and #__param) or 0
	print("filter.newFilter:", __paramCount, __filterName, __count)
	print("filter.newFilter __param:", __param)
	-- If count is nil, it means the Filter does not need a parameter.
	if __count == nil then
		if __paramCount == 0 then
			return __cls:create()
		end
	elseif __count == 0 then
		return __cls:create()
	else
		if __paramCount == 0 then
			return __cls:create(unpack(__default))
		end
		assert(__paramCount == __count, 
			string.format("filter.newFilter() - the parameters have a wrong amount! Expect %d, get %d.", 
			__count, __paramCount))
	end
	return __cls:create(unpack(__param))
end

--[[--

创建滤镜数组，并返回 CCFilter 的数组对象

@param table __filterNames 滤镜名称数组
@param table __params 对应参数数组

@return CCFilter数组

]]
function filter.newFilters(__filterNames, __params)
	assert(#__filterNames == #__params, 
		"filter.newFilters() - Please ensure the filters and the parameters have the same amount.")
	local __filters = CCArray:create()
	for i in ipairs(__filterNames) do
		__filters:addObject(filter.newFilter(__filterNames[i], __params[i]))
	end
	return __filters
end

return filter
