/****************************************************************************
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada
Copyright 2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "renderer/CCGLProgram.h"

#ifndef WIN32
#include <alloca.h>
#endif

#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "platform/CCFileUtils.h"

// helper functions

static void replaceDefines(const std::string& compileTimeDefines, std::string& out)
{
    // Replace semicolons with '#define ... \n'
    if (!compileTimeDefines.empty())
    {
        // append ';' if the last char doesn't have one
        auto copyDefines = compileTimeDefines;
        if (copyDefines[copyDefines.length()-1] != ';')
            copyDefines.append(1, ';');

        std::string currentDefine;

        for (auto itChar: copyDefines)
        {
            if (itChar == ';')
            {
                if (!currentDefine.empty())
                {
                    out.append("\n#define " + currentDefine);
                    currentDefine.clear();
                }
            }
            else
            {
                currentDefine.append(1, itChar);
            }
        }
        out += "\n";
    }
}


NS_CC_BEGIN
const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR = "#ShaderETC1ASPositionTextureColor";
const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP = "#ShaderETC1ASPositionTextureColor_noMVP";

const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY = "#ShaderETC1ASPositionTextureGray";
const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP = "#ShaderETC1ASPositionTextureGray_noMVP";

const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR = "ShaderPositionTextureColor";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP = "ShaderPositionTextureColor_noMVP";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST = "ShaderPositionTextureColorAlphaTest";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV = "ShaderPositionTextureColorAlphaTest_NoMV";
const char* GLProgram::SHADER_NAME_POSITION_COLOR = "ShaderPositionColor";
const char* GLProgram::SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE = "ShaderPositionColorTexAsPointsize";
const char* GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP = "ShaderPositionColor_noMVP";

const char* GLProgram::SHADER_NAME_POSITION_TEXTURE = "ShaderPositionTexture";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR = "ShaderPositionTexture_uColor";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR = "ShaderPositionTextureA8Color";
const char* GLProgram::SHADER_NAME_POSITION_U_COLOR = "ShaderPosition_uColor";
const char* GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR = "ShaderPositionLengthTextureColor";
const char* GLProgram::SHADER_NAME_POSITION_GRAYSCALE = "ShaderUIGrayScale";
const char* GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL = "ShaderLabelDFNormal";
const char* GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW = "ShaderLabelDFGlow";
const char* GLProgram::SHADER_NAME_LABEL_NORMAL = "ShaderLabelNormal";
const char* GLProgram::SHADER_NAME_LABEL_OUTLINE = "ShaderLabelOutline";

const char* GLProgram::SHADER_3D_POSITION = "Shader3DPosition";
const char* GLProgram::SHADER_3D_POSITION_TEXTURE = "Shader3DPositionTexture";
const char* GLProgram::SHADER_3D_SKINPOSITION_TEXTURE = "Shader3DSkinPositionTexture";
const char* GLProgram::SHADER_3D_POSITION_NORMAL = "Shader3DPositionNormal";
const char* GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE = "Shader3DPositionNormalTexture";
const char* GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE = "Shader3DSkinPositionNormalTexture";
const char* GLProgram::SHADER_3D_POSITION_BUMPEDNORMAL_TEXTURE = "Shader3DPositionBumpedNormalTexture";
const char* GLProgram::SHADER_3D_SKINPOSITION_BUMPEDNORMAL_TEXTURE = "Shader3DSkinPositionBumpedNormalTexture";
const char* GLProgram::SHADER_3D_PARTICLE_COLOR = "Shader3DParticleColor";
const char* GLProgram::SHADER_3D_PARTICLE_TEXTURE = "Shader3DParticleTexture";
const char* GLProgram::SHADER_3D_SKYBOX = "Shader3DSkybox";
const char* GLProgram::SHADER_3D_TERRAIN = "Shader3DTerrain";
const char* GLProgram::SHADER_CAMERA_CLEAR = "ShaderCameraClear";
const char* GLProgram::SHADER_LAYER_RADIAL_GRADIENT = "ShaderLayerRadialGradient";


// uniform names
const char* GLProgram::UNIFORM_NAME_AMBIENT_COLOR = "CC_AmbientColor";
const char* GLProgram::UNIFORM_NAME_P_MATRIX = "CC_PMatrix";
const char* GLProgram::UNIFORM_NAME_MULTIVIEW_P_MATRIX = "CC_MultiViewPMatrix";
const char* GLProgram::UNIFORM_NAME_MV_MATRIX = "CC_MVMatrix";
const char* GLProgram::UNIFORM_NAME_MVP_MATRIX  = "CC_MVPMatrix";
const char* GLProgram::UNIFORM_NAME_MULTIVIEW_MVP_MATRIX  = "CC_MultiViewMVPMatrix";
const char* GLProgram::UNIFORM_NAME_NORMAL_MATRIX = "CC_NormalMatrix";
const char* GLProgram::UNIFORM_NAME_TIME = "CC_Time";
const char* GLProgram::UNIFORM_NAME_SIN_TIME = "CC_SinTime";
const char* GLProgram::UNIFORM_NAME_COS_TIME = "CC_CosTime";
const char* GLProgram::UNIFORM_NAME_RANDOM01 = "CC_Random01";
const char* GLProgram::UNIFORM_NAME_SAMPLER0 = "CC_Texture0";
const char* GLProgram::UNIFORM_NAME_SAMPLER1 = "CC_Texture1";
const char* GLProgram::UNIFORM_NAME_SAMPLER2 = "CC_Texture2";
const char* GLProgram::UNIFORM_NAME_SAMPLER3 = "CC_Texture3";
const char* GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE = "CC_alpha_value";

// Attribute names
const char* GLProgram::ATTRIBUTE_NAME_COLOR = "a_color";
const char* GLProgram::ATTRIBUTE_NAME_POSITION = "a_position";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD1 = "a_texCoord1";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD2 = "a_texCoord2";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD3 = "a_texCoord3";
const char* GLProgram::ATTRIBUTE_NAME_NORMAL = "a_normal";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT = "a_blendWeight";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_INDEX = "a_blendIndex";
const char* GLProgram::ATTRIBUTE_NAME_TANGENT = "a_tangent";
const char* GLProgram::ATTRIBUTE_NAME_BINORMAL = "a_binormal";



static const char * COCOS2D_SHADER_UNIFORMS =
        "uniform mat4 CC_PMatrix;\n"
        "uniform mat4 CC_MultiViewPMatrix[4];\n"
        "uniform mat4 CC_MVMatrix;\n"
        "uniform mat4 CC_MVPMatrix;\n"
        "uniform mat4 CC_MultiViewMVPMatrix[4];\n"
        "uniform mat3 CC_NormalMatrix;\n"
        "uniform vec4 CC_Time;\n"
        "uniform vec4 CC_SinTime;\n"
        "uniform vec4 CC_CosTime;\n"
        "uniform vec4 CC_Random01;\n"
        "uniform sampler2D CC_Texture0;\n"
        "uniform sampler2D CC_Texture1;\n"
        "uniform sampler2D CC_Texture2;\n"
        "uniform sampler2D CC_Texture3;\n"
        "//CC INCLUDES END\n\n";

static const std::string EMPTY_DEFINE;

GLProgram* GLProgram::createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    return createWithByteArrays(vShaderByteArray, fShaderByteArray, EMPTY_DEFINE);
}

GLProgram* GLProgram::createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeDefines)
{
    return createWithByteArrays(vShaderByteArray, fShaderByteArray, EMPTY_DEFINE, compileTimeDefines);
}

GLProgram* GLProgram::createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeHeaders, const std::string& compileTimeDefines)
{
    auto ret = new (std::nothrow) GLProgram();
    if(ret && ret->initWithByteArrays(vShaderByteArray, fShaderByteArray, compileTimeHeaders, compileTimeDefines)) {
        ret->link();
        ret->updateUniforms();
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLProgram* GLProgram::createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename)
{
    return createWithFilenames(vShaderFilename, fShaderFilename, EMPTY_DEFINE);
}

GLProgram* GLProgram::createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeDefines)
{
    return createWithFilenames(vShaderFilename, fShaderFilename, EMPTY_DEFINE, compileTimeDefines);
}

GLProgram* GLProgram::createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& /*compileTimeHeaders*/, const std::string& compileTimeDefines)
{
    auto ret = new (std::nothrow) GLProgram();
    if(ret && ret->initWithFilenames(vShaderFilename, fShaderFilename, compileTimeDefines)) {
        ret->link();
        ret->updateUniforms();
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLProgram::GLProgram()
: _program(0)
, _vertShader(0)
, _fragShader(0)
, _flags()
{
    _director = Director::getInstance();
    CCASSERT(nullptr != _director, "Director is null when init a GLProgram");
    memset(_builtInUniforms, 0, sizeof(_builtInUniforms));
}

GLProgram::~GLProgram()
{
    CCLOGINFO("%s %d deallocing GLProgram: %p", __FUNCTION__, __LINE__, this);

    clearShader();

    if (_program)
    {
        glDeleteProgram(_program);
    }


    clearHashUniforms();
}

bool GLProgram::initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    return initWithByteArrays(vShaderByteArray, fShaderByteArray, EMPTY_DEFINE);
}

bool GLProgram::initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeDefines)
{
    return initWithByteArrays(vShaderByteArray, fShaderByteArray, "", compileTimeDefines);
}

