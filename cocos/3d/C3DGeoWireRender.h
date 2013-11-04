#ifndef C3DGEOWIRERENDER_H_
#define C3DGEOWIRERENDER_H_

#include "C3DVector4.h"
#include "C3DVector3.h"
#include "C3DNode.h"

namespace cocos3d
{



class C3DMesh;
class BBVertex;
class C3DVector4;
class C3DAABB;
class Rectangle;
class C3DOBB;
class C3DNode;
class C3DBatchModel;
class C3DVector3;
class C3DVector2;
class C3DCylinder;
class C3DCollitionBox;
    class C3DCapsule;

/**
 * interface for rendering wired primitive geometry.
 */
class C3DGeoWireRender
{
    friend class C3DModel;
    friend class C3DResourceLoader;

public:  
	C3DGeoWireRender();
	virtual ~C3DGeoWireRender();

	/**
	* init with node
	*/
	bool init(C3DNode* node);
	/**
	* add bounding box
	* @param box bounding box to render
	* @param color, color of bounding box
	*/
	void addBoundingBox(const C3DAABB* box, const C3DVector4& color);

	/**
	 * add oriented bounding box
	 * @param obb oriented bounding box to render
	 * @param color, color of obb
	 */
	void addOBB(const C3DOBB* obb,const C3DVector4& color);

	/**
	 * add 3D line
	 * @param start, start point of 3D line
	 * @param end, end point of 3D line
	 * @param color, color of line
	 */
	void add3DLine(const C3DVector3& start, const C3DVector3& end, const C3DVector4& color);

	/**
	 * add 3D rectangle
	 * @param v0, v1, v2, v3, rectangle corner
	 * @param color, color of rectangle
	 */
	void add3DRect(const C3DVector3& v0, const C3DVector3& v1, const C3DVector3& v2, const C3DVector3& v3, const C3DVector4& color);
	
	/**
	 * add 3D triangle
	 * @param v0, v1, v2,  triangle corner
	 * @param color, color of triangle
	 */
	void add3DTriangle(const C3DVector3& v0, const C3DVector3& v1, const C3DVector3& v2, const C3DVector4& color);

	/**
	 * add sphere
	 * @param vPos, sphere center
	 * @param radius, sphere radius
	 * @param color, color of sphere
	 */
	void addSphere(const C3DVector3& vPos, float radius, const C3DVector4& color);

	/**
	 * add sphere
	 * @param cylinder, cylinder to render
	 * @param color, color of cylinder
	 */
	void addCylinder(const C3DCylinder* cylinder, const C3DVector4& color);

	void addCollitionBox(const C3DCollitionBox* box, const C3DVector4& color);

    /**
	 * add sphere
	 * @param capsule, capsule to render
	 * @param color, color of capsule
	 */
	void addCapsule(const C3DCapsule* capsule, const C3DVector4& color);

	/**
	 * add vertex for render(3D geometry)
	 * @param verts, vertex to be rendered, vertex <v0, v1, v2, v3, v4, v5>...
	 * @param vertCount, vertex number
	 * @param index, be careful, index should PrimitiveType_LINES
	 * @param indexCount, index number
	 * @param color, vertex color
	 */
	void addLinesRenderData(const C3DVector3* verts, int vertCount, const unsigned short* index, int indexCount, const C3DVector4& color);

	/**
	 * finish draw 
	 */
	void flush();

	/**
	 * begin draw 
	 */
	void begin();

protected:
	
	C3DBatchModel* _model_3D;

	unsigned int _lastCapacity_3D;
	unsigned int _lastIndexCapacity_3D;

	// support 2D geometry maybe
	C3DBatchModel* _model_2D;

};

}

#endif
