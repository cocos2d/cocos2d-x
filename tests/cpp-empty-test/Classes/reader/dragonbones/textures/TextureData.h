#ifndef DRAGONBONES_TEXTURE_DATA_H
#define DRAGONBONES_TEXTURE_DATA_H

#include "../core/BaseObject.h"
#include "../geom/Rectangle.h"

DRAGONBONES_NAMESPACE_BEGIN

class TextureAtlasData;

/**
 * @private
 */
class TextureData : public BaseObject
{
public:
    static Rectangle* generateRectangle();

public:
    bool rotated;
    std::string name;
    Rectangle* frame;
    TextureAtlasData* parent;
    Rectangle region;

    TextureData();
    virtual ~TextureData() = 0;

protected:
    virtual void _onClear() override;
};

class TextureAtlasData : public BaseObject
{
public:
    bool autoSearch;
    float scale;
    TextureFormat format;
    std::string name;
    std::string imagePath;
    /** @private */
    std::map<std::string, TextureData*> textures;

    /** @private */
    TextureAtlasData();
    /** @private */
    virtual ~TextureAtlasData() = 0;

protected:
    virtual void _onClear() override;

public:
    /** @private */
    virtual TextureData* generateTexture() const = 0;
    /** @private */
    virtual void addTexture(TextureData* value);
    /** @private */
    inline TextureData* getTexture(const std::string& texName) const
    {
        return mapFind(textures, texName);
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_TEXTURE_DATA_H
