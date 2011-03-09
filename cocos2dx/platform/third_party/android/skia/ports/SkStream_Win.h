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

#ifndef SkStream_Win_DEFINED
#define SkStream_Win_DEFINED

#ifndef SK_BUILD_FOR_WIN
#error "only valid for windows and wince builds"
#endif

#ifndef SkStream_DEFINED
#include "SkStream.h"
#endif
#include "SkString.h"
#include "Wininet.h"

/** \cond ZERO */
class SkURLStream : public SkStream {
public:
    SkURLStream(const char url[] = NULL);
    virtual ~SkURLStream();

    /** Close the current URL, and open a new URL.
        If URL is null, just close the current URL.
    */
    void setURL(const char url[]);

    // overrides
    virtual bool rewind();
    virtual size_t read(void* buffer, size_t size);
    
private:
    SkString fURL;
    HINTERNET fConnection;
    HINTERNET fURLStream;
};

/** \endcond */
#endif // SkStream_Win_DEFINED

