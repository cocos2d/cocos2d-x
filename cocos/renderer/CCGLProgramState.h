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

#include <unordered_map>

#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

NS_CC_BEGIN

class GLProgram;
class Texture2D;
struct Uniform;
struct VertexAttrib;
class EventListenerCustom;
class EventCustom;

/**
 Uniform Value, which is used to store to value send to openGL pipe line by glUniformXXX.
 */
class CC_DLL UniformValue
{
    friend class GLProgram;
    friend class GLProgramState;
public:
    /**@{
     Construtor. If contruct the UniformValue with no param, the Uniform and Glprogram will be nullptr.
     @param uniform Uniform to apply the value.
     @param glprogram Specify the owner GLProgram of this uniform and uniform value.
     */
    UniformValue();
    UniformValue(Uniform *uniform, GLProgram* glprogram);
    /**
     @}
     */
    /**Destructor.*/
    ~UniformValue();
    /**@{
     Set data to Uniform value. Generally, there are many type of data could be supported,
     including float, int, Vec2/3/4, Mat4 and texture. Besides of this, there are also custom call
     back functions for sending data when you want to send struct or array data.
     If we want to send texture to uniform, there are two value to send, first one is texture handle ID,
     the second one the texture unit.
     @param value Value to be sent, support float, int, Vec2/3/4, Mat4.
     @param textureID The texture handle.
     @param textureUnit The binding texture unit to be used in shader.
     @param callback Callback function to send data to OpenGL pipeline.
     */
    void setFloat(float value);
    void setInt(int value);
    void setVec2(const Vec2& value);
    void setVec3(const Vec3& value);
    void setVec4(const Vec4& value);
    void setMat4(const Mat4& value);
    void setCallback(const std::function<void(GLProgram*, Uniform*)> &callback);
    void setTexture(GLuint textureId, GLuint textureUnit);
    /**
     @}
     */
    
    /**Apply the uniform value to openGL pipeline.*/
    void apply();

protected:
    /**Weak reference to Uniform.*/
	Uniform* _uniform;
    /**Weak reference to GLprogram.*/
    GLProgram* _glprogram;
    /**Whether or not callback is used.*/
    bool _useCallback;
    /**
     @name Uniform Value Uniform
     @{
     */
    union U{
        float floatValue;
        int intValue;
        float v2Value[2];
        float v3Value[3];
        float v4Value[4];
        float matrixValue[16];
        struct {
            GLuint textureId;
            GLuint textureUnit;
        } tex;
        std::function<void(GLProgram*, Uniform*)> *callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
    /**
     @}
     */
};

/**Vertex Attribute Value, which is an abstraction of VertexAttribute and data pointer.*/
class CC_DLL VertexAttribValue
{
    friend class GLProgram;
    friend class GLProgramState;

public:
    /**
    @{ 
     Constuctor and Destructor.
     @paran vertexAttrib VertexAttrib from shader.
    */
    VertexAttribValue(VertexAttrib *vertexAttrib);
    VertexAttribValue();
    ~VertexAttribValue();
    
    /**@}*/
    
    /**
     Set the data pointer, which is similar as glVertexAttribPointer.
     @param size The number of type in the vertex attribute.
     @param type The type of data in vertex attribute.
     @param normalized If true, 0-255 data will be mapped to 0.0-1.0.
     @param stride The number of bytes if an interleaved vertex array is used. 0 means array is not interleaved.
     @param pointer The pointer to the vertex data.
     */
	void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**Set a user call back for set VertexAttrib array.*/
    void setCallback(const std::function<void(VertexAttrib*)> &callback);
    /**Apply the vertex attribute to the openGL pipeline.*/
    void apply();

protected:
	VertexAttrib* _vertexAttrib;  // weak ref
    bool _useCallback;
    bool _enabled;

    union U{
        struct {
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            GLvoid *pointer;
        } pointer;
        std::function<void(VertexAttrib*)> *callback;

        U() { memset( this, 0, sizeof(*this) ); }
        ~U(){}
        U& operator=( const U& other ) {
            memcpy(this, &other, sizeof(*this));
            return *this;
        }
    } _value;
};


/**
 GLProgramState holds the 'state' (uniforms and attributes) of the GLProgram.
 A GLProgram can be used by thousands of Nodes, but if different uniform values 
 are going to be used, then each node will need its own GLProgramState
 */
class CC_DLL GLProgramState : public Ref
{
    friend class GLProgramStateCache;
public:

