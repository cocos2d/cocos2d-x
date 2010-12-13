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

#ifndef SkUnitMappers_DEFINED
#define SkUnitMappers_DEFINED

#include "SkUnitMapper.h"

/** This discretizes the range [0...1) into N discret values.
*/
class SkDiscreteMapper : public SkUnitMapper {
public:
    SkDiscreteMapper(int segments);
    // override from SkUnitMapper
    virtual uint16_t mapUnit16(uint16_t x);

protected:
    SkDiscreteMapper(SkFlattenableReadBuffer& );
    // overrides from SkFlattenable
    virtual void flatten(SkFlattenableWriteBuffer& );
    virtual Factory getFactory();
private:
    int     fSegments;
    SkFract fScale;    // computed from fSegments

    static SkFlattenable* Create(SkFlattenableReadBuffer& buffer);
    
    typedef SkUnitMapper INHERITED;
};

/** This returns cos(x), to simulate lighting a sphere, where 0 maps to the
    center of the sphere, and 1 maps to the edge.
*/
class SkCosineMapper : public SkUnitMapper {
public:
    SkCosineMapper() {}
    // override from SkUnitMapper
    virtual uint16_t mapUnit16(uint16_t x);

protected:
    SkCosineMapper(SkFlattenableReadBuffer&);
    // overrides from SkFlattenable
    virtual Factory getFactory();

private:
    static SkFlattenable* Create(SkFlattenableReadBuffer&);

    typedef SkUnitMapper INHERITED;
};

#endif

