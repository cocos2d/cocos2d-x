//
//  Texture2DMutable.h
//   Ported to C++ by Dmitry Matyukhin
//
//  MutableTexture.m
//	Created by Lam Hoang Pham.
//  Improved by Manuel Martinez-Almeida.
//

#ifndef Texture2DMutable_cpp
#define Texture2DMutable_cpp

#include "cocos2d.h"

#define CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA 0

class Texture2DMutable : public cocos2d::Texture2D
{
#if CC_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA
    
    CC_PROPERTY_READONLY(void*, originalData_, OriginalTexData);
    
#endif
    
    CC_PROPERTY(void*, data_, TexData);
    
    
	unsigned int bytesPerPixel_;
	bool dirty_;
    
    cocos2d::Image *image_;
    
public:
    Texture2DMutable(void);
    ~Texture2DMutable(void);
    
    void restore();
    
	/** These functions are needed to create mutable textures */
	void releaseData(void *data);
	void* keepData(void *data, unsigned int length);
    
    bool initWithImageFile(const char *imageFile, cocos2d::Texture2D::PixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const cocos2d::Size& contentSize);
    
    bool initWithImageFile(const char *imageFilex);
    
	/** Intializes with a texture2d with data */
	bool initWithData(const void* data, cocos2d::Texture2D::PixelFormat pixelFormat, unsigned int pixelsWide, unsigned int pixelsHigh, const cocos2d::Size& contentSize);
    
    
    cocos2d::Color4B pixelAt(const cocos2d::Point& pt);
    
    ///
    //	@param pt is a point to get a pixel (0,0) is top-left to (width,height) bottom-right
    //	@param c is a Color4B which is a colour.
    //	@returns if a pixel was set
    //	Remember to call apply to actually update the texture canvas.
    ///
    bool setPixelAt(const cocos2d::Point& pt, cocos2d::Color4B c);
    
    ///
    //	Fill with specified colour
    ///
    void fill(cocos2d::Color4B c);
    
    ///
    //	@param textureToCopy is the texture image to copy over
    //	@param offset also offset's the texture image
    ///
    Texture2D* copyMutable(bool isMutable);
    
    Texture2DMutable* copy();
    
    void copy(Texture2DMutable* textureToCopy, const cocos2d::Point& offset);
    
    ///
    //	apply actually updates the texture with any new data we added.
    ///
    void apply();
    
    
    void *getData();

};

#endif // Texture2DMutable_cpp
