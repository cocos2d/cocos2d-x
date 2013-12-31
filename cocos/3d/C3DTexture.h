#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "EnumDef_GL.h"
#include "cocos2d.h"

namespace cocos2d
{
class Texture2D;
class Image;

/**
* Represents a texture.
It wraps the cocos2d::ccTexture
*/
class C3DTexture : public cocos2d::CCObject
{
	friend class C3DSampler;

public:

	/**
	* Defines the set of supported texture formats.
	*/
	enum Format
	{
		RGB     = GL_RGB,
		RGBA    = GL_RGBA,
		ALPHA   = GL_ALPHA,
		DEPTH   = GL_DEPTH_COMPONENT,
#ifdef USE_PVRTC
		COMPRESSED_RGB_PVRTC_4BPP = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,
		COMPRESSED_RGBA_PVRTC_4BPP = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,
		COMPRESSED_RGB_PVRTC_2BPP = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,
		COMPRESSED_RGBA_PVRTC_2BPP = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
#endif
	};

	/**
	* Creates a texture from the given image resource.
	*
	* @param path The image resource path.
	* @param generateMipmaps true to auto-generate a full mipmap chain, false otherwise.
	*
	* @return The new texture, or nullptr if the texture could not be loaded/created.
	*/
	static C3DTexture* create(const char* path, bool generateMipmaps = false);
	static C3DTexture* create(int width, int height, Format fmt, bool generateMipmaps = false);
	static C3DTexture* create(int width, int height, Format fmt, const void* data, ssize_t dataLen, bool generateMipmaps = false);

	/**
	* Returns the texture width.
	*/
	unsigned int getWidth() const;

	/**
	* Returns the texture height.
	*/
	unsigned int getHeight() const;

	/**
	* Sets the wrap mode for this texture.
	*
	* @param wrapS Horizontal wrapping mode for the texture.
	* @param wrapT Vertical wrapping mode for the texture.
	*/
	void setWrapMode(Texture_Wrap wrapS, Texture_Wrap wrapT);

	/**
	* Sets the minification and magnification filter modes for this texture.
	*
	* @param minificationFilter New texture minification filter.
	* @param magnificationFilter New texture magnification filter.
	*/
	void setFilterMode(Texture_Filter minificationFilter, Texture_Filter magnificationFilter);

	/**
	* Generates a full mipmap chain for this texture if it isn't already mipmapped.
	*/
	void generateMipmaps();

	/**
	* Determines if this texture currently contains a full mipmap chain.
	*
	* @return True if this texture is currently mipmapped, false otherwise.
	*/
	bool isMipmapped() const;

	/**
	* Returns the texture handle.
	*
	* @return The texture handle.
	*/
	GLuint getHandle() const;

	/**
	* get texture path
	*/
	const char* getPath() const { return _path.c_str(); };

private:

	/**
	* Constructor.
	*/
	C3DTexture();

	/**
	* Copy constructor.
	*/
	C3DTexture(const C3DTexture& copy);

	/**
	* Destructor.
	*/
	virtual ~C3DTexture();

#ifdef USE_PVRTC
	static C3DTexture* createCompressedPVRTC(const char* path);
#endif

	//properties
	std::string _path;
	GLuint _handle;
	unsigned int _width;
	unsigned int _height;
	bool _mipmapped;

	cocos2d::CCTexture2D * _texture;
};
}

#endif
