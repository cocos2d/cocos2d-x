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
 
 Autobinding Interface from GamePlay3D: http://www.gameplay3d.org/
****************************************************************************/

#ifndef __CCGLPROGRAMSTATE_H__
#define __CCGLPROGRAMSTATE_H__

#include <unordered_map>

#include "base/ccTypes.h"
#include "base/CCVector.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class GLProgram;
class Texture2D;
struct Uniform;
struct VertexAttrib;
class EventListenerCustom;
class EventCustom;
class Node;

/**@class UniformValue
@brief
@~english
 * Uniform Value, which is used to store to value send to openGL pipe line by glUniformXXX.
 *
 * @~chinese 
 * Uniform的值, 存储的数据通过glUniformXXX函数发送到openGL渲染管线。
 * 
 * @lua NA
 */
class CC_DLL UniformValue
{
    friend class GLProgram;
    friend class GLProgramState;
public:
    /**@~english
     Constructor. The Uniform and Glprogram will be nullptr.
     * @~chinese 
     * 构造函数，对象中的Uniform和GLProgram都将是null。
     */
    UniformValue();
    /**@~english
     Constructor with uniform and glprogram.
     * @~chinese 
     * 构造函数。
     @param uniform @~english Uniform to apply the value.
     * @~chinese 用于设置数据的Uniform。
     @param glprogram @~english Specify the owner GLProgram of this uniform and uniform value.
     * @~chinese Uniform和Uniform Value属于哪个GLProgram。
     */
    UniformValue(Uniform *uniform, GLProgram* glprogram);

    /**@~english Destructor. @~chinese 析构函数。*/
    ~UniformValue();
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param value @~english The float value @~chinese float数据。
    */
    void setFloat(float value);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param value @~english The int value @~chinese int数据。
    */
    void setInt(int value);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param size @~english The number of float. @~chinese float数据的个数。
    @param pointer @~english The float value pointer @~chinese float数据指针。
    */
    void setFloatv(ssize_t size, const float* pointer);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param value @~english The Vec2 value @~chinese Vec2数据。
    */
    void setVec2(const Vec2& value);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param size @~english The number of Vec2. @~chinese Vec2数据的个数。
    @param pointer @~english The Vec2 value pointer @~chinese Vec2数据指针。
    */
    void setVec2v(ssize_t size, const Vec2* pointer);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param value @~english The Vec2 value @~chinese Vec2数据。
    */
    void setVec3(const Vec3& value);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param size @~english The number of Vec3. @~chinese Vec3数据的个数。
    @param pointer @~english The Vec3 value pointer @~chinese Vec3数据指针。
    */
    void setVec3v(ssize_t size, const Vec3* pointer);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param value @~english The Vec2 value @~chinese Vec2数据。
    */
    void setVec4(const Vec4& value);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param size @~english The number of Vec4. @~chinese Vec4数据的个数。
    @param pointer @~english The Vec4 value pointer @~chinese Vec4数据指针。
    */
    void setVec4v(ssize_t size, const Vec4* pointer);
    /**
    @~english Set Uniform value. @~chinese 设置Uniform数据。
    @param value @~english The Mat4 value @~chinese Mat4数据。
    */
    void setMat4(const Mat4& value);
    /**
     @}
     */
    
    /**@~english
     Set call back to uniform value, which could be used for array and struct.
     * @~chinese 
     * 给UniformValue设置回调函数。
     @param callback @~english Callback function to send data to OpenGL pipeline.
     * @~chinese 回调函数。
     */
    void setCallback(const std::function<void(GLProgram*, Uniform*)> &callback);
    /**@~english
     Set texture to uniform value.
     * @~chinese 
     * 设置纹理值给UniformValue。
     @param textureId @~english The texture handle.
     * @~chinese 纹理句柄。
     @param textureUnit @~english The binding texture unit to be used in shader.
     * @~chinese 纹理要被绑定到哪个采样器上。
    */
    void setTexture(GLuint textureId, GLuint textureUnit);
    
    /**
    @~english Apply the uniform value to openGL pipeline. 
    @~chinese 将uniform数值应用到openGL渲染管线。
    */
    void apply();

protected:

    enum class Type {
        VALUE,
        POINTER,
        CALLBACK_FN     // CALLBACK is already defined in windows, can't use it.
    };

