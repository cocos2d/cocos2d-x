#include "CCSlot.h"
#include "CCTextureData.h"
#include "CCArmatureDisplay.h"

DRAGONBONES_NAMESPACE_BEGIN

CCSlot::CCSlot() 
{
    _onClear();
}
CCSlot::~CCSlot() 
{
    _onClear();
}

void CCSlot::_onClear()
{
    Slot::_onClear();

    _renderDisplay = nullptr;
}

void CCSlot::_initDisplay(void* value)
{
    const auto renderDisplay = static_cast<cocos2d::Node*>(value);
    renderDisplay->retain();
}

void CCSlot::_disposeDisplay(void* value)
{
    const auto renderDisplay = static_cast<cocos2d::Node*>(value);
    renderDisplay->release();
}

void CCSlot::_onUpdateDisplay()
{
    if (!this->_rawDisplay)
    {
        // TODO
    }

    if (this->_display)
    {
        if (this->_childArmature)
        {
            _renderDisplay = dynamic_cast<cocos2d::Node*>(static_cast<IArmatureDisplay*>(this->_display));
        }
        else
        {
            _renderDisplay = static_cast<cocos2d::Node*>(this->_display);
        }
    }
    else
    {
        _renderDisplay = static_cast<cocos2d::Node*>(this->_rawDisplay);
    }
}

void CCSlot::_addDisplay()
{
    const auto container = dynamic_cast<CCArmatureDisplay*>(this->_armature->_display);
    container->addChild(_renderDisplay);
}

void CCSlot::_replaceDisplay(void* value, bool isArmatureDisplayContainer)
{
    const auto container = dynamic_cast<CCArmatureDisplay*>(this->_armature->_display);
    const auto prevDisplay = isArmatureDisplayContainer ? dynamic_cast<cocos2d::Node*>(static_cast<IArmatureDisplay*>(value)) : static_cast<cocos2d::Node*>(value); // static_cast<cocos2d::Node*>(isArmatureDisplayContainer ? static_cast<CCArmatureDisplay*>(value) : value); // WTF
    container->addChild(_renderDisplay, prevDisplay->getLocalZOrder());
    container->removeChild(prevDisplay);
}

void CCSlot::_removeDisplay()
{
    _renderDisplay->removeFromParent();
}

void CCSlot::_updateVisible()
{
    this->_renderDisplay->setVisible(this->_parent->getVisible());
}

void CCSlot::_updateBlendMode()
{
    cocos2d::Sprite* spriteDisplay = dynamic_cast<cocos2d::Sprite*>(_renderDisplay);
    if (spriteDisplay)
    {
        switch (this->_blendMode)
        {
            case BlendMode::Normal:
                //spriteDisplay->setBlendFunc(cocos2d::BlendFunc::DISABLE);
                break;

            case BlendMode::Add:
            {
                const auto texture = spriteDisplay->getTexture();
                if (texture && texture->hasPremultipliedAlpha())
                {
                    cocos2d::BlendFunc blendFunc = { GL_ONE, GL_ONE };
                    spriteDisplay->setBlendFunc(blendFunc);
                }
                else
                {
                    spriteDisplay->setBlendFunc(cocos2d::BlendFunc::ADDITIVE);
                }
                break;
            }

            default:
                break;
        }
    }
    else if (this->_childArmature)
    {
        for (const auto slot : this->_childArmature->getSlots())
        {
            slot->_blendMode = this->_blendMode;
            slot->_updateBlendMode();
        }
    }
}

void CCSlot::_updateColor()
{
    _renderDisplay->setOpacity(this->_colorTransform.alphaMultiplier * 255.f);
    static cocos2d::Color3B helpColor;
    helpColor.r = this->_colorTransform.redMultiplier * 255.f;
    helpColor.g = this->_colorTransform.greenMultiplier * 255.f;
    helpColor.b = this->_colorTransform.blueMultiplier * 255.f;
    _renderDisplay->setColor(helpColor);
}

void CCSlot::_updateFilters() 
{
}

