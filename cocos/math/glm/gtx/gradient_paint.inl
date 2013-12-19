///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-03-06
// Updated : 2009-03-09
// Licence : This source is under MIT License
// File    : glm/gtx/gradient_paint.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename valType>
	valType radialGradient
	(
		detail::tvec2<valType> const & Center,
		valType const & Radius,
		detail::tvec2<valType> const & Focal,
		detail::tvec2<valType> const & Position
	)
	{
		detail::tvec2<valType> F = Focal - Center;
		detail::tvec2<valType> D = Position - Focal;
		valType Radius2 = pow2(Radius);
		valType Fx2 = pow2(F.x);
		valType Fy2 = pow2(F.y);

		valType Numerator = (D.x * F.x + D.y * F.y) + sqrt(Radius2 * (pow2(D.x) + pow2(D.y)) - pow2(D.x * F.y - D.y * F.x));
		valType Denominator = Radius2 - (Fx2 + Fy2);
		return Numerator / Denominator;
	}

	template <typename valType>
	valType linearGradient
	(
		detail::tvec2<valType> const & Point0,
		detail::tvec2<valType> const & Point1,
		detail::tvec2<valType> const & Position
	)
	{
		detail::tvec2<valType> Dist = Point1 - Point0;
		return (Dist.x * (Position.x - Point0.x) + Dist.y * (Position.y - Point0.y)) / glm::dot(Dist, Dist);
	}
}//namespace glm
