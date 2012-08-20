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

#ifndef SkPDFCatalog_DEFINED
#define SkPDFCatalog_DEFINED

#include <sys/types.h>

#include "SkPDFTypes.h"
#include "SkRefCnt.h"
#include "SkTDArray.h"

/** \class SkPDFCatalog

    The PDF catalog manages object numbers and file offsets.  It is used
    to create the PDF cross reference table.
*/
class SK_API SkPDFCatalog {
public:
    /** Create a PDF catalog.
     */
    SkPDFCatalog();
    ~SkPDFCatalog();

    /** Add the passed object to the catalog.  Refs obj.
     *  @param obj         The object to add.
     *  @param onFirstPage Is the object on the first page.
     *  @return The obj argument is returned.
     */
    SkPDFObject* addObject(SkPDFObject* obj, bool onFirstPage);

    /** Inform the catalog of the object's position in the final stream.
     *  The object should already have been added to the catalog.  Returns
     *  the object's size.
     *  @param obj         The object to add.
     *  @param offset      The byte offset in the output stream of this object.
     */
    size_t setFileOffset(SkPDFObject* obj, size_t offset);

    /** Output the object number for the passed object.
     *  @param obj         The object of interest.
     *  @param stream      The writable output stream to send the output to.
     */
    void emitObjectNumber(SkWStream* stream, SkPDFObject* obj);

    /** Return the number of bytes that would be emitted for the passed
     *  object's object number.
     *  @param obj         The object of interest
     */
    size_t getObjectNumberSize(SkPDFObject* obj);

    /** Output the cross reference table for objects in the catalog.
     *  Returns the total number of objects.
     *  @param stream      The writable output stream to send the output to.
     *  @param firstPage   If true, include first page objects only, otherwise
     *                     include all objects not on the first page.
     */
    int32_t emitXrefTable(SkWStream* stream, bool firstPage);

private:
    struct Rec {
        Rec(SkPDFObject* object, bool onFirstPage)
            : fObject(object),
              fFileOffset(0),
              fObjNumAssigned(false),
              fOnFirstPage(onFirstPage) {
        }
        SkPDFObject* fObject;
        off_t fFileOffset;
        bool fObjNumAssigned;
        bool fOnFirstPage;
    };

    // TODO(vandebo) Make this a hash if it's a performance problem.
    SkTDArray<struct Rec> fCatalog;

    // Number of objects on the first page.
    uint32_t fFirstPageCount;
    // Next object number to assign (on page > 1).
    uint32_t fNextObjNum;
    // Next object number to assign on the first page.
    uint32_t fNextFirstPageObjNum;

    int findObjectIndex(SkPDFObject* obj) const;

    int assignObjNum(SkPDFObject* obj);
};

#endif
