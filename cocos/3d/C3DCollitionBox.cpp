#include "Base.h"
#include "C3DCollitionBox.h"
#include "C3DRenderNode.h"
#include "C3DSprite.h"

namespace cocos3d
{


	C3DCollitionBox::C3DCollitionBox(C3DRenderNode* pRenderNode, const std::string& strBone, const C3DVector3& offset, float fRadius)
		:m_pParentNode(pRenderNode),
		m_strBone(strBone),
		m_fRadius(fRadius),
		m_fScale(1.f),
		m_Rotate(C3DQuaternion::zero()),
		m_LocalPos(offset),
		m_WorldPos(C3DVector3::zero()),
		_min(C3DVector3::zero()),
		_max(C3DVector3::zero())
	{
		assert(m_pParentNode);
		update();
	}

	float C3DCollitionBox::getRadius()
	{
		float fRadius = getScale() * m_fRadius;
		return fRadius;
	}

	C3DVector3 C3DCollitionBox::getLocalPos()
	{
		return m_LocalPos;
	}

	C3DVector3 C3DCollitionBox::getWorldPos()
	{
		C3DVector3 tmpWorldPos = getParentPos() + m_Rotate * m_LocalPos * getScale();
		return tmpWorldPos;
	}
	void C3DCollitionBox::getCorners(C3DVector3* dst) const
	{
		assert(dst);

		// Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
		// Left-top-front.
		dst[0].set(_min.x, _max.y, _max.z);
		// Left-bottom-front.
		dst[1].set(_min.x, _min.y, _max.z);
		// Right-bottom-front.
		dst[2].set(_max.x, _min.y, _max.z);
		// Right-top-front.
		dst[3].set(_max.x, _max.y, _max.z);

		// Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
		// Right-top-back.
		dst[4].set(_max.x, _max.y, _min.z);
		// Right-bottom-back.
		dst[5].set(_max.x, _min.y, _min.z);
		// Left-bottom-back.
		dst[6].set(_min.x, _min.y, _min.z);
		// Left-top-back.
		dst[7].set(_min.x, _max.y, _min.z);
	}

	void C3DCollitionBox::update()
	{
		rotate(m_pParentNode->getRotation());
		C3DVector3 vOffset = C3DVector3(getRadius(), getRadius(), getRadius());
		C3DVector3 vWorldPos = getWorldPos();
		_min = vWorldPos - vOffset;
		_max = vWorldPos + vOffset;
	}

	void C3DCollitionBox::translate(float cx, float cy, float cz)
	{
		C3DVector3 offset = C3DVector3(cx, cy, cz);
		m_LocalPos += offset;
	}

	void C3DCollitionBox::rotate(const C3DQuaternion& rotate)
	{
		m_Rotate = rotate;
	}

	void C3DCollitionBox::scale(float fScale)
	{
		m_fScale = fScale;
	}

	float C3DCollitionBox::getScale()
	{
		return m_fScale + (m_pParentNode->getScale().x - 1.f);
	}

	float C3DCollitionBox::getScaleLocal()
	{
		return m_fScale;
	}

	const C3DVector3 C3DCollitionBox::getParentPos()const
	{
		if (m_strBone == "")
		{
			return m_pParentNode->getPosition();
		}
		else
		{
			C3DBone* tpBone = static_cast<C3DSprite*>(m_pParentNode)->getBone(m_strBone.c_str());
			assert(tpBone);
			if (!tpBone) return C3DVector3::zero();

			C3DMatrix matChild = tpBone->getWorldMatrix();
			C3DVector3 vChildPos;
			matChild.getPosition(&vChildPos);

			return vChildPos;
		}
	}


}
