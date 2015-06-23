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
#include "navmesh/CCNavMeshUtils.h"
#if CC_USE_NAVMESH

#include "recast/Detour/DetourCommon.h"
#include "recast/Detour/DetourNavMeshBuilder.h"
#include "recast/fastlz/fastlz.h"

NS_CC_BEGIN

LinearAllocator::LinearAllocator(const int cap)
: buffer(nullptr)
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

MeshProcess::MeshProcess(const GeomData *geom)
    : data(geom)
{
}

MeshProcess::~MeshProcess()
{

}

void MeshProcess::process(struct dtNavMeshCreateParams* params
    , unsigned char* polyAreas, unsigned short* polyFlags)
{
    // Update poly flags from areas.
    for (int i = 0; i < params->polyCount; ++i)
    {
        if (polyAreas[i] == DT_TILECACHE_WALKABLE_AREA)
            polyAreas[i] = 0;

        if (polyAreas[i] == 0)
            polyFlags[i] = 1;

        //if (polyAreas[i] == SAMPLE_POLYAREA_GROUND ||
        //	polyAreas[i] == SAMPLE_POLYAREA_GRASS ||
        //	polyAreas[i] == SAMPLE_POLYAREA_ROAD)
        //{
        //	polyFlags[i] = SAMPLE_POLYFLAGS_WALK;
        //}
        //else if (polyAreas[i] == SAMPLE_POLYAREA_WATER)
        //{
        //	polyFlags[i] = SAMPLE_POLYFLAGS_SWIM;
        //}
        //else if (polyAreas[i] == SAMPLE_POLYAREA_DOOR)
        //{
        //	polyFlags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
        //}
    }

    // Pass in off-mesh connections.
    params->offMeshConVerts = data->offMeshConVerts;
    params->offMeshConRad = data->offMeshConRads;
    params->offMeshConDir = data->offMeshConDirs;
    params->offMeshConAreas = data->offMeshConAreas;
    params->offMeshConFlags = data->offMeshConFlags;
    params->offMeshConUserID = data->offMeshConId;
    params->offMeshConCount = data->offMeshConCount;
}

bool getSteerTarget(dtNavMeshQuery* navQuery, const float* startPos, const float* endPos, const float minTargetDist, const dtPolyRef* path, const int pathSize, float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef, float* outPoints /*= 0*/, int* outPointCount /*= 0*/)
{
    // Find steer target.
    static const int MAX_STEER_POINTS = 3;
    float steerPath[MAX_STEER_POINTS * 3];
    unsigned char steerPathFlags[MAX_STEER_POINTS];
    dtPolyRef steerPathPolys[MAX_STEER_POINTS];
    int nsteerPath = 0;
    navQuery->findStraightPath(startPos, endPos, path, pathSize,
        steerPath, steerPathFlags, steerPathPolys, &nsteerPath, MAX_STEER_POINTS);
    if (!nsteerPath)
        return false;

    if (outPoints && outPointCount)
    {
        *outPointCount = nsteerPath;
        for (int i = 0; i < nsteerPath; ++i)
            dtVcopy(&outPoints[i * 3], &steerPath[i * 3]);
    }


    // Find vertex far enough to steer to.
    int ns = 0;
    while (ns < nsteerPath)
    {
        // Stop at Off-Mesh link or when point is further than slop away.
        if ((steerPathFlags[ns] & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ||
            !inRange(&steerPath[ns * 3], startPos, minTargetDist, 1000.0f))
            break;
        ns++;
    }
    // Failed to find good point to steer to.
    if (ns >= nsteerPath)
        return false;

    dtVcopy(steerPos, &steerPath[ns * 3]);
    steerPos[1] = startPos[1];
    steerPosFlag = steerPathFlags[ns];
    steerPosRef = steerPathPolys[ns];

    return true;
}

int fixupShortcuts(dtPolyRef* path, int npath, dtNavMeshQuery* navQuery)
{
    if (npath < 3)
        return npath;

    // Get connected polygons
    static const int maxNeis = 16;
    dtPolyRef neis[maxNeis];
    int nneis = 0;

    const dtMeshTile* tile = 0;
    const dtPoly* poly = 0;
    if (dtStatusFailed(navQuery->getAttachedNavMesh()->getTileAndPolyByRef(path[0], &tile, &poly)))
        return npath;

    for (unsigned int k = poly->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
    {
        const dtLink* link = &tile->links[k];
        if (link->ref != 0)
        {
            if (nneis < maxNeis)
                neis[nneis++] = link->ref;
        }
    }

    // If any of the neighbour polygons is within the next few polygons
    // in the path, short cut to that polygon directly.
    static const int maxLookAhead = 6;
    int cut = 0;
    for (int i = dtMin(maxLookAhead, npath) - 1; i > 1 && cut == 0; i--) {
        for (int j = 0; j < nneis; j++)
        {
            if (path[i] == neis[j]) {
                cut = i;
                break;
            }
        }
    }
    if (cut > 1)
    {
        int offset = cut - 1;
        npath -= offset;
        for (int i = 1; i < npath; i++)
            path[i] = path[i + offset];
    }

    return npath;
}

int fixupCorridor(dtPolyRef* path, const int npath, const int maxPath, const dtPolyRef* visited, const int nvisited)
{
    int furthestPath = -1;
    int furthestVisited = -1;

    // Find furthest common polygon.
    for (int i = npath - 1; i >= 0; --i)
    {
        bool found = false;
        for (int j = nvisited - 1; j >= 0; --j)
        {
            if (path[i] == visited[j])
            {
                furthestPath = i;
                furthestVisited = j;
                found = true;
            }
        }
        if (found)
            break;
    }

    // If no intersection found just return current path. 
    if (furthestPath == -1 || furthestVisited == -1)
        return npath;

    // Concatenate paths.	

    // Adjust beginning of the buffer to include the visited.
    const int req = nvisited - furthestVisited;
    const int orig = dtMin(furthestPath + 1, npath);
    int size = dtMax(0, npath - orig);
    if (req + size > maxPath)
        size = maxPath - req;
    if (size)
        memmove(path + req, path + orig, size*sizeof(dtPolyRef));

    // Store visited
    for (int i = 0; i < req; ++i)
        path[i] = visited[(nvisited - 1) - i];

    return req + size;
}

bool inRange(const float* v1, const float* v2, const float r, const float h)
{
    const float dx = v2[0] - v1[0];
    const float dy = v2[1] - v1[1];
    const float dz = v2[2] - v1[2];
    return (dx*dx + dz*dz) < r*r && fabsf(dy) < h;
}

NS_CC_END

#endif //CC_USE_NAVMESH
