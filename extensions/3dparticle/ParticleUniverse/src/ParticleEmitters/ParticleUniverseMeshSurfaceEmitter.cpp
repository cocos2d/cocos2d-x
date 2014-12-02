/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleEmitters/ParticleUniverseMeshSurfaceEmitter.h"
#include "OgreMeshManager.h"
#include "OgreSubMesh.h"

namespace ParticleUniverse
{
	// Constants
	const Vector3 MeshSurfaceEmitter::DEFAULT_SCALE(1, 1, 1);
	const MeshInfo::MeshSurfaceDistribution MeshSurfaceEmitter::DEFAULT_DISTRIBUTION = MeshInfo::MSD_HOMOGENEOUS;

	//-----------------------------------------------------------------------
	inline void Triangle::calculateSquareSurface (void)
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
		Real a = sqrt (	(v1.x - v3.x) * (v1.x - v3.x) + 
							(v1.y - v3.y) * (v1.y - v3.y) + 
							(v1.z - v3.z) * (v1.z - v3.z));
		Real b = sqrt (	(v2.x - v1.x) * (v2.x - v1.x) + 
							(v2.y - v1.y) * (v2.y - v1.y) + 
							(v2.z - v1.z) * (v2.z - v1.z));
		Real c = sqrt (	(v3.x - v2.x) * (v3.x - v2.x) + 
							(v3.y - v2.y) * (v3.y - v2.y) + 
							(v3.z - v2.z) * (v3.z - v2.z));
		Real p = 0.5f * (a + b + c);

