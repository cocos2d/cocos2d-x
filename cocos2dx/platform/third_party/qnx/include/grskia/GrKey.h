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


#ifndef GrKey_DEFINED
#define GrKey_DEFINED

#include "GrRefCnt.h"

class GrKey : public GrRefCnt {
public:
    typedef intptr_t Hash;

    explicit GrKey(Hash hash) : fHash(hash) {}

    intptr_t getHash() const { return fHash; }

    bool operator<(const GrKey& rh) const {
        return fHash < rh.fHash || (fHash == rh.fHash && this->lt(rh));
    }
    bool operator==(const GrKey& rh) const {
        return fHash == rh.fHash && this->eq(rh);
    }

protected:
    virtual bool lt(const GrKey& rh) const = 0;
    virtual bool eq(const GrKey& rh) const = 0;

private:
    const Hash fHash;
};

#endif

