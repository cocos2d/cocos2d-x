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
/// @file glm/core/type_vec2.hpp
/// @date 2008-08-18 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_gentype2
#define glm_core_type_gentype2

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
	template <typename T> struct tvec3;
	template <typename T> struct tvec4;

	template <typename T>
	struct tvec2
	{
		enum ctor{null};

		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec2<T> type;
		typedef tvec2<bool> bool_type;

		GLM_FUNC_DECL GLM_CONSTEXPR size_type length() const;

		//////////////////////////////////////
		// Data

#	if(GLM_COMPONENT == GLM_COMPONENT_CXX11)
		union 
		{
			struct{value_type x, y;};
			struct{value_type r, g;};
			struct{value_type s, t;};

#		if(defined(GLM_SWIZZLE))
			_GLM_SWIZZLE2_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, x, y)
			_GLM_SWIZZLE2_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, r, g)
			_GLM_SWIZZLE2_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, s, t)
			_GLM_SWIZZLE2_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, x, y)
			_GLM_SWIZZLE2_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, r, g)
			_GLM_SWIZZLE2_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, s, t)
			_GLM_SWIZZLE2_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, x, y)
			_GLM_SWIZZLE2_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, r, g)
			_GLM_SWIZZLE2_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, s, t)
#		endif//(defined(GLM_SWIZZLE))
		};
#	elif(GLM_COMPONENT == GLM_COMPONENT_CXX98)
		union {value_type x, r, s;};
		union {value_type y, g, t;};

#		if(defined(GLM_SWIZZLE))
			// Defines all he swizzle operator as functions
			GLM_SWIZZLE_GEN_REF_FROM_VEC2(value_type, detail::tvec2, detail::tref2)
			GLM_SWIZZLE_GEN_VEC_FROM_VEC2(value_type, detail::tvec2, detail::tvec2, detail::tvec3, detail::tvec4)
#		endif//(defined(GLM_SWIZZLE))
#	else //(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
		value_type x, y;

#		if(defined(GLM_SWIZZLE))
			// Defines all he swizzle operator as functions
			GLM_SWIZZLE_GEN_REF2_FROM_VEC2_SWIZZLE(value_type, detail::tvec2, detail::tref2, x, y)
			GLM_SWIZZLE_GEN_VEC_FROM_VEC2_COMP(value_type, detail::tvec2, detail::tvec2, detail::tvec3, detail::tvec4, x, y)
#		endif//(defined(GLM_SWIZZLE))
#	endif//GLM_COMPONENT

		//////////////////////////////////////
		// Accesses

		GLM_FUNC_DECL value_type & operator[](size_type i);
		GLM_FUNC_DECL value_type const & operator[](size_type i) const;

		//////////////////////////////////////
		// Implicit basic constructors

		GLM_FUNC_DECL tvec2();
		GLM_FUNC_DECL tvec2(tvec2<T> const & v);

		//////////////////////////////////////
		// Explicit basic constructors

		GLM_FUNC_DECL explicit tvec2(
			ctor);
		GLM_FUNC_DECL explicit tvec2(
			value_type const & s);
		GLM_FUNC_DECL explicit tvec2(
			value_type const & s1, 
			value_type const & s2);

		//////////////////////////////////////
		// Swizzle constructors

		GLM_FUNC_DECL tvec2(tref2<T> const & r);

		template <int E0, int E1>
		GLM_FUNC_DECL tvec2(const glm::detail::swizzle<2,T,tvec2<T>,E0,E1,-1,-2>& that)
		{
			*this = that();
		}

		//////////////////////////////////////
		// Convertion constructors

		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U> 
		GLM_FUNC_DECL explicit tvec2(
			U const & x);
		//! Explicit converions (From section 5.4.1 Conversion and scalar constructors of GLSL 1.30.08 specification)
		template <typename U, typename V> 
		GLM_FUNC_DECL explicit tvec2(
			U const & x, 
			V const & y);

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

		GLM_FUNC_DECL tvec2<T> & operator= (tvec2<T> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator= (tvec2<U> const & v);

		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator+=(U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator+=(tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator-=(U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator-=(tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator*=(U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator*=(tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator/=(U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator/=(tvec2<U> const & v);
		GLM_FUNC_DECL tvec2<T> & operator++();
		GLM_FUNC_DECL tvec2<T> & operator--();

		//////////////////////////////////////
		// Unary bit operators

		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator%= (U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator%= (tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator&= (U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator&= (tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator|= (U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator|= (tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator^= (U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator^= (tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator<<=(U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator<<=(tvec2<U> const & v);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator>>=(U s);
		template <typename U> 
		GLM_FUNC_DECL tvec2<T> & operator>>=(tvec2<U> const & v);

		//////////////////////////////////////
		// Swizzle operators

		GLM_FUNC_DECL value_type swizzle(comp X) const;
		GLM_FUNC_DECL tvec2<T> swizzle(comp X, comp Y) const;
		GLM_FUNC_DECL tvec3<T> swizzle(comp X, comp Y, comp Z) const;
		GLM_FUNC_DECL tvec4<T> swizzle(comp X, comp Y, comp Z, comp W) const;
		GLM_FUNC_DECL tref2<T> swizzle(comp X, comp Y);
	};

	template <typename T>
	struct tref2
	{
		GLM_FUNC_DECL tref2(T & x, T & y);
		GLM_FUNC_DECL tref2(tref2<T> const & r);
		GLM_FUNC_DECL explicit tref2(tvec2<T> const & v);

		GLM_FUNC_DECL tref2<T> & operator= (tref2<T> const & r);
		GLM_FUNC_DECL tref2<T> & operator= (tvec2<T> const & v);

		GLM_FUNC_DECL tvec2<T> operator() ();

		T & x;
		T & y;
	};

	GLM_DETAIL_IS_VECTOR(tvec2);

} //namespace detail

	/// @addtogroup core_precision
	/// @{

	/// 2 components vector of high precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<highp_float>		highp_vec2;

	/// 2 components vector of medium precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<mediump_float>	mediump_vec2;

	/// 2 components vector of low precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<lowp_float>		lowp_vec2;

	/// 2 components vector of high precision signed integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<highp_int>		highp_ivec2;

	/// 2 components vector of medium precision signed integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<mediump_int>		mediump_ivec2;

	/// 2 components vector of low precision signed integer numbers.
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<lowp_int>			lowp_ivec2;
	
	/// 2 components vector of high precision unsigned integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<highp_uint>		highp_uvec2;

	/// 2 components vector of medium precision unsigned integer numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<mediump_uint>		mediump_uvec2;

	/// 2 components vector of low precision unsigned integer numbers.
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.5 Vectors</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tvec2<lowp_uint>		lowp_uvec2;

	/// @}
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_vec2.inl"
#endif//GLM_EXTERNAL_TEMPLATE

#endif//glm_core_type_gentype2
