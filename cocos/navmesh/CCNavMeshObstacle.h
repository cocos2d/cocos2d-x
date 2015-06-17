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

#ifndef __CCNAV_MESH_OBSTACLE_H__
#define __CCNAV_MESH_OBSTACLE_H__

#include "base/ccConfig.h"
#if CC_USE_NAVMESH

#include "2d/CCComponent.h"

#include "base/CCRef.h"
#include "math/Vec3.h"
#include "recast/Detour/DetourNavMesh.h"
#include "recast/DetourTileCache/DetourTileCache.h"

NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */

/** @brief NavMeshObstacle: The code wrapping of dtTileCacheObstacle, use component mode. */
class CC_DLL NavMeshObstacle : public Component
{
    friend class NavMesh;
public:

    enum NavMeshObstacleSyncFlag
    {
        NONE = 0,
        NODE_TO_OBSTACLE = 1,
        OBSTACLE_TO_NODE = 2,
        NODE_AND_NODE = NODE_TO_OBSTACLE | OBSTACLE_TO_NODE,
    };

    /**
    Create obstacle, shape is cylinder

    @param radius The radius of obstacle.
    @param height The height of obstacle.
    */
    static NavMeshObstacle* create(float radius, float height);
    static const std::string& getNavMeshObstacleComponentName();

    virtual void onEnter() override;
    virtual void onExit() override;

    /** Set radius of obstacle */
    void setRadius(float radius);

    /** Get radius of obstacle */
    float getRadius() const { return _radius; }

    /** Set height of obstacle */
    void setHeight(float height);

    /** Get height of obstacle */
    float getHeight() const { return _height; }

    /**
    * synchronization between node and obstacle is time consuming, you can skip some synchronization using this function
    */
    void setSyncFlag(const NavMeshObstacleSyncFlag &flag) { _syncFlag = flag; }
    NavMeshObstacleSyncFlag getSyncFlag() const { return _syncFlag; }

    /** synchronize parameter to obstacle. */
    void syncToObstacle();

    /** synchronize parameter to node. */
    void syncToNode();

CC_CONSTRUCTOR_ACCESS:
    NavMeshObstacle();
    virtual ~NavMeshObstacle();

    bool initWith(float radius, float height);

private:

    void addTo(dtTileCache *tileCache);
    void removeFrom(dtTileCache *tileCache);
    void preUpdate(float delta);
    void postUpdate(float delta);

private:

    float _radius;
    float _height;
    NavMeshObstacleSyncFlag _syncFlag;
    dtObstacleRef _obstacleID;
    dtTileCache *_tileCache;
};

/** @} */

NS_CC_END

#endif //CC_USE_NAVMESH

#endif // __CCNAV_MESH_OBSTACLE_H__
