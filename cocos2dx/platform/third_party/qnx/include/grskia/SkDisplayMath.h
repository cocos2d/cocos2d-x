/* libs/graphics/animator/SkDisplayMath.h
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

#ifndef SkDisplayMath_DEFINED
#define SkDisplayMath_DEFINED

#include "SkDisplayable.h"
#include "SkMemberInfo.h"
#include "SkRandom.h"

class SkDisplayMath : public SkDisplayable {
    DECLARE_DISPLAY_MEMBER_INFO(Math);
    virtual void executeFunction(SkDisplayable* , int index, 
        SkTDArray<SkScriptValue>& parameters, SkDisplayTypes type,
        SkScriptValue* );
    virtual const SkFunctionParamType* getFunctionsParameters();
    virtual bool getProperty(int index, SkScriptValue* value) const;
private:
    mutable SkRandom fRandom;
    static const SkScalar gConstants[];
    static const SkFunctionParamType fFunctionParameters[];

};
    
#endif // SkDisplayMath_DEFINED

