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
/// @ref gtc_type_precision
/// @file glm/gtc/type_precision.hpp
/// @date 2009-06-04 / 2011-12-07
/// @author Christophe Riccio
/// 
/// @see core (dependence)
/// @see gtc_half_float (dependence)
/// @see gtc_quaternion (dependence)
/// 
/// @defgroup gtc_type_precision GLM_GTC_type_precision
/// @ingroup gtc
/// 
/// @brief Defines specific C++-based precision types.
/// 
/// @ref core_precision defines types based on GLSL's precision qualifiers. This
/// extension defines types based on explicitly-sized C++ data types.
/// 
/// <glm/gtc/type_precision.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTC_type_precision
#define GLM_GTC_type_precision GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtc/quaternion.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_type_precision extension included")
#endif

namespace glm
{
	///////////////////////////
	// Signed int vector types 

	/// @addtogroup gtc_type_precision
	/// @{

	/// 8 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int8 int8;
	
	/// 16 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int16 int16;

	/// 32 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int32 int32;

	/// 64 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int64 int64;


	/// 8 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int8 int8_t;
	
	/// 16 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int16 int16_t;

	/// 32 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int32 int32_t;

	/// 64 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int64 int64_t;


	/// 8 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int8 i8;
	
	/// 16 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int16 i16;

	/// 32 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int32 i32;

	/// 64 bit signed integer type. 
	/// @see gtc_type_precision
	typedef detail::int64 i64;


	/// 8 bit signed integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<i8> i8vec1;
	
	/// 8 bit signed integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<i8> i8vec2;

	/// 8 bit signed integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<i8> i8vec3;

	/// 8 bit signed integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<i8> i8vec4;


	/// 16 bit signed integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<i16> i16vec1;
	
	/// 16 bit signed integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<i16> i16vec2;

	/// 16 bit signed integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<i16> i16vec3;

	/// 16 bit signed integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<i16> i16vec4;


	/// 32 bit signed integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<i32> i32vec1;
	
	/// 32 bit signed integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<i32> i32vec2;

	/// 32 bit signed integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<i32> i32vec3;

	/// 32 bit signed integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<i32> i32vec4;


	/// 64 bit signed integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<i64> i64vec1;
	
	/// 64 bit signed integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<i64> i64vec2;

	/// 64 bit signed integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<i64> i64vec3;

	/// 64 bit signed integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<i64> i64vec4;


	/////////////////////////////
	// Unsigned int vector types 

	/// 8 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint8 uint8;
	
	/// 16 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint16 uint16;

	/// 32 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint32 uint32;

	/// 64 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint64 uint64;


	/// 8 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint8 uint8_t;
	
	/// 16 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint16 uint16_t;

	/// 32 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint32 uint32_t;

	/// 64 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint64 uint64_t;


	/// 8 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint8 u8;
	
	/// 16 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint16 u16;

	/// 32 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint32 u32;

	/// 64 bit unsigned integer type. 
	/// @see gtc_type_precision
	typedef detail::uint64 u64;


	/// 8 bit unsigned integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<u8> u8vec1;
	
	/// 8 bit unsigned integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<u8> u8vec2;

	/// 8 bit unsigned integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<u8> u8vec3;

	/// 8 bit unsigned integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<u8> u8vec4;


	/// 16 bit unsigned integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<u16> u16vec1;
	
	/// 16 bit unsigned integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<u16> u16vec2;

	/// 16 bit unsigned integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<u16> u16vec3;

	/// 16 bit unsigned integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<u16> u16vec4;


	/// 32 bit unsigned integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<u32> u32vec1;
	
	/// 32 bit unsigned integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<u32> u32vec2;

	/// 32 bit unsigned integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<u32> u32vec3;

	/// 32 bit unsigned integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<u32> u32vec4;


	/// 64 bit unsigned integer scalar type. 
	/// @see gtc_type_precision
	typedef detail::tvec1<u64> u64vec1;
	
	/// 64 bit unsigned integer vector of 2 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec2<u64> u64vec2;

	/// 64 bit unsigned integer vector of 3 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec3<u64> u64vec3;

	/// 64 bit unsigned integer vector of 4 components type. 
	/// @see gtc_type_precision
	typedef detail::tvec4<u64> u64vec4;


	//////////////////////
	// Float vector types 

	/// 16 bit half-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef detail::float16 float16;

	/// 32 bit single-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef detail::float32 float32;

	/// 64 bit double-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef detail::float64 float64;


	/// 16 bit half-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef detail::float16 float16_t;

	/// 32 bit single-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef detail::float32 float32_t;

	/// 64 bit double-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef detail::float64 float64_t;


	/// 16 bit half-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef float16 f16;

	/// 32 bit single-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef float32 f32;

	/// 64 bit double-precision floating-point scalar. 
	/// @see gtc_type_precision
	typedef float64 f64;


	/// Single-precision floating-point vector of 1 component. 
	/// @see gtc_type_precision
	typedef detail::tvec1<float> fvec1;

	/// Single-precision floating-point vector of 2 components. 
	/// @see gtc_type_precision
	typedef detail::tvec2<float> fvec2;

	/// Single-precision floating-point vector of 3 components. 
	/// @see gtc_type_precision
	typedef detail::tvec3<float> fvec3;

	/// Single-precision floating-point vector of 4 components. 
	/// @see gtc_type_precision
	typedef detail::tvec4<float> fvec4;


	/// Half-precision floating-point vector of 1 component. 
	/// @see gtc_type_precision
	typedef detail::tvec1<f16> f16vec1;

	/// Half-precision floating-point vector of 2 components. 
	/// @see gtc_type_precision
	typedef detail::tvec2<f16> f16vec2;

