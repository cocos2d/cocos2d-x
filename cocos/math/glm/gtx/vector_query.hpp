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
/// @ref gtx_vector_query
/// @file glm/gtx/vector_query.hpp
/// @date 2008-03-10 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_vector_query GLM_GTX_vector_query
/// @ingroup gtx
/// 
/// @brief Query informations of vector types
///
/// <glm/gtx/vector_query.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_vector_query
#define GLM_GTX_vector_query GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include <cfloat>
#include <limits>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vector_query extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_vector_query
	/// @{

	//! Check whether two vectors are collinears.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool areCollinear(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon/* = std::numeric_limits<typename genType::value_type>::epsilon()*/);
		
    //! Check whether two vectors are orthogonals.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType> 
	bool areOrthogonal(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon/* = std::numeric_limits<typename genType::value_type>::epsilon()*/);

	//! Check whether a vector is normalized.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType, template <typename> class vecType> 
	bool isNormalized(
		vecType<genType> const & v, 
		genType const & epsilon/* = std::numeric_limits<genType>::epsilon()*/);
		
	//! Check whether a vector is null.
	//! From GLM_GTX_vector_query extensions.
	template <typename valType> 
	bool isNull(
		detail::tvec2<valType> const & v, 
		valType const & epsilon/* = std::numeric_limits<typename genType::value_type>::epsilon()*/);

	//! Check whether a vector is null.
	//! From GLM_GTX_vector_query extensions.
	template <typename valType> 
	bool isNull(
		detail::tvec3<valType> const & v, 
		valType const & epsilon/* = std::numeric_limits<typename genType::value_type>::epsilon()*/);

	//! Check whether a vector is null.
	//! From GLM_GTX_vector_query extensions.
	template <typename valType> 
	bool isNull(
		detail::tvec4<valType> const & v, 
		valType const & epsilon/* = std::numeric_limits<typename genType::value_type>::epsilon()*/);

	//! Check whether two vectors are orthonormal.
	//! From GLM_GTX_vector_query extensions.
	template <typename genType>
	bool areOrthonormal(
		genType const & v0, 
		genType const & v1, 
		typename genType::value_type const & epsilon/* = std::numeric_limits<typename genType::value_type>::epsilon()*/);

	/// @}
}// namespace glm

#include "vector_query.inl"

#endif//GLM_GTX_vector_query
