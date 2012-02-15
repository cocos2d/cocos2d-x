/* libs/graphics/animator/SkDisplayXMLParser.h
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

#ifndef SkDisplayXMLParser_DEFINED
#define SkDisplayXMLParser_DEFINED

#include "SkIntArray.h"
#include "SkTDict.h"
#include "SkDisplayType.h"
#include "SkXMLParser.h"

class SkAnimateMaker;
class SkDisplayable;

class SkDisplayXMLParserError : public SkXMLParserError {
public:
    enum ErrorCode {
        kApplyScopesItself = kUnknownError + 1,
        kDisplayTreeTooDeep,
        kElementMissingParent,
        kElementTypeNotAllowedInParent,
        kErrorAddingDataToPost,
        kErrorAddingToMatrix,
        kErrorAddingToPaint,
        kErrorAddingToPath,
        kErrorInAttributeValue,
        kErrorInScript,
        kExpectedMovie,
        kFieldNotInTarget,
        kGradientOffsetsDontMatchColors,
        kGradientOffsetsMustBeNoMoreThanOne,
        kGradientOffsetsMustEndWithOne,
        kGradientOffsetsMustIncrease,
        kGradientOffsetsMustStartWithZero,
        kGradientPointsLengthMustBeFour,
        kInInclude,
        kInMovie,
        kIncludeNameUnknownOrMissing,
        kIndexOutOfRange,
        kMovieNameUnknownOrMissing,
        kNoParentAvailable,
        kParentElementCantContain,
        kSaveLayerNeedsBounds,
        kTargetIDNotFound,
        kUnexpectedType
    };
    virtual ~SkDisplayXMLParserError();
    virtual void getErrorString(SkString* str) const;
    void setCode(ErrorCode code) { INHERITED::setCode((INHERITED::ErrorCode) code); }
    void setInnerError(SkAnimateMaker* maker, const SkString& str);
    typedef SkXMLParserError INHERITED;
    friend class SkDisplayXMLParser;
};

class SkDisplayXMLParser : public SkXMLParser {
public:
    SkDisplayXMLParser(SkAnimateMaker& maker);
    virtual ~SkDisplayXMLParser();
protected:
    virtual bool onAddAttribute(const char name[], const char value[]);
    bool onAddAttributeLen(const char name[], const char value[], size_t len);
    virtual bool onEndElement(const char elem[]);
    virtual bool onStartElement(const char elem[]);
    bool onStartElementLen(const char elem[], size_t len);
private:
    struct Parent {
        SkDisplayable* fDisplayable;
        SkDisplayTypes fType;
    };
    SkTDArray<Parent> fParents;
    SkDisplayXMLParser& operator= (const SkDisplayXMLParser& );
    SkDisplayXMLParserError* getError() { return (SkDisplayXMLParserError*) fError; }
    const SkMemberInfo* searchContainer(const SkMemberInfo* ,
        int infoCount);
    SkAnimateMaker& fMaker;
    SkBool fInInclude;
    SkBool fInSkia;
    // local state between onStartElement and onAddAttribute
    SkDisplayable*  fCurrDisplayable;
    SkDisplayTypes  fCurrType;
    friend class SkXMLAnimatorWriter;
    typedef SkXMLParser INHERITED;
};

#endif // SkDisplayXMLParser_DEFINED


