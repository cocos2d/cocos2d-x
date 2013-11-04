#ifndef C3DAABB_H_
#define C3DAABB_H_
#include "C3DVector3.h"
#include "C3DMatrix.h"

namespace cocos3d
{

/**
 * Defines a class describe 3-dimensional axis-aligned bounding box.
 */
class C3DAABB
{
public:

    C3DVector3 _min;

    C3DVector3 _max;

	/**
     * Constructor.
     */
    C3DAABB();

	/**
     * Constructor.
     */
    C3DAABB(const C3DVector3& min, const C3DVector3& max);

	/**
     * Constructor.
     */
	C3DAABB(const C3DAABB& box);

	/**
     * Destructor.
     */
    ~C3DAABB();

	/**
     * Gets the center point of the bounding box.
	 */
    C3DVector3 getCenter();

	 /**
     * Gets the corners of the bounding box in the specified array.
     */
	void getCorners(C3DVector3* dst) const;
	
	 /**
     * Tests whether this bounding box intersects the specified bounding object.
     */
    bool intersects(const C3DAABB& box) const;	

	 /**
     * Sets this bounding box to the smallest bounding box
     * that contains both this bounding object and the specified bounding box.
     */
    void merge(const C3DAABB& box);

	 /**
     * Sets this bounding box to the specified values.
     */
    void set(const C3DVector3& min, const C3DVector3& max);

	/**
     * Transforms the bounding box by the given transformation matrix.
     */
    void transform(const C3DMatrix& matrix);

};


}



#endif
