/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Neophit
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "cocoa/CCGeometry.h"
#include "cocoa/CCString.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"

NS_CC_BEGIN

/**
 * @addtogroup tilemap_parallax_nodes
 * @{
 */

/** @brief TMXObjectGroup represents the TMX object group.
@since v0.99.0
*/
class CC_DLL TMXObjectGroup : public Object
{
public:
    TMXObjectGroup();
    virtual ~TMXObjectGroup();

    inline const char* getGroupName(){ return _groupName.c_str(); }
    inline void setGroupName(const char *groupName){ _groupName = groupName; }

    /** return the value for the specific property name */
    String* getProperty(const char* propertyName) const;
    
    CC_DEPRECATED_ATTRIBUTE String *propertyNamed(const char* propertyName) const { return getProperty(propertyName); };

    /** return the dictionary for the specific object name.
    It will return the 1st object found on the array for the given name.
    */
    Dictionary* getObject(const char *objectName) const;
    
    CC_DEPRECATED_ATTRIBUTE Dictionary* objectNamed(const char *objectName) const { return getObject(objectName); };
    
    /** Gets the offset position of child objects */
    inline const Point& getPositionOffset() const { return _positionOffset; };
    
    /** Sets the offset position of child objects */
    inline void setPositionOffset(const Point& offset) { _positionOffset = offset; };
    
    /** Gets the list of properties stored in a dictionary */
    inline Dictionary* getProperties() const { return _properties; };
    
    /** Sets the list of properties */
    inline void setProperties(Dictionary* properties) {
        CC_SAFE_RETAIN(properties);
        CC_SAFE_RELEASE(_properties);
        _properties = properties;
    };
    
    /** Gets the array of the objects */
    inline Array* getObjects() const { return _objects; };
    
    /** Sets the array of the objects */
    inline void setObjects(Array* objects) {
        CC_SAFE_RETAIN(objects);
        CC_SAFE_RELEASE(_objects);
        _objects = objects;
    };
    
protected:
    /** name of the group */
    std::string _groupName;
    /** offset position of child objects */
    Point _positionOffset;
    /** list of properties stored in a dictionary */
    Dictionary* _properties;
    /** array of the objects */
    Array* _objects;
};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //__CCTMX_OBJECT_GROUP_H__