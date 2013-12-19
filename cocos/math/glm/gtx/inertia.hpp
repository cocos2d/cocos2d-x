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
/// @ref gtx_inertia
/// @file glm/gtx/inertia.hpp
/// @date 2006-04-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_inertia GLM_GTX_inertia
/// @ingroup gtx
/// 
/// @brief Create inertia matrices
/// 
/// <glm/gtx/inertia.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_inertia
#define GLM_GTX_inertia GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_inertia extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_inertia
	/// @{

	//! Build an inertia matrix for a box.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat3x3<T> boxInertia3(
		T const & Mass, 
		detail::tvec3<T> const & Scale);
		
	//! Build an inertia matrix for a box.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat4x4<T> boxInertia4(
		T const & Mass, 
		detail::tvec3<T> const & Scale);
		
	//! Build an inertia matrix for a disk.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat3x3<T> diskInertia3(
		T const & Mass, 
		T const & Radius);

	//! Build an inertia matrix for a disk.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat4x4<T> diskInertia4(
		T const & Mass, 
		T const & Radius);

	//! Build an inertia matrix for a ball.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat3x3<T> ballInertia3(
		T const & Mass, 
		T const & Radius);
		
	//! Build an inertia matrix for a ball.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat4x4<T> ballInertia4(
		T const & Mass, 
		T const & Radius);

	//! Build an inertia matrix for a sphere.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat3x3<T> sphereInertia3(
		T const & Mass, 
		T const & Radius);

	//! Build an inertia matrix for a sphere.
	//! From GLM_GTX_inertia extension.
	template <typename T> 
	detail::tmat4x4<T> sphereInertia4(
		T const & Mass, 
		T const & Radius);

	/// @}
}// namespace glm

#include "inertia.inl"

#endif//GLM_GTX_inertia
