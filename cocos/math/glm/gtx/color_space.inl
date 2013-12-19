///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2007-02-22
// Licence : This source is under MIT License
// File    : glm/gtx/color_space.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> rgbColor(const detail::tvec3<T>& hsvColor)
	{
		detail::tvec3<T> hsv = hsvColor;
		detail::tvec3<T> rgbColor;

		if(hsv.y == T(0))
			// achromatic (grey)
			rgbColor = detail::tvec3<T>(hsv.z);
		else
		{
			T sector = floor(hsv.x / T(60));
			T frac = (hsv.x / T(60)) - sector;
			// factorial part of h
			T o = hsv.z * (T(1) - hsv.y);
			T p = hsv.z * (T(1) - hsv.y * frac);
			T q = hsv.z * (T(1) - hsv.y * (T(1) - frac));

			switch(int(sector))
			{
			default:
			case 0:
				rgbColor.r = hsv.z;
				rgbColor.g = q;
				rgbColor.b = o;
				break;
			case 1:
				rgbColor.r = p;
				rgbColor.g = hsv.z;
				rgbColor.b = o;
				break;
			case 2:
				rgbColor.r = o;
				rgbColor.g = hsv.z;
				rgbColor.b = q;
				break;
			case 3:
				rgbColor.r = o;
				rgbColor.g = p;
				rgbColor.b = hsv.z;
				break;
			case 4:
				rgbColor.r = q; 
				rgbColor.g = o; 
				rgbColor.b = hsv.z;
				break;
			case 5:
				rgbColor.r = hsv.z; 
				rgbColor.g = o; 
				rgbColor.b = p;
				break;
			}
		}

		return rgbColor;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> hsvColor(const detail::tvec3<T>& rgbColor)
	{
		detail::tvec3<T> hsv = rgbColor;
		float Min   = min(min(rgbColor.r, rgbColor.g), rgbColor.b);
		float Max   = max(max(rgbColor.r, rgbColor.g), rgbColor.b);
		float Delta = Max - Min;

		hsv.z = Max;                               
    	
		if(Max != T(0))
		{
			hsv.y = Delta / hsv.z;    
			T h = T(0);

			if(rgbColor.r == Max)
				// between yellow & magenta
				h = T(0) + T(60) * (rgbColor.g - rgbColor.b) / Delta;
			else if(rgbColor.g == Max)
				// between cyan & yellow
				h = T(120) + T(60) * (rgbColor.b - rgbColor.r) / Delta;
			else
				// between magenta & cyan
				h = T(240) + T(60) * (rgbColor.r - rgbColor.g) / Delta;
            
			if(h < T(0)) 
				hsv.x = h + T(360);
			else
				hsv.x = h;
		}
		else
		{
			// If r = g = b = 0 then s = 0, h is undefined
			hsv.y = T(0);
			hsv.x = T(0);
		}

		return hsv;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> saturation(const T s)
	{
		detail::tvec3<T> rgbw = detail::tvec3<T>(T(0.2126), T(0.7152), T(0.0722));

		T col0 = (T(1) - s) * rgbw.r;
		T col1 = (T(1) - s) * rgbw.g;
		T col2 = (T(1) - s) * rgbw.b;

		detail::tmat4x4<T> result(T(1));
		result[0][0] = col0 + s;
		result[0][1] = col0;
		result[0][2] = col0;
		result[1][0] = col1;
		result[1][1] = col1 + s;
		result[1][2] = col1;
		result[2][0] = col2;
		result[2][1] = col2;
		result[2][2] = col2 + s;
		return result;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec3<T> saturation(const T s, const detail::tvec3<T>& color)
	{
		return detail::tvec3<T>(saturation(s) * detail::tvec4<T>(color, T(0)));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER detail::tvec4<T> saturation(const T s, const detail::tvec4<T>& color)
	{
		return saturation(s) * color;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER T luminosity(const detail::tvec3<T>& color)
	{
		const detail::tvec3<T> tmp = detail::tvec3<T>(0.33, 0.59, 0.11);
		return dot(color, tmp);
	}
}//namespace glm
