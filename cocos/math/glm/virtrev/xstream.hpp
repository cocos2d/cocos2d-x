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
/// @ref virtrev_xstream
/// @file glm/virtrev/xstream.hpp
/// @date 2008-05-24 / 2008-05-26
/// @author Mathieu Roumillac (matrem84.free.fr)
///
/// @see core (dependence)
/// @see gtc_matrix_access (dependence)
///
/// @defgroup virtrev_xstream GLM_VIRTREV_xstream: xml like output
/// @ingroup virtrev
/// 
/// @brief Streaming vector and matrix in a xml way.
/// 
/// Include <glm/virtrev/xstream.hpp> for this functionality.
///////////////////////////////////////////////////////////////////////////////////

#ifndef GLM_VIRTREV_xstream
#define GLM_VIRTREV_xstream GLM_VERSION

#include "../glm.hpp"
#include "../gtc/matrix_access.hpp"
#include <iostream>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_VIRTREV_xstream extension included")
#endif
/*
namespace glm{
namespace detail
{
	template<typename T>
	std::ostream & operator << (std::ostream & stream, glm::detail::tvec2<T> const & vec)
	{
		stream << "<glm_vec2 ";
		stream << "x=\"" << vec.x << "\" ";
		stream << "y=\"" << vec.y << "\" ";
		stream << "/>";

		return stream;
	}

	template<typename T>
	std::ostream & operator << (std::ostream & stream, glm::detail::tvec3<T> const & vec)
	{
		stream << "<glm_vec3 ";
		stream << "x=\"" << vec.x << "\" ";
		stream << "y=\"" << vec.y << "\" ";
		stream << "z=\"" << vec.z << "\" ";
		stream << "/>";

		return stream;
	}

	template<typename T>
	std::ostream & operator << (std::ostream & stream, glm::detail::tvec4<T> const & vec)
	{
		stream << "<glm_vec4 ";
		stream << "x=\"" << vec.x << "\" ";
		stream << "y=\"" << vec.y << "\" ";
		stream << "z=\"" << vec.z << "\" ";
		stream << "w=\"" << vec.w << "\" ";
		stream << "/>";

		return stream;
	}

	template<typename T>
	std::ostream & operator << (std::ostream & stream, glm::detail::tmat2x2<T> const & mat)
	{
		stream << "<glm_mat2>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
		stream << "/>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
		stream << "/>" << std::endl;
		stream << "</glm_mat2>";

		return stream;
	}

	template<typename T>
	std::ostream & operator << (std::ostream & stream, glm::detail::tmat3x3<T> const & mat)
	{
		stream << "<glm_mat3>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 0)[2] << "\" ";
		stream << "/>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 1)[2] << "\" ";
		stream << "/>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 2)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 2)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 2)[2] << "\" ";
		stream << "/>" << std::endl;
		stream << "</glm_mat3>";

		return stream;
	}

	template<typename T>
	std::ostream & operator << (std::ostream & stream, glm::detail::tmat4x4<T> const & mat)
	{
		stream << "<glm_mat4>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 0)[2] << "\" ";
		stream << "w=\"" << glm::row(mat, 0)[3] << "\" ";
		stream << "/>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 1)[2] << "\" ";
		stream << "w=\"" << glm::row(mat, 1)[3] << "\" ";
		stream << "/>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 2)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 2)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 2)[2] << "\" ";
		stream << "w=\"" << glm::row(mat, 2)[3] << "\" ";
		stream << "/>" << std::endl;
		stream << "<row ";
		stream << "x=\"" << glm::row(mat, 3)[0] << "\" ";
		stream << "y=\"" << glm::row(mat, 3)[1] << "\" ";
		stream << "z=\"" << glm::row(mat, 3)[2] << "\" ";
		stream << "w=\"" << glm::row(mat, 3)[3] << "\" ";
		stream << "/>" << std::endl;
		stream << "</glm_mat4>";
			
		return stream;
	}

}//namespace detail
}//namespace glm
*/
#endif//GLM_VIRTREV_xstream
