/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

// extern
#include "kazmath/GL/matrix.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

static GLuint      s_uCurrentProjectionMatrix = -1;
static bool        s_bVertexAttribPosition = false;
static bool        s_bVertexAttribColor = false;
static bool        s_bVertexAttribTexCoords = false;


#if CC_ENABLE_GL_STATE_CACHE

#define kMaxActiveTexture 16

static GLuint    s_uCurrentShaderProgram = -1;
static GLuint    s_uCurrentBoundTexture[kMaxActiveTexture] =  {(GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, (GLuint)-1,(GLuint)-1,(GLuint)-1,(GLuint)-1, };
static GLenum    s_eBlendingSource = -1;
static GLenum    s_eBlendingDest = -1;
static int       s_eGLServerState = 0;
#if CC_TEXTURE_ATLAS_USE_VAO
static GLuint    s_uVAO = 0;
#endif
#endif // CC_ENABLE_GL_STATE_CACHE

// GL State Cache functions

namespace GL {

void invalidateStateCache( void )
{
    kmGLFreeAll();
    
    s_uCurrentProjectionMatrix = -1;
    s_bVertexAttribPosition = false;
    s_bVertexAttribColor = false;
    s_bVertexAttribTexCoords = false;
    
#if CC_ENABLE_GL_STATE_CACHE
    s_uCurrentShaderProgram = -1;
    for( int i=0; i < kMaxActiveTexture; i++ )
    {
        s_uCurrentBoundTexture[i] = -1;
    }

    s_eBlendingSource = -1;
    s_eBlendingDest = -1;
    s_eGLServerState = 0;
#if CC_TEXTURE_ATLAS_USE_VAO
    s_uVAO = 0;
#endif
    
#endif // CC_ENABLE_GL_STATE_CACHE
}

void deleteProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
    if(program == s_uCurrentShaderProgram)
    {
        s_uCurrentShaderProgram = -1;
    }
#endif // CC_ENABLE_GL_STATE_CACHE

    glDeleteProgram( program );
}

void useProgram( GLuint program )
{
#if CC_ENABLE_GL_STATE_CACHE
    if( program != s_uCurrentShaderProgram ) {
        s_uCurrentShaderProgram = program;
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
    if (sfactor != s_eBlendingSource || dfactor != s_eBlendingDest)
    {
        s_eBlendingSource = sfactor;
        s_eBlendingDest = dfactor;
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
	SetBlending(s_eBlendingSource, s_eBlendingDest);
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
    if (s_uCurrentBoundTexture[textureUnit] != textureId)
    {
        s_uCurrentBoundTexture[textureUnit] = textureId;
        glActiveTexture(GL_TEXTURE0 + textureUnit);
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
	if (s_uCurrentBoundTexture[textureUnit] == textureId)
    {
		s_uCurrentBoundTexture[textureUnit] = -1;
    }
#endif // CC_ENABLE_GL_STATE_CACHE
    
	glDeleteTextures(1, &textureId);
}

void bindVAO(GLuint vaoId)
{
#if CC_TEXTURE_ATLAS_USE_VAO  
    
#if CC_ENABLE_GL_STATE_CACHE
	if (s_uVAO != vaoId)
	{
		s_uVAO = vaoId;
		glBindVertexArray(vaoId);
	}
#else
	glBindVertexArray(vaoId);
#endif // CC_ENABLE_GL_STATE_CACHE
    
#endif
}

//#pragma mark - GL Vertex Attrib functions

void enableVertexAttribs( unsigned int flags )
{
    bindVAO(0);
    
    /* Position */
    bool enablePosition = flags & VERTEX_ATTRIB_FLAG_POSITION;

    if( enablePosition != s_bVertexAttribPosition ) {
        if( enablePosition )
            glEnableVertexAttribArray( GLProgram::VERTEX_ATTRIB_POSITION );
        else
            glDisableVertexAttribArray( GLProgram::VERTEX_ATTRIB_POSITION );

        s_bVertexAttribPosition = enablePosition;
    }

    /* Color */
    bool enableColor = (flags & VERTEX_ATTRIB_FLAG_COLOR) != 0 ? true : false;

    if( enableColor != s_bVertexAttribColor ) {
        if( enableColor )
            glEnableVertexAttribArray( GLProgram::VERTEX_ATTRIB_COLOR );
        else
            glDisableVertexAttribArray( GLProgram::VERTEX_ATTRIB_COLOR );

        s_bVertexAttribColor = enableColor;
    }

    /* Tex Coords */
    bool enableTexCoords = (flags & VERTEX_ATTRIB_FLAG_TEX_COORDS) != 0 ? true : false;

    if( enableTexCoords != s_bVertexAttribTexCoords ) {
        if( enableTexCoords )
            glEnableVertexAttribArray( GLProgram::VERTEX_ATTRIB_TEX_COORDS );
        else
            glDisableVertexAttribArray( GLProgram::VERTEX_ATTRIB_TEX_COORDS );

        s_bVertexAttribTexCoords = enableTexCoords;
    }
}

//#pragma mark - GL Uniforms functions

void setProjectionMatrixDirty( void )
{
    s_uCurrentProjectionMatrix = -1;
}

} // Namespace GL

NS_CC_END
