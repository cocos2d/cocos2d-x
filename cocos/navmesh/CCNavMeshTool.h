/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCNAV_MESH_TOOL_H__
#define __CCNAV_MESH_TOOL_H__

#if CC_USE_NAVMESH

#include "base/ccConfig.h"
#include "platform/CCPlatformMacros.h"

#include "recast/DetourTileCache/DetourTileCache.h"
#include "recast/DetourTileCache/DetourTileCacheBuilder.h"

NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */

struct LinearAllocator : public dtTileCacheAlloc
{
    unsigned char* buffer;
    int capacity;
    int top;
    int high;

    LinearAllocator(const int cap);

    ~LinearAllocator();

    void resize(const int cap);

    virtual void reset();

    virtual void* alloc(const int size);

    virtual void free(void* /*ptr*/);
};

struct FastLZCompressor : public dtTileCacheCompressor
{
    virtual int maxCompressedSize(const int bufferSize);

    virtual dtStatus compress(const unsigned char* buffer, const int bufferSize,
        unsigned char* compressed, const int /*maxCompressedSize*/, int* compressedSize);

    virtual dtStatus decompress(const unsigned char* compressed, const int compressedSize,
        unsigned char* buffer, const int maxBufferSize, int* bufferSize);
};

struct MeshProcess : public dtTileCacheMeshProcess
{
    //InputGeom* m_geom;

    MeshProcess();

    //void init(InputGeom* geom)
    //{
    //	m_geom = geom;
    //}

    virtual void process(struct dtNavMeshCreateParams* params,
        unsigned char* polyAreas, unsigned short* polyFlags) override;
};

/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_H__
