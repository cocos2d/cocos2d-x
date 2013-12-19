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
/// @file glm/core/func_exponential.inl
/// @date 2008-08-03 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// pow
	template <typename genType>
	GLM_FUNC_QUALIFIER genType pow
	(
		genType const & x, 
		genType const & y
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'pow' only accept floating-point input");

		return genType(::std::pow(x, y));
	}

	VECTORIZE_VEC_VEC(pow)

	// exp
	template <typename genType>
	GLM_FUNC_QUALIFIER genType exp
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'exp' only accept floating-point input");

		return genType(::std::exp(x));
	}

	VECTORIZE_VEC(exp)

	// log
	template <typename genType>
	GLM_FUNC_QUALIFIER genType log
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'log' only accept floating-point input");

		return genType(::std::log(x));
	}

	VECTORIZE_VEC(log)

	//exp2, ln2 = 0.69314718055994530941723212145818f
	template <typename genType>
	GLM_FUNC_QUALIFIER genType exp2
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'exp2' only accept floating-point input");

		return genType(::std::exp(genType(0.69314718055994530941723212145818) * x));
	}

	VECTORIZE_VEC(exp2)

namespace _detail
{
	template <int _PATH = detail::float_or_int_value::GLM_ERROR>
	struct _compute_log2
	{
		template <typename T>
		T operator() (T const & Value) const;
/*
		{
			GLM_STATIC_ASSERT(0, "'log2' parameter has an invalid template parameter type. GLM core features only supports floating-point types, include <glm/gtx/integer.hpp> for integer types support. Others types are not supported.");
			return Value;
		}
*/
	};

	template <>
	struct _compute_log2<detail::float_or_int_value::GLM_FLOAT>
	{
		template <typename T>
		T operator() (T const & Value) const
		{
			return T(::std::log(Value)) / T(0.69314718055994530941723212145818);
		}
	};

}//namespace _detail

	// log2, ln2 = 0.69314718055994530941723212145818f
	template <typename genType>
	GLM_FUNC_QUALIFIER genType log2
	(
		genType const & x
	)
	{
		assert(x > genType(0)); // log2 is only defined on the range (0, inf]
		return _detail::_compute_log2<detail::float_or_int_trait<genType>::ID>()(x);
	}

	VECTORIZE_VEC(log2)

	// sqrt
	template <typename genType>
	GLM_FUNC_QUALIFIER genType sqrt
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'sqrt' only accept floating-point input");

		return genType(::std::sqrt(x));
	}

	VECTORIZE_VEC(sqrt)

	template <typename genType>
	GLM_FUNC_QUALIFIER genType inversesqrt
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'inversesqrt' only accept floating-point input");
		assert(x > genType(0));

		return genType(1) / ::std::sqrt(x);
	}

	VECTORIZE_VEC(inversesqrt)

}//namespace glm
