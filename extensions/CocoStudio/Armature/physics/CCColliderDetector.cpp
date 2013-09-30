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


NS_CC_EXT_ARMATURE_BEGIN


#if ENABLE_PHYSICS_BOX2D_DETECT
ColliderBody::ColliderBody(ContourData *contourData)
    : _fixture(NULL)
    , _filter(NULL)
    , _contourData(contourData)
{
    CC_SAFE_RETAIN(_contourData);
}
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT

ColliderBody::ColliderBody(ContourData *contourData)
    : _shape(NULL)
    , _contourData(contourData)
{
    CC_SAFE_RETAIN(_contourData);
}
#endif

ColliderBody::~ColliderBody()
{
    CC_SAFE_RELEASE(_contourData);

#if ENABLE_PHYSICS_BOX2D_DETECT
    CC_SAFE_DELETE(_filter);
#endif
}



ColliderDetector *ColliderDetector::create()
{
    ColliderDetector *pColliderDetector = new ColliderDetector();
    if (pColliderDetector && pColliderDetector->init())
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return NULL;
}

ColliderDetector *ColliderDetector::create(Bone *bone)
{
    ColliderDetector *pColliderDetector = new ColliderDetector();
    if (pColliderDetector && pColliderDetector->init(bone))
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return NULL;
}

ColliderDetector::ColliderDetector()
    : _colliderBodyList(NULL)
    , _active(false)
{
    _body = NULL;
}

ColliderDetector::~ColliderDetector()
{
    _colliderBodyList->removeAllObjects();
    CC_SAFE_DELETE(_colliderBodyList);
}

bool ColliderDetector::init()
{
    _colliderBodyList = Array::create();
    CCASSERT(_colliderBodyList, "create _colliderBodyList failed!");
    _colliderBodyList->retain();

    return true;
}

bool ColliderDetector::init(Bone *bone)
{
    init();
    setBone(bone);

    return true;
}

void ColliderDetector::addContourData(ContourData *contourData)
{
    ColliderBody *colliderBody = new ColliderBody(contourData);
    _colliderBodyList->addObject(colliderBody);
    colliderBody->release();
}

void ColliderDetector::addContourDataList(Array *contourDataList)
{
    Object *object = NULL;
    CCARRAY_FOREACH(contourDataList, object)
    {
        addContourData((ContourData *)object);
    }
}

void ColliderDetector::removeContourData(ContourData *contourData)
{
	Object *object = NULL;
	CCARRAY_FOREACH(_colliderBodyList, object)
	{
		ColliderBody *body = (ColliderBody*)object;
		if (body && body->getContourData() == contourData)
		{
			_colliderBodyList->removeObject(body);
		}
	}
}

void ColliderDetector::removeAll()
{
    _colliderBodyList->removeAllObjects();
}


void ColliderDetector::setActive(bool active)
{
    if (_active == active)
    {
        return;
    }

    _active = active;

#if ENABLE_PHYSICS_BOX2D_DETECT
    if (_body)
    {
        if (active)
        {
            setBody(_body);
        }
        else
        {
            Object *object = NULL;
            CCARRAY_FOREACH(_colliderBodyList, object)
            {
                ColliderBody *colliderBody = (ColliderBody *)object;
                b2Fixture *fixture = colliderBody->getB2Fixture();

                b2Filter *filter = colliderBody->getB2Filter();
                *filter = fixture->GetFilterData();

                _body->DestroyFixture(fixture);
                colliderBody->setB2Fixture(NULL);
            }
        }
    }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (_body)
    {
        Object *object = NULL;
        if (_active)
        {
            CCARRAY_FOREACH(_colliderBodyList, object)
            {
                ColliderBody *colliderBody = (ColliderBody *)object;
                cpShape *shape = colliderBody->getShape();
                cpSpaceAddShape(_body->space_private, shape);
            }
        }
        else
        {
            CCARRAY_FOREACH(_colliderBodyList, object)
            {
                ColliderBody *colliderBody = (ColliderBody *)object;
                cpShape *shape = colliderBody->getShape();
                cpSpaceRemoveShape(_body->space_private, shape);
            }
        }
    }
#endif
}

bool ColliderDetector::getActive()
{
    return _active;
}

Array *ColliderDetector::getColliderBodyList()
{
    return _colliderBodyList;
}


Point helpPoint;

void ColliderDetector::updateTransform(AffineTransform &t)
{
    if (!_active)
    {
        return;
    }

    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        ContourData *contourData = colliderBody->getContourData();

#if ENABLE_PHYSICS_BOX2D_DETECT
        b2PolygonShape *shape = NULL;
        if (_body != NULL)
        {
            shape = (b2PolygonShape *)colliderBody->getB2Fixture()->GetShape();
        }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
        cpPolyShape *shape = NULL;
        if (_body != NULL)
        {
            shape = (cpPolyShape *)colliderBody->getShape();
        }
#endif

        int num = contourData->vertexList.count();
        ContourVertex2 **vs = (ContourVertex2 **)contourData->vertexList.data->arr;

        for (int i = 0; i < num; i++)
        {
            helpPoint.setPoint( vs[i]->x,  vs[i]->y);
            helpPoint = PointApplyAffineTransform(helpPoint, t);


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
        for (int i = 0; i < num; i++)
        {
            cpVect b = shape->verts[(i + 1) % shape->numVerts];
            cpVect n = cpvnormalize(cpvperp(cpvsub(b, shape->verts[i])));

            shape->planes[i].n = n;
            shape->planes[i].d = cpvdot(n, shape->verts[i]);
        }
#endif
    }
}

#if ENABLE_PHYSICS_BOX2D_DETECT

void ColliderDetector::setBody(b2Body *pBody)
{
    _body = pBody;

    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        ContourData *contourData = colliderBody->getContourData();
        const Array *array = &contourData->vertexList;
        Object *object = NULL;

        b2Vec2 *b2bv = new b2Vec2[contourData->vertexList.count()];

        int i = 0;
        CCARRAY_FOREACH(array, object)
        {
            ContourVertex2 *v = (ContourVertex2 *)object;
            b2bv[i].Set(v->x / PT_RATIO, v->y / PT_RATIO);
            i++;
        }

        b2PolygonShape polygon;
        polygon.Set(b2bv, contourData->vertexList.count());

        CC_SAFE_DELETE(b2bv);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygon;
        fixtureDef.isSensor = true;

        b2Fixture *fixture = _body->CreateFixture(&fixtureDef);
        fixture->SetUserData(_bone);

        if (colliderBody->getB2Fixture() != NULL)
        {
            _body->DestroyFixture(colliderBody->getB2Fixture());
        }
        colliderBody->setB2Fixture(fixture);

        if (colliderBody->getB2Filter() == NULL)
        {
            b2Filter *filter = new b2Filter;
            colliderBody->setB2Filter(filter);
        }
        else
        {
            fixture->SetFilterData(*colliderBody->getB2Filter());
        }
    }
}

b2Body *ColliderDetector::getBody()
{
    return _body;
}

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
void ColliderDetector::setBody(cpBody *pBody)
{
    _body = pBody;

    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        ContourData *contourData = colliderBody->getContourData();

        int num = contourData->vertexList.count();
        ContourVertex2 **vs = (ContourVertex2 **)contourData->vertexList.data->arr;
        cpVect *verts = new cpVect[num];
        for (int i = 0; i < num; i++)
        {
            verts[num - 1 - i].x = vs[i]->x;
            verts[num - 1 - i].y = vs[i]->y;
        }

        cpShape *shape = cpPolyShapeNew(_body, num, verts, cpvzero);

        shape->sensor = true;
        shape->data = _bone;
        cpSpaceAddShape(_body->space_private, shape);

        colliderBody->setShape(shape);

        delete []verts;
    }
}

cpBody *ColliderDetector::getBody()
{
    return _body;
}

#endif


NS_CC_EXT_ARMATURE_END
