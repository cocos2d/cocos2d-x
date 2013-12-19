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
/// @file glm/core/type_mat2x3.hpp
/// @date 2006-10-01 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_mat2x3
#define glm_core_type_mat2x3

#include "type_mat.hpp"

namespace glm{
namespace detail
{
	template <typename T> struct tvec1;
	template <typename T> struct tvec2;
	template <typename T> struct tvec3;
	template <typename T> struct tvec4;
	template <typename T> struct tmat2x2;
	template <typename T> struct tmat2x3;
	template <typename T> struct tmat2x4;
	template <typename T> struct tmat3x2;
	template <typename T> struct tmat3x3;
	template <typename T> struct tmat3x4;
	template <typename T> struct tmat4x2;
	template <typename T> struct tmat4x3;
	template <typename T> struct tmat4x4;

	template <typename T> 
	struct tmat2x3
	{
		enum ctor{null};
		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec3<T> col_type;
		typedef tvec2<T> row_type;
		typedef tmat2x3<T> type;
		typedef tmat3x2<T> transpose_type;

		static GLM_FUNC_DECL size_type col_size();
		static GLM_FUNC_DECL size_type row_size();

		GLM_FUNC_DECL GLM_CONSTEXPR size_type length() const;

	private:
		// Data 
		col_type value[2];

	public:
		// Constructors
		GLM_FUNC_DECL tmat2x3();
		GLM_FUNC_DECL tmat2x3(tmat2x3 const & m);

		GLM_FUNC_DECL explicit tmat2x3(
			ctor);
		GLM_FUNC_DECL explicit tmat2x3(
			value_type const & s);
		GLM_FUNC_DECL explicit tmat2x3(
			value_type const & x0, value_type const & y0, value_type const & z0,
			value_type const & x1, value_type const & y1, value_type const & z1);
		GLM_FUNC_DECL explicit tmat2x3(
			col_type const & v0, 
			col_type const & v1);

		//////////////////////////////////////
		// Conversions
		template <typename U> 
		GLM_FUNC_DECL explicit tmat2x3(
			U const & x);
			
		template <typename X1, typename Y1, typename Z1, typename X2, typename Y2, typename Z2> 
		GLM_FUNC_DECL explicit tmat2x3(
			X1 const & x1, Y1 const & y1, Z1 const & z1, 
			X2 const & x2, Y2 const & y2, Z2 const & z2);
			
		template <typename U, typename V> 
		GLM_FUNC_DECL explicit tmat2x3(
			tvec3<U> const & v1, 
			tvec3<V> const & v2);

		//////////////////////////////////////
		// Matrix conversion
		template <typename U> 
		GLM_FUNC_DECL explicit tmat2x3(tmat2x3<U> const & m);

		GLM_FUNC_DECL explicit tmat2x3(tmat2x2<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat3x3<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat4x4<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat2x4<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat3x2<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat3x4<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat4x2<T> const & x);
		GLM_FUNC_DECL explicit tmat2x3(tmat4x3<T> const & x);

		// Accesses
		GLM_FUNC_DECL col_type & operator[](size_type i);
		GLM_FUNC_DECL col_type const & operator[](size_type i) const;

		// Unary updatable operators
		GLM_FUNC_DECL tmat2x3<T> & operator=  (tmat2x3<T> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator=  (tmat2x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator+= (U s);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator+= (tmat2x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator-= (U s);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator-= (tmat2x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator*= (U s);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator*= (tmat2x3<U> const & m);
		template <typename U> 
		GLM_FUNC_DECL tmat2x3<T> & operator/= (U s);

		GLM_FUNC_DECL tmat2x3<T> & operator++ ();
		GLM_FUNC_DECL tmat2x3<T> & operator-- ();
	};

	// Binary operators
	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator+ (
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator+ (
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator- (
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator- (
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator* (
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator* (
		typename tmat2x3<T>::value_type const & s, 
		tmat2x3<T> const & m);

	template <typename T>
	GLM_FUNC_DECL typename tmat2x3<T>::col_type operator* (
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::row_type const & v);

	template <typename T> 
	GLM_FUNC_DECL typename tmat2x3<T>::row_type operator* (
		typename tmat2x3<T>::col_type const & v, 
		tmat2x3<T> const & m);

	template <typename T>
	GLM_FUNC_DECL tmat2x3<T> operator* (
		tmat2x3<T> const & m1, 
		tmat2x2<T> const & m2);

	template <typename T>
	GLM_FUNC_DECL tmat3x3<T> operator* (
		tmat2x3<T> const & m1, 
		tmat3x2<T> const & m2);
		
	template <typename T>
	GLM_FUNC_DECL tmat4x3<T> operator* (
		tmat2x3<T> const & m1, 
		tmat4x2<T> const & m2);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator/ (
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> operator/ (
		typename tmat2x3<T>::value_type const & s,
		tmat2x3<T> const & m);

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> const operator-  (
		tmat2x3<T> const & m);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> const operator-- (
		tmat2x3<T> const & m, 
		int);

	template <typename T> 
	GLM_FUNC_DECL tmat2x3<T> const operator++ (
		tmat2x3<T> const & m, 
		int);

} //namespace detail

	/// @addtogroup core_precision
	/// @{

	/// 2 columns of 3 components matrix of low precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tmat2x3<lowp_float>		lowp_mat2x3;
    
	/// 2 columns of 3 components matrix of medium precision floating-point numbers. 
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tmat2x3<mediump_float>	mediump_mat2x3;
    
	/// 2 columns of 3 components matrix of high precision floating-point numbers.
	/// There is no guarantee on the actual precision.
	/// 
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</a>
	/// @see <a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</a>
	typedef detail::tmat2x3<highp_float>	highp_mat2x3;

	/// @}
}//namespace glm

#ifndef GLM_EXTERNAL_TEMPLATE
#include "type_mat2x3.inl"
#endif

#endif //glm_core_type_mat2x3
