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

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "OpenGLES20Context.h"
#include "ShaderProgram.h"
#include "OpenGLESUtil.h"
#include "OpenGLES20Implementation.h"
#include "OpenGLESConfig.h"

using namespace OpenGLES::OpenGLES2;

OpenGLES20Context::OpenGLES20Context() : OpenGLESContext(2, new OpenGLES20Implementation()), matrixStack(&openGLESState, implementation), openGLESState(), shaderProgramId(0)
{
	implementation->init();
	matrixStack.init();
	openGLESState.init(implementation);
}

OpenGLES20Context::~OpenGLES20Context() 
{
	
}

void OpenGLES20Context::glActiveTexture (GLenum texture)
{
	openGLESState.setActiveTexture(texture - GL_TEXTURE0);
	::glActiveTexture(texture);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glAlphaFunc (GLenum func, GLclampf ref)
{
	openGLESState.setAlphaFunc(func);
	openGLESState.setAlphaFuncValue(OpenGLESMath::clamp<GLclampf>(ref, 0, 1));
}

void OpenGLES20Context::glAlphaFuncx (GLenum func, GLclampx ref)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glAlphaFuncx Not implemented.");
}

void OpenGLES20Context::glBindTexture (GLenum target, GLuint texture)
{
	openGLESState.setBoundTexture(texture);
	openGLESState.setTextureFormat();
	::glBindTexture(target, texture);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBlendFunc (GLenum sfactor, GLenum dfactor)
{
	::glBlendFunc(sfactor, dfactor);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glClear(GLbitfield mask)
{
	::glClear(mask);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	::glClearColor(red, green, blue, alpha);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glClearColorx Not implemented.");
}

void OpenGLES20Context::glClearDepthf (GLclampf depth)
{
	::glClearDepthf(depth);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glClearDepthx (GLclampx depth)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glClearDepthx Not implemented.");
}

void OpenGLES20Context::glClearStencil (GLint s)
{
	::glClearStencil(s);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glClientActiveTexture (GLenum texture)
{
	openGLESState.setClientActiveTexture(texture - GL_TEXTURE0);
}

void OpenGLES20Context::glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glColor4f Not implemented.");
}

void OpenGLES20Context::glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glColor4x Not implemented.");
}

void OpenGLES20Context::glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	::glColorMask(red, green, blue, alpha);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	openGLESState.setColor(size, type, stride, pointer);
}

