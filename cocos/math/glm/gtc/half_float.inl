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
/// @ref gtc_half_float
/// @file glm/gtc/half_float.inl
/// @date 2009-04-29 / 2012-11-06
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
#if(GLM_COMPONENT == GLM_COMPONENT_CXX98)

	//////////////////////////////////////
	// hvec2

	GLM_FUNC_QUALIFIER tvec2<half>::size_type tvec2<half>::length() const
	{
		return 2;
	}

	GLM_FUNC_QUALIFIER tvec2<half>::size_type tvec2<half>::value_size()
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	GLM_FUNC_QUALIFIER half & tvec2<half>::operator[](tvec2<half>::size_type i)
	{
		assert(/*i >= tvec2<half>::size_type(0) && */i < tvec2<half>::value_size());
		return (&x)[i];
	}

	GLM_FUNC_QUALIFIER half const & tvec2<half>::operator[](tvec2<half>::size_type i) const
	{
		assert(/*i >= tvec2<half>::size_type(0) && */i < tvec2<half>::value_size());
		return (&x)[i];
	}

	//////////////////////////////////////
	// Implicit basic constructors

	GLM_FUNC_QUALIFIER tvec2<half>::tvec2() :
		x(half(0.f)),
		y(half(0.f))
	{}

	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		tvec2<half> const & v
	) :
		x(v.x),
		y(v.y)
	{}

	//////////////////////////////////////
	// Explicit basic constructors

	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		half const & s
	) :
		x(s),
		y(s)
	{}

	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		half const & s1, 
		half const & s2
	) :
		x(s1),
		y(s2)
	{}

	//////////////////////////////////////
	// Swizzle constructors

	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		tref2<half> const & r
	) :
		x(r.x),
		y(r.y)
	{}

	//////////////////////////////////////
	// Convertion scalar constructors

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		U const & x
	) :
		x(half(x)),
		y(half(x))
	{}

	template <typename U, typename V> 
	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		U const & x, 
		V const & y
	) :
		x(half(x)),
		y(half(y))
	{}

	//////////////////////////////////////
	// Convertion vector constructors

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		tvec2<U> const & v
	) :
		x(half(v.x)),
		y(half(v.y))
	{}

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(	
		tvec3<U> const & v
	) :
		x(half(v.x)),
		y(half(v.y))
	{}

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<half>::tvec2
	(
		tvec4<U> const & v
	) :
		x(half(v.x)),
		y(half(v.y))
	{}

	//////////////////////////////////////
	// Unary arithmetic operators

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator= 
	(
		tvec2<half> const & v
	)
	{
		this->x = v.x;
		this->y = v.y;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator+=
	(
		half const & s
	)
	{
		this->x += s;
		this->y += s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator+=
	(
		tvec2<half> const & v
	)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator-=
	(
		half const & s
	)
	{
		this->x -= s;
		this->y -= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator-=
	(
		tvec2<half> const & v
	)
	{
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half>& tvec2<half>::operator*=
	(
		half const & s
	)
	{
		this->x *= s;
		this->y *= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator*=
	(
		tvec2<half> const & v
	)
	{
		this->x *= v.x;
		this->y *= v.y;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator/=
	(
		half const & s
	)
	{
		this->x /= s;
		this->y /= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator/=
	(
		tvec2<half> const & v
	)
	{
		this->x /= v.x;
		this->y /= v.y;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half> & tvec2<half>::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec2<half>& tvec2<half>::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	//////////////////////////////////////
	// Swizzle operators

	GLM_FUNC_QUALIFIER half tvec2<half>::swizzle(comp x) const
	{
		return (*this)[x];
	}

	GLM_FUNC_QUALIFIER tvec2<half> tvec2<half>::swizzle(comp x, comp y) const
	{
		return tvec2<half>(
			(*this)[x],
			(*this)[y]);
	}

	GLM_FUNC_QUALIFIER tvec3<half> tvec2<half>::swizzle(comp x, comp y, comp z) const
	{
		return tvec3<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z]);
	}

	GLM_FUNC_QUALIFIER tvec4<half> tvec2<half>::swizzle(comp x, comp y, comp z, comp w) const
	{
		return tvec4<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z],
			(*this)[w]);
	}

	GLM_FUNC_QUALIFIER tref2<half> tvec2<half>::swizzle(comp x, comp y)
	{
		return tref2<half>(
			(*this)[x],
			(*this)[y]);
	}

	//////////////////////////////////////
	// hvec3

	GLM_FUNC_QUALIFIER tvec3<half>::size_type tvec3<half>::length() const
	{
		return 3;
	}

	GLM_FUNC_QUALIFIER tvec3<half>::size_type tvec3<half>::value_size()
	{
		return 3;
	}

	//////////////////////////////////////
	// Accesses

	GLM_FUNC_QUALIFIER half & tvec3<half>::operator[]
	(
		tvec3<half>::size_type i
	)
	{
		assert(/*i >= tvec3<half>::size_type(0) &&*/ i < tvec3<half>::value_size());

		return (&x)[i];
	}

	GLM_FUNC_QUALIFIER half const & tvec3<half>::operator[]
	(
		tvec3<half>::size_type i
	) const
	{
		assert(/*i >= tvec3<half>::size_type(0) &&*/ i < tvec3<half>::value_size());

		return (&x)[i];
	}

	//////////////////////////////////////
	// Implicit basic constructors

	GLM_FUNC_QUALIFIER tvec3<half>::tvec3() :
		x(half(0)),
		y(half(0)),
		z(half(0))
	{}

	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		tvec3<half> const & v
	) :
		x(v.x),
		y(v.y),
		z(v.z)
	{}

	//////////////////////////////////////
	// Explicit basic constructors

	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		half const & s
	) :
		x(s),
		y(s),
		z(s)
	{}

	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		half const & s0, 
		half const & s1, 
		half const & s2
	) :
		x(s0),
		y(s1),
		z(s2)
	{}

	//////////////////////////////////////
	// Swizzle constructors

	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		tref3<half> const & r
	) :
		x(r.x),
		y(r.y),
		z(r.z)
	{}

	//////////////////////////////////////
	// Convertion scalar constructors

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		U const & x
	) :
		x(half(x)),
		y(half(x)),
		z(half(x))
	{}

	template <typename A, typename B, typename C> 
	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		A const & x, 
		B const & y, 
		C const & z
	) :
		x(half(x)),
		y(half(y)),
		z(half(z))
	{}

	//////////////////////////////////////
	// Convertion vector constructors

	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		tvec2<A> const & v, 
		B const & s
	) :
		x(half(v.x)),
		y(half(v.y)),
		z(half(s))
	{}

	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		A const & s, 
		tvec2<B> const & v
	) :
		x(half(s)),
		y(half(v.x)),
		z(half(v.y))
	{}

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		tvec3<U> const & v
	) :
		x(half(v.x)),
		y(half(v.y)),
		z(half(v.z))
	{}

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<half>::tvec3
	(
		tvec4<U> const & v
	) :
		x(half(v.x)),
		y(half(v.y)),
		z(half(v.z))
	{}

	//////////////////////////////////////
	// Unary arithmetic operators

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator= 
	(
		tvec3<half> const & v
	)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator+=
	(
		half const & s
	)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator+=
	(
		tvec3<half> const & v
	)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator-=
	(
		half const & s
	)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator-=
	(
		tvec3<half> const & v
	)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator*=
	(
		half const & s
	)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator*=
	(
		tvec3<half> const & v
	)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator/=
	(
		half const & s
	)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator/=
	(
		tvec3<half> const & v
	)
	{
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec3<half> & tvec3<half>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	//////////////////////////////////////
	// Swizzle operators

	GLM_FUNC_QUALIFIER half tvec3<half>::swizzle(comp x) const
	{
		return (*this)[x];
	}

	GLM_FUNC_QUALIFIER tvec2<half> tvec3<half>::swizzle(comp x, comp y) const
	{
		return tvec2<half>(
			(*this)[x],
			(*this)[y]);
	}

	GLM_FUNC_QUALIFIER tvec3<half> tvec3<half>::swizzle(comp x, comp y, comp z) const
	{
		return tvec3<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z]);
	}

	GLM_FUNC_QUALIFIER tvec4<half> tvec3<half>::swizzle(comp x, comp y, comp z, comp w) const
	{
		return tvec4<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z],
			(*this)[w]);
	}

	GLM_FUNC_QUALIFIER tref3<half> tvec3<half>::swizzle(comp x, comp y, comp z)
	{
		return tref3<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z]);
	}

	//////////////////////////////////////
	// hvec4

	GLM_FUNC_QUALIFIER tvec4<half>::size_type tvec4<half>::length() const
	{
		return 4;
	}

	GLM_FUNC_QUALIFIER tvec4<half>::size_type tvec4<half>::value_size()
	{
		return 4;
	}
	
	//////////////////////////////////////
	// Accesses

	GLM_FUNC_QUALIFIER half & tvec4<half>::operator[]
	(
		tvec4<half>::size_type i
	)
	{
		assert(/*i >= tvec4<half>::size_type(0) && */i < tvec4<half>::value_size());

		return (&x)[i];
	}

	GLM_FUNC_QUALIFIER half const & tvec4<half>::operator[]
	(
		tvec4<half>::size_type i
	) const
	{
		assert(/*i >= tvec4<half>::size_type(0) && */i < tvec4<half>::value_size());

		return (&x)[i];
	}

	//////////////////////////////////////
	// Implicit basic constructors

	GLM_FUNC_QUALIFIER tvec4<half>::tvec4() :
		x(half(0)),
		y(half(0)),
		z(half(0)),
		w(half(0))
	{}

	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		tvec4<half> const & v
	) :
		x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{}

	//////////////////////////////////////
	// Explicit basic constructors

	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		half const & s
	) :
		x(s),
		y(s),
		z(s),
		w(s)
	{}

	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		half const & s1, 
		half const & s2, 
		half const & s3, 
		half const & s4
	) :
		x(s1),
		y(s2),
		z(s3),
		w(s4)
	{}

	//////////////////////////////////////
	// Swizzle constructors

	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		tref4<half> const & r
	) :
		x(r.x),
		y(r.y),
		z(r.z),
		w(r.w)
	{}

	//////////////////////////////////////
	// Convertion scalar constructors

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		U const & x
	) :
		x(half(x)),
		y(half(x)),
		z(half(x)),
		w(half(x))
	{}

	template <typename A, typename B, typename C, typename D> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		A const & x, 
		B const & y, 
		C const & z, 
		D const & w
	) :
		x(half(x)),
		y(half(y)),
		z(half(z)),
		w(half(w))
	{}

	//////////////////////////////////////
	// Convertion vector constructors

	template <typename A, typename B, typename C> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		tvec2<A> const & v, 
		B const & s1, 
		C const & s2
	) :
		x(half(v.x)),
		y(half(v.y)),
		z(half(s1)),
		w(half(s2))
	{}

	template <typename A, typename B, typename C> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		A const & s1, 
		tvec2<B> const & v, 
		C const & s2
	) :
		x(half(s1)),
		y(half(v.x)),
		z(half(v.y)),
		w(half(s2))
	{}

	template <typename A, typename B, typename C> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		A const & s1, 
		B const & s2, 
		tvec2<C> const & v
	) :
		x(half(s1)),
		y(half(s2)),
		z(half(v.x)),
		w(half(v.y))
	{}

	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		tvec3<A> const & v, 
		B const & s
	) :
		x(half(v.x)),
		y(half(v.y)),
		z(half(v.z)),
		w(half(s))
	{}

	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		A const & s, 
		tvec3<B> const & v
	) :
		x(half(s)),
		y(half(v.x)),
		z(half(v.y)),
		w(half(v.z))
	{}

	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		tvec2<A> const & v1, 
		tvec2<B> const & v2
	) :
		x(half(v1.x)),
		y(half(v1.y)),
		z(half(v2.x)),
		w(half(v2.y))
	{}

	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<half>::tvec4
	(
		tvec4<U> const & v
	) :
		x(half(v.x)),
		y(half(v.y)),
		z(half(v.z)),
		w(half(v.w))
	{}

	//////////////////////////////////////
	// Unary arithmetic operators

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator= 
	(
		tvec4<half> const & v
	)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = v.w;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator+=
	(
		half const & s
	)
	{
		this->x += s;
		this->y += s;
		this->z += s;
		this->w += s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator+=
	(
		tvec4<half> const & v
	)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		this->w += v.w;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator-=
	(
		half const & s
	)
	{
		this->x -= s;
		this->y -= s;
		this->z -= s;
		this->w -= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator-=
	(
		tvec4<half> const & v
	)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		this->w -= v.w;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator*=
	(
		half const & s
	)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator*=
	(
		tvec4<half> const & v
	)
	{
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		this->w *= v.w;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator/=
	(
		half const & s
	)
	{
		this->x /= s;
		this->y /= s;
		this->z /= s;
		this->w /= s;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator/=
	(
		tvec4<half> const & v
	)
	{
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
		this->w /= v.w;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	GLM_FUNC_QUALIFIER tvec4<half>& tvec4<half>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	//////////////////////////////////////
	// Swizzle operators

	GLM_FUNC_QUALIFIER half tvec4<half>::swizzle(comp x) const
	{
		return (*this)[x];
	}

	GLM_FUNC_QUALIFIER tvec2<half> tvec4<half>::swizzle(comp x, comp y) const
	{
		return tvec2<half>(
			(*this)[x],
			(*this)[y]);
	}

	GLM_FUNC_QUALIFIER tvec3<half> tvec4<half>::swizzle(comp x, comp y, comp z) const
	{
		return tvec3<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z]);
	}

	GLM_FUNC_QUALIFIER tvec4<half> tvec4<half>::swizzle(comp x, comp y, comp z, comp w) const
	{
		return tvec4<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z],
			(*this)[w]);
	}

	GLM_FUNC_QUALIFIER tref4<half> tvec4<half>::swizzle(comp x, comp y, comp z, comp w)
	{
		return tref4<half>(
			(*this)[x],
			(*this)[y],
			(*this)[z],
			(*this)[w]);
	}

#endif//(GLM_COMPONENT == GLM_COMPONENT_CXX98)

}//namespace detail

	GLM_FUNC_QUALIFIER half abs(half const & x)
	{
		return float(x) >= float(0) ? x : -x;
	}

	GLM_FUNC_QUALIFIER hvec2 abs(hvec2 const & v)
	{
		return hvec2(
			float(v.x) >= float(0) ? v.x : -v.x, 
			float(v.y) >= float(0) ? v.y : -v.y);
	}

	GLM_FUNC_QUALIFIER hvec3 abs(hvec3 const & v)
	{
		return hvec3(
			float(v.x) >= float(0) ? v.x : -v.x, 
			float(v.y) >= float(0) ? v.y : -v.y, 
			float(v.z) >= float(0) ? v.z : -v.z);
	}

	GLM_FUNC_QUALIFIER hvec4 abs(hvec4 const & v)
	{
		return hvec4(
			float(v.x) >= float(0) ? v.x : -v.x, 
			float(v.y) >= float(0) ? v.y : -v.y, 
			float(v.z) >= float(0) ? v.z : -v.z, 
			float(v.w) >= float(0) ? v.w : -v.w);
	}

	template <>
	GLM_FUNC_QUALIFIER glm::half mix
	(
		glm::half const & x, 
		glm::half const & y, 
		bool const & a
	)
	{
		return a ? y : x;
	}

}//namespace glm