bool GLProgram::initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray, const std::string& compileTimeHeaders, const std::string& compileTimeDefines)
{
    _program = glCreateProgram();
    CHECK_GL_ERROR_DEBUG();

    // convert defines here. If we do it in "compileShader" we will do it twice.
    // a cache for the defines could be useful, but seems like overkill at this point
    std::string replacedDefines = "";
    replaceDefines(compileTimeDefines, replacedDefines);

    _vertShader = _fragShader = 0;

    if (vShaderByteArray)
    {
        if (!compileShader(&_vertShader, GL_VERTEX_SHADER, vShaderByteArray, compileTimeHeaders, replacedDefines))
        {
            CCLOG("cocos2d: ERROR: Failed to compile vertex shader");
            return false;
        }
    }

    // Create and compile fragment shader
    if (fShaderByteArray)
    {
        if (!compileShader(&_fragShader, GL_FRAGMENT_SHADER, fShaderByteArray, compileTimeHeaders, replacedDefines))
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

    clearHashUniforms();

    CHECK_GL_ERROR_DEBUG();

    return true;
}

bool GLProgram::initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename)
{
    return initWithFilenames(vShaderFilename, fShaderFilename, EMPTY_DEFINE);
}

bool GLProgram::initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeDefines)
{
    return initWithFilenames(vShaderFilename, fShaderFilename, EMPTY_DEFINE, compileTimeDefines);
}

