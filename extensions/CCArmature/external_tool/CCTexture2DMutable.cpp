//
//  CCTexture2DMutable.cpp
//   Ported to C++ by Dmitry Matyukhin
//
//  CCMutableTexture.m
//	Created by Lam Hoang Pham.
//  Improved by Manuel Martinez-Almeida.
//


#include "CCTexture2DMutable.h"


using namespace cocos2d;

#if CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA
void* CCTexture2DMutable::getOriginalTexData() {
    return originalData_;
}
#endif

void* CCTexture2DMutable::getTexData() {
    return data_;
}

void CCTexture2DMutable::setTexData(void *var) {
    data_ = var;
}


void CCTexture2DMutable::releaseData(void* data)
{
	//Don't free the data
}

void* CCTexture2DMutable::keepData(void* data, unsigned int lenght)
{
	void *newData = malloc(lenght);
	memmove(newData, data, lenght);
	return newData;
}

bool CCTexture2DMutable::initWithImageFile(const char *imageFile, cocos2d::CCTexture2DPixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const cocos2d::CCSize& contentSize)
{
    image_ = new cocos2d::CCImage();
    image_->initWithImageFile(imageFile);
    
    
    return initWithData(image_->getData(), pixelFormat, pixelsWide, pixelsHigh, contentSize);
}

bool CCTexture2DMutable::initWithImageFile(const char *imageFile)
{
    image_ = new cocos2d::CCImage();
    image_->initWithImageFile(imageFile);
    
    bool                      hasAlpha = image_->hasAlpha();
    CCSize                    imageSize = CCSizeMake((float)(image_->getWidth()), (float)(image_->getHeight()));
    size_t                    bpp = image_->getBitsPerComponent();
    cocos2d::CCTexture2DPixelFormat pixelFormat;
    
    // compute pixel format
    if(hasAlpha)
    {
        pixelFormat = kCCTexture2DPixelFormat_Default;
    }
    else
    {
        if (bpp >= 8)
        {
            pixelFormat = kCCTexture2DPixelFormat_RGB888;
        }
        else
        {
            pixelFormat = kCCTexture2DPixelFormat_RGB565;
        }
        
    }
    
    return initWithData(image_->getData(), pixelFormat, imageSize.width, imageSize.height, imageSize);
}

bool CCTexture2DMutable::initWithData(const void* data, CCTexture2DPixelFormat pixelFormat, unsigned int width, unsigned int height, const CCSize& size)
{
	if(!CCTexture2D::initWithData(data, pixelFormat, width, height, size)) {
        return false;
    }
        
    switch (pixelFormat) {
        case kTexture2DPixelFormat_RGBA8888:	bytesPerPixel_ = 4; break;
        case kTexture2DPixelFormat_A8:			bytesPerPixel_ = 1; break;
        case kTexture2DPixelFormat_RGBA4444:
        case kTexture2DPixelFormat_RGB565:
        case kTexture2DPixelFormat_RGB5A1:
            bytesPerPixel_ = 2;
            break;
        default:break;
    }
    
    data_ = (void*) data;
    
#if CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA
    unsigned int max = width * height * bytesPerPixel_;
    originalData_ = malloc(max);
    memcpy(originalData_, data_, max);
#endif

    return true;
}

