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
/// @ref gtx_matrix_interpolation
/// @file glm/gtx/matrix_interpolation.hpp
/// @date 2011-03-05 / 2011-06-07
/// @author Ghenadii Ursachi (the.asteroth@gmail.com)
///
/// @see core (dependence)
///
/// @defgroup gtx_matrix_interpolation GLM_GTX_matrix_interpolation
/// @ingroup gtx
/// 
/// @brief Allows to directly interpolate two exiciting matrices.
/// 
/// <glm/gtx/matrix_interpolation.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_matrix_interpolation
#define GLM_GTX_matrix_interpolation GLM_VERSION

// Dependency:
//#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_matrix_interpolation extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_matrix_interpolation
	/// @{

	//! Get the axis and angle of the rotation from a matrix.
    //! From GLM_GTX_matrix_interpolation extension.
	template <typename T>
    void axisAngle(
        detail::tmat4x4<T> const & mat,
        detail::tvec3<T> & axis,
        T & angle);

    //! Build a matrix from axis and angle.
    //! From GLM_GTX_matrix_interpolation extension.
	template <typename T>
    detail::tmat4x4<T> axisAngleMatrix(
        detail::tvec3<T> const & axis,
        T const angle);

	//! Extracts the rotation part of a matrix.
    //! From GLM_GTX_matrix_interpolation extension.
	template <typename T>
	detail::tmat4x4<T> extractMatrixRotation(
		detail::tmat4x4<T> const & mat);

	//! Build a interpolation of 4 * 4 matrixes.
    //! From GLM_GTX_matrix_interpolation extension.
    //! Warning! works only with rotation and/or translation matrixes, scale will generate unexpected results.
	template <typename T>
    detail::tmat4x4<T> interpolate(
        detail::tmat4x4<T> const & m1,
        detail::tmat4x4<T> const & m2,
        T const delta);

	/// @}
}//namespace glm

#include "matrix_interpolation.inl"

#endif//GLM_GTX_matrix_interpolation
