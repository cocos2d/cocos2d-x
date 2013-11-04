#include "C3DScaleAxis.h"
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
#include "C3DNode.h"
#include "C3DRay.h"
#include "C3DRenderSystem.h"
#include "C3DCamera.h"
#include "C3DPlane.h"
#include "C3DScene.h"
#include "C3DCylinder.h"
#include "C3DCone.h"
#include "Geo.h"

namespace cocos3d
{
	
const float fCyLinderLengh = 1.f;
const float fCyLinderHalfLengh = fCyLinderLengh / 2.f;
const float fCyLinderRadius = 0.1f;
const float fConeRadius = fCyLinderRadius;
const float fConeHeight = fConeRadius * 3.f;
const float fEdge0 = 0.5f;
const float fEdge1 = 0.7f;

C3DScaleAxis::C3DScaleAxis(C3DNode*parent)
:C3DGimoAxis(parent),
m_pBaseMesh(0),
m_pSelectedMesh(0),
m_pBaseModelNode(0),
m_pSelectedModelNode(0),
m_nBaseIndexLineX(0),
m_nBaseIndexLineY(0),
m_nBaseIndexLineZ(0),

m_nBaseIndexLineX0Y0(0),
m_nBaseIndexLineX0Z0(0),
m_nBaseIndexLineY0X0(0),
m_nBaseIndexLineY0Z0(0),
m_nBaseIndexLineZ0X0(0),
m_nBaseIndexLineZ0Y0(0),

m_nBaseIndexLineX1Y1(0),
m_nBaseIndexLineX1Z1(0),
m_nBaseIndexLineY1X1(0),
m_nBaseIndexLineY1Z1(0),
m_nBaseIndexLineZ1X1(0),
m_nBaseIndexLineZ1Y1(0),

m_pCylinderX(0),
m_pCylinderY(0),
m_pCylinderZ(0)
{
	m_AxisType = AXIS_TYPE_SCALE;
	updateGimo();
	buildBaseAxisMesh();
	buildBaseAxisShape();
}

C3DScaleAxis::~C3DScaleAxis()
{
	m_pParentNode->removeChild(m_pBaseModelNode);
	m_pParentNode->removeChild(m_pSelectedModelNode);
	SAFE_DELETE(m_pCylinderX);
	SAFE_DELETE(m_pCylinderY);
	SAFE_DELETE(m_pCylinderZ);
}

void C3DScaleAxis::updateGimo()
{
	m_OriginPoint.clear();
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, 0));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge0, 0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fEdge0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, fEdge0));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge1, 0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fEdge1, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, fEdge1));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fCyLinderLengh, 0, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fCyLinderLengh, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, 0, fCyLinderLengh));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge0 / 2.f, fEdge0 / 2.f, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge0 / 2.f, 0, fEdge0 / 2.f));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fEdge0 / 2.f, fEdge0 / 2.f));

	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge1 / 2.f, fEdge1 / 2.f, 0));
	m_OriginPoint.push_back(getPosition() + C3DVector3(fEdge1 / 2.f, 0, fEdge1 / 2.f));
	m_OriginPoint.push_back(getPosition() + C3DVector3(0, fEdge1 / 2.f, fEdge1 / 2.f));

	m_XYPoints.clear();
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_X0]);
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_Y0]);
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_Y1]);
	m_XYPoints.push_back(m_OriginPoint[POINT_INDEX_X1]);

	m_XZPoints.clear();
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_X0]);
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_Z0]);
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_Z1]);
	m_XZPoints.push_back(m_OriginPoint[POINT_INDEX_X1]);

	m_YZPoints.clear();
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Y0]);
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Z0]);
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Z1]);
	m_YZPoints.push_back(m_OriginPoint[POINT_INDEX_Y1]);

	m_XYZPoints.clear();
	m_XYZPoints.push_back(m_OriginPoint[POINT_INDEX_X0]);
	m_XYZPoints.push_back(m_OriginPoint[POINT_INDEX_Y0]);
	m_XYZPoints.push_back(m_OriginPoint[POINT_INDEX_Z0]);

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

