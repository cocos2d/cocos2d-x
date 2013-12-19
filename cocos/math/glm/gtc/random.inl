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
/// @ref gtc_random
/// @file glm/gtc/random.inl
/// @date 2011-09-19 / 2012-04-07
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <cassert>

namespace glm{
namespace detail
{
	struct compute_linearRand
	{
		template <typename T>
		GLM_FUNC_QUALIFIER T operator() (T const & Min, T const & Max) const;
/*
		{
			GLM_STATIC_ASSERT(0, "'linearRand' invalid template parameter type. GLM_GTC_random only supports floating-point template types.");
			return Min;
		}
*/
	};
    
	template <>
	GLM_FUNC_QUALIFIER half compute_linearRand::operator()<half> (half const & Min, half const & Max) const
	{
		return half(float(std::rand()) / float(RAND_MAX) * (float(Max) - float(Min)) + float(Min));
	}

	template <>
	GLM_FUNC_QUALIFIER float compute_linearRand::operator()<float> (float const & Min, float const & Max) const
	{
		return float(std::rand()) / float(RAND_MAX) * (Max - Min) + Min;
	}

	template <>
	GLM_FUNC_QUALIFIER double compute_linearRand::operator()<double> (double const & Min, double const & Max) const
	{
		return double(std::rand()) / double(RAND_MAX) * (Max - Min) + Min;
	}
    
	template <>
	GLM_FUNC_QUALIFIER long double compute_linearRand::operator()<long double> (long double const & Min, long double const & Max) const
	{
		return (long double)(std::rand()) / (long double)(RAND_MAX) * (Max - Min) + Min;
	}
}//namespace detail

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType linearRand
	(
		genType const & Min, 
		genType const & Max
	)
	{
		return detail::compute_linearRand()(Min, Max);
	}

	VECTORIZE_VEC_VEC(linearRand)

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType gaussRand
	(
		genType const & Mean,	
		genType const & Deviation
	)
	{
		genType w, x1, x2;
	
		do
		{
			x1 = linearRand(genType(-1), genType(1));
			x2 = linearRand(genType(-1), genType(1));
		
			w = x1 * x1 + x2 * x2;
		} while(w > genType(1));
	
		return x2 * Deviation * Deviation * sqrt((genType(-2) * log(w)) / w) + Mean;
	}

	VECTORIZE_VEC_VEC(gaussRand)

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> diskRand
	(
		T const & Radius
	)
	{		
		detail::tvec2<T> Result(T(0));
		T LenRadius(T(0));
		
		do
		{
			Result = linearRand(detail::tvec2<T>(-Radius), detail::tvec2<T>(Radius));
			LenRadius = length(Result);
		}
		while(LenRadius > Radius);
		
		return Result;
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> ballRand
	(
		T const & Radius
	)
	{		
		detail::tvec3<T> Result(T(0));
		T LenRadius(T(0));
		
		do
		{
			Result = linearRand(detail::tvec3<T>(-Radius), detail::tvec3<T>(Radius));
			LenRadius = length(Result);
		}
		while(LenRadius > Radius);
		
		return Result;
	}
	
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec2<T> circularRand
	(
		T const & Radius
	)
	{
		T a = linearRand(T(0), T(6.283185307179586476925286766559f));
		return detail::tvec2<T>(cos(a), sin(a)) * Radius;		
	}
	
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> sphericalRand
	(
		T const & Radius
	)
	{
		T z = linearRand(T(-1), T(1));
		T a = linearRand(T(0), T(6.283185307179586476925286766559f));
	
		T r = sqrt(T(1) - z * z);
	
		T x = r * cos(a);
		T y = r * sin(a);
	
		return detail::tvec3<T>(x, y, z) * Radius;	
	}
}//namespace glm
