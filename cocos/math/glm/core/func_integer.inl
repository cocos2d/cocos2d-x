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
/// @file glm/core/func_integer.inl
/// @date 2010-03-17 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#if(GLM_ARCH != GLM_ARCH_PURE)
#if(GLM_COMPILER & GLM_COMPILER_VC)
#	include <intrin.h>
#	pragma intrinsic(_BitScanReverse)
#endif//(GLM_COMPILER & GLM_COMPILER_VC)
#endif//(GLM_ARCH != GLM_ARCH_PURE)

namespace glm
{
	// uaddCarry
	template <typename genUType>
	GLM_FUNC_QUALIFIER genUType uaddCarry
	(
		genUType const & x, 
		genUType const & y, 
		genUType & Carry
	)
	{
		detail::highp_uint_t Value64 = detail::highp_uint_t(x) + detail::highp_uint_t(y);
		genUType Result = genUType(Value64 % (detail::highp_uint_t(1) << detail::highp_uint_t(32)));
		Carry = (Value64 % (detail::highp_uint_t(1) << detail::highp_uint_t(32))) > 1 ? 1 : 0;
		return Result;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> uaddCarry
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		detail::tvec2<T> & Carry
	)
	{
		return detail::tvec2<T>(
			uaddCarry(x[0], y[0], Carry[0]),
			uaddCarry(x[1], y[1], Carry[1]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> uaddCarry
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		detail::tvec3<T> & Carry
	)
	{
		return detail::tvec3<T>(
			uaddCarry(x[0], y[0], Carry[0]),
			uaddCarry(x[1], y[1], Carry[1]),
			uaddCarry(x[2], y[2], Carry[2]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> uaddCarry
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		detail::tvec4<T> & Carry
	)
	{
		return detail::tvec4<T>(
			uaddCarry(x[0], y[0], Carry[0]),
			uaddCarry(x[1], y[1], Carry[1]),
			uaddCarry(x[2], y[2], Carry[2]),
			uaddCarry(x[3], y[3], Carry[3]));
	}

	// usubBorrow
	template <typename genUType>
	GLM_FUNC_QUALIFIER genUType usubBorrow
	(
		genUType const & x, 
		genUType const & y, 
		genUType & Borrow
	)
	{
		Borrow = x >= y ? 0 : 1;
		if(x > y)
			return genUType(detail::highp_int_t(x) - detail::highp_int_t(y));
		else
			return genUType((detail::highp_int_t(1) << detail::highp_int_t(32)) + detail::highp_int_t(x) - detail::highp_int_t(y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> usubBorrow
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		detail::tvec2<T> & Borrow
	)
	{
		return detail::tvec2<T>(
			usubBorrow(x[0], y[0], Borrow[0]),
			usubBorrow(x[1], y[1], Borrow[1]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> usubBorrow
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		detail::tvec3<T> & Borrow
	)
	{
		return detail::tvec3<T>(
			usubBorrow(x[0], y[0], Borrow[0]),
			usubBorrow(x[1], y[1], Borrow[1]),
			usubBorrow(x[2], y[2], Borrow[2]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> usubBorrow
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		detail::tvec4<T> & Borrow
	)
	{
		return detail::tvec4<T>(
			usubBorrow(x[0], y[0], Borrow[0]),
			usubBorrow(x[1], y[1], Borrow[1]),
			usubBorrow(x[2], y[2], Borrow[2]),
			usubBorrow(x[3], y[3], Borrow[3]));
	}

	// umulExtended
	template <typename genUType>
	GLM_FUNC_QUALIFIER void umulExtended
	(
		genUType const & x, 
		genUType const & y, 
		genUType & msb, 
		genUType & lsb
	)
	{
		detail::highp_uint_t ValueX64 = x;
		detail::highp_uint_t ValueY64 = y;
		detail::highp_uint_t Value64 = ValueX64 * ValueY64;
		msb = *(genUType*)&genUType(Value64 & ((detail::highp_uint_t(1) << detail::highp_uint_t(32)) - detail::highp_uint_t(1)));
		lsb = *(genUType*)&genUType(Value64 >> detail::highp_uint_t(32));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> umulExtended
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		detail::tvec2<T> & msb, 
		detail::tvec2<T> & lsb
	)
	{
		return detail::tvec2<T>(
			umulExtended(x[0], y[0], msb, lsb),
			umulExtended(x[1], y[1], msb, lsb));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> umulExtended
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		detail::tvec3<T> & msb, 
		detail::tvec3<T> & lsb
	)
	{
		return detail::tvec3<T>(
			umulExtended(x[0], y[0], msb, lsb),
			umulExtended(x[1], y[1], msb, lsb),
			umulExtended(x[2], y[2], msb, lsb));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> umulExtended
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		detail::tvec4<T> & msb, 
		detail::tvec4<T> & lsb
	)
	{
		return detail::tvec4<T>(
			umulExtended(x[0], y[0], msb, lsb),
			umulExtended(x[1], y[1], msb, lsb),
			umulExtended(x[2], y[2], msb, lsb),
			umulExtended(x[3], y[3], msb, lsb));
	}

	// imulExtended
	template <typename genIType>
	GLM_FUNC_QUALIFIER void imulExtended
	(
		genIType const & x, 
		genIType const & y, 
		genIType & msb, 
		genIType & lsb
	)
	{
		detail::highp_int_t ValueX64 = x;
		detail::highp_int_t ValueY64 = y;
		detail::highp_int_t Value64 = ValueX64 * ValueY64;
		msb = *(genIType*)&genIType(Value64 & ((detail::highp_uint_t(1) << detail::highp_uint_t(32)) - detail::highp_uint_t(1)));
		lsb = *(genIType*)&genIType(Value64 >> detail::highp_uint_t(32));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> imulExtended
	(
		detail::tvec2<T> const & x, 
		detail::tvec2<T> const & y, 
		detail::tvec2<T> & msb, 
		detail::tvec2<T> & lsb
	)
	{
		return detail::tvec2<T>(
			imulExtended(x[0], y[0], msb, lsb),
			imulExtended(x[1], y[1], msb, lsb));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> imulExtended
	(
		detail::tvec3<T> const & x, 
		detail::tvec3<T> const & y, 
		detail::tvec3<T> & msb, 
		detail::tvec3<T> & lsb
	)
	{
		return detail::tvec3<T>(
			imulExtended(x[0], y[0], msb, lsb),
			imulExtended(x[1], y[1], msb, lsb),
			imulExtended(x[2], y[2], msb, lsb));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> imulExtended
	(
		detail::tvec4<T> const & x, 
		detail::tvec4<T> const & y, 
		detail::tvec4<T> & msb, 
		detail::tvec4<T> & lsb
	)
	{
		return detail::tvec4<T>(
			imulExtended(x[0], y[0], msb, lsb),
			imulExtended(x[1], y[1], msb, lsb),
			imulExtended(x[2], y[2], msb, lsb),
			imulExtended(x[3], y[3], msb, lsb));
	}

	// bitfieldExtract
	template <typename genIUType>
	GLM_FUNC_QUALIFIER genIUType bitfieldExtract
	(
		genIUType const & Value, 
		int const & Offset, 
		int const & Bits
	)
	{
		int GenSize = int(sizeof(genIUType)) << int(3);

		assert(Offset + Bits <= GenSize);

		genIUType ShiftLeft = Bits ? Value << (GenSize - (Bits + Offset)) : genIUType(0);
		genIUType ShiftBack = ShiftLeft >> genIUType(GenSize - Bits);

		return ShiftBack;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> bitfieldExtract
	(
		detail::tvec2<T> const & Value, 
		int const & Offset, 
		int const & Bits
	)
	{
		return detail::tvec2<T>(
			bitfieldExtract(Value[0], Offset, Bits),
			bitfieldExtract(Value[1], Offset, Bits));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> bitfieldExtract
	(
		detail::tvec3<T> const & Value, 
		int const & Offset, 
		int const & Bits
	)
	{
		return detail::tvec3<T>(
			bitfieldExtract(Value[0], Offset, Bits),
			bitfieldExtract(Value[1], Offset, Bits),
			bitfieldExtract(Value[2], Offset, Bits));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> bitfieldExtract
	(
		detail::tvec4<T> const & Value, 
		int const & Offset, 
		int const & Bits
	)
	{
		return detail::tvec4<T>(
			bitfieldExtract(Value[0], Offset, Bits),
			bitfieldExtract(Value[1], Offset, Bits),
			bitfieldExtract(Value[2], Offset, Bits),
			bitfieldExtract(Value[3], Offset, Bits));
	}

	// bitfieldInsert
	template <typename genIUType>
	GLM_FUNC_QUALIFIER genIUType bitfieldInsert
	(
		genIUType const & Base, 
		genIUType const & Insert, 
		int const & Offset, 
		int const & Bits
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldInsert' only accept integer values");
		assert(Offset + Bits <= sizeof(genIUType));

		if(Bits == 0)
			return Base;

		genIUType Mask = 0;
		for(int Bit = Offset; Bit < Offset + Bits; ++Bit)
			Mask |= (1 << Bit);

		return (Base & ~Mask) | (Insert & Mask);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> bitfieldInsert
	(
		detail::tvec2<T> const & Base, 
		detail::tvec2<T> const & Insert, 
		int const & Offset, 
		int const & Bits
	)
	{
		return detail::tvec2<T>(
			bitfieldInsert(Base[0], Insert[0], Offset, Bits),
			bitfieldInsert(Base[1], Insert[1], Offset, Bits));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> bitfieldInsert
	(
		detail::tvec3<T> const & Base, 
		detail::tvec3<T> const & Insert, 
		int const & Offset, 
		int const & Bits
	)
	{
		return detail::tvec3<T>(
			bitfieldInsert(Base[0], Insert[0], Offset, Bits),
			bitfieldInsert(Base[1], Insert[1], Offset, Bits),
			bitfieldInsert(Base[2], Insert[2], Offset, Bits));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> bitfieldInsert
	(
		detail::tvec4<T> const & Base, 
		detail::tvec4<T> const & Insert, 
		int const & Offset, 
		int const & Bits
	)
	{
		return detail::tvec4<T>(
			bitfieldInsert(Base[0], Insert[0], Offset, Bits),
			bitfieldInsert(Base[1], Insert[1], Offset, Bits),
			bitfieldInsert(Base[2], Insert[2], Offset, Bits),
			bitfieldInsert(Base[3], Insert[3], Offset, Bits));
	}

	// bitfieldReverse
	template <typename genIUType>
	GLM_FUNC_QUALIFIER genIUType bitfieldReverse(genIUType const & Value)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldReverse' only accept integer values");

		genIUType Out = 0;
		std::size_t BitSize = sizeof(genIUType) * 8;
		for(std::size_t i = 0; i < BitSize; ++i)
			if(Value & (genIUType(1) << i))
				Out |= genIUType(1) << (BitSize - 1 - i);
		return Out;
	}	

	VECTORIZE_VEC(bitfieldReverse)

	// bitCount
	template <typename genIUType>
	GLM_FUNC_QUALIFIER int bitCount(genIUType const & Value)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitCount' only accept integer values");

		int Count = 0;
		for(std::size_t i = 0; i < sizeof(genIUType) * std::size_t(8); ++i)
		{
			if(Value & (1 << i))
				++Count;
		}
		return Count;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<int> bitCount
	(
		detail::tvec2<T> const & value
	)
	{
		return detail::tvec2<int>(
			bitCount(value[0]),
			bitCount(value[1]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<int> bitCount
	(
		detail::tvec3<T> const & value
	)
	{
		return detail::tvec3<int>(
			bitCount(value[0]),
			bitCount(value[1]),
			bitCount(value[2]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<int> bitCount
	(
		detail::tvec4<T> const & value
	)
	{
		return detail::tvec4<int>(
			bitCount(value[0]),
			bitCount(value[1]),
			bitCount(value[2]),
			bitCount(value[3]));
	}

	// findLSB
	template <typename genIUType>
	GLM_FUNC_QUALIFIER int findLSB
	(
		genIUType const & Value
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findLSB' only accept integer values");
		if(Value == 0)
			return -1;

		genIUType Bit;
		for(Bit = genIUType(0); !(Value & (1 << Bit)); ++Bit){}
		return Bit;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<int> findLSB
	(
		detail::tvec2<T> const & value
	)
	{
		return detail::tvec2<int>(
			findLSB(value[0]),
			findLSB(value[1]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<int> findLSB
	(
		detail::tvec3<T> const & value
	)
	{
		return detail::tvec3<int>(
			findLSB(value[0]),
			findLSB(value[1]),
			findLSB(value[2]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<int> findLSB
	(
		detail::tvec4<T> const & value
	)
	{
		return detail::tvec4<int>(
			findLSB(value[0]),
			findLSB(value[1]),
			findLSB(value[2]),
			findLSB(value[3]));
	}

	// findMSB
#if((GLM_ARCH != GLM_ARCH_PURE) && (GLM_COMPILER & GLM_COMPILER_VC))

	template <typename genIUType>
	GLM_FUNC_QUALIFIER int findMSB
	(
		genIUType const & Value
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findMSB' only accept integer values");
		if(Value == 0)
			return -1;

		unsigned long Result(0);
		_BitScanReverse(&Result, Value); 
		return int(Result);
	}
/*
// __builtin_clz seems to be buggy as it crasks for some values, from 0x00200000 to 80000000
#elif((GLM_ARCH != GLM_ARCH_PURE) && (GLM_COMPILER & GLM_COMPILER_GCC) && (GLM_COMPILER >= GLM_COMPILER_GCC40))

	template <typename genIUType>
	GLM_FUNC_QUALIFIER int findMSB
	(
		genIUType const & Value
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findMSB' only accept integer values");
		if(Value == 0)
			return -1;

		// clz returns the number or trailing 0-bits; see
		// http://gcc.gnu.org/onlinedocs/gcc-4.7.1/gcc/Other-Builtins.html
		//
		// NoteBecause __builtin_clz only works for unsigned ints, this
		// implementation will not work for 64-bit integers.
		//
		return 31 - __builtin_clzl(Value);
	}
*/
#else

/* SSE implementation idea

		__m128i const Zero = _mm_set_epi32( 0,  0,  0,  0);
		__m128i const One = _mm_set_epi32( 1,  1,  1,  1);
		__m128i Bit = _mm_set_epi32(-1, -1, -1, -1);
		__m128i Tmp = _mm_set_epi32(Value, Value, Value, Value);
		__m128i Mmi = Zero;
		for(int i = 0; i < 32; ++i)
		{
			__m128i Shilt = _mm_and_si128(_mm_cmpgt_epi32(Tmp, One), One);
			Tmp = _mm_srai_epi32(Tmp, One);
			Bit = _mm_add_epi32(Bit, _mm_and_si128(Shilt, i));
			Mmi = _mm_and_si128(Mmi, One);
		}
		return Bit;

*/

	template <typename genIUType>
	GLM_FUNC_QUALIFIER int findMSB
	(
		genIUType const & Value
	)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findMSB' only accept integer values");
		
		if(Value == genIUType(0) || Value == genIUType(-1))
			return -1;
		else if(Value > 0)
		{
			genIUType Bit = genIUType(-1);
			for(genIUType tmp = Value; tmp > 0; tmp >>= 1, ++Bit){}
			return Bit;
		}
		else //if(Value < 0)
		{
			int const BitCount(sizeof(genIUType) * 8);
			int MostSignificantBit(-1);
			for(int BitIndex(0); BitIndex < BitCount; ++BitIndex)
				MostSignificantBit = (Value & (1 << BitIndex)) ? MostSignificantBit : BitIndex;
			assert(MostSignificantBit >= 0);
			return MostSignificantBit;
		}
	}
#endif//(GLM_COMPILER)

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<int> findMSB
	(
		detail::tvec2<T> const & value
	)
	{
		return detail::tvec2<int>(
			findMSB(value[0]),
			findMSB(value[1]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<int> findMSB
	(
		detail::tvec3<T> const & value
	)
	{
		return detail::tvec3<int>(
			findMSB(value[0]),
			findMSB(value[1]),
			findMSB(value[2]));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<int> findMSB
	(
		detail::tvec4<T> const & value
	)
	{
		return detail::tvec4<int>(
			findMSB(value[0]),
			findMSB(value[1]),
			findMSB(value[2]),
			findMSB(value[3]));
	}
}//namespace glm
