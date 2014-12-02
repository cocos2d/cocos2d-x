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

#include "ParticleRenderers/ParticleUniverseSphereSet.h"
#include "ParticleRenderers/ParticleUniverseSphere.h"
#include "OgreNode.h"
#include "OgreHardwareBufferManager.h"
#include "OgreCamera.h"
#include "OgreRoot.h"
#include "ParticleUniverseSimpleSphere.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	SphereSet::SphereSet(void) :
		PrimitiveShapeSet(),
		mAutoExtendPool(true),
		mVertexData(0),
		mIndexData(0),
		mBuffersCreated(false),
		mPoolSize(0),
		mExternalData(false),
		mNumberOfRings(16),
		mNumberOfSegments(16),
		mLockPtr(0),
		pIdx(0),
		mDefaultRadius(20),
		mVertexIndex(1)
	{
		setNumberOfRings(16);
		setNumberOfSegments(16);
	}
	//-----------------------------------------------------------------------
	SphereSet::SphereSet(const String& name, unsigned int poolSize, bool externalData) :
		PrimitiveShapeSet(name, poolSize, externalData),
		mAutoExtendPool(true),
		mVertexData(0),
		mIndexData(0),
		mBuffersCreated(false),
		mPoolSize(poolSize),
		mExternalData(externalData),
		mNumberOfRings(16),
		mNumberOfSegments(16),
		mLockPtr(0),
		pIdx(0),
		mDefaultRadius(20),
		mVertexIndex(1)
	{
		setPoolSize(poolSize);
		setNumberOfRings(16);
		setNumberOfSegments(16);
	}
	//-----------------------------------------------------------------------
	SphereSet::~SphereSet(void)
	{
		// Free pool items
		SpherePool::iterator i;
		for (i = mSpherePool.begin(); i != mSpherePool.end(); ++i)
		{
			PU_DELETE *i;
		}

		// Delete buffers
		_destroyBuffers();
	}
    //-----------------------------------------------------------------------
	Sphere* SphereSet::createSphere(const Vector3& position)
    {
		if(mFreeSpheres.empty())
		{
			if(mAutoExtendPool)
			{
				setPoolSize(getPoolSize() * 2);
            }
			else
			{
				return 0;
			}
		}

        // Get a new sphere
        Sphere* newSphere = mFreeSpheres.front();
		mActiveSpheres.splice(mActiveSpheres.end(), mFreeSpheres, mFreeSpheres.begin());
		newSphere->setPosition(position);
        newSphere->resetRadius();
        newSphere->_notifyOwner(this);

		// Merge
        Vector3 vecAdjust(mDefaultRadius, mDefaultRadius, mDefaultRadius);
		Vector3 newMin = position - vecAdjust;
		Vector3 newMax = position + vecAdjust;
        mAABB.merge(newMin);
        mAABB.merge(newMax);
		mBoundingRadius = std::max(mBoundingRadius, mDefaultRadius);

		return newSphere;
	}
	//-----------------------------------------------------------------------
	Sphere* SphereSet::createSphere(Real x, Real y, Real z)
	{
		return createSphere(Vector3( x, y, z ));
	}
	//-----------------------------------------------------------------------
	unsigned int SphereSet::getNumSpheres(void) const
	{
		return static_cast<int>(mActiveSpheres.size());
	}
	//-----------------------------------------------------------------------
	void SphereSet::clear(void)
	{
		mFreeSpheres.splice(mFreeSpheres.end(), mActiveSpheres);
	}
	//-----------------------------------------------------------------------
	Sphere* SphereSet::getSphere(unsigned int index) const
	{
		assert(index < mActiveSpheres.size() && "Sphere index out of bounds." );

        ActiveSphereList::const_iterator it;
		if(index >= (mActiveSpheres.size() >> 1))
		{
			index = static_cast<unsigned int>(mActiveSpheres.size()) - index;
			for(it = mActiveSpheres.end(); index; --index, --it );
		}
		else
		{
			for(it = mActiveSpheres.begin(); index; --index, ++it );
		}

		return *it;
    }
	//-----------------------------------------------------------------------
	void SphereSet::removeSphere(unsigned int index)
	{
		assert(index < mActiveSpheres.size() && "Sphere index out of bounds." );

        ActiveSphereList::iterator it;
        if(index >= (mActiveSpheres.size() >> 1 ))
		{
			index = static_cast<unsigned int>(mActiveSpheres.size()) - index;
			for(it = mActiveSpheres.end(); index; --index, --it );
		}
		else
		{
			for(it = mActiveSpheres.begin(); index; --index, ++it );
		}

		mFreeSpheres.splice(mFreeSpheres.end(), mActiveSpheres, it);
    }
	//-----------------------------------------------------------------------
	void SphereSet::removeSphere(Sphere* sphere)
	{
		ActiveSphereList::iterator it = std::find(mActiveSpheres.begin(), mActiveSpheres.end(), sphere);
		assert(it != mActiveSpheres.end() && "Sphere isn't in the active list." );

		mFreeSpheres.splice(mFreeSpheres.end(), mActiveSpheres, it);
	}
	//-----------------------------------------------------------------------
	void SphereSet::setDefaultRadius(Real radius)
	{
		mDefaultRadius = radius;
	}
	//-----------------------------------------------------------------------
	Real SphereSet::getDefaultRadius(void) const
	{
		return mDefaultRadius;
	}
	//-----------------------------------------------------------------------
	void SphereSet::setNumberOfRings(unsigned int numberOfRings)
	{
		mNumberOfRings = numberOfRings;
		_calculateVertexAndIndexPerSphere();
	}
	//-----------------------------------------------------------------------
	unsigned int SphereSet::getNumberOfRings(void) const
	{
		return mNumberOfRings;
	}
	//-----------------------------------------------------------------------
	void SphereSet::setNumberOfSegments(unsigned int numberOfSegments)
	{
		mNumberOfSegments = numberOfSegments;
		_calculateVertexAndIndexPerSphere();
	}
	//-----------------------------------------------------------------------
	unsigned int SphereSet::getNumberOfSegments(void) const
	{
		return mNumberOfSegments;
	}
	//-----------------------------------------------------------------------
	void SphereSet::_calculateVertexAndIndexPerSphere(void)
	{
		mVertexCountPerSphere = (mNumberOfRings + 1) * (mNumberOfSegments + 1);
		mIndexCountPerSphere = 6 * mNumberOfRings * (mNumberOfSegments + 1);
	}
	//-----------------------------------------------------------------------
	void SphereSet::beginSpheres(size_t numSpheres)
    {
		// Create vertex / index buffers
		if(!mBuffersCreated)
			_createBuffers();

        mNumVisibleSpheres = 0;
		mVertexIndex = 1;

		if (numSpheres)
		{
			numSpheres = std::min(mPoolSize, numSpheres);
			size_t sphereVertexSize = mMainBuf->getVertexSize() * mVertexCountPerSphere;
			assert (numSpheres * sphereVertexSize <= mMainBuf->getSizeInBytes());

			mLockPtr = static_cast<float*>(
				mMainBuf->lock(0, numSpheres * sphereVertexSize, 
				Ogre::HardwareBuffer::HBL_DISCARD));

			size_t sphereIndexSize = mIndexData->indexBuffer->getIndexSize() * mIndexCountPerSphere;
			assert (numSpheres * sphereIndexSize <= mIndexData->indexBuffer->getSizeInBytes());

			pIdx = static_cast<ushort*>(
				mIndexData->indexBuffer->lock(0, numSpheres * sphereIndexSize, 
				Ogre::HardwareBuffer::HBL_DISCARD));
		}
		else
		{
			mLockPtr = static_cast<float*>(
				mMainBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

			pIdx = static_cast<ushort*>(
				mIndexData->indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
		}
	}
	//-----------------------------------------------------------------------
	void SphereSet::injectSphere(Sphere& sphere)
	{
		if (mNumVisibleSpheres == mPoolSize) return;

		if (!sphereVisible(mCurrentCamera, sphere)) return;

		// Generate vertices
		_genVertices(sphere);
        
		mNumVisibleSpheres++;
	}
    //-----------------------------------------------------------------------
	void SphereSet::endSpheres(void)
	{
		mMainBuf->unlock();
		mIndexData->indexBuffer->unlock();
	}
	//-----------------------------------------------------------------------
	void SphereSet::setBounds(const AxisAlignedBox& box, Real radius)
	{
		mAABB = box;
		mBoundingRadius = radius;
	}
    //-----------------------------------------------------------------------
    void SphereSet::_updateBounds(void)
    {
        if (mActiveSpheres.empty())
        {
            // No spheres
            mAABB.setNull();
			mBoundingRadius = 0.0f;
        }
        else
        {
			Real maxSqLen = -1.0f;

            Vector3 min(Math::POS_INFINITY, Math::POS_INFINITY, Math::POS_INFINITY);
            Vector3 max(Math::NEG_INFINITY, Math::NEG_INFINITY, Math::NEG_INFINITY);
            ActiveSphereList::iterator i, iend;

            iend = mActiveSpheres.end();
            for (i = mActiveSpheres.begin(); i != iend; ++i)
            {
                const Vector3& pos = (*i)->getPosition();
                min.makeFloor(pos);
                max.makeCeil(pos);

				maxSqLen = std::max(maxSqLen, pos.squaredLength());
            }

            Vector3 vecAdjust(mDefaultRadius, mDefaultRadius, mDefaultRadius);
            min -= vecAdjust;
            max += vecAdjust;

            mAABB.setExtents(min, max);
			mBoundingRadius = Math::Sqrt(maxSqLen);
        }

        if (mParentNode)
            mParentNode->needUpdate();

    }
	//-----------------------------------------------------------------------
	void SphereSet::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
		if (!mExternalData)
		{
			beginSpheres(mActiveSpheres.size());
			ActiveSphereList::iterator it;
			ActiveSphereList::iterator itEnd = mActiveSpheres.end();
			for(it = mActiveSpheres.begin(); it != itEnd; ++it)
			{
				injectSphere(*(*it));
			}
			endSpheres();
		}

		if( mRenderQueueIDSet )
		{
			queue->addRenderable(this, mRenderQueueID);
		}
		else
		{
			queue->addRenderable(this);
		}
	}
	//-----------------------------------------------------------------------
	void SphereSet::getRenderOperation(Ogre::RenderOperation& op)
	{
		op.vertexData = mVertexData;
		op.vertexData->vertexStart = 0;
		op.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		op.useIndexes = true;
		op.vertexData->vertexCount = mNumVisibleSpheres * mVertexCountPerSphere;
		op.indexData = mIndexData;
		op.indexData->indexCount = mNumVisibleSpheres * mIndexCountPerSphere;
		op.indexData->indexStart = 0;
	}
	//-----------------------------------------------------------------------
	void SphereSet::setAutoextend(bool autoextend)
	{
		mAutoExtendPool = autoextend;
	}
	//-----------------------------------------------------------------------
	bool SphereSet::isAutoextend(void) const
	{
		return mAutoExtendPool;
	}
	//-----------------------------------------------------------------------
	void SphereSet::setPoolSize(size_t size)
	{
		if (!mExternalData)
		{
			size_t currSize = mSpherePool.size();
			if (currSize >= size)
				return;

			this->increasePool(size);

			for(size_t i = currSize; i < size; ++i)
			{
				// Add new items to the queue
				mFreeSpheres.push_back(mSpherePool[i]);
			}
		}

		mPoolSize = size;
		_destroyBuffers();
	}
	//-----------------------------------------------------------------------
	void SphereSet::_createBuffers(void)
	{
		// Create vertex buffer
		mVertexData = PU_NEW Ogre::VertexData();
		mVertexData->vertexCount = mPoolSize * mVertexCountPerSphere;

        mVertexData->vertexStart = 0;
		Ogre::VertexDeclaration* decl = mVertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* binding = mVertexData->vertexBufferBinding;

		// Create Vertices, Normals, Colour and Texture Coordinates
		size_t offset = 0;
		decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		decl->addElement(0, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
		decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, 0);

		mMainBuf =
			Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			decl->getVertexSize(0),
			mVertexData->vertexCount,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

		// Bind
		binding->setBinding(0, mMainBuf);

		// Create indices
		const size_t ibufCount = mIndexCountPerSphere;
		mIndexData  = PU_NEW Ogre::IndexData();
		mIndexData->indexStart = 0;
		mIndexData->indexCount = mPoolSize * ibufCount;
		mIndexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().
			createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
			mIndexData->indexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

        mBuffersCreated = true;
	}
	//-----------------------------------------------------------------------
	void SphereSet::_destroyBuffers(void)
	{
		if (mVertexData)
		{
			PU_DELETE mVertexData;
			mVertexData = 0;
		}
		if (mIndexData)
		{
			PU_DELETE mIndexData;
			mIndexData = 0;
		}

		mMainBuf.setNull();

		mBuffersCreated = false;
	}
	//-----------------------------------------------------------------------
	unsigned int SphereSet::getPoolSize(void) const
	{
		return static_cast<unsigned int>(mSpherePool.size());
	}
	//-----------------------------------------------------------------------
	bool SphereSet::sphereVisible(Camera* cam, const Sphere& sphere)
	{
		// If not individually culled it is always visible
		if (!mCullIndividual) return true;

		// Culling based on sphere
		SimpleSphere sph;
		Ogre::Matrix4 xworld;
		getWorldTransforms(&xworld);
		sph.setCenter(xworld.transformAffine(sphere.mPosition));

		if (sphere.mOwnRadius)
		{
			sph.setRadius(sphere.getOwnRadius());
		}
		else
		{
			sph.setRadius(getDefaultRadius());
		}

		return cam->isVisible(sph);
	}
	//-----------------------------------------------------------------------
	void SphereSet::increasePool(size_t size)
	{
		size_t oldSize = mSpherePool.size();

		// Increase size
		mSpherePool.reserve(size);
		mSpherePool.resize(size);

		// Create new spheres
		for(size_t i = oldSize; i < size; ++i)
			mSpherePool[i] = PU_NEW Sphere();
	}
	//-----------------------------------------------------------------------
	void SphereSet::_genVertices(Sphere& sphere)
	{
		Ogre::RGBA colour;
		Ogre::Root::getSingleton().convertColourValue(sphere.mColour, &colour);
		Ogre::RGBA* pCol;
		Real radius = getDefaultRadius();
		if (sphere.mOwnRadius)
		{
			radius = sphere.getOwnRadius();
		}

		Real stepRingAngle = (Math::PI / mNumberOfRings);
		Real stepSegmentAngle = (2 * Math::PI / mNumberOfSegments);

		for(unsigned int ring = 0; ring <= mNumberOfRings; ring++)
		{
			Real r0 = radius * sinf (ring * stepRingAngle);
			Real y0 = radius * cosf (ring * stepRingAngle);

			for(unsigned int segment = 0; segment <= mNumberOfSegments; segment++)
			{
				Real x0 = r0 * sinf(segment * stepSegmentAngle);
				Real z0 = r0 * cosf(segment * stepSegmentAngle);

				// Vertex
				Vector3 orientedVertex = sphere.mOrientation * Vector3(x0, y0, z0);
				*mLockPtr++ = (float) (orientedVertex.x + sphere.mPosition.x);
				*mLockPtr++ = (float) (orientedVertex.y + sphere.mPosition.y);
				*mLockPtr++ = (float) (orientedVertex.z + sphere.mPosition.z);

				// Normal
				Vector3 vNormal = orientedVertex.normalisedCopy();
				*mLockPtr++ = (float) vNormal.x;
				*mLockPtr++ = (float) vNormal.y;
				*mLockPtr++ = (float) vNormal.z;

				// Colour
				pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(mLockPtr));
				*pCol++ = colour;
				mLockPtr = static_cast<float*>(static_cast<void*>(pCol));

				// Texture Coordinates
				*mLockPtr++ = (float) segment / (float) mNumberOfSegments;
				*mLockPtr++ = (float) ring / (float) mNumberOfRings;

				if (ring != mNumberOfRings)
				{
					// each vertex (except the last) has six indices pointing to it
					*pIdx++ = mVertexIndex + mNumberOfSegments + 1;
					*pIdx++ = mVertexIndex;
					*pIdx++ = mVertexIndex + mNumberOfSegments;
					*pIdx++ = mVertexIndex + mNumberOfSegments + 1;
					*pIdx++ = mVertexIndex + 1;
					*pIdx++ = mVertexIndex;
				}
				mVertexIndex++;
			}
		}
	}
	//-----------------------------------------------------------------------
	const String& SphereSet::getMovableType(void) const
	{
		return SphereSetFactory::PU_FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	String SphereSetFactory::PU_FACTORY_TYPE_NAME = "SphereSet";
	//-----------------------------------------------------------------------
	const String& SphereSetFactory::getType(void) const
	{
		return PU_FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	Ogre::MovableObject* SphereSetFactory::createInstanceImpl(const String& name, const Ogre::NameValuePairList* params)
	{
		bool externalData = false;
		unsigned int poolSize = 0;

		if (params != 0)
		{
			Ogre::NameValuePairList::const_iterator ni = params->find("poolSize");
			if (ni != params->end())
			{
				poolSize = StringConverter::parseUnsignedInt(ni->second);
			}
			ni = params->find("externalData");
			if (ni != params->end())
			{
				externalData = StringConverter::parseBool(ni->second);
			}
		}

		if (poolSize > 0)
		{
			return PU_NEW SphereSet(name, poolSize, externalData);
		}
		else
		{
			return PU_NEW SphereSet(name);
		}
	}
	//-----------------------------------------------------------------------
	void SphereSetFactory::destroyInstance(Ogre::MovableObject* obj)
	{
		PU_DELETE obj;
	}

}
