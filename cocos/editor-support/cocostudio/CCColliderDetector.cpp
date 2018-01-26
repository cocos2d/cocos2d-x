/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "editor-support/cocostudio/CCColliderDetector.h"
#include "editor-support/cocostudio/CCBone.h"
#include "editor-support/cocostudio/CCTransformHelp.h"



using namespace cocos2d;

namespace cocostudio {


#if ENABLE_PHYSICS_BOX2D_DETECT
ColliderFilter::ColliderFilter(uint16 categoryBits, uint16 maskBits, int16 groupIndex)
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
ColliderFilter::ColliderFilter(cpCollisionType collisionType, cpGroup group)
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
    _filter = new (std::nothrow) ColliderFilter();

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
    _filter = new (std::nothrow) ColliderFilter();

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    _calculatedVertexList = Array::create();
    CC_SAFE_RETAIN(_calculatedVertexList);
#endif
}
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
ColliderBody::ColliderBody(ContourData *contourData)
    : _contourData(contourData)
{
    CC_SAFE_RETAIN(_contourData);
}
#endif

ColliderBody::~ColliderBody()
{
    CC_SAFE_RELEASE(_contourData);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SAFE_DELETE(_filter);
#endif
}

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
void ColliderBody::setColliderFilter(ColliderFilter *filter)
{
    *_filter = *filter;
}
ColliderFilter *ColliderBody::getColliderFilter()
{
    return _filter;
}
#endif



ColliderDetector *ColliderDetector::create()
{
    ColliderDetector *pColliderDetector = new (std::nothrow) ColliderDetector();
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
    ColliderDetector *pColliderDetector = new (std::nothrow) ColliderDetector();
    if (pColliderDetector && pColliderDetector->init(bone))
    {
        pColliderDetector->autorelease();
        return pColliderDetector;
    }
    CC_SAFE_DELETE(pColliderDetector);
    return nullptr;
}

ColliderDetector::ColliderDetector()
    :  _active(false)
{
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    _body = nullptr;
    _filter = nullptr;
#endif
}

ColliderDetector::~ColliderDetector()
{
    _colliderBodyList.clear();

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    CC_SAFE_DELETE(_filter);
#endif
}

bool ColliderDetector::init()
{
    _colliderBodyList.clear();

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    _filter = new (std::nothrow) ColliderFilter();
#endif

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
    ColliderBody *colliderBody = new (std::nothrow) ColliderBody(contourData);
    _colliderBodyList.pushBack(colliderBody);
    colliderBody->release();


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    std::vector<Vec2> &calculatedVertexList = colliderBody->_calculatedVertexList;
    
    unsigned long num = contourData->vertexList.size();
    for (unsigned long i = 0; i < num; i++)
    {
        calculatedVertexList.push_back(Vec2());
    }
#endif
}

void ColliderDetector::addContourDataList(cocos2d::Vector<ContourData*> &contourDataList)
{
    for (const auto &contourData : contourDataList)
    {
        this->addContourData(contourData);
    }
}

void ColliderDetector::removeContourData(ContourData *contourData)
{
    std::vector<ColliderBody*> eraseList;
    
    for (const auto &body : _colliderBodyList)
    {
		if (body && body->getContourData() == contourData)
		{
            eraseList.push_back(body);
		}
    }
    
    for (const auto &body : eraseList)
    {
        this->_colliderBodyList.eraseObject(body);
    }
}

void ColliderDetector::removeAll()
{
    _colliderBodyList.clear();
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
            for(auto& object : _colliderBodyList)
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
            for(auto& object : _colliderBodyList)
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
            for(auto& object : _colliderBodyList)
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

const cocos2d::Vector<ColliderBody*>& ColliderDetector::getColliderBodyList()
{
    return _colliderBodyList;
}


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
void ColliderDetector::setColliderFilter(ColliderFilter *filter)
{
    *_filter = *filter;
    
    for(auto& object : _colliderBodyList)
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
#endif


Vec2 helpPoint;

void ColliderDetector::updateTransform(Mat4 &t)
{
    if (!_active)
    {
        return;
    }

    for(auto& object : _colliderBodyList)
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

        unsigned long num = contourData->vertexList.size();
        std::vector<cocos2d::Vec2> &vs = contourData->vertexList;

#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
        std::vector<cocos2d::Vec2> &cvs = colliderBody->_calculatedVertexList;
#endif

        for (unsigned long i = 0; i < num; i++)
        {
            helpPoint.setPoint( vs.at(i).x,  vs.at(i).y);
            helpPoint = PointApplyTransform(helpPoint, t);


#if ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
            cvs.at(i).x = helpPoint.x;
            cvs.at(i).y = helpPoint.y;
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
        cpConvexHull((int)num, shape->verts, nullptr, nullptr, 0);
        for (unsigned long i = 0; i < num; i++)
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

    for(auto& object : _colliderBodyList)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        ContourData *contourData = colliderBody->getContourData();
        
        b2Vec2 *b2bv = new (std::nothrow) b2Vec2[contourData->vertexList.size()];

        int i = 0;
        for(auto& v : contourData->vertexList)
        {
            b2bv[i].Set(v.x / PT_RATIO, v.y / PT_RATIO);
            i++;
        }

        b2PolygonShape polygon;
        polygon.Set(b2bv, (int)contourData->vertexList.size());

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

    for(auto& object : _colliderBodyList)
    {
        ColliderBody *colliderBody = (ColliderBody *)object;

        ContourData *contourData = colliderBody->getContourData();

        ssize_t num = contourData->vertexList.size();
        auto vs = contourData->vertexList;
        cpVect *verts = new (std::nothrow) cpVect[num];
        for (int i = 0; i < num; i++)
        {
            verts[num - 1 - i].x = vs.at(i).x;
            verts[num - 1 - i].y = vs.at(i).y;
        }

        cpShape *shape = cpPolyShapeNew(_body, (int)num, verts, cpvzero);

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
