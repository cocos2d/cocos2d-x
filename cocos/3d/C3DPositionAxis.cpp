#include "C3DPositionAxis.h"
#include "ccMacros.h"
#include "Vertex.h"
#include "C3DVector3.h"
#include "C3DVector4.h"
#include "C3DMatrix.h"
#include "C3DVertexFormat.h"
#include "C3DMesh.h"
#include "MeshPart.h"
#include "C3DMaterial.h"
#include "C3DPass.h"
#include "C3DTechnique.h"
#include "C3DVertexDeclaration.h"
#include "C3DModel.h"
#include "C3DModelNode.h"
#include "C3DScene.h"
#include "C3DRay.h"
#include "C3DRenderSystem.h"
#include "C3DCamera.h"
#include "C3DPlane.h"
#include "C3DScene.h"
#include "C3DCylinder.h"
#include "Geo.h"
#include "C3DCone.h"
#include "C3DMaterialManager.h"

namespace cocos3d
{
	
const float fCyLinderLengh = 1.f;
const float fCyLinderHalfLengh = fCyLinderLengh / 2.f;
const float fCyLinderRadius = 0.1f;
const float fConeRadius = fCyLinderRadius;
const float fConeHeight = fConeRadius * 3.f;
const float fEdge0 = fConeRadius * 3.f;

C3DPositionAxis::C3DPositionAxis(C3DNode* parent)
:C3DGimoAxis(parent),
m_pBaseMesh(0),
m_pSelectedMesh(0),
m_pBaseModelNode(0),
m_pSelectedModelNode(0),
m_pParentNode(parent),
m_nBaseIndexLineX(0),
m_nBaseIndexLineY(0),
m_nBaseIndexLineZ(0),
m_nBaseIndexLineXY(0),
m_nBaseIndexLineXZ(0),
m_nBaseIndexLineYX(0),
m_nBaseIndexLineYZ(0),
m_nBaseIndexLineZX(0),
m_nBaseIndexLineZY(0),
m_pCylinderX(0),
m_pCylinderY(0),
m_pCylinderZ(0),
m_pConeX(0)
{
	m_AxisType = AXIS_TYPE_POSITION;
	updateGimo();
	buildBaseAxisMesh();
	buildBaseAxisShape();
}

C3DPositionAxis::~C3DPositionAxis()
{
	m_pParentNode->removeChild(m_pBaseModelNode);
	m_pParentNode->removeChild(m_pSelectedModelNode);
	SAFE_DELETE(m_pCylinderX);
	SAFE_DELETE(m_pCylinderY);
	SAFE_DELETE(m_pCylinderZ);
}

void C3DPositionAxis::updateGimo()
{
	m_OriginPoint.clear();
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, 0));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge0, 0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fEdge0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, fEdge0));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fCyLinderLengh, 0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fCyLinderLengh, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, fCyLinderLengh));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge0, fEdge0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge0, 0, fEdge0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fEdge0, fEdge0));

	m_XYPoints.clear();
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_ZERO]);
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_X0]);
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_X0Y0]);
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_Y0]);

	m_XZPoints.clear();
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_ZERO]);
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_X0]);
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_X0Z0]);
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_Z0]);

	m_YZPoints.clear();
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_ZERO]);
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Y0]);
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Y0Z0]);
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Z0]);

	if (m_pBaseModelNode)
		m_pBaseModelNode->setPosition(getPosition());

	if (m_pSelectedModelNode)
		m_pSelectedModelNode->setPosition(getPosition());

	if (m_pCylinderX) 
		m_pCylinderX->setPosition(C3DVector3(m_Position.x + (fCyLinderLengh + fConeHeight) / 2.f, m_Position.y, m_Position.z));

	if (m_pCylinderY)
		m_pCylinderY->setPosition(C3DVector3(m_Position.x, m_Position.y + (fCyLinderLengh + fConeHeight) / 2.f, m_Position.z));

	if (m_pCylinderZ)
		m_pCylinderZ->setPosition(C3DVector3(m_Position.x, m_Position.y, m_Position.z + (fCyLinderLengh + fConeHeight) / 2.f)); 
}

