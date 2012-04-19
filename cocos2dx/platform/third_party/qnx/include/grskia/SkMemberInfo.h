/* libs/graphics/animator/SkMemberInfo.h
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

#ifndef SkMemberInfo_DEFINED
#define SkMemberInfo_DEFINED

#if defined SK_BUILD_CONDENSED
    #define SK_USE_CONDENSED_INFO 0
#endif

#include "SkDisplayType.h"
#include "SkScript.h"
#include "SkString.h"
#include "SkIntArray.h"

class SkAnimateMaker;
class SkDisplayable;
class SkScriptEngine;

// temporary hacks until name change is more complete
#define SkFloat SkScalar
#define SkInt SkS32

struct SkMemberInfo {
    //!!! alternative:
    // if fCount == 0, record is member property
    // then fType can be type, so caller doesn't have to check
#if SK_USE_CONDENSED_INFO == 0
    const char* fName;  // may be NULL for anonymous functions
    size_t fOffset; // if negative, is index into member pointer table (for properties and functions)
    SkDisplayTypes fType;
    int fCount;         // for properties, actual type (count is always assumed to be 1)
#else
    unsigned char fName;
    signed char fOffset;
    unsigned char fType;
    signed char fCount;
#endif
    SkDisplayTypes arrayType() const {
        SkASSERT(fType == SkType_Array);
        return (SkDisplayTypes) fCount;  // hack, but worth it?
    }
    int functionIndex() const {
        SkASSERT(fType == SkType_MemberFunction);
        return (signed) fOffset > 0 ? -1 + (int) fOffset : -1 - (int) fOffset;
    }
    bool getArrayValue(const SkDisplayable* displayable, int index, SkOperand* value) const;
    int getCount() const {
        return fType == SkType_MemberProperty || fType == SkType_Array ||
            fType == SkType_MemberFunction ? 1 : fCount;
    }
    const SkMemberInfo* getInherited() const;
    size_t getSize(const SkDisplayable* ) const;
    void getString(const SkDisplayable* , SkString** string) const;
    SkDisplayTypes getType() const {
        return fType == SkType_MemberProperty || fType == SkType_Array ||
            fType == SkType_MemberFunction ? (SkDisplayTypes) fCount : (SkDisplayTypes) fType;
    }
    void getValue(const SkDisplayable* , SkOperand values[], int count) const;
    bool isEnum() const;
    const char* mapEnums(const char* match, int* value) const;
    void* memberData(const SkDisplayable* displayable) const {
        SkASSERT(fType != SkType_MemberProperty &&  fType != SkType_MemberFunction);
        return (void*) ((const char*) displayable + fOffset);
    }
    int propertyIndex() const {
        SkASSERT(fType == SkType_MemberProperty);
        return (signed) fOffset > 0 ? -1 + (int) fOffset : -1 - (int) fOffset;
    }
    SkDisplayTypes propertyType() const {
        SkASSERT(fType == SkType_MemberProperty || fType == SkType_Array);
        return (SkDisplayTypes) fCount;  // hack, but worth it?
    }
    void setMemberData(SkDisplayable* displayable, const void* child, size_t size) const {
        SkASSERT(fType != SkType_MemberProperty &&  fType != SkType_MemberFunction);
        memcpy((char*) displayable + fOffset, child, size);
    }
    void setString(SkDisplayable* , SkString* ) const;
    void setValue(SkDisplayable* , const SkOperand values[], int count) const;
    bool setValue(SkAnimateMaker& , SkTDOperandArray* storage, 
        int storageOffset, int maxStorage, SkDisplayable* , 
        SkDisplayTypes outType, const char value[], size_t len) const;
    bool setValue(SkAnimateMaker& , SkTDOperandArray* storage, 
        int storageOffset, int maxStorage, SkDisplayable* , 
        SkDisplayTypes outType, SkString& str) const;
//  void setValue(SkDisplayable* , const char value[], const char name[]) const;
    bool writeValue(SkDisplayable* displayable, SkTDOperandArray* arrayStorage, 
        int storageOffset, int maxStorage, void* untypedStorage, SkDisplayTypes outType, 
        SkScriptValue& scriptValue) const;
#if SK_USE_CONDENSED_INFO == 0
    static const SkMemberInfo* Find(const SkMemberInfo [], int count, int* index);
    static const SkMemberInfo* Find(const SkMemberInfo [], int count, const char** name);
#else
    static const SkMemberInfo* Find(SkDisplayTypes type, int* index);
    static const SkMemberInfo* Find(SkDisplayTypes type, const char** name);
#endif
    static size_t GetSize(SkDisplayTypes type); // size of simple types only
//  static bool SetValue(void* value, const char* name, SkDisplayTypes , int count);
};

#define SK_MEMBER(_member, _type) \
    { #_member, SK_OFFSETOF(BASE_CLASS, _member), SkType_##_type, \
    sizeof(((BASE_CLASS*) 1)->_member) / sizeof(SkScalar) }

#define SK_MEMBER_ALIAS(_member, _alias, _type) \
    { #_member, SK_OFFSETOF(BASE_CLASS, _alias), SkType_##_type, \
    sizeof(((BASE_CLASS*) 1)->_alias) / sizeof(SkScalar) }

#define SK_MEMBER_ARRAY(_member, _type) \
    { #_member, SK_OFFSETOF(BASE_CLASS, _member), SkType_Array, \
    (int) SkType_##_type }

#define SK_MEMBER_INHERITED \
    { (const char*) INHERITED::fInfo, 0, SkType_BaseClassInfo, INHERITED::fInfoCount }

// #define SK_MEMBER_KEY_TYPE(_member, _type) 
//  {#_member, (size_t) -1, SkType_##_type, 0}

#define SK_FUNCTION(_member) \
    k_##_member##Function

#define SK_PROPERTY(_member) \
    k_##_member##Property

#define SK_MEMBER_DYNAMIC_FUNCTION(_member, _type) \
    {#_member, (size_t) (+1 + SK_FUNCTION(_member)), SkType_MemberFunction, \
    (int) SkType_##_type }

#define SK_MEMBER_DYNAMIC_PROPERTY(_member, _type) \
    {#_member, (size_t) (1 + SK_PROPERTY(_member)), SkType_MemberProperty, \
    (int) SkType_##_type }

#define SK_MEMBER_FUNCTION(_member, _type) \
    {#_member, (size_t) (-1 - SK_FUNCTION(_member)), SkType_MemberFunction, \
    (int) SkType_##_type }

#define SK_MEMBER_PROPERTY(_member, _type) \
    {#_member, (size_t) (-1 - SK_PROPERTY(_member)), SkType_MemberProperty, \
    (int) SkType_##_type }

#if SK_USE_CONDENSED_INFO == 0

#define DECLARE_PRIVATE_MEMBER_INFO(_type) \
public: \
    static const SkMemberInfo fInfo[]; \
    static const int fInfoCount; \
    virtual const SkMemberInfo* getMember(int index); \
    virtual const SkMemberInfo* getMember(const char name[]); \
    typedef Sk##_type BASE_CLASS

#define DECLARE_MEMBER_INFO(_type) \
public: \
    static const SkMemberInfo fInfo[]; \
    static const int fInfoCount; \
    virtual const SkMemberInfo* getMember(int index); \
    virtual const SkMemberInfo* getMember(const char name[]); \
    virtual SkDisplayTypes getType() const { return SkType_##_type; } \
    typedef Sk##_type BASE_CLASS

#define DECLARE_DRAW_MEMBER_INFO(_type) \
public: \
    static const SkMemberInfo fInfo[]; \
    static const int fInfoCount; \
    virtual const SkMemberInfo* getMember(int index); \
    virtual const SkMemberInfo* getMember(const char name[]); \
    virtual SkDisplayTypes getType() const { return SkType_##_type; } \
    typedef SkDraw##_type BASE_CLASS

#define DECLARE_DISPLAY_MEMBER_INFO(_type) \
public: \
    static const SkMemberInfo fInfo[]; \
    static const int fInfoCount; \
    virtual const SkMemberInfo* getMember(int index); \
    virtual const SkMemberInfo* getMember(const char name[]); \
    virtual SkDisplayTypes getType() const { return SkType_##_type; } \
    typedef SkDisplay##_type BASE_CLASS

#define DECLARE_EMPTY_MEMBER_INFO(_type) \
public: \
    virtual SkDisplayTypes getType() const { return SkType_##_type; }
    
#define DECLARE_EXTRAS_MEMBER_INFO(_type) \
public: \
    static const SkMemberInfo fInfo[]; \
    static const int fInfoCount; \
    virtual const SkMemberInfo* getMember(int index); \
    virtual const SkMemberInfo* getMember(const char name[]); \
    SkDisplayTypes fType; \
    virtual SkDisplayTypes getType() const { return fType; } \
    typedef _type BASE_CLASS

#define DECLARE_NO_VIRTUALS_MEMBER_INFO(_type) \
public: \
    static const SkMemberInfo fInfo[]; \
    static const int fInfoCount; \
    typedef Sk##_type BASE_CLASS

#define DEFINE_GET_MEMBER(_class) \
    const SkMemberInfo* _class::getMember(int index) { \
        const SkMemberInfo* result = SkMemberInfo::Find(fInfo, SK_ARRAY_COUNT(fInfo), &index); \
        return result; \
    } \
    const SkMemberInfo* _class::getMember(const char name[]) { \
        const SkMemberInfo* result = SkMemberInfo::Find(fInfo, SK_ARRAY_COUNT(fInfo), &name); \
        return result; \
    } \
    const int _class::fInfoCount = SK_ARRAY_COUNT(fInfo)

#define DEFINE_NO_VIRTUALS_GET_MEMBER(_class) \
    const int _class::fInfoCount = SK_ARRAY_COUNT(fInfo)

#else

#define DECLARE_PRIVATE_MEMBER_INFO(_type) \
public: \
    typedef Sk##_type BASE_CLASS

#define DECLARE_MEMBER_INFO(_type) \
public: \
    virtual const SkMemberInfo* getMember(int index) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &index); } \
    virtual const SkMemberInfo* getMember(const char name[]) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &name); } \
    virtual SkDisplayTypes getType() const { return SkType_##_type; } \
    typedef Sk##_type BASE_CLASS

#define DECLARE_DRAW_MEMBER_INFO(_type) \
public: \
    virtual const SkMemberInfo* getMember(int index) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &index); } \
    virtual const SkMemberInfo* getMember(const char name[]) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &name); } \
    virtual SkDisplayTypes getType() const { return SkType_##_type; } \
    typedef SkDraw##_type BASE_CLASS

#define DECLARE_DISPLAY_MEMBER_INFO(_type) \
public: \
    virtual const SkMemberInfo* getMember(int index) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &index); } \
    virtual const SkMemberInfo* getMember(const char name[]) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &name); } \
    virtual SkDisplayTypes getType() const { return SkType_##_type; } \
    typedef SkDisplay##_type BASE_CLASS

#define DECLARE_EXTRAS_MEMBER_INFO(_type) \
public: \
    virtual const SkMemberInfo* getMember(int index) { \
        return SkDisplayType::GetMember(NULL, SkType_##_type, &index); } \
    virtual const SkMemberInfo* getMember(const char name[]) { \
        return SkDisplayType::GetMember(NULL, fType, &name); } \
    SkDisplayTypes fType; \
    virtual SkDisplayTypes getType() const { return fType; } \
    typedef _type BASE_CLASS

#define DECLARE_NO_VIRTUALS_MEMBER_INFO(_type) \
public: \
    typedef Sk##_type BASE_CLASS

#define DEFINE_GET_MEMBER(_class)
#define DEFINE_NO_VIRTUALS_GET_MEMBER(_class)

#endif

#endif // SkMemberInfo_DEFINED

