///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/handed_coordinate_space.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T> 
	GLM_FUNC_QUALIFIER bool rightHanded
	(
		detail::tvec3<T> const & tangent, 
		detail::tvec3<T> const & binormal,
		detail::tvec3<T> const & normal
	)
	{
		return dot(cross(normal, tangent), binormal) > T(0);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool leftHanded
	(
		detail::tvec3<T> const & tangent, 
		detail::tvec3<T> const & binormal, 
		detail::tvec3<T> const & normal
	)
	{
		return dot(cross(normal, tangent), binormal) < T(0);
	}
}//namespace glm
