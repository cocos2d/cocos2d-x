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
#ifndef __PLATFORM_UPHONE_CCXCOCOS2D_DEFINE_H__
#define __PLATFORM_UPHONE_CCXCOCOS2D_DEFINE_H__

/** CCX_PROPERTY_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 @warning : The getter is a public virtual function, you should rewrite it first.
 The variables and methods declared after CCX_PROPERTY_READONLY are all public.
 If you need protected or private, please declare.
 */
#define CCX_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);

/** CCX_PROPERTY is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public virtual functions, you should rewrite them first.
 The variables and methods declared after CCX_PROPERTY are all public.
 If you need protected or private, please declare.
 */
#define CCX_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);

/** CCX_SYNTHESIZE_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 @warning : The getter is a public inline function.
 The variables and methods declared after CCX_SYNTHESIZE_READONLY are all public.
 If you need protected or private, please declare.
 */
#define CCX_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void){ return varName; }

/** CCX_SYNTHESIZE is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType : the type of variable.
 @param varName : variable name.
 @param funName : "get + funName" is the name of the getter.
 "set + funName" is the name of the setter.
 @warning : The getter and setter are public  inline functions.
 The variables and methods declared after CCX_SYNTHESIZE are all public.
 If you need protected or private, please declare.
 */
#define CCX_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType get##funName(void){ return varName; }\
public: inline void set##funName(varType var){ varName = var; }

#define CCX_SAFE_DELETE(p)			if(p) { delete p; p=NULL; }
#define CCX_SAFE_DELETE_ARRAY(p)    if(p) { delete[] p; p=NULL; }
#define CCX_SAFE_FREE(p)			if(p) { free(p); p=NULL; }
#define CCX_SAFE_RELEASE(p)			if(p) { p->release(); }
#define CCX_SAFE_RELEASE_NULL(p)	if(p) { p->release(); p = NULL; }
#define CCX_SAFE_RETAIN(p)			if(p) { p->retain(); }
#define CCX_BREAK_IF(cond)			if(cond) break;

#ifdef _DEBUG
#include <assert.h>
#include <stdio.h>
#define NSAssert(_CONDITION, _TXT)\
if(! (_CONDITION) )			\
{							\
assert( (_CONDITION) );	\
}
#else
#define NSAssert(_CONDITION, _TXT)
#endif	// _DEBUG

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))	
#endif	

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define self	this
#define YES		true
#define NO		false
#define nil     NULL

#endif // __PLATFORM_UPHONE_CCXCOCOS2D_DEFINE_H__

