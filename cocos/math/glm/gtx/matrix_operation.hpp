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
/// @ref gtx_matrix_operation
/// @file glm/gtx/matrix_operation.hpp
/// @date 2009-08-29 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_matrix_operation GLM_GTX_matrix_operation
/// @ingroup gtx
/// 
/// @brief Build diagonal matrices from vectors.
/// 
/// <glm/gtx/matrix_operation.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_matrix_operation
#define GLM_GTX_matrix_operation GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_matrix_operation extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_matrix_operation
	/// @{

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat2x2<valType> diagonal2x2(
		detail::tvec2<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat2x3<valType> diagonal2x3(
		detail::tvec2<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat2x4<valType> diagonal2x4(
		detail::tvec2<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat3x2<valType> diagonal3x2(
		detail::tvec2<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat3x3<valType> diagonal3x3(
		detail::tvec3<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat3x4<valType> diagonal3x4(
		detail::tvec3<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat4x2<valType> diagonal4x2(
		detail::tvec2<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat4x3<valType> diagonal4x3(
		detail::tvec3<valType> const & v);

	//! Build a diagonal matrix.
	//! From GLM_GTX_matrix_operation extension.
	template <typename valType> 
	detail::tmat4x4<valType> diagonal4x4(
		detail::tvec4<valType> const & v);

	/// @}
}//namespace glm

#include "matrix_operation.inl"

#endif//GLM_GTX_matrix_operation
