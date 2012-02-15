/* libs/graphics/animator/SkExtras.h
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

#ifndef SkExtras_DEFINED
#define SkExtras_DEFINED

#include "SkScript.h"

class SkExtras {
public:
            SkExtras();
    virtual ~SkExtras() {}

    virtual SkDisplayable* createInstance(SkDisplayTypes type) = 0;
    virtual bool definesType(SkDisplayTypes type) = 0;
#if SK_USE_CONDENSED_INFO == 0
    virtual const SkMemberInfo* getMembers(SkDisplayTypes type, int* infoCountPtr) = 0;
#endif
#ifdef SK_DEBUG
    virtual const char* getName(SkDisplayTypes type) = 0;
#endif
    virtual SkDisplayTypes getType(const char match[], size_t len ) = 0;

    SkScriptEngine::_propertyCallBack fExtraCallBack;
    void* fExtraStorage;
};

#endif // SkExtras_DEFINED