void C3DScaleAxis::buildBaseAxisMesh()
{
	// X-Cone
	C3DMatrix m;
	m = C3DMatrix::identity();
	m.rotateY(CC_DEGREES_TO_RADIANS(90));
	addCone(m_VerticesBuffer, m_IndicesTriangles, C3DVector3(fCyLinderLengh, 0, 0), fConeRadius, fConeHeight, false, C3DVector4(1.f, 0.f, 0.f, 1.f), m);

	// Y-Cone
	m = C3DMatrix::identity();
	m.rotateX(CC_DEGREES_TO_RADIANS(-90));
	addCone(m_VerticesBuffer, m_IndicesTriangles, C3DVector3(0, fCyLinderLengh, 0), fConeRadius, fConeHeight, false, C3DVector4(0.f, 1.f, 0.f, 1.f), m);
		
	// Z-Cone
	addCone(m_VerticesBuffer, m_IndicesTriangles, C3DVector3(0, 0, fCyLinderLengh), fConeRadius, fConeHeight, false, C3DVector4(0.f, 0.f, 1.f, 1.f));

	// X0Y0-Line
	m_nBaseIndexLineX0Y0 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_X0Y0], C3DVector4(1.f, 0.f, 0.f, 1.f));

	// X0Z0-Line
	m_nBaseIndexLineX0Z0 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_X0Z0], C3DVector4(1.f, 0.f, 0.f, 1.f));
	// Y0X0-Line
	m_nBaseIndexLineY0X0 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_X0Y0], C3DVector4(0.f, 1.f, 0.f, 1.f));
	// Y0Z0-Line
	m_nBaseIndexLineY0Z0 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_Y0Z0], C3DVector4(0.f, 1.f, 0.f, 1.f));
	// Z0X0-Line
	m_nBaseIndexLineZ0X0 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_X0Z0], C3DVector4(0.f, 0.f, 1.f, 1.f));
	// Z0Y0-Line
	m_nBaseIndexLineZ0Y0 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_Y0Z0], C3DVector4(0.f, 0.f, 1.f, 1.f));

	// X1Y1-Line
	m_nBaseIndexLineX1Y1 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_X1], m_OriginPoint[POINT_INDEX_X1Y1], C3DVector4(1.f, 0.f, 0.f, 1.f));
	// X1Z1-Line
	m_nBaseIndexLineX1Z1 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_X1], m_OriginPoint[POINT_INDEX_X1Z1], C3DVector4(1.f, 0.f, 0.f, 1.f));
	// Y1X1-Line
	m_nBaseIndexLineY1X1 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Y1], m_OriginPoint[POINT_INDEX_X1Y1], C3DVector4(0.f, 1.f, 0.f, 1.f));
	// Y1Z1-Line
	m_nBaseIndexLineY1Z1 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Y1], m_OriginPoint[POINT_INDEX_Y1Z1], C3DVector4(0.f, 1.f, 0.f, 1.f));
	// Z1X1-Line
	m_nBaseIndexLineZ1X1 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Z1], m_OriginPoint[POINT_INDEX_X1Z1], C3DVector4(0.f, 0.f, 1.f, 1.f));
	// Z1Y1-Line
	m_nBaseIndexLineZ1Y1 = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_Z1], m_OriginPoint[POINT_INDEX_Y1Z1], C3DVector4(0.f, 0.f, 1.f, 1.f));

	// X-Line
	m_nBaseIndexLineX = m_VerticesBuffer.size();
	m = C3DMatrix::identity();
	m.rotateY(CC_DEGREES_TO_RADIANS( 90 ));
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_X2], C3DVector4(1.f, 0.f, 0.f, 1.f));

	// Y-Line
	m_nBaseIndexLineY = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_Y2], C3DVector4(0.f, 1.f, 0.f, 1.f));

	// Z-Line
	m_nBaseIndexLineZ = m_VerticesBuffer.size();
	addLine(m_VerticesBuffer, m_IndicesLines, m_OriginPoint[POINT_INDEX_ZERO], m_OriginPoint[POINT_INDEX_Z2], C3DVector4(0.f, 0.f, 1.f, 1.f));

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
	m_pBaseModelNode = C3DModelNode::create("ScaleAxis");
	C3DModel* tpModel = C3DModel::create(m_pBaseMesh);
	SAFE_RELEASE(m_pBaseMesh);
	tpModel->setNode(m_pBaseModelNode);
	tpModel->setMaterial(pMaterial);
	m_pBaseModelNode->setModel(tpModel);
	m_pParentNode->addChild(m_pBaseModelNode);
}

void C3DScaleAxis::buildBaseAxisShape()
{
	m_pCylinderX = new C3DCylinder(C3DVector3(m_Position.x + (fCyLinderLengh + fConeHeight) / 2.f, m_Position.y, m_Position.z), C3DCylinder::xAxis, fCyLinderRadius, (fCyLinderLengh + fConeHeight) / 2.f);
	m_pCylinderY = new C3DCylinder(C3DVector3(m_Position.x, m_Position.y + (fCyLinderLengh + fConeHeight) / 2.f, m_Position.z), C3DCylinder::yAxis, fCyLinderRadius, (fCyLinderLengh + fConeHeight) / 2.f);
	m_pCylinderZ = new C3DCylinder(C3DVector3(m_Position.x, m_Position.y, m_Position.z + (fCyLinderLengh + fConeHeight) / 2.f), C3DCylinder::zAxis, fCyLinderRadius, (fCyLinderLengh + fConeHeight) / 2.f);
}

bool C3DScaleAxis::pick(int x, int y)
{
	C3DRay ray;
	if (m_pBaseModelNode && m_pBaseModelNode->getScene() && m_pBaseModelNode->getScene()->getActiveCamera())
	{
		m_pBaseModelNode->getScene()->getActiveCamera()->getAxes(C3DRenderSystem::getInstance()->getViewport(), x, y, &ray);
	}

	onSelectedNone();
	if (intersectXYZ(&ray))
	{
		onSelectedAxisXYZ();
	}
	else if (intersectXY(&ray))
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

void C3DScaleAxis::buildSelectTriangleFaceMesh(const C3DVector3& pos0,
	const C3DVector3& pos1,
	const C3DVector3& pos2,
	const C3DVector4& color)
{
	// remove last model
	if (m_pSelectedModelNode)
	{
		m_pParentNode->removeChild(m_pSelectedModelNode);
		m_pSelectedModelNode = NULL;
	}

	addTrangle(m_VerticesSelectedMesh, m_IndicesSelectedMesh, pos0, pos1, pos2, color);

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

	m_pSelectedModelNode = C3DModelNode::create("select");
	C3DModel* tpModel = C3DModel::create(m_pSelectedMesh);
	SAFE_RELEASE(m_pSelectedMesh);
	tpModel->setNode(m_pSelectedModelNode);
	C3DMaterial* pMaterial = C3DMaterial::create("shaders/axis.vsh", "shaders/axis.fsh");
	tpModel->setMaterial(pMaterial);
	m_pSelectedModelNode->setModel(tpModel);
	m_pParentNode->addChild(m_pSelectedModelNode);
	m_pSelectedModelNode->setPosition(getPosition());
}

void C3DScaleAxis::buildSelectQuadrilateralFaceMesh(const C3DVector3& pos0, 
	const C3DVector3& pos1, 
	const C3DVector3& pos2,
	const C3DVector3& pos3,
	const C3DVector4& color)
{
	// remove last model
	if (m_pSelectedModelNode)
	{
		m_pParentNode->removeChild(m_pSelectedModelNode);
		m_pSelectedModelNode = NULL;
	}

	m_VerticesSelectedMesh.clear();
	m_IndicesSelectedMesh.clear();
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

void C3DScaleAxis::resetColor()
{
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1, 0, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX0Y0, 2, C3DVector4(1, 0, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX0Z0, 2, C3DVector4(1, 0, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX1Y1, 2, C3DVector4(1, 0, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX1Z1, 2, C3DVector4(1, 0, 0, 1));

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(0, 1, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY0X0, 2, C3DVector4(0, 1, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY0Z0, 2, C3DVector4(0, 1, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY1X1, 2, C3DVector4(0, 1, 0, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY1Z1, 2, C3DVector4(0, 1, 0, 1));

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(0, 0, 1, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ0X0, 2, C3DVector4(0, 0, 1, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ0Y0, 2, C3DVector4(0, 0, 1, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ1X1, 2, C3DVector4(0, 0, 1, 1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ1Y1, 2, C3DVector4(0, 0, 1, 1));
}

void C3DScaleAxis::resetSelectFace()
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

void C3DScaleAxis::setMeshColor(std::vector< BBVertex >& VertexBuffer, C3DMesh* pMesh, unsigned int nBaseIndex, unsigned int nVertexNum, const C3DVector4& color)
{
	assert(pMesh);
	if (!pMesh) return;

	int nEnd = nBaseIndex + nVertexNum;
	for (int i = nBaseIndex; i < nEnd; i++)
	{
		m_VerticesBuffer[i].color = color;
	}
	pMesh->setVertexData(&VertexBuffer[nBaseIndex], nBaseIndex, nVertexNum);
}

bool C3DScaleAxis::onSelectedAxisX()
{
	if (!C3DGimoAxis::onSelectedAxisX())
		return false;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	return true;
}

bool C3DScaleAxis::onSelectedAxisY()
{
	if (!C3DGimoAxis::onSelectedAxisY())
		return false;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	return true;
}

bool C3DScaleAxis::onSelectedAxisZ()
{
	if (!C3DGimoAxis::onSelectedAxisZ())
		return false;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	return true;
}

bool C3DScaleAxis::onSelectedAxisXY()
{
	if (m_SelectAxis == AXIS_SELECT_XY)
		return false;

	m_SelectAxis = AXIS_SELECT_XY;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX0Y0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY0X0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX1Y1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY1X1, 2, C3DVector4(1,1,0,1));

	buildSelectQuadrilateralFaceMesh(C3DVector3(fEdge0, 0, 0), C3DVector3(fEdge1, 0, 0), C3DVector3(0, fEdge1, 0), C3DVector3(0, fEdge0, 0), C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DScaleAxis::onSelectedAxisXZ()
{
	if (m_SelectAxis == AXIS_SELECT_XZ)
		return false;

	m_SelectAxis = AXIS_SELECT_XZ;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX0Z0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ0X0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX1Z1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ1X1, 2, C3DVector4(1,1,0,1));

	buildSelectQuadrilateralFaceMesh(C3DVector3(fEdge0, 0, 0), C3DVector3(fEdge1, 0, 0), C3DVector3(0, 0, fEdge1), C3DVector3(0, 0, fEdge0), C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DScaleAxis::onSelectedAxisYZ()
{
	if (m_SelectAxis == AXIS_SELECT_YZ)
		return false;

	m_SelectAxis = AXIS_SELECT_YZ;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY0Z0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ0Y0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY1Z1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ1Y1, 2, C3DVector4(1,1,0,1));

	buildSelectQuadrilateralFaceMesh(C3DVector3(0, fEdge0, 0), C3DVector3(0, fEdge1, 0), C3DVector3(0, 0, fEdge1), C3DVector3(0, 0, fEdge0), C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DScaleAxis::onSelectedAxisXYZ()
{
	if (m_SelectAxis == AXIS_SELECT_XYZ)
		return false;

	m_SelectAxis = AXIS_SELECT_XYZ;

	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX0Y0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY0X0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX0Z0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ0X0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY0Z0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ0Y0, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX1Y1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY1X1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineX1Z1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ1X1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineY1Z1, 2, C3DVector4(1,1,0,1));
	setMeshColor(m_VerticesBuffer, m_pBaseModelNode->getModel()->getMesh(), m_nBaseIndexLineZ1Y1, 2, C3DVector4(1,1,0,1));

	buildSelectTriangleFaceMesh(C3DVector3(fEdge0, 0, 0), C3DVector3(0, fEdge0, 0), C3DVector3(0, 0, fEdge0), C3DVector4(0.8f, 0.8f, 0.f, 0.f));
	return true;
}

bool C3DScaleAxis::onSelectedNone()
{
	if (!C3DGimoAxis::onSelectedNone())
		return false;

	return true;
}

bool C3DScaleAxis::intersectX(const C3DRay* ray)const
{
	if (m_pCylinderX && m_pCylinderX->Intersect(ray))
		return true;

	return false;
}

bool C3DScaleAxis::intersectY(const C3DRay* ray)const
{
	if (!m_pCylinderY)
		return false;

	return m_pCylinderY->Intersect(ray);
}

bool C3DScaleAxis::intersectZ(const C3DRay* ray)const
{
	if (!m_pCylinderZ)
		return false;

	return m_pCylinderZ->Intersect(ray);
}

bool C3DScaleAxis::intersectXY(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_Y1]);
	C3DVector3 vIntersectPoint = ray->intersects(&plane);
	return pointInPolygon(vIntersectPoint, m_XYPoints);
}

bool C3DScaleAxis::intersectXZ(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_Z1]);
	C3DVector3 vIntersectPoint = ray->intersects(&plane);
	return pointInPolygon(vIntersectPoint, m_XZPoints);
}

bool C3DScaleAxis::intersectYZ(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_Z0], m_OriginPoint[POINT_INDEX_Z1]);
	C3DVector3 vIntersectPoint = ray->intersects(&plane);
	return pointInPolygon(vIntersectPoint, m_YZPoints);
}

bool C3DScaleAxis::intersectXYZ(const C3DRay* ray)const
{
	C3DPlane plane(m_OriginPoint[POINT_INDEX_X0], m_OriginPoint[POINT_INDEX_Y0], m_OriginPoint[POINT_INDEX_Z0]);
	float t = ray->dist(&plane);
	C3DVector3 vIntersectPoint = ray->getOrigin() + ray->getDirection() * t;
	return pointInPolygon(vIntersectPoint, m_XYZPoints);
}


}