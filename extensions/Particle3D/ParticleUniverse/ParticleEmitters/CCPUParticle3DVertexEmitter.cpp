/****************************************************************************
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

#include "CCPUParticle3DVertexEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
//// Constants
//const unsigned short Particle3DVertexEmitter::DEFAULT_STEP = 1;
//const unsigned short Particle3DVertexEmitter::DEFAULT_SEGMENTS = 1;
//const unsigned short Particle3DVertexEmitter::DEFAULT_ITERATIONS = 1;
//
////-----------------------------------------------------------------------
//Particle3DVertexEmitter::Particle3DVertexEmitter(void) : ParticleEmitter(),
//	mPositionElement(0),
//	mVertexData(0),
//	mVertexBuffer(0),
//	mMesh(0),
//	mSubMesh(0),
//	mVertexSize(12),
//	mMaxVertexCount(0),
//	mVertexCount(0),
//	mStep(DEFAULT_STEP),
//	mSegments(DEFAULT_SEGMENTS),
//	mMeshProcessed(false),
//	mAllVerticesProcessed(false),
//	mSubMeshNumber(0),
//	mIterations(DEFAULT_ITERATIONS),
//	mMeshName(StringUtil::BLANK)
//{
//	mBuffer.setNull();
//}
////-----------------------------------------------------------------------
//unsigned short Particle3DVertexEmitter::getIterations(void) const
//{
//	return mIterations;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::setIterations(unsigned short iterations)
//{
//	mIterations = iterations;
//}
////-----------------------------------------------------------------------
//unsigned short Particle3DVertexEmitter::getSegments(void) const
//{
//	return mSegments;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::setSegments(unsigned short segments)
//{
//	mSegments = segments;
//}
////-----------------------------------------------------------------------
//unsigned short Particle3DVertexEmitter::getStep(void) const
//{
//	return mStep;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::setStep(unsigned short step)
//{
//	mStep = step;
//}
////-----------------------------------------------------------------------
//const std::string& Particle3DVertexEmitter::getMeshName(void) const
//{
//	return mMeshName;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::setMeshName(const std::string& meshName)
//{
//	_setDefaults(); // Triggers loading the new mesh
//	mMeshName = meshName;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_notifyStart (void)
//{
//	ParticleEmitter::_notifyStart();
//	_setDefaults();
//}
////-----------------------------------------------------------------------
//unsigned short Particle3DVertexEmitter::_calculateRequestedParticles(float timeElapsed)
//{
//	// Only return the requested number if the emitter can actually emit them
//	unsigned short requested = ParticleEmitter::_calculateRequestedParticles(timeElapsed);
//	if (requested <= mSpawnPositionList.size())
//	{
//		return requested;
//	}
//
//	return 0;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_initParticlePosition(Particle* particle)
//{
//	// Get the first one from the list.
//	// The _calculateRequestedParticles() ensures that there are particles in the list.
//	// All positions in mSpawnPositionList are in localspace
//	ParticleSystem* sys = mParentTechnique->getParentSystem();
//	if (sys)
//	{
//		particle->position = getDerivedPosition() +
//			sys->getDerivedOrientation() * 
//			(_mEmitterScale * *mSpawnPositionList.begin());
//	}
//	else
//	{
//		particle->position = getDerivedPosition() + _mEmitterScale * *mSpawnPositionList.begin();
//	}
//			
//	mSpawnPositionList.pop_front();
//	particle->originalPosition = particle->position;
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_preProcessParticles(ParticleTechnique* technique, float timeElapsed)
//{
//	if (mAllVerticesProcessed)
//	{
//		return;
//	}
//
//	// Generate the next few spawn points if not all vertices are processed.
//	for (unsigned short i = 0; i < mIterations; ++i)
//	{
//		_generatePoints();
//		if (mAllVerticesProcessed)
//		{
//			return;
//		}
//	}
//
//	// Calculate the emitters position
//	getDerivedPosition();
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_setDefaults(void)
//{
//	// Set the default values except the name of the mesh, which may only be changed by the 
//	// setMeshName() function
//	mSpawnPositionList.clear();
//	mPositionElement = 0;
//	mVertexData = 0;
//	mVertexBuffer = 0;
//	mMesh = 0;
//	mSubMesh = 0;
//	mMaxVertexCount = 0;
//	mVertexCount = 0;
//	mMeshProcessed = false;
//	mAllVerticesProcessed = false;
//	mSubMeshNumber = 0;
//
//	if (!mBuffer.isNull())
//	{
//		if (mBuffer->isLocked())
//		{
//			mBuffer->unlock();
//		}
//		mBuffer.setNull();
//	}
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_loadMesh (void)
//{
//	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(mMeshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//	mMesh = mesh.getPointer();
//	mMeshProcessed = false;
//			
//	if (mMesh->getNumSubMeshes() > 0)
//	{
//		mSubMesh = mMesh->getSubMesh(0);
//	}
//	else
//	{
//		mSubMesh = 0;
//	}
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_generatePoints (void)
//{
//	if (mAllVerticesProcessed)
//	{
//		return;
//	}
//
//	if (!mMesh && mMeshName != StringUtil::BLANK)
//	{
//		_loadMesh();
//	}
//
//	// At least process the vertices of the mesh itself and then all its submeshes
//	if (!mMeshProcessed)
//	{
//		_generatePointsFromMesh();
//	}
//	else
//	{
//		if (mSubMesh && !mSubMesh->useSharedVertices)
//		{
//			_generatePointsFromSubMesh();
//		}
//	}
//
//	if (mVertexCount > 0 && mVertexCount >= mMaxVertexCount)
//	{
//		// The vertices of 1 mesh/subMesh are processed. Determine whether more submeshes need to
//		// be processed.
//		mBuffer->unlock();
//		mBuffer.setNull();
//		mVertexCount = 0;
//		mMaxVertexCount = 0;
//		mVertexData = 0;
//		mVertexBuffer = 0;
//		mSubMeshNumber++;
//		if (mSubMeshNumber >= mMesh->getNumSubMeshes())
//		{
//			mAllVerticesProcessed = true;
//		}
//		else
//		{
//			mSubMesh = mMesh->getSubMesh(mSubMeshNumber);
//		}
//	}
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_generatePointsFromMesh (void)
//{
//	if (mMaxVertexCount == 0 && mMesh)
//	{
//		mVertexData = mMesh->sharedVertexData;
//		if (!mVertexData)
//		{
//			mMeshProcessed = true;
//			return;
//		}
//		_fillVertexBuffer();
//	}
//
//	_generatePointsFromVertexBuffer();
//	if (mVertexCount >= mMaxVertexCount)
//	{
//		mMeshProcessed = true;
//	}
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_generatePointsFromSubMesh (void)
//{
//	if (mMaxVertexCount == 0 && mSubMesh)
//	{
//		mVertexData = mSubMesh->vertexData;
//		if (!mVertexData)
//		{
//			return;
//		}
//		_fillVertexBuffer();
//	}
//
//	_generatePointsFromVertexBuffer();
//}	
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_fillVertexBuffer(void)
//{
//	mVertexCount = 0;
//	mMaxVertexCount = mVertexData->vertexCount - mStep;
//	mPositionElement = mVertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
//	mBuffer = mVertexData->vertexBufferBinding->getBuffer(mPositionElement->getSource());
//	mVertexSize = mBuffer->getVertexSize();
//	mVertexBuffer = static_cast<unsigned char*>(mBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_generatePointsFromVertexBuffer(void)
//{
//	if (mMaxVertexCount > 1)
//	{
//		float* pReal;
//		mPositionElement->baseVertexPointerToElement(mVertexBuffer, &pReal);
//		Vec3 v1(pReal[0], pReal[1], pReal[2]);
//		mVertexBuffer += mStep * mVertexSize; // No validation; assume that it doesn't exceed.
//		mPositionElement->baseVertexPointerToElement(mVertexBuffer, &pReal);
//		Vec3 v2(pReal[0], pReal[1], pReal[2]);
//		_generatePoints (v1, v2);
//		mVertexCount += mStep;
//	}
//}
////-----------------------------------------------------------------------
//void Particle3DVertexEmitter::_generatePoints (const Vec3& startVector,
//	const Vec3& endVector,
//	float lengthIncrement)
//{
//	/*  Two possible ways of generating spawn points.
//		1. Generate (mSegments + 2) Vectors (including start and end vector), equally distributed.
//		2. Generate number of Vectors depending on the length between startVector and endVector. The
//			longer the length, the more vectors are generated.
//
//		The distribution of the spawn points in the list is as followed.
//		first iteration p1, 3 points:
//		- p1.3, p1.2, p1.1
//		second iteration, p2, 4 points:
//		- p2.4, p1.3, p2.3, p1.2, p2.2, p1.1, p2.1
//		second iteration, p3, 3 points:
//		- p3.3, p2.4, p3.2, p1.3, p3.1, p2.3, p1.2, p2.2, p1.1, p2.1
//	@remarks
//		Use objectspace for the vectors and only transform as soon as a particle is emitted.
//	*/
//	list<Vec3>::iterator iterator = mSpawnPositionList.end();
//	Vec3 start = startVector;
//	if (lengthIncrement > 0.0f)
//	{
//		// Determine number of dividers, based on the length increment
//		mSegments = (unsigned short)(((endVector - startVector).length()) / lengthIncrement - 1);
//	}
//    Vec3 increment = (endVector - startVector) / mSegments;
//		
//	for (unsigned short i = 0; i <= mSegments; i++)
//	{
//		mSpawnPositionList.insert (iterator, start);
//		start += increment;
//		iterator--;
//		if (iterator != mSpawnPositionList.begin())
//			iterator--;
//	}
//}
NS_CC_END