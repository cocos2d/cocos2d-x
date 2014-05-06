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

#include "base/CCDirector.h"
#include "2d/CCGLProgram.h"
#include "2d/ccGLStateCache.h"
#include "base/ccMacros.h"
#include "2d/platform/CCFileUtils.h"
#include "2d/uthash.h"
#include "deprecated/CCString.h"
#include "CCGL.h"

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
,_isTight(false)
{
    memset(_uniforms, 0, sizeof(_uniforms));
    _programData = new GLProgramData();
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
    
    CC_SAFE_DELETE(_programData);
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

void GLProgram::setUniformsForUserDef()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
	Matrix matrixMV;
	matrixMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
	Matrix matrixP = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
	// Set Uniform value
    
    for(unsigned int i = 0, count = _programData->getUniformCount(); i < count; ++i)
    {
        _programData->getUniform(i)->_uniformvalue->bindUniform(this);
    }
}

void GLProgram::setAttribForUserDef()
{
    for(unsigned int i = 0, count = _programData->getAttribCount(); i < count; ++i)
    {
        GLProgramData::VertexAttrib* attrib = _programData->getAttrib(i);
        if(i == 0)
        {
            glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        }
        else if(attrib->_type == GL_FLOAT_VEC4)
        {
            glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
        }
        else if(attrib->_type == GL_FLOAT_VEC2)
        {
            glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        }
    }
}

// have some questions.
void GLProgram::setVertexAttrib(const GLvoid* vertex, bool isTight)
{
	static GLint vertexsize = 0;
    if(vertexsize == 0)
    {
        for(unsigned int i = 0, count = _programData->getAttribCount(); i < count; ++i)
        {
            GLProgramData::VertexAttrib* _attrib = _programData->getAttrib(i);
        
            if(_attrib->_type == GL_UNSIGNED_BYTE)
                vertexsize += _attrib->_size ;
            else
                vertexsize += _attrib->_size * 4;
        }
    }
    if(isTight)
        vertexsize = 0;
    
    size_t offset = 0;
	for(unsigned int i = 0, count = _programData->getAttribCount(); i < count; ++i)
	{
        
		GLProgramData::VertexAttrib* _attrib = _programData->getAttrib(i);
		std::string name = _attrib->_name;
		GLint size = _attrib->_size;
		GLenum type = _attrib->_type;
        bool normalized = GL_FALSE;
        
		glVertexAttribPointer(i, size, type, normalized, vertexsize, (size_t*)(vertex)+ offset);
        if(_attrib->_type != GL_UNSIGNED_BYTE)
            offset += size * 4 ;
        else
            offset += size;
	}
}

void GLProgram::autoParse()
{
	// Link	program
	GLint status = GL_TRUE;
	glLinkProgram(_program);
    
	// Delete shaders after linking
	if (_vertShader)
	{
		glDeleteShader(_vertShader);
	}
    
	if (_fragShader)
	{
		glDeleteShader(_fragShader);
	}
    
	_vertShader = _fragShader = 0;
    
	// Query and store vertex attribute meta-data from the program.
	GLint activeAttributes;
	GLint length;
	glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	if(activeAttributes > 0)
	{
		glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
		if(length > 0)
		{
			GLchar* attribName = new GLchar[length + 1];
			GLint attribSize;
			GLenum attribType;
			GLint attribLocation;
            GLint vertexsize = 0;
            
			for(int i = 0; i < activeAttributes; ++i)
			{
				// Query attribute info.
				glGetActiveAttrib(_program, i, length, NULL, &attribSize, &attribType, attribName);
				attribName[length] = '\0';
                
				// Query the pre-assigned attribute location
				attribLocation = glGetAttribLocation(_program, attribName);
				std::string name = attribName;
                
                GLuint size;
                switch (attribType) {
                    case GL_FLOAT:
                        size = 1;
                        attribType = GL_FLOAT;
                        break;
                    case GL_FLOAT_VEC2:
                        attribType = GL_FLOAT;
                        size = 2;
                        break;
                    case GL_FLOAT_VEC3:
                        attribType = GL_FLOAT;
                        size = 3;
                        break;
                    case GL_FLOAT_VEC4:
                        attribType = GL_FLOAT;
                            size = 4;
                        break;
                    case GL_FLOAT_MAT4:
                        attribType = GL_FLOAT;
                        size = 16;
                        break;
                    case GL_INT:
                        size = 1;
                        attribType = GL_INT;
                        break;
                    case GL_INT_VEC2:
                        size = 2;
                        attribType = GL_INT;
                        break;
                    case GL_INT_VEC3:
                        size = 3;
                        attribType = GL_INT;
                        break;
                    case GL_INT_VEC4:
                        size = 4;
                        attribType = GL_INT;
                        break;
                    default:
                        size = 1;
                        break;
                }
                
                GLProgramData::_VertexAttrib* attrib = new GLProgramData::_VertexAttrib();
                attrib->_name = name;
                attrib->_size = size;
                attrib->_type = attribType;
                attrib->_index = i;
                //vertexsize +=size;
                
				_programData->addAttrib(name, attrib);
                
				//_user_vertAttributes[attribName] = attribLocation;
            //    bindAttribLocation(attribName,attribLocation);
			}
			CC_SAFE_DELETE_ARRAY(attribName);
		}
	}

	// Query and store uniforms from the program.
	GLint activeUniforms;
	glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &activeUniforms);
	if(activeUniforms > 0)
	{
		glGetProgramiv(_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
		if(length > 0)
		{
			GLchar* uniformName = new char[length + 1];
			GLint uniformSize;
			GLenum uniformType;
			GLint uniformLocation;
            
			unsigned int  sampleIndex = 0;
			for(int i = 0; i < activeUniforms; ++i)
			{
				// Query uniform info.
				glGetActiveUniform(_program, i, length, NULL, &uniformSize, &uniformType, uniformName);
				uniformName[length] = '\0';
                
				if(uniformSize > 1 && length > 3)
				{
					char* c = strrchr(uniformName, '[');
					if(c)
					{
						*c = '\0';
					}
				}
                
				uniformLocation = glGetUniformLocation(_program, uniformName);
				//_user_uniforms[uniformName] = uniformLocation;
				std::string name = uniformName;
                GLProgramData::_Uniform* uniform = new GLProgramData::_Uniform();
                
                uniform->_location = uniformLocation;
                uniform->_name = uniformName;
                uniform->_size = uniformSize;
                uniform->_type = uniformType;
                
                UniformValue* uniformvalue = new UniformValue();
                uniform->_uniformvalue = uniformvalue;
                uniformvalue->init(uniform);
                
				_programData->addUniform(name, uniform);
			}
			CC_SAFE_DELETE_ARRAY(uniformName);
		}
	}
    
    for(unsigned int i = 0, count = _programData->getAttribCount(); i < count; ++i)
	{
		GLProgramData::VertexAttrib* _attrib = _programData->getAttrib(i);
		std::string name = _attrib->_name;
        GLint attribLocation = getAttribLocation(name.c_str());
        bindAttribLocation( name.c_str(),attribLocation);
	}
    
}

