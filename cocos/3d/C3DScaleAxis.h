#ifndef SCALE_AXIS_H_
#define SCALE_AXIS_H_
#include <vector>
#include "C3DMatrix.h"
#include "C3DGimoAxis.h"

namespace cocos3d
{

	class C3DVector3;
	class C3DVector4;
	class BBVertex;
	class C3DMesh;
	class C3DMaterial;
	class C3DModelNode;
	class C3DRay;
	class C3DNode;
	class C3DCylinder;
	class C3DCone;

	class C3DScaleAxis : public C3DGimoAxis
	{
	public:
		enum PosIndex
		{
			POINT_INDEX_ZERO,

			POINT_INDEX_X0,
			POINT_INDEX_Y0,
			POINT_INDEX_Z0,

			POINT_INDEX_X1,
			POINT_INDEX_Y1,
			POINT_INDEX_Z1,

			POINT_INDEX_X2,
			POINT_INDEX_Y2,
			POINT_INDEX_Z2,

			POINT_INDEX_X0Y0,
			POINT_INDEX_X0Z0,
			POINT_INDEX_Y0Z0,

			POINT_INDEX_X1Y1,
			POINT_INDEX_X1Z1,
			POINT_INDEX_Y1Z1,

			POINT_INDEX_NUM
		};

	public:
		C3DScaleAxis(C3DNode*parent);
		~C3DScaleAxis();

	public:
		virtual void updateGimo();

		void buildBaseAxisMesh();

		void buildBaseAxisShape();

		virtual bool pick(int x, int y);

	protected:
		void buildSelectTriangleFaceMesh(const C3DVector3& pos0, 
										const C3DVector3& pos1, 
										const C3DVector3& pos2,
										const C3DVector4& color);

		void buildSelectQuadrilateralFaceMesh(const C3DVector3& pos0, 
											 const C3DVector3& pos1, 
											 const C3DVector3& pos2,
											 const C3DVector3& pos3,
											 const C3DVector4& color);

		
		

		void resetColor();

		void resetSelectFace();

		void setMeshColor(std::vector< BBVertex >& VertexBuffer, C3DMesh* pMesh, unsigned int nBaseIndex, unsigned int nVertexNum, const C3DVector4& color);

		virtual bool onSelectedAxisX();

		virtual bool onSelectedAxisY();

		virtual bool onSelectedAxisZ();

		virtual bool onSelectedAxisXY();

		virtual bool onSelectedAxisXZ();

		virtual bool onSelectedAxisYZ();

		virtual bool onSelectedAxisXYZ();

		virtual bool onSelectedNone();

		bool intersectX(const C3DRay* ray)const;

		bool intersectY(const C3DRay* ray)const;

		bool intersectZ(const C3DRay* ray)const;

		bool intersectXY(const C3DRay* ray)const;

		bool intersectXZ(const C3DRay* ray)const;

		bool intersectYZ(const C3DRay* ray)const;

		bool intersectXYZ(const C3DRay* ray)const;

	protected:
		C3DMesh* m_pBaseMesh;
		C3DMesh* m_pSelectedMesh;
		C3DModelNode* m_pBaseModelNode;
		C3DModelNode* m_pSelectedModelNode;

		std::vector< BBVertex > m_VerticesBuffer;
		std::vector< unsigned short > m_IndicesTriangles;
		std::vector< unsigned short > m_IndicesLines;

		std::vector< BBVertex > m_VerticesSelectedMesh;
		std::vector< unsigned short > m_IndicesSelectedMesh;

		std::vector< C3DVector3 > m_OriginPoint;
		std::vector< C3DVector3 > m_XYPoints;
		std::vector< C3DVector3 > m_XZPoints;
		std::vector< C3DVector3 > m_YZPoints;
		std::vector< C3DVector3 > m_XYZPoints;

		unsigned int m_nBaseIndexLineX;
		unsigned int m_nBaseIndexLineY;
		unsigned int m_nBaseIndexLineZ;

		unsigned int m_nBaseIndexLineX0Y0;
		unsigned int m_nBaseIndexLineX0Z0;
		unsigned int m_nBaseIndexLineY0X0;
		unsigned int m_nBaseIndexLineY0Z0;
		unsigned int m_nBaseIndexLineZ0X0;
		unsigned int m_nBaseIndexLineZ0Y0;

		unsigned int m_nBaseIndexLineX1Y1;
		unsigned int m_nBaseIndexLineX1Z1;
		unsigned int m_nBaseIndexLineY1X1;
		unsigned int m_nBaseIndexLineY1Z1;
		unsigned int m_nBaseIndexLineZ1X1;
		unsigned int m_nBaseIndexLineZ1Y1;

		C3DCylinder* m_pCylinderX;
		C3DCylinder* m_pCylinderY;
		C3DCylinder* m_pCylinderZ;
	};

}

#endif//SCALE_AXIS_H_
