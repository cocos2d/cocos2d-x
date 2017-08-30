#include "CCTextureData.h"

DRAGONBONES_NAMESPACE_BEGIN

CCTextureData::CCTextureData() :
    texture(nullptr)
{
    _onClear();
}
CCTextureData::~CCTextureData()
{
    _onClear();
}

void CCTextureData::_onClear()
{
    TextureData::_onClear();

    if (texture)
    {
        texture->release();
        texture = nullptr;
    }
}

CCTextureAtlasData::CCTextureAtlasData() :
    texture(nullptr)
{
    _onClear();
}
CCTextureAtlasData::~CCTextureAtlasData()
{
    _onClear();
}

void CCTextureAtlasData::_onClear()
{
    TextureAtlasData::_onClear();

    if (texture)
    {
        //texture->release();
        texture = nullptr;
    }
}

TextureData * CCTextureAtlasData::generateTexture() const
{
    return BaseObject::borrowObject<CCTextureData>();
}

DRAGONBONES_NAMESPACE_END