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

#include "OpenGLESImplementation.h"
#include "OpenGLESUtil.h"

using namespace OpenGLES;

OpenGLESImplementation::OpenGLESImplementation() 
{
	
}

OpenGLESImplementation::~OpenGLESImplementation() 
{
	free(shaderBinaryFormats);
}

void OpenGLESImplementation::print()
{
	OPENGLES_LOG_DEBUG_MESSAGE("OpenGL Implementation Details:");
	OPENGLES_LOG_DEBUG_MESSAGE("------------------------------");
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max viewport dimensions: ") + maxViewportDims[0] + OpenGLESString("*") + maxViewportDims[1]);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Depth bits: ") + depthBits);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Stencil bits: ") + stencilBits);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Color read format: ") + colorReadFormat);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Color read type: ") + colorReadType);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max render buffer size: ") + maxRenderBufferSize);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max texture size: ") + maxTextureSize);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Number of compressed texture formats: ") + numCompressedTextureFormats);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max combined texture image units: ") + maxCombinedTextureImageUnits);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max cubemap texture size: ") + maxCubeMapTextureSize);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Shader compiler support: ") + shaderCompilerSupported);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Number of shader binary formats: ") + numShaderBinaryFormats);
	for (int i = 0; i < numShaderBinaryFormats; i++) {
		OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Supported shader binary format: ") + shaderBinaryFormats[i]);
	}
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max vertex attributes: ") + maxVertexAttribs);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max vertex uniform vectors: ") + maxVertexUniformVectors);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max varying vectors: ") + maxVaryingVectors);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max fragment uniform vectors: ") + maxFragmentUniformVectors);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max texture image units: ") + maxTextureImageUnits);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Max vertex texture image units: ") + maxVertexTextureImageUnits);
	OPENGLES_LOG_DEBUG_MESSAGE("------------------------------");
}
