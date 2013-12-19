///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-11-25
// Updated : 2010-02-13
// Licence : This source is under MIT License
// File    : glm/gtx/wrap.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType clamp
	(
		genType const & Texcoord
	)
	{
		return glm::clamp(Texcoord, genType(0), genType(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec2<T> clamp
	(
		detail::tvec2<T> const & Texcoord
	)
	{
		detail::tvec2<T> Result;
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			Result[i] = clamp(Texcoord[i]);
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> clamp
	(
		detail::tvec3<T> const & Texcoord
	)
	{
		detail::tvec3<T> Result;
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size(); ++i)
			Result[i] = clamp(Texcoord[i]);
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec4<T> clamp
	(
		detail::tvec4<T> const & Texcoord
	)
	{
		detail::tvec4<T> Result;
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size(); ++i)
			Result[i] = clamp(Texcoord[i]);
		return Result;
	}

	////////////////////////
	// repeat

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType repeat
	(
		genType const & Texcoord
	)
	{
		return glm::fract(Texcoord);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec2<T> repeat
	(
		detail::tvec2<T> const & Texcoord
	)
	{
		detail::tvec2<T> Result;
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			Result[i] = repeat(Texcoord[i]);
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> repeat
	(
		detail::tvec3<T> const & Texcoord
	)
	{
		detail::tvec3<T> Result;
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size(); ++i)
			Result[i] = repeat(Texcoord[i]);
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec4<T> repeat
	(
		detail::tvec4<T> const & Texcoord
	)
	{
		detail::tvec4<T> Result;
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size(); ++i)
			Result[i] = repeat(Texcoord[i]);
		return Result;
	}

	////////////////////////
	// mirrorRepeat

	template <typename genType> 
	GLM_FUNC_QUALIFIER genType mirrorRepeat
	(
		genType const & Texcoord
	)
	{
		genType const Clamp = genType(int(glm::floor(Texcoord)) % 2);
		genType const Floor = glm::floor(Texcoord);
		genType const Rest = Texcoord - Floor;
		genType const Mirror = Clamp + Rest;

		genType Out;
		if(Mirror >= genType(1))
			Out = genType(1) - Rest;
		else
			Out = Rest;
		return Out;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec2<T> mirrorRepeat
	(
		detail::tvec2<T> const & Texcoord
	)
	{
		detail::tvec2<T> Result;
		for(typename detail::tvec2<T>::size_type i = 0; i < detail::tvec2<T>::value_size(); ++i)
			Result[i] = mirrorRepeat(Texcoord[i]);
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> mirrorRepeat
	(
		detail::tvec3<T> const & Texcoord
	)
	{
		detail::tvec3<T> Result;
		for(typename detail::tvec3<T>::size_type i = 0; i < detail::tvec3<T>::value_size(); ++i)
			Result[i] = mirrorRepeat(Texcoord[i]);
		return Result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec4<T> mirrorRepeat
	(
		detail::tvec4<T> const & Texcoord
	)
	{
		detail::tvec4<T> Result;
		for(typename detail::tvec4<T>::size_type i = 0; i < detail::tvec4<T>::value_size(); ++i)
			Result[i] = mirrorRepeat(Texcoord[i]);
		return Result;
	}
}//namespace glm
