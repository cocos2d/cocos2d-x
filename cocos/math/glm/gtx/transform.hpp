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
/// @ref gtx_transform
/// @file glm/gtx/transform.hpp
/// @date 2005-12-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_matrix_transform (dependence)
/// @see gtx_transform
/// @see gtx_transform2
///
/// @defgroup gtx_transform GLM_GTX_transform
/// @ingroup gtx
///
/// @brief Add transformation matrices
/// 
/// <glm/gtx/transform.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_transform 
#define GLM_GTX_transform GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_transform.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_transform extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_transform
	/// @{

	//! Builds a translation 4 * 4 matrix created from 3 scalars.
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::translate GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> translate(
		T x, T y, T z);
		
	//! Transforms a matrix with a translation 4 * 4 matrix created from 3 scalars. 
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::translate GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> translate(
		detail::tmat4x4<T> const & m, 
		T x, T y, T z);
		
	//! Transforms a matrix with a translation 4 * 4 matrix created from 3 scalars. 
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::translate GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> translate(
		detail::tvec3<T> const & v);

	//! Builds a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in degrees. 
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::rotate GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> rotate(
		T angle, 
		T x, T y, T z);

	//! Builds a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in degrees. 
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::rotate GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> rotate(
		T angle, 
		detail::tvec3<T> const & v);

	//! Transforms a matrix with a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in degrees. 
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::rotate GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> rotate(
		detail::tmat4x4<T> const & m, 
		T angle, 
		T x, T y, T z);
		
	//! Builds a scale 4 * 4 matrix created from 3 scalars. 
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::scale GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> scale(
		T x, T y, T z);
		
	//! Transforms a matrix with a scale 4 * 4 matrix created from 3 scalars.
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::scale GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> scale(
		detail::tmat4x4<T> const & m, 
		T x, T y, T z);

	//! Transforms a matrix with a scale 4 * 4 matrix created from a vector of 3 components.
	//! - From \link gtx_transform GLM_GTX_transform \endlink extension
	// - See also: \link glm::scale GLM_GTC_matrix_transform \endlink
	template <typename T> 
	detail::tmat4x4<T> scale(
		detail::tvec3<T> const & v);

	/// @}
}// namespace glm

#include "transform.inl"

#endif//GLM_GTX_transform
