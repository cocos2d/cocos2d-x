/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_FORCE_FIELD_H__
#define __PU_FORCE_FIELD_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseNoise.h"
#include "OgreWorkQueue.h"

namespace ParticleUniverse
{
	/** Pure virtual ForceFieldCalculationFactory
	*/
	class _ParticleUniverseExport ForceFieldCalculationFactory : public FactoryAlloc
	{
		public:
			// Const
			static const Vector3 DEFAULT_WORLDSIZE;

			ForceFieldCalculationFactory(void) : 
				mOctaves(2),
				mFrequency(1.0f),
				mAmplitude(1.0f),
				mPersistence(1.0f),
				mMappedPosition(Vector3::ZERO),
				mMapScale(Vector3::ZERO),
				mWorldSize(DEFAULT_WORLDSIZE)
			{
			};
			virtual ~ForceFieldCalculationFactory(void){};

			/** Generates the force field
			@remarks
				This function takes several arguments. 
				- forceFieldSize defines the internal dimensions of the force field. 
				- octaves, frequency, amplitude and persistence define the noise that is being generated.
				- worldSize defines the dimensions in the real world (scene).
			*/
			virtual void generate(unsigned int forceFieldSize, 
				ushort octaves, 
				double frequency, 
				double amplitude, 
				double persistence, 
				const Vector3& worldSize) = 0;

			/** Determine force, based on the position of a particle.
			#remarks
				The position is the position of a particle. The argument 'delta' defines the radius around the position that contributes to the 
				calculation of the force.
			*/
			virtual void determineForce(const Vector3& position, Vector3& force, Real delta) = 0;

			/** Default Getters/Setters
			*/
			virtual ushort getOctaves(void) const;
			virtual void setOctaves(ushort octaves);
			virtual double getFrequency(void) const;
			virtual void setFrequency(double frequency);
			virtual double getAmplitude(void) const;
			virtual void setAmplitude(double amplitude);
			virtual double getPersistence(void) const;
			virtual void setPersistence(double persistence);
			virtual unsigned int getForceFieldSize(void) const;
			virtual void setForceFieldSize(unsigned int forceFieldSize);
			virtual Vector3 getWorldSize(void) const;
			virtual void setWorldSize(const Vector3& worldSize);

		protected:
			Noise3D mNoise3D;
			ushort mOctaves;
			double mFrequency;
			double mAmplitude;
			double mPersistence;
			Vector3 mMapScale;
			Vector3 mWorldSize;
			Vector3 mMappedPosition;
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** Factory class to calculate forces in realtime
	*/
	class _ParticleUniverseExport RealTimeForceFieldCalculationFactory : public ForceFieldCalculationFactory
	{
		public:
			RealTimeForceFieldCalculationFactory(void) : ForceFieldCalculationFactory() {};
			virtual ~RealTimeForceFieldCalculationFactory(void){};

			/** Override from ForceFieldCalculationFactory
			*/
			virtual void generate(unsigned int forceFieldSize, 
				ushort octaves, 
				double frequency, 
				double amplitude, 
				double persistence, 
				const Vector3& worldSize);

