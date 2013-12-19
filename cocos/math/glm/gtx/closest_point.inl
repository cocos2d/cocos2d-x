///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-30
// Updated : 2008-10-05
// Licence : This source is under MIT License
// File    : glm/gtx/closest_point.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_closest_point
#define glm_gtx_closest_point

namespace glm
{
	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tvec3<valType> closestPointOnLine
	(
		detail::tvec3<valType> const & point, 
		detail::tvec3<valType> const & a, 
		detail::tvec3<valType> const & b
	)
	{
		valType LineLength = distance(a, b);
		detail::tvec3<valType> Vector = point - a;
		detail::tvec3<valType> LineDirection = (b - a) / LineLength;

		// Project Vector to LineDirection to get the distance of point from a
		valType Distance = dot(Vector, LineDirection);

		if(Distance <= valType(0)) return a;
		if(Distance >= LineLength) return b;
		return a + LineDirection * Distance;
	}
}//namespace glm

#endif//glm_gtx_closest_point
