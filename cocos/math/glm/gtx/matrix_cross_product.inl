///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2005-12-21
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_cross_product.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> matrixCross3
	(
		detail::tvec3<T> const & x
	)
	{
		detail::tmat3x3<T> Result(T(0));
		Result[0][1] = x.z;
		Result[1][0] = -x.z;
		Result[0][2] = -x.y;
		Result[2][0] = x.y;
		Result[1][2] = x.x;
		Result[2][1] = -x.x;
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> matrixCross4
	(
		detail::tvec3<T> const & x
	)
	{
		detail::tmat4x4<T> Result(T(0));
		Result[0][1] = x.z;
		Result[1][0] = -x.z;
		Result[0][2] = -x.y;
		Result[2][0] = x.y;
		Result[1][2] = x.x;
		Result[2][1] = -x.x;
		return Result;
	}

}//namespace glm
