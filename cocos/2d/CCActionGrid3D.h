/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__

#include "2d/CCActionGrid.h"

NS_CC_BEGIN

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief @~english Waves3D action.
 * @~chinese Waves3D动作。
 * @details @~english This action is used for making 3D waves effect on the target node.
        You can control the effect by these parameters:
        duration, grid size, waves count, amplitude.
 * @~chinese 该动作用于在目标节点上制造3D波浪效果。
 * 你可以控制这些参数来影响效果:
 * 持续时间、网格大小、波浪的数量、振幅。
*/
class CC_DLL Waves3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create an action with duration, grid size, waves and amplitude.
     * @~chinese 使用持续时间、网格大小、波浪的数量和振幅来创建一个Wave3D动作。
    @param duration @~english Specify the duration of the Waves3D action. It's a value in seconds.
     * @~chinese 指定的持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param waves @~english Specify the waves count of the Waves3D action.
     * @~chinese 波浪的数量。
    @param amplitude @~english Specify the amplitude of the Waves3D action.
     * @~chinese 振幅。
    @return @~english If the creation sucess, return a pointer of Waves3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个指针Waves3D动作，否则，返回空指针。
    */
    static Waves3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese 获取Wave3D特效的振幅。
    @return @~english Return the amplitude of the effect.
     * @~chinese 返回振幅。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese 设置Wave3D特效的振幅。
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese 振幅的值。
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese 获得振幅衰减率。
    @return @~english Return the amplitude rate of the effect.
     * @~chinese 返回振幅衰减率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese 设置振幅衰减率。
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese 振幅衰减率。
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

	// Overrides
	virtual Waves3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves3D() {}
    virtual ~Waves3D() {}

    /** 
    @brief @~english Initializes an action with duration, grid size, waves and amplitude.
     * @~chinese 使用持续时间、网格大小、波浪的数量和振幅来初始化一个Wave3D动作。
    @param duration @~english Specify the duration of the Waves3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param waves @~english Specify the waves count of the Waves3D action.
     * @~chinese 波浪的数量。
    @param amplitude @~english Specify the amplitude of the Waves3D action.
     * @~chinese 振幅。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Waves3D);
};

/**
@brief @~english FlipX3D action.
 * @~chinese FlipX3D行动。
@details @~english This action is used for flipping the target node on the x axis.
 * @~chinese 该动作用于将目标节点沿x轴进行翻转。
*/
class CC_DLL FlipX3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration.
     * @~chinese 用持续时间创建FlipX3D动作。
    @param duration @~english Specify the duration of the FilpX3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @return @~english If the creation sucess, return a pointer of FilpX3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个指针FilpX3D动作，否则，返回空指针。
    */
    static FlipX3D* create(float duration);

    // Override
	virtual FlipX3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FlipX3D() {}
    virtual ~FlipX3D() {}

    /** 
    @brief @~english Initializes an action with duration.
     * @~chinese 用持续时间初始化FlipX3D动作。
    @param duration @~english Specify the duration of the FlipX3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithDuration(float duration);

    /** 
    @brief @~english Initializes an action with duration and grid size.
     * @~chinese 用持续时间和网格大小初始化Flip3D动作。
    @param gridSize @~english Specify the grid size of the FlipX3D action.
     * @~chinese 网格的大小.
    @param duration @~english Specify the duration of the FlipX3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    virtual bool initWithSize(const Size& gridSize, float duration);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipX3D);
};

/**
@brief @~english FlipY3D action.
 * @~chinese FlipY3D行动。
@details @~english This action is used for flipping the target node on the y axis.
 * @~chinese 该动作用于将目标节点沿y轴进行翻转。
*/
class CC_DLL FlipY3D : public FlipX3D
{
public:
    /**
    @brief @~english Create the action with duration.
     * @~chinese 用持续时间创建FlipY3D动作。
    @param duration @~english Specify the duration of the FlipY3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @return @~english If the creation sucess, return a pointer of FlipY3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个指针FlipY3D动作，否则，返回空指针。
    */
    static FlipY3D* create(float duration);

