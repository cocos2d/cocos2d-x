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
/// @file glm/core/type_int.hpp
/// @date 2008-08-22 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_int
#define glm_core_type_int

#include "setup.hpp"
#include "_detail.hpp"

namespace glm{
namespace detail
{
	typedef signed short			lowp_int_t;
	typedef signed int				mediump_int_t;
	typedef sint64					highp_int_t;

	typedef unsigned short			lowp_uint_t;
	typedef unsigned int			mediump_uint_t;
	typedef uint64					highp_uint_t;

	GLM_DETAIL_IS_INT(signed char);
	GLM_DETAIL_IS_INT(signed short);
	GLM_DETAIL_IS_INT(signed int);
	GLM_DETAIL_IS_INT(signed long);

	GLM_DETAIL_IS_UINT(unsigned char);
	GLM_DETAIL_IS_UINT(unsigned short);
	GLM_DETAIL_IS_UINT(unsigned int);
	GLM_DETAIL_IS_UINT(unsigned long);
	
#if(GLM_LANG >= GLM_LANG_CXX0X)
	GLM_DETAIL_IS_INT(signed long long);
	GLM_DETAIL_IS_UINT(unsigned long long);
#else
	GLM_DETAIL_IS_INT(highp_int_t);
	GLM_DETAIL_IS_UINT(highp_uint_t);
#endif
}//namespace detail

	/// @addtogroup core_precision
	/// @{

	/// Low precision signed integer. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::lowp_int_t				lowp_int;

	/// Medium precision signed integer. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::mediump_int_t			mediump_int;

	/// High precision signed integer.
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::highp_int_t				highp_int;

	/// Low precision unsigned integer. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::lowp_uint_t				lowp_uint;

	/// Medium precision unsigned integer. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::mediump_uint_t			mediump_uint;

	/// High precision unsigned integer. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::highp_uint_t				highp_uint;

#if(!defined(GLM_PRECISION_HIGHP_INT) && !defined(GLM_PRECISION_MEDIUMP_INT) && !defined(GLM_PRECISION_LOWP_INT))
	typedef mediump_int                 int_t;
#elif(defined(GLM_PRECISION_HIGHP_INT) && !defined(GLM_PRECISION_MEDIUMP_INT) && !defined(GLM_PRECISION_LOWP_INT))
	typedef highp_int					int_t;
#elif(!defined(GLM_PRECISION_HIGHP_INT) && defined(GLM_PRECISION_MEDIUMP_INT) && !defined(GLM_PRECISION_LOWP_INT))
	typedef mediump_int                 int_t;
#elif(!defined(GLM_PRECISION_HIGHP_INT) && !defined(GLM_PRECISION_MEDIUMP_INT) && defined(GLM_PRECISION_LOWP_INT))
	typedef lowp_int					int_t;
#else
#	error "GLM error: multiple default precision requested for signed interger types"
#endif

#if(!defined(GLM_PRECISION_HIGHP_UINT) && !defined(GLM_PRECISION_MEDIUMP_UINT) && !defined(GLM_PRECISION_LOWP_UINT))
	typedef mediump_uint				uint_t;
#elif(defined(GLM_PRECISION_HIGHP_UINT) && !defined(GLM_PRECISION_MEDIUMP_UINT) && !defined(GLM_PRECISION_LOWP_UINT))
	typedef highp_uint					uint_t;
#elif(!defined(GLM_PRECISION_HIGHP_UINT) && defined(GLM_PRECISION_MEDIUMP_UINT) && !defined(GLM_PRECISION_LOWP_UINT))
	typedef mediump_uint				uint_t;
#elif(!defined(GLM_PRECISION_HIGHP_UINT) && !defined(GLM_PRECISION_MEDIUMP_UINT) && defined(GLM_PRECISION_LOWP_UINT))
	typedef lowp_uint					uint_t;
#else
#	error "GLM error: multiple default precision requested for unsigned interger types"
#endif

	/// Unsigned integer type. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.3 Integers</a>
	typedef uint_t								uint;

	/// @}
}//namespace glm

#endif//glm_core_type_int
