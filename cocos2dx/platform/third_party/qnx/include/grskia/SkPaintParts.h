/* libs/graphics/animator/SkPaintParts.h
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

#ifndef SkPaintParts_DEFINED
#define SkPaintParts_DEFINED

#include "SkDisplayable.h"
#include "SkMemberInfo.h"
#include "SkPaint.h"
#include "SkShader.h"
#include "SkTypeface.h"
#include "SkXfermode.h"

class SkDrawPaint;
class SkDrawMatrix;

class SkPaintPart : public SkDisplayable {
public:
    SkPaintPart();
    virtual bool add() = 0;
    virtual SkDisplayable* getParent() const;
    virtual bool setParent(SkDisplayable* parent);
#ifdef SK_DEBUG
    virtual bool isPaintPart() const { return true; }
#endif
protected:
    SkDrawPaint* fPaint;
};

class SkDrawMaskFilter : public SkPaintPart {
    DECLARE_EMPTY_MEMBER_INFO(MaskFilter);
    virtual SkMaskFilter* getMaskFilter();
protected:
    virtual bool add();
};

class SkDrawPathEffect : public SkPaintPart {
    DECLARE_EMPTY_MEMBER_INFO(PathEffect);
    virtual SkPathEffect* getPathEffect();
protected:
    virtual bool add();
};

class SkDrawShader : public SkPaintPart {
    DECLARE_DRAW_MEMBER_INFO(Shader);
    SkDrawShader();
    virtual SkShader* getShader();
protected:
    virtual bool add();
    void addPostlude(SkShader* shader);
    SkDrawMatrix* matrix;
    int /*SkShader::TileMode*/ tileMode;
};

class SkDrawTypeface  : public SkPaintPart {
    DECLARE_DRAW_MEMBER_INFO(Typeface);
    SkDrawTypeface();
#ifdef SK_DUMP_ENABLED
    virtual void dump(SkAnimateMaker *);
#endif
    SkTypeface* getTypeface() {
        return SkTypeface::CreateFromName(fontName.c_str(), style); }
protected:
    virtual bool add();
    SkString fontName;
    SkTypeface::Style style;
};

#endif // SkPaintParts_DEFINED
