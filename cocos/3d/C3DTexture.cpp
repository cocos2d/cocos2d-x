#include "Base.h"
#include "C3DTexture.h"
#include "Stream.h"
#include "cocos2d.h"
#include "CCTexture2D.h"
#include "CCTextureCache.h"
#include "ccUtils.h"

using namespace std;
using namespace cocos2d;

namespace cocos2d
{
static std::vector<C3DTexture*> __textureCache;

C3DTexture::C3DTexture() : _handle(0), _mipmapped(false), _width(0), _height(0), /*_cached(false), */_texture(nullptr)
{
}

C3DTexture::C3DTexture(const C3DTexture& copy)
{
}

C3DTexture::~C3DTexture()
{
	std::vector<C3DTexture*>::iterator itr = std::find(__textureCache.begin(), __textureCache.end(), this);
	if (itr != __textureCache.end())
	{
		__textureCache.erase(itr);
	}
	SAFE_RELEASE(_texture);
}

C3DTexture* C3DTexture::create(const char* path, bool generateMipmaps)
{
	for (size_t i = 0; i < __textureCache.size(); ++i) {
		C3DTexture* t = __textureCache[i];
		if (t->_path == path)
		{
			// If 'generateMipmaps' is true, call C3DTexture::generateMipamps() to force the
			// texture to generate its mipmap chain if it hasn't already done so.
			if (generateMipmaps && !t->isMipmapped())
			{
				t->generateMipmaps();
			}

			// Found a match.
			t->retain();

			return t;
		}
	}

	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(path);
	if (tex == nullptr)
	{
		LOG_ERROR_VARG("failed to load texture file: %s", path);

		return nullptr;
	}

	if (generateMipmaps)
		tex->generateMipmap();
	tex->retain();
	C3DTexture* retTexture = new C3DTexture();
	retTexture->_texture = tex;
	retTexture->_path = path;
	retTexture->_width = tex->getPixelsWide();
	retTexture->_height = tex->getPixelsHigh();

	retTexture->autorelease();
	return retTexture;
}

inline unsigned long nextPOT(unsigned long x)
{
	x = x - 1;
	x = x | (x >> 1);
	x = x | (x >> 2);
	x = x | (x >> 4);
	x = x | (x >> 8);
	x = x | (x >>16);
	return x + 1;
}

C3DTexture* C3DTexture::create(int width, int height, C3DTexture::Format fmt, const void* data, ssize_t dataLen, bool generateMipmaps)
{
	CCTexture2DPixelFormat format;
	switch(fmt)
	{
		case C3DTexture::RGBA:
			format = kCCTexture2DPixelFormat_RGBA8888;
			break;
		case C3DTexture::RGB:
			format = kCCTexture2DPixelFormat_RGB888;
			break;

		default:
			return nullptr;
	}

	CCTexture2D* texture2D = new CCTexture2D();
	texture2D->initWithData(data, dataLen, format, width, height, CCSize(width, height));

	C3DTexture* retTexture = new C3DTexture();
	retTexture->_texture = texture2D;
	retTexture->_width = width;
	retTexture->_height = height;
	retTexture->_mipmapped = generateMipmaps;
	retTexture->autorelease();

	if (generateMipmaps)
		retTexture->generateMipmaps();

	return retTexture;
}

C3DTexture* C3DTexture::create(int width, int height, C3DTexture::Format fmt, bool generateMipmaps)
{
	GLuint handle;
	GL_ASSERT(glGenTextures(1, &handle));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, handle));

	// Specify OpenGL texture image
	GLenum internalFormat = GL_RGBA;
	GLenum type = GL_UNSIGNED_BYTE;
	switch(fmt)
	{
		case RGBA:
			internalFormat = GL_RGBA;
			break;
		case RGB:
			internalFormat = GL_RGB;
			break;
		case ALPHA:
			internalFormat = GL_ALPHA;
			break;
		case DEPTH:
			internalFormat = GL_DEPTH_COMPONENT;
			type = GL_UNSIGNED_SHORT;
			break;
		default:
			LOG_ERROR_VARG("Unknown texture formmat: %d", fmt);

			return nullptr;
	}

	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, (GLenum)fmt, type, 0));

	C3DTexture* retTexture = new C3DTexture();
	retTexture->_handle = handle;
	retTexture->_texture = nullptr;
	retTexture->_width = width;
	retTexture->_height = height;
	retTexture->_mipmapped = false;
	retTexture->autorelease();
	return retTexture;
}

#ifdef USE_PVRTC
C3DTexture* C3DTexture::createCompressedPVRTC(const char* path)
{
	return create(path, false);
}
#endif

unsigned int C3DTexture::getWidth() const
{
	return _width;
}

unsigned int C3DTexture::getHeight() const
{
	return _height;
}

TextureHandle C3DTexture::getHandle() const
{
	if (_handle)
		return _handle;

	if (_texture == nullptr)
	{
		LOG_ERROR("getHandle from nullptr texture");
		return -1;
	}

	return _texture->getName();
}

void C3DTexture::setWrapMode(Texture_Wrap wrapS, Texture_Wrap wrapT)
{
	if (_texture != nullptr)
	{
		GLint currentTextureId;

		GL_ASSERT( glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTextureId) );
		GL_ASSERT( glBindTexture(GL_TEXTURE_2D, _texture->getName()) );
		GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)wrapS) );
		GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)wrapT) );
		GL_ASSERT( glBindTexture(GL_TEXTURE_2D, (GLuint)currentTextureId) );
	}
}

void C3DTexture::setFilterMode(Texture_Filter minificationFilter, Texture_Filter magnificationFilter)
{
	if (_texture != nullptr)
	{
		GLint currentTextureId;
		GL_ASSERT( glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTextureId) );
		GL_ASSERT( glBindTexture(GL_TEXTURE_2D, _texture->getName()) );
		GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)minificationFilter) );
		GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)magnificationFilter) );
		GL_ASSERT( glBindTexture(GL_TEXTURE_2D, (GLuint)currentTextureId) );
	}
}

void C3DTexture::generateMipmaps()
{
	if (_texture != nullptr && !_texture->hasMipmaps() )
	{
		_texture->generateMipmap();
		GLint currentTextureId;
		GL_ASSERT( glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTextureId) );
		GL_ASSERT( glBindTexture(GL_TEXTURE_2D, _texture->getName()) );
		glGenerateMipmap(GL_TEXTURE_2D);

		GL_ASSERT( glBindTexture(GL_TEXTURE_2D, (GLuint)currentTextureId) );
	}
}

bool C3DTexture::isMipmapped() const
{
	if (_texture == nullptr)
	{
		return false;
	}
	return _texture->hasMipmaps();
}
}
