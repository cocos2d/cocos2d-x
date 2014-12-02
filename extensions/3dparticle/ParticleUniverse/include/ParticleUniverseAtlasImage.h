/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ATLAS_IMAGE_H__
#define __PU_ATLAS_IMAGE_H__

#include "ParticleUniversePrerequisites.h"
#include "OgreImage.h"

namespace ParticleUniverse
{
	/** The AtlasImage class offers the possibility to create one (atlas) image from other images.
	*/
	class _ParticleUniverseExport AtlasImage
	{
		public:
			AtlasImage(void);
			virtual ~AtlasImage(void);

			/** If true, the atlas image if recompiled after each change (i.e. an image is added).
			@remarks
				If false, compilation must be done manually (calling the _compile() function)
			*/
			const bool getAlwaysUpdate (void) const;

			/** See getAlwaysUpdate
			*/
			void setAlwaysUpdate (const bool alwaysUpdate);

			/** Add an Ogre Image to the atlas.
			@remarks
				All added images must have the same format. The AtlasImage tries to optimise its own image size.
			@par
				Internally, a copy is made from each added image. This means that the AtlasImage class isn´t responsible
				for destruction of the the added image pointer.
			*/
			bool addImage (const Ogre::Image* image);

			/** Get a pointer to the Ogre image of the atlas.
			*/
			const Ogre::Image* getImage (void) const;

			/** Construct the atlas image from all added images.
			@remarks
				This internal method is called as soon as an image is added to the atlas, so it can be updated.
			*/
			void _compile (void);

			/** Save the atlas image as a file. The filename must include the extention (png, jpg)
			*/
			void save (const String& filename);

		protected:
			typedef vector<Ogre::Image*> ImageList;
			ImageList mImageList;
			Ogre::Image* mAtlas;
			size_t mIndividualImageWidth;
			size_t mIndividualImageHeight;
			size_t mIndividualImageRowSpan;
			Ogre::PixelFormat mPixelFormat;
			bool mAlwaysUpdate;
	};

}
#endif
