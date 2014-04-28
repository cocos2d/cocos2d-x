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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "2d/CCDirector.h"
#include "2d/CCGLProgram.h"
#include "2d/ccGLStateCache.h"
#include "2d/ccMacros.h"
#include "2d/platform/CCFileUtils.h"
#include "2d/uthash.h"
#include "deprecated/CCString.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "CCPrecompiledShaders.h"
#endif

NS_CC_BEGIN

typedef struct _hashUniformEntry
{
    GLvoid*         value;       // value
    unsigned int    location;    // Key
    UT_hash_handle  hh;          // hash entry
} tHashUniformEntry;

const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR = "ShaderPositionTextureColor";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP = "ShaderPositionTextureColor_noMVP";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST = "ShaderPositionTextureColorAlphaTest";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV = "ShaderPositionTextureColorAlphaTest_NoMV";
const char* GLProgram::SHADER_NAME_POSITION_COLOR = "ShaderPositionColor";
const char* GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP = "ShaderPositionColor_noMVP";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE = "ShaderPositionTexture";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR = "ShaderPositionTexture_uColor";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR = "ShaderPositionTextureA8Color";
const char* GLProgram::SHADER_NAME_POSITION_U_COLOR = "ShaderPosition_uColor";
const char* GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR = "ShaderPositionLengthTextureColor";

const char* GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL = "ShaderLabelDFNormal";
const char* GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW = "ShaderLabelDFGlow";
const char* GLProgram::SHADER_NAME_LABEL_NORMAL = "ShaderLabelNormal";
const char* GLProgram::SHADER_NAME_LABEL_OUTLINE = "ShaderLabelOutline";


// uniform names
const char* GLProgram::UNIFORM_NAME_P_MATRIX = "CC_PMatrix";
const char* GLProgram::UNIFORM_NAME_MV_MATRIX = "CC_MVMatrix";
const char* GLProgram::UNIFORM_NAME_MVP_MATRIX  = "CC_MVPMatrix";
const char* GLProgram::UNIFORM_NAME_TIME = "CC_Time";
const char* GLProgram::UNIFORM_NAME_SIN_TIME = "CC_SinTime";
const char* GLProgram::UNIFORM_NAME_COS_TIME = "CC_CosTime";
const char* GLProgram::UNIFORM_NAME_RANDOM01 = "CC_Random01";
const char* GLProgram::UNIFORM_NAME_SAMPLER = "CC_Texture0";
const char* GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE = "CC_alpha_value";

// Attribute names
const char* GLProgram::ATTRIBUTE_NAME_COLOR = "a_color";
const char* GLProgram::ATTRIBUTE_NAME_POSITION = "a_position";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";


GLProgram::GLProgram()
: _program(0)
, _vertShader(0)
, _fragShader(0)
, _hashForUniforms(nullptr)
, _flags()
{
    memset(_uniforms, 0, sizeof(_uniforms));
}

GLProgram::~GLProgram()
{
    CCLOGINFO("%s %d deallocing GLProgram: %p", __FUNCTION__, __LINE__, this);

    // there is no need to delete the shaders. They should have been already deleted.
    CCASSERT(_vertShader == 0, "Vertex Shaders should have been already deleted");
    CCASSERT(_fragShader == 0, "Fragment Shaders should have been already deleted");

    if (_program) 
    {
        GL::deleteProgram(_program);
    }

    tHashUniformEntry *current_element, *tmp;

    // Purge uniform hash
    HASH_ITER(hh, _hashForUniforms, current_element, tmp)
    {
        HASH_DEL(_hashForUniforms, current_element);
        free(current_element->value);
        free(current_element);
    }
}

bool GLProgram::initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    GLboolean hasCompiler = false;
    glGetBooleanv(GL_SHADER_COMPILER, &hasCompiler);
    _hasShaderCompiler = (hasCompiler == GL_TRUE);

    if(!_hasShaderCompiler)
    {
        return initWithPrecompiledProgramByteArray(vShaderByteArray,fShaderByteArray);
    }
#endif

    _program = glCreateProgram();
    CHECK_GL_ERROR_DEBUG();

    _vertShader = _fragShader = 0;

    if (vShaderByteArray)
    {
        if (!compileShader(&_vertShader, GL_VERTEX_SHADER, vShaderByteArray))
        {
            CCLOG("cocos2d: ERROR: Failed to compile vertex shader");
            return false;
       }
    }

    // Create and compile fragment shader
    if (fShaderByteArray)
    {
        if (!compileShader(&_fragShader, GL_FRAGMENT_SHADER, fShaderByteArray))
        {
            CCLOG("cocos2d: ERROR: Failed to compile fragment shader");
            return false;
        }
    }

    if (_vertShader)
    {
        glAttachShader(_program, _vertShader);
    }
    CHECK_GL_ERROR_DEBUG();

    if (_fragShader)
    {
        glAttachShader(_program, _fragShader);
    }
    _hashForUniforms = nullptr;
    
    CHECK_GL_ERROR_DEBUG();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    _shaderId = CCPrecompiledShaders::getInstance()->addShaders(vShaderByteArray, fShaderByteArray);
