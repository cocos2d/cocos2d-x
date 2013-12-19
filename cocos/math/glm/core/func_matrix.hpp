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
/// @file glm/core/func_matrix.hpp
/// @date 2008-08-03 / 2011-06-15
/// @author Christophe Riccio
///
/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
/// 
/// @defgroup core_func_matrix Matrix functions
/// @ingroup core
/// 
/// For each of the following built-in matrix functions, there is both a 
/// single-precision floating point version, where all arguments and return values 
/// are single precision, and a double-precision floating version, where all 
/// arguments and return values are double precision. Only the single-precision 
/// floating point version is shown.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_CORE_func_matrix
#define GLM_CORE_func_matrix GLM_VERSION

namespace glm
{
	/// @addtogroup core_func_matrix
	/// @{

	/// Multiply matrix x by matrix y component-wise, i.e., 
	/// result[i][j] is the scalar product of x[i][j] and y[i][j].
	/// 
	/// @tparam matType Floating-point matrix types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/matrixCompMult.xml">GLSL matrixCompMult man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template <typename matType> 
	GLM_FUNC_DECL matType matrixCompMult(
		matType const & x, 
		matType const & y);

	/// Treats the first parameter c as a column vector 
	/// and the second parameter r as a row vector
	/// and does a linear algebraic matrix multiply c * r.
	/// 
	/// @tparam matType Floating-point matrix types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/outerProduct.xml">GLSL outerProduct man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	/// 
	/// @todo Clarify the declaration to specify that matType doesn't have to be provided when used.
	template <typename vecType, typename matType> 
	GLM_FUNC_DECL matType outerProduct(
		vecType const & c, 
		vecType const & r);

	/// Returns the transposed matrix of x
	/// 
	/// @tparam matType Floating-point matrix types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/transpose.xml">GLSL transpose man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>	
	template <typename matType> 
	GLM_FUNC_DECL typename matType::transpose_type transpose(
		matType const & x);
	
	/// Return the determinant of a mat2 matrix. 
	/// 
	/// @tparam valType Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/determinant.xml">GLSL determinant man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>	
	template <typename valType> 
	GLM_FUNC_DECL typename detail::tmat2x2<valType>::value_type determinant(
		detail::tmat2x2<valType> const & m);

	/// Return the determinant of a mat3 matrix. 
	/// 
	/// @tparam valType Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/determinant.xml">GLSL determinant man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>	
	template <typename valType> 
	GLM_FUNC_DECL typename detail::tmat3x3<valType>::value_type determinant(
		detail::tmat3x3<valType> const & m);

	/// Return the determinant of a mat4 matrix. 
	/// 
	/// @tparam valType Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/determinant.xml">GLSL determinant man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>		
	template <typename valType> 
	GLM_FUNC_DECL typename detail::tmat4x4<valType>::value_type determinant(
		detail::tmat4x4<valType> const & m);

	/// Return the inverse of a mat2 matrix. 
	/// 
	/// @tparam valType Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inverse.xml">GLSL inverse man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>	 
	template <typename valType> 
	GLM_FUNC_DECL detail::tmat2x2<valType> inverse(
		detail::tmat2x2<valType> const & m);

	/// Return the inverse of a mat3 matrix. 
	/// 
	/// @tparam valType Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inverse.xml">GLSL inverse man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a> 
	template <typename valType> 
	GLM_FUNC_DECL detail::tmat3x3<valType> inverse(
		detail::tmat3x3<valType> const & m);

	/// Return the inverse of a mat4 matrix. 
	/// 
	/// @tparam valType Floating-point scalar types.
	///
	/// @see <a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inverse.xml">GLSL inverse man page</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</a>
	template <typename valType> 
	GLM_FUNC_DECL detail::tmat4x4<valType> inverse(
		detail::tmat4x4<valType> const & m);

	/// @}
}//namespace glm

#include "func_matrix.inl"

#endif//GLM_CORE_func_matrix
