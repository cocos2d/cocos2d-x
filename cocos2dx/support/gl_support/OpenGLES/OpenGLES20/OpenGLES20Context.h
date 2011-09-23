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

#ifndef OpenGLES2Context_H_
#define OpenGLES2Context_H_

#include "OpenGLESContext.h"
#include "MatrixStack.h"
#include "OpenGLESState.h"

namespace OpenGLES {
	namespace OpenGLES2 {
		
		class OpenGLES20Context : public OpenGLESContext {
		public:
			OpenGLES20Context();
			~OpenGLES20Context();

			// OpenglES 1.0 functions
			void glActiveTexture (GLenum texture);
			void glAlphaFunc (GLenum func, GLclampf ref);
			void glAlphaFuncx (GLenum func, GLclampx ref);
			void glBindTexture (GLenum target, GLuint texture);
			void glBlendFunc (GLenum sfactor, GLenum dfactor);
			void glClear(GLbitfield mask);
			void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
			void glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
			void glClearDepthf (GLclampf depth);
			void glClearDepthx (GLclampx depth);
			void glClearStencil (GLint s);
			void glClientActiveTexture (GLenum texture);
			void glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
			void glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
			void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
			void glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
			void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
			void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
			void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
			void glCullFace (GLenum mode);
			void glDeleteTextures (GLsizei n, const GLuint *textures);
			void glDepthFunc (GLenum func);
			void glDepthMask (GLboolean flag);
			void glDepthRangef (GLclampf zNear, GLclampf zFar);
			void glDepthRangex (GLclampx zNear, GLclampx zFar);
			void glDisable (GLenum cap);
			void glDisableClientState (GLenum array);
			void glDrawArrays(GLenum mode, GLint first, GLsizei count);
			void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
			void glEnable (GLenum cap);
			void glEnableClientState (GLenum array);
			void glFinish (void);
			void glFlush (void);
			void glFogf (GLenum pname, GLfloat param);
			void glFogfv (GLenum pname, const GLfloat *params);
			void glFogx (GLenum pname, GLfixed param);
			void glFogxv (GLenum pname, const GLfixed *params);
			void glFrontFace (GLenum mode);
			void glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
			void glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
			void glGenTextures (GLsizei n, GLuint *textures);
			GLenum glGetError (void);
			void glGetIntegerv (GLenum pname, GLint *params);
			const GLubyte *glGetString (GLenum name);
			void glHint (GLenum target, GLenum mode);
			void glLightModelf (GLenum pname, GLfloat param);
			void glLightModelfv (GLenum pname, const GLfloat *params);
			void glLightModelx (GLenum pname, GLfixed param);
			void glLightModelxv (GLenum pname, const GLfixed *params);
			void glLightf (GLenum light, GLenum pname, GLfloat param);
			void glLightfv (GLenum light, GLenum pname, const GLfloat *params);
			void glLightx (GLenum light, GLenum pname, GLfixed param);
			void glLightxv (GLenum light, GLenum pname, const GLfixed *params);
			void glLineWidth (GLfloat width);
			void glLineWidthx (GLfixed width);
			void glLoadIdentity (void);
			void glLoadMatrixf (const GLfloat *m);
			void glLoadMatrixx (const GLfixed *m);
			void glLogicOp (GLenum opcode);
			void glMaterialf (GLenum face, GLenum pname, GLfloat param);
			void glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
			void glMaterialx (GLenum face, GLenum pname, GLfixed param);
			void glMaterialxv (GLenum face, GLenum pname, const GLfixed *params);
			void glMatrixMode (GLenum mode);
			void glMultMatrixf (const GLfloat *m);
			void glMultMatrixx (const GLfixed *m);
			void glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
			void glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
			void glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
			void glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz);
			void glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
			void glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
			void glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
			void glPixelStorei (GLenum pname, GLint param);
			void glPointSize (GLfloat size);
			void glPointSizex (GLfixed size);
			void glPolygonOffset (GLfloat factor, GLfloat units);
			void glPolygonOffsetx (GLfixed factor, GLfixed units);
			void glPopMatrix (void);
			void glPushMatrix (void);
			void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
			void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
			void glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
			void glSampleCoverage (GLclampf value, GLboolean invert);
			void glSampleCoveragex (GLclampx value, GLboolean invert);
			void glScalef (GLfloat x, GLfloat y, GLfloat z);
			void glScalex (GLfixed x, GLfixed y, GLfixed z);
			void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
			void glShadeModel (GLenum mode);
			void glStencilFunc (GLenum func, GLint ref, GLuint mask);
			void glStencilMask (GLuint mask);
			void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
			void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void glTexEnvf (GLenum target, GLenum pname, GLfloat param);
			void glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
			void glTexEnvx (GLenum target, GLenum pname, GLfixed param);
			void glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params);
			void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
			void glTexParameterf (GLenum target, GLenum pname, GLfloat param);
			void glTexParameterx (GLenum target, GLenum pname, GLfixed param);
			void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
			void glTranslatef (GLfloat x, GLfloat y, GLfloat z);
			void glTranslatex (GLfixed x, GLfixed y, GLfixed z);
			void glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
			
