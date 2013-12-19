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
/// @file glm/core/type_tvec3.inl
/// @date 2008-08-22 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tvec3<T>::size_type tvec3<T>::length() const
	{
		return 3;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec3<T>::value_type & 
	tvec3<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return (&x)[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec3<T>::value_type const & 
	tvec3<T>::operator[]
	(
		size_type i
	) const
	{
		assert(i < this->length());
		return (&x)[i];
	}

	//////////////////////////////////////
	// Implicit basic constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3() :
		x(value_type(0)),
		y(value_type(0)),
		z(value_type(0))
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		ctor
	)
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		tvec3<T> const & v
	) :
		x(v.x),
		y(v.y),
		z(v.z)
	{}

	//////////////////////////////////////
	// Explicit basic constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		value_type const & s
	) :
		x(s),
		y(s),
		z(s)
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		value_type const & s0, 
		value_type const & s1, 
		value_type const & s2
	) :
		x(s0),
		y(s1),
		z(s2)
	{}

	//////////////////////////////////////
	// Swizzle constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		tref3<T> const & r
	) :
		x(r.x),
		y(r.y),
		z(r.z)
	{}

	template <typename T>
	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		tref2<A> const & v, 
		B const & s
	) : 
		x(value_type(v.x)),
		y(value_type(v.y)),
		z(value_type(s))
	{}

	template <typename T>
	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		A const & s, 
		tref2<B> const & v
	) :
		x(value_type(s)),
		y(value_type(v.x)),
		z(value_type(v.y))
	{}

	//////////////////////////////////////
	// Convertion scalar constructors
		
	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		U const & s
	) :
		x(value_type(s)),
		y(value_type(s)),
		z(value_type(s))
	{}

	template <typename T>
	template <typename A, typename B, typename C> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		A const & x, 
		B const & y, 
		C const & z
	) :
		x(value_type(x)),
		y(value_type(y)),
		z(value_type(z))
	{}

	//////////////////////////////////////
	// Convertion vector constructors

	template <typename T>
	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		tvec2<A> const & v, 
		B const & s
	) :
		x(value_type(v.x)),
		y(value_type(v.y)),
		z(value_type(s))
	{}

	template <typename T>
	template <typename A, typename B> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(	
		A const & s, 
		tvec2<B> const & v
	) :
		x(value_type(s)),
		y(value_type(v.x)),
		z(value_type(v.y))
	{}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		tvec3<U> const & v
	) :
		x(value_type(v.x)),
		y(value_type(v.y)),
		z(value_type(v.z))
	{}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T>::tvec3
	(
		tvec4<U> const & v
	) :
		x(value_type(v.x)),
		y(value_type(v.y)),
		z(value_type(v.z))
	{}

	//////////////////////////////////////
	// Unary arithmetic operators

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T>& tvec3<T>::operator= 
	(
		tvec3<T> const & v
	)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T>& tvec3<T>::operator= 
	(
		tvec3<U> const & v
	)
	{
		this->x = T(v.x);
		this->y = T(v.y);
		this->z = T(v.z);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator+=(U s)
	{
		this->x += T(s);
		this->y += T(s);
		this->z += T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator+=
	(
		tvec3<U> const & v
	)
	{
		this->x += T(v.x);
		this->y += T(v.y);
		this->z += T(v.z);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator-=(U s)
	{
		this->x -= T(s);
		this->y -= T(s);
		this->z -= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator-=
	(
		tvec3<U> const & v
	)
	{
		this->x -= T(v.x);
		this->y -= T(v.y);
		this->z -= T(v.z);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator*=(U s)
	{
		this->x *= T(s);
		this->y *= T(s);
		this->z *= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator*=
	(
		tvec3<U> const & v
	)
	{
		this->x *= T(v.x);
		this->y *= T(v.y);
		this->z *= T(v.z);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator/=(U s)
	{
		this->x /= T(s);
		this->y /= T(s);
		this->z /= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator/=
	(
		tvec3<U> const & v
	)
	{
		this->x /= T(v.x);
		this->y /= T(v.y);
		this->z /= T(v.z);
		return *this;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}

	//////////////////////////////////////
	// Unary bit operators

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator%=(U s)
	{
		this->x %= s;
		this->y %= s;
		this->z %= s;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator%=
	(
		tvec3<U> const & v
	)
	{
		this->x %= v.x;
		this->y %= v.y;
		this->z %= v.z;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator&=(U s)
	{
		this->x &= s;
		this->y &= s;
		this->z &= s;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator&=
	(
		tvec3<U> const & v
	)
	{
		this->x &= v.x;
		this->y &= v.y;
		this->z &= v.z;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator|=(U s)
	{
		this->x |= s;
		this->y |= s;
		this->z |= s;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator|=
	(
		tvec3<U> const & v
	)
	{
		this->x |= v.x;
		this->y |= v.y;
		this->z |= v.z;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator^=(U s)
	{
		this->x ^= s;
		this->y ^= s;
		this->z ^= s;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator^=
	(
		tvec3<U> const & v
	)
	{
		this->x ^= v.x;
		this->y ^= v.y;
		this->z ^= v.z;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator<<=(U s)
	{
		this->x <<= s;
		this->y <<= s;
		this->z <<= s;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator<<=
	(
		tvec3<U> const & v
	)
	{
		this->x <<= T(v.x);
		this->y <<= T(v.y);
		this->z <<= T(v.z);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator>>=(U s)
	{
		this->x >>= T(s);
		this->y >>= T(s);
		this->z >>= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T> & tvec3<T>::operator>>=
	(
		tvec3<U> const & v
	)
	{
		this->x >>= T(v.x);
		this->y >>= T(v.y);
		this->z >>= T(v.z);
		return *this;
	}

	//////////////////////////////////////
	// Swizzle operators

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec3<T>::value_type 
	tvec3<T>::swizzle
	(
		comp x
	) const
	{
		return (*this)[x];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> tvec3<T>::swizzle
	(
		comp x, 
		comp y
	) const
	{
		return tvec2<T>(
			(*this)[x],
			(*this)[y]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> tvec3<T>::swizzle
	(
		comp x, 
		comp y, 
		comp z
	) const
	{
		return tvec3<T>(
			(*this)[x],
			(*this)[y],
			(*this)[z]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec4<T> tvec3<T>::swizzle
	(
		comp x, 
		comp y, 
		comp z, 
		comp w
	) const
	{
		return tvec4<T>(
			(*this)[x],
			(*this)[y],
			(*this)[z],
			(*this)[w]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tref2<T> tvec3<T>::swizzle
	(
		comp x, 
		comp y
	)
	{
		return tref2<T>(
			(*this)[x],
			(*this)[y]);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tref3<T> tvec3<T>::swizzle
	(
		comp x, 
		comp y, 
		comp z
	)
	{
		return tref3<T>(
			(*this)[x],
			(*this)[y],
			(*this)[z]);
	}

	//////////////////////////////////////
	// Binary arithmetic operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator+
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x + T(s),
			v.y + T(s),
			v.z + T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator+ 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) + v.x,
			T(s) + v.y,
			T(s) + v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator+ 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x + T(v2.x),
			v1.y + T(v2.y),
			v1.z + T(v2.z));
	}

	//operator-
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator- 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x - T(s),
			v.y - T(s),
			v.z - T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator- 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) - v.x,
			T(s) - v.y,
			T(s) - v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator- 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x - T(v2.x),
			v1.y - T(v2.y),
			v1.z - T(v2.z));
	}

	//operator*
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator*
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x * T(s),
			v.y * T(s),
			v.z * T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator* 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) * v.x,
			T(s) * v.y,
			T(s) * v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator* 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x * T(v2.x),
			v1.y * T(v2.y),
			v1.z * T(v2.z));
	}

	//operator/
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator/
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x / T(s),
			v.y / T(s),
			v.z / T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator/ 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) / v.x,
			T(s) / v.y,
			T(s) / v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator/ 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x / T(v2.x),
			v1.y / T(v2.y),
			v1.z / T(v2.z));
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator- 
	(
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			-v.x, 
			-v.y, 
			-v.z);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator++ 
	(
		tvec3<T> const & v, 
		int
	)
	{
		return tvec3<T>(
			v.x + T(1), 
			v.y + T(1), 
			v.z + T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator-- 
	(
		tvec3<T> const & v, 
		int
	)
	{
		return tvec3<T>(
			v.x - T(1), 
			v.y - T(1), 
			v.z - T(1));
	}

	//////////////////////////////////////
	// Binary bit operators

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator% 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x % T(s),
			v.y % T(s),
			v.z % T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator%
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) % v.x,
			T(s) % v.y,
			T(s) % v.z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator% 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x % T(v2.x),
			v1.y % T(v2.y),
			v1.z % T(v2.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator& 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x & T(s),
			v.y & T(s),
			v.z & T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator& 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) & v.x,
			T(s) & v.y,
			T(s) & v.z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator& 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x & T(v2.x),
			v1.y & T(v2.y),
			v1.z & T(v2.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator| 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x | T(s),
			v.y | T(s),
			v.z | T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator| 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) | v.x,
			T(s) | v.y,
			T(s) | v.z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator| 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x | T(v2.x),
			v1.y | T(v2.y),
			v1.z | T(v2.z));
	}
		
	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator^ 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x ^ T(s),
			v.y ^ T(s),
			v.z ^ T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator^ 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) ^ v.x,
			T(s) ^ v.y,
			T(s) ^ v.z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator^ 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x ^ T(v2.x),
			v1.y ^ T(v2.y),
			v1.z ^ T(v2.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator<< 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x << T(s),
			v.y << T(s),
			v.z << T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator<< 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			T(s) << v.x,
			T(s) << v.y,
			T(s) << v.z);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator<< 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x << T(v2.x),
			v1.y << T(v2.y),
			v1.z << T(v2.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator>> 
	(
		tvec3<T> const & v, 
		T const & s
	)
	{
		return tvec3<T>(
			v.x >> T(s),
			v.y >> T(s),
			v.z >> T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator>> 
	(
		T const & s, 
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			s >> T(v.x),
			s >> T(v.y),
			s >> T(v.z));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec3<T> operator>> 
	(
		tvec3<T> const & v1, 
		tvec3<T> const & v2
	)
	{
		return tvec3<T>(
			v1.x >> T(v2.x),
			v1.y >> T(v2.y),
			v1.z >> T(v2.z));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> operator~ 
	(
		tvec3<T> const & v
	)
	{
		return tvec3<T>(
			~v.x,
			~v.y,
			~v.z);
	}

	//////////////////////////////////////
	// tref definition

	template <typename T> 
	GLM_FUNC_QUALIFIER tref3<T>::tref3(T & x, T & y, T & z) :
		x(x),
		y(y),
		z(z)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref3<T>::tref3
	(
		tref3<T> const & r
	) :
		x(r.x),
		y(r.y),
		z(r.z)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref3<T>::tref3
	(
		tvec3<T> const & v
	) :
		x(v.x),
		y(v.y),
		z(v.z)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref3<T> & tref3<T>::operator=
	(
		tref3<T> const & r
	)
	{
		x = r.x;
		y = r.y;
		z = r.z;
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref3<T> & tref3<T>::operator=
	(
		tvec3<T> const & v
	)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec3<T> tref3<T>::operator() ()
	{
		return tvec3<T>(this->x, this->y, this->z);
	}

}//namespace detail
}//namespace glm
