/* libs/graphics/animator/SkDrawColor.h
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

#ifndef SkDrawColor_DEFINED
#define SkDrawColor_DEFINED

#include "SkPaintParts.h"
#include "SkColor.h"

class SkDrawColor : public SkPaintPart {
    DECLARE_DRAW_MEMBER_INFO(Color);
    SkDrawColor();
    virtual bool add();
    virtual void dirty();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker* );
#endif
    SkColor getColor();
    virtual SkDisplayable* deepCopy(SkAnimateMaker* );
    virtual SkDisplayable* getParent() const;
    virtual bool getProperty(int index, SkScriptValue* value) const;
    virtual void onEndElement(SkAnimateMaker& );
    virtual bool setParent(SkDisplayable* parent);
    virtual bool setProperty(int index, SkScriptValue&);
protected:
    SkColor color;
    SkScalar fHue;
    SkScalar fSaturation;
    SkScalar fValue;
    SkBool fDirty;
private:
    friend class SkGradient;
    typedef SkPaintPart INHERITED;
};

#endif // SkDrawColor_DEFINED
