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
/// @ref gtx_transform2
/// @file glm/gtx/transform2.hpp
/// @date 2005-12-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtx_transform (dependence)
///
/// @defgroup gtx_transform2 GLM_GTX_transform2
/// @ingroup gtx
/// 
/// @brief Add extra transformation matrices
///
/// <glm/gtx/transform2.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_transform2
#define GLM_GTX_transform2 GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtx/transform.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_transform2 extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_transform2
	/// @{

	//! Transforms a matrix with a shearing on X axis.
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat3x3<T> shearX2D(
		detail::tmat3x3<T> const & m, 
		T y);

	//! Transforms a matrix with a shearing on Y axis.
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat3x3<T> shearY2D(
		detail::tmat3x3<T> const & m, 
		T x);

	//! Transforms a matrix with a shearing on X axis
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat4x4<T> shearX3D(
		const detail::tmat4x4<T> & m,
		T y, 
		T z);
		
	//! Transforms a matrix with a shearing on Y axis.
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat4x4<T> shearY3D(
		const detail::tmat4x4<T> & m, 
		T x, 
		T z);
		
	//! Transforms a matrix with a shearing on Z axis. 
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat4x4<T> shearZ3D(
		const detail::tmat4x4<T> & m, 
		T x, 
		T y);

	//template <typename T> GLM_FUNC_QUALIFIER detail::tmat4x4<T> shear(const detail::tmat4x4<T> & m, shearPlane, planePoint, angle)
	// Identity + tan(angle) * cross(Normal, OnPlaneVector)     0
	// - dot(PointOnPlane, normal) * OnPlaneVector              1

	// Reflect functions seem to don't work
	//template <typename T> detail::tmat3x3<T> reflect2D(const detail::tmat3x3<T> & m, const detail::tvec3<T>& normal){return reflect2DGTX(m, normal);}									//!< \brief Build a reflection matrix (from GLM_GTX_transform2 extension)
	//template <typename T> detail::tmat4x4<T> reflect3D(const detail::tmat4x4<T> & m, const detail::tvec3<T>& normal){return reflect3DGTX(m, normal);}									//!< \brief Build a reflection matrix (from GLM_GTX_transform2 extension)
		
	//! Build planar projection matrix along normal axis.
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat3x3<T> proj2D(
		const detail::tmat3x3<T> & m, 
		const detail::tvec3<T>& normal);
				
	//! Build planar projection matrix along normal axis.
	//! From GLM_GTX_transform2 extension.
	template <typename T> 
	detail::tmat4x4<T> proj3D(
		const detail::tmat4x4<T> & m, 
		const detail::tvec3<T>& normal);

	//! Build a scale bias matrix. 
	//! From GLM_GTX_transform2 extension.
	template <typename valType> 
	detail::tmat4x4<valType> scaleBias(
		valType scale, 
		valType bias);

	//! Build a scale bias matrix.
	//! From GLM_GTX_transform2 extension.
	template <typename valType> 
	detail::tmat4x4<valType> scaleBias(
		detail::tmat4x4<valType> const & m, 
		valType scale, 
		valType bias);

	/// @}
}// namespace glm

#include "transform2.inl"

#endif//GLM_GTX_transform2
