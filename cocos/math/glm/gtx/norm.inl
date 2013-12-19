///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2008-07-24
// Licence : This source is under MIT License
// File    : glm/gtx/norm.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T>
	GLM_FUNC_QUALIFIER T length2
	(
		T const & x
	)
	{
		return x * x;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T length2
	(
		detail::tvec2<T> const & x
	)
	{
		return dot(x, x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T length2
	(
		detail::tvec3<T> const & x
	)
	{
		return dot(x, x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T length2
	(
		detail::tvec4<T> const & x
	)
	{
		return dot(x, x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T length2
	(
		detail::tquat<T> const & q
	)
	{
		return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T distance2
	(
		T const & p0, 
		T const & p1
	)
	{
		return length2(p1 - p0);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T distance2
	(
		detail::tvec2<T> const & p0, 
		detail::tvec2<T> const & p1
	)
	{
		return length2(p1 - p0);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T distance2
	(
		detail::tvec3<T> const & p0, 
		detail::tvec3<T> const & p1
	)
	{
		return length2(p1 - p0);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T distance2
	(
		detail::tvec4<T> const & p0, 
		detail::tvec4<T> const & p1
	)
	{
		return length2(p1 - p0);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T l1Norm
	(
		detail::tvec3<T> const & a, 
		detail::tvec3<T> const & b
	)
	{
		return abs(b.x - a.x) + abs(b.y - a.y) + abs(b.z - a.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T l1Norm
	(
		detail::tvec3<T> const & v
	)
	{
		return abs(v.x) + abs(v.y) + abs(v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T l2Norm
	(
		detail::tvec3<T> const & a, 
		detail::tvec3<T> const & b
	)
	{
		return length(b - a);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T l2Norm
	(
		detail::tvec3<T> const & v
	)
	{
		return length(v);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T lxNorm
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		unsigned int Depth
	)
	{
		return pow(pow(y.x - x.x, T(Depth)) + pow(y.y - x.y, T(Depth)) + pow(y.z - x.z, T(Depth)), T(1) / T(Depth));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T lxNorm
	(
		detail::tvec3<T> const & v, 
		unsigned int Depth
	)
	{
		return pow(pow(v.x, T(Depth)) + pow(v.y, T(Depth)) + pow(v.z, T(Depth)), T(1) / T(Depth));
	}

}//namespace glm