void CCSlot::_updateFrame()
{
    const auto frameDisplay = (DBCCSprite*)(this->_rawDisplay);

    if (this->_display && this->_displayIndex >= 0)
    {
        const unsigned displayIndex = this->_displayIndex;
        const auto rawDisplayData = displayIndex < this->_displayDataSet->displays.size() ? this->_displayDataSet->displays[displayIndex] : nullptr;
        const auto replacedDisplayData = displayIndex < this->_replacedDisplayDataSet.size() ? this->_replacedDisplayDataSet[displayIndex] : nullptr;
        const auto currentDisplayData = replacedDisplayData ? replacedDisplayData : rawDisplayData;
        const auto currentTextureData = static_cast<CCTextureData*>(currentDisplayData->texture);

        if (currentTextureData)
        {
            const auto textureAtlasTexture = static_cast<CCTextureAtlasData*>(currentTextureData->parent)->texture;
            if (!currentTextureData->texture && textureAtlasTexture)
            {
                cocos2d::Rect rect(currentTextureData->region.x, currentTextureData->region.y, currentTextureData->region.width, currentTextureData->region.height);
                cocos2d::Vec2 offset(0.f, 0.f);
                cocos2d::Size originSize(currentTextureData->region.width, currentTextureData->region.height);

                currentTextureData->texture = cocos2d::SpriteFrame::createWithTexture(textureAtlasTexture, rect, currentTextureData->rotated, offset, originSize); // TODO multiply textureAtlas
                currentTextureData->texture->retain();
            }

            const auto texture = this->_armature->_replacedTexture ? static_cast<cocos2d::Texture2D*>(this->_armature->_replacedTexture) : (currentTextureData->texture ? currentTextureData->texture->getTexture() : nullptr);

            if (this->_meshData && this->_display == this->_meshDisplay)
            {
                const auto& region = currentTextureData->region;
                const auto& textureAtlasSize = currentTextureData->texture->getTexture()->getContentSizeInPixels();
                auto displayVertices = new cocos2d::V3F_C4B_T2F[(unsigned)(this->_meshData->uvs.size() / 2)]; // does cocos2dx release it?
                auto vertexIndices = new unsigned short[this->_meshData->vertexIndices.size()]; // does cocos2dx release it?
                cocos2d::Rect boundsRect(999999.f, 999999.f, -999999.f, -999999.f);

                if (this->_meshData != rawDisplayData->mesh && rawDisplayData && rawDisplayData != currentDisplayData)
                {
                    this->_pivotX = rawDisplayData->transform.x - currentDisplayData->transform.x;
                    this->_pivotY = rawDisplayData->transform.y - currentDisplayData->transform.y;
                }
                else
                {
                    this->_pivotX = 0.f;
                    this->_pivotY = 0.f;
                }

                for (std::size_t i = 0, l = this->_meshData->uvs.size(); i < l; i += 2)
                {
                    const auto iH = (unsigned)(i / 2);
                    const auto x = this->_meshData->vertices[i];
                    const auto y = this->_meshData->vertices[i + 1];
                    cocos2d::V3F_C4B_T2F vertexData;
                    vertexData.vertices.set(x, -y, 0.f);
                    vertexData.texCoords.u = (region.x + this->_meshData->uvs[i] * region.width) / textureAtlasSize.width;
                    vertexData.texCoords.v = (region.y + this->_meshData->uvs[i + 1] * region.height) / textureAtlasSize.height;
                    vertexData.colors = cocos2d::Color4B::WHITE;
                    displayVertices[iH] = vertexData;

                    if (boundsRect.origin.x > x)
                    {
                        boundsRect.origin.x = x;
                    }

                    if (boundsRect.size.width < x) 
                    {
                        boundsRect.size.width = x;
                    }

                    if (boundsRect.origin.y > -y)
                    {
                        boundsRect.origin.y = -y;
                    }

                    if (boundsRect.size.height < -y)
                    {
                        boundsRect.size.height = -y;
                    }
                }

                boundsRect.size.width -= boundsRect.origin.x;
                boundsRect.size.height -= boundsRect.origin.y;

                for (std::size_t i = 0, l = this->_meshData->vertexIndices.size(); i < l; ++i)
                {
                    vertexIndices[i] = this->_meshData->vertexIndices[i];
                }

                // In cocos2dx render meshDisplay and frameDisplay are the same display
                if (currentTextureData->texture)
                {
                    frameDisplay->setSpriteFrame(currentTextureData->texture); // polygonInfo will be override
                    if (texture != currentTextureData->texture->getTexture())
                    {
                        frameDisplay->setTexture(texture); // Relpace texture // polygonInfo will be override
                    }
                }

                //
                cocos2d::PolygonInfo polygonInfo;
                auto& triangles = polygonInfo.triangles;
                triangles.verts = displayVertices;
                triangles.indices = vertexIndices;
                triangles.vertCount = (unsigned)(this->_meshData->uvs.size() / 2);
                triangles.indexCount = (unsigned)(this->_meshData->vertexIndices.size());
#if COCOS2D_VERSION >= 0x00031400
                polygonInfo.setRect(boundsRect);
#else
                polygonInfo.rect = boundsRect; // Copy
#endif
                frameDisplay->setContentSize(boundsRect.size);
                frameDisplay->setPolygonInfo(polygonInfo);
                frameDisplay->setColor(frameDisplay->getColor()); // Backup

                if (this->_meshData->skinned)
                {
                    frameDisplay->setPosition(0.f, 0.f);
                    frameDisplay->setRotation(0.f);
                    frameDisplay->setRotationSkewX(0.f);
                    frameDisplay->setRotationSkewY(0.f);
                    frameDisplay->setScale(1.f, 1.f);
                }
            }
            else
            {
                const auto scale = this->_armature->getArmatureData().scale;
                this->_pivotX = currentDisplayData->pivot.x;
                this->_pivotY = currentDisplayData->pivot.y;

                if (currentDisplayData->isRelativePivot)
                {
                    const auto& rectData = currentTextureData->frame ? *currentTextureData->frame : currentTextureData->region;
                    auto width = rectData.width * scale;
                    auto height = rectData.height * scale;
                    if (!currentTextureData->frame && currentTextureData->rotated)
                    {
                        width = rectData.height;
                        height = rectData.width;
                    }

                    this->_pivotX *= width;
                    this->_pivotY *= height;
                }

                if (currentTextureData->frame)
                {
                    this->_pivotX += currentTextureData->frame->x * scale;
                    this->_pivotY += currentTextureData->frame->y * scale;
                }

                if (rawDisplayData && rawDisplayData != currentDisplayData)
                {
                    this->_pivotX += rawDisplayData->transform.x - currentDisplayData->transform.x;
                    this->_pivotY += rawDisplayData->transform.y - currentDisplayData->transform.y;
                }

                this->_pivotY -= currentTextureData->region.height * this->_armature->getArmatureData().scale;

                frameDisplay->setSpriteFrame(currentTextureData->texture); // polygonInfo will be override

                if (texture != currentTextureData->texture->getTexture())
                {
                    frameDisplay->setTexture(texture); // Relpace texture // polygonInfo will be override
                }

                this->_blendModeDirty = true; // Relpace texture // blendMode will be override
            }

            this->_updateVisible();

            return;
        }
    }

    this->_pivotX = 0.f;
    this->_pivotY = 0.f;

    frameDisplay->setTexture(nullptr);
    frameDisplay->setTextureRect(cocos2d::Rect::ZERO);
    frameDisplay->setVisible(false);
    frameDisplay->setPosition(this->origin.x, this->origin.y);
}

