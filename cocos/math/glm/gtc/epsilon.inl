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
/// @ref gtc_epsilon
/// @file glm/gtc/epsilon.inl
/// @date 2012-04-07 / 2012-04-07
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	GLM_FUNC_QUALIFIER bool epsilonEqual
	(
		glm::half const & x, 
		glm::half const & y, 
		glm::half const & epsilon
	)
	{
		return abs(x - y) < epsilon;
	}

	GLM_FUNC_QUALIFIER bool epsilonEqual
	(
		float const & x, 
		float const & y, 
		float const & epsilon
	)
	{
		return abs(x - y) < epsilon;
	}

	GLM_FUNC_QUALIFIER bool epsilonEqual
	(
		double const & x, 
		double const & y, 
		double const & epsilon
	)
	{
		return abs(x - y) < epsilon;
	}

	GLM_FUNC_QUALIFIER bool epsilonNotEqual
	(
		glm::half const & x, 
		glm::half const & y, 
		glm::half const & epsilon
	)
	{
		return abs(x - y) >= epsilon;
	}

	GLM_FUNC_QUALIFIER bool epsilonNotEqual
	(
		float const & x, 
		float const & y, 
		float const & epsilon
	)
	{
		return abs(x - y) >= epsilon;
	}

	GLM_FUNC_QUALIFIER bool epsilonNotEqual
	(
		double const & x, 
		double const & y, 
		double const & epsilon
	)
	{
		return abs(x - y) >= epsilon;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<bool> epsilonEqual
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y, 
		valType const & epsilon)
	{
		return detail::tvec2<bool>(
			abs(x.x - y.x) < epsilon,
			abs(x.y - y.y) < epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<bool> epsilonEqual
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y, 
		detail::tvec2<valType> const & epsilon
	)
	{
		return detail::tvec2<bool>(
			abs(x.x - y.x) < epsilon.x,
			abs(x.y - y.y) < epsilon.y);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<bool> epsilonEqual
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y, 
		valType const & epsilon)
	{
		return detail::tvec3<bool>(
			abs(x.x - y.x) < epsilon,
			abs(x.y - y.y) < epsilon,
			abs(x.z - y.z) < epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<bool> epsilonEqual
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y, 
		detail::tvec3<valType> const & epsilon
	)
	{
		return detail::tvec3<bool>(
			abs(x.x - y.x) < epsilon.x,
			abs(x.y - y.y) < epsilon.y,
			abs(x.z - y.z) < epsilon.z);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> epsilonEqual
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y, 
		valType const & epsilon
	)
	{
		return detail::tvec4<bool>(
			abs(x.x - y.x) < epsilon,
			abs(x.y - y.y) < epsilon,
			abs(x.z - y.z) < epsilon,
			abs(x.w - y.w) < epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> epsilonEqual
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y, 
		detail::tvec4<valType> const & epsilon
	)
	{
		return detail::tvec4<bool>(
			abs(x.x - y.x) < epsilon.x,
			abs(x.y - y.y) < epsilon.y,
			abs(x.z - y.z) < epsilon.z,
			abs(x.w - y.w) < epsilon.w);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<bool> epsilonNotEqual
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y, 
		valType const & epsilon
	)
	{
		return detail::tvec2<bool>(
			abs(x.x - y.x) >= epsilon,
			abs(x.y - y.y) >= epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec2<bool> epsilonNotEqual
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y, 
		detail::tvec2<valType> const & epsilon
	)
	{
		return detail::tvec2<bool>(
			abs(x.x - y.x) >= epsilon.x,
			abs(x.y - y.y) >= epsilon.y);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<bool> epsilonNotEqual
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y, 
		valType const & epsilon
	)
	{
		return detail::tvec3<bool>(
			abs(x.x - y.x) >= epsilon,
			abs(x.y - y.y) >= epsilon,
			abs(x.z - y.z) >= epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec3<bool> epsilonNotEqual
	(
		detail::tvec3<valType> const & x, 
		detail::tvec3<valType> const & y, 
		detail::tvec3<valType> const & epsilon
	)
	{
		return detail::tvec3<bool>(
			abs(x.x - y.x) >= epsilon.x,
			abs(x.y - y.y) >= epsilon.y,
			abs(x.z - y.z) >= epsilon.z);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> epsilonNotEqual
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y, 
		valType const & epsilon
	)
	{
		return detail::tvec4<bool>(
			abs(x.x - y.x) >= epsilon,
			abs(x.y - y.y) >= epsilon,
			abs(x.z - y.z) >= epsilon,
			abs(x.w - y.w) >= epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> epsilonNotEqual
	(
		detail::tvec4<valType> const & x, 
		detail::tvec4<valType> const & y, 
		detail::tvec4<valType> const & epsilon
	)
	{
		return detail::tvec4<bool>(
			abs(x.x - y.x) >= epsilon.x,
			abs(x.y - y.y) >= epsilon.y,
			abs(x.z - y.z) >= epsilon.z,
			abs(x.w - y.w) >= epsilon.w);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> epsilonEqual
	(
		detail::tquat<valType> const & x, 
		detail::tquat<valType> const & y, 
		valType const & epsilon
	)
	{
		return detail::tvec4<bool>(
			abs(x.x - y.x) < epsilon,
			abs(x.y - y.y) < epsilon,
			abs(x.z - y.z) < epsilon,
			abs(x.w - y.w) < epsilon);
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER detail::tvec4<bool> epsilonNotEqual
	(
		detail::tquat<valType> const & x, 
		detail::tquat<valType> const & y, 
		valType const & epsilon
	)
	{
		return detail::tvec4<bool>(
			abs(x.x - y.x) >= epsilon,
			abs(x.y - y.y) >= epsilon,
			abs(x.z - y.z) >= epsilon,
			abs(x.w - y.w) >= epsilon);
	}
}//namespace glm
