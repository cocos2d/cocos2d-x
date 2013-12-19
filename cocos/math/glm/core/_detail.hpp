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
/// @file glm/core/_detail.hpp
/// @date 2008-07-24 / 2011-06-14
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_detail
#define glm_core_detail

#include "setup.hpp"
#include <cassert>
#if(defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#include <cstdint>
#endif

namespace glm{
namespace detail
{
	class half;

#if(defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) // C99 detected, 64 bit types available
	typedef int64_t								sint64;
	typedef uint64_t							uint64;
#elif(GLM_COMPILER & GLM_COMPILER_VC)
	typedef signed __int64						sint64;
	typedef unsigned __int64					uint64;
#elif(GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_LLVM_GCC | GLM_COMPILER_CLANG))
	__extension__ typedef signed long long		sint64;
	__extension__ typedef unsigned long long	uint64;
#elif(GLM_COMPILER & GLM_COMPILER_BC)
	typedef Int64								sint64;
	typedef Uint64								uint64;
#else//unknown compiler
	typedef signed long	long					sint64;
	typedef unsigned long long					uint64;
#endif//GLM_COMPILER

	template<bool C>
	struct If
	{
		template<typename F, typename T>
		static GLM_FUNC_QUALIFIER T apply(F functor, const T& val)
		{
			return functor(val);
		}
	};

	template<>
	struct If<false>
	{
		template<typename F, typename T>
		static GLM_FUNC_QUALIFIER T apply(F, const T& val)
		{
			return val;
		}
	};

	//template <typename T>
	//struct traits
	//{
	//	static const bool is_signed = false;
	//	static const bool is_float = false;
	//	static const bool is_vector = false;
	//	static const bool is_matrix = false;
	//	static const bool is_genType = false;
	//	static const bool is_genIType = false;
	//	static const bool is_genUType = false;
	//};

	//template <>
	//struct traits<half>
	//{
	//	static const bool is_float = true;
	//	static const bool is_genType = true;
	//};

	//template <>
	//struct traits<float>
	//{
	//	static const bool is_float = true;
	//	static const bool is_genType = true;
	//};

	//template <>
	//struct traits<double>
	//{
	//	static const bool is_float = true;
	//	static const bool is_genType = true;
	//};

	//template <typename genType>
	//struct desc
	//{
	//	typedef genType							type;
	//	typedef genType *						pointer;
	//	typedef genType const*					const_pointer;
	//	typedef genType const *const			const_pointer_const;
	//	typedef genType *const					pointer_const;
	//	typedef genType &						reference;
	//	typedef genType const&					const_reference;
	//	typedef genType const&					param_type;

	//	typedef typename genType::value_type	value_type;
	//	typedef typename genType::size_type		size_type;
	//	static const typename size_type			value_size;
	//};

	//template <typename genType>
	//const typename desc<genType>::size_type desc<genType>::value_size = genType::value_size();

	union uif32
	{
		GLM_FUNC_QUALIFIER uif32() :
			i(0)
		{}

		GLM_FUNC_QUALIFIER uif32(float f) :
			f(f)
		{}

		GLM_FUNC_QUALIFIER uif32(unsigned int i) :
			i(i)
		{}

		float f;
		unsigned int i;
	};

	union uif64
	{
		GLM_FUNC_QUALIFIER uif64() :
			i(0)
		{}

		GLM_FUNC_QUALIFIER uif64(double f) :
			f(f)
		{}

		GLM_FUNC_QUALIFIER uif64(uint64 i) :
			i(i)
		{}

		double f;
		uint64 i;
	};

	typedef uif32 uif;

	//////////////////
	// int

	template <typename T>
	struct is_int
	{
		enum is_int_enum
		{
			_YES = 0,
			_NO = 1
		};
	};

#define GLM_DETAIL_IS_INT(T)	\
	template <>					\
	struct is_int<T>			\
	{							\
		enum is_int_enum		\
		{						\
			_YES = 1,			\
			_NO = 0				\
		};						\
	}

	//////////////////
	// uint

	template <typename T>
	struct is_uint
	{
		enum is_uint_enum
		{
			_YES = 0,
			_NO = 1
		};
	};

#define GLM_DETAIL_IS_UINT(T)	\
	template <>					\
	struct is_uint<T>			\
	{							\
		enum is_uint_enum		\
		{						\
			_YES = 1,			\
			_NO = 0				\
		};						\
	}

	//GLM_DETAIL_IS_UINT(unsigned long long)

	//////////////////
	// float

	template <typename T>
	struct is_float
	{
		enum is_float_enum
		{
			_YES = 0,
			_NO = 1
		};
	};

#define GLM_DETAIL_IS_FLOAT(T)	\
	template <>					\
	struct is_float<T>			\
	{							\
		enum is_float_enum		\
		{						\
			_YES = 1,			\
			_NO = 0				\
		};						\
	}

	GLM_DETAIL_IS_FLOAT(detail::half);
	GLM_DETAIL_IS_FLOAT(float);
	GLM_DETAIL_IS_FLOAT(double);
	GLM_DETAIL_IS_FLOAT(long double);

	//////////////////
	// bool

