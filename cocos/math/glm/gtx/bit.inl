///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-14
// Updated : 2008-11-14
// Licence : This source is under MIT License
// File    : glm/gtx/bit.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genIType>
	GLM_FUNC_QUALIFIER genIType mask
	(
		genIType const & count
	)
	{
		return ((genIType(1) << (count)) - genIType(1));
	}

	VECTORIZE_VEC(mask)

	// extractField
	template <typename genIType>
	GLM_FUNC_QUALIFIER genIType extractField
	(
		half const & value, 
		genIType const & first, 
		genIType const & count
	)
	{
		assert(first + count < sizeof(half));
		return (value._data() << first) >> ((sizeof(half) << 3) - count);
	}

	template <typename genIType>
	GLM_FUNC_QUALIFIER genIType extractField
	(
		float const & value, 
		genIType const & first, 
		genIType const & count
	)
	{
		assert(first + count < sizeof(float));
		return (detail::uif32(value).i << first) >> ((sizeof(float) << 3) - count);
	}

	template <typename genIType>
	GLM_FUNC_QUALIFIER genIType extractField
	(
		double const & value, 
		genIType const & first, 
		genIType const & count
	)
	{
		assert(first + count < sizeof(double));
		return (detail::uif64(value).i << first) >> ((sizeof(double) << genIType(3)) - count);
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER genIUType extractField
	(
		genIUType const & Value, 
		sizeType const & First, 
		sizeType const & Count
	)
	{
		sizeType GenSize = sizeof(genIUType) << 3;

		assert(First + Count <= GenSize);

		genIUType ShiftLeft = Count ? Value << (GenSize - (Count + First)) : 0;
		genIUType ShiftBack = ShiftLeft >> genIUType(GenSize - Count);

		return ShiftBack;
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec2<genIUType> extractField
	(
		detail::tvec2<genIUType> const & value, 
		sizeType const & first, 
		sizeType const & count
	)
	{
		return detail::tvec2<genIUType>(
			extractField(value[0], first, count),
			extractField(value[1], first, count));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec3<genIUType> extractField
	(
		detail::tvec3<genIUType> const & value, 
		sizeType const & first, 
		sizeType const & count
	)
	{
		return detail::tvec3<genIUType>(
			extractField(value[0], first, count),
			extractField(value[1], first, count),
			extractField(value[2], first, count));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec4<genIUType> extractField
	(
		detail::tvec4<genIUType> const & value, 
		sizeType const & first, 
		sizeType const & count
	)
	{
		return detail::tvec4<genIUType>(
			extractField(value[0], first, count),
			extractField(value[1], first, count),
			extractField(value[2], first, count),
			extractField(value[3], first, count));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec2<genIUType> extractField
	(
		detail::tvec2<genIUType> const & value, 
		detail::tvec2<sizeType> const & first, 
		detail::tvec2<sizeType> const & count
	)
	{
		return detail::tvec2<genIUType>(
			extractField(value[0], first[0], count[0]),
			extractField(value[1], first[1], count[1]));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec3<genIUType> extractField
	(
		detail::tvec3<genIUType> const & value, 
		detail::tvec3<sizeType> const & first, 
		detail::tvec3<sizeType> const & count
	)
	{
		return detail::tvec3<genIUType>(
			extractField(value[0], first[0], count[0]),
			extractField(value[1], first[1], count[1]),
			extractField(value[2], first[2], count[2]));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec4<genIUType> extractField
	(
		detail::tvec4<genIUType> const & value, 
		detail::tvec4<sizeType> const & first, 
		detail::tvec4<sizeType> const & count
	)
	{
		return detail::tvec4<genIUType>(
			extractField(value[0], first[0], count[0]),
			extractField(value[1], first[1], count[1]),
			extractField(value[2], first[2], count[2]),
			extractField(value[3], first[3], count[3]));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec2<genIUType> extractField
	(
		genIUType const & value, 
		detail::tvec2<sizeType> const & first, 
		detail::tvec2<sizeType> const & count
	)
	{
		return detail::tvec2<genIUType>(
			extractField(value, first[0], count[0]),
			extractField(value, first[1], count[1]));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec3<genIUType> extractField
	(
		genIUType const & value, 
		detail::tvec3<sizeType> const & first, 
		detail::tvec3<sizeType> const & count
	)
	{
		return detail::tvec3<genIUType>(
			extractField(value, first[0], count[0]),
			extractField(value, first[1], count[1]),
			extractField(value, first[2], count[2]));
	}

	template <typename genIUType, typename sizeType>
	GLM_FUNC_QUALIFIER detail::tvec4<genIUType> extractField
	(
		genIUType const & value, 
		detail::tvec4<sizeType> const & first, 
		detail::tvec4<sizeType> const & count
	)
	{
		return detail::tvec4<genIUType>(
			extractField(value, first[0], count[0]),
			extractField(value, first[1], count[1]),
			extractField(value, first[2], count[2]),
			extractField(value, first[3], count[3]));
	}

	// lowestBit
	template <typename genType>
	GLM_FUNC_QUALIFIER int lowestBit
	(
		genType const & Value
	)
	{
		assert(Value != genType(0)); // not valid call

		genType Bit;
		for(Bit = genType(0); !(Value & (1 << Bit)); ++Bit){}
		return Bit;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<int> lowestBit
	(
		detail::tvec2<valType> const & value
	)
	{
		return detail::tvec2<int>(
			lowestBit(value[0]),
			lowestBit(value[1]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<int> lowestBit
	(
		detail::tvec3<valType> const & value
	)
	{
		return detail::tvec3<int>(
			lowestBit(value[0]),
			lowestBit(value[1]),
			lowestBit(value[2]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<int> lowestBit
	(
		detail::tvec4<valType> const & value
	)
	{
		return detail::tvec4<int>(
			lowestBit(value[0]),
			lowestBit(value[1]),
			lowestBit(value[2]),
			lowestBit(value[3]));
	}

	// highestBit
	template <typename genType>
	GLM_FUNC_QUALIFIER int highestBit
	(
		genType const & value
	)
	{
		assert(value != genType(0)); // not valid call

		genType bit = genType(-1);
		for(genType tmp = value; tmp; tmp >>= 1, ++bit){}
		return bit;
	}

	//template <>
	//GLM_FUNC_QUALIFIER int highestBit<int>
	//(
	//	int value
	//)
	//{
	//	int bit = -1;
	//	for(int tmp = value; tmp; tmp >>= 1, ++bit);
	//	return bit;
	//}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<int> highestBit
	(
		detail::tvec2<valType> const & value
	)
	{
		return detail::tvec2<int>(
			highestBit(value[0]),
			highestBit(value[1]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<int> highestBit
	(
		detail::tvec3<valType> const & value
	)
	{
		return detail::tvec3<int>(
			highestBit(value[0]),
			highestBit(value[1]),
			highestBit(value[2]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<int> highestBit
	(
		detail::tvec4<valType> const & value
	)
	{
		return detail::tvec4<int>(
			highestBit(value[0]),
			highestBit(value[1]),
			highestBit(value[2]),
			highestBit(value[3]));
	}

	// highestBitValue
	template <typename genType>
	GLM_FUNC_QUALIFIER genType highestBitValue
	(
		genType const & value
	)
	{
		genType tmp = value;
		genType result = genType(0);
		while(tmp)
		{
			result = (tmp & (~tmp + 1)); // grab lowest bit
			tmp &= ~result; // clear lowest bit
		}
		return result;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<int> highestBitValue
	(
		detail::tvec2<valType> const & value
	)
	{
		return detail::tvec2<int>(
			highestBitValue(value[0]),
			highestBitValue(value[1]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<int> highestBitValue
	(
		detail::tvec3<valType> const & value
	)
	{
		return detail::tvec3<int>(
			highestBitValue(value[0]),
			highestBitValue(value[1]),
			highestBitValue(value[2]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<int> highestBitValue
	(
		detail::tvec4<valType> const & value
	)
	{
		return detail::tvec4<int>(
			highestBitValue(value[0]),
			highestBitValue(value[1]),
			highestBitValue(value[2]),
			highestBitValue(value[3]));
	}

	// isPowerOfTwo
	template <typename genType>
	GLM_FUNC_QUALIFIER bool isPowerOfTwo(genType const & Value)
	{
		//detail::If<std::numeric_limits<genType>::is_signed>::apply(abs, Value);
		//return !(Value & (Value - 1));

		// For old complier?
		genType Result = Value;
		if(std::numeric_limits<genType>::is_signed)
			Result = abs(Result);
		return !(Result & (Result - 1));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<bool> isPowerOfTwo
	(
		detail::tvec2<valType> const & value
	)
	{
		return detail::tvec2<bool>(
			isPowerOfTwo(value[0]),
			isPowerOfTwo(value[1]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<bool> isPowerOfTwo
	(
		detail::tvec3<valType> const & value
	)
	{
		return detail::tvec3<bool>(
			isPowerOfTwo(value[0]),
			isPowerOfTwo(value[1]),
			isPowerOfTwo(value[2]));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> isPowerOfTwo
	(
		detail::tvec4<valType> const & value
	)
	{
		return detail::tvec4<bool>(
			isPowerOfTwo(value[0]),
			isPowerOfTwo(value[1]),
			isPowerOfTwo(value[2]),
			isPowerOfTwo(value[3]));
	}

	// powerOfTwoAbove
	template <typename genType>
	GLM_FUNC_QUALIFIER genType powerOfTwoAbove(genType const & value)
	{
		return isPowerOfTwo(value) ? value : highestBitValue(value) << 1;
	}

	VECTORIZE_VEC(powerOfTwoAbove)

	// powerOfTwoBelow
	template <typename genType>
	GLM_FUNC_QUALIFIER genType powerOfTwoBelow
	(
		genType const & value
	)
	{
		return isPowerOfTwo(value) ? value : highestBitValue(value);
	}

	VECTORIZE_VEC(powerOfTwoBelow)

	// powerOfTwoNearest
	template <typename genType>
	GLM_FUNC_QUALIFIER genType powerOfTwoNearest
	(
		genType const & value
	)
	{
		if(isPowerOfTwo(value))
			return value;

		genType prev = highestBitValue(value);
		genType next = prev << 1;
		return (next - value) < (value - prev) ? next : prev;
	}

	VECTORIZE_VEC(powerOfTwoNearest)

	template <typename genType>
	GLM_FUNC_QUALIFIER genType bitRevert(genType const & In)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_integer, "'bitRevert' only accept integer values");

		genType Out = 0;
		std::size_t BitSize = sizeof(genType) * 8;
		for(std::size_t i = 0; i < BitSize; ++i)
			if(In & (genType(1) << i))
				Out |= genType(1) << (BitSize - 1 - i);
		return Out;
	}

	VECTORIZE_VEC(bitRevert)

	template <typename genType>
	GLM_FUNC_QUALIFIER genType bitRotateRight(genType const & In, std::size_t Shift)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_integer, "'bitRotateRight' only accept integer values");

		std::size_t BitSize = sizeof(genType) * 8;
		return (In << Shift) | (In >> (BitSize - Shift));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<valType> bitRotateRight
	(
		detail::tvec2<valType> const & Value, 
		std::size_t Shift
	)
	{
		return detail::tvec2<valType>(
			bitRotateRight(Value[0], Shift),
			bitRotateRight(Value[1], Shift));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<valType> bitRotateRight
	(
		detail::tvec3<valType> const & Value, 
		std::size_t Shift
	)
	{
		return detail::tvec3<valType>(
			bitRotateRight(Value[0], Shift),
			bitRotateRight(Value[1], Shift),
			bitRotateRight(Value[2], Shift));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<valType> bitRotateRight
	(
		detail::tvec4<valType> const & Value, 
		std::size_t Shift
	)
	{
		return detail::tvec4<valType>(
			bitRotateRight(Value[0], Shift),
			bitRotateRight(Value[1], Shift),
			bitRotateRight(Value[2], Shift),
			bitRotateRight(Value[3], Shift));
	}

	template <typename genType>
	GLM_FUNC_QUALIFIER genType bitRotateLeft(genType const & In, std::size_t Shift)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_integer, "'bitRotateLeft' only accept integer values");

		std::size_t BitSize = sizeof(genType) * 8;
		return (In >> Shift) | (In << (BitSize - Shift));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<valType> bitRotateLeft
	(
		detail::tvec2<valType> const & Value, 
		std::size_t Shift
	)
	{
		return detail::tvec2<valType>(
			bitRotateLeft(Value[0], Shift),
			bitRotateLeft(Value[1], Shift));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<valType> bitRotateLeft
	(
		detail::tvec3<valType> const & Value, 
		std::size_t Shift
	)
	{
		return detail::tvec3<valType>(
			bitRotateLeft(Value[0], Shift),
			bitRotateLeft(Value[1], Shift),
			bitRotateLeft(Value[2], Shift));
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<valType> bitRotateLeft
	(
		detail::tvec4<valType> const & Value, 
		std::size_t Shift
	)
	{
		return detail::tvec4<valType>(
			bitRotateLeft(Value[0], Shift),
			bitRotateLeft(Value[1], Shift),
			bitRotateLeft(Value[2], Shift),
			bitRotateLeft(Value[3], Shift));
	}

	template <typename genIUType>
	GLM_FUNC_QUALIFIER genIUType fillBitfieldWithOne
	(
		genIUType const & Value,
		int const & FromBit, 
		int const & ToBit
	)
	{
		assert(FromBit <= ToBit);
		assert(ToBit <= sizeof(genIUType) * std::size_t(8));

		genIUType Result = Value;
		for(std::size_t i = 0; i <= ToBit; ++i)
			Result |= (1 << i);
		return Result;
	}

	template <typename genIUType>
	GLM_FUNC_QUALIFIER genIUType fillBitfieldWithZero
	(
		genIUType const & Value,
		int const & FromBit, 
		int const & ToBit
	)
	{
		assert(FromBit <= ToBit);
		assert(ToBit <= sizeof(genIUType) * std::size_t(8));

		genIUType Result = Value;
		for(std::size_t i = 0; i <= ToBit; ++i)
			Result &= ~(1 << i);
		return Result;
	}
}//namespace glm
