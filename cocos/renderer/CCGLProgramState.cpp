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

#include "renderer/CCGLProgramState.h"

#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCTexture2D.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

// static vector with all the registered custom binding resolvers
std::vector<GLProgramState::AutoBindingResolver*> GLProgramState::_customAutoBindingResolvers;

//
//
// UniformValue
//
//

UniformValue::UniformValue()
: _uniform(nullptr)
, _glprogram(nullptr)
, _type(Type::VALUE)
{
}

UniformValue::UniformValue(Uniform *uniform, GLProgram* glprogram)
: _uniform(uniform)
, _glprogram(glprogram)
, _type(Type::VALUE)
{
}

UniformValue::UniformValue(const UniformValue& o)
{
    *this = o;
}

UniformValue::~UniformValue()
{
    if (_type == Type::CALLBACK_FN)
        delete _value.callback;

    if (_uniform->type == GL_SAMPLER_2D)
    {
        CC_SAFE_RELEASE(_value.tex.texture);
    }
}

void UniformValue::apply()
{
    if (_type == Type::CALLBACK_FN)
    {
        (*_value.callback)(_glprogram, _uniform);
    }
    else if (_type == Type::POINTER)
    {
        switch (_uniform->type) {
            case GL_FLOAT:
                _glprogram->setUniformLocationWith1fv(_uniform->location, _value.floatv.pointer, _value.floatv.size);
                break;

            case GL_FLOAT_VEC2:
                _glprogram->setUniformLocationWith2fv(_uniform->location, _value.v2f.pointer, _value.v2f.size);
                break;

            case GL_FLOAT_VEC3:
                _glprogram->setUniformLocationWith3fv(_uniform->location, _value.v3f.pointer, _value.v3f.size);
                break;

            case GL_FLOAT_VEC4:
                _glprogram->setUniformLocationWith4fv(_uniform->location, _value.v4f.pointer, _value.v4f.size);
                break;

            default:
                CCASSERT(false, "Unsupported type");
                break;
        }
    }
    else /* _type == VALUE */
    {
        switch (_uniform->type) {
            case GL_SAMPLER_2D:
                _glprogram->setUniformLocationWith1i(_uniform->location, _value.tex.textureUnit);
                glActiveTexture(GL_TEXTURE0 + _value.tex.textureUnit);
                glBindTexture(GL_TEXTURE_2D, _value.tex.textureId);
                break;

            case GL_SAMPLER_CUBE:
                _glprogram->setUniformLocationWith1i(_uniform->location, _value.tex.textureUnit);
                glActiveTexture(GL_TEXTURE0 + _value.tex.textureUnit);
                glBindTexture(GL_TEXTURE_CUBE_MAP, _value.tex.textureId);
                break;

            case GL_INT:
                _glprogram->setUniformLocationWith1i(_uniform->location, _value.intValue);
                break;

            case GL_FLOAT:
                _glprogram->setUniformLocationWith1f(_uniform->location, _value.floatValue);
                break;

            case GL_FLOAT_VEC2:
                _glprogram->setUniformLocationWith2f(_uniform->location, _value.v2Value[0], _value.v2Value[1]);
                break;

            case GL_FLOAT_VEC3:
                _glprogram->setUniformLocationWith3f(_uniform->location, _value.v3Value[0], _value.v3Value[1], _value.v3Value[2]);
                break;

            case GL_FLOAT_VEC4:
                _glprogram->setUniformLocationWith4f(_uniform->location, _value.v4Value[0], _value.v4Value[1], _value.v4Value[2], _value.v4Value[3]);
                break;

            case GL_FLOAT_MAT4:
                _glprogram->setUniformLocationWithMatrix4fv(_uniform->location, (GLfloat*)&_value.matrixValue, 1);
                break;

            default:
                CCASSERT(false, "Invalid UniformValue");
                break;
        }
    }
}

void UniformValue::setCallback(const std::function<void(GLProgram*, Uniform*)> &callback)
{
    // delete previously set callback
    // TODO: memory will leak if the user does:
    //    value->setCallback();
    //    value->setFloat();
    if (_type == Type::CALLBACK_FN)
        delete _value.callback;

    _value.callback = new (std::nothrow) std::function<void(GLProgram*, Uniform*)>();
	*_value.callback = callback;

    _type = Type::CALLBACK_FN;
}

