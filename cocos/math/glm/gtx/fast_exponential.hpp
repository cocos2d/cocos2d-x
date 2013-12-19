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
/// @ref gtx_fast_exponential
/// @file glm/gtx/fast_exponential.hpp
/// @date 2006-01-09 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtx_half_float (dependence)
///
/// @defgroup gtx_fast_exponential GLM_GTX_fast_exponential
/// @ingroup gtx
/// 
/// @brief Fast but less accurate implementations of exponential based functions.
/// 
/// <glm/gtx/fast_exponential.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_fast_exponential
#define GLM_GTX_fast_exponential GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_fast_exponential extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_fast_exponential
	/// @{

	/// Faster than the common pow function but less accurate.
	/// @see gtx_fast_exponential
	template <typename genType> 
	genType fastPow(
		genType const & x, 
		genType const & y);

	/// Faster than the common pow function but less accurate.
	/// @see gtx_fast_exponential
	template <typename genTypeT, typename genTypeU> 
	genTypeT fastPow(
		genTypeT const & x, 
		genTypeU const & y);
		
	/// Faster than the common exp function but less accurate.
	/// @see gtx_fast_exponential
	template <typename T> 
	T fastExp(const T& x);
		
	/// Faster than the common log function but less accurate.
	/// @see gtx_fast_exponential
	template <typename T> 
	T fastLog(const T& x);

	/// Faster than the common exp2 function but less accurate.
	/// @see gtx_fast_exponential
	template <typename T> 
	T fastExp2(const T& x);
		
	/// Faster than the common log2 function but less accurate.
	/// @see gtx_fast_exponential
	template <typename T> 
	T fastLog2(const T& x);

	/// Faster than the common ln function but less accurate.
	/// @see gtx_fast_exponential
	template <typename T> 
	T fastLn(const T& x);

	/// @}
}//namespace glm

#include "fast_exponential.inl"

#endif//GLM_GTX_fast_exponential
