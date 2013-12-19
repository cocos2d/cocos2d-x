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
/// @ref gtc_quaternion
/// @file glm/gtc/quaternion.hpp
/// @date 2009-05-21 / 2012-12-20
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_half_float (dependence)
/// @see gtc_constants (dependence)
///
/// @defgroup gtc_quaternion GLM_GTC_quaternion
/// @ingroup gtc
/// 
/// @brief Defines a templated quaternion type and several quaternion operations.
/// 
/// <glm/gtc/quaternion.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTC_quaternion
#define GLM_GTC_quaternion GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"
#include "../gtc/constants.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_quaternion extension included")
#endif

namespace glm{
namespace detail
{
	template <typename T> 
	struct tquat// : public genType<T, tquat>
	{
		enum ctor{null};

		typedef T value_type;
		typedef std::size_t size_type;

	public:
		value_type x, y, z, w;

		GLM_FUNC_DECL size_type length() const;

		// Constructors
		tquat();
		explicit tquat(
			value_type const & s, 
			glm::detail::tvec3<T> const & v);
		explicit tquat(
			value_type const & w, 
			value_type const & x, 
			value_type const & y, 
			value_type const & z);

		// Convertions

		/// Build a quaternion from euler angles (pitch, yaw, roll), in radians.
		explicit tquat(
			tvec3<T> const & eulerAngles);
		explicit tquat(
			tmat3x3<T> const & m);
		explicit tquat(
			tmat4x4<T> const & m);

		// Accesses
		value_type & operator[](int i);
		value_type const & operator[](int i) const;

		// Operators
		tquat<T> & operator*=(value_type const & s);
		tquat<T> & operator/=(value_type const & s);
	};

	template <typename T> 
	detail::tquat<T> operator- (
		detail::tquat<T> const & q);

	template <typename T> 
	detail::tquat<T> operator+ ( 
		detail::tquat<T> const & q, 
		detail::tquat<T> const & p); 

	template <typename T> 
	detail::tquat<T> operator* ( 
		detail::tquat<T> const & q, 
		detail::tquat<T> const & p); 

	template <typename T> 
	detail::tvec3<T> operator* (
		detail::tquat<T> const & q, 
		detail::tvec3<T> const & v);

	template <typename T> 
	detail::tvec3<T> operator* (
		detail::tvec3<T> const & v,
		detail::tquat<T> const & q);

	template <typename T> 
	detail::tvec4<T> operator* (
		detail::tquat<T> const & q, 
		detail::tvec4<T> const & v);

	template <typename T> 
	detail::tvec4<T> operator* (
		detail::tvec4<T> const & v,
		detail::tquat<T> const & q);

	template <typename T> 
	detail::tquat<T> operator* (
		detail::tquat<T> const & q, 
		typename detail::tquat<T>::value_type const & s);

	template <typename T> 
	detail::tquat<T> operator* (
		typename detail::tquat<T>::value_type const & s,
		detail::tquat<T> const & q);

	template <typename T> 
	detail::tquat<T> operator/ (
		detail::tquat<T> const & q, 
		typename detail::tquat<T>::value_type const & s);

} //namespace detail

	/// @addtogroup gtc_quaternion
	/// @{

