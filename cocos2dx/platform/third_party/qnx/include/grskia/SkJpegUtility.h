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

#ifndef SkJpegUtility_DEFINED
#define SkJpegUtility_DEFINED

#include "SkImageDecoder.h"
#include "SkStream.h"

extern "C" {
    #include "jpeglib.h"
    #include "jerror.h"
}

#include <setjmp.h>

/* Our error-handling struct.
 *
*/
struct skjpeg_error_mgr : jpeg_error_mgr {
    jmp_buf fJmpBuf;
};


void skjpeg_error_exit(j_common_ptr cinfo);

///////////////////////////////////////////////////////////////////////////
/* Our source struct for directing jpeg to our stream object.
*/
struct skjpeg_source_mgr : jpeg_source_mgr {
    skjpeg_source_mgr(SkStream* stream, SkImageDecoder* decoder, bool ownStream);
    ~skjpeg_source_mgr();

    SkStream*   fStream;
    void*       fMemoryBase;
    size_t      fMemoryBaseSize;
    bool        fUnrefStream;
    SkImageDecoder* fDecoder;
    enum {
        kBufferSize = 1024
    };
    char    fBuffer[kBufferSize];
};

/////////////////////////////////////////////////////////////////////////////
/* Our destination struct for directing decompressed pixels to our stream
 * object.
 */
struct skjpeg_destination_mgr : jpeg_destination_mgr {
    skjpeg_destination_mgr(SkWStream* stream);

    SkWStream*  fStream;

    enum {
        kBufferSize = 1024
    };
    uint8_t fBuffer[kBufferSize];
};

#endif
