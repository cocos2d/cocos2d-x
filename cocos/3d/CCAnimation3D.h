/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCANIMATION3D_H__
#define __CCANIMATION3D_H__

#include <unordered_map>

#include "3d/CCAnimationCurve.h"

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "3d/CCBundle3DData.h"

NS_CC_BEGIN
/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class Animation3D
 * @brief @~english Static animation data, shared
 * @~chinese 静态的动画数据，可以被多个Animate3D共享
 */
class CC_DLL Animation3D: public Ref
{
    friend class Bundle3D;
public:
    /**
     * @class Curve
     * @brief @~english Animation curve, including translation, rotation, and scale
     * @~chinese 动画曲线，包括平移，旋转和缩放变换
     */
    class Curve
    {
    public:
        typedef AnimationCurve<3> AnimationCurveVec3;
        typedef AnimationCurve<4> AnimationCurveQuat;
        /**@~english Translation curve. @~chinese 平移曲线*/
        AnimationCurveVec3* translateCurve;
        /**@~english Rotation curve. @~chinese 旋转曲线*/
        AnimationCurveQuat* rotCurve;
        /**@~english Scaling curve. @~chinese 缩放曲线*/
        AnimationCurveVec3* scaleCurve;
        /**Constructor */
        Curve();
        /**Destructor. */
        ~Curve();
    };
    
    /**
     * @~english Create Animation3D from the specified file name and animation name.
     * @~chinese 通过文件与动画名称，来创建一个Animation3D对象
     * @param filename @~english The c3t or c3b file which contatin animation.
     * @~chinese 指定的包含了动画数据的c3t 或c3b文件
     * @param animationName @~english The specified animation name, if the animation name is "" read the first animation.
     * @~chinese 指定的动画名，如果动画名为""（空），将会读取第一个动画
     * @return @~english The Animation3D object.
     * @~chinese 被创建的Animation3D对象
     */
    static Animation3D* create(const std::string& filename, const std::string& animationName = "");
    
    /**the cache method to create or get an Animation3D object*/
    CC_DEPRECATED_ATTRIBUTE static Animation3D* getOrCreate(const std::string& filename, const std::string& animationName = ""){ return create(filename, animationName); }
       
    /**
     * @~english Get duration.
     * @~chinese 获取动画持续时间
     * @return @~english The duration time.
     * @~chinese 持续时间
     */
    float getDuration() const { return _duration; }
    
    /**
     * @~english Get bone curve.
     * @~chinese 通过指定名称获取骨骼曲线
     * @param name @~english The specified bone curve's name.
     * @~chinese 指定的骨骼曲线名称
     * @return @~english Return the curve object.
     * @~chinese 返回骨骼曲线对象
     * @lua NA
     */
    Curve* getBoneCurveByName(const std::string& name) const;
    

    /**
     * @~english Get the bone Curves set.
     * @~chinese 获取骨骼曲线的集合
     * @return @~english The bone curves set.
     * @~chinese 骨骼曲线的集合
     */
    const std::unordered_map<std::string, Curve*>& getBoneCurves() const {return _boneCurves;}
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * Constructor.
     */
    Animation3D();

    /**
     * Destructor.
     */
    virtual ~Animation3D(); 
     
    /**
     * @~english Init Animation3D from bundle data.
     * @~chinese 通过读取bundle中的数据来初始化Animation3D对象
     * @param data @~english The Animation3DData.
     * @~chinese 指定的Animation3DData 对象
     * @return @~english Return true if success, otherwise return false.
     * @~chinese 当初始化成功时返回true,反之返回false
     */
    bool init(const Animation3DData& data);
    
    /**
     * @~english Init Animation3D with file name and animation name
     * @~chinese 通过指定的文件名以及动画名称来创建Animation3D对象
     * @param filename @~english The file name
     * @~chinese 指定的包含骨骼信息的C3b和C3t文件
     * @param animationName @~english The animation name
     * @~chinese 动画名称
     * @return @~english Return true if success, otherwise return false.
     * @~chinese 当初始化成功时返回true,反之返回false
     */
    bool initWithFile(const std::string& filename, const std::string& animationName);
    
protected:
    std::unordered_map<std::string, Curve*> _boneCurves;//bone curves map, key bone name, value AnimationCurve

    float _duration; //animation duration
};

/**
 * @~english Animation3DCache, used to caching Animation3D objects.
 * @~chinese Animation3DCache用于缓存Animation3D对象
 * @class Animation3DCache
 * @brief @~english Cache of the Animation3D
 * @~chinese Animation3D的缓存
 */
class Animation3DCache
{
public:

    /**
     * @~english Get the instance.
     * @~chinese 获取单例
     * @return @~english Animation3DCache the instance
     * @~chinese Animation3DCache类的单例
     */
    static Animation3DCache* getInstance();

    /**
     * @~english Destroy the instance
     * @~chinese 销毁单例
     */
    static void destroyInstance();
    
    /**
     * @~english Get animation by key.
     * @~chinese 通过指定的Key获取一个Animation3D对象
     * @param key @~english The key string.
     * @~chinese 指定的Key的字符串，该key必须是独一无二的
     * @return @~english The Animation3D object.
     * @~chinese 对应的Animation3D对象
     */
    Animation3D* getAnimation(const std::string& key);
    
    /**
     * @~english Add animation to cache.
     * @~chinese 讲一个Animation3D对象加入缓存池中
     * @param key @~english The key string
     * @~chinese 该Animation3D对象对应的Key
     * @param animation @~english The specified animation
     * @~chinese 指定的Animation3D对象
     **/
    void addAnimation(const std::string& key, Animation3D* animation);
    
    /**
     * @~english Remove all animation
     * @~chinese 将缓存池清空
     */
    void removeAllAnimations();
    /**
     * @~english Remove unused animation
     * @~chinese 清除缓存池中所有未被使用的Animation3D对象，所谓的未被使用，即当前的Animation3D的引用技术的引用技术为一即未被加入任何Animate3D动作中
     */
    void removeUnusedAnimation();

protected:
    Animation3DCache();
    ~Animation3DCache();
    
    static Animation3DCache* _cacheInstance; //cache instance
    
    std::unordered_map<std::string, Animation3D*> _animations; //cached animations
};

// end of 3d group
/// @}
NS_CC_END

#endif // __CCANIMATION3D_H__
