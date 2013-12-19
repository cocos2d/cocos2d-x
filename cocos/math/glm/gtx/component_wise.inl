///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-05-21
// Updated : 2010-02-12
// Licence : This source is under MIT License
// File    : gtx_component_wise.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType>
	GLM_FUNC_QUALIFIER typename genType::value_type compAdd(genType const & v)
	{
		typename genType::value_type result = typename genType::value_type(0);
		for(typename genType::size_type i = 0; i < v.length(); ++i)
			result += v[i];
		return result;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER typename genType::value_type compMul(genType const & v)
	{
		typename genType::value_type result = typename genType::value_type(1);
		for(typename genType::size_type i = 0; i < v.length(); ++i)
			result *= v[i];
		return result;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER typename genType::value_type compMin(genType const & v)
	{
		typename genType::value_type result = typename genType::value_type(v[0]);
		for(typename genType::size_type i = 1; i < v.length(); ++i)
			result = min(result, v[i]);
		return result;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER typename genType::value_type compMax(genType const & v)
	{
		typename genType::value_type result = typename genType::value_type(v[0]);
		for(typename genType::size_type i = 1; i < v.length(); ++i)
			result = max(result, v[i]);
		return result;
	}
}//namespace glm
