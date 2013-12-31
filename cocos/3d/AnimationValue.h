#ifndef ANIMATIONVALUE_H_
#define ANIMATIONVALUE_H_


namespace cocos2d
{
/**
 * Defines a interface to describe the animation value.
 */
class AnimationValue
{
    friend class C3DAnimationClip;

public:
    /**
     * Gets the value by the specified index.
     *
     * @param index The index of the component to get the value for.
     *
     * @return The float value at the specified index.
     */
    float getFloat(unsigned int index) const;

    /**
     * Sets the value by the specified index.
     *
     * @param index The index of the component to set the value for.
     * @param value The value to set the component to.
     */
    void setFloat(unsigned int index, float value);

private:

    /**
     * Constructor.
     */
    AnimationValue(unsigned int componentCount);

    /**
     * Destructor.
     */
    ~AnimationValue();

    unsigned int _componentCount;   // The number of float values for the property.
    unsigned int _componentSize;    // The number of bytes of memory the property is.
    float* _value;                  // The current value of the property.

};

}

#endif