bool GLProgram::initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename, const std::string& compileTimeHeaders, const std::string& compileTimeDefines)
{
    auto fileUtils = FileUtils::getInstance();
    std::string vertexSource = fileUtils->getStringFromFile(FileUtils::getInstance()->fullPathForFilename(vShaderFilename));
    std::string fragmentSource = fileUtils->getStringFromFile(FileUtils::getInstance()->fullPathForFilename(fShaderFilename));

    return initWithByteArrays(vertexSource.c_str(), fragmentSource.c_str(), compileTimeHeaders, compileTimeDefines);
}

void GLProgram::bindPredefinedVertexAttribs()
{
    static const struct {
        const char *attributeName;
        int location;
    } attribute_locations[] =
    {
        {GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION},
        {GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR},
        {GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD},
        {GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1},
        {GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2},
        {GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3},
        {GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL},
    };

    const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);

    for(int i=0; i<size;i++) {
        glBindAttribLocation(_program, attribute_locations[i].location, attribute_locations[i].attributeName);
    }
}

void GLProgram::parseVertexAttribs()
{
    //_vertexAttribs.clear();

    // Query and store vertex attribute meta-data from the program.
    GLint activeAttributes;
    GLint length;
    glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
    if(activeAttributes > 0)
    {
        VertexAttrib attribute;

        glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
        if(length > 0)
        {
            GLchar* attribName = (GLchar*) alloca(length + 1);

            for(int i = 0; i < activeAttributes; ++i)
            {
                // Query attribute info.
                glGetActiveAttrib(_program, i, length, nullptr, &attribute.size, &attribute.type, attribName);
                attribName[length] = '\0';
                attribute.name = std::string(attribName);

                // Query the pre-assigned attribute location
                attribute.index = glGetAttribLocation(_program, attribName);
                _vertexAttribs[attribute.name] = attribute;
            }
        }
    }
    else
    {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(_program, sizeof(ErrorLog), nullptr, ErrorLog);
        CCLOG("Error linking shader program: '%s'\n", ErrorLog);
    }
}

