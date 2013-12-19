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
/// @file glm/gtc/noise.inl
/// @date 2011-04-21 / 2012-04-07
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////
// Based on the work of Stefan Gustavson and Ashima Arts on "webgl-noise": 
// https://github.com/ashima/webgl-noise 
// Following Stefan Gustavson's paper "Simplex noise demystified": 
// http://www.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T>
	GLM_FUNC_QUALIFIER T mod289(T const & x)
	{
		return x - floor(x * T(1.0 / 289.0)) * T(289.0);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T permute(T const & x)
	{
		return mod289(((x * T(34)) + T(1)) * x);
	}

	template <typename T, template<typename> class vecType>
	GLM_FUNC_QUALIFIER vecType<T> permute(vecType<T> const & x)
	{
		return mod289(((x * T(34)) + T(1)) * x);
	}
  
	template <typename T>
	GLM_FUNC_QUALIFIER T taylorInvSqrt(T const & r)
	{
		return T(1.79284291400159) - T(0.85373472095314) * r;
	}

	template <typename T, template<typename> class vecType>
	GLM_FUNC_QUALIFIER vecType<T> taylorInvSqrt(vecType<T> const & r)
	{
		return T(1.79284291400159) - T(0.85373472095314) * r;
	}

	template <typename T, template <typename> class vecType> 
	GLM_FUNC_QUALIFIER vecType<T> fade(vecType<T> const & t) 
	{
		return t * t * t * (t * (t * T(6) - T(15)) + T(10));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> grad4(T const & j, detail::tvec4<T> const & ip)
	{
		detail::tvec3<T> pXYZ = floor(fract(detail::tvec3<T>(j) * detail::tvec3<T>(ip)) * T(7)) * ip[2] - T(1);
		T pW = T(1.5) - dot(abs(pXYZ), detail::tvec3<T>(1));
		detail::tvec4<T> s = detail::tvec4<T>(lessThan(detail::tvec4<T>(pXYZ, pW), detail::tvec4<T>(0.0)));
		pXYZ = pXYZ + (detail::tvec3<T>(s) * T(2) - T(1)) * s.w; 
		return detail::tvec4<T>(pXYZ, pW);
	}

	// Classic Perlin noise
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec2<T> const & P)
	{
		detail::tvec4<T> Pi = glm::floor(detail::tvec4<T>(P.x, P.y, P.x, P.y)) + detail::tvec4<T>(0.0, 0.0, 1.0, 1.0);
		detail::tvec4<T> Pf = glm::fract(detail::tvec4<T>(P.x, P.y, P.x, P.y)) - detail::tvec4<T>(0.0, 0.0, 1.0, 1.0);
		Pi = mod(Pi, T(289)); // To avoid truncation effects in permutation
		detail::tvec4<T> ix(Pi.x, Pi.z, Pi.x, Pi.z);
		detail::tvec4<T> iy(Pi.y, Pi.y, Pi.w, Pi.w);
		detail::tvec4<T> fx(Pf.x, Pf.z, Pf.x, Pf.z);
		detail::tvec4<T> fy(Pf.y, Pf.y, Pf.w, Pf.w);

		detail::tvec4<T> i = glm::permute(glm::permute(ix) + iy);

		detail::tvec4<T> gx = T(2) * glm::fract(i / T(41)) - T(1);
		detail::tvec4<T> gy = glm::abs(gx) - T(0.5);
		detail::tvec4<T> tx = glm::floor(gx + T(0.5));
		gx = gx - tx;

		detail::tvec2<T> g00(gx.x, gy.x);
		detail::tvec2<T> g10(gx.y, gy.y);
		detail::tvec2<T> g01(gx.z, gy.z);
		detail::tvec2<T> g11(gx.w, gy.w);

		detail::tvec4<T> norm = taylorInvSqrt(detail::tvec4<T>(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
		g00 *= norm.x;  
		g01 *= norm.y;  
		g10 *= norm.z;  
		g11 *= norm.w;  

		T n00 = dot(g00, detail::tvec2<T>(fx.x, fy.x));
		T n10 = dot(g10, detail::tvec2<T>(fx.y, fy.y));
		T n01 = dot(g01, detail::tvec2<T>(fx.z, fy.z));
		T n11 = dot(g11, detail::tvec2<T>(fx.w, fy.w));

		detail::tvec2<T> fade_xy = fade(detail::tvec2<T>(Pf.x, Pf.y));
		detail::tvec2<T> n_x = mix(detail::tvec2<T>(n00, n01), detail::tvec2<T>(n10, n11), fade_xy.x);
		T n_xy = mix(n_x.x, n_x.y, fade_xy.y);
		return T(2.3) * n_xy;
	}

	// Classic Perlin noise
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec3<T> const & P)
	{
		detail::tvec3<T> Pi0 = floor(P); // Integer part for indexing
		detail::tvec3<T> Pi1 = Pi0 + T(1); // Integer part + 1
		Pi0 = mod289(Pi0);
		Pi1 = mod289(Pi1);
		detail::tvec3<T> Pf0 = fract(P); // Fractional part for interpolation
		detail::tvec3<T> Pf1 = Pf0 - T(1); // Fractional part - 1.0
		detail::tvec4<T> ix(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
		detail::tvec4<T> iy = detail::tvec4<T>(detail::tvec2<T>(Pi0.y), detail::tvec2<T>(Pi1.y));
		detail::tvec4<T> iz0(Pi0.z);
		detail::tvec4<T> iz1(Pi1.z);

		detail::tvec4<T> ixy = permute(permute(ix) + iy);
		detail::tvec4<T> ixy0 = permute(ixy + iz0);
		detail::tvec4<T> ixy1 = permute(ixy + iz1);

		detail::tvec4<T> gx0 = ixy0 * T(1.0 / 7.0);
		detail::tvec4<T> gy0 = fract(floor(gx0) * T(1.0 / 7.0)) - T(0.5);
		gx0 = fract(gx0);
		detail::tvec4<T> gz0 = detail::tvec4<T>(0.5) - abs(gx0) - abs(gy0);
		detail::tvec4<T> sz0 = step(gz0, detail::tvec4<T>(0.0));
		gx0 -= sz0 * (step(T(0), gx0) - T(0.5));
		gy0 -= sz0 * (step(T(0), gy0) - T(0.5));

		detail::tvec4<T> gx1 = ixy1 * T(1.0 / 7.0);
		detail::tvec4<T> gy1 = fract(floor(gx1) * T(1.0 / 7.0)) - T(0.5);
		gx1 = fract(gx1);
		detail::tvec4<T> gz1 = detail::tvec4<T>(0.5) - abs(gx1) - abs(gy1);
		detail::tvec4<T> sz1 = step(gz1, detail::tvec4<T>(0.0));
		gx1 -= sz1 * (step(T(0), gx1) - T(0.5));
		gy1 -= sz1 * (step(T(0), gy1) - T(0.5));

		detail::tvec3<T> g000(gx0.x, gy0.x, gz0.x);
		detail::tvec3<T> g100(gx0.y, gy0.y, gz0.y);
		detail::tvec3<T> g010(gx0.z, gy0.z, gz0.z);
		detail::tvec3<T> g110(gx0.w, gy0.w, gz0.w);
		detail::tvec3<T> g001(gx1.x, gy1.x, gz1.x);
		detail::tvec3<T> g101(gx1.y, gy1.y, gz1.y);
		detail::tvec3<T> g011(gx1.z, gy1.z, gz1.z);
		detail::tvec3<T> g111(gx1.w, gy1.w, gz1.w);

		detail::tvec4<T> norm0 = taylorInvSqrt(detail::tvec4<T>(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
		g000 *= norm0.x;
		g010 *= norm0.y;
		g100 *= norm0.z;
		g110 *= norm0.w;
		detail::tvec4<T> norm1 = taylorInvSqrt(detail::tvec4<T>(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
		g001 *= norm1.x;
		g011 *= norm1.y;
		g101 *= norm1.z;
		g111 *= norm1.w;

		T n000 = dot(g000, Pf0);
		T n100 = dot(g100, detail::tvec3<T>(Pf1.x, Pf0.y, Pf0.z));
		T n010 = dot(g010, detail::tvec3<T>(Pf0.x, Pf1.y, Pf0.z));
		T n110 = dot(g110, detail::tvec3<T>(Pf1.x, Pf1.y, Pf0.z));
		T n001 = dot(g001, detail::tvec3<T>(Pf0.x, Pf0.y, Pf1.z));
		T n101 = dot(g101, detail::tvec3<T>(Pf1.x, Pf0.y, Pf1.z));
		T n011 = dot(g011, detail::tvec3<T>(Pf0.x, Pf1.y, Pf1.z));
		T n111 = dot(g111, Pf1);

		detail::tvec3<T> fade_xyz = fade(Pf0);
		detail::tvec4<T> n_z = mix(detail::tvec4<T>(n000, n100, n010, n110), detail::tvec4<T>(n001, n101, n011, n111), fade_xyz.z);
		detail::tvec2<T> n_yz = mix(detail::tvec2<T>(n_z.x, n_z.y), detail::tvec2<T>(n_z.z, n_z.w), fade_xyz.y);
		T n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); 
		return T(2.2) * n_xyz;
	}
	/*
	// Classic Perlin noise
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec3<T> const & P)
	{
		detail::tvec3<T> Pi0 = floor(P); // Integer part for indexing
		detail::tvec3<T> Pi1 = Pi0 + T(1); // Integer part + 1
		Pi0 = mod(Pi0, T(289));
		Pi1 = mod(Pi1, T(289));
		detail::tvec3<T> Pf0 = fract(P); // Fractional part for interpolation
		detail::tvec3<T> Pf1 = Pf0 - T(1); // Fractional part - 1.0
		detail::tvec4<T> ix(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
		detail::tvec4<T> iy(Pi0.y, Pi0.y, Pi1.y, Pi1.y);
		detail::tvec4<T> iz0(Pi0.z);
		detail::tvec4<T> iz1(Pi1.z);

		detail::tvec4<T> ixy = permute(permute(ix) + iy);
		detail::tvec4<T> ixy0 = permute(ixy + iz0);
		detail::tvec4<T> ixy1 = permute(ixy + iz1);

		detail::tvec4<T> gx0 = ixy0 / T(7);
		detail::tvec4<T> gy0 = fract(floor(gx0) / T(7)) - T(0.5);
		gx0 = fract(gx0);
		detail::tvec4<T> gz0 = detail::tvec4<T>(0.5) - abs(gx0) - abs(gy0);
		detail::tvec4<T> sz0 = step(gz0, detail::tvec4<T>(0.0));
		gx0 -= sz0 * (step(0.0, gx0) - T(0.5));
		gy0 -= sz0 * (step(0.0, gy0) - T(0.5));

		detail::tvec4<T> gx1 = ixy1 / T(7);
		detail::tvec4<T> gy1 = fract(floor(gx1) / T(7)) - T(0.5);
		gx1 = fract(gx1);
		detail::tvec4<T> gz1 = detail::tvec4<T>(0.5) - abs(gx1) - abs(gy1);
		detail::tvec4<T> sz1 = step(gz1, detail::tvec4<T>(0.0));
		gx1 -= sz1 * (step(T(0), gx1) - T(0.5));
		gy1 -= sz1 * (step(T(0), gy1) - T(0.5));

		detail::tvec3<T> g000(gx0.x, gy0.x, gz0.x);
		detail::tvec3<T> g100(gx0.y, gy0.y, gz0.y);
		detail::tvec3<T> g010(gx0.z, gy0.z, gz0.z);
		detail::tvec3<T> g110(gx0.w, gy0.w, gz0.w);
		detail::tvec3<T> g001(gx1.x, gy1.x, gz1.x);
		detail::tvec3<T> g101(gx1.y, gy1.y, gz1.y);
		detail::tvec3<T> g011(gx1.z, gy1.z, gz1.z);
		detail::tvec3<T> g111(gx1.w, gy1.w, gz1.w);

		detail::tvec4<T> norm0 = taylorInvSqrt(detail::tvec4<T>(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
		g000 *= norm0.x;
		g010 *= norm0.y;
		g100 *= norm0.z;
		g110 *= norm0.w;
		detail::tvec4<T> norm1 = taylorInvSqrt(detail::tvec4<T>(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
		g001 *= norm1.x;
		g011 *= norm1.y;
		g101 *= norm1.z;
		g111 *= norm1.w;

		T n000 = dot(g000, Pf0);
		T n100 = dot(g100, detail::tvec3<T>(Pf1.x, Pf0.y, Pf0.z));
		T n010 = dot(g010, detail::tvec3<T>(Pf0.x, Pf1.y, Pf0.z));
		T n110 = dot(g110, detail::tvec3<T>(Pf1.x, Pf1.y, Pf0.z));
		T n001 = dot(g001, detail::tvec3<T>(Pf0.x, Pf0.y, Pf1.z));
		T n101 = dot(g101, detail::tvec3<T>(Pf1.x, Pf0.y, Pf1.z));
		T n011 = dot(g011, detail::tvec3<T>(Pf0.x, Pf1.y, Pf1.z));
		T n111 = dot(g111, Pf1);

		detail::tvec3<T> fade_xyz = fade(Pf0);
		detail::tvec4<T> n_z = mix(detail::tvec4<T>(n000, n100, n010, n110), detail::tvec4<T>(n001, n101, n011, n111), fade_xyz.z);
		detail::tvec2<T> n_yz = mix(
			detail::tvec2<T>(n_z.x, n_z.y), 
			detail::tvec2<T>(n_z.z, n_z.w), fade_xyz.y);
		T n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); 
		return T(2.2) * n_xyz;
	}
	*/
	// Classic Perlin noise
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec4<T> const & P)
	{
		detail::tvec4<T> Pi0 = floor(P); // Integer part for indexing
		detail::tvec4<T> Pi1 = Pi0 + T(1); // Integer part + 1
		Pi0 = mod(Pi0, T(289));
		Pi1 = mod(Pi1, T(289));
		detail::tvec4<T> Pf0 = fract(P); // Fractional part for interpolation
		detail::tvec4<T> Pf1 = Pf0 - T(1); // Fractional part - 1.0
		detail::tvec4<T> ix(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
		detail::tvec4<T> iy(Pi0.y, Pi0.y, Pi1.y, Pi1.y);
		detail::tvec4<T> iz0(Pi0.z);
		detail::tvec4<T> iz1(Pi1.z);
		detail::tvec4<T> iw0(Pi0.w);
		detail::tvec4<T> iw1(Pi1.w);

		detail::tvec4<T> ixy = permute(permute(ix) + iy);
		detail::tvec4<T> ixy0 = permute(ixy + iz0);
		detail::tvec4<T> ixy1 = permute(ixy + iz1);
		detail::tvec4<T> ixy00 = permute(ixy0 + iw0);
		detail::tvec4<T> ixy01 = permute(ixy0 + iw1);
		detail::tvec4<T> ixy10 = permute(ixy1 + iw0);
		detail::tvec4<T> ixy11 = permute(ixy1 + iw1);

		detail::tvec4<T> gx00 = ixy00 / T(7);
		detail::tvec4<T> gy00 = floor(gx00) / T(7);
		detail::tvec4<T> gz00 = floor(gy00) / T(6);
		gx00 = fract(gx00) - T(0.5);
		gy00 = fract(gy00) - T(0.5);
		gz00 = fract(gz00) - T(0.5);
		detail::tvec4<T> gw00 = detail::tvec4<T>(0.75) - abs(gx00) - abs(gy00) - abs(gz00);
		detail::tvec4<T> sw00 = step(gw00, detail::tvec4<T>(0.0));
		gx00 -= sw00 * (step(T(0), gx00) - T(0.5));
		gy00 -= sw00 * (step(T(0), gy00) - T(0.5));

		detail::tvec4<T> gx01 = ixy01 / T(7);
		detail::tvec4<T> gy01 = floor(gx01) / T(7);
		detail::tvec4<T> gz01 = floor(gy01) / T(6);
		gx01 = fract(gx01) - T(0.5);
		gy01 = fract(gy01) - T(0.5);
		gz01 = fract(gz01) - T(0.5);
		detail::tvec4<T> gw01 = detail::tvec4<T>(0.75) - abs(gx01) - abs(gy01) - abs(gz01);
		detail::tvec4<T> sw01 = step(gw01, detail::tvec4<T>(0.0));
		gx01 -= sw01 * (step(T(0), gx01) - T(0.5));
		gy01 -= sw01 * (step(T(0), gy01) - T(0.5));

		detail::tvec4<T> gx10 = ixy10 / T(7);
		detail::tvec4<T> gy10 = floor(gx10) / T(7);
		detail::tvec4<T> gz10 = floor(gy10) / T(6);
		gx10 = fract(gx10) - T(0.5);
		gy10 = fract(gy10) - T(0.5);
		gz10 = fract(gz10) - T(0.5);
		detail::tvec4<T> gw10 = detail::tvec4<T>(0.75) - abs(gx10) - abs(gy10) - abs(gz10);
		detail::tvec4<T> sw10 = step(gw10, detail::tvec4<T>(0));
		gx10 -= sw10 * (step(T(0), gx10) - T(0.5));
		gy10 -= sw10 * (step(T(0), gy10) - T(0.5));

		detail::tvec4<T> gx11 = ixy11 / T(7);
		detail::tvec4<T> gy11 = floor(gx11) / T(7);
		detail::tvec4<T> gz11 = floor(gy11) / T(6);
		gx11 = fract(gx11) - T(0.5);
		gy11 = fract(gy11) - T(0.5);
		gz11 = fract(gz11) - T(0.5);
		detail::tvec4<T> gw11 = detail::tvec4<T>(0.75) - abs(gx11) - abs(gy11) - abs(gz11);
		detail::tvec4<T> sw11 = step(gw11, detail::tvec4<T>(0.0));
		gx11 -= sw11 * (step(T(0), gx11) - T(0.5));
		gy11 -= sw11 * (step(T(0), gy11) - T(0.5));

		detail::tvec4<T> g0000(gx00.x, gy00.x, gz00.x, gw00.x);
		detail::tvec4<T> g1000(gx00.y, gy00.y, gz00.y, gw00.y);
		detail::tvec4<T> g0100(gx00.z, gy00.z, gz00.z, gw00.z);
		detail::tvec4<T> g1100(gx00.w, gy00.w, gz00.w, gw00.w);
		detail::tvec4<T> g0010(gx10.x, gy10.x, gz10.x, gw10.x);
		detail::tvec4<T> g1010(gx10.y, gy10.y, gz10.y, gw10.y);
		detail::tvec4<T> g0110(gx10.z, gy10.z, gz10.z, gw10.z);
		detail::tvec4<T> g1110(gx10.w, gy10.w, gz10.w, gw10.w);
		detail::tvec4<T> g0001(gx01.x, gy01.x, gz01.x, gw01.x);
		detail::tvec4<T> g1001(gx01.y, gy01.y, gz01.y, gw01.y);
		detail::tvec4<T> g0101(gx01.z, gy01.z, gz01.z, gw01.z);
		detail::tvec4<T> g1101(gx01.w, gy01.w, gz01.w, gw01.w);
		detail::tvec4<T> g0011(gx11.x, gy11.x, gz11.x, gw11.x);
		detail::tvec4<T> g1011(gx11.y, gy11.y, gz11.y, gw11.y);
		detail::tvec4<T> g0111(gx11.z, gy11.z, gz11.z, gw11.z);
		detail::tvec4<T> g1111(gx11.w, gy11.w, gz11.w, gw11.w);

		detail::tvec4<T> norm00 = taylorInvSqrt(detail::tvec4<T>(dot(g0000, g0000), dot(g0100, g0100), dot(g1000, g1000), dot(g1100, g1100)));
		g0000 *= norm00.x;
		g0100 *= norm00.y;
		g1000 *= norm00.z;
		g1100 *= norm00.w;

		detail::tvec4<T> norm01 = taylorInvSqrt(detail::tvec4<T>(dot(g0001, g0001), dot(g0101, g0101), dot(g1001, g1001), dot(g1101, g1101)));
		g0001 *= norm01.x;
		g0101 *= norm01.y;
		g1001 *= norm01.z;
		g1101 *= norm01.w;

		detail::tvec4<T> norm10 = taylorInvSqrt(detail::tvec4<T>(dot(g0010, g0010), dot(g0110, g0110), dot(g1010, g1010), dot(g1110, g1110)));
		g0010 *= norm10.x;
		g0110 *= norm10.y;
		g1010 *= norm10.z;
		g1110 *= norm10.w;

		detail::tvec4<T> norm11 = taylorInvSqrt(detail::tvec4<T>(dot(g0011, g0011), dot(g0111, g0111), dot(g1011, g1011), dot(g1111, g1111)));
		g0011 *= norm11.x;
		g0111 *= norm11.y;
		g1011 *= norm11.z;
		g1111 *= norm11.w;

		T n0000 = dot(g0000, Pf0);
		T n1000 = dot(g1000, detail::tvec4<T>(Pf1.x, Pf0.y, Pf0.z, Pf0.w));
		T n0100 = dot(g0100, detail::tvec4<T>(Pf0.x, Pf1.y, Pf0.z, Pf0.w));
		T n1100 = dot(g1100, detail::tvec4<T>(Pf1.x, Pf1.y, Pf0.z, Pf0.w));
		T n0010 = dot(g0010, detail::tvec4<T>(Pf0.x, Pf0.y, Pf1.z, Pf0.w));
		T n1010 = dot(g1010, detail::tvec4<T>(Pf1.x, Pf0.y, Pf1.z, Pf0.w));
		T n0110 = dot(g0110, detail::tvec4<T>(Pf0.x, Pf1.y, Pf1.z, Pf0.w));
		T n1110 = dot(g1110, detail::tvec4<T>(Pf1.x, Pf1.y, Pf1.z, Pf0.w));
		T n0001 = dot(g0001, detail::tvec4<T>(Pf0.x, Pf0.y, Pf0.z, Pf1.w));
		T n1001 = dot(g1001, detail::tvec4<T>(Pf1.x, Pf0.y, Pf0.z, Pf1.w));
		T n0101 = dot(g0101, detail::tvec4<T>(Pf0.x, Pf1.y, Pf0.z, Pf1.w));
		T n1101 = dot(g1101, detail::tvec4<T>(Pf1.x, Pf1.y, Pf0.z, Pf1.w));
		T n0011 = dot(g0011, detail::tvec4<T>(Pf0.x, Pf0.y, Pf1.z, Pf1.w));
		T n1011 = dot(g1011, detail::tvec4<T>(Pf1.x, Pf0.y, Pf1.z, Pf1.w));
		T n0111 = dot(g0111, detail::tvec4<T>(Pf0.x, Pf1.y, Pf1.z, Pf1.w));
		T n1111 = dot(g1111, Pf1);

		detail::tvec4<T> fade_xyzw = fade(Pf0);
		detail::tvec4<T> n_0w = mix(detail::tvec4<T>(n0000, n1000, n0100, n1100), detail::tvec4<T>(n0001, n1001, n0101, n1101), fade_xyzw.w);
		detail::tvec4<T> n_1w = mix(detail::tvec4<T>(n0010, n1010, n0110, n1110), detail::tvec4<T>(n0011, n1011, n0111, n1111), fade_xyzw.w);
		detail::tvec4<T> n_zw = mix(n_0w, n_1w, fade_xyzw.z);
		detail::tvec2<T> n_yzw = mix(detail::tvec2<T>(n_zw.x, n_zw.y), detail::tvec2<T>(n_zw.z, n_zw.w), fade_xyzw.y);
		T n_xyzw = mix(n_yzw.x, n_yzw.y, fade_xyzw.x);
		return T(2.2) * n_xyzw;
	}

	// Classic Perlin noise, periodic variant
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec2<T> const & P, detail::tvec2<T> const & rep)
	{
		detail::tvec4<T> Pi = floor(detail::tvec4<T>(P.x, P.y, P.x, P.y)) + detail::tvec4<T>(0.0, 0.0, 1.0, 1.0);
		detail::tvec4<T> Pf = fract(detail::tvec4<T>(P.x, P.y, P.x, P.y)) - detail::tvec4<T>(0.0, 0.0, 1.0, 1.0);
		Pi = mod(Pi, detail::tvec4<T>(rep.x, rep.y, rep.x, rep.y)); // To create noise with explicit period
		Pi = mod(Pi, T(289)); // To avoid truncation effects in permutation
		detail::tvec4<T> ix(Pi.x, Pi.z, Pi.x, Pi.z);
		detail::tvec4<T> iy(Pi.y, Pi.y, Pi.w, Pi.w);
		detail::tvec4<T> fx(Pf.x, Pf.z, Pf.x, Pf.z);
		detail::tvec4<T> fy(Pf.y, Pf.y, Pf.w, Pf.w);

		detail::tvec4<T> i = permute(permute(ix) + iy);

		detail::tvec4<T> gx = T(2) * fract(i / T(41)) - T(1);
		detail::tvec4<T> gy = abs(gx) - T(0.5);
		detail::tvec4<T> tx = floor(gx + T(0.5));
		gx = gx - tx;

		detail::tvec2<T> g00(gx.x, gy.x);
		detail::tvec2<T> g10(gx.y, gy.y);
		detail::tvec2<T> g01(gx.z, gy.z);
		detail::tvec2<T> g11(gx.w, gy.w);

		detail::tvec4<T> norm = taylorInvSqrt(detail::tvec4<T>(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
		g00 *= norm.x;  
		g01 *= norm.y;  
		g10 *= norm.z;  
		g11 *= norm.w;  

		T n00 = dot(g00, detail::tvec2<T>(fx.x, fy.x));
		T n10 = dot(g10, detail::tvec2<T>(fx.y, fy.y));
		T n01 = dot(g01, detail::tvec2<T>(fx.z, fy.z));
		T n11 = dot(g11, detail::tvec2<T>(fx.w, fy.w));

		detail::tvec2<T> fade_xy = fade(detail::tvec2<T>(Pf.x, Pf.y));
		detail::tvec2<T> n_x = mix(detail::tvec2<T>(n00, n01), detail::tvec2<T>(n10, n11), fade_xy.x);
		T n_xy = mix(n_x.x, n_x.y, fade_xy.y);
		return T(2.3) * n_xy;
	}

	// Classic Perlin noise, periodic variant
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec3<T> const & P, detail::tvec3<T> const & rep)
	{
		detail::tvec3<T> Pi0 = mod(floor(P), rep); // Integer part, modulo period
		detail::tvec3<T> Pi1 = mod(Pi0 + detail::tvec3<T>(1.0), rep); // Integer part + 1, mod period
		Pi0 = mod(Pi0, T(289));
		Pi1 = mod(Pi1, T(289));
		detail::tvec3<T> Pf0 = fract(P); // Fractional part for interpolation
		detail::tvec3<T> Pf1 = Pf0 - detail::tvec3<T>(1.0); // Fractional part - 1.0
		detail::tvec4<T> ix = detail::tvec4<T>(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
		detail::tvec4<T> iy = detail::tvec4<T>(Pi0.y, Pi0.y, Pi1.y, Pi1.y);
		detail::tvec4<T> iz0(Pi0.z);
		detail::tvec4<T> iz1(Pi1.z);

		detail::tvec4<T> ixy = permute(permute(ix) + iy);
		detail::tvec4<T> ixy0 = permute(ixy + iz0);
		detail::tvec4<T> ixy1 = permute(ixy + iz1);

		detail::tvec4<T> gx0 = ixy0 / T(7);
		detail::tvec4<T> gy0 = fract(floor(gx0) / T(7)) - T(0.5);
		gx0 = fract(gx0);
		detail::tvec4<T> gz0 = detail::tvec4<T>(0.5) - abs(gx0) - abs(gy0);
		detail::tvec4<T> sz0 = step(gz0, detail::tvec4<T>(0));
		gx0 -= sz0 * (step(0.0, gx0) - T(0.5));
		gy0 -= sz0 * (step(0.0, gy0) - T(0.5));

		detail::tvec4<T> gx1 = ixy1 / T(7);
		detail::tvec4<T> gy1 = fract(floor(gx1) / T(7)) - T(0.5);
		gx1 = fract(gx1);
		detail::tvec4<T> gz1 = detail::tvec4<T>(0.5) - abs(gx1) - abs(gy1);
		detail::tvec4<T> sz1 = step(gz1, detail::tvec4<T>(0.0));
		gx1 -= sz1 * (step(0.0, gx1) - T(0.5));
		gy1 -= sz1 * (step(0.0, gy1) - T(0.5));

		detail::tvec3<T> g000 = detail::tvec3<T>(gx0.x, gy0.x, gz0.x);
		detail::tvec3<T> g100 = detail::tvec3<T>(gx0.y, gy0.y, gz0.y);
		detail::tvec3<T> g010 = detail::tvec3<T>(gx0.z, gy0.z, gz0.z);
		detail::tvec3<T> g110 = detail::tvec3<T>(gx0.w, gy0.w, gz0.w);
		detail::tvec3<T> g001 = detail::tvec3<T>(gx1.x, gy1.x, gz1.x);
		detail::tvec3<T> g101 = detail::tvec3<T>(gx1.y, gy1.y, gz1.y);
		detail::tvec3<T> g011 = detail::tvec3<T>(gx1.z, gy1.z, gz1.z);
		detail::tvec3<T> g111 = detail::tvec3<T>(gx1.w, gy1.w, gz1.w);

		detail::tvec4<T> norm0 = taylorInvSqrt(detail::tvec4<T>(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
		g000 *= norm0.x;
		g010 *= norm0.y;
		g100 *= norm0.z;
		g110 *= norm0.w;
		detail::tvec4<T> norm1 = taylorInvSqrt(detail::tvec4<T>(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
		g001 *= norm1.x;
		g011 *= norm1.y;
		g101 *= norm1.z;
		g111 *= norm1.w;

		T n000 = dot(g000, Pf0);
		T n100 = dot(g100, detail::tvec3<T>(Pf1.x, Pf0.y, Pf0.z));
		T n010 = dot(g010, detail::tvec3<T>(Pf0.x, Pf1.y, Pf0.z));
		T n110 = dot(g110, detail::tvec3<T>(Pf1.x, Pf1.y, Pf0.z));
		T n001 = dot(g001, detail::tvec3<T>(Pf0.x, Pf0.y, Pf1.z));
		T n101 = dot(g101, detail::tvec3<T>(Pf1.x, Pf0.y, Pf1.z));
		T n011 = dot(g011, detail::tvec3<T>(Pf0.x, Pf1.y, Pf1.z));
		T n111 = dot(g111, Pf1);

		detail::tvec3<T> fade_xyz = fade(Pf0);
		detail::tvec4<T> n_z = mix(detail::tvec4<T>(n000, n100, n010, n110), detail::tvec4<T>(n001, n101, n011, n111), fade_xyz.z);
		detail::tvec2<T> n_yz = mix(detail::tvec2<T>(n_z.x, n_z.y), detail::tvec2<T>(n_z.z, n_z.w), fade_xyz.y);
		T n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); 
		return T(2.2) * n_xyz;
	}

	// Classic Perlin noise, periodic version
	template <typename T>
	GLM_FUNC_QUALIFIER T perlin(detail::tvec4<T> const & P, detail::tvec4<T> const & rep)
	{
		detail::tvec4<T> Pi0 = mod(floor(P), rep); // Integer part modulo rep
		detail::tvec4<T> Pi1 = mod(Pi0 + T(1), rep); // Integer part + 1 mod rep
		detail::tvec4<T> Pf0 = fract(P); // Fractional part for interpolation
		detail::tvec4<T> Pf1 = Pf0 - T(1); // Fractional part - 1.0
		detail::tvec4<T> ix = detail::tvec4<T>(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
		detail::tvec4<T> iy = detail::tvec4<T>(Pi0.y, Pi0.y, Pi1.y, Pi1.y);
		detail::tvec4<T> iz0(Pi0.z);
		detail::tvec4<T> iz1(Pi1.z);
		detail::tvec4<T> iw0(Pi0.w);
		detail::tvec4<T> iw1(Pi1.w);

		detail::tvec4<T> ixy = permute(permute(ix) + iy);
		detail::tvec4<T> ixy0 = permute(ixy + iz0);
		detail::tvec4<T> ixy1 = permute(ixy + iz1);
		detail::tvec4<T> ixy00 = permute(ixy0 + iw0);
		detail::tvec4<T> ixy01 = permute(ixy0 + iw1);
		detail::tvec4<T> ixy10 = permute(ixy1 + iw0);
		detail::tvec4<T> ixy11 = permute(ixy1 + iw1);

		detail::tvec4<T> gx00 = ixy00 / T(7);
		detail::tvec4<T> gy00 = floor(gx00) / T(7);
		detail::tvec4<T> gz00 = floor(gy00) / T(6);
		gx00 = fract(gx00) - T(0.5);
		gy00 = fract(gy00) - T(0.5);
		gz00 = fract(gz00) - T(0.5);
		detail::tvec4<T> gw00 = detail::tvec4<T>(0.75) - abs(gx00) - abs(gy00) - abs(gz00);
		detail::tvec4<T> sw00 = step(gw00, detail::tvec4<T>(0));
		gx00 -= sw00 * (step(0.0, gx00) - T(0.5));
		gy00 -= sw00 * (step(0.0, gy00) - T(0.5));

		detail::tvec4<T> gx01 = ixy01 / T(7);
		detail::tvec4<T> gy01 = floor(gx01) / T(7);
		detail::tvec4<T> gz01 = floor(gy01) / T(6);
		gx01 = fract(gx01) - T(0.5);
		gy01 = fract(gy01) - T(0.5);
		gz01 = fract(gz01) - T(0.5);
		detail::tvec4<T> gw01 = detail::tvec4<T>(0.75) - abs(gx01) - abs(gy01) - abs(gz01);
		detail::tvec4<T> sw01 = step(gw01, detail::tvec4<T>(0.0));
		gx01 -= sw01 * (step(0.0, gx01) - T(0.5));
		gy01 -= sw01 * (step(0.0, gy01) - T(0.5));

		detail::tvec4<T> gx10 = ixy10 / T(7);
		detail::tvec4<T> gy10 = floor(gx10) / T(7);
		detail::tvec4<T> gz10 = floor(gy10) / T(6);
		gx10 = fract(gx10) - T(0.5);
		gy10 = fract(gy10) - T(0.5);
		gz10 = fract(gz10) - T(0.5);
		detail::tvec4<T> gw10 = detail::tvec4<T>(0.75) - abs(gx10) - abs(gy10) - abs(gz10);
		detail::tvec4<T> sw10 = step(gw10, detail::tvec4<T>(0.0));
		gx10 -= sw10 * (step(0.0, gx10) - T(0.5));
		gy10 -= sw10 * (step(0.0, gy10) - T(0.5));

		detail::tvec4<T> gx11 = ixy11 / T(7);
		detail::tvec4<T> gy11 = floor(gx11) / T(7);
		detail::tvec4<T> gz11 = floor(gy11) / T(6);
		gx11 = fract(gx11) - T(0.5);
		gy11 = fract(gy11) - T(0.5);
		gz11 = fract(gz11) - T(0.5);
		detail::tvec4<T> gw11 = detail::tvec4<T>(0.75) - abs(gx11) - abs(gy11) - abs(gz11);
		detail::tvec4<T> sw11 = step(gw11, detail::tvec4<T>(0.0));
		gx11 -= sw11 * (step(0.0, gx11) - T(0.5));
		gy11 -= sw11 * (step(0.0, gy11) - T(0.5));

		detail::tvec4<T> g0000(gx00.x, gy00.x, gz00.x, gw00.x);
		detail::tvec4<T> g1000(gx00.y, gy00.y, gz00.y, gw00.y);
		detail::tvec4<T> g0100(gx00.z, gy00.z, gz00.z, gw00.z);
		detail::tvec4<T> g1100(gx00.w, gy00.w, gz00.w, gw00.w);
		detail::tvec4<T> g0010(gx10.x, gy10.x, gz10.x, gw10.x);
		detail::tvec4<T> g1010(gx10.y, gy10.y, gz10.y, gw10.y);
		detail::tvec4<T> g0110(gx10.z, gy10.z, gz10.z, gw10.z);
		detail::tvec4<T> g1110(gx10.w, gy10.w, gz10.w, gw10.w);
		detail::tvec4<T> g0001(gx01.x, gy01.x, gz01.x, gw01.x);
		detail::tvec4<T> g1001(gx01.y, gy01.y, gz01.y, gw01.y);
		detail::tvec4<T> g0101(gx01.z, gy01.z, gz01.z, gw01.z);
		detail::tvec4<T> g1101(gx01.w, gy01.w, gz01.w, gw01.w);
		detail::tvec4<T> g0011(gx11.x, gy11.x, gz11.x, gw11.x);
		detail::tvec4<T> g1011(gx11.y, gy11.y, gz11.y, gw11.y);
		detail::tvec4<T> g0111(gx11.z, gy11.z, gz11.z, gw11.z);
		detail::tvec4<T> g1111(gx11.w, gy11.w, gz11.w, gw11.w);

		detail::tvec4<T> norm00 = taylorInvSqrt(detail::tvec4<T>(dot(g0000, g0000), dot(g0100, g0100), dot(g1000, g1000), dot(g1100, g1100)));
		g0000 *= norm00.x;
		g0100 *= norm00.y;
		g1000 *= norm00.z;
		g1100 *= norm00.w;

		detail::tvec4<T> norm01 = taylorInvSqrt(detail::tvec4<T>(dot(g0001, g0001), dot(g0101, g0101), dot(g1001, g1001), dot(g1101, g1101)));
		g0001 *= norm01.x;
		g0101 *= norm01.y;
		g1001 *= norm01.z;
		g1101 *= norm01.w;

		detail::tvec4<T> norm10 = taylorInvSqrt(detail::tvec4<T>(dot(g0010, g0010), dot(g0110, g0110), dot(g1010, g1010), dot(g1110, g1110)));
		g0010 *= norm10.x;
		g0110 *= norm10.y;
		g1010 *= norm10.z;
		g1110 *= norm10.w;

		detail::tvec4<T> norm11 = taylorInvSqrt(detail::tvec4<T>(dot(g0011, g0011), dot(g0111, g0111), dot(g1011, g1011), dot(g1111, g1111)));
		g0011 *= norm11.x;
		g0111 *= norm11.y;
		g1011 *= norm11.z;
		g1111 *= norm11.w;

		T n0000 = dot(g0000, Pf0);
		T n1000 = dot(g1000, detail::tvec4<T>(Pf1.x, Pf0.y, Pf0.z, Pf0.w));
		T n0100 = dot(g0100, detail::tvec4<T>(Pf0.x, Pf1.y, Pf0.z, Pf0.w));
		T n1100 = dot(g1100, detail::tvec4<T>(Pf1.x, Pf1.y, Pf0.z, Pf0.w));
		T n0010 = dot(g0010, detail::tvec4<T>(Pf0.x, Pf0.y, Pf1.z, Pf0.w));
		T n1010 = dot(g1010, detail::tvec4<T>(Pf1.x, Pf0.y, Pf1.z, Pf0.w));
		T n0110 = dot(g0110, detail::tvec4<T>(Pf0.x, Pf1.y, Pf1.z, Pf0.w));
		T n1110 = dot(g1110, detail::tvec4<T>(Pf1.x, Pf1.y, Pf1.z, Pf0.w));
		T n0001 = dot(g0001, detail::tvec4<T>(Pf0.x, Pf0.y, Pf0.z, Pf1.w));
		T n1001 = dot(g1001, detail::tvec4<T>(Pf1.x, Pf0.y, Pf0.z, Pf1.w));
		T n0101 = dot(g0101, detail::tvec4<T>(Pf0.x, Pf1.y, Pf0.z, Pf1.w));
		T n1101 = dot(g1101, detail::tvec4<T>(Pf1.x, Pf1.y, Pf0.z, Pf1.w));
		T n0011 = dot(g0011, detail::tvec4<T>(Pf0.x, Pf0.y, Pf1.z, Pf1.w));
		T n1011 = dot(g1011, detail::tvec4<T>(Pf1.x, Pf0.y, Pf1.z, Pf1.w));
		T n0111 = dot(g0111, detail::tvec4<T>(Pf0.x, Pf1.y, Pf1.z, Pf1.w));
		T n1111 = dot(g1111, Pf1);

		detail::tvec4<T> fade_xyzw = fade(Pf0);
		detail::tvec4<T> n_0w = mix(detail::tvec4<T>(n0000, n1000, n0100, n1100), detail::tvec4<T>(n0001, n1001, n0101, n1101), fade_xyzw.w);
		detail::tvec4<T> n_1w = mix(detail::tvec4<T>(n0010, n1010, n0110, n1110), detail::tvec4<T>(n0011, n1011, n0111, n1111), fade_xyzw.w);
		detail::tvec4<T> n_zw = mix(n_0w, n_1w, fade_xyzw.z);
		detail::tvec2<T> n_yzw = mix(detail::tvec2<T>(n_zw.x, n_zw.y), detail::tvec2<T>(n_zw.z, n_zw.w), fade_xyzw.y);
		T n_xyzw = mix(n_yzw.x, n_yzw.y, fade_xyzw.x);
		return T(2.2) * n_xyzw;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T simplex(glm::detail::tvec2<T> const & v)
	{
		detail::tvec4<T> const C = detail::tvec4<T>(
			T( 0.211324865405187),  // (3.0 -  sqrt(3.0)) / 6.0
			T( 0.366025403784439),  //  0.5 * (sqrt(3.0)  - 1.0)
			T(-0.577350269189626),	// -1.0 + 2.0 * C.x
			T( 0.024390243902439)); //  1.0 / 41.0

		// First corner
		detail::tvec2<T> i  = floor(v + dot(v, detail::tvec2<T>(C[1])));
		detail::tvec2<T> x0 = v -   i + dot(i, detail::tvec2<T>(C[0]));

		// Other corners
		//i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
		//i1.y = 1.0 - i1.x;
		detail::tvec2<T> i1 = (x0.x > x0.y) ? detail::tvec2<T>(1, 0) : detail::tvec2<T>(0, 1);
		// x0 = x0 - 0.0 + 0.0 * C.xx ;
		// x1 = x0 - i1 + 1.0 * C.xx ;
		// x2 = x0 - 1.0 + 2.0 * C.xx ;
		detail::tvec4<T> x12 = detail::tvec4<T>(x0.x, x0.y, x0.x, x0.y) + detail::tvec4<T>(C.x, C.x, C.z, C.z);
		x12 = detail::tvec4<T>(detail::tvec2<T>(x12) - i1, x12.z, x12.w);

		// Permutations
		i = mod(i, T(289)); // Avoid truncation effects in permutation
		detail::tvec3<T> p = permute(
			permute(i.y + detail::tvec3<T>(T(0), i1.y, T(1)))
			+ i.x + detail::tvec3<T>(T(0), i1.x, T(1)));

		detail::tvec3<T> m = max(T(0.5) - detail::tvec3<T>(
			dot(x0, x0), 
			dot(detail::tvec2<T>(x12.x, x12.y), detail::tvec2<T>(x12.x, x12.y)), 
			dot(detail::tvec2<T>(x12.z, x12.w), detail::tvec2<T>(x12.z, x12.w))), T(0));
		m = m * m ;
		m = m * m ;

		// Gradients: 41 points uniformly over a line, mapped onto a diamond.
		// The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)

		detail::tvec3<T> x = T(2) * fract(p * C.w) - T(1);
		detail::tvec3<T> h = abs(x) - T(0.5);
		detail::tvec3<T> ox = floor(x + T(0.5));
		detail::tvec3<T> a0 = x - ox;

		// Normalise gradients implicitly by scaling m
		// Inlined for speed: m *= taylorInvSqrt( a0*a0 + h*h );
		m *= T(1.79284291400159) - T(0.85373472095314) * (a0 * a0 + h * h);

		// Compute final noise value at P
		detail::tvec3<T> g;
		g.x  = a0.x  * x0.x  + h.x  * x0.y;
		//g.yz = a0.yz * x12.xz + h.yz * x12.yw;
		g.y = a0.y * x12.x + h.y * x12.y;
		g.z = a0.z * x12.z + h.z * x12.w;
		return T(130) * dot(m, g);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T simplex(detail::tvec3<T> const & v)
	{ 
		detail::tvec2<T> const C(1.0 / 6.0, 1.0 / 3.0);
		detail::tvec4<T> const D(0.0, 0.5, 1.0, 2.0);

		// First corner
		detail::tvec3<T> i(floor(v + dot(v, detail::tvec3<T>(C.y))));
		detail::tvec3<T> x0(v - i + dot(i, detail::tvec3<T>(C.x)));

		// Other corners
		detail::tvec3<T> g(step(detail::tvec3<T>(x0.y, x0.z, x0.x), x0));
		detail::tvec3<T> l(T(1) - g);
		detail::tvec3<T> i1(min(g, detail::tvec3<T>(l.z, l.x, l.y)));
		detail::tvec3<T> i2(max(g, detail::tvec3<T>(l.z, l.x, l.y)));

		//   x0 = x0 - 0.0 + 0.0 * C.xxx;
		//   x1 = x0 - i1  + 1.0 * C.xxx;
		//   x2 = x0 - i2  + 2.0 * C.xxx;
		//   x3 = x0 - 1.0 + 3.0 * C.xxx;
		detail::tvec3<T> x1(x0 - i1 + C.x);
		detail::tvec3<T> x2(x0 - i2 + C.y); // 2.0*C.x = 1/3 = C.y
		detail::tvec3<T> x3(x0 - D.y);      // -1.0+3.0*C.x = -0.5 = -D.y

		// Permutations
		i = mod289(i); 
		detail::tvec4<T> p(permute(permute(permute( 
			i.z + detail::tvec4<T>(T(0), i1.z, i2.z, T(1))) + 
			i.y + detail::tvec4<T>(T(0), i1.y, i2.y, T(1))) + 
			i.x + detail::tvec4<T>(T(0), i1.x, i2.x, T(1))));

		// Gradients: 7x7 points over a square, mapped onto an octahedron.
		// The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
		T n_ = T(0.142857142857); // 1.0/7.0
		detail::tvec3<T> ns(n_ * detail::tvec3<T>(D.w, D.y, D.z) - detail::tvec3<T>(D.x, D.z, D.x));

		detail::tvec4<T> j(p - T(49) * floor(p * ns.z * ns.z));  //  mod(p,7*7)

		detail::tvec4<T> x_(floor(j * ns.z));
		detail::tvec4<T> y_(floor(j - T(7) * x_));    // mod(j,N)

		detail::tvec4<T> x(x_ * ns.x + ns.y);
		detail::tvec4<T> y(y_ * ns.x + ns.y);
		detail::tvec4<T> h(T(1) - abs(x) - abs(y));

		detail::tvec4<T> b0(x.x, x.y, y.x, y.y);
		detail::tvec4<T> b1(x.z, x.w, y.z, y.w);

		// vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
		// vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
		detail::tvec4<T> s0(floor(b0) * T(2) + T(1));
		detail::tvec4<T> s1(floor(b1) * T(2) + T(1));
		detail::tvec4<T> sh(-step(h, detail::tvec4<T>(0.0)));

		detail::tvec4<T> a0 = detail::tvec4<T>(b0.x, b0.z, b0.y, b0.w) + detail::tvec4<T>(s0.x, s0.z, s0.y, s0.w) * detail::tvec4<T>(sh.x, sh.x, sh.y, sh.y);
		detail::tvec4<T> a1 = detail::tvec4<T>(b1.x, b1.z, b1.y, b1.w) + detail::tvec4<T>(s1.x, s1.z, s1.y, s1.w) * detail::tvec4<T>(sh.z, sh.z, sh.w, sh.w);

		detail::tvec3<T> p0(a0.x, a0.y, h.x);
		detail::tvec3<T> p1(a0.z, a0.w, h.y);
		detail::tvec3<T> p2(a1.x, a1.y, h.z);
		detail::tvec3<T> p3(a1.z, a1.w, h.w);

		// Normalise gradients
		detail::tvec4<T> norm = taylorInvSqrt(detail::tvec4<T>(dot(p0, p0), dot(p1, p1), dot(p2, p2), dot(p3, p3)));
		p0 *= norm.x;
		p1 *= norm.y;
		p2 *= norm.z;
		p3 *= norm.w;

		// Mix final noise value
		detail::tvec4<T> m = max(T(0.6) - detail::tvec4<T>(dot(x0, x0), dot(x1, x1), dot(x2, x2), dot(x3, x3)), T(0));
		m = m * m;
		return T(42) * dot(m * m, detail::tvec4<T>(dot(p0, x0), dot(p1, x1), dot(p2, x2), dot(p3, x3)));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER T simplex(detail::tvec4<T> const & v)
	{
		detail::tvec4<T> const C(
			0.138196601125011,  // (5 - sqrt(5))/20  G4
			0.276393202250021,  // 2 * G4
			0.414589803375032,  // 3 * G4
			-0.447213595499958); // -1 + 4 * G4

		// (sqrt(5) - 1)/4 = F4, used once below
		T const F4 = T(0.309016994374947451);

		// First corner
		detail::tvec4<T> i  = floor(v + dot(v, vec4(F4)));
		detail::tvec4<T> x0 = v -   i + dot(i, vec4(C.x));

		// Other corners

		// Rank sorting originally contributed by Bill Licea-Kane, AMD (formerly ATI)
		detail::tvec4<T> i0;
		detail::tvec3<T> isX = step(detail::tvec3<T>(x0.y, x0.z, x0.w), detail::tvec3<T>(x0.x));
		detail::tvec3<T> isYZ = step(detail::tvec3<T>(x0.z, x0.w, x0.w), detail::tvec3<T>(x0.y, x0.y, x0.z));
		//  i0.x = dot(isX, vec3(1.0));
		//i0.x = isX.x + isX.y + isX.z;
		//i0.yzw = T(1) - isX;
		i0 = detail::tvec4<T>(isX.x + isX.y + isX.z, T(1) - isX);
		//  i0.y += dot(isYZ.xy, vec2(1.0));
		i0.y += isYZ.x + isYZ.y;
		//i0.zw += 1.0 - detail::tvec2<T>(isYZ.x, isYZ.y);
		i0.z += T(1) - isYZ.x;
		i0.w += T(1) - isYZ.y;
		i0.z += isYZ.z;
		i0.w += T(1) - isYZ.z;

		// i0 now contains the unique values 0,1,2,3 in each channel
		detail::tvec4<T> i3 = clamp(i0, 0.0, 1.0);
		detail::tvec4<T> i2 = clamp(i0 - 1.0, 0.0, 1.0);
		detail::tvec4<T> i1 = clamp(i0 - 2.0, 0.0, 1.0);

		//  x0 = x0 - 0.0 + 0.0 * C.xxxx
		//  x1 = x0 - i1  + 0.0 * C.xxxx
		//  x2 = x0 - i2  + 0.0 * C.xxxx
		//  x3 = x0 - i3  + 0.0 * C.xxxx
		//  x4 = x0 - 1.0 + 4.0 * C.xxxx
		detail::tvec4<T> x1 = x0 - i1 + C.x;
		detail::tvec4<T> x2 = x0 - i2 + C.y;
		detail::tvec4<T> x3 = x0 - i3 + C.z;
		detail::tvec4<T> x4 = x0 + C.w;

		// Permutations
		i = mod(i, T(289)); 
		T j0 = permute(permute(permute(permute(i.w) + i.z) + i.y) + i.x);
		detail::tvec4<T> j1 = permute(permute(permute(permute(
					i.w + detail::tvec4<T>(i1.w, i2.w, i3.w, T(1)))
				+ i.z + detail::tvec4<T>(i1.z, i2.z, i3.z, T(1)))
				+ i.y + detail::tvec4<T>(i1.y, i2.y, i3.y, T(1)))
				+ i.x + detail::tvec4<T>(i1.x, i2.x, i3.x, T(1)));

		// Gradients: 7x7x6 points over a cube, mapped onto a 4-cross polytope
		// 7*7*6 = 294, which is close to the ring size 17*17 = 289.
		detail::tvec4<T> ip = detail::tvec4<T>(T(1) / T(294), T(1) / T(49), T(1) / T(7), T(0));

		detail::tvec4<T> p0 = grad4(j0,   ip);
		detail::tvec4<T> p1 = grad4(j1.x, ip);
		detail::tvec4<T> p2 = grad4(j1.y, ip);
		detail::tvec4<T> p3 = grad4(j1.z, ip);
		detail::tvec4<T> p4 = grad4(j1.w, ip);

		// Normalise gradients
		detail::tvec4<T> norm = taylorInvSqrt(detail::tvec4<T>(dot(p0, p0), dot(p1, p1), dot(p2, p2), dot(p3, p3)));
		p0 *= norm.x;
		p1 *= norm.y;
		p2 *= norm.z;
		p3 *= norm.w;
		p4 *= taylorInvSqrt(dot(p4, p4));

		// Mix contributions from the five corners
		detail::tvec3<T> m0 = max(T(0.6) - detail::tvec3<T>(dot(x0, x0), dot(x1, x1), dot(x2, x2)), T(0));
		detail::tvec2<T> m1 = max(T(0.6) - detail::tvec2<T>(dot(x3, x3), dot(x4, x4)             ), T(0));
		m0 = m0 * m0;
		m1 = m1 * m1;
		return T(49) * 
			(dot(m0 * m0, detail::tvec3<T>(dot(p0, x0), dot(p1, x1), dot(p2, x2))) + 
			dot(m1 * m1, detail::tvec2<T>(dot(p3, x3), dot(p4, x4))));
	}
}//namespace glm
