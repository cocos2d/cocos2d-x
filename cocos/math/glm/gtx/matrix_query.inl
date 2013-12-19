///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-05
// Updated : 2007-03-05
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_query.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template<typename T> 
	GLM_FUNC_QUALIFIER bool isNull
	(
		detail::tmat2x2<T> const & m, 
		T const & epsilon)
	{
		bool result = true;
		for(int i = 0; result && i < 2 ; ++i)
			result = isNull(m[i], epsilon);
		return result;
	}

	template<typename T> 
	GLM_FUNC_QUALIFIER bool isNull
	(
		detail::tmat3x3<T> const & m, 
		T const & epsilon
	)
	{
		bool result = true;
		for(int i = 0; result && i < 3 ; ++i)
			result = isNull(m[i], epsilon);
		return result;
	}

	template<typename T> 
	GLM_FUNC_QUALIFIER bool isNull
	(
		detail::tmat4x4<T> const & m, 
		T const & epsilon
	)
	{
		bool result = true;
		for(int i = 0; result && i < 4 ; ++i)
			result = isNull(m[i], epsilon);
		return result;
	}

	template<typename genType> 
	GLM_FUNC_QUALIFIER bool isIdentity
	(
		genType const & m, 
		typename genType::value_type const & epsilon
	)
	{
		bool result = true;
		for(typename genType::size_type i = typename genType::size_type(0); result && i < genType::col_size(); ++i)
		{
			for(typename genType::size_type j = typename genType::size_type(0); result && j < i ; ++j)
				result = abs(m[i][j]) <= epsilon;
			if(result)
				result = abs(m[i][i] - typename genType::value_type(1)) <= epsilon;
			for(typename genType::size_type j = i + typename genType::size_type(1); result && j < genType::row_size(); ++j)
				result = abs(m[i][j]) <= epsilon;
		}
		return result;
	}

	template<typename genType>  
	GLM_FUNC_QUALIFIER bool isNormalized
	(
		detail::tmat2x2<genType> const & m, 
		genType const & epsilon
	)
	{
		bool result(true);
                for(typename detail::tmat2x2<genType>::size_type i(0); result && i < m.length(); ++i)
			result = isNormalized(m[i], epsilon);
                for(typename detail::tmat2x2<genType>::size_type i(0); result && i < m.length(); ++i)
		{
                        typename detail::tmat2x2<genType>::col_type v;
                        for(typename detail::tmat2x2<genType>::size_type j(0); j < m.length(); ++j)
				v[j] = m[j][i];
			result = isNormalized(v, epsilon);
		}
		return result;
	}

	template<typename genType>  
	GLM_FUNC_QUALIFIER bool isNormalized
	(
		detail::tmat3x3<genType> const & m, 
		genType const & epsilon
	)
	{
		bool result(true);
                for(typename detail::tmat3x3<genType>::size_type i(0); result && i < m.length(); ++i)
			result = isNormalized(m[i], epsilon);
                for(typename detail::tmat3x3<genType>::size_type i(0); result && i < m.length(); ++i)
		{
                        typename detail::tmat3x3<genType>::col_type v;
                        for(typename detail::tmat3x3<genType>::size_type j(0); j < m.length(); ++j)
				v[j] = m[j][i];
			result = isNormalized(v, epsilon);
		}
		return result;
	}

	template<typename genType>  
	GLM_FUNC_QUALIFIER bool isNormalized
	(
		detail::tmat4x4<genType> const & m, 
		genType const & epsilon
	)
	{
		bool result(true);
                for(typename detail::tmat4x4<genType>::size_type i(0); result && i < m.length(); ++i)
			result = isNormalized(m[i], epsilon);
                for(typename detail::tmat4x4<genType>::size_type i(0); result && i < m.length(); ++i)
		{
                        typename detail::tmat4x4<genType>::col_type v;
                        for(typename detail::tmat4x4<genType>::size_type j(0); j < m.length(); ++j)
				v[j] = m[j][i];
			result = isNormalized(v, epsilon);
		}
		return result;
	}

	template<typename genType, template <typename> class matType>  
	GLM_FUNC_QUALIFIER bool isOrthogonal
	(
		matType<genType> const & m, 
		genType const & epsilon
	)
	{
		bool result(true);
		for(typename matType<genType>::size_type i(0); result && i < m.length() - 1; ++i)
		for(typename matType<genType>::size_type j(i + 1); result && j < m.length(); ++j)
			result = areOrthogonal(m[i], m[j], epsilon);

		if(result)
		{
			matType<genType> tmp = transpose(m);
			for(typename matType<genType>::size_type i(0); result && i < m.length() - 1 ; ++i)
			for(typename matType<genType>::size_type j(i + 1); result && j < m.length(); ++j)
				result = areOrthogonal(tmp[i], tmp[j], epsilon);
		}
		return result;
	}
}//namespace glm
