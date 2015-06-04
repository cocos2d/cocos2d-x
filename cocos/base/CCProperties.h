/****************************************************************************
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 ****************************************************************************/


#ifndef __cocos2d_libs__CCProperties__
#define __cocos2d_libs__CCProperties__

#include <string>
#include <functional>
#include <cstdint>
#include <vector>

#include "renderer/CCTexture2D.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Properties;
class Vec2;
class Vec3;
class Vec4;
class Mat4;
class Data;
class Data;


/**
 * @~english Defines a properties file for loading text files.
 *
 * A properties file has very simple syntax and can contain only namespaces and
 * name/value pairs (the properties of a namespace).  
 * The file can have any file extension a user specifies.
 *
 * Here's an example of a simple
 * file that uses all the available features of the markup language:
 *
  @verbatim
     // This is a comment.
  
     // This property is in the default namespace:
     integerProperty = 5
  
     // This line defines a namespace of type "mynamespace" without an ID:
     mynamespace
     {
         // This namespace can be retrieved by searching for its ID, "spriteTexture",
         // or by its name "texture":
         texture spriteTexture 
         {
             fileName = sprite.png
             width = 64
             height = 64
         }
  
         // This property is in the "space" namespace:
         booleanProperty = true
  
         // It's legal to have a name without a value if you leave out the '=' character:
         foo
  
         // In fact, the '=' character is optional if you'd rather write:
         bar 23
  
         // But don't write this or you'll get an error:
         // illegalProperty =
  
         // Or this:
         // = 15
  
         // Properties objects let you retrieve values as various types.
         floatProperty = 3.333
         stringProperty = This is a string.
         vector3Property = 1.0, 5.0, 3.55
         colorProperty = 1.0, 0.4, 0.0, 1.0
     }
  @endverbatim
 * 
 * Retrieving information out of a file like this could be done in two ways.  If the
 * available namespaces and name/value pairs are known in advance they can be queried by ID or name.
 * For example, if the namespace "spriteTexture" and its properties are required then they can
 * be retrieved with a call to getNamespace() followed by calls to getString() and getInt().
 * A namespace is stored and retrieved as a Properties object.
 * Reading the spriteTexture properties out of the file above in this way could be done with the following code:
 * 
  @verbatim
     // Create the top-level Properties object.
     Properties* properties = Properties::createNonRefCounted("example.properties");
     // Retrieve the "spriteTexture" namespace.
     Properties* spriteTexture = properties->getNamespace("spriteTexture");
  
     // Get the values of known texture properties out of the namespace.
     const char* fileName = spriteTexture->getString("fileName");
     int width = spriteTexture->getInt("width");
     int height = spriteTexture->getInt("height");
  
     // Deleting the top-level Properties object will clean up all nested namespaces.
     SAFE_DELETE(properties);
  @endverbatim
 *
 * On the other hand, if the structure of the file is not known in advance its 
 * namespaces and name/value pairs can be retrieved one by one using the getNextNamespace()
 * and getNextProperty() methods.  The following method prints the contents of any properties file
 * to the console:
 * 
  @verbatim
     void printProperties(Properties* properties)
     {
         // Print the name and ID of the current namespace.
         const char* spacename = properties->getNamespace();
         const char* id = properties->getId();
         GP_WARN("Namespace: %s  ID: %s\n{", spacename, id);
  
         // Print all properties in this namespace.
         const char* name = properties->getNextProperty();
         const char* value = NULL;
         while (name != NULL)
         {
             value = properties->getString(name);
             GP_WARN("%s = %s", name, value);
             name = properties->getNextProperty();
         }
         GP_WARN("}\n");
  
         // Print the properties of every namespace within this one.
         Properties* space = properties->getNextNamespace();
         while (space != NULL)
         {
             printProperties(space);
             space = properties->getNextNamespace();
         }
     }
  @endverbatim
 *
 * Note that this method does not keep track of the namespace hierarchy, but could be
 * modified to do so.  Also note that nothing in a properties file indicates the type
 * of a property. If the type is unknown, its string can be retrieved and interpreted
 * as necessary.
 *
 * @~chinese 
 * 定义一个用于加载文本文件的属性文件。
 *
 * 一个属性文件语法很简单，可以只包含命名空间和键值对（命名空间下的属性）。
 * 这个文件可以使用用户指定的任意扩展名。
 *
 * 这里有一个简单的示例文件，覆盖了 markup 语言的所有可用功能：
 *
  @verbatim
     // This is a comment.
  
     // This property is in the default namespace:
     integerProperty = 5
  
     // This line defines a namespace of type "mynamespace" without an ID:
     mynamespace
     {
         // This namespace can be retrieved by searching for its ID, "spriteTexture",
         // or by its name "texture":
         texture spriteTexture 
         {
             fileName = sprite.png
             width = 64
             height = 64
         }
  
         // This property is in the "space" namespace:
         booleanProperty = true
  
         // It's legal to have a name without a value if you leave out the '=' character:
         foo
  
         // In fact, the '=' character is optional if you'd rather write:
         bar 23
  
         // But don't write this or you'll get an error:
         // illegalProperty =
  
         // Or this:
         // = 15
  
         // Properties objects let you retrieve values as various types.
         floatProperty = 3.333
         stringProperty = This is a string.
         vector3Property = 1.0, 5.0, 3.55
         colorProperty = 1.0, 0.4, 0.0, 1.0
     }
  @endverbatim
 * 
 * 有两种方法可以从文件中检索数据。
 * 如果已知可用的命名空间与键值对，那么可以使用 ID 或者名称来查找属性。
 * 例如：如果要使用 "spriteTexture" 这个命名空间及其属性，那么可以通过调用 getNamespace() 获取命名空间，
 * 再调用 getString() 或者 getInt() 来获取数据。
 * 命名空间在内存中也是一个属性对象。
 * 可以参考如下代码来读取 "spriteTexture" 命名空间下的属性：
 * 
  @verbatim
     // Create the top-level Properties object.
     Properties* properties = Properties::createNonRefCounted("example.properties");
     // Retrieve the "spriteTexture" namespace.
     Properties* spriteTexture = properties->getNamespace("spriteTexture");
  
     // Get the values of known texture properties out of the namespace.
     const char* fileName = spriteTexture->getString("fileName");
     int width = spriteTexture->getInt("width");
     int height = spriteTexture->getInt("height");
  
     // Deleting the top-level Properties object will clean up all nested namespaces.
     SAFE_DELETE(properties);
  @endverbatim
 *
 * 另一方面，如果命名空间及其属性未知，那么可以使用 getNextNamespace() 和 getNextProperty() 函数逐个读取命名空间与键值对。
 * 下面的代码可以将属性文件的内容输出到控制台：
 * 
  @verbatim
     void printProperties(Properties* properties)
     {
         // Print the name and ID of the current namespace.
         const char* spacename = properties->getNamespace();
         const char* id = properties->getId();
         GP_WARN("Namespace: %s  ID: %s\n{", spacename, id);
  
         // Print all properties in this namespace.
         const char* name = properties->getNextProperty();
         const char* value = NULL;
         while (name != NULL)
         {
             value = properties->getString(name);
             GP_WARN("%s = %s", name, value);
             name = properties->getNextProperty();
         }
         GP_WARN("}\n");
  
         // Print the properties of every namespace within this one.
         Properties* space = properties->getNextNamespace();
         while (space != NULL)
         {
             printProperties(space);
             space = properties->getNextNamespace();
         }
     }
  @endverbatim
 *
 * 注意上述示例代码不能处理多层级的命名空间，可以通过调整来实现。
 * 还要注意的是，在属性文件中，没有表示属性值类型的字段。
 * 如果属性值的类型未知，可以读取到字符串类型的值。
 */
