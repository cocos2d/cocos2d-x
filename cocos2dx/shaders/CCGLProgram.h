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
    kVertexAttrib_Position,
    kVertexAttrib_Color,
    kVertexAttrib_TexCoords,

    kVertexAttrib_MAX,
};

enum {
	kUniformPMatrix,
	kUniformMVMatrix,
	kUniformMVPMatrix,
	kUniformTime,
	kUniformSinTime,
	kUniformCosTime,
	kUniformRandom01,
	kUniformSampler,
    
	kUniform_MAX,
};

#define kShader_PositionTextureColor              "ShaderPositionTextureColor"
#define kShader_PositionTextureColorAlphaTest     "ShaderPositionTextureColorAlphaTest"
#define kShader_PositionColor                     "ShaderPositionColor"
#define kShader_PositionTexture                   "ShaderPositionTexture"
#define kShader_PositionTexture_uColor            "ShaderPositionTexture_uColor"
#define kShader_PositionTextureA8Color            "ShaderPositionTextureA8Color"
#define kShader_Position_uColor                   "ShaderPosition_uColor"
#define kShader_PositionLengthTexureColor         "ShaderPositionLengthTextureColor"

// uniform names
#define kUniformPMatrix_s				"CC_PMatrix"
#define kUniformMVMatrix_s			"CC_MVMatrix"
#define kUniformMVPMatrix_s			"CC_MVPMatrix"
#define kUniformTime_s				"CC_Time"
#define kUniformSinTime_s				"CC_SinTime"
#define kUniformCosTime_s				"CC_CosTime"
#define kUniformRandom01_s			"CC_Random01"
#define kUniformSampler_s				"CC_Texture0"
#define kUniformAlphaTestValue		"CC_alpha_value"

// Attribute names
#define    kAttributeNameColor           "a_color"
#define    kAttributeNamePosition        "a_position"
#define    kAttributeNameTexCoord        "a_texCoord"

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
    - kUniformSampler

 And it will bind "kUniformSampler" to 0

 */
    void updateUniforms();
    
    /** calls retrieves the named uniform location for this shader program. */
    GLint getUniformLocationForName(const char* name);
    
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
    const char* vertexShaderLog();
    /** returns the fragmentShader error log */
    const char* fragmentShaderLog();
    /** returns the program error log */
    const char* programLog();
    
    // reload all shaders, this function is designed for android
    // when opengl context lost, so don't call it.
    void reset();
    
    inline const GLuint getProgram() { return _program; }

private:
    bool updateUniformLocation(GLint location, GLvoid* data, unsigned int bytes);
    const char* description();
    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    const char* logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc);

private:
    GLuint            _program;
    GLuint            _vertShader;
    GLuint            _fragShader;
    GLint             _uniforms[kUniform_MAX];
    struct _hashUniformEntry* _hashForUniforms;
    bool              _usesTime;
};

// end of shaders group
/// @}

NS_CC_END

#endif /* __CCGLPROGRAM_H__ */
