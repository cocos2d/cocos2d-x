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
/// @file glm/core/type_mat3x3.inl
/// @date 2005-01-27 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tmat3x3<T>::size_type tmat3x3<T>::length() const
	{
		return 3;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::size_type tmat3x3<T>::col_size()
	{
		return 3;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::size_type tmat3x3<T>::row_size()
	{
		return 3;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::col_type &
	tmat3x3<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::col_type const &
	tmat3x3<T>::operator[]
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
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3()
	{
		value_type const Zero(0);
		value_type const One(1);
		this->value[0] = col_type(One, Zero, Zero);
		this->value[1] = col_type(Zero, One, Zero);
		this->value[2] = col_type(Zero, Zero, One);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat3x3<T> const & m
	)
	{
		this->value[0] = m.value[0];
		this->value[1] = m.value[1];
		this->value[2] = m.value[2];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		ctor
	)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		value_type const & s
	)
	{
		value_type const Zero(0);
		this->value[0] = col_type(s, Zero, Zero);
		this->value[1] = col_type(Zero, s, Zero);
		this->value[2] = col_type(Zero, Zero, s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		value_type const & x0, value_type const & y0, value_type const & z0, 
		value_type const & x1, value_type const & y1, value_type const & z1,
		value_type const & x2, value_type const & y2, value_type const & z2
	)
	{
		this->value[0] = col_type(x0, y0, z0);
		this->value[1] = col_type(x1, y1, z1);
		this->value[2] = col_type(x2, y2, z2);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		col_type const & v0, 
		col_type const & v1, 
		col_type const & v2
	)
	{
		this->value[0] = v0;
		this->value[1] = v1;
		this->value[2] = v2;
	}

	//////////////////////////////////////
	// Convertion constructors
	template <typename T> 
	template <typename U> 
	GLM_FUNC_DECL tmat3x3<T>::tmat3x3
	(
		U const & s
	)
	{
		value_type const Zero(0);
		this->value[0] = tvec3<T>(value_type(s), Zero, Zero);
		this->value[1] = tvec3<T>(Zero, value_type(s), Zero);
		this->value[2] = tvec3<T>(Zero, Zero, value_type(s));
	}
	
	template <typename T> 
	template <
		typename X1, typename Y1, typename Z1, 
		typename X2, typename Y2, typename Z2, 
		typename X3, typename Y3, typename Z3>  
	GLM_FUNC_DECL tmat3x3<T>::tmat3x3
	(
		X1 const & x1, Y1 const & y1, Z1 const & z1, 
		X2 const & x2, Y2 const & y2, Z2 const & z2, 
		X3 const & x3, Y3 const & y3, Z3 const & z3 
	)
	{
		this->value[0] = col_type(value_type(x1), value_type(y1), value_type(z1));
		this->value[1] = col_type(value_type(x2), value_type(y2), value_type(z2));
		this->value[2] = col_type(value_type(x3), value_type(y3), value_type(z3));
	}
	
	template <typename T> 
	template <typename V1, typename V2, typename V3> 
	GLM_FUNC_DECL tmat3x3<T>::tmat3x3
	(
		tvec3<V1> const & v1, 
		tvec3<V2> const & v2, 
		tvec3<V3> const & v3
	)
	{
		this->value[0] = col_type(v1);
		this->value[1] = col_type(v2);
		this->value[2] = col_type(v3);
	}

	//////////////////////////////////////////////////////////////
	// Conversions

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat3x3<U> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
		this->value[2] = col_type(m[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat2x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], value_type(0));
		this->value[1] = col_type(m[1], value_type(0));
		this->value[2] = col_type(detail::tvec2<T>(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat4x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
		this->value[2] = col_type(m[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat2x3<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = col_type(detail::tvec2<T>(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat3x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], value_type(0));
		this->value[1] = col_type(m[1], value_type(0));
		this->value[2] = col_type(m[2], value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat2x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
		this->value[2] = col_type(detail::tvec2<T>(0), value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat4x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], value_type(0));
		this->value[1] = col_type(m[1], value_type(0));
		this->value[2] = col_type(m[2], value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat3x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
		this->value[2] = col_type(m[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T>::tmat3x3
	(
		tmat4x3<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
	}

	//////////////////////////////////////////////////////////////
	// Operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator=
	(
		tmat3x3<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator=
	(
		tmat3x3<U> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator+= (U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator+=
	(
		tmat3x3<U> const & m
	)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator-= (U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator-= 
	(
		tmat3x3<U> const & m
	)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator*= (U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator*= 
	(
		tmat3x3<U> const & m
	)
	{
		return (*this = *this * m);
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator/= (U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator/= 
	(
		tmat3x3<U> const & m
	)
	{
		return (*this = *this / m);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator++ ()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> & tmat3x3<T>::operator-- ()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> tmat3x3<T>::_inverse() const
	{
		T S00 = value[0][0];
		T S01 = value[0][1];
		T S02 = value[0][2];

		T S10 = value[1][0];
		T S11 = value[1][1];
		T S12 = value[1][2];

		T S20 = value[2][0];
		T S21 = value[2][1];
		T S22 = value[2][2];
/*
		tmat3x3<T> Inverse(
			+ (S11 * S22 - S21 * S12),
			- (S10 * S22 - S20 * S12),
			+ (S10 * S21 - S20 * S11),
			- (S01 * S22 - S21 * S02),
			+ (S00 * S22 - S20 * S02),
			- (S00 * S21 - S20 * S01),
			+ (S01 * S12 - S11 * S02),
			- (S00 * S12 - S10 * S02),
			+ (S00 * S11 - S10 * S01));
*/
		tmat3x3<T> Inverse(
			S11 * S22 - S21 * S12,
			S12 * S20 - S22 * S10,
			S10 * S21 - S20 * S11,
			S02 * S21 - S01 * S22,
			S00 * S22 - S02 * S20,
			S01 * S20 - S00 * S21,
			S12 * S01 - S11 * S02,
			S10 * S02 - S12 * S00,
			S11 * S00 - S10 * S01);

		T Determinant = S00 * (S11 * S22 - S21 * S12)
						- S10 * (S01 * S22 - S21 * S02)
						+ S20 * (S01 * S12 - S11 * S02);

		Inverse /= Determinant;
		return Inverse;
	}

	//////////////////////////////////////////////////////////////
	// Binary operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator+ 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
	{
		return tmat3x3<T>(
			m[0] + s,
			m[1] + s,
			m[2] + s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator+ 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
	{
		return tmat3x3<T>(
			m[0] + s,
			m[1] + s,
			m[2] + s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator+ 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return tmat3x3<T>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator- 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
	{
		return tmat3x3<T>(
			m[0] - s,
			m[1] - s,
			m[2] - s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator- 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
	{
		return tmat3x3<T>(
			s - m[0],
			s - m[1],
			s - m[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator- 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return tmat3x3<T>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator* 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
	{
		return tmat3x3<T>(
			m[0] * s,
			m[1] * s,
			m[2] * s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator* 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
	{
		return tmat3x3<T>(
			m[0] * s,
			m[1] * s,
			m[2] * s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::col_type operator* 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::row_type const & v
	)
	{
		return typename tmat3x3<T>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::row_type operator* 
	(
		typename tmat3x3<T>::col_type const & v, 
		tmat3x3<T> const & m
	)
	{
		return typename tmat3x3<T>::row_type(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator* 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		typename tmat3x3<T>::value_type const SrcA00 = m1[0][0];
		typename tmat3x3<T>::value_type const SrcA01 = m1[0][1];
		typename tmat3x3<T>::value_type const SrcA02 = m1[0][2];
		typename tmat3x3<T>::value_type const SrcA10 = m1[1][0];
		typename tmat3x3<T>::value_type const SrcA11 = m1[1][1];
		typename tmat3x3<T>::value_type const SrcA12 = m1[1][2];
		typename tmat3x3<T>::value_type const SrcA20 = m1[2][0];
		typename tmat3x3<T>::value_type const SrcA21 = m1[2][1];
		typename tmat3x3<T>::value_type const SrcA22 = m1[2][2];

		typename tmat3x3<T>::value_type const SrcB00 = m2[0][0];
		typename tmat3x3<T>::value_type const SrcB01 = m2[0][1];
		typename tmat3x3<T>::value_type const SrcB02 = m2[0][2];
		typename tmat3x3<T>::value_type const SrcB10 = m2[1][0];
		typename tmat3x3<T>::value_type const SrcB11 = m2[1][1];
		typename tmat3x3<T>::value_type const SrcB12 = m2[1][2];
		typename tmat3x3<T>::value_type const SrcB20 = m2[2][0];
		typename tmat3x3<T>::value_type const SrcB21 = m2[2][1];
		typename tmat3x3<T>::value_type const SrcB22 = m2[2][2];

		tmat3x3<T> Result(tmat3x3<T>::null);
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
		return Result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x3<T> operator* 
	(
		tmat3x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return tmat2x3<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat4x3<T> operator* 
	(
		tmat3x3<T> const & m1, 
		tmat4x3<T> const & m2
	)
	{
		return tmat4x3<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2],
			m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator/ 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::value_type const & s
	)
	{
		return tmat3x3<T>(
			m[0] / s,
			m[1] / s,
			m[2] / s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator/ 
	(
		typename tmat3x3<T>::value_type const & s, 
		tmat3x3<T> const & m
	)
	{
		return tmat3x3<T>(
			s / m[0],
			s / m[1],
			s / m[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::col_type operator/ 
	(
		tmat3x3<T> const & m, 
		typename tmat3x3<T>::row_type const & v
	)
	{
		return m._inverse() * v;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat3x3<T>::row_type operator/ 
	(
		typename tmat3x3<T>::col_type const & v, 
		tmat3x3<T> const & m
	)
	{
		return v * m._inverse();
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator/ 
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return m1 * m2._inverse();
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> const operator- 
	(
		tmat3x3<T> const & m
	)
	{
		return tmat3x3<T>(
			-m[0], 
			-m[1],
			-m[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> const operator++ 
	(
		tmat3x3<T> const & m, 
		int
	) 
	{
		return tmat3x3<T>(
			m[0] + T(1),
			m[1] + T(1),
			m[2] + T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> const operator-- 
	(
		tmat3x3<T> const & m, 
		int
	) 
	{
		return tmat3x3<T>(
			m[0] - T(1),
			m[1] - T(1),
			m[2] - T(1));
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tmat3x3<T> const & m1, 
		tmat3x3<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}

} //namespace detail
} //namespace glm
