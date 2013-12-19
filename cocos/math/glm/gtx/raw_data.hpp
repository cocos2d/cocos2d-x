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
/// @ref gtx_raw_data
/// @file glm/gtx/raw_data.hpp
/// @date 2008-11-19 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_raw_data GLM_GTX_raw_data
/// @ingroup gtx
/// 
/// @brief Projection of a vector to other one
/// 
/// <glm/gtx/raw_data.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_raw_data
#define GLM_GTX_raw_data GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/type_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_raw_data extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_raw_data
	/// @{

	//! Type for byte numbers. 
	//! From GLM_GTX_raw_data extension.
	typedef uint8		byte;

	//! Type for word numbers. 
	//! From GLM_GTX_raw_data extension.
	typedef uint16		word;

	//! Type for dword numbers. 
	//! From GLM_GTX_raw_data extension.
	typedef uint32		dword;

	//! Type for qword numbers. 
	//! From GLM_GTX_raw_data extension.
	typedef uint64		qword;

	/// @}
}// namespace glm

#include "raw_data.inl"

#endif//GLM_GTX_raw_data
