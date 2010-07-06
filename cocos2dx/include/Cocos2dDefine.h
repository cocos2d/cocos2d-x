#ifndef __COCOS2D_DEFINE_H__
#define __COCOS2D_DEFINE_H__

#define GET_VARIABLE(varType, varName)\
	public inline varType get##varName() { return varName; };

#define SET_VARIABLE(varType, varName)\
	public inline void set##varName(varType funVar) { varName = funVar; };

#define VAR_PROPERTY_READONLY(varType, varName)\
	protected varType m_##varName;\
	GET_VARIABLE(varType, varName)

#define VAR_PROPERTY_READWRITE(varType, varName)\
	protected varType m_##varName;\
	GET_VARIABLE(varType, varName)\
	SET_VARIABLE(varTYPE, varName)

#endif // __COCOS2D_DEFINE_H__