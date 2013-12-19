///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file glm/core/_vectorize.hpp
/// @date 2011-10-14 / 2011-10-14
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#define VECTORIZE2_VEC(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec2<T> func( \
		detail::tvec2<T> const & v) \
	{ \
		return detail::tvec2<T>( \
			func(v.x), \
			func(v.y)); \
	}

#define VECTORIZE3_VEC(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec3<T> func( \
		detail::tvec3<T> const & v) \
	{ \
		return detail::tvec3<T>( \
			func(v.x), \
			func(v.y), \
			func(v.z)); \
	}

#define VECTORIZE4_VEC(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec4<T> func( \
		detail::tvec4<T> const & v) \
	{ \
		return detail::tvec4<T>( \
			func(v.x), \
			func(v.y), \
			func(v.z), \
			func(v.w)); \
	}

#define VECTORIZE_VEC(func) \
	VECTORIZE2_VEC(func) \
	VECTORIZE3_VEC(func) \
	VECTORIZE4_VEC(func)

#define VECTORIZE2_VEC_SCA(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec2<T> func \
	( \
		detail::tvec2<T> const & x,  \
		typename detail::tvec2<T>::value_type const & y \
	) \
	{ \
		return detail::tvec2<T>( \
			func(x.x, y), \
			func(x.y, y)); \
	}

#define VECTORIZE3_VEC_SCA(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec3<T> func \
	( \
		detail::tvec3<T> const & x,  \
		typename detail::tvec3<T>::value_type const & y \
	) \
	{ \
		return detail::tvec3<T>( \
			func(x.x, y), \
			func(x.y, y), \
			func(x.z, y)); \
	}

#define VECTORIZE4_VEC_SCA(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec4<T> func \
	( \
		detail::tvec4<T> const & x,  \
		typename detail::tvec4<T>::value_type const & y \
	) \
	{ \
		return detail::tvec4<T>( \
			func(x.x, y), \
			func(x.y, y), \
			func(x.z, y), \
			func(x.w, y)); \
	}

#define VECTORIZE_VEC_SCA(func) \
	VECTORIZE2_VEC_SCA(func) \
	VECTORIZE3_VEC_SCA(func) \
	VECTORIZE4_VEC_SCA(func)

#define VECTORIZE2_VEC_VEC(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec2<T> func \
	( \
		detail::tvec2<T> const & x,  \
		detail::tvec2<T> const & y \
	) \
	{ \
		return detail::tvec2<T>( \
			func(x.x, y.x), \
			func(x.y, y.y)); \
	}

#define VECTORIZE3_VEC_VEC(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec3<T> func \
	( \
		detail::tvec3<T> const & x,  \
		detail::tvec3<T> const & y \
	) \
	{ \
		return detail::tvec3<T>( \
			func(x.x, y.x), \
			func(x.y, y.y), \
			func(x.z, y.z)); \
	}

#define VECTORIZE4_VEC_VEC(func) \
	template <typename T> \
	GLM_FUNC_QUALIFIER detail::tvec4<T> func \
	( \
		detail::tvec4<T> const & x,  \
		detail::tvec4<T> const & y \
	) \
	{ \
		return detail::tvec4<T>( \
			func(x.x, y.x), \
			func(x.y, y.y), \
			func(x.z, y.z), \
			func(x.w, y.w)); \
	}

#define VECTORIZE_VEC_VEC(func) \
	VECTORIZE2_VEC_VEC(func) \
	VECTORIZE3_VEC_VEC(func) \
	VECTORIZE4_VEC_VEC(func)
