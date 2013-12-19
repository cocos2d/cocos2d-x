///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-16
// Updated : 2008-10-24
// Licence : This source is under MIT License
// File    : glm/gtx/compatibility.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// isfinite
	template <typename genType> 
	GLM_FUNC_QUALIFIER bool isfinite(
		genType const & x)
	{
#		if(GLM_COMPILER & GLM_COMPILER_VC)
			return _finite(x);
#		elif(GLM_COMPILER & GLM_COMPILER_GCC)
#			if(GLM_PLATFORM & GLM_PLATFORM_ANDROID)
				return _isfinite(x) != 0;
#			else
				return std::isfinite(x) != 0;
#			endif
#		else
			return std::isfinite(x) != 0;
#		endif
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec2<bool> isfinite(
		detail::tvec2<valType> const & x)
	{
		return detail::tvec2<bool>(
			isfinite(x.x),
			isfinite(x.y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec3<bool> isfinite(
		detail::tvec3<valType> const & x)
	{
		return detail::tvec3<bool>(
			isfinite(x.x),
			isfinite(x.y),
			isfinite(x.z));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec4<bool> isfinite(
		detail::tvec4<valType> const & x)
	{
		return detail::tvec4<bool>(
			isfinite(x.x),
			isfinite(x.y),
			isfinite(x.z),
			isfinite(x.w));
	}

}//namespace glm
