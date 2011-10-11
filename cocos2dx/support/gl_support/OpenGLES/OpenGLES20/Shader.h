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

#ifndef Shader_H_
#define Shader_H_

#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "OpenGLES/ES2/gl.h"
#include "OpenGLES/ES2/glext.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
#error "Not tested platform"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#error "Not tested platform"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
#error "Not tested platform"
#include <IwGL.h>
#endif

#include <vector>

namespace OpenGLES {
	namespace OpenGLES2 {
		
		class ShaderSource;
		
		class Shader {
		public:
			Shader(GLenum type, std::vector<ShaderSource *> &sources);
			~Shader();
			
			GLuint compile();
		private:
			bool readShaderSource();
			
			GLenum type;
			std::vector<ShaderSource *> &sources;
			GLuint id;
		};
	}
}

#endif