void GLProgram::parseUniforms()
{
    //_userUniforms.clear();

    // Query and store uniforms from the program.
    GLint activeUniforms;
    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &activeUniforms);
    if(activeUniforms > 0)
    {
        GLint length;
        glGetProgramiv(_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
        if(length > 0)
        {
            Uniform uniform;

            GLchar* uniformName = (GLchar*)alloca(length + 1);

            for(int i = 0; i < activeUniforms; ++i)
            {
                // Query uniform info.
                glGetActiveUniform(_program, i, length, nullptr, &uniform.size, &uniform.type, uniformName);
                uniformName[length] = '\0';

                // Only add uniforms that are not built-in.
                // The ones that start with 'CC_' are built-ins
                if(strncmp("CC_", uniformName, 3) != 0) {

                    // remove possible array '[]' from uniform name
                    if(length > 3)
                    {
                        char* c = strrchr(uniformName, '[');
                        if(c)
                        {
                            *c = '\0';
                        }
                    }
                    uniform.name = std::string(uniformName);
                    uniform.location = glGetUniformLocation(_program, uniformName);
                    GLenum __gl_error_code = glGetError();
                    if (__gl_error_code != GL_NO_ERROR)
                    {
                        CCLOG("error: 0x%x  uniformName: %s", (int)__gl_error_code, uniformName);
                    }
                    assert(__gl_error_code == GL_NO_ERROR);

                    _userUniforms[uniform.name] = uniform;
                }
            }
        }
    }
    else
    {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(_program, sizeof(ErrorLog), nullptr, ErrorLog);
        CCLOG("Error linking shader program: '%s'\n", ErrorLog);

    }

}

Uniform* GLProgram::getUniform(const std::string &name)
{
    const auto itr = _userUniforms.find(name);
    if( itr != _userUniforms.end())
        return &itr->second;
    return nullptr;
}

VertexAttrib* GLProgram::getVertexAttrib(const std::string &name)
{
    const auto itr = _vertexAttribs.find(name);
    if( itr != _vertexAttribs.end())
        return &itr->second;
    return nullptr;
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
    return compileShader(shader, type, source, "");
}

bool GLProgram::compileShader(GLuint* shader, GLenum type, const GLchar* source, const std::string& convertedDefines)
{
    return compileShader(shader, type, source, "", convertedDefines);
}

