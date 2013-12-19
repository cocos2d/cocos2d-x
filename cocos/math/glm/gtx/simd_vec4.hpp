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
/// @ref gtx_simd_vec4
/// @file glm/gtx/simd_vec4.hpp
/// @date 2009-05-07 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_simd_vec4 GLM_GTX_simd_vec4
/// @ingroup gtx
/// 
/// @brief SIMD implementation of vec4 type.
/// 
/// <glm/gtx/simd_vec4.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_simd_vec4
#define GLM_GTX_simd_vec4 GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(GLM_ARCH != GLM_ARCH_PURE)

#if(GLM_ARCH & GLM_ARCH_SSE2)
#	include "../core/intrinsic_common.hpp"
#	include "../core/intrinsic_geometric.hpp"
#else
#	error "GLM: GLM_GTX_simd_vec4 requires compiler support of SSE2 through intrinsics"
#endif

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_simd_vec4 extension included")
#endif


// Warning silencer for nameless struct/union.
#if (GLM_COMPILER & GLM_COMPILER_VC)
#   pragma warning(push)
#   pragma warning(disable:4201)   // warning C4201: nonstandard extension used : nameless struct/union
#endif


namespace glm{
namespace detail
{
	/// 4-dimensional vector implemented using SIMD SEE intrinsics.
	/// \ingroup gtx_simd_vec4
	GLM_ALIGNED_STRUCT(16) fvec4SIMD
	{
		enum ctor{null};
		typedef __m128 value_type;
		typedef std::size_t size_type;
		static size_type value_size();

		typedef fvec4SIMD type;
		typedef tvec4<bool> bool_type;

#ifdef GLM_SIMD_ENABLE_XYZW_UNION
        union
        {
		    __m128 Data;
            struct {float x, y, z, w;};
        };
#else
        __m128 Data;
#endif

		//////////////////////////////////////
		// Implicit basic constructors

		fvec4SIMD();
		fvec4SIMD(__m128 const & Data);
		fvec4SIMD(fvec4SIMD const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		explicit fvec4SIMD(
			ctor);
		explicit fvec4SIMD(
			float const & s);
		explicit fvec4SIMD(
			float const & x, 
			float const & y, 
			float const & z, 
			float const & w);
		explicit fvec4SIMD(
			tvec4<float> const & v);

		////////////////////////////////////////
		//// Convertion vector constructors

		fvec4SIMD(vec2 const & v, float const & s1, float const & s2);
		fvec4SIMD(float const & s1, vec2 const & v, float const & s2);
		fvec4SIMD(float const & s1, float const & s2, vec2 const & v);
		fvec4SIMD(vec3 const & v, float const & s);
		fvec4SIMD(float const & s, vec3 const & v);
		fvec4SIMD(vec2 const & v1, vec2 const & v2);
		//fvec4SIMD(ivec4SIMD const & v);

		//////////////////////////////////////
		// Unary arithmetic operators

		fvec4SIMD& operator= (fvec4SIMD const & v);
		fvec4SIMD& operator+=(fvec4SIMD const & v);
		fvec4SIMD& operator-=(fvec4SIMD const & v);
		fvec4SIMD& operator*=(fvec4SIMD const & v);
		fvec4SIMD& operator/=(fvec4SIMD const & v);

		fvec4SIMD& operator+=(float const & s);
		fvec4SIMD& operator-=(float const & s);
		fvec4SIMD& operator*=(float const & s);
		fvec4SIMD& operator/=(float const & s);

		fvec4SIMD& operator++();
		fvec4SIMD& operator--();

		//////////////////////////////////////
		// Swizzle operators

		template <comp X, comp Y, comp Z, comp W>
		fvec4SIMD& swizzle();
		template <comp X, comp Y, comp Z, comp W>
		fvec4SIMD swizzle() const;
		template <comp X, comp Y, comp Z>
		fvec4SIMD swizzle() const;
		template <comp X, comp Y>
		fvec4SIMD swizzle() const;
		template <comp X>
		fvec4SIMD swizzle() const;
	};
}//namespace detail

	typedef glm::detail::fvec4SIMD simdVec4;

