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
/// @ref gtx_string_cast
/// @file glm/gtx/string_cast.hpp
/// @date 2008-04-26 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_half_float (dependence)
/// @see gtx_integer (dependence)
/// @see gtx_quaternion (dependence)
///
/// @defgroup gtx_string_cast GLM_GTX_string_cast
/// @ingroup gtx
/// 
/// @brief Setup strings for GLM type values
/// 
/// <glm/gtx/string_cast.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_string_cast
#define GLM_GTX_string_cast GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtx/integer.hpp"
#include "../gtx/quaternion.hpp"
#include <string>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_string_cast extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_string_cast
	/// @{

	/// Create a string from a GLM type value.
	/// From GLM_GTX_string_cast extension.
	template <typename genType> 
	std::string to_string(genType const & x);

	/// @}
}//namespace glm

#include "string_cast.inl"

#endif//GLM_GTX_string_cast
