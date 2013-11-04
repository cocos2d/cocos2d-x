#include "Base.h"
#include "C3DPlane.h"
#include "C3DMesh.h"


namespace cocos3d
{

    float C3DPlane::s_fOnPlaneErr = 0.001f;
    
    void C3DPlane::setOnPlaneErr(float fError)
    {
        s_fOnPlaneErr = fabs(fError);
    }

C3DPlane::C3DPlane()
    {
        m_vNormal.set(0.0f, 0.0f, 1.0f);
        m_fDist = 0.0f;
    }
// create plane from tree point
C3DPlane::C3DPlane(const C3DVector3& p1, const C3DVector3& p2, const C3DVector3& p3)
    {
        initPlane(p1, p2, p3);
    }
// create plane from normal and dist
C3DPlane::C3DPlane(const C3DVector3& normal, float dist)
    {
        initPlane(normal, dist);
    }
// create plane from normal and a point on plane
C3DPlane::C3DPlane(const C3DVector3& normal, const C3DVector3& point)
    {
        initPlane(normal, point);
    }
C3DPlane::~C3DPlane()
    {
        
    }
    
void C3DPlane::initPlane(const C3DVector3& p1, const C3DVector3& p2, const C3DVector3& p3)
    {
        C3DVector3 p21 = p2 - p1;
        C3DVector3 p32 = p3 - p2;
        
        C3DVector3::cross(p21, p32, &m_vNormal);
       
        m_vNormal.normalize();
        m_fDist = m_vNormal.dot(p1);
    }
void C3DPlane::initPlane(const C3DVector3& normal, float dist)
    {
        m_vNormal = normal;
        m_vNormal.normalize();
        m_fDist = dist;
    }
void C3DPlane::initPlane(const C3DVector3& normal, const C3DVector3& point)
    {
        m_vNormal = normal;
        m_vNormal.normalize();
        m_fDist = m_vNormal.dot(point);
    }

float C3DPlane::dist2Plane(const C3DVector3& p) const
    {
        return m_vNormal.dot(p) - m_fDist;
    }
void C3DPlane::setNormal(const C3DVector3& noraml)
    {
        m_vNormal = noraml;
        m_vNormal.normalize();
    }
C3DPlane::POINT_CLASSIFICATION C3DPlane::pointClassify(const C3DVector3& point) const
    {
        float dist = dist2Plane(point);
        if (dist > s_fOnPlaneErr)
            return C3DPlane::FRONT_PLANE;
        else if (dist < -s_fOnPlaneErr)
            return C3DPlane::BEHIND_PLANE;
        
        return C3DPlane::ON_PLANE;
    }

}
