/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCColliderDetector.h"
#include "../CCBone.h"
#include "../utils/CCTransformHelp.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif


NS_CC_EXT_BEGIN

CCColliderDetector *CCColliderDetector::create()
{
	CCColliderDetector *pColliderDetector = new CCColliderDetector();
	if (pColliderDetector && pColliderDetector->init())
	{
		pColliderDetector->autorelease();
		return pColliderDetector;
	}
	CC_SAFE_DELETE(pColliderDetector);
	return NULL;
}

CCColliderDetector *CCColliderDetector::create(CCBone *bone)
{
	CCColliderDetector *pColliderDetector = new CCColliderDetector();
	if (pColliderDetector && pColliderDetector->init(bone))
	{
		pColliderDetector->autorelease();
		return pColliderDetector;
	}
	CC_SAFE_DELETE(pColliderDetector);
	return NULL;
}

CCColliderDetector::CCColliderDetector()
	: m_pColliderBodyList(NULL)
	, m_bActive(false)
{
#if ENABLE_PHYSICS_BOX2D_DETECT
	m_pB2Body = NULL;
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
	m_pCPBody = NULL;
#endif
}

CCColliderDetector::~CCColliderDetector()
{
	m_pColliderBodyList->removeAllObjects();
	CC_SAFE_DELETE(m_pColliderBodyList);
}

bool CCColliderDetector::init()
{
	m_pColliderBodyList = CCArray::create();
	CCAssert(m_pColliderBodyList, "create m_pColliderBodyList failed!");
	m_pColliderBodyList->retain();

	return true;
}

bool CCColliderDetector::init(CCBone *bone)
{
	init();
	setBone(bone);

	return true;
}

void CCColliderDetector::addContourData(CCContourData *contourData)
{
	ColliderBody *colliderBody = new ColliderBody(contourData);
	m_pColliderBodyList->addObject(colliderBody);
	colliderBody->release();
}

void CCColliderDetector::addContourDataList(CCArray *contourDataList)
{
	CCObject *object = NULL;
	CCARRAY_FOREACH(contourDataList, object)
	{
		addContourData((CCContourData *)object);
	}
}

void CCColliderDetector::removeContourData(CCContourData *_contourData)
{
	m_pColliderBodyList->removeObject(_contourData);
}

void CCColliderDetector::removeAll()
{
	m_pColliderBodyList->removeAllObjects();
}


void CCColliderDetector::setActive(bool active)
{
	if (m_bActive == active)
	{
		return;
	}

	m_bActive = active;

#if ENABLE_PHYSICS_BOX2D_DETECT
	if (m_pB2Body)
	{
		if (active)
		{
			setB2Body(m_pB2Body);
		}
		else
		{
			CCObject *object = NULL;
			CCARRAY_FOREACH(m_pColliderBodyList, object)
			{
				ColliderBody *colliderBody = (ColliderBody *)object;
				b2Fixture *fixture = colliderBody->getB2Fixture();
				m_pB2Body->DestroyFixture(fixture);
				colliderBody->setB2Fixture(NULL);
			}
		}
	}
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
	if (m_pCPBody)
	{
		CCObject *object = NULL;
		if (m_bActive)
		{
			CCARRAY_FOREACH(m_pColliderBodyList, object)
			{
				ColliderBody *colliderBody = (ColliderBody *)object;
				cpShape *shape = colliderBody->getShape();
				cpSpaceAddShape(m_pCPBody->space_private, shape);
			}
		}
		else
		{
			CCARRAY_FOREACH(m_pColliderBodyList, object)
			{
				ColliderBody *colliderBody = (ColliderBody *)object;
				cpShape *shape = colliderBody->getShape();
				cpSpaceRemoveShape(m_pCPBody->space_private, shape);
			}
		}
	}
#endif
}

bool CCColliderDetector::getActive()
{
	return m_bActive;
}

CCArray *CCColliderDetector::getColliderBodyList()
{
	return m_pColliderBodyList;
}


CCPoint helpPoint;

