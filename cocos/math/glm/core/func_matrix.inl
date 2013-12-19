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
/// @file glm/core/func_matrix.inl
/// @date 2008-03-08 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// matrixCompMult
	template <typename matType>
	GLM_FUNC_QUALIFIER matType matrixCompMult
	(
		matType const & x, 
		matType const & y
	)
	{
		GLM_STATIC_ASSERT(detail::type<typename matType::value_type>::is_float, "'matrixCompMult' only accept floating-point inputs");

		matType result(matType::null);
		for(typename matType::size_type i = 0; i < matType::row_size(); ++i)
			result[i] = x[i] * y[i];
		return result;
	}

	// outerProduct
	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> outerProduct
	(
		detail::tvec2<T> const & c, 
		detail::tvec2<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat2x2<T> m(detail::tmat2x2<T>::null);
		m[0][0] = c[0] * r[0];
		m[0][1] = c[1] * r[0];
		m[1][0] = c[0] * r[1];
		m[1][1] = c[1] * r[1];
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> outerProduct
	(
		detail::tvec3<T> const & c, 
		detail::tvec3<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat3x3<T> m(detail::tmat3x3<T>::null);
		for(typename detail::tmat3x3<T>::size_type i(0); i < m.length(); ++i)
			m[i] = c * r[i];
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> outerProduct
	(
		detail::tvec4<T> const & c, 
		detail::tvec4<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat4x4<T> m(detail::tmat4x4<T>::null);
		for(typename detail::tmat4x4<T>::size_type i(0); i < m.length(); ++i)
			m[i] = c * r[i];
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x3<T> outerProduct
	(
		detail::tvec3<T> const & c, 
		detail::tvec2<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat2x3<T> m(detail::tmat2x3<T>::null);
		m[0][0] = c.x * r.x;
		m[0][1] = c.y * r.x;
		m[0][2] = c.z * r.x;
		m[1][0] = c.x * r.y;
		m[1][1] = c.y * r.y;
		m[1][2] = c.z * r.y;
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x2<T> outerProduct
	(
		detail::tvec2<T> const & c, 
		detail::tvec3<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat3x2<T> m(detail::tmat3x2<T>::null);
		m[0][0] = c.x * r.x;
		m[0][1] = c.y * r.x;
		m[1][0] = c.x * r.y;
		m[1][1] = c.y * r.y;
		m[2][0] = c.x * r.z;
		m[2][1] = c.y * r.z;
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x4<T> outerProduct
	(
		detail::tvec4<T> const & c, 
		detail::tvec2<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat2x4<T> m(detail::tmat2x4<T>::null);
		m[0][0] = c.x * r.x;
		m[0][1] = c.y * r.x;
		m[0][2] = c.z * r.x;
		m[0][3] = c.w * r.x;
		m[1][0] = c.x * r.y;
		m[1][1] = c.y * r.y;
		m[1][2] = c.z * r.y;
		m[1][3] = c.w * r.y;
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x2<T> outerProduct
	(
		detail::tvec2<T> const & c, 
		detail::tvec4<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat4x2<T> m(detail::tmat4x2<T>::null);
		m[0][0] = c.x * r.x;
		m[0][1] = c.y * r.x;
		m[1][0] = c.x * r.y;
		m[1][1] = c.y * r.y;
		m[2][0] = c.x * r.z;
		m[2][1] = c.y * r.z;
		m[3][0] = c.x * r.w;
		m[3][1] = c.y * r.w;
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x4<T> outerProduct
	(
		detail::tvec4<T> const & c, 
		detail::tvec3<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat3x4<T> m(detail::tmat3x4<T>::null);
		m[0][0] = c.x * r.x;
		m[0][1] = c.y * r.x;
		m[0][2] = c.z * r.x;
		m[0][3] = c.w * r.x;
		m[1][0] = c.x * r.y;
		m[1][1] = c.y * r.y;
		m[1][2] = c.z * r.y;
		m[1][3] = c.w * r.y;
		m[2][0] = c.x * r.z;
		m[2][1] = c.y * r.z;
		m[2][2] = c.z * r.z;
		m[2][3] = c.w * r.z;
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x3<T> outerProduct
	(
		detail::tvec3<T> const & c, 
		detail::tvec4<T> const & r
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'outerProduct' only accept floating-point inputs");

		detail::tmat4x3<T> m(detail::tmat4x3<T>::null);
		m[0][0] = c.x * r.x;
		m[0][1] = c.y * r.x;
		m[0][2] = c.z * r.x;
		m[1][0] = c.x * r.y;
		m[1][1] = c.y * r.y;
		m[1][2] = c.z * r.y;
		m[2][0] = c.x * r.z;
		m[2][1] = c.y * r.z;
		m[2][2] = c.z * r.z;
		m[3][0] = c.x * r.w;
		m[3][1] = c.y * r.w;
		m[3][2] = c.z * r.w;
		return m;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> transpose
	(
		detail::tmat2x2<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat2x2<T> result(detail::tmat2x2<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> transpose
	(
		detail::tmat3x3<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat3x3<T> result(detail::tmat3x3<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];

		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];

		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> transpose
	(
		detail::tmat4x4<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat4x4<T> result(detail::tmat4x4<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];

		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];

		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[2][3] = m[3][2];

		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		result[3][2] = m[2][3];
		result[3][3] = m[3][3];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x3<T> transpose
	(
		detail::tmat3x2<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat2x3<T> result(detail::tmat2x3<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x2<T> transpose
	(
		detail::tmat2x3<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat3x2<T> result(detail::tmat3x2<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x4<T> transpose
	(
		detail::tmat4x2<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat2x4<T> result(detail::tmat2x4<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x2<T> transpose
	(
		detail::tmat2x4<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat4x2<T> result(detail::tmat4x2<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x4<T> transpose
	(
		detail::tmat4x3<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat3x4<T> result(detail::tmat3x4<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];
		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[2][3] = m[3][2];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x3<T> transpose
	(
		detail::tmat3x4<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'transpose' only accept floating-point inputs");

		detail::tmat4x3<T> result(detail::tmat4x3<T>::null);
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		result[3][2] = m[2][3];
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tmat2x2<T>::value_type determinant
	(
		detail::tmat2x2<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'determinant' only accept floating-point inputs");

		return m[0][0] * m[1][1] - m[1][0] * m[0][1];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tmat3x3<T>::value_type determinant
	(
		detail::tmat3x3<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'determinant' only accept floating-point inputs");

		return 
			+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tmat4x4<T>::value_type determinant
	(
		detail::tmat4x4<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'determinant' only accept floating-point inputs");

		T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

		detail::tvec4<T> DetCof(
			+ (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
			- (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
			+ (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
			- (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));

		return m[0][0] * DetCof[0]
				+ m[0][1] * DetCof[1]
				+ m[0][2] * DetCof[2]
				+ m[0][3] * DetCof[3];
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> inverse
	(
		detail::tmat2x2<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'inverse' only accept floating-point inputs");
			
		//valType Determinant = m[0][0] * m[1][1] - m[1][0] * m[0][1];
		T Determinant = determinant(m);

		detail::tmat2x2<T> Inverse(
			+ m[1][1] / Determinant,
			- m[0][1] / Determinant, 
			- m[1][0] / Determinant,
			+ m[0][0] / Determinant);

		return Inverse;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> inverse
	(
		detail::tmat3x3<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'inverse' only accept floating-point inputs");

		//valType Determinant = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
		//					- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
		//					+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);

		T Determinant = determinant(m);

		detail::tmat3x3<T> Inverse(detail::tmat3x3<T>::null);
		Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
		Inverse[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
		Inverse[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
		Inverse[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]);
		Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
		Inverse[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]);
		Inverse[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		Inverse[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]);
		Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
		Inverse /= Determinant;

		return Inverse;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> inverse
	(
		detail::tmat4x4<T> const & m
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'inverse' only accept floating-point inputs");

		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		detail::tvec4<T> const SignA(+1, -1, +1, -1);
		detail::tvec4<T> const SignB(-1, +1, -1, +1);

		detail::tvec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
		detail::tvec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
		detail::tvec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
		detail::tvec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
		detail::tvec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
		detail::tvec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

		detail::tvec4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		detail::tvec4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		detail::tvec4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		detail::tvec4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		detail::tvec4<T> Inv0 = SignA * (Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		detail::tvec4<T> Inv1 = SignB * (Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		detail::tvec4<T> Inv2 = SignA * (Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		detail::tvec4<T> Inv3 = SignB * (Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		detail::tmat4x4<T> Inverse(Inv0, Inv1, Inv2, Inv3);

		detail::tvec4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		T Determinant = glm::dot(m[0], Row0);

		Inverse /= Determinant;

		return Inverse;
	}
}//namespace glm
