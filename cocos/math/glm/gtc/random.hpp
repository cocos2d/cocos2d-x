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
/// @ref gtc_random
/// @file glm/gtc/random.hpp
/// @date 2011-09-18 / 2011-09-18
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_half_float (dependence)
/// @see gtx_random (extended)
///
/// @defgroup gtc_random GLM_GTC_random
/// @ingroup gtc
/// 
/// @brief Generate random number from various distribution methods.
/// 
/// <glm/gtc/random.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTC_random
#define GLM_GTC_random GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_random extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_random
	/// @{
	
	/// Generate random numbers in the interval [Min, Max], according a linear distribution 
	/// 
	/// @param Min 
	/// @param Max 
	/// @tparam genType Value type. Currently supported: half (not recommanded), float or double scalars and vectors.
	/// @see gtc_random
	template <typename genType> 
	genType linearRand(
		genType const & Min, 
		genType const & Max);

	/// Generate random numbers in the interval [Min, Max], according a gaussian distribution 
	/// 
	/// @param Mean
	/// @param Deviation
	/// @see gtc_random
	template <typename genType>
	genType gaussRand(
		genType const & Mean, 
		genType const & Deviation);
	
	/// Generate a random 2D vector which coordinates are regulary distributed on a circle of a given radius
	/// 
	/// @param Radius 
	/// @see gtc_random
	template <typename T> 
	detail::tvec2<T> circularRand(
		T const & Radius); 
	
	/// Generate a random 3D vector which coordinates are regulary distributed on a sphere of a given radius
	/// 
	/// @param Radius
	/// @see gtc_random
	template <typename T> 
	detail::tvec3<T> sphericalRand(
		T const & Radius); 
	
	/// Generate a random 2D vector which coordinates are regulary distributed within the area of a disk of a given radius
	/// 
	/// @param Radius
	/// @see gtc_random
	template <typename T> 
	detail::tvec2<T> diskRand(
		T const & Radius); 
	
	/// Generate a random 3D vector which coordinates are regulary distributed within the volume of a ball of a given radius
	/// 
	/// @param Radius
	/// @see gtc_random
	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> ballRand(
		T const & Radius);
	
	/// @}
}//namespace glm

#include "random.inl"

#endif//GLM_GTC_random
