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

struct _hashUniformEntry;

typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);

/** GLProgram
 Class that implements a glProgram
 
 
 @since v2.0.0
 */
class CC_DLL GLProgram : public Object
{
public:
    enum
    {
        VERTEX_ATTRIB_POSITION,
        VERTEX_ATTRIB_COLOR,
        VERTEX_ATTRIB_TEX_COORDS,
        
        VERTEX_ATTRIB_MAX,
    };
    
    enum
    {
        UNIFORM_P_MATRIX,
        UNIFORM_MV_MATRIX,
        UNIFORM_MVP_MATRIX,
        UNIFORM_TIME,
        UNIFORM_SIN_TIME,
        UNIFORM_COS_TIME,
        UNIFORM_RANDOM01,
        UNIFORM_SAMPLER,
        
        UNIFORM_MAX,
    };
    
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
    static const char* SHADER_NAME_POSITION_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE;
    static const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
    static const char* SHADER_NAME_POSITION_U_COLOR;
    static const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;
    
    // uniform names
    static const char* UNIFORM_NAME_P_MATRIX;
    static const char* UNIFORM_NAME_MV_MATRIX;
    static const char* UNIFORM_NAME_MVP_MATRIX;
    static const char* UNIFORM_NAME_TIME;
    static const char* UNIFORM_NAME_SIN_TIME;
    static const char* UNIFORM_NAME_COS_TIME;
    static const char* UNIFORM_NAME_RANDOM01;
    static const char* UNIFORM_NAME_SAMPLER;
    static const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
    
    // Attribute names
    static const char* ATTRIBUTE_NAME_COLOR;
    static const char* ATTRIBUTE_NAME_POSITION;
    static const char* ATTRIBUTE_NAME_TEX_COORD;
    
    GLProgram();
    virtual ~GLProgram();
    /** Initializes the GLProgram with a vertex and fragment with bytes array */
    bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    /** Initializes the GLProgram with a vertex and fragment with contents of filenames */
    bool initWithVertexShaderFilename(const char* vShaderFilename, const char* fShaderFilename);
    /**  It will add a new attribute to the shader */
    void addAttribute(const char* attributeName, GLuint index);
    /** links the glProgram */
    bool link();
    /** it will call glUseProgram() */
    void use();
/** It will create 4 uniforms:
    - kUniformPMatrix
    - kUniformMVMatrix
    - kUniformMVPMatrix
    - GLProgram::UNIFORM_SAMPLER

 And it will bind "GLProgram::UNIFORM_SAMPLER" to 0

 */
    void updateUniforms();
    
    /** calls retrieves the named uniform location for this shader program. */
    GLint getUniformLocationForName(const char* name) const;
    
    /** calls glUniform1i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith1i(GLint location, GLint i1);
    
    /** calls glUniform2i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);
    
    /** calls glUniform3i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);
    
    /** calls glUniform4i only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);
    
    /** calls glUniform2iv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    
    /** calls glUniform3iv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    
    /** calls glUniform4iv only if the values are different than the previous call for this same shader program. */
    
    void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** calls glUniform1f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** calls glUniform2f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** calls glUniform3f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** calls glUniform4f only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4fv(GLint location, GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix4fv(GLint location, GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** will update the builtin uniforms if they are different than the previous call for this same shader program. */
    void setUniformsForBuiltins();

    /** returns the vertexShader error log */
    const char* vertexShaderLog() const;
    /** returns the fragmentShader error log */
    const char* fragmentShaderLog() const;
    /** returns the program error log */
    const char* programLog() const;
    
    // reload all shaders, this function is designed for android
    // when opengl context lost, so don't call it.
    void reset();
    
    inline const GLuint getProgram() const { return _program; }

private:
    bool updateUniformLocation(GLint location, GLvoid* data, unsigned int bytes);
    const char* description() const;
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    const char* logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc) const;

private:
    GLuint            _program;
    GLuint            _vertShader;
    GLuint            _fragShader;
    GLint             _uniforms[UNIFORM_MAX];
    struct _hashUniformEntry* _hashForUniforms;
    bool              _usesTime;
};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCGLPROGRAM_H__ */
