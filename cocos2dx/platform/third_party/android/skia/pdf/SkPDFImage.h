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

#ifndef SkPDFImage_DEFINED
#define SkPDFImage_DEFINED

#include "SkPDFStream.h"
#include "SkPDFTypes.h"
#include "SkRefCnt.h"

class SkBitmap;
class SkPaint;
class SkPDFCatalog;

/** \class SkPDFImage

    An image XObject.
*/

// We could play the same trick here as is done in SkPDFGraphicState, storing
// a copy of the Bitmap object (not the pixels), the pixel generation number,
// and settings used from the paint to canonicalize image objects.
class SkPDFImage : public SkPDFObject {
public:
    /** Create a PDF image XObject. Entries for the image properties are
     *  automatically added to the stream dictionary.
     *  @param bitmap  The image to use.
     *  @param paint   Used to calculate alpha, masks, etc.
     */
    SkPDFImage(const SkBitmap& bitmap, const SkPaint& paint);
    virtual ~SkPDFImage();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

    /** Add the value to the stream dictionary with the given key.
     *  @param key   The key for this dictionary entry.
     *  @param value The value for this dictionary entry.
     */
    void insert(SkPDFName* key, SkPDFObject* value);

    /** Add the value to the stream dictionary with the given key.
     *  @param key   The text of the key for this dictionary entry.
     *  @param value The value for this dictionary entry.
     */
    void insert(const char key[], SkPDFObject* value);

private:
    SkRefPtr<SkPDFStream> fStream;
};

#endif
