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

#include "base/ccConfig.h"
#if CC_USE_NAVMESH

#include "platform/CCPlatformMacros.h"
#include "math/CCMath.h"

#include "recast/Detour/DetourCommon.h"
#include "recast/Detour/DetourNavMesh.h"
#include "recast/Detour/DetourNavMeshQuery.h"
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

struct GeomData
{
    static const int MAX_OFFMESH_CONNECTIONS = 256;
    float offMeshConVerts[MAX_OFFMESH_CONNECTIONS * 3 * 2];
    float offMeshConRads[MAX_OFFMESH_CONNECTIONS];
    unsigned char offMeshConDirs[MAX_OFFMESH_CONNECTIONS];
    unsigned char offMeshConAreas[MAX_OFFMESH_CONNECTIONS];
    unsigned short offMeshConFlags[MAX_OFFMESH_CONNECTIONS];
    unsigned int offMeshConId[MAX_OFFMESH_CONNECTIONS];
    int offMeshConCount;
};

struct MeshProcess : public dtTileCacheMeshProcess
{
    const GeomData *data;

    MeshProcess(const GeomData *geom);
    virtual ~MeshProcess();

    //void init(InputGeom* geom)
    //{
    //	m_geom = geom;
    //}

    virtual void process(struct dtNavMeshCreateParams* params,
        unsigned char* polyAreas, unsigned short* polyFlags) override;
};

bool inRange(const float* v1, const float* v2, const float r, const float h);

int fixupCorridor(dtPolyRef* path, const int npath, const int maxPath,
    const dtPolyRef* visited, const int nvisited);

// This function checks if the path has a small U-turn, that is,
// a polygon further in the path is adjacent to the first polygon
// in the path. If that happens, a shortcut is taken.
// This can happen if the target (T) location is at tile boundary,
// and we're (S) approaching it parallel to the tile edge.
// The choice at the vertex can be arbitrary, 
//  +---+---+
//  |:::|:::|
//  +-S-+-T-+
//  |:::|   | <-- the step can end up in here, resulting U-turn path.
//  +---+---+
int fixupShortcuts(dtPolyRef* path, int npath, dtNavMeshQuery* navQuery);

bool getSteerTarget(dtNavMeshQuery* navQuery, const float* startPos, const float* endPos,
    const float minTargetDist,
    const dtPolyRef* path, const int pathSize,
    float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef,
    float* outPoints = nullptr, int* outPointCount = nullptr);
/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_H__
