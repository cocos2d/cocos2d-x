/****************************************************************************
 Copyright (c) 2014     PlayFirst Inc.
 Copyright (c) 2014     Chukong Technologies Inc.
 
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

#ifndef __CC_REF_PTR_H__
#define __CC_REF_PTR_H__

#include "base/CCRef.h"
#include <type_traits>

NS_CC_BEGIN

/**
 * Utility/support macros. Defined to enable RefPtr<T> to contain types like 'const T' because we do not
 * regard retain()/release() as affecting mutability of state.
 */
#define CC_REF_PTR_SAFE_RETAIN(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->retain();\
        }\
    \
    }   while (0);

#define CC_REF_PTR_SAFE_RELEASE(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->release();\
        }\
    \
    }   while (0);

#define CC_REF_PTR_SAFE_RELEASE_NULL(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->release();\
            ptr = nullptr;\
        }\
    \
    }   while (0);

/**
 * Wrapper class which maintains a strong reference to a cocos2dx cocos2d::Ref* type object.
 * Similar in concept to a boost smart pointer.
 *
 * Enables the use of the RAII idiom with Cocos2dx objects and helps automate some of the more 
 * mundane tasks of pointer initialization and cleanup.
 *
 * The class itself is modelled on C++ 11 std::shared_ptr, and trys to keep some of the methods 
 * and functionality consistent with std::shared_ptr.
 */
