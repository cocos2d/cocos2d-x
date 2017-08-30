#ifndef DRAGONBONES_CC_TEXTURE_DATA_H
#define DRAGONBONES_CC_TEXTURE_DATA_H

#include "dragonbones/DragonBonesHeaders.h"
#include "cocos2d.h"

DRAGONBONES_NAMESPACE_BEGIN
class CCTextureData final : public TextureData
{
    BIND_CLASS_TYPE(CCTextureData);

public:
    cocos2d::SpriteFrame* texture;

    CCTextureData();
    ~CCTextureData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(CCTextureData);

protected:
    virtual void _onClear() override;
};

class CCTextureAtlasData final : public TextureAtlasData
{
    BIND_CLASS_TYPE(CCTextureAtlasData);

public:
    cocos2d::Texture2D* texture;

    CCTextureAtlasData();
    ~CCTextureAtlasData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(CCTextureAtlasData);

protected:
    virtual void _onClear() override;

public:
    virtual TextureData* generateTexture() const override;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_CC_TEXTURE_DATA_H
