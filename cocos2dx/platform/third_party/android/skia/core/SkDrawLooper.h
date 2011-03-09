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

#ifndef SkDrawLooper_DEFINED
#define SkDrawLooper_DEFINED

#include "SkFlattenable.h"

////////////////// EXPERIMENTAL //////////////////////////

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
class SkDrawLooper : public SkFlattenable {
public:
    /** Called right before something is being drawn to the specified canvas
        with the specified paint. Subclass that want to modify either parameter
        can do so now.
    */
    virtual void init(SkCanvas*, SkPaint*) {}
    /** Called in a loop (after init()). Each time true is returned, the object
        is drawn (possibly with a modified canvas and/or paint). When false is
        finally returned, drawing for the object stops.
    */
    virtual bool next() { return false; }
    /** Called after the looper has finally returned false from next(), allowing
        the looper to restore the canvas/paint to their original states.
        is this required, since the subclass knows when it is done???
        should we pass the canvas/paint here, and/or to the next call
        so that subclasses don't need to retain pointers to them during the 
        loop?
    */
    virtual void restore() {}
    
protected:
    SkDrawLooper() {}
    SkDrawLooper(SkFlattenableReadBuffer& buffer) : INHERITED(buffer) {}

private:
    typedef SkFlattenable INHERITED;
};

#endif