			// OpenGL ES 1.1 functions
			void glBindBuffer (GLenum target, GLuint buffer);
			void glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
			void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
			void glClipPlanef(GLenum plane, const GLfloat *equation);
			void glClipPlanex (GLenum plane, const GLfixed *equation);
			void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
			void glDeleteBuffers (GLsizei n, const GLuint *buffers);
			void glGenBuffers (GLsizei n, GLuint *buffers);
			void glGetClipPlanef(GLenum pname, GLfloat eqn[4]);
			void glGetFloatv(GLenum pname, GLfloat *params);
			void glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
			void glGetLightxv (GLenum light, GLenum pname, GLfixed *params);
			void glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
			void glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params);
			void glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params);
			void glGetTexEnviv (GLenum env, GLenum pname, GLint *params);
			void glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params);
			void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
			void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
			void glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params);
			void glGetBooleanv (GLenum pname, GLboolean *params);
			void glGetFixedv (GLenum pname, GLfixed *params);
			void glGetPointerv (GLenum pname, void **params);
			GLboolean glIsBuffer (GLuint buffer);
			GLboolean glIsEnabled (GLenum cap);
			GLboolean glIsTexture (GLuint texture);
			void glPointParameterf (GLenum pname, GLfloat param);
			void glPointParameterfv (GLenum pname, const GLfloat *params);
			void glPointParameterx (GLenum pname, GLfixed param);
			void glPointParameterxv (GLenum pname, const GLfixed *params);
			void glTexEnvi (GLenum target, GLenum pname, GLint param);
			void glTexEnviv (GLenum target, GLenum pname, const GLint *params);
			void glTexParameteri (GLenum target, GLenum pname, GLint param);
			void glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
			
			
			// OpenGLE S 1.1 extensions
			void glCurrentPaletteMatrixOES (GLuint matrixpaletteindex);
			void glLoadPaletteFromModelViewMatrixOES (void);
			void glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void glWeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void glPointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer);
			void glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
			void glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height);
			void glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
			void glDrawTexsvOES (const GLshort *coords);
			void glDrawTexivOES (const GLint *coords);
			void glDrawTexxvOES (const GLfixed *coords);
			void glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
			void glDrawTexfvOES (const GLfloat *coords);
			
			// OpenGL ES 2
			void glAttachShader (GLuint program, GLuint shader);
			void glBindAttribLocation (GLuint program, GLuint index, const GLchar* name);
			void glBindFramebuffer (GLenum target, GLuint framebuffer);
			void glBindRenderbuffer (GLenum target, GLuint renderbuffer);
			void glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
			void glBlendEquation ( GLenum mode );
			void glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha);
			void glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
			GLenum glCheckFramebufferStatus (GLenum target);
			void glCompileShader (GLuint shader);
			GLuint glCreateProgram (void);
			GLuint glCreateShader (GLenum type);
			void glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers);
			void glDeleteProgram (GLuint program);
			void glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers);
			void glDeleteShader (GLuint shader);
			void glDetachShader (GLuint program, GLuint shader);
			void glDisableVertexAttribArray (GLuint index);
			void glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments);
			void glEnableVertexAttribArray (GLuint index);
			void glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
			void glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
			void glGenerateMipmap (GLenum target);
			void glGenFramebuffers (GLsizei n, GLuint* framebuffers);
			void glGenRenderbuffers (GLsizei n, GLuint* renderbuffers);
			void glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
			void glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
			void glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
			int glGetAttribLocation (GLuint program, const GLchar* name);
			void glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params);
			void glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params);
			void glGetProgramiv (GLuint program, GLenum pname, GLint* params);
			void glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
			void glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params);
			void glGetShaderiv (GLuint shader, GLenum pname, GLint* params);
			void glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
			void glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
			void glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
			void glGetUniformfv (GLuint program, GLint location, GLfloat* params);
			void glGetUniformiv (GLuint program, GLint location, GLint* params);
			int glGetUniformLocation (GLuint program, const GLchar* name);
			void glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params);
			void glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params);
			void glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer);
			GLboolean glIsFramebuffer (GLuint framebuffer);
			GLboolean glIsProgram (GLuint program);
			GLboolean glIsRenderbuffer (GLuint renderbuffer);
			GLboolean glIsShader (GLuint shader);
			void glLinkProgram (GLuint program);
			void glReleaseShaderCompiler (void);
			void glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
			void glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
			void glResolveMultisampleFramebufferAPPLE(void);
			void glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
			void glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
			void glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
			void glStencilMaskSeparate (GLenum face, GLuint mask);
			void glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
			void glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params);
			void glUniform1f (GLint location, GLfloat x);
			void glUniform1fv (GLint location, GLsizei count, const GLfloat* v);
			void glUniform1i (GLint location, GLint x);
			void glUniform1iv (GLint location, GLsizei count, const GLint* v);
			void glUniform2f (GLint location, GLfloat x, GLfloat y);
			void glUniform2fv (GLint location, GLsizei count, const GLfloat* v);
			void glUniform2i (GLint location, GLint x, GLint y);
			void glUniform2iv (GLint location, GLsizei count, const GLint* v);
			void glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z);
			void glUniform3fv (GLint location, GLsizei count, const GLfloat* v);
			void glUniform3i (GLint location, GLint x, GLint y, GLint z);
			void glUniform3iv (GLint location, GLsizei count, const GLint* v);
			void glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
			void glUniform4fv (GLint location, GLsizei count, const GLfloat* v);
			void glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w);
			void glUniform4iv (GLint location, GLsizei count, const GLint* v);
			void glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
			void glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
			void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
			void glUseProgram (GLuint program);
			void glValidateProgram (GLuint program);
			void glVertexAttrib1f (GLuint indx, GLfloat x);
			void glVertexAttrib1fv (GLuint indx, const GLfloat* values);
			void glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y);
			void glVertexAttrib2fv (GLuint indx, const GLfloat* values);
			void glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z);
			void glVertexAttrib3fv (GLuint indx, const GLfloat* values);
			void glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
			void glVertexAttrib4fv (GLuint indx, const GLfloat* values);
			void glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
			
			// OpenGL ES 2 Extensions
			void glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params);
			GLvoid * glMapBufferOES (GLenum target, GLenum access);
			GLboolean glUnmapBufferOES (GLenum target);
			
			// Non-API
			int getCachedShaderAmount();
			
		private:
			MatrixStack matrixStack;
			OpenGLESState openGLESState;
			GLuint shaderProgramId;
			
			void prepareToDraw();
		};
		
	}
}

#endif
