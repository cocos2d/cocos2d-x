#include "Base.h"
#include "C3DFrustum.h"
#include "C3DCamera.h"

namespace cocos3d
{



    bool C3DFrustum::initFrustum(C3DCamera* pCamera)
    {
        
        _bInit = true;
        C3DCamera::Type type = pCamera->getCameraType();
        
        switch (type) {
            case C3DCamera::PERSPECTIVE:
                createPersPlane(pCamera);
                break;
            case C3DCamera::ORTHOGRAPHIC:
                createOrthPlane(pCamera);
                break;
                
            default:
                _bInit = false;
                return false;
        }
        return true;
    }
    bool C3DFrustum::isOutFrustum(const C3DAABB& aabb) const
    {
        if (_bInit)
        {
            C3DVector3 point;
            
            int nplane = _bClipZ ? 6 : 4;
            for (int i = 0; i < nplane; i++) {
                const C3DVector3& normal = _plane[i].getNormal();
                point.x = normal.x < 0 ? aabb._max.x : aabb._min.x;
                point.y = normal.y < 0 ? aabb._max.y : aabb._min.y;
                point.z = normal.z < 0 ? aabb._max.z : aabb._min.z;
                if (_plane[i].pointClassify(point) == C3DPlane::FRONT_PLANE )//kmPlaneClassifyPoint(&_plane[i], &point) == POINT_INFRONT_OF_PLANE)
                    return true;
            }
        }
        return false;
    }
    
    bool C3DFrustum::isOutFrustum(const C3DOBB& obb) const
    {
        if (_bInit)
        {
            C3DVector3 point;
            
            int nplane = _bClipZ ? 6 : 4;
            
            for (int i = 0; i < nplane; i++) {
                const C3DVector3& normal = _plane[i].getNormal();
                
                point = obb.center;
                point = normal.dot(obb.xAxis) > 0 ? point - obb.extX : point + obb.extX;//obb.xAxis.dot()
                point = normal.dot(obb.yAxis) > 0 ? point - obb.extY : point + obb.extY;
                point = normal.dot(obb.zAxis) > 0 ? point - obb.extZ : point + obb.extZ;
                
                if (_plane[i].pointClassify(point) == C3DPlane::FRONT_PLANE )//kmPlaneClassifyPoint(&_plane[i], &point) == POINT_INFRONT_OF_PLANE)
                    return true;
            }
        }
        return  false;
    }
    
    void C3DFrustum::createOrthPlane(C3DCamera* pcamera)
    {
        const C3DMatrix& invmat = pcamera->getInverseViewProjectionMatrix();
        C3DVector3 n, point;
        C3DVector4 pos;
        
        pos.set(-1.0f, 0.0f, 0.0f, 1.0f);
        invmat.transformVector(pos, &pos);
        n.set(-1.0f, 0.0f, 0.0f);
        invmat.transformVector(&n);
        point.set(pos.x, pos.y, pos.z);
        _plane[0].initPlane(n, point);
        
        pos.set(1.0f, 0.0f, 0.0f, 1.0f);
        invmat.transformVector(pos, &pos);
        n.set(1.0f, 0.0f, 0.0f);
        invmat.transformVector(&n);
        point.set(pos.x, pos.y, pos.z);
        _plane[1].initPlane(n, point);
        
        pos.set(0.0f, 1.0f, 0.0f, 1.0f);
        invmat.transformVector(pos, &pos);
        n.set(0.0f, 1.0f, 0.0f);
        invmat.transformVector(&n);
        point.set(pos.x, pos.y, pos.z);
        _plane[2].initPlane(n, point);
        
        pos.set(0.0f, -1.0f, 0.0f, 1.0f);
        invmat.transformVector(pos, &pos);
        n.set(0.0f, -1.0f, 0.0f);
        invmat.transformVector(&n);
        point.set(pos.x, pos.y, pos.z);
        _plane[3].initPlane(n, point);
        
        if (_bClipZ)
        {
//            pos.set(0.0f, 0.0f, -1.0f, 1.0f);
//            invmat.transformVector(pos, &pos);
//            n.set(0.0f, 0.0f, -1.0f);
//            invmat.transformVector(&n);
//            point.set(pos.x, pos.y, pos.z);
//            _plane[4].initPlane(n, point);
//            
//            pos.set(0.0f, 0.0f, 1.0f, 1.0f);
//            invmat.transformVector(pos, &pos);
//            n.set(0.0f, 0.0f, 1.0f);
//            invmat.transformVector(&n);
//            point.set(pos.x, pos.y, pos.z);
//            _plane[5].initPlane(n, point);
            
            C3DVector3 dir = pcamera->getForwardVector();
            dir.normalize();
            C3DVector3 nearpos = pcamera->getTranslationWorld() + dir * pcamera->getNearPlane();
            //invmat.transformVector(&n);
            _plane[4].initPlane(-dir, nearpos);
            
            //n.set(0.0f, 0.0f, -1.0f);
            //invmat.transformVector(&n);
            C3DVector3 farpos = pcamera->getTranslationWorld() + dir * pcamera->getFarPlane();
            _plane[5].initPlane(dir, farpos);
        }
        
    }
    
    void C3DFrustum::createPersPlane(C3DCamera* pcamera)
    {
        float fov = pcamera->getFieldOfView(), aspect = pcamera->getAspectRatio();
        
        float c, s, fAngle = CC_DEGREES_TO_RADIANS(fov * 0.5f);
        
        c = (float)cos(fAngle);
        s = (float)sin(fAngle);
        
        C3DVector3 pos = pcamera->getTranslationWorld();
        C3DVector3 n;
        C3DMatrix invmat = pcamera->getInverseViewMatrix();
        
        n.set(0.0f, c, s);
        invmat.transformVector(&n);
        _plane[2].initPlane(n, pos);

        
        n.set(0.0f, -c, s);
        invmat.transformVector(&n);
        _plane[3].initPlane(n, pos);
    
        
        fAngle = (float)(tan(fAngle) * aspect);
        
        c = (float)cos(atan(fAngle));
        s = (float)sin(atan(fAngle));
        
        n.set(-c, 0.0f, s);
        invmat.transformVector(&n);
        _plane[0].initPlane(n, pos);
        
        n.set(c, 0.0f, s);
        invmat.transformVector(&n);
        _plane[1].initPlane(n, pos);
        
        if (_bClipZ)
        {
            //n.set(0.0f, 0.0f, 1.0f);
            C3DVector3 dir = pcamera->getForwardVector();
            dir.normalize();
            C3DVector3 nearpos = pos + dir * pcamera->getNearPlane();
            //invmat.transformVector(&n);
            _plane[4].initPlane(-dir, nearpos);
            
            //n.set(0.0f, 0.0f, -1.0f);
            //invmat.transformVector(&n);
            C3DVector3 farpos = pos + dir * pcamera->getFarPlane();
            _plane[5].initPlane(dir, farpos);
        }
        
    }

}
