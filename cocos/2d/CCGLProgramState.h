/****************************************************************************
Copyright 2014 Chukong Technologies Inc.
 
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

#ifndef __CCGLPROGRAMSTATE_H__
#define __CCGLPROGRAMSTATE_H__

#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "2d/CCTexture2D.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

#include <unordered_map>

NS_CC_BEGIN

class GLProgram;
class Uniform;
class VertexAttrib;

//
//
// UniformValue
//
//
class UniformValue
{
    friend class GLProgram;

public:
    UniformValue();
    UniformValue(Uniform *uniform);
    ~UniformValue();

	void setValue(float value);
	void setValue(int value);
	void setValue(const Vector2& value);
	void setValue(const Vector3& value);
	void setValue(const Vector4& value);
	void setValue(const Matrix& value);
    void setValue(const std::function<void(Uniform*)> callback);

    void apply();

protected:
	Uniform* _uniform;  // weak ref
    bool _useCallback;
    
    union U{
        float floatValue;
        int intValue;
        Vector2 v2Value;
        Vector3 v3Value;
        Vector4 v4Value;
        Matrix matrixValue;
        std::function<void(Uniform*)> callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
};

//
//
// VertexAttribValue
//
//
class VertexAttribValue
{
    friend class GLProgram;

public:
    VertexAttribValue(VertexAttrib *vertexAttrib);
    VertexAttribValue();
    ~VertexAttribValue();

	void setValue(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    void setValue(const std::function<void(VertexAttrib*)> callback);
    void apply();

protected:
	VertexAttrib* _vertexAttrib;  // weak ref
    bool _useCallback;

    union U{
        struct {
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLvoid *pointer;
        } pointer;
        std::function<void(VertexAttrib*)> callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
};


//
//
// GLProgramState
//
//
class GLProgramState : public Ref
{
public:
    GLProgramState* create(GLProgram* glprogram);

    void apply();
    void setTexture(Texture2D *texture) { _textures.insert(0, texture); }
    Texture2D* getTexture() const { return _textures.at(0); }

    void setBlendFunc(const BlendFunc& blendFunc) { _blendFunc = blendFunc; }
    const BlendFunc& getBlendFunc() const { return _blendFunc; }

    UniformValue* getUniformValue(const std::string &uniformName);
    VertexAttribValue* getVertexAttribValue(const std::string &attributeName);

protected:
    GLProgramState();
    ~GLProgramState();
    bool init(GLProgram* program);

    std::unordered_map<std::string, UniformValue> _uniforms;
    std::unordered_map<std::string, VertexAttribValue> _attributes;
    
    GLProgram *_glprogram;
    Vector<Texture2D*> _textures;
    BlendFunc _blendFunc;
};

NS_CC_END

#endif /* __CCGLPROGRAMSTATE_H__ */
