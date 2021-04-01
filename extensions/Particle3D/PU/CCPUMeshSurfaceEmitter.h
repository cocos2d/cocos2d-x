/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __CC_PU_PARTICLE_MESH_SURFACE_EMITTER_H__
#define __CC_PU_PARTICLE_MESH_SURFACE_EMITTER_H__

#include "extensions/Particle3D/PU/CCPUEmitter.h"

NS_CC_BEGIN

/** Definition of a Triangle
*/
class PUTriangle
{
public:
    /** The struct is used to return both the position and the normal
    */
    struct PositionAndNormal
    {
        Vec3 position;
        Vec3 normal;
    };

    /** Public attributes **/
    float squareSurface;
    Vec3 surfaceNormal;	// Normal of triangle v1-v2-v3
    Vec3 v1;				// Vertex v1
    Vec3 v2;				// Vertex v2
    Vec3 v3;				// Vertex v3
    Vec3 vn1;			// Normal of vertex v1
    Vec3 vn2;			// Normal of vertex v2
    Vec3 vn3;			// Normal of vertex v3
    Vec3 en1;			// Normal of edge v1-v2
    Vec3 en2;			// Normal of edge v2-v3
    Vec3 en3;			// Normal of edge v3-v1

    /** Constructor **/
    PUTriangle(){};

    /** Calculate the (square) surface of the triangle **/
    void calculateSquareSurface ();

    /** Calculate the surface normal of the triangle **/
    void calculateSurfaceNormal ();

    /** Calculate the edge normals of the 3 edges  **/
    void calculateEdgeNormals ();

    /** Determine a random position on this triangle **/
    const Vec3 getRandomTrianglePosition ();

    /** Determine a random position including its normal on a one of the edges **/
    const PositionAndNormal getRandomEdgePositionAndNormal ();

    /** Determine a random vertex including its normal of this triangle **/
    const PositionAndNormal getRandomVertexAndNormal ();
};

/** Comparer used for sorting vector in ascending order
*/
struct PUSortAscending
{
    bool operator() (const PUTriangle& a, const PUTriangle& b)
    {
        return a.squareSurface < b.squareSurface;
    }
};

/** Comparer used for sorting vector in descending order
*/
struct PUSortDescending
{
    bool operator() (const PUTriangle& a, const PUTriangle& b)
    {
        return a.squareSurface > b.squareSurface;
    }
};

/** Define a template class for a vector of triangles.
*/
typedef std::vector<PUTriangle> Triangles;

/** Class that constructs mesh information of a given mesh name
@remarks
*/
class MeshInfo
{
public:
    /** Defining several methods to emit particles on the mesh surface
    @remarks
        Sometimes the difference is not always visible, for example if the mesh contains triangles with more or
        less the same size. Only in case a mesh contains both small and large triangles the difference between
        the various distribution methods is more obvious.
    */
    enum MeshSurfaceDistribution
    { 
        MSD_HOMOGENEOUS,		// Distribute particles homogeneous (random) on the mesh surface
        MSD_HETEROGENEOUS_1,	// Distribute more particles on the smaller faces
        MSD_HETEROGENEOUS_2,	// Same as above, but now more particles are emitting from the larger faces
        MSD_VERTEX,				// Particles only emit from the vertices
        MSD_EDGE				// Particles emit random on the edges
    };

    /** Constructor **/
    MeshInfo (const std::string& meshName, 
        const MeshSurfaceDistribution distribution = MSD_HOMOGENEOUS,
        const Quaternion& orientation = Quaternion(),
        const Vec3& scale = Vec3::ZERO);

    /** Destructor **/
    ~MeshInfo ();

    /** Generate a random number. The high argument determines that numbers are 
        returned between [0..high] **/
    float getGaussianRandom (float high, float cutoff = 4);

    ///** Retrieve vertex info **/
    //void getMeshInformation(Ogre::MeshPtr mesh,
    //						const Vec3& position = Vec3::ZERO,
    //						const Quaternion& orient = Quaternion(),
    //						const Vec3& scale = Vec3::ONE);

    /** Get a triangle based on the index. */
    const PUTriangle& getTriangle (size_t triangleIndex);

    /** Get a random triangle (index) from the mesh. */
    size_t getRandomTriangleIndex();
    
    /** Get triangle number */
    size_t getTriangleCount() const { return _triangles.size(); }

    /** Returns both a random point on a given triangle and its normal vector.
        How the random point and the normal are determined depends on the distribution type.
    **/
    const PUTriangle::PositionAndNormal getRandomPositionAndNormal (const size_t triangleIndex);

protected:
    Triangles _triangles;
    MeshSurfaceDistribution mDistribution;
};

/** The MeshSurfaceEmitter is a ParticleEmitter that emits particles on the surface of a mesh.
@remarks
    There are several ways of emitting it on the surface, from the vertices, edges and faces of a mesh.
    It is also possible to define whether more particles emit on larger faces.
*/

class CC_DLL PUMeshSurfaceEmitter : public PUEmitter
{
public:
    // Constants
    static const Vec3 DEFAULT_SCALE;
    static const MeshInfo::MeshSurfaceDistribution DEFAULT_DISTRIBUTION;

    static PUMeshSurfaceEmitter* create();

    /** Returns the mesh name.
    */
    const std::string& getMeshName() const;

    /** Sets the mesh name.
    */
    void setMeshName(const std::string& meshName, bool doBuild = true);

    /** Returns true if normals are used for the particle direction.
    */
    bool useNormals () const;

    /** Set indication whether normals are used for the particle direction.
    */
    void setUseNormals (bool useNormals);

    /** Returns the type op distribution.
    @remarks
        There are several ways to emit particles on the surface of a mesh. This attribute indicates
        the type of distribution on the surface.
    */
    MeshInfo::MeshSurfaceDistribution getDistribution() const;

    /** Set the type of particle distribution on the surface of a mesh.
    */
    void setDistribution(MeshInfo::MeshSurfaceDistribution distribution);

    /** Returns the scale of the mesh.
    */
    const Vec3& getScale () const;

    /** Set the scale of the mesh.
    @remarks
        This options makes it possible to scale the mesh independently from the particle system scale as a whole.
    */
    void setScale (const Vec3& scale);

    /** Build all the data needed to generate the particles.
    */
    void build();

    /** Build the data if the mesh name has been set.
    */
    virtual void prepare() override;

    /** Reverse it.
    */
    virtual void unPrepare() override;

    /** Determine a particle position on the mesh surface.
    */
    virtual void initParticlePosition(PUParticle3D* particle) override;

    /** See ParticleEmitter.
    */
    virtual unsigned short calculateRequestedParticles(float timeElapsed) override;

    /** Determine the particle direction.
    */
    virtual void initParticleDirection(PUParticle3D* particle) override;

    virtual PUMeshSurfaceEmitter* clone() override;
    virtual void copyAttributesTo (PUEmitter* emitter) override;

CC_CONSTRUCTOR_ACCESS:
    PUMeshSurfaceEmitter();
    virtual ~PUMeshSurfaceEmitter();

protected:
    std::string _meshName;
    Quaternion _orientation;
    Vec3 _scale;
    MeshInfo::MeshSurfaceDistribution _distribution;
    MeshInfo* _meshInfo;
    size_t _triangleIndex;
    bool _directionSet;
};

NS_CC_END

#endif