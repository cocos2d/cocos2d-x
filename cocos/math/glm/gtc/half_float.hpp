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
/// @ref gtc_half_float
/// @file glm/gtc/half_float.hpp
/// @date 2009-04-29 / 2012-11-06
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtc_half_float GLM_GTC_half_float
/// @ingroup gtc
/// 
/// Defines the half-precision floating-point type, along with various typedefs for vectors and matrices.
/// <glm/gtc/half_float.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTC_half_float
#define GLM_GTC_half_float GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_half_float extension included")
#endif

namespace glm{
namespace detail
{
#if(GLM_COMPONENT == GLM_COMPONENT_CXX98)
	template <>
	struct tvec2<half>
	{
		enum ctor{null};
		typedef half value_type;
		typedef std::size_t size_type;

		GLM_FUNC_DECL size_type length() const;
		static GLM_FUNC_DECL size_type value_size();

		typedef tvec2<half> type;
		typedef tvec2<bool> bool_type;

		//////////////////////////////////////
		// Data

		half x, y;

		//////////////////////////////////////
		// Accesses

		GLM_FUNC_DECL half & operator[](size_type i);
		GLM_FUNC_DECL half const & operator[](size_type i) const;

		//////////////////////////////////////
		// Implicit basic constructors

		GLM_FUNC_DECL tvec2();
		GLM_FUNC_DECL tvec2(tvec2<half> const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		GLM_FUNC_DECL explicit tvec2(ctor);
		GLM_FUNC_DECL explicit tvec2(
			half const & s);
		GLM_FUNC_DECL explicit tvec2(
			half const & s1, 
			half const & s2);

		//////////////////////////////////////
		// Swizzle constructors

		GLM_FUNC_DECL tvec2(tref2<half> const & r);

		//////////////////////////////////////
		// Convertion scalar constructors

		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec2(U const & x);
		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U, typename V> 
		GLM_FUNC_DECL explicit tvec2(U const & x, V const & y);			

		//////////////////////////////////////
		// Convertion vector constructors

		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec2(tvec2<U> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec2(tvec3<U> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec2(tvec4<U> const & v);

		//////////////////////////////////////
		// Unary arithmetic operators

		GLM_FUNC_DECL tvec2<half>& operator= (tvec2<half> const & v);

		GLM_FUNC_DECL tvec2<half>& operator+=(half const & s);
		GLM_FUNC_DECL tvec2<half>& operator+=(tvec2<half> const & v);
		GLM_FUNC_DECL tvec2<half>& operator-=(half const & s);
		GLM_FUNC_DECL tvec2<half>& operator-=(tvec2<half> const & v);
		GLM_FUNC_DECL tvec2<half>& operator*=(half const & s);
		GLM_FUNC_DECL tvec2<half>& operator*=(tvec2<half> const & v);
		GLM_FUNC_DECL tvec2<half>& operator/=(half const & s);
		GLM_FUNC_DECL tvec2<half>& operator/=(tvec2<half> const & v);
		GLM_FUNC_DECL tvec2<half>& operator++();
		GLM_FUNC_DECL tvec2<half>& operator--();

		//////////////////////////////////////
		// Swizzle operators

		GLM_FUNC_DECL half swizzle(comp X) const;
		GLM_FUNC_DECL tvec2<half> swizzle(comp X, comp Y) const;
		GLM_FUNC_DECL tvec3<half> swizzle(comp X, comp Y, comp Z) const;
		GLM_FUNC_DECL tvec4<half> swizzle(comp X, comp Y, comp Z, comp W) const;
		GLM_FUNC_DECL tref2<half> swizzle(comp X, comp Y);
	};

	template <>
	struct tvec3<half>
	{
		enum ctor{null};
		typedef half value_type;
		typedef std::size_t size_type;
		GLM_FUNC_DECL size_type length() const;
		static GLM_FUNC_DECL size_type value_size();

		typedef tvec3<half> type;
		typedef tvec3<bool> bool_type;

		//////////////////////////////////////
		// Data

		half x, y, z;

		//////////////////////////////////////
		// Accesses

		GLM_FUNC_DECL half & operator[](size_type i);
		GLM_FUNC_DECL half const & operator[](size_type i) const;

		//////////////////////////////////////
		// Implicit basic constructors

		GLM_FUNC_DECL tvec3();
		GLM_FUNC_DECL tvec3(tvec3<half> const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		GLM_FUNC_DECL explicit tvec3(ctor);
		GLM_FUNC_DECL explicit tvec3(
			half const & s);
		GLM_FUNC_DECL explicit tvec3(
			half const & s1, 
			half const & s2, 
			half const & s3);

		//////////////////////////////////////
		// Swizzle constructors

		GLM_FUNC_DECL tvec3(tref3<half> const & r);

		//////////////////////////////////////
		// Convertion scalar constructors

		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec3(U const & x);
		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U, typename V, typename W> 
		GLM_FUNC_DECL explicit tvec3(U const & x, V const & y, W const & z);			

		//////////////////////////////////////
		// Convertion vector constructors

		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec3(tvec2<A> const & v, B const & s);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec3(A const & s, tvec2<B> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec3(tvec3<U> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec3(tvec4<U> const & v);

		//////////////////////////////////////
		// Unary arithmetic operators

		GLM_FUNC_DECL tvec3<half>& operator= (tvec3<half> const & v);

		GLM_FUNC_DECL tvec3<half>& operator+=(half const & s);
		GLM_FUNC_DECL tvec3<half>& operator+=(tvec3<half> const & v);
		GLM_FUNC_DECL tvec3<half>& operator-=(half const & s);
		GLM_FUNC_DECL tvec3<half>& operator-=(tvec3<half> const & v);
		GLM_FUNC_DECL tvec3<half>& operator*=(half const & s);
		GLM_FUNC_DECL tvec3<half>& operator*=(tvec3<half> const & v);
		GLM_FUNC_DECL tvec3<half>& operator/=(half const & s);
		GLM_FUNC_DECL tvec3<half>& operator/=(tvec3<half> const & v);
		GLM_FUNC_DECL tvec3<half>& operator++();
		GLM_FUNC_DECL tvec3<half>& operator--();

		//////////////////////////////////////
		// Swizzle operators

		GLM_FUNC_DECL half swizzle(comp X) const;
		GLM_FUNC_DECL tvec2<half> swizzle(comp X, comp Y) const;
		GLM_FUNC_DECL tvec3<half> swizzle(comp X, comp Y, comp Z) const;
		GLM_FUNC_DECL tvec4<half> swizzle(comp X, comp Y, comp Z, comp W) const;
		GLM_FUNC_DECL tref3<half> swizzle(comp X, comp Y, comp Z);
	};

	template <>
	struct tvec4<half>
	{
		enum ctor{null};
		typedef half value_type;
		typedef std::size_t size_type;
		GLM_FUNC_DECL size_type length() const;
		static GLM_FUNC_DECL size_type value_size();

		typedef tvec4<half> type;
		typedef tvec4<bool> bool_type;

		//////////////////////////////////////
		// Data

		half x, y, z, w;

		//////////////////////////////////////
		// Accesses

		GLM_FUNC_DECL half & operator[](size_type i);
		GLM_FUNC_DECL half const & operator[](size_type i) const;

		//////////////////////////////////////
		// Implicit basic constructors

		GLM_FUNC_DECL tvec4();
		GLM_FUNC_DECL tvec4(tvec4<half> const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		GLM_FUNC_DECL explicit tvec4(ctor);
		GLM_FUNC_DECL explicit tvec4(
			half const & s);
		GLM_FUNC_DECL explicit tvec4(
			half const & s0, 
			half const & s1, 
			half const & s2, 
			half const & s3);

		//////////////////////////////////////
		// Swizzle constructors

		GLM_FUNC_DECL tvec4(tref4<half> const & r);

		//////////////////////////////////////
		// Convertion scalar constructors

		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec4(U const & x);
		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C, typename D> 
		GLM_FUNC_DECL explicit tvec4(A const & x, B const & y, C const & z, D const & w);			

		//////////////////////////////////////
		// Convertion vector constructors

		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C> 
		GLM_FUNC_DECL explicit tvec4(tvec2<A> const & v, B const & s1, C const & s2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C> 
		GLM_FUNC_DECL explicit tvec4(A const & s1, tvec2<B> const & v, C const & s2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C> 
		GLM_FUNC_DECL explicit tvec4(A const & s1, B const & s2, tvec2<C> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(tvec3<A> const & v, B const & s);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(A const & s, tvec3<B> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(tvec2<A> const & v1, tvec2<B> const & v2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec4(tvec4<U> const & v);

		//////////////////////////////////////
		// Unary arithmetic operators

		GLM_FUNC_DECL tvec4<half>& operator= (tvec4<half> const & v);

		GLM_FUNC_DECL tvec4<half>& operator+=(half const & s);
		GLM_FUNC_DECL tvec4<half>& operator+=(tvec4<half> const & v);
		GLM_FUNC_DECL tvec4<half>& operator-=(half const & s);
		GLM_FUNC_DECL tvec4<half>& operator-=(tvec4<half> const & v);
		GLM_FUNC_DECL tvec4<half>& operator*=(half const & s);
		GLM_FUNC_DECL tvec4<half>& operator*=(tvec4<half> const & v);
		GLM_FUNC_DECL tvec4<half>& operator/=(half const & s);
		GLM_FUNC_DECL tvec4<half>& operator/=(tvec4<half> const & v);
		GLM_FUNC_DECL tvec4<half>& operator++();
		GLM_FUNC_DECL tvec4<half>& operator--();

		//////////////////////////////////////
		// Swizzle operators

		GLM_FUNC_DECL half swizzle(comp X) const;
		GLM_FUNC_DECL tvec2<half> swizzle(comp X, comp Y) const;
		GLM_FUNC_DECL tvec3<half> swizzle(comp X, comp Y, comp Z) const;
		GLM_FUNC_DECL tvec4<half> swizzle(comp X, comp Y, comp Z, comp W) const;
		GLM_FUNC_DECL tref4<half> swizzle(comp X, comp Y, comp Z, comp W);
	};
#endif//(GLM_COMPONENT == GLM_COMPONENT_CXX98)
}
//namespace detail

	/// @addtogroup gtc_half_float
	/// @{

	/// Type for half-precision floating-point numbers. 
	/// @see gtc_half_float
	typedef detail::half					half;

	/// Vector of 2 half-precision floating-point numbers. 
	/// @see gtc_half_float
	typedef detail::tvec2<detail::half>	hvec2;

	/// Vector of 3 half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tvec3<detail::half>	hvec3;

	/// Vector of 4 half-precision floating-point numbers. 
	/// @see gtc_half_float
	typedef detail::tvec4<detail::half>	hvec4;

	/// 2 * 2 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat2x2<detail::half>	hmat2;

	/// 3 * 3 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat3x3<detail::half>	hmat3;

	/// 4 * 4 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat4x4<detail::half>	hmat4;

	/// 2 * 2 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat2x2<detail::half>	hmat2x2;

	/// 2 * 3 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat2x3<detail::half>	hmat2x3;

	/// 2 * 4 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat2x4<detail::half>	hmat2x4;

	/// 3 * 2 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat3x2<detail::half>	hmat3x2;

	/// 3 * 3 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat3x3<detail::half>	hmat3x3;

	/// 3 * 4 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat3x4<detail::half>	hmat3x4;

	/// 4 * 2 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat4x2<detail::half>	hmat4x2;    

	/// 4 * 3 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat4x3<detail::half>	hmat4x3;

	/// 4 * 4 matrix of half-precision floating-point numbers.
	/// @see gtc_half_float
	typedef detail::tmat4x4<detail::half>	hmat4x4;

	/// Returns the absolute value of a half-precision floating-point value
	/// @see gtc_half_float
	GLM_FUNC_DECL half abs(half const & x);

	/// Returns the absolute value of a half-precision floating-point two dimensional vector
	/// @see gtc_half_float
	GLM_FUNC_DECL hvec2 abs(hvec2 const & x);

	/// Returns the absolute value of a half-precision floating-point three dimensional vector
	/// @see gtc_half_float
	GLM_FUNC_DECL hvec3 abs(hvec3 const & x);

	/// Returns the absolute value of a half-precision floating-point four dimensional vector
	/// @see gtc_half_float
	GLM_FUNC_DECL hvec4 abs(hvec4 const & x);

	/// Selects which vector each returned component comes
	/// from. For a component of <a> that is false, the
	/// corresponding component of x is returned. For a
	/// component of a that is true, the corresponding
	/// component of y is returned. Components of x and y that
	/// are not selected are allowed to be invalid floating point
	/// values and will have no effect on the results. Thus, this
	/// provides different functionality than
	/// genType mix(genType x, genType y, genType(a))
	/// where a is a Boolean vector.
	///
	/// @see gtc_half_float
	GLM_FUNC_DECL half mix(half const & x, half const & y, bool const & a);

	/// @}
}// namespace glm

#include "half_float.inl"

#endif//GLM_GTC_half_float