bool GLProgram::compileShader(GLuint * shader, GLenum type, const GLchar* source, const std::string& compileTimeHeaders, const std::string& convertedDefines)
{
    GLint status;

    if (!source)
    {
        return false;
    }

    std::string headersDef;
    if (compileTimeHeaders.empty()) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
        headersDef = (type == GL_VERTEX_SHADER ? "precision mediump float;\n precision mediump int;\n" : "precision mediump float;\n precision mediump int;\n");
// Bugfix to make shader variables types constant to be understood by the current Android Virtual Devices or Emulators. This will also eliminate the 0x501 and 0x502 OpenGL Errors during emulation.
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        headersDef = "#version 100\n precision mediump float;\n precision mediump int;\n";
#elif (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_LINUX && CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
        headersDef = (type == GL_VERTEX_SHADER ? "precision highp float;\n precision highp int;\n" : "precision mediump float;\n precision mediump int;\n");
#endif
    }else{
        headersDef = compileTimeHeaders;
    }

    const GLchar *sources[] = {
        headersDef.c_str(),
        COCOS2D_SHADER_UNIFORMS,
        convertedDefines.c_str(),
        source};

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

        return false;
    }

    return (status == GL_TRUE);
}

GLint GLProgram::getAttribLocation(const std::string &attributeName) const
{
    return glGetAttribLocation(_program, attributeName.c_str());
}

GLint GLProgram::getUniformLocation(const std::string &attributeName) const
{
    return glGetUniformLocation(_program, attributeName.c_str());
}

void GLProgram::bindAttribLocation(const std::string &attributeName, GLuint index) const
{
    glBindAttribLocation(_program, index, attributeName.c_str());
}

void GLProgram::updateUniforms()
{
    _builtInUniforms[UNIFORM_AMBIENT_COLOR] = glGetUniformLocation(_program, UNIFORM_NAME_AMBIENT_COLOR);
    _builtInUniforms[UNIFORM_P_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_P_MATRIX);
    _builtInUniforms[UNIFORM_MULTIVIEW_P_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MULTIVIEW_P_MATRIX);
    _builtInUniforms[UNIFORM_MV_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MV_MATRIX);
    _builtInUniforms[UNIFORM_MVP_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MVP_MATRIX);
    _builtInUniforms[UNIFORM_MULTIVIEW_MVP_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MULTIVIEW_MVP_MATRIX);
    _builtInUniforms[UNIFORM_NORMAL_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_NORMAL_MATRIX);

    _builtInUniforms[UNIFORM_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_TIME);
    _builtInUniforms[UNIFORM_SIN_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_SIN_TIME);
    _builtInUniforms[UNIFORM_COS_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_COS_TIME);

    _builtInUniforms[UNIFORM_RANDOM01] = glGetUniformLocation(_program, UNIFORM_NAME_RANDOM01);

    _builtInUniforms[UNIFORM_SAMPLER0] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER0);
    _builtInUniforms[UNIFORM_SAMPLER1] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER1);
    _builtInUniforms[UNIFORM_SAMPLER2] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER2);
    _builtInUniforms[UNIFORM_SAMPLER3] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER3);

    _flags.usesP = _builtInUniforms[UNIFORM_P_MATRIX] != -1;
    _flags.usesMultiViewP = _builtInUniforms[UNIFORM_MULTIVIEW_P_MATRIX] != -1;
    _flags.usesMV = _builtInUniforms[UNIFORM_MV_MATRIX] != -1;
    _flags.usesMVP = _builtInUniforms[UNIFORM_MVP_MATRIX] != -1;
    _flags.usesMultiViewMVP = _builtInUniforms[UNIFORM_MULTIVIEW_MVP_MATRIX] != -1;
    _flags.usesNormal = _builtInUniforms[UNIFORM_NORMAL_MATRIX] != -1;
    _flags.usesTime = (
                       _builtInUniforms[UNIFORM_TIME] != -1 ||
                       _builtInUniforms[UNIFORM_SIN_TIME] != -1 ||
                       _builtInUniforms[UNIFORM_COS_TIME] != -1
                       );
    _flags.usesRandom = _builtInUniforms[UNIFORM_RANDOM01] != -1;

    this->use();

    // Since sample most probably won't change, set it to 0,1,2,3 now.
    if(_builtInUniforms[UNIFORM_SAMPLER0] != -1)
       setUniformLocationWith1i(_builtInUniforms[UNIFORM_SAMPLER0], 0);
    if(_builtInUniforms[UNIFORM_SAMPLER1] != -1)
        setUniformLocationWith1i(_builtInUniforms[UNIFORM_SAMPLER1], 1);
    if(_builtInUniforms[UNIFORM_SAMPLER2] != -1)
        setUniformLocationWith1i(_builtInUniforms[UNIFORM_SAMPLER2], 2);
    if(_builtInUniforms[UNIFORM_SAMPLER3] != -1)
        setUniformLocationWith1i(_builtInUniforms[UNIFORM_SAMPLER3], 3);

    // clear any glErrors created by any not found uniforms
    glGetError();
}

