/* libs/graphics/animator/SkDrawGradient.h
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

#ifndef SkDrawGradient_DEFINED
#define SkDrawGradient_DEFINED

#include "SkDrawColor.h"
#include "SkDrawShader.h"
#include "SkIntArray.h"

class SkUnitMapper;

class SkGradient : public SkDrawShader {
    DECLARE_PRIVATE_MEMBER_INFO(Gradient);
    SkGradient();
    virtual ~SkGradient();
    virtual bool add(SkAnimateMaker& , SkDisplayable* child);
#ifdef SK_DUMP_ENABLED
    virtual void dumpRest(SkAnimateMaker*);
#endif    
    virtual void onEndElement(SkAnimateMaker& );
protected:
    SkTDScalarArray offsets;
    SkString unitMapper;
    SkTDColorArray fColors;
    SkTDDrawColorArray fDrawColors;
    SkUnitMapper* fUnitMapper;
    int addPrelude();
private:
    typedef SkDrawShader INHERITED;
};

class SkLinearGradient : public SkGradient {
    DECLARE_MEMBER_INFO(LinearGradient);
    SkLinearGradient();
    virtual void onEndElement(SkAnimateMaker& );
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker*);
#endif
    virtual SkShader* getShader();
protected:
    SkTDScalarArray points;
private:
    typedef SkGradient INHERITED;
};

class SkRadialGradient : public SkGradient {
    DECLARE_MEMBER_INFO(RadialGradient);
    SkRadialGradient();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker*);
#endif    
    virtual SkShader* getShader();
protected:
    SkPoint center;
    SkScalar radius;
private:
    typedef SkGradient INHERITED;
};

#endif // SkDrawGradient_DEFINED

