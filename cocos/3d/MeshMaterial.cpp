#include "MeshMaterial.h"
#include "Mesh.h"
#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "cocos2d.h"
#include "CCMath.h"
#define STRINGIFY(A)  #A
//#include "../Shaders/TexturedLighting.es2.vert.h"
#include "Textured.es2.vert.h"
#include "Textured.es2.frag.h"
#include "Colored.es2.frag.h"

#ifdef NDEBUG
#define GL_ASSERT( gl_code ) gl_code
#else
#define GL_ASSERT( gl_code ) \
{ \
gl_code; \
__gl_error_code = glGetError(); \
if (__gl_error_code != GL_NO_ERROR) \
{ \
LOG_ERROR_VARG(#gl_code ": 0x%x", (int)__gl_error_code); \
} \
assert(__gl_error_code == GL_NO_ERROR); \
}
#endif

USING_NS_CC_MATH;

NS_CC_BEGIN

static const char* s_shaderSampler = "CC_Texture0";
static const char* s_destColor = "u_color";

const char* s_attribute_Normal_Name = "a_normal";
int s_attribute_Normal = GLProgram::VERTEX_ATTRIB_MAX;

static int s_attributeCount = GLProgram::VERTEX_ATTRIB_MAX + 1;

GLProgram* VertexDeclaration::s_defProgramTex = nullptr;
GLProgram* VertexDeclaration::s_defProgram = nullptr;

static std::vector<VertexDeclaration*> s_cachedVertexDecl;

VertexDeclaration::VertexDeclaration(): _mesh(nullptr), _program(nullptr), _attribFlag(0), _vao(0)
{
    _attributes = new VertexDeclaration::VertexAttribute[s_attributeCount];
}

VertexDeclaration::~VertexDeclaration()
{
    for (auto it = s_cachedVertexDecl.begin(); it != s_cachedVertexDecl.end(); it++) {
        if ((*it) == this)
        {
            s_cachedVertexDecl.erase(it);
        }
    }
    CC_SAFE_RELEASE_NULL(_mesh);
    delete[] _attributes;
    CC_SAFE_RELEASE_NULL(_program);
    if (_vao)
    {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
    
    for (auto it = _uniforms.begin(); it != _uniforms.end(); it++) {
        delete it->second;
    }
    _uniforms.clear();
}

VertexDeclaration* VertexDeclaration::create(Mesh* mesh, GLProgram* program)
{
    //find in the cache first
    for (auto it = s_cachedVertexDecl.begin(); it != s_cachedVertexDecl.end(); it++) {
        
        if ((*it)->_mesh == mesh && (*it)->_program == program)
        {
            return *it;
        }
    }
    
    int attrFlag = mesh->getAttribFlag();
    
    //not find create new VertexDeclaration
    auto vertexdel = new VertexDeclaration();
    if (program == nullptr)
    {
        program = vertexdel->getDefProgram(attrFlag & GL::VERTEX_ATTRIB_FLAG_TEX_COORDS);
    }
    vertexdel->_mesh = mesh;
    vertexdel->_program = program;
    vertexdel->_attribFlag = attrFlag;
    mesh->retain();
    program->retain();
    
    if (!vertexdel->buildBuffer())
    {
        delete vertexdel;
        return nullptr;
    }

    vertexdel->setupUniforms();
    
    vertexdel->autorelease();
    
    
    return vertexdel;
}

bool VertexDeclaration::buildBuffer()
{
    int attrFlag = _mesh->getAttribFlag();
    if(CCConfiguration::getInstance()->supportsShareableVAO())
    {
        if (_vao)
        {
            glDeleteVertexArrays(1, &_vao);
            _vao = 0;
        }
        
        ( glBindBuffer(GL_ARRAY_BUFFER, 0) );
        ( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
        
        // Use hardware VAOs.
        ( glGenVertexArrays(1, &_vao) );
        
        if (_vao == 0)
        {
            
            return false;
        }
        
        // Bind the new VAO.
        ( glBindVertexArray(_vao) );
        
        // Bind the C3DMesh VBO so our glVertexAttribPointer calls use it.
        ( glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer()) );
    }
    
    
    unsigned int offset = 0;
    int stride = 0;
    if (attrFlag & GL::VERTEX_ATTRIB_FLAG_POSITION)
    {
        stride += sizeof(Vector3);
    }
    if (attrFlag & GL::VERTEX_ATTRIB_FLAG_NORMAL)
    {
        stride += sizeof(Vector3);
    }
    if (attrFlag & GL::VERTEX_ATTRIB_FLAG_TEX_COORDS)
    {
        stride += sizeof(Vector2);
    }
    
    if (attrFlag & GL::VERTEX_ATTRIB_FLAG_POSITION)
    {
        setAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        offset += sizeof(Vector3);
    }
    if (attrFlag & GL::VERTEX_ATTRIB_FLAG_NORMAL)
    {
        setAttribPointer(s_attribute_Normal, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        offset += sizeof(Vector3);
    }
    if (attrFlag & GL::VERTEX_ATTRIB_FLAG_TEX_COORDS)
    {
        setAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    }
    
    if(CCConfiguration::getInstance()->supportsShareableVAO())
    {
        if (_vao)
        {
            ( glBindBuffer(GL_ARRAY_BUFFER, 0) );
            ( glBindVertexArray(0) );
        }
    }
    return true;
}

void VertexDeclaration::setAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalize, GLsizei stride, void* pointer)
{
    if (_vao)
    {
        glEnableVertexAttribArray(indx);
        glVertexAttribPointer(indx, size, type, normalize, stride, pointer);
    }
    else
    {
        _attributes[indx].enabled = true;
        _attributes[indx].size = size;
        _attributes[indx].type = type;
        _attributes[indx].normalized = normalize;
        _attributes[indx].stride = stride;
        _attributes[indx].pointer = pointer;
    }

}

GLProgram* VertexDeclaration::getDefProgram(bool textured)
{
    if (textured && s_defProgramTex)
        return s_defProgramTex;
    
    if (!textured && s_defProgram)
        return s_defProgram;
    
    GLProgram* program = nullptr;
    if (textured)
    {
        s_defProgramTex = new GLProgram();
        (s_defProgramTex->initWithByteArrays(baseVertexShader, baseTexturedFrag));
        program = s_defProgramTex;
        
    }
    else
    {
        s_defProgram = new GLProgram();
        s_defProgram->initWithByteArrays(baseVertexShader, baseColoredFrag);
        program = s_defProgram;
    }
    
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    
    program->link();
    
    program->updateUniforms();
    return program;
}

void VertexDeclaration::bind()
{
    if (_vao)
    {
        GL::bindVAO(_vao);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBuffer());
        GL::enableVertexAttribs(_attribFlag);
        for (unsigned int i = 0; i < s_attributeCount; ++i)
        {
            VertexDeclaration::VertexAttribute& attr = _attributes[i];
            if (attr.enabled)
            {
                ( glVertexAttribPointer(i, attr.size, attr.type, attr.normalized, attr.stride, attr.pointer) );
            }
        }
    }
}

void VertexDeclaration::unbind()
{
    if (_vao)
    {
        // Hardware mode
        ( GL::bindVAO(0) );
    }
    else
    {
        
        GL::enableVertexAttribs(0);
    }
}

void VertexDeclaration::setupUniforms()
{
    for (auto it = _uniforms.begin(); it != _uniforms.end(); it++) {
        delete it->second;
    }
    _uniforms.clear();
    
    
    // Query and store uniforms from the program.
    GLint activeUniforms;
    GLuint program = _program->getProgram();
    ( glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms) );
    if (activeUniforms > 0)
    {
        GLint length;
        
        ( glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length) );
        if (length > 0)
        {
            GLchar* uniformName = new GLchar[length + 1];
            GLint uniformSize;
            GLenum uniformType;
            GLint uniformLocation;
            for (int i = 0; i < activeUniforms; ++i)
            {
                // Query uniform info.
                ( glGetActiveUniform(program, i, length, NULL, &uniformSize, &uniformType, uniformName) );
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
                ( uniformLocation = glGetUniformLocation(program, uniformName) );
                
                this->_uniforms[uniformName] = new Uniform(uniformLocation, uniformType);
            }
            delete[] (uniformName);
        }
    }
    
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void VertexDeclaration::restoreAllVertexDecl()
{
    //rebuild default program
    if (s_defProgramTex)
    {
        s_defProgramTex->reset();
        (s_defProgramTex->initWithByteArrays(baseVertexShader, baseTexturedFrag));
        s_defProgramTex->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        s_defProgramTex->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        s_defProgramTex->bindAttribLocation(s_attribute_Normal_Name, s_attribute_Normal);
        s_defProgramTex->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
        s_defProgramTex->link();
        
        s_defProgramTex->updateUniforms();
    }
    if (s_defProgram)
    {
        s_defProgram->reset();
        (s_defProgram->initWithByteArrays(baseVertexShader, baseTexturedFrag));
        s_defProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        s_defProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        s_defProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
        s_defProgram->bindAttribLocation(s_attribute_Normal_Name, s_attribute_Normal);
        
        s_defProgram->link();
        
        s_defProgram->updateUniforms();
    }
    for (auto it = s_cachedVertexDecl.begin(); it != s_cachedVertexDecl.end(); it++) {
        if ((*it) == this)
        {
            //rebuild vbo, vao
            (*it)->buildBuffer();
            (*it)->setupUniforms();
            //how about other userdefine program
        }
    }
}
#endif

