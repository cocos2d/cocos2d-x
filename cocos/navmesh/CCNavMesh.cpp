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

NS_CC_BEGIN

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

NavMesh* NavMesh::create(const std::string &filePath, int maxSearchNodes)
{
	auto ref = new (std::nothrow) NavMesh();
	if (ref && ref->initWithFilePath(filePath, maxSearchNodes))
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
{

}

NavMesh::~NavMesh()
{
	dtFreeNavMesh(_navMesh);
	dtFreeNavMeshQuery(_navMeshQuery);
}

bool NavMesh::initWithFilePath(const std::string &filePath, int maxSearchNodes)
{
	_filePath = filePath;
	if (!read()) return false;
	_navMeshQuery = dtAllocNavMeshQuery();
	_navMeshQuery->init(_navMesh, maxSearchNodes);
	return true;
}

bool NavMesh::read()
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(_filePath);
	FILE* fp = fopen(fullPath.c_str(), "rb");
	if (!fp) return false;

	// Read header.
	NavMeshSetHeader header;
	size_t readLen = fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (readLen != 1)
	{
		fclose(fp);
		return 0;
	}
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return 0;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return 0;
	}

	if (_navMesh) dtFreeNavMesh(_navMesh);

	_navMesh = dtAllocNavMesh();
	if (!_navMesh)
	{
		fclose(fp);
		return 0;
	}
	dtStatus status = _navMesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return 0;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		readLen = fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (readLen != 1)
			return 0;

		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		readLen = fread(data, tileHeader.dataSize, 1, fp);
		if (readLen != 1)
			return 0;

		_navMesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	//duDebugDrawNavMesh(&_debugDraw, *_navMesh, DU_DRAWNAVMESH_OFFMESHCONS);
	return true;
}

NS_CC_END