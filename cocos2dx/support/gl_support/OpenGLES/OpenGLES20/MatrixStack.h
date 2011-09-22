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

#ifndef MatrixStack_H_
#define MatrixStack_H_

#include "OpenGLESMath.h"
#include <vector>

namespace OpenGLES {
	
	class OpenGLESImplementation;
	
	namespace OpenGLES2 {
		
		class OpenGLESState;
		
		class MatrixStack {
		public:
			MatrixStack(OpenGLESState *openGLESState, OpenGLESImplementation *impl);
			~MatrixStack();
			
			void init();
			void setMatrixMode(GLenum mode);
			void pushMatrix();
			void popMatrix();
			
			void loadIdentity();
			void loadMatrix(const GLfloat *newMat);
			void translate(GLfloat x, GLfloat y, GLfloat z);
			void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
			void scale(GLfloat x, GLfloat y, GLfloat z);
			void frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
			void ortho( GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar );
			void multiply(const GLfloat *m);
			
			Matrix4x4<GLfloat>* getModelViewMatrix();
			Matrix4x4<GLfloat>* getProjectionMatrix();
			Matrix4x4<GLfloat>* getTextureMatrix(int index);
			
		private:
			OpenGLESState *openGLESState;
			OpenGLESImplementation * implementation;
			GLenum mode;
			std::vector<Matrix4x4<GLfloat> *> modelViewStack;
			std::vector<Matrix4x4<GLfloat> *> projectionStack;
			std::vector<Matrix4x4<GLfloat> *> *textureStacks;
			std::vector<Matrix4x4<GLfloat> *> *currentStack;
		};
	}
}

#endif
