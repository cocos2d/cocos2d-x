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
/// @file glm/core/type_mat4x4.inl
/// @date 2005-01-27 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tmat4x4<T>::size_type tmat4x4<T>::length() const
	{
		return 4;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::size_type tmat4x4<T>::col_size()
	{
		return 4;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::size_type tmat4x4<T>::row_size()
	{
		return 4;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::col_type & 
	tmat4x4<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::col_type const & 
	tmat4x4<T>::operator[]
	(
		size_type i
	) const
	{
		assert(i < this->length());
		return this->value[i];
	}

	//////////////////////////////////////////////////////////////
	// Constructors

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4()
	{
		value_type Zero(0);
		value_type One(1);
		this->value[0] = col_type(One, Zero, Zero, Zero);
		this->value[1] = col_type(Zero, One, Zero, Zero);
		this->value[2] = col_type(Zero, Zero, One, Zero);
		this->value[3] = col_type(Zero, Zero, Zero, One);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat4x4<T> const & m
	)
	{
		this->value[0] = m.value[0];
		this->value[1] = m.value[1];
		this->value[2] = m.value[2];
		this->value[3] = m.value[3];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		ctor
	)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		value_type const & s
	)
	{
		value_type const Zero(0);
		this->value[0] = col_type(s, Zero, Zero, Zero);
		this->value[1] = col_type(Zero, s, Zero, Zero);
		this->value[2] = col_type(Zero, Zero, s, Zero);
		this->value[3] = col_type(Zero, Zero, Zero, s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
		value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1,
		value_type const & x2, value_type const & y2, value_type const & z2, value_type const & w2,
		value_type const & x3, value_type const & y3, value_type const & z3, value_type const & w3
	)
	{
		this->value[0] = col_type(x0, y0, z0, w0);
		this->value[1] = col_type(x1, y1, z1, w1);
		this->value[2] = col_type(x2, y2, z2, w2);
		this->value[3] = col_type(x3, y3, z3, w3);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		col_type const & v0, 
		col_type const & v1, 
		col_type const & v2,
		col_type const & v3
	)
	{
		this->value[0] = v0;
		this->value[1] = v1;
		this->value[2] = v2;
		this->value[3] = v3;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat4x4<U> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
		this->value[2] = col_type(m[2]);
		this->value[3] = col_type(m[3]);
	}

	//////////////////////////////////////
	// Convertion constructors
	template <typename T> 
	template <typename U> 
	GLM_FUNC_DECL tmat4x4<T>::tmat4x4
	(
		U const & s
	)
	{
		GLM_STATIC_ASSERT(detail::type<U>::is_float || std::numeric_limits<U>::is_integer, "*mat4x4 constructor only takes float and integer types");

		value_type const Zero(0);
		this->value[0] = tvec4<T>(value_type(s), Zero, Zero, Zero);
		this->value[1] = tvec4<T>(Zero, value_type(s), Zero, Zero);
		this->value[2] = tvec4<T>(Zero, Zero, value_type(s), Zero);
		this->value[3] = tvec4<T>(Zero, Zero, Zero, value_type(s));
	}
	
	template <typename T> 
	template <
		typename X1, typename Y1, typename Z1, typename W1, 
		typename X2, typename Y2, typename Z2, typename W2, 
		typename X3, typename Y3, typename Z3, typename W3, 
		typename X4, typename Y4, typename Z4, typename W4>  
	GLM_FUNC_DECL tmat4x4<T>::tmat4x4
	(
		X1 const & x1, Y1 const & y1, Z1 const & z1, W1 const & w1, 
		X2 const & x2, Y2 const & y2, Z2 const & z2, W2 const & w2, 
		X3 const & x3, Y3 const & y3, Z3 const & z3, W3 const & w3, 
		X4 const & x4, Y4 const & y4, Z4 const & z4, W4 const & w4
	)
	{
		GLM_STATIC_ASSERT(detail::type<X1>::is_float || std::numeric_limits<X1>::is_integer, "*mat4x4 constructor only takes float and integer types, 1st parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Y1>::is_float || std::numeric_limits<Y1>::is_integer, "*mat4x4 constructor only takes float and integer types, 2nd parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Z1>::is_float || std::numeric_limits<Z1>::is_integer, "*mat4x4 constructor only takes float and integer types, 3rd parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<W1>::is_float || std::numeric_limits<W1>::is_integer, "*mat4x4 constructor only takes float and integer types, 4th parameter type invalid.");

		GLM_STATIC_ASSERT(detail::type<X2>::is_float || std::numeric_limits<X2>::is_integer, "*mat4x4 constructor only takes float and integer types, 5th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Y2>::is_float || std::numeric_limits<Y2>::is_integer, "*mat4x4 constructor only takes float and integer types, 6th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Z2>::is_float || std::numeric_limits<Z2>::is_integer, "*mat4x4 constructor only takes float and integer types, 7th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<W2>::is_float || std::numeric_limits<W2>::is_integer, "*mat4x4 constructor only takes float and integer types, 8th parameter type invalid.");

		GLM_STATIC_ASSERT(detail::type<X3>::is_float || std::numeric_limits<X3>::is_integer, "*mat4x4 constructor only takes float and integer types, 9th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Y3>::is_float || std::numeric_limits<Y3>::is_integer, "*mat4x4 constructor only takes float and integer types, 10th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Z3>::is_float || std::numeric_limits<Z3>::is_integer, "*mat4x4 constructor only takes float and integer types, 11th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<W3>::is_float || std::numeric_limits<W3>::is_integer, "*mat4x4 constructor only takes float and integer types, 12th parameter type invalid.");

		GLM_STATIC_ASSERT(detail::type<X4>::is_float || std::numeric_limits<X4>::is_integer, "*mat4x4 constructor only takes float and integer types, 13th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Y4>::is_float || std::numeric_limits<Y4>::is_integer, "*mat4x4 constructor only takes float and integer types, 14th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<Z4>::is_float || std::numeric_limits<Z4>::is_integer, "*mat4x4 constructor only takes float and integer types, 15th parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<W4>::is_float || std::numeric_limits<W4>::is_integer, "*mat4x4 constructor only takes float and integer types, 16th parameter type invalid.");

		this->value[0] = col_type(value_type(x1), value_type(y1), value_type(z1), value_type(w1));
		this->value[1] = col_type(value_type(x2), value_type(y2), value_type(z2), value_type(w2));
		this->value[2] = col_type(value_type(x3), value_type(y3), value_type(z3), value_type(w3));
		this->value[3] = col_type(value_type(x4), value_type(y4), value_type(z4), value_type(w4));
	}
	
	template <typename T> 
	template <typename V1, typename V2, typename V3, typename V4> 
	GLM_FUNC_DECL tmat4x4<T>::tmat4x4
	(
		tvec4<V1> const & v1, 
		tvec4<V2> const & v2, 
		tvec4<V3> const & v3,
		tvec4<V4> const & v4
	)		
	{
		GLM_STATIC_ASSERT(detail::type<V1>::is_float || std::numeric_limits<V1>::is_integer, "*mat4x4 constructor only takes float and integer types, 1st parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<V2>::is_float || std::numeric_limits<V2>::is_integer, "*mat4x4 constructor only takes float and integer types, 2nd parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<V3>::is_float || std::numeric_limits<V3>::is_integer, "*mat4x4 constructor only takes float and integer types, 3rd parameter type invalid.");
		GLM_STATIC_ASSERT(detail::type<V4>::is_float || std::numeric_limits<V4>::is_integer, "*mat4x4 constructor only takes float and integer types, 4th parameter type invalid.");

		this->value[0] = col_type(v1);
		this->value[1] = col_type(v2);
		this->value[2] = col_type(v3);
		this->value[3] = col_type(v4);
	}

	//////////////////////////////////////
	// Matrix convertion constructors
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat2x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], detail::tvec2<T>(0));
		this->value[1] = col_type(m[1], detail::tvec2<T>(0));
		this->value[2] = col_type(value_type(0));
		this->value[3] = col_type(value_type(0), value_type(0), value_type(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat3x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0], value_type(0));
		this->value[1] = col_type(m[1], value_type(0));
		this->value[2] = col_type(m[2], value_type(0));
		this->value[3] = col_type(value_type(0), value_type(0), value_type(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat2x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0], value_type(0));
		this->value[1] = col_type(m[1], value_type(0));
		this->value[2] = col_type(value_type(0));
		this->value[3] = col_type(value_type(0), value_type(0), value_type(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat3x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], detail::tvec2<T>(0));
		this->value[1] = col_type(m[1], detail::tvec2<T>(0));
		this->value[2] = col_type(m[2], detail::tvec2<T>(0));
		this->value[3] = col_type(value_type(0), value_type(0), value_type(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat2x4<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = col_type(T(0));
		this->value[3] = col_type(T(0), T(0), T(0), T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat4x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], detail::tvec2<T>(0));
		this->value[1] = col_type(m[1], detail::tvec2<T>(0));
		this->value[2] = col_type(T(0));
		this->value[3] = col_type(T(0), T(0), T(0), T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat3x4<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = col_type(T(0), T(0), T(0), T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>::tmat4x4
	(
		tmat4x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0], T(0));
		this->value[1] = col_type(m[1], T(0));
		this->value[2] = col_type(m[2], T(0));
		this->value[3] = col_type(m[3], T(1));
	}

	//////////////////////////////////////////////////////////////
	// Operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T>& tmat4x4<T>::operator= 
	(
		tmat4x4<T> const & m
	)
	{
		//memcpy could be faster
		//memcpy(&this->value, &m.value, 16 * sizeof(valType));
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat4x4<T>& tmat4x4<T>::operator= 
	(
		tmat4x4<U> const & m
	)
	{
		//memcpy could be faster
		//memcpy(&this->value, &m.value, 16 * sizeof(valType));
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat4x4<T>& tmat4x4<T>::operator+= (U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		this->value[3] += s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat4x4<T>& tmat4x4<T>::operator+= 
	(
		tmat4x4<U> const & m
	)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		this->value[3] += m[3];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator-= (U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		this->value[3] -= s;
		return *this;
	}

	template <typename T> 
	template <typename U>
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator-= 
	(
		tmat4x4<U> const & m
	)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		this->value[3] -= m[3];
		return *this;
	}

	template <typename T> 
	template <typename U>
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator*= (U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		this->value[3] *= s;
		return *this;
	}

	template <typename T> 
	template <typename U>
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator*= 
	(
		tmat4x4<U> const & m
	)
	{
		return (*this = *this * m);
	}

	template <typename T> 
	template <typename U>
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator/= (U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		this->value[3] /= s;
		return *this;
	}

	template <typename T> 
	template <typename U>
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator/= 
	(
		tmat4x4<U> const & m
	)
	{
		return (*this = *this / m);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator++ ()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		++this->value[3];
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> & tmat4x4<T>::operator-- ()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		--this->value[3];
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> tmat4x4<T>::_inverse() const
	{
		// Calculate all mat2 determinants
		value_type SubFactor00 = this->value[2][2] * this->value[3][3] - this->value[3][2] * this->value[2][3];
		value_type SubFactor01 = this->value[2][1] * this->value[3][3] - this->value[3][1] * this->value[2][3];
		value_type SubFactor02 = this->value[2][1] * this->value[3][2] - this->value[3][1] * this->value[2][2];
		value_type SubFactor03 = this->value[2][0] * this->value[3][3] - this->value[3][0] * this->value[2][3];
		value_type SubFactor04 = this->value[2][0] * this->value[3][2] - this->value[3][0] * this->value[2][2];
		value_type SubFactor05 = this->value[2][0] * this->value[3][1] - this->value[3][0] * this->value[2][1];
		value_type SubFactor06 = this->value[1][2] * this->value[3][3] - this->value[3][2] * this->value[1][3];
		value_type SubFactor07 = this->value[1][1] * this->value[3][3] - this->value[3][1] * this->value[1][3];
		value_type SubFactor08 = this->value[1][1] * this->value[3][2] - this->value[3][1] * this->value[1][2];
		value_type SubFactor09 = this->value[1][0] * this->value[3][3] - this->value[3][0] * this->value[1][3];
		value_type SubFactor10 = this->value[1][0] * this->value[3][2] - this->value[3][0] * this->value[1][2];
		value_type SubFactor11 = this->value[1][1] * this->value[3][3] - this->value[3][1] * this->value[1][3];
		value_type SubFactor12 = this->value[1][0] * this->value[3][1] - this->value[3][0] * this->value[1][1];
		value_type SubFactor13 = this->value[1][2] * this->value[2][3] - this->value[2][2] * this->value[1][3];
		value_type SubFactor14 = this->value[1][1] * this->value[2][3] - this->value[2][1] * this->value[1][3];
		value_type SubFactor15 = this->value[1][1] * this->value[2][2] - this->value[2][1] * this->value[1][2];
		value_type SubFactor16 = this->value[1][0] * this->value[2][3] - this->value[2][0] * this->value[1][3];
		value_type SubFactor17 = this->value[1][0] * this->value[2][2] - this->value[2][0] * this->value[1][2];
		value_type SubFactor18 = this->value[1][0] * this->value[2][1] - this->value[2][0] * this->value[1][1];
/*
		tmat4x4<T> Inverse(
			+ (this->value[1][1] * SubFactor00 - this->value[1][2] * SubFactor01 + this->value[1][3] * SubFactor02),
			- (this->value[1][0] * SubFactor00 - this->value[1][2] * SubFactor03 + this->value[1][3] * SubFactor04),
			+ (this->value[1][0] * SubFactor01 - this->value[1][1] * SubFactor03 + this->value[1][3] * SubFactor05),
			- (this->value[1][0] * SubFactor02 - this->value[1][1] * SubFactor04 + this->value[1][2] * SubFactor05),

			- (this->value[0][1] * SubFactor00 - this->value[0][2] * SubFactor01 + this->value[0][3] * SubFactor02),
			+ (this->value[0][0] * SubFactor00 - this->value[0][2] * SubFactor03 + this->value[0][3] * SubFactor04),
			- (this->value[0][0] * SubFactor01 - this->value[0][1] * SubFactor03 + this->value[0][3] * SubFactor05),
			+ (this->value[0][0] * SubFactor02 - this->value[0][1] * SubFactor04 + this->value[0][2] * SubFactor05),

			+ (this->value[0][1] * SubFactor06 - this->value[0][2] * SubFactor07 + this->value[0][3] * SubFactor08),
			- (this->value[0][0] * SubFactor06 - this->value[0][2] * SubFactor09 + this->value[0][3] * SubFactor10),
			+ (this->value[0][0] * SubFactor11 - this->value[0][1] * SubFactor09 + this->value[0][3] * SubFactor12),
			- (this->value[0][0] * SubFactor08 - this->value[0][1] * SubFactor10 + this->value[0][2] * SubFactor12),

			- (this->value[0][1] * SubFactor13 - this->value[0][2] * SubFactor14 + this->value[0][3] * SubFactor15),
			+ (this->value[0][0] * SubFactor13 - this->value[0][2] * SubFactor16 + this->value[0][3] * SubFactor17),
			- (this->value[0][0] * SubFactor14 - this->value[0][1] * SubFactor16 + this->value[0][3] * SubFactor18),
			+ (this->value[0][0] * SubFactor15 - this->value[0][1] * SubFactor17 + this->value[0][2] * SubFactor18));
*/
		tmat4x4<T> Inverse(
			+ this->value[1][1] * SubFactor00 - this->value[1][2] * SubFactor01 + this->value[1][3] * SubFactor02,
			- this->value[1][0] * SubFactor00 + this->value[1][2] * SubFactor03 - this->value[1][3] * SubFactor04,
			+ this->value[1][0] * SubFactor01 - this->value[1][1] * SubFactor03 + this->value[1][3] * SubFactor05,
			- this->value[1][0] * SubFactor02 + this->value[1][1] * SubFactor04 - this->value[1][2] * SubFactor05,

			- this->value[0][1] * SubFactor00 + this->value[0][2] * SubFactor01 - this->value[0][3] * SubFactor02,
			+ this->value[0][0] * SubFactor00 - this->value[0][2] * SubFactor03 + this->value[0][3] * SubFactor04,
			- this->value[0][0] * SubFactor01 + this->value[0][1] * SubFactor03 - this->value[0][3] * SubFactor05,
			+ this->value[0][0] * SubFactor02 - this->value[0][1] * SubFactor04 + this->value[0][2] * SubFactor05,

			+ this->value[0][1] * SubFactor06 - this->value[0][2] * SubFactor07 + this->value[0][3] * SubFactor08,
			- this->value[0][0] * SubFactor06 + this->value[0][2] * SubFactor09 - this->value[0][3] * SubFactor10,
			+ this->value[0][0] * SubFactor11 - this->value[0][1] * SubFactor09 + this->value[0][3] * SubFactor12,
			- this->value[0][0] * SubFactor08 + this->value[0][1] * SubFactor10 - this->value[0][2] * SubFactor12,

			- this->value[0][1] * SubFactor13 + this->value[0][2] * SubFactor14 - this->value[0][3] * SubFactor15,
			+ this->value[0][0] * SubFactor13 - this->value[0][2] * SubFactor16 + this->value[0][3] * SubFactor17,
			- this->value[0][0] * SubFactor14 + this->value[0][1] * SubFactor16 - this->value[0][3] * SubFactor18,
			+ this->value[0][0] * SubFactor15 - this->value[0][1] * SubFactor17 + this->value[0][2] * SubFactor18);

		value_type Determinant = 
			+ this->value[0][0] * Inverse[0][0] 
			+ this->value[0][1] * Inverse[1][0] 
			+ this->value[0][2] * Inverse[2][0] 
			+ this->value[0][3] * Inverse[3][0];

		Inverse /= Determinant;
		return Inverse;
	}

	// Binary operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator+ 
	(
		tmat4x4<T> const & m, 
		typename tmat4x4<T>::value_type const & s
	)
	{
		return tmat4x4<T>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator+ 
	(
		typename tmat4x4<T>::value_type const & s, 
		tmat4x4<T> const & m
	)
	{
		return tmat4x4<T>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator+ 
	(
		tmat4x4<T> const & m1, 
		tmat4x4<T> const & m2
	)
	{
		return tmat4x4<T>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]);
	}
    
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator- 
	(
		tmat4x4<T> const & m, 
		typename tmat4x4<T>::value_type const & s
	)
	{
		return tmat4x4<T>(
			m[0] - s,
			m[1] - s,
			m[2] - s,
			m[3] - s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator- 
	(
		typename tmat4x4<T>::value_type const & s, 
		tmat4x4<T> const & m
	)
	{
		return tmat4x4<T>(
			s - m[0],
			s - m[1],
			s - m[2],
			s - m[3]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator- 
	(
		tmat4x4<T> const & m1, 
		tmat4x4<T> const & m2
	)
	{
		return tmat4x4<T>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator* 
	(
		tmat4x4<T> const & m, 
		typename tmat4x4<T>::value_type const  & s
	)
	{
		return tmat4x4<T>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator* 
	(
		typename tmat4x4<T>::value_type const & s, 
		tmat4x4<T> const & m
	)
	{
		return tmat4x4<T>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::col_type operator* 
	(
		tmat4x4<T> const & m, 
		typename tmat4x4<T>::row_type const & v
	)
	{
		return typename tmat4x4<T>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::row_type operator* 
	(
		typename tmat4x4<T>::col_type const & v, 
		tmat4x4<T> const & m
	)
	{
		return typename tmat4x4<T>::row_type(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x4<T> operator* 
	(
		tmat4x4<T> const & m1, 
		tmat2x4<T> const & m2
	)
	{
		return tmat2x4<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat3x4<T> operator* 
	(
		tmat4x4<T> const & m1, 
		tmat3x4<T> const & m2
	)
	{
		return tmat3x4<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
			m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
			m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
			m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator* 
	(
		tmat4x4<T> const & m1, 
		tmat4x4<T> const & m2
	)
	{
		typename tmat4x4<T>::col_type const SrcA0 = m1[0];
		typename tmat4x4<T>::col_type const SrcA1 = m1[1];
		typename tmat4x4<T>::col_type const SrcA2 = m1[2];
		typename tmat4x4<T>::col_type const SrcA3 = m1[3];

		typename tmat4x4<T>::col_type const SrcB0 = m2[0];
		typename tmat4x4<T>::col_type const SrcB1 = m2[1];
		typename tmat4x4<T>::col_type const SrcB2 = m2[2];
		typename tmat4x4<T>::col_type const SrcB3 = m2[3];

		tmat4x4<T> Result(tmat4x4<T>::null);
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator/ 
	(
		tmat4x4<T> const & m, 
		typename tmat4x4<T>::value_type const & s
	)
	{
		return tmat4x4<T>(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator/ 
	(
		typename tmat4x4<T>::value_type const & s, 
		tmat4x4<T> const & m
	)
	{
		return tmat4x4<T>(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::col_type operator/ 
	(
		tmat4x4<T> const & m, 
		typename tmat4x4<T>::row_type const & v
	)
	{
		return m._inverse() * v;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat4x4<T>::row_type operator/ 
	(
		typename tmat4x4<T>::col_type const & v, 
		tmat4x4<T> const & m
	)
	{
		return v * m._inverse();
	}
 
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> operator/ 
	(
		tmat4x4<T> const & m1, 
		tmat4x4<T> const & m2
	)
	{
		return m1 * m2._inverse();
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> const operator- 
	(
		tmat4x4<T> const & m
	)
	{
		return tmat4x4<T>(
			-m[0], 
			-m[1],
			-m[2],
			-m[3]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> const operator++ 
	(
		tmat4x4<T> const & m, 
		int
	) 
	{
		return tmat4x4<T>(
			m[0] + typename tmat4x4<T>::value_type(1),
			m[1] + typename tmat4x4<T>::value_type(1),
			m[2] + typename tmat4x4<T>::value_type(1),
			m[3] + typename tmat4x4<T>::value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat4x4<T> const operator-- 
	(
		tmat4x4<T> const & m, 
		int
	) 
	{
		return tmat4x4<T>(
			m[0] - typename tmat4x4<T>::value_type(1),
			m[1] - typename tmat4x4<T>::value_type(1),
			m[2] - typename tmat4x4<T>::value_type(1),
			m[3] - typename tmat4x4<T>::value_type(1));
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tmat4x4<T> const & m1, 
		tmat4x4<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tmat4x4<T> const & m1, 
		tmat4x4<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}

} //namespace detail
} //namespace glm
