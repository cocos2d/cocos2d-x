/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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


#include "CCObject.h"
#include "CCAutoreleasePool.h"
#include "ccMacros.h"
#include "script_support/CCScriptSupport.h"
#include <map>

NS_CC_BEGIN


CCObject* CCCopying::copyWithZone(CCZone *pZone)
{
    CC_UNUSED_PARAM(pZone);
    CCAssert(0, "not implement");
    return 0;
}

CCObject::CCObject(void)
: m_nLuaID(0)
, m_uReference(1) // when the object is created, the reference count of it is 1
, m_uAutoReleaseCount(0)
{
    static unsigned int uObjectCount = 0;

    m_uID = ++uObjectCount;
}

static void releaseWeakReferenceFor(CCObject *obj);
CCObject::~CCObject(void)
{
    // release weak reference to this object
    releaseWeakReferenceFor(this);

    // if the object is managed, we should remove it
    // from pool manager
    if (m_uAutoReleaseCount > 0)
    {
        CCPoolManager::sharedPoolManager()->removeObject(this);
    }

    // if the object is referenced by Lua engine, remove it
    if (m_nLuaID)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptObjectByCCObject(this);
    }
    else
    {
        CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        if (pEngine != NULL && pEngine->getScriptType() == kScriptTypeJavascript)
        {
            pEngine->removeScriptObjectByCCObject(this);
        }
    }
}

CCObject* CCObject::copy()
{
    return copyWithZone(0);
}

void CCObject::release(void)
{
    CCAssert(m_uReference > 0, "reference count should greater than 0");
    --m_uReference;

    if (m_uReference == 0)
    {
        delete this;
    }
}

void CCObject::retain(void)
{
    CCAssert(m_uReference > 0, "reference count should greater than 0");

    ++m_uReference;
}

CCObject* CCObject::autorelease(void)
{
    CCPoolManager::sharedPoolManager()->addObject(this);
    return this;
}

bool CCObject::isSingleReference(void)
{
    return m_uReference == 1;
}

unsigned int CCObject::retainCount(void)
{
    return m_uReference;
}

bool CCObject::isEqual(const CCObject *pObject)
{
    return this == pObject;
}

// CCWeakReference

// weak reference info, a std::pair which contains (refcount, CCObject *)
typedef std::pair<unsigned int, CCObject **> Referent;
// a map which stores all weak reference infomations.
// the key is CCObject::m_uID
typedef std::map<unsigned int, Referent> ReferentMap;



// the order of initialization of global variables is undeterminable, using lazyload
// can avoid potential crash.
static inline ReferentMap* GetReferentMap()
{
    static cocos2d::ReferentMap _referent_map;
    return &_referent_map;
}

static void releaseWeakReferenceFor(CCObject *obj) {
    ReferentMap *ref_map = GetReferentMap();
    if(ref_map->size() == 0)
        return;

    // takes O(lgN) times, N is the amount of currently weak referenced objects.
    ReferentMap::iterator iter = ref_map->find(obj->m_uID);

    if (iter == ref_map->end()) { //not found
        return;
    } else {
        CCObject **ppobj = iter->second.second;
        *ppobj = NULL;
    }
}

CCWeakReference::CCWeakReference(CCObject *obj) :
object_id(obj ? obj->m_uID : 0),
pp_obj(NULL)
{
    incRef(obj);
}

CCWeakReference::CCWeakReference(const CCWeakReference &weakref) :
object_id(weakref.getObjectId()),
pp_obj(NULL)
{
    incRef();
}

CCWeakReference &CCWeakReference::operator=(const CCWeakReference& weakref)
{
    decRef(); // for previous referenced obj

    this->object_id = weakref.getObjectId();
    this->pp_obj = NULL;

    incRef();
    return *this;
}

bool CCWeakReference::operator==(const CCWeakReference& weakref) const
{
    return this->object_id == weakref.object_id;
}

CCWeakReference::~CCWeakReference()
{
    decRef();
}

unsigned int CCWeakReference::getWeakRefCount(CCObject *obj)
{
    ReferentMap *ref_map = GetReferentMap();

    ReferentMap::const_iterator iter = ref_map->find(obj->m_uID);
    if (iter == ref_map->end()){ //not found
        return 0;
    } else {
        return iter->second.first;
    }
}

void CCWeakReference::incRef(CCObject *obj)
{
    if(!object_id)
        return;

    ReferentMap *ref_map = GetReferentMap();

    ReferentMap::iterator iter = ref_map->find(object_id);
    if (iter == ref_map->end()){  //not referenced before
        // point to CCObject *
        CCObject **ppobj = new CCObject *;
        *ppobj = obj;

        // set ref count to 1, and add to map
        (*ref_map)[object_id] = Referent(1, ppobj);
        this->pp_obj = ppobj;
    } else {  // already referenced before
        // ref count + 1
        iter->second.first += 1;
        this->pp_obj = iter->second.second;
    }
}

void CCWeakReference::decRef()
{
    if (!object_id)
        return;

    ReferentMap *ref_map = GetReferentMap();

    ReferentMap::iterator iter = ref_map->find(object_id);
    if (iter == ref_map->end()){  // not referenced
        //error
        CCAssert(0, "weakref < 0");
    } else {
        // ref count - 1
        unsigned int weakref = (iter->second.first -= 1);

        // no weak ref anymore
        if( weakref == 0 ) {
            CCObject **ppobj = iter->second.second;
            // remove from map
            ref_map->erase(iter);
            delete ppobj;
        }
    }
}

// End of CCWeakReference

NS_CC_END
