/**
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2015-2017 Chukong Technologies
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
 */


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
class Quaternion;
class Data;


/**
 * Defines a properties file for loading text files.
 *
 * A properties file has very simple syntax and can contain only namespaces and
 * name/value pairs (the properties of a namespace).  
 * The file can have any file extension a user specifies.
 *
 * Here's an example of a simple
 * file that uses all the available features of the markup language:
 
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
 
 * Retrieving information out of a file like this could be done in two ways.  If the
 * available namespaces and name/value pairs are known in advance they can be queried by ID or name.
 * For example, if the namespace "spriteTexture" and its properties are required then they can
 * be retrieved with a call to getNamespace() followed by calls to getString() and getInt().
 * A namespace is stored and retrieved as a Properties object.
 * Reading the spriteTexture properties out of the file above in this way could be done with the following code:
 
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

 * On the other hand, if the structure of the file is not known in advance its 
 * namespaces and name/value pairs can be retrieved one by one using the getNextNamespace()
 * and getNextProperty() methods.  The following method prints the contents of any properties file
 * to the console:
 
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

 * Note that this method does not keep track of the namespace hierarchy, but could be
 * modified to do so.  Also note that nothing in a properties file indicates the type
 * of a property. If the type is unknown, its string can be retrieved and interpreted
 * as necessary.
 */
class CC_DLL Properties
{
public:

    /**
     * Data types supported by the properties class.
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

    /**
     * Creates a Properties runtime settings from the specified URL, where the URL is of
     * the format "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>"
     * (and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     * 
     * @param url The URL to create the properties from.
     * 
     * @return The created Properties or NULL if there was an error.
     * @script{create}
     */
    static Properties* createNonRefCounted(const std::string& url);

    /**
     * Destructor.
     */
    ~Properties();

    /**
     * Get the name of the next property.
     *
     * If a valid next property is returned, the value of the property can be
     * retrieved using any of the get methods in this class, passing NULL for
     // the property name.
     *
     * @return The name of the next property, or NULL if there are no properties remaining.
     */
    const char* getNextProperty();

    /**
     * Get the next namespace.
     */
    Properties* getNextNamespace();

    /** 
     * Rewind the getNextProperty() and getNextNamespace() iterators
     * to the beginning of the file.
     */
    void rewind();

    /**
     * Get a specific namespace by ID or name. This method will optionally
     * perform a depth-first search on all namespaces and inner namespaces
     * within this Property.
     *
     * @param id The ID or name of the namespace to find.
     * @param searchNames If true, namespace names are used in the search,
     *      instead of namespace IDs. By default this parameter is false
     *      and namespace IDs are searched.
     * @param recurse If true, perform a depth-first search, otherwise search
     *      only the immediate child namespaces.
     * 
     * @return A properties object with the given ID or name.
     */
    Properties* getNamespace(const char* id, bool searchNames = false, bool recurse = true) const;

    /**
     * Get the name of this Property's namespace.
     *
     * @return The name of this Property's namespace.
     */
    const char* getNamespace() const;

    /**
     * Get the ID of this Property's namespace. The ID should be a unique identifier,
     * but its uniqueness is not enforced.
     *
     * @return The ID of this Property's namespace.
     */
    const char* getId() const;

    /**
     * Check if a property with the given name is specified in this Properties object.
     *
     * @param name The name of the property to query.
     * 
     * @return True if the property exists, false otherwise.
     */
    bool exists(const char* name) const;

    /**
     * Returns the type of a property.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's type.
     *
     * @return The type of the property.
     */
    Type getType(const char* name = NULL) const;

    /**
     * Get the value of the given property as a string. This can always be retrieved,
     * whatever the intended type of the property.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param defaultValue The default value to return if the specified property does not exist.
     * 
     * @return The value of the given property as a string, or the empty string if no property with that name exists.
     */
    const char* getString(const char* name = NULL, const char* defaultValue = NULL) const;

    /**
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
     * @param name The name of the property to set.
     * @param value The property value.
     *
     * @return True if the property was set, false otherwise.
     */
    bool setString(const char* name, const char* value);

    /**
     * Interpret the value of the given property as a boolean.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param defaultValue the default value to return if the specified property does not exist within the properties file.
     * 
     * @return true if the property exists and its value is "true", otherwise false.
     */
    bool getBool(const char* name = NULL, bool defaultValue = false) const;

    /**
     * Interpret the value of the given property as an integer.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @return The value of the given property interpreted as an integer.
     *   Zero if the property does not exist or could not be scanned.
     */
    int getInt(const char* name = NULL) const;

    /**
     * Interpret the value of the given property as a floating-point number.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @return The value of the given property interpreted as a float.
     *   Zero if the property does not exist or could not be scanned.
     */
    float getFloat(const char* name = NULL) const;

    /**
     * Interpret the value of the given property as a long integer.
     * If the property does not exist, zero will be returned.
     * If the property exists but could not be scanned, an error will be logged and zero will be returned.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * 
     * @return The value of the given property interpreted as a long.
     *   Zero if the property does not exist or could not be scanned.
     */
    long getLong(const char* name = NULL) const;

