#ifndef COLLITIONBOX_H_
#define COLLITIONBOX_H_
#include "C3DVector3.h"
#include "C3DMatrix.h"
#include "C3DNode.h"

namespace cocos3d
{

class C3DRenderNode;
class C3DCollitionBox
{
public:
	/**
     * Constructor.
     */
    C3DCollitionBox(C3DRenderNode* pRender, const std::string& strBoneName = "", const C3DVector3& offset = C3DVector3::zero(), float fRadius = 1.f);
	
	std::string getBone(){return m_strBone;}
    
	float getRadius();

	C3DVector3 getLocalPos();

	C3DVector3 getWorldPos();
	
	void getCorners(C3DVector3* dst) const;

	void update();

	// is a relative pos
	void translate(float cx, float cy, float cz);

	void rotate(const C3DQuaternion& rotate);

	void scale(float fScale);
	float getScale();
	float getScaleLocal();

	C3DVector3 getMin(){return _min;}
	C3DVector3 getMax(){return _max;}

protected:
	C3DCollitionBox(){}
	const C3DVector3 getParentPos()const;

protected:
	C3DRenderNode* m_pParentNode;
	std::string m_strBone;
	float m_fRadius;
	float m_fScale;
	C3DQuaternion m_Rotate;
	C3DVector3 m_LocalPos;
	C3DVector3 m_WorldPos;
	C3DVector3 _min;
	C3DVector3 _max;
	
};


}



#endif//COLLITIONBOX_H_
