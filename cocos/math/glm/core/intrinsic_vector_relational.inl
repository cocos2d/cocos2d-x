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
/// @file glm/core/intrinsic_vector_relational.inl
/// @date 2009-06-09 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////
//
//// lessThan
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec2<valType>::bool_type lessThan
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//    return typename detail::tvec2<bool>::bool_type(x.x < y.x, x.y < y.y);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec3<valType>::bool_type lessThan
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec3<bool>::bool_type(x.x < y.x, x.y < y.y, x.z < y.z);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec4<valType>::bool_type lessThan
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec4<bool>::bool_type(x.x < y.x, x.y < y.y, x.z < y.z, x.w < y.w);
//}
//
//// lessThanEqual
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec2<valType>::bool_type lessThanEqual
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec2<bool>::bool_type(x.x <= y.x, x.y <= y.y);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec3<valType>::bool_type lessThanEqual
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec3<bool>::bool_type(x.x <= y.x, x.y <= y.y, x.z <= y.z);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec4<valType>::bool_type lessThanEqual
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec4<bool>::bool_type(x.x <= y.x, x.y <= y.y, x.z <= y.z, x.w <= y.w);
//}
//
//// greaterThan
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec2<valType>::bool_type greaterThan
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec2<bool>::bool_type(x.x > y.x, x.y > y.y);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec3<valType>::bool_type greaterThan
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec3<bool>::bool_type(x.x > y.x, x.y > y.y, x.z > y.z);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec4<valType>::bool_type greaterThan
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec4<bool>::bool_type(x.x > y.x, x.y > y.y, x.z > y.z, x.w > y.w);
//}
//
//// greaterThanEqual
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec2<valType>::bool_type greaterThanEqual
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec2<bool>::bool_type(x.x >= y.x, x.y >= y.y);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec3<valType>::bool_type greaterThanEqual
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec3<bool>::bool_type(x.x >= y.x, x.y >= y.y, x.z >= y.z);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec4<valType>::bool_type greaterThanEqual
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec4<bool>::bool_type(x.x >= y.x, x.y >= y.y, x.z >= y.z, x.w >= y.w);
//}
//
//// equal
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec2<valType>::bool_type equal
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec2<valType>::bool_type(x.x == y.x, x.y == y.y);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec3<valType>::bool_type equal
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec3<valType>::bool_type(x.x == y.x, x.y == y.y, x.z == y.z);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec4<valType>::bool_type equal
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec4<valType>::bool_type(x.x == y.x, x.y == y.y, x.z == y.z, x.w == y.w);
//}
//
//// notEqual
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec2<valType>::bool_type notEqual
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec2<valType>::bool_type(x.x != y.x, x.y != y.y);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec3<valType>::bool_type notEqual
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec3<valType>::bool_type(x.x != y.x, x.y != y.y, x.z != y.z);
//}
//
//template <typename valType>
//GLM_FUNC_QUALIFIER typename detail::tvec4<valType>::bool_type notEqual
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec4<valType>::bool_type(x.x != y.x, x.y != y.y, x.z != y.z, x.w != y.w);
//}
//
//// any
//GLM_FUNC_QUALIFIER bool any(detail::tvec2<bool> const & x)
//{
//	return x.x || x.y;
//}
//
//GLM_FUNC_QUALIFIER bool any(detail::tvec3<bool> const & x)
//{
//    return x.x || x.y || x.z;
//}
//
//GLM_FUNC_QUALIFIER bool any(detail::tvec4<bool> const & x)
//{
//    return x.x || x.y || x.z || x.w;
//}
//
//// all
//GLM_FUNC_QUALIFIER bool all(const detail::tvec2<bool>& x)
//{
//    return x.x && x.y;
//}
//
//GLM_FUNC_QUALIFIER bool all(const detail::tvec3<bool>& x)
//{
//    return x.x && x.y && x.z;
//}
//
//GLM_FUNC_QUALIFIER bool all(const detail::tvec4<bool>& x)
//{
//    return x.x && x.y && x.z && x.w;
//}
//
//// not
//GLM_FUNC_QUALIFIER detail::tvec2<bool>::bool_type not_
//(
//	detail::tvec2<bool> const & v
//)
//{
//    return detail::tvec2<bool>::bool_type(!v.x, !v.y);
//}
//
//GLM_FUNC_QUALIFIER detail::tvec3<bool>::bool_type not_
//(
//	detail::tvec3<bool> const & v
//)
//{
//    return detail::tvec3<bool>::bool_type(!v.x, !v.y, !v.z);
//}
//
//GLM_FUNC_QUALIFIER detail::tvec4<bool>::bool_type not_
//(
//	detail::tvec4<bool> const & v
//)
//{
//    return detail::tvec4<bool>::bool_type(!v.x, !v.y, !v.z, !v.w);
//}