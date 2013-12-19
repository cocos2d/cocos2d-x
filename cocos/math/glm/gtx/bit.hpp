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
/// @ref gtx_bit
/// @file glm/gtx/bit.hpp
/// @date 2007-03-14 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_half_float (dependence)
///
/// @defgroup gtx_bit GLM_GTX_bit
/// @ingroup gtx
/// 
/// @brief Allow to perform bit operations on integer values
/// 
/// <glm/gtx/bit.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_bit
#define GLM_GTX_bit GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_bit extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_bit
	/// @{

	/// Build a mask of 'count' bits
	/// @see gtx_bit
	template <typename genIType>
	genIType mask(genIType const & count);

	/// Component wise extraction of bit fields.
	/// genType and genIType could be a scalar or a vector.
	/// @see gtx_bit
	template <typename genIUType, typename sizeType>
	GLM_DEPRECATED genIUType extractField(
		genIUType const & v, 
		sizeType const & first, 
		sizeType const & count);

	//! Find the lowest bit set to 1 in a integer variable.
	/// @see gtx_bit
	template <typename genType> 
	GLM_DEPRECATED int lowestBit(genType const & value);

	//! Find the highest bit set to 1 in a integer variable.
	/// @see gtx_bit
	template <typename genType> 
	GLM_DEPRECATED int highestBit(genType const & value);

	//! Find the highest bit set to 1 in a integer variable and return its value. 
	/// @see gtx_bit
	template <typename genType> 
	genType highestBitValue(genType const & value);

	//! Return true if the value is a power of two number. 
	/// @see gtx_bit
	template <typename genType> 
	bool isPowerOfTwo(genType const & value);

	//! Return the power of two number which value is just higher the input value.
	/// @see gtx_bit
	template <typename genType> 
	genType powerOfTwoAbove(genType const & value);

	//! Return the power of two number which value is just lower the input value. 
	/// @see gtx_bit
	template <typename genType> 
	genType powerOfTwoBelow(genType const & value);

	//! Return the power of two number which value is the closet to the input value. 
	/// @see gtx_bit
	template <typename genType> 
	genType powerOfTwoNearest(genType const & value);

	//! Revert all bits of any integer based type. 
	/// @see gtx_bit
	template <typename genType> 
	GLM_DEPRECATED genType bitRevert(genType const & value);

	//! Rotate all bits to the right.
	/// @see gtx_bit
	template <typename genType>
	genType bitRotateRight(genType const & In, std::size_t Shift);

	//! Rotate all bits to the left.
	/// @see gtx_bit
	template <typename genType>
	genType bitRotateLeft(genType const & In, std::size_t Shift);

	//! Set to 1 a range of bits.
	/// @see gtx_bit
	template <typename genIUType>
	genIUType fillBitfieldWithOne(
		genIUType const & Value,
		int const & FromBit, 
		int const & ToBit);

	//! Set to 0 a range of bits.
	/// @see gtx_bit
	template <typename genIUType>
	genIUType fillBitfieldWithZero(
		genIUType const & Value,
		int const & FromBit, 
		int const & ToBit);

	/// @}
} //namespace glm

#include "bit.inl"

#endif//GLM_GTX_bit
