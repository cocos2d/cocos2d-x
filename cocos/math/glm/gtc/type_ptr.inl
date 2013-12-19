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
/// @ref gtc_type_ptr
/// @file glm/gtc/type_ptr.inl
/// @date 2011-06-15 / 2011-12-07
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{ 
	/// @addtogroup gtc_type_ptr
	/// @{

	/// Return the constant address to the data of the input parameter.
    /// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tvec2<T> const & vec
	)
	{
		return &(vec.x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tvec2<T> & vec
	)
	{
		return &(vec.x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tvec3<T> const & vec
	)
	{
		return &(vec.x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tvec3<T> & vec
	)
	{
		return &(vec.x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(	
		detail::tvec4<T> const & vec
	)
	{
		return &(vec.x);
	}

	//! Return the constant address to the data of the input parameter.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(	
		detail::tvec4<T> & vec
	)
	{
		return &(vec.x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat2x2<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat2x2<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat3x3<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat3x3<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat4x4<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	//! From GLM_GTC_type_ptr extension.
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat4x4<T> & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat2x3<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat2x3<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat3x2<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat3x2<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat2x4<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat2x4<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat4x2<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(	
		detail::tmat4x2<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat3x4<T> const & mat
	)
	{
		return &(mat[0].x);
	}

	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
		detail::tmat3x4<T> & mat
	)
	{
		return &(mat[0].x);
	}
		
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
		detail::tmat4x3<T> const & mat
	)
	{
		return &(mat[0].x);
	}
    
	//! Get the address of the matrix content.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr(detail::tmat4x3<T> & mat)
	{
		return &(mat[0].x);
	}
    
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T const * value_ptr
	(
        detail::tquat<T> const & q
    )
	{
		return &(q[0]);
	}
    
	//! Return the constant address to the data of the input parameter.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER T * value_ptr
	(
        detail::tquat<T> & q
    )
	{
		return &(q[0]);
	}

	//! Build a vector from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tvec2<T> make_vec2(T const * const ptr)
	{
		detail::tvec2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tvec2<T>));
		return Result;
	}

	//! Build a vector from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tvec3<T> make_vec3(T const * const ptr)
	{
		detail::tvec3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tvec3<T>));
		return Result;
	}

	//! Build a vector from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tvec4<T> make_vec4(T const * const ptr)
	{
		detail::tvec4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tvec4<T>));
		return Result;
	}

	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> make_mat2x2(T const * const ptr)
	{
		detail::tmat2x2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat2x2<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x3<T> make_mat2x3(T const * const ptr)
	{
		detail::tmat2x3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat2x3<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x4<T> make_mat2x4(T const * const ptr)
	{
		detail::tmat2x4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat2x4<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x2<T> make_mat3x2(T const * const ptr)
	{
		detail::tmat3x2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat3x2<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> make_mat3x3(T const * const ptr)
	{
		detail::tmat3x3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat3x3<T>));
		return Result;
	}

	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x4<T> make_mat3x4(T const * const ptr)
	{
		detail::tmat3x4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat3x4<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x2<T> make_mat4x2(T const * const ptr)
	{
		detail::tmat4x2<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat4x2<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x3<T> make_mat4x3(T const * const ptr)
	{
		detail::tmat4x3<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat4x3<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> make_mat4x4(T const * const ptr)
	{
		detail::tmat4x4<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tmat4x4<T>));
		return Result;
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat2x2<T> make_mat2(T const * const ptr)
	{
		return make_mat2x2(ptr);
	}
        
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat3x3<T> make_mat3(T const * const ptr)
	{
		return make_mat3x3(ptr);
	}
		
	//! Build a matrix from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tmat4x4<T> make_mat4(T const * const ptr)
	{
		return make_mat4x4(ptr);
	}
 
	//! Build a quaternion from a pointer.
	/// @see gtc_type_ptr
	template<typename T>
	GLM_FUNC_QUALIFIER detail::tquat<T> make_quat(T const * const ptr)
	{
		detail::tquat<T> Result;
		memcpy(value_ptr(Result), ptr, sizeof(detail::tquat<T>));
		return Result;
	}
    
	/// @}
}//namespace glm

