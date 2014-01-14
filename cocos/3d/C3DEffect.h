#ifndef EFFECT_H_
#define EFFECT_H_
#include <string>
#include <map>

#include "Base.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "C3DMatrix.h"
#include "C3DResource.h"

NS_CC_BEGIN

class Uniform;
class C3DTexture;
class C3DSampler;
class ElementNode;
class C3DSamplerCube;

/**
*A C3DEffect wraps an OpenGL program object,includes the
* vertex and fragment shader.It can be applied during rendering.
*/
class C3DEffect: public C3DResource
{
    friend class C3DEffectManager;

public:        

    C3DEffect(const std::string& name);

    virtual ~C3DEffect();    

    /**
    * load cur effect    
    */
    bool load(ElementNode* node);

    /**
    * Returns the vertex attribute handle for the vertex attribute with the specified name.
    *
    * @param name The name of the vertex attribute to return.
    * 
    * @return The vertex attribute, or -1 if no such vertex attribute exists.
    */
    VertexAttribute getVertexAttribute(const char* name) const;

    /**
    * Returns the uniform handle for the uniform with the specified name.
    *
    * @param name The name of the uniform to return.
    * 
    * @return The uniform, or NULL if no such uniform exists.
    */
    Uniform* getUniform(const char* name) const;

    /**
    * Returns the specified active uniform.
    * 
    * @param index The index of the uniform to return.
    * 
    * @return The uniform, or NULL if index is invalid.
    */
    Uniform* getUniform(unsigned int index) const;

    /**
    * Returns the number of active uniforms in this effect.
    * 
    * @return The number of active uniforms.
    */
    unsigned int getUniformCount() const;

    /**
    * Sets a float uniform value.
    *
    * @param uniform The uniform to set.
    * @param value The float value to set.
    */
    void bindValue(Uniform* uniform, float value);

    /**
    * Sets a float array uniform value.
    *
    * @param uniform The uniform to set.
    * @param values The array to set.
    * @param count The number of elements in the array.
    */
    void bindValue(Uniform* uniform, const float* values, unsigned int count = 1);

    /**
    * Sets an integer uniform value.
    *
    * @param uniform The uniform to set.
    * @param value The value to set.
    */
    void bindValue(Uniform* uniform, int value);

    /**
    * Sets an integer array uniform value.
    *
    * @param uniform The uniform to set.
    * @param values The array to set.
    * @param count The number of elements in the array.
    */
    void bindValue(Uniform* uniform, const int* values, unsigned int count = 1);

    /**
    * Sets a matrix uniform value.
    *
    * @param uniform The uniform to set.
    * @param value The value to set.
    */
    void bindValue(Uniform* uniform, const Matrix& value);

    /**
    * Sets a matrix array uniform value.
    *
    * @param uniform The uniform to set.
    * @param values The array to set.
    * @param count The number of elements in the array.
    */
    void bindValue(Uniform* uniform, const Matrix* values, unsigned int count = 1);

    /**
    * Sets a vector uniform value.
    *
    * @param uniform The uniform to set.
    * @param value The value to set.
    */
    void bindValue(Uniform* uniform, const Vector2& value);

    /**
    * Sets a vector array uniform value.
    *
    * @param uniform The uniform to set.
    * @param values The array to set.
    * @param count The number of elements in the array.
    */
    void bindValue(Uniform* uniform, const Vector2* values, unsigned int count = 1);

    /**
    * Sets a vector uniform value.
    *
    * @param uniform The uniform to set.
    * @param value The value to set.
    */
    void bindValue(Uniform* uniform, const Vector3& value);

    /**
    * Sets a vector array uniform value.
    *
    * @param uniform The uniform to set.
    * @param values The array to set.
    * @param count The number of elements in the array.
    */
    void bindValue(Uniform* uniform, const Vector3* values, unsigned int count = 1);

    /**
    * Sets a vector uniform value.
    *
    * @param uniform The uniform to set.
    * @param value The value to set.
    */
    void bindValue(Uniform* uniform, const Vector4& value);

    /**
    * Sets a vector array uniform value.
    *
    * @param uniform The uniform to set.
    * @param values The array to set.
    * @param count The number of elements in the array.
    */
    void bindValue(Uniform* uniform, const Vector4* values, unsigned int count = 1);

    /**
    * Sets a sampler uniform value.
    *
    * @param uniform The uniform to set.
    * @param sampler The sampler to set.
    */
    void bindValue(Uniform* uniform, const C3DSampler* sampler);
    void bindValue(Uniform* uniform, const C3DTexture* texture);

    /**
    * Binds this effect to make it the currently active effect for the rendering system.
    */
    void bind();

    static C3DEffect* getCurrentEffect();

private:

    /**
    * load an effect from the given vertex and fragment shader source code.
    *
    * @param vshSource The vertex shader source code.
    * @param fshSource The fragment shader source code.
    * @param defines A new-line delimited list of preprocessor defines. May be NULL.
    * 
    * @return The created effect.
    */
    bool load(const char* vshSource, const char* fshSource, const char* defines);

    GLuint _program;

    std::map<std::string, VertexAttribute> _vertexAttributes;
    std::map<std::string, Uniform*> _uniforms;
    static Uniform _emptyUniform;

    std::string _vshPath;
    std::string _fshPath;
    std::string _defines;
};

/**
* Represents a uniform variable within an effect.
*/
class Uniform
{
    friend class C3DEffect;

public:

    /**
    * Returns the name of this uniform.
    * 
    * @return The name of the uniform.
    */
    const std::string& getName() const;

    /**
    * Returns the OpenGL uniform type.
    * 
    * @return The OpenGL uniform type.
    */
    const GLenum getType() const;

    /**
    * Returns the effect for this uniform.
    *
    * @return The uniform's effect.
    */
    C3DEffect* getEffect() const;

private:

    /**
    * Constructor.
    */
    Uniform();

    /**
    * Copy constructor.
    */
    Uniform(const Uniform& copy);

    /**
    * Destructor.
    */
    ~Uniform();

    std::string _name;
    GLint _location;
    GLenum _type;
    unsigned int _index;
    C3DEffect* _effect;
};

NS_CC_END

#endif // EFFECT_H_
