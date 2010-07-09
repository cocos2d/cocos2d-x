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

#ifndef __COCOS2D_DEFINE_H__
#define __COCOS2D_DEFINE_H__

/** CCX_DECLARE_VAR_READONLY is used to declare a protected variable.
	We can use get method to read the variable.
	@param varType : the type of variable.
	@param varName : variable name.
	@param funName : "get + funName" is the name of the get method.
	@warning : The get method is a public virtual function, you should override it first.
			The variables and methods declared after CCX_DECLARE_VAR_READONLY are all public.
			If you need protected or private, please declare.
*/
#define CCX_DECLARE_VAR_READONLY(varType, varName, funName)\
	protected: varType varName;\
	public: virtual varType get##funName(void);

/** CCX_DECLARE_VAR_READWRITE is used to declare a protected variable.
	We can use get method to read the variable, and use the set method to change the variable.
	@param varType : the type of variable.
	@param varName : variable name.
	@param funName : "get + funName" is the name of the get method.
					 "set + funName" is the name of the set method.
	@warning : The get and set methods are public virtual functions, you should override them first.
			The variables and methods declared after CCX_DECLARE_VAR_READWRITE are all public.
			If you need protected or private, please declare.
*/
#define CCX_DECLARE_VAR_READWRITE(varType, varName, funName)\
	protected: varType varName;\
	public: virtual varType get##funName(void);\
	public: virtual void set##funName(varType var);

/** CCX_DECLARE_VAR_READONLY_INLINE is used to declare a protected variable.
	We can use get method to read the variable.
	@param varType : the type of variable.
	@param varName : variable name.
	@param funName : "get + funName" is the name of the get method.
	@warning : The get method is a public inline function.
			The variables and methods declared after CCX_DECLARE_VAR_READONLY_INLINE are all public.
			If you need protected or private, please declare.
*/
#define CCX_DECLARE_VAR_READONLY_INLINE(varType, varName, funName)\
	protected: varType varName;\
	public: inline varType get##funName(void){ return varName; }

/** CCX_DECLARE_VAR_READWRITE_INLINE is used to declare a protected variable.
	We can use get method to read the variable, and use the set method to change the variable.
	@param varType : the type of variable.
	@param varName : variable name.
	@param funName : "get + funName" is the name of the get method.
					 "set + funName" is the name of the set method.
	@warning : The get and set methods are public  inline functions.
			The variables and methods declared after CCX_DECLARE_VAR_READWRITE_INLINE are all public.
			If you need protected or private, please declare.
*/
#define CCX_DECLARE_VAR_READWRITE_INLINE(varType, varName, funName)\
	protected: varType varName;\
	public: inline varType get##funName(void){ return varName; }\
	public: inline void set##funName(varType var){ varName = var; }

#endif // __COCOS2D_DEFINE_H__