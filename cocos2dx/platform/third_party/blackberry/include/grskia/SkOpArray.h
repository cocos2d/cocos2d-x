#ifndef SkOpArray_DEFINED
#define SkOpArray_DEFINED

#include "SkOperand2.h"
#include "SkTDArray_Experimental.h"

typedef SkLongArray(SkOperand2) SkTDOperand2Array; 

class SkOpArray : public SkTDOperand2Array {
public:
	SkOpArray();
	SkOpArray(SkOperand2::OpType type);
	bool getIndex(int index, SkOperand2* operand);
	SkOperand2::OpType getType() { return fType; }
	void setType(SkOperand2::OpType type) { 
		fType = type;
	}
protected:
	SkOperand2::OpType fType;
};

#endif // SkOpArray_DEFINED
