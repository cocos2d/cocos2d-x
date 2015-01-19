/****************************************************************************
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada
Copyright 2012 cocos2d-x.org
Copyright 2013-2014 Chukong Technologies Inc.
 
 
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

#include <unordered_map>

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "platform/CCGL.h"
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

class GLProgram;
class Director;
//FIXME: these two typedefs would be deprecated or removed in version 4.0
typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);

struct VertexAttrib
{
    GLuint index;
    GLint size;
    GLenum type;
    std::string name;
};

struct Uniform
{
    GLint location;
    GLint size;
    GLenum type;
    std::string name;
};

/** GLProgram
 Class that implements a glProgram
 
 
 @since v2.0.0
 */
class CC_DLL GLProgram : public Ref
{
    friend class GLProgramState;

public:
    enum
    {
        VERTEX_ATTRIB_POSITION,
        VERTEX_ATTRIB_COLOR,
        VERTEX_ATTRIB_TEX_COORD,
        VERTEX_ATTRIB_TEX_COORD1,
        VERTEX_ATTRIB_TEX_COORD2,
        VERTEX_ATTRIB_TEX_COORD3,
        VERTEX_ATTRIB_NORMAL,
        VERTEX_ATTRIB_BLEND_WEIGHT,
        VERTEX_ATTRIB_BLEND_INDEX,
        VERTEX_ATTRIB_POINTSIZE,
        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };
    
    enum
    {
        UNIFORM_AMBIENT_COLOR,
        UNIFORM_P_MATRIX,
        UNIFORM_MV_MATRIX,
        UNIFORM_MVP_MATRIX,
        UNIFORM_NORMAL_MATRIX,
        UNIFORM_TIME,
        UNIFORM_SIN_TIME,
        UNIFORM_COS_TIME,
        UNIFORM_RANDOM01,
        UNIFORM_SAMPLER0,
        UNIFORM_SAMPLER1,
        UNIFORM_SAMPLER2,
        UNIFORM_SAMPLER3,

        UNIFORM_MAX,
    };
    
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV;
    static const char* SHADER_NAME_POSITION_COLOR;
    static const char* SHADER_NAME_POSITION_COLOR_POINTSIZE;
    static const char* SHADER_NAME_POSITION_COLOR_NO_MVP;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || defined(WP8_SHADER_COMPILER)
    static const char* SHADER_NAME_POSITION_COLOR_NO_MVP_GRAYSCALE;
#endif
    static const char* SHADER_NAME_POSITION_TEXTURE;
    static const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
    static const char* SHADER_NAME_POSITION_U_COLOR;
    static const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

    static const char* SHADER_NAME_LABEL_NORMAL;
    static const char* SHADER_NAME_LABEL_OUTLINE;

    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL;
    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_GLOW;
    
    //3D
    static const char* SHADER_3D_POSITION;
    static const char* SHADER_3D_POSITION_TEXTURE;
    static const char* SHADER_3D_SKINPOSITION_TEXTURE;
    static const char* SHADER_3D_POSITION_NORMAL;
    static const char* SHADER_3D_POSITION_NORMAL_TEXTURE;
    static const char* SHADER_3D_SKINPOSITION_NORMAL_TEXTURE;
    
    // uniform names
    static const char* UNIFORM_NAME_AMBIENT_COLOR;
    static const char* UNIFORM_NAME_P_MATRIX;
    static const char* UNIFORM_NAME_MV_MATRIX;
    static const char* UNIFORM_NAME_MVP_MATRIX;
    static const char* UNIFORM_NAME_NORMAL_MATRIX;
    static const char* UNIFORM_NAME_TIME;
    static const char* UNIFORM_NAME_SIN_TIME;
    static const char* UNIFORM_NAME_COS_TIME;
    static const char* UNIFORM_NAME_RANDOM01;
    static const char* UNIFORM_NAME_SAMPLER0;
    static const char* UNIFORM_NAME_SAMPLER1;
    static const char* UNIFORM_NAME_SAMPLER2;
    static const char* UNIFORM_NAME_SAMPLER3;
    static const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
    
    // Attribute names
    static const char* ATTRIBUTE_NAME_COLOR;
    static const char* ATTRIBUTE_NAME_POSITION;
    static const char* ATTRIBUTE_NAME_POINTSIZE;
    static const char* ATTRIBUTE_NAME_TEX_COORD;
    static const char* ATTRIBUTE_NAME_TEX_COORD1;
    static const char* ATTRIBUTE_NAME_TEX_COORD2;
    static const char* ATTRIBUTE_NAME_TEX_COORD3;
    static const char* ATTRIBUTE_NAME_NORMAL;
    static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
    static const char* ATTRIBUTE_NAME_BLEND_INDEX;

    GLProgram();
    virtual ~GLProgram();
    /** Initializes the GLProgram with a vertex and fragment with bytes array 
     * @js initWithString
     * @lua initWithString
     */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    /** Initializes the CCGLProgram with precompiled shader program */
    static GLProgram* createWithPrecompiledProgramByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    bool initWithPrecompiledProgramByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
#endif

    /** Initializes the GLProgram with a vertex and fragment with bytes array 
     * @js initWithString
     * @lua initWithString
     */
    static GLProgram* createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);

    /** Initializes the GLProgram with a vertex and fragment with contents of filenames 
     * @js init
     * @lua init
     */
    static GLProgram* createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);
    bool initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);

    //void bindUniform(std::string uniformName, int value);
    Uniform* getUniform(const std::string& name);
    VertexAttrib* getVertexAttrib(const std::string& name);

    /**  It will add a new attribute to the shader by calling glBindAttribLocation */
    void bindAttribLocation(const std::string& attributeName, GLuint index) const;

    /** calls glGetAttribLocation */
    GLint getAttribLocation(const std::string& attributeName) const;

    /** calls glGetUniformLocation() */
    GLint getUniformLocation(const std::string& attributeName) const;

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
    
    /** calls glUniform1i only if the values are different than the previous call for this same shader program. 
     * @js setUniformLocationI32
     * @lua setUniformLocationI32
     */
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

    /** calls glUniform1f only if the values are different than the previous call for this same shader program. 
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** calls glUniform2f only if the values are different than the previous call for this same shader program. 
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** calls glUniform3f only if the values are different than the previous call for this same shader program. 
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** calls glUniform4f only if the values are different than the previous call for this same shader program. 
     * In js or lua,please use setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** calls glUniformfv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith1fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** calls glUniformMatrix2fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** calls glUniformMatrix3fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. */
    void setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** will update the builtin uniforms if they are different than the previous call for this same shader program. */
    void setUniformsForBuiltins();
    void setUniformsForBuiltins(const Mat4 &modelView);

    // Attribute

    /** returns the vertexShader error log */
    std::string getVertexShaderLog() const;

    /** returns the fragmentShader error log */
    std::string getFragmentShaderLog() const;

    /** returns the program error log */
    std::string getProgramLog() const;
    
    // reload all shaders, this function is designed for android
    // when opengl context lost, so don't call it.
    void reset();
    
    inline const GLuint getProgram() const { return _program; }

    // DEPRECATED
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderByteArray(const GLchar* vertexByteArray, const GLchar* fragByteArray)
    { return initWithByteArrays(vertexByteArray, fragByteArray); }
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderFilename(const std::string &vertexFilename, const std::string& fragFilename)
    { return initWithFilenames(vertexFilename, fragFilename); }
    CC_DEPRECATED_ATTRIBUTE void addAttribute(const std::string &attributeName, GLuint index) const { return bindAttribLocation(attributeName, index); }


protected:
    bool updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes);
    virtual std::string getDescription() const;

    void bindPredefinedVertexAttribs();
    void parseVertexAttribs();
    void parseUniforms();

    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    
    GLuint            _program;
    GLuint            _vertShader;
    GLuint            _fragShader;
    GLint             _builtInUniforms[UNIFORM_MAX];
    bool              _hasShaderCompiler;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || defined(WP8_SHADER_COMPILER)
    std::string       _shaderId;
#endif

    struct flag_struct {
        unsigned int usesTime:1;
        unsigned int usesNormal:1;
        unsigned int usesMVP:1;
        unsigned int usesMV:1;
        unsigned int usesP:1;
        unsigned int usesRandom:1;
        // handy way to initialize the bitfield
        flag_struct() { memset(this, 0, sizeof(*this)); }
    } _flags;

    std::unordered_map<std::string, Uniform> _userUniforms;
    std::unordered_map<std::string, VertexAttrib> _vertexAttribs;
    std::unordered_map<GLint, GLvoid*> _hashForUniforms;
    //cached director pointer for calling
    Director* _director;
};

NS_CC_END

#endif /* __CCGLPROGRAM_H__ */