		// Assign square surface of the triangle
		squareSurface = p * (p-a) * (p-b) * (p-c);
	}
	//-----------------------------------------------------------------------
	inline void Triangle::calculateSurfaceNormal (void)
	{
		/* Calculating the surface normal of a triangle with the following algorithm:
		   v1 = Vector3(x1, y1, z1)
		   v2 = Vector3(x2, y2, z2)
		   v3 = Vector3(x3, y3, z3)
		   n = (v2-v1)x(v3-v1), where the 'x' is the cross product
		*/
		surfaceNormal = (v2-v1).crossProduct(v3-v1);
		surfaceNormal.normalise();
	}
	//-----------------------------------------------------------------------
	inline void Triangle::calculateEdgeNormals (void)
	{
		en1 = v1.crossProduct(v2);
		en1.normalise();
		en2 = v2.crossProduct(v3);
		en2.normalise();
		en3 = v3.crossProduct(v1);
		en3.normalise();
	}
	//-----------------------------------------------------------------------
	const Vector3 Triangle::getRandomTrianglePosition (void)
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
		Real a = Math::RangeRandom(0, 1);
		Real b = Math::RangeRandom(0, 1);
		if (a + b > 1)
		{
			a = 1 - a;
			b = 1 - b;
		}
		Real c = 1 - a - b;
		return a * v1 + b * v2 + c * v3;
	}
	//-----------------------------------------------------------------------
	const Triangle::PositionAndNormal Triangle::getRandomEdgePositionAndNormal (void)
	{
		Real mult = Math::RangeRandom(0, 1);
		Real randomVal = Math::RangeRandom(0, 3);
		PositionAndNormal pAndN;
		pAndN.position = Vector3::ZERO;
		pAndN.normal = Vector3::ZERO;
		if (randomVal < 1)
		{
			pAndN.position = Vector3(	v2.x + mult*(v1.x - v2.x),
											v2.y + mult*(v1.y - v2.y),
											v2.z + mult*(v1.z - v2.z));
			pAndN.normal = en1;
		}
		else
		{
			if (randomVal < 2)
			{
				pAndN.position = Vector3(	v3.x + mult*(v2.x - v3.x),
												v3.y + mult*(v2.y - v3.y),
												v3.z + mult*(v2.z - v3.z));
				pAndN.normal = en2;
			}
			else
			{
	
				pAndN.position = Vector3(	v1.x + mult*(v3.x - v1.x),
												v1.y + mult*(v3.y - v1.y),
												v1.z + mult*(v3.z - v1.z));
				pAndN.normal = en3;
			}
		}

		return pAndN;
	}
	//-----------------------------------------------------------------------
	const Triangle::PositionAndNormal Triangle::getRandomVertexAndNormal (void)
	{
		Real randomVal = Math::RangeRandom(0, 3);
		PositionAndNormal pAndN;
		pAndN.position = Vector3::ZERO;
		pAndN.normal = Vector3::ZERO;

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
	MeshInfo::MeshInfo (const String& meshName, 
		MeshSurfaceDistribution distribution,
		const Quaternion& orientation,
		const Vector3& scale) : 
		mDistribution(distribution)
	{
		Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		getMeshInformation(mesh, Vector3::ZERO, orientation, scale);
	}
	//-----------------------------------------------------------------------
	MeshInfo::~MeshInfo (void)
	{
		_triangles.clear();
	}
	//-----------------------------------------------------------------------
	inline Real MeshInfo::getGaussianRandom (Real high, Real cutoff)
	{
		Real x1 = 0;
		Real x2 = 0;
		Real w = 0;
		Real y1 = 0;

		uint max = 0;
		do
		{
			x1 = Math::RangeRandom(0,1);
			x2 = Math::RangeRandom(0,1);
			w = x1 * x1 + x2 * x2;

			// Prevent infinite loop
			if (w >= 1.0f && max > 4 )
				w = x1;
		
		} while (w >= 1.0f);
	
		w = sqrt((-2.0f * log(w)) / w);
		y1 = abs(x1 * w);
		y1 = y1 > cutoff ? cutoff : y1;
		y1 *= high / cutoff;
		return y1;
	}

	//-----------------------------------------------------------------------
	const Triangle& MeshInfo::getTriangle (size_t triangleIndex)
	{
		return _triangles[triangleIndex];
	}

	//-----------------------------------------------------------------------
	const size_t MeshInfo::getRandomTriangleIndex (void)
	{
		size_t index;
		if (mDistribution == MSD_HOMOGENEOUS || mDistribution == MSD_HETEROGENEOUS_1)
		{
			index = (size_t)getGaussianRandom((Real)_triangles.size() - 1);
		}
		else
			index = (size_t)Math::RangeRandom(0.0f, (Real)(_triangles.size() - 1));

		return index;
	}

	//-----------------------------------------------------------------------
	const Triangle::PositionAndNormal MeshInfo::getRandomPositionAndNormal (const size_t triangleIndex)
	{
		Triangle triangle = getTriangle(triangleIndex);
		Triangle::PositionAndNormal pAndN;
		pAndN.position = Vector3::ZERO;
		pAndN.normal = Vector3::ZERO;
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
	void MeshInfo::getMeshInformation(	Ogre::MeshPtr mesh,
										const Vector3 &position,
										const Quaternion &orient,
										const Vector3 &scale)
	{
		size_t vertexCount = 0;
		size_t indexCount = 0;
		Vector3* vertices = 0;
		Vector3* normals;
		unsigned long* indices = 0;

		bool added_shared = false;
		size_t current_offset = 0;
		size_t shared_offset = 0;
		size_t next_offset = 0;
		size_t index_offset = 0;

		// Calculate how many vertices and indices we're going to need
		for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
		{
			Ogre::SubMesh* submesh = mesh->getSubMesh( i );

			// We only need to add the shared vertices once
			if(submesh->useSharedVertices)
			{
				if( !added_shared )
				{
					vertexCount += mesh->sharedVertexData->vertexCount;
					added_shared = true;
				}
			}
			else
			{
				vertexCount += submesh->vertexData->vertexCount;
			}

			// Add the indices
			indexCount += submesh->indexData->indexCount;
		}

		// Allocate space for the vertices and indices
		vertices = new Vector3[vertexCount];
		normals = new Vector3[vertexCount];
		indices = new unsigned long[indexCount];
		added_shared = false;

		// Run through the submeshes again, adding the data into the arrays
		for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
		{
			Ogre::SubMesh* submesh = mesh->getSubMesh(i);
			Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

			if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
			{
				if(submesh->useSharedVertices)
				{
					added_shared = true;
					shared_offset = current_offset;
				}

				const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
				const Ogre::VertexElement* normalElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
				Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
				unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
				float* pReal;

				for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
				{
					posElem->baseVertexPointerToElement(vertex, &pReal);
					Vector3 pt(pReal[0], pReal[1], pReal[2]);
					vertices[current_offset + j] = (orient * (pt * scale)) + position;

					normalElem->baseVertexPointerToElement(vertex, &pReal);
					Vector3 nt(pReal[0], pReal[1], pReal[2]);
					normals[current_offset + j] = nt;
				}
      
				vbuf->unlock();
				next_offset += vertex_data->vertexCount;
			}

			Ogre::IndexData* index_data = submesh->indexData;
			size_t numTris = index_data->indexCount / 3;
			Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
    		bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
			unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);
			size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;

			size_t numTrisMultThree = numTris*3;
			if ( use32bitindexes )
			{
				for ( size_t k = 0; k < numTrisMultThree; ++k)
				{
					indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
				}
			}
			else
			{
				for ( size_t k = 0; k < numTrisMultThree; ++k)
				{
					indices[index_offset++] = static_cast<unsigned long>(pShort[k]) + static_cast<unsigned long>(offset);
				}
			}

			ibuf->unlock();
			current_offset = next_offset;
		}

		// Create triangles from the retrieved data
		for (size_t k = 0; k < indexCount-1; k+=3)
		{
			Triangle t;
			t.v1 = vertices [indices[k]];
			t.vn1 = normals [indices[k]];

			t.v2 = vertices [indices[k+1]];
			t.vn2 = normals [indices[k+1]];

			t.v3 = vertices [indices[k+2]];
			t.vn3 = normals [indices[k+2]];

			t.calculateSquareSurface();
			t.calculateSurfaceNormal();
			t.calculateEdgeNormals();
			_triangles.push_back(t);
		}

		// Delete intermediate arrays
		delete [] indices;
		delete [] normals;
		delete [] vertices;

		// Sort the triangle on their size, if needed (only if a gaussian random number generator
		// function is used to perform a random lookup of a triangle)
		if (mDistribution == MSD_HOMOGENEOUS)
			sort(_triangles.begin(), _triangles.end(), SortDescending());
		else
			if (mDistribution == MSD_HETEROGENEOUS_1)
				sort(_triangles.begin(), _triangles.end(), SortAscending());
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	MeshSurfaceEmitter::MeshSurfaceEmitter(void) : 
		ParticleEmitter(),
		mMeshName(StringUtil::BLANK),
		mOrientation(Quaternion::IDENTITY),
		mScale(DEFAULT_SCALE),
		mDistribution(DEFAULT_DISTRIBUTION),
		mMeshInfo(0),
		mTriangleIndex(0),
		mDirectionSet(false)
	{
	}
	//-----------------------------------------------------------------------
	MeshSurfaceEmitter::~MeshSurfaceEmitter(void)
    {
		if (mMeshInfo)
		{
			PU_DELETE_T(mMeshInfo, MeshInfo, MEMCATEGORY_SCENE_OBJECTS);
			mMeshInfo = 0;
		}
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::_prepare(ParticleTechnique* particleTechnique)
    {
		// Build the data
		if (mMeshName != StringUtil::BLANK)
		{
			build();
		}
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::_unprepare(ParticleTechnique* particleTechnique)
    {
		// Todo
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::_initParticlePosition(Particle* particle)
	{
		Triangle::PositionAndNormal pAndN;
		pAndN.position = Vector3::ZERO;
		pAndN.normal = Vector3::ZERO;
		mDirectionSet = false;

		if (mMeshInfo)
		{
			getDerivedPosition();
			mTriangleIndex = mMeshInfo->getRandomTriangleIndex (); // Get a random triangle index
			pAndN = mMeshInfo->getRandomPositionAndNormal(mTriangleIndex); // Determine position and normal
			ParticleSystem* sys = mParentTechnique->getParentSystem();
			if (mAutoDirection)
			{
				if (pAndN.normal != Vector3::ZERO)
				{
					// Set position and direction of the particle
					if (sys)
					{
						particle->position = mDerivedPosition + sys->getDerivedOrientation() * (_mEmitterScale * pAndN.position);
					}
					else
					{
						particle->position = mDerivedPosition + _mEmitterScale * pAndN.position;
					}

					// The value of the direction vector that has been set does not have a meaning
					Radian angle(mDynamicAttributeHelper.calculate(mDynAngle, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart()));
					if (angle != Radian(0))
					{
						particle->direction = (pAndN.normal).randomDeviant(angle, mUpVector);
					}
					else
					{
						particle->direction = pAndN.normal;
					}

					particle->originalDirection = particle->direction;
					mDirectionSet = true;
				}
			}
			else
			{
				// Set position of the particle
				if (sys)
				{
					particle->position = mDerivedPosition + sys->getDerivedOrientation() * (_mEmitterScale * pAndN.position);
				}
				else
				{
					particle->position = mDerivedPosition + _mEmitterScale * pAndN.position;
				}
			}
	
			particle->originalPosition = particle->position;
		}
	}
    //-----------------------------------------------------------------------
	unsigned short MeshSurfaceEmitter::_calculateRequestedParticles(Real timeElapsed)
	{
		if (mMeshInfo)
		{
			return ParticleEmitter::_calculateRequestedParticles(timeElapsed);
		}

		return 0;
	}
	//-----------------------------------------------------------------------
    void MeshSurfaceEmitter::_initParticleDirection(Particle* particle)
    {
		// Only determine direction if it hasn't been calculated yet
		if (!mDirectionSet)
		{
			ParticleEmitter::_initParticleDirection(particle);
		}
    }
    //-----------------------------------------------------------------------
	const String& MeshSurfaceEmitter::getMeshName(void) const
	{
		return mMeshName;
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::setMeshName(const String& meshName, bool doBuild)
	{
		mMeshName = meshName;

		// If needed, build the data needed for emitting particles
		if (doBuild)
		{
			build();
		}
	}
	//-----------------------------------------------------------------------
	const MeshInfo::MeshSurfaceDistribution MeshSurfaceEmitter::getDistribution (void) const
	{
		return mDistribution;
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::setDistribution(MeshInfo::MeshSurfaceDistribution distribution)
	{
		mDistribution = distribution;
	}
	//-----------------------------------------------------------------------
	const Vector3& MeshSurfaceEmitter::getScale (void) const
	{
		return mScale;
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::setScale (const Vector3& scale)
	{
		mScale = scale;
	}
    //-----------------------------------------------------------------------
	void MeshSurfaceEmitter::build(void)
	{
		// Delete the mesh info if already existing
		if (mMeshInfo)
		{
			PU_DELETE_T(mMeshInfo, MeshInfo, MEMCATEGORY_SCENE_OBJECTS);
			mMeshInfo = 0;
		}

		// Generate meshinfo.
		mMeshInfo = PU_NEW_T(MeshInfo, MEMCATEGORY_SCENE_OBJECTS)(mMeshName, mDistribution, mOrientation, mScale);
	}
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);
		MeshSurfaceEmitter* meshSurfaceEmitter = static_cast<MeshSurfaceEmitter*>(emitter);
		meshSurfaceEmitter->mMeshName = mMeshName;
		meshSurfaceEmitter->mDistribution = mDistribution;
		meshSurfaceEmitter->mOrientation = mOrientation;
		meshSurfaceEmitter->mScale = mScale;
	}
}