#endif

    return true;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
bool GLProgram::initWithPrecompiledProgramByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    bool haveProgram = false;

    _program = glCreateProgram();
    CHECK_GL_ERROR_DEBUG();

    _vertShader = _fragShader = 0;

    haveProgram = CCPrecompiledShaders::getInstance()->loadProgram(_program, vShaderByteArray, fShaderByteArray);

    CHECK_GL_ERROR_DEBUG();
    _hashForUniforms = NULL;

    CHECK_GL_ERROR_DEBUG();  

    return haveProgram;
}
#endif

bool GLProgram::initWithFilenames(const std::string &vShaderFilename, const std::string &fShaderFilename)
{
    auto fileUtils = FileUtils::getInstance();
    std::string vertexSource = fileUtils->getStringFromFile(FileUtils::getInstance()->fullPathForFilename(vShaderFilename));
    std::string fragmentSource = fileUtils->getStringFromFile(FileUtils::getInstance()->fullPathForFilename(fShaderFilename));

    return initWithByteArrays(vertexSource.c_str(), fragmentSource.c_str());
}

std::string GLProgram::getDescription() const
{
    return StringUtils::format("<GLProgram = "
                                      CC_FORMAT_PRINTF_SIZE_T
                                      " | Program = %i, VertexShader = %i, FragmentShader = %i>",
                                      (size_t)this, _program, _vertShader, _fragShader);
}

bool GLProgram::compileShader(GLuint * shader, GLenum type, const GLchar* source)
{
    GLint status;
 
    if (!source)
    {
        return false;
    }
    
    const GLchar *sources[] = {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_LINUX && CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
        (type == GL_VERTEX_SHADER ? "precision highp float;\n" : "precision mediump float;\n"),
#endif
        "uniform mat4 CC_PMatrix;\n"
        "uniform mat4 CC_MVMatrix;\n"
        "uniform mat4 CC_MVPMatrix;\n"
        "uniform vec4 CC_Time;\n"
        "uniform vec4 CC_SinTime;\n"
        "uniform vec4 CC_CosTime;\n"
        "uniform vec4 CC_Random01;\n"
        "//CC INCLUDES END\n\n",
        source,
    };

    *shader = glCreateShader(type);
    glShaderSource(*shader, sizeof(sources)/sizeof(*sources), sources, nullptr);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

    if (! status)
    {
        GLsizei length;
        glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
        GLchar* src = (GLchar *)malloc(sizeof(GLchar) * length);
        
        glGetShaderSource(*shader, length, nullptr, src);
        CCLOG("cocos2d: ERROR: Failed to compile shader:\n%s", src);
        
        if (type == GL_VERTEX_SHADER)
        {
            CCLOG("cocos2d: %s", getVertexShaderLog().c_str());
        }
        else
        {
            CCLOG("cocos2d: %s", getFragmentShaderLog().c_str());
        }
        free(src);

        abort();
    }
    return (status == GL_TRUE);
}

GLint GLProgram::getAttribLocation(const char* attributeName) const
{
    return glGetAttribLocation(_program, attributeName);
}

GLint GLProgram::getUniformLocation(const char* attributeName) const
{
    return glGetUniformLocation(_program, attributeName);
}

void GLProgram::bindAttribLocation(const char* attributeName, GLuint index) const
{
    glBindAttribLocation(_program, index, attributeName);
}

void GLProgram::updateUniforms()
{
    _uniforms[UNIFORM_P_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_P_MATRIX);
    _uniforms[UNIFORM_MV_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MV_MATRIX);
    _uniforms[UNIFORM_MVP_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MVP_MATRIX);
    
    _uniforms[UNIFORM_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_TIME);
    _uniforms[UNIFORM_SIN_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_SIN_TIME);
    _uniforms[UNIFORM_COS_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_COS_TIME);

    _uniforms[UNIFORM_RANDOM01] = glGetUniformLocation(_program, UNIFORM_NAME_RANDOM01);

    _uniforms[UNIFORM_SAMPLER] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER);

    _flags.usesP = _uniforms[UNIFORM_P_MATRIX] != -1;
    _flags.usesMV = _uniforms[UNIFORM_MV_MATRIX] != -1;
    _flags.usesMVP = _uniforms[UNIFORM_MVP_MATRIX] != -1;
    _flags.usesTime = (
                       _uniforms[UNIFORM_TIME] != -1 ||
                       _uniforms[UNIFORM_SIN_TIME] != -1 ||
                       _uniforms[UNIFORM_COS_TIME] != -1
                       );
    _flags.usesRandom = _uniforms[UNIFORM_RANDOM01] != -1;

    this->use();
    
    // Since sample most probably won't change, set it to 0 now.
    this->setUniformLocationWith1i(_uniforms[UNIFORM_SAMPLER], 0);
}

