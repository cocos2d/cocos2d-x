#ifndef MATERIALPARAMETER_H_
#define MATERIALPARAMETER_H_

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "C3DMatrix.h"

#include "C3DEffect.h"
#include "cocos2d.h"

NS_CC_BEGIN

class C3DSamplerCube;

/**
* Defines a material parameter.
*
* This class represents a parameter that can be set for a material.
* The methods in this class provide a mechanism to set parameters
* of all supported types. Some types support setting by value,
* while others only support setting by reference/pointer.
*/
class MaterialParameter : public cocos2d::CCObject
{
    friend class C3DRenderState;
    friend class C3DPass;
    friend class C3DMaterial;

public:

    /**
    * Animates the uniform.
    */
    static const int ANIMATE_UNIFORM = 1;

    /**
    * Returns the name of this material parameter.
    */
    const char* getName() const;

    /**
    * Sets the value of this parameter to a float value.
    */
    void setValue(float value);

    /**
    * Sets the value of this parameter to an integer value.
    */
    void setValue(int value);

    /**
    * Stores a pointer/array of float values in this parameter.
    */
    void setValue(const float* values, unsigned int count = 1);

    /**
    * Stores a pointer/array of integer values in this parameter.
    */
    void setValue(const int* values, unsigned int count = 1);

    /**
    * Stores a copy of the specified Vector2 value in this parameter.
    */
    void setValue(const Vector2& value);

    /**
    * Stores a pointer/array of Vector2 values in this parameter.
    */
    void setValue(const Vector2* values, unsigned int count = 1);

    /**
    * Stores a copy of the specified Vector3 value in this parameter.
    */
    void setValue(const Vector3& value);

    /**
    * Stores a pointer/array of Vector3 values in this parameter.
    */
    void setValue(const Vector3* values, unsigned int count = 1);

    /**
    * Stores a copy of the specified Vector4 value in this parameter.
    */
    void setValue(const Vector4& value);

    /**
    * Stores a pointer/array of Vector4 values in this parameter.
    */
    void setValue(const Vector4* values, unsigned int count = 1);

    /**
    * Stores a copy of the specified Matrix value in this parameter.
    */
    void setValue(const Matrix& value);

    /**
    * Stores a pointer/array of Matrix values in this parameter.
    */
    void setValue(const Matrix* values, unsigned int count = 1);

    /**
    * Sets the value of this parameter to the specified texture sampler.
    */
    void setValue(const C3DSampler* sampler);

    void setValue(const C3DSamplerCube* sampler);

    void setValue(const C3DTexture* texture);

    /**
    * Loads a texture sampler from the specified path and sets it as the value of this parameter.
    *
    * @param texturePath The path to the texture to set.
    * @param generateMipmaps True to generate a full mipmap chain for the texture, false otherwise.
    *
    * @return The texture sampler that was set for this material parameter.
    */
    C3DSampler* setValue(const char* texturePath, bool generateMipmaps);

    /**
    * Binds the return value of a class method to this material parameter.
    */
    template <class ClassType, class ParameterType>
    void setValue(ClassType* classInstance, ParameterType (ClassType::*valueMethod)());

    /**
    * Binds the return value of a class method to this material parameter.     
    */
    template <class ClassType, class ParameterType>
    void setValue(ClassType* classInstance, ParameterType (ClassType::*valueMethod)(unsigned int index), 
        unsigned int (ClassType::*countMethod)(unsigned int index),unsigned int (ClassType::*indexMethod)());


    Uniform* getUniform() const;

    MaterialParameter* clone() const;

    int getType() const {return _type;}
    float getFloatValue() const {return _value.floatValue;}
    int getIntValue() const {return _value.intValue;}
    float* getFloatPtrValue() const {return _value.floatPtrValue;}
    int* getIntPtrValue() const {return _value.intPtrValue;}
    const C3DSampler* getSamplerValue() const {return _value.samplerValue;}
    const C3DTexture* getTextureValue() const {return _value.textureValue;}

public:
    enum
    {
        NONE,
        FLOAT,
        INT,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        MATRIX,
        SAMPLER,
        SAMPLERCUBE,
        TEXTURE,
        METHOD,
        METHOD_PARAM
    } _type;

private:

    MaterialParameter(const char* name);

    ~MaterialParameter();

    /**
    * Interface implemented by templated method bindings for simple storage and iteration.
    */
    class MethodBinding : public cocos2d::CCObject
    {
    public:
        virtual void bindValue(C3DEffect* effect) = 0;
        virtual MethodBinding* clone() const = 0;

    protected:
        /**
        * Destructor.
        */
        virtual ~MethodBinding() { }
    };