void CCColliderDetector::updateTransform(CCAffineTransform &t)
{
	if (!m_bActive)
	{
		return;
	}

	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pColliderBodyList, object)
	{
		ColliderBody *colliderBody = (ColliderBody *)object;
		CCContourData *contourData = colliderBody->getContourData();

#if ENABLE_PHYSICS_BOX2D_DETECT
		b2PolygonShape *shape = NULL;
		if (m_pB2Body != NULL)
		{
			shape = (b2PolygonShape *)colliderBody->getB2Fixture()->GetShape();
		}
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
		cpPolyShape *shape = NULL;
		if (m_pCPBody != NULL)
		{
			shape = (cpPolyShape *)colliderBody->getShape();
		}
#endif

		int num = contourData->vertexList.count();
		CCContourVertex2 **vs = (CCContourVertex2 **)contourData->vertexList.data->arr;
		
		for (int i=0; i<num; i++)
		{
			helpPoint.setPoint( vs[i]->x,  vs[i]->y);
			helpPoint = CCPointApplyAffineTransform(helpPoint, t);


#if ENABLE_PHYSICS_BOX2D_DETECT
			if (shape != NULL)
			{
				b2Vec2 &bv = shape->m_vertices[i];
				bv.Set(helpPoint.x / PT_RATIO, helpPoint.y / PT_RATIO);
			}
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
			if (shape != NULL)
			{
				cpVect v ;
				v.x = helpPoint.x;
				v.y = helpPoint.y;
				shape->verts[i] = v;
			}
#endif
		}

#if ENABLE_PHYSICS_CHIPMUNK_DETECT
		cpConvexHull(num, shape->verts, NULL, NULL, 0);
		for (int i=0; i<num; i++)
		{
			cpVect b = shape->verts[(i+1)%shape->numVerts];
			cpVect n = cpvnormalize(cpvperp(cpvsub(b, shape->verts[i])));

			shape->planes[i].n = n;
			shape->planes[i].d = cpvdot(n, shape->verts[i]);
		}
#endif
	}
}

#if ENABLE_PHYSICS_BOX2D_DETECT

void CCColliderDetector::setB2Body(b2Body *pBody)
{
	m_pB2Body = pBody;

	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pColliderBodyList, object)
	{
		ColliderBody *colliderBody = (ColliderBody *)object;

		CCContourData *contourData = colliderBody->getContourData();
		const CCArray *array = &contourData->vertexList;
		CCObject *object = NULL;

		b2Vec2 *b2bv = new b2Vec2[contourData->vertexList.count()];

		int i = 0;
		CCARRAY_FOREACH(array, object)
		{
			CCContourVertex2 *v = (CCContourVertex2 *)object;
			b2bv[i].Set(v->x / PT_RATIO, v->y / PT_RATIO);
			i++;
		}

		b2PolygonShape polygon;
		polygon.Set(b2bv, contourData->vertexList.count());

		CC_SAFE_DELETE(b2bv);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &polygon;
		fixtureDef.isSensor = true;

		b2Fixture *fixture = m_pB2Body->CreateFixture(&fixtureDef);
		fixture->SetUserData(m_pBone);

		if (colliderBody->getB2Fixture() != NULL)
		{
			m_pB2Body->DestroyFixture(colliderBody->getB2Fixture());
		}
		colliderBody->setB2Fixture(fixture);
	}
}

b2Body *CCColliderDetector::getB2Body()
{
	return m_pB2Body;
}

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
void CCColliderDetector::setCPBody(cpBody *pBody)
{
	m_pCPBody = pBody;

	CCObject *object = NULL;
	CCARRAY_FOREACH(m_pColliderBodyList, object)
	{
		ColliderBody *colliderBody = (ColliderBody *)object;

		CCContourData *contourData = colliderBody->getContourData();

		int num = contourData->vertexList.count();
		CCContourVertex2 **vs = (CCContourVertex2 **)contourData->vertexList.data->arr;
		cpVect *verts = new cpVect[num];
		for (int i=0; i<num; i++)
		{
			verts[num-1-i].x = vs[i]->x;
			verts[num-1-i].y = vs[i]->y;
		}

		cpShape* shape = cpPolyShapeNew(m_pCPBody, num, verts, cpvzero);

		shape->sensor = true;
		shape->data = m_pBone;
		cpSpaceAddShape(m_pCPBody->space_private, shape);

		colliderBody->setShape(shape);

		delete []verts;
	}
}

cpBody *CCColliderDetector::getCPBody()
{
	return m_pCPBody;
}

#endif


NS_CC_EXT_END
