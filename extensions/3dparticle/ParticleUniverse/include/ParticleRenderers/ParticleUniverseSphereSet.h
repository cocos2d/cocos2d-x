/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_SET_H__
#define __PU_SPHERE_SET_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleRenderers/ParticleUniversePrimitiveShapeSet.h"

namespace ParticleUniverse
{
	class Sphere;

	/** The SphereSet and Sphere classes are comparable with the BillboardSet and Billboard classes in Ogre, instead
		Spheres are rendered.
    */
	class _ParticleUniverseExport SphereSet : public PrimitiveShapeSet
	{
		protected:
			/** Default radius of each sphere
			*/
			Real mDefaultRadius;

			/** Flag indicating whether to autoextend pool
			*/
			bool mAutoExtendPool;

			typedef list<Sphere*> ActiveSphereList;
			typedef list<Sphere*> FreeSphereList;
			typedef vector<Sphere*> SpherePool;

			/** Active sphere list.
			@remarks
				This is a linked list of pointers to spheres in the sphere pool.
			*/
			ActiveSphereList mActiveSpheres;

			/** Free sphere queue.
			*/
			FreeSphereList mFreeSpheres;

			/** Pool of sphere instances for use and reuse in the active sphere list.
			*/
			SpherePool mSpherePool;

			/** The vertex position data for all spheres in this set.
			*/
			Ogre::VertexData* mVertexData;

			/** The number of vertices per sphere.
			*/
			size_t mVertexCountPerSphere;

			/** Shortcut to main buffer
			*/
			Ogre::HardwareVertexBufferSharedPtr mMainBuf;

			/** Locked pointer to buffer
			*/
			float* mLockPtr;

			/** Locked pointer to index buffer
			*/
			ushort* pIdx;

			/** The vertex index data for all spheres in this set (1 set only)
			*/
			Ogre::IndexData* mIndexData;

			/** The number of indeces per sphere.
			*/
			size_t mIndexCountPerSphere;

			typedef vector<Ogre::FloatRect> TextureCoordSets;
			TextureCoordSets mTextureCoords;

			/** Internal method for culling individual sphere
			*/
			inline bool sphereVisible(Camera* cam, const Sphere& sphere);

			/** Number of visible sphere
			*/
			unsigned short mNumVisibleSpheres;

			/** Internal method for increasing pool size
			*/
			void increasePool(size_t size);

			/** Internal method for generating vertex data
			*/
			void _genVertices(Sphere& sphere);

			/** Number of rings of which the sphere consists
			*/
			unsigned int mNumberOfRings;

			/** Number of segments of which the sphere consists
			*/
			unsigned int mNumberOfSegments;

			/** Internal vertex counter
			*/
			unsigned short mVertexIndex;

			/** Helper function to calculate number of number of vertices and indices per sphere
			*/
			void _calculateVertexAndIndexPerSphere(void);


		private:
			/** Flag indicating whether the HW buffers have been created.
			*/
			bool mBuffersCreated;

			/** The number of spheres in the pool.
			*/
			size_t mPoolSize;
        
			/** Is external sphere data in use?
			*/
			bool mExternalData;

			/** Internal method creates vertex and index buffers.
			*/
			void _createBuffers(void);
        
			/** Internal method destroys vertex and index buffers.
			*/
			void _destroyBuffers(void);

		public:
			/** Default constructor.
			*/
			SphereSet(const String& name, unsigned int poolSize = 20, bool externalData = false);

			/** Default constructor.
			*/
			SphereSet(void);

			/** Default destructor.
			*/
	        virtual ~SphereSet(void);

			/** Creates a new sphere and adds it to this set.
			*/
			Sphere* createSphere(const Vector3& position);

			/** Creates a new sphere and adds it to this set.
			*/
			Sphere* createSphere(Real x, Real y, Real z);

			/** Returns the number of active spheres which currently make up this set.
			*/
			unsigned int getNumSpheres(void) const;
			
			/** Tells the set whether to allow automatic extension of the pool of spheres.
			*/
			void setAutoextend(bool autoextend);
			
			/** Returns true if the sphere pool automatically extends.
			*/
			bool isAutoextend(void) const;

			/** Adjusts the size of the pool of spheres available in this set.
			*/
			void setPoolSize(size_t size);

			/** Returns the current size of the sphere pool.
			*/
			unsigned int getPoolSize(void) const;

			/** Empties this set of all spheres.
			*/
			void clear(void);

			/** Returns a pointer to the sphere at the supplied index.
			*/
			Sphere* getSphere(unsigned int index) const;

			/** Removes the sphere at the supplied index.
			*/
			void removeSphere(unsigned int index);

			/** Removes a sphere from the set.
			*/
			void removeSphere(Sphere* sphere);

			/** Sets the default radius of the spheres in this set.
			*/
			void setDefaultRadius(Real radius);

			/** See setDefaultRadius
			*/
			Real getDefaultRadius(void) const;

			/** Set the number of rings of which this sphere consists.
			*/
			void setNumberOfRings(unsigned int numberOfRings);

			/** Get the number of rings of which this sphere consists.
			*/
			unsigned int getNumberOfRings(void) const;

			/** Set the number of segments of which this sphere consists.
			*/
			void setNumberOfSegments(unsigned int numberOfSegments);

			/** Get the number of segments of which this sphere consists.
			*/
			unsigned int getNumberOfSegments(void) const;

			/** Begin injection of sphere data; applicable when constructing the SphereSet for external data use.
			*/
			void beginSpheres(size_t numSpheres = 0);

			/** Define a sphere.
			*/
			void injectSphere(Sphere& sphere);
        
			/** Finish defining spheres. */
			void endSpheres(void);

			/** Set the bounds of the SphereSet.
			*/
			void setBounds(const AxisAlignedBox& box, Real radius);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual void getRenderOperation(Ogre::RenderOperation& op);

			/** Overridden from MovableObject 
			*/
			virtual const String& getMovableType(void) const;

			/** Update the bounds of the sphere set
			*/
			virtual void _updateBounds(void);

			/** Sets whether spheres should be treated as being in world space. 
			*/
			void setSpheresInWorldSpace(bool ws) { mWorldSpace = ws; }
	};

	/** Factory object for creating SphereSet instances */
	class _ParticleUniverseExport SphereSetFactory : public Ogre::MovableObjectFactory
	{
	
		protected:
			Ogre::MovableObject* createInstanceImpl( const String& name, const Ogre::NameValuePairList* params);

		public:
			SphereSetFactory(void) {}
			~SphereSetFactory(void) {}

			static String PU_FACTORY_TYPE_NAME;

			const String& getType(void) const;
			void destroyInstance( Ogre::MovableObject* obj);  
	};

}

#endif
