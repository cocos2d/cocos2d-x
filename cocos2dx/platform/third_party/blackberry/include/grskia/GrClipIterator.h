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


#ifndef GrClipIterator_DEFINED
#define GrClipIterator_DEFINED

#include "GrPath.h"
#include "GrRect.h"

/**
 * A clip is a list of paths and/or rects with set operations to combine them.
 */
class GrClipIterator {
public:
    virtual ~GrClipIterator() {}

    /**
     *  Returns true if there are no more rects to process
     */
    virtual bool isDone() const = 0;

    /**
     *  Rewind the iterator to replay the set of clip elements again
     */
    virtual void rewind() = 0;

    /**
     * Get the type of the current clip element
     */
    virtual GrClipType getType() const = 0;

    /**
     * Return the current path. It is an error to call this when isDone() is
     * true or when getType() is kRect_Type.
     */
    virtual const GrPath* getPath() = 0;

    /**
     * Return the fill rule for the path. It is an error to call this when
     * isDone() is true or when getType is kRect_Type.
     */
    virtual GrPathFill getPathFill() const = 0;

    /**
    * Return the current rect. It is an error to call this when isDone is true
    * or when getType() is kPath_Type.
    */
    virtual void getRect(GrRect* rect) const = 0;

    /**
     * Gets the operation used to apply the current item to previously iterated
     * items. Iterators should not produce a Replace op.
     */
    virtual GrSetOp getOp() const = 0;

    /**
     *  Call to move to the next element in the list, previous path iter can be
     *  made invalid.
     */
    virtual void next() = 0;
};

/**
 *  Call to rewind iter, first checking to see if iter is NULL
 */
static inline void GrSafeRewind(GrClipIterator* iter) {
    if (iter) {
        iter->rewind();
    }
}

#endif

