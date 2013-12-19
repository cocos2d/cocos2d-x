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
/// @ref gtx_vector_access
/// @file glm/gtx/vector_access.hpp
/// @date 2006-01-16 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_vector_access GLM_GTX_vector_access
/// @ingroup gtx
/// 
/// @brief Function to set values to vectors
/// 
/// <glm/gtx/vector_access.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_vector_access
#define GLM_GTX_vector_access GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vector_access extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_vector_access
	/// @{

	//! Set values to a 2 components vector.
	//! From GLM_GTX_vector_access extension.
    template <typename valType> 
	void set(
		detail::tvec2<valType> & v, 
		valType const & x, 
		valType const & y);

	//! Set values to a 3 components vector.
	//! From GLM_GTX_vector_access extension.
    template <typename valType> 
	void set(
		detail::tvec3<valType> & v, 
		valType const & x, 
		valType const & y, 
		valType const & z);

	//! Set values to a 4 components vector.
	//! From GLM_GTX_vector_access extension.
    template <typename valType> 
	void set(
		detail::tvec4<valType> & v, 
		valType const & x, 
		valType const & y, 
		valType const & z, 
		valType const & w);

	/// @}
}//namespace glm

#include "vector_access.inl"

#endif//GLM_GTX_vector_access
