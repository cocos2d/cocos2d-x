///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-24
// Updated : 2008-10-24
// Licence : This source is under MIT License
// File    : glm/gtx/log_base.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename genType> 
	GLM_FUNC_QUALIFIER genType log(
		genType const & x, 
		genType const & base)
	{
		assert(x != genType(0));

		return glm::log(x) / glm::log(base);
	}

	VECTORIZE_VEC_SCA(log)
	VECTORIZE_VEC_VEC(log)
}//namespace glm
