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

/**
 * Uniform Value, which is used to store to value send to openGL pipe line by glUniformXXX.
 *
 * @lua NA
 */
class CC_DLL UniformValue
{
    friend class GLProgram;
    friend class GLProgramState;
public:
    /**
     Constructor. The Uniform and Glprogram will be nullptr.
     */
    UniformValue();
    /**
     Constructor with uniform and glprogram.
     @param uniform Uniform to apply the value.
     @param glprogram Specify the owner GLProgram of this uniform and uniform value.
     */
    UniformValue(Uniform *uniform, GLProgram* glprogram);

    /**Destructor.*/
    ~UniformValue();
    /**@{
     Set data to Uniform value. Generally, there are many type of data could be supported,
     including float, int, Vec2/3/4, Mat4.
     @param value Value to be sent, support float, int, Vec2/3/4, Mat4.
     */
    void setFloat(float value);
    void setInt(int value);
    void setFloatv(ssize_t size, const float* pointer);
    void setVec2(const Vec2& value);
    void setVec2v(ssize_t size, const Vec2* pointer);
    void setVec3(const Vec3& value);
    void setVec3v(ssize_t size, const Vec3* pointer);
    void setVec4(const Vec4& value);
    void setVec4v(ssize_t size, const Vec4* pointer);
    void setMat4(const Mat4& value);
    /**
     @}
     */
    
    /**
     Set call back to uniform value, which could be used for array and struct.
     @param callback Callback function to send data to OpenGL pipeline.
     */
    void setCallback(const std::function<void(GLProgram*, Uniform*)> &callback);
    /**
     Set texture to uniform value.
     @param textureId The texture handle.
     @param textureUnit The binding texture unit to be used in shader.
    */
    void setTexture(GLuint textureId, GLuint textureUnit);
    
    /**Apply the uniform value to openGL pipeline.*/
    void apply();

protected:

    enum class Type {
        VALUE,
        POINTER,
        CALLBACK_FN     // CALLBACK is already defined in windows, can't use it.
    };

    /**Weak reference to Uniform.*/
	Uniform* _uniform;
    /**Weak reference to GLprogram.*/
    GLProgram* _glprogram;
    /** What kind of type is the Uniform */
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
 * Vertex Attribute Value, which is an abstraction of VertexAttribute and data pointer.
 *
 * @lua NA
 */
class CC_DLL VertexAttribValue
{
    friend class GLProgram;
    friend class GLProgramState;
    friend class VertexAttribBinding;

public:
    /**
     Constructor.
     @param vertexAttrib VertexAttrib from shader.
    */
    VertexAttribValue(VertexAttrib *vertexAttrib);
    /**
     Constructor.
     */
    VertexAttribValue();
    /**
     Destructor.
     */
    ~VertexAttribValue();
    
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
    static GLProgramState* getOrCreateWithGLProgramName(const std::string& glProgramName );

    /** gets-or-creates an instance of GLProgramState for the given GLProgramName & texture */
    static GLProgramState* getOrCreateWithGLProgramName(const std::string& glProgramName, Texture2D* texture);

    /** gets-or-creates an instance of GLProgramState for given shaders */
    static GLProgramState* getOrCreateWithShaders(const std::string& vertexShader, const std::string& fragShader, const std::string& compileTimeDefines);

    /** Returns a new copy of the GLProgramState. The GLProgram is reused */
    GLProgramState* clone() const;

    /**
     Apply GLProgram, attributes and uniforms.
     @param modelView The applied modelView matrix to shader.
     */
    void apply(const Mat4& modelView);

    /**
     Apply GLProgram, and built in uniforms.
     @param modelView The applied modelView matrix to shader.
     */
    void applyGLProgram(const Mat4& modelView);
    /**
     Apply attributes.
     @param applyAttribFlags Call GL::enableVertexAttribs(_vertexAttribsFlags) or not.
     */
    void applyAttributes(bool applyAttribFlags = true);
    /**
     Apply user defined uniforms.
     */
    void applyUniforms();
    
    /**@{ 
     Setter and Getter of the owner GLProgram binded in this program state.
     */
    void setGLProgram(GLProgram* glprogram);
    GLProgram* getGLProgram() const { return _glprogram; }
    
    /**@}*/
    
    /** Get the flag of vertex attribs used by OR operation.*/
    uint32_t getVertexAttribsFlags() const;
    /**Get the number of vertex attributes.*/
    ssize_t getVertexAttribCount() const;
    /**@{
     Set the vertex attribute value.
     */
    void setVertexAttribCallback(const std::string& name, const std::function<void(VertexAttrib*)> &callback);
    void setVertexAttribPointer(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
    /**@}*/
    
    /**Get the number of user defined uniform count.*/
    ssize_t getUniformCount() const { return _uniforms.size(); }
    
    /** @{
     Setting user defined uniforms by uniform string name in the shader.
     */
    void setUniformInt(const std::string& uniformName, int value);
    void setUniformFloat(const std::string& uniformName, float value);
    void setUniformFloatv(const std::string& uniformName, ssize_t size, const float* pointer);
    void setUniformVec2(const std::string& uniformName, const Vec2& value);
    void setUniformVec2v(const std::string& uniformName, ssize_t size, const Vec2* pointer);
    void setUniformVec3(const std::string& uniformName, const Vec3& value);
    void setUniformVec3v(const std::string& uniformName, ssize_t size, const Vec3* pointer);
    void setUniformVec4(const std::string& uniformName, const Vec4& value);
    void setUniformVec4v(const std::string& uniformName, ssize_t size, const Vec4* pointer);
    void setUniformMat4(const std::string& uniformName, const Mat4& value);
    void setUniformCallback(const std::string& uniformName, const std::function<void(GLProgram*, Uniform*)> &callback);
    void setUniformTexture(const std::string& uniformName, Texture2D *texture);
    void setUniformTexture(const std::string& uniformName, GLuint textureId);
    /**@}*/
    
    /** @{
     Setting user defined uniforms by uniform location in the shader.
     */
    void setUniformInt(GLint uniformLocation, int value);
    void setUniformFloat(GLint uniformLocation, float value);
    void setUniformFloatv(GLint uniformLocation, ssize_t size, const float* pointer);
    void setUniformVec2(GLint uniformLocation, const Vec2& value);
    void setUniformVec2v(GLint uniformLocation, ssize_t size, const Vec2* pointer);
    void setUniformVec3(GLint uniformLocation, const Vec3& value);
    void setUniformVec3v(GLint uniformLocation, ssize_t size, const Vec3* pointer);
    void setUniformVec4(GLint uniformLocation, const Vec4& value);
    void setUniformVec4v(GLint uniformLocation, ssize_t size, const Vec4* pointer);
    void setUniformMat4(GLint uniformLocation, const Mat4& value);
    void setUniformCallback(GLint uniformLocation, const std::function<void(GLProgram*, Uniform*)> &callback);
    void setUniformTexture(GLint uniformLocation, Texture2D *texture);
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
     * @script{ignore}
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
    virtual ~GLProgramState();
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
