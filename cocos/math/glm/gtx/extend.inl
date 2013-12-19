///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-01-07
// Updated : 2008-10-05
// Licence : This source is under MIT License
// File    : glm/gtx/extend.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType>
	genType extend
	(
		genType const & Origin, 
		genType const & Source, 
		genType const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template <typename valType>
	detail::tvec2<valType> extend
	(
		detail::tvec2<valType> const & Origin, 
		detail::tvec2<valType> const & Source, 
		valType const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template <typename valType>
	detail::tvec3<valType> extend
	(
		detail::tvec3<valType> const & Origin, 
		detail::tvec3<valType> const & Source, 
		valType const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}

	template <typename valType>
	detail::tvec4<valType> extend
	(
		detail::tvec4<valType> const & Origin, 
		detail::tvec4<valType> const & Source, 
		valType const & Distance
	)
	{
		return Origin + (Source - Origin) * Distance;
	}
}//namespace glm
