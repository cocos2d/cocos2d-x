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

#include "ParticleUniverseAtlasImage.h"
#include "ParticleUniverseMath.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	AtlasImage::AtlasImage(void) :
		mAtlas(0),
		mIndividualImageWidth(0),
		mIndividualImageHeight(0),
		mIndividualImageRowSpan(0),
		mPixelFormat(Ogre::PF_UNKNOWN),
		mAlwaysUpdate(true)
	{
	}
	//-----------------------------------------------------------------------
	AtlasImage::~AtlasImage(void)
	{
		// Delete all images
		ImageList::iterator it;
		ImageList::iterator itEnd = mImageList.end();
		for (it = mImageList.begin(); it != itEnd; ++it)
		{
			PU_DELETE *it;
		}

		// Delete the atlas itself
		if (mAtlas)
		{
			PU_DELETE mAtlas;
		}
	}
	//-----------------------------------------------------------------------
	bool AtlasImage::addImage (const Ogre::Image* image)
	{
		if (!image)
			return false;

		if (mImageList.empty())
		{
			mIndividualImageWidth = image->getWidth();
			mIndividualImageHeight = image->getHeight();
			mIndividualImageRowSpan = image->getRowSpan();
			mPixelFormat = image->getFormat();
		}
		else
		{
			if (image->getWidth() != mIndividualImageWidth || image->getHeight() != mIndividualImageHeight)
			{
				// Image not added, because its size doesn't match
				return false;
			}
		}

		mImageList.push_back(PU_NEW Ogre::Image(*image));
		if (mAlwaysUpdate)
		{
			_compile();
		}

		return true;
	}
	//-----------------------------------------------------------------------
	const bool AtlasImage::getAlwaysUpdate (void) const
	{
		return mAlwaysUpdate;
	}
	//-----------------------------------------------------------------------
	void AtlasImage::setAlwaysUpdate (const bool alwaysUpdate)
	{
		mAlwaysUpdate = alwaysUpdate;
	}
	//-----------------------------------------------------------------------
	const Ogre::Image* AtlasImage::getImage (void) const
	{
		return mAtlas;
	}
	//-----------------------------------------------------------------------
	void AtlasImage::save (const String& filename)
	{
		if (mAtlas)
		{
			mAtlas->save(filename);
		}
	}
	//-----------------------------------------------------------------------
	void AtlasImage::_compile (void)
	{
		// 0. Reject if no images are added
		if (mImageList.empty())
			return;

		// 1. Destroy old atlas
		if (mAtlas)
		{
			PU_DELETE mAtlas;
		}

		// 2. Determine size of the atlas image and alloc memory - Is it possibe to create a square image?
		size_t imageColums = (size_t)(Math::Ceil(Math::Sqrt((Real)mImageList.size())));
		size_t imageRows = (size_t)(Math::Ceil((Real)(mImageList.size()) / (Real)imageColums));
		size_t width = imageColums * mIndividualImageWidth;
		size_t height = imageRows * mIndividualImageHeight;
		size_t pixelSize = Ogre::PixelUtil::getNumElemBytes(mPixelFormat);
		size_t bufferSize = width * height * pixelSize;
		uchar* data = OGRE_ALLOC_T(uchar, bufferSize, MEMCATEGORY_GENERAL);
		memset (data, 0, bufferSize);
		mAtlas = PU_NEW Ogre::Image();
		mAtlas->loadDynamicImage(data, width, height, 1, mPixelFormat, true); // Create atlas image, no mipmaps

		// 3. Add the buffers of all images to the atlas buffer
		ImageList::iterator it = mImageList.begin();
		Ogre::Image* image = *it;
		size_t imageColum = 0;
		size_t imageRow = 0;
		size_t pixelLine = 0;
		size_t atlasPointer = 0;
		for(imageRow = 0; imageRow < imageRows; ++imageRow)
		{
			atlasPointer = imageRow * mIndividualImageHeight * mAtlas->getRowSpan();
			for(imageColum = 0; imageColum < imageColums; ++imageColum)
			{
				atlasPointer = (imageRow * mIndividualImageHeight * mAtlas->getRowSpan()) + (imageColum * mIndividualImageRowSpan);
				for(pixelLine = 0; pixelLine < mIndividualImageHeight; ++pixelLine)
				{
					memcpy(data + atlasPointer, image->getData() + pixelLine * mIndividualImageRowSpan, mIndividualImageRowSpan);	
					atlasPointer += mAtlas->getRowSpan();
				}
				it++;
				if (it != mImageList.end())
				{
					image = *it;
				}
				else
				{
					return;
				}
			}
		}
	}

}
