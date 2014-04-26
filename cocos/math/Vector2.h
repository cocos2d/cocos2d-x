#ifndef VECTOR2_H_
#define VECTOR2_H_

#include "CCMathBase.h"
#include "base/CCPlatformMacros.h"
#include "2d/ccMacros.h"

NS_CC_MATH_BEGIN

/** Clamp a value between from and to.
 */

inline float clampf(float value, float min_inclusive, float max_inclusive)
{
    if (min_inclusive > max_inclusive) {
        CC_SWAP(min_inclusive, max_inclusive, float);
    }
    return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
}

class Matrix;

/**
 * Defines a 2-element floating point vector.
 */
class Vector2
{
public:

    /**
     * The x coordinate.
     */
    float x;

    /**
     * The y coordinate.
     */
    float y;

    /**
     * Constructs a new vector initialized to all zeros.
     */
    Vector2();

    /**
     * Constructs a new vector initialized to the specified values.
     *
     * @param xx The x coordinate.
     * @param yy The y coordinate.
     */
    Vector2(float xx, float yy);

    /**
     * Constructs a new vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y.
     */
    Vector2(const float* array);

    /**
     * Constructs a vector that describes the direction between the specified points.
     *
     * @param p1 The first point.
     * @param p2 The second point.
     */
    Vector2(const Vector2& p1, const Vector2& p2);

    /**
     * Constructs a new vector that is a copy of the specified vector.
     *
     * @param copy The vector to copy.
     */
    Vector2(const Vector2& copy);

    /**
     * Destructor.
     */
    ~Vector2();

    /**
     * Returns the zero vector.
     *
     * @return The 2-element vector of 0s.
     */
    static const Vector2& zero();

    /**
     * Returns the one vector.
     *
     * @return The 2-element vector of 1s.
     */
    static const Vector2& one();

    /**
     * Returns the unit x vector.
     *
     * @return The 2-element unit vector along the x axis.
     */
    static const Vector2& unitX();

    /**
     * Returns the unit y vector.
     *
     * @return The 2-element unit vector along the y axis.
     */
    static const Vector2& unitY();

    /**
     * Indicates whether this vector contains all zeros.
     *
     * @return true if this vector contains all zeros, false otherwise.
     */
    bool isZero() const;

    /**
     * Indicates whether this vector contains all ones.
     *
     * @return true if this vector contains all ones, false otherwise.
     */
    bool isOne() const;

    /**
     * Returns the angle (in radians) between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return The angle between the two vectors (in radians).
     */
    static float angle(const Vector2& v1, const Vector2& v2);

    /**
     * Adds the elements of the specified vector to this one.
     *
     * @param v The vector to add.
     */
    void add(const Vector2& v);

    /**
     * Adds the specified vectors and stores the result in dst.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst A vector to store the result in.
     */
    static void add(const Vector2& v1, const Vector2& v2, Vector2* dst);

    /**
     * Clamps this vector within the specified range.
     *
     * @param min The minimum value.
     * @param max The maximum value.
     */
    void clamp(const Vector2& min, const Vector2& max);

    /**
     * Clamps the specified vector within the specified range and returns it in dst.
     *
     * @param v The vector to clamp.
     * @param min The minimum value.
     * @param max The maximum value.
     * @param dst A vector to store the result in.
     */
    static void clamp(const Vector2& v, const Vector2& min, const Vector2& max, Vector2* dst);

    /**
     * Returns the distance between this vector and v.
     *
     * @param v The other vector.
     * 
     * @return The distance between this vector and v.
     * 
     * @see distanceSquared
     */
    float distance(const Vector2& v) const;

    /**
     * Returns the squared distance between this vector and v.
     *
     * When it is not necessary to get the exact distance between
     * two vectors (for example, when simply comparing the
     * distance between different vectors), it is advised to use
     * this method instead of distance.
     *
     * @param v The other vector.
     * 
     * @return The squared distance between this vector and v.
     * 
     * @see distance
     */
    float distanceSquared(const Vector2& v) const;

    /**
     * Returns the dot product of this vector and the specified vector.
     *
     * @param v The vector to compute the dot product with.
     * 
     * @return The dot product.
     */
    float dot(const Vector2& v) const;

    /**
     * Returns the dot product between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * 
     * @return The dot product between the vectors.
     */
    static float dot(const Vector2& v1, const Vector2& v2);

    /**
     * Computes the length of this vector.
     *
     * @return The length of the vector.
     * 
     * @see lengthSquared
     */
    float length() const;

    /**
     * Returns the squared length of this vector.
     *
     * When it is not necessary to get the exact length of a
     * vector (for example, when simply comparing the lengths of
     * different vectors), it is advised to use this method
     * instead of length.
     *
     * @return The squared length of the vector.
     * 
     * @see length
     */
    float lengthSquared() const;

    /**
     * Negates this vector.
     */
    void negate();

    /**
     * Normalizes this vector.
     *
     * This method normalizes this Vector2 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     * 
     * @return This vector, after the normalization occurs.
     */
    Vector2& normalize();

    /**
     * Normalizes this vector and stores the result in dst.
     *
     * If the vector already has unit length or if the length
     * of the vector is zero, this method simply copies the
     * current vector into dst.
     *
     * @param dst The destination vector.
     */
    void normalize(Vector2* dst) const;

    /**
     * Scales all elements of this vector by the specified value.
     *
     * @param scalar The scalar value.
     */
    void scale(float scalar);

    /**
     * Scales each element of this vector by the matching component of scale.
     *
     * @param scale The vector to scale by.
     */
    void scale(const Vector2& scale);

    /**
     * Rotates this vector by angle (specified in radians) around the given point.
     *
     * @param point The point to rotate around.
     * @param angle The angle to rotate by (in radians).
     */
    void rotate(const Vector2& point, float angle);

    /**
     * Sets the elements of this vector to the specified values.
     *
     * @param xx The new x coordinate.
     * @param yy The new y coordinate.
     */
    void set(float xx, float yy);

    /**
     * Sets the elements of this vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y.
     */
    void set(const float* array);

    /**
     * Sets the elements of this vector to those in the specified vector.
     *
     * @param v The vector to copy.
     */
    void set(const Vector2& v);

    /**
     * Sets this vector to the directional vector between the specified points.
     * 
     * @param p1 The first point.
     * @param p2 The second point.
     */
    void set(const Vector2& p1, const Vector2& p2);

    /**
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @param v The vector to subtract.
     */
    void subtract(const Vector2& v);

    /**
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst The destination vector.
     */
    static void subtract(const Vector2& v1, const Vector2& v2, Vector2* dst);

    /**
     * Updates this vector towards the given target using a smoothing function.
     * The given response time determines the amount of smoothing (lag). A longer
     * response time yields a smoother result and more lag. To force this vector to
     * follow the target closely, provide a response time that is very small relative
     * to the given elapsed time.
     *
     * @param target target value.
     * @param elapsedTime elapsed time between calls.
     * @param responseTime response time (in the same units as elapsedTime).
     */
    void smooth(const Vector2& target, float elapsedTime, float responseTime);

    /**
     * Calculates the sum of this vector with the given vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @param v The vector to add.
     * @return The vector sum.
     */
    inline const Vector2 operator+(const Vector2& v) const;

    /**
     * Adds the given vector to this vector.
     * 
     * @param v The vector to add.
     * @return This vector, after the addition occurs.
     */
    inline Vector2& operator+=(const Vector2& v);

    /**
     * Calculates the sum of this vector with the given vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @param v The vector to add.
     * @return The vector sum.
     */
    inline const Vector2 operator-(const Vector2& v) const;

    /**
     * Subtracts the given vector from this vector.
     * 
     * @param v The vector to subtract.
     * @return This vector, after the subtraction occurs.
     */
    inline Vector2& operator-=(const Vector2& v);

    /**
     * Calculates the negation of this vector.
     * 
     * Note: this does not modify this vector.
     * 
     * @return The negation of this vector.
     */
    inline const Vector2 operator-() const;

    /**
     * Calculates the scalar product of this vector with the given value.
     * 
     * Note: this does not modify this vector.
     * 
     * @param s The value to scale by.
     * @return The scaled vector.
     */
    inline const Vector2 operator*(float s) const;

    /**
     * Scales this vector by the given value.
     * 
     * @param s The value to scale by.
     * @return This vector, after the scale occurs.
     */
    inline Vector2& operator*=(float s);
    
    /**
     * Returns the components of this vector divided by the given constant
     *
     * Note: this does not modify this vector.
     *
     * @param s the constant to divide this vector with
     * @return a smaller vector
     */
    inline const Vector2 operator/(float s) const;

    /**
     * Determines if this vector is less than the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is less than the given vector, false otherwise.
     */
    inline bool operator<(const Vector2& v) const;

    /**
     * Determines if this vector is equal to the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is equal to the given vector, false otherwise.
     */
    inline bool operator==(const Vector2& v) const;

    /**
     * Determines if this vector is not equal to the given vector.
     * 
     * @param v The vector to compare against.
     * 
     * @return True if this vector is not equal to the given vector, false otherwise.
     */
    inline bool operator!=(const Vector2& v) const;

    //code added compatible for Point
public:
      /**
     * @js NA
     * @lua NA
     */
    void setPoint(float xx, float yy);
    /**
     * @js NA
     */
    bool equals(const Vector2& target) const;
    
    /** @returns if points have fuzzy equality which means equal with some degree of variance.
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    bool fuzzyEquals(const Vector2& target, float variance) const;

    /** Calculates distance between point an origin
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLength() const {
        return sqrtf(x*x + y*y);
    };

    /** Calculates the square length of a Vector2 (not calling sqrt() )
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getLengthSq() const {
        return dot(*this); //x*x + y*y;
    };

    /** Calculates the square distance between two points (not calling sqrt() )
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistanceSq(const Vector2& other) const {
        return (*this - other).getLengthSq();
    };

    /** Calculates the distance between two points
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getDistance(const Vector2& other) const {
        return (*this - other).getLength();
    };

    /** @returns the angle in radians between this vector and the x axis
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };

    /** @returns the angle in radians between two vector directions
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    float getAngle(const Vector2& other) const;

    /** Calculates cross product of two points.
     @return float
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline float cross(const Vector2& other) const {
        return x*other.y - y*other.x;
    };

    /** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
     @return Vector2
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 getPerp() const {
        return Vector2(-y, x);
    };
    
    /** Calculates midpoint between two points.
     @return Vector2
     @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vector2 getMidpoint(const Vector2& other) const
    {
        return Vector2((x + other.x) / 2.0f, (y + other.y) / 2.0f);
    }
    
    /** Clamp a point between from and to.
     @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vector2 getClampPoint(const Vector2& min_inclusive, const Vector2& max_inclusive) const
    {
        return Vector2(clampf(x,min_inclusive.x,max_inclusive.x), clampf(y, min_inclusive.y, max_inclusive.y));
    }
    
    /** Run a math operation function on each point component
     * absf, fllorf, ceilf, roundf
     * any function that has the signature: float func(float);
     * For example: let's try to take the floor of x,y
     * p.compOp(floorf);
     @since v3.0
     * @js NA
     * @lua NA
     */
    inline Vector2 compOp(std::function<float(float)> function) const
    {
        return Vector2(function(x), function(y));
    }

    /** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
     @return Vector2
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 getRPerp() const {
        return Vector2(y, -x);
    };

    /** Calculates the projection of this over other.
     @return Vector2
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 project(const Vector2& other) const {
        return other * (dot(other)/other.dot(other));
    };

    /** Complex multiplication of two points ("rotates" two points).
     @return Vector2 vector with an angle of this.getAngle() + other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 rotate(const Vector2& other) const {
        return Vector2(x*other.x - y*other.y, x*other.y + y*other.x);
    };

    /** Unrotates two points.
     @return Vector2 vector with an angle of this.getAngle() - other.getAngle(),
     and a length of this.getLength() * other.getLength().
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 unrotate(const Vector2& other) const {
        return Vector2(x*other.x + y*other.y, y*other.x - x*other.y);
    };

    /** Returns point multiplied to a length of 1.
     * If the point is 0, it returns (1, 0)
     @return Vector2
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 normalize() const {
        float length = getLength();
        if(length == 0.) return Vector2(1.f, 0);
        return *this / getLength();
    };

    /** Linear Interpolation between two points a and b
     @returns
        alpha == 0 ? a
        alpha == 1 ? b
        otherwise a value between a..b
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    inline Vector2 lerp(const Vector2& other, float alpha) const {
        return *this * (1.f - alpha) + other * alpha;
    };

    /** Rotates a point counter clockwise by the angle around a pivot
     @param pivot is the pivot, naturally
     @param angle is the angle of rotation ccw in radians
     @returns the rotated point
     @since v2.1.4
     * @js NA
     * @lua NA
     */
    Vector2 rotateByAngle(const Vector2& pivot, float angle) const;

    /**
     * @js NA
     * @lua NA
     */
    static inline Vector2 forAngle(const float a)
    {
        return Vector2(cosf(a), sinf(a));
    }
    
    /** A general line-line intersection test
     @param A   the startpoint for the first line L1 = (A - B)
     @param B   the endpoint for the first line L1 = (A - B)
     @param C   the startpoint for the second line L2 = (C - D)
     @param D   the endpoint for the second line L2 = (C - D)
     @param S   the range for a hitpoint in L1 (p = A + S*(B - A))
     @param T   the range for a hitpoint in L2 (p = C + T*(D - C))
     @returns   whether these two lines interects.

     Note that to truly test intersection for segments we have to make
     sure that S & T lie within [0..1] and for rays, make sure S & T > 0
     the hit point is        C + T * (D - C);
     the hit point also is   A + S * (B - A);
     @since 3.0
     * @js NA
     * @lua NA
     */
    static bool isLineIntersect(const Vector2& A, const Vector2& B,
                                 const Vector2& C, const Vector2& D,
                                 float *S = nullptr, float *T = nullptr);
    
    /**
     returns true if Line A-B overlap with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineOverlap(const Vector2& A, const Vector2& B,
                                const Vector2& C, const Vector2& D);
    
    /**
     returns true if Line A-B parallel with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isLineParallel(const Vector2& A, const Vector2& B,
                   const Vector2& C, const Vector2& D);
    
    /**
     returns true if Segment A-B overlap with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentOverlap(const Vector2& A, const Vector2& B,
                                 const Vector2& C, const Vector2& D,
                                 Vector2* S = nullptr, Vector2* E = nullptr);
    
    /**
     returns true if Segment A-B intersects with segment C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static bool isSegmentIntersect(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
    
    /**
     returns the intersection point of line A-B, C-D
     @since v3.0
     * @js NA
     * @lua NA
     */
    static Vector2 getIntersectPoint(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
    
    /** equals to Vector2(0,0) */
    static const Vector2 ZERO;
    /** equals to Vector2(0.5, 0.5) */
    static const Vector2 ANCHOR_MIDDLE;
    /** equals to Vector2(0, 0) */
    static const Vector2 ANCHOR_BOTTOM_LEFT;
    /** equals to Vector2(0, 1) */
    static const Vector2 ANCHOR_TOP_LEFT;
    /** equals to Vector2(1, 0) */
    static const Vector2 ANCHOR_BOTTOM_RIGHT;
    /** equals to Vector2(1, 1) */
    static const Vector2 ANCHOR_TOP_RIGHT;
    /** equals to Vector2(1, 0.5) */
    static const Vector2 ANCHOR_MIDDLE_RIGHT;
    /** equals to Vector2(0, 0.5) */
    static const Vector2 ANCHOR_MIDDLE_LEFT;
    /** equals to Vector2(0.5, 1) */
    static const Vector2 ANCHOR_MIDDLE_TOP;
    /** equals to Vector2(0.5, 0) */
    static const Vector2 ANCHOR_MIDDLE_BOTTOM;
};

/**
 * Calculates the scalar product of the given vector with the given value.
 * 
 * @param x The value to scale by.
 * @param v The vector to scale.
 * @return The scaled vector.
 */
inline const Vector2 operator*(float x, const Vector2& v);

NS_CC_MATH_END

#include "Vector2.inl"

#endif
