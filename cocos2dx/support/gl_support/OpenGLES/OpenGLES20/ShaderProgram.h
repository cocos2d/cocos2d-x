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

#ifndef ShaderProgram_H_
#define ShaderProgram_H_

#include <stdlib.h>
#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include <vector>
#include "OpenGLESString.h"

namespace OpenGLES {
	namespace OpenGLES2 {
		
		class Shader;
		class UniformBase;
		class AttributeSimple;
		class UniformSimple;
		
		class ShaderProgram {
		public:
			ShaderProgram(OpenGLESString name, Shader *vertexShader, Shader *fragmentShader);
			ShaderProgram(OpenGLESString name, const void *binary, int length, GLenum binaryformat);
			~ShaderProgram();
			
			void use();
			void unuse();
			void validate();
			
			std::vector<AttributeSimple *> *getActiveAttributes();
			std::vector<UniformSimple *> *getActiveUniforms();
			
			void setAttributeVertexPointer(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
			
			void setUniform1i(const char *name, GLint i);
			void setUniform1i(GLint loc, GLint i);
			void setUniform1iv(const char *name, GLint count, GLint* i);
			void setUniform1iv(GLint loc, GLint count, GLint* i);
			void setUniform1f(const char *name, GLfloat v);
			void setUniform1f(GLint loc, GLfloat v);
			void setUniform3f(const char *name, GLfloat x, GLfloat y, GLfloat z);
			void setUniform3f(GLint loc, GLfloat x, GLfloat y, GLfloat z);
			void setUniform3fv(const char *name, GLint count, GLfloat *v);
			void setUniform3fv(GLint loc, GLint count, GLfloat *v);
			void setUniform4f(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
			void setUniform4f(GLint loc, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
			void setUniform4fv(const char *name, GLint count, GLfloat *v);
			void setUniform4fv(GLint loc, GLint count, GLfloat *v);
			void setUniformMatrix4fv(const char *name, GLfloat* m);
			void setUniformMatrix4fv(GLint loc, GLfloat* m);
			void setUniformMatrix3fv(const char *name, GLfloat* m);
			void setUniformMatrix3fv(GLint loc, GLfloat* m);
			
		private:
			GLuint createProgram(Shader *vertexShader, Shader *fragmentShader);
			GLint getUniformLocation(const char* name);
			GLint getAttributeLocation(const char* name);
			
			OpenGLESString name;
			GLuint program;
			
			GLint activeUniforms;
			GLint activeUniformsMaxLength;
			std::vector<UniformSimple *> uniforms;
			
			GLint activeAttributes;
			GLint activeAttributesMaxLength;
			std::vector<AttributeSimple *> attributes;
			
			GLint attachedShaders;
		};
		
	}
}

#endif