    // Overrides
    virtual void update(float time) override;
	virtual FlipY3D* clone() const override;

CC_CONSTRUCTOR_ACCESS:
    FlipY3D() {}
    virtual ~FlipY3D() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FlipY3D);
};

/**
@brief @~english Lens3D action.
 * @~chinese Lens3D动作。
 * @details @~english This action is used for take effect on the target node as lens.
        You can create the action by these parameters:
        duration, grid size, center position of lens, radius of lens.
        Also you can change the lens effect value & whether effect is concave by the setter methods.
 * @~chinese 该动作用于在目标节点上产生3D镜头特效。
 * 你可以用这些参数定制动作:
 * 持续时间、网格尺寸、镜头的中心位置、镜头的半径。
 * 也可以设置透镜值和选择镜头效果是否是凹面的。
*/
class CC_DLL Lens3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with center position, radius, a grid size and duration.
     * @~chinese 用镜头中心位置，半径，网格的大小和持续时间创建一个Lens3D动作。
    @param duration @~english Specify the duration of the Lens3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param position @~english Specify the center position of the lens.
     * @~chinese 镜头的中心位置。
    @param radius @~english Specify the radius of the lens.
     * @~chinese 镜头的半径。
    @return @~english If the creation sucess, return a pointer of Lens3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个指针Lens3D动作，否则，返回空指针。
    */
    static Lens3D* create(float duration, const Size& gridSize, const Vec2& position, float radius);

    /**
    @brief @~english Get the value of lens effect. Default value is 0.7.
     * @~chinese 获取透镜值，默认值是0.7。
    @return @~english The value of lens effect.
     * @~chinese 透镜值。
    */
    inline float getLensEffect() const { return _lensEffect; }

    /**
    @brief @~english Set the value of lens effect.
     * @~chinese 设置透镜值。
    @param lensEffect @~english The value of lens effect will be set.
     * @~chinese 透镜值。
    */
    inline void setLensEffect(float lensEffect) { _lensEffect = lensEffect; }

    /**
    @brief @~english Set whether lens is concave.
     * @~chinese 设置镜头是否为凹面。
    @param concave @~english Whether lens is concave.
     * @~chinese 镜头是否为凹面。
    */
    inline void setConcave(bool concave) { _concave = concave; }

    /**
    @brief @~english Get the center position of lens effect.
     * @~chinese 获取镜头的中心位置。
    @return @~english The center position of lens effect.
     * @~chinese 镜头的中心位置。
    */
    inline const Vec2& getPosition() const { return _position; }

    /**
    @brief @~english Set the center position of lens effect.
     * @~chinese 设置镜头的中心位置。
    @param position @~english The center position will be set.
     * @~chinese 镜头的中心位置。
    */
    void setPosition(const Vec2& position);

    // Overrides
	virtual Lens3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Lens3D() {}
    virtual ~Lens3D() {}

    /**
    @brief @~english Initializes the action with center position, radius, grid size and duration.
     * @~chinese 用镜头中心位置，半径，网格的大小和持续时间初始化一个Lens3D动作。
    @param duration @~english Specify the duration of the Lens3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param position @~english Specify the center position of the lens.
     * @~chinese 镜头的中心位置。
    @param radius @~english Specify the radius of the lens.
     * @~chinese 镜头的半径。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius);

protected:
    /* @~english lens center position  @~chinese 镜头的中心位置 */
    Vec2 _position;
    float _radius;
    /** @~english lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect  @~chinese 透镜值，默认为0.7 - 0意味着没有效果，1是很强的效果*/
    float _lensEffect;
    /** @~english lens is concave. (true = concave, false = convex) default is convex  @~chinese 镜头是凹面的。(true=凹,false=凸)默认是凸面的 */
    bool _concave;

    bool _dirty;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Lens3D);
};