bool GLProgram::link()
{
    CCASSERT(_program != 0, "Cannot link invalid program");

    GLint status = GL_TRUE;

    bindPredefinedVertexAttribs();

    glLinkProgram(_program);

    // Calling glGetProgramiv(...GL_LINK_STATUS...) will force linking of the program at this moment.
    // Otherwise, they might be linked when they are used for the first time. (I guess this depends on the driver implementation)
    // So it might slow down the "booting" process on certain devices. But, on the other hand it is important to know if the shader
    // linked successfully. Some shaders might be downloaded in runtime so, release version should have this check.
    // For more info, see Github issue #16231
    glGetProgramiv(_program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        CCLOG("cocos2d: ERROR: Failed to link program: %i", _program);
        glDeleteProgram(_program);
        _program = 0;
    }
    else
    {
        parseVertexAttribs();
        parseUniforms();

        clearShader();
    }

    return (status == GL_TRUE);
}

void GLProgram::use()
{
    glUseProgram(_program);
}

static std::string logForOpenGLShader(GLuint shader)
{
    GLint logLength = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength < 1)
        return "";

    char *logBytes = (char*)malloc(sizeof(char) * logLength);
    glGetShaderInfoLog(shader, logLength, nullptr, logBytes);
    std::string ret(logBytes);

    free(logBytes);
    return ret;
}

static std::string logForOpenGLProgram(GLuint program)
{
    GLint logLength = 0;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength < 1)
        return "";

    char *logBytes = (char*)malloc(sizeof(char) * logLength);
    glGetProgramInfoLog(program, logLength, nullptr, logBytes);
    std::string ret(logBytes);

    free(logBytes);
    return ret;
}

std::string GLProgram::getVertexShaderLog() const
{
    return cocos2d::logForOpenGLShader(_vertShader);
}

std::string GLProgram::getFragmentShaderLog() const
{
    return cocos2d::logForOpenGLShader(_fragShader);
}

std::string GLProgram::getProgramLog() const
{
    return logForOpenGLProgram(_program);
}

// Uniform cache

bool GLProgram::updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes)
{
    if (location < 0)
    {
        return false;
    }

    bool updated = true;

    auto element = _hashForUniforms.find(location);
    if (element == _hashForUniforms.end())
    {
        GLvoid* value = malloc(bytes);
        memcpy(value, data, bytes );
        _hashForUniforms.emplace(location, std::make_pair(value, bytes));
    }
    else
    {
        if (element->second.second < bytes)
        {
            GLvoid* value = realloc(element->second.first, bytes);
            memcpy(value, data, bytes);
            _hashForUniforms[location] = std::make_pair(value, bytes);
        }
        else
        {
            if (memcmp(element->second.first, data, bytes) == 0)
            {
                updated = false;
            }
            else
                memcpy(element->second.first, data, bytes);
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
    bool updated = updateUniformLocation(location, &i1, sizeof(i1)*1);

    if (updated)
    {
        glUniform1i( (GLint)location, i1);
    }
}

void GLProgram::setUniformLocationWith2i(GLint location, GLint i1, GLint i2)
{
    GLint ints[2] = {i1,i2};
    bool updated = updateUniformLocation(location, ints, sizeof(ints));

    if (updated)
    {
        glUniform2i( (GLint)location, i1, i2);
    }
}

void GLProgram::setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3)
{
    GLint ints[3] = {i1,i2,i3};
    bool updated = updateUniformLocation(location, ints, sizeof(ints));

    if (updated)
    {
        glUniform3i( (GLint)location, i1, i2, i3);
    }
}

void GLProgram::setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4)
{
    GLint ints[4] = {i1,i2,i3,i4};
    bool updated = updateUniformLocation(location, ints, sizeof(ints));

    if (updated)
    {
        glUniform4i( (GLint)location, i1, i2, i3, i4);
    }
}