void OpenGLES20Context::glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
	::glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	::glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glCullFace (GLenum mode)
{
	::glCullFace(mode);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDeleteTextures (GLsizei n, const GLuint *textures)
{
	::glDeleteTextures(n, textures);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDepthFunc (GLenum func)
{
	::glDepthFunc(func);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDepthMask (GLboolean flag)
{
	::glDepthMask(flag);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDepthRangef (GLclampf zNear, GLclampf zFar)
{
	::glDepthRangef(zNear, zFar);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDepthRangex (GLclampx zNear, GLclampx zFar)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glDepthRangex Not implemented.");
}

void OpenGLES20Context::glDisable (GLenum cap)
{
	switch (cap) {
		case GL_LIGHTING:
			openGLESState.setLighting(false);
			break;
		case GL_LIGHT0:
		case GL_LIGHT1:
		case GL_LIGHT2:
		case GL_LIGHT3:
		case GL_LIGHT4:
		case GL_LIGHT5:
		case GL_LIGHT6:
		case GL_LIGHT7:
			openGLESState.setLight(cap - GL_LIGHT0, false);
			break;
		case GL_TEXTURE_2D:
			openGLESState.setTexture(false);
			break;
		case GL_CULL_FACE:
		case GL_BLEND:
		case GL_DITHER:
		case GL_STENCIL_TEST:
		case GL_DEPTH_TEST:
		case GL_SCISSOR_TEST:
		case GL_POLYGON_OFFSET_FILL:
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
		case GL_SAMPLE_COVERAGE:
			::glDisable(cap);
			break;
		case GL_NORMALIZE:
			openGLESState.setNormalize(false);
			break;
		case GL_RESCALE_NORMAL:
			openGLESState.setRescaleNormal(false);
			break;
		case GL_FOG:
			openGLESState.setFog(false);
			break;
		case GL_ALPHA_TEST:
			openGLESState.setAlphaTest(false);
			break;
		case GL_CLIP_PLANE0:
		case GL_CLIP_PLANE1:
		case GL_CLIP_PLANE2:
		case GL_CLIP_PLANE3:
		case GL_CLIP_PLANE4:
		case GL_CLIP_PLANE5:
			openGLESState.setClipPlane(cap - GL_CLIP_PLANE0, false);
			break;
		default:
			OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown cap ") + cap);
			break;
	}
}

void OpenGLES20Context::glDisableClientState (GLenum array)
{
	switch (array) {
		case GL_VERTEX_ARRAY:
			openGLESState.setPosition(false);
			break;
		case GL_COLOR_ARRAY:
			openGLESState.setColor(false);
			break;
		case GL_NORMAL_ARRAY:
			openGLESState.setNormal(false);
			break;
		case GL_TEXTURE_COORD_ARRAY:
			openGLESState.setTexCoord(false);
			break;
		default:
			OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown argument ") + array);
			break;
	}
}

void OpenGLES20Context::prepareToDraw()
{
	Matrix4x4<GLfloat> *modelViewMatrix = matrixStack.getModelViewMatrix();
	openGLESState.setModelViewMatrix(*modelViewMatrix);
	Matrix4x4<GLfloat> *projectionMatrix = matrixStack.getProjectionMatrix();
	
	Matrix4x4<GLfloat> mvp;
	OpenGLESMath::multiply(&mvp, modelViewMatrix, projectionMatrix);
	openGLESState.setModelViewProjectionMatrix(mvp);
	
	if (openGLESState.isNormal()) {
		// If only uniform scaling used (TODO: detect somehow)
		Matrix3x3<GLfloat> modelViewMatrix3x3;
		OpenGLESMath::copyMatrix4x4UpperLeftToMatrix3x3(&modelViewMatrix3x3, modelViewMatrix);
		OpenGLESMath::adjoint(&modelViewMatrix3x3, &modelViewMatrix3x3);
		OpenGLESMath::transpose(&modelViewMatrix3x3);
		openGLESState.setTransposeAdjointModelViewMatrix(modelViewMatrix3x3);
		
		if (openGLESState.isRescaleNormal()) {
			openGLESState.setRescaleNormalFactor(1.0f/sqrtf(modelViewMatrix3x3.m[0]*modelViewMatrix3x3.m[0] + modelViewMatrix3x3.m[3]*modelViewMatrix3x3.m[3] + modelViewMatrix3x3.m[6]*modelViewMatrix3x3.m[6]));
		}
		
		// else do it slow but works always
		/*Matrix4x4<GLfloat> transposeInverseModelViewMatrix;
		 OpenGLESMath::inverse(&transposeInverseModelViewMatrix, modelViewMatrix);
		 OpenGLESMath::transpose(&transposeInverseModelViewMatrix);
		 Matrix3x3<GLfloat> modelViewMatrix3x3;
		 OpenGLESMath::copyMatrix4x4UpperLeftToMatrix3x3(&modelViewMatrix3x3, &transposeInverseModelViewMatrix);
		 openGLESState.setTransposeAdjointModelViewMatrix(modelViewMatrix3x3);
		 
		 if (openGLESState.isRescaleNormal()) {
		 openGLESState.setRescaleNormalFactor(1.0f/sqrtf(transposeInverseModelViewMatrix.m[0]*transposeInverseModelViewMatrix.m[0] + transposeInverseModelViewMatrix.m[4]*transposeInverseModelViewMatrix.m[4] + transposeInverseModelViewMatrix.m[8]*transposeInverseModelViewMatrix.m[8]));
		 }*/
	}
	
	for (int i = 0; i < implementation->maxTextureImageUnits; i++) {
		if (openGLESState.isTexCoord(i)) {
			Matrix4x4<GLfloat> *textureMatrix = matrixStack.getTextureMatrix(i);
			openGLESState.setTextureMatrix(i, *textureMatrix);
		}
	}
	
	
	openGLESState.setCurrentProgram();
}

void OpenGLES20Context::glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	if (shaderProgramId == 0) {
		prepareToDraw();
	}
	::glDrawArrays(mode, first, count);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
	if (shaderProgramId == 0) {
		prepareToDraw();
	}
	::glDrawElements(mode, count, type, indices);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glEnable (GLenum cap)
{
	switch (cap) {
		case GL_LIGHTING:
			openGLESState.setLighting(true);
			break;
		case GL_LIGHT0:
		case GL_LIGHT1:
		case GL_LIGHT2:
		case GL_LIGHT3:
		case GL_LIGHT4:
		case GL_LIGHT5:
		case GL_LIGHT6:
		case GL_LIGHT7:
		{
			openGLESState.setLight(cap - GL_LIGHT0, true);
		}
			break;
		case GL_TEXTURE_2D:
			openGLESState.setTexture(true);
			break;
		case GL_CULL_FACE:
		case GL_BLEND:
		case GL_DITHER:
		case GL_STENCIL_TEST:
		case GL_DEPTH_TEST:
		case GL_SCISSOR_TEST:
		case GL_POLYGON_OFFSET_FILL:
		case GL_SAMPLE_ALPHA_TO_COVERAGE:
		case GL_SAMPLE_COVERAGE:
			::glEnable(cap);
			break;
		case GL_NORMALIZE:
			openGLESState.setNormalize(true);
			break;
		case GL_FOG:
			openGLESState.setFog(true);
			break;
		case GL_RESCALE_NORMAL:
			openGLESState.setRescaleNormal(true);
			break;
		case GL_ALPHA_TEST:
			openGLESState.setAlphaTest(true);
			break;
		case GL_CLIP_PLANE0:
		case GL_CLIP_PLANE1:
		case GL_CLIP_PLANE2:
		case GL_CLIP_PLANE3:
		case GL_CLIP_PLANE4:
		case GL_CLIP_PLANE5:
			openGLESState.setClipPlane(cap - GL_CLIP_PLANE0, true);
			break;
		default:
			OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown cap ") + cap);
			break;
	}
}

void OpenGLES20Context::glEnableClientState (GLenum array)
{
	switch (array) {
		case GL_VERTEX_ARRAY:
			openGLESState.setPosition(true);
			break;
		case GL_COLOR_ARRAY:
			openGLESState.setColor(true);
			break;
		case GL_NORMAL_ARRAY:
			openGLESState.setNormal(true);
			break;
		case GL_TEXTURE_COORD_ARRAY:
			openGLESState.setTexCoord(true);
			break;
		default:
			OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown argument ") + array);
			break;
	}
}

void OpenGLES20Context::glFinish (void)
{
	::glFinish();
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glFlush (void)
{
	::glFlush();
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glFogf (GLenum pname, GLfloat param)
{
	switch (pname)
	{
		case GL_FOG_MODE:
		{
			GLint p = (GLint)param;
			if (p == GL_LINEAR || p == GL_EXP || p == GL_EXP2) {
				openGLESState.setFogMode(p);
			} else {
				OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown fog mode ") + param);
			}
			break;
		}	
		case GL_FOG_DENSITY:
			openGLESState.setFogDensity(param);
			break;
		case GL_FOG_START:
			openGLESState.setFogStart(param);
			break;
		case GL_FOG_END:
			openGLESState.setFogEnd(param);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown fog parameter ") + pname);
			break;
	}
}

void OpenGLES20Context::glFogfv (GLenum pname, const GLfloat *params)
{
	switch (pname)
	{
		case GL_FOG_COLOR:
			openGLESState.setFogColor(params);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown fog parameter ") + pname);
			break;
	}
}

void OpenGLES20Context::glFogx (GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glFogx Not implemented.");
}

void OpenGLES20Context::glFogxv (GLenum pname, const GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glFogxv Not implemented.");
}

void OpenGLES20Context::glFrontFace (GLenum mode)
{
	::glFrontFace(mode);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	matrixStack.frustum(left, right, bottom, top, zNear, zFar);
}

void OpenGLES20Context::glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glFrustumx Not implemented.");
}

void OpenGLES20Context::glGenTextures (GLsizei n, GLuint *textures)
{
	::glGenTextures(n, textures);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

GLenum OpenGLES20Context::glGetError (void)
{
	return ::glGetError();
}

void OpenGLES20Context::glGetIntegerv (GLenum pname, GLint *params)
{
	if (pname == GL_MAX_MODELVIEW_STACK_DEPTH) {
		*params = 32;
	} else {
		::glGetIntegerv(pname, params);
		OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	}
}

const GLubyte *OpenGLES20Context::glGetString (GLenum name)
{
	return ::glGetString(name);
}

void OpenGLES20Context::glHint (GLenum target, GLenum mode)
{
	switch (target) {
		case GL_FOG_HINT:
			openGLESState.setFogHint(mode);
			break;
		case GL_LIGHTING_HINT:
			openGLESState.setLightingHint(mode);
			break;
		default:
			::glHint(target, mode);
			OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
			break;
	}
}

void OpenGLES20Context::glLightModelf (GLenum pname, GLfloat param)
{
	switch (pname)
	{
		case GL_LIGHT_MODEL_TWO_SIDE:
			openGLESState.setLightModelTwoSide(param != 0);
			break;
		case GL_LIGHT_MODEL_LOCAL_VIEWER:
			openGLESState.setLightModelLocalViewer(param != 0);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown light model") + pname);
			break;
	}
}

void OpenGLES20Context::glLightModelfv (GLenum pname, const GLfloat *params)
{
	switch (pname)
	{
		case GL_LIGHT_MODEL_AMBIENT:
			openGLESState.setGlobalAmbientColor(params);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown light model" + pname));
			break;
	}
}

void OpenGLES20Context::glLightModelx (GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLightModelx Not implemented.");
}

void OpenGLES20Context::glLightModelxv (GLenum pname, const GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLightModelxv Not implemented.");
}

void OpenGLES20Context::glLightf (GLenum l, GLenum pname, GLfloat param)
{
	int lightIndex = l - GL_LIGHT0;
	switch (pname)
	{
		case GL_SPOT_EXPONENT:
			openGLESState.setLightSpotExponent(lightIndex, param);
			if (OpenGLESConfig::DEBUG) {
				if (param > 128) {
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: Spot exponent cannot be over 128");
				}
			}
			break;
		case GL_SPOT_CUTOFF:
			openGLESState.setLightSpotCutoffAngleCos(lightIndex, cosf(param*PI/180.0f));
			if (OpenGLESConfig::DEBUG) {
				if (param > 90 && param != 180) {
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: Spot cutoff cannot be over 90 and different from 180.");
				}
			}
			break;
		case GL_CONSTANT_ATTENUATION:
			openGLESState.setLightConstantAttenuation(lightIndex, param);
			break;
		case GL_LINEAR_ATTENUATION:
			openGLESState.setLightLinearAttenuation(lightIndex, param);
			break;
		case GL_QUADRATIC_ATTENUATION:
			openGLESState.setLightQuadraticAttenuation(lightIndex, param);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown light parameter ") + pname);
			break;
	}
}

void OpenGLES20Context::glLightfv (GLenum l, GLenum pname, const GLfloat *params)
{
	int lightIndex = l - GL_LIGHT0;
	switch (pname)
	{
		case GL_AMBIENT:
			openGLESState.setLightAmbient(lightIndex, params);
			break;
		case GL_DIFFUSE:
			openGLESState.setLightDiffuse(lightIndex, params);
			break;
		case GL_SPECULAR:
			openGLESState.setLightSpecular(lightIndex, params);
			break;
		case GL_POSITION:
		{
			Matrix4x4<GLfloat> *modelViewMatrix = matrixStack.getModelViewMatrix();
			Vector4<GLfloat> vec(params);
			OpenGLESMath::multiply(&vec, modelViewMatrix, &vec);
			openGLESState.setLightPosition(lightIndex, vec);
			
			if (OpenGLESConfig::DEBUG) {
				if (vec[3] == 0.0f && !OpenGLESMath::isUnitVector(&vec)) {
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: Directional light's position is not unit vector.");
				}
			}
			
		}
			break;
		case GL_SPOT_DIRECTION:
		{
			Matrix4x4<GLfloat> *modelViewMatrix = matrixStack.getModelViewMatrix();
			Matrix3x3<GLfloat> modelViewMatrix3x3;
			OpenGLESMath::copyMatrix4x4UpperLeftToMatrix3x3(&modelViewMatrix3x3, modelViewMatrix);
			Vector3<GLfloat> vec(params);
			OpenGLESMath::multiply(&vec, &modelViewMatrix3x3, &vec);
			openGLESState.setLightSpotDirection(lightIndex, vec);
		}
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown light parameter ") + pname);
			break;
	}
}

void OpenGLES20Context::glLightx (GLenum light, GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLightx Not implemented.");
}

void OpenGLES20Context::glLightxv (GLenum light, GLenum pname, const GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLightxv Not implemented.");
}

void OpenGLES20Context::glLineWidth (GLfloat width)
{
	::glLineWidth(width);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glLineWidthx (GLfixed width)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLineWidthx Not implemented.");
}

void OpenGLES20Context::glLoadIdentity (void)
{
	matrixStack.loadIdentity();
}

void OpenGLES20Context::glLoadMatrixf (const GLfloat *m)
{
	matrixStack.loadMatrix(m);
}

void OpenGLES20Context::glLoadMatrixx (const GLfixed *m)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLoadMatrixx Not implemented.");
}

void OpenGLES20Context::glLogicOp (GLenum opcode)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glLogicOp Not implemented.");
}

void OpenGLES20Context::glMaterialf (GLenum face, GLenum pname, GLfloat param)
{
	switch (pname)
	{
		case GL_SHININESS:
			openGLESState.setMaterialShininess(param);
			if (OpenGLESConfig::DEBUG) {
				if (param > 128) {
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: Shininess cannot be over 128");
				}
			}
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown material parameter ") + pname);
			break;
	}
}

void OpenGLES20Context::glMaterialfv (GLenum face, GLenum pname, const GLfloat *params)
{
	switch (pname)
	{
		case GL_AMBIENT:
			openGLESState.setMaterialAmbient(params);
			break;
		case GL_DIFFUSE:
			openGLESState.setMaterialDiffuse(params);
			break;
		case GL_SPECULAR:
			openGLESState.setMaterialSpecular(params);
			break;
		case GL_EMISSION:
			openGLESState.setMaterialEmission(params);
			break;
		case GL_AMBIENT_AND_DIFFUSE:
			openGLESState.setMaterialAmbient(params);
			openGLESState.setMaterialDiffuse(params);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown material parameter ") + pname);
			break;
	}
	
}

void OpenGLES20Context::glMaterialx (GLenum face, GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glMaterialx Not implemented.");
}

void OpenGLES20Context::glMaterialxv (GLenum face, GLenum pname, const GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glMaterialxv Not implemented.");
}

void OpenGLES20Context::glMatrixMode (GLenum mode)
{
	matrixStack.setMatrixMode(mode);
}

void OpenGLES20Context::glMultMatrixf (const GLfloat *m)
{
	matrixStack.multiply(m);
}

void OpenGLES20Context::glMultMatrixx (const GLfixed *m)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glMultMatrixx Not implemented.");
}

void OpenGLES20Context::glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glMultiTexCoord4f Not implemented.");
}

void OpenGLES20Context::glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glMultiTexCoord4x Not implemented.");
}

void OpenGLES20Context::glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glNormal3f Not implemented.");
}

