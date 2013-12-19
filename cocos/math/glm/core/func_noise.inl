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
/// @ref core
/// @file glm/core/func_noise.inl
/// @date 2008-08-01 / 2011-09-27
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	template <typename T>
	GLM_FUNC_QUALIFIER T noise1(T const & x)
	{
		return noise1(glm::detail::tvec2<T>(x, T(0)));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec2<T> noise2(T const & x)
	{
		return glm::detail::tvec2<T>(
			noise1(x + T(0.0)),
			noise1(x + T(1.0)));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec3<T> noise3(T const & x)
	{
		return glm::detail::tvec3<T>(
			noise1(x - T(1.0)),
			noise1(x + T(0.0)),
			noise1(x + T(1.0)));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec4<T> noise4(T const & x)
	{
		return glm::detail::tvec4<T>(
			noise1(x - T(1.0)),
			noise1(x + T(0.0)),
			noise1(x + T(1.0)),
			noise1(x + T(2.0)));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER T noise1(glm::detail::tvec2<T> const & v)
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
	GLM_FUNC_QUALIFIER T noise1(detail::tvec3<T> const & v)
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
	GLM_FUNC_QUALIFIER T noise1(detail::tvec4<T> const & v)
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
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec2<T> noise2(glm::detail::tvec2<T> const & x)
	{
		return glm::detail::tvec2<T>(
			noise1(x + glm::detail::tvec2<T>(0.0)),
			noise1(glm::detail::tvec2<T>(0.0) - x));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec2<T> noise2(glm::detail::tvec3<T> const & x)
	{
		return glm::detail::tvec2<T>(
			noise1(x + glm::detail::tvec3<T>(0.0)),
			noise1(glm::detail::tvec3<T>(0.0) - x));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec2<T> noise2(glm::detail::tvec4<T> const & x)
	{
		return glm::detail::tvec2<T>(
			noise1(x + glm::detail::tvec4<T>(0.0)),
			noise1(glm::detail::tvec4<T>(0.0) - x));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec3<T> noise3(glm::detail::tvec2<T> const & x)
	{
		return glm::detail::tvec3<T>(
			noise1(x - glm::detail::tvec2<T>(1.0)),
			noise1(x + glm::detail::tvec2<T>(0.0)),
			noise1(x + glm::detail::tvec2<T>(1.0)));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec3<T> noise3(glm::detail::tvec3<T> const & x)
	{
		return glm::detail::tvec3<T>(
			noise1(x - glm::detail::tvec3<T>(1.0)),
			noise1(x + glm::detail::tvec3<T>(0.0)),
			noise1(x + glm::detail::tvec3<T>(1.0)));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec3<T> noise3(glm::detail::tvec4<T> const & x)
	{
		return glm::detail::tvec3<T>(
			noise1(x - glm::detail::tvec4<T>(1.0)),
			noise1(x + glm::detail::tvec4<T>(0.0)),
			noise1(x + glm::detail::tvec4<T>(1.0)));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec4<T> noise4(glm::detail::tvec2<T> const & x)
	{
		return glm::detail::tvec4<T>(
			noise1(x - glm::detail::tvec2<T>(1.0)),
			noise1(x + glm::detail::tvec2<T>(0.0)),
			noise1(x + glm::detail::tvec2<T>(1.0)),
			noise1(x + glm::detail::tvec2<T>(2.0)));
	}

	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec4<T> noise4(glm::detail::tvec3<T> const & x)
	{
		return glm::detail::tvec4<T>(
			noise1(x - glm::detail::tvec3<T>(1.0)),
			noise1(x + glm::detail::tvec3<T>(0.0)),
			noise1(x + glm::detail::tvec3<T>(1.0)),
			noise1(x + glm::detail::tvec3<T>(2.0)));
	}
	
	template <typename T>
	GLM_FUNC_QUALIFIER glm::detail::tvec4<T> noise4(glm::detail::tvec4<T> const & x)
	{
		return glm::detail::tvec4<T>(
			noise1(x - glm::detail::tvec4<T>(1.0)),
			noise1(x + glm::detail::tvec4<T>(0.0)),
			noise1(x + glm::detail::tvec4<T>(1.0)),
			noise1(x + glm::detail::tvec4<T>(2.0)));
	}
	
}//namespace glm
