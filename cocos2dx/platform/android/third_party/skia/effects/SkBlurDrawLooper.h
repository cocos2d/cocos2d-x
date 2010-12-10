/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkBlurDrawLooper_DEFINED
#define SkBlurDrawLooper_DEFINED

#include "SkDrawLooper.h"
#include "SkColor.h"

class SkMaskFilter;

/** \class SkBlurDrawLooper
    This class draws a shadow of the object (possibly offset), and then draws
    the original object in its original position.
    should there be an option to just draw the shadow/blur layer? webkit?
*/
class SkBlurDrawLooper : public SkDrawLooper {
public:
    SkBlurDrawLooper(SkScalar radius, SkScalar dx, SkScalar dy, SkColor color);
    virtual ~SkBlurDrawLooper();

    // overrides from SkDrawLooper
    virtual void init(SkCanvas*, SkPaint*);
    virtual bool next();
    virtual void restore();

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkBlurDrawLooper, (buffer));
    }

protected:
    SkBlurDrawLooper(SkFlattenableReadBuffer&);
    // overrides from SkFlattenable
    virtual void flatten(SkFlattenableWriteBuffer& );
    virtual Factory getFactory() { return CreateProc; }

private:
    SkCanvas*       fCanvas;
    SkPaint*        fPaint;
    SkMaskFilter*   fBlur;
    SkScalar        fDx, fDy;
    SkColor         fBlurColor;
    SkColor         fSavedColor;    // remember the original
    int             fSaveCount;

    enum State {
        kBeforeEdge,
        kAfterEdge,
        kDone
    };
    State   fState;
    
    typedef SkDrawLooper INHERITED;
};

#endif