void OpenGLES20Context::glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glNormal3x Not implemented.");
}

void OpenGLES20Context::glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	openGLESState.setNormal(3, type, stride, pointer);
}

void OpenGLES20Context::glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	matrixStack.ortho(left, right, bottom, top, zNear, zFar);
}

void OpenGLES20Context::glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glOrthox Not implemented.");
}

void OpenGLES20Context::glPixelStorei (GLenum pname, GLint param)
{
	::glPixelStorei(pname, param);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glPointSize (GLfloat size)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPointSize Not implemented.");
}

void OpenGLES20Context::glPointSizex (GLfixed size)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPointSizex Not implemented.");
}

void OpenGLES20Context::glPolygonOffset (GLfloat factor, GLfloat units)
{
	::glPolygonOffset(factor, units);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glPolygonOffsetx (GLfixed factor, GLfixed units)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPolygonOffsetx Not implemented.");
}

void OpenGLES20Context::glPopMatrix (void)
{
	matrixStack.popMatrix();
}

void OpenGLES20Context::glPushMatrix (void)
{
	matrixStack.pushMatrix();
}

void OpenGLES20Context::glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
	::glReadPixels(x, y, width, height, format, type, pixels);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	matrixStack.rotate(-angle, x, y, z);
}

void OpenGLES20Context::glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glRotatex Not implemented.");
}

