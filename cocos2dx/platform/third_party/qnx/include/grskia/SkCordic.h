/* libs/corecg/SkCordic.h
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

#ifndef SkCordic_DEFINED
#define SkCordic_DEFINED

#include "SkTypes.h"
#include "SkFixed.h"

SkFixed SkCordicACos(SkFixed a);
SkFixed SkCordicASin(SkFixed a);
SkFixed SkCordicATan2(SkFixed y, SkFixed x);
SkFixed SkCordicExp(SkFixed a);
SkFixed SkCordicLog(SkFixed a);
SkFixed SkCordicSinCos(SkFixed radians, SkFixed* cosp);
SkFixed SkCordicTan(SkFixed a);

#ifdef SK_DEBUG
    void SkCordic_UnitTest();
#endif

#endif // SkCordic 

