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
/// @file glm/core/type_half.hpp
/// @date 2008-08-17 / 2011-09-20
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_half
#define glm_core_type_half

#include <cstdlib>

namespace glm{
namespace detail
{
	typedef short hdata;

	GLM_FUNC_DECL float toFloat32(hdata value);
	GLM_FUNC_DECL hdata toFloat16(float const & value);

	class half
	{
	public: 
		// Constructors
		GLM_FUNC_DECL half();
		GLM_FUNC_DECL half(half const & s);
			
		template <typename U>
		GLM_FUNC_DECL explicit half(U const & s);

		// Cast
		//template <typename U>
		//GLM_FUNC_DECL operator U() const;
		GLM_FUNC_DECL operator float() const;

		// Unary updatable operators
		GLM_FUNC_DECL half& operator= (half const & s);
		GLM_FUNC_DECL half& operator+=(half const & s);
		GLM_FUNC_DECL half& operator-=(half const & s);
		GLM_FUNC_DECL half& operator*=(half const & s);
		GLM_FUNC_DECL half& operator/=(half const & s);
		GLM_FUNC_DECL half& operator++();
		GLM_FUNC_DECL half& operator--();
	
		GLM_FUNC_DECL float toFloat() const{return toFloat32(data);}

		GLM_FUNC_DECL hdata _data() const{return data;}

	private:
		hdata data;
	};

	GLM_FUNC_DECL half operator+ (half const & s1, half const & s2);

	GLM_FUNC_DECL half operator- (half const & s1, half const & s2);

	GLM_FUNC_DECL half operator* (half const & s1, half const & s2);

	GLM_FUNC_DECL half operator/ (half const & s1, half const & s2);

	// Unary constant operators
	GLM_FUNC_DECL half operator- (half const & s);

	GLM_FUNC_DECL half operator-- (half const & s, int);

	GLM_FUNC_DECL half operator++ (half const & s, int);

	GLM_FUNC_DECL bool operator==(
		detail::half const & x, 
		detail::half const & y);

	GLM_FUNC_DECL bool operator!=(
		detail::half const & x, 
		detail::half const & y);

	GLM_FUNC_DECL bool operator<(
		detail::half const & x, 
		detail::half const & y);

	GLM_FUNC_DECL bool operator<=(
		detail::half const & x, 
		detail::half const & y);

	GLM_FUNC_DECL bool operator>(
		detail::half const & x, 
		detail::half const & y);

	GLM_FUNC_DECL bool operator>=(
		detail::half const & x, 
		detail::half const & y);

}//namespace detail
}//namespace glm

#include "type_half.inl"

#endif//glm_core_type_half