void OpenGLES20Context::glSampleCoverage (GLclampf value, GLboolean invert)
{
	::glSampleCoverage(value, invert);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glSampleCoveragex (GLclampx value, GLboolean invert)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glSampleCoveragex Not implemented.");
}

void OpenGLES20Context::glScalef (GLfloat x, GLfloat y, GLfloat z)
{
	matrixStack.scale(x, y, z);
}

void OpenGLES20Context::glScalex (GLfixed x, GLfixed y, GLfixed z)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glScalex Not implemented.");
}

void OpenGLES20Context::glScissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
	::glScissor(x, y, width, height);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glShadeModel (GLenum mode)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glShadeModel Not implemented.");
}

void OpenGLES20Context::glStencilFunc (GLenum func, GLint ref, GLuint mask)
{
	::glStencilFunc(func, ref, mask);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glStencilMask (GLuint mask)
{
	::glStencilMask(mask);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
	::glStencilOp(fail, zfail, zpass);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	openGLESState.setTexCoord(size, type, stride, pointer);
}

void OpenGLES20Context::glTexEnvf (GLenum target, GLenum pname, GLfloat param)
{
	switch (pname) {
		case GL_BLUR_AMOUNT:
			openGLESState.setTextureEnvBlurAmount(param);
			break;
		default:
			glTexEnvi(target, pname, (GLint)(param));
			break;
	}
}

void OpenGLES20Context::glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params)
{
	switch (pname) {
		case GL_TEXTURE_ENV_COLOR:
			openGLESState.setTextureEnvColor(params);
			break;
		default:
			glTexEnvi(target, pname, (GLint)(params[0]));
			break;
	}
}