    /** returns a new instance of GLProgramState for a given GLProgram */
    static GLProgramState* create(GLProgram* glprogram);

    /** gets-or-creates an instance of GLProgramState for a given GLProgram */
    static GLProgramState* getOrCreateWithGLProgram(GLProgram* glprogram);

    /** gets-or-creates an instance of GLProgramState for a given GLProgramName */
    static GLProgramState* getOrCreateWithGLProgramName(const std::string &glProgramName );

    /** @{
     Apply GLProgram, attributes and uniforms.
     `apply` function will apply all the states, include GLProgram, attributes and uniforms.
     `applyGLProgram` function will apply GLProgram and built in uniform.
     `applyAttributes` will apply the vertex attributes.
     `applyUniforms` will apply user defined uniforms.
     
     @param The applied modelView matrix to shader.
     @param applyAttribFlags Call GL::enableVertexAttribs(_vertexAttribsFlags) or not.
     */
    void apply(const Mat4& modelView);
    void applyGLProgram(const Mat4& modelView);
    void applyAttributes(bool applyAttribFlags = true);
    void applyUniforms();
    /**@}*/
    
    /**@{ 
     Setter and Getter of the owner GLProgram binded in this program state.
     */
    void setGLProgram(GLProgram* glprogram);
    GLProgram* getGLProgram() const { return _glprogram; }
    
    /**@}*/
    
    /** Get the flag of vertex attribs used by OR operation.*/
    uint32_t getVertexAttribsFlags() const { return _vertexAttribsFlags; }
    /**Get the number of vertex attributes.*/
    ssize_t getVertexAttribCount() const { return _attributes.size(); }
    /**@{
     Set the vertex attribute value.
     */
    void setVertexAttribCallback(const std::string &name, const std::function<void(VertexAttrib*)> &callback);
    void setVertexAttribPointer(const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**@}*/
    
    /**Get the number of user defined uniform count.*/
    ssize_t getUniformCount() const { return _uniforms.size(); }
    
    /** @{
     Setting user defined uniforms by uniform string name in the shader.
     */
    void setUniformInt(const std::string &uniformName, int value);
    void setUniformFloat(const std::string &uniformName, float value);
    void setUniformVec2(const std::string &uniformName, const Vec2& value);
    void setUniformVec3(const std::string &uniformName, const Vec3& value);
    void setUniformVec4(const std::string &uniformName, const Vec4& value);
    void setUniformMat4(const std::string &uniformName, const Mat4& value);
    void setUniformCallback(const std::string &uniformName, const std::function<void(GLProgram*, Uniform*)> &callback);
    void setUniformTexture(const std::string &uniformName, Texture2D *texture);
    void setUniformTexture(const std::string &uniformName, GLuint textureId);
    /**@}*/
    
    /** @{
     Setting user defined uniforms by uniform location in the shader.
     */
    void setUniformInt(GLint uniformLocation, int value);
    void setUniformFloat(GLint uniformLocation, float value);
    void setUniformVec2(GLint uniformLocation, const Vec2& value);
    void setUniformVec3(GLint uniformLocation, const Vec3& value);
    void setUniformVec4(GLint uniformLocation, const Vec4& value);
    void setUniformMat4(GLint uniformLocation, const Mat4& value);
    void setUniformCallback(GLint uniformLocation, const std::function<void(GLProgram*, Uniform*)> &callback);
    void setUniformTexture(GLint uniformLocation, Texture2D *texture);
    void setUniformTexture(GLint uniformLocation, GLuint textureId);
    /**@}*/
    
protected:
    GLProgramState();
    ~GLProgramState();
    bool init(GLProgram* program);
    void resetGLProgram();
    void updateUniformsAndAttributes();
    VertexAttribValue* getVertexAttribValue(const std::string &attributeName);
    UniformValue* getUniformValue(const std::string &uniformName);
    UniformValue* getUniformValue(GLint uniformLocation);
    
    bool _uniformAttributeValueDirty;
    std::unordered_map<std::string, GLint> _uniformsByName;
    std::unordered_map<GLint, UniformValue> _uniforms;
    std::unordered_map<std::string, VertexAttribValue> _attributes;
    std::unordered_map<std::string, int> _boundTextureUnits;

    int _textureUnitIndex;
    uint32_t _vertexAttribsFlags;
    GLProgram *_glprogram;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundlistener;
#endif
};

NS_CC_END

#endif /* __CCGLPROGRAMSTATE_H__ */
