///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-06
// Updated : 2009-05-01
// Licence : This source is under MIT License
// File    : glm/gtx/polar_coordinates.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> polar
	(
		detail::tvec3<T> const & euclidean
	)
	{
		T const Length(length(euclidean));
		detail::tvec3<T> const tmp(euclidean / Length);
		T const xz_dist(sqrt(tmp.x * tmp.x + tmp.z * tmp.z));

#ifdef GLM_FORCE_RADIANS
		return detail::tvec3<T>(
			atan(xz_dist, tmp.y),	// latitude
			atan(tmp.x, tmp.z),		// longitude
			xz_dist);				// xz distance
#else
		return detail::tvec3<T>(
			degrees(atan(xz_dist, tmp.y)),	// latitude
			degrees(atan(tmp.x, tmp.z)),	// longitude
			xz_dist);						// xz distance
#endif
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> euclidean
	(
		detail::tvec2<T> const & polar
	)
	{
#ifdef GLM_FORCE_RADIANS
		T const latitude(polar.x);
		T const longitude(polar.y);
#else
		T const latitude(radians(polar.x));
		T const longitude(radians(polar.y));
#endif

		return detail::tvec3<T>(
			cos(latitude) * sin(longitude),
			sin(latitude),
			cos(latitude) * cos(longitude));
	}

}//namespace glm
