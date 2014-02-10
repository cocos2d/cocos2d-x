#include "Base.h"
#include "C3DSampler.h"
#include "C3DTexture.h"
#include "Stream.h"
#include "ElementNode.h"

NS_CC_BEGIN

C3DSampler::C3DSampler()
:_texture(nullptr)
,_wrapS(Texture_Wrap_REPEAT)
,_wrapT(Texture_Wrap_REPEAT)
,_magFilter(Texture_Filter_LINEAR)
{
    _minFilter = Texture_Filter_LINEAR;
}

C3DSampler::C3DSampler(C3DTexture* texture)
:_texture(texture)
,_wrapS(Texture_Wrap_REPEAT)
,_wrapT(Texture_Wrap_REPEAT)
,_magFilter(Texture_Filter_LINEAR)
{
    texture->retain();
    _minFilter = texture->isMipmapped() ? Texture_Filter_LINEAR_MIPMAP_LINEAR : Texture_Filter_LINEAR;
}

C3DSampler::~C3DSampler()
{
    SAFE_RELEASE(_texture);
}

C3DSampler* C3DSampler::create(C3DTexture* texture)
{
    assert(texture != nullptr);    

    C3DSampler* sample = new C3DSampler(texture);

    return sample;
}

C3DSampler* C3DSampler::create(const char* path, bool generateMipmaps)
{
    C3DTexture* texture = C3DTexture::create(path, generateMipmaps);

    assert(texture != nullptr);    

    C3DSampler* sample = new C3DSampler(texture);

    return sample;
}

void C3DSampler::setTexture(const char* path, bool generateMipmaps)
{
    SAFE_RELEASE(_texture);
    C3DTexture* texture = C3DTexture::create(path, generateMipmaps);

    assert(texture != nullptr);    
    
    _texture = texture;    
    _texture->retain();    
   
}

void C3DSampler::setWrapMode(Texture_Wrap wrapS, Texture_Wrap wrapT)
{
    _wrapS = wrapS;
    _wrapT = wrapT;
}

void C3DSampler::setFilterMode(Texture_Filter minificationFilter, Texture_Filter magnificationFilter)
{
    _minFilter = minificationFilter;
    _magFilter = magnificationFilter;
}

C3DTexture* C3DSampler::getTexture() const
{
    return _texture;
}

void C3DSampler::bind()
{
    if(_texture == nullptr)
        return;

    GL_ASSERT( glBindTexture(GL_TEXTURE_2D, _texture->getHandle()) );
    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)_wrapS) );
    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)_wrapT) );
    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)_minFilter) );
    GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)_magFilter) );
}

const char* C3DSampler::getPath() const
{
    if (_texture)
        return _texture->getPath();
    else
        return "";
}

Texture_Wrap parseTextureWrapMode(const char* str, Texture_Wrap defaultValue)
{
    if (str == nullptr || strlen(str) == 0)
    {
        return defaultValue;
    }
    else if (strcmp(str, "REPEAT") == 0)
    {
        return Texture_Wrap_REPEAT;
    }
    else if (strcmp(str, "CLAMP") == 0)
    {
        return Texture_Wrap_CLAMP;
    }
    return defaultValue;
}

Texture_Filter parseTextureFilterMode(const char* str, Texture_Filter defaultValue)
{
    if (str == nullptr || strlen(str) == 0)
    {
        return defaultValue;
    }
    else if (strcmp(str, "NEAREST") == 0)
    {
        return Texture_Filter_NEAREST;
    }
    else if (strcmp(str, "LINEAR") == 0)
    {
        return Texture_Filter_LINEAR;
    }
    else if (strcmp(str, "NEAREST_MIPMAP_NEAREST") == 0)
    {
        return Texture_Filter_NEAREST_MIPMAP_NEAREST;
    }
    else if (strcmp(str, "LINEAR_MIPMAP_NEAREST") == 0)
    {
        return Texture_Filter_LINEAR_MIPMAP_NEAREST;
    }
    else if (strcmp(str, "NEAREST_MIPMAP_LINEAR") == 0)
    {
        return Texture_Filter_NEAREST_MIPMAP_LINEAR;
    }
    else if (strcmp(str, "LINEAR_MIPMAP_LINEAR") == 0)
    {
        return Texture_Filter_LINEAR_MIPMAP_LINEAR;
    }
    return defaultValue;
}

const char* textureFilterModeToString(Texture_Filter filter)
{
    switch (filter)
    {
    case Texture_Filter_LINEAR:
        return "LINEAR";
    case Texture_Filter_NEAREST:
        return "NEAREST";
    case Texture_Filter_LINEAR_MIPMAP_LINEAR:
        return "LINEAR_MIPMAP_LINEAR";
    case Texture_Filter_LINEAR_MIPMAP_NEAREST:
        return "LINEAR_MIPMAP_NEAREST";
    case Texture_Filter_NEAREST_MIPMAP_LINEAR:
        return "NEAREST_MIPMAP_LINEAR";
    case Texture_Filter_NEAREST_MIPMAP_NEAREST:
        return "NEAREST_MIPMAP_NEAREST";

    }

    return "NEAREST";
}

bool textureFilterModeHasMipmap(Texture_Filter filter)
{
    return filter != Texture_Filter_LINEAR && filter != Texture_Filter_NEAREST;
}

const char* textureWrapModeToString(Texture_Wrap wrap)
{
    switch (wrap)
    {
    case Texture_Wrap_CLAMP:
        return "CLAMP";
    case Texture_Wrap_REPEAT:
        return "REPEAT";
    }
    return "CLAMP";
}


bool C3DSampler::load(ElementNode* node)
{
    // Read the texture uniform name
    const char* name = node->getNodeName();
    if (strlen(name) == 0)
        return false; // missing texture uniform name

    // Get the texture path
    const char* path = node->getElement("path");
    if (path == nullptr || strlen(path) == 0)
        return false; // missing texture path

    // Read texture state (booleans default to 'false' if not present)
    bool mipmap = node->getElement("mipmap",&mipmap);
    Texture_Wrap wrapS = parseTextureWrapMode(node->getElement("wrapS"), Texture_Wrap_REPEAT);
    Texture_Wrap wrapT = parseTextureWrapMode(node->getElement("wrapT"), Texture_Wrap_REPEAT);
    Texture_Filter minFilter = parseTextureFilterMode(node->getElement("minFilter"), mipmap ? Texture_Filter_NEAREST_MIPMAP_LINEAR : Texture_Filter_LINEAR);
    Texture_Filter magFilter = parseTextureFilterMode(node->getElement("magFilter"), Texture_Filter_LINEAR);
        
    this->setTexture(path,mipmap);
   
    this->setWrapMode(wrapS, wrapT);
    this->setFilterMode(minFilter, magFilter);
  
    return true;
}

bool C3DSampler::save(ElementNode* node)
{    
    node->setElement("path", this->getPath());
    node->setElement("mipmap", textureFilterModeHasMipmap(this->getMinFilter()) ? "true" : "false");
    node->setElement("wrapS", textureWrapModeToString(this->getWrapS()));
    node->setElement("wrapT", textureWrapModeToString(this->getWrapS()));
    node->setElement("minFilter", textureFilterModeToString(this->getMinFilter()));
    node->setElement("magFilter", textureFilterModeToString(this->getMagFilter()));
    return true;
}

NS_CC_END
