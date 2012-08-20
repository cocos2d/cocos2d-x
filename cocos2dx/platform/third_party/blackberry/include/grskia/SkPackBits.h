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

#ifndef SkPackBits_DEFINED
#define SkPackBits_DEFINED

#include "SkTypes.h"

class SkPackBits {
public:
    /** Given the number of 16bit values that will be passed to Pack16,
        returns the worst-case size needed for the dst[] buffer.
    */
    static size_t ComputeMaxSize16(int count);

    /** Given the number of 8bit values that will be passed to Pack8,
        returns the worst-case size needed for the dst[] buffer.
    */
    static size_t ComputeMaxSize8(int count);

    /** Write the src array into a packed format. The packing process may end
        up writing more bytes than it read, so dst[] must be large enough.
        @param src      Input array of 16bit values
        @param count    Number of entries in src[]
        @param dst      Buffer (allocated by caller) to write the packed data
                        into
        @return the number of bytes written to dst[]
    */
    static size_t Pack16(const uint16_t src[], int count, uint8_t dst[]);

    /** Write the src array into a packed format. The packing process may end
        up writing more bytes than it read, so dst[] must be large enough.
        @param src      Input array of 8bit values
        @param count    Number of entries in src[]
        @param dst      Buffer (allocated by caller) to write the packed data
                        into
        @return the number of bytes written to dst[]
    */
    static size_t Pack8(const uint8_t src[], int count, uint8_t dst[]);

    /** Unpack the data in src[], and expand it into dst[]. The src[] data was
        written by a previous call to Pack16.
        @param src  Input data to unpack, previously created by Pack16.
        @param srcSize  Number of bytes of src to unpack
        @param dst  Buffer (allocated by caller) to expand the src[] into.
        @return the number of dst elements (not bytes) written into dst.
    */
    static int Unpack16(const uint8_t src[], size_t srcSize, uint16_t dst[]);

    /** Unpack the data in src[], and expand it into dst[]. The src[] data was
        written by a previous call to Pack8.
        @param src      Input data to unpack, previously created by Pack8.
        @param srcSize  Number of bytes of src to unpack
        @param dst      Buffer (allocated by caller) to expand the src[] into.
        @return the number of bytes written into dst.
    */
    static int Unpack8(const uint8_t src[], size_t srcSize, uint8_t dst[]);

    /** Unpack the data from src[], skip the first dstSkip bytes, then write
        dstWrite bytes into dst[]. The src[] data was written by a previous
        call to Pack8. Return the number of bytes actually writtten into dst[]
        @param src      Input data to unpack, previously created by Pack8.
        @param dst      Buffer (allocated by caller) to expand the src[] into.
        @param dstSkip  Number of bytes of unpacked src to skip before writing
                        into dst
        @param dstWrite Number of bytes of unpacked src to write into dst (after
                        skipping dstSkip bytes)
    */
    static void Unpack8(uint8_t dst[], size_t dstSkip, size_t dstWrite,
                        const uint8_t src[]);
};

#endif