class CC_DLL Properties
{
    friend class Game;

public:

    /**@~english
     * Data types supported by the properties class.
     * @~chinese 
     * Properties 类中支持的数据类型列表。
     */
    enum Type
    {
        NONE,
        STRING,
        NUMBER,
        VECTOR2,
        VECTOR3,
        VECTOR4,
        MATRIX
    };

    /**@~english
     * Creates a Properties runtime settings from the specified URL, where the URL is of
     * the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * 
     * @~chinese 
     * 从指定的 URL 创建一个 Properties 对象。URL 的格式为：
     * "<文件路径>.<扩展名>#<命名空间 ID>/<命名空间 ID>/.../<命名空间 ID>"
     * (其中 "#<命名空间 ID>" 是可选的)
     * 
     * @param url @~english The URL to create the properties from.
     * 
     * @~chinese 指定的 URL。
     * 
     * @return @~english The created Properties or NULL if there was an error.
     * @~chinese 返回 Properties 实例。如果创建失败，返回 nullptr。
     */
    static Properties* createNonRefCounted(const std::string& url);

    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     */
    ~Properties();

    /**@~english
     * Get the name of the next property.
     *
     * If a valid next property is returned, the value of the property can be
     * retrieved using any of the get methods in this class, passing NULL for
     * the property name.
     *
     * @~chinese 
     * 获取下一个属性的名称。
     * 
     * 如果返回值是一个有效的属性，可以通过任何 get 函数来获取属性值（name 参数使用 NULL）。
     * 
     * @return @~english The name of the next property, or NULL if there are no properties remaining.
     * @~chinese 下一个属性的名称，如果不存在则返回 NULL。
     */
    const char* getNextProperty();

