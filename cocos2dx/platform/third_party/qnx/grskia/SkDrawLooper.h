/*
 * Copyright (C) 2011 The Android Open Source Project
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

#ifndef SkDrawLooper_DEFINED
#define SkDrawLooper_DEFINED

#include "SkFlattenable.h"

class SkCanvas;
class SkPaint;

/** \class SkDrawLooper
    Subclasses of SkDrawLooper can be attached to a SkPaint. Where they are,
    and something is drawn to a canvas with that paint, the looper subclass will
    be called, allowing it to modify the canvas and/or paint for that draw call.
    More than that, via the next() method, the looper can modify the draw to be
    invoked multiple times (hence the name loop-er), allow it to perform effects
    like shadows or frame/fills, that require more than one pass.
*/
class SK_API SkDrawLooper : public SkFlattenable {
public:
    /**
     *  Called right before something is being drawn. This will be followed by
     *  calls to next() until next() returns false.
     */
    virtual void init(SkCanvas*) = 0;

    /**
     *  Called in a loop (after init()). Each time true is returned, the object
     *  is drawn (possibly with a modified canvas and/or paint). When false is
     *  finally returned, drawing for the object stops.
     *
     *  On each call, the paint will be in its original state, but the canvas
     *  will be as it was following the previous call to next() or init().
     *
     *  The implementation must ensure that, when next() finally returns false,
     *  that the canvas has been restored to the state it was initially, before
     *  init() was first called.
     */
    virtual bool next(SkCanvas*, SkPaint* paint) = 0;
    
protected:
    SkDrawLooper() {}
    SkDrawLooper(SkFlattenableReadBuffer& buffer) : INHERITED(buffer) {}

private:
    typedef SkFlattenable INHERITED;
};

#endif
