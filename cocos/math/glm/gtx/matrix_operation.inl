///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-08-29
// Updated : 2009-08-29
// Licence : This source is under MIT License
// File    : glm/gtx/matrix_operation.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat2x2<valType> diagonal2x2
	(
		detail::tvec2<valType> const & v
	)
	{
		detail::tmat2x2<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat2x3<valType> diagonal2x3
	(
		detail::tvec2<valType> const & v
	)
	{
		detail::tmat2x3<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat2x4<valType> diagonal2x4
	(
		detail::tvec2<valType> const & v
	)
	{
		detail::tmat2x4<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat3x2<valType> diagonal3x2
	(
		detail::tvec2<valType> const & v
	)
	{
		detail::tmat3x2<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat3x3<valType> diagonal3x3
	(
		detail::tvec3<valType> const & v
	)
	{
		detail::tmat3x3<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		Result[2][2] = v[2];
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat3x4<valType> diagonal3x4
	(
		detail::tvec3<valType> const & v
	)
	{
		detail::tmat3x4<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		Result[2][2] = v[2];
		return Result;
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<valType> diagonal4x4
	(
		detail::tvec4<valType> const & v
	)
	{
		detail::tmat4x4<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		Result[2][2] = v[2];
		Result[3][3] = v[3];
		return Result;		
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x3<valType> diagonal4x3
	(
		detail::tvec3<valType> const & v
	)
	{
		detail::tmat4x3<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		Result[2][2] = v[2];
		return Result;		
	}

	template <typename valType> 
	GLM_FUNC_QUALIFIER detail::tmat4x2<valType> diagonal4x2
	(
		detail::tvec2<valType> const & v
	)
	{
		detail::tmat4x2<valType> Result(valType(1));
		Result[0][0] = v[0];
		Result[1][1] = v[1];
		return Result;		
	}
}//namespace glm
