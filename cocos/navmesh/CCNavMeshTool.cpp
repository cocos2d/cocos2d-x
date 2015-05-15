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
#include "navmesh/CCNavMeshTool.h"
#if CC_USE_NAVMESH

#include "recast/Detour/DetourCommon.h"
#include "recast/fastlz/fastlz.h"

NS_CC_BEGIN

LinearAllocator::LinearAllocator(const int cap)
: buffer(0)
, capacity(0)
, top(0)
, high(0)
{
    resize(cap);
}

LinearAllocator::~LinearAllocator()
{
    dtFree(buffer);
}

void LinearAllocator::free(void* /*ptr*/)
{

}

void* LinearAllocator::alloc(const int size)
{
    if (!buffer)
        return 0;
    if (top + size > capacity)
        return 0;
    unsigned char* mem = &buffer[top];
    top += size;
    return mem;
}

void LinearAllocator::reset()
{
    high = dtMax(high, top);
    top = 0;
}

void LinearAllocator::resize(const int cap)
{
    if (buffer) dtFree(buffer);
    buffer = (unsigned char*)dtAlloc(cap, DT_ALLOC_PERM);
    capacity = cap;
}

int FastLZCompressor::maxCompressedSize(const int bufferSize)
{
    return (int)(bufferSize* 1.05f);
}

dtStatus cocos2d::FastLZCompressor::decompress(const unsigned char* compressed, const int compressedSize
                                             , unsigned char* buffer, const int maxBufferSize, int* bufferSize)
{
    *bufferSize = fastlz_decompress(compressed, compressedSize, buffer, maxBufferSize);
    return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
}

dtStatus cocos2d::FastLZCompressor::compress(const unsigned char* buffer, const int bufferSize
    , unsigned char* compressed, const int /*maxCompressedSize*/, int* compressedSize)
{
    *compressedSize = fastlz_compress((const void *const)buffer, bufferSize, compressed);
    return DT_SUCCESS;
}

MeshProcess::MeshProcess()
//	: m_geom(0)
{
}

MeshProcess::~MeshProcess()
{

}

void MeshProcess::process(struct dtNavMeshCreateParams* params
    , unsigned char* polyAreas, unsigned short* polyFlags)
{
    //// Update poly flags from areas.
    //for (int i = 0; i < params->polyCount; ++i)
    //{
    //	if (polyAreas[i] == DT_TILECACHE_WALKABLE_AREA)
    //		polyAreas[i] = SAMPLE_POLYAREA_GROUND;

    //	if (polyAreas[i] == SAMPLE_POLYAREA_GROUND ||
    //		polyAreas[i] == SAMPLE_POLYAREA_GRASS ||
    //		polyAreas[i] == SAMPLE_POLYAREA_ROAD)
    //	{
    //		polyFlags[i] = SAMPLE_POLYFLAGS_WALK;
    //	}
    //	else if (polyAreas[i] == SAMPLE_POLYAREA_WATER)
    //	{
    //		polyFlags[i] = SAMPLE_POLYFLAGS_SWIM;
    //	}
    //	else if (polyAreas[i] == SAMPLE_POLYAREA_DOOR)
    //	{
    //		polyFlags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
    //	}
    //}

    //// Pass in off-mesh connections.
    //if (m_geom)
    //{
    //	params->offMeshConVerts = m_geom->getOffMeshConnectionVerts();
    //	params->offMeshConRad = m_geom->getOffMeshConnectionRads();
    //	params->offMeshConDir = m_geom->getOffMeshConnectionDirs();
    //	params->offMeshConAreas = m_geom->getOffMeshConnectionAreas();
    //	params->offMeshConFlags = m_geom->getOffMeshConnectionFlags();
    //	params->offMeshConUserID = m_geom->getOffMeshConnectionId();
    //	params->offMeshConCount = m_geom->getOffMeshConnectionCount();
    //}
}

NS_CC_END

#endif //CC_USE_NAVMESH
