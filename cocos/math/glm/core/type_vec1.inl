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
/// @file glm/core/type_vec1.inl
/// @date 2008-08-25 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	template <typename T>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tvec1<T>::size_type tvec1<T>::length() const
	{
		return 1;
	}

	//////////////////////////////////////
	// Accesses

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec1<T>::value_type & tvec1<T>::operator[]
	(
		size_type i
	)
	{
		assert(i < this->length());
		return (&x)[i];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER typename tvec1<T>::value_type const & tvec1<T>::operator[]
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
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1() :
		x(value_type(0))
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		ctor
	)
	{}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		tvec1<T> const & v
	) :
		x(v.x)
	{}

	//////////////////////////////////////
	// Explicit basic constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		value_type const & s
	) :
		x(s)
	{}

	//////////////////////////////////////
	// Swizzle constructors

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		tref1<T> const & r
	) :
		x(r.x)
	{}

	//////////////////////////////////////
	// Convertion scalar constructors
		
	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		U const & s
	) :
		x(value_type(s))
	{}

	//////////////////////////////////////
	// Convertion vector constructors

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		tvec2<U> const & v
	) :
		x(value_type(v.x))
	{}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		tvec3<U> const & v
	) :
		x(value_type(v.x))
	{}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T>::tvec1
	(
		tvec4<U> const & v
	) :
		x(value_type(v.x))
	{}

	//////////////////////////////////////
	// Unary arithmetic operators

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator=
	(
		tvec1<T> const & v
	)
	{
		this->x = v.x;
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator=
	(
		tvec1<U> const & v
	)
	{
		this->x = T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator+=
	(
		U const & s
	)
	{
		this->x += T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator+=
	(
		tvec1<U> const & v
	)
	{
		this->x += T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator-=
	(
		U const & s
	)
	{
		this->x -= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator-=
	(
		tvec1<U> const & v
	)
	{
		this->x -= T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator*=
	(
		U const & s
	)
	{
		this->x *= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator*=
	(	
		tvec1<U> const & v
	)
	{
		this->x *= T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator/=
	(
		U const & s
	)
	{
		this->x /= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator/=
	(
		tvec1<U> const & v
	)
	{
		this->x /= T(v.x);
		return *this;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator++()
	{
		++this->x;
		return *this;
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator--()
	{
		--this->x;
		return *this;
	}

	//////////////////////////////////////
	// Boolean operators

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator==
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return (v1.x == v2.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER bool operator!=
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return (v1.x != v2.x);
	}

	//////////////////////////////////////
	// Unary bit operators

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator%=
	(
		U const & s
	)
	{
		this->x %= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator%=
	(
		tvec1<U> const & v
	)
	{
		this->x %= T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator&=
	(
		U const & s
	)
	{
		this->x &= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator&=
	(
		tvec1<U> const & v
	)
	{
		this->x &= T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator|=
	(
		U const & s
	)
	{
		this->x |= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator|=
	(
		tvec1<U> const & v
	)
	{
		this->x |= U(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator^=
	(
		U const & s
	)
	{
		this->x ^= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator^=
	(
		tvec1<U> const & v
	)
	{
		this->x ^= T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator<<=
	(
		U const & s
	)
	{
		this->x <<= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator<<=
	(
		tvec1<U> const & v
	)
	{
		this->x <<= T(v.x);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator>>=
	(
		U const & s
	)
	{
		this->x >>= T(s);
		return *this;
	}

	template <typename T>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec1<T> & tvec1<T>::operator>>=
	(
		tvec1<U> const & v
	)
	{
		this->x >>= T(v.x);
		return *this;
	}

	//////////////////////////////////////
	// Swizzle operators

	template <typename T>
	GLM_FUNC_QUALIFIER T 
	tvec1<T>::swizzle(comp x) const
	{
		return (*this)[x];
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec2<T> 
	tvec1<T>::swizzle
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
	GLM_FUNC_QUALIFIER tvec3<T> 
	tvec1<T>::swizzle
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
	GLM_FUNC_QUALIFIER tvec4<T> 
	tvec1<T>::swizzle
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
	GLM_FUNC_QUALIFIER tref1<T> 
	tvec1<T>::swizzle
	(
		comp x
	)
	{
		return tref1<T>(
			(*this)[x]);
	}

	//////////////////////////////////////
	// Binary arithmetic operators

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator+ 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x + s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator+ 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s + v.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator+ 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x + v2.x);
	}

	//operator-
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator- 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x - s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator- 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s - v.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator- 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x - v2.x);
	}

	//operator*
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator* 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x * s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator* 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s * v.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator*
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x * v2.x);
	}

	//operator/
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator/ 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x / s);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator/ 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s / v.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator/ 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x / v2.x);
	}

	// Unary constant operators
	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator- 
	(
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			-v.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator++ 
	(
		tvec1<T> const & v, 
		int
	)
	{
		return tvec1<T>(
			v.x + T(1));
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator-- 
	(
		tvec1<T> const & v, 
		int
	)
	{
		return tvec1<T>(
			v.x - T(1));
	}

	//////////////////////////////////////
	// Binary bit operators

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator% 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x % s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator% 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s % v.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator% 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x % v2.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator& 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x & s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator& 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s & v.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator& 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x & v2.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator| 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x | s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator| 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s | v.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator| 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x | v2.x);
	}
		
	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator^ 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x ^ s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator^ 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s ^ v.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator^ 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x ^ v2.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator<< 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x << s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator<< 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s << v.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator<< 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x << v2.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator>> 
	(
		tvec1<T> const & v, 
		typename tvec1<T>::value_type const & s
	)
	{
		return tvec1<T>(
			v.x >> s);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator>> 
	(
		typename tvec1<T>::value_type const & s, 
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			s >> v.x);
	}

	template <typename T>
	GLM_FUNC_QUALIFIER tvec1<T> operator>> 
	(
		tvec1<T> const & v1, 
		tvec1<T> const & v2
	)
	{
		return tvec1<T>(
			v1.x >> v2.x);
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tvec1<T> operator~ 
	(
		tvec1<T> const & v
	)
	{
		return tvec1<T>(
			~v.x);
	}

	//////////////////////////////////////
	// tref definition

	template <typename T> 
	GLM_FUNC_QUALIFIER tref1<T>::tref1
	(
		T & x
	) :
		x(x)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref1<T>::tref1
	(
		tref1<T> const & r
	) :
		x(r.x)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref1<T>::tref1
	(
		tvec1<T> const & v
	) :
		x(v.x)
	{}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref1<T> & tref1<T>::operator= 
	(
		tref1<T> const & r
	)
	{
		x = r.x;
		return *this;
	}

	template <typename T> 
	GLM_FUNC_QUALIFIER tref1<T> & tref1<T>::operator= 
	(
		tvec1<T> const & v
	)
	{
		x = v.x;
		return *this;
	}

}//namespace detail
}//namespace glm
