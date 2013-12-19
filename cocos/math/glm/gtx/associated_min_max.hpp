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
/// @ref gtx_associated_min_max
/// @file glm/gtx/associated_min_max.hpp
/// @date 2008-03-10 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtx_extented_min_max (dependence)
///
/// @defgroup gtx_associated_min_max GLM_GTX_associated_min_max
/// @ingroup gtx
/// 
/// @brief Min and max functions that return associated values not the compared onces.
/// <glm/gtx/associated_min_max.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_associated_min_max
#define GLM_GTX_associated_min_max GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_associated_min_max extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_associated_min_max
	/// @{

	/// Min comparison between 2 variables
	/// @see gtx_associated_min_max
	template<typename genTypeT, typename genTypeU>
	genTypeU associatedMin(
		const genTypeT& x, const genTypeU& a, 
		const genTypeT& y, const genTypeU& b);

	/// Min comparison between 3 variables
	/// @see gtx_associated_min_max
	template<typename genTypeT, typename genTypeU>
	genTypeU associatedMin(
		const genTypeT& x, const genTypeU& a, 
		const genTypeT& y, const genTypeU& b, 
		const genTypeT& z, const genTypeU& c);

	/// Min comparison between 4 variables
	/// @see gtx_associated_min_max
	template<typename genTypeT, typename genTypeU>
	genTypeU associatedMin(
		const genTypeT& x, const genTypeU& a, 
		const genTypeT& y, const genTypeU& b, 
		const genTypeT& z, const genTypeU& c, 
		const genTypeT& w, const genTypeU& d);

	/// Max comparison between 2 variables
	/// @see gtx_associated_min_max
	template<typename genTypeT, typename genTypeU>
	genTypeU associatedMax(
		const genTypeT& x, const genTypeU& a, 
		const genTypeT& y, const genTypeU& b);

	/// Max comparison between 3 variables
	/// @see gtx_associated_min_max
	template<typename genTypeT, typename genTypeU>
	genTypeU associatedMax(
		const genTypeT& x, const genTypeU& a, 
		const genTypeT& y, const genTypeU& b, 
		const genTypeT& z, const genTypeU& c);

	/// Max comparison between 4 variables
	/// @see gtx_associated_min_max
	template<typename genTypeT, typename genTypeU>
	genTypeU associatedMax(
		const genTypeT& x, const genTypeU& a, 
		const genTypeT& y, const genTypeU& b, 
		const genTypeT& z, const genTypeU& c, 
		const genTypeT& w, const genTypeU& d);

	/// @}
} //namespace glm

#include "associated_min_max.inl"

#endif//GLM_GTX_associated_min_max
