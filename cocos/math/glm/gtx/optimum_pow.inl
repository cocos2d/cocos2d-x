///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2005-12-27
// Licence : This source is under MIT License
// File    : glm/gtx/optimum_pow.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType pow2(const genType& x)
	{
		return x * x;
	}

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType pow3(const genType& x)
	{
		return x * x * x;
	}

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType pow4(const genType& x)
	{
		return x * x * x * x;
	}

	GLM_FUNC_QUALIFIER bool powOfTwo(int x)
	{
		return !(x & (x - 1));
	}

	GLM_FUNC_QUALIFIER detail::tvec2<bool> powOfTwo(const detail::tvec2<int>& x)
	{
		return detail::tvec2<bool>(
			powOfTwo(x.x),
			powOfTwo(x.y));
	}

	GLM_FUNC_QUALIFIER detail::tvec3<bool> powOfTwo(const detail::tvec3<int>& x)
	{
		return detail::tvec3<bool>(
			powOfTwo(x.x),
			powOfTwo(x.y),
			powOfTwo(x.z));
	}

	GLM_FUNC_QUALIFIER detail::tvec4<bool> powOfTwo(const detail::tvec4<int>& x)
	{
		return detail::tvec4<bool>(
			powOfTwo(x.x),
			powOfTwo(x.y),
			powOfTwo(x.z),
			powOfTwo(x.w));
	}
}//namespace glm