ccColor4B CCTexture2DMutable::pixelAt(const CCPoint& pt)
{
    
	ccColor4B c = {0, 0, 0, 0};
	if(!data_) return c;
	if(pt.x < 0 || pt.y < 0) return c;
	if(pt.x >= m_tContentSize.width || pt.y >= m_tContentSize.height) return c;
    
    //! modified, texture origin point is left top, cocos2d origin point is left bottom
    //! unsigned int x = pt.x, y = pt.y
	unsigned int x = pt.x, y = m_uPixelsHigh - 1 - pt.y;
    
	if(m_ePixelFormat == kTexture2DPixelFormat_RGBA8888){
		unsigned int *pixel = (unsigned int *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		c.r = *pixel & 0xff;
		c.g = (*pixel >> 8) & 0xff;
		c.b = (*pixel >> 16) & 0xff;
		c.a = (*pixel >> 24) & 0xff;
	} else if(m_ePixelFormat == kTexture2DPixelFormat_RGBA4444){
		GLushort *pixel = (GLushort *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		c.a = ((*pixel & 0xf) << 4) | (*pixel & 0xf);
		c.b = (((*pixel >> 4) & 0xf) << 4) | ((*pixel >> 4) & 0xf);
		c.g = (((*pixel >> 8) & 0xf) << 4) | ((*pixel >> 8) & 0xf);
		c.r = (((*pixel >> 12) & 0xf) << 4) | ((*pixel >> 12) & 0xf);
	} else if(m_ePixelFormat == kTexture2DPixelFormat_RGB5A1){
		GLushort *pixel = (GLushort *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		c.r = ((*pixel >> 11) & 0x1f)<<3;
		c.g = ((*pixel >> 6) & 0x1f)<<3;
		c.b = ((*pixel >> 1) & 0x1f)<<3;
		c.a = (*pixel & 0x1)*255;
	} else if(m_ePixelFormat == kTexture2DPixelFormat_RGB565){
		GLushort *pixel = (GLushort *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		c.b = (*pixel & 0x1f)<<3;
		c.g = ((*pixel >> 5) & 0x3f)<<2;
		c.r = ((*pixel >> 11) & 0x1f)<<3;
		c.a = 255;
	} else if(m_ePixelFormat == kTexture2DPixelFormat_A8){
		GLubyte *pixel = (GLubyte *)data_;
		c.a = pixel[(y * m_uPixelsWide) + x];
		// Default white
		c.r = 255;
		c.g = 255;
		c.b = 255;
	}
    
    //CCLog("color : %i, %i, %i, %i", c.r, c.g, c.b, c.a);
    
	return c;
}

bool CCTexture2DMutable::setPixelAt(const CCPoint& pt, ccColor4B c)
{
	if(!data_)return false;
	if(pt.x < 0 || pt.y < 0) return false;
	if(pt.x >= m_tContentSize.width || pt.y >= m_tContentSize.height) return false;
	unsigned int x = pt.x, y = pt.y;
    
	dirty_ = true;
    
	//	Shifted bit placement based on little-endian, let's make this more
	//	portable =/
    
	if(m_ePixelFormat == kTexture2DPixelFormat_RGBA8888){
		unsigned int *pixel = (unsigned int *)data_;
		pixel[(y * m_uPixelsWide) + x] = (c.a << 24) | (c.b << 16) | (c.g << 8) | c.r;
	} else if(m_ePixelFormat == kTexture2DPixelFormat_RGBA4444){
		GLushort *pixel = (GLushort *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		*pixel = ((c.r >> 4) << 12) | ((c.g >> 4) << 8) | ((c.b >> 4) << 4) | (c.a >> 4);
	} else if(m_ePixelFormat == kTexture2DPixelFormat_RGB5A1){
		GLushort *pixel = (GLushort *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		*pixel = ((c.r >> 3) << 11) | ((c.g >> 3) << 6) | ((c.b >> 3) << 1) | (c.a > 0);
	} else if(m_ePixelFormat == kTexture2DPixelFormat_RGB565){
		GLushort *pixel = (GLushort *)data_;
		pixel = pixel + (y * m_uPixelsWide) + x;
		*pixel = ((c.r >> 3) << 11) | ((c.g >> 2) << 5) | (c.b >> 3);
	} else if(m_ePixelFormat == kTexture2DPixelFormat_A8){
		GLubyte *pixel = (GLubyte *)data_;
		pixel[(y * m_uPixelsWide) + x] = c.a;
	} else {
		dirty_ = false;
		return false;
	}
	return true;
}

void CCTexture2DMutable::fill(ccColor4B p)
{
	for(int r = 0; r < m_tContentSize.height; ++r)
		for(int c = 0; c < m_tContentSize.width; ++c)
            this->setPixelAt(CCPointMake(c, r), p);
}

CCTexture2D* CCTexture2DMutable::copyMutable(bool isMutable )
{	
	CCTexture2D* co;
	if(isMutable)
	{
		int mem = m_uPixelsWide*m_uPixelsHigh*bytesPerPixel_;
		void *newData = malloc(mem);
		memcpy(newData, data_, mem);
        co = new CCTexture2DMutable();
        if (!co->initWithData(newData, m_ePixelFormat, m_uPixelsWide, m_uPixelsHigh, m_tContentSize)) {
            delete co;
            co = NULL;
        }
	}else {
        
        co = new CCTexture2D();
        if (!co->initWithData(data_, m_ePixelFormat, m_uPixelsWide, m_uPixelsHigh, m_tContentSize)) {
            delete co;
            co = NULL;
        }
    }
        
    return co;
}

CCTexture2DMutable* CCTexture2DMutable::copy()
{
	return (CCTexture2DMutable*)this->copyMutable( true );
}

void CCTexture2DMutable::copy(CCTexture2DMutable* textureToCopy, const CCPoint& offset)
{
	for(int r = 0; r < m_tContentSize.height;++r){
		for(int c = 0; c < m_tContentSize.width; ++c){
            setPixelAt(CCPointMake(c + offset.x, r + offset.y), textureToCopy->pixelAt(CCPointMake(c, r)));
		}
	}
}

void CCTexture2DMutable::restore()
{
#if CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA
	memcpy(data_, originalData_, bytesPerPixel_*m_uPixelsWide*m_uPixelsHigh);
	this->apply();
#else
	//You should set CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA 1 in CCTexture2DMutable.h
    CCAssert(false, "Exception:  CCMutableTexture.restore was disabled by the user.");
#endif
}

void CCTexture2DMutable::apply()
{
	if(!data_) return;
    
	glBindTexture(GL_TEXTURE_2D, m_uName);
    
	switch(m_ePixelFormat)
	{
		case kTexture2DPixelFormat_RGBA8888:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_uPixelsWide, m_uPixelsHigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);
			break;
		case kTexture2DPixelFormat_RGBA4444:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_uPixelsWide, m_uPixelsHigh, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data_);
			break;
		case kTexture2DPixelFormat_RGB5A1:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_uPixelsWide, m_uPixelsHigh, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data_);
			break;
		case kTexture2DPixelFormat_RGB565:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_uPixelsWide, m_uPixelsHigh, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data_);
			break;
		case kTexture2DPixelFormat_A8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_uPixelsWide, m_uPixelsHigh, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data_);
			break;
		default:
            CCAssert(false, "NSInternalInconsistencyException");

	}
	glBindTexture(GL_TEXTURE_2D, 0);
	dirty_ = false;
}

void *CCTexture2DMutable::getData()
{
    return data_;
}

CCTexture2DMutable::CCTexture2DMutable(void)
{
    image_ = NULL;
}

CCTexture2DMutable::~CCTexture2DMutable(void)
{
	CCLOGINFO("cocos2d: deallocing %p", this);
    
	if (image_)
	{
		CC_SAFE_DELETE(image_);
	}
	else
	{
		free(data_);
	}
    
#if CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA
	free(originalData_);
#endif

}

