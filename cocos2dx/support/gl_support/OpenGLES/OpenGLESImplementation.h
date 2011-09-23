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

#ifndef OpenGLESImplementation_H_
#define OpenGLESImplementation_H_

namespace OpenGLES {
	class OpenGLESImplementation {
	public:
		OpenGLESImplementation();
		virtual ~OpenGLESImplementation();
		
		virtual void init() = 0;
		void print();
		
		//protected:
		int colorReadFormat;
		int colorReadType;
		int maxCombinedTextureImageUnits;
		int maxCubeMapTextureSize;
		int maxFragmentUniformVectors;
		int maxRenderBufferSize;
		int maxTextureImageUnits;
		int maxTextureSize;
		int maxVaryingVectors;
		int maxVertexAttribs;
		int maxVertexTextureImageUnits;
		int maxVertexUniformVectors;
		int maxViewportDims[2];
		int numCompressedTextureFormats;
		int numShaderBinaryFormats;
		int* shaderBinaryFormats;
		bool shaderCompilerSupported;
		int depthBits;
		int stencilBits;
		
		// TODO: extensions?
	};
}
#endif
