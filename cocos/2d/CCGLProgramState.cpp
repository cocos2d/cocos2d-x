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

#include "2d/CCGLProgramState.h"
#include "2d/CCGLProgram.h"
#include "2d/ccGLStateCache.h"

NS_CC_BEGIN

//
//
// UniformValue
//
//

UniformValue::UniformValue()
: _useCallback(false)
, _uniform(nullptr)
, _glprogram(nullptr)
{
}

UniformValue::UniformValue(Uniform *uniform, GLProgram* glprogram)
: _useCallback(false)
, _uniform(uniform)
, _glprogram(glprogram)
{
}

UniformValue::~UniformValue()
{
}

void UniformValue::apply()
{
    if(_useCallback) {
        _value.callback(_uniform);
    }
    else
    {
        switch (_uniform->type) {
            case GL_FLOAT:
                _glprogram->setUniformLocationWith1f(_uniform->location, _value.floatValue);
                break;

            case GL_INT:
            case GL_SAMPLER_2D:
                _glprogram->setUniformLocationWith1i(_uniform->location, _value.intValue);
                break;

            case GL_FLOAT_VEC2:
                _glprogram->setUniformLocationWith2f(_uniform->location, _value.v2Value.x, _value.v2Value.y);
                break;

            case GL_FLOAT_VEC3:
                _glprogram->setUniformLocationWith3f(_uniform->location, _value.v3Value.x, _value.v3Value.y, _value.v3Value.z);
                break;

            case GL_FLOAT_VEC4:
                _glprogram->setUniformLocationWith4f(_uniform->location, _value.v4Value.x, _value.v4Value.y, _value.v4Value.z, _value.v4Value.w);
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

void UniformValue::setValue(const std::function<void(Uniform*)> callback)
{
    _value.callback = callback;
    _useCallback = true;
}

void UniformValue::setValue(float value)
{
    CCASSERT (_uniform->type == GL_FLOAT, "");
    _value.floatValue = value;
    _useCallback = false;
}

void UniformValue::setValue(int value)
{
    CCASSERT ((_uniform->type == GL_INT || _uniform->type == GL_SAMPLER_2D), "");
    _value.intValue = value;
    _useCallback = false;
}

void UniformValue::setValue(const Vector2& value)
{
    CCASSERT (_uniform->type == GL_FLOAT_VEC2, "");
    _value.v2Value = value;
    _useCallback = false;
}

void UniformValue::setValue(const Vector3& value)
{
    CCASSERT (_uniform->type == GL_FLOAT_VEC3, "");
    _value.v3Value = value;
    _useCallback = false;
}

void UniformValue::setValue(const Vector4& value)
{
    CCASSERT (_uniform->type == GL_FLOAT_VEC4, "");
    _value.v4Value = value;
    _useCallback = false;
}

void UniformValue::setValue(const Matrix& value)
{
    CCASSERT(_uniform->type == GL_FLOAT_MAT4, "");
    _value.matrixValue = value;
    _useCallback = false;
}

//
//
// VertexAttribValue
//
//

VertexAttribValue::VertexAttribValue()
: _useCallback(false)
, _vertexAttrib(nullptr)
{
}

VertexAttribValue::VertexAttribValue(VertexAttrib *vertexAttrib)
: _useCallback(false)
, _vertexAttrib(vertexAttrib)
{
}

VertexAttribValue::~VertexAttribValue()
{
}

void VertexAttribValue::apply()
{    
    if(_useCallback) {
        _value.callback(_vertexAttrib);
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

void VertexAttribValue::setCallback(const std::function<void(VertexAttrib*)> callback)
{
    _value.callback = callback;
    _useCallback = true;
}

void VertexAttribValue::setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
{
    _value.pointer.size = size;
    _value.pointer.type = type;
    _value.pointer.normalized = normalized;
    _value.pointer.stride = stride;
    _value.pointer.pointer = pointer;
}

//
//
// GLProgramState
//
//

GLProgramState* GLProgramState::create(GLProgram *glprogram)
{
    auto ret = new (std::nothrow) GLProgramState;
    if(ret && ret->init(glprogram)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

GLProgramState::GLProgramState()
: _vertexAttribsFlags(0)
, _blendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED)
{
}

GLProgramState::~GLProgramState()
{
    _glprogram->release();
}

bool GLProgramState::init(GLProgram* glprogram)
{
    CCASSERT(glprogram, "invalid shader");

    _glprogram = glprogram;
    _glprogram->retain();

    for(auto &attrib : _glprogram->_attributesDictionary) {
        VertexAttribValue value(&attrib.second);
        _attributes[attrib.first] = value;
    }

    for(auto &uniform : _glprogram->_uniformsDictionary) {
        UniformValue value(&uniform.second, _glprogram);
        _uniforms[uniform.first] = value;
    }

    return true;
}

void GLProgramState::resetGLProgram()
{
    CC_SAFE_RELEASE(_glprogram);
    _uniforms.clear();
    _attributes.clear();
}

void GLProgramState::apply(const Matrix& modelView)
{
    CCASSERT(_glprogram, "invalid glprogram");

    // set shader
    _glprogram->use();

    _glprogram->setUniformsForBuiltins(modelView);

    // set texture
    int i = 0;
    for(const auto& texture : _textures) {
        GL::bindTexture2DN(i++, texture->getName());
    }

    // set blending function
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);


    // enable/disable vertex attribs
    GL::enableVertexAttribs(_vertexAttribsFlags);

    // set attributes
    for(auto &attribute : _attributes) {
        attribute.second.apply();
    }

    // set uniforms
    for(auto& uniform : _uniforms) {
        uniform.second.apply();
    }
}

void GLProgramState::setGLProgram(GLProgram *glprogram)
{
    CCASSERT(glprogram,  "invalid GLProgram");

    if( _glprogram != glprogram) {
        resetGLProgram();
        init(glprogram);
    }
}

void GLProgramState::setTexture(cocos2d::Texture2D *texture)
{
    if(_textures.size()>0)
        _textures.replace(0, texture);
    else
        _textures.pushBack(texture);
}

UniformValue* GLProgramState::getUniformValue(const std::string &name)
{
    const auto itr = _uniforms.find(name);
    if( itr != _uniforms.end())
        return &itr->second;
    return nullptr;
}

VertexAttribValue* GLProgramState::getVertexAttribValue(const std::string &name)
{
    const auto itr = _attributes.find(name);
    if( itr != _attributes.end())
        return &itr->second;
    return nullptr;
}

void GLProgramState::setVertexAttribCallback(const std::string &name, const std::function<void(VertexAttrib*)> callback)
{
    VertexAttribValue *v = getVertexAttribValue(name);
    v->setCallback(callback);
    _vertexAttribsFlags |= 1 << v->_vertexAttrib->index;
}

void GLProgramState::setVertexAttribPointer(const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
{
    auto v = getVertexAttribValue(name);
    v->setPointer(size, type, normalized, stride, pointer);
    _vertexAttribsFlags |= 1 << v->_vertexAttrib->index;
}


NS_CC_END