bool GLProgram::link()
{
    CCASSERT(_program != 0, "Cannot link invalid program");
    

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    if(!_hasShaderCompiler)
    {
        // precompiled shader program is already linked
        return true;
    }
#endif

    GLint status = GL_TRUE;
    
    glLinkProgram(_program);

    if (_vertShader)
    {
        glDeleteShader(_vertShader);
    }
    
    if (_fragShader)
    {
        glDeleteShader(_fragShader);
    }
    
    _vertShader = _fragShader = 0;
    
#if DEBUG || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    
    if (status == GL_FALSE)
    {
        CCLOG("cocos2d: ERROR: Failed to link program: %i", _program);
        GL::deleteProgram(_program);
        _program = 0;
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    if (status == GL_TRUE)
    {
        CCPrecompiledShaders::getInstance()->addProgram(_program, _shaderId);
    }
#endif

    return (status == GL_TRUE);
}

void GLProgram::use()
{
    GL::useProgram(_program);
}

std::string GLProgram::logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc) const
{
    std::string ret;
    GLint logLength = 0, charsWritten = 0;

    infoFunc(object, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength < 1)
        return "";

    char *logBytes = (char*)malloc(logLength);
    logFunc(object, logLength, &charsWritten, logBytes);

    ret = logBytes;

    free(logBytes);
    return ret;
}

std::string GLProgram::getVertexShaderLog() const
{
    return this->logForOpenGLObject(_vertShader, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

std::string GLProgram::getFragmentShaderLog() const
{
    return this->logForOpenGLObject(_fragShader, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

std::string GLProgram::getProgramLog() const
{
    return this->logForOpenGLObject(_program, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
}

// Uniform cache

bool GLProgram::updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes)
{
    if (location < 0)
    {
        return false;
    }

    bool updated = true;
    tHashUniformEntry *element = nullptr;
    HASH_FIND_INT(_hashForUniforms, &location, element);

    if (! element)
    {
        element = (tHashUniformEntry*)malloc( sizeof(*element) );

        // key
        element->location = location;

        // value
        element->value = malloc( bytes );
        memcpy(element->value, data, bytes );

        HASH_ADD_INT(_hashForUniforms, location, element);
    }
    else
    {
        if (memcmp(element->value, data, bytes) == 0)
        {
            updated = false;
        }
        else
        {
            memcpy(element->value, data, bytes);
        }
    }

    return updated;
}

GLint GLProgram::getUniformLocationForName(const char* name) const
{
    CCASSERT(name != nullptr, "Invalid uniform name" );
    CCASSERT(_program != 0, "Invalid operation. Cannot get uniform location when program is not initialized");
    
    return glGetUniformLocation(_program, name);
}

void GLProgram::setUniformLocationWith1i(GLint location, GLint i1)
{
    bool updated =  updateUniformLocation(location, &i1, sizeof(i1)*1);
    
    if( updated )
    {
        glUniform1i( (GLint)location, i1);
    }
}

void GLProgram::setUniformLocationWith2i(GLint location, GLint i1, GLint i2)
{
    GLint ints[2] = {i1,i2};
    bool updated =  updateUniformLocation(location, ints, sizeof(ints));
    
    if( updated )
    {
        glUniform2i( (GLint)location, i1, i2);
    }
}

void GLProgram::setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3)
{
    GLint ints[3] = {i1,i2,i3};
    bool updated =  updateUniformLocation(location, ints, sizeof(ints));
    
    if( updated )
    {
        glUniform3i( (GLint)location, i1, i2, i3);
    }
}

void GLProgram::setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4)
{
    GLint ints[4] = {i1,i2,i3,i4};
    bool updated =  updateUniformLocation(location, ints, sizeof(ints));
    
    if( updated )
    {
        glUniform4i( (GLint)location, i1, i2, i3, i4);
    }
}

void GLProgram::setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
    bool updated =  updateUniformLocation(location, ints, sizeof(int)*2*numberOfArrays);
    
    if( updated )
    {
        glUniform2iv( (GLint)location, (GLsizei)numberOfArrays, ints );
    }
}

void GLProgram::setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
    bool updated =  updateUniformLocation(location, ints, sizeof(int)*3*numberOfArrays);
    
    if( updated )
    {
        glUniform3iv( (GLint)location, (GLsizei)numberOfArrays, ints );
    }
}

