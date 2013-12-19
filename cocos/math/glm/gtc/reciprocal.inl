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
/// @ref gtc_reciprocal
/// @file glm/gtc/reciprocal.inl
/// @date 2008-10-09 / 2012-04-07
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// sec
	template <typename genType>
	GLM_FUNC_QUALIFIER genType sec
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sec' only accept floating-point values");

		return genType(1) / glm::cos(angle);
	}

	VECTORIZE_VEC(sec)

	// csc
	template <typename genType>
	GLM_FUNC_QUALIFIER genType csc
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'csc' only accept floating-point values");

		return genType(1) / glm::sin(angle);
	}

	VECTORIZE_VEC(csc)

	// cot
	template <typename genType>
	GLM_FUNC_QUALIFIER genType cot
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'cot' only accept floating-point values");

		return genType(1) / glm::tan(angle);
	}

	VECTORIZE_VEC(cot)

	// asec
	template <typename genType>
	GLM_FUNC_QUALIFIER genType asec
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asec' only accept floating-point values");
	
		return acos(genType(1) / x);
	}

	VECTORIZE_VEC(asec)

	// acsc
	template <typename genType>
	GLM_FUNC_QUALIFIER genType acsc
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acsc' only accept floating-point values");

		return asin(genType(1) / x);
	}

	VECTORIZE_VEC(acsc)

	// acot
	template <typename genType>
	GLM_FUNC_QUALIFIER genType acot
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acot' only accept floating-point values");

		genType const pi_over_2 = genType(3.1415926535897932384626433832795 / 2.0);
		return pi_over_2 - atan(x);
	}

	VECTORIZE_VEC(acot)

	// sech
	template <typename genType>
	GLM_FUNC_QUALIFIER genType sech
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sech' only accept floating-point values");

		return genType(1) / glm::cosh(angle);
	}

	VECTORIZE_VEC(sech)

	// csch
	template <typename genType>
	GLM_FUNC_QUALIFIER genType csch
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'csch' only accept floating-point values");

		return genType(1) / glm::sinh(angle);
	}

	VECTORIZE_VEC(csch)

	// coth
	template <typename genType>
	GLM_FUNC_QUALIFIER genType coth
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'coth' only accept floating-point values");

		return glm::cosh(angle) / glm::sinh(angle);
	}

	VECTORIZE_VEC(coth)

	// asech
	template <typename genType>
	GLM_FUNC_QUALIFIER genType asech
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asech' only accept floating-point values");

		return acosh(genType(1) / x);
	}

	VECTORIZE_VEC(asech)

	// acsch
	template <typename genType>
	GLM_FUNC_QUALIFIER genType acsch
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acsch' only accept floating-point values");

		return asinh(genType(1) / x);
	}

	VECTORIZE_VEC(acsch)

	// acoth
	template <typename genType>
	GLM_FUNC_QUALIFIER genType acoth
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acoth' only accept floating-point values");

		return atanh(genType(1) / x);
	}

	VECTORIZE_VEC(acoth)
}//namespace glm
