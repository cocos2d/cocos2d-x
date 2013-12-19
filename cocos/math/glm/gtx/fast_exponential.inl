///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-09
// Updated : 2006-01-09
// Licence : This source is under MIT License
// File    : glm/gtx/fast_exponential.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// fastPow:
	template <typename genType>
	GLM_FUNC_QUALIFIER genType fastPow(genType const & x, genType const & y)
	{
		return exp(y * log(x));
	}

	VECTORIZE_VEC_VEC(fastPow)

	template <typename T>
	GLM_FUNC_QUALIFIER T fastPow(const T x, int y)
	{
		T f = T(1);
		for(int i = 0; i < y; ++i)
			f *= x;
		return f;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> fastPow(
		const detail::tvec2<T>& x, 
		const detail::tvec2<int>& y)
	{
		return detail::tvec2<T>(
			fastPow(x.x, y.x),
			fastPow(x.y, y.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> fastPow(
		const detail::tvec3<T>& x, 
		const detail::tvec3<int>& y)
	{
		return detail::tvec3<T>(
			fastPow(x.x, y.x),
			fastPow(x.y, y.y),
			fastPow(x.z, y.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> fastPow(
		const detail::tvec4<T>& x, 
		const detail::tvec4<int>& y)
	{
		return detail::tvec4<T>(
			fastPow(x.x, y.x),
			fastPow(x.y, y.y),
			fastPow(x.z, y.z),
			fastPow(x.w, y.w));
	}

	// fastExp
	// Note: This function provides accurate results only for value between -1 and 1, else avoid it.
	template <typename T>
	GLM_FUNC_QUALIFIER T fastExp(const T x)
	{
		// This has a better looking and same performance in release mode than the following code. However, in debug mode it's slower.
		// return 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25 * (1.0f + x * 0.2f))));
		T x2 = x * x;
		T x3 = x2 * x;
		T x4 = x3 * x;
		T x5 = x4 * x;
		return T(1) + x + (x2 * T(0.5)) + (x3 * T(0.1666666667)) + (x4 * T(0.041666667)) + (x5 * T(0.008333333333));
	}
	/*  // Try to handle all values of float... but often shower than std::exp, glm::floor and the loop kill the performance
	GLM_FUNC_QUALIFIER float fastExp(float x)
	{
		const float e = 2.718281828f;
		const float IntegerPart = floor(x);
		const float FloatPart = x - IntegerPart;
		float z = 1.f;

		for(int i = 0; i < int(IntegerPart); ++i)
			z *= e;

		const float x2 = FloatPart * FloatPart;
		const float x3 = x2 * FloatPart;
		const float x4 = x3 * FloatPart;
		const float x5 = x4 * FloatPart;
		return z * (1.0f + FloatPart + (x2 * 0.5f) + (x3 * 0.1666666667f) + (x4 * 0.041666667f) + (x5 * 0.008333333333f));
	}

	// Increase accuracy on number bigger that 1 and smaller than -1 but it's not enough for high and negative numbers
	GLM_FUNC_QUALIFIER float fastExp(float x)
	{
		// This has a better looking and same performance in release mode than the following code. However, in debug mode it's slower.
		// return 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25 * (1.0f + x * 0.2f))));
		float x2 = x * x;
		float x3 = x2 * x;
		float x4 = x3 * x;
		float x5 = x4 * x;
		float x6 = x5 * x;
		float x7 = x6 * x;
		float x8 = x7 * x;
		return 1.0f + x + (x2 * 0.5f) + (x3 * 0.1666666667f) + (x4 * 0.041666667f) + (x5 * 0.008333333333f)+ (x6 * 0.00138888888888f) + (x7 * 0.000198412698f) + (x8 * 0.0000248015873f);;
	}
	*/

	VECTORIZE_VEC(fastExp)

	// fastLog
	template <typename genType>
	GLM_FUNC_QUALIFIER genType fastLog(genType const & x)
	{
		return std::log(x);
	}

	/* Slower than the VC7.1 function...
	GLM_FUNC_QUALIFIER float fastLog(float x)
	{
		float y1 = (x - 1.0f) / (x + 1.0f);
		float y2 = y1 * y1;
		return 2.0f * y1 * (1.0f + y2 * (0.3333333333f + y2 * (0.2f + y2 * 0.1428571429f)));
	}
	*/

	VECTORIZE_VEC(fastLog)

	//fastExp2, ln2 = 0.69314718055994530941723212145818f
	template <typename genType>
	GLM_FUNC_QUALIFIER genType fastExp2(genType const & x)
	{
		return fastExp(0.69314718055994530941723212145818f * x);
	}

	VECTORIZE_VEC(fastExp2)

	// fastLog2, ln2 = 0.69314718055994530941723212145818f
	template <typename genType>
	GLM_FUNC_QUALIFIER genType fastLog2(genType const & x)
	{
		return fastLog(x) / 0.69314718055994530941723212145818f;
	}

	VECTORIZE_VEC(fastLog2)

}//namespace glm
