/****************************************************************************
Copyright 2012 cocos2d-x.org
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada

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

#ifndef __CCGLPROGRAM_H__
#define __CCGLPROGRAM_H__

#include "ccMacros.h"
#include "cocoa/CCObject.h"

#include "CCGL.h"

NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

enum {
    kCCVertexAttrib_Position,
    kCCVertexAttrib_Color,
    kCCVertexAttrib_TexCoords,

    kCCVertexAttrib_MAX,
};

enum {
    kCCUniformMVPMatrix,
    kCCUniformSampler,

    kCCUniform_MAX,
};

#define kCCShader_PositionTextureColor            "ShaderPositionTextureColor"
#define kCCShader_PositionTextureColorAlphaTest    "ShaderPositionTextureColorAlphaTest"
#define kCCShader_PositionColor                    "ShaderPositionColor"
#define kCCShader_PositionTexture                "ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor        "ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color        "ShaderPositionTextureA8Color"
#define kCCShader_Position_uColor                "ShaderPosition_uColor"

// uniform names
#define kCCUniformMVPMatrix_s            "u_MVPMatrix"
#define kCCUniformSampler_s                "u_texture"
#define kCCUniformAlphaTestValue        "u_alpha_value"

// Attribute names
#define    kCCAttributeNameColor            "a_color"
#define    kCCAttributeNamePosition        "a_position"
#define    kCCAttributeNameTexCoord        "a_texCoord"

struct _hashUniformEntry;

typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);

/** CCGLProgram
 Class that implements a glProgram
 
 
 @since v2.0.0
 */
class CC_DLL CCGLProgram : public CCObject
{
public:


    CCGLProgram();
    virtual ~CCGLProgram();
    /** Initializes the CCGLProgram with a vertex and fragment with bytes array */
    bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    /** Initializes the CCGLProgram with a vertex and fragment with contents of filenames */
    bool initWithVertexShaderFilename(const char* vShaderFilename, const char* fShaderFilename);
    /**  It will add a new attribute to the shader */
    void addAttribute(const char* attributeName, GLuint index);
    /** links the glProgram */
    bool link();
    /** it will call glUseProgram() */
    void use();
/** It will create 3 uniforms:
    - kCCUniformPMatrix
    - kCCUniformMVMatrix
    - kCCUniformSampler

 And it will bind "kCCUniformSampler" to 0

 */
    void updateUniforms();
    /** calls glUniform1i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith1i(unsigned int location, GLint i1);

    /** calls glUniform1f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith1f(unsigned int location, GLfloat f1);

    /** calls glUniform2f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2f(unsigned int location, GLfloat f1, GLfloat f2);

    /** calls glUniform3f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3f(unsigned int location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** calls glUniform4f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4f(unsigned int location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2fv(unsigned int location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3fv(unsigned int location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4fv(unsigned int location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationwithMatrix4fv(unsigned int location, GLfloat* matrixArray, unsigned int numberOfMatrices);

    /** will update the MVP matrix on the MVP uniform if it is different than the previous call for this same shader program. */
    void setUniformForModelViewProjectionMatrix();

    /** returns the vertexShader error log */
    const char* vertexShaderLog();
    /** returns the fragmentShader error log */
    const char* fragmentShaderLog();
    /** returns the program error log */
    const char* programLog();
    
    // reload all shaders, this function is designed for android
    // when opengl context lost, so don't call it.
    void reset();
    
    inline const GLuint getProgram() { return m_uProgram; }

private:
    bool updateUniformLocation(unsigned int location, GLvoid* data, unsigned int bytes);
    const char* description();
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    const char* logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc);

private:
    GLuint            m_uProgram;
    GLuint            m_uVertShader;
    GLuint            m_uFragShader;
    GLint            m_uUniforms[kCCUniform_MAX];
    struct _hashUniformEntry* m_pHashForUniforms;
};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCGLPROGRAM_H__ */
