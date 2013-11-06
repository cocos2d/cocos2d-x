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

#include "cocostudio/CCColliderDetector.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCTransformHelp.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif

using namespace cocos2d;

namespace cocostudio {


#if ENABLE_PHYSICS_BOX2D_DETECT
ColliderFilter::ColliderFilter(unsigned short categoryBits, unsigned short maskBits, signed short groupIndex)
    : _categoryBits(categoryBits)
    , _maskBits(maskBits)
    , _groupIndex(groupIndex)
{
}

void ColliderFilter::updateShape(b2Fixture *fixture)
{
        b2Filter filter;
        filter.categoryBits = _categoryBits;
        filter.groupIndex = _groupIndex;
        filter.maskBits = _maskBits;
        
        fixture->SetFilterData(filter);
}

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
ColliderFilter::ColliderFilter(uintptr_t collisionType, uintptr_t group)
    : _collisionType(collisionType)
    , _group(group)
{
}
void ColliderFilter::updateShape(cpShape *shape)
{
        shape->collision_type = _collisionType;
        shape->group = _group;
}
#endif

#if ENABLE_PHYSICS_BOX2D_DETECT
ColliderBody::ColliderBody(ContourData *contourData)
    : _fixture(nullptr)
    , _contourData(contourData)
{
    CC_SAFE_RETAIN(_contourData);
    _filter = new ColliderFilter();

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    _calculatedVertexList = Array::create();
    CC_SAFE_RETAIN(_calculatedVertexList);
#endif
}
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT

ColliderBody::ColliderBody(ContourData *contourData)
    : _shape(nullptr)
    , _contourData(contourData)
{
    CC_SAFE_RETAIN(_contourData);
    _filter = new ColliderFilter();

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    _calculatedVertexList = Array::create();
    CC_SAFE_RETAIN(_calculatedVertexList);
#endif
}
#endif

ColliderBody::~ColliderBody()
{
    CC_SAFE_RELEASE(_contourData);
    CC_SAFE_DELETE(_filter);

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    CC_SAFE_RELEASE(_calculatedVertexList);
#endif
}

void ColliderBody::setColliderFilter(ColliderFilter *filter)
{
    *_filter = *filter;
}
ColliderFilter *ColliderBody::getColliderFilter()
{
    return _filter;
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
    return nullptr;
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
    return nullptr;
}

ColliderDetector::ColliderDetector()
    : _colliderBodyList(nullptr)
    , _filter(nullptr)
    , _active(false)
{
    _body = nullptr;
}

ColliderDetector::~ColliderDetector()
{
    _colliderBodyList->removeAllObjects();
    CC_SAFE_DELETE(_colliderBodyList);
    CC_SAFE_DELETE(_filter);
}

bool ColliderDetector::init()
{
    _colliderBodyList = Array::create();
    CCASSERT(_colliderBodyList, "create _colliderBodyList failed!");
    _colliderBodyList->retain();

    _filter = new ColliderFilter();

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


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    CCArray *calculatedVertexList = colliderBody->getCalculatedVertexList();
    
    int num = contourData->vertexList.count();
    for (int i = 0; i < num; i++)
    {
        ContourVertex2 *newVertex = new ContourVertex2(0, 0);
        calculatedVertexList->addObject(newVertex);
        newVertex->release();
    }
#endif
}

void ColliderDetector::addContourDataList(Array *contourDataList)
{
    for(auto object : *contourDataList)
    {
        addContourData((ContourData *)object);
    }
}

void ColliderDetector::removeContourData(ContourData *contourData)
{
	for(auto object : *_colliderBodyList)
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
            for(auto object : *_colliderBodyList)
            {
                ColliderBody *colliderBody = (ColliderBody *)object;
                b2Fixture *fixture = colliderBody->getB2Fixture();

                _body->DestroyFixture(fixture);
                colliderBody->setB2Fixture(nullptr);
            }
        }
    }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (_body)
    {
        if (_active)
        {
            for(auto object : *_colliderBodyList)
            {
                ColliderBody *colliderBody = (ColliderBody *)object;
                cpShape *shape = colliderBody->getShape();
                if(shape->space_private == nullptr)
                {
                    cpSpaceAddShape(_body->space_private, shape);
                }
            }
        }
        else
        {
            for(auto object : *_colliderBodyList)
            {
                ColliderBody *colliderBody = (ColliderBody *)object;
                cpShape *shape = colliderBody->getShape();
                if (shape->space_private != nullptr)
                {
                    cpSpaceRemoveShape(_body->space_private, shape);
                }
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

void ColliderDetector::setColliderFilter(ColliderFilter *filter)
{
    *_filter = *filter;
    
    for(auto object : *_colliderBodyList)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        colliderBody->setColliderFilter(filter);

#if ENABLE_PHYSICS_BOX2D_DETECT
        if (colliderBody->getB2Fixture())
        {
            colliderBody->getColliderFilter()->updateShape(colliderBody->getB2Fixture());
        }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
        if (colliderBody->getShape())
        {
            colliderBody->getColliderFilter()->updateShape(colliderBody->getShape());
        }
#endif
    }
}
ColliderFilter *ColliderDetector::getColliderFilter()
{
    return _filter;
}


Point helpPoint;

void ColliderDetector::updateTransform(AffineTransform &t)
{
    if (!_active)
    {
        return;
    }

    for(auto object : *_colliderBodyList)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        ContourData *contourData = colliderBody->getContourData();

#if ENABLE_PHYSICS_BOX2D_DETECT
        b2PolygonShape *shape = nullptr;
        if (_body != nullptr)
        {
            shape = (b2PolygonShape *)colliderBody->getB2Fixture()->GetShape();
        }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
        cpPolyShape *shape = nullptr;
        if (_body != nullptr)
        {
            shape = (cpPolyShape *)colliderBody->getShape();
        }
#endif

        int num = contourData->vertexList.count();
        ContourVertex2 **vs = (ContourVertex2 **)contourData->vertexList.data->arr;

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
        ContourVertex2 **cvs = (ContourVertex2 **)colliderBody->getCalculatedVertexList()->data->arr;
#endif

        for (int i = 0; i < num; i++)
        {
            helpPoint.setPoint( vs[i]->x,  vs[i]->y);
            helpPoint = PointApplyAffineTransform(helpPoint, t);


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
            cvs[i]->x = helpPoint.x;
            cvs[i]->y = helpPoint.y;
#endif

#if ENABLE_PHYSICS_BOX2D_DETECT
            if (shape != nullptr)
            {
                b2Vec2 &bv = shape->m_vertices[i];
                bv.Set(helpPoint.x / PT_RATIO, helpPoint.y / PT_RATIO);
            }
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
            if (shape != nullptr)
            {
                cpVect v ;
                v.x = helpPoint.x;
                v.y = helpPoint.y;
                shape->verts[i] = v;
            }
#endif
        }

#if ENABLE_PHYSICS_CHIPMUNK_DETECT
        cpConvexHull(num, shape->verts, nullptr, nullptr, 0);
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

    for(auto object : *_colliderBodyList)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        ContourData *contourData = colliderBody->getContourData();
        const Array *array = &contourData->vertexList;
        Object *object = nullptr;

        b2Vec2 *b2bv = new b2Vec2[contourData->vertexList.count()];

        int i = 0;
        for(auto object : *array)
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

        if (colliderBody->getB2Fixture() != nullptr)
        {
            _body->DestroyFixture(colliderBody->getB2Fixture());
        }
        colliderBody->setB2Fixture(fixture);

        colliderBody->getColliderFilter()->updateShape(fixture);
    }
}

b2Body *ColliderDetector::getBody() const
{
    return _body;
}

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
void ColliderDetector::setBody(cpBody *pBody)
{
    _body = pBody;

    for(auto object : *_colliderBodyList)
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

        if (_active)
        {
            cpSpaceAddShape(_body->space_private, shape);
        }

        colliderBody->setShape(shape);
        colliderBody->getColliderFilter()->updateShape(shape);

        delete []verts;
    }
}

cpBody *ColliderDetector::getBody() const
{
    return _body;
}

#endif


}
