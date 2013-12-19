///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-14
// Updated : 2010-02-19
// Licence : This source is under MIT License
// File    : gtx_extented_min_max.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T>
	GLM_FUNC_QUALIFIER T min(
		T const & x, 
		T const & y, 
		T const & z)
	{
		return glm::min(glm::min(x, y), z);
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const & x, 
		typename C<T>::value_type const & y, 
		typename C<T>::value_type const & z
	)
	{
		return glm::min(glm::min(x, y), z);
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const & x, 
		C<T> const & y, 
		C<T> const & z
	)
	{
		return glm::min(glm::min(x, y), z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T min
	(
		T const & x, 
		T const & y, 
		T const & z, 
		T const & w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const & x, 
		typename C<T>::value_type const & y, 
		typename C<T>::value_type const & z, 
		typename C<T>::value_type const & w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const & x, 
		C<T> const & y, 
		C<T> const & z, 
		C<T> const & w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T max(
		T const & x, 
		T const & y, 
		T const & z)
	{
		return glm::max(glm::max(x, y), z);
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const & x, 
		typename C<T>::value_type const & y, 
		typename C<T>::value_type const & z
	)
	{
		return glm::max(glm::max(x, y), z);
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const & x, 
		C<T> const & y, 
		C<T> const & z
	)
	{
		return glm::max(glm::max(x, y), z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T max
	(
		T const & x, 
		T const & y, 
		T const & z, 
		T const & w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const & x, 
		typename C<T>::value_type const & y, 
		typename C<T>::value_type const & z, 
		typename C<T>::value_type const & w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template 
	<
		typename T, 
		template <typename> class C
	>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const & x, 
		C<T> const & y, 
		C<T> const & z, 
		C<T> const & w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

}//namespace glm