/**
@brief @~english Ripple3D action.
 * @~chinese 3D波纹（Ripple3D）动作。
 * @details @~english This action is used for take effect on the target node as ripple.
        You can create the action by these parameters:
        duration, grid size, center position of ripple,
        radius of ripple, waves count, amplitude.
 * @~chinese 该动作用于在目标节点上产生波纹特效。
 * 你可以用这些参数定制效果:
 * 持续时间、网格大小、波纹的中心位置、波纹的半径、波纹的数量、振幅。
*/
class CC_DLL Ripple3D : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with center position, radius, number of waves, amplitude, a grid size and duration.
     * @~chinese 用中心位置，半径，波纹的数量，振幅，网格的大小和持续时间来创建一个Ripple3D动作。
    @param duration @~english Specify the duration of the Ripple3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param position @~english Specify the center position of the ripple effect.
     * @~chinese 波纹的中心位置。
    @param radius @~english Specify the radius of the ripple effect.
     * @~chinese 波纹的半径.
    @param waves @~english Specify the waves count of the ripple effect.
     * @~chinese 波纹的数量。
    @param amplitude @~english Specify the amplitude of the ripple effect.
     * @~chinese 波纹的振幅。
    @return @~english If the creation sucess, return a pointer of Ripple3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个Ripple3D行动，否则，返回空指针。
    */
    static Ripple3D* create(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the center position of ripple effect.
     * @~chinese 获取波纹的中心位置。
    @return @~english The center position of ripple effect.
     * @~chinese 波纹中心位置。
    */
    inline const Vec2& getPosition() const { return _position; }
    /**
    @brief @~english Set the center position of ripple effect.
     * @~chinese 设置波纹的中心位置。
    @param position @~english The center position of ripple effect will be set.
     * @~chinese 波纹的中心位置。
    */
    void setPosition(const Vec2& position);

    /**
    @brief @~english Get the amplitude of ripple effect.
     * @~chinese 获取的波纹的振幅。
    @return @~english The amplitude of ripple effect.
     * @~chinese 波纹的振幅。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude of ripple effect.
     * @~chinese 设置波纹的振幅。
    @param fAmplitude @~english The amplitude of ripple effect.
     * @~chinese 波纹的振幅。
    */
    inline void setAmplitude(float fAmplitude) { _amplitude = fAmplitude; }

    /**
    @brief @~english Get the amplitude rate of ripple effect.
     * @~chinese 获取波纹的振幅衰减率。
    @return @~english The amplitude rate of ripple effect.
     * @~chinese 振幅衰减率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the amplitude rate of ripple effect.
     * @~chinese 设置波纹的振幅衰减率。
    @param fAmplitudeRate @~english The amplitude rate of ripple effect.
     * @~chinese 振幅衰减率。
    */
    inline void setAmplitudeRate(float fAmplitudeRate) { _amplitudeRate = fAmplitudeRate; }

    // Override
	virtual Ripple3D* clone() const override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    Ripple3D() {}
    virtual ~Ripple3D() {}

    /**
    @brief @~english Initializes the action with center position, radius, number of waves, amplitude, a grid size and duration.
     * @~chinese 用中心位置，半径，波纹的数量，振幅，网格的大小和持续时间来初始化一个Ripple3D动作。
    @param duration @~english Specify the duration of the Ripple3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param position @~english Specify the center position of the ripple effect.
     * @~chinese 波纹的中心位置。
    @param radius @~english Specify the radius of the ripple effect.
     * @~chinese 波纹的半径.
    @param waves @~english Specify the waves count of the ripple effect.
     * @~chinese 波纹的数量。
    @param amplitude @~english Specify the amplitude of the ripple effect.
     * @~chinese 波纹的振幅。
    @return @~english If the initialization success, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
     */
    bool initWithDuration(float duration, const Size& gridSize, const Vec2& position, float radius, unsigned int waves, float amplitude);

protected:
    /* @~english The center position of the ripple effect  @~chinese 波纹的中心位置 */
    Vec2 _position;
    /* @~english The radius of the ripple effect  @~chinese 波纹的半径 */
    float _radius;
    /* @~english The wave count of the ripple effect  @~chinese 波纹的数量 */
    unsigned int _waves;
    /* @~english The amplitude of the ripple effect  @~chinese 波纹的振幅 */
    float _amplitude;
    /* @~english The amplitude rate of the ripple effect  @~chinese 波纹的振幅衰减率 */
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Ripple3D);
};