    /** Weak reference to Uniform.*/
	Uniform* _uniform;
    /** Weak reference to GLprogram.*/
    GLProgram* _glprogram;
    /** What kind of type is the Uniform*/
    Type _type;

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
        struct {
            const float* pointer;
            GLsizei size;
        } floatv;
        struct {
            const float* pointer;
            GLsizei size;
        } v2f;
        struct {
            const float* pointer;
            GLsizei size;
        } v3f;
        struct {
            const float* pointer;
            GLsizei size;
        } v4f;
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

/**
@class VertexAttribValue
@brief
@~english
 * Vertex Attribute Value, which is an abstraction of VertexAttribute and data pointer.
 *
 * @~chinese 
 * 顶点属性值,用于抽象的VertexAttribute和数据。
 * 
 * @lua NA
 */
class CC_DLL VertexAttribValue
{
    friend class GLProgram;
    friend class GLProgramState;
    friend class VertexAttribBinding;

public:
    /**@~english
     Constructor.
     * @~chinese 
     * 构造函数。
     @param vertexAttrib @~english VertexAttrib from shader.
     * @~chinese 从shader传过来的VertexAttrib。
    */
    VertexAttribValue(VertexAttrib *vertexAttrib);
    /**@~english
     Constructor.
     * @~chinese 
     * 构造函数。
     */
    VertexAttribValue();
    /**@~english
     Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~VertexAttribValue();
    
    /**@~english
     Set the data pointer, which is similar as glVertexAttribPointer.
     * @~chinese 
     * 设置数据指针,参数类似glVertexAttribPointer，并被其使用。
     @param size @~english The number of type in the vertex attribute.
     * @~chinese 顶点属性数莸氖俊�
     @param type @~english The type of data in vertex attribute.
     * @~chinese 顶点属性数据的类型。
     @param normalized @~english If true, 0-255 data will be mapped to 0.0-1.0.
     * @~chinese 如果这是真的,0 - 255数据将被映射到0.0－1.0。
     @param stride @~english The number of bytes if an interleaved vertex array is used. 0 means array is not interleaved.
     * @~chinese 如果是一个属性交叉的顶点数组，其表示相邻两个顶点的偏移值。0表示非交叉顶点数组。
     @param pointer @~english The pointer to the vertex data.
     * @~chinese 顶点数据的指针。
     */
	void setPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**
    @~english Set a user call back for set VertexAttrib array. 
    @~chinese 设置一组用户回调函数用于设置顶点属性。
    */
    void setCallback(const std::function<void(VertexAttrib*)> &callback);
    /**
    @~english Apply the vertex attribute to the openGL pipeline. 
    @~chinese 将顶点属性应用于openGL渲染管线。
    */
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
@class GLProgramState
@brief
@~english
 GLProgramState holds the 'state' (uniforms and attributes) of the GLProgram.
 A GLProgram can be used by thousands of Nodes, but if different uniform values 
 are going to be used, then each node will need its own GLProgramState
 * @~chinese 
 * GLProgramState持有这些状态，包含GLProgram的Uniform和顶点属性。
 GLProgram可以被很多个Node使用，但是如果Node使用的Unifrom数值不同的话，那么Node就需要持有自己的GLProgramState。
 */
class CC_DLL GLProgramState : public Ref
{
    friend class GLProgramStateCache;
public:

    /** 
    @~english returns a new instance of GLProgramState for a given GLProgram  
    @~chinese 从GLProgram中创建一个GLProgramState的新实例。
    */
    static GLProgramState* create(GLProgram* glprogram);
    /** 
    @~english gets-or-creates an instance of GLProgramState for a given GLProgram  
    @~chinese 从Cache中，按照GLProgram值，新创建或者获取cache的GLProgramState的实例。
    */
    static GLProgramState* getOrCreateWithGLProgram(GLProgram* glprogram);

    /** 
    @~english gets-or-creates an instance of GLProgramState for a given GLProgramName  
    @~chinese 从Cache中，按照GLProgram的名字，新创建或者获取cache的GLProgramState的实例。
    */
    static GLProgramState* getOrCreateWithGLProgramName(const std::string &glProgramName );

    /** 
    @~english gets-or-creates an instance of GLProgramState for given shaders  
    @~chinese 从Cache中，按照VertexShader和FragmentShader的源代码，新创建或者获取cache的GLProgramState的实例。
    */
    static GLProgramState* getOrCreateWithShaders(const std::string& vertexShader, const std::string& fragShader, const std::string& compileTimeDefines);