    /**@~english
     * Get the next namespace.
     * @~chinese 
     * 获取下一个命名空间。
     */
    Properties* getNextNamespace();

    /** @~english
     * Rewind the getNextProperty() and getNextNamespace() iterators
     * to the beginning of the file.
     * @~chinese 
     * 重置 getNextProperty() 和 getNextNamespace() 获取的迭代器到文件的开始。
     */
    void rewind();

    /**@~english
     * Get a specific namespace by ID or name. This method will optionally
     * perform a depth-first search on all namespaces and inner namespaces
     * within this Property.
     *
     * @~chinese 
     * 通过指定的 ID 或者名称来获取命名空间。该方法可以选择在
     * 当前对象的所有命名空间和以及内部的命名空间中进行递归查找。
     * 
     * @param id @~english The ID or name of the namespace to find.
     * @~chinese 命名空间的ID或名称。
     * @param searchNames @~english If true, namespace names are used in the search,
     *      instead of namespace IDs. By default this parameter is false
     *      and namespace IDs are searched.
     * @~chinese 如果为 true 则使用名称来查找，否则使用 ID 进行查找。默认使用 ID 进行查找。
     * @param recurse @~english If true, perform a depth-first search, otherwise search
     *      only the immediate child namespaces.
     * 
     * @~chinese 如果为 true，则进行递归查找；否则只在当前对象中查找。
     * 
     * @return @~english A properties object with the given ID or name.
     * @~chinese 与指定的名称或 ID 匹配的 Properties 对象。
     */
    Properties* getNamespace(const char* id, bool searchNames = false, bool recurse = true) const;

    /**@~english
     * Get the name of this Property's namespace.
     *
     * @~chinese 
     * 获取当前对象的命名空间名称。
     * 
     * @return @~english The name of this Property's namespace.
     * @~chinese 当前对象的命名空间名称。
     */
    const char* getNamespace() const;

    /**@~english
     * Get the ID of this Property's namespace. The ID should be a unique identifier,
     * but its uniqueness is not enforced.
     *
     * @~chinese 
     * 获取当前对象的命名空间 ID。ID 应该是一个唯一的值，但是并不强制要求其唯一性。
     * 
     * @return @~english The ID of this Property's namespace.
     * @~chinese 当前对象的命名空间 ID。
     */
    const char* getId() const;

    /**@~english
     * Check if a property with the given name is specified in this Properties object.
     *
     * @~chinese 
     * 检查是否存在指定名称的属性。
     * 
     * @param name @~english The name of the property to query.
     * 
     * @~chinese 要检查的属性的名称。
     * 
     * @return @~english True if the property exists, false otherwise.
     * @~chinese 如果存在返回 true；否则返回 false。
     */
    bool exists(const char* name) const;

