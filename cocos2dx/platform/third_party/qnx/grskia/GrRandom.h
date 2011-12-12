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


#ifndef GrRandom_DEFINED
#define GrRandom_DEFINED

class GrRandom {
public:
    GrRandom() : fSeed(0) {}
    GrRandom(uint32_t seed) : fSeed(seed) {}

    uint32_t seed() const { return fSeed; }

    uint32_t nextU() {
        fSeed = fSeed * kMUL + kADD;
        return fSeed;
    }

    int32_t nextS() { return (int32_t)this->nextU(); }

    /**
     *  Returns value [0...1) as a float
     */
    float nextF() {
        // const is 1 / (2^32 - 1)
        return (float)(this->nextU() * 2.32830644e-10);
    }

    /**
     *  Returns value [min...max) as a float
     */
    float nextF(float min, float max) {
        return min + this->nextF() * (max - min);
    }

private:
    /*
     *  These constants taken from "Numerical Recipes in C", reprinted 1999
     */
    enum {
        kMUL = 1664525,
        kADD = 1013904223
    };
    uint32_t    fSeed;
};

#endif

