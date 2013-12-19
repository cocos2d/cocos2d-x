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
/// @file glm/core/type_vec4.hpp
/// @date 2008-08-22 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype4
#define glm_core_type_gentype4

#include "type_vec.hpp"
#include "type_float.hpp"
#include "type_int.hpp"
#include "type_size.hpp"
#include "_swizzle.hpp"

namespace glm{
namespace detail
{
	template <typename T> struct tref2;
	template <typename T> struct tref3;
	template <typename T> struct tref4;
	template <typename T> struct tvec2;
	template <typename T> struct tvec3;

	template <typename T>
	struct tvec4
	{
		enum ctor{null};

		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec4<T> type;
		typedef tvec4<bool> bool_type;

		GLM_FUNC_DECL GLM_CONSTEXPR size_type length() const;

		//////////////////////////////////////
		// Data

#	if(GLM_COMPONENT == GLM_COMPONENT_CXX11)
		union 
		{
			struct{value_type x, y, z, w;};
			struct{value_type r, g, b, a;};
			struct{value_type s, t, p, q;};

#		if(defined(GLM_SWIZZLE))
			_GLM_SWIZZLE4_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, x, y, z, w)
			_GLM_SWIZZLE4_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, r, g, b, a)
			_GLM_SWIZZLE4_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, s, t, p, q)
			_GLM_SWIZZLE4_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, x, y, z, w)
			_GLM_SWIZZLE4_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, r, g, b, a)
			_GLM_SWIZZLE4_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, s, t, p, q)
			_GLM_SWIZZLE4_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, x, y, z, w)
			_GLM_SWIZZLE4_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, r, g, b, a)
			_GLM_SWIZZLE4_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, s, t, p, q)
#		endif//(defined(GLM_SWIZZLE))
		};
#	elif(GLM_COMPONENT == GLM_COMPONENT_CXX98)
		union {value_type x, r, s;};
		union {value_type y, g, t;};
		union {value_type z, b, p;};
		union {value_type w, a, q;};

#		if(defined(GLM_SWIZZLE))
			// Defines all he swizzle operator as functions
			GLM_SWIZZLE_GEN_REF_FROM_VEC4(T, detail::tvec4, detail::tref2, detail::tref3, detail::tref4)
			GLM_SWIZZLE_GEN_VEC_FROM_VEC4(T, detail::tvec4, detail::tvec2, detail::tvec3, detail::tvec4)
#		endif//(defined(GLM_SWIZZLE))
#	else //(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
		value_type x, y, z, w;

#		if(defined(GLM_SWIZZLE))
			// Defines all he swizzle operator as functions
			GLM_SWIZZLE_GEN_REF_FROM_VEC4_COMP(T, detail::tvec4, detail::tref2, detail::tref3, detail::tref4, x, y, z, w)
			GLM_SWIZZLE_GEN_VEC_FROM_VEC4_COMP(T, detail::tvec4, detail::tvec2, detail::tvec3, detail::tvec4, x, y, z, w)
#		endif//(defined(GLM_SWIZZLE))
#	endif//GLM_COMPONENT

		//////////////////////////////////////
		// Accesses

		GLM_FUNC_DECL value_type & operator[](size_type i);
		GLM_FUNC_DECL value_type const & operator[](size_type i) const;

		//////////////////////////////////////
		// Implicit basic constructors

		GLM_FUNC_DECL tvec4();
		GLM_FUNC_DECL tvec4(type const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		GLM_FUNC_DECL explicit tvec4(
			ctor);
		GLM_FUNC_DECL explicit tvec4(
			value_type const & s);
		GLM_FUNC_DECL explicit tvec4(
			value_type const & s0, 
			value_type const & s1, 
			value_type const & s2, 
			value_type const & s3);

		//////////////////////////////////////
		// Convertion scalar constructors

		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec4(
			U const & x);
		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C, typename D> 
		GLM_FUNC_DECL explicit tvec4(
			A const & x, 
			B const & y, 
			C const & z, 
			D const & w);			

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

		template <int E0, int E1, int E2, int E3>
		GLM_FUNC_DECL tvec4(glm::detail::swizzle<4, T, tvec4<T>, E0, E1, E2, E3> const & that)
		{
			*this = that();
		}

		template <int E0, int E1, int F0, int F1>
		GLM_FUNC_DECL tvec4(glm::detail::swizzle<2, T, tvec2<T>, E0, E1, -1, -2> const & v, glm::detail::swizzle<2, T, tvec2<T>, F0, F1, -1, -2> const & u)
		{
			*this = tvec4<T>(v(), u());
		}

		template <int E0, int E1>
		GLM_FUNC_DECL tvec4(T const & x, T const & y, glm::detail::swizzle<2, T, tvec2<T>, E0, E1, -1, -2> const & v)
		{
			*this = tvec4<T>(x, y, v());
		}

		template <int E0, int E1>
		GLM_FUNC_DECL tvec4(T const & x, glm::detail::swizzle<2, T, tvec2<T>, E0, E1, -1, -2> const & v, T const & w)
		{
			*this = tvec4<T>(x, v(), w);
		}

		template <int E0, int E1>
		GLM_FUNC_DECL tvec4(glm::detail::swizzle<2, T, tvec2<T>, E0, E1, -1, -2> const & v, T const & z, T const & w)
		{
			*this = tvec4<T>(v(), z, w);
		}

		template <int E0, int E1, int E2>
		GLM_FUNC_DECL tvec4(glm::detail::swizzle<3, T, tvec3<T>, E0, E1, E2, -1> const & v, T const & w)
		{
			*this = tvec4<T>(v(), w);
		}

		template <int E0, int E1, int E2>
		GLM_FUNC_DECL tvec4(T const & x, glm::detail::swizzle<3, T, tvec3<T>, E0, E1, E2, -1> const & v)
		{
			*this = tvec4<T>(x, v());
		}

		//////////////////////////////////////
		// Swizzle constructors

		GLM_FUNC_DECL tvec4(tref4<T> const & r);

		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C> 
		GLM_FUNC_DECL explicit tvec4(tref2<A> const & v, B const & s1, C const & s2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C> 
		GLM_FUNC_DECL explicit tvec4(A const & s1, tref2<B> const & v, C const & s2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B, typename C> 
		GLM_FUNC_DECL explicit tvec4(A const & s1, B const & s2, tref2<C> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(tref3<A> const & v, B const & s);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(A const & s, tref3<B> const & v);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(tref2<A> const & v1, tref2<B> const & v2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(tvec2<A> const & v1, tref2<B> const & v2);
		//! Explicit conversions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename A, typename B> 
		GLM_FUNC_DECL explicit tvec4(tref2<A> const & v1, tvec2<B> const & v2);

		//////////////////////////////////////
		// Unary arithmetic operators

		GLM_FUNC_DECL tvec4<T> & operator= (tvec4<T> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator= (tvec4<U> const & v);

		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator+=(U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator+=(tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator-=(U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator-=(tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator*=(U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator*=(tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator/=(U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator/=(tvec4<U> const & v);
		GLM_FUNC_DECL tvec4<T> & operator++();
		GLM_FUNC_DECL tvec4<T> & operator--();

		//////////////////////////////////////
		// Unary bit operators

		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator%= (U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator%= (tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator&= (U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator&= (tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator|= (U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator|= (tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator^= (U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator^= (tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator<<=(U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator<<=(tvec4<U> const & v);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator>>=(U s);
		template <typename U>
		GLM_FUNC_DECL tvec4<T> & operator>>=(tvec4<U> const & v);

		//////////////////////////////////////
		// Swizzle operators

		GLM_FUNC_DECL value_type swizzle(comp X) const;
		GLM_FUNC_DECL tvec2<T> swizzle(comp X, comp Y) const;
		GLM_FUNC_DECL tvec3<T> swizzle(comp X, comp Y, comp Z) const;
		GLM_FUNC_DECL tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
		GLM_FUNC_DECL tref2<T> swizzle(comp X, comp Y);
		GLM_FUNC_DECL tref3<T> swizzle(comp X, comp Y, comp Z);
		GLM_FUNC_DECL tref4<T> swizzle(comp X, comp Y, comp Z, comp W);
	};

	template <typename T>
	struct tref4
	{
		GLM_FUNC_DECL tref4(T & x, T & y, T & z, T & w);
		GLM_FUNC_DECL tref4(tref4<T> const & r);
		GLM_FUNC_DECL explicit tref4(tvec4<T> const & v);

		GLM_FUNC_DECL tref4<T> & operator= (tref4<T> const & r);
		GLM_FUNC_DECL tref4<T> & operator= (tvec4<T> const & v);

		GLM_FUNC_DECL tvec4<T> operator() ();

		T & x;
		T & y;
		T & z;
		T & w;
	};

	GLM_DETAIL_IS_VECTOR(tvec4);
}//namespace detail

	/// @addtogroup core_precision
	/// @{

	/// 4 components vector of high precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	///
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<highp_float>		highp_vec4;

	/// 4 components vector of medium precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<mediump_float>	mediump_vec4;

	/// 4 components vector of low precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<lowp_float>		lowp_vec4;

	/// 4 components vector of high precision signed integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<highp_int>		highp_ivec4;

	/// 4 components vector of medium precision signed integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<mediump_int>		mediump_ivec4;

	/// 4 components vector of low precision signed integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<lowp_int>			lowp_ivec4;

	/// 4 components vector of high precision unsigned integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<highp_uint>		highp_uvec4;

	/// 4 components vector of medium precision unsigned integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<mediump_uint>		mediump_uvec4;

	/// 4 components vector of low precision unsigned integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec4<lowp_uint>		lowp_uvec4;

	/// @}
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec4.inl"
#endif//GLM_EXTERNAL_TEMPLATE

#endif//glm_core_type_gentype4