    /**@~english
     * Returns the type of a property.
     *
     * @~chinese 
     * 返回属性的类型。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's type.
     *
     * @~chinese 属性的名称，如果为 NULL 则返回当前对象的类型。
     * 
     * @return @~english The type of the property.
     * @~chinese 属性的类型。
     */
    Type getType(const char* name = NULL) const;

    /**@~english
     * Get the value of the given property as a string. This can always be retrieved,
     * whatever the intended type of the property.
     *
     * @~chinese 
     * 获取指定属性值的字符串。可以检索任意类型的属性。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 属性名称，如果为 NULL 则返回当前属性的值。
     * @param defaultValue @~english The default value to return if the specified property does not exist.
     * 
     * @~chinese 默认值，如果指定的属性不存在，则返回此默认值。
     * 
     * @return @~english The value of the given property as a string, or the empty string if no property with that name exists.
     * @~chinese 指定属性值的字符串。如果属性不存在，则返回指定的默认值或者空字符串。
     */
    const char* getString(const char* name = NULL, const char* defaultValue = NULL) const;

    /**@~english
     * Sets the value of the property with the specified name.
     *
     * If there is no property in this namespace with the current name,
     * one is added. Otherwise, the value of the first property with the
     * specified name is updated.
     *
     * If name is NULL, the value current property (see getNextProperty) is
     * set, unless there is no current property, in which case false
     * is returned.
     *
     * @~chinese 
     * 设置指定名称的属性值字符串。
     * 
     * 如果属性不存在，则增加该属性。否则，查找到的第一个属性值将被更新。
     * 
     * 如果名称是 NULL，则更新当前属性的值。如果当前对象不是一个属性，则返回 false。
     * 
     * @param name @~english The name of the property to set.
     * @~chinese 指定的属性名称。
     * @param value @~english The property value.
     *
     * @~chinese 设置的属性值。
     * 
     * @return @~english True if the property was set, false otherwise.
     * @~chinese 如果设置成功返回 true；否则返回 false。
     */
    bool setString(const char* name, const char* value);

    /**@~english
     * Interpret the value of the given property as a boolean.
     *
     * @~chinese 
     * 获取布尔类型的属性值。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称。如果为 NULL，则返回当前对象的属性值。
     * @param defaultValue @~english the default value to return if the specified property does not exist within the properties file.
     * 
     * @~chinese 默认值，如果找不到指定的属性，则返回此默认值。
     * 
     * @return @~english true if the property exists and its value is "true", otherwise false.
     * @~chinese 指定属性的布尔值。如果属性不存在，则返回指定的默认值或者 false。
     */
    bool getBool(const char* name = NULL, bool defaultValue = false) const;

    /**@~english
     * Interpret the value of the given property as an integer.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @~chinese 
     * 获取指定属性的整数值。
     * 如果属性不存在，将返回 0。
     * 如果属性存在，但并非整数类型，则输出错误日志并返回 0。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * 
     * @return @~english The value of the given property interpreted as an integer.
     *   Zero if the property does not exist or could not be scanned.
     * @~chinese 获取属性的整数值。如果属性不存在或者读取失败则返回 0。
     */
    int getInt(const char* name = NULL) const;

    /**@~english
     * Interpret the value of the given property as a floating-point number.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @~chinese 
     * 获取指定属性的浮点值。
     * 如果属性不存在，将返回 0。
     * 如果属性存在，但并非浮点类型，则输出错误日志并返回 0。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * 
     * @return @~english The value of the given property interpreted as a float.
     *   Zero if the property does not exist or could not be scanned.
     * @~chinese 获取属性的浮点值。如果属性不存在或者读取失败则返回 0。
     */
    float getFloat(const char* name = NULL) const;

    /**@~english
     * Interpret the value of the given property as a long integer.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @~chinese 
     * 获取指定属性的长整数值。
     * 如果属性不存在，将返回 0。
     * 如果属性存在，但并非长整数类型，则输出错误日志并返回 0。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * 
     * @return @~english The value of the given property interpreted as a long.
     *   Zero if the property does not exist or could not be scanned.
     * @~chinese 获取属性的长整数值。如果属性不存在或者读取失败则返回 0。
     */
    long getLong(const char* name = NULL) const;