	/// @addtogroup gtx_simd_vec4
	/// @{

	//! Convert a simdVec4 to a vec4.
	//! (From GLM_GTX_simd_vec4 extension)
	detail::tvec4<float> vec4_cast(
		detail::fvec4SIMD const & x);

	//! Returns x if x >= 0; otherwise, it returns -x. 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD abs(detail::fvec4SIMD const & x);

	//! Returns 1.0 if x > 0, 0.0 if x = 0, or -1.0 if x < 0. 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD sign(detail::fvec4SIMD const & x);

	//! Returns a value equal to the nearest integer that is less then or equal to x. 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD floor(detail::fvec4SIMD const & x);

	//! Returns a value equal to the nearest integer to x 
	//! whose absolute value is not larger than the absolute value of x. 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD trunc(detail::fvec4SIMD const & x);

	//! Returns a value equal to the nearest integer to x. 
	//! The fraction 0.5 will round in a direction chosen by the 
	//! implementation, presumably the direction that is fastest. 
	//! This includes the possibility that round(x) returns the 
	//! same value as roundEven(x) for all values of x. 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD round(detail::fvec4SIMD const & x);

	//! Returns a value equal to the nearest integer to x.
	//! A fractional part of 0.5 will round toward the nearest even
	//! integer. (Both 3.5 and 4.5 for x will return 4.0.) 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//detail::fvec4SIMD roundEven(detail::fvec4SIMD const & x);

	//! Returns a value equal to the nearest integer 
	//! that is greater than or equal to x. 
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD ceil(detail::fvec4SIMD const & x);

	//! Return x - floor(x).
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD fract(detail::fvec4SIMD const & x);

	//! Modulus. Returns x - y * floor(x / y) 
	//! for each component in x using the floating point value y.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD mod(
		detail::fvec4SIMD const & x, 
		detail::fvec4SIMD const & y);

