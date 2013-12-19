//////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
//////////////////////////////////////////////////////////////////////////////////
// Created : 2007-09-28
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/normalize_dot.inl
//////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType normalizeDot
	(
		genType const & x, 
		genType const & y
	)
	{
		return 
			glm::dot(x, y) * 
			glm::inversesqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER valType normalizeDot
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y
	)
	{
		return 
			glm::dot(x, y) * 
			glm::inversesqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER valType normalizeDot
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y
	)
	{
		return 
			glm::dot(x, y) * 
			glm::inversesqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER valType normalizeDot
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y
	)
	{
		return 
			glm::dot(x, y) * 
			glm::inversesqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType fastNormalizeDot
	(
		genType const & x, 
		genType const & y
	)
	{
		return 
			glm::dot(x, y) * 
			fastInverseSqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER valType fastNormalizeDot
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y
	)
	{
		return 
			glm::dot(x, y) * 
			fastInverseSqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER valType fastNormalizeDot
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y
	)
	{
		return 
			glm::dot(x, y) * 
			fastInverseSqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER valType fastNormalizeDot
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y
	)
	{
		return 
			glm::dot(x, y) * 
			fastInverseSqrt(glm::dot(x, x) * 
			glm::dot(y, y));
	}
}//namespace glm
