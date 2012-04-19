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


#ifndef GrPathSink_DEFINED
#define GrPathSink_DEFINED

#include "GrScalar.h"

class GrPathSink {
public:
    virtual ~GrPathSink() {}

    virtual void moveTo(GrScalar x, GrScalar y) = 0;
    virtual void lineTo(GrScalar x, GrScalar y) = 0;
    virtual void quadTo(GrScalar x0, GrScalar y0, GrScalar x1, GrScalar y1) = 0;
    virtual void cubicTo(GrScalar x0, GrScalar y0, GrScalar x1, GrScalar y1,
                         GrScalar x2, GrScalar y2) = 0;
    virtual void close() = 0;
};

#endif

