/****************************************************************************
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (C) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "ccGLStateCache.h"
#include "CCGLProgram.h"
#include "CCDirector.h"
#include "ccConfig.h"
#include "CCConfiguration.h"

// extern
#include "kazmath/GL/matrix.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

namespace
{
    static GLuint      s_currentProjectionMatrix = -1;
    static bool        s_vertexAttribPosition = false;
    static bool        s_vertexAttribColor = false;
    static bool        s_vertexAttribTexCoords = false;
    
#if CC_ENABLE_GL_STATE_CACHE
    
#define kMaxActiveTexture 16
    
    static GLuint    s_currentShaderProgram = -1;
    static GLuint    s_currentBoundTexture[kMaxActiveTexture] =  {(GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, };
    static GLenum    s_blendingSource = -1;
    static GLenum    s_blendingDest = -1;
    static int       s_GLServerState = 0;
    static GLuint    s_VAO = 0;
    static GLenum    s_activeTexture = -1;

#endif // CC_ENABLE_GL_STATE_CACHE
}

// GL State Cache functions

namespace GL {

void invalidateStateCache( void )
{
    kmGLFreeAll();
    
    s_currentProjectionMatrix = -1;
    s_vertexAttribPosition = false;
    s_vertexAttribColor = false;
    s_vertexAttribTexCoords = false;
    
#if CC_ENABLE_GL_STATE_CACHE
    s_currentShaderProgram = -1;
    for( int i=0; i < kMaxActiveTexture; i++ )
    {
        s_currentBoundTexture[i] = -1;
    }

    s_blendingSource = -1;
    s_blendingDest = -1;
    s_GLServerState = 0;
    s_VAO = 0;
    
#endif // CC_ENABLE_GL_STATE_CACHE
}

void deleteProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
    if(program == s_currentShaderProgram)
    {
        s_currentShaderProgram = -1;
    }
#endif // CC_ENABLE_GL_STATE_CACHE

    glDeleteProgram( program );
}

void useProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
    if( program != s_currentShaderProgram ) {
        s_currentShaderProgram = program;
        glUseProgram(program);
    }
#else
    glUseProgram(program);
#endif // CC_ENABLE_GL_STATE_CACHE
}

static void SetBlending(GLenum sfactor, GLenum dfactor)
{
	if (sfactor == GL_ONE && dfactor == GL_ZERO)
    {
		glDisable(GL_BLEND);
	}
    else
    {
		glEnable(GL_BLEND);
		glBlendFunc(sfactor, dfactor);
	}
}

void blendFunc(GLenum sfactor, GLenum dfactor)
{
#if CC_ENABLE_GL_STATE_CACHE
    if (sfactor != s_blendingSource || dfactor != s_blendingDest)
    {
        s_blendingSource = sfactor;
        s_blendingDest = dfactor;
        SetBlending(sfactor, dfactor);
    }
#else
    SetBlending( sfactor, dfactor );
#endif // CC_ENABLE_GL_STATE_CACHE
}

void blendResetToCache(void)
{
	glBlendEquation(GL_FUNC_ADD);
#if CC_ENABLE_GL_STATE_CACHE
	SetBlending(s_blendingSource, s_blendingDest);
#else
	SetBlending(CC_BLEND_SRC, CC_BLEND_DST);
#endif // CC_ENABLE_GL_STATE_CACHE
}

void bindTexture2D(GLuint textureId)
{
    GL::bindTexture2DN(0, textureId);
}

void bindTexture2DN(GLuint textureUnit, GLuint textureId)
{
#if CC_ENABLE_GL_STATE_CACHE
    CCASSERT(textureUnit < kMaxActiveTexture, "textureUnit is too big");
    if (s_currentBoundTexture[textureUnit] != textureId)
    {
        s_currentBoundTexture[textureUnit] = textureId;
        activeTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
#else
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
#endif
}


void deleteTexture(GLuint textureId)
{
    deleteTextureN(0, textureId);
}

void deleteTextureN(GLuint textureUnit, GLuint textureId)
{
#if CC_ENABLE_GL_STATE_CACHE
	if (s_currentBoundTexture[textureUnit] == textureId)
    {
		s_currentBoundTexture[textureUnit] = -1;
    }
#endif // CC_ENABLE_GL_STATE_CACHE
    
	glDeleteTextures(1, &textureId);
}

void activeTexture(GLenum texture)
{
#if CC_ENABLE_GL_STATE_CACHE
    if(s_activeTexture != texture) {
        s_activeTexture = texture;
        glActiveTexture(s_activeTexture);
    }
#else
    glActiveTexture(texture);
#endif
}

void bindVAO(GLuint vaoId)
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
    
#if CC_ENABLE_GL_STATE_CACHE
        if (s_VAO != vaoId)
        {
            s_VAO = vaoId;
            glBindVertexArray(vaoId);
        }
#else
        glBindVertexArray(vaoId);
#endif // CC_ENABLE_GL_STATE_CACHE
    
    }
}

//#pragma mark - GL Vertex Attrib functions

void enableVertexAttribs( unsigned int flags )
{
    bindVAO(0);
    
    /* Position */
    bool enablePosition = flags & VERTEX_ATTRIB_FLAG_POSITION;

    if( enablePosition != s_vertexAttribPosition ) {
        if( enablePosition )
            glEnableVertexAttribArray( GLProgram::VERTEX_ATTRIB_POSITION );
        else
            glDisableVertexAttribArray( GLProgram::VERTEX_ATTRIB_POSITION );

        s_vertexAttribPosition = enablePosition;
    }

    /* Color */
    bool enableColor = (flags & VERTEX_ATTRIB_FLAG_COLOR) != 0 ? true : false;

    if( enableColor != s_vertexAttribColor ) {
        if( enableColor )
            glEnableVertexAttribArray( GLProgram::VERTEX_ATTRIB_COLOR );
        else
            glDisableVertexAttribArray( GLProgram::VERTEX_ATTRIB_COLOR );

        s_vertexAttribColor = enableColor;
    }

    /* Tex Coords */
    bool enableTexCoords = (flags & VERTEX_ATTRIB_FLAG_TEX_COORDS) != 0 ? true : false;

    if( enableTexCoords != s_vertexAttribTexCoords ) {
        if( enableTexCoords )
            glEnableVertexAttribArray( GLProgram::VERTEX_ATTRIB_TEX_COORDS );
        else
            glDisableVertexAttribArray( GLProgram::VERTEX_ATTRIB_TEX_COORDS );

        s_vertexAttribTexCoords = enableTexCoords;
    }
}

//#pragma mark - GL Uniforms functions

void setProjectionMatrixDirty( void )
{
    s_currentProjectionMatrix = -1;
}

} // Namespace GL

NS_CC_END