void CCSlot::_updateMesh() 
{
    const auto meshDisplay = static_cast<DBCCSprite*>(this->_meshDisplay);
    const auto hasFFD = !this->_ffdVertices.empty();
    const auto displayVertices = meshDisplay->getPolygonInfoModify().triangles.verts;
    cocos2d::Rect boundsRect(999999.f, 999999.f, -999999.f, -999999.f);

    if (this->_meshData->skinned)
    {
        std::size_t iF = 0;
        for (std::size_t i = 0, l = this->_meshData->vertices.size(); i < l; i += 2)
        {
            const auto iH = unsigned(i / 2);

            const auto& boneIndices = this->_meshData->boneIndices[iH];
            const auto& boneVertices = this->_meshData->boneVertices[iH];
            const auto& weights = this->_meshData->weights[iH];

            float xG = 0.f, yG = 0.f;
            for (std::size_t iB = 0, lB = boneIndices.size(); iB < lB; ++iB)
            {
                const auto bone = this->_meshBones[boneIndices[iB]];
                const auto matrix = bone->globalTransformMatrix;
                const auto weight = weights[iB];

                float xL = 0.f, yL = 0.f;
                if (hasFFD)
                {
                    xL = boneVertices[iB * 2] + this->_ffdVertices[iF];
                    yL = boneVertices[iB * 2 + 1] + this->_ffdVertices[iF + 1];
                }
                else
                {
                    xL = boneVertices[iB * 2];
                    yL = boneVertices[iB * 2 + 1];
                }

                xG += (matrix->a * xL + matrix->c * yL + matrix->tx) * weight;
                yG += (matrix->b * xL + matrix->d * yL + matrix->ty) * weight;

                iF += 2;
            }

            auto& vertices = displayVertices[iH];
            auto& vertex = vertices.vertices;

            vertex.set(xG, -yG, 0.f);

            if (boundsRect.origin.x > xG)
            {
                boundsRect.origin.x = xG;
            }

            if (boundsRect.size.width < xG)
            {
                boundsRect.size.width = xG;
            }

            if (boundsRect.origin.y > -yG)
            {
                boundsRect.origin.y = -yG;
            }

            if (boundsRect.size.height < -yG)
            {
                boundsRect.size.height = -yG;
            }
        }
    }
    else if (hasFFD)
    {
        const auto& vertices = _meshData->vertices;
        for (std::size_t i = 0, l = this->_meshData->vertices.size(); i < l; i += 2)
        {
            const auto iH = unsigned(i / 2);
            const auto xG = vertices[i] + _ffdVertices[i];
            const auto yG = vertices[i + 1] + _ffdVertices[i + 1];

            auto& vertices = displayVertices[iH];
            auto& vertex = vertices.vertices;

            vertex.set(xG, -yG, 0.f);

            if (boundsRect.origin.x > xG)
            {
                boundsRect.origin.x = xG;
            }

            if (boundsRect.size.width < xG)
            {
                boundsRect.size.width = xG;
            }

            if (boundsRect.origin.y > -yG)
            {
                boundsRect.origin.y = -yG;
            }

            if (boundsRect.size.height < -yG)
            {
                boundsRect.size.height = -yG;
            }
        }
    }

    boundsRect.size.width -= boundsRect.origin.x;
    boundsRect.size.height -= boundsRect.origin.y;


    auto polygonInfo = meshDisplay->getPolygonInfo();
#if COCOS2D_VERSION >= 0x00031400
    polygonInfo.setRect(boundsRect);
#else
    polygonInfo.rect = boundsRect; // Copy
#endif
    const auto& transform = meshDisplay->getNodeToParentTransform();
    meshDisplay->setContentSize(boundsRect.size);
    meshDisplay->setPolygonInfo(polygonInfo);

    _renderDisplay->setNodeToParentTransform(transform);
}

void CCSlot::_updateTransform()
{
    static cocos2d::Mat4 transform;
    transform.m[0] = this->globalTransformMatrix->a;
    transform.m[1] = -this->globalTransformMatrix->b;
    transform.m[4] = -this->globalTransformMatrix->c;
    transform.m[5] = this->globalTransformMatrix->d;
    transform.m[12] = this->globalTransformMatrix->tx - (this->globalTransformMatrix->a * this->_pivotX + this->globalTransformMatrix->c * this->_pivotY);
    transform.m[13] = -(this->globalTransformMatrix->ty - (this->globalTransformMatrix->b * this->_pivotX + this->globalTransformMatrix->d * this->_pivotY));

    _renderDisplay->setNodeToParentTransform(transform);
}

DRAGONBONES_NAMESPACE_END
