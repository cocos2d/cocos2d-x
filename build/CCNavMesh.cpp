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
#include "platform/CCFileUtils.h"
#include "renderer/CCRenderer.h"

NS_CC_BEGIN

struct TileCacheSetHeader
{
    int magic;
    int version;
    int numTiles;
    dtNavMeshParams meshParams;
    dtTileCacheParams cacheParams;
};

struct TileCacheTileHeader
{
    dtCompressedTileRef tileRef;
    int dataSize;
};

static const int TILECACHESET_MAGIC = 'T' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'TSET';
static const int TILECACHESET_VERSION = 1;
static const int MAX_AGENTS = 128;

NavMesh* NavMesh::create(const std::string &filePath)
{
    auto ref = new (std::nothrow) NavMesh();
    if (ref && ref->initWithFilePath(filePath))
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
}

bool NavMesh::initWithFilePath(const std::string &filePath)
{
    _filePath = filePath;
    if (!read()) return false;
    return true;
}

bool NavMesh::read()
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(_filePath);
    FILE* fp = fopen(fullPath.c_str(), "rb");
    if (!fp) return false;

    // Read header.
    TileCacheSetHeader header;
    fread(&header, sizeof(TileCacheSetHeader), 1, fp);
    if (header.magic != TILECACHESET_MAGIC)
    {
        fclose(fp);
        return false;
    }
    if (header.version != TILECACHESET_VERSION)
    {
        fclose(fp);
        return false;
    }

    _navMesh = dtAllocNavMesh();
    if (!_navMesh)
    {
        fclose(fp);
        return false;
    }
    dtStatus status = _navMesh->init(&header.meshParams);
    if (dtStatusFailed(status))
    {
        fclose(fp);
        return false;
    }

    _tileCache = dtAllocTileCache();
    if (!_tileCache)
    {
        fclose(fp);
        return false;
    }

    _allocator = new LinearAllocator(32000);
    _compressor = new FastLZCompressor;
    _meshProcess = new MeshProcess;
    status = _tileCache->init(&header.cacheParams, _allocator, _compressor, _meshProcess);

    if (dtStatusFailed(status))
    {
        fclose(fp);
        return false;
    }

    // Read tiles.
    for (int i = 0; i < header.numTiles; ++i)
    {
        TileCacheTileHeader tileHeader;
        fread(&tileHeader, sizeof(tileHeader), 1, fp);
        if (!tileHeader.tileRef || !tileHeader.dataSize)
            break;

        unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
        if (!data) break;
        memset(data, 0, tileHeader.dataSize);
        fread(data, tileHeader.dataSize, 1, fp);

        dtCompressedTileRef tile = 0;
        _tileCache->addTile(data, tileHeader.dataSize, DT_COMPRESSEDTILE_FREE_DATA, &tile);

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
        _debugDraw.draw(renderer);
    }
}

void NavMesh::update(float dt)
{
    for (auto iter : _agentList){
        iter->preUpdate(dt);
    }

    for (auto iter : _obstacleList){
        iter->preUpdate(dt);
    }

    if (_crowed)
        _crowed->update(dt, nullptr);

    for (auto iter : _agentList){
        iter->postUpdate(dt);
    }

    for (auto iter : _obstacleList){
        iter->postUpdate(dt);
    }
}

NS_CC_END