UniformValue* GLProgram::getUniform(std::string &name)
{
	GLProgramData::Uniform* uniform = _programData->getUniform(name);
	return uniform->_uniformvalue;
}

GLProgramData::VertexAttrib* GLProgram::getAttrib(std::string &name)
{
    GLProgramData::VertexAttrib* attrib = _programData->getAttrib(name);
    return attrib;
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




GLProgramData::GLProgramData():
_vertexsize(0)
{
	_uniforms.clear();
	_vertAttributes.clear();
}

GLProgramData::~GLProgramData()
{
	for(std::map<std::string, Uniform*>::iterator itr = _uniforms.begin(); itr != _uniforms.end(); itr++)
	{
		CC_SAFE_DELETE(itr->second);
	}
	
	for(std::map<std::string, VertexAttrib*>::iterator itr = _vertAttributes.begin(); itr != _vertAttributes.end(); itr++)
	{
		CC_SAFE_DELETE(itr->second);
	}
}

void GLProgramData::addUniform(std::string &name, Uniform* uniform)
{
	_uniforms[name] = uniform;
}

void GLProgramData::addAttrib(std::string &name, VertexAttrib* attrib)
{
	_vertAttributes[name] = attrib;
}

GLProgramData::Uniform* GLProgramData::getUniform(unsigned int index)
{
	unsigned int i = 0;
	for (std::map<std::string, Uniform*>::const_iterator itr = _uniforms.begin(); itr != _uniforms.end(); itr++, i++)
	{
		if (i == index)
		{
			return itr->second;
		}
	}
	return NULL;
}

GLProgramData::Uniform* GLProgramData::getUniform(std::string& name)
{
	std::map<std::string, Uniform*>::const_iterator itr = _uniforms.find(name);
	if(itr != _uniforms.end())
		return itr->second;
	else
		return NULL;
}

GLProgramData::VertexAttrib* GLProgramData::getAttrib(unsigned int index)
{
	//unsigned int i = 0;
	for (std::map<std::string, VertexAttrib*>::const_iterator itr = _vertAttributes.begin(); itr != _vertAttributes.end(); itr++)
	{
		if (itr->second->_index == index)
		{
			return itr->second;
		}
	}
	return NULL;
}

GLProgramData::VertexAttrib* GLProgramData::getAttrib(std::string& name)
{
    std::map<std::string, VertexAttrib*>::const_iterator itr = _vertAttributes.find(name);
	if(itr != _vertAttributes.end())
		return itr->second;
	else
		return NULL;
}

unsigned int GLProgramData::getUniformCount()
{
	return _uniforms.size();
}

unsigned int GLProgramData::getAttribCount()
{
	return _vertAttributes.size();
}


UniformValue::UniformValue(): _count(0),_type(UniformValue::NONE),_update(false)
{
    
}

UniformValue::~UniformValue()
{
	resetValue();
}

bool UniformValue::init(GLProgramData::Uniform* uniform)
{
	resetValue();
	_uniform = uniform;
	return true;
}

void UniformValue::bindUniform(GLProgram* program)
{
	switch(_type){
		case UniformValue::FLOAT:
            program->setUniformLocationWith1f(_uniform->_location, *_value.floatPtrValue);
			break;
		case UniformValue::INT:
            program->setUniformLocationWith1i(_uniform->_location, *_value.intPtrValue);
			break;
		case UniformValue::VECTOR2:
            program->setUniformLocationWith2f(_uniform->_location, _value.vec2PtrValue->x,  _value.vec2PtrValue->y);
			break;
		case UniformValue::VECTOR3:
            program->setUniformLocationWith3f(_uniform->_location, _value.vec3PtrValue->x,  _value.vec3PtrValue->y, _value.vec3PtrValue->z);
			break;
		case UniformValue::VECTOR4:
            program->setUniformLocationWith4f(_uniform->_location, _value.vec4PtrValue->x,  _value.vec4PtrValue->y, _value.vec4PtrValue->z, _value.vec4PtrValue->w);
			break;
		case UniformValue::MATRIX:
            program->setUniformLocationWithMatrix4fv(_uniform->_location, _value.matPtrValue->m, _count);
			break;
		default:
			break;
	}
}

bool UniformValue::setValue(float value)
{
    _update = false;
    if(*(_value.floatPtrValue) == value)
        return true;
    
	if(_uniform && _uniform->_type == GL_FLOAT)
	{
		_count = 1;
		_type = UniformValue::FLOAT;
		if(_value.floatPtrValue == nullptr)
			_value.floatPtrValue = new float[_count];
		
		*(_value.floatPtrValue) = value;
        _update = true;
		return true;
	}
	return false;
}

bool UniformValue::setValue(int value)
{
    _update = false;
    if(_value.intPtrValue != nullptr)
        if(*(_value.intPtrValue) == value)
            return true;
    
	if(_uniform && _uniform->_type == GL_INT)
	{
		_count = 1;
		_type = UniformValue::INT;
		if(_value.floatPtrValue == nullptr)
			_value.floatPtrValue = new float[_count];
        
		*(_value.floatPtrValue) = value;
        _update = true;
		return true;
	}
	return false;
}

bool UniformValue::setValue(const Vector2& value)
{
    _update = false;
    if(_value.vec2PtrValue != nullptr)
        if(*(_value.vec2PtrValue) == value)
            return true;
    
	if(_uniform && _uniform->_type == GL_FLOAT_VEC2)
	{
		_count = 1;
		_type = UniformValue::VECTOR2;
		if(_value.vec2PtrValue == nullptr)
			_value.vec2PtrValue = new Vector2[_count];
        
		*(_value.vec2PtrValue) = value;
		return true;
	}
	return false;
}

bool UniformValue::setValue(const Vector3& value)
{
    _update = false;
    if(_value.vec3PtrValue != nullptr)
        if(*(_value.vec3PtrValue) == value)
            return true;
    
	if(_uniform && _uniform->_type == GL_FLOAT_VEC3)
	{
		_count = 1;
		_type = UniformValue::VECTOR3;
		if(_value.vec3PtrValue == nullptr)
			_value.vec3PtrValue = new Vector3[_count];
        
		*(_value.vec3PtrValue) = value;
		return true;
	}
	return false;
}

bool UniformValue::setValue(const Vector4& value)
{
    _update = false;
    if(_value.vec4PtrValue != nullptr)
        if(*(_value.vec4PtrValue) == value)
            return true;
    
	if(_uniform && _uniform->_type == GL_FLOAT_VEC4)
	{
		_count = 1;
		_type = UniformValue::VECTOR4;
		if(_value.vec4PtrValue == nullptr)
			_value.vec4PtrValue = new Vector4[_count];
        
		*(_value.vec4PtrValue) = value;
		return true;
	}
	return false;
}

bool UniformValue::setValue(const Matrix& value)
{
    _update = false;
    //  if(_value.matPtrValue != nullptr)
    //     if(*(_value.matPtrValue) == value)
    //        return true;
    
	if(_uniform && _uniform->_type == GL_FLOAT_MAT4)
	{
		_count = 1;
		_type = UniformValue::MATRIX;
		if(_value.matPtrValue == nullptr)
			_value.matPtrValue = new Matrix[_count];
        
		*(_value.matPtrValue) = value;
		return true;
	}
	return false;
}

void UniformValue::resetValue()
{
	switch(_type)
	{
        case UniformValue::FLOAT :
            CC_SAFE_DELETE(_value.floatPtrValue);
            break;
        case UniformValue::INT:
            CC_SAFE_DELETE(_value.intPtrValue);
            break;
        case UniformValue::VECTOR2:
            CC_SAFE_DELETE(_value.vec2PtrValue);
            break;
        case UniformValue::VECTOR3:
            CC_SAFE_DELETE(_value.vec3PtrValue);
            break;
        case UniformValue::VECTOR4:
            CC_SAFE_DELETE(_value.vec4PtrValue);
            break;
        case UniformValue::MATRIX:
            CC_SAFE_DELETE(_value.matPtrValue);
            break;
        default:
            break;
	}
    
	memset(&_value,0, sizeof(_value));
	_count = 0;
	_type = UniformValue::NONE;
}

NS_CC_END
