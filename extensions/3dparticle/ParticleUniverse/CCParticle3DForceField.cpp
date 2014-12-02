/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCParticle3DForceField.h"

NS_CC_BEGIN

const Vec3 ForceFieldCalculationFactory::DEFAULT_WORLDSIZE = Vec3(500.0f, 500.0f, 500.0f);

//-----------------------------------------------------------------------
unsigned short ForceFieldCalculationFactory::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void ForceFieldCalculationFactory::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
double ForceFieldCalculationFactory::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void ForceFieldCalculationFactory::setFrequency(double frequency)
{
    _frequency = frequency;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
double ForceFieldCalculationFactory::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void ForceFieldCalculationFactory::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
double ForceFieldCalculationFactory::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void ForceFieldCalculationFactory::setPersistence(double persistence)
{
    _persistence = persistence;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
unsigned int ForceFieldCalculationFactory::getForceFieldSize(void) const
{
    return 1; // Return default cubic size
}
//-----------------------------------------------------------------------
void ForceFieldCalculationFactory::setForceFieldSize(unsigned int forceFieldSize)
{
    // The forcefield cannot be zero
    if (forceFieldSize == 0)
        return;

    generate(forceFieldSize, _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
Vec3 ForceFieldCalculationFactory::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void ForceFieldCalculationFactory::setWorldSize(const Vec3& worldSize)
{
    // The worldsize cannot be zero
    if (worldSize == Vec3::ZERO)
        return;

    _worldSize = worldSize;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void RealTimeForceFieldCalculationFactory::generate(unsigned int forceFieldSize, 
                                                    unsigned short octaves, 
                                                    double frequency, 
                                                    double amplitude, 
                                                    double persistence, 
                                                    const Vec3& worldSize)
{
    _octaves = octaves;
    _frequency = frequency;
    _amplitude = amplitude;
    _persistence = persistence;
    _worldSize = worldSize;
    _noise3D.initialise(octaves, frequency, amplitude, persistence);

    if (worldSize != Vec3::ZERO)
    {
        _mapScale.x = 1.0f / worldSize.x; // Remark: forceFieldSize is not used, because it is a unit cube
        _mapScale.y = 1.0f / worldSize.y;
        _mapScale.z = 1.0f / worldSize.z;
    }
}
//-----------------------------------------------------------------------
void RealTimeForceFieldCalculationFactory::determineForce(const Vec3& position, Vec3& force, float delta)
{
    _mappedPosition.x = _mapScale.x * position.x;
    _mappedPosition.y = _mapScale.y * position.y;
    _mappedPosition.z = _mapScale.z * position.z;

    if (_mappedPosition.x < 0.0f || _mappedPosition.x > 1.0f ||
        _mappedPosition.y < 0.0f || _mappedPosition.y > 1.0f ||
        _mappedPosition.z < 0.0f || _mappedPosition.z > 1.0f)
    {
        // Position is outside the forcefield (outside the unit cube)
        return;
    }

    force.x = (float)(_noise3D.noise(_mappedPosition.x + delta, _mappedPosition.y, _mappedPosition.z) - 
        _noise3D.noise(_mappedPosition.x - delta, _mappedPosition.y, _mappedPosition.z));
    force.y = (float)(_noise3D.noise(_mappedPosition.x, _mappedPosition.y + delta, _mappedPosition.z) - 
        _noise3D.noise(_mappedPosition.x, _mappedPosition.y - delta, _mappedPosition.z));
    force.z = (float)(_noise3D.noise(_mappedPosition.x, _mappedPosition.y, _mappedPosition.z + delta) - 
        _noise3D.noise(_mappedPosition.x, _mappedPosition.y, _mappedPosition.z - delta));
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//const uint16 MatrixForceFieldCalculationFactory::WORKQUEUE_GENERATE_REQUEST = 1;
////-----------------------------------------------------------------------
//MatrixForceFieldCalculationFactory::MatrixForceFieldCalculationFactory(void) : 
//	ForceFieldCalculationFactory(),
//	mMatrixPositions(0),
//	mForceFieldSize(0),
//	mX(0),
//	mY(0),
//	mZ(0),
//	mInitialising(false)
//{
//	Ogre::WorkQueue* wq = Ogre::Root::getSingleton().getWorkQueue();
//	mWorkQueueChannel = wq->getChannel("ParticleUniverse/MatrixForceFieldCalculationFactory");
//	wq->addRequestHandler(mWorkQueueChannel, this);
//	wq->addResponseHandler(mWorkQueueChannel, this);
//}
////-----------------------------------------------------------------------
//MatrixForceFieldCalculationFactory::~MatrixForceFieldCalculationFactory(void)
//{
//	Ogre::WorkQueue* wq = Ogre::Root::getSingleton().getWorkQueue();
//	wq->removeRequestHandler(mWorkQueueChannel, this);
//	wq->removeResponseHandler(mWorkQueueChannel, this);
//	deleteMatrix();
//}
////-----------------------------------------------------------------------
//void MatrixForceFieldCalculationFactory::generate(unsigned int forceFieldSize, 
//												  unsigned short octaves, 
//												  double frequency, 
//												  double amplitude, 
//												  double persistence, 
//												  const Vec3& worldSize)
//{
//	// Push request to the workerqueue
//	MatrixRequest req(this);
//	req.forceFieldSize = forceFieldSize;
//	req.octaves = octaves;
//	req.frequency = frequency;
//	req.amplitude = amplitude;
//	req.persistence = persistence;
//	req.worldSize = worldSize;
//	mInitialising = true;
//	Ogre::Root::getSingleton().getWorkQueue()->addRequest(mWorkQueueChannel, WORKQUEUE_GENERATE_REQUEST, Any(req), 0, false);
//}
////-----------------------------------------------------------------------
//void MatrixForceFieldCalculationFactory::deleteMatrix(void)
//{
//	if (!mMatrixPositions)
//		return;
//
//	for(unsigned int i = 0; i < mForceFieldSize; ++i)
//	{
//		for(unsigned int j = 0; j < mForceFieldSize; ++j)
//		{
//			delete [] mMatrixPositions[i][j];
//		}
//		delete [] mMatrixPositions[i];
//	}
//	delete [] mMatrixPositions;
//	mMatrixPositions = 0;
//}
////-----------------------------------------------------------------------
//void MatrixForceFieldCalculationFactory::determineForce(const Vec3& position, Vec3& force, float delta)
//{
//	if (mInitialising)
//	{
//		return;
//	}
//
//	// Ignore delta, because it is not needed to search into the matrix
//	mX = (unsigned int)(mMapScale.x * position.x);
//	mY = (unsigned int)(mMapScale.y * position.y);
//	mZ = (unsigned int)(mMapScale.z * position.z);
//	if (mX >= mForceFieldSize || mY >= mForceFieldSize || mZ >= mForceFieldSize)
//	{
//		// Position is outside the forcefield
//		return;
//	}
//
//	force.x = mMatrixPositions[mX][mY][mZ].x;
//	force.y = mMatrixPositions[mX][mY][mZ].y;
//	force.z = mMatrixPositions[mX][mY][mZ].z;
//}
////---------------------------------------------------------------------
//bool MatrixForceFieldCalculationFactory::canHandleRequest(const Ogre::WorkQueue::Request* req, const Ogre::WorkQueue* srcQ)
//{
//	MatrixRequest preq = any_cast<MatrixRequest>(req->getData());
//	if (preq.src != this)
//		return false;
//	else
//		return RequestHandler::canHandleRequest(req, srcQ);
//}
////---------------------------------------------------------------------
//bool MatrixForceFieldCalculationFactory::canHandleResponse(const Ogre::WorkQueue::Response* res, const Ogre::WorkQueue* srcQ)
//{
//	MatrixRequest preq = any_cast<MatrixRequest>(res->getRequest()->getData());
//	if (preq.src != this)
//		return false;
//	else
//		return true;
//}
////---------------------------------------------------------------------
//Ogre::WorkQueue::Response* MatrixForceFieldCalculationFactory::handleRequest(const Ogre::WorkQueue::Request* req, const Ogre::WorkQueue* srcQ)
//{
//	MatrixRequest preq = any_cast<MatrixRequest>(req->getData());
//	if (preq.src != this)
//		return 0;
//
//	// Setup the 3D matrix with precalculated force field vectors
//	mNoise3D.initialise(preq.octaves, preq.frequency, preq.amplitude, preq.persistence);
//	mMapScale.x = preq.forceFieldSize / preq.worldSize.x;
//	mMapScale.y = preq.forceFieldSize / preq.worldSize.y;
//	mMapScale.z = preq.forceFieldSize / preq.worldSize.z;
//
//	deleteMatrix();
//	mForceFieldSize = preq.forceFieldSize;
//	mMatrixPositions = new MatrixPosition**[mForceFieldSize];
//	for(unsigned int i = 0; i < mForceFieldSize; ++i)
//	{
//		mMatrixPositions[i] = new MatrixPosition*[mForceFieldSize];
//		for(unsigned int j = 0; j < mForceFieldSize; ++j)
//		{
//			mMatrixPositions[i][j] = new MatrixPosition[mForceFieldSize];
//		}
//	}
//
//	// Fill the matrix
//	mForceFieldSize = mForceFieldSize == 0 ? 1 : mForceFieldSize; // The forcefield may not be 0
//	float delta = 1.0f / mForceFieldSize;
//	for(unsigned int i = 0; i < mForceFieldSize; ++i)
//	{
//		for(unsigned int j = 0; j < mForceFieldSize; ++j)
//		{
//			for(unsigned int k = 0; k < mForceFieldSize; ++k)
//			{
//				mMatrixPositions[i][j][k].x = (float)(mNoise3D.noise(i * delta + delta, j * delta, k * delta) - 
//					mNoise3D.noise(i * delta - delta, j * delta, k * delta));
//				mMatrixPositions[i][j][k].y = (float)(mNoise3D.noise(i * delta, j * delta + delta, k * delta) - 
//					mNoise3D.noise(i * delta, j * delta - delta, k * delta));
//				mMatrixPositions[i][j][k].z = (float)(mNoise3D.noise(i * delta, j * delta, k * delta + delta) - 
//					mNoise3D.noise(i * delta, j * delta, k * delta - delta));
//			}
//		}
//	}
//
//	MatrixResponse res;
//	Ogre::WorkQueue::Response* response = PU_NEW Ogre::WorkQueue::Response(req, true, Any(res));
//	return response;
//}
////---------------------------------------------------------------------
//void MatrixForceFieldCalculationFactory::handleResponse(const Ogre::WorkQueue::Response* res, const Ogre::WorkQueue* srcQ)
//{
//	// Response itself is not used
//	mInitialising = false;
//}
////-----------------------------------------------------------------------
//unsigned int MatrixForceFieldCalculationFactory::getForceFieldSize(void) const
//{
//	return mForceFieldSize;
//}
////-----------------------------------------------------------------------
//void MatrixForceFieldCalculationFactory::setForceFieldSize(unsigned int forceFieldSize)
//{
//	mForceFieldSize = forceFieldSize;
//	generate(mForceFieldSize, mOctaves, mFrequency, mAmplitude, mPersistence, mWorldSize);
//}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
ForceField::ForceField(void) :
    _forceFieldCalculationFactory(0),
    _forceFieldPositionBase(Vec3::ZERO),
    _forceFieldType(FF_REALTIME_CALC),
    _octaves(2),
    _frequency(1.0f),
    _amplitude(1.0f),
    _persistence(1.0f),
    _forceFieldSize(64),
    _worldSize(ForceFieldCalculationFactory::DEFAULT_WORLDSIZE)
{
}
//-----------------------------------------------------------------------
ForceField::~ForceField(void)
{
    if (_forceFieldCalculationFactory)
    {
        delete _forceFieldCalculationFactory;
    }
}
//-----------------------------------------------------------------------
void ForceField::initialise(ForceFieldType type,
                            const Vec3& position,
                            unsigned int forceFieldSize, 
                            unsigned short octaves, 
                            double frequency, 
                            double amplitude, 
                            double persistence, 
                            const Vec3& worldSize)

{
    // Initialise first
    initialise(type, forceFieldSize, octaves, frequency, amplitude, persistence, worldSize);

    // Store the base and max position of the forcefield.
    _forceFieldPositionBase = position;
    _forceFieldPositionBase.x -= 0.5f * worldSize.x;
    _forceFieldPositionBase.y -= 0.5f * worldSize.y;
    _forceFieldPositionBase.z -= 0.5f * worldSize.z;
}
//-----------------------------------------------------------------------
void ForceField::initialise(ForceFieldType type,
                            unsigned int forceFieldSize, 
                            unsigned short octaves, 
                            double frequency, 
                            double amplitude, 
                            double persistence, 
                            const Vec3& worldSize)
{
    // Create a factory
    _forceFieldCalculationFactory = createForceFieldCalculationFactory(type);

    // Create all necessary data for the force field
    _forceFieldCalculationFactory->generate(forceFieldSize, octaves, frequency, amplitude, persistence, worldSize);
}
//-----------------------------------------------------------------------
const Vec3& ForceField::getForceFieldPositionBase(void) const
{
    return _forceFieldPositionBase;
}
//-----------------------------------------------------------------------
void ForceField::setForceFieldPositionBase(const Vec3& position)
{
    _forceFieldPositionBase = position;
}
//-----------------------------------------------------------------------
void ForceField::determineForce(const Vec3& position, Vec3& force, float delta)
{
    force.x = 0.0f;
    force.y = 0.0f;
    force.z = 0.0f;

    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->determineForce(position - _forceFieldPositionBase, force, delta);
    }
}
//-----------------------------------------------------------------------
ForceFieldCalculationFactory* ForceField::getForceFieldCalculationFactory() const
{
    return _forceFieldCalculationFactory;
}
//-----------------------------------------------------------------------
void ForceField::setForceFieldCalculationFactory(ForceFieldCalculationFactory* forceFieldCalculationFactory)
{
    if (_forceFieldCalculationFactory)
    {
        delete _forceFieldCalculationFactory;
    }
    _forceFieldCalculationFactory = forceFieldCalculationFactory;
}
//-----------------------------------------------------------------------
ForceFieldCalculationFactory* ForceField::createForceFieldCalculationFactory(ForceFieldType type)
{
    _forceFieldType = type;
    if (type == FF_MATRIX_CALC)
    {
        // Use precreated matrix
        //setForceFieldCalculationFactory(new MatrixForceFieldCalculationFactory());
        return getForceFieldCalculationFactory();
    }
    else
    {
        // Use realtime calculation
        setForceFieldCalculationFactory(new RealTimeForceFieldCalculationFactory());
        return getForceFieldCalculationFactory();
    }
}
//-----------------------------------------------------------------------
const ForceField::ForceFieldType ForceField::getForceFieldType(void) const
{
    return _forceFieldType;
}
//-----------------------------------------------------------------------
void ForceField::setForceFieldType(const ForceField::ForceFieldType forceFieldType)
{
    _forceFieldType = forceFieldType;
    if (_forceFieldCalculationFactory)
    {
        initialise(_forceFieldType, _forceFieldSize, _octaves, _frequency, _amplitude, _persistence, _worldSize);
    }
}
//-----------------------------------------------------------------------
unsigned short ForceField::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void ForceField::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setOctaves(octaves);
    }
}
//-----------------------------------------------------------------------
double ForceField::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void ForceField::setFrequency(double frequency)
{
    _frequency = frequency;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setFrequency(frequency);
    }
}
//-----------------------------------------------------------------------
double ForceField::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void ForceField::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setAmplitude(amplitude);
    }
}
//-----------------------------------------------------------------------
double ForceField::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void ForceField::setPersistence(double persistence)
{
    _persistence = persistence;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setPersistence(persistence);
    }
}
//-----------------------------------------------------------------------
unsigned int ForceField::getForceFieldSize(void) const
{
    return _forceFieldSize;
}
//-----------------------------------------------------------------------
void ForceField::setForceFieldSize(unsigned int forceFieldSize)
{
    _forceFieldSize = forceFieldSize;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setForceFieldSize(forceFieldSize);
    }
}
//-----------------------------------------------------------------------
Vec3 ForceField::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void ForceField::setWorldSize(const Vec3& worldSize)
{
    _worldSize = worldSize;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setWorldSize(worldSize);
    }
}

NS_CC_END
