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
/// @ref core
/// @file glm/glm.hpp
/// @date 2005-01-14 / 2011-10-24
/// @author Christophe Riccio
///
///	@defgroup core GLM Core
///	
///	@brief The core of GLM, which implements exactly and only the GLSL specification to the degree possible.
///
/// The GLM core consists of @ref core_types "C++ types that mirror GLSL types" and
/// C++ functions that mirror the GLSL functions. It also includes 
/// @ref core_precision "a set of precision-based types" that can be used in the appropriate
/// functions. The C++ types are all based on a basic set of @ref core_template "template types".
/// 
/// The best documentation for GLM Core is the current GLSL specification,
/// <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.clean.pdf">version 4.2
/// (pdf file)</a>.
/// There are a few @ref pg_differences "differences" between GLM core and GLSL.
/// 
/// GLM core functionnalities require <glm/glm.hpp> to be included to be used.
/// 
/// @defgroup core_types Types
/// 
/// @brief The standard types defined by the specification.
/// 
/// These types are all typedefs of more generalized, template types. To see the definiton
/// of these template types, go to @ref core_template.
/// 
/// @ingroup core
/// 
/// @defgroup core_precision Precision types
/// 
/// @brief Non-GLSL types that are used to define precision-based types.
/// 
/// The GLSL language allows the user to define the precision of a particular variable.
/// In OpenGL's GLSL, these precision qualifiers have no effect; they are there for compatibility
/// with OpenGL ES's precision qualifiers, where they @em do have an effect.
/// 
/// C++ has no language equivalent to precision qualifiers. So GLM provides the next-best thing:
/// a number of typedefs of the @ref core_template that use a particular precision.
/// 
/// None of these types make any guarantees about the actual precision used.
/// 
/// @ingroup core
/// 
/// @defgroup core_template Template types
/// 
/// @brief The generic template types used as the basis for the core types. 
/// 
/// These types are all templates used to define the actual @ref core_types.
/// These templetes are implementation details of GLM types and should not be used explicitly.
/// 
/// @ingroup core
///////////////////////////////////////////////////////////////////////////////////

#include "core/_fixes.hpp"

#ifndef glm_glm
#define glm_glm

#include <cmath>
#include <climits>
#include <cfloat>
#include <limits>
#include <cstdio>
//#include <type_traits>
#include "core/setup.hpp"

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_CORE_INCLUDED_DISPLAYED))
#	define GLM_MESSAGE_CORE_INCLUDED_DISPLAYED
#	pragma message("GLM: Core library included")
#endif//GLM_MESSAGE

#include "./core/_detail.hpp"
#include "./core/_vectorize.hpp"
#include "./core/type.hpp"

#include "./core/func_trigonometric.hpp"
#include "./core/func_exponential.hpp"
#include "./core/func_common.hpp"
#include "./core/func_packing.hpp"
#include "./core/func_geometric.hpp"
#include "./core/func_matrix.hpp"
#include "./core/func_vector_relational.hpp"
#include "./core/func_integer.hpp"
#include "./core/func_noise.hpp"
#include "./core/_swizzle.hpp"

////////////////////
// check type sizes
#ifndef GLM_STATIC_ASSERT_NULL
	GLM_STATIC_ASSERT(sizeof(glm::detail::int8) == 1, "int8 size isn't 1 byte on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::int16) == 2, "int16 size isn't 2 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::int32) == 4, "int32 size isn't 4 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::int64) == 8, "int64 size isn't 8 bytes on this platform");

	GLM_STATIC_ASSERT(sizeof(glm::detail::uint8) == 1, "uint8 size isn't 1 byte on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::uint16) == 2, "uint16 size isn't 2 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::uint32) == 4, "uint32 size isn't 4 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::uint64) == 8, "uint64 size isn't 8 bytes on this platform");

	GLM_STATIC_ASSERT(sizeof(glm::detail::float16) == 2, "float16 size isn't 2 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::float32) == 4, "float32 size isn't 4 bytes on this platform");
	GLM_STATIC_ASSERT(sizeof(glm::detail::float64) == 8, "float64 size isn't 8 bytes on this platform");
#endif//GLM_STATIC_ASSERT_NULL

#endif//glm_glm
