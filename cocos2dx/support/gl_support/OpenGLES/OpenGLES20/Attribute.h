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

#ifndef Attribute_H_
#define Attribute_H_

#include <OpenGLES/ES2/gl.h>
#include <string>

namespace OpenGLES {
	namespace OpenGLES2 {
		
		class ShaderProgram;
		
		class AttributeSimple {
		public:
			AttributeSimple(int id, GLint location);
			const int getId();
			const GLint getLocation();
			
		private:
			int id;
			GLint location;
		};
		
		class Attribute {
		public:
			Attribute();
			~Attribute();
			
			const GLint getLocation();
			void setEnabled(bool enabled);
			void setLocation(GLint loc);
			void upload(ShaderProgram *program);
			void setValues(GLint size, GLenum type, GLsizei stride, const void *pointer);
			void setSize(GLint size);
			void setType(GLenum type);
			void setNormalized(GLboolean normalized);
			void setStride(GLsizei stride);
			void setPointer(const void *pointer);
			
		private:
			GLint location;
			bool enabled;
			bool uploaded;
			
			GLint size;
			GLenum type;
			GLboolean normalized;
			GLsizei stride;
			const void *pointer;
		};
		
	}
}

#endif