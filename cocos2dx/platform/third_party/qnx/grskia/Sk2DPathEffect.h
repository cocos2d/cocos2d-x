/*
 * Copyright (C) 2006 The Android Open Source Project
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

#ifndef Sk2DPathEffect_DEFINED
#define Sk2DPathEffect_DEFINED

#include "SkPathEffect.h"
#include "SkMatrix.h"

//  This class is not exported to java.
class Sk2DPathEffect : public SkPathEffect {
public:
    Sk2DPathEffect(const SkMatrix& mat);

    // overrides
    //  This method is not exported to java.
    virtual bool filterPath(SkPath* dst, const SkPath& src, SkScalar* width);

    // overrides from SkFlattenable
    //  This method is not exported to java.
    virtual void flatten(SkFlattenableWriteBuffer&);
    
    //  This method is not exported to java.
    virtual Factory getFactory();

protected:
    /** New virtual, to be overridden by subclasses.
        This is called once from filterPath, and provides the
        uv parameter bounds for the path. Subsequent calls to
        next() will receive u and v values within these bounds,
        and then a call to end() will signal the end of processing.
    */
    virtual void begin(const SkIRect& uvBounds, SkPath* dst);
    virtual void next(const SkPoint& loc, int u, int v, SkPath* dst);
    virtual void end(SkPath* dst);

    /** Low-level virtual called per span of locations in the u-direction.
        The default implementation calls next() repeatedly with each
        location.
    */
    virtual void nextSpan(int u, int v, int ucount, SkPath* dst);

    const SkMatrix& getMatrix() const { return fMatrix; }

    // protected so that subclasses can call this during unflattening
    Sk2DPathEffect(SkFlattenableReadBuffer&);

private:
    SkMatrix    fMatrix, fInverse;
    // illegal
    Sk2DPathEffect(const Sk2DPathEffect&);
    Sk2DPathEffect& operator=(const Sk2DPathEffect&);

    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

    friend class Sk2DPathEffectBlitter;
    typedef SkPathEffect INHERITED;
};

#endif
