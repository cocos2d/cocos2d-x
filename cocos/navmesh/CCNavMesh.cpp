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
#include "navmesh/CCNavMesh.h"
#if CC_USE_NAVMESH

#include "platform/CCFileUtils.h"
#include "renderer/CCRenderer.h"
#include "recast/Detour/DetourCommon.h"
#include "recast/DebugUtils/DetourDebugDraw.h"
#include <sstream>

NS_CC_BEGIN

#pragma pack(push,1)
struct TileCacheSetHeader
{
    int32_t magic;
    int32_t version;
    int32_t numTiles;
    dtNavMeshParams meshParams;
    dtTileCacheParams cacheParams;
};

struct TileCacheTileHeader
{
    dtCompressedTileRef tileRef;
    int32_t dataSize;
};
#pragma pack(pop)

static unsigned char* parseRow(unsigned char* buf, unsigned char* bufEnd, char* row, int len)
{
    bool start = true;
    bool done = false;
    int n = 0;
    while (!done && buf < bufEnd)
    {
        char c = *buf;
        buf++;
        // multirow
        switch (c)
        {
        case '\n':
            if (start) break;
            done = true;
            break;
        case '\r':
            break;
        case '\t':
        case ' ':
            if (start) break;
        default:
            start = false;
            row[n++] = c;
            if (n >= len - 1)
                done = true;
            break;
        }
    }
    row[n] = '\0';
    return buf;
}

static const int TILECACHESET_MAGIC = 'T' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'TSET';
static const int TILECACHESET_VERSION = 1;
static const int MAX_AGENTS = 128;

NavMesh* NavMesh::create(const std::string &navFilePath, const std::string &geomFilePath)
{
    auto ref = new (std::nothrow) NavMesh();
    if (ref && ref->initWithFilePath(navFilePath, geomFilePath))
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}

NavMesh::NavMesh()
    : _navMesh(nullptr)
    , _navMeshQuery(nullptr)
    , _crowed(nullptr)
    , _tileCache(nullptr)
    , _allocator(nullptr)
    , _compressor(nullptr)
    , _meshProcess(nullptr)
    , _geomData(nullptr)
    , _isDebugDrawEnabled(false)
{

}

NavMesh::~NavMesh()
{
    dtFreeTileCache(_tileCache);
    dtFreeCrowd(_crowed);
    dtFreeNavMesh(_navMesh);
    dtFreeNavMeshQuery(_navMeshQuery);
    CC_SAFE_DELETE(_allocator);
    CC_SAFE_DELETE(_compressor);
    CC_SAFE_DELETE(_meshProcess);
    CC_SAFE_DELETE(_geomData);

    for (auto iter : _agentList){
        CC_SAFE_RELEASE(iter);
    }
    _agentList.clear();

    for (auto iter : _obstacleList){
        CC_SAFE_RELEASE(iter);
    }
    _obstacleList.clear();
}

bool NavMesh::initWithFilePath(const std::string &navFilePath, const std::string &geomFilePath)
{
    _navFilePath = navFilePath;
    _geomFilePath = geomFilePath;
    if (!read()) return false;
    return true;
}

bool NavMesh::read()
{
    if (!loadGeomFile()) return false;
    if (!loadNavMeshFile()) return false;

    return true;
}