    /**
    * Defines a method parameter binding for a single value.
    */
    template <class ClassType, class ParameterType>
    class MethodValueBinding : public MethodBinding
    {
        typedef ParameterType (ClassType::*ValueMethod)();
    public:
        MethodValueBinding(MaterialParameter* param, ClassType* instance, ValueMethod valueMethod);
        void bindValue(C3DEffect* effect);
        virtual MethodBinding* clone() const;

    private:
        MaterialParameter* _parameter;
        ClassType* _instance;
        ValueMethod _valueMethod;

    };

    template <class ClassType, class ParameterType>
    class MethodArrayBinding : public MethodBinding
    {
        typedef ParameterType (ClassType::*ValueMethod)(unsigned int index);
        typedef unsigned int (ClassType::*CountMethod)(unsigned int index);
        typedef unsigned int (ClassType::*IndexMethod)();
    public:
        MethodArrayBinding(MaterialParameter* param, ClassType* instance, ValueMethod valueMethod, CountMethod countMethod, IndexMethod indexMethod);
        void bindValue(C3DEffect* effect);
        virtual MethodBinding* clone() const;

    private:
        MaterialParameter* _parameter;
        ClassType* _instance;
        ValueMethod _valueMethod;
        CountMethod _countMethod;
        IndexMethod _indexMethod;
    };

    void clearValue();

    void bind(C3DEffect* effect);

    void setParamMethonAutoUniform(C3DEffect* effect);

    union
    {
        float floatValue;
        int intValue;
        float* floatPtrValue;
        int* intPtrValue;
        const C3DSampler* samplerValue;
        const C3DSamplerCube* samplerCubeValue;
        const C3DTexture* textureValue;
        MethodBinding* method;
    } _value;

    unsigned int _count;
    bool _dynamic;
    std::string _name;
    Uniform* _uniform;
};

template <class ClassType, class ParameterType>
void MaterialParameter::setValue(ClassType* classInstance, ParameterType (ClassType::*valueMethod)())
{
    clearValue();

    _value.method = new MethodValueBinding<ClassType, ParameterType>(this, classInstance, valueMethod);
    _dynamic = true;
    _type = MaterialParameter::METHOD;
}

template <class ClassType, class ParameterType>
void MaterialParameter::setValue(ClassType* classInstance, ParameterType (ClassType::*valueMethod)(unsigned int index), 
    unsigned int (ClassType::*countMethod)(unsigned int index), unsigned int (ClassType::*indexMethod)())
{
    clearValue();

    _value.method = new MethodArrayBinding<ClassType, ParameterType>(this, classInstance, valueMethod, countMethod,indexMethod);
    _dynamic = true;
    _type = MaterialParameter::METHOD_PARAM;
}

template <class ClassType, class ParameterType>
MaterialParameter::MethodValueBinding<ClassType, ParameterType>::MethodValueBinding(MaterialParameter* param, ClassType* instance, ValueMethod valueMethod) :
_parameter(param), _instance(instance), _valueMethod(valueMethod)
{
}

template <class ClassType, class ParameterType>
MaterialParameter::MethodBinding* cocos2d::MaterialParameter::MethodValueBinding<ClassType, ParameterType>::clone() const
{
    MethodValueBinding<ClassType, ParameterType>* other = new MethodValueBinding<ClassType, ParameterType>(_parameter, _instance, _valueMethod);
    return other;
}


template <class ClassType, class ParameterType>
void MaterialParameter::MethodValueBinding<ClassType, ParameterType>::bindValue(C3DEffect* effect)
{
    effect->bindValue(_parameter->_uniform, (_instance->*_valueMethod)());
}

template <class ClassType, class ParameterType>
MaterialParameter::MethodArrayBinding<ClassType, ParameterType>::MethodArrayBinding(MaterialParameter* param, ClassType* instance, ValueMethod valueMethod, CountMethod countMethod, IndexMethod indexMethod) :
_parameter(param), _instance(instance), _valueMethod(valueMethod), _countMethod(countMethod), _indexMethod(indexMethod)
{
}

template <class ClassType, class ParameterType>
void MaterialParameter::MethodArrayBinding<ClassType, ParameterType>::bindValue(C3DEffect* effect)
{
    int index = (_instance->*_indexMethod)();
    effect->bindValue(_parameter->_uniform, (_instance->*_valueMethod)(index), (_instance->*_countMethod)(index));
}

template <class ClassType, class ParameterType>
MaterialParameter::MethodBinding* cocos2d::MaterialParameter::MethodArrayBinding<ClassType, ParameterType>::clone() const
{
    MethodArrayBinding<ClassType, ParameterType>* other = new MethodArrayBinding<ClassType, ParameterType>(_parameter, _instance, _valueMethod, _countMethod, _indexMethod);
    return other;
}

NS_CC_END

#endif // MATERIALPARAMETER_H_
