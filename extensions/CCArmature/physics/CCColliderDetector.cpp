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
#include "CCPhysicsWorld.h"
#include "../CCBone.h"
#include "Box2D/Box2D.h"

namespace cocos2d { namespace extension { namespace armature {

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
{
}

ColliderDetector::~ColliderDetector()
{
    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = static_cast<ColliderBody *>(object);

        b2Body *body = colliderBody->getB2Body();
        PhysicsWorld::sharedPhysicsWorld()->getNoGravityWorld()->DestroyBody(body);
    }


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
    const Array *array = &contourData->vertexList;
    Object *object = NULL;

    b2Vec2 *b2bv = new b2Vec2[contourData->vertexList.count()];

    int i = 0;
    CCARRAY_FOREACH(array, object)
    {
        ContourVertex2F *v = static_cast<ContourVertex2F *>(object);
        b2bv[i].Set(v->x / PT_RATIO, v->y / PT_RATIO);
        i++;
    }

    b2PolygonShape polygon;
    polygon.Set(b2bv, contourData->vertexList.count());

    CC_SAFE_DELETE(b2bv);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 10.0f;
    fixtureDef.isSensor = true;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(0.0f, 0.0f);
    bodyDef.userData = _bone;

    b2Body *body = PhysicsWorld::sharedPhysicsWorld()->getNoGravityWorld()->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);

    ColliderBody *colliderBody = new ColliderBody(body, contourData);
    _colliderBodyList->addObject(colliderBody);
    colliderBody->release();
}

void ColliderDetector::addContourDataList(Array *contourDataList)
{
    Object *object = NULL;
    CCARRAY_FOREACH(contourDataList, object)
    {
        addContourData(static_cast<ContourData *>(object));
    }
}

void ColliderDetector::removeContourData(ContourData *_contourData)
{
    _colliderBodyList->removeObject(_contourData);
}

void ColliderDetector::removeAll()
{
    _colliderBodyList->removeAllObjects();
}

void ColliderDetector::setColliderFilter(b2Filter &filter)
{
    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = static_cast<ColliderBody *>(object);
        colliderBody->getB2Body()->GetFixtureList()->SetFilterData(filter);
    }
}

void ColliderDetector::setActive(bool active)
{
    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = static_cast<ColliderBody *>(object);
        colliderBody->getB2Body()->SetActive(active);
    }
}

Point helpPoint;

void ColliderDetector::updateTransform(AffineTransform &t)
{
    Object *object = NULL;
    CCARRAY_FOREACH(_colliderBodyList, object)
    {
        ColliderBody *colliderBody = static_cast<ColliderBody *>(object);

        ContourData *contourData = colliderBody->getContourData();
        b2Body *body = colliderBody->getB2Body();

        b2PolygonShape *shape = (b2PolygonShape *)body->GetFixtureList()->GetShape();

        //! update every vertex
        const Array *array = &contourData->vertexList;
        Object *object = NULL;
        int i = 0;
        CCARRAY_FOREACH(array, object)
        {
            ContourVertex2F *cv = static_cast<ContourVertex2F *>(object);
            b2Vec2 &bv = shape->m_vertices[i];

            helpPoint.setPoint(cv->x, cv->y);
            helpPoint = PointApplyAffineTransform(helpPoint, t);

            bv.Set(helpPoint.x / PT_RATIO, helpPoint.y / PT_RATIO);

            i++;
        }
    }
}



}}} // namespace cocos2d { namespace extension { namespace armature {
