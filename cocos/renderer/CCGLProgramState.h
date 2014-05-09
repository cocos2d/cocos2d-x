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
    UniformValue(Uniform *uniform, GLProgram* glprogram);
    ~UniformValue();

	void setFloat(float value);
	void setInt(int value);
	void setVec2(const Vector2& value);
	void setVec3(const Vector3& value);
	void setVec4(const Vector4& value);
	void setMat4(const Matrix& value);
    void setCallback(const std::function<void(Uniform*)> &callback);

    void apply();

protected:
	Uniform* _uniform;  // weak ref
    GLProgram* _glprogram; // weak ref
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
    friend class GLProgramState;

public:
    VertexAttribValue(VertexAttrib *vertexAttrib);
    VertexAttribValue();
    ~VertexAttribValue();

	void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    void setCallback(const std::function<void(VertexAttrib*)> &callback);
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
    static GLProgramState* create(GLProgram* glprogram);

    void apply(const Matrix& modelView);

    void setGLProgram(GLProgram* glprogram);
    GLProgram* getGLProgram() const { return _glprogram; }

    void setVertexAttribCallback(const std::string &name, const std::function<void(VertexAttrib*)> &callback);
    void setVertexAttribPointer(const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);

    void setUniformFloat(const std::string &uniformName, float value);
	void setUniformInt(const std::string &uniformName, int value);
	void setUniformVec2(const std::string &uniformName, const Vector2& value);
	void setUniformVec3(const std::string &uniformName, const Vector3& value);
	void setUniformVec4(const std::string &uniformName, const Vector4& value);
	void setUniformMat4(const std::string &uniformName, const Matrix& value);
    void setUniformCallback(const std::string &uniformName, const std::function<void(Uniform*)> &callback);

protected:
    GLProgramState();
    ~GLProgramState();
    bool init(GLProgram* program);
    void resetGLProgram();
    VertexAttribValue* getVertexAttribValue(const std::string &attributeName);
    UniformValue* getUniformValue(const std::string &uniformName);

    std::unordered_map<std::string, UniformValue> _uniforms;
    std::unordered_map<std::string, VertexAttribValue> _attributes;

    uint32_t _vertexAttribsFlags;

    GLProgram *_glprogram;
};

NS_CC_END

#endif /* __CCGLPROGRAMSTATE_H__ */
