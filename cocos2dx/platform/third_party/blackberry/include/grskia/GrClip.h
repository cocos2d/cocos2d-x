/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrClip_DEFINED
#define GrClip_DEFINED

#include "GrClipIterator.h"
#include "GrRect.h"
#include "GrPath.h"
#include "GrTArray.h"
#include "GrTemplates.h"


class GrClip {
public:
    GrClip();
    GrClip(const GrClip& src);
    /**
     *  If specified, the conservativeBounds parameter already takes (tx,ty)
     *  into account.
     */
    GrClip(GrClipIterator* iter, GrScalar tx, GrScalar ty,
           const GrRect* conservativeBounds = NULL);
    GrClip(const GrIRect& rect);
    GrClip(const GrRect& rect);

    ~GrClip();

    GrClip& operator=(const GrClip& src);

    bool hasConservativeBounds() const { return fConservativeBoundsValid; }

    const GrRect& getConservativeBounds() const { return fConservativeBounds; }

    int getElementCount() const { return fList.count(); }

    GrClipType getElementType(int i) const { return fList[i].fType; }

    const GrPath& getPath(int i) const {
        GrAssert(kPath_ClipType == fList[i].fType);
        return fList[i].fPath;
    }

    GrPathFill getPathFill(int i) const {
        GrAssert(kPath_ClipType == fList[i].fType);
        return fList[i].fPathFill;
    }

    const GrRect& getRect(int i) const {
        GrAssert(kRect_ClipType == fList[i].fType);
        return fList[i].fRect;
    }

    GrSetOp getOp(int i) const { return fList[i].fOp; }

    bool isRect() const {
        if (1 == fList.count() && kRect_ClipType == fList[0].fType) {
            // if we determined that the clip is a single rect
            // we ought to have also used that rect as the bounds.
            GrAssert(fConservativeBoundsValid);
            GrAssert(fConservativeBounds == fList[0].fRect);
            return true;
        } else {
            return false;
        }
    }

    bool isEmpty() const { return 0 == fList.count(); }

    /**
     *  Resets this clip to be empty
     */
    void setEmpty();

    /**
     *  If specified, the bounds parameter already takes (tx,ty) into account.
     */
    void setFromIterator(GrClipIterator* iter, GrScalar tx, GrScalar ty,
                         const GrRect* conservativeBounds = NULL);
    void setFromRect(const GrRect& rect);
    void setFromIRect(const GrIRect& rect);

    friend bool operator==(const GrClip& a, const GrClip& b) {
        if (a.fList.count() != b.fList.count()) {
            return false;
        }
        int count = a.fList.count();
        for (int i = 0; i < count; ++i) {
            if (a.fList[i] != b.fList[i]) {
                return false;
            }
        }
        return true;
    }
    friend bool operator!=(const GrClip& a, const GrClip& b) {
        return !(a == b);
    }

private:
    struct Element {
        GrClipType  fType;
        GrRect      fRect;
        GrPath      fPath;
        GrPathFill  fPathFill;
        GrSetOp     fOp;
        bool operator ==(const Element& e) const {
            if (e.fType != fType || e.fOp != fOp) {
                return false;
            }
            switch (fType) {
                case kRect_ClipType:
                    return fRect == e.fRect;
                    break;
                case kPath_ClipType:
                    return fPath == e.fPath;
                default:
                    GrCrash("Unknown clip element type.");
                    return false; // suppress warning
            }
        }
        bool operator !=(const Element& e) const { return !(*this == e); }
    };

    GrRect              fConservativeBounds;
    bool                fConservativeBoundsValid;

    enum {
        kPreAllocElements = 4,
    };
    GrAlignedSTStorage<kPreAllocElements, Element>  fListStorage;
    GrTArray<Element>   fList;
};
#endif

