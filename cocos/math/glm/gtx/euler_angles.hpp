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
/// @ref gtx_euler_angles
/// @file glm/gtx/euler_angles.hpp
/// @date 2005-12-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_half_float (dependence)
///
/// @defgroup gtx_euler_angles GLM_GTX_euler_angles
/// @ingroup gtx
/// 
/// @brief Build matrices from Euler angles.
/// 
/// <glm/gtx/euler_angles.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_euler_angles
#define GLM_GTX_euler_angles GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_euler_angles extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_euler_angles
	/// @{

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from an euler angle X.
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleX(
		valType const & angleX);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from an euler angle Y.
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleY(
		valType const & angleY);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from an euler angle Z.
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleZ(
		valType const & angleZ);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (X * Y).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleXY(
		valType const & angleX, 
		valType const & angleY);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Y * X).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleYX(
		valType const & angleY, 
		valType const & angleX);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (X * Z).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleXZ(
		valType const & angleX, 
		valType const & angleZ);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Z * X).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleZX(
		valType const & angleZ, 
		valType const & angleX);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Y * Z).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleYZ(
		valType const & angleY, 
		valType const & angleZ);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Z * Y).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleZY(
		valType const & angleZ, 
		valType const & angleY);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Y * X * Z).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> eulerAngleYXZ(
		valType const & yaw, 
		valType const & pitch, 
		valType const & roll);

	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Y * X * Z).
	/// @see gtx_euler_angles
	template <typename valType> 
	detail::tmat4x4<valType> yawPitchRoll(
		valType const & yaw, 
		valType const & pitch, 
		valType const & roll);

	/// Creates a 2D 2 * 2 rotation matrix from an euler angle.
	/// @see gtx_euler_angles
	template <typename T> 
	detail::tmat2x2<T> orientate2(T const & angle);

	/// Creates a 2D 4 * 4 homogeneous rotation matrix from an euler angle.
	/// @see gtx_euler_angles
	template <typename T> 
	detail::tmat3x3<T> orientate3(T const & angle);

	/// Creates a 3D 3 * 3 rotation matrix from euler angles (Y * X * Z). 
	/// @see gtx_euler_angles
	template <typename T> 
	detail::tmat3x3<T> orientate3(detail::tvec3<T> const & angles);
		
	/// Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Y * X * Z).
	/// @see gtx_euler_angles
	template <typename T> 
	detail::tmat4x4<T> orientate4(detail::tvec3<T> const & angles);

	/// @}
}//namespace glm

#include "euler_angles.inl"

#endif//GLM_GTX_euler_angles
