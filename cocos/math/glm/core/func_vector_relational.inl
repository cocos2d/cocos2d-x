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
/// @file glm/core/func_vector_relational.inl
/// @date 2008-08-03 / 2011-09-09
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER typename vecType<T>::bool_type lessThan
	(
		vecType<T> const & x, 
		vecType<T> const & y
	)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
			"Invalid template instantiation of 'lessThan', GLM vector types required");
		GLM_STATIC_ASSERT(detail::is_bool<T>::_NO,
			"Invalid template instantiation of 'lessThan', GLM vector types required floating-point or integer value types vectors");
		assert(x.length() == y.length());

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < x.length(); ++i)
			Result[i] = x[i] < y[i];

		return Result;
	}

	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER typename vecType<T>::bool_type lessThanEqual
	(
		vecType<T> const & x, 
		vecType<T> const & y
	)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
			"Invalid template instantiation of 'lessThanEqual', GLM vector types required");
		GLM_STATIC_ASSERT(detail::is_bool<T>::_NO, 
			"Invalid template instantiation of 'lessThanEqual', GLM vector types required floating-point or integer value types vectors");
		assert(x.length() == y.length());

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < x.length(); ++i)
			Result[i] = x[i] <= y[i];
		return Result;
	}

	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER typename vecType<T>::bool_type greaterThan
	(
		vecType<T> const & x, 
		vecType<T> const & y
	)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
			"Invalid template instantiation of 'greaterThan', GLM vector types required");
		GLM_STATIC_ASSERT(detail::is_bool<T>::_NO, 
			"Invalid template instantiation of 'greaterThan', GLM vector types required floating-point or integer value types vectors");
		assert(x.length() == y.length());

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < x.length(); ++i)
			Result[i] = x[i] > y[i];
		return Result;
	}

	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER typename vecType<T>::bool_type greaterThanEqual
	(
		vecType<T> const & x, 
		vecType<T> const & y
	)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
			"Invalid template instantiation of 'greaterThanEqual', GLM vector types required");
		GLM_STATIC_ASSERT(detail::is_bool<T>::_NO, 
			"Invalid template instantiation of 'greaterThanEqual', GLM vector types required floating-point or integer value types vectors");
		assert(x.length() == y.length());

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < x.length(); ++i)
			Result[i] = x[i] >= y[i];
		return Result;
	}

	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER typename vecType<T>::bool_type equal
	(
		vecType<T> const & x, 
		vecType<T> const & y
	)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
			"Invalid template instantiation of 'equal', GLM vector types required");
		assert(x.length() == y.length());

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < x.length(); ++i)
			Result[i] = x[i] == y[i];
		return Result;
	}

	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER typename vecType<T>::bool_type notEqual
	(
		vecType<T> const & x, 
		vecType<T> const & y
	)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<T> >::_YES, 
			"Invalid template instantiation of 'notEqual', GLM vector types required");
		assert(x.length() == y.length());

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < x.length(); ++i)
			Result[i] = x[i] != y[i];
		return Result;
	}

	template <template <typename> class vecType> 
	GLM_FUNC_QUALIFIER bool any(vecType<bool> const & v)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<bool> >::_YES, 
			"Invalid template instantiation of 'any', GLM boolean vector types required");

		bool Result = false;
		for(typename vecType<bool>::size_type i = 0; i < v.length(); ++i)
			Result = Result || v[i];
		return Result;
	}

	template <template <typename> class vecType> 
	GLM_FUNC_QUALIFIER bool all(vecType<bool> const & v)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<bool> >::_YES, 
			"Invalid template instantiation of 'all', GLM boolean vector types required");

		bool Result = true;
		for(typename vecType<bool>::size_type i = 0; i < v.length(); ++i)
			Result = Result && v[i];
		return Result;
	}

	template <template <typename> class vecType> 
	GLM_FUNC_QUALIFIER vecType<bool> not_(vecType<bool> const & v)
	{
		GLM_STATIC_ASSERT(detail::is_vector<vecType<bool> >::_YES, 
			"Invalid template instantiation of 'not_', GLM vector types required");

		typename vecType<bool>::bool_type Result(vecType<bool>::null);
		for(typename vecType<bool>::size_type i = 0; i < v.length(); ++i)
			Result[i] = !v[i];
		return Result;
	}
}//namespace glm