    /**@~english
     * Interpret the value of the given property as a Matrix.
     * If the property does not exist, out will be set to the identity matrix.
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to the identity matrix.
     *
     * @~chinese 
     * 获取指定属性的矩阵值。
     * 如果属性不存在，返回单位矩阵。
     * 如果属性存在，但并非矩阵类型，则输出错误日志并返回单位矩阵。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The matrix to set to this property's interpreted value.
     * 
     * @~chinese 返回的矩阵值。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getMat4(const char* name, Mat4* out) const;

    /**@~english
     * Interpret the value of the given property as a Vector2.
     * If the property does not exist, out will be set to Vector2(0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector2(0.0f, 0.0f).
     *
     * @~chinese 
     * 获取指定属性的 Vec2 值。
     * 如果属性不存在，返回 (0.0f, 0.0f)。
     * 如果属性存在，但并非 Vec2 类型，则输出错误日志并返回 (0.0f, 0.0f)。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese 返回的 Vec2 实例。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getVec2(const char* name, Vec2* out) const;

    /**@~english
     * Interpret the value of the given property as a Vector3.
     * If the property does not exist, out will be set to Vector3(0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector3(0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * 获取指定属性的 Vec3 值。
     * 如果属性不存在，返回 (0.0f, 0.0f, 0.0f)。
     * 如果属性存在，但并非 Vec3 类型，则输出错误日志并返回 (0.0f, 0.0f, 0.0f)。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese 返回的 Vec3 实例。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getVec3(const char* name, Vec3* out) const;

    /**@~english
     * Interpret the value of the given property as a Vector4.
     * If the property does not exist, out will be set to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * 获取指定属性的 Vec4 值。
     * 如果属性不存在，返回 (0.0f, 0.0f, 0.0f, 0.0f)。
     * 如果属性存在，但并非 Vec3 类型，则输出错误日志并返回 (0.0f, 0.0f, 0.0f, 0.0f)。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese 返回的 Vec4 实例。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getVec4(const char* name, Vec4* out) const;

    /**@~english
     * Interpret the value of the given property as a Quaternion specified as an axis angle.
     * If the property does not exist, out will be set to Quaternion().
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Quaternion().
     *
     * @~chinese 
     * 获取指定属性的四元数。
     * 如果属性不存在，返回 Quaternion()。
     * 如果属性存在，但并非四元数类型，则输出错误日志并返回 Quaternion()。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The quaternion to set to this property's interpreted value.
     * 
     * @~chinese 返回的四元数。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getQuaternionFromAxisAngle(const char* name, Quaternion* out) const;

    /**@~english
     * Interpret the value of the given property as an RGB color in hex and write this color to a Vector3.
     * E.g. 0xff0000 represents red and sets the vector to (1, 0, 0).
     * If the property does not exist, out will be set to Vector3(0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector3(0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * 属性值按照 RGB 颜色解析并存储在 Vector3 对象中。
     * 例如：0xff0000 代表红色，返回值为(1, 0, 0)。
     * 如果属性不存在，返回值为 Vector3(0.0f, 0.0f, 0.0f)。
     * 如果属性存在，但解析失败，则输出错误日志并返回 Vector3(0.0f, 0.0f, 0.0f)。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese 返回的颜色值数据。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getColor(const char* name, Vec3* out) const;

    /**@~english
     * Interpret the value of the given property as an RGBA color in hex and write this color to a Vector4.
     * E.g. 0xff0000ff represents opaque red and sets the vector to (1, 0, 0, 1).
     * If the property does not exist, out will be set to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     *
     * @~chinese 
     * 属性值按照 RGBA 颜色解析并存储在 Vector4 对象中。
     * 例如：0xff0000ff 代表不透明的红色，返回值为(1, 0, 0, 1)。
     * 如果属性不存在，返回值为 Vector4(0.0f, 0.0f, 0.0f, 0.0f)。
     * 如果属性存在，但解析失败，则输出错误日志并返回 Vector4(0.0f, 0.0f, 0.0f, 0.0f)。
     * 
     * @param name @~english The name of the property to interpret, or NULL to return the current property's value.
     * @~chinese 指定的属性名称，如果为 NULL 则返回当前对象的属性值。
     * @param out @~english The vector to set to this property's interpreted value.
     * 
     * @~chinese 返回的颜色值数据。
     * 
     * @return @~english True on success, false if the property does not exist or could not be scanned.
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getColor(const char* name, Vec4* out) const;

    /**@~english
     * Gets the file path for the given property if the file exists.
     * 
     * This method will first search for the file relative to the working directory.
     * If the file is not found then it will search relative to the directory the bundle file is in.
     * 
     * @~chinese 
     * 获取指定属性的路径值。
     * 
     * 该方法首先相对于工作目录查找属性值所表示的文件。
     * 如果没有找到文件，那么它将搜索整个包目录。
     * 
     * @param name @~english The name of the property.
     * @~chinese 属性的名称。
     * @param path @~english The string to copy the path to if the file exists.
     * 
     * @~chinese 返回的路径值。
     * 
     * @return @~english True if the property exists and the file exists, false otherwise.
     *
     * @~chinese 如果获取成功返回 true；否则返回 false。
     */
    bool getPath(const char* name, std::string* path) const;

    /**@~english
     * Returns the value of a variable that is set in this Properties object.
     *
     * Variables take on the format ${name} and are inherited from parent Property objects.
     *
     * @~chinese 
     * 获取指定属性的变量值。
     * 
     * 变量的格式 ${name}，是继承自父类属性的对象。
     * 
     * @param name @~english Name of the variable to get.
     * @~chinese 属性的名称。
     * @param defaultValue @~english Value to return if the variable is not found.
     *
     * @~chinese 默认值，当属性不存在时返回此默认值。
     * 
     * @return @~english The value of the specified variable, or defaultValue if not found.
     * @~chinese 获取到的变量值，如果获取失败，则返回指定的默认值。
     */
    const char* getVariable(const char* name, const char* defaultValue = NULL) const;

    /**@~english
     * Sets the value of the specified variable.
     *
     * @~chinese 
     * 设置指定属性的变量值。
     * 
     * @param name @~english Name of the variable to set.
     * @~chinese 指定的属性名称。
     * @param value @~english The value to set.
     * @~chinese 设置的变量值。
     */
    void setVariable(const char* name, const char* value);

    /**@~english
     * Attempts to parse the specified string as a Vector2 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * 尝试将指定的字符串解析为 Vec2 数据。
     * 
     * 如果出错，则返回 false，返回值设置为 `Vec2::ZERO`。
     * 
     * @param str @~english The string to parse.
     * @~chinese 要解析的字符串
     * @param out @~english The value to populate if successful.
     *
     * @~chinese 解析出的 Vec2 实例。
     * 
     * @return @~english True if a valid Vector2 was parsed, false otherwise.
     * @~chinese 如果解析成功，返回 true；否则返回 false。
     */
    static bool parseVec2(const char* str, Vec2* out);

    /**@~english
     * Attempts to parse the specified string as a Vector3 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * 尝试将指定的字符串解析为 Vec3 数据。
     * 
     * 如果出错，则返回 false，返回值设置为 `Vec3::ZERO`。
     * 
     * @param str @~english The string to parse.
     * @~chinese 要解析的字符串
     * @param out @~english The value to populate if successful.
     *
     * @~chinese 解析出的 Vec3 实例。
     * 
     * @return @~english True if a valid Vector3 was parsed, false otherwise.
     * @~chinese 如果解析成功，返回 true；否则返回 false。
     */
    static bool parseVec3(const char* str, Vec3* out);
    