/**
@brief @~english Shaky3D action.
 * @~chinese 3D摇晃（Shaky3D）动作。
 * @details @~english This action is used for take effect on the target node as shaky.
        You can create the action by these parameters:
        duration, grid size, range, whether shake on the z axis.
 * @~chinese 该动作用于在目标节点上制造摇晃的视觉特效。
 * 你可以改变这些参数来定制效果:
 * 持续时间、网格大小、范围、是否在z轴摇晃。
*/
class CC_DLL Shaky3D : public Grid3DAction
{
public:
    /** 
    @brief @~english Create the action with duration, grid size, range and whether shake on Z axis.
     * @~chinese 用持续时间、网格大小、范围、是否在z轴摇晃等参数来创建一个Shaky3D动作。
    @param initWithDuration @~english Specify the duration of the Shaky3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param range @~english Specify the range of the shaky effect.
     * @~chinese 晃动特效的范围。
    @param shakeZ @~english Specify whether shake on the z axis.
     * @~chinese 指定是否在z轴晃动。
    @return @~english If the creation sucess, return a pointer of Shaky3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个Shaky3D动作，否则，返回空指针。
    */
    static Shaky3D* create(float initWithDuration, const Size& gridSize, int range, bool shakeZ);

    // Overrides
	virtual Shaky3D* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Shaky3D() {}
    virtual ~Shaky3D() {}
    
    /** 
    @brief @~english Initializes the action with duration, grid size, range and whether shake on Z axis.
     * @~chinese 用持续时间、网格大小、范围、是否在z轴摇晃等参数来初始化一个Shaky3D动作。
    @param duration @~english Specify the duration of the Shaky3D action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param range @~english Specify the range of the shaky effect.
     * @~chinese 晃动特效的范围。
    @param shakeZ @~english Specify whether shake on the z axis.
     * @~chinese 指定是否在z轴晃动。
    @return @~english If the creation sucess, return a pointer of Shaky3D action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个Shaky3D动作，否则，返回空指针。
    */
    bool initWithDuration(float duration, const Size& gridSize, int range, bool shakeZ);

protected:
    int _randrange;
    bool _shakeZ;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Shaky3D);
};

/**
@brief @~english Liquid action.
 * @~chinese 液体（Liquid）动作。
 * @details @~english This action is used for take effect on the target node as liquid.
        You can create the action by these parameters:
        duration, grid size, waves count, amplitude of the liquid effect.
 * @~chinese 该动作用于在目标节点上制造液体效果。
 * 你可以用这些参数定制特效:
 * 持续时间、网格大小、波的数量、液体特效的振幅。
*/
class CC_DLL Liquid : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration, grid size, waves count and amplitude.
     * @~chinese 用持续时间、网格大小、波的数量和振幅来创建一个Liquid动作。
    @param duration @~english Specify the duration of the Liquid action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param waves @~english Specify the waves count of the Liquid action.
     * @~chinese 波的数量。
    @param amplitude @~english Specify the amplitude of the Liquid action.
     * @~chinese Liquid动作的振幅。
    @return @~english If the creation sucess, return a pointer of Liquid action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个Liquid动作，否则，返回空指针。
    */
    static Liquid* create(float duration, const Size& gridSize, unsigned int waves, float amplitude);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese 获取振幅。
    @return @~english Return the amplitude of the effect.
     * @~chinese 振幅。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese 设置振幅。
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese 振幅。
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese 获得振幅衰减率。
    @return @~english Return the amplitude rate of the effect.
     * @~chinese 振幅衰减率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese 设置振幅衰减率。
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese 振幅衰减率。
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Overrides
	virtual Liquid* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Liquid() {}
    virtual ~Liquid() {}
    
    /**
    @brief @~english Initializes the action with duration, grid size, waves count and amplitude.
     * @~chinese 用持续时间、网格大小、波的数量和振幅来创建一个Liquid动作。
    @param duration @~english Specify the duration of the Liquid action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param waves @~english Specify the waves count of the Liquid action.
     * @~chinese 波的数量。
    @param amplitude @~english Specify the amplitude of the Liquid action.
     * @~chinese Liquid动作的振幅。
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Liquid);
};

/**
@brief @~english Waves action.
 * @~chinese 波浪特效动作。
 * @details @~english This action is used for take effect on the target node as waves.
        You can control the effect by these parameters:
        duration, grid size, waves count, amplitude,
        whether waves on horizontal and whether waves on vertical.
 * @~chinese 该动作用于在目标节点上制造波浪特效。
 * 你可以控制这些参数来定制特效:
 * 持续时间、网格大小、波浪的数量、振幅、波浪是否在水平方向上和垂直方向上。
 */
