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
/// @file glm/core/type_tvec2.inl
/// @date 2008-08-18 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tvec2<T>::size_type tvec2<T>::length() const
	{
		return 2;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec2<T>::value_type & 
	tvec2<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return (&x)[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec2<T>::value_type const & 
	tvec2<T>::operator[]
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
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2() :
		x(value_type(0)),
		y(value_type(0))
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		ctor
	)
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		tvec2<T> const & v
	) :
		x(v.x),
		y(v.y)
	{}

	//////////////////////////////////////
	// Explicit basic constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		value_type const & s
	) :
		x(s),
		y(s)
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		value_type const & s1, 
		value_type const & s2
	) :
		x(s1),
		y(s2)
	{}

	//////////////////////////////////////
	// Swizzle constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		tref2<T> const & r
	) :
		x(r.x),
		y(r.y)
	{}

	//////////////////////////////////////
	// Convertion scalar constructors
		
	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		U const & x
	) :
		x(value_type(x)),
		y(value_type(x))
	{}

	template <typename T>
	template <typename U, typename V> 
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		U const & a, 
		V const & b
	) :
		x(value_type(a)),
		y(value_type(b))
	{}

	//////////////////////////////////////
	// Convertion vector constructors

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		tvec2<U> const & v
	) :
		x(value_type(v.x)),
		y(value_type(v.y))
	{}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		tvec3<U> const & v
	) :
		x(value_type(v.x)),
		y(value_type(v.y))
	{}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T>::tvec2
	(
		tvec4<U> const & v
	) :
		x(value_type(v.x)),
		y(value_type(v.y))
	{}

	//////////////////////////////////////
	// Unary arithmetic operators

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator= 
	(
		tvec2<T> const & v
	)
	{
		this->x = v.x;
		this->y = v.y;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator= 
	(
		tvec2<U> const & v
	)
	{
		this->x = T(v.x);
		this->y = T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator+=(U s)
	{
		this->x += T(s);
		this->y += T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator+=
	(
		tvec2<U> const & v
	)
	{
		this->x += T(v.x);
		this->y += T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator-=(U s)
	{
		this->x -= T(s);
		this->y -= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator-=
	(
		tvec2<U> const & v
	)
	{
		this->x -= T(v.x);
		this->y -= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator*=(U s)
	{
		this->x *= T(s);
		this->y *= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator*=
	(
		tvec2<U> const & v
	)
	{
		this->x *= T(v.x);
		this->y *= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator/=(U s)
	{
		this->x /= T(s);
		this->y /= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator/=
	(
		tvec2<U> const & v
	)
	{
		this->x /= T(v.x);
		this->y /= T(v.y);
		return *this;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return (v1.x == v2.x) && (v1.y == v2.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return (v1.x != v2.x) || (v1.y != v2.y);
	}

	//////////////////////////////////////
	// Unary bit operators

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator%=(U s)
	{
		this->x %= T(s);
		this->y %= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator%=
	(
		tvec2<U> const & v
	)
	{
		this->x %= T(v.x);
		this->y %= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator&=(U s)
	{
		this->x &= T(s);
		this->y &= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator&=
	(
		tvec2<U> const & v
	)
	{
		this->x &= T(v.x);
		this->y &= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator|=(U s)
	{
		this->x |= T(s);
		this->y |= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator|=
	(
		tvec2<U> const & v
	)
	{
		this->x |= T(v.x);
		this->y |= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator^=(U s)
	{
		this->x ^= T(s);
		this->y ^= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator^=
	(
		tvec2<U> const & v
	)
	{
		this->x ^= T(v.x);
		this->y ^= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator<<=(U s)
	{
		this->x <<= T(s);
		this->y <<= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator<<=
	(
		tvec2<U> const & v
	)
	{
		this->x <<= T(v.x);
		this->y <<= T(v.y);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator>>=(U s)
	{
		this->x >>= T(s);
		this->y >>= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec2<T> & tvec2<T>::operator>>=
	(
		tvec2<U> const & v
	)
	{
		this->x >>= T(v.x);
		this->y >>= T(v.y);
		return *this;
	}

	//////////////////////////////////////
	// Swizzle operators

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec2<T>::value_type tvec2<T>::swizzle
	(
		comp x
	) const
	{
		return (*this)[x];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> tvec2<T>::swizzle
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
	GLM_FUNC_QUALIFIER tvec3<T> tvec2<T>::swizzle
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
	GLM_FUNC_QUALIFIER tvec4<T> tvec2<T>::swizzle
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
	GLM_FUNC_QUALIFIER tref2<T> tvec2<T>::swizzle
	(
		comp x, 
		comp y
	)
	{
		return tref2<T>(
			(*this)[x],
			(*this)[y]);
	}

	//////////////////////////////////////
	// Binary arithmetic operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator+ 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x + T(s),
			v.y + T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator+ 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) + v.x,
			T(s) + v.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator+ 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x + T(v2.x),
			v1.y + T(v2.y));
	}

	//operator-
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator-
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x - T(s),
			v.y - T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator- 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) - v.x,
			T(s) - v.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator- 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x - T(v2.x),
			v1.y - T(v2.y));
	}

	//operator*
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator* 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x * T(s),
			v.y * T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator* 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) * v.x,
			T(s) * v.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator*
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x * T(v2.x),
			v1.y * T(v2.y));
	}

	//operator/
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator/
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x / T(s),
			v.y / T(s));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator/
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) / v.x,
			T(s) / v.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator/ 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x / T(v2.x),
			v1.y / T(v2.y));
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator- 
	(
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			-v.x, 
			-v.y);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator++ 
	(
		tvec2<T> const & v, 
		int
	)
	{
		return tvec2<T>(
			v.x + T(1), 
			v.y + T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator-- 
	(
		tvec2<T> const & v, 
		int
	)
	{
		return tvec2<T>(
			v.x - T(1), 
			v.y - T(1));
	}

	//////////////////////////////////////
	// Binary bit operators

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator% 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x % T(s),
			v.y % T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator%
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) % v.x,
			T(s) % v.y);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator% 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x % T(v2.x),
			v1.y % T(v2.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator& 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x & T(s),
			v.y & T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator& 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) & v.x,
			T(s) & v.y);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator& 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x & T(v2.x),
			v1.y & T(v2.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator| 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x | T(s),
			v.y | T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator| 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) | v.x,
			T(s) | v.y);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator| 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x | T(v2.x),
			v1.y | T(v2.y));
	}
		
	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator^ 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x ^ T(s),
			v.y ^ T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator^ 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) ^ v.x,
			T(s) ^ v.y);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator^ 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x ^ T(v2.x),
			v1.y ^ T(v2.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator<< 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x << T(s),
			v.y << T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator<< 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			s << T(v.x),
			s << T(v.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator<< 
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x << T(v2.x),
			v1.y << T(v2.y));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator>> 
	(
		tvec2<T> const & v, 
		T const & s
	)
	{
		return tvec2<T>(
			v.x >> T(s),
			v.y >> T(s));
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator>> 
	(
		T const & s, 
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			T(s) >> v.x,
			T(s) >> v.y);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> operator>>
	(
		tvec2<T> const & v1, 
		tvec2<T> const & v2
	)
	{
		return tvec2<T>(
			v1.x >> T(v2.x),
			v1.y >> T(v2.y));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> operator~ 
	(
		tvec2<T> const & v
	)
	{
		return tvec2<T>(
			~v.x,
			~v.y);
	}

	//////////////////////////////////////
	// tref definition

	template <typename T> 
	tref2<T>::tref2
	(
		T & x, 
		T & y
	) :
		x(x),
		y(y)
	{}

	template <typename T> 
	tref2<T>::tref2
	(
		tref2<T> const & r
	) :
		x(r.x),
		y(r.y)
	{}

	template <typename T> 
	tref2<T>::tref2
	(
		tvec2<T> const & v
	) :
		x(v.x),
		y(v.y)
	{}

	template <typename T> 
	tref2<T>& tref2<T>::operator= 
	(
		tref2<T> const & r
	)
	{
		x = r.x;
		y = r.y;
		return *this;
	}

	template <typename T> 
	tref2<T>& tref2<T>::operator= 
	(
		tvec2<T> const & v
	)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec2<T> tref2<T>::operator() ()
	{
		return tvec2<T>(this->x, this->y);
	}
}//namespace detail
}//namespace glm
