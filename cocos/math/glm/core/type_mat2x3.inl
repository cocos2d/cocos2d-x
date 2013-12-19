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
/// @file glm/core/type_mat2x3.inl
/// @date 2006-08-05 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tmat2x3<T>::size_type tmat2x3<T>::length() const
	{
		return 2;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x3<T>::size_type tmat2x3<T>::col_size()
	{
		return 3;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x3<T>::size_type tmat2x3<T>::row_size()
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x3<T>::col_type &
	tmat2x3<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x3<T>::col_type const &
	tmat2x3<T>::operator[]
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
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3()
	{
		this->value[0] = col_type(T(1), T(0), T(0));
		this->value[1] = col_type(T(0), T(1), T(0));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat2x3<T> const & m
	)
	{
		this->value[0] = m.value[0];
		this->value[1] = m.value[1];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		ctor
	)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		value_type const & s
	)
	{
		this->value[0] = col_type(s, T(0), T(0));
		this->value[1] = col_type(T(0), s, T(0));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		value_type const & x0, value_type const & y0, value_type const & z0,
		value_type const & x1, value_type const & y1, value_type const & z1
	)
	{
		this->value[0] = col_type(x0, y0, z0);
		this->value[1] = col_type(x1, y1, z1);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		col_type const & v0, 
		col_type const & v1
	)
	{
		this->value[0] = v0;
		this->value[1] = v1;
	}

	//////////////////////////////////////
	// Convertion constructors
	template <typename T> 
	template <typename U> 
	GLM_FUNC_DECL tmat2x3<T>::tmat2x3
	(
		U const & s
	)
	{
		value_type const Zero(0);
		this->value[0] = tvec3<T>(value_type(s), Zero, Zero);
		this->value[1] = tvec3<T>(Zero, value_type(s), Zero);
	}
	
	template <typename T> 
	template <
		typename X1, typename Y1, typename Z1, 
		typename X2, typename Y2, typename Z2> 
	GLM_FUNC_DECL tmat2x3<T>::tmat2x3
	(
		X1 const & x1, Y1 const & y1, Z1 const & z1, 
		X2 const & x2, Y2 const & y2, Z2 const & z2
	)		
	{
		this->value[0] = col_type(value_type(x1), value_type(y1), value_type(z1));
		this->value[1] = col_type(value_type(x2), value_type(y2), value_type(z2));
	}
	
	template <typename T> 
	template <typename V1, typename V2> 
	GLM_FUNC_DECL tmat2x3<T>::tmat2x3
	(
		tvec3<V1> const & v1, 
		tvec3<V2> const & v2
	)		
	{
		this->value[0] = col_type(v1);
		this->value[1] = col_type(v2);
	}

	//////////////////////////////////////
	// Matrix conversions
    
	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat2x3<U> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat2x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], T(0));
		this->value[1] = col_type(m[1], T(0));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat3x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat4x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat2x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat3x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], T(0));
		this->value[1] = col_type(m[1], T(0));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat3x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat4x2<T> const & m
	)
	{
		this->value[0] = col_type(m[0], T(0));
		this->value[1] = col_type(m[1], T(0));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>::tmat2x3
	(
		tmat4x3<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
	}

	//////////////////////////////////////////////////////////////
	// Unary updatable operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T>& tmat2x3<T>::operator= 
	(
		tmat2x3<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T>& tmat2x3<T>::operator= 
	(
		tmat2x3<U> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T> & tmat2x3<T>::operator+= (U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T>& tmat2x3<T>::operator+=
	(
		tmat2x3<U> const & m
	)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T>& tmat2x3<T>::operator-= (U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T>& tmat2x3<T>::operator-= 
	(
		tmat2x3<U> const & m
	)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T>& tmat2x3<T>::operator*= (U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T> & tmat2x3<T>::operator*= 
	(
		tmat2x3<U> const & m
	)
	{
		return (*this = tmat2x3<U>(*this * m));
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x3<T> & tmat2x3<T>::operator/= (U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> & tmat2x3<T>::operator++ ()
	{
		++this->value[0];
		++this->value[1];
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> & tmat2x3<T>::operator-- ()
	{
		--this->value[0];
		--this->value[1];
		return *this;
	}

	//////////////////////////////////////////////////////////////
	// Binary operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator+ 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
	{
		return tmat2x3<T>(
			m[0] + s,
			m[1] + s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator+ 
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return tmat2x3<T>(
			m1[0] + m2[0],
			m1[1] + m2[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator- 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
	{
		return tmat2x3<T>(
			m[0] - s,
			m[1] - s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator- 
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return tmat2x3<T>(
			m1[0] - m2[0],
			m1[1] - m2[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator* 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
	{
		return tmat2x3<T>(
			m[0] * s,
			m[1] * s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator* 
	(
		typename tmat2x3<T>::value_type const & s, 
		tmat2x3<T> const & m
	)
	{
		return tmat2x3<T>(
			m[0] * s,
			m[1] * s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x3<T>::col_type operator* 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::row_type const & v)
	{
		return typename tmat2x3<T>::col_type(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y,
			m[0][2] * v.x + m[1][2] * v.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat2x3<T>::row_type operator* 
	(
		typename tmat2x3<T>::col_type const & v, 
		tmat2x3<T> const & m) 
	{
		return typename tmat2x3<T>::row_type(
			v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2],
			v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x3<T> operator* 
	(
		tmat2x3<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return tmat2x3<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat3x3<T> operator* 
	(
		tmat2x3<T> const & m1, 
		tmat3x2<T> const & m2
	)
	{
		typename tmat2x3<T>::value_type SrcA00 = m1[0][0];
		typename tmat2x3<T>::value_type SrcA01 = m1[0][1];
		typename tmat2x3<T>::value_type SrcA02 = m1[0][2];
		typename tmat2x3<T>::value_type SrcA10 = m1[1][0];
		typename tmat2x3<T>::value_type SrcA11 = m1[1][1];
		typename tmat2x3<T>::value_type SrcA12 = m1[1][2];

		typename tmat2x3<T>::value_type SrcB00 = m2[0][0];
		typename tmat2x3<T>::value_type SrcB01 = m2[0][1];
		typename tmat2x3<T>::value_type SrcB10 = m2[1][0];
		typename tmat2x3<T>::value_type SrcB11 = m2[1][1];
		typename tmat2x3<T>::value_type SrcB20 = m2[2][0];
		typename tmat2x3<T>::value_type SrcB21 = m2[2][1];

		tmat3x3<T> Result(tmat3x3<T>::null);
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
		return Result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat4x3<T> operator* 
	(
		tmat2x3<T> const & m1, 
		tmat4x2<T> const & m2
	)
	{
		return tmat4x3<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1],
			m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator/ 
	(
		tmat2x3<T> const & m, 
		typename tmat2x3<T>::value_type const & s
	)
	{
		return tmat2x3<T>(
			m[0] / s,
			m[1] / s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> operator/ 
	(
		typename tmat2x3<T>::value_type const & s, 
		tmat2x3<T> const & m
	)
	{
		return tmat2x3<T>(
			s / m[0],
			s / m[1]);
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> const operator- 
	(
		tmat2x3<T> const & m
	)
	{
		return tmat2x3<T>(
			-m[0], 
			-m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> const operator++ 
	(
		tmat2x3<T> const & m, 
		int
	) 
	{
		return tmat2x3<T>(
			m[0] + typename tmat2x3<T>::value_type(1),
			m[1] + typename tmat2x3<T>::value_type(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x3<T> const operator-- 
	(
		tmat2x3<T> const & m, 
		int
	) 
	{
		return tmat2x3<T>(
			m[0] - typename tmat2x3<T>::value_type(1),
			m[1] - typename tmat2x3<T>::value_type(1));
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tmat2x3<T> const & m1, 
		tmat2x3<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}
} //namespace detail
} //namespace glm
