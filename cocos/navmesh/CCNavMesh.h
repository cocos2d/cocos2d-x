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

#ifndef __CCNAV_MESH_H__
#define __CCNAV_MESH_H__

#include "base/ccConfig.h"
#if CC_USE_NAVMESH

#include "base/CCRef.h"
#include "math/Vec3.h"
#include "recast/Detour/DetourNavMesh.h"
#include "recast/Detour/DetourNavMeshQuery.h"
#include "recast/DetourCrowd/DetourCrowd.h"
#include "recast/DetourTileCache/DetourTileCache.h"
#include <string>
#include <vector>

#include "navmesh/CCNavMeshAgent.h"
#include "navmesh/CCNavMeshDebugDraw.h"
#include "navmesh/CCNavMeshObstacle.h"
#include "navmesh/CCNavMeshTool.h"


NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */
class Renderer;
class CC_DLL NavMesh : public Ref
{
public:

    struct hitInfo
    {
        Vec3 position;
        Vec3 normal;
    };

    static NavMesh* create(const std::string &filePath);

    void update(float dt);
    void debugDraw(Renderer* renderer);
    void setDebugDrawEnable(bool enable);
    bool isDebugDrawEnabled() const;
    void addNavMeshAgent(NavMeshAgent *agent);
    void removeNavMeshAgent(NavMeshAgent *agent);
    void addNavMeshObstacle(NavMeshObstacle *obstacle);
    void removeNavMeshObstacle(NavMeshObstacle *obstacle);

    void findPath(const Vec3 &start, const Vec3 &end, std::vector<Vec3> &pathPoints);

CC_CONSTRUCTOR_ACCESS:
    NavMesh();
    virtual ~NavMesh();

protected:

    bool initWithFilePath(const std::string &filePath);
    bool read();

protected:

    dtNavMesh *_navMesh;
    dtNavMeshQuery *_navMeshQuery;
    dtCrowd *_crowed;
    dtTileCache *_tileCache;
    LinearAllocator *_allocator;
    FastLZCompressor *_compressor;
    MeshProcess *_meshProcess;

    std::vector<NavMeshAgent*> _agentList;
    std::vector<NavMeshObstacle*> _obstacleList;
    NavMeshDebugDraw _debugDraw;
    std::string _filePath;
    bool _isDebugDrawEnabled;
};

/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_H__