	template <typename T>
	struct is_bool
	{
		enum is_bool_enum
		{
			_YES = 0,
			_NO = 1
		};
	};
	
	template <>
	struct is_bool<bool>
	{
		enum is_bool_enum
		{
			_YES = 1,
			_NO = 0
		};
	};
	
	//////////////////
	// vector

	template <typename T>
	struct is_vector
	{
		enum is_vector_enum
		{
			_YES = 0,
			_NO = 1
		};
	};

#	define GLM_DETAIL_IS_VECTOR(TYPE) \
		template <typename T> \
		struct is_vector<TYPE<T> > \
		{ \
			enum is_vector_enum \
			{ \
				_YES = 1, \
				_NO = 0 \
			}; \
		}

	//////////////////
	// matrix

	template <typename T>
	struct is_matrix
	{
		enum is_matrix_enum
		{
			_YES = 0,
			_NO = 1
		};
	};

#define GLM_DETAIL_IS_MATRIX(T)	\
	template <>					\
	struct is_matrix			\
	{							\
		enum is_matrix_enum		\
		{						\
			_YES = 1,			\
			_NO = 0				\
		};						\
	}

	//////////////////
	// type

	template <typename T>
	struct type
	{
		enum type_enum
		{
			is_float = is_float<T>::_YES,
			is_int = is_int<T>::_YES,
			is_uint = is_uint<T>::_YES,
			is_bool = is_bool<T>::_YES
		};
	};
	
	//////////////////
	// type
	
	typedef signed char							int8;
	typedef signed short						int16;
	typedef signed int							int32;
	typedef detail::sint64						int64;
	
	typedef unsigned char						uint8;
	typedef unsigned short						uint16;
	typedef unsigned int						uint32;
	typedef detail::uint64						uint64;
	
	typedef detail::half						float16;
	typedef float								float32;
	typedef double								float64;
	
	//////////////////
	// float_or_int_trait 

	struct float_or_int_value
	{
		enum
		{
			GLM_ERROR,
			GLM_FLOAT,
			GLM_INT
		};
	};

	template <typename T>
	struct float_or_int_trait
	{
		enum{ID = float_or_int_value::GLM_ERROR};
	};

	template <>
	struct float_or_int_trait<int8>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<int16>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<int32>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<int64>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<uint8>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<uint16>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<uint32>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<uint64>
	{
		enum{ID = float_or_int_value::GLM_INT};
	};

	template <>
	struct float_or_int_trait<float16>
	{
		enum{ID = float_or_int_value::GLM_FLOAT};
	};

	template <>
	struct float_or_int_trait<float32>
	{
		enum{ID = float_or_int_value::GLM_FLOAT};
	};

	template <>
	struct float_or_int_trait<float64>
	{
		enum{ID = float_or_int_value::GLM_FLOAT};
	};

}//namespace detail
}//namespace glm

#if((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC2005))
#	define GLM_DEPRECATED __declspec(deprecated)
#	define GLM_ALIGN(x) __declspec(align(x)) 
#	define GLM_ALIGNED_STRUCT(x) __declspec(align(x)) struct 
#	define GLM_RESTRICT __declspec(restrict)
#	define GLM_RESTRICT_VAR __restrict
#	define GLM_CONSTEXPR 
#elif(GLM_COMPILER & GLM_COMPILER_INTEL)
#	define GLM_DEPRECATED
#	define GLM_ALIGN(x) __declspec(align(x))
#	define GLM_ALIGNED_STRUCT(x) __declspec(align(x)) struct
#	define GLM_RESTRICT
#	define GLM_RESTRICT_VAR __restrict
#	define GLM_CONSTEXPR
#elif(((GLM_COMPILER & (GLM_COMPILER_GCC | GLM_COMPILER_LLVM_GCC)) && (GLM_COMPILER >= GLM_COMPILER_GCC31)) || (GLM_COMPILER & GLM_COMPILER_CLANG))
#	define GLM_DEPRECATED __attribute__((__deprecated__))
#	define GLM_ALIGN(x) __attribute__((aligned(x)))
#	define GLM_ALIGNED_STRUCT(x) struct __attribute__((aligned(x)))
#	if(GLM_COMPILER >= GLM_COMPILER_GCC33)
#		define GLM_RESTRICT __restrict__
#		define GLM_RESTRICT_VAR __restrict__
#	else
#		define GLM_RESTRICT
#		define GLM_RESTRICT_VAR
#	endif
#	define GLM_RESTRICT __restrict__
#	define GLM_RESTRICT_VAR __restrict__
#	if((GLM_COMPILER >= GLM_COMPILER_GCC47) && ((GLM_LANG & GLM_LANG_CXX0X) == GLM_LANG_CXX0X))
#		define GLM_CONSTEXPR constexpr 
#	else
#		define GLM_CONSTEXPR 
#	endif
#else
#	define GLM_DEPRECATED
#	define GLM_ALIGN
#	define GLM_ALIGNED_STRUCT(x) 
#	define GLM_RESTRICT
#	define GLM_RESTRICT_VAR
#	define GLM_CONSTEXPR 
#endif//GLM_COMPILER

#endif//glm_core_detail