    /** 
    @~english Returns a new copy of the GLProgramState. The GLProgram is reused  
    @~chinese 返回一个新的GLProgramState的副本。
    */
    GLProgramState* clone() const;

    /**@~english
     Apply GLProgram, attributes and uniforms.
     * @~chinese 
     * 应用GLProgram,顶点属性和Uniform参数到渲染管线。
     @param modelView @~english The applied modelView matrix to shader.
     * @~chinese 要设置的ModelView矩阵。
     */
    void apply(const Mat4& modelView);
    /**@~english
     Apply GLProgram, and built in uniforms.
     * @~chinese 
     * 应用GLProgram和内置的Uniform参数。
     @param modelView @~english The applied modelView matrix to shader.
     * @~chinese 要设置的ModelView矩阵。
     */
    void applyGLProgram(const Mat4& modelView);
    /**@~english
     Apply attributes.
     * @~chinese 
     * 应用顶点属性。
     @param applyAttribFlags @~english Call GL::enableVertexAttribs(_vertexAttribsFlags) or not.
     * @~chinese 是否调用GL::enableVertexAttribs函数。
     */
    void applyAttributes(bool applyAttribFlags = true);
    /**@~english
     Apply user defined uniforms.
     * @~chinese 
     * 应用自定义Uniform数值。
     */
    void applyUniforms();

    /**
    @~english Set the binded GLProgram.
    @~chinese 设置绑定的GLProgram。
    */
    void setGLProgram(GLProgram* glprogram);
    /**
    @~english Get the binded GLProgram.
    @~chinese 得到绑定的GLProgram。
    */
    GLProgram* getGLProgram() const { return _glprogram; }
    
