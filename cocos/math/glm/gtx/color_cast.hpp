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
/// @ref gtx_color_cast
/// @file glm/gtx/color_cast.hpp
/// @date 2007-06-21 / 2011-06-07
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtx_number_precision (dependence)
///
/// @defgroup gtx_color_cast GLM_GTX_color_cast
/// @ingroup gtx
///
/// @brief Conversion between two color types.
/// 
/// <glm/gtx/color_cast.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_GTX_color_cast
#define GLM_GTX_color_cast GLM_VERSION

// Dependency:
#include "../glm.hpp"
#include "../gtx/number_precision.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_color_cast extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_color_cast
	/// @{

	//! Conversion of a floating value into a 8bit unsigned int value. 
	/// @see gtx_color_cast
	template <typename valType> uint8 u8channel_cast(valType a);

	/// Conversion of a floating value into a 16bit unsigned int value. 
	/// @see gtx_color_cast
	template <typename valType>	uint16 u16channel_cast(valType a);

	template <typename T> uint32 u32_rgbx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint32 u32_xrgb_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint32 u32_bgrx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint32 u32_xbgr_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)

	template <typename T> uint32 u32_rgba_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint32 u32_argb_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint32 u32_bgra_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint32 u32_abgr_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 32bit unsigned int value. (From GLM_GTX_color_cast extension)

	template <typename T> uint64 u64_rgbx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint64 u64_xrgb_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint64 u64_bgrx_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint64 u64_xbgr_cast(const detail::tvec3<T>& c);		//!< \brief Conversion of a 3 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)

	template <typename T> uint64 u64_rgba_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint64 u64_argb_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint64 u64_bgra_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)
	template <typename T> uint64 u64_abgr_cast(const detail::tvec4<T>& c);		//!< \brief Conversion of a 4 components color into an 64bit unsigned int value. (From GLM_GTX_color_cast extension)

	template <typename T> f16 f16_channel_cast(T a);	//!< \brief Conversion of a u8 or u16 value to a single channel floating value. (From GLM_GTX_color_cast extension)

	template <typename T> f16vec3 f16_rgbx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f16vec3 f16_xrgb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f16vec3 f16_bgrx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f16vec3 f16_xbgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)

	template <typename T> f16vec4 f16_rgba_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f16vec4 f16_argb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f16vec4 f16_bgra_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f16vec4 f16_abgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)

	template <typename T> f32 f32_channel_cast(T a);		//!< \brief Conversion of a u8 or u16 value to a single channel floating value. (From GLM_GTX_color_cast extension)

	template <typename T> f32vec3 f32_rgbx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f32vec3 f32_xrgb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f32vec3 f32_bgrx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f32vec3 f32_xbgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)

	template <typename T> f32vec4 f32_rgba_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f32vec4 f32_argb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f32vec4 f32_bgra_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f32vec4 f32_abgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)

	template <typename T> f64 f64_channel_cast(T a);		//!< \brief Conversion of a u8 or u16 value to a single channel floating value. (From GLM_GTX_color_cast extension)

	template <typename T> f64vec3 f64_rgbx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f64vec3 f64_xrgb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f64vec3 f64_bgrx_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f64vec3 f64_xbgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 3 components floating color. (From GLM_GTX_color_cast extension)

	template <typename T> f64vec4 f64_rgba_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f64vec4 f64_argb_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f64vec4 f64_bgra_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)
	template <typename T> f64vec4 f64_abgr_cast(T c);		//!< \brief Conversion of a u32 or u64 color into 4 components floating color. (From GLM_GTX_color_cast extension)

	/// @}
}//namespace glm

#include "color_cast.inl"

#endif//GLM_GTX_color_cast
