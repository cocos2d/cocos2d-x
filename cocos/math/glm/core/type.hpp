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
/// @file glm/core/type.hpp
/// @date 2008-01-08 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type
#define glm_core_type

#include "type_half.hpp"
#include "type_float.hpp"
#include "type_int.hpp"

#include "type_gentype.hpp"

#include "type_vec1.hpp"
#include "type_vec2.hpp"
#include "type_vec3.hpp"
#include "type_vec4.hpp"

#include "type_mat2x2.hpp"
#include "type_mat2x3.hpp"
#include "type_mat2x4.hpp"
#include "type_mat3x2.hpp"
#include "type_mat3x3.hpp"
#include "type_mat3x4.hpp"
#include "type_mat4x2.hpp"
#include "type_mat4x3.hpp"
#include "type_mat4x4.hpp"

namespace glm
{
	/// @addtogroup core_types
	/// @{

	//////////////////////////
	// Float definition

#if(defined(GLM_PRECISION_HIGHP_FLOAT))
	typedef highp_vec2          vec2;
	typedef highp_vec3          vec3;
	typedef highp_vec4          vec4;
	typedef highp_mat2x2		mat2x2;
	typedef highp_mat2x3		mat2x3;
	typedef highp_mat2x4		mat2x4;
	typedef highp_mat3x2		mat3x2;
	typedef highp_mat3x3		mat3x3;
	typedef highp_mat3x4		mat3x4;
	typedef highp_mat4x2		mat4x2;
	typedef highp_mat4x3		mat4x3;
	typedef highp_mat4x4		mat4x4;
#elif(defined(GLM_PRECISION_MEDIUMP_FLOAT))
	typedef mediump_vec2		vec2;
	typedef mediump_vec3		vec3;
	typedef mediump_vec4		vec4;
	typedef mediump_mat2x2      mat2x2;
	typedef mediump_mat2x3      mat2x3;
	typedef mediump_mat2x4      mat2x4;
	typedef mediump_mat3x2      mat3x2;
	typedef mediump_mat3x3      mat3x3;
	typedef mediump_mat3x4      mat3x4;
	typedef mediump_mat4x2      mat4x2;
	typedef mediump_mat4x3      mat4x3;
	typedef mediump_mat4x4      mat4x4;
#elif(defined(GLM_PRECISION_LOWP_FLOAT))
	typedef lowp_vec2			vec2;
	typedef lowp_vec3			vec3;
	typedef lowp_vec4			vec4;
	typedef lowp_mat2x2			mat2x2;
	typedef lowp_mat2x3			mat2x3;
	typedef lowp_mat2x4			mat2x4;
	typedef lowp_mat3x2			mat3x2;
	typedef lowp_mat3x3			mat3x3;
	typedef lowp_mat3x4			mat3x4;
	typedef lowp_mat4x2			mat4x2;
	typedef lowp_mat4x3			mat4x3;
	typedef lowp_mat4x4			mat4x4;
#else
	/// 2 components vector of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_vec2		vec2;

	//! 3 components vector of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_vec3		vec3;

	//! 4 components vector of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_vec4		vec4;

	//! 2 columns of 2 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat2x2		mat2x2;

	//! 2 columns of 3 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat2x3		mat2x3;

	//! 2 columns of 4 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat2x4		mat2x4;

	//! 3 columns of 2 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat3x2		mat3x2;

	//! 3 columns of 3 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat3x3		mat3x3;

	//! 3 columns of 4 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat3x4		mat3x4;

	//! 4 columns of 2 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat4x2		mat4x2;

	//! 4 columns of 3 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat4x3		mat4x3;

	//! 4 columns of 4 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mediump_mat4x4		mat4x4;

#endif//GLM_PRECISION

	//! 2 columns of 2 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat2x2							mat2;

	//! 3 columns of 3 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat3x3							mat3;

	//! 4 columns of 4 components matrix of floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef mat4x4							mat4;

	//////////////////////////
	// Signed integer definition

#if(defined(GLM_PRECISION_HIGHP_INT))
	typedef highp_ivec2			ivec2;
	typedef highp_ivec3			ivec3;
	typedef highp_ivec4			ivec4;
#elif(defined(GLM_PRECISION_MEDIUMP_INT))
	typedef mediump_ivec2		ivec2;
	typedef mediump_ivec3		ivec3;
	typedef mediump_ivec4		ivec4;
#elif(defined(GLM_PRECISION_LOWP_INT))
	typedef lowp_ivec2			ivec2;
	typedef lowp_ivec3			ivec3;
	typedef lowp_ivec4			ivec4;
#else
	//! 2 components vector of signed integer numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_ivec2		ivec2;

	//! 3 components vector of signed integer numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_ivec3		ivec3;

	//! 4 components vector of signed integer numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_ivec4		ivec4;
#endif//GLM_PRECISION

	//////////////////////////
	// Unsigned integer definition

#if(defined(GLM_PRECISION_HIGHP_UINT))
	typedef highp_uvec2			uvec2;
	typedef highp_uvec3			uvec3;
	typedef highp_uvec4			uvec4;
#elif(defined(GLM_PRECISION_MEDIUMP_UINT))
	typedef mediump_uvec2		uvec2;
	typedef mediump_uvec3		uvec3;
	typedef mediump_uvec4		uvec4;
#elif(defined(GLM_PRECISION_LOWP_UINT))
	typedef lowp_uvec2			uvec2;
	typedef lowp_uvec3			uvec3;
	typedef lowp_uvec4			uvec4;
#else
	//! 2 components vector of unsigned integer numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_uvec2		uvec2;

	//! 3 components vector of unsigned integer numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_uvec3		uvec3;

	//! 4 components vector of unsigned integer numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef mediump_uvec4		uvec4;
#endif//GLM_PRECISION

	//////////////////////////
	// Boolean definition

	//! 2 components vector of boolean. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef detail::tvec2<bool>		bvec2;

	//! 3 components vector of boolean. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef detail::tvec3<bool>		bvec3;

	//! 4 components vector of boolean. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef detail::tvec4<bool>		bvec4;

	//////////////////////////
	// Double definition

	//! Vector of 2 double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef detail::tvec2<double>	dvec2;

	//! Vector of 3 double-precision floating-point numbers.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef detail::tvec3<double>	dvec3;

	//! Vector of 4 double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	typedef detail::tvec4<double>	dvec4;

	//! 2 * 2 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat2x2<double>	dmat2;

	//! 3 * 3 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat3x3<double>	dmat3;

	//! 4 * 4 matrix of double-precision floating-point numbers.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat4x4<double>	dmat4;

	//! 2 * 2 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat2x2<double>	dmat2x2;

	//! 2 * 3 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat2x3<double>	dmat2x3;

	//! 2 * 4 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat2x4<double>	dmat2x4;

	//! 3 * 2 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat3x2<double>	dmat3x2;

	//! 3 * 3 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat3x3<double>	dmat3x3;

	//! 3 * 4 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat3x4<double>	dmat3x4;

	//! 4 * 2 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat4x2<double>	dmat4x2;

	//! 4 * 3 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat4x3<double>	dmat4x3;

	//! 4 * 4 matrix of double-precision floating-point numbers. 
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	typedef detail::tmat4x4<double>	dmat4x4;

	/// @}
}//namespace glm

#endif//glm_core_type
