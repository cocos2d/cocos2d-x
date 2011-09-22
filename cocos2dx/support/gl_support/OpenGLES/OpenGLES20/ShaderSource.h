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

#ifndef ShaderSource_H_
#define ShaderSource_H_

#include <OpenGLES/ES2/gl.h>
#include <string>

namespace OpenGLES {
	namespace OpenGLES2 {
			
		class ShaderFile;
		
		class ShaderSource {
		public:
			ShaderSource(ShaderFile *file);
			ShaderSource(ShaderFile *file, std::string additionalSource);
			
			void appendAdditionalSource(std::string additionalSource);
			ShaderFile *getFile();
			std::string getSource();
			
		private:
			bool expandSource();
			
			ShaderFile *file;
			std::string additionalSource;
			std::string source;
			bool sourceExpanded;
		};
	}
}

#endif
