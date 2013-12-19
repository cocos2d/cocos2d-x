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
/// @file glm/core/func_common.inl
/// @date 2008-08-03 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename genFIType, bool /*signed*/>
	struct Abs_
	{};

	template <typename genFIType>
	struct Abs_<genFIType, true>
	{
		GLM_FUNC_QUALIFIER static genFIType get(genFIType const & x)
		{
			GLM_STATIC_ASSERT(
				detail::type<genFIType>::is_float || 
				detail::type<genFIType>::is_int, "'abs' only accept floating-point and integer inputs");
			return x >= genFIType(0) ? x : -x;
			// TODO, perf comp with: *(((int *) &x) + 1) &= 0x7fffffff;
		}
	};

	template <typename genFIType>
	struct Abs_<genFIType, false>
	{
		GLM_FUNC_QUALIFIER static genFIType get(genFIType const & x)
		{
			GLM_STATIC_ASSERT(
					detail::type<genFIType>::is_uint, "'abs' only accept floating-point and integer inputs");
			return x;
		}
	};
}//namespace detail

	// abs
	template <typename genFIType>
	GLM_FUNC_QUALIFIER genFIType abs
	(
		genFIType const & x
	)
	{
		return detail::Abs_<genFIType, std::numeric_limits<genFIType>::is_signed>::get(x);
	}

	VECTORIZE_VEC(abs)

	// sign
	//Try something like based on x >> 31 to get the sign bit
	template <typename genFIType> 
	GLM_FUNC_QUALIFIER genFIType sign
	(
		genFIType const & x
	)
	{
		GLM_STATIC_ASSERT(
			detail::type<genFIType>::is_float || 
			detail::type<genFIType>::is_int, "'sign' only accept signed inputs");

		genFIType result;
		if(x > genFIType(0))
			result = genFIType(1);
		else if(x < genFIType(0))
			result = genFIType(-1);
		else
			result = genFIType(0);
		return result;
	}
	
	VECTORIZE_VEC(sign)

	// floor
	template <>
	GLM_FUNC_QUALIFIER detail::half floor<detail::half>(detail::half const & x)
	{
		return detail::half(::std::floor(float(x)));
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType floor(genType const & x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'floor' only accept floating-point inputs");

		return ::std::floor(x);
	}

	VECTORIZE_VEC(floor)

	// trunc
	template <typename genType>
	GLM_FUNC_QUALIFIER genType trunc(genType const & x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'trunc' only accept floating-point inputs");
		return x < 0 ? -floor(-x) : floor(x);
	}

	VECTORIZE_VEC(trunc)

	// round
	template <typename genType>
	GLM_FUNC_QUALIFIER genType round(genType const& x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'round' only accept floating-point inputs");

		if(x < 0)
			return genType(int(x - genType(0.5)));
		return genType(int(x + genType(0.5)));
	}

	VECTORIZE_VEC(round)

/*
	// roundEven
	template <typename genType>
	GLM_FUNC_QUALIFIER genType roundEven(genType const& x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'roundEven' only accept floating-point inputs");

		return genType(int(x + genType(int(x) % 2)));
	}
*/
	
	// roundEven
	template <typename genType>
	GLM_FUNC_QUALIFIER genType roundEven(genType const & x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'roundEven' only accept floating-point inputs");
		
		int Integer = int(x);
		genType IntegerPart = genType(Integer);
		genType FractionalPart = fract(x);

		if(FractionalPart > genType(0.5) || FractionalPart < genType(0.5))
		{
			return round(x);
		}
		else if((Integer % 2) == 0)
		{
			return IntegerPart;
		}
		else if(x <= genType(0)) // Work around... 
		{
			return IntegerPart - 1;
		}
		else
		{
			return IntegerPart + 1;
		}
		//else // Bug on MinGW 4.5.2
		//{
		//	return mix(IntegerPart + genType(-1), IntegerPart + genType(1), x <= genType(0));
		//}
	}
	
	VECTORIZE_VEC(roundEven)

	// ceil
	template <typename genType>
	GLM_FUNC_QUALIFIER genType ceil(genType const & x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'ceil' only accept floating-point inputs");

		return ::std::ceil(x);
	}

	VECTORIZE_VEC(ceil)

	// fract
	template <typename genType>
	GLM_FUNC_QUALIFIER genType fract
	(
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'fract' only accept floating-point inputs");

		return x - ::std::floor(x);
	}

	VECTORIZE_VEC(fract)

	// mod
	template <typename genType>
	GLM_FUNC_QUALIFIER genType mod
	(
		genType const & x, 
		genType const & y
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'mod' only accept floating-point inputs");

		return x - y * floor(x / y);
	}

	VECTORIZE_VEC_SCA(mod)
	VECTORIZE_VEC_VEC(mod)

	// modf
	template <typename genType>
	GLM_FUNC_QUALIFIER genType modf
	(
		genType const & x, 
		genType & i
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'modf' only accept floating-point inputs");

		return std::modf(x, &i);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<valType> modf
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> & i
	)
	{
		return detail::tvec2<valType>(
			modf(x.x, i.x),
			modf(x.y, i.y));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<valType> modf
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> & i
	)
	{
		return detail::tvec3<valType>(
			modf(x.x, i.x),
			modf(x.y, i.y),
			modf(x.z, i.z));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<valType> modf
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> & i
	)
	{
		return detail::tvec4<valType>(
			modf(x.x, i.x),
			modf(x.y, i.y),
			modf(x.z, i.z),
			modf(x.w, i.w));
	}

	//// Only valid if (INT_MIN <= x-y <= INT_MAX)
	//// min(x,y)
	//r = y + ((x - y) & ((x - y) >> (sizeof(int) *
	//CHAR_BIT - 1)));
	//// max(x,y)
	//r = x - ((x - y) & ((x - y) >> (sizeof(int) *
	//CHAR_BIT - 1)));

	// min
	template <typename genType>
	GLM_FUNC_QUALIFIER genType min
	(
		genType const & x, 
		genType const & y
	)
	{
		GLM_STATIC_ASSERT(
			detail::type<genType>::is_float || 
			detail::type<genType>::is_int ||
			detail::type<genType>::is_uint, "'min' only accept numbers");

		return x < y ? x : y;
	}

	VECTORIZE_VEC_SCA(min)
	VECTORIZE_VEC_VEC(min)

	// max
	template <typename genType>
	GLM_FUNC_QUALIFIER genType max
	(
		genType const & x, 
		genType const & y
	)
	{
		GLM_STATIC_ASSERT(
			detail::type<genType>::is_float || 
			detail::type<genType>::is_int ||
			detail::type<genType>::is_uint, "'max' only accept numbers");

		return x > y ? x : y;
	}

	VECTORIZE_VEC_SCA(max)
	VECTORIZE_VEC_VEC(max)

	// clamp
	template <typename valType>
	GLM_FUNC_QUALIFIER valType clamp
	(
		valType const & x, 
		valType const & minVal, 
		valType const & maxVal
	)
	{
		GLM_STATIC_ASSERT(
			detail::type<valType>::is_float || 
			detail::type<valType>::is_int ||
			detail::type<valType>::is_uint, "'clamp' only accept numbers");
		
		return min(maxVal, max(minVal, x));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> clamp
	(
		detail::tvec2<T> const & x, 
		typename detail::tvec2<T>::value_type const & minVal, 
		typename detail::tvec2<T>::value_type const & maxVal
	)
	{
		return detail::tvec2<T>(
			clamp(x.x, minVal, maxVal),
			clamp(x.y, minVal, maxVal));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> clamp
	(
		detail::tvec3<T> const & x, 
		typename detail::tvec3<T>::value_type const & minVal, 
		typename detail::tvec3<T>::value_type const & maxVal
	)
	{
		return detail::tvec3<T>(
			clamp(x.x, minVal, maxVal),
			clamp(x.y, minVal, maxVal),
			clamp(x.z, minVal, maxVal));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> clamp
	(
		detail::tvec4<T> const & x, 
		typename detail::tvec4<T>::value_type const & minVal, 
		typename detail::tvec4<T>::value_type const & maxVal
	)
	{
		return detail::tvec4<T>(
			clamp(x.x, minVal, maxVal),
			clamp(x.y, minVal, maxVal),
			clamp(x.z, minVal, maxVal),
			clamp(x.w, minVal, maxVal));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> clamp
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & minVal, 
		detail::tvec2<T> const & maxVal
	)
	{
		return detail::tvec2<T>(
			clamp(x.x, minVal.x, maxVal.x),
			clamp(x.y, minVal.y, maxVal.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> clamp
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & minVal, 
		detail::tvec3<T> const & maxVal
	)
	{
		return detail::tvec3<T>(
			clamp(x.x, minVal.x, maxVal.x),
			clamp(x.y, minVal.y, maxVal.y),
			clamp(x.z, minVal.z, maxVal.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> clamp
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & minVal, 
		detail::tvec4<T> const & maxVal
	)
	{
		return detail::tvec4<T>(
			clamp(x.x, minVal.x, maxVal.x),
			clamp(x.y, minVal.y, maxVal.y),
			clamp(x.z, minVal.z, maxVal.z),
			clamp(x.w, minVal.w, maxVal.w));
	}

	// mix
	template <typename genType>
	GLM_FUNC_QUALIFIER genType mix
	(
		genType const & x, 
		genType const & y, 
		genType const & a
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float , "'genType' is not floating-point type");

		return x + a * (y - x);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<valType> mix
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y, 
		valType const & a
	)
	{
		GLM_STATIC_ASSERT(detail::type<valType>::is_float , "'genType' is not floating-point type");

		return x + a * (y - x);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<valType> mix
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y, 
		valType const & a
	)
	{
		return x + a * (y - x);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<valType> mix
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y, 
		valType const & a
	)
	{
		return x + a * (y - x);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<valType> mix
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y, 
		detail::tvec2<valType> const & a
	)
	{
		return x + a * (y - x);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<valType> mix
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y, 
		detail::tvec3<valType> const & a
	)
	{
		GLM_STATIC_ASSERT(detail::type<valType>::is_float , "'genType' is not floating-point type");

		return x + a * (y - x);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<valType> mix
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y, 
		detail::tvec4<valType> const & a
	)
	{
		return x + a * (y - x);
	}

	//template <typename genTypeT>
	//GLM_FUNC_QUALIFIER genTypeT mix
	//(
	//	genTypeT const & x, 
	//	genTypeT const & y, 
	//	float const & a
	//)
	//{
	//	// It could be a vector too
	//	//GLM_STATIC_ASSERT(
	//	//	detail::type<genTypeT>::is_float && 
	//	//	detail::type<genTypeU>::is_float);

	//	return x + a * (y - x);
	//}

	template <>
	GLM_FUNC_QUALIFIER float mix
	(
		float const & x, 
		float const & y, 
		bool const & a
	)
	{
		return a ? y : x;
	}

	template <>
	GLM_FUNC_QUALIFIER double mix
	(
		double const & x, 
		double const & y, 
		bool const & a
	)
	{
		return a ? y : x;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> mix
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		bool a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		return a ? y : x;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> mix
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		bool a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		return a ? y : x;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> mix
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		bool a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		return a ? y : x;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> mix
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		typename detail::tvec2<T>::bool_type a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		detail::tvec2<T> result;
		for
		(
			typename detail::tvec2<T>::size_type i = 0; 
			i < x.length(); ++i
		)
		{
			result[i] = a[i] ? y[i] : x[i];
		}
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> mix
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		typename detail::tvec3<T>::bool_type a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		detail::tvec3<T> result;
		for
		(
			typename detail::tvec3<T>::size_type i = 0; 
			i < x.length(); ++i
		)
		{
			result[i] = a[i] ? y[i] : x[i];
		}
		return result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> mix
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		typename detail::tvec4<T>::bool_type a
	)
	{
		GLM_STATIC_ASSERT(detail::type<T>::is_float, "'mix' only accept floating-point inputs");

		detail::tvec4<T> result;
		for
		(
			typename detail::tvec4<T>::size_type i = 0; 
			i < x.length(); ++i
		)
		{
			result[i] = a[i] ? y[i] : x[i];
		}
		return result;
	}

	// step
	template <typename genType>
	GLM_FUNC_QUALIFIER genType step
	(
		genType const & edge, 
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'step' only accept floating-point inputs");

		return x < edge ? genType(0) : genType(1);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> step
	(
		typename detail::tvec2<T>::value_type const & edge, 
		detail::tvec2<T> const & x
	)
	{
		return detail::tvec2<T>(
			x.x < edge ? T(0) : T(1),
			x.y < edge ? T(0) : T(1));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> step
	(
		typename detail::tvec3<T>::value_type const & edge, 
		detail::tvec3<T> const & x
	)
	{
		return detail::tvec3<T>(
			x.x < edge ? T(0) : T(1),
			x.y < edge ? T(0) : T(1),
			x.z < edge ? T(0) : T(1));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> step
	(
		typename detail::tvec4<T>::value_type const & edge, 
		detail::tvec4<T> const & x
	)
	{
		return detail::tvec4<T>(
			x.x < edge ? T(0) : T(1),
			x.y < edge ? T(0) : T(1),
			x.z < edge ? T(0) : T(1),
			x.w < edge ? T(0) : T(1));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> step
	(
		detail::tvec2<T> const & edge, 
		detail::tvec2<T> const & x
	)
	{
		return detail::tvec2<T>(
			x.x < edge.x ? T(0) : T(1),
			x.y < edge.y ? T(0) : T(1));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> step
	(
		detail::tvec3<T> const & edge, 
		detail::tvec3<T> const & x
	)
	{
		return detail::tvec3<T>(
			x.x < edge.x ? T(0) : T(1),
			x.y < edge.y ? T(0) : T(1),
			x.z < edge.z ? T(0) : T(1));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> step
	(
		detail::tvec4<T> const & edge, 
		detail::tvec4<T> const & x
	)
	{
		return detail::tvec4<T>(
			x.x < edge.x ? T(0) : T(1),
			x.y < edge.y ? T(0) : T(1),
			x.z < edge.z ? T(0) : T(1),
			x.w < edge.w ? T(0) : T(1));
	}

	// smoothstep
	template <typename genType>
	GLM_FUNC_QUALIFIER genType smoothstep
	(
		genType const & edge0, 
		genType const & edge1, 
		genType const & x
	)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'smoothstep' only accept floating-point inputs");

		genType tmp = clamp((x - edge0) / (edge1 - edge0), genType(0), genType(1));
		return tmp * tmp * (genType(3) - genType(2) * tmp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> smoothstep
	(
		typename detail::tvec2<T>::value_type const & edge0, 
		typename detail::tvec2<T>::value_type const & edge1, 
		detail::tvec2<T> const & x
	)
	{
		return detail::tvec2<T>(
			smoothstep(edge0, edge1, x.x),
			smoothstep(edge0, edge1, x.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> smoothstep
	(
		typename detail::tvec3<T>::value_type const & edge0, 
		typename detail::tvec3<T>::value_type const & edge1, 
		detail::tvec3<T> const & x
	)
	{
		return detail::tvec3<T>(
			smoothstep(edge0, edge1, x.x),
			smoothstep(edge0, edge1, x.y),
			smoothstep(edge0, edge1, x.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> smoothstep
	(
		typename detail::tvec4<T>::value_type const & edge0, 
		typename detail::tvec4<T>::value_type const & edge1, 
		detail::tvec4<T> const & x
	)
	{
		return detail::tvec4<T>(
			smoothstep(edge0, edge1, x.x),
			smoothstep(edge0, edge1, x.y),
			smoothstep(edge0, edge1, x.z),
			smoothstep(edge0, edge1, x.w));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> smoothstep
	(
		detail::tvec2<T> const & edge0, 
		detail::tvec2<T> const & edge1, 
		detail::tvec2<T> const & x
	)
	{
		return detail::tvec2<T>(
			smoothstep(edge0.x, edge1.x, x.x),
			smoothstep(edge0.y, edge1.y, x.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> smoothstep
	(
		detail::tvec3<T> const & edge0, 
		detail::tvec3<T> const & edge1, 
		detail::tvec3<T> const & x
	)
	{
		return detail::tvec3<T>(
			smoothstep(edge0.x, edge1.x, x.x),
			smoothstep(edge0.y, edge1.y, x.y),
			smoothstep(edge0.z, edge1.z, x.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> smoothstep
	(
		detail::tvec4<T> const & edge0, 
		detail::tvec4<T> const & edge1, 
		detail::tvec4<T> const & x
	)
	{
		return detail::tvec4<T>(
			smoothstep(edge0.x, edge1.x, x.x),
			smoothstep(edge0.y, edge1.y, x.y),
			smoothstep(edge0.z, edge1.z, x.z),
			smoothstep(edge0.w, edge1.w, x.w));
	}

	// TODO: Not working on MinGW...
	template <typename genType> 
	GLM_FUNC_QUALIFIER bool isnan(genType const & x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'isnan' only accept floating-point inputs");

#		if(GLM_COMPILER & (GLM_COMPILER_VC | GLM_COMPILER_INTEL))
			return _isnan(x) != 0;
#		elif(GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_CLANG))
#			if(GLM_PLATFORM & GLM_PLATFORM_ANDROID)
				return _isnan(x) != 0;
#			else
				return std::isnan(x);
#			endif
#		elif(GLM_COMPILER & GLM_COMPILER_CUDA)
			return isnan(x) != 0;
#		else
			return std::isnan(x);
#		endif
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tvec2<T>::bool_type isnan
	(
		detail::tvec2<T> const & x
	)
	{
		return typename detail::tvec2<T>::bool_type(
			isnan(x.x),
			isnan(x.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tvec3<T>::bool_type isnan
	(
		detail::tvec3<T> const & x
	)
	{
		return typename detail::tvec3<T>::bool_type(
			isnan(x.x),
			isnan(x.y),
			isnan(x.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tvec4<T>::bool_type isnan
	(
		detail::tvec4<T> const & x
	)
	{
		return typename detail::tvec4<T>::bool_type(
			isnan(x.x),
			isnan(x.y),
			isnan(x.z),
			isnan(x.w));
	}

	template <typename genType> 
	GLM_FUNC_QUALIFIER bool isinf(
		genType const & x)
	{
		GLM_STATIC_ASSERT(detail::type<genType>::is_float, "'isinf' only accept floating-point inputs");

#		if(GLM_COMPILER & (GLM_COMPILER_INTEL | GLM_COMPILER_VC))
			return _fpclass(x) == _FPCLASS_NINF || _fpclass(x) == _FPCLASS_PINF;
#		elif(GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_CLANG))
#			if(GLM_PLATFORM & GLM_PLATFORM_ANDROID)
				return _isinf(x) != 0;
#			else
				return std::isinf(x);
#			endif
#		elif(GLM_COMPILER & GLM_COMPILER_CUDA)
			// http://developer.download.nvidia.com/compute/cuda/4_2/rel/toolkit/docs/online/group__CUDA__MATH__DOUBLE_g13431dd2b40b51f9139cbb7f50c18fab.html#g13431dd2b40b51f9139cbb7f50c18fab
			return isinf(double(x)) != 0;
#		else
			return std::isinf(x);
#		endif
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tvec2<T>::bool_type isinf
	(
		detail::tvec2<T> const & x
	)
	{
		return typename detail::tvec2<T>::bool_type(
			isinf(x.x),
			isinf(x.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tvec3<T>::bool_type isinf
	(
		detail::tvec3<T> const & x
	)
	{
		return typename detail::tvec3<T>::bool_type(
			isinf(x.x),
			isinf(x.y),
			isinf(x.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename detail::tvec4<T>::bool_type isinf
	(
		detail::tvec4<T> const & x
	)
	{
		return typename detail::tvec4<T>::bool_type(
			isinf(x.x),
			isinf(x.y),
			isinf(x.z),
			isinf(x.w));
	}

	GLM_FUNC_QUALIFIER int floatBitsToInt(float const & value)
	{
		union
		{
			float f;
			int i;
		} fi;

		fi.f = value;
		return fi.i;
	}

	GLM_FUNC_QUALIFIER detail::tvec2<int> floatBitsToInt
	(
		detail::tvec2<float> const & value
	)
	{
		return detail::tvec2<int>(
			floatBitsToInt(value.x),
			floatBitsToInt(value.y));
	}

	GLM_FUNC_QUALIFIER detail::tvec3<int> floatBitsToInt
	(
		detail::tvec3<float> const & value
	)
	{
		return detail::tvec3<int>(
			floatBitsToInt(value.x),
			floatBitsToInt(value.y),
			floatBitsToInt(value.z));
	}

	GLM_FUNC_QUALIFIER detail::tvec4<int> floatBitsToInt
	(
		detail::tvec4<float> const & value
	)
	{
		return detail::tvec4<int>(
			floatBitsToInt(value.x),
			floatBitsToInt(value.y),
			floatBitsToInt(value.z),
			floatBitsToInt(value.w));
	}

	GLM_FUNC_QUALIFIER uint floatBitsToUint(float const & value)
	{
		union
		{
			float f;
			uint u;
		} fu;

		fu.f = value;
		return fu.u;
	}

	GLM_FUNC_QUALIFIER detail::tvec2<uint> floatBitsToUint
	(
		detail::tvec2<float> const & value
	)
	{
		return detail::tvec2<uint>(
			floatBitsToUint(value.x),
			floatBitsToUint(value.y));
	}

	GLM_FUNC_QUALIFIER detail::tvec3<uint> floatBitsToUint
	(
		detail::tvec3<float> const & value
	)
	{
		return detail::tvec3<uint>(
			floatBitsToUint(value.x),
			floatBitsToUint(value.y),
			floatBitsToUint(value.z));
	}

	GLM_FUNC_QUALIFIER detail::tvec4<uint> floatBitsToUint
	(
		detail::tvec4<float> const & value
	)
	{
		return detail::tvec4<uint>(
			floatBitsToUint(value.x),
			floatBitsToUint(value.y),
			floatBitsToUint(value.z),
			floatBitsToUint(value.w));
	}

	GLM_FUNC_QUALIFIER float intBitsToFloat(int const & value)
	{
		union
		{
			float f;
			int i;
		} fi;

		fi.i = value;
		return fi.f;
	}

	GLM_FUNC_QUALIFIER detail::tvec2<float> intBitsToFloat

	(
		detail::tvec2<int> const & value
	)
	{
		return detail::tvec2<float>(
			intBitsToFloat(value.x),
			intBitsToFloat(value.y));
	}

	GLM_FUNC_QUALIFIER detail::tvec3<float> intBitsToFloat
	(
		detail::tvec3<int> const & value
	)
	{
		return detail::tvec3<float>(
			intBitsToFloat(value.x),
			intBitsToFloat(value.y),
			intBitsToFloat(value.z));
	}

	GLM_FUNC_QUALIFIER detail::tvec4<float> intBitsToFloat
	(
		detail::tvec4<int> const & value
	)
	{
		return detail::tvec4<float>(
			intBitsToFloat(value.x),
			intBitsToFloat(value.y),
			intBitsToFloat(value.z),
			intBitsToFloat(value.w));
	}

	GLM_FUNC_QUALIFIER float uintBitsToFloat(uint const & value)
	{
		union
		{
			float f;
			uint u;
		} fu;

		fu.u = value;
		return fu.f;
	}

	GLM_FUNC_QUALIFIER detail::tvec2<float> uintBitsToFloat
	(
		detail::tvec2<uint> const & value
	)
	{
		return detail::tvec2<float>(
			uintBitsToFloat(value.x),
			uintBitsToFloat(value.y));
	}

	GLM_FUNC_QUALIFIER detail::tvec3<float> uintBitsToFloat
	(
		detail::tvec3<uint> const & value
	)
	{
		return detail::tvec3<float>(
			uintBitsToFloat(value.x),
			uintBitsToFloat(value.y),
			uintBitsToFloat(value.z));
	}

	GLM_FUNC_QUALIFIER detail::tvec4<float> uintBitsToFloat
	(
		detail::tvec4<uint> const & value
	)
	{
		return detail::tvec4<float>(
			uintBitsToFloat(value.x),
			uintBitsToFloat(value.y),
			uintBitsToFloat(value.z),
			uintBitsToFloat(value.w));
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType fma
	(
		genType const & a, 
		genType const & b, 
		genType const & c
	)
	{
		return a * b + c;
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType frexp
	(
		genType const & x, 
		int & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> frexp
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<int> & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> frexp
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<int> & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> frexp
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<int> & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType ldexp
	(
		genType const & x, 
		int const & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> ldexp
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<int> const & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> ldexp
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<int> const & exp
	)
	{
		return std::frexp(x, exp);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> ldexp
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<int> const & exp
	)
	{
		return std::frexp(x, exp);
	}

}//namespace glm
