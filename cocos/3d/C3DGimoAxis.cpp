#include "C3DGimoAxis.h"
#include "ccMacros.h"
#include "Vertex.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DMatrix.h"
#include "C3DVertexFormat.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DMaterial.h"
#include "C3DVertexDeclaration.h"
#include "C3DModel.h"
#include "C3DScene.h"
#include "C3DRay.h"
#include "C3DRenderSystem.h"
#include "C3DCamera.h"
#include "C3DPlane.h"
#include "C3DScene.h"
#include "C3DCylinder.h"
#include "Geo.h"
#include "C3DCone.h"

namespace cocos3d
{
	
const float fCyLinderLengh = 1.f;
const float fCyLinderHalfLengh = fCyLinderLengh / 2.f;
const float fCyLinderRadius = 0.1f;
const float fConeRadius = fCyLinderRadius;

C3DGimoAxis::C3DGimoAxis(C3DNode* parent)
:m_pParentNode(parent),
m_Position(C3DVector3::zero()),
m_SelectAxis(AXIS_SELECT_NONE)
{
	
}

C3DGimoAxis::~C3DGimoAxis()
{
}

void C3DGimoAxis::draw()const
{

}

void C3DGimoAxis::addLine(std::vector< BBVertex >& VerticesBuffer, 
								std::vector< unsigned short >& IndicesBuffer,
								const C3DVector3& pos0, 
								const C3DVector3& pos1,
								const C3DVector4& color)
{
	unsigned int	vertexBase = VerticesBuffer.size();
	unsigned int	indexBase  = IndicesBuffer.size();

	BBVertex vert;
	vert.position = pos0;
	vert.color = color;
	VerticesBuffer.push_back(vert);
	vert.position = pos1;
	vert.color = color;
	VerticesBuffer.push_back(vert);

	IndicesBuffer.push_back(vertexBase);
	IndicesBuffer.push_back(vertexBase + 1);
}

void C3DGimoAxis::addTrangle(std::vector< BBVertex >& VerticesBuffer, 
									std::vector< unsigned short >& IndicesBuffer,
									const C3DVector3& pos0, 
									const C3DVector3& pos1, 
									const C3DVector3& pos2, 
									const C3DVector4& color)
{
	unsigned int	vertexBase = VerticesBuffer.size();
	unsigned int	indexBase  = IndicesBuffer.size();

	BBVertex vert;
	vert.position = pos0;
	vert.color = color;
	VerticesBuffer.push_back(vert);
	vert.position = pos1;
	vert.color = color;
	VerticesBuffer.push_back(vert);
	vert.position = pos2;
	vert.color = color;
	VerticesBuffer.push_back(vert);

	IndicesBuffer.push_back(vertexBase);
	IndicesBuffer.push_back(vertexBase + 1);
	IndicesBuffer.push_back(vertexBase + 2);
}

void C3DGimoAxis::addCone( std::vector< BBVertex >& VerticesBuffer, 
								std::vector< unsigned short >& IndicesBuffer,
								const C3DVector3& pos, 
								float radius, 
								float length, 
								bool cap, 
								const C3DVector4& color, 
								const C3DMatrix& transform )
{
	radius = fabsf(radius);
	unsigned int vertexBase = VerticesBuffer.size();

	bool invert = length < 0;

	C3DVector3 vDir = C3DVector3::unitZ();
	transform.transformVector(&vDir);
	vDir.normalize();

	BBVertex vert;
	vert.position = pos + vDir * length;
	vert.color = color;

	VerticesBuffer.push_back(vert);

	C3DVector3 offset = C3DVector3(radius,0,0);
	transform.transformVector(&offset);
	offset.normalize();

	C3DMatrix m;
	C3DMatrix::createRotation(vDir, CC_DEGREES_TO_RADIANS(10), &m);

	for (int i = 0; i < 36;i++)
	{
		vert.position = pos + offset * radius;

		VerticesBuffer.push_back(vert);
		m.transformVector(offset, &offset);
	}

	for (int i = 0; i < 36; i++)
	{
		IndicesBuffer.push_back( vertexBase );
		if (!invert)
		{
			IndicesBuffer.push_back( vertexBase + 1 + i);
			IndicesBuffer.push_back( vertexBase + 1 + ((i+1) % 36) );
		}
		else
		{
			IndicesBuffer.push_back( vertexBase + 1 + ((i+1) % 36) );
			IndicesBuffer.push_back( vertexBase + 1 + i);
		}
	}

	if (cap)
	{
		vertexBase = VerticesBuffer.size();
		for (int i = 0; i < 36;i++)
		{
			vert.position = pos + offset* radius;
			VerticesBuffer.push_back(vert);
			m.transformVector(offset, &offset);
		}

		for (int i = 0; i < 35; i++)
		{
			IndicesBuffer.push_back( vertexBase );
			if (invert)
			{
				IndicesBuffer.push_back( vertexBase + 1 + i);
				IndicesBuffer.push_back( vertexBase + 1 + ((i+1) % 35) );
			}
			else
			{
				IndicesBuffer.push_back( vertexBase + 1 + ((i+1) % 35) );
				IndicesBuffer.push_back( vertexBase + 1 + i);
			}
		}
	}
}

void C3DGimoAxis::setPosition(const C3DVector3& pos)
{
	m_Position = pos;
	updateGimo();
}

C3DVector3 C3DGimoAxis::getPosition()
{
	return m_Position;
}

void C3DGimoAxis::resetAxis()
{
	resetColor();
	resetSelectFace();
}

bool C3DGimoAxis::pick(int x, int y)
{
	return false;
}

bool C3DGimoAxis::onSelectedAxisX()
{
	if (m_SelectAxis == AXIS_SELECT_X)
		return false;

	m_SelectAxis = AXIS_SELECT_X;
	return true;
}

bool C3DGimoAxis::onSelectedAxisY()
{
	if (m_SelectAxis == AXIS_SELECT_Y)
		return false;

	m_SelectAxis = AXIS_SELECT_Y;
	return true;
}

bool C3DGimoAxis::onSelectedAxisZ()
{
	if (m_SelectAxis == AXIS_SELECT_Z)
		return false;

	m_SelectAxis = AXIS_SELECT_Z;
	return true;
}

bool C3DGimoAxis::onSelectedNone()
{
	if (m_SelectAxis == AXIS_SELECT_NONE)
		return false;

	m_SelectAxis = AXIS_SELECT_NONE;
	resetAxis();
	return true;
}

void C3DGimoAxis::setMeshColor(std::vector< BBVertex >& VertexBuffer, C3DMesh* pMesh, unsigned int nBaseIndex, unsigned int nVertexNum, const C3DVector4& color)
{
	assert(pMesh);
	if (!pMesh) return;

	int nEnd = nBaseIndex + nVertexNum;
	for (int i = nBaseIndex; i < nEnd; i++)
	{
		VertexBuffer[i].color = color;
	}
	pMesh->setVertexData(&VertexBuffer[nBaseIndex], nBaseIndex, nVertexNum);
}

bool C3DGimoAxis::pointInPolygon(const C3DVector3& point, const std::vector<C3DVector3>& points)const
{
	C3DVector3 vOldNormal = C3DVector3::zero();
	C3DVector3 vNewNormal = C3DVector3::zero();
	for (unsigned int i = 0; i < points.size(); i++)
	{
		C3DVector3 vec0;
		C3DVector3 vec1;
		if (i + 1 < points.size())
		{
			vec0 = points[i];
			vec1 = points[i + 1];
		}
		else
		{
			vec0 = points[i];
			vec1 = points[0];
		}

		C3DVector3 vEdge = vec1 - vec0;
		C3DVector3 vDest = point - vec0;;
		C3DVector3::cross(vDest, vEdge, &vNewNormal);
		vNewNormal.normalize();

		float a = C3DVector3::dot(vNewNormal, vOldNormal);
		if ((vOldNormal != C3DVector3::zero()) && a < 0)
		{
			return false;
		}
		vOldNormal = vNewNormal;
			
	}
	return true;
}


}