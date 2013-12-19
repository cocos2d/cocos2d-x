///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2009-04-29
// Licence : This source is under MIT License
// File    : glm/gtx/transform.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> translate(
		T x, T y, T z)
    {
		return translate(
			detail::tmat4x4<T>(1.0f), 
			detail::tvec3<T>(x, y , z));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> translate(
		detail::tmat4x4<T> const & m, 
		T x, T y, T z)
    {
        return translate(
			m, detail::tvec3<T>(x, y , z));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> translate(
		detail::tvec3<T> const & v)
    {
		return translate(
			detail::tmat4x4<T>(1.0f), v);
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> rotate(
		T angle, 
		T x, T y, T z)
    {
		return rotate(
			detail::tmat4x4<T>(1), angle, detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> rotate(
		T angle, 
		detail::tvec3<T> const & v)
    {
		return rotate(
			detail::tmat4x4<T>(1), angle, v);
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> rotate(
		detail::tmat4x4<T> const & m, 
		T angle, 
		T x, T y, T z)
    {
		return rotate(
			m, angle, detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> scale(T x, T y, T z)
    {
		return scale(
			detail::tmat4x4<T>(1), detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> scale(
		detail::tmat4x4<T> const & m, 
		T x, T y, T z)
    {
        return scale(
			m, detail::tvec3<T>(x, y, z));
    }

    template <typename T> 
    GLM_FUNC_QUALIFIER detail::tmat4x4<T> scale(
		detail::tvec3<T> const & v)
    {
        return scale(
			detail::tmat4x4<T>(1.0f), v);
    }

}//namespace glm
