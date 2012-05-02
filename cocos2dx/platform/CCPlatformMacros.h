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
#ifndef __CC_PLATFORM_MACROS_H__
#define __CC_PLATFORM_MACROS_H__

/**
 * define some platform specific macros
 */
#include "ccConfig.h"
#include "CCPlatformConfig.h"
#include "CCPlatformDefine.h"

/** @def CC_ENABLE_CACHE_TEXTTURE_DATA
Enable it if you want to cache the texture data.
Basically,it's only enabled in android

It's new in cocos2d-x since v0.99.5
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #define CC_ENABLE_CACHE_TEXTTURE_DATA       1
#else
    #define CC_ENABLE_CACHE_TEXTTURE_DATA       0
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    /* Application will crash in glDrawElements function on some win32 computers and some android devices.
       Indices should be bound again while drawing to avoid this bug.
     */
    #define CC_REBIND_INDICES_BUFFER  1
#else
    #define CC_REBIND_INDICES_BUFFER  0
#endif

// generic macros

// namespace cocos2d {}
#ifdef __cplusplus
    #define NS_CC_BEGIN                     namespace cocos2d {
    #define NS_CC_END                       }
    #define USING_NS_CC                     using namespace cocos2d
    #define NS_CC_EXT_BEGIN                 namespace cocos2d { namespace extension { 
    #define NS_CC_EXT_END                   }} 
    #define USING_NS_CC_EXT                 using namespace cocos2d::extension
#else
    #define NS_CC_BEGIN                     
    #define NS_CC_END
    #define USING_NS_CC                     
    #define NS_CC_EXT_BEGIN                 
    #define NS_CC_EXT_END    
    #define USING_NS_CC_EXT 
#endif 

/** CC_PROPERTY_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 @warning : The getter is a public virtual function, you should rewrite it first.
 The variables and methods declared after CC_PROPERTY_READONLY are all public.
 If you need protected or private, please declare.
 */
#define CC_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);

#define CC_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void);

/** CC_PROPERTY is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public virtual functions, you should rewrite them first.
 The variables and methods declared after CC_PROPERTY are all public.
 If you need protected or private, please declare.
 */
#define CC_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);

#define CC_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void);\
public: virtual void set##funName(const varType& var);

/** CC_SYNTHESIZE_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 @warning : The getter is a public inline function.
 The variables and methods declared after CC_SYNTHESIZE_READONLY are all public.
 If you need protected or private, please declare.
 */
#define CC_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define CC_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }

/** CC_SYNTHESIZE is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public  inline functions.
 The variables and methods declared after CC_SYNTHESIZE are all public.
 If you need protected or private, please declare.
 */
#define CC_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define CC_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }

#define CC_SYNTHESIZE_RETAIN(varType, varName, funName)    \
private: varType varName; \
public: virtual varType get##funName(void) const { return varName; } \
public: virtual void set##funName(varType var)   \
{ \
    if (varName != var) \
    { \
        CC_SAFE_RETAIN(var); \
        CC_SAFE_RELEASE(varName); \
        varName = var; \
    } \
} 

#define CC_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define CC_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define CC_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define CC_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define CC_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#define CC_BREAK_IF(cond)            if(cond) break


// cocos2d debug
#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
#define CCLOG(...)              
#define CCLOGINFO(...)         
#define CCLOGERROR(...)         

#elif COCOS2D_DEBUG == 1
#define CCLOG(format, ...)      cocos2d::CCLog(format, ##__VA_ARGS__)
#define CCLOGERROR(format,...)  cocos2d::CCLog(format, ##__VA_ARGS__)
#define CCLOGINFO(format,...)   do {} while (0)

#elif COCOS2D_DEBUG > 1
#define CCLOG(format, ...)      cocos2d::CCLog(format, ##__VA_ARGS__)
#define CCLOGERROR(format,...)  cocos2d::CCLog(format, ##__VA_ARGS__)
#define CCLOGINFO(format,...)   cocos2d::CCLog(format, ##__VA_ARGS__)
#endif // COCOS2D_DEBUG

// Lua engine debug
#if !defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0 || CC_LUA_ENGINE_DEBUG == 0
#define LUALOG(...)
#else
#define LUALOG(format, ...)     cocos2d::CCLog(format, ##__VA_ARGS__)
#endif // Lua engine debug


#endif // __CC_PLATFORM_MACROS_H__
