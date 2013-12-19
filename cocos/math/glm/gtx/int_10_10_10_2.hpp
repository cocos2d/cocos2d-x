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
/// @ref gtx_int_10_10_10_2
/// @file glm/gtx/int_10_10_10_2.hpp
/// @date 2010-07-07 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtx_raw_data (dependence)
///
/// @defgroup gtx_int_10_10_10_2 GLM_GTX_int_10_10_10_2
/// @ingroup gtx
/// 
/// @brief Pack vector to 1010102 integers. Storage only.
/// 
/// <glm/gtx/int_10_10_10_2.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_int_10_10_10_2
#define GLM_GTX_int_10_10_10_2 GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtx/raw_data.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_int_10_10_10_2 extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_int_10_10_10_2
	/// @{

	//! From GLM_GTX_int_10_10_10_2 extension.
	//! Cast a vec4 to an u_10_10_10_2.
	dword uint10_10_10_2_cast(glm::vec4 const & v);

	/// @}
}//namespace glm

#include "int_10_10_10_2.inl"

#endif//GLM_GTX_int_10_10_10_2
