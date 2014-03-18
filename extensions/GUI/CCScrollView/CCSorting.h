/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im
 
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

#ifndef __CCSORTING_H__
#define __CCSORTING_H__

#include "cocoa/CCArray.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCSortableObject
{
public:
    virtual ~CCSortableObject() {}
    virtual void setObjectID(unsigned int objectID) = 0;
    virtual unsigned int getObjectID() = 0;
};
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCArrayForObjectSorting : public CCArray
{
public:
    CCArrayForObjectSorting() : CCArray() {}
    /*!
     * Inserts a given object into array.
     * 
     * Inserts a given object into array with key and value that are used in
     * sorting. "value" must respond to message, compare:, which returns 
     * (NSComparisonResult). If it does not respond to the message, it is appended.
     * If the compare message does not result NSComparisonResult, sorting behavior
     * is not defined. It ignores duplicate entries and inserts next to it.
     *
     * @param object to insert
     */
    void insertSortedObject(CCSortableObject* object);

    /*!
     * Removes an object in array.
     *
     * Removes an object with given key and value. If no object is found in array
     * with the key and value, no action is taken.
     *
     * @param value to remove
     */
    void removeSortedObject(CCSortableObject* object);
    /*!
     * Sets a new value of the key for the given object.
     * 
     * In case where sorting value must be changed, this message must be sent to
     * keep consistency of being sorted. If it is changed externally, it must be
     * sorted completely again.
     *
     * @param value to set
     * @param object the object which has the value
     */
    void setObjectID_ofSortedObject(unsigned int tag, CCSortableObject* object);

    CCSortableObject* objectWithObjectID(unsigned int tag);
    /*!
     * Returns an object with given key and value.
     * 
     * Returns an object with given key and value. If no object is found,
     * it returns nil.
     *
     * @param value to locate object
     * @return object found or nil.
     */
    CCSortableObject* getObjectWithObjectID(unsigned int tag);

    /*!
     * Returns an index of the object with given key and value.
     *
     * Returns the index of an object with given key and value. 
     * If no object is found, it returns an index at which the given object value
     * would have been located. If object must be located at the end of array,
     * it returns the length of the array, which is out of bound.
     * 
     * @param value to locate object
     * @return index of an object found
     */
    unsigned int indexOfSortedObject(CCSortableObject* obj);

};

NS_CC_EXT_END

#endif /* __CCSORTING_H__ */

