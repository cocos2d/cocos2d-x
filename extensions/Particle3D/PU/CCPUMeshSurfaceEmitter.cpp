/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "CCPUMeshSurfaceEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUUtil.h"

NS_CC_BEGIN
// Constants
const Vec3 PUMeshSurfaceEmitter::DEFAULT_SCALE(1, 1, 1);
const MeshInfo::MeshSurfaceDistribution PUMeshSurfaceEmitter::DEFAULT_DISTRIBUTION = MeshInfo::MSD_HOMOGENEOUS;

//-----------------------------------------------------------------------
inline void PUTriangle::calculateSquareSurface (void)
{
    /* Calculating the surface of a triangle with the following algorithm:
        v1 = Vector3(x1, y1, z1)
        v2 = Vector3(x2, y2, z2)
        v3 = Vector3(x3, y3, z3)
        a = sqrt ((x1-x3)*(x1-x3) + (y1-y3)*(y1-y3) + (z1-z3)*(z1-z3))
        b = sqrt ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1))
        c = sqrt ((x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) + (z3-z2)*(z3-z2))
        p = 0.5 * (a + b + c)
        surface = sqrt (p * (p-a) * (p-b) * (p-c));
    */

    // a, b and c are the length of each triangle
    float a = sqrt (	(v1.x - v3.x) * (v1.x - v3.x) + 
                        (v1.y - v3.y) * (v1.y - v3.y) + 
                        (v1.z - v3.z) * (v1.z - v3.z));
    float b = sqrt (	(v2.x - v1.x) * (v2.x - v1.x) + 
                        (v2.y - v1.y) * (v2.y - v1.y) + 
                        (v2.z - v1.z) * (v2.z - v1.z));
    float c = sqrt (	(v3.x - v2.x) * (v3.x - v2.x) + 
                        (v3.y - v2.y) * (v3.y - v2.y) + 
                        (v3.z - v2.z) * (v3.z - v2.z));
    float p = 0.5f * (a + b + c);

    // Assign square surface of the triangle
    squareSurface = p * (p-a) * (p-b) * (p-c);
}
//-----------------------------------------------------------------------
inline void PUTriangle::calculateSurfaceNormal (void)
{
    /* Calculating the surface normal of a triangle with the following algorithm:
        v1 = Vector3(x1, y1, z1)
        v2 = Vector3(x2, y2, z2)
        v3 = Vector3(x3, y3, z3)
        n = (v2-v1)x(v3-v1), where the 'x' is the cross product
    */
    Vec3::cross(v2-v1, v3-v1, &surfaceNormal);
    surfaceNormal.normalize();
}
//-----------------------------------------------------------------------
inline void PUTriangle::calculateEdgeNormals (void)
{
    Vec3::cross(v1, v2, &en1);
    en1.normalize();
    Vec3::cross(v2, v3, &en2);
    en2.normalize();
    Vec3::cross(v3, v1, &en3);
    en3.normalize();
}
//-----------------------------------------------------------------------
const Vec3 PUTriangle::getRandomTrianglePosition (void)
{
    // Use barycentric coordinates. Let A, B, C be the three vertices of the triangle. Any point P inside can 
    // be expressed uniquely as P = aA + bB + cC, where a+b+c=1 and a,b,c are each >= 0.
    // Knowing a and b permits you to calculate c=1-a-b.
    // So if you can generate two random numbers a and b, each in [0,1], such that their sum <=1, you've got a 
    // random point in your triangle. Generate random a and b independently and uniformly in [0,1] 
    // If a+b>1, replace a by 1-a, b by 1-b. Let c=1-a-b. Then aA + bB + cC is uniformly distributed 
    // in triangle ABC: the reflection step a=1-a; b=1-b gives a point (a,b) uniformly distributed in the 
    // triangle (0,0)(1,0)(0,1), which is then mapped affinely to ABC. Now you have barycentric coordinates 
    // a,b,c. Compute your point P = aA + bB + cC.
    float a = CCRANDOM_0_1();
    float b = CCRANDOM_0_1();
    if (a + b > 1)
    {
        a = 1 - a;
        b = 1 - b;
    }
    float c = 1 - a - b;
    return a * v1 + b * v2 + c * v3;
}
//-----------------------------------------------------------------------
const PUTriangle::PositionAndNormal PUTriangle::getRandomEdgePositionAndNormal (void)
{
    float mult = CCRANDOM_0_1();
    float randomVal = CCRANDOM_0_1() * 3.0f;
    PositionAndNormal pAndN;
    pAndN.position = Vec3::ZERO;
    pAndN.normal = Vec3::ZERO;
    if (randomVal < 1)
    {
        pAndN.position = Vec3(	v2.x + mult*(v1.x - v2.x),
                                        v2.y + mult*(v1.y - v2.y),
                                        v2.z + mult*(v1.z - v2.z));
        pAndN.normal = en1;
    }
    else
    {
        if (randomVal < 2)
        {
            pAndN.position = Vec3(	v3.x + mult*(v2.x - v3.x),
                                            v3.y + mult*(v2.y - v3.y),
                                            v3.z + mult*(v2.z - v3.z));
            pAndN.normal = en2;
        }
        else
        {
    
            pAndN.position = Vec3(	v1.x + mult*(v3.x - v1.x),
                                            v1.y + mult*(v3.y - v1.y),
                                            v1.z + mult*(v3.z - v1.z));
            pAndN.normal = en3;
        }
    }

    return pAndN;
}
//-----------------------------------------------------------------------
const PUTriangle::PositionAndNormal PUTriangle::getRandomVertexAndNormal (void)
{
    float randomVal = CCRANDOM_0_1() * 3.0f;
    PositionAndNormal pAndN;
    pAndN.position = Vec3::ZERO;
    pAndN.normal = Vec3::ZERO;

    if (randomVal < 1)
    {
        pAndN.position = v1;
        pAndN.normal = vn1;
    }
    else
    {
        if (randomVal < 2)
        {
            pAndN.position = v2;
            pAndN.normal = vn2;
        }
        else
        {
            pAndN.position = v3;
            pAndN.normal = vn3;
        }
    }

    return pAndN;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
MeshInfo::MeshInfo (const std::string& meshName, 
    MeshSurfaceDistribution distribution,
    const Quaternion& orientation,
    const Vec3& scale) : 
    mDistribution(distribution)
{
    //Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //getMeshInformation(mesh, Vec3::ZERO, orientation, scale);
}
//-----------------------------------------------------------------------
MeshInfo::~MeshInfo (void)
{
    _triangles.clear();
}
//-----------------------------------------------------------------------
inline float MeshInfo::getGaussianRandom (float high, float cutoff)
{
    float x1 = 0;
    float x2 = 0;
    float w = 0;
    float y1 = 0;

    unsigned int max = 0;
    do
    {
        x1 = CCRANDOM_0_1();
        x2 = CCRANDOM_0_1();
        w = x1 * x1 + x2 * x2;

        // Prevent infinite loop
        if (w >= 1.0f && max > 4 )
            w = x1;
        
    } while (w >= 1.0f);
    
    w = sqrt((-2.0f * ::log(w)) / w);
    y1 = abs(x1 * w);
    y1 = y1 > cutoff ? cutoff : y1;
    y1 *= high / cutoff;
    return y1;
}

//-----------------------------------------------------------------------
const PUTriangle& MeshInfo::getTriangle (size_t triangleIndex)
{
    return _triangles[triangleIndex];
}

//-----------------------------------------------------------------------
const size_t MeshInfo::getRandomTriangleIndex (void)
{
    size_t index;
    if (mDistribution == MSD_HOMOGENEOUS || mDistribution == MSD_HETEROGENEOUS_1)
    {
        index = (size_t)getGaussianRandom((float)_triangles.size() - 1);
    }
    else
        index = (size_t)(CCRANDOM_0_1() * (float)(_triangles.size() - 1));

    return index;
}

//-----------------------------------------------------------------------
const PUTriangle::PositionAndNormal MeshInfo::getRandomPositionAndNormal (const size_t triangleIndex)
{
    PUTriangle triangle = getTriangle(triangleIndex);
    PUTriangle::PositionAndNormal pAndN;
    pAndN.position = Vec3::ZERO;
    pAndN.normal = Vec3::ZERO;
    if (mDistribution == MSD_HOMOGENEOUS || mDistribution == MSD_HETEROGENEOUS_1 || mDistribution == MSD_HETEROGENEOUS_2)
    {
        pAndN.position = triangle.getRandomTrianglePosition();
        pAndN.normal = triangle.surfaceNormal;
    }
    else
    {
        if (mDistribution == MSD_VERTEX)
        {
            pAndN = triangle.getRandomVertexAndNormal();
        }
        else
        {
            if (mDistribution == MSD_EDGE)
            {
                pAndN = triangle.getRandomEdgePositionAndNormal();
            }
        }
    }
    return pAndN;
}

//-----------------------------------------------------------------------
//void MeshInfo::getMeshInformation(	Ogre::MeshPtr mesh,
//									const Vec3 &position,
//									const Quaternion &orient,
//									const Vec3 &scale)
//{
//	size_t vertexCount = 0;
//	size_t indexCount = 0;
//	Vec3* vertices = 0;
//	Vec3* normals;
//	unsigned long* indices = 0;
//
//	bool added_shared = false;
//	size_t current_offset = 0;
//	size_t shared_offset = 0;
//	size_t next_offset = 0;
//	size_t index_offset = 0;
//
//	// Calculate how many vertices and indices we're going to need
//	for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
//	{
//		Ogre::SubMesh* submesh = mesh->getSubMesh( i );
//
//		// We only need to add the shared vertices once
//		if(submesh->useSharedVertices)
//		{
//			if( !added_shared )
//			{
//				vertexCount += mesh->sharedVertexData->vertexCount;
//				added_shared = true;
//			}
//		}
//		else
//		{
//			vertexCount += submesh->vertexData->vertexCount;
//		}
//
//		// Add the indices
//		indexCount += submesh->indexData->indexCount;
//	}
//
//	// Allocate space for the vertices and indices
//	vertices = new (std::nothrow) Vec3[vertexCount];
//	normals = new (std::nothrow) Vec3[vertexCount];
//	indices = new (std::nothrow) unsigned long[indexCount];
//	added_shared = false;
//
//	// Run through the submeshes again, adding the data into the arrays
//	for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
//	{
//		Ogre::SubMesh* submesh = mesh->getSubMesh(i);
//		Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
//
//		if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
//		{
//			if(submesh->useSharedVertices)
//			{
//				added_shared = true;
//				shared_offset = current_offset;
//			}
//
//			const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
//			const Ogre::VertexElement* normalElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
//			Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
//			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
//			float* pReal;
//
//			for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
//			{
//				posElem->baseVertexPointerToElement(vertex, &pReal);
//				Vec3 pt(pReal[0], pReal[1], pReal[2]);
//				vertices[current_offset + j] = (orient * (pt * scale)) + position;
//
//				normalElem->baseVertexPointerToElement(vertex, &pReal);
//				Vec3 nt(pReal[0], pReal[1], pReal[2]);
//				normals[current_offset + j] = nt;
//			}
//      
//			vbuf->unlock();
//			next_offset += vertex_data->vertexCount;
//		}
//
//		Ogre::IndexData* index_data = submesh->indexData;
//		size_t numTris = index_data->indexCount / 3;
//		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
//    	bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
//		unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
//		unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);
//		size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;
//
//		size_t numTrisMultThree = numTris*3;
//		if ( use32bitindexes )
//		{
//			for ( size_t k = 0; k < numTrisMultThree; ++k)
//			{
//				indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
//			}
//		}
//		else
//		{
//			for ( size_t k = 0; k < numTrisMultThree; ++k)
//			{
//				indices[index_offset++] = static_cast<unsigned long>(pShort[k]) + static_cast<unsigned long>(offset);
//			}
//		}
//
//		ibuf->unlock();
//		current_offset = next_offset;
//	}
//
//	// Create triangles from the retrieved data
//	for (size_t k = 0; k < indexCount-1; k+=3)
//	{
//		Triangle t;
//		t.v1 = vertices [indices[k]];
//		t.vn1 = normals [indices[k]];
//
//		t.v2 = vertices [indices[k+1]];
//		t.vn2 = normals [indices[k+1]];
//
//		t.v3 = vertices [indices[k+2]];
//		t.vn3 = normals [indices[k+2]];
//
//		t.calculateSquareSurface();
//		t.calculateSurfaceNormal();
//		t.calculateEdgeNormals();
//		_triangles.push_back(t);
//	}
//
//	// Delete intermediate arrays
//	delete [] indices;
//	delete [] normals;
//	delete [] vertices;
//
//	// Sort the triangle on their size, if needed (only if a gaussian random number generator
//	// function is used to perform a random lookup of a triangle)
//	if (mDistribution == MSD_HOMOGENEOUS)
//		sort(_triangles.begin(), _triangles.end(), SortDescending());
//	else
//		if (mDistribution == MSD_HETEROGENEOUS_1)
//			sort(_triangles.begin(), _triangles.end(), SortAscending());
//}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
PUMeshSurfaceEmitter::PUMeshSurfaceEmitter(void) : 
    PUEmitter(),
    _meshName(),
    _orientation(),
    _scale(DEFAULT_SCALE),
    _distribution(DEFAULT_DISTRIBUTION),
    _meshInfo(0),
    _triangleIndex(0),
    _directionSet(false)
{
}
//-----------------------------------------------------------------------
PUMeshSurfaceEmitter::~PUMeshSurfaceEmitter(void)
{
    if (_meshInfo)
    {
        CC_SAFE_DELETE(_meshInfo);
    }
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::prepare()
{
    PUEmitter::prepare();
    // Build the data
    if (!_meshName.empty())
    {
        build();
    }
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::unPrepare()
{
    // Todo
    PUEmitter::unPrepare();
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::initParticlePosition(PUParticle3D* particle)
{
    PUTriangle::PositionAndNormal pAndN;
    pAndN.position = Vec3::ZERO;
    pAndN.normal = Vec3::ZERO;
    _directionSet = false;

    if (_meshInfo && _meshInfo->getTriangleCount())
    {
        getDerivedPosition();
        _triangleIndex = _meshInfo->getRandomTriangleIndex (); // Get a random triangle index
        pAndN = _meshInfo->getRandomPositionAndNormal(_triangleIndex); // Determine position and normal
        //ParticleSystem* sys = mParentTechnique->getParentSystem();
        if (_autoDirection)
        {
            if (pAndN.normal != Vec3::ZERO)
            {
                // Set position and direction of the particle
                //if (sys)
                {
                    Mat4 rotMat;
                    Mat4::createRotation(static_cast<PUParticleSystem3D *>(_particleSystem)->getDerivedOrientation(), &rotMat);
                    particle->position = _derivedPosition + rotMat * Vec3(_emitterScale.x * pAndN.position.x, _emitterScale.y * pAndN.position.y, _emitterScale.z * pAndN.position.z);
                }
                //else
                //{
                //	particle->position = _derivedPosition + _emitterScale * pAndN.position;
                //}

                // The value of the direction vector that has been set does not have a meaning
                float angle = (_dynamicAttributeHelper.calculate(_dynAngle, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart()));
                if (angle != 0.0f)
                {
                    //particle->direction = (pAndN.normal).randomDeviant(angle, mUpVector);
                    particle->direction = PUUtil::randomDeviant(pAndN.normal, angle, _upVector);
                }
                else
                {
                    particle->direction = pAndN.normal;
                }

                particle->originalDirection = particle->direction;
                _directionSet = true;
            }
        }
        else
        {
            // Set position of the particle
            //if (sys)
            {
                Mat4 rotMat;
                Mat4::createRotation(static_cast<PUParticleSystem3D *>(_particleSystem)->getDerivedOrientation(), &rotMat);
                particle->position = _derivedPosition + rotMat * Vec3(_emitterScale.x * pAndN.position.x, _emitterScale.y * pAndN.position.y, _emitterScale.z * pAndN.position.z);
            }
            //else
            //{
            //	particle->position = mDerivedPosition + _mEmitterScale * pAndN.position;
            //}
        }
    
        particle->originalPosition = particle->position;
    }
}
//-----------------------------------------------------------------------
unsigned short PUMeshSurfaceEmitter::calculateRequestedParticles(float timeElapsed)
{
    if (_meshInfo)
    {
        return PUEmitter::calculateRequestedParticles(timeElapsed);
    }

    return 0;
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::initParticleDirection(PUParticle3D* particle)
{
    // Only determine direction if it hasn't been calculated yet
    if (!_directionSet)
    {
        PUEmitter::initParticleDirection(particle);
    }
}
//-----------------------------------------------------------------------
const std::string& PUMeshSurfaceEmitter::getMeshName(void) const
{
    return _meshName;
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::setMeshName(const std::string& meshName, bool doBuild)
{
    _meshName = meshName;

    // If needed, build the data needed for emitting particles
    if (doBuild)
    {
        build();
    }
}
//-----------------------------------------------------------------------
const MeshInfo::MeshSurfaceDistribution PUMeshSurfaceEmitter::getDistribution (void) const
{
    return _distribution;
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::setDistribution(MeshInfo::MeshSurfaceDistribution distribution)
{
    _distribution = distribution;
}
//-----------------------------------------------------------------------
const Vec3& PUMeshSurfaceEmitter::getScale (void) const
{
    return _scale;
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::setScale (const Vec3& scale)
{
    _scale = scale;
}
//-----------------------------------------------------------------------
void PUMeshSurfaceEmitter::build(void)
{
    // Delete the mesh info if already existing
    if (_meshInfo)
    {
        CC_SAFE_DELETE(_meshInfo);
    }

    // Generate meshinfo.
    _meshInfo = new (std::nothrow) MeshInfo(_meshName, _distribution, _orientation, _scale);
}

PUMeshSurfaceEmitter* PUMeshSurfaceEmitter::create()
{
    auto pe = new (std::nothrow) PUMeshSurfaceEmitter();
    pe->autorelease();
    return pe;
}

void PUMeshSurfaceEmitter::copyAttributesTo( PUEmitter* emitter )
{
    PUEmitter::copyAttributesTo(emitter);
    PUMeshSurfaceEmitter* meshSurfaceEmitter = static_cast<PUMeshSurfaceEmitter*>(emitter);
    meshSurfaceEmitter->_meshName = _meshName;
    meshSurfaceEmitter->_distribution = _distribution;
    meshSurfaceEmitter->_orientation = _orientation;
    meshSurfaceEmitter->_scale = _scale;
}

PUMeshSurfaceEmitter* PUMeshSurfaceEmitter::clone()
{
    auto be = PUMeshSurfaceEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END