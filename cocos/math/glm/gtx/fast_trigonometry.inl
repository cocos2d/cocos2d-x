///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-08
// Updated : 2011-10-14
// Licence : This source is under MIT License
// File    : glm/gtx/fast_trigonometry.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// sin
	template <typename T> 
	GLM_FUNC_QUALIFIER T fastSin(T const & x)
	{
		return x - ((x * x * x) / T(6)) + ((x * x * x * x * x) / T(120)) - ((x * x * x * x * x * x * x) / T(5040));
	}

	VECTORIZE_VEC(fastSin)

	// cos
	template <typename T> 
	GLM_FUNC_QUALIFIER T fastCos(T const & x)
	{
		return T(1) - (x * x * T(0.5)) + (x * x * x * x * T(0.041666666666)) - (x * x * x * x * x * x * T(0.00138888888888));
	}

	VECTORIZE_VEC(fastCos)

	// tan
	template <typename T> 
	GLM_FUNC_QUALIFIER T fastTan(T const & x)
	{
		return x + (x * x * x * T(0.3333333333)) + (x * x * x * x * x * T(0.1333333333333)) + (x * x * x * x * x * x * x * T(0.0539682539));
	}

	VECTORIZE_VEC(fastTan)

	// asin
	template <typename T> 
	GLM_FUNC_QUALIFIER T fastAsin(T const & x)
	{
		return x + (x * x * x * T(0.166666667)) + (x * x * x * x * x * T(0.075)) + (x * x * x * x * x * x * x * T(0.0446428571)) + (x * x * x * x * x * x * x * x * x * T(0.0303819444));// + (x * x * x * x * x * x * x * x * x * x * x * T(0.022372159));
	}

	VECTORIZE_VEC(fastAsin)

	// acos
	template <typename T> 
	GLM_FUNC_QUALIFIER T fastAcos(T const & x)
	{
		return T(1.5707963267948966192313216916398) - fastAsin(x); //(PI / 2)
	}

	VECTORIZE_VEC(fastAcos)

	// atan
	template <typename T> 
	GLM_FUNC_QUALIFIER T fastAtan(T const & y, T const & x)
	{
		T sgn = sign(y) * sign(x);
		return abs(fastAtan(y / x)) * sgn;
	}

	VECTORIZE_VEC_VEC(fastAtan)

	template <typename T> 
	GLM_FUNC_QUALIFIER T fastAtan(T const & x)
	{
		return x - (x * x * x * T(0.333333333333)) + (x * x * x * x * x * T(0.2)) - (x * x * x * x * x * x * x * T(0.1428571429)) + (x * x * x * x * x * x * x * x * x * T(0.111111111111)) - (x * x * x * x * x * x * x * x * x * x * x * T(0.0909090909));
	}

	VECTORIZE_VEC(fastAtan)

}//namespace glm