	/// Half-precision floating-point vector of 3 components. 
	/// @see gtc_type_precision
	typedef detail::tvec3<f16> f16vec3;

	/// Half-precision floating-point vector of 4 components. 
	/// @see gtc_type_precision
	typedef detail::tvec4<f16> f16vec4;

	
	/// Single-precision floating-point vector of 1 component. 
	/// @see gtc_type_precision
	typedef detail::tvec1<f32> f32vec1;

	/// Single-precision floating-point vector of 2 components. 
	/// @see gtc_type_precision
	typedef detail::tvec2<f32> f32vec2;

	/// Single-precision floating-point vector of 3 components. 
	/// @see gtc_type_precision
	typedef detail::tvec3<f32> f32vec3;

	/// Single-precision floating-point vector of 4 components. 
	/// @see gtc_type_precision
	typedef detail::tvec4<f32> f32vec4;


	/// Double-precision floating-point vector of 1 component. 
	/// @see gtc_type_precision
	typedef detail::tvec1<f64> f64vec1;

	/// Double-precision floating-point vector of 2 components. 
	/// @see gtc_type_precision
	typedef detail::tvec2<f64> f64vec2;

	/// Double-precision floating-point vector of 3 components. 
	/// @see gtc_type_precision
	typedef detail::tvec3<f64> f64vec3;

	/// Double-precision floating-point vector of 4 components. 
	/// @see gtc_type_precision
	typedef detail::tvec4<f64> f64vec4;


	//////////////////////
	// Float matrix types 

	/// Single-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef detail::tmat1x1<f32> fmat1;

	/// Single-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f32> fmat2;

	/// Single-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f32> fmat3;

	/// Single-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f32> fmat4;


	/// Single-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef f32 fmat1x1;

	/// Single-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f32> fmat2x2;

	/// Single-precision floating-point 2x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x3<f32> fmat2x3;

	/// Single-precision floating-point 2x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x4<f32> fmat2x4;

	/// Single-precision floating-point 3x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x2<f32> fmat3x2;

	/// Single-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f32> fmat3x3;

	/// Single-precision floating-point 3x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x4<f32> fmat3x4;

	/// Single-precision floating-point 4x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x2<f32> fmat4x2;

	/// Single-precision floating-point 4x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x3<f32> fmat4x3;

	/// Single-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f32> fmat4x4;


	/// Half-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef detail::tmat1x1<f16> f16mat1;

	/// Half-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f16> f16mat2;

	/// Half-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f16> f16mat3;

	/// Half-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f16> f16mat4;


	/// Half-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef f16 f16mat1x1;

	/// Half-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f16> f16mat2x2;

	/// Half-precision floating-point 2x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x3<f16> f16mat2x3;

	/// Half-precision floating-point 2x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x4<f16> f16mat2x4;

	/// Half-precision floating-point 3x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x2<f16> f16mat3x2;

	/// Half-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f16> f16mat3x3;

	/// Half-precision floating-point 3x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x4<f16> f16mat3x4;

	/// Half-precision floating-point 4x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x2<f16> f16mat4x2;

	/// Half-precision floating-point 4x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x3<f16> f16mat4x3;

	/// Half-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f16> f16mat4x4;


	/// Single-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef detail::tmat1x1<f32> f32mat1;

	/// Single-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f32> f32mat2;

	/// Single-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f32> f32mat3;

	/// Single-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f32> f32mat4;


	/// Single-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef f32 f32mat1x1;

	/// Single-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f32> f32mat2x2;

	/// Single-precision floating-point 2x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x3<f32> f32mat2x3;

	/// Single-precision floating-point 2x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x4<f32> f32mat2x4;

	/// Single-precision floating-point 3x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x2<f32> f32mat3x2;

	/// Single-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f32> f32mat3x3;

	/// Single-precision floating-point 3x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x4<f32> f32mat3x4;

	/// Single-precision floating-point 4x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x2<f32> f32mat4x2;

	/// Single-precision floating-point 4x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x3<f32> f32mat4x3;

	/// Single-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f32> f32mat4x4;


	/// Double-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef detail::tmat1x1<f64> f64mat1;

	/// Double-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f64> f64mat2;

	/// Double-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f64> f64mat3;

	/// Double-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f64> f64mat4;


	/// Double-precision floating-point 1x1 matrix. 
	/// @see gtc_type_precision
	//typedef f64 f64mat1x1;

	/// Double-precision floating-point 2x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x2<f64> f64mat2x2;

	/// Double-precision floating-point 2x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x3<f64> f64mat2x3;

	/// Double-precision floating-point 2x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat2x4<f64> f64mat2x4;

	/// Double-precision floating-point 3x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x2<f64> f64mat3x2;

	/// Double-precision floating-point 3x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x3<f64> f64mat3x3;

	/// Double-precision floating-point 3x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat3x4<f64> f64mat3x4;

	/// Double-precision floating-point 4x2 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x2<f64> f64mat4x2;

	/// Double-precision floating-point 4x3 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x3<f64> f64mat4x3;

	/// Double-precision floating-point 4x4 matrix. 
	/// @see gtc_type_precision
	typedef detail::tmat4x4<f64> f64mat4x4;


	//////////////////////////
	// Quaternion types 

	/// Half-precision floating-point quaternion. 
	/// @see gtc_type_precision
	typedef detail::tquat<f16> f16quat;

	/// Single-precision floating-point quaternion. 
	/// @see gtc_type_precision
	typedef detail::tquat<f32> f32quat;

	/// Double-precision floating-point quaternion. 
	/// @see gtc_type_precision
	typedef detail::tquat<f64> f64quat;

	/// @}
}//namespace glm

#include "type_precision.inl"

#endif//GLM_GTC_type_precision
