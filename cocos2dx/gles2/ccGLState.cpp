/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ccGLState.h"
#include "CCGLProgram.h"
#include "CCDirector.h"
#include "ccConfig.h"

// extern
#include "kazmath/GL/matrix.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

static GLuint	_ccCurrentProjectionMatrix = -1;
static bool		_vertexAttribPosition = false;
static bool		_vertexAttribColor = false;
static bool		_vertexAttribTexCoords = false;

#if CC_ENABLE_GL_STATE_CACHE
#define kCCMaxActiveTexture 16
static GLuint	_ccCurrentShaderProgram = -1;
static GLuint	_ccCurrentBoundTexture[kCCMaxActiveTexture] =  {-1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, };
static GLenum	_ccCurrentActiveTexture = (GL_TEXTURE0 - GL_TEXTURE0);
static GLenum	_ccBlendingSource = -1;
static GLenum	_ccBlendingDest = -1;
static int      _ccGLServerState = 0;
#endif // CC_ENABLE_GL_STATE_CACHE

//#pragma mark - GL State Cache functions

void ccGLInvalidateStateCache( void )
{
	kmGLFreeAll();

#if CC_ENABLE_GL_STATE_CACHE
	_ccCurrentShaderProgram = -1;
	for( int i=0; i < kCCMaxActiveTexture; i++ )
		_ccCurrentBoundTexture[i] = -1;
	_ccCurrentActiveTexture = (GL_TEXTURE0 - GL_TEXTURE0);
	_ccBlendingSource = -1;
	_ccBlendingDest = -1;
	_ccGLServerState = 0;
#endif
}

void ccGLDeleteProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
	if( program == _ccCurrentShaderProgram )
		_ccCurrentShaderProgram = -1;
#endif // CC_ENABLE_GL_STATE_CACHE

	glDeleteProgram( program );
}

void ccGLUseProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
	if( program != _ccCurrentShaderProgram ) {
		_ccCurrentShaderProgram = program;
		glUseProgram(program);
	}
#else
	glUseProgram(program);
#endif // CC_ENABLE_GL_STATE_CACHE
}


void ccGLBlendFunc(GLenum sfactor, GLenum dfactor)
{
#if CC_ENABLE_GL_STATE_CACHE
	if( sfactor != _ccBlendingSource || dfactor != _ccBlendingDest ) {
		_ccBlendingSource = sfactor;
		_ccBlendingDest = dfactor;
		glBlendFunc( sfactor, dfactor );
	}
#else
	glBlendFunc( sfactor, dfactor );
#endif // CC_ENABLE_GL_STATE_CACHE
}

GLenum ccGLGetActiveTexture( void )
{
#if CC_ENABLE_GL_STATE_CACHE
	return _ccCurrentActiveTexture + GL_TEXTURE0;
#else
	GLenum activeTexture;
	glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&activeTexture);
	return activeTexture;
#endif
}

void ccGLActiveTexture( GLenum textureEnum )
{
#if CC_ENABLE_GL_STATE_CACHE
	CCAssert( (textureEnum - GL_TEXTURE0) < kCCMaxActiveTexture, "cocos2d ERROR: Increase kCCMaxActiveTexture to %d!", (textureEnum-GL_TEXTURE0) );
	if( (textureEnum - GL_TEXTURE0) != _ccCurrentActiveTexture ) {
		_ccCurrentActiveTexture = (textureEnum - GL_TEXTURE0);
		glActiveTexture( textureEnum );
	}
#else
	glActiveTexture( textureEnum );
#endif
}

void ccGLBindTexture2D( GLuint textureId )
{
#if CC_ENABLE_GL_STATE_CACHE
	if( _ccCurrentBoundTexture[ _ccCurrentActiveTexture ] != textureId )
	{
		_ccCurrentBoundTexture[ _ccCurrentActiveTexture ] = textureId;
		glBindTexture(GL_TEXTURE_2D, textureId );
	}
#else
	glBindTexture(GL_TEXTURE_2D, textureId );
#endif
}


void ccGLDeleteTexture( GLuint textureId )
{
#if CC_ENABLE_GL_STATE_CACHE
	if( textureId == _ccCurrentBoundTexture[ _ccCurrentActiveTexture ] )
	   _ccCurrentBoundTexture[ _ccCurrentActiveTexture ] = -1;
#endif
	glDeleteTextures(1, &textureId );
}

void ccGLEnable( ccGLServerState flags )
{
#if CC_ENABLE_GL_STATE_CACHE

	bool enabled = false;

	/* GL_BLEND */
	if( (enabled=(flags & CC_GL_BLEND)) != (_ccGLServerState & CC_GL_BLEND) ) {
		if( enabled ) {
			glEnable( GL_BLEND );
			_ccGLServerState |= CC_GL_BLEND;
		} else {
			glDisable( GL_BLEND );
			_ccGLServerState &=  ~CC_GL_BLEND;
		}
	}

#else
	if( flags & CC_GL_BLEND )
		glEnable( GL_BLEND );
	else
		glDisable( GL_BLEND );
#endif
}

//#pragma mark - GL Vertex Attrib functions

void ccGLEnableVertexAttribs( unsigned int flags )
{
	/* Position */
	bool enablePosition = flags & kCCVertexAttribFlag_Position;

	if( enablePosition != _vertexAttribPosition ) {
		if( enablePosition )
			glEnableVertexAttribArray( kCCVertexAttrib_Position );
		else
			glDisableVertexAttribArray( kCCVertexAttrib_Position );

		_vertexAttribPosition = enablePosition;
	}

	/* Color */
	bool enableColor = (flags & kCCVertexAttribFlag_Color) != 0 ? true : false;

	if( enableColor != _vertexAttribColor ) {
		if( enableColor )
			glEnableVertexAttribArray( kCCVertexAttrib_Color );
		else
			glDisableVertexAttribArray( kCCVertexAttrib_Color );

		_vertexAttribColor = enableColor;
	}

	/* Tex Coords */
	bool enableTexCoords = (flags & kCCVertexAttribFlag_TexCoords) != 0 ? true : false;

	if( enableTexCoords != _vertexAttribTexCoords ) {
		if( enableTexCoords )
			glEnableVertexAttribArray( kCCVertexAttrib_TexCoords );
		else
			glDisableVertexAttribArray( kCCVertexAttrib_TexCoords );

		_vertexAttribTexCoords = enableTexCoords;
	}
}

//#pragma mark - GL Uniforms functions

void ccGLUniformModelViewProjectionMatrix( CCGLProgram *shaderProgram )
{
	kmMat4 matrixP;
	kmMat4 matrixMV;
	kmMat4 matrixMVP;

	kmGLGetMatrix(KM_GL_PROJECTION, &matrixP );
	kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV );

	kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);

	glUniformMatrix4fv( shaderProgram->uniforms_[kCCUniformMVPMatrix], 1, GL_FALSE, matrixMVP.mat);
}

void ccSetProjectionMatrixDirty( void )
{
	_ccCurrentProjectionMatrix = -1;
}

NS_CC_END