	//! Modulus. Returns x - y * floor(x / y) 
	//! for each component in x using the floating point value y.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD mod(
		detail::fvec4SIMD const & x, 
		float const & y);

	//! Returns the fractional part of x and sets i to the integer
	//! part (as a whole number floating point value). Both the
	//! return value and the output parameter will have the same
	//! sign as x.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//detail::fvec4SIMD modf(
	//	detail::fvec4SIMD const & x, 
	//	detail::fvec4SIMD & i);

	//! Returns y if y < x; otherwise, it returns x.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD min(
		detail::fvec4SIMD const & x, 
		detail::fvec4SIMD const & y);

	detail::fvec4SIMD min(
		detail::fvec4SIMD const & x, 
		float const & y);

	//! Returns y if x < y; otherwise, it returns x.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD max(
		detail::fvec4SIMD const & x, 
		detail::fvec4SIMD const & y);

	detail::fvec4SIMD max(
		detail::fvec4SIMD const & x, 
		float const & y);

	//! Returns min(max(x, minVal), maxVal) for each component in x 
	//! using the floating-point values minVal and maxVal.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD clamp(
		detail::fvec4SIMD const & x, 
		detail::fvec4SIMD const & minVal, 
		detail::fvec4SIMD const & maxVal); 

	detail::fvec4SIMD clamp(
		detail::fvec4SIMD const & x, 
		float const & minVal, 
		float const & maxVal); 

	//! \return If genTypeU is a floating scalar or vector: 
	//! Returns x * (1.0 - a) + y * a, i.e., the linear blend of 
	//! x and y using the floating-point value a. 
	//! The value for a is not restricted to the range [0, 1].
	//!
	//! \return If genTypeU is a boolean scalar or vector: 
	//! Selects which vector each returned component comes
	//! from. For a component of a that is false, the
	//! corresponding component of x is returned. For a
	//! component of a that is true, the corresponding
	//! component of y is returned. Components of x and y that
	//! are not selected are allowed to be invalid floating point
	//! values and will have no effect on the results. Thus, this
	//! provides different functionality than
	//! genType mix(genType x, genType y, genType(a))
	//! where a is a Boolean vector.
	//! 
	//! From GLSL 1.30.08 specification, section 8.3
	//! 
	//! \param[in]  x Floating point scalar or vector.
	//! \param[in]  y Floating point scalar or vector.
	//! \param[in]  a Floating point or boolean scalar or vector.
	//!
	// \todo Test when 'a' is a boolean.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD mix(
		detail::fvec4SIMD const & x, 
		detail::fvec4SIMD const & y, 
		detail::fvec4SIMD const & a);

	//! Returns 0.0 if x < edge, otherwise it returns 1.0.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD step(
		detail::fvec4SIMD const & edge, 
		detail::fvec4SIMD const & x);

	detail::fvec4SIMD step(
		float const & edge, 
		detail::fvec4SIMD const & x);

	//! Returns 0.0 if x <= edge0 and 1.0 if x >= edge1 and
	//! performs smooth Hermite interpolation between 0 and 1
	//! when edge0 < x < edge1. This is useful in cases where
	//! you would want a threshold function with a smooth
	//! transition. This is equivalent to:
	//! genType t;
	//! t = clamp ((x - edge0) / (edge1 - edge0), 0, 1);
	//! return t * t * (3 - 2 * t);
	//! Results are undefined if edge0 >= edge1.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD smoothstep(
		detail::fvec4SIMD const & edge0, 
		detail::fvec4SIMD const & edge1, 
		detail::fvec4SIMD const & x);

	detail::fvec4SIMD smoothstep(
		float const & edge0, 
		float const & edge1, 
		detail::fvec4SIMD const & x);

	//! Returns true if x holds a NaN (not a number)
	//! representation in the underlying implementation's set of
	//! floating point representations. Returns false otherwise,
	//! including for implementations with no NaN
	//! representations.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//bvec4 isnan(detail::fvec4SIMD const & x);

	//! Returns true if x holds a positive infinity or negative
	//! infinity representation in the underlying implementation's
	//! set of floating point representations. Returns false
	//! otherwise, including for implementations with no infinity
	//! representations.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//bvec4 isinf(detail::fvec4SIMD const & x);

	//! Returns a signed or unsigned integer value representing
	//! the encoding of a floating-point value. The floatingpoint
	//! value's bit-level representation is preserved.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//detail::ivec4SIMD floatBitsToInt(detail::fvec4SIMD const & value);

	//! Returns a floating-point value corresponding to a signed
	//! or unsigned integer encoding of a floating-point value.
	//! If an inf or NaN is passed in, it will not signal, and the
	//! resulting floating point value is unspecified. Otherwise,
	//! the bit-level representation is preserved.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//detail::fvec4SIMD intBitsToFloat(detail::ivec4SIMD const & value);

	//! Computes and returns a * b + c.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	detail::fvec4SIMD fma(
		detail::fvec4SIMD const & a, 
		detail::fvec4SIMD const & b, 
		detail::fvec4SIMD const & c);

	//! Splits x into a floating-point significand in the range
	//! [0.5, 1.0) and an integral exponent of two, such that:
	//! x = significand * exp(2, exponent)
	//! The significand is returned by the function and the
	//! exponent is returned in the parameter exp. For a
	//! floating-point value of zero, the significant and exponent
	//! are both zero. For a floating-point value that is an
	//! infinity or is not a number, the results are undefined.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//detail::fvec4SIMD frexp(detail::fvec4SIMD const & x, detail::ivec4SIMD & exp);

	//! Builds a floating-point number from x and the
	//! corresponding integral exponent of two in exp, returning:
	//! significand * exp(2, exponent)
	//! If this product is too large to be represented in the
	//! floating-point type, the result is undefined.
	//! (From GLM_GTX_simd_vec4 extension, common function)
	//detail::fvec4SIMD ldexp(detail::fvec4SIMD const & x, detail::ivec4SIMD const & exp);

	//! Returns the length of x, i.e., sqrt(x * x).
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	float length(
		detail::fvec4SIMD const & x);

	//! Returns the length of x, i.e., sqrt(x * x).
	//! Less accurate but much faster than simdLength.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	float fastLength(
		detail::fvec4SIMD const & x);

	//! Returns the length of x, i.e., sqrt(x * x).
	//! Slightly more accurate but much slower than simdLength.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	float niceLength(
		detail::fvec4SIMD const & x);

	//! Returns the length of x, i.e., sqrt(x * x).
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD length4(
		detail::fvec4SIMD const & x);

	//! Returns the length of x, i.e., sqrt(x * x).
	//! Less accurate but much faster than simdLength4.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD fastLength4(
		detail::fvec4SIMD const & x);

	//! Returns the length of x, i.e., sqrt(x * x).
	//! Slightly more accurate but much slower than simdLength4.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD niceLength4(
		detail::fvec4SIMD const & x);

	//! Returns the distance betwwen p0 and p1, i.e., length(p0 - p1).
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	float distance(
		detail::fvec4SIMD const & p0,
		detail::fvec4SIMD const & p1);

	//! Returns the distance betwwen p0 and p1, i.e., length(p0 - p1).
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD distance4(
		detail::fvec4SIMD const & p0,
		detail::fvec4SIMD const & p1);

	//! Returns the dot product of x and y, i.e., result = x * y.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	float simdDot(
		detail::fvec4SIMD const & x,
		detail::fvec4SIMD const & y);

	//! Returns the dot product of x and y, i.e., result = x * y.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD dot4(
		detail::fvec4SIMD const & x,
		detail::fvec4SIMD const & y);

	//! Returns the cross product of x and y.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD cross(
		detail::fvec4SIMD const & x,
		detail::fvec4SIMD const & y);

	//! Returns a vector in the same direction as x but with length of 1.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD normalize(
		detail::fvec4SIMD const & x);

	//! Returns a vector in the same direction as x but with length of 1.
	//! Less accurate but much faster than simdNormalize.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD fastNormalize(
		detail::fvec4SIMD const & x);

	//! If dot(Nref, I) < 0.0, return N, otherwise, return -N.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD simdFaceforward(
		detail::fvec4SIMD const & N,
		detail::fvec4SIMD const & I,
		detail::fvec4SIMD const & Nref);

	//! For the incident vector I and surface orientation N,
	//! returns the reflection direction : result = I - 2.0 * dot(N, I) * N.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD reflect(
		detail::fvec4SIMD const & I,
		detail::fvec4SIMD const & N);

	//! For the incident vector I and surface normal N,
	//! and the ratio of indices of refraction eta,
	//! return the refraction vector.
	//! (From GLM_GTX_simd_vec4 extension, geometry functions)
	detail::fvec4SIMD refract(
		detail::fvec4SIMD const & I,
		detail::fvec4SIMD const & N,
		float const & eta);

	//! Returns the positive square root of x.
	//! (From GLM_GTX_simd_vec4 extension, exponential function)
	detail::fvec4SIMD sqrt(
		detail::fvec4SIMD const & x);

	//! Returns the positive square root of x with the nicest quality but very slow.
	//! Slightly more accurate but much slower than simdSqrt.
	//! (From GLM_GTX_simd_vec4 extension, exponential function)
	detail::fvec4SIMD niceSqrt(
		detail::fvec4SIMD const & x);

	//! Returns the positive square root of x
	//! Less accurate but much faster than sqrt.
	//! (From GLM_GTX_simd_vec4 extension, exponential function)
	detail::fvec4SIMD fastSqrt(
		detail::fvec4SIMD const & x);

	//! Returns the reciprocal of the positive square root of x.
	//! (From GLM_GTX_simd_vec4 extension, exponential function)
	detail::fvec4SIMD inversesqrt(
		detail::fvec4SIMD const & x);

	//! Returns the reciprocal of the positive square root of x.
	//! Faster than inversesqrt but less accurate.
	//! (From GLM_GTX_simd_vec4 extension, exponential function)
	detail::fvec4SIMD fastInversesqrt(
		detail::fvec4SIMD const & x);

	/// @}
}//namespace glm

#include "simd_vec4.inl"


#if (GLM_COMPILER & GLM_COMPILER_VC)
#   pragma warning(pop)
#endif


#endif//(GLM_ARCH != GLM_ARCH_PURE)

#endif//GLM_GTX_simd_vec4
