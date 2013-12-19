///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-28
// Updated : 2008-10-28
// Licence : This source is under MIT License
// File    : glm/gtx/color_space_YCoCg.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec3<valType> rgb2YCoCg
	(
		detail::tvec3<valType> const & rgbColor
	)
	{
		detail::tvec3<valType> result;
		result.x/*Y */ =   rgbColor.r / valType(4) + rgbColor.g / valType(2) + rgbColor.b / valType(4);
		result.y/*Co*/ =   rgbColor.r / valType(2) + rgbColor.g * valType(0) - rgbColor.b / valType(2);
		result.z/*Cg*/ = - rgbColor.r / valType(4) + rgbColor.g / valType(2) - rgbColor.b / valType(4);
		return result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec3<valType> rgb2YCoCgR
	(
		detail::tvec3<valType> const & rgbColor
	)
	{
		detail::tvec3<valType> result;
		result.x/*Y */ = rgbColor.g / valType(2) + (rgbColor.r + rgbColor.b) / valType(4);
		result.y/*Co*/ = rgbColor.r - rgbColor.b;
		result.z/*Cg*/ = rgbColor.g - (rgbColor.r + rgbColor.b) / valType(2);
		return result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec3<valType> YCoCg2rgb
	(
		detail::tvec3<valType> const & YCoCgColor
	)
	{
		detail::tvec3<valType> result;
		result.r = YCoCgColor.x + YCoCgColor.y - YCoCgColor.z;
		result.g = YCoCgColor.x                + YCoCgColor.z;
		result.b = YCoCgColor.x - YCoCgColor.y - YCoCgColor.z;
		return result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec3<valType> YCoCgR2rgb
	(
		detail::tvec3<valType> const & YCoCgRColor
	)
	{
		detail::tvec3<valType> result;
		valType tmp = YCoCgRColor.x - (YCoCgRColor.z / valType(2));
		result.g = YCoCgRColor.z + tmp;
		result.b = tmp - (YCoCgRColor.y / valType(2));
		result.r = result.b + YCoCgRColor.y;
		return result;
	}
}//namespace glm