void GLProgram::setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
    bool updated =  updateUniformLocation(location, ints, sizeof(int)*4*numberOfArrays);
    
    if( updated )
    {
        glUniform4iv( (GLint)location, (GLsizei)numberOfArrays, ints );
    }
}

void GLProgram::setUniformLocationWith1f(GLint location, GLfloat f1)
{
    bool updated =  updateUniformLocation(location, &f1, sizeof(f1)*1);

    if( updated )
    {
        glUniform1f( (GLint)location, f1);
    }
}

void GLProgram::setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2)
{
    GLfloat floats[2] = {f1,f2};
    bool updated =  updateUniformLocation(location, floats, sizeof(floats));

    if( updated )
    {
        glUniform2f( (GLint)location, f1, f2);
    }
}

void GLProgram::setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3)
{
    GLfloat floats[3] = {f1,f2,f3};
    bool updated =  updateUniformLocation(location, floats, sizeof(floats));

    if( updated )
    {
        glUniform3f( (GLint)location, f1, f2, f3);
    }
}

void GLProgram::setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    GLfloat floats[4] = {f1,f2,f3,f4};
    bool updated =  updateUniformLocation(location, floats, sizeof(floats));

    if( updated )
    {
        glUniform4f( (GLint)location, f1, f2, f3,f4);
    }
}

void GLProgram::setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
    bool updated =  updateUniformLocation(location, floats, sizeof(float)*2*numberOfArrays);

    if( updated )
    {
        glUniform2fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
    bool updated =  updateUniformLocation(location, floats, sizeof(float)*3*numberOfArrays);

    if( updated )
    {
        glUniform3fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
    bool updated =  updateUniformLocation(location, floats, sizeof(float)*4*numberOfArrays);

    if( updated )
    {
        glUniform4fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices) {
    bool updated =  updateUniformLocation(location, matrixArray, sizeof(float)*4*numberOfMatrices);
    
    if( updated )
    {
        glUniformMatrix2fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}

void GLProgram::setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices) {
    bool updated =  updateUniformLocation(location, matrixArray, sizeof(float)*9*numberOfMatrices);
    
    if( updated )
    {
        glUniformMatrix3fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}


void GLProgram::setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
    bool updated =  updateUniformLocation(location, matrixArray, sizeof(float)*16*numberOfMatrices);

    if( updated )
    {
        glUniformMatrix4fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}

void GLProgram::setUniformsForBuiltins()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Matrix matrixMV;
    matrixMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    setUniformsForBuiltins(matrixMV);
}

void GLProgram::setUniformsForBuiltins(const Matrix &matrixMV)
{
    Matrix matrixP = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    if(_flags.usesP)
        setUniformLocationWithMatrix4fv(_uniforms[UNIFORM_P_MATRIX], matrixP.m, 1);

    if(_flags.usesMV)
        setUniformLocationWithMatrix4fv(_uniforms[UNIFORM_MV_MATRIX], matrixMV.m, 1);

    if(_flags.usesMVP) {
        Matrix matrixMVP = matrixP * matrixMV;
        setUniformLocationWithMatrix4fv(_uniforms[UNIFORM_MVP_MATRIX], matrixMVP.m, 1);
    }

    if(_flags.usesTime) {
        Director *director = Director::getInstance();
        // This doesn't give the most accurate global time value.
        // Cocos2D doesn't store a high precision time value, so this will have to do.
        // Getting Mach time per frame per shader using time could be extremely expensive.
        float time = director->getTotalFrames() * director->getAnimationInterval();
        
        setUniformLocationWith4f(_uniforms[GLProgram::UNIFORM_TIME], time/10.0, time, time*2, time*4);
        setUniformLocationWith4f(_uniforms[GLProgram::UNIFORM_SIN_TIME], time/8.0, time/4.0, time/2.0, sinf(time));
        setUniformLocationWith4f(_uniforms[GLProgram::UNIFORM_COS_TIME], time/8.0, time/4.0, time/2.0, cosf(time));
    }
    
    if(_flags.usesRandom)
        setUniformLocationWith4f(_uniforms[GLProgram::UNIFORM_RANDOM01], CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}

void GLProgram::reset()
{
    _vertShader = _fragShader = 0;
    memset(_uniforms, 0, sizeof(_uniforms));
    

    // it is already deallocated by android
    //GL::deleteProgram(_program);
    _program = 0;

    
    tHashUniformEntry *current_element, *tmp;
    
    // Purge uniform hash
    HASH_ITER(hh, _hashForUniforms, current_element, tmp) 
    {
        HASH_DEL(_hashForUniforms, current_element);
        free(current_element->value);
        free(current_element);
    }
    _hashForUniforms = nullptr;
}

NS_CC_END
