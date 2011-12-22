#ifndef SkScriptRuntime_DEFINED
#define SkScriptRuntime_DEFINED

#include "SkOperand2.h"
#include "SkTDArray_Experimental.h"
#include "SkTDStack.h"

class SkScriptCallBack;

typedef SkLongArray(SkString*) SkTDStringArray; 
typedef SkLongArray(SkScriptCallBack*) SkTDScriptCallBackArray; 

class SkScriptRuntime {
public:
	enum SkError {
		kNoError,
		kArrayIndexOutOfBounds,
		kCouldNotFindReferencedID,
		kFunctionCallFailed,
		kMemberOpFailed,
		kPropertyOpFailed
	};

	SkScriptRuntime(SkTDScriptCallBackArray& callBackArray) : fCallBackArray(callBackArray)
		{  }
	~SkScriptRuntime();
	bool executeTokens(unsigned char* opCode);
	bool getResult(SkOperand2* result);
	void untrack(SkOpArray* array);
	void untrack(SkString* string);
private:
	void track(SkOpArray* array);
	void track(SkString* string);
	SkTDScriptCallBackArray& fCallBackArray;
	SkError fError;
	SkTDStack<SkOperand2> fRunStack;
	SkLongArray(SkOpArray*) fTrackArray;
	SkTDStringArray fTrackString;
	// illegal
	SkScriptRuntime& operator=(const SkScriptRuntime&);
};

#endif // SkScriptRuntime_DEFINED