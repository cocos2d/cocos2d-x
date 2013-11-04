#ifndef GIMO_AXIS_H_
#define GIMO_AXIS_H_
#include <vector>
#include "C3DMatrix.h"
#include "C3DModel.h"

namespace cocos3d
{

	class C3DVector3;
	class C3DVector4;
	class BBVertex;
	class C3DMesh;

	class C3DGimoAxis
	{
	public:
		enum AxisType
		{
			AXIS_TYPE_POSITION,
			AXIS_TYPE_ROTATE,
			AXIS_TYPE_SCALE
		};

		enum AxisSelectType
		{
			AXIS_SELECT_NONE,
			AXIS_SELECT_X,
			AXIS_SELECT_Y,
			AXIS_SELECT_Z,
			AXIS_SELECT_XY,
			AXIS_SELECT_XZ,
			AXIS_SELECT_YZ,
			AXIS_SELECT_XYZ,
		};

	public:
		virtual void draw()const;

		void addLine(std::vector< BBVertex >& VerticesBuffer, 
			std::vector< unsigned short >& IndicesBuffer,
			const C3DVector3& pos0,
			const C3DVector3& pos1,
			const C3DVector4& color);

		void addTrangle(std::vector< BBVertex >& VerticesBuffer,
			std::vector< unsigned short >& IndicesBuffer,
			const C3DVector3& pos0, 
			const C3DVector3& pos1, 
			const C3DVector3& pos2,
			const C3DVector4& color);

		void addCone(std::vector< BBVertex >& VerticesBuffer,
			std::vector< unsigned short >& IndicesBuffer,
			const C3DVector3& pos, float radius, 
			float length, 
			bool cap, 
			const C3DVector4& color , 
			const C3DMatrix& transform = C3DMatrix::identity());

		virtual bool pick(int x, int y);

		virtual void setPosition(const C3DVector3& pos);

		C3DVector3 getPosition();

		virtual void updateGimo(){};
		
		AxisSelectType getSelectedAxis(){return m_SelectAxis;}

		virtual void resetAxis();
		
	protected:
		C3DGimoAxis(C3DNode* parent);
		virtual ~C3DGimoAxis();

	protected:
		virtual bool onSelectedAxisX();
		
		virtual bool onSelectedAxisY();
		
		virtual bool onSelectedAxisZ();
		
		virtual bool onSelectedNone();

		virtual void resetColor(){;}

		virtual void resetSelectFace(){;}

		void setMeshColor(std::vector< BBVertex >& VertexBuffer, C3DMesh* pMesh, unsigned int nBaseIndex, unsigned int nVertexNum, const C3DVector4& color);

		bool pointInPolygon(const C3DVector3& point, const std::vector<C3DVector3>& points)const;

	protected:
		C3DNode* m_pParentNode;
		AxisType m_AxisType;
		C3DVector3 m_Position;
		AxisSelectType m_SelectAxis;
	};

}

#endif//GIMO_AXIS_H_
