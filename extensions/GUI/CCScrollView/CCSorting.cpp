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

#include "CCSorting.h"
#include "ccCArray.h"


NS_CC_EXT_BEGIN

class SortedObject : public Object, public SortableObject
{
public:
    SortedObject() : objectID(0) {}
    virtual void setObjectID(long id) { this->objectID = id; }
    virtual long getObjectID() { return objectID; }
private:
    long objectID;
};

#if 0
static int _compareObject(const void * val1, const void * val2)
{
    SortableObject* operand1;
    SortableObject* operand2;

    operand1 = (SortableObject*)val1;
    operand2 = (SortableObject*)val2;

    if (operand1->getObjectID() > operand2->getObjectID())
    {
        return 1;
    } 
    else if (operand1->getObjectID() < operand2->getObjectID()) {
        return -1;
    }
    return 0;
}
#endif


void ArrayForObjectSorting::insertSortedObject(SortableObject* object)
{
    Object* pObj = dynamic_cast<Object*>(object);
    CCASSERT(pObj, "Invalid parameter.");
    long idx = this->indexOfSortedObject(object);
    
    this->insertObject(pObj, idx);
}

void ArrayForObjectSorting::removeSortedObject(SortableObject* object)
{
    if (this->count() == 0) {
        return;
    }

    SortableObject* foundObj = nullptr;
    long idx = this->indexOfSortedObject(object);
    
    if (idx < this->count() && idx != CC_INVALID_INDEX) {
        foundObj = dynamic_cast<SortableObject*>(this->getObjectAtIndex(idx));
        
        if(foundObj->getObjectID() == object->getObjectID()) {
            this->removeObjectAtIndex(idx);
        }
    }
}

void ArrayForObjectSorting::setObjectID_ofSortedObject(unsigned int tag, SortableObject* object)
{
    SortableObject* foundObj = nullptr;
    
    long  idx = this->indexOfSortedObject(object);
    
    if (idx < this->count() && idx != CC_INVALID_INDEX)
    {
        foundObj = dynamic_cast<SortableObject*>(this->getObjectAtIndex(idx));
        Object* pObj = dynamic_cast<Object*>(foundObj);
        pObj->retain();
        
        if(foundObj->getObjectID() == object->getObjectID()) {
            this->removeObjectAtIndex(idx);
            foundObj->setObjectID(tag);
            this->insertSortedObject(foundObj);
            pObj->release();
        } else {
            pObj->release();
        }
    }
}

SortableObject* ArrayForObjectSorting::objectWithObjectID(long tag)
{
    if (this->count() == 0) {
        return NULL;
    }
    
    SortableObject* foundObj = new SortedObject();
    foundObj->setObjectID(tag);
    
    long idx  = this->indexOfSortedObject(foundObj);
    
    ((SortedObject*)foundObj)->release();
    foundObj = NULL;
    
    if (idx < this->count() && idx != CC_INVALID_INDEX)
    {
        foundObj = dynamic_cast<SortableObject*>(this->getObjectAtIndex(idx));
        if (foundObj->getObjectID() != tag) {
            foundObj = NULL;
        }
    }
    
    return foundObj;
}

long ArrayForObjectSorting::indexOfSortedObject(SortableObject* object)
{
    long  idx = 0;
    if (object)
    {
 //       Object* pObj = (Object*)bsearch((Object*)&object, data->arr, data->num, sizeof(Object*), _compareObject);
        // FIXME: need to use binary search to improve performance
        Object* obj = NULL;
        long prevObjectID = 0;
        long ofSortObjectID = object->getObjectID();

        CCARRAY_FOREACH(this, obj)
        {
            SortableObject* sortableObj = dynamic_cast<SortableObject*>(obj);
            long curObjectID = sortableObj->getObjectID();
            if (  (ofSortObjectID == curObjectID)
                  || (ofSortObjectID >= prevObjectID && ofSortObjectID < curObjectID))
            {
                break;
            }
            
            prevObjectID = curObjectID;
            idx++;
        }
    }
    else
    {
        idx = CC_INVALID_INDEX;
    }
    return idx;
}

NS_CC_EXT_END