void OpenGLES20Context::glTexEnvx (GLenum target, GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glTexEnvx Not implemented.");
}

void OpenGLES20Context::glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glTexEnvxv Not implemented.");
}

void OpenGLES20Context::glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	openGLESState.setBoundTextureFormat(internalformat);
	openGLESState.setTextureFormat();
	::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glTexParameterf (GLenum target, GLenum pname, GLfloat param)
{
	::glTexParameterf(target, pname, param);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glTexParameterx (GLenum target, GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glTexParameterx Not implemented.");
}

void OpenGLES20Context::glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
	::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glTranslatef (GLfloat x, GLfloat y, GLfloat z)
{
	matrixStack.translate(x, y, z);
}

void OpenGLES20Context::glTranslatex (GLfixed x, GLfixed y, GLfixed z)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glTranslatex Not implemented.");
}

void OpenGLES20Context::glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	openGLESState.setPosition(size, type, stride, pointer);
}

void OpenGLES20Context::glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
	::glViewport(x, y, width, height);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}



// OpenGL ES 1.1 functions
void OpenGLES20Context::glBindBuffer (GLenum target, GLuint buffer)
{
	::glBindBuffer(target, buffer);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
	::glBufferData(target, size, data, usage);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	::glBufferSubData(target, offset, size, data);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glClipPlanef(GLenum plane, const GLfloat *equation)
{
	Matrix4x4<GLfloat> tranposeInverseModelViewMatrix;
	OpenGLESMath::inverse(&tranposeInverseModelViewMatrix, matrixStack.getModelViewMatrix()); // TODO: calculated also before drawing, optimize?
	OpenGLESMath::transpose(&tranposeInverseModelViewMatrix);
	Vector4<GLfloat> clipPlane(equation);
	OpenGLESMath::multiply(&clipPlane, &tranposeInverseModelViewMatrix, &clipPlane);
	
	openGLESState.setClipPlane(plane - GL_CLIP_PLANE0, clipPlane);
}

void OpenGLES20Context::glClipPlanex (GLenum plane, const GLfixed *equation)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glClipPlanex Not implemented.");
}

void OpenGLES20Context::glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glColor4ub Not implemented.");
}

void OpenGLES20Context::glDeleteBuffers (GLsizei n, const GLuint *buffers)
{
	::glDeleteBuffers(n, buffers);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGenBuffers (GLsizei n, GLuint *buffers)
{
	::glGenBuffers(n, buffers);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetClipPlanef(GLenum pname, GLfloat eqn[4])
{
	openGLESState.getClipPlane(pname - GL_CLIP_PLANE0, eqn);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetFloatv(GLenum pname, GLfloat *params)
{
	switch (pname) {
		case GL_MODELVIEW_MATRIX:
			for (int i = 0; i < 16; i++) {
				params[i] = matrixStack.getModelViewMatrix()->m[i];
			}
			break;
		default:
			::glGetFloatv(pname, params);
			break;
	}
	
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetLightfv (GLenum light, GLenum pname, GLfloat *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetLightfv Not implemented.");
}

void OpenGLES20Context::glGetLightxv (GLenum light, GLenum pname, GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetLightxv Not implemented.");
}

void OpenGLES20Context::glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetMaterialfv Not implemented.");
}

void OpenGLES20Context::glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetMaterialxv Not implemented.");
}

void OpenGLES20Context::glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetTexEnvfv Not implemented.");
}

void OpenGLES20Context::glGetTexEnviv (GLenum env, GLenum pname, GLint *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetTexEnviv Not implemented.");
}

void OpenGLES20Context::glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetTexEnvxv Not implemented.");
}

