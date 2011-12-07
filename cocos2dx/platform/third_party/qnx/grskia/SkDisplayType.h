/* libs/graphics/animator/SkDisplayType.h
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

#ifndef SkDisplayType_DEFINED
#define SkDisplayType_DEFINED

#include "SkMath.h"
#include "SkScalar.h"

#ifdef SK_DEBUG
    #ifdef SK_CAN_USE_FLOAT
        #define SK_DUMP_ENABLED
    #endif
    #ifdef SK_BUILD_FOR_MAC
        #define SK_FIND_LEAKS
    #endif
#endif

#define SK_LITERAL_STR_EQUAL(str, token, len) (sizeof(str) - 1 == len \
    && strncmp(str, token, sizeof(str) - 1) == 0)

class SkAnimateMaker;
class SkDisplayable;
struct SkMemberInfo;

enum SkDisplayTypes {
    SkType_Unknown,
    SkType_Math, // for ecmascript compatible Math functions and constants
    SkType_Number,  // for for ecmascript compatible Number functions and constants
    SkType_Add,
    SkType_AddCircle,
    SkType_AddGeom,
    SkType_AddMode,
    SkType_AddOval,
    SkType_AddPath,
    SkType_AddRect, // path part
    SkType_AddRoundRect,
    SkType_Align,
    SkType_Animate,
    SkType_AnimateBase, // base type for animate, set
    SkType_Apply,
    SkType_ApplyMode,
    SkType_ApplyTransition,
    SkType_Array,
    SkType_ARGB,
    SkType_Base64,
    SkType_BaseBitmap,
    SkType_BaseClassInfo,
    SkType_Bitmap,
    SkType_BitmapEncoding,
    SkType_BitmapFormat,
    SkType_BitmapShader,
    SkType_Blur,
    SkType_Boolean, // can have values -1 (uninitialized), 0, 1
    SkType_Boundable,
    SkType_Bounds,
    SkType_Cap,
    SkType_Clear,
    SkType_Clip,
    SkType_Close,
    SkType_Color,
    SkType_CubicTo,
    SkType_Dash,
    SkType_DataInput,
    SkType_Discrete,
    SkType_Displayable,
    SkType_Drawable,
    SkType_DrawTo,
    SkType_Dump,
    SkType_DynamicString,   // evaluate at draw time
    SkType_Emboss,
    SkType_Event,
    SkType_EventCode,
    SkType_EventKind,
    SkType_EventMode,
    SkType_FillType,
    SkType_FilterType,
    SkType_Float,
    SkType_FontStyle,
    SkType_FromPath,
    SkType_FromPathMode,
    SkType_Full,
    SkType_Gradient,
    SkType_Group,
    SkType_HitClear,
    SkType_HitTest,
    SkType_Image,
    SkType_Include,
    SkType_Input,
    SkType_Int,
    SkType_Join,
    SkType_Line, // simple line primitive
    SkType_LineTo, // used as part of path construction
    SkType_LinearGradient,
    SkType_MaskFilter,
    SkType_MaskFilterBlurStyle,
    SkType_MaskFilterLight,
    SkType_Matrix,
    SkType_MemberFunction,
    SkType_MemberProperty,
    SkType_Move,
    SkType_MoveTo,
    SkType_Movie,
    SkType_MSec,
    SkType_Oval,
    SkType_Paint,
    SkType_Path,
    SkType_PathDirection,
    SkType_PathEffect,
    SkType_Point,   // used inside other structures, no vtable
    SkType_DrawPoint, // used to draw points, has a vtable
    SkType_PolyToPoly,
    SkType_Polygon,
    SkType_Polyline,
    SkType_Post,
    SkType_QuadTo,
    SkType_RCubicTo,
    SkType_RLineTo,
    SkType_RMoveTo,
    SkType_RQuadTo,
    SkType_RadialGradient,
    SkType_Random,
    SkType_Rect,
    SkType_RectToRect,
    SkType_Remove,
    SkType_Replace,
    SkType_Rotate,
    SkType_RoundRect,
    SkType_Save,
    SkType_SaveLayer,
    SkType_Scale,
    SkType_Screenplay,
    SkType_Set,
    SkType_Shader,
    SkType_Skew,
    SkType_3D_Camera,
    SkType_3D_Patch,
    SkType_3D_Point,
    SkType_Snapshot,
    SkType_String,  // pointer to SkString
    SkType_Style,
    SkType_Text,
    SkType_TextBox,
    SkType_TextBoxAlign,
    SkType_TextBoxMode,
    SkType_TextOnPath,
    SkType_TextToPath,
    SkType_TileMode,
    SkType_Translate,
    SkType_TransparentShader,
    SkType_Typeface,
    SkType_Xfermode,
    kNumberOfTypes
};

struct TypeNames {
    const char* fName;
    SkDisplayTypes fType;
#if defined SK_DEBUG || defined SK_BUILD_CONDENSED
    bool fDrawPrefix;
    bool fDisplayPrefix;
#endif
};

#ifdef SK_DEBUG
typedef SkDisplayTypes SkFunctionParamType;
#else
typedef unsigned char SkFunctionParamType;
#endif

extern const TypeNames gTypeNames[];
extern const int kTypeNamesSize;

class SkDisplayType {
public:
    static SkDisplayTypes Find(SkAnimateMaker* , const SkMemberInfo* );
    static const SkMemberInfo* GetMember(SkAnimateMaker* , SkDisplayTypes , const char** );
    static const SkMemberInfo* GetMembers(SkAnimateMaker* , SkDisplayTypes , int* infoCountPtr);
    static SkDisplayTypes GetParent(SkAnimateMaker* , SkDisplayTypes );
    static bool IsDisplayable(SkAnimateMaker* , SkDisplayTypes );
    static bool IsEnum(SkAnimateMaker* , SkDisplayTypes );
    static bool IsStruct(SkAnimateMaker* , SkDisplayTypes );
    static SkDisplayTypes RegisterNewType();
    static SkDisplayTypes Resolve(const char[] , const SkMemberInfo** );
#ifdef SK_DEBUG
    static bool IsAnimate(SkDisplayTypes type ) { return type == SkType_Animate || 
        type == SkType_Set; }
    static const char* GetName(SkAnimateMaker* , SkDisplayTypes );
#endif
#ifdef SK_SUPPORT_UNITTEST
    static void UnitTest();
#endif
#if defined SK_DEBUG || defined SK_BUILD_CONDENSED
    static void BuildCondensedInfo(SkAnimateMaker* );
#endif
    static SkDisplayTypes GetType(SkAnimateMaker* , const char[] , size_t len);
    static SkDisplayable* CreateInstance(SkAnimateMaker* , SkDisplayTypes );
private:
    static SkDisplayTypes gNewTypes;
};

#endif // SkDisplayType_DEFINED
