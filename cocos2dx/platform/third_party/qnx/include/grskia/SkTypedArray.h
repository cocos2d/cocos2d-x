/* libs/graphics/animator/SkTypedArray.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkTypedArray_DEFINED
#define SkTypedArray_DEFINED

#include "SkScript.h"
#include "SkTDArray_Experimental.h"

class SkTypedArray : public SkTDOperandArray {
public:
    SkTypedArray();
    SkTypedArray(SkDisplayTypes type);
    bool getIndex(int index, SkOperand* operand);
    SkDisplayTypes getType() { return fType; }
    SkScriptEngine::SkOpType getOpType() { return SkScriptEngine::ToOpType(fType); }
    void setType(SkDisplayTypes type) { 
    //  SkASSERT(count() == 0);
        fType = type;
    }
protected:
    SkDisplayTypes fType;
};

#endif // SkTypedArray_DEFINED
