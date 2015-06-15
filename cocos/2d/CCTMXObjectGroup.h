/****************************************************************************
Copyright (c) 2010      Neophit
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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
#ifndef __CCTMX_OBJECT_GROUP_H__
#define __CCTMX_OBJECT_GROUP_H__

#include "math/CCGeometry.h"
#include "base/CCValue.h"
#include "base/CCRef.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */


/** @brief @~english TMXObjectGroup represents the TMX object group.
 * @~chinese TMXObjectGroup用来表示TMX对象组。
 * @since v0.99.0
 */

class CC_DLL TMXObjectGroup : public Ref
{
public:
    /**
     * @js ctor
     */
    TMXObjectGroup();

    /**
     * @js NA
     * @lua NA
     */
    virtual ~TMXObjectGroup();
    
    /** @~english Get the group name. 
     *
     * @~chinese 获取组名称。
     * 
     * @return @~english The group name.
     * @~chinese 组名称。
     */
    inline const std::string& getGroupName() const { return _groupName; }
    
    /** @~english Set the group name. 
     *
     * @~chinese 设置组名称。
     * 
     * @param groupName @~english A string,it is used to set the group name.
     * @~chinese 一个字符串,它是用来设置组名称。
     */
    inline void setGroupName(const std::string& groupName){ _groupName = groupName; }

    /** @~english Return the value for the specific property name. 
     *
     * @~chinese 获取指定属性名的值。
     * 
     * @param propertyName @~english The specific property name.
     * @~chinese 特定的属性名。
     * @return @~english Return the value for the specific property name.
     * @~chinese 返回指定属性名的值。
     * @js NA
     */
    Value getProperty(const std::string& propertyName) const;
    
    CC_DEPRECATED_ATTRIBUTE Value propertyNamed(const std::string& propertyName) const { return getProperty(propertyName); };

    /** @~english Return the dictionary for the specific object name.
     * It will return the 1st object found on the array for the given name.
     *
     * @~chinese 获取指定对象名的字典。
     * 它将返回的是符号指定名字的数组中第一个对象。
     * 
     * @return @~english Return the dictionary for the specific object name.
     * @~chinese 返回指定对象名的字典。
     */
    ValueMap getObject(const std::string& objectName) const;
    
    CC_DEPRECATED_ATTRIBUTE ValueMap objectNamed(const std::string& objectName) const { return getObject(objectName); };
    
    /** @~english Gets the offset position of child objects. 
     *
     * @~chinese 获取子对象的偏移位置。
     * 
     * @return @~english The offset position of child objects.
     * @~chinese 子对象的偏移位置。
     */
    inline const Vec2& getPositionOffset() const { return _positionOffset; };
    
    /** @~english Sets the offset position of child objects. 
     *
     * @~chinese 设置子对象的偏移位置。
     * 
     * @param offset @~english The offset position of child objects.
     * @~chinese 子对象的偏移位置。
     */
    inline void setPositionOffset(const Vec2& offset) { _positionOffset = offset; };
    
    /** @~english Gets the list of properties stored in a dictionary. 
     *
     * @~chinese 获取存储在字典中的属性队列。
     * 
     * @return @~english The list of properties stored in a dictionary.
     * @~chinese 存储在字典中的属性队列。
     */
    inline const ValueMap& getProperties() const { return _properties; };
    inline ValueMap& getProperties() { return _properties; };
    
    /** @~english Sets the list of properties.
     *
     * @~chinese 设置属性队列。
     * 
     * @param properties @~english The list of properties.
     * @~chinese 属性队列。
     */
    inline void setProperties(const ValueMap& properties) {
        _properties = properties;
    };
    
    /** @~english Gets the array of the objects. 
     *
     * @~chinese 获取对象数组。
     * 
     * @return @~english The array of the objects.
     * @~chinese 对象数组.
     */
    inline const ValueVector& getObjects() const { return _objects; };
    inline ValueVector& getObjects() { return _objects; };
    
    /** @~english Sets the array of the objects.
     *
     * @~chinese 设置对象数组。
     * 
     * @param objects @~english The array of the objects.
     * @~chinese 对象数组。
     */
    inline void setObjects(const ValueVector& objects) {
        _objects = objects;
    };
    
protected:
    /** @~english name of the group  @~chinese 组的名称*/
    std::string _groupName;
    
    /** @~english offset position of child objects  @~chinese 子对象的偏移位置*/
    Vec2 _positionOffset;
    
    /** @~english list of properties stored in a dictionary  @~chinese 存储在一个字典中的属性列表*/
    ValueMap _properties;
    
    /** @~english array of the objects  @~chinese 对象数组*/
    ValueVector _objects;
};

// end of tilemap_parallax_nodes group
/** @} */


NS_CC_END

#endif //__CCTMX_OBJECT_GROUP_H__
