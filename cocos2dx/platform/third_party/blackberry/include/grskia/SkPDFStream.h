/*
 * Copyright (C) 2010 Google Inc.
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

#ifndef SkPDFStream_DEFINED
#define SkPDFStream_DEFINED

#include "SkPDFTypes.h"
#include "SkRefCnt.h"
#include "SkStream.h"
#include "SkTemplates.h"

class SkPDFCatalog;

/** \class SkPDFStream

    A stream object in a PDF.  Note, all streams must be indirect objects (via
    SkObjRef).
*/
class SkPDFStream : public SkPDFDict {
public:
    /** Create a PDF stream. A Length entry is automatically added to the
     *  stream dictionary. The stream may be retained (stream->ref() may be
     *  called) so its contents must not be changed after calling this.
     *  @param stream The data part of the stream.
     */
    explicit SkPDFStream(SkStream* stream);
    virtual ~SkPDFStream();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

private:
    size_t fLength;
    // Only one of the two streams will be valid.
    SkRefPtr<SkStream> fPlainData;
    SkDynamicMemoryWStream fCompressedData;

    typedef SkPDFDict INHERITED;
};

#endif