bool NavMesh::loadNavMeshFile()
{
    auto data = FileUtils::getInstance()->getDataFromFile(_navFilePath);
    if (data.isNull()) return false;

    // Read header.
    unsigned int offset = 0;
    TileCacheSetHeader header = *((TileCacheSetHeader*)(data.getBytes() + offset));
    offset += sizeof(TileCacheSetHeader);
    if (header.magic != TILECACHESET_MAGIC)
    {
        return false;
    }
    if (header.version != TILECACHESET_VERSION)
    {
        return false;
    }

    _navMesh = dtAllocNavMesh();
    if (!_navMesh)
    {
        return false;
    }
    dtStatus status = _navMesh->init(&header.meshParams);
    if (dtStatusFailed(status))
    {
        return false;
    }

    _tileCache = dtAllocTileCache();
    if (!_tileCache)
    {
        return false;
    }

    _allocator = new (std::nothrow) LinearAllocator(32000);
    _compressor = new (std::nothrow) FastLZCompressor;
    _meshProcess = new (std::nothrow) MeshProcess(_geomData);
    status = _tileCache->init(&header.cacheParams, _allocator, _compressor, _meshProcess);

    if (dtStatusFailed(status))
    {
        return false;
    }

    // Read tiles.
    for (int i = 0; i < header.numTiles; ++i)
    {
        TileCacheTileHeader tileHeader = *((TileCacheTileHeader*)(data.getBytes() + offset));
        offset += sizeof(TileCacheTileHeader);
        if (!tileHeader.tileRef || !tileHeader.dataSize)
            break;

        unsigned char* tileData = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
        if (!tileData) break;
        memcpy(tileData, (data.getBytes() + offset), tileHeader.dataSize);
        offset += tileHeader.dataSize;

        dtCompressedTileRef tile = 0;
        _tileCache->addTile(tileData, tileHeader.dataSize, DT_COMPRESSEDTILE_FREE_DATA, &tile);

        if (tile)
            _tileCache->buildNavMeshTile(tile, _navMesh);
    }

    //create crowed
    _crowed = dtAllocCrowd();
    _crowed->init(MAX_AGENTS, header.cacheParams.walkableRadius, _navMesh);

    //create NavMeshQuery
    _navMeshQuery = dtAllocNavMeshQuery();
    _navMeshQuery->init(_navMesh, 2048);

    _agentList.assign(MAX_AGENTS, nullptr);
    _obstacleList.assign(header.cacheParams.maxObstacles, nullptr);
    //duDebugDrawNavMesh(&_debugDraw, *_navMesh, DU_DRAWNAVMESH_OFFMESHCONS);
    return true;
}

bool NavMesh::loadGeomFile()
{
    unsigned char* buf = nullptr;
    auto data = FileUtils::getInstance()->getDataFromFile(_geomFilePath);
    if (data.isNull()) return false;
    buf = data.getBytes();
    _geomData = new (std::nothrow) GeomData;
    _geomData->offMeshConCount = 0;

    unsigned char* src = buf;
    unsigned char* srcEnd = buf + data.getSize();
    char row[512];
    while (src < srcEnd)
    {
        // Parse one row
        row[0] = '\0';
        src = parseRow(src, srcEnd, row, sizeof(row) / sizeof(char));
        if (row[0] == 'c')
        {
            // Off-mesh connection
            if (_geomData->offMeshConCount < GeomData::MAX_OFFMESH_CONNECTIONS)
            {
                float* v = &_geomData->offMeshConVerts[_geomData->offMeshConCount * 3 * 2];
                int bidir, area = 0, flags = 0;
                float rad;
                sscanf(row + 1, "%f %f %f  %f %f %f %f %d %d %d",
                    &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &rad, &bidir, &area, &flags);
                _geomData->offMeshConRads[_geomData->offMeshConCount] = rad;
                _geomData->offMeshConDirs[_geomData->offMeshConCount] = (unsigned char)bidir;
                _geomData->offMeshConAreas[_geomData->offMeshConCount] = (unsigned char)area;
                _geomData->offMeshConFlags[_geomData->offMeshConCount] = (unsigned short)flags;
                _geomData->offMeshConCount++;
            }
        }
    }

    return true;
}

void NavMesh::dtDraw()
{
    drawObstacles();
    _debugDraw.depthMask(false);
    duDebugDrawNavMeshWithClosedList(&_debugDraw, *_navMesh, *_navMeshQuery, DU_DRAWNAVMESH_OFFMESHCONS | DU_DRAWNAVMESH_CLOSEDLIST/* | DU_DRAWNAVMESH_COLOR_TILES*/);
    drawAgents();
    drawOffMeshConnections();
    _debugDraw.depthMask(true);
}

void cocos2d::NavMesh::drawOffMeshConnections()
{
    unsigned int conColor = duRGBA(192, 0, 128, 192);
    unsigned int baseColor = duRGBA(0, 0, 0, 64);
    _debugDraw.begin(DU_DRAW_LINES, 2.0f);
    for (int i = 0; i < _geomData->offMeshConCount; ++i)
    {
        float* v = &_geomData->offMeshConVerts[i * 3 * 2];

        _debugDraw.vertex(v[0], v[1], v[2], baseColor);
        _debugDraw.vertex(v[0], v[1] + 0.2f, v[2], baseColor);

        _debugDraw.vertex(v[3], v[4], v[5], baseColor);
        _debugDraw.vertex(v[3], v[4] + 0.2f, v[5], baseColor);

        duAppendCircle(&_debugDraw, v[0], v[1] + 0.1f, v[2], _geomData->offMeshConRads[i], baseColor);
        duAppendCircle(&_debugDraw, v[3], v[4] + 0.1f, v[5], _geomData->offMeshConRads[i], baseColor);

        if (/*hilight*/true)
        {
            duAppendArc(&_debugDraw, v[0], v[1], v[2], v[3], v[4], v[5], 0.25f,
                (_geomData->offMeshConDirs[i] & 1) ? 0.6f : 0.0f, 0.6f, conColor);
        }
    }
    _debugDraw.end();
}

