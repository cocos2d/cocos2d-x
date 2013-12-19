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
/// @file glm/core/func_exponential.hpp
/// @date 2008-08-08 / 2011-06-14
/// @author Christophe Riccio
/// 
/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
///
/// @defgroup core_func_exponential Exponential functions
/// @ingroup core
/// 
/// These all operate component-wise. The description is per component.
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_func_exponential
#define glm_core_func_exponential GLM_VERSION

namespace glm
{
	/// @addtogroup core_func_exponential
	/// @{

	/// Returns 'base' raised to the power 'exponent'. 
	///
	/// @param base Floating point value. pow function is defined for input values of x defined in the range (inf-, inf+) in the limit of the type precision.
	/// @param exponent Floating point value representing the 'exponent'.
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/pow.xml">GLSL pow man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType pow(genType const & base, genType const & exponent);

	/// Returns the natural exponentiation of x, i.e., e^x.
	///
	/// @param x exp function is defined for input values of x defined in the range (inf-, inf+) in the limit of the type precision.
	/// @tparam genType Floating-point scalar or vector types.
	/// 
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/exp.xml">GLSL exp man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType exp(genType const & x);

	/// Returns the natural logarithm of x, i.e., 
	/// returns the value y which satisfies the equation x = e^y. 
	/// Results are undefined if x <= 0.
	///
	/// @param x log function is defined for input values of x defined in the range (0, inf+) in the limit of the type precision.
	/// @tparam genType Floating-point scalar or vector types.
	/// 
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/log.xml">GLSL log man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType log(genType const & x);

	/// Returns 2 raised to the x power.
	/// 
	/// @param x exp2 function is defined for input values of x defined in the range (inf-, inf+) in the limit of the type precision.
	/// @tparam genType Floating-point scalar or vector types.
	/// 
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/exp2.xml">GLSL exp2 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType exp2(genType const & x);

	/// Returns the base 2 log of x, i.e., returns the value y, 
	/// which satisfies the equation x = 2 ^ y.
	/// 
	/// @param x log2 function is defined for input values of x defined in the range (0, inf+) in the limit of the type precision.
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/log2.xml">GLSL log2 man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType log2(genType const & x);

	/// Returns the positive square root of x.
	/// 
	/// @param x sqrt function is defined for input values of x defined in the range [0, inf+) in the limit of the type precision.
	/// @tparam genType Floating-point scalar or vector types.
	/// 
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sqrt.xml">GLSL sqrt man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType sqrt(genType const & x);
    
	/// Returns the reciprocal of the positive square root of x.
	/// 
	/// @param x inversesqrt function is defined for input values of x defined in the range [0, inf+) in the limit of the type precision.
	/// @tparam genType Floating-point scalar or vector types.
	/// 
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inversesqrt.xml">GLSL inversesqrt man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.2 Exponential Functions</a>
	template <typename genType> 
	GLM_FUNC_DECL genType inversesqrt(genType const & x);

	/// @}
}//namespace glm

#include "func_exponential.inl"

#endif//glm_core_func_exponential
