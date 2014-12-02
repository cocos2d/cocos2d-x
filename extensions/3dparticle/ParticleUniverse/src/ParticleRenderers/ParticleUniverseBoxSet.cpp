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

#include "ParticleRenderers/ParticleUniverseBoxSet.h"
#include "ParticleRenderers/ParticleUniverseBox.h"
#include "OgreNode.h"
#include "OgreHardwareBufferManager.h"
#include "ParticleUniverseCamera.h"
#include "OgreRoot.h"
#include "ParticleUniverseSimpleSphere.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	BoxSet::BoxSet(void) :
		PrimitiveShapeSet(),
		mAutoExtendPool(true),
		mVertexData(0),
		mIndexData(0),
		mBuffersCreated(false),
		mPoolSize(0),
		mExternalData(false)
	{
		setDefaultDimensions(100, 100, 100);
		_initTextCoord();
	}
	//-----------------------------------------------------------------------
	BoxSet::BoxSet(const String& name, unsigned int poolSize, bool externalData) :
		PrimitiveShapeSet(name, poolSize, externalData),
		mAutoExtendPool(true),
		mVertexData(0),
		mIndexData(0),
		mBuffersCreated(false),
		mPoolSize(poolSize),
		mExternalData(externalData)
	{
		setDefaultDimensions(100, 100, 100);
		setPoolSize(poolSize);
		_initTextCoord();
	}
	//-----------------------------------------------------------------------
	BoxSet::~BoxSet(void)
	{
		// Free pool items
		BoxPool::iterator i;
		for (i = mBoxPool.begin(); i != mBoxPool.end(); ++i)
		{
			PU_DELETE *i;
		}

		// Delete buffers
		_destroyBuffers();
	}
    //-----------------------------------------------------------------------
	Box* BoxSet::createBox(const Vector3& position)
    {
		if(mFreeBoxes.empty())
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

        // Get a new box
        Box* newBox = mFreeBoxes.front();
		mActiveBoxes.splice(mActiveBoxes.end(), mFreeBoxes, mFreeBoxes.begin());
		newBox->setPosition(position);
        newBox->resetDimensions();
        newBox->_notifyOwner(this);

		// Merge
		Real adjust = std::max(mDefaultWidth, mDefaultHeight);
		adjust = std::max(adjust, mDefaultDepth);
        Vector3 vecAdjust(adjust, adjust, adjust);
		Vector3 newMin = position - vecAdjust;
		Vector3 newMax = position + vecAdjust;

        mAABB.merge(newMin);
        mAABB.merge(newMax);

		Real sqlen = std::max(newMin.squaredLength(), newMax.squaredLength());
		mBoundingRadius = std::max(mBoundingRadius, Math::Sqrt(sqlen));

        return newBox;
	}
	//-----------------------------------------------------------------------
	Box* BoxSet::createBox(Real x, Real y, Real z)
	{
		return createBox(Vector3( x, y, z ));
	}
	//-----------------------------------------------------------------------
	unsigned int BoxSet::getNumBoxes(void) const
	{
		return static_cast<int>(mActiveBoxes.size());
	}
	//-----------------------------------------------------------------------
	void BoxSet::clear(void)
	{
		mFreeBoxes.splice(mFreeBoxes.end(), mActiveBoxes);
	}
	//-----------------------------------------------------------------------
	Box* BoxSet::getBox(unsigned int index) const
	{
		assert(index < mActiveBoxes.size() && "Box index out of bounds." );

        ActiveBoxList::const_iterator it;
		if(index >= (mActiveBoxes.size() >> 1))
		{
			index = static_cast<unsigned int>(mActiveBoxes.size()) - index;
			for(it = mActiveBoxes.end(); index; --index, --it );
		}
		else
		{
			for(it = mActiveBoxes.begin(); index; --index, ++it );
		}

		return *it;
    }
	//-----------------------------------------------------------------------
	void BoxSet::removeBox(unsigned int index)
	{
		assert(index < mActiveBoxes.size() && "Box index out of bounds." );

        ActiveBoxList::iterator it;
        if(index >= (mActiveBoxes.size() >> 1 ))
		{
			index = static_cast<unsigned int>(mActiveBoxes.size()) - index;
			for(it = mActiveBoxes.end(); index; --index, --it );
		}
		else
		{
			for(it = mActiveBoxes.begin(); index; --index, ++it );
		}

		mFreeBoxes.splice(mFreeBoxes.end(), mActiveBoxes, it);
    }
	//-----------------------------------------------------------------------
	void BoxSet::removeBox(Box* box)
	{
		ActiveBoxList::iterator it = std::find(mActiveBoxes.begin(), mActiveBoxes.end(), box);
		assert(it != mActiveBoxes.end() && "Box isn't in the active list." );

		mFreeBoxes.splice(mFreeBoxes.end(), mActiveBoxes, it);
	}
	//-----------------------------------------------------------------------
	void BoxSet::setDefaultDimensions(Real width, Real height, Real depth)
	{
		mDefaultWidth = width;
		mDefaultHeight = height;
		mDefaultDepth = depth;
		mDefaultHalfWidth = 0.5f * width;
		mDefaultHalfHeight = 0.5f * height;
		mDefaultHalfDepth = 0.5f * depth;
		_genDefaultCorners();
	}
	//-----------------------------------------------------------------------
	void BoxSet::setDefaultWidth(Real width)
	{
		mDefaultWidth = width;
		mDefaultHalfWidth = 0.5f * width;
		_genDefaultCorners();
	}
	//-----------------------------------------------------------------------
	Real BoxSet::getDefaultWidth(void) const
	{
		return mDefaultWidth;
	}
	//-----------------------------------------------------------------------
	void BoxSet::setDefaultHeight(Real height)
	{
		mDefaultHeight = height;
		mDefaultHalfHeight = 0.5f * height;
		_genDefaultCorners();
	}
	//-----------------------------------------------------------------------
	Real BoxSet::getDefaultHeight(void) const
	{
		return mDefaultHeight;
	}
	//-----------------------------------------------------------------------
	void BoxSet::setDefaultDepth(Real depth)
	{
		mDefaultDepth = depth;
		mDefaultHalfDepth = 0.5f * depth;
		_genDefaultCorners();
	}
	//-----------------------------------------------------------------------
	Real BoxSet::getDefaultDepth(void) const
	{
		return mDefaultDepth;
	}
	//-----------------------------------------------------------------------
	void BoxSet::beginBoxes(size_t numBoxes)
    {
		// Create vertex / index buffers
		if(!mBuffersCreated)
			_createBuffers();

        mNumVisibleBoxes = 0;

		if (numBoxes)
		{
			size_t boxSize;
			numBoxes = std::min(mPoolSize, numBoxes);

			// Corners of the box + extra vertices for texture mapping
			boxSize = mMainBuf->getVertexSize() * 16;
			assert (numBoxes * boxSize <= mMainBuf->getSizeInBytes());

			mLockPtr = static_cast<float*>(
				mMainBuf->lock(0, numBoxes * boxSize, 
				Ogre::HardwareBuffer::HBL_DISCARD));
		}
		else // lock the entire thing
			mLockPtr = static_cast<float*>(
				mMainBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD) );
	}
	//-----------------------------------------------------------------------
	void BoxSet::injectBox(Box& box)
	{
		if (mNumVisibleBoxes == mPoolSize) return;

		if (!boxVisible(mCurrentCamera, box)) return;

		// Generate vertices
		_genVertices(box);
        
		mNumVisibleBoxes++;
	}
    //-----------------------------------------------------------------------
	void BoxSet::endBoxes(void)
	{
		mMainBuf->unlock();
	}
	//-----------------------------------------------------------------------
	void BoxSet::setBounds(const AxisAlignedBox& box, Real radius)
	{
		mAABB = box;
		mBoundingRadius = radius;
	}
    //-----------------------------------------------------------------------
    void BoxSet::_updateBounds(void)
    {
        if (mActiveBoxes.empty())
        {
            // No boxes
            mAABB.setNull();
			mBoundingRadius = 0.0f;
        }
        else
        {
			Real maxSqLen = -1.0f;

            Vector3 min(Math::POS_INFINITY, Math::POS_INFINITY, Math::POS_INFINITY);
            Vector3 max(Math::NEG_INFINITY, Math::NEG_INFINITY, Math::NEG_INFINITY);
            ActiveBoxList::iterator i, iend;

            iend = mActiveBoxes.end();
            for (i = mActiveBoxes.begin(); i != iend; ++i)
            {
                const Vector3& pos = (*i)->getPosition();
                min.makeFloor(pos);
                max.makeCeil(pos);

				maxSqLen = std::max(maxSqLen, pos.squaredLength());
            }

			Real adjust = std::max(mDefaultWidth, mDefaultHeight);
            Vector3 vecAdjust(adjust, adjust, adjust);
            min -= vecAdjust;
            max += vecAdjust;

            mAABB.setExtents(min, max);
			mBoundingRadius = Math::Sqrt(maxSqLen);
        }

        if (mParentNode)
            mParentNode->needUpdate();

    }
	//-----------------------------------------------------------------------
	void BoxSet::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
		if (!mExternalData)
		{
			beginBoxes(mActiveBoxes.size());
			ActiveBoxList::iterator it;
			ActiveBoxList::iterator itEnd = mActiveBoxes.end();
			for(it = mActiveBoxes.begin(); it != itEnd; ++it)
			{
				injectBox(*(*it));
			}
			endBoxes();
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
	void BoxSet::getRenderOperation(Ogre::RenderOperation& op)
	{
		op.vertexData = mVertexData;
		op.vertexData->vertexStart = 0;
		op.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		op.useIndexes = true;
		op.vertexData->vertexCount = mNumVisibleBoxes * 16;
		op.indexData = mIndexData;
		op.indexData->indexCount = mNumVisibleBoxes * 36; // 36 indices
		op.indexData->indexStart = 0;
	}
	//-----------------------------------------------------------------------
	void BoxSet::setAutoextend(bool autoextend)
	{
		mAutoExtendPool = autoextend;
	}
	//-----------------------------------------------------------------------
	bool BoxSet::isAutoextend(void) const
	{
		return mAutoExtendPool;
	}
	//-----------------------------------------------------------------------
	void BoxSet::setPoolSize(size_t size)
	{
		if (!mExternalData)
		{
			size_t currSize = mBoxPool.size();
			if (currSize >= size)
				return;

			this->increasePool(size);

			for(size_t i = currSize; i < size; ++i)
			{
				// Add new items to the queue
				mFreeBoxes.push_back(mBoxPool[i]);
			}
		}

		mPoolSize = size;
		_destroyBuffers();
	}
	//-----------------------------------------------------------------------
	void BoxSet::_createBuffers(void)
	{
		// Create vertex buffer
		mVertexData = PU_NEW Ogre::VertexData();
		mVertexData->vertexCount = mPoolSize * 16;

        mVertexData->vertexStart = 0;
		Ogre::VertexDeclaration* decl = mVertexData->vertexDeclaration;
		Ogre::VertexBufferBinding* binding = mVertexData->vertexBufferBinding;

		// Create Vertices, Colour and Texture Coordinates
		size_t offset = 0;
		decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
//		decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
//		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
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
		const size_t ibufCount = 36;
		mIndexData = PU_NEW Ogre::IndexData();
		mIndexData->indexStart = 0;
		mIndexData->indexCount = mPoolSize * ibufCount;
		mIndexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().
			createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT,
			mIndexData->indexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

		ushort* pIdx = static_cast<ushort*>(
			mIndexData->indexBuffer->lock(0,
			mIndexData->indexBuffer->getSizeInBytes(),
			Ogre::HardwareBuffer::HBL_DISCARD));

		for(size_t idx, idxOff, box = 0; box < mPoolSize; ++box)
		{
			// Do indexes
			idx = box * ibufCount;
			idxOff = box * 16;

			pIdx[idx] = static_cast<unsigned short>(idxOff + 4);
			pIdx[idx+1] = static_cast<unsigned short>(idxOff + 6);
			pIdx[idx+2] = static_cast<unsigned short>(idxOff + 2);

			pIdx[idx+3] = static_cast<unsigned short>(idxOff + 2);
			pIdx[idx+4] = static_cast<unsigned short>(idxOff + 0);
			pIdx[idx+5] = static_cast<unsigned short>(idxOff + 4);

			pIdx[idx+6] = static_cast<unsigned short>(idxOff + 1);
			pIdx[idx+7] = static_cast<unsigned short>(idxOff + 3);
			pIdx[idx+8] = static_cast<unsigned short>(idxOff + 7);

			pIdx[idx+9] = static_cast<unsigned short>(idxOff + 7);
			pIdx[idx+10] = static_cast<unsigned short>(idxOff + 5);
			pIdx[idx+11] = static_cast<unsigned short>(idxOff + 1);

			pIdx[idx+12] = static_cast<unsigned short>(idxOff + 8);
			pIdx[idx+13] = static_cast<unsigned short>(idxOff + 9);
			pIdx[idx+14] = static_cast<unsigned short>(idxOff + 13);

			pIdx[idx+15] = static_cast<unsigned short>(idxOff + 13);
			pIdx[idx+16] = static_cast<unsigned short>(idxOff + 12);
			pIdx[idx+17] = static_cast<unsigned short>(idxOff + 8);

			pIdx[idx+18] = static_cast<unsigned short>(idxOff + 10);
			pIdx[idx+19] = static_cast<unsigned short>(idxOff + 14);
			pIdx[idx+20] = static_cast<unsigned short>(idxOff + 15);

			pIdx[idx+21] = static_cast<unsigned short>(idxOff + 15);
			pIdx[idx+22] = static_cast<unsigned short>(idxOff + 11);
			pIdx[idx+23] = static_cast<unsigned short>(idxOff + 10);

			pIdx[idx+24] = static_cast<unsigned short>(idxOff + 8);
			pIdx[idx+25] = static_cast<unsigned short>(idxOff + 10);
			pIdx[idx+26] = static_cast<unsigned short>(idxOff + 11);

			pIdx[idx+27] = static_cast<unsigned short>(idxOff + 11);
			pIdx[idx+28] = static_cast<unsigned short>(idxOff + 9);
			pIdx[idx+29] = static_cast<unsigned short>(idxOff + 8);

			pIdx[idx+30] = static_cast<unsigned short>(idxOff + 4);
			pIdx[idx+31] = static_cast<unsigned short>(idxOff + 5);
			pIdx[idx+32] = static_cast<unsigned short>(idxOff + 7);

			pIdx[idx+33] = static_cast<unsigned short>(idxOff + 7);
			pIdx[idx+34] = static_cast<unsigned short>(idxOff + 6);
			pIdx[idx+35] = static_cast<unsigned short>(idxOff + 4);
		}
		
		mIndexData->indexBuffer->unlock();

        mBuffersCreated = true;
    }
	//-----------------------------------------------------------------------
	void BoxSet::_destroyBuffers(void)
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
	unsigned int BoxSet::getPoolSize(void) const
	{
		return static_cast<unsigned int>(mBoxPool.size());
	}
	//-----------------------------------------------------------------------
	bool BoxSet::boxVisible(Camera* cam, const Box& box)
	{
		// If not individually culled it is always visible
		if (!mCullIndividual) return true;

		// Culling based on sphere
		SimpleSphere sph;
		Ogre::Matrix4 xworld;
		getWorldTransforms(&xworld);
		sph.setCenter(xworld.transformAffine(box.mPosition));

		if (box.mOwnDimensions)
		{
			Real max = std::max(box.mWidth, box.mHeight);
			max = std::max(box.mDepth, max);
			sph.setRadius(max);
		}
		else
		{
			Real max = std::max(mDefaultWidth, mDefaultHeight);
			max = std::max(mDefaultDepth, max);
			sph.setRadius(max);
		}

		return cam->isVisible(sph);
	}
	//-----------------------------------------------------------------------
	void BoxSet::increasePool(size_t size)
	{
		size_t oldSize = mBoxPool.size();

		// Increase size
		mBoxPool.reserve(size);
		mBoxPool.resize(size);

		// Create new boxes
		for(size_t i = oldSize; i < size; ++i)
			mBoxPool[i] = PU_NEW Box();
	}
	//-----------------------------------------------------------------------
	void BoxSet::_genDefaultCorners(void)
	{
		mDefaultCorners[0].x = - mDefaultHalfWidth;
		mDefaultCorners[0].y = - mDefaultHalfHeight;
		mDefaultCorners[0].z = - mDefaultHalfDepth;
	
		mDefaultCorners[1].x = mDefaultHalfWidth;
		mDefaultCorners[1].y = - mDefaultHalfHeight;
		mDefaultCorners[1].z = - mDefaultHalfDepth;

		mDefaultCorners[2].x = - mDefaultHalfWidth;
		mDefaultCorners[2].y = mDefaultHalfHeight;
		mDefaultCorners[2].z = - mDefaultHalfDepth;

		mDefaultCorners[3].x = mDefaultHalfWidth;
		mDefaultCorners[3].y = mDefaultHalfHeight;
		mDefaultCorners[3].z = - mDefaultHalfDepth;

		mDefaultCorners[4].x = - mDefaultHalfWidth;
		mDefaultCorners[4].y = - mDefaultHalfHeight;
		mDefaultCorners[4].z = mDefaultHalfDepth;

		mDefaultCorners[5].x = mDefaultHalfWidth;
		mDefaultCorners[5].y = - mDefaultHalfHeight;
		mDefaultCorners[5].z = mDefaultHalfDepth;

		mDefaultCorners[6].x = - mDefaultHalfWidth;
		mDefaultCorners[6].y = mDefaultHalfHeight;
		mDefaultCorners[6].z = mDefaultHalfDepth;

		mDefaultCorners[7].x = mDefaultHalfWidth;
		mDefaultCorners[7].y = mDefaultHalfHeight;
		mDefaultCorners[7].z = mDefaultHalfDepth;

		mDefaultCorners[8].x = - mDefaultHalfWidth;
		mDefaultCorners[8].y = - mDefaultHalfHeight;
		mDefaultCorners[8].z = - mDefaultHalfDepth;

		mDefaultCorners[9].x = mDefaultHalfWidth;
		mDefaultCorners[9].y = - mDefaultHalfHeight;
		mDefaultCorners[9].z = - mDefaultHalfDepth;

		mDefaultCorners[10].x = - mDefaultHalfWidth;
		mDefaultCorners[10].y = mDefaultHalfHeight;
		mDefaultCorners[10].z = - mDefaultHalfDepth;

		mDefaultCorners[11].x = mDefaultHalfWidth;
		mDefaultCorners[11].y = mDefaultHalfHeight;
		mDefaultCorners[11].z = - mDefaultHalfDepth;

		mDefaultCorners[12].x = - mDefaultHalfWidth;
		mDefaultCorners[12].y = - mDefaultHalfHeight;
		mDefaultCorners[12].z = mDefaultHalfDepth;

		mDefaultCorners[13].x = mDefaultHalfWidth;
		mDefaultCorners[13].y = - mDefaultHalfHeight;
		mDefaultCorners[13].z = mDefaultHalfDepth;

		mDefaultCorners[14].x = - mDefaultHalfWidth;
		mDefaultCorners[14].y = mDefaultHalfHeight;
		mDefaultCorners[14].z = mDefaultHalfDepth;

		mDefaultCorners[15].x = mDefaultHalfWidth;
		mDefaultCorners[15].y = mDefaultHalfHeight;
		mDefaultCorners[15].z = mDefaultHalfDepth;
	}
	//-----------------------------------------------------------------------
	void BoxSet::_genVertices(Box& box)
	{
		Ogre::RGBA colour;
		Ogre::Root::getSingleton().convertColourValue(box.mColour, &colour);
		Ogre::RGBA* pCol;

		if (!box.mOwnDimensions)
		{
			for (size_t i = 0; i < 16; ++i)
			{
				// Vertex
				Ogre::Vector3 corner = Ogre::Vector3::ZERO;
				if (box.mOrientation == Ogre::Quaternion::IDENTITY)
				{
					// Boxes didn´t rotate
					corner = mDefaultCorners[i];
				}
				else
				{
					// Take box orientation into account
					corner = box.mOrientation * mDefaultCorners[i];
				}

				*mLockPtr++ = corner.x + box.mPosition.x;
				*mLockPtr++ = corner.y + box.mPosition.y;
				*mLockPtr++ = corner.z + box.mPosition.z;

				// Colour
				pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(mLockPtr));
				*pCol++ = colour;
				mLockPtr = static_cast<float*>(static_cast<void*>(pCol));

				// Texture Coordinates
				*mLockPtr++ = mTextCoord[i].x;
				*mLockPtr++ = mTextCoord[i].y;
			}
		}
		else
		{	
			/** Loop twice through the corners of the box, because we have duplicated the number of
				vertices, because of the texture mapping.
			*/
			size_t t = 0;
			for (size_t i = 0; i < 2; ++i)
			{
				for (size_t j = 0; j < 8; ++j)
				{
					// Vertex: The box itself takes position and orientation into account
					*mLockPtr++ = box.getWorldspaceCorner(j).x;
					*mLockPtr++ = box.getWorldspaceCorner(j).y;
					*mLockPtr++ = box.getWorldspaceCorner(j).z;

					// Colour
					pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(mLockPtr));
					*pCol++ = colour;
					mLockPtr = static_cast<float*>(static_cast<void*>(pCol));

					// Texture Coordinates
					*mLockPtr++ = mTextCoord[t].x;
					*mLockPtr++ = mTextCoord[t].y;
					t++;
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	const String& BoxSet::getMovableType(void) const
	{
		return BoxSetFactory::PU_FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	void BoxSet::_initTextCoord(void)
	{
		mTextCoord [0] = Vector2(0.0f, 0.0f);
		mTextCoord [1] = Vector2(0.0f, 1.0f);
		mTextCoord [2] = Vector2(0.5f, 0.0f);
		mTextCoord [3] = Vector2(0.5f, 1.0f);

		mTextCoord [4] = Vector2(0.0f, 0.33f);
		mTextCoord [5] = Vector2(0.0f, 0.66f);
		mTextCoord [6] = Vector2(0.5f, 0.33f);
		mTextCoord [7] = Vector2(0.5f, 0.66f);

		mTextCoord [8] = Vector2(0.5f, 0.33f);
		mTextCoord [9] = Vector2(1.0f, 0.33f);
		mTextCoord [10] = Vector2(0.5f, 0.66f);
		mTextCoord [11] = Vector2(1.0f, 0.66f);

		mTextCoord [12] = Vector2(0.5f, 0.0f);
		mTextCoord [13] = Vector2(1.0f, 0.0f);
		mTextCoord [14] = Vector2(0.5f, 1.0f);
		mTextCoord [15] = Vector2(1.0f, 1.0f);
	}
	//-----------------------------------------------------------------------
	String BoxSetFactory::PU_FACTORY_TYPE_NAME = "BoxSet";
	//-----------------------------------------------------------------------
	const String& BoxSetFactory::getType(void) const
	{
		return PU_FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	Ogre::MovableObject* BoxSetFactory::createInstanceImpl(const String& name, const Ogre::NameValuePairList* params)
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
			return PU_NEW BoxSet(name, poolSize, externalData);
		}
		else
		{
			return PU_NEW BoxSet(name);
		}
	}
	//-----------------------------------------------------------------------
	void BoxSetFactory::destroyInstance(Ogre::MovableObject* obj)
	{
		PU_DELETE obj;
	}

}
