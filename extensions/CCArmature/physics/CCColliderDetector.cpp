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
{
}

CCColliderDetector::~CCColliderDetector()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pColliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        b2Body *body = colliderBody->getB2Body();
        CCPhysicsWorld::sharedPhysicsWorld()->getNoGravityWorld()->DestroyBody(body);
    }


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
    fixtureDef.density = 10.0f;
    fixtureDef.isSensor = true;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(0.0f, 0.0f);
    bodyDef.userData = m_pBone;

    b2Body *body = CCPhysicsWorld::sharedPhysicsWorld()->getNoGravityWorld()->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);

    ColliderBody *colliderBody = new ColliderBody(body, contourData);
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

void CCColliderDetector::setColliderFilter(b2Filter &filter)
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pColliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        colliderBody->getB2Body()->GetFixtureList()->SetFilterData(filter);
    }
}

void CCColliderDetector::setActive(bool active)
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pColliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;
        colliderBody->getB2Body()->SetActive(active);
    }
}

CCPoint helpPoint;

void CCColliderDetector::updateTransform(CCAffineTransform &t)
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pColliderBodyList, object)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        CCContourData *contourData = colliderBody->getContourData();
        b2Body *body = colliderBody->getB2Body();

        b2PolygonShape *shape = (b2PolygonShape *)body->GetFixtureList()->GetShape();

        //! update every vertex
        const CCArray *array = &contourData->vertexList;
        CCObject *object = NULL;
        int i = 0;
        CCARRAY_FOREACH(array, object)
        {
            CCContourVertex2 *cv = (CCContourVertex2 *)object;
            b2Vec2 &bv = shape->m_vertices[i];

            helpPoint.setPoint(cv->x, cv->y);
            helpPoint = CCPointApplyAffineTransform(helpPoint, t);

            bv.Set(helpPoint.x / PT_RATIO, helpPoint.y / PT_RATIO);

            i++;
        }
    }
}



NS_CC_EXT_END