    /**
     * Interpret the value of the given property as a Matrix.
     * If the property does not exist, out will be set to the identity matrix.
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to the identity matrix.
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The matrix to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getMat4(const char* name, Mat4* out) const;

    /**
     * Interpret the value of the given property as a Vector2.
     * If the property does not exist, out will be set to Vector2(0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector2(0.0f, 0.0f).
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The vector to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getVec2(const char* name, Vec2* out) const;

    /**
     * Interpret the value of the given property as a Vector3.
     * If the property does not exist, out will be set to Vector3(0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector3(0.0f, 0.0f, 0.0f).
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The vector to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getVec3(const char* name, Vec3* out) const;

    /**
     * Interpret the value of the given property as a Vector4.
     * If the property does not exist, out will be set to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The vector to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getVec4(const char* name, Vec4* out) const;

    /**
     * Interpret the value of the given property as a Quaternion specified as an axis angle.
     * If the property does not exist, out will be set to Quaternion().
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Quaternion().
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The quaternion to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getQuaternionFromAxisAngle(const char* name, Quaternion* out) const;

    /**
     * Interpret the value of the given property as an RGB color in hex and write this color to a Vector3.
     * E.g. 0xff0000 represents red and sets the vector to (1, 0, 0).
     * If the property does not exist, out will be set to Vector3(0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector3(0.0f, 0.0f, 0.0f).
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The vector to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getColor(const char* name, Vec3* out) const;

    /**
     * Interpret the value of the given property as an RGBA color in hex and write this color to a Vector4.
     * E.g. 0xff0000ff represents opaque red and sets the vector to (1, 0, 0, 1).
     * If the property does not exist, out will be set to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     * If the property exists but could not be scanned, an error will be logged and out will be set
     * to Vector4(0.0f, 0.0f, 0.0f, 0.0f).
     *
     * @param name The name of the property to interpret, or NULL to return the current property's value.
     * @param out The vector to set to this property's interpreted value.
     * 
     * @return True on success, false if the property does not exist or could not be scanned.
     */
    bool getColor(const char* name, Vec4* out) const;

    /**
     * Gets the file path for the given property if the file exists.
     * 
     * This method will first search for the file relative to the working directory.
     * If the file is not found then it will search relative to the directory the bundle file is in.
     * 
     * @param name The name of the property.
     * @param path The string to copy the path to if the file exists.
     * 
     * @return True if the property exists and the file exists, false otherwise.
     *
     * @script{ignore}
     */
    bool getPath(const char* name, std::string* path) const;

    /**
     * Returns the value of a variable that is set in this Properties object.
     *
     * Variables take on the format ${name} and are inherited from parent Property objects.
     *
     * @param name Name of the variable to get.
     * @param defaultValue Value to return if the variable is not found.
     *
     * @return The value of the specified variable, or defaultValue if not found.
     */
    const char* getVariable(const char* name, const char* defaultValue = NULL) const;

    /**
     * Sets the value of the specified variable.
     *
     * @param name Name of the variable to set.
     * @param value The value to set.
     */
    void setVariable(const char* name, const char* value);

    /**
     * Attempts to parse the specified string as a Vector2 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @param str The string to parse.
     * @param out The value to populate if successful.
     *
     * @return True if a valid Vector2 was parsed, false otherwise.
     */
    static bool parseVec2(const char* str, Vec2* out);

    /**
     * Attempts to parse the specified string as a Vector3 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @param str The string to parse.
     * @param out The value to populate if successful.
     *
     * @return True if a valid Vector3 was parsed, false otherwise.
     */
    static bool parseVec3(const char* str, Vec3* out);
    
    /**
     * Attempts to parse the specified string as a Vector4 value.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @param str The string to parse.
     * @param out The value to populate if successful.
     *
     * @return True if a valid Vector4 was parsed, false otherwise.
     */
    static bool parseVec4(const char* str, Vec4* out);

    /**
     * Attempts to parse the specified string as an axis-angle value.
     *
     * The specified string is expected to contain four comma-separated
     * values, where the first three values represents the axis and the
     * fourth value represents the angle, in degrees.
     *
     * On error, false is returned and the output is set to all zero values.
     *
     * @param str The string to parse.
     * @param out A Quaternion populated with the orientation of the axis-angle, if successful.
     *
     * @return True if a valid axis-angle was parsed, false otherwise.
     */
    static bool parseAxisAngle(const char* str, Quaternion* out);

    /**
     * Attempts to parse the specified string as an RGB color value.
     *
     * @param str The string to parse.
     * @param out The value to populate if successful.
     *
     * @return True if a valid RGB color was parsed, false otherwise.
     */
    static bool parseColor(const char* str, Vec3* out);

    /**
     * Attempts to parse the specified string as an RGBA color value.
     *
     * @param str The string to parse.
     * @param out The value to populate if successful.
     *
     * @return True if a valid RGBA color was parsed, false otherwise.
     */
    static bool parseColor(const char* str, Vec4* out);

private:
    
    /**
     * Internal structure containing a single property.
     */
    struct Property
    {
        std::string name;
        std::string value;
        Property(const std::string& aname, const std::string& avalue) : name(aname), value(avalue) { }
    };

    /**
     * Constructor.
     */
    Properties();

    /**
     * Constructs the Properties class from a file.
     *
     * @param stream The stream used for reading the properties from file.
     */
    Properties(Data* data, ssize_t* dataIdx);
    Properties(const Properties& copy);

    /**
     * Constructor. Read from the beginning of namespace specified.
     */
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

    /**
     * Reads the next character from the Data. Returns EOF if the end of the Data is reached.
     */

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