void cocos2d::NavMesh::drawObstacles()
{
    // Draw obstacles
    for (auto iter : _obstacleList)
    {
        if (iter){
            const dtTileCacheObstacle* ob = _tileCache->getObstacleByRef(iter->_obstacleID);
            if (ob->state == DT_OBSTACLE_EMPTY) continue;
            float bmin[3], bmax[3];
            _tileCache->getObstacleBounds(ob, bmin, bmax);

            unsigned int col = 0;
            if (ob->state == DT_OBSTACLE_PROCESSING)
                col = duRGBA(255, 255, 0, 128);
            else if (ob->state == DT_OBSTACLE_PROCESSED)
                col = duRGBA(255, 192, 0, 192);
            else if (ob->state == DT_OBSTACLE_REMOVING)
                col = duRGBA(220, 0, 0, 128);

            duDebugDrawCylinder(&_debugDraw, bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2], col);
            duDebugDrawCylinderWire(&_debugDraw, bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2], duDarkenCol(col), 2);
        }
    }
}

void cocos2d::NavMesh::drawAgents()
{
    for (auto iter : _agentList)
    {
        if (iter){
            auto agent = _crowed->getAgent(iter->_agentID);
            float r = iter->getRadius();
            float h = iter->getHeight();

            unsigned int col = duRGBA(0, 0, 0, 32);
            duDebugDrawCircle(&_debugDraw, agent->npos[0], agent->npos[1], agent->npos[2], r, col, 2.0f);

            col = duRGBA(220, 220, 220, 128);
            if (agent->targetState == DT_CROWDAGENT_TARGET_REQUESTING || agent->targetState == DT_CROWDAGENT_TARGET_WAITING_FOR_QUEUE)
                col = duLerpCol(col, duRGBA(128, 0, 255, 128), 32);
            else if (agent->targetState == DT_CROWDAGENT_TARGET_WAITING_FOR_PATH)
                col = duLerpCol(col, duRGBA(128, 0, 255, 128), 128);
            else if (agent->targetState == DT_CROWDAGENT_TARGET_FAILED)
                col = duRGBA(255, 32, 16, 128);
            else if (agent->targetState == DT_CROWDAGENT_TARGET_VELOCITY)
                col = duLerpCol(col, duRGBA(64, 255, 0, 128), 128);

            duDebugDrawCylinder(&_debugDraw, agent->npos[0] - r, agent->npos[1] + r*0.1f, agent->npos[2] - r,
                agent->npos[0] + r, agent->npos[1] + h, agent->npos[2] + r, col);

        }
    }

    // Velocity stuff.
    for (auto iter : _agentList)
    {
        if (iter){
            auto agent = _crowed->getAgent(iter->_agentID);

            const float radius = agent->params.radius;
            const float height = agent->params.height;
            const float* pos = agent->npos;
            const float* vel = agent->vel;
//            const float* dvel = agent->dvel;

            unsigned int col = duRGBA(220, 220, 220, 192);
            if (agent->targetState == DT_CROWDAGENT_TARGET_REQUESTING || agent->targetState == DT_CROWDAGENT_TARGET_WAITING_FOR_QUEUE)
                col = duLerpCol(col, duRGBA(128, 0, 255, 192), 32);
            else if (agent->targetState == DT_CROWDAGENT_TARGET_WAITING_FOR_PATH)
                col = duLerpCol(col, duRGBA(128, 0, 255, 192), 128);
            else if (agent->targetState == DT_CROWDAGENT_TARGET_FAILED)
                col = duRGBA(255, 32, 16, 192);
            else if (agent->targetState == DT_CROWDAGENT_TARGET_VELOCITY)
                col = duLerpCol(col, duRGBA(64, 255, 0, 192), 128);

            duDebugDrawCircle(&_debugDraw, pos[0], pos[1] + height, pos[2], radius, col, 2.0f);

            //duDebugDrawArrow(&_debugDraw, pos[0], pos[1] + height, pos[2],
            //    pos[0] + dvel[0], pos[1] + height + dvel[1], pos[2] + dvel[2],
            //    0.0f, 0.4f, duRGBA(0, 192, 255, 192), 2.0f);

            duDebugDrawArrow(&_debugDraw, pos[0], pos[1] + height, pos[2],
                pos[0] + vel[0], pos[1] + height + vel[1], pos[2] + vel[2],
                0.0f, 0.4f, duRGBA(0, 0, 0, 160), 2.0f);
        }
    }
}

void NavMesh::removeNavMeshObstacle(NavMeshObstacle *obstacle)
{
    auto iter = std::find(_obstacleList.begin(), _obstacleList.end(), obstacle);
    if (iter != _obstacleList.end()){
        obstacle->removeFrom(_tileCache);
        obstacle->release();
        _obstacleList[iter - _obstacleList.begin()] = nullptr;
    }
}

void NavMesh::addNavMeshObstacle(NavMeshObstacle *obstacle)
{
    auto iter = std::find(_obstacleList.begin(), _obstacleList.end(), nullptr);
    if (iter != _obstacleList.end()){
        obstacle->addTo(_tileCache);
        obstacle->retain();
        _obstacleList[iter - _obstacleList.begin()] = obstacle;
    }
}

void NavMesh::removeNavMeshAgent(NavMeshAgent *agent)
{
    auto iter = std::find(_agentList.begin(), _agentList.end(), agent);
    if (iter != _agentList.end()){
        agent->removeFrom(_crowed);
        agent->setNavMeshQuery(nullptr);
        agent->release();
        _agentList[iter - _agentList.begin()] = nullptr;
    }
}

void NavMesh::addNavMeshAgent(NavMeshAgent *agent)
{
    auto iter = std::find(_agentList.begin(), _agentList.end(), nullptr);
    if (iter != _agentList.end()){
        agent->addTo(_crowed);
        agent->setNavMeshQuery(_navMeshQuery);
        agent->retain();
        _agentList[iter - _agentList.begin()] = agent;
    }
}

bool NavMesh::isDebugDrawEnabled() const
{
    return _isDebugDrawEnabled;
}

void NavMesh::setDebugDrawEnable(bool enable)
{
    _isDebugDrawEnabled = enable;
}

void NavMesh::debugDraw(Renderer* renderer)
{
    if (_isDebugDrawEnabled){
        _debugDraw.clear();
        dtDraw();
        _debugDraw.draw(renderer);
    }
}

void NavMesh::update(float dt)
{
    for (auto iter : _agentList){
        if (iter)
            iter->preUpdate(dt);
    }

    for (auto iter : _obstacleList){
        if (iter)
            iter->preUpdate(dt);
    }

    if (_crowed)
        _crowed->update(dt, nullptr);

    if (_tileCache)
        _tileCache->update(dt, _navMesh);

    for (auto iter : _agentList){
        if (iter)
            iter->postUpdate(dt);
    }

    for (auto iter : _obstacleList){
        if (iter)
            iter->postUpdate(dt);
    }
}

void cocos2d::NavMesh::findPath(const Vec3 &start, const Vec3 &end, std::vector<Vec3> &pathPoints)
{
    static const int MAX_POLYS = 256;
    static const int MAX_SMOOTH = 2048;
    float ext[3];
    ext[0] = 2; ext[1] = 4; ext[2] = 2;
    dtQueryFilter filter;
    dtPolyRef startRef, endRef;
    dtPolyRef polys[MAX_POLYS];
    int npolys = 0;
    _navMeshQuery->findNearestPoly(&start.x, ext, &filter, &startRef, 0);
    _navMeshQuery->findNearestPoly(&end.x, ext, &filter, &endRef, 0);
    _navMeshQuery->findPath(startRef, endRef, &start.x, &end.x, &filter, polys, &npolys, MAX_POLYS);

    if (npolys)
    {
        //// Iterate over the path to find smooth path on the detail mesh surface.
        //dtPolyRef polys[MAX_POLYS];
        //memcpy(polys, polys, sizeof(dtPolyRef)*npolys);
        //int npolys = npolys;

        float iterPos[3], targetPos[3];
        _navMeshQuery->closestPointOnPoly(startRef, &start.x, iterPos, 0);
        _navMeshQuery->closestPointOnPoly(polys[npolys - 1], &end.x, targetPos, 0);

        static const float STEP_SIZE = 0.5f;
        static const float SLOP = 0.01f;

        int nsmoothPath = 0;
        //dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
        //m_nsmoothPath++;

        pathPoints.push_back(Vec3(iterPos[0], iterPos[1], iterPos[2]));
        nsmoothPath++;

        // Move towards target a small advancement at a time until target reached or
        // when ran out of memory to store the path.
        while (npolys && nsmoothPath < MAX_SMOOTH)
        {
            // Find location to steer towards.
            float steerPos[3];
            unsigned char steerPosFlag;
            dtPolyRef steerPosRef;

            if (!getSteerTarget(_navMeshQuery, iterPos, targetPos, SLOP,
                polys, npolys, steerPos, steerPosFlag, steerPosRef))
                break;

            bool endOfPath = (steerPosFlag & DT_STRAIGHTPATH_END) ? true : false;
            bool offMeshConnection = (steerPosFlag & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ? true : false;

            // Find movement delta.
            float delta[3], len;
            dtVsub(delta, steerPos, iterPos);
            len = dtMathSqrtf(dtVdot(delta, delta));
            // If the steer target is end of path or off-mesh link, do not move past the location.
            if ((endOfPath || offMeshConnection) && len < STEP_SIZE)
                len = 1;
            else
                len = STEP_SIZE / len;
            float moveTgt[3];
            dtVmad(moveTgt, iterPos, delta, len);

            // Move
            float result[3];
            dtPolyRef visited[16];
            int nvisited = 0;
            _navMeshQuery->moveAlongSurface(polys[0], iterPos, moveTgt, &filter,
                result, visited, &nvisited, 16);

            npolys = fixupCorridor(polys, npolys, MAX_POLYS, visited, nvisited);
            npolys = fixupShortcuts(polys, npolys, _navMeshQuery);

            float h = 0;
            _navMeshQuery->getPolyHeight(polys[0], result, &h);
            result[1] = h;
            dtVcopy(iterPos, result);

            // Handle end of path and off-mesh links when close enough.
            if (endOfPath && inRange(iterPos, steerPos, SLOP, 1.0f))
            {
                // Reached end of path.
                dtVcopy(iterPos, targetPos);
                if (nsmoothPath < MAX_SMOOTH)
                {
                    //dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
                    //m_nsmoothPath++;
                    pathPoints.push_back(Vec3(iterPos[0], iterPos[1], iterPos[2]));
                    nsmoothPath++;
                }
                break;
            }
            else if (offMeshConnection && inRange(iterPos, steerPos, SLOP, 1.0f))
            {
                // Reached off-mesh connection.
                float startPos[3], endPos[3];

                // Advance the path up to and over the off-mesh connection.
                dtPolyRef prevRef = 0, polyRef = polys[0];
                int npos = 0;
                while (npos < npolys && polyRef != steerPosRef)
                {
                    prevRef = polyRef;
                    polyRef = polys[npos];
                    npos++;
                }
                for (int i = npos; i < npolys; ++i)
                    polys[i - npos] = polys[i];
                npolys -= npos;

                // Handle the connection.
                dtStatus status = _navMesh->getOffMeshConnectionPolyEndPoints(prevRef, polyRef, startPos, endPos);
                if (dtStatusSucceed(status))
                {
                    if (nsmoothPath < MAX_SMOOTH)
                    {
                        //dtVcopy(&m_smoothPath[m_nsmoothPath * 3], startPos);
                        //m_nsmoothPath++;
                        pathPoints.push_back(Vec3(startPos[0], startPos[1], startPos[2]));
                        nsmoothPath++;
                        // Hack to make the dotted path not visible during off-mesh connection.
                        if (nsmoothPath & 1)
                        {
                            //dtVcopy(&m_smoothPath[m_nsmoothPath * 3], startPos);
                            //m_nsmoothPath++;
                            pathPoints.push_back(Vec3(startPos[0], startPos[1], startPos[2]));
                            nsmoothPath++;
                        }
                    }
                    // Move position at the other side of the off-mesh link.
                    dtVcopy(iterPos, endPos);
                    float eh = 0.0f;
                    _navMeshQuery->getPolyHeight(polys[0], iterPos, &eh);
                    iterPos[1] = eh;
                }
            }

            // Store results.
            if (nsmoothPath < MAX_SMOOTH)
            {
                //dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
                //m_nsmoothPath++;

                pathPoints.push_back(Vec3(iterPos[0], iterPos[1], iterPos[2]));
                nsmoothPath++;
            }
        }
    }
}

NS_CC_END

#endif //CC_USE_NAVMESH