UniformValue::UniformValue(): _uniform(nullptr), _count(0), _type(UniformValue::NONE)
{
    memset(&_value, 0, sizeof(_value));
}
UniformValue::~UniformValue()
{
    resetValue();
}

void UniformValue::resetValue()
{
    switch (_type) {
        case UniformValue::FLOAT:
            delete[] _value.floatPtrValue;
            break;
        case UniformValue::INT:
            delete[] _value.intPtrValue;
            break;
        case UniformValue::VECTOR2:
            delete[] _value.vec2PtrValue;
            break;
        case UniformValue::VECTOR3:
            delete[] _value.vec3PtrValue;
            break;
        case UniformValue::VECTOR4:
            delete[] _value.vec4PtrValue;
            break;
        case UniformValue::MATRIX:
            delete[] _value.matPtrValue;
            break;
        default:
            break;
    }
    
    memset(&_value, 0, sizeof(_value));
    _type = UniformValue::NONE;
    _count = 0;
}

bool UniformValue::init(VertexDeclaration::Uniform* uniform)
{
    resetValue();
    _uniform = uniform;
    return true;
}

void UniformValue::bindUniform(GLProgram* program)
{
    CCASSERT(_uniform, "null uniform");
    
    switch (_type) {
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
    if (_uniform && _uniform->_type == GL_FLOAT)
    {
        _count = 1;
        _type = UniformValue::FLOAT;
        if (_value.floatPtrValue == nullptr)
            _value.floatPtrValue = new float[_count];
        *(_value.floatPtrValue) = value;
        return true;
    }
    return false;
}

bool UniformValue::setValue(int value)
{
    if (_uniform && (_uniform->_type == GL_INT || _uniform->_type == GL_SAMPLER_2D))
    {
        _count = 1;
        _type = UniformValue::INT;
        if (_value.intPtrValue == nullptr)
            _value.intPtrValue = new int[_count];
        *(_value.intPtrValue) = value;
        return true;
    }
    return false;
}

bool UniformValue::setValue(const math::Vector2& value)
{
    if (_uniform && _uniform->_type == GL_FLOAT_VEC2)
    {
        _count = 1;
        _type = UniformValue::VECTOR2;
        if (_value.vec2PtrValue == nullptr)
            _value.vec2PtrValue = new Vector2[_count];
        *(_value.vec2PtrValue) = value;
        return true;
    }
    return false;
}

bool UniformValue::setValue(const math::Vector3& value)
{
    if (_uniform && _uniform->_type == GL_FLOAT_VEC3)
    {
        _count = 1;
        _type = UniformValue::VECTOR3;
        if (_value.vec3PtrValue == nullptr)
            _value.vec3PtrValue = new Vector3[_count];
        *(_value.vec3PtrValue) = value;
        return true;
    }
    return false;
}

bool UniformValue::setValue(const math::Vector4& value)
{
    if (_uniform && _uniform->_type == GL_FLOAT_VEC4)
    {
        _count = 1;
        _type = UniformValue::VECTOR4;
        if (_value.vec4PtrValue == nullptr)
            _value.vec4PtrValue = new Vector4[_count];
        *(_value.vec4PtrValue) = value;
        return true;
    }
    return false;
}

bool UniformValue::setValue(const math::Matrix& value)
{
    if (_uniform && _uniform->_type == GL_FLOAT_MAT4)
    {
        _count = 1;
        _type = UniformValue::MATRIX;
        if (_value.matPtrValue == nullptr)
            _value.matPtrValue = new Matrix[_count];
        *(_value.matPtrValue) = value;
        return true;
    }
    return false;
}

MeshMaterial* MeshMaterial::create(Mesh* mesh, GLProgram* program)
{
    MeshMaterial* material = new MeshMaterial();
    
    VertexDeclaration* vertexdec = VertexDeclaration::create(mesh, program);
    
    material->setVertexDeclaration(vertexdec);
    
    material->autorelease();
        
    return material;
}

void MeshMaterial::setVertexDeclaration(VertexDeclaration* vertexDec)
{
    if (_vertexDeclaration != vertexDec)
    {
        //shader changed, uniforms are invalidate
        if (_vertexDeclaration && vertexDec && vertexDec->getProgram() != _vertexDeclaration->getProgram())
            releaseUniformValues();
        
        CC_SAFE_RETAIN(vertexDec);
        CC_SAFE_RELEASE_NULL(_vertexDeclaration);
        _vertexDeclaration = vertexDec;
    }
}


void MeshMaterial::setTexture(Texture2D* texture)
{
    if (texture != _texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE_NULL(_texture);
        _texture = texture;
        updateBlendFunc();
        auto uniformValue = getUniformValue(s_shaderSampler);
        if (uniformValue)
            uniformValue->setValue(0);
    }
    
}

void MeshMaterial::setTexture(const std::string& filename)
{
    auto cache = Director::getInstance()->getTextureCache();
    Texture2D *tex = cache->addImage(filename);
    setTexture(tex);
}

void MeshMaterial::setColor(const Vector4& color)
{
    auto uniformValue = getUniformValue(s_destColor);
    if (uniformValue)
       uniformValue->setValue(color);
}

UniformValue* MeshMaterial::getUniformValue(const std::string& uniformName)
{
    CCASSERT(_vertexDeclaration, "null vertex init");
    
    auto it = _uniformValueMap.find(uniformName);
    if (it != _uniformValueMap.end())
        return it->second;
    
    auto uniforms = _vertexDeclaration->getUniforms();
    auto uniform = uniforms.find(uniformName);
    if (uniform != uniforms.end())
    {
        //can find in the shader
        auto uniformValue = new UniformValue();
        uniformValue->init(uniform->second);
        _uniformValueMap[uniformName] = uniformValue;
        
        return uniformValue;
    }
    
    return nullptr;//can not find in shader
}

void MeshMaterial::releaseUniformValues()
{
    for (auto it = _uniformValueMap.begin(); it != _uniformValueMap.end(); it++) {
        delete it->second;
    }
    _uniformValueMap.clear();
}

void MeshMaterial::bind()
{
    if (_vertexDeclaration)
    {
        //blend function
        GL::blendFunc( _blendFunc.src, _blendFunc.dst );
        
        if (_texture && _texture->getName()) {
            GL::bindTexture2D(_texture->getName());
        }
        
        //bind uniforms auto
        for (auto it = _uniformValueMap.begin(); it != _uniformValueMap.end(); it++) {
            it->second->bindUniform(_vertexDeclaration->getProgram());
        }
        _vertexDeclaration->bind();
    }
    
}

void MeshMaterial::unbind()
{
    if(_vertexDeclaration)
    {
        _vertexDeclaration->unbind();
    }
}

void MeshMaterial::updateBlendFunc()
{
	// it is possible to have an untextured sprite
	if( !_texture || ! _texture->hasPremultipliedAlpha() ) {
		_blendFunc.src = GL_SRC_ALPHA;
		_blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
	} else {
		_blendFunc.src = CC_BLEND_SRC;
		_blendFunc.dst = CC_BLEND_DST;
	}
}

MeshMaterial::MeshMaterial():_vertexDeclaration(nullptr), _texture(nullptr)
{
    
}

MeshMaterial::~MeshMaterial()
{
    CC_SAFE_RELEASE_NULL(_vertexDeclaration);
    
    releaseUniformValues();
}

NS_CC_END