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

#ifndef SkPDFFormXObject_DEFINED
#define SkPDFFormXObject_DEFINED

#include "SkPDFStream.h"
#include "SkPDFTypes.h"
#include "SkRefCnt.h"
#include "SkString.h"

class SkMatrix;
class SkPDFDevice;
class SkPDFCatalog;

/** \class SkPDFFormXObject

    A form XObject; a self contained description of graphics objects.  A form
    XObject is basically a page object with slightly different syntax, that
    can be drawn onto a page.
*/

// The caller could keep track of the form XObjects it creates and
// canonicalize them, but the Skia API doesn't provide enough context to
// automatically do it (trivially).
class SkPDFFormXObject : public SkPDFObject {
public:
    /** Create a PDF form XObject. Entries for the dictionary entries are
     *  automatically added.
     *  @param device      The set of graphical elements on this form.
     */
    explicit SkPDFFormXObject(SkPDFDevice* device);
    virtual ~SkPDFFormXObject();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);
    virtual void getResources(SkTDArray<SkPDFObject*>* resourceList);

    /** Add the value to the stream dictionary with the given key.  Refs value.
     *  @param key   The key for this dictionary entry.
     *  @param value The value for this dictionary entry.
     *  @return The value argument is returned.
     */
    SkPDFObject* insert(SkPDFName* key, SkPDFObject* value);

    /** Add the value to the stream dictionary with the given key.  Refs value.
     *  @param key   The text of the key for this dictionary entry.
     *  @param value The value for this dictionary entry.
     *  @return The value argument is returned.
     */
    SkPDFObject* insert(const char key[], SkPDFObject* value);

private:
    SkRefPtr<SkPDFStream> fStream;
    SkTDArray<SkPDFObject*> fResources;
};

#endif