void UniformValue::setTexture(GLuint textureId, GLuint textureUnit)
{
    //CCASSERT(_uniform->type == GL_SAMPLER_2D, "Wrong type. expecting GL_SAMPLER_2D");
    _value.tex.textureId = textureId;
    _value.tex.textureUnit = textureUnit;
    _value.tex.texture = nullptr;
    _type = Type::VALUE;
}

void UniformValue::setTexture(Texture2D* texture, GLuint textureUnit)
{
    CCASSERT(texture != nullptr, "texture is nullptr");

    if (texture != _value.tex.texture)
    {
        CC_SAFE_RELEASE(_value.tex.texture);
        CC_SAFE_RETAIN(texture);
        _value.tex.texture = texture;

        _value.tex.textureId = texture->getName();
        _value.tex.textureUnit = textureUnit;
        _type = Type::VALUE;
    }
}

void UniformValue::setInt(int value)
{
    CCASSERT(_uniform->type == GL_INT, "Wrong type: expecting GL_INT");
    _value.intValue = value;
    _type = Type::VALUE;
}

void UniformValue::setFloat(float value)
{
    CCASSERT(_uniform->type == GL_FLOAT, "Wrong type: expecting GL_FLOAT");
    _value.floatValue = value;
    _type = Type::VALUE;
}

void UniformValue::setFloatv(ssize_t size, const float* pointer)
{
    CCASSERT(_uniform->type == GL_FLOAT, "Wrong type: expecting GL_FLOAT");
    _value.floatv.pointer = (const float*)pointer;
    _value.floatv.size = (GLsizei)size;
    _type = Type::POINTER;
}

void UniformValue::setVec2(const Vec2& value)
{
    CCASSERT(_uniform->type == GL_FLOAT_VEC2, "Wrong type: expecting GL_FLOAT_VEC2");
	memcpy(_value.v2Value, &value, sizeof(_value.v2Value));
    _type = Type::VALUE;
}

void UniformValue::setVec2v(ssize_t size, const Vec2* pointer)
{
    CCASSERT(_uniform->type == GL_FLOAT_VEC2, "Wrong type: expecting GL_FLOAT_VEC2");
    _value.v2f.pointer = (const float*)pointer;
    _value.v2f.size = (GLsizei)size;
    _type = Type::POINTER;
}

void UniformValue::setVec3(const Vec3& value)
{
    CCASSERT(_uniform->type == GL_FLOAT_VEC3, "Wrong type: expecting GL_FLOAT_VEC3");
	memcpy(_value.v3Value, &value, sizeof(_value.v3Value));
    _type = Type::VALUE;

}

void UniformValue::setVec3v(ssize_t size, const Vec3* pointer)
{
    CCASSERT(_uniform->type == GL_FLOAT_VEC3, "Wrong type: expecting GL_FLOAT_VEC3");
    _value.v3f.pointer = (const float*)pointer;
    _value.v3f.size = (GLsizei)size;
    _type = Type::POINTER;
}

void UniformValue::setVec4(const Vec4& value)
{
    CCASSERT (_uniform->type == GL_FLOAT_VEC4, "Wrong type: expecting GL_FLOAT_VEC4");
	memcpy(_value.v4Value, &value, sizeof(_value.v4Value));
    _type = Type::VALUE;
}

void UniformValue::setVec4v(ssize_t size, const Vec4* pointer)
{
    CCASSERT (_uniform->type == GL_FLOAT_VEC4, "Wrong type: expecting GL_FLOAT_VEC4");
    _value.v4f.pointer = (const float*)pointer;
    _value.v4f.size = (GLsizei)size;
    _type = Type::POINTER;
}

void UniformValue::setMat4(const Mat4& value)
{
    CCASSERT(_uniform->type == GL_FLOAT_MAT4, "_uniform's type should be equal GL_FLOAT_MAT4.");
	memcpy(_value.matrixValue, &value, sizeof(_value.matrixValue));
    _type = Type::VALUE;
}

UniformValue& UniformValue::operator=(const UniformValue& o)
{
    if (this != &o)
    {
        _uniform = o._uniform;
        _glprogram = o._glprogram;
        _type = o._type;
        _value = o._value;

        if (_uniform->type == GL_SAMPLER_2D)
        {
            CC_SAFE_RETAIN(_value.tex.texture);
        }
    }
    return *this;
}

//
//
// VertexAttribValue
//
//

VertexAttribValue::VertexAttribValue()
: _vertexAttrib(nullptr)
, _useCallback(false)
, _enabled(false)
{
}

VertexAttribValue::VertexAttribValue(VertexAttrib *vertexAttrib)
: _vertexAttrib(vertexAttrib)
, _useCallback(false)
, _enabled(false)
{
}

VertexAttribValue::~VertexAttribValue()
{
	if (_useCallback)
		delete _value.callback;
}

void VertexAttribValue::apply()
{
    if(_enabled) {
        if(_useCallback) {
            (*_value.callback)(_vertexAttrib);
        }
        else
        {
            glVertexAttribPointer(_vertexAttrib->index,
                                  _value.pointer.size,
                                  _value.pointer.type,
                                  _value.pointer.normalized,
                                  _value.pointer.stride,
                                  _value.pointer.pointer);
        }
    }
}

void VertexAttribValue::setCallback(const std::function<void(VertexAttrib*)> &callback)
{
	_value.callback = new (std::nothrow) std::function<void(VertexAttrib*)>();
	*_value.callback = callback;
    _useCallback = true;
    _enabled = true;
}

void VertexAttribValue::setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
{
    _value.pointer.size = size;
    _value.pointer.type = type;
    _value.pointer.normalized = normalized;
    _value.pointer.stride = stride;
    _value.pointer.pointer = pointer;
    _enabled = true;
}

//
//
// GLProgramState
//
//
GLProgramState* GLProgramState::getOrCreateWithGLProgramName(const std::string& glProgramName, Texture2D* texture)
{
    if (texture != nullptr && texture->getAlphaTextureName() != 0) {
        if (glProgramName == GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR) {
            return GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR);
        }
        else if (glProgramName == GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP) {
            return GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP);
        }
        else if (glProgramName == GLProgram::SHADER_NAME_POSITION_GRAYSCALE) {
            return GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP);
        }
    }

    return GLProgramState::getOrCreateWithGLProgramName(glProgramName);
}

GLProgramState* GLProgramState::create(GLProgram *glprogram)
{
    GLProgramState* ret = new (std::nothrow) GLProgramState();
    if(ret && ret->init(glprogram))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLProgramState* GLProgramState::getOrCreateWithGLProgramName(const std::string& glProgramName )
{
    GLProgram *glProgram = GLProgramCache::getInstance()->getGLProgram(glProgramName);
    if( glProgram )
        return getOrCreateWithGLProgram(glProgram);

    CCLOG("cocos2d: warning: GLProgram '%s' not found", glProgramName.c_str());
    return nullptr;
}


GLProgramState* GLProgramState::getOrCreateWithGLProgram(GLProgram *glprogram)
{
    GLProgramState* ret = GLProgramStateCache::getInstance()->getGLProgramState(glprogram);
    return ret;
}

GLProgramState* GLProgramState::getOrCreateWithShaders(const std::string& vertexShader, const std::string& fragShader, const std::string& compileTimeDefines)
{
    auto glprogramcache = GLProgramCache::getInstance();
    const std::string key = vertexShader + "+" + fragShader + "+" + compileTimeDefines;
    auto glprogram = glprogramcache->getGLProgram(key);

    if (!glprogram) {
        glprogram = GLProgram::createWithFilenames(vertexShader, fragShader, compileTimeDefines);
        glprogramcache->addGLProgram(glprogram, key);
    }

    return create(glprogram);
}


GLProgramState::GLProgramState()
: _uniformAttributeValueDirty(true)
, _textureUnitIndex(4)  // first 4 textures unites are reserved for CC_Texture0-3
, _vertexAttribsFlags(0)
, _glprogram(nullptr)
, _nodeBinding(nullptr)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _backToForegroundlistener(nullptr)
#endif
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    /** listen the event that renderer was recreated on Android/WP8 */
    CCLOG("create rendererRecreatedListener for GLProgramState");
    _backToForegroundlistener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, 
        [this](EventCustom*) 
        {
            CCLOG("Dirty Uniform and Attributes of GLProgramState"); 
            _uniformAttributeValueDirty = true;
        });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
#endif
}

GLProgramState::~GLProgramState()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundlistener);
#endif

    // _uniforms must be cleared before releasing _glprogram since
    // the destructor of UniformValue will call a weak pointer
    // which points to the member variable in GLProgram.
    _uniforms.clear();
    _attributes.clear();

    CC_SAFE_RELEASE(_glprogram);
}

GLProgramState* GLProgramState::clone() const
{
    auto glprogramstate = new (std::nothrow) GLProgramState();

    // copy everything manually, instead of calling init since this is faster

    glprogramstate->_glprogram = this->_glprogram;
    CC_SAFE_RETAIN(glprogramstate->_glprogram);

    glprogramstate->_attributes = this->_attributes;
    glprogramstate->_vertexAttribsFlags = this->_vertexAttribsFlags;

    // copy uniforms
    glprogramstate->_uniformsByName = this->_uniformsByName;
    glprogramstate->_uniforms = this->_uniforms;
    glprogramstate->_uniformAttributeValueDirty = this->_uniformAttributeValueDirty;

    // copy textures
    glprogramstate->_textureUnitIndex = this->_textureUnitIndex;
    glprogramstate->_boundTextureUnits = this->_boundTextureUnits;

    // _nodeBinding is null since a node can only have one state.
    // making the null explicit to avoid possible bugs in the future
    glprogramstate->_nodeBinding = nullptr;

    // copy autobindings... rebound them once a target is set again
    glprogramstate->_autoBindings = _autoBindings;

    glprogramstate->autorelease();
    return glprogramstate;
}

bool GLProgramState::init(GLProgram* glprogram)
{
    CCASSERT(glprogram, "invalid shader");

    _glprogram = glprogram;
    _glprogram->retain();

    for(auto &attrib : _glprogram->_vertexAttribs) {
        VertexAttribValue value(&attrib.second);
        _attributes[attrib.first] = value;
    }

    for(auto &uniform : _glprogram->_userUniforms) {
        UniformValue value(&uniform.second, _glprogram);
        _uniforms[uniform.second.location] = std::move(value);
        _uniformsByName[uniform.first] = uniform.second.location;
    }

    return true;
}

void GLProgramState::resetGLProgram()
{
    // _uniforms must be cleared before releasing _glprogram since
    // the destructor of UniformValue will call a weak pointer
    // which points to the member variable in GLProgram.
    _uniforms.clear();
    _attributes.clear();

    CC_SAFE_RELEASE(_glprogram);
    _glprogram = nullptr;
    // first texture is GL_TEXTURE1
    _textureUnitIndex = 1;
    _nodeBinding = nullptr;
}

void GLProgramState::apply(const Mat4& modelView)
{
    applyGLProgram(modelView);

    applyAttributes();

    applyUniforms();
}

void GLProgramState::updateUniformsAndAttributes()
{
    CCASSERT(_glprogram, "invalid glprogram");
    if(_uniformAttributeValueDirty)
    {
        for(auto& uniformLocation : _uniformsByName)
        {
            _uniforms[uniformLocation.second]._uniform = _glprogram->getUniform(uniformLocation.first);
        }
        
        _vertexAttribsFlags = 0;
        for(auto& attributeValue : _attributes)
        {
            attributeValue.second._vertexAttrib = _glprogram->getVertexAttrib(attributeValue.first);
            if(attributeValue.second._enabled)
                _vertexAttribsFlags |= 1 << attributeValue.second._vertexAttrib->index;
        }
        
        _uniformAttributeValueDirty = false;
        
    }
}

void GLProgramState::applyGLProgram(const Mat4& modelView)
{
    CCASSERT(_glprogram, "invalid glprogram");
    updateUniformsAndAttributes();
    // set shader
    _glprogram->use();
    _glprogram->setUniformsForBuiltins(modelView);
}

void GLProgramState::applyAttributes(bool applyAttribFlags)
{
    // Don't set attributes if they weren't set
    // Use Case: Auto-batching
    updateUniformsAndAttributes();
    if(_vertexAttribsFlags) {
        // enable/disable vertex attribs
        if (applyAttribFlags)
        {
            auto flags = _vertexAttribsFlags;
            for (int i = 0; flags > 0; i++)
            {
                int flag = 1 << i;
                if (flag & flags)
                    glEnableVertexAttribArray(i);
                
                flags &= ~flag;
            }
        }
        // set attributes
        for(auto &attribute : _attributes)
        {
            attribute.second.apply();
        }
    }
}
void GLProgramState::applyUniforms()
{
    // set uniforms
    updateUniformsAndAttributes();
    for(auto& uniform : _uniforms) {
        uniform.second.apply();
    }
}

void GLProgramState::setGLProgram(GLProgram *glprogram)
{
    CCASSERT(glprogram, "invalid GLProgram");

    if( _glprogram != glprogram) {
        resetGLProgram();
        init(glprogram);
    }
}

uint32_t GLProgramState::getVertexAttribsFlags() const
{
    return _vertexAttribsFlags;
}

