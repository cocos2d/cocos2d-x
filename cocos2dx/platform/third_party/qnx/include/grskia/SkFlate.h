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

#ifndef SkFlate_DEFINED
#define SkFlate_DEFINED

#include "SkTypes.h"

class SkData;
class SkWStream;
class SkStream;

/** \class SkFlate
    A class to provide access to the flate compression algorithm.
*/
class SkFlate {
public:
    /** Indicates if the flate algorithm is available.
     */
    static bool HaveFlate();

    /**
     *  Use the flate compression algorithm to compress the data in src,
     *  putting the result into dst.  Returns false if an error occurs.
     */
    static bool Deflate(SkStream* src, SkWStream* dst);
    
    /**
     *  Use the flate compression algorithm to compress the data in src,
     *  putting the result into dst.  Returns false if an error occurs.
     */
    static bool Deflate(const void* src, size_t len, SkWStream* dst);
    
    /**
     *  Use the flate compression algorithm to compress the data,
     *  putting the result into dst.  Returns false if an error occurs.
     */
    static bool Deflate(const SkData*, SkWStream* dst);
    
    /** Use the flate compression algorithm to decompress the data in src,
        putting the result into dst.  Returns false if an error occurs.
     */
    static bool Inflate(SkStream* src, SkWStream* dst);
};

#endif
