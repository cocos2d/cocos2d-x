#include "Base.h"
#include "C3DEffect.h"
#include "C3DStream.h"
#include "C3DTexture.h"
#include "C3DSampler.h"
#include "C3DRenderState.h"
#include "C3DElementNode.h"

#define OPENGL_ES_DEFINE  "#define OPENGL_ES"

namespace cocos3d
{

static C3DEffect* __currentEffect = NULL;

C3DEffect::C3DEffect(const std::string& name) : C3DResource(name),_program(0)
{
}

C3DEffect::~C3DEffect()
{
    // Free uniforms.
    for (std::map<std::string, Uniform*>::iterator itr = _uniforms.begin(); itr != _uniforms.end(); itr++)
    {
        SAFE_DELETE(itr->second);
    }

    if (_program)
    {
        // If our program object is currently bound, unbind it before we're destroyed.
        if (__currentEffect == this)
        {
            GL_ASSERT( glUseProgram(0) );
            __currentEffect = NULL;
        }

        GL_ASSERT( glDeleteProgram(_program) );
        _program = 0;
    }
}


bool C3DEffect::load(C3DElementNode* node)
{
	C3DResource::load(node);

	const char* vshPath = node->getElement("vertexShader");
	const char* fshPath = node->getElement("fragmentShader");
	const char* defines = node->getElement("defines");

	_vshPath = (vshPath == NULL) ? "" : vshPath ;
	_fshPath = (fshPath == NULL) ? "" : fshPath ;
	_defines = (defines == NULL) ? "" : defines ;


    // Read source from file.
	char* vshSource = C3DStreamManager::readAll(vshPath);
    if (vshSource == NULL)
    {  
		return false;
    }
	char* fshSource = C3DStreamManager::readAll(fshPath);
    if (fshSource == NULL)
    {
        SAFE_DELETE_ARRAY(vshSource);    
		return false;
    }
    
    if(this->load(vshSource,fshSource,defines) == false)
	{
		LOG_ERROR_VARG("Failed to create effect from shaders: %s, %s", _vshPath.c_str(), _fshPath.c_str());
	}
	
    SAFE_DELETE_ARRAY(vshSource);
    SAFE_DELETE_ARRAY(fshSource);
	
    return true;
}


bool C3DEffect::load(const char* vshSource, const char* fshSource, const char* defines)
{
    const unsigned int SHADER_SOURCE_LENGTH = 3;
    const GLchar* shaderSource[SHADER_SOURCE_LENGTH];
    char* infoLog = NULL;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
    GLint length;
    GLint success;

    // Compile vertex shader.
    std::string definesStr = (defines == NULL) ? "" : defines;
#ifdef OPENGL_ES
    if (defines && strlen(defines) != 0)
        definesStr += "\n";
    definesStr+= OPENGL_ES_DEFINE;
#endif
    shaderSource[0] = definesStr.c_str();
    shaderSource[1] = "\n";
    shaderSource[2] = vshSource;
    GL_ASSERT( vertexShader = glCreateShader(GL_VERTEX_SHADER) );
    GL_ASSERT( glShaderSource(vertexShader, SHADER_SOURCE_LENGTH, shaderSource, NULL) );
    GL_ASSERT( glCompileShader(vertexShader) );
    GL_ASSERT( glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success) );
    if (success != GL_TRUE)
    {
        GL_ASSERT( glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length) );
        if (length > 0)
        {
            infoLog = new char[length];
            GL_ASSERT( glGetShaderInfoLog(vertexShader, length, NULL, infoLog) );
            infoLog[length-1] = '\0';
        }
        LOG_ERROR_VARG("Compile failed for vertex shader (%s): %s", _vshPath.c_str() == NULL ? "NULL" : _vshPath.c_str(), infoLog == NULL ? "" : infoLog);
        SAFE_DELETE_ARRAY(infoLog);

        // Clean up.
        GL_ASSERT( glDeleteShader(vertexShader) );

        return false;
    }

    // Compile the fragment shader.
    definesStr = (defines == NULL) ? "" : defines;
#ifdef OPENGL_ES
    if (defines && strlen(defines) != 0)
        definesStr += "\n";
    definesStr+= OPENGL_ES_DEFINE;