    /**@~english
     * Attempts to parse the specified string as a Vector4 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * 尝试将指定的字符串解析为 Vec4 数据。
     * 
     * 如果出错，则返回 false，返回值设置为 `Vec4::ZERO`。
     * 
     * @param str @~english The string to parse.
     * @~chinese 要解析的字符串
     * @param out @~english The value to populate if successful.
     *
     * @~chinese 解析出的 Vec4 实例。
     * 
     * @return @~english True if a valid Vector4 was parsed, false otherwise.
     * @~chinese 如果解析成功，返回 true；否则返回 false。
     */
    static bool parseVec4(const char* str, Vec4* out);

    /**@~english
     * Attempts to parse the specified string as an axis-angle value.
     *
     * The specified string is expected to contain four comma-separated
     * values, where the first three values represents the axis and the
     * fourth value represents the angle, in degrees.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @~chinese 
     * 尝试将指定的字符串解析为四元数。
     * 
     * 期望的格式为：四个逗号分隔的数值，前三个值表示轴，
     * 第四个值表示角度。
     * 
     * 如果解析失败，则返回 false。返回的全部数据都设置为 0。
     * 
     * @param str @~english The string to parse.
     * @~chinese 要解析的字符串。
     * @param out @~english A Quaternion populated with the orientation of the axis-angle, if successful.
     *
     * @~chinese 解析出的四元数实例。
     * 
     * @return @~english True if a valid axis-angle was parsed, false otherwise.
     * @~chinese 如果解析成功，返回 true；否则返回 false。
     */
    static bool parseAxisAngle(const char* str, Quaternion* out);

    /**@~english
     * Atempts to parse the specified string as an RGB color value.
     *
     * @~chinese 
     * 尝试将指定的字符串解析为 RGB 颜色值。
     * 
     * @param str @~english The string to parse.
     * @~chinese 要解析的字符串。
     * @param out @~english The value to populate if successful.
     *
     * @~chinese 返回的颜色值。
     * 
     * @return @~english True if a valid RGB color was parsed, false otherwise.
     * @~chinese 如果解析成功，返回 true；否则返回 false。
     */
    static bool parseColor(const char* str, Vec3* out);

    /**@~english
     * Atempts to parse the specified string as an RGBA color value.
     *
     * @~chinese 
     * 尝试将指定的字符串解析为 RGBA 颜色值。
     * 
     * @param str @~english The string to parse.
     * @~chinese 要解析的字符串。
     * @param out @~english The value to populate if successful.
     *
     * @~chinese 返回的颜色值。
     * 
     * @return @~english True if a valid RGBA color was parsed, false otherwise.
     * @~chinese 如果解析成功，返回 true；否则返回 false。
     */
    static bool parseColor(const char* str, Vec4* out);

private:

    struct Property
    {
        std::string name;
        std::string value;
        Property(const std::string& aname, const std::string& avalue) : name(aname), value(avalue) { }
    };

    Properties();

    Properties(Data* data, ssize_t* dataIdx);
    Properties(const Properties& copy);

    Properties(Data* data, ssize_t* dataIdx, const std::string& name, const char* id, const char* parentID, Properties* parent);

    // Data manipulation methods
    void readProperties();
    void skipWhiteSpace();
    char* trimWhiteSpace(char* str);
    signed char readChar();
    char* readLine(char* output, int num);
    bool seekFromCurrent(int offset);
    bool eof();

    // Called after createNonRefCounted(); copies info from parents into derived namespaces.
    void resolveInheritance(const char* id = NULL);

    // Called by resolveInheritance().
    void mergeWith(Properties* overrides);

    // Clones the Properties object.
    Properties* clone();

    void setDirectoryPath(const std::string* path);
    void setDirectoryPath(const std::string& path);

    // XXX: hack in order to simulate GamePlay's Stream with Cocos2d's Data
    ssize_t *_dataIdx;
    Data *_data;

    std::string _namespace;
    std::string _id;
    std::string _parentID;
    std::vector<Property> _properties;
    std::vector<Property>::iterator _propertiesItr;
    std::vector<Properties*> _namespaces;
    std::vector<Properties*>::const_iterator _namespacesItr;
    std::vector<Property>* _variables;
    std::string* _dirPath;
    Properties* _parent;
};

}

#endif // __cocos2d_libs__CCProperties__