class CC_DLL Waves : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration, grid size, waves count, amplitude, whether waves on horizontal and on vertical.
     * @~chinese 用持续时间，网格大小，波浪的数量，振幅，波浪是否在水平方向上和垂直方向上来创建一个Waves动作。
    @param duration @~english Specify the duration of the Waves action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param waves @~english Specify the waves count of the Waves action.
     * @~chinese 波浪的数量。
    @param amplitude @~english Specify the amplitude of the Waves action.
     * @~chinese 波浪的振幅。
    @param horizontal @~english Specify whether waves on horizontal.
     * @~chinese 指定水平方向是否有波浪。
    @param vertical @~english Specify whether waves on vertical.
     * @~chinese 指定垂直方向是否有波浪。
    @return @~english If the creation sucess, return a pointer of Waves action; otherwise, return nil.
     * @~chinese 如果创建成功,返回一个Waves动作，否则，返回空指针。
    */
    static Waves* create(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese 获取振幅。
    @return @~english Return the amplitude of the effect.
     * @~chinese 振幅。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese 设置振幅。
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese 振幅。
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese 获取振幅衰减率。
    @return @~english Return the amplitude rate of the effect.
     * @~chinese 返回振幅衰减率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese 设置振幅衰减率。
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese 振幅衰减率。
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }

    // Overrides
	virtual Waves* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Waves() {}
    virtual ~Waves() {}
    
    /**
    @brief @~english Initializes the action with duration, grid size, waves count, amplitude, whether waves on horizontal and on vertical.
     * @~chinese 用持续时间，网格大小，波浪的数量，振幅，波浪是否在水平方向上和垂直方向上来创建一个Waves动作。
    @param duration @~english Specify the duration of the Waves action. It's a value in seconds.
     * @~chinese 持续时间，以秒为单位。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param waves @~english Specify the waves count of the Waves action.
     * @~chinese 波浪的数量。
    @param amplitude @~english Specify the amplitude of the Waves action.
     * @~chinese 波浪的振幅。
    @param horizontal @~english Specify whether waves on horizontal.
     * @~chinese 指定水平方向是否有波浪。
    @param vertical @~english Specify whether waves on vertical.
     * @~chinese 指定垂直方向是否有波浪。
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithDuration(float duration, const Size& gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

protected:
    unsigned int _waves;
    float _amplitude;
    float _amplitudeRate;
    bool _vertical;
    bool _horizontal;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Waves);
};

/**
@brief @~english Twirl action.
 * @~chinese 漩涡（Twirl）动作。
@details @~english This action is used for take effect on the target node as twirl.
        You can control the effect by these parameters:
        duration, grid size, center position, twirls count, amplitude.
 * @~chinese 该动作用于在目标节点上产生漩涡效果。
 * 你可以控制这些参数来定制特效:
 * 持续时间、网格大小、中心位置、漩涡计数、幅度。
*/
class CC_DLL Twirl : public Grid3DAction
{
public:
    /**
    @brief @~english Create the action with duration, grid size, center position, number of twirls and amplitude.
     * @~chinese 用持续时间、网格大小、中心位置、漩涡计数、幅度来创建一个Twirl动作
    @param duration @~english Specify the duration of the Twirl action. It's a value in seconds.
     * @~chinese 持续时间。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param position @~english Specify the center position of the twirl action.
     * @~chinese 漩涡的中心位置。
    @param twirls @~english Specify the twirls count of the Twirl action.
     * @~chinese 漩涡的数量。
    @param amplitude @~english Specify the amplitude of the Twirl action.
     * @~chinese 漩涡动作的幅度。
    @return @~english If the creation sucess, return a pointer of Twirl action; otherwise, return nil.
     * @~chinese 如果创建成功，返回一个Twirl动作，否则，返回空指针。
    */
    static Twirl* create(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude);

