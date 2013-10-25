#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include "C3DVector3.h"
#include "C3DMatrix.h"

namespace cocos3d
{

/**
 * Defines a class describe 3-dimensional axis-aligned bounding box.
 */
class BoundingBox
{
public:

    C3DVector3 _min;

    C3DVector3 _max;

	/**
     * Constructor.
     */
    BoundingBox();

	/**
     * Constructor.
     */
    BoundingBox(const C3DVector3& min, const C3DVector3& max);

	/**
     * Constructor.
     */
	BoundingBox(const BoundingBox& box);

	/**
     * Destructor.
     */
    ~BoundingBox();

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
    bool intersects(const BoundingBox& box) const;	

	 /**
     * Sets this bounding box to the smallest bounding box
     * that contains both this bounding object and the specified bounding box.
     */
    void merge(const BoundingBox& box);

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