void OpenGLES20Context::glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	::glGetTexParameterfv(target, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetTexParameteriv (GLenum target, GLenum pname, GLint *params)
{
	::glGetTexParameteriv(target, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetTexParameterxv Not implemented.");
}

void OpenGLES20Context::glGetBooleanv (GLenum pname, GLboolean *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetBooleanv Not implemented.");
}

void OpenGLES20Context::glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetBufferParameteriv Not implemented.");
}

void OpenGLES20Context::glGetFixedv (GLenum pname, GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetFixedv Not implemented.");
}

void OpenGLES20Context::glGetPointerv (GLenum pname, void **params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glGetPointerv Not implemented.");
}

GLboolean OpenGLES20Context::glIsBuffer (GLuint buffer)
{
	return ::glIsBuffer(buffer);
}

GLboolean OpenGLES20Context::glIsEnabled (GLenum cap)
{
	return ::glIsEnabled(cap);
}

GLboolean OpenGLES20Context::glIsTexture (GLuint texture)
{
	return ::glIsTexture(texture);
}

void OpenGLES20Context::glPointParameterf (GLenum pname, GLfloat param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPointParameterf Not implemented.");
}

void OpenGLES20Context::glPointParameterfv (GLenum pname, const GLfloat *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPointParameterfv Not implemented.");
}

void OpenGLES20Context::glPointParameterx (GLenum pname, GLfixed param)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPointParameterx Not implemented.");
}

void OpenGLES20Context::glPointParameterxv (GLenum pname, const GLfixed *params)
{
	OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: glPointParameterxv Not implemented.");
}

void OpenGLES20Context::glTexEnvi (GLenum target, GLenum pname, GLint param)
{
	switch (pname) {
		case GL_TEXTURE_ENV_MODE:
			switch (param) {
				case GL_MODULATE:
				case GL_ADD:
				case GL_DECAL:
				case GL_BLEND:
				case GL_REPLACE:
				case GL_COMBINE:
				case GL_BLUR:
					openGLESState.setTextureEnvMode(param);
					break;
				default:
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown GL_TEXTURE_ENV_MODE parameter ") + param);
					break;
			}
			break;
		case GL_COMBINE_RGB:
			switch (param) {
				case GL_REPLACE:
				case GL_MODULATE:
				case GL_ADD:
				case GL_ADD_SIGNED:
				case GL_INTERPOLATE:
				case GL_SUBTRACT:
				case GL_DOT3_RGB:
				case GL_DOT3_RGBA:
					openGLESState.setTextureEnvCombineRGB(param);
					break;
				default:
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown GL_COMBINE_RGB parameter ") + param);
					break;
			}
			break;
		case GL_COMBINE_ALPHA:
			switch (param) {
				case GL_REPLACE:
				case GL_MODULATE:
				case GL_ADD:
				case GL_ADD_SIGNED:
				case GL_INTERPOLATE:
				case GL_SUBTRACT:
					openGLESState.setTextureEnvCombineAlpha(param);
					break;
				default:
					OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown GL_COMBINE_ALPHA parameter ") + param);
					break;
			}
			break;
		case GL_SRC0_RGB:
		case GL_SRC1_RGB:
		case GL_SRC2_RGB:
			if (GL_TEXTURE0 <= param && param <= GL_TEXTURE31) {
				openGLESState.setTextureEnvSrcRGB(pname - GL_SRC0_RGB, param - GL_TEXTURE0);
			} else if (param == GL_TEXTURE) {
				openGLESState.setTextureEnvSrcRGB(pname - GL_SRC0_RGB, openGLESState.getActiveTexture());
			} else {
				openGLESState.setTextureEnvSrcRGB(pname - GL_SRC0_RGB, param);
			}
			break;
		case GL_SRC0_ALPHA:
		case GL_SRC1_ALPHA:
		case GL_SRC2_ALPHA:
			if (GL_TEXTURE0 <= param && param <= GL_TEXTURE31) {
				openGLESState.setTextureEnvSrcAlpha(pname - GL_SRC0_ALPHA, param - GL_TEXTURE0);
			} else if (param == GL_TEXTURE) {
				openGLESState.setTextureEnvSrcAlpha(pname - GL_SRC0_ALPHA, openGLESState.getActiveTexture());
			} else {
				openGLESState.setTextureEnvSrcAlpha(pname - GL_SRC0_ALPHA, param);
			}
			break;
		case GL_OPERAND0_RGB:
		case GL_OPERAND1_RGB:
		case GL_OPERAND2_RGB:
			openGLESState.setTextureEnvOperandRGB(pname - GL_OPERAND0_RGB, param);
			break;
		case GL_OPERAND0_ALPHA:
		case GL_OPERAND1_ALPHA:
		case GL_OPERAND2_ALPHA:
			openGLESState.setTextureEnvOperandAlpha(pname - GL_OPERAND0_ALPHA, param);
			break;
		case GL_RGB_SCALE:
			openGLESState.setTextureEnvRGBScale(param);
			break;
		case GL_ALPHA_SCALE:
			openGLESState.setTextureEnvAlphaScale(param);
			break;
		default:
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown parameter ") + pname);
			break;
	}
}

void OpenGLES20Context::glTexEnviv (GLenum target, GLenum pname, const GLint *params)
{
	glTexEnvfv(target, pname, (GLfloat *)params);
}

void OpenGLES20Context::glTexParameteri (GLenum target, GLenum pname, GLint param)
{
	::glTexParameteri(target, pname, param);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glTexParameteriv (GLenum target, GLenum pname, const GLint *params)
{
	::glTexParameteriv(target, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexsOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexiOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexxOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glDrawTexsvOES (const GLshort *coords)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexsvOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glDrawTexivOES (const GLint *coords)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexivOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glDrawTexxvOES (const GLfixed *coords) 
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexxvOES No effect in OpenGL ES 2.x");
}


void OpenGLES20Context::glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexfOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glDrawTexfvOES (const GLfloat *coords)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glDrawTexfvOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glCurrentPaletteMatrixOES (GLuint matrixpaletteindex)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glCurrentPaletteMatrixOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glLoadPaletteFromModelViewMatrixOES (void)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glLoadPaletteFromModelViewMatrixOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glMatrixIndexPointerOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glWeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glWeightPointerOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glPointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glPointSizePointerOES No effect in OpenGL ES 2.x");
}

void OpenGLES20Context::glAttachShader (GLuint program, GLuint shader)
{
	::glAttachShader(program, shader);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBindAttribLocation (GLuint program, GLuint index, const GLchar* name)
{
	::glBindAttribLocation(program, index, name);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBindFramebuffer (GLenum target, GLuint framebuffer)
{
	::glBindFramebuffer(target, framebuffer);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBindRenderbuffer (GLenum target, GLuint renderbuffer)
{
	::glBindRenderbuffer(target, renderbuffer);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	::glBlendColor(red, green, blue, alpha);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBlendEquation ( GLenum mode )
{
	::glBlendEquation(mode);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)
{
	::glBlendEquationSeparate(modeRGB, modeAlpha);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	::glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

GLenum OpenGLES20Context::glCheckFramebufferStatus (GLenum target)
{
	return ::glCheckFramebufferStatus(target);
}

void OpenGLES20Context::glCompileShader (GLuint shader)
{
	::glCompileShader(shader);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

GLuint OpenGLES20Context::glCreateProgram (void)
{
	return ::glCreateProgram();
}

GLuint OpenGLES20Context::glCreateShader (GLenum type)
{
	return ::glCreateShader(type);
}

void OpenGLES20Context::glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers)
{
	::glDeleteFramebuffers(n, framebuffers);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDeleteProgram (GLuint program)
{
	::glDeleteProgram(program);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers)
{
	::glDeleteRenderbuffers(n, renderbuffers);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDeleteShader (GLuint shader)
{
	::glDeleteShader(shader);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDetachShader (GLuint program, GLuint shader)
{
	::glDetachShader(program, shader);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDisableVertexAttribArray (GLuint index)
{
	::glDisableVertexAttribArray(index);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments) {
	::glDiscardFramebufferEXT(target, numAttachments, attachments);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);	
}

void OpenGLES20Context::glEnableVertexAttribArray (GLuint index)
{
	::glEnableVertexAttribArray(index);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	::glFramebufferTexture2D(target, attachment, textarget, texture, level);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGenerateMipmap (GLenum target)
{
	::glGenerateMipmap(target);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGenFramebuffers (GLsizei n, GLuint* framebuffers)
{
	::glGenFramebuffers(n, framebuffers);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGenRenderbuffers (GLsizei n, GLuint* renderbuffers)
{
	::glGenRenderbuffers(n, renderbuffers);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	::glGetActiveAttrib(program, index, bufsize, length, size, type, name);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
	::glGetActiveUniform(program, index, bufsize, length, size, type, name);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
	::glGetAttachedShaders(program, maxcount, count, shaders);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

int OpenGLES20Context::glGetAttribLocation (GLuint program, const GLchar* name)
{
	return ::glGetAttribLocation(program, name);
}

void OpenGLES20Context::glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
	::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetProgramiv (GLuint program, GLenum pname, GLint* params)
{
	::glGetProgramiv(program, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
	::glGetProgramInfoLog(program, bufsize, length, infolog);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params)
{
	::glGetRenderbufferParameteriv(target, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetShaderiv (GLuint shader, GLenum pname, GLint* params)
{
	::glGetShaderiv(shader, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
	::glGetShaderInfoLog(shader, bufsize, length, infolog);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
	::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{
	::glGetShaderSource(shader, bufsize, length, source);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetUniformfv (GLuint program, GLint location, GLfloat* params)
{
	::glGetUniformfv(program, location, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetUniformiv (GLuint program, GLint location, GLint* params)
{
	::glGetUniformiv(program, location, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

int OpenGLES20Context::glGetUniformLocation (GLuint program, const GLchar* name)
{
	return ::glGetUniformLocation(program, name);
}

void OpenGLES20Context::glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params)
{
	::glGetVertexAttribfv(index, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params)
{
	::glGetVertexAttribiv(index, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer)
{
	::glGetVertexAttribPointerv(index, pname, pointer);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

GLboolean OpenGLES20Context::glIsFramebuffer (GLuint framebuffer)
{
	return ::glIsFramebuffer(framebuffer);
}

GLboolean OpenGLES20Context::glIsProgram (GLuint program)
{
	return ::glIsProgram(program);
}

GLboolean OpenGLES20Context::glIsRenderbuffer (GLuint renderbuffer)
{
	return ::glIsRenderbuffer(renderbuffer);
}

GLboolean OpenGLES20Context::glIsShader (GLuint shader)
{
	return ::glIsShader(shader);
}

void OpenGLES20Context::glLinkProgram (GLuint program)
{
	::glLinkProgram(program);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glReleaseShaderCompiler (void)
{
	::glReleaseShaderCompiler();
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	::glRenderbufferStorage(target, internalformat, width, height);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
	::glRenderbufferStorageMultisampleAPPLE(target, samples, internalformat, width, height);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glResolveMultisampleFramebufferAPPLE(void) {
	::glResolveMultisampleFramebufferAPPLE();
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);	
}

void OpenGLES20Context::glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
{
	::glShaderBinary(n,shaders,binaryformat,binary,length);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glShaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
	::glShaderSource(shader, count, string, length);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask)
{
	::glStencilFuncSeparate(face, func, ref, mask);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glStencilMaskSeparate (GLenum face, GLuint mask)
{
	::glStencilMaskSeparate(face, mask);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
	::glStencilOpSeparate(face,fail,zfail,zpass);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params)
{
	::glTexParameterfv(target, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform1f (GLint location, GLfloat x)
{
	::glUniform1f(location, x);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform1fv (GLint location, GLsizei count, const GLfloat* v)
{
	::glUniform1fv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform1i (GLint location, GLint x)
{
	::glUniform1i(location, x);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform1iv (GLint location, GLsizei count, const GLint* v)
{
	::glUniform1iv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform2f (GLint location, GLfloat x, GLfloat y)
{
	::glUniform2f(location, x, y);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform2fv (GLint location, GLsizei count, const GLfloat* v)
{
	::glUniform2fv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform2i (GLint location, GLint x, GLint y)
{
	::glUniform2i(location, x, y);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform2iv (GLint location, GLsizei count, const GLint* v)
{
	::glUniform2iv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	::glUniform3f(location, x, y, z);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform3fv (GLint location, GLsizei count, const GLfloat* v)
{
	::glUniform3fv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform3i (GLint location, GLint x, GLint y, GLint z)
{
	::glUniform3i(location, x, y, z);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform3iv (GLint location, GLsizei count, const GLint* v)
{
	::glUniform3iv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	::glUniform4f(location, x, y, z, w);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform4fv (GLint location, GLsizei count, const GLfloat* v)
{
	::glUniform4fv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w)
{
	::glUniform4i(location, x, y, z, w);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniform4iv (GLint location, GLsizei count, const GLint* v)
{
	::glUniform4iv(location, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	::glUniformMatrix2fv(location, count, transpose, value);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	::glUniformMatrix3fv(location, count, transpose, value);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	::glUniformMatrix4fv(location, count, transpose, value);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glUseProgram (GLuint program)
{
	::glUseProgram(program);
	shaderProgramId = program;
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glValidateProgram (GLuint program)
{
	::glValidateProgram(program);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib1f (GLuint indx, GLfloat x)
{
	::glVertexAttrib1f(indx, x);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib1fv (GLuint indx, const GLfloat* values)
{
	::glVertexAttrib1fv(indx, values);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y)
{
	::glVertexAttrib2f(indx, x, y);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib2fv (GLuint indx, const GLfloat* values)
{
	::glVertexAttrib2fv(indx, values);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
	::glVertexAttrib3f(indx, x, y, z);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib3fv (GLuint indx, const GLfloat* values)
{
	::glVertexAttrib3fv(indx, values);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	::glVertexAttrib4f(indx, x, y, z, w);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttrib4fv (GLuint indx, const GLfloat* values)
{
	::glVertexAttrib4fv(indx, values);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void OpenGLES20Context::glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
	::glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}


// OpenGL ES 2 Extensions
void OpenGLES20Context::glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params)
{
#if GL_OES_mapbuffer
	::glGetBufferPointervOES(target, pname, params);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
#else
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glGetBufferPointervOES Not supported");
#endif
}

GLvoid * OpenGLES20Context::glMapBufferOES (GLenum target, GLenum access)
{
#if GL_OES_mapbuffer
	return ::glMapBufferOES(target, access);
#else
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glMapBufferOES Not supported");
	return 0;
#endif
}

GLboolean OpenGLES20Context::glUnmapBufferOES (GLenum target)
{
#if GL_OES_mapbuffer
	return ::glUnmapBufferOES(target);
#else
	OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "WARNING: glUnmapBufferOES Not supported");
	return 0;
#endif
}

int OpenGLES20Context::getCachedShaderAmount()
{
	return openGLESState.getCachedShaderAmount();
}
