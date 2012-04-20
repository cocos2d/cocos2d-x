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


#ifndef GrIndexBuffer_DEFINED
#define GrIndexBuffer_DEFINED

#include "GrGeometryBuffer.h"

class GrIndexBuffer : public GrGeometryBuffer {
public:
        /**
         * Retrieves the maximum number of quads that could be rendered
         * from the index buffer (using kTriangles_PrimitiveType).
         * @return the maximum number of quads using full size of index buffer.
         */
        int maxQuads() const { return size() / (sizeof(uint16_t) * 6); }
protected:
    GrIndexBuffer(GrGpu* gpu, size_t sizeInBytes, bool dynamic)
        : INHERITED(gpu, sizeInBytes, dynamic) {}
private:
    typedef GrGeometryBuffer INHERITED;
};

#endif
