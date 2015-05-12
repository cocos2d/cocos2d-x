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
#include "navmesh/CCNavMeshObstacle.h"

NS_CC_BEGIN

NavMeshObstacle* NavMeshObstacle::create(const Vec3 &position, float radius, float height)
{
	auto ref = new (std::nothrow) NavMeshObstacle();
	if (ref && ref->init(position, radius, height))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

NavMeshObstacle::NavMeshObstacle()
: _radius(0.0f)
, _height(0.0f)
{

}

cocos2d::NavMeshObstacle::~NavMeshObstacle()
{

}

bool NavMeshObstacle::init(const Vec3 &position, float radius, float height)
{
	_position = position;
	_radius = radius;
	_height = height;
	return true;
}

NS_CC_END

