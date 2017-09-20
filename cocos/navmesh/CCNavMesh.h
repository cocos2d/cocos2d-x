/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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
#include "navmesh/CCNavMeshUtils.h"


NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */
class Renderer;
/** @brief NavMesh: The NavMesh information container, include mesh, tileCache, and so on. */
class CC_DLL NavMesh : public Ref
{
public:

    /**
    Create navmesh

    @param navFilePath The NavMesh File path.
    @param geomFilePath The geometry File Path,include offmesh information,etc.
    */
    static NavMesh* create(const std::string &navFilePath, const std::string &geomFilePath);

    /** update navmesh. */
    void update(float dt);

    /** Internal method, the updater of debug drawing, need called each frame. */
    void debugDraw(Renderer* renderer);

    /** Enable debug draw or disable. */
    void setDebugDrawEnable(bool enable);

    /** Check enabled debug draw. */
    bool isDebugDrawEnabled() const;

    /** add a agent to navmesh. */
    void addNavMeshAgent(NavMeshAgent *agent);

    /** remove a agent from navmesh. */
    void removeNavMeshAgent(NavMeshAgent *agent);

    /** add a obstacle to navmesh. */
    void addNavMeshObstacle(NavMeshObstacle *obstacle);

    /** remove a obstacle from navmesh. */
    void removeNavMeshObstacle(NavMeshObstacle *obstacle);

    /**
    find a path on navmesh

    @param start The start search position in world coordinate system.
    @param end The end search position in world coordinate system.
    @param pathPoints the key points of path.
    */
    void findPath(const Vec3 &start, const Vec3 &end, std::vector<Vec3> &pathPoints);

CC_CONSTRUCTOR_ACCESS:
    NavMesh();
    virtual ~NavMesh();

protected:

    bool initWithFilePath(const std::string &navFilePath, const std::string &geomFilePath);
    bool read();
    bool loadNavMeshFile();
    bool loadGeomFile();
    void dtDraw();
    void drawAgents();
    void drawObstacles();
    void drawOffMeshConnections();

protected:

    dtNavMesh *_navMesh;
    dtNavMeshQuery *_navMeshQuery;
    dtCrowd *_crowed;
    dtTileCache *_tileCache;
    LinearAllocator *_allocator;
    FastLZCompressor *_compressor;
    MeshProcess *_meshProcess;
    GeomData *_geomData;

    std::vector<NavMeshAgent*> _agentList;
    std::vector<NavMeshObstacle*> _obstacleList;
    NavMeshDebugDraw _debugDraw;
    std::string _navFilePath;
    std::string _geomFilePath;
    bool _isDebugDrawEnabled;
};

/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_H__
