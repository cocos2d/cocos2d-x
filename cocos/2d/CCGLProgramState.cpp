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
{
}

UniformValue::UniformValue(Uniform *uniform)
: _useCallback(false)
, _uniform(uniform)
{
}

void UniformValue::apply()
{
    if(_useCallback) {
        _value.callback(_uniform);
    }
    else
    {
        switch (_uniform->_type) {
            case GL_FLOAT:
                _uniform->_program->setUniformLocationWith1f(_uniform->_location, _value.floatValue);
                break;

            case GL_INT:
            case GL_SAMPLER_2D:
                _uniform->_program->setUniformLocationWith1i(_uniform->_location, _value.intValue);
                break;

            case GL_FLOAT_VEC2:
                _uniform->_program->setUniformLocationWith2f(_uniform->_location, _value.v2Value.x, _value.v2Value.y);
                break;

            case GL_FLOAT_VEC3:
                _uniform->_program->setUniformLocationWith3f(_uniform->_location, _value.v3Value.x, _value.v3Value.y, _value.v3Value.z);
                break;

            case GL_FLOAT_VEC4:
                _uniform->_program->setUniformLocationWith4f(_uniform->_location, _value.v4Value.x, _value.v4Value.y, _value.v4Value.z, _value.v4Value.w);
                break;

            case GL_FLOAT_MAT4:
                _uniform->_program->setUniformLocationWithMatrix4fv(_uniform->_location, (GLfloat*)&_value.matrixValue, 1);
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
    CCASSERT (_uniform->_type == GL_FLOAT, "");
    _value.floatValue = value;
}

void UniformValue::setValue(int value)
{
    CCASSERT ((_uniform->_type == GL_INT || _uniform->_type == GL_SAMPLER_2D), "");
    _value.intValue = value;
}

void UniformValue::setValue(const Vector2& value)
{
    CCASSERT (_uniform->_type == GL_FLOAT_VEC2, "");
    _value.v2Value = value;
}

void UniformValue::setValue(const Vector3& value)
{
    CCASSERT (_uniform->_type == GL_FLOAT_VEC3, "");
    _value.v3Value = value;
}

void UniformValue::setValue(const Vector4& value)
{
    CCASSERT (_uniform->_type == GL_FLOAT_VEC4, "");
    _value.v4Value = value;
}

void UniformValue::setValue(const Matrix& value)
{
    CCASSERT(_uniform->_type == GL_FLOAT_MAT4, "");
    _value.matrixValue = value;
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

void VertexAttribValue::apply()
{
    GL::enableVertexAttribs(0);
    
    if(_useCallback) {
        _value.callback(_vertexAttrib);
    }
    else
    {
        glVertexAttribPointer(_vertexAttrib->_index,
                              _value.pointer.size,
                              _value.pointer.type,
                              _value.pointer.normalized,
                              _value.pointer.stride,
                              _value.pointer.pointer);
    }
}

void VertexAttribValue::setValue(const std::function<void(VertexAttrib*)> callback)
{
    _value.callback = callback;
    _useCallback = true;
}

void VertexAttribValue::setValue(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer)
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
    CCASSERT(glprogram, "invalid shader");

    auto ret = new (std::nothrow) GLProgramState;
    if(ret && ret->init(glprogram)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

GLProgramState::~GLProgramState()
{
    _glprogram->release();
}

bool GLProgramState::init(GLProgram* glprogram)
{
    _glprogram = glprogram;
    _glprogram->retain();

    for(auto &attrib : _glprogram->_attributesDictionary) {
        VertexAttribValue value(&attrib.second);
        _attributes[attrib.first] = value;
    }

    for(auto &uniform : _glprogram->_uniformsDictionary) {
        UniformValue value(&uniform.second);
        _uniforms[uniform.first] = value;
    }

    return true;
}
void GLProgramState::apply()
{
    CCASSERT(_glprogram, "invalid glprogram");

    // set shader
    _glprogram->use();


    // set texture
    int i = 0;
    for(const auto& texture : _textures) {
        GL::bindTexture2DN(i++, texture->getName());
    }

    // set blending function
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);


    // set uniforms
    for(auto& uniform : _uniforms) {
        uniform.second.apply();
    }

    // set attributes
    for(auto &attribute : _attributes) {
        attribute.second.apply();
    }
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

NS_CC_END
