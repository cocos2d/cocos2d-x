#ifndef POSITION_AXIS_H_
#define POSITION_AXIS_H_
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
	class ModelNode;
	class C3DNode;
	class C3DRay;
	class C3DScene;
	class C3DCylinder;
	class C3DCone;

	// 自定义图形模型基类
	class C3DPositionAxis : public C3DGimoAxis
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

			POINT_INDEX_X0Y0,
			POINT_INDEX_X0Z0,
			POINT_INDEX_Y0Z0,

			POINT_INDEX_NUM
		};

	public:
		C3DPositionAxis(C3DNode*parent);
		~C3DPositionAxis();

	public:
		virtual void updateGimo();

		bool pick(int x, int y);

	protected:
		void buildBaseAxisMesh();

		void buildBaseAxisShape();

		void buildSelectFaceMesh(const C3DVector3& pos0, 
								const C3DVector3& pos1, 
								const C3DVector3& pos2,
								const C3DVector3& pos3,
								const C3DVector4& color);

		void resetColor();

		void resetSelectFace();

		virtual bool onSelectedAxisX();

		virtual bool onSelectedAxisY();

		virtual bool onSelectedAxisZ();

		virtual bool onSelectedAxisXY();
		
		virtual bool onSelectedAxisXZ();
		
		virtual bool onSelectedAxisYZ();

		virtual bool onSelectedNone();

		virtual bool intersectX(const C3DRay* ray)const;

		virtual bool intersectY(const C3DRay* ray)const;

		virtual bool intersectZ(const C3DRay* ray)const;

		virtual bool intersectXY(const C3DRay* ray)const;

		virtual bool intersectXZ(const C3DRay* ray)const;

		virtual bool intersectYZ(const C3DRay* ray)const;

	protected:
		C3DMesh* m_pBaseMesh;
		C3DMesh* m_pSelectedMesh;
		C3DModelNode* m_pBaseModelNode;
		C3DModelNode* m_pSelectedModelNode;
	
		C3DNode* m_pParentNode;
		std::vector< BBVertex > m_VerticesBuffer;
		std::vector< unsigned short > m_IndicesTriangles;
		std::vector< unsigned short > m_IndicesLines;

		std::vector< BBVertex > m_VerticesSelectedMesh;
		std::vector< unsigned short > m_IndicesSelectedMesh;

		std::vector< C3DVector3 > m_OriginPoint;
		std::vector< C3DVector3 > m_XYPoints;
		std::vector< C3DVector3 > m_XZPoints;
		std::vector< C3DVector3 > m_YZPoints;

		unsigned int m_nBaseIndexLineX;
		unsigned int m_nBaseIndexLineY;
		unsigned int m_nBaseIndexLineZ;
		unsigned int m_nBaseIndexLineXY;
		unsigned int m_nBaseIndexLineXZ;
		unsigned int m_nBaseIndexLineYX;
		unsigned int m_nBaseIndexLineYZ;
		unsigned int m_nBaseIndexLineZX;
		unsigned int m_nBaseIndexLineZY;

		C3DCylinder* m_pCylinderX;
		C3DCylinder* m_pCylinderY;
		C3DCylinder* m_pCylinderZ;
		C3DCone* m_pConeX;
	};

}

#endif//POSITION_AXIS
