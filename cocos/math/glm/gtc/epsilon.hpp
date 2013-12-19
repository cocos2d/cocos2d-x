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
/// @ref gtc_epsilon
/// @file glm/gtc/epsilon.hpp
/// @date 2012-04-07 / 2012-04-07
/// @author Christophe Riccio
/// 
/// @see core (dependence)
/// @see gtc_half_float (dependence)
/// @see gtc_quaternion (dependence)
///
/// @defgroup gtc_epsilon GLM_GTC_epsilon
/// @ingroup gtc
/// 
/// @brief Comparison functions for a user defined epsilon values.
/// 
/// <glm/gtc/epsilon.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTC_epsilon
#define GLM_GTC_epsilon GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtc/quaternion.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_epsilon extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_epsilon
	/// @{

	/// Returns the component-wise compare of |x - y| < epsilon.
	/// @see gtc_epsilon
	template <typename genType>
	typename genType::boolType epsilonEqual(
		genType const & x,
		genType const & y,
		typename genType::value_type const & epsilon);

	/// Returns the component-wise compare of |x - y| < epsilon.
	/// @see gtc_epsilon
	template <typename genType> 
	typename genType::boolType epsilonEqual(
		genType const & x, 
		genType const & y, 
		genType const & epsilon);

	/// Returns the component-wise compare of |x - y| < epsilon.
	/// @see gtc_epsilon
	template <typename genType>
	typename genType::boolType epsilonNotEqual(
		genType const & x,
		genType const & y,
		typename genType::value_type const & epsilon);

	/// Returns the component-wise compare of |x - y| >= epsilon.
	/// @see gtc_epsilon
	template <typename genType>
	typename genType::boolType epsilonNotEqual(
		genType const & x, 
		genType const & y, 
		genType const & epsilon);

	/// @}
}//namespace glm

#include "epsilon.inl"

#endif//GLM_GTC_epsilon
