#ifndef GEO_H_
#define GEO_H_

namespace cocos3d
{



class C3DMesh;
class BBVertex;
class C3DVector4;

/**
 * Geo is an interface for creating some C3DMesh.
 */
class Geo
{
    friend class C3DModel;
    friend class C3DResourceLoader;

public:  
	/**
	* create board mesh.
	*/
	static C3DMesh* createBoard(float x, float y, float width, float height);

	/**
	* create full screen quad mesh.
	*/
	static C3DMesh* createQuadFullscreen();

	/**
	* create Sphere mesh.
	*/
	static bool CreateSphere(float radius, std::vector< BBVertex > &ppVertices, std::vector< unsigned short > &ppIndices, const C3DVector4& color, int stacks = 20, int slices = 20);
	
};

}

#endif
