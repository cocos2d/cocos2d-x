///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-30
// Updated : 2008-09-29
// Licence : This source is under MIT License
// File    : glm/gtx/vector_angle.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType> 
	GLM_FUNC_QUALIFIER typename genType::value_type angle
	(
		genType const & x, 
		genType const & y
	)
	{
		return degrees(acos(dot(x, y)));
	}

	//! \todo epsilon is hard coded to 0.01
	template <typename valType> 
	GLM_FUNC_QUALIFIER valType orientedAngle
	(
		detail::tvec2<valType> const & x, 
		detail::tvec2<valType> const & y
	)
	{
#ifdef GLM_FORCE_RADIANS
		valType const Angle(acos(dot(x, y)));
#else
		valType const Angle(glm::degrees(acos(dot(x, y))));
#endif
		detail::tvec2<valType> const TransformedVector(glm::rotate(x, Angle));
		if(all(epsilonEqual(y, TransformedVector, valType(0.01))))
			return Angle;
		else
			return -Angle;
	}

	template <typename valType>
	GLM_FUNC_QUALIFIER valType orientedAngle
	(
		detail::tvec3<valType> const & x,
		detail::tvec3<valType> const & y,
		detail::tvec3<valType> const & ref
	)
	{
		valType const Angle(glm::degrees(glm::acos(glm::dot(x, y))));

		if(glm::dot(ref, glm::cross(x, y)) < valType(0))
			return -Angle;
		else
			return Angle;
	}
}//namespace glm
