#ifndef SkAnimatorScript2_DEFINED
#define SkAnimatorScript2_DEFINED

#include "SkDisplayable.h"
#include "SkScript2.h"
#include "SkTypedArray.h"

class SkAnimateMaker;
struct SkMemberInfo;

#ifndef SkAnimatorScript_DEFINED
struct SkDisplayEnumMap {
	SkDisplayTypes fType;
	const char* fValues;
};
#endif

class SkAnimatorScript2 : public SkScriptEngine2 {
public:
	SkAnimatorScript2(SkAnimateMaker& , SkDisplayable* working, SkDisplayTypes type);
	~SkAnimatorScript2();
	bool evalMemberCommon(const SkMemberInfo* info, 
		SkDisplayable* displayable, SkOperand2* value);
	SkAnimateMaker& getMaker() { return fMaker; }
	SkDisplayable* getWorking() { return fWorking; }
	static bool MapEnums(const char* ptr, const char* match, size_t len, int* value);
	static const SkDisplayEnumMap& GetEnumValues(SkDisplayTypes type); 
	static SkDisplayTypes ToDisplayType(SkOperand2::OpType type);
	static SkOperand2::OpType ToOpType(SkDisplayTypes type);
private:
	SkAnimateMaker& fMaker;
	SkDisplayable* fWorking;
	friend class SkDump;
	friend struct SkScriptNAnswer;
	// illegal
	SkAnimatorScript2& operator=(const SkAnimatorScript2&);
#ifdef SK_DEBUG
public:
	static void UnitTest();
#endif
};

#endif // SkAnimatorScript2_DEFINED