template <typename T> class RefPtr
{
public:
    
    inline RefPtr()
    :
        _ptr(nullptr)
    {
        
    }
    
    inline RefPtr(RefPtr<T> && other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline RefPtr(T * ptr)
    :
        _ptr(const_cast<typename std::remove_const<T>::type*>(ptr))     // Const cast allows RefPtr<T> to reference objects marked const too.
    {
        CC_REF_PTR_SAFE_RETAIN(_ptr);
    }
    
    inline RefPtr(std::nullptr_t ptr)
    :
        _ptr(nullptr)
    {
        
    }
    
    inline RefPtr(const RefPtr<T> & other)
    :
        _ptr(other._ptr)
    {
        CC_REF_PTR_SAFE_RETAIN(_ptr);
    }
    
    inline ~RefPtr()
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
    }
    
    inline RefPtr<T> & operator = (const RefPtr<T> & other)
    {
        if (other._ptr != _ptr)
        {
            CC_REF_PTR_SAFE_RETAIN(other._ptr);
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
        }
        
        return *this;
    }
    
    inline RefPtr<T> & operator = (RefPtr<T> && other)
    {
        if (&other != this)
        {
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        
        return *this;
    }
    
    inline RefPtr<T> & operator = (T * other)
    {
        if (other != _ptr)
        {
            CC_REF_PTR_SAFE_RETAIN(other);
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = const_cast<typename std::remove_const<T>::type*>(other);     // Const cast allows RefPtr<T> to reference objects marked const too.
        }
        
        return *this;
    }
    
    inline RefPtr<T> & operator = (std::nullptr_t other)
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
        return *this;
    }
    
    // Note: using reinterpret_cast<> instead of static_cast<> here because it doesn't require type info.
    // Since we verify the correct type cast at compile time on construction/assign we don't need to know the type info
    // here. Not needing the type info here enables us to use these operations in inline functions in header files when
    // the type pointed to by this class is only forward referenced.
    
    inline operator T * () const { return reinterpret_cast<T*>(_ptr); }
    
    inline T & operator * () const
    {
        CCASSERT(_ptr, "Attempt to dereference a null pointer!");
        return reinterpret_cast<T&>(*_ptr);
    }
    
    inline T * operator->() const
    {
        CCASSERT(_ptr, "Attempt to dereference a null pointer!");
        return reinterpret_cast<T*>(_ptr);
    }
    
    inline T * get() const { return reinterpret_cast<T*>(_ptr); }
    
    
    inline bool operator == (const RefPtr<T> & other) const { return _ptr == other._ptr; }
    
    inline bool operator == (const T * other) const { return _ptr == other; }
    
    inline bool operator == (typename std::remove_const<T>::type * other) const { return _ptr == other; }
    
    inline bool operator == (const std::nullptr_t other) const { return _ptr == other; }
    
    
    inline bool operator != (const RefPtr<T> & other) const { return _ptr != other._ptr; }
    
    inline bool operator != (const T * other) const { return _ptr != other; }
    
    inline bool operator != (typename std::remove_const<T>::type * other) const { return _ptr != other; }
    
    inline bool operator != (const std::nullptr_t other) const { return _ptr != other; }
    
    
    inline bool operator > (const RefPtr<T> & other) const { return _ptr > other._ptr; }
    
    inline bool operator > (const T * other) const { return _ptr > other; }
    
    inline bool operator > (typename std::remove_const<T>::type * other) const { return _ptr > other; }
    
    inline bool operator > (const std::nullptr_t other) const { return _ptr > other; }
    
    
    inline bool operator < (const RefPtr<T> & other) const { return _ptr < other._ptr; }
    
    inline bool operator < (const T * other) const { return _ptr < other; }
    
    inline bool operator < (typename std::remove_const<T>::type * other) const { return _ptr < other; }
    
    inline bool operator < (const std::nullptr_t other) const { return _ptr < other; }
    
        
    inline bool operator >= (const RefPtr<T> & other) const { return _ptr >= other._ptr; }
    
    inline bool operator >= (const T * other) const { return _ptr >= other; }
    
    inline bool operator >= (typename std::remove_const<T>::type * other) const { return _ptr >= other; }
    
    inline bool operator >= (const std::nullptr_t other) const { return _ptr >= other; }
    
        
    inline bool operator <= (const RefPtr<T> & other) const { return _ptr <= other._ptr; }
    
    inline bool operator <= (const T * other) const { return _ptr <= other; }
    
    inline bool operator <= (typename std::remove_const<T>::type * other) const { return _ptr <= other; }
    
    inline bool operator <= (const std::nullptr_t other) const { return _ptr <= other; }
    
        
    inline operator bool() const { return _ptr != nullptr; }
        
    inline void reset()
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
    }
        
    inline void swap(RefPtr<T> & other)
    {
        if (&other != this)
        {
            Ref * tmp = _ptr;
            _ptr = other._ptr;
            other._ptr = tmp;
        }
    }
    
    /**
     * This function assigns to this RefPtr<T> but does not increase the reference count of the object pointed to.
     * Useful for assigning an object created through the 'new' operator to a RefPtr<T>. Basically used in scenarios
     * where the RefPtr<T> has the initial ownership of the object.
     *
     * E.G:
     *      RefPtr<cocos2d::Image> image;
     *      image.weakAssign(new cocos2d::Image());
     *
     * Instead of:
     *      RefPtr<cocos2d::Image> image;
     *      image = new cocos2d::Image();
     *      image->release();               // Required because new'd object already has a reference count of '1'.
     */
    inline void weakAssign(const RefPtr<T> & other)
    {
        CC_REF_PTR_SAFE_RELEASE(_ptr);
        _ptr = other._ptr;
    }
    
private:
    Ref * _ptr;
};
    
/**
 * Cast between RefPtr types statically.
 */
template<class T, class U> RefPtr<T> static_pointer_cast(const RefPtr<U> & r)
{
    return RefPtr<T>(static_cast<T*>(r.get()));
}

/**
 * Cast between RefPtr types dynamically.
 */
template<class T, class U> RefPtr<T> dynamic_pointer_cast(const RefPtr<U> & r)
{
    return RefPtr<T>(dynamic_cast<T*>(r.get()));
}

/**
 * Done with these macros.
 */
#undef CC_REF_PTR_SAFE_RETAIN
#undef CC_REF_PTR_SAFE_RELEASE
#undef CC_REF_PTR_SAFE_RELEASE_NULL

NS_CC_END

#endif  // __CC_REF_PTR_H__