			/** Override from ForceFieldCalculationFactory
			*/
			virtual void determineForce(const Vector3& position, Vector3& force, Real delta);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** Factory class to calculate forces based on a precalculated force field
	*/
	class _ParticleUniverseExport MatrixForceFieldCalculationFactory : 
		public ForceFieldCalculationFactory, 
		public Ogre::WorkQueue::RequestHandler, 
		public Ogre::WorkQueue::ResponseHandler
	{
		public:
			static const uint16 WORKQUEUE_GENERATE_REQUEST;
			struct MatrixPosition
			{
				Real x;
				Real y;
				Real z;
			};

			MatrixForceFieldCalculationFactory(void);
			virtual ~MatrixForceFieldCalculationFactory(void);

			/** Override from ForceFieldCalculationFactory
			*/
			virtual void generate(unsigned int forceFieldSize, 
				ushort octaves, 
				double frequency, 
				double amplitude, 
				double persistence, 
				const Vector3& worldSize);

			/** Delete the internally build matrix
			*/
			void deleteMatrix(void);

			/** Override from ForceFieldCalculationFactory
			*/
			virtual void determineForce(const Vector3& position, Vector3& force, Real delta);

			/** WorkQueue::RequestHandler override
			*/
			bool canHandleRequest(const Ogre::WorkQueue::Request* req, const Ogre::WorkQueue* srcQ);

			/** WorkQueue::RequestHandler override
			*/
			Ogre::WorkQueue::Response* handleRequest(const Ogre::WorkQueue::Request* req, const Ogre::WorkQueue* srcQ);

			/** WorkQueue::ResponseHandler override
			*/
			bool canHandleResponse(const Ogre::WorkQueue::Response* res, const Ogre::WorkQueue* srcQ);

			/** WorkQueue::ResponseHandler override
			*/
			void handleResponse(const Ogre::WorkQueue::Response* res, const Ogre::WorkQueue* srcQ);

			/** Get/Set Forcefield size.
			@remarks
				These get/set functions override default ones.
			*/
			virtual unsigned int getForceFieldSize(void) const;
			virtual void setForceFieldSize(unsigned int forceFieldSize);

		protected:
			MatrixPosition*** mMatrixPositions;
			unsigned int mForceFieldSize;
			unsigned int mX;
			unsigned int mY;
			unsigned int mZ;
			uint16 mWorkQueueChannel;
			bool mInitialising;

			// Request / response structures
			struct MatrixRequest
			{
				unsigned int forceFieldSize;
				ushort octaves;
				double frequency;
				double amplitude;
				double persistence;
				Vector3 worldSize;
				MatrixForceFieldCalculationFactory* src;
				_ParticleUniverseExport friend std::ostream& operator<<(std::ostream& o, const MatrixRequest& r)
					{return o;}
				MatrixRequest(MatrixForceFieldCalculationFactory* f): src(f) {};
			};
			
			struct MatrixResponse
			{
				_ParticleUniverseExport friend std::ostream& operator<<(std::ostream& o, const MatrixResponse& r)
					{return o;}		
			};
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	/** Force Field Affector Class:
		This class defines a force field to affect the particle direction. The force field is based on 3D noise. The force can be calculated in
		realtime or based on a precreated 3D force field matrix, which essentially involves one lookup. To speed things up, the 3d matrix can be
		precreated in a separate thread (optionally).
	*/
	class _ParticleUniverseExport ForceField
	{
		public:
			enum ForceFieldType
			{
				FF_REALTIME_CALC,
				FF_MATRIX_CALC
			};

			ForceField(void);
			~ForceField(void);

			/** Initialises a ForceField */
			virtual void initialise(ForceFieldType type,
				const Vector3& position,
				unsigned int forceFieldSize, 
				ushort octaves, 
				double frequency, 
				double amplitude, 
				double persistence, 
				const Vector3& worldSize);

			/** Initialises a ForceField */
			virtual void initialise(ForceFieldType type,
				unsigned int forceFieldSize, 
				ushort octaves, 
				double frequency, 
				double amplitude, 
				double persistence, 
				const Vector3& worldSize);

			/** Get/Set the base position of the force field */
			const Vector3& getForceFieldPositionBase(void) const;
			void setForceFieldPositionBase(const Vector3& position);

			/** Calculate the force, based on a certain position */
			void determineForce(const Vector3& position, Vector3& force, Real delta);

			/** Getters/Setters
			*/
			virtual ushort getOctaves(void) const;
			virtual void setOctaves(ushort octaves);
			virtual double getFrequency(void) const;
			virtual void setFrequency(double frequency);
			virtual double getAmplitude(void) const;
			virtual void setAmplitude(double amplitude);
			virtual double getPersistence(void) const;
			virtual void setPersistence(double persistence);
			virtual unsigned int getForceFieldSize(void) const;
			virtual void setForceFieldSize(unsigned int forceFieldSize);
			virtual Vector3 getWorldSize(void) const;
			virtual void setWorldSize(const Vector3& worldSize);
			
			/** Get/Set the Forcefield type
			*/
			const ForceFieldType getForceFieldType(void) const;
			void setForceFieldType(const ForceFieldType forceFieldType);

		protected:
			ushort mOctaves;
			double mFrequency;
			double mAmplitude;
			double mPersistence;
			Vector3 mWorldSize;
			unsigned int mForceFieldSize;
			ForceFieldCalculationFactory* mForceFieldCalculationFactory; // Internal factory that creates a certain force field type
			Vector3 mForceFieldPositionBase; // Position of the force field
			ForceFieldType mForceFieldType;

			/** Get/Set/Create ForceFieldCalculationFactory */
			ForceFieldCalculationFactory* getForceFieldCalculationFactory() const;
			void setForceFieldCalculationFactory(ForceFieldCalculationFactory* forceFieldCalculationFactory);
			ForceFieldCalculationFactory* createForceFieldCalculationFactory(ForceFieldType type);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
}
#endif