bool C3DPositionAxis::pick(int x, int y)
{
	if (!m_pParentNode)
		return false;

	C3DRay ray;
	if (m_pParentNode->getScene() && m_pParentNode->getScene()->getActiveCamera())
	{
		m_pParentNode->getScene()->getActiveCamera()->getAxes(C3DRenderSystem::getInstance()->getViewport(), x, y, &ray);
	}

	onSelectedNone();
	if (intersectXY(&ray))
	{
		onSelectedAxisXY();
	}
	else if (intersectXZ(&ray))
	{
		onSelectedAxisXZ();
	}
	else if (intersectYZ(&ray))
	{
		onSelectedAxisYZ();
	}
	else if (intersectX(&ray))
	{
		onSelectedAxisX();
	}
	else if (intersectY(&ray))
	{
		onSelectedAxisY();
	}
	else if (intersectZ(&ray))
	{
		onSelectedAxisZ();
	}
	return true;
}

void C3DPositionAxis::buildBaseAxisMesh()
{
	// X-Cone
	C3DMatrix m;
	m = C3DMatrix::identity();
	m.rotateY(CC_DEGREES_TO_RADIANS(90));
	addCone(m_VerticesBuffer, m_IndicesTriangles, C3DVector3(fCyLinderLengh, 0, 0), fConeRadius, fConeHeight, true, C3DVector4(1.f, 0.f, 0.f, 1.f), m);

	// Y-Cone
	m = C3DMatrix::identity();
	m.rotateX(CC_DEGREES_TO_RADIANS(-90));
	addCone(m_VerticesBuffer, m_IndicesTriangles, C3DVector3(0, fCyLinderLengh, 0), fConeRadius, fConeHeight, true, C3DVector4(0.f, 1.f, 0.f, 1.f), m);

	// Z-Cone
	addCone(m_VerticesBuffer, m_IndicesTriangles, C3DVector3(0, 0, fCyLinderLengh), fConeRadius, fConeHeight, true, C3DVector4(0.f, 0.f, 1.f, 1.f));

	// XY-Line
	m_nBaseIndexLineXY = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_X0Y0], C3DVector4(1.f, 0.f, 0.f, 1.f));

	// XZ-Line
	m_nBaseIndexLineXZ = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_X0Z0], C3DVector4(1.f, 0.f, 0.f, 1.f));

	// YX-Line
	m_nBaseIndexLineYX = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_X0Y0], C3DVector4(0.f, 1.f, 0.f, 1.f));

	// YZ-Line
	m_nBaseIndexLineYZ = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_Y0Z0], C3DVector4(0.f, 1.f, 0.f, 1.f));

	// ZX-Line
	m_nBaseIndexLineZX = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_X0Z0], C3DVector4(0.f, 0.f, 1.f, 1.f));

	// ZY-Line
	m_nBaseIndexLineZY = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_Y0Z0], C3DVector4(0.f, 0.f, 1.f, 1.f));

	// X-Line
	m_nBaseIndexLineX = m_VerticesBuffer.size();
	m = C3DMatrix::identity();
	m.rotateY(CC_DEGREES_TO_RADIANS( 90 ));
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_X1], C3DVector4(1.f, 0.f, 0.f, 1.f));

	// Y-Line
	m_nBaseIndexLineY = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_Y1], C3DVector4(0.f, 1.f, 0.f, 1.f));

	// Z-Line
	m_nBaseIndexLineZ = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_Z1], C3DVector4(0.f, 0.f, 1.f, 1.f));

	C3DVertexElement elements[] =
	{
		C3DVertexElement(Vertex_Usage_POSITION, 3),
		C3DVertexElement(Vertex_Usage_COLOR, 4)
	};

	C3DVertexFormat vertformat(elements, 2);
	m_pBaseMesh = C3DMesh::createMesh(&vertformat, m_VerticesBuffer.size());
	m_pBaseMesh->setPrimitiveType(PrimitiveType_TRIANGLES);
	m_pBaseMesh->setVertexData(&m_VerticesBuffer.front(), 0, m_VerticesBuffer.size());

	MeshPart* part = m_pBaseMesh->addPart(PrimitiveType_TRIANGLES, IndexFormat_INDEX16, m_IndicesTriangles.size());
	part->setIndexData(&m_IndicesTriangles.front(), 0, m_IndicesTriangles.size());

	MeshPart* part2 = m_pBaseMesh->addPart(PrimitiveType_LINES, IndexFormat_INDEX16, m_IndicesLines.size());
	part2->setIndexData(&m_IndicesLines.front(), 0, m_IndicesLines.size());

	C3DMaterial* pMaterial = C3DMaterial::create("shaders/axis.vsh", "shaders/axis.fsh");
	m_pBaseModelNode = C3DModelNode::create("PositionAxis");
	C3DModel* tpModel = C3DModel::create(m_pBaseMesh);
	SAFE_RELEASE(m_pBaseMesh);
	tpModel->setNode(m_pBaseModelNode);
	tpModel->setMaterial(pMaterial);
	m_pBaseModelNode->setModel(tpModel);
	m_pParentNode->addChild(m_pBaseModelNode);
}

void C3DPositionAxis::buildBaseAxisShape()
{
	C3DVector3 pos = C3DVector3(m_Position.x + (fCyLinderLengh + fConeHeight) / 2.f, m_Position.y, m_Position.z);
	m_pCylinderX = new C3DCylinder(pos, C3DCylinder::xAxis, fCyLinderRadius, (fCyLinderLengh + fConeHeight) / 2.f);

	pos = C3DVector3(m_Position.x, m_Position.y + (fCyLinderLengh + fConeHeight) / 2.f, m_Position.z);
	m_pCylinderY = new C3DCylinder(pos, C3DCylinder::yAxis, fCyLinderRadius, (fCyLinderLengh + fConeHeight) / 2.f);

	pos = C3DVector3(m_Position.x, m_Position.y, m_Position.z + (fCyLinderLengh + fConeHeight) / 2.f);
	m_pCylinderZ = new C3DCylinder(pos, C3DCylinder::zAxis, fCyLinderRadius, (fCyLinderLengh + fConeHeight) / 2.f);

	pos = C3DVector3(m_Position.x + fCyLinderLengh, m_Position.y, m_Position.z);
	m_pConeX = new C3DCone(pos, C3DCone::xAxis, fConeRadius, fConeHeight);
}

void C3DPositionAxis::buildSelectFaceMesh(const C3DVector3& pos0,
											const C3DVector3& pos1,
											const C3DVector3& pos2,
											const C3DVector3& pos3,
											const C3DVector4& color)
{
	addTrangle(m_VerticesSelectedMesh, m_IndicesSelectedMesh, pos0, pos1, pos2, color);
	addTrangle(m_VerticesSelectedMesh, m_IndicesSelectedMesh, pos0, pos2, pos3, color);

	C3DVertexElement elements[] =
	{
		C3DVertexElement(Vertex_Usage_POSITION, 3),
		C3DVertexElement(Vertex_Usage_COLOR, 4)
	};

	C3DVertexFormat vertformat(elements, 2);
	m_pSelectedMesh = C3DMesh::createMesh(&vertformat, m_VerticesSelectedMesh.size());
	m_pSelectedMesh->setPrimitiveType(PrimitiveType_TRIANGLES);
	m_pSelectedMesh->setVertexData(&m_VerticesSelectedMesh.front(), 0, m_VerticesSelectedMesh.size());

	MeshPart* part = m_pSelectedMesh->addPart(PrimitiveType_TRIANGLES, IndexFormat_INDEX16, m_IndicesSelectedMesh.size());
	part->setIndexData(&m_IndicesSelectedMesh.front(), 0, m_IndicesSelectedMesh.size());

	m_pSelectedModelNode = C3DModelNode::create("SelectFace");
	C3DModel* tpModel = C3DModel::create(m_pSelectedMesh);
	SAFE_RELEASE(m_pSelectedMesh);
	tpModel->setNode(m_pSelectedModelNode);
	C3DMaterial* pMaterial = C3DMaterial::create("shaders/axis.vsh", "shaders/axis.fsh");
	tpModel->setMaterial(pMaterial);
	m_pSelectedModelNode->setModel(tpModel);
	m_pParentNode->addChild(m_pSelectedModelNode);
	m_pSelectedModelNode->setPosition(getPosition());
}

void C3DPositionAxis::resetColor()
{
	if (!m_pBaseModelNode)
		return;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1, 0, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineXY, 2, C3DVector4(1, 0, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineXZ, 2, C3DVector4(1, 0, 0, 1));

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(0, 1, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineYX, 2, C3DVector4(0, 1, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineYZ, 2, C3DVector4(0, 1, 0, 1));

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(0, 0, 1, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZX, 2, C3DVector4(0, 0, 1, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZY, 2, C3DVector4(0, 0, 1, 1));
}

void C3DPositionAxis::resetSelectFace()
{
	// remove last model
	if (m_pSelectedModelNode)
	{
		m_pParentNode->removeChild(m_pSelectedModelNode);
		m_pSelectedModelNode = NULL;
	}

	m_VerticesSelectedMesh.clear();
	m_IndicesSelectedMesh.clear();
}

bool C3DPositionAxis::onSelectedAxisX()
{
	if (!C3DGimoAxis::onSelectedAxisX())
		return false;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	return true;
}

bool C3DPositionAxis::onSelectedAxisY()
{
	if (!C3DGimoAxis::onSelectedAxisY())
		return false;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	return true;
}

bool C3DPositionAxis::onSelectedAxisZ()
{
	if (!C3DGimoAxis::onSelectedAxisZ())
		return false;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	return true;
}

bool C3DPositionAxis::onSelectedAxisXY()
{
	if (m_SelectAxis == AXIS_SELECT_XY) 
		return false;

	m_SelectAxis = AXIS_SELECT_XY;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineXY, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineYX, 2, C3DVector4(1,1,0,1));
	buildSelectFaceMesh(C3DVector3(0.f, 0.f, 0.f),
						C3DVector3(fEdge0, 0.f, 0.f),
						C3DVector3(fEdge0, fEdge0, 0.f),
						C3DVector3(0.f, fEdge0, 0.f),
						C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DPositionAxis::onSelectedAxisXZ()
{
	if (m_SelectAxis == AXIS_SELECT_XZ)
		return false;

	m_SelectAxis = AXIS_SELECT_XZ;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineXZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZX, 2, C3DVector4(1,1,0,1));
	buildSelectFaceMesh(C3DVector3(0.f, 0.f, 0.f),
						C3DVector3(fEdge0, 0.f, 0.f),
						C3DVector3(fEdge0, 0.f, fEdge0),
						C3DVector3(0.f, 0.f, fEdge0),
						C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DPositionAxis::onSelectedAxisYZ()
{
	if (m_SelectAxis == AXIS_SELECT_YZ)
		return false;

	m_SelectAxis = AXIS_SELECT_YZ;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineYZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZY, 2, C3DVector4(1,1,0,1));
	buildSelectFaceMesh(C3DVector3(0.f, 0.f, 0.f),
						C3DVector3(0.f, fEdge0, 0.f),
						C3DVector3(0.f, fEdge0, fEdge0),
						C3DVector3(0.f, 0.f, fEdge0),
						C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DPositionAxis::onSelectedNone()
{
	if (!C3DGimoAxis::onSelectedNone())
		return false;

	return true;
}

bool C3DPositionAxis::intersectX(const C3DRay* ray)const
{
	if (m_pCylinderX && m_pCylinderX->Intersect(ray))
		return true;

	return false;
}

bool C3DPositionAxis::intersectY(const C3DRay* ray)const
{
	if (!m_pCylinderY)
		return false;

	return m_pCylinderY->Intersect(ray);
}

bool C3DPositionAxis::intersectZ(const C3DRay* ray)const
{
	if (!m_pCylinderZ)
		return false;

	return m_pCylinderZ->Intersect(ray);
}

bool C3DPositionAxis::intersectXY(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_X0Y0]);
	C3DVector3 vIntersectPoint = ray->intersects(&plane);
	return pointInPolygon(vIntersectPoint, m_XYPoints);
}

bool C3DPositionAxis::intersectXZ(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_X0Z0]);
	C3DVector3 vIntersectPoint = ray->intersects(&plane);
	return pointInPolygon(vIntersectPoint, m_XZPoints);
}

bool C3DPositionAxis::intersectYZ(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_Y0Z0]);
	C3DVector3 vIntersectPoint = ray->intersects(&plane);
	return pointInPolygon(vIntersectPoint, m_YZPoints);
}

}