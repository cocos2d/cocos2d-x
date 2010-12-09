/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef SkPDFGraphicState_DEFINED
#define SkPDFGraphicState_DEFINED

#include "SkPaint.h"
#include "SkPDFTypes.h"
#include "SkTemplates.h"
#include "SkThread.h"

/** \class SkPDFGraphicState
    SkPaint objects roughly correspond to graphic state dictionaries that can
    be installed.  So that a given dictionary is only output to the pdf file
    once, we want to canonicalize them.  Static methods in this class manage
    a weakly referenced set of SkPDFGraphicState objects: when the last
    reference to a SkPDFGraphicState is removed, it removes itself from the
    static set of objects.

*/
class SkPDFGraphicState : public SkPDFDict {
public:
    virtual ~SkPDFGraphicState();

    // Override emitObject and getOutputSize so that we can populate
    // the dictionary on demand.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

    /** Get the graphic state for the passed SkPaint. The reference count of
     *  the object is incremented and it is the caller's responsibility to
     *  unreference it when done.  This is needed to accommodate the weak
     *  reference pattern used when the returned object is new and has no
     *  other references.
     *  @param paint  The SkPaint to emulate.
     */
    static SkPDFGraphicState* getGraphicStateForPaint(const SkPaint& paint);

private:
    const SkPaint fPaint;
    bool fPopulated;

    class GSCanonicalEntry {
    public:
        SkPDFGraphicState* fGraphicState;
        const SkPaint* fPaint;

        bool operator==(const GSCanonicalEntry& b) const;
        explicit GSCanonicalEntry(SkPDFGraphicState* gs)
            : fGraphicState(gs),
              fPaint(&gs->fPaint) {}
        explicit GSCanonicalEntry(const SkPaint* paint) : fPaint(paint) {}
    };

    // This should be made a hash table if performance is a problem.
    static SkTDArray<GSCanonicalEntry>& canonicalPaints();
    static SkMutex& canonicalPaintsMutex();

    explicit SkPDFGraphicState(const SkPaint& paint);

    void populateDict();

    static int find(const SkPaint& paint);
};

#endif