void GLProgram::setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
    bool updated = updateUniformLocation(location, ints, sizeof(int)*2*numberOfArrays);

    if (updated)
    {
        glUniform2iv( (GLint)location, (GLsizei)numberOfArrays, ints );
    }
}

void GLProgram::setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
    bool updated = updateUniformLocation(location, ints, sizeof(int)*3*numberOfArrays);

    if (updated)
    {
        glUniform3iv( (GLint)location, (GLsizei)numberOfArrays, ints );
    }
}

void GLProgram::setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
    bool updated = updateUniformLocation(location, ints, sizeof(int)*4*numberOfArrays);

    if (updated)
    {
        glUniform4iv( (GLint)location, (GLsizei)numberOfArrays, ints );
    }
}

void GLProgram::setUniformLocationWith1f(GLint location, GLfloat f1)
{
    bool updated = updateUniformLocation(location, &f1, sizeof(f1)*1);

    if (updated)
    {
        glUniform1f( (GLint)location, f1);
    }
}

void GLProgram::setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2)
{
    GLfloat floats[2] = {f1,f2};
    bool updated =  updateUniformLocation(location, floats, sizeof(floats));

    if (updated)
    {
        glUniform2f( (GLint)location, f1, f2);
    }
}

void GLProgram::setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3)
{
    GLfloat floats[3] = {f1,f2,f3};
    bool updated = updateUniformLocation(location, floats, sizeof(floats));

    if (updated)
    {
        glUniform3f( (GLint)location, f1, f2, f3);
    }
}

void GLProgram::setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    GLfloat floats[4] = {f1,f2,f3,f4};
    bool updated = updateUniformLocation(location, floats, sizeof(floats));

    if (updated)
    {
        glUniform4f( (GLint)location, f1, f2, f3,f4);
    }
}


