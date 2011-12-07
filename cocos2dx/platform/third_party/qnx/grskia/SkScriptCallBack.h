#ifndef SkScriptCallBack_DEFINED
#define SkScriptCallBack_DEFINED

#include "SkOperand2.h"
#include "SkTDArray_Experimental.h"

class SkScriptCallBack {
public:
	enum Type {
		kBox,
		kFunction,
		kMember,
		kMemberFunction,
		kProperty,
		kUnbox
	};

	virtual bool getReference(const char* , size_t len, SkScriptValue2* result) {  return false; }
	virtual SkOperand2::OpType getReturnType(size_t ref, SkOperand2*) { 
		return SkOperand2::kS32; }
	virtual Type getType() const = 0;
};

class SkScriptCallBackConvert : public SkScriptCallBack {
public:
	virtual bool convert(SkOperand2::OpType type, SkOperand2* operand) = 0;
};

class SkScriptCallBackFunction : public SkScriptCallBack {
public:
	virtual void getParamTypes(SkIntArray(SkOperand2::OpType)* types) = 0;
	virtual Type getType() const { return kFunction; }
	virtual bool invoke(size_t ref, SkOpArray* params, SkOperand2* value) = 0;
};

class SkScriptCallBackMember: public SkScriptCallBack {
public:
	bool getMemberReference(const char* , size_t len, void* object, SkScriptValue2* ref);
	virtual Type getType() const { return kMember; }
	virtual bool invoke(size_t ref, void* object, SkOperand2* value) = 0;
};

class SkScriptCallBackMemberFunction : public SkScriptCallBack {
public:
	bool getMemberReference(const char* , size_t len, void* object, SkScriptValue2* ref);
	virtual void getParamTypes(SkIntArray(SkOperand2::OpType)* types) = 0;
	virtual Type getType() const { return kMemberFunction; }
	virtual bool invoke(size_t ref, void* object, SkOpArray* params, SkOperand2* value) = 0;
};

class SkScriptCallBackProperty : public SkScriptCallBack {
public:
	virtual bool getConstValue(const char* name, size_t len, SkOperand2* value) { return false; }
	virtual bool getResult(size_t ref, SkOperand2* answer) { return false; }
	virtual Type getType() const { return kProperty; }
};

#endif // SkScriptCallBack_DEFINED
