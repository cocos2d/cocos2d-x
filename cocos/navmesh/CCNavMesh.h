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

#include "base/CCRef.h"
#include "math/Vec3.h"
#include "recast/Detour/DetourNavMesh.h"
#include "recast/Detour/DetourNavMeshQuery.h"
#include <string>
#include <vector>


NS_CC_BEGIN

/**
 * @addtogroup 3d
 * @{
 */

class CC_DLL NavMesh : public Ref
{
public:

	static NavMesh* create(const std::string &filePath, int maxSearchNodes = 2048);

	void findPath(const Vec3 &start, const Vec3 &end, std::vector<Vec3> &pathPoints);


CC_CONSTRUCTOR_ACCESS:
	NavMesh();
	virtual ~NavMesh();

protected:

	bool initWithFilePath(const std::string &filePath, int maxSearchNodes);
	bool read();

protected:

	dtNavMesh *_navMesh;
	dtNavMeshQuery *_navMeshQuery;
	std::string _filePath;
};

/** @} */

NS_CC_END

#endif // __CCNAV_MESH_H__
