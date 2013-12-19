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
/// @file glm/core/func_trigonometric.inl
/// @date 2008-08-03 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// radians
	template <typename genType>
	GLM_FUNC_QUALIFIER genType radians
	(
		genType const & degrees
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'radians' only accept floating-point input");

		genType const pi = genType(3.1415926535897932384626433832795);
		return degrees * (pi / genType(180));
	}

	VECTORIZE_VEC(radians)
	
	// degrees
	template <typename genType>
	GLM_FUNC_QUALIFIER genType degrees
	(
		genType const & radians
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'degrees' only accept floating-point input");

		const genType pi = genType(3.1415926535897932384626433832795);
		return radians * (genType(180) / pi);
	}

	VECTORIZE_VEC(degrees)

	// sin
	template <typename genType>
	GLM_FUNC_QUALIFIER genType sin
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sin' only accept floating-point input");

		return genType(::std::sin(angle));
	}

	VECTORIZE_VEC(sin)

	// cos
	template <typename genType>
	GLM_FUNC_QUALIFIER genType cos(genType const & angle)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'cos' only accept floating-point input");

		return genType(::std::cos(angle));
	}

	VECTORIZE_VEC(cos)

	// tan
	template <typename genType>
	GLM_FUNC_QUALIFIER genType tan
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'tan' only accept floating-point input");

		return genType(::std::tan(angle));
	}

	VECTORIZE_VEC(tan)

	// asin
	template <typename genType>
	GLM_FUNC_QUALIFIER genType asin
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asin' only accept floating-point input");

		return genType(::std::asin(x));
	}

	VECTORIZE_VEC(asin)

	// acos
	template <typename genType>
	GLM_FUNC_QUALIFIER genType acos
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acos' only accept floating-point input");

		return genType(::std::acos(x));
	}

	VECTORIZE_VEC(acos)

	// atan
	template <typename genType>
	GLM_FUNC_QUALIFIER genType atan
	(
		genType const & y, 
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'atan' only accept floating-point input");

		return genType(::std::atan2(y, x));
	}

	VECTORIZE_VEC_VEC(atan)

	template <typename genType>
	GLM_FUNC_QUALIFIER genType atan
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'atan' only accept floating-point input");

		return genType(::std::atan(x));
	}

	VECTORIZE_VEC(atan)

	// sinh
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType sinh
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sinh' only accept floating-point input");

		return genType(std::sinh(angle));
	}

	VECTORIZE_VEC(sinh)

	// cosh
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType cosh
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'cosh' only accept floating-point input");

		return genType(std::cosh(angle));
	}

	VECTORIZE_VEC(cosh)

	// tanh
	template <typename genType>
	GLM_FUNC_QUALIFIER genType tanh
	(
		genType const & angle
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'tanh' only accept floating-point input");

		return genType(std::tanh(angle));
	}

	VECTORIZE_VEC(tanh)

	// asinh
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType asinh
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'asinh' only accept floating-point input");
		
		return (x < genType(0) ? genType(-1) : (x > genType(0) ? genType(1) : genType(0))) * log(abs(x) + sqrt(genType(1) + x * x));
	}

	VECTORIZE_VEC(asinh)

	// acosh
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType acosh
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'acosh' only accept floating-point input");

		if(x < genType(1))
			return genType(0);
		return log(x + sqrt(x * x - genType(1)));
	}

	VECTORIZE_VEC(acosh)

	// atanh
	template <typename genType>
	GLM_FUNC_QUALIFIER genType atanh
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'atanh' only accept floating-point input");
		
		if(abs(x) >= genType(1))
			return 0;
		return genType(0.5) * log((genType(1) + x) / (genType(1) - x));
	}

	VECTORIZE_VEC(atanh)

}//namespace glm