void GLProgram::setUniformLocationWith1fv( GLint location, const GLfloat* floats, unsigned int numberOfArrays )
{
    bool updated = updateUniformLocation(location, floats, sizeof(float)*numberOfArrays);

    if (updated)
    {
        glUniform1fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
    bool updated = updateUniformLocation(location, floats, sizeof(float)*2*numberOfArrays);

    if (updated)
    {
        glUniform2fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
    bool updated = updateUniformLocation(location, floats, sizeof(float)*3*numberOfArrays);

    if (updated)
    {
        glUniform3fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
    bool updated = updateUniformLocation(location, floats, sizeof(float)*4*numberOfArrays);

    if (updated)
    {
        glUniform4fv( (GLint)location, (GLsizei)numberOfArrays, floats );
    }
}

void GLProgram::setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices) {
    bool updated = updateUniformLocation(location, matrixArray, sizeof(float)*4*numberOfMatrices);

    if (updated)
    {
        glUniformMatrix2fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}

void GLProgram::setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices) {
    bool updated = updateUniformLocation(location, matrixArray, sizeof(float)*9*numberOfMatrices);

    if (updated)
    {
        glUniformMatrix3fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}


void GLProgram::setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
    bool updated = updateUniformLocation(location, matrixArray, sizeof(float)*16*numberOfMatrices);

    if (updated)
    {
        glUniformMatrix4fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
    }
}

void GLProgram::setUniformsForBuiltins()
{
    setUniformsForBuiltins(_director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW));
}

void GLProgram::setUniformsForBuiltins(const Mat4 &matrixMV)
{
    const auto& matrixP = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    if (_flags.usesP)
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_P_MATRIX], matrixP.m, 1);

    if (_flags.usesMultiViewP)
    {
        Mat4 mats[4];
        const auto stackSize = std::min<size_t>(_director->getProjectionMatrixStackSize(), 4);
        for (size_t i = 0; i < stackSize; ++i) {
            mats[i] = _director->getProjectionMatrix(i);
        }
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_MULTIVIEW_P_MATRIX], mats[0].m, 4);
    }

    if (_flags.usesMV)
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_MV_MATRIX], matrixMV.m, 1);

    if (_flags.usesMVP)
    {
        Mat4 matrixMVP = matrixP * matrixMV;
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_MVP_MATRIX], matrixMVP.m, 1);
    }

    if (_flags.usesMultiViewMVP)
    {
        Mat4 mats[4];
        const auto stackSize = std::min<size_t>(_director->getProjectionMatrixStackSize(), 4);
        for (size_t i = 0; i < stackSize; ++i) {
            mats[i] = _director->getProjectionMatrix(i) * matrixMV;
        }
        setUniformLocationWithMatrix4fv(_builtInUniforms[UNIFORM_MULTIVIEW_MVP_MATRIX], mats[0].m, 4);
    }

    if (_flags.usesNormal)
    {
        Mat4 mvInverse = matrixMV;
        mvInverse.m[12] = mvInverse.m[13] = mvInverse.m[14] = 0.0f;
        mvInverse.inverse();
        mvInverse.transpose();
        GLfloat normalMat[9];
        normalMat[0] = mvInverse.m[0];normalMat[1] = mvInverse.m[1];normalMat[2] = mvInverse.m[2];
        normalMat[3] = mvInverse.m[4];normalMat[4] = mvInverse.m[5];normalMat[5] = mvInverse.m[6];
        normalMat[6] = mvInverse.m[8];normalMat[7] = mvInverse.m[9];normalMat[8] = mvInverse.m[10];
        setUniformLocationWithMatrix3fv(_builtInUniforms[UNIFORM_NORMAL_MATRIX], normalMat, 1);
    }

    if (_flags.usesTime) {
        // This doesn't give the most accurate global time value.
        // Cocos2D doesn't store a high precision time value, so this will have to do.
        // Getting Mach time per frame per shader using time could be extremely expensive.
        float time = _director->getTotalFrames() * _director->getAnimationInterval();

        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_TIME], time/10.0f, time, time*2, time*4);
        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_SIN_TIME], time/8.0f, time/4.0f, time/2.0f, sinf(time));
        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_COS_TIME], time/8.0f, time/4.0f, time/2.0f, cosf(time));
    }

    if (_flags.usesRandom)
        setUniformLocationWith4f(_builtInUniforms[GLProgram::UNIFORM_RANDOM01], CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
}

void GLProgram::reset()
{
    _vertShader = _fragShader = 0;
    memset(_builtInUniforms, 0, sizeof(_builtInUniforms));


    // it is already deallocated by android
    //GL::deleteProgram(_program);
    _program = 0;

    clearHashUniforms();
}

inline void GLProgram::clearShader()
{
    if (_vertShader)
    {
        glDeleteShader(_vertShader);
    }

    if (_fragShader)
    {
        glDeleteShader(_fragShader);
    }

    _vertShader = _fragShader = 0;
}

inline void GLProgram::clearHashUniforms()
{
    for (auto e: _hashForUniforms)
    {
        free(e.second.first);
    }

    _hashForUniforms.clear();
}

NS_CC_END
