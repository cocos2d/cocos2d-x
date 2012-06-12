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


#ifndef GrTBSearch_DEFINED
#define GrTBSearch_DEFINED

template <typename ELEM, typename KEY>
int GrTBSearch(const ELEM array[], int count, KEY target) {
    GrAssert(count >= 0);
    if (0 == count) {
        // we should insert it at 0
        return ~0;
    }
    
    int high = count - 1;
    int low = 0;
    while (high > low) {
        int index = (low + high) >> 1;
        if (LT(array[index], target)) {
            low = index + 1;
        } else {
            high = index;
        }
    }
    
    // check if we found it
    if (EQ(array[high], target)) {
        return high;
    }
    
    // now return the ~ of where we should insert it
    if (LT(array[high], target)) {
        high += 1;
    }
    return ~high;
}

#endif

