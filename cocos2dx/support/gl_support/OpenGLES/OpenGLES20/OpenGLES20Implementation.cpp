/*
 Copyright 2009 Johannes Vuorinen
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 
 http://www.apache.org/licenses/LICENSE-2.0 
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "OpenGLES20Implementation.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <stdlib.h>
#include "OpenGLESMath.h"

using namespace OpenGLES::OpenGLES2;

OpenGLES20Implementation::OpenGLES20Implementation() : OpenGLESImplementation()
{
	
}

OpenGLES20Implementation::~OpenGLES20Implementation()
{
	
}

void OpenGLES20Implementation::init() 
{	
//	glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &colorReadFormat);
//	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
//	glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &colorReadType);
//	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	maxCombinedTextureImageUnits = std::min(3, maxCombinedTextureImageUnits); // TODO: currently shaders support 3 textures
	glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &maxCubeMapTextureSize);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &maxFragmentUniformVectors);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderBufferSize);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	maxTextureImageUnits = std::min(3, maxTextureImageUnits); // TODO: currently shaders support 3 textures
	glGetIntegerv(GL_MAX_VARYING_VECTORS, &maxVaryingVectors);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureImageUnits);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertexUniformVectors);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, maxViewportDims);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCompressedTextureFormats);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &numShaderBinaryFormats);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	shaderBinaryFormats = (int *)malloc(sizeof(int) * numShaderBinaryFormats);
	glGetIntegerv(GL_SHADER_BINARY_FORMATS, shaderBinaryFormats);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	
	unsigned char tmp;
	glGetBooleanv(GL_SHADER_COMPILER, &tmp);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	shaderCompilerSupported = tmp == 0;
	
	glGetIntegerv(GL_DEPTH_BITS, &depthBits);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	glGetIntegerv(GL_STENCIL_BITS, &stencilBits);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	
	print();
}