#endif
    shaderSource[0] = definesStr.c_str();
    shaderSource[1] = "\n";
    shaderSource[2] = fshSource;
    GL_ASSERT( fragmentShader = glCreateShader(GL_FRAGMENT_SHADER) );
    GL_ASSERT( glShaderSource(fragmentShader, SHADER_SOURCE_LENGTH, shaderSource, NULL) );
    GL_ASSERT( glCompileShader(fragmentShader) );
    GL_ASSERT( glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success) );
    if (success != GL_TRUE)
    {
        GL_ASSERT( glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length) );
        if (length > 0)
        {
            infoLog = new char[length];
            GL_ASSERT( glGetShaderInfoLog(fragmentShader, length, NULL, infoLog) );
            infoLog[length-1] = '\0';
        }
        LOG_ERROR_VARG("Compile failed for fragment shader (%s): %s", _fshPath.c_str() == NULL ? "NULL" : _fshPath.c_str(), infoLog == NULL ? "" : infoLog);
        SAFE_DELETE_ARRAY(infoLog);

        // Clean up.
        GL_ASSERT( glDeleteShader(vertexShader) );
        GL_ASSERT( glDeleteShader(fragmentShader) );

        return false;
    }

    // Link program.
    GL_ASSERT( program = glCreateProgram() );
    GL_ASSERT( glAttachShader(program, vertexShader) );
    GL_ASSERT( glAttachShader(program, fragmentShader) );
    GL_ASSERT( glLinkProgram(program) );
    GL_ASSERT( glGetProgramiv(program, GL_LINK_STATUS, &success) );

    // Delete shaders after linking.
    GL_ASSERT( glDeleteShader(vertexShader) );
    GL_ASSERT( glDeleteShader(fragmentShader) );

    // Check link status.
    if (success != GL_TRUE)
    {
        GL_ASSERT( glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length) );
        if (length > 0)
        {
            infoLog = new char[length];
            GL_ASSERT( glGetProgramInfoLog(program, length, NULL, infoLog) );
            infoLog[length-1] = '\0';
        }
        LOG_ERROR_VARG("Linking program failed (%s,%s): %s", _vshPath.c_str() == NULL ? "NULL" : _vshPath.c_str(), _fshPath.c_str() == NULL ? "NULL" : _fshPath.c_str(), infoLog == NULL ? "" : infoLog);
        SAFE_DELETE_ARRAY(infoLog);

        // Clean up.
        GL_ASSERT( glDeleteProgram(program) );

        return false;
    }
	  
    this->_program = program;

    // Query and store vertex attribute meta-data from the program.
    // NOTE: Rather than using glBindAttribLocation to explicitly specify our own
    // preferred attribute locations, we're going to query the locations that were
    // automatically bound by the GPU. While it can sometimes be convenient to use
    // glBindAttribLocation, some vendors actually reserve certain attribute indices
    // and thereore using this function can create compatibility issues between
    // different hardware vendors.
    GLint activeAttributes;
    GL_ASSERT( glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttributes) );
    if (activeAttributes > 0)
    {
        GL_ASSERT( glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length) );
        if (length > 0)
        {
            GLchar* attribName = new GLchar[length + 1];
            GLint attribSize;
            GLenum attribType;
            GLint attribLocation;
            for (int i = 0; i < activeAttributes; ++i)
            {
                // Query attribute info.
                GL_ASSERT( glGetActiveAttrib(program, i, length, NULL, &attribSize, &attribType, attribName) );
                attribName[length] = '\0';

                // Query the pre-assigned attribute location.
                GL_ASSERT( attribLocation = glGetAttribLocation(program, attribName) );

                // Assign the vertex attribute mapping for the effect.
                this->_vertexAttributes[attribName] = attribLocation;
            }
            SAFE_DELETE_ARRAY(attribName);
        }
    }

    // Query and store uniforms from the program.
    GLint activeUniforms;
    GL_ASSERT( glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms) );
    if (activeUniforms > 0)
    {
        GL_ASSERT( glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length) );
        if (length > 0)
        {
            GLchar* uniformName = new GLchar[length + 1];
            GLint uniformSize;
            GLenum uniformType;
            GLint uniformLocation;
            unsigned int samplerIndex = 0;
            for (int i = 0; i < activeUniforms; ++i)
            {
                // Query uniform info.
                GL_ASSERT( glGetActiveUniform(program, i, length, NULL, &uniformSize, &uniformType, uniformName) );
                uniformName[length] = '\0';  // null terminate
                if (uniformSize > 1 && length > 3)
                {
                    // This is an array uniform. I'm stripping array indexers off it since GL does not
                    // seem to be consistent across different drivers/implementations in how it returns
                    // array uniforms. On some systems it will return "u_matrixArray", while on others
                    // it will return "u_matrixArray[0]".
                    char* c = strrchr(uniformName, '[');
                    if (c)
                    {
                        *c = '\0';
                    }
                }

                // Query the pre-assigned uniform location.
                GL_ASSERT( uniformLocation = glGetUniformLocation(program, uniformName) );

                Uniform* uniform = new Uniform();
                uniform->_effect = this;
                uniform->_name = uniformName;
                uniform->_location = uniformLocation;
                uniform->_type = uniformType;
                uniform->_index = uniformType == GL_SAMPLER_2D ? (samplerIndex++) : 0;

                this->_uniforms[uniformName] = uniform;
            }
            SAFE_DELETE_ARRAY(uniformName);
        }
    }
    return true;
}


//const char* C3DEffect::getId() const
//{
//    return _id.c_str();
//}

VertexAttribute C3DEffect::getVertexAttribute(const char* name) const
{
    std::map<std::string, VertexAttribute>::const_iterator itr = _vertexAttributes.find(name);
    return (itr == _vertexAttributes.end() ? -1 : itr->second);
}

Uniform* C3DEffect::getUniform(const char* name) const
{
    std::map<std::string, Uniform*>::const_iterator itr = _uniforms.find(name);
    return (itr == _uniforms.end() ? NULL : itr->second);
}

Uniform* C3DEffect::getUniform(unsigned int index) const
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

unsigned int C3DEffect::getUniformCount() const
{
    return _uniforms.size();
}

void C3DEffect::bindValue(Uniform* uniform, float value)
{
    GL_ASSERT( glUniform1f(uniform->_location, value) );
}

void C3DEffect::bindValue(Uniform* uniform, const float* values, unsigned int count)
{
    GL_ASSERT( glUniform1fv(uniform->_location, count, values) );
}

void C3DEffect::bindValue(Uniform* uniform, int value)
{
    GL_ASSERT( glUniform1i(uniform->_location, value) );
}

void C3DEffect::bindValue(Uniform* uniform, const int* values, unsigned int count)
{
    GL_ASSERT( glUniform1iv(uniform->_location, count, values) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DMatrix& value)
{
    GL_ASSERT( glUniformMatrix4fv(uniform->_location, 1, GL_FALSE, value.m) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DMatrix* values, unsigned int count)
{
    GL_ASSERT( glUniformMatrix4fv(uniform->_location, count, GL_FALSE, (GLfloat*)values) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DVector2& value)
{
    GL_ASSERT( glUniform2f(uniform->_location, value.x, value.y) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DVector2* values, unsigned int count)
{
    GL_ASSERT( glUniform2fv(uniform->_location, count, (GLfloat*)values) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DVector3& value)
{
    GL_ASSERT( glUniform3f(uniform->_location, value.x, value.y, value.z) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DVector3* values, unsigned int count)
{
    GL_ASSERT( glUniform3fv(uniform->_location, count, (GLfloat*)values) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DVector4& value)
{
    GL_ASSERT( glUniform4f(uniform->_location, value.x, value.y, value.z, value.w) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DVector4* values, unsigned int count)
{
    GL_ASSERT( glUniform4fv(uniform->_location, count, (GLfloat*)values) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DSampler* sampler)
{
    assert(uniform->_type == GL_SAMPLER_2D);

    //GL_ASSERT( glActiveTexture(GL_TEXTURE0 + uniform->_index) );
    
    C3DRenderState::activeTexture(GL_TEXTURE0 + uniform->_index);

    // Bind the sampler - this binds the texture and applies sampler state
    const_cast<C3DSampler*>(sampler)->bind();

    GL_ASSERT( glUniform1i(uniform->_location, uniform->_index) );
}

void C3DEffect::bindValue(Uniform* uniform, const C3DTexture* texture)
{
	assert(uniform->_type == GL_SAMPLER_2D);

    //GL_ASSERT( glActiveTexture(GL_TEXTURE0 + uniform->_index) );
    
    C3DRenderState::activeTexture(GL_TEXTURE0 + uniform->_index);

    //binds the texture
	GL_ASSERT( glBindTexture(GL_TEXTURE_2D, texture->getHandle()) );
 

    GL_ASSERT( glUniform1i(uniform->_location, uniform->_index) );

}

void C3DEffect::bind()
{
    GL_ASSERT( glUseProgram(_program) );

    __currentEffect = this;
}

C3DEffect* C3DEffect::getCurrentEffect()
{
    return __currentEffect;
}

Uniform::Uniform() :
    _location(-1), _type(0), _index(0)
{
}

Uniform::Uniform(const Uniform& copy)
{
    // hidden
}

Uniform::~Uniform()
{
    // hidden
}

C3DEffect* Uniform::getEffect() const
{
    return _effect;
}

const char* Uniform::getName() const
{
    return _name.c_str();
}

const GLenum Uniform::getType() const
{
    return _type;
}

}
