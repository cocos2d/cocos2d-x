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
/// @ref gtx_vec1
/// @file glm/gtx/vec1.hpp
/// @date 2010-02-08 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_vec1 GLM_GTX_vec1
/// @ingroup gtx
/// 
/// @brief Add vec1, ivec1, uvec1 and bvec1 types.
/// <glm/gtx/vec1.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_vec1
#define GLM_GTX_vec1 GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../core/type_vec1.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_vec1 extension included")
#endif

namespace glm
{
	//! 1 component vector of high precision floating-point numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::highp_vec1_t			highp_vec1;
	//! 1 component vector of medium precision floating-point numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::mediump_vec1_t			mediump_vec1;
	//! 1 component vector of low precision floating-point numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::lowp_vec1_t				lowp_vec1;

	//! 1 component vector of high precision signed integer numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::highp_ivec1_t			highp_ivec1;
	//! 1 component vector of medium precision signed integer numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::mediump_ivec1_t			mediump_ivec1;
	//! 1 component vector of low precision signed integer numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::lowp_ivec1_t			lowp_ivec1;

	//! 1 component vector of high precision unsigned integer numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::highp_uvec1_t			highp_uvec1;
	//! 1 component vector of medium precision unsigned integer numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::mediump_uvec1_t			mediump_uvec1;
	//! 1 component vector of low precision unsigned integer numbers. 
	//! There is no guarantee on the actual precision.
	//! From GLM_GTX_vec1 extension.
	typedef detail::lowp_uvec1_t			lowp_uvec1;

	//////////////////////////
	// vec1 definition

	//! 1 component vector of boolean.
	//! From GLM_GTX_vec1 extension.
	typedef detail::tvec1<bool>	bvec1;

#if(defined(GLM_PRECISION_HIGHP_FLOAT))
	typedef highp_vec1			vec1;
#elif(defined(GLM_PRECISION_MEDIUMP_FLOAT))
	typedef mediump_vec1			vec1;
#elif(defined(GLM_PRECISION_LOWP_FLOAT))
	typedef lowp_vec1			vec1;
#else
	//! 1 component vector of floating-point numbers.
	//! From GLM_GTX_vec1 extension.
	typedef mediump_vec1			vec1;
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION_HIGHP_INT))
	typedef highp_ivec1			ivec1;
#elif(defined(GLM_PRECISION_MEDIUMP_INT))
	typedef mediump_ivec1		ivec1;
#elif(defined(GLM_PRECISION_LOWP_INT))
	typedef lowp_ivec1			ivec1;
#else
	//! 1 component vector of signed integer numbers. 
	//! From GLM_GTX_vec1 extension.
	typedef mediump_ivec1		ivec1;
#endif//GLM_PRECISION

#if(defined(GLM_PRECISION_HIGHP_UINT))
	typedef highp_uvec1			uvec1;
#elif(defined(GLM_PRECISION_MEDIUMP_UINT))
	typedef mediump_uvec1		uvec1;
#elif(defined(GLM_PRECISION_LOWP_UINT))
	typedef lowp_uvec1			uvec1;
#else
	//! 1 component vector of unsigned integer numbers. 
	//! From GLM_GTX_vec1 extension.
	typedef mediump_uvec1		uvec1;
#endif//GLM_PRECISION

}// namespace glm

#include "vec1.inl"

#endif//GLM_GTX_vec1