    /** 
    @~english Get the flag of vertex attribs used by OR operation. 
    @~chinese 按照GLProgramState顶点属性，得到GL::enableVertexAttribs的flag参数。
    */
    uint32_t getVertexAttribsFlags() const;
    /**
    @~english Get the number of vertex attributes. 
    @~chinese 得到顶点属性的数量。
    */
    ssize_t getVertexAttribCount() const;
    /**@~english
     Set the vertex attribute value by calling callback.
     * @~chinese 
     * 通过回调函数设置顶点属性值。
     @param name @~english The name of Vertex attrib. @~chinese 顶点属性的名字
     @param callback @~english The callback for setting vertex attrib. @~chinese 设置属性的回调函数。
     */
    void setVertexAttribCallback(const std::string &name, const std::function<void(VertexAttrib*)> &callback);
    /**@~english
     Set the vertex attribute value.
     * @~chinese 
     * 设置顶点属性值。
     @param name @~english The vertex attrib name. @~chinese 顶点属性的名字。
     @param size @~english The count of data in the vertex attrib, range from 0-4. @~chinese 顶点属性的值个数，从0-4。
     @param type @~english The type of data in the vertex attrib @~chinese 顶点数据的类型。
     @param normalized @~english Normalize the data or not 0-255 will be mapped to 0-1.0  @~chinese 数据的归一化标记，0-255被映射到0-1.0
     @param stride @~english The stride of the interleaved array.  @~chinese 交叉顶点属性的顶点数组中的步进。
     @param pointer @~english The data pointer  @~chinese 数据指针。
     */
    void setVertexAttribPointer(const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    
    /**
    @~english Get the number of user defined uniform count. 
    @~chinese 用户自定义的Uniform的个数。
    */
    ssize_t getUniformCount() const { return _uniforms.size(); }
    
    /** @{
     Setting user defined uniforms by uniform string name in the shader.
     */
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param value @~english The int value @~chinese int数值
    */
    void setUniformInt(const std::string &uniformName, int value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param value @~english The float value @~chinese Uniform的float数值。
    */
    void setUniformFloat(const std::string &uniformName, float value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param size @~english The count of value @~chinese float数值的个数
    @param pointer @~english The pointer of float value @~chinese Uniform的float数值指针
    */
    void setUniformFloatv(const std::string &uniformName, ssize_t size, const float* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param value @~english The Vec2 value @~chinese Uniform的Vec2数值。
    */
    void setUniformVec2(const std::string &uniformName, const Vec2& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param size @~english The count of value @~chinese Vec2数值的个数
    @param pointer @~english The pointer of Vec2 value @~chinese Uniform的Vec2数值指针
    */
    void setUniformVec2v(const std::string &uniformName, ssize_t size, const Vec2* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param value @~english The Vec3 value @~chinese Uniform的Vec3数值。
    */
    void setUniformVec3(const std::string &uniformName, const Vec3& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param size @~english The count of value @~chinese Vec3数值的个数
    @param pointer @~english The pointer of Vec3 value @~chinese Uniform的Vec3数值指针
    */
    void setUniformVec3v(const std::string &uniformName, ssize_t size, const Vec3* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param value @~english The Vec4 value @~chinese Uniform的Vec4数值。
    */
    void setUniformVec4(const std::string &uniformName, const Vec4& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param size @~english The count of value @~chinese Vec4数值的个数
    @param pointer @~english The pointer of Vec4 value @~chinese Uniform的Vec4数值指针
    */
    void setUniformVec4v(const std::string &uniformName, ssize_t size, const Vec4* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param value @~english The Mat4 value @~chinese Uniform的Mat4数值
    */
    void setUniformMat4(const std::string &uniformName, const Mat4& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param callback @~english callback function for uniform @~chinese Uniform的回调函数。
    */
    void setUniformCallback(const std::string &uniformName, const std::function<void(GLProgram*, Uniform*)> &callback);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param texture @~english The texture value，the openGL handle will be used @~chinese Uniform的纹理值。
    */
    void setUniformTexture(const std::string &uniformName, Texture2D *texture);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformName @~english The name of uniform. @~chinese Uniform的名字。
    @param textureId @~english The texture value @~chinese Uniform的纹理值。
    */
    void setUniformTexture(const std::string &uniformName, GLuint textureId);
    /**@}*/
    
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param value @~english The int value @~chinese int数值
    */
    void setUniformInt(GLint uniformLocation, int value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param value @~english The float value @~chinese Uniform的float数值。
    */
    void setUniformFloat(GLint uniformLocation, float value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param size @~english The count of value @~chinese float数值的个数
    @param pointer @~english The pointer of float value @~chinese Uniform的float数值指针
    */
    void setUniformFloatv(GLint uniformLocation, ssize_t size, const float* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param value @~english The Vec2 value @~chinese Uniform的Vec2数值。
    */
    void setUniformVec2(GLint uniformLocation, const Vec2& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param size @~english The count of value @~chinese Vec2数值的个数
    @param pointer @~english The pointer of Vec2 value @~chinese Uniform的Vec2数值指针
    */
    void setUniformVec2v(GLint uniformLocation, ssize_t size, const Vec2* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param value @~english The Vec3 value @~chinese Uniform的Vec3数值。
    */
    void setUniformVec3(GLint uniformLocation, const Vec3& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param size @~english The count of value @~chinese Vec3数值的个数
    @param pointer @~english The pointer of Vec3 value @~chinese Uniform的Vec3数值指针
    */
    void setUniformVec3v(GLint uniformLocation, ssize_t size, const Vec3* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param value @~english The Vec4 value @~chinese Uniform的Vec4数值。
    */
    void setUniformVec4(GLint uniformLocation, const Vec4& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param size @~english The count of value @~chinese Vec4数值的个数
    @param pointer @~english The pointer of Vec4 value @~chinese Uniform的Vec4数值指针
    */
    void setUniformVec4v(GLint uniformLocation, ssize_t size, const Vec4* pointer);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param value @~english The Mat4 value @~chinese Uniform的Mat4数值
    */
    void setUniformMat4(GLint uniformLocation, const Mat4& value);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param callback @~english callback function for uniform @~chinese Uniform的回调函数。
    */
    void setUniformCallback(GLint uniformLocation, const std::function<void(GLProgram*, Uniform*)> &callback);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param texture @~english The texture value，the openGL handle will be used @~chinese Uniform的纹理值。
    */
    void setUniformTexture(GLint uniformLocation, Texture2D *texture);
    /**
    @~english set the value for uniform.
    @~chinese 设置Uniform数值.
    @param uniformLocation @~english The location of uniform. @~chinese Uniform的位置。
    @param textureId @~english The texture value @~chinese Uniform的纹理值。
    */
    void setUniformTexture(GLint uniformLocation, GLuint textureId);
    /**@}*/

    /** 
     * Returns the Node bound to the GLProgramState
     */
    Node* getNodeBinding() const;

    /**
     * Sets the node that this render state is bound to.
     *
     * The specified node is used to apply auto-bindings for the render state.
     * This is typically set to the node of the model that a material is
     * applied to.
     *
     * @param node The node to use for applying auto-bindings.
     */
    void setNodeBinding(Node* node);

    /**
     * Applies the specified custom auto-binding.
     *
     * @param uniformName Name of the shader uniform.
     * @param autoBinding Name of the auto binding.
     */
    void applyAutoBinding(const std::string& uniformName, const std::string& autoBinding);

    /**
     * Sets a uniform auto-binding.
     *
     * This method parses the passed in autoBinding string and attempts to convert it
     * to an enumeration value. If it matches to one of the predefined strings, it will create a
     * callback to get the correct value at runtime.
     *
     * @param uniformName The name of the material parameter to store an auto-binding for.
     * @param autoBinding A string matching one of the built-in AutoBinding enum constants.
     */
    void setParameterAutoBinding(const std::string& uniformName, const std::string& autoBinding);

    /**
     * An abstract base class that can be extended to support custom material auto bindings.
     *
     * Implementing a custom auto binding resolver allows the set of built-in parameter auto
     * bindings to be extended or overridden. Any parameter auto binding that is set on a
     * material will be forwarded to any custom auto binding resolvers, in the order in which
     * they are registered. If a registered resolver returns true (specifying that it handles
     * the specified autoBinding), no further code will be executed for that autoBinding.
     * This allows auto binding resolvers to not only implement new/custom binding strings,
     * but it also lets them override existing/built-in ones. For this reason, you should
     * ensure that you ONLY return true if you explicitly handle a custom auto binding; return
     * false otherwise.
     *
     * Note that the custom resolver is called only once for a GLProgramState object when its
     * node binding is initially set. This occurs when a material is initially bound to a
     * Node. The resolver is NOT called each frame or each time the GLProgramState is bound.
     *
     * If no registered resolvers explicitly handle an auto binding, the binding will attempt
     * to be resolved using the internal/built-in resolver, which is able to handle any
     * auto bindings found in the GLProgramState::AutoBinding enumeration.
     *
     * When an instance of a class that extends AutoBindingResolver is created, it is automatically
     * registered as a custom auto binding handler. Likewise, it is automatically unregistered
     * on destruction.
     *
     * @js NA
     * @lua NA
     */
    class CC_DLL AutoBindingResolver
    {
    public:

        /**
         * Destructor.
         */
        virtual ~AutoBindingResolver();

        /**
         * Called when an unrecognized uniform variable is encountered
         * during material loading.
         *
         * Implementations of this method should do a string comparison on the passed
         * in name parameter and decide whether or not they should handle the
         * parameter. If the parameter is not handled, false should be returned so
         * that other auto binding resolvers get a chance to handle the parameter.
         * Otherwise, the parameter should be set or bound and true should be returned.
         *
         * @param glProgramState The glProgramState
         * @param node The node that the material is attached to.
         * @param uniformName Name of the uniform
         * @param autoBinding Name of the auto binding to be resolved.
         *
         * @return True if the auto binding is handled and the associated parameter is
         *      bound, false otherwise.
         */
        virtual bool resolveAutoBinding(GLProgramState* glProgramState, Node* node, const std::string& uniformName, const std::string& autoBinding) = 0;

    protected:

        /**
         * Constructor.
         */
        AutoBindingResolver();
    };

protected:
    GLProgramState();
    ~GLProgramState();
    bool init(GLProgram* program);
    void resetGLProgram();
    void updateUniformsAndAttributes();
    VertexAttribValue* getVertexAttribValue(const std::string& attributeName);
    UniformValue* getUniformValue(const std::string& uniformName);
    UniformValue* getUniformValue(GLint uniformLocation);


    bool _uniformAttributeValueDirty;
    std::unordered_map<std::string, GLint> _uniformsByName;
    std::unordered_map<GLint, UniformValue> _uniforms;
    std::unordered_map<std::string, VertexAttribValue> _attributes;
    std::unordered_map<std::string, int> _boundTextureUnits;

    int _textureUnitIndex;
    uint32_t _vertexAttribsFlags;
    GLProgram* _glprogram;

    Node* _nodeBinding; // weak ref

    // contains uniform name and variable
    std::unordered_map<std::string, std::string> _autoBindings;

    // Map of custom auto binding resolvers.
    static std::vector<AutoBindingResolver*> _customAutoBindingResolvers;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundlistener;
#endif

};

NS_CC_END

/**
 end of support group
 @}
 */
#endif /* __CCGLPROGRAMSTATE_H__ */
