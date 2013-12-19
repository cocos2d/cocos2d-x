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
/// @file glm/core/func_packing.inl
/// @date 2010-03-17 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	GLM_FUNC_QUALIFIER detail::uint32 packUnorm2x16(detail::tvec2<detail::float32> const & v)
	{
		detail::uint16 A(detail::uint16(round(clamp(v.x, 0.0f, 1.0f) * 65535.0f)));
		detail::uint16 B(detail::uint16(round(clamp(v.y, 0.0f, 1.0f) * 65535.0f)));
		return detail::uint32((B << 16) | A);
	}

	GLM_FUNC_QUALIFIER detail::tvec2<detail::float32> unpackUnorm2x16(detail::uint32 const & p)
	{
		detail::uint32 Mask16((1 << 16) - 1);
		detail::uint32 A((p >>  0) & Mask16);
		detail::uint32 B((p >> 16) & Mask16);
		return detail::tvec2<detail::float32>(
			A * 1.0f / 65535.0f, 
			B * 1.0f / 65535.0f);
	}
	
	GLM_FUNC_QUALIFIER detail::uint32 packSnorm2x16(detail::tvec2<detail::float32> const & v)
	{
		union iu
		{
			detail::int16 i;
			detail::uint16 u;
		} A, B;
		
		detail::tvec2<detail::float32> Unpack = clamp(v ,-1.0f, 1.0f) * 32767.0f;
		A.i = detail::int16(round(Unpack.x));
		B.i = detail::int16(round(Unpack.y));
		detail::uint32 Pack = (detail::uint32(B.u) << 16) | (detail::uint32(A.u) << 0);
		return Pack;
	}

	GLM_FUNC_QUALIFIER detail::tvec2<detail::float32> unpackSnorm2x16(detail::uint32 const & p)
	{
		union iu
		{
			detail::int16 i;
			detail::uint16 u;
		} A, B;
		
		detail::uint32 Mask16((1 << 16) - 1);
		A.u = detail::uint16((p >>  0) & Mask16);
		B.u = detail::uint16((p >> 16) & Mask16);
		detail::tvec2<detail::float32> Pack(A.i, B.i);
		
		return clamp(Pack * 1.0f / 32767.0f, -1.0f, 1.0f);
	}

	GLM_FUNC_QUALIFIER detail::uint32 packUnorm4x8(detail::tvec4<detail::float32> const & v)
	{
		detail::uint8 A((detail::uint8)round(clamp(v.x, 0.0f, 1.0f) * 255.0f));
		detail::uint8 B((detail::uint8)round(clamp(v.y, 0.0f, 1.0f) * 255.0f));
		detail::uint8 C((detail::uint8)round(clamp(v.z, 0.0f, 1.0f) * 255.0f));
		detail::uint8 D((detail::uint8)round(clamp(v.w, 0.0f, 1.0f) * 255.0f));
		return detail::uint32((D << 24) | (C << 16) | (B << 8) | A);
	}

	GLM_FUNC_QUALIFIER detail::tvec4<detail::float32> unpackUnorm4x8(detail::uint32 const & p)
	{	
		detail::uint32 Mask8((1 << 8) - 1);
		detail::uint32 A((p >>  0) & Mask8);
		detail::uint32 B((p >>  8) & Mask8);
		detail::uint32 C((p >> 16) & Mask8);
		detail::uint32 D((p >> 24) & Mask8);
		return detail::tvec4<detail::float32>(
			A * 1.0f / 255.0f, 
			B * 1.0f / 255.0f, 
			C * 1.0f / 255.0f, 
			D * 1.0f / 255.0f);
	}
	
	GLM_FUNC_QUALIFIER detail::uint32 packSnorm4x8(detail::tvec4<detail::float32> const & v)
	{
		union iu
		{
			detail::int8 i;
			detail::uint8 u;
		} A, B, C, D;
	
		detail::tvec4<detail::float32> Unpack = clamp(v ,-1.0f, 1.0f) * 127.0f;
		A.i = detail::int8(round(Unpack.x));
		B.i = detail::int8(round(Unpack.y));
		C.i = detail::int8(round(Unpack.z));
		D.i = detail::int8(round(Unpack.w));
		detail::uint32 Pack = (detail::uint32(D.u) << 24) | (detail::uint32(C.u) << 16) | (detail::uint32(B.u) << 8) | (detail::uint32(A.u) << 0);
		return Pack;
	}
	
	GLM_FUNC_QUALIFIER detail::tvec4<detail::float32> unpackSnorm4x8(detail::uint32 const & p)
	{	
		union iu
		{
			detail::int8 i;
			detail::uint8 u;
		} A, B, C, D;
	
		detail::uint32 Mask8((1 << 8) - 1);
		A.u = detail::uint8((p >>  0) & Mask8);
		B.u = detail::uint8((p >>  8) & Mask8);
		C.u = detail::uint8((p >> 16) & Mask8);
		D.u = detail::uint8((p >> 24) & Mask8);
		detail::tvec4<detail::float32> Pack(A.i, B.i, C.i, D.i);
	
		return clamp(Pack * 1.0f / 127.0f, -1.0f, 1.0f);
	}

	GLM_FUNC_QUALIFIER double packDouble2x32(detail::tvec2<detail::uint32> const & v)
	{
		struct uint32_pair
		{
			detail::uint32 x;
			detail::uint32 y;
		};

		union helper
		{
			uint32_pair input;
			double output;
		} Helper;

		Helper.input.x = v.x;
		Helper.input.y = v.y;

		return Helper.output;
		//return *(double*)&v;
	}

	GLM_FUNC_QUALIFIER detail::tvec2<uint> unpackDouble2x32(double const & v)
	{
		struct uint32_pair
		{
			detail::uint32 x;
			detail::uint32 y;
		};

		union helper
		{
			double input;
			uint32_pair output;
		} Helper;

		Helper.input = v;

		return detail::tvec2<uint>(Helper.output.x, Helper.output.y);
	}

	GLM_FUNC_QUALIFIER uint packHalf2x16(detail::tvec2<float> const & v)
	{
		union helper
		{ 
			uint other; 
			struct 
			{ 
				detail::hdata a, b; 
			} orig; 
		} Pack; 

		Pack.orig.a = detail::toFloat16(v.x); 
		Pack.orig.b = detail::toFloat16(v.y); 
		return Pack.other;
	}

	GLM_FUNC_QUALIFIER vec2 unpackHalf2x16(uint const & v)
	{
		union helper
		{ 
			uint other; 
			struct 
			{ 
				detail::hdata a, b; 
			} orig; 
		} Unpack; 
		Unpack.other = v;

		return vec2(detail::toFloat32(Unpack.orig.a), detail::toFloat32(Unpack.orig.b));
	}
}//namespace glm

