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
/// @ref gtc_noise
/// @file glm/gtc/noise.hpp
/// @date 2011-04-21 / 2011-09-27
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtc_noise GLM_GTC_noise
/// @ingroup gtc
/// 
/// Defines 2D, 3D and 4D procedural noise functions 
/// Based on the work of Stefan Gustavson and Ashima Arts on "webgl-noise": 
/// https://github.com/ashima/webgl-noise 
/// Following Stefan Gustavson's paper "Simplex noise demystified": 
/// http://www.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
/// <glm/gtc/noise.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTC_noise
#define GLM_GTC_noise GLM_VERSION

// Dependency:
#include "../glm.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTC_noise extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_noise
	/// @{

	/// Classic perlin noise.
    /// @see gtc_noise
	template <typename T, template<typename> class vecType> 
    T perlin(
		vecType<T> const & p);
		
	/// Periodic perlin noise.
	/// @see gtc_noise
	template <typename T, template<typename> class vecType> 
    T perlin(
		vecType<T> const & p, 
		vecType<T> const & rep);

	/// Simplex noise.
	/// @see gtc_noise
	template <typename T, template<typename> class vecType> 
    T simplex(
		vecType<T> const & p);

	/// @}
}//namespace glm

#include "noise.inl"

#endif//GLM_GTC_noise