	/// Returns the length of the quaternion. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	T length(
		detail::tquat<T> const & q);

	/// Returns the normalized quaternion. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> normalize(
		detail::tquat<T> const & q);
		
	/// Returns dot product of q1 and q2, i.e., q1[0] * q2[0] + q1[1] * q2[1] + ... 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	T dot(
		detail::tquat<T> const & q1, 
		detail::tquat<T> const & q2);

	/// Spherical linear interpolation of two quaternions.
	/// The interpolation is oriented and the rotation is performed at constant speed.
	/// For short path spherical linear interpolation, use the slerp function.
	/// 
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
	/// @tparam T Value type used to build the quaternion. Supported: half, float or double.
	/// @see gtc_quaternion
	/// @see - slerp(detail::tquat<T> const & x, detail::tquat<T> const & y, T const & a) 
	template <typename T> 
	detail::tquat<T> mix(
		detail::tquat<T> const & x, 
		detail::tquat<T> const & y, 
		T const & a);

	/// Linear interpolation of two quaternions. 
	/// The interpolation is oriented.
	/// 
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined in the range [0, 1].
	/// @tparam T Value type used to build the quaternion. Supported: half, float or double.
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> lerp(
		detail::tquat<T> const & x, 
		detail::tquat<T> const & y, 
		T const & a);

	/// Spherical linear interpolation of two quaternions.
	/// The interpolation always take the short path and the rotation is performed at constant speed.
	/// 
	/// @param x A quaternion
	/// @param y A quaternion
	/// @param a Interpolation factor. The interpolation is defined beyond the range [0, 1].
	/// @tparam T Value type used to build the quaternion. Supported: half, float or double.
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> slerp(
		detail::tquat<T> const & x, 
		detail::tquat<T> const & y, 
		T const & a);

	/// Returns the q conjugate. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> conjugate(
		detail::tquat<T> const & q);

	/// Returns the q inverse. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> inverse(
		detail::tquat<T> const & q);

	/// Rotates a quaternion from an vector of 3 components axis and an angle.
	/// 
	/// @param q Source orientation
	/// @param angle Angle expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
	/// @param axis Axis of the rotation, must be normalized.
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> rotate(
		detail::tquat<T> const & q, 
		typename detail::tquat<T>::value_type const & angle, 
		detail::tvec3<T> const & axis);

	/// Returns euler angles, yitch as x, yaw as y, roll as z. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tvec3<T> eulerAngles(
		detail::tquat<T> const & x);

	/// Returns roll value of euler angles expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
	///
	/// @see gtx_quaternion
	template <typename valType> 
	valType roll(
		detail::tquat<valType> const & x);

	/// Returns pitch value of euler angles expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
	///
	/// @see gtx_quaternion
	template <typename valType> 
	valType pitch(
		detail::tquat<valType> const & x);

	/// Returns yaw value of euler angles expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
	///
	/// @see gtx_quaternion
	template <typename valType> 
	valType yaw(
		detail::tquat<valType> const & x);

	/// Converts a quaternion to a 3 * 3 matrix. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tmat3x3<T> mat3_cast(
		detail::tquat<T> const & x);

	/// Converts a quaternion to a 4 * 4 matrix. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tmat4x4<T> mat4_cast(
		detail::tquat<T> const & x);

	/// Converts a 3 * 3 matrix to a quaternion. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> quat_cast(
		detail::tmat3x3<T> const & x);

	/// Converts a 4 * 4 matrix to a quaternion. 
	/// 
	/// @see gtc_quaternion
	template <typename T> 
	detail::tquat<T> quat_cast(
		detail::tmat4x4<T> const & x);

	/// Returns the quaternion rotation angle. 
	///
	/// @see gtc_quaternion
	template <typename valType> 
	valType angle(
		detail::tquat<valType> const & x);

	/// Returns the q rotation axis. 
	///
	/// @see gtc_quaternion
	template <typename valType> 
	detail::tvec3<valType> axis(
		detail::tquat<valType> const & x);

	/// Build a quaternion from an angle and a normalized axis. 
	///
	/// @param angle Angle expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
	/// @param x x component of the x-axis, x, y, z must be a normalized axis
	/// @param y y component of the y-axis, x, y, z must be a normalized axis
	/// @param z z component of the z-axis, x, y, z must be a normalized axis
	///
	/// @see gtc_quaternion
	template <typename valType> 
	detail::tquat<valType> angleAxis(
		valType const & angle, 
		valType const & x, 
		valType const & y, 
		valType const & z);

	/// Build a quaternion from an angle and a normalized axis.
	///
	/// @param angle Angle expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
	/// @param axis Axis of the quaternion, must be normalized. 
	///
	/// @see gtc_quaternion
	template <typename valType> 
	detail::tquat<valType> angleAxis(
		valType const & angle, 
		detail::tvec3<valType> const & axis);

	/// Quaternion of floating-point numbers. 
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<float> quat;

	/// Quaternion of half-precision floating-point numbers.
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<detail::half>	hquat;

	/// Quaternion of single-precision floating-point numbers. 
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<float>	fquat;

	/// Quaternion of double-precision floating-point numbers. 
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<double>	dquat;

	/// Quaternion of low precision floating-point numbers.
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<lowp_float>		lowp_quat;

	/// Quaternion of medium precision floating-point numbers. 
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<mediump_float>	mediump_quat;

	/// Quaternion of high precision floating-point numbers. 
	/// 
	/// @see gtc_quaternion
	typedef detail::tquat<highp_float>		highp_quat;

	/// @}
} //namespace glm

#include "quaternion.inl"

#endif//GLM_GTC_quaternion
