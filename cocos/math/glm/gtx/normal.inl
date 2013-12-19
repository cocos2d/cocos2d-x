///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2011-06-07
// Licence : This source is under MIT License
// File    : glm/gtx/normal.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> triangleNormal
	(
		detail::tvec3<T> const & p1, 
		detail::tvec3<T> const & p2, 
		detail::tvec3<T> const & p3
	)
	{
		return normalize(cross(p1 - p2, p1 - p3));
	}
}//namespace glm
