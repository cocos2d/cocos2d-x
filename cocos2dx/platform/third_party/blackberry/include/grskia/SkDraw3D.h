/* libs/graphics/animator/SkDraw3D.h
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

#ifndef SkDraw3D_DEFINED
#define SkDraw3D_DEFINED

#include "SkCamera.h"
#include "SkDrawable.h"
#include "SkMemberInfo.h"

class Sk3D_Patch;

struct Sk3D_Point {
    DECLARE_NO_VIRTUALS_MEMBER_INFO(3D_Point);
    Sk3D_Point();
private:
    SkPoint3D fPoint;
};

class Sk3D_Camera : public SkDrawable {
    DECLARE_MEMBER_INFO(3D_Camera);
    Sk3D_Camera();
    virtual ~Sk3D_Camera();
    virtual bool draw(SkAnimateMaker& );
private:
    SkScalar hackWidth;
    SkScalar hackHeight;
    SkCamera3D fCamera;
    Sk3D_Patch* patch;
};

class Sk3D_Patch : public SkDisplayable {
    DECLARE_MEMBER_INFO(3D_Patch);
private:
    virtual void executeFunction(SkDisplayable* , int index, 
        SkTDArray<SkScriptValue>& parameters, SkDisplayTypes type,
        SkScriptValue* );
    virtual const SkFunctionParamType* getFunctionsParameters();
    SkPatch3D  fPatch;
    static const SkFunctionParamType fFunctionParameters[];
    friend class Sk3D_Camera;
};

#endif // SkDraw3D_DEFINED