ssize_t GLProgramState::getVertexAttribCount() const
{
    return _attributes.size();
}

UniformValue* GLProgramState::getUniformValue(GLint uniformLocation)
{
    updateUniformsAndAttributes();
    const auto itr = _uniforms.find(uniformLocation);
    if (itr != _uniforms.end())
        return &itr->second;
    return nullptr;
}

UniformValue* GLProgramState::getUniformValue(const std::string& name)
{
    updateUniformsAndAttributes();
    const auto itr = _uniformsByName.find(name);
    if (itr != _uniformsByName.end())
        return &_uniforms[itr->second];
    return nullptr;
}

VertexAttribValue* GLProgramState::getVertexAttribValue(const std::string& name)
{
    updateUniformsAndAttributes();
    const auto itr = _attributes.find(name);
    if( itr != _attributes.end())
        return &itr->second;
    return nullptr;
}

// VertexAttrib Setters
void GLProgramState::setVertexAttribCallback(const std::string& name, const std::function<void(VertexAttrib*)> &callback)
{
    VertexAttribValue *v = getVertexAttribValue(name);
    if(v) {
        v->setCallback(callback);
        _vertexAttribsFlags |= 1 << v->_vertexAttrib->index;
    }
    else
    {
		CCLOG("cocos2d: warning: Attribute not found: %s", name.c_str());
	}
}

void GLProgramState::setVertexAttribPointer(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
{
    auto v = getVertexAttribValue(name);
    if(v) {
        v->setPointer(size, type, normalized, stride, pointer);
        _vertexAttribsFlags |= 1 << v->_vertexAttrib->index;
    }
    else
    {
		CCLOG("cocos2d: warning: Attribute not found: %s", name.c_str());
    }
}

// Uniform Setters

void GLProgramState::setUniformCallback(const std::string& uniformName, const std::function<void(GLProgram*, Uniform*)> &callback)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setCallback(callback);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformCallback(GLint uniformLocation, const std::function<void(GLProgram*, Uniform*)> &callback)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setCallback(callback);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformFloat(const std::string& uniformName, float value)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setFloat(value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformFloat(GLint uniformLocation, float value)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setFloat(value);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformInt(const std::string& uniformName, int value)
{
    auto v = getUniformValue(uniformName);
    if(v)
        v->setInt(value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformInt(GLint uniformLocation, int value)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setInt(value);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);

}

void GLProgramState::setUniformFloatv(const std::string& uniformName, ssize_t size, const float* pointer)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setFloatv(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformFloatv(GLint uniformLocation, ssize_t size, const float* pointer)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setFloatv(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformVec2(const std::string& uniformName, const Vec2& value)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setVec2(value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformVec2(GLint uniformLocation, const Vec2& value)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setVec2(value);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformVec2v(const std::string& uniformName, ssize_t size, const Vec2* pointer)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setVec2v(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformVec2v(GLint uniformLocation, ssize_t size, const Vec2* pointer)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setVec2v(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformVec3(const std::string& uniformName, const Vec3& value)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setVec3(value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformVec3(GLint uniformLocation, const Vec3& value)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setVec3(value);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformVec3v(const std::string& uniformName, ssize_t size, const Vec3* pointer)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setVec3v(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformVec3v(GLint uniformLocation, ssize_t size, const Vec3* pointer)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setVec3v(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformVec4(const std::string& uniformName, const Vec4& value)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setVec4(value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformVec4(GLint uniformLocation, const Vec4& value)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setVec4(value);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

void GLProgramState::setUniformVec4v(const std::string& uniformName, ssize_t size, const Vec4* value)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setVec4v(size, value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformVec4v(GLint uniformLocation, ssize_t size, const Vec4* pointer)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setVec4v(size, pointer);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}


void GLProgramState::setUniformMat4(const std::string& uniformName, const Mat4& value)
{
    auto v = getUniformValue(uniformName);
    if (v)
        v->setMat4(value);
    else
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
}

void GLProgramState::setUniformMat4(GLint uniformLocation, const Mat4& value)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
        v->setMat4(value);
    else
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
}

// Textures

void GLProgramState::setUniformTexture(const std::string& uniformName, Texture2D *texture)
{
    CCASSERT(texture, "Invalid texture");
    auto v = getUniformValue(uniformName);
    if (v)
    {
        if (_boundTextureUnits.find(uniformName) != _boundTextureUnits.end())
        {
            v->setTexture(texture, _boundTextureUnits[uniformName]);
        }
        else
        {
            v->setTexture(texture, _textureUnitIndex);
            _boundTextureUnits[uniformName] = _textureUnitIndex++;
        }
    }
    else
    {
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
    }
}

void GLProgramState::setUniformTexture(GLint uniformLocation, Texture2D *texture)
{
    CCASSERT(texture, "Invalid texture");
    auto v = getUniformValue(uniformLocation);
    if (v)
    {
        if (_boundTextureUnits.find(v->_uniform->name) != _boundTextureUnits.end())
        {
            v->setTexture(texture, _boundTextureUnits[v->_uniform->name]);
        }
        else
        {
            v->setTexture(texture, _textureUnitIndex);
            _boundTextureUnits[v->_uniform->name] = _textureUnitIndex++;
        }
    }
    else
    {
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
    }
}

void GLProgramState::setUniformTexture(const std::string& uniformName, GLuint textureId)
{
    auto v = getUniformValue(uniformName);
    if (v)
    {
        if (_boundTextureUnits.find(uniformName) != _boundTextureUnits.end())
        {
            v->setTexture(textureId, _boundTextureUnits[uniformName]);
        }
        else
        {
            v->setTexture(textureId, _textureUnitIndex);
            _boundTextureUnits[uniformName] = _textureUnitIndex++;
        }
    }
    else
    {
        CCLOG("cocos2d: warning: Uniform not found: %s", uniformName.c_str());
    }
}

void GLProgramState::setUniformTexture(GLint uniformLocation, GLuint textureId)
{
    auto v = getUniformValue(uniformLocation);
    if (v)
    {
        if (_boundTextureUnits.find(v->_uniform->name) != _boundTextureUnits.end())
        {
            v->setTexture(textureId, _boundTextureUnits[v->_uniform->name]);
        }
        else
        {
            v->setTexture(textureId, _textureUnitIndex);
            _boundTextureUnits[v->_uniform->name] = _textureUnitIndex++;
        }
    }
    else
    {
        CCLOG("cocos2d: warning: Uniform at location not found: %i", uniformLocation);
    }
}

// Auto bindings
void GLProgramState::setParameterAutoBinding(const std::string& uniformName, const std::string& autoBinding)
{
    _autoBindings[uniformName] = autoBinding;

    if (_nodeBinding)
        applyAutoBinding(uniformName, autoBinding);
}

void GLProgramState::applyAutoBinding(const std::string& uniformName, const std::string& autoBinding)
{
    // This code tries to replace GLProgram::setUniformsForBuiltins. But it is unfinished ATM.
    // The idea is that users will be able to use variables from cocos2d-x without hardcoding the
    // information on GLProgram and other objects.
    // Instead, the Cocos2d uniform variables will be callbacks.
    // As an example of how bad the current design is, the ModelView matrix is being passed from Node, to the Commands, to the GLProgram.
    // Instead, the GLProgramState should obtain it from its target.

    bool resolved = false;
    for (const auto resolver: _customAutoBindingResolvers)
    {
        resolved = resolver->resolveAutoBinding(this, _nodeBinding, uniformName, autoBinding);
        if (resolved)
            break;
    }

    if (!resolved)
    {
        // add cocos2d-x variables here like:
        // PROJECT_MATRIX
        // MODEL_MATRIX
        // MODEL_VIEW
        // MODEL_VIEW_PROJECTION
        // etc...
        //
        // and remove them from GLProgram::setUniformsForBuiltins
    }
}

void GLProgramState::setNodeBinding(Node* target)
{
    CCASSERT(target, "must be non-null");

    // weak ref
    _nodeBinding = target;

    for (const auto& autobinding: _autoBindings)
        applyAutoBinding(autobinding.first, autobinding.second);
}

Node* GLProgramState::getNodeBinding() const
{
    return _nodeBinding;
}

//
// MARK: AutoBindingResolver
//
GLProgramState::AutoBindingResolver::AutoBindingResolver()
{
    _customAutoBindingResolvers.push_back(this);
}

GLProgramState::AutoBindingResolver::~AutoBindingResolver()
{
    std::vector<GLProgramState::AutoBindingResolver*>::iterator itr = std::find(_customAutoBindingResolvers.begin(), _customAutoBindingResolvers.end(), this);
    if (itr != _customAutoBindingResolvers.end())
        _customAutoBindingResolvers.erase(itr);
}

NS_CC_END
