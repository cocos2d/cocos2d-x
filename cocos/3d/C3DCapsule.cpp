#include "Base.h"
#include "C3DCapsule.h"

namespace cocos3d
{

    C3DCapsule::C3DCapsule(): _radius(0.0f), _height(0.0f), _vAxisX(1.0f, 0.0f, 0.0f),
    _vAxisY(0.0f, 1.0f, 0.0f), _vAxisZ(0.0f, 0.0f, 1.0f), _vCenter(0.0f, 0.0f, 0.0f)
{
        
}
C3DCapsule::~C3DCapsule()
{
    
}
    
/**
* set capsule z, y axis
*/
void C3DCapsule::setDirAndUp(const C3DVector3& dirz, const C3DVector3& upY)
{
    _vAxisZ = dirz;
	_vAxisZ.normalize();
	_vAxisY = upY;
	_vAxisY.normalize();
    
	C3DVector3::cross(_vAxisY, _vAxisZ, &_vAxisX);
    C3DVector3::cross(_vAxisZ, _vAxisX, &_vAxisY);
}



}