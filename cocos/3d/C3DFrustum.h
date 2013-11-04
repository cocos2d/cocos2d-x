#ifndef C3DFRUSTUM_H_
#define C3DFRUSTUM_H_

#include "C3DAABB.h"
#include "C3DOBB.h"
#include "C3DPlane.h"

namespace cocos3d
{

    class C3DCamera;
    /**
	* Defines a 3-dimensional frustum.
	*/
	/**
	Defines a frustum created from camera
	It is used for camera culling 
	*/
    class C3DFrustum
    {
    public:
        /**
		 * Constructor & Destructor.
		 */
        C3DFrustum(): _bInit(false), _bClipZ(false){}
		~C3DFrustum(){}
        
		/**
		 * init frustum from camera.
		 */
        bool initFrustum(C3DCamera* pCamera);

		/**
		 * is aabb out of frustum.
		 */
        bool isOutFrustum(const C3DAABB& aabb) const;
		/**
		 * is obb out of frustum
		 */
        bool isOutFrustum(const C3DOBB& obb) const;
        
		/**
		 * get & set z clip. if bclipZ == true use near and far plane
		 */
        void setClipZ(bool bclipZ) { _bClipZ = bclipZ; }
        bool isClipZ() { return _bClipZ; }
        
    protected:
		/**
		 * create clip plane
		 */
        void createPersPlane(C3DCamera* pcamera);
        void createOrthPlane(C3DCamera* pcamera);
        
        C3DPlane _plane[6];// clip plane, left, right, top, bottom, near, far
        bool _bClipZ;//use near and far clip plane
        bool _bInit;
    };

}

#endif
