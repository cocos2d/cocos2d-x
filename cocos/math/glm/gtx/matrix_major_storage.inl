///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-04-19
// Updated : 2009-02-19
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_major_storage.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> rowMajor2
	(
		detail::tvec2<T> const & v1, 
		detail::tvec2<T> const & v2
	)
	{
		detail::tmat2x2<T> Result;
		Result[0][0] = v1.x;
		Result[1][0] = v1.y;
		Result[0][1] = v2.x;
		Result[1][1] = v2.y;
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> rowMajor2(
		const detail::tmat2x2<T>& m)
	{
		detail::tmat2x2<T> Result;
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> rowMajor3(
		const detail::tvec3<T>& v1, 
		const detail::tvec3<T>& v2, 
		const detail::tvec3<T>& v3)
	{
		detail::tmat3x3<T> Result;
		Result[0][0] = v1.x;
		Result[1][0] = v1.y;
		Result[2][0] = v1.z;
		Result[0][1] = v2.x;
		Result[1][1] = v2.y;
		Result[2][1] = v2.z;
		Result[0][2] = v3.x;
		Result[1][2] = v3.y;
		Result[2][2] = v3.z;
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> rowMajor3(
		const detail::tmat3x3<T>& m)
	{
		detail::tmat3x3<T> Result;
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[2][2] = m[2][2];
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> rowMajor4(
		const detail::tvec4<T>& v1, 
		const detail::tvec4<T>& v2, 
		const detail::tvec4<T>& v3, 
		const detail::tvec4<T>& v4)
	{
		detail::tmat4x4<T> Result;
		Result[0][0] = v1.x;
		Result[1][0] = v1.y;
		Result[2][0] = v1.z;
		Result[3][0] = v1.w;
		Result[0][1] = v2.x;
		Result[1][1] = v2.y;
		Result[2][1] = v2.z;
		Result[3][1] = v2.w;
		Result[0][2] = v3.x;
		Result[1][2] = v3.y;
		Result[2][2] = v3.z;
		Result[3][2] = v3.w;
		Result[0][3] = v4.x;
		Result[1][3] = v4.y;
		Result[2][3] = v4.z;
		Result[3][3] = v4.w;
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> rowMajor4(
		const detail::tmat4x4<T>& m)
	{
		detail::tmat4x4<T> Result;
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[0][3] = m[3][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		Result[1][3] = m[3][1];
		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[2][2] = m[2][2];
		Result[2][3] = m[3][2];
		Result[3][0] = m[0][3];
		Result[3][1] = m[1][3];
		Result[3][2] = m[2][3];
		Result[3][3] = m[3][3];
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> colMajor2(
		const detail::tvec2<T>& v1, 
		const detail::tvec2<T>& v2)
	{
		return detail::tmat2x2<T>(v1, v2);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> colMajor2(
		const detail::tmat2x2<T>& m)
	{
		return detail::tmat2x2<T>(m);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> colMajor3(
		const detail::tvec3<T>& v1, 
		const detail::tvec3<T>& v2, 
		const detail::tvec3<T>& v3)
	{
		return detail::tmat3x3<T>(v1, v2, v3);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> colMajor3(
		const detail::tmat3x3<T>& m)
	{
		return detail::tmat3x3<T>(m);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> colMajor4(
		const detail::tvec4<T>& v1, 
		const detail::tvec4<T>& v2, 
		const detail::tvec4<T>& v3, 
		const detail::tvec4<T>& v4)
	{
		return detail::tmat4x4<T>(v1, v2, v3, v4);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> colMajor4(
		const detail::tmat4x4<T>& m)
	{
		return detail::tmat4x4<T>(m);
	}
}//namespace glm
