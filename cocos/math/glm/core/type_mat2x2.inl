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
/// @file glm/core/type_mat2x2.inl
/// @date 2005-01-16 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tmat2x2<T>::size_type tmat2x2<T>::length() const
	{
		return 2;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::size_type tmat2x2<T>::col_size()
	{
		return 2;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::size_type tmat2x2<T>::row_size()
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::col_type &
	tmat2x2<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return this->value[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::col_type const &
	tmat2x2<T>::operator[]
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
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2()
	{
		this->value[0] = col_type(1, 0);
		this->value[1] = col_type(0, 1);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat2x2<T> const & m
	)
	{
		this->value[0] = m.value[0];
		this->value[1] = m.value[1];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		ctor
	)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		value_type const & s
	)
	{
		value_type const Zero(0);
		this->value[0] = col_type(s, Zero);
		this->value[1] = col_type(Zero, s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		value_type const & x0, value_type const & y0, 
		value_type const & x1, value_type const & y1
	)
	{
		this->value[0] = col_type(x0, y0);
		this->value[1] = col_type(x1, y1);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
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
	GLM_FUNC_DECL tmat2x2<T>::tmat2x2
	(
		U const & s
	)
	{
		value_type const Zero(0);
		this->value[0] = tvec2<T>(value_type(s), Zero);
		this->value[1] = tvec2<T>(Zero, value_type(s));
	}
	
	template <typename T> 
	template <typename X1, typename Y1, typename X2, typename Y2> 
	GLM_FUNC_DECL tmat2x2<T>::tmat2x2
	(
		X1 const & x1, Y1 const & y1, 
		X2 const & x2, Y2 const & y2
	)
	{
		this->value[0] = col_type(value_type(x1), value_type(y1));
		this->value[1] = col_type(value_type(x2), value_type(y2));
	}
	
	template <typename T> 
	template <typename V1, typename V2> 
	GLM_FUNC_DECL tmat2x2<T>::tmat2x2
	(
		tvec2<V1> const & v1, 
		tvec2<V2> const & v2
	)
	{
		this->value[0] = col_type(v1);
		this->value[1] = col_type(v2);
	}

	//////////////////////////////////////////////////////////////
	// mat2x2 matrix conversions

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat2x2<U> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat3x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat4x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat2x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat3x2<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat2x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat4x2<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat3x4<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>::tmat2x2
	(
		tmat4x3<T> const & m
	)
	{
		this->value[0] = col_type(m[0]);
		this->value[1] = col_type(m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> tmat2x2<T>::_inverse() const
	{
		typename tmat2x2<T>::value_type Determinant = this->value[0][0] * this->value[1][1] - this->value[1][0] * this->value[0][1];

		tmat2x2<T> Inverse(
			+ this->value[1][1] / Determinant,
			- this->value[0][1] / Determinant,
			- this->value[1][0] / Determinant, 
			+ this->value[0][0] / Determinant);
		return Inverse;
	}

	//////////////////////////////////////////////////////////////
	// mat2x2 operators

	// This function shouldn't required but it seems that VC7.1 have an optimisation bug if this operator wasn't declared
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator=
	(
		tmat2x2<T> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator=
	(
		tmat2x2<U> const & m
	)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator+= (U s)
	{
		this->value[0] += s;
		this->value[1] += s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator+=
	(
		tmat2x2<U> const & m
	)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator-= (U s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator-=
	(
		tmat2x2<U> const & m
	)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator*= (U s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator*= 
	(
		tmat2x2<U> const & m
	)
	{
		return (*this = *this * m);
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator/= (U s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		return *this;
	}

	template <typename T> 
	template <typename U> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator/= 
	(
		tmat2x2<U> const & m
	)
	{
		return (*this = *this / m);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator++ ()
	{
		++this->value[0];
		++this->value[1];
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T>& tmat2x2<T>::operator-- ()
	{
		--this->value[0];
		--this->value[1];
		return *this;
	}

	//////////////////////////////////////////////////////////////
	// Binary operators

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator+ 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
	{
		return tmat2x2<T>(
			m[0] + s,
			m[1] + s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator+ 
	(
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
	{
		return tmat2x2<T>(
			m[0] + s,
			m[1] + s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator+ 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return tmat2x2<T>(
			m1[0] + m2[0],
			m1[1] + m2[1]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator- 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
	{
		return tmat2x2<T>(
			m[0] - s,
			m[1] - s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator- 
	(
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
	{
		return tmat2x2<T>(
			s - m[0],
			s - m[1]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator- 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return tmat2x2<T>(
			m1[0] - m2[0],
			m1[1] - m2[1]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator* 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
	{
		return tmat2x2<T>(
			m[0] * s,
			m[1] * s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator* 
	(	
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
	{
		return tmat2x2<T>(
			m[0] * s,
			m[1] * s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::col_type operator*
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::row_type const & v
	)
	{
		return detail::tvec2<T>(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::row_type operator*
	(
		typename tmat2x2<T>::col_type const & v, 
		tmat2x2<T> const & m
	)
	{
		return detail::tvec2<T>(
			v.x * m[0][0] + v.y * m[0][1],
			v.x * m[1][0] + v.y * m[1][1]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat2x2<T> operator*
	(
		tmat2x2<T> const & m1,
		tmat2x2<T> const & m2
	)
	{
		return tmat2x2<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat3x2<T> operator*
	(
		tmat2x2<T> const & m1, 
		tmat3x2<T> const & m2
	)
	{
		return tmat3x2<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tmat4x2<T> operator*
	(
		tmat2x2<T> const & m1, 
		tmat4x2<T> const & m2
	)
	{
		return tmat4x2<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
			m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
			m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
			m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
			m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> operator/ 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::value_type const & s
	)
	{
		return tmat2x2<T>(
			m[0] / s,
			m[1] / s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> operator/ 
	(
		typename tmat2x2<T>::value_type const & s, 
		tmat2x2<T> const & m
	)
	{
		return tmat2x2<T>(
			s / m[0],
			s / m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::col_type operator/ 
	(
		tmat2x2<T> const & m, 
		typename tmat2x2<T>::row_type & v
	)
	{
		return m._inverse() * v;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER typename tmat2x2<T>::row_type operator/ 
	(
		typename tmat2x2<T>::col_type const & v,
		tmat2x2<T> const & m
	)
	{
		return v * m._inverse();
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> operator/ 
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return m1 * m2._inverse();
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> const operator- 
	(
		tmat2x2<T> const & m
	)
	{
		return tmat2x2<T>(
			-m[0], 
			-m[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> const operator++ 
	(
		tmat2x2<T> const & m, 
		int
	) 
	{
		return tmat2x2<T>(
			m[0] + T(1),
			m[1] + T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tmat2x2<T> const operator-- 
	(
		tmat2x2<T> const & m, 
		int
	) 
	{
		return tmat2x2<T>(
			m[0] - T(1),
			m[1] - T(1));
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tmat2x2<T> const & m1, 
		tmat2x2<T> const & m2
	)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]);
	}

} //namespace detail
} //namespace glm