    /**
    @brief @~english Get the center position of twirl action.
     * @~chinese 获取漩涡的中心位置。
    @return @~english The center position of twirl action.
     * @~chinese 漩涡的中心位置。
    */
    inline const Vec2& getPosition() const { return _position; }
    /**
    @brief @~english Set the center position of twirl action.
     * @~chinese 设置漩涡的中心位置。
    @param position @~english The center position of twirl action will be set.
     * @~chinese 漩涡的中心位置。
    */
    void setPosition(const Vec2& position);

    /**
    @brief @~english Get the amplitude of the effect.
     * @~chinese 获取漩涡特效的幅度。
    @return @~english Return the amplitude of the effect.
     * @~chinese 漩涡特效的幅度。
    */
    inline float getAmplitude() const { return _amplitude; }
    /**
    @brief @~english Set the amplitude to the effect.
     * @~chinese 设置漩涡特效的幅度。
    @param amplitude @~english The value of amplitude will be set.
     * @~chinese 漩涡特效的幅度。
    */
    inline void setAmplitude(float amplitude) { _amplitude = amplitude; }

    /**
    @brief @~english Get the amplitude rate of the effect.
     * @~chinese 获得漩涡特效的幅度比率。
    @return @~english Return the amplitude rate of the effect.
     * @~chinese 漩涡特效的幅度比率。
    */
    inline float getAmplitudeRate() const { return _amplitudeRate; }
    /**
    @brief @~english Set the ampliture rate of the effect.
     * @~chinese 设置漩涡特效的幅度比率。
    @param amplitudeRate @~english The value of amplitude rate will be set.
     * @~chinese 漩涡特效的幅度比率。
    */
    inline void setAmplitudeRate(float amplitudeRate) { _amplitudeRate = amplitudeRate; }


    // Overrides
	virtual Twirl* clone() const override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    Twirl() {}
    virtual ~Twirl() {}

    /**
    @brief @~english Initializes the action with duration, grid size, center position, number of twirls and amplitude.
     * @~chinese 用持续时间、网格大小、中心位置、漩涡计数、幅度来创建一个Twirl动作
    @param duration @~english Specify the duration of the Twirl action. It's a value in seconds.
     * @~chinese 持续时间。
    @param gridSize @~english Specify the size of the grid.
     * @~chinese 网格的大小。
    @param position @~english Specify the center position of the twirl action.
     * @~chinese 漩涡的中心位置。
    @param twirls @~english Specify the twirls count of the Twirl action.
     * @~chinese 漩涡的旋转数量。
    @param amplitude @~english Specify the amplitude of the Twirl action.
     * @~chinese 漩涡动作的幅度。
    @return @~english If the initialization sucess, return true; otherwise, return false.
     * @~chinese 如果初始化成功，返回true，否则返回false。
    */
    bool initWithDuration(float duration, const Size& gridSize, Vec2 position, unsigned int twirls, float amplitude);

protected:
    /* @~english The twirl center position @~chinese 漩涡的中心位置 */
    Vec2 _position;
    /* @~english The twirls count  @~chinese 漩涡的数量 */
    unsigned int _twirls;
    /* @~english The twirls amplitude  @~chinese 漩涡特效的幅度 */
    float _amplitude;
    /* @~english The twirls amplitude rate @~chinese 漩涡特效的幅度比率 */
    float _amplitudeRate;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Twirl);
};

// end of actions group
/// @}

NS_CC_END

#endif // __ACTION_CCGRID3D_ACTION_H__
