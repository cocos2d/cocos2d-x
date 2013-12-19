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
/// @ref gtx_handed_coordinate_space
/// @file glm/gtx/handed_coordinate_space.hpp
/// @date 2005-12-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_handed_coordinate_space GLM_GTX_handed_coordinate_space
/// @ingroup gtx
/// 
/// @brief To know if a set of three basis vectors defines a right or left-handed coordinate system.
/// 
/// <glm/gtx/handed_coordinate_system.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_handed_coordinate_space
#define GLM_GTX_handed_coordinate_space GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_handed_coordinate_space extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_handed_coordinate_space
	/// @{

	//! Return if a trihedron right handed or not.
	//! From GLM_GTX_handed_coordinate_space extension.
	template <typename T> 
	bool rightHanded(
		detail::tvec3<T> const & tangent, 
		detail::tvec3<T> const & binormal, 
		detail::tvec3<T> const & normal);

	//! Return if a trihedron left handed or not.
	//! From GLM_GTX_handed_coordinate_space extension.
	template <typename T> 
	bool leftHanded(
		detail::tvec3<T> const & tangent, 
		detail::tvec3<T> const & binormal, 
		detail::tvec3<T> const & normal);

	/// @}
}// namespace glm

#include "handed_coordinate_space.inl"

#endif//GLM_GTX_handed_coordinate_space
