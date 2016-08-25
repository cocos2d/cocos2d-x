/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "2d/CCSpriteFrameCache.h"

#include <vector>


#include "2d/CCSprite.h"
#include "2d/CCAutoPolygon.h"
#include "platform/CCFileUtils.h"
#include "base/CCNS.h"
#include "base/ccMacros.h"
#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCTextureCache.h"
#include "base/CCNinePatchImageParser.h"

using namespace std;

NS_CC_BEGIN

static SpriteFrameCache *_sharedSpriteFrameCache = nullptr;

SpriteFrameCache* SpriteFrameCache::getInstance()
{
    if (! _sharedSpriteFrameCache)
    {
        _sharedSpriteFrameCache = new (std::nothrow) SpriteFrameCache();
        _sharedSpriteFrameCache->init();
    }

    return _sharedSpriteFrameCache;
}

void SpriteFrameCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedSpriteFrameCache);
}

bool SpriteFrameCache::init()
{
    _spriteFrames.reserve(20);
    _spriteFramesAliases.reserve(20);
    _loadedFileNames = new std::set<std::string>();
    return true;
}

SpriteFrameCache::~SpriteFrameCache()
{
    CC_SAFE_DELETE(_loadedFileNames);
}

void SpriteFrameCache::parseIntegerList(const std::string &string, std::vector<int> &res)
{
    std::string delim(" ");

    size_t n = std::count(string.begin(), string.end(), ' ');
    res.resize(n+1);
    
    size_t start  = 0U;
    size_t end = string.find(delim);
    
    int i=0;
    while (end != std::string::npos)
    {
        res[i++] = atoi(string.substr(start, end - start).c_str());
        start = end + delim.length();
        end = string.find(delim, start);
    }
    
    res[i] = atoi(string.substr(start, end).c_str());
}

void SpriteFrameCache::initializePolygonInfo(const Size &textureSize,
                                             const Size &spriteSize,
                                             const std::vector<int> &vertices,
                                             const std::vector<int> &verticesUV,
                                             const std::vector<int> &triangleIndices,
                                             PolygonInfo &info)
{
    size_t vertexCount = vertices.size();
    size_t indexCount = triangleIndices.size();
    
    float scaleFactor = CC_CONTENT_SCALE_FACTOR();

    V3F_C4B_T2F *vertexData = new (std::nothrow) V3F_C4B_T2F[vertexCount];
    for (size_t i = 0; i < vertexCount/2; i++)
    {
        vertexData[i].colors = Color4B::WHITE;
        vertexData[i].vertices = Vec3(vertices[i*2] / scaleFactor,
                                      (spriteSize.height - vertices[i*2+1]) / scaleFactor,
                                      0);
        vertexData[i].texCoords = Tex2F(verticesUV[i*2] / textureSize.width,
                                        verticesUV[i*2+1] / textureSize.height);
    }

    unsigned short *indexData = new unsigned short[indexCount];
    for (size_t i = 0; i < indexCount; i++)
    {
        indexData[i] = static_cast<unsigned short>(triangleIndices[i]);
    }

    info.triangles.vertCount = static_cast<int>(vertexCount);
    info.triangles.verts = vertexData;
    info.triangles.indexCount = static_cast<int>(indexCount);
    info.triangles.indices = indexData;
    info.rect = Rect(0, 0, spriteSize.width, spriteSize.height);
}

void SpriteFrameCache::addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D* texture)
{
    /*
    Supported Zwoptex Formats:

    ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
    ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
    ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
    ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+

    Version 3 with TexturePacker 4.0 polygon mesh packing
    */

    if (dictionary["frames"].getType() != cocos2d::Value::Type::MAP)
        return;

    ValueMap& framesDict = dictionary["frames"].asValueMap();
    int format = 0;

    Size textureSize;

    // get the format
    if (dictionary.find("metadata") != dictionary.end())
    {
        ValueMap& metadataDict = dictionary["metadata"].asValueMap();
        format = metadataDict["format"].asInt();

        if(metadataDict.find("size") != metadataDict.end())
        {
            textureSize = SizeFromString(metadataDict["size"].asString());
        }
    }

    // check the format
    CCASSERT(format >=0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    auto textureFileName = Director::getInstance()->getTextureCache()->getTextureFilePath(texture);
    Image* image = nullptr;
    NinePatchImageParser parser;
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        ValueMap& frameDict = iter->second.asValueMap();
        std::string spriteFrameName = iter->first;
        SpriteFrame* spriteFrame = _spriteFrames.at(spriteFrameName);
        if (spriteFrame)
        {
            continue;
        }
        
        if(format == 0) 
        {
            float x = frameDict["x"].asFloat();
            float y = frameDict["y"].asFloat();
            float w = frameDict["width"].asFloat();
            float h = frameDict["height"].asFloat();
            float ox = frameDict["offsetX"].asFloat();
            float oy = frameDict["offsetY"].asFloat();
            int ow = frameDict["originalWidth"].asInt();
            int oh = frameDict["originalHeight"].asInt();
            // check ow/oh
            if(!ow || !oh)
            {
                CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenerate the .plist");
            }
            // abs ow/oh
            ow = std::abs(ow);
            oh = std::abs(oh);
            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                                                         Rect(x, y, w, h),
                                                         false,
                                                         Vec2(ox, oy),
                                                         Size((float)ow, (float)oh)
                                                         );
        } 
        else if(format == 1 || format == 2) 
        {
            Rect frame = RectFromString(frameDict["frame"].asString());
            bool rotated = false;

            // rotation
            if (format == 2)
            {
                rotated = frameDict["rotated"].asBool();
            }

            Vec2 offset = PointFromString(frameDict["offset"].asString());
            Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());

            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                                                         frame,
                                                         rotated,
                                                         offset,
                                                         sourceSize
                                                         );
        } 
        else if (format == 3)
        {
            // get values
            Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
            Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
            Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
            Rect textureRect = RectFromString(frameDict["textureRect"].asString());
            bool textureRotated = frameDict["textureRotated"].asBool();

            // get aliases
            ValueVector& aliases = frameDict["aliases"].asValueVector();

            for(const auto &value : aliases) {
                std::string oneAlias = value.asString();
                if (_spriteFramesAliases.find(oneAlias) != _spriteFramesAliases.end())
                {
                    CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                }

                _spriteFramesAliases[oneAlias] = Value(spriteFrameName);
            }

            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                                                         Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
                                                         textureRotated,
                                                         spriteOffset,
                                                         spriteSourceSize);

            if(frameDict.find("vertices") != frameDict.end())
            {
                std::vector<int> vertices;
                parseIntegerList(frameDict["vertices"].asString(), vertices);
                std::vector<int> verticesUV;
                parseIntegerList(frameDict["verticesUV"].asString(), verticesUV);
                std::vector<int> indices;
                parseIntegerList(frameDict["triangles"].asString(), indices);

                PolygonInfo info;
                initializePolygonInfo(textureSize, spriteSourceSize, vertices, verticesUV, indices, info);
                spriteFrame->setPolygonInfo(info);
            }
            if (frameDict.find("anchor") != frameDict.end())
            {
                spriteFrame->setAnchorPoint(PointFromString(frameDict["anchor"].asString()));
            }
        }

        bool flag = NinePatchImageParser::isNinePatchImage(spriteFrameName);
        if(flag)
        {
            if (image == nullptr) {
                image = new (std::nothrow) Image();
                image->initWithImageFile(textureFileName);
            }
            parser.setSpriteFrameInfo(image, spriteFrame->getRectInPixels(), spriteFrame->isRotated());
            texture->addSpriteFrameCapInset(spriteFrame, parser.parseCapInset());
        }
        // add sprite frame
        _spriteFrames.insert(spriteFrameName, spriteFrame);
    }
    CC_SAFE_DELETE(image);
}

void SpriteFrameCache::addSpriteFramesWithDictionary(ValueMap& dict, const std::string &texturePath)
{
    std::string pixelFormatName;
    if (dict.find("metadata") != dict.end())
    {
        ValueMap& metadataDict = dict.at("metadata").asValueMap();
        if (metadataDict.find("pixelFormat") != metadataDict.end())
        {
            pixelFormatName = metadataDict.at("pixelFormat").asString();
        }
    }
    
    Texture2D *texture = nullptr;
    static std::unordered_map<std::string, Texture2D::PixelFormat> pixelFormats = {
        {"RGBA8888", Texture2D::PixelFormat::RGBA8888},
        {"RGBA4444", Texture2D::PixelFormat::RGBA4444},
        {"RGB5A1", Texture2D::PixelFormat::RGB5A1},
        {"RGBA5551", Texture2D::PixelFormat::RGB5A1},
        {"RGB565", Texture2D::PixelFormat::RGB565},
        {"A8", Texture2D::PixelFormat::A8},
        {"ALPHA", Texture2D::PixelFormat::A8},
        {"I8", Texture2D::PixelFormat::I8},
        {"AI88", Texture2D::PixelFormat::AI88},
        {"ALPHA_INTENSITY", Texture2D::PixelFormat::AI88},
        //{"BGRA8888", Texture2D::PixelFormat::BGRA8888}, no Image conversion RGBA -> BGRA
        {"RGB888", Texture2D::PixelFormat::RGB888}
    };

    auto pixelFormatIt = pixelFormats.find(pixelFormatName);
    if (pixelFormatIt != pixelFormats.end())
    {
        const Texture2D::PixelFormat pixelFormat = (*pixelFormatIt).second;
        const Texture2D::PixelFormat currentPixelFormat = Texture2D::getDefaultAlphaPixelFormat();
        Texture2D::setDefaultAlphaPixelFormat(pixelFormat);
        texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
        Texture2D::setDefaultAlphaPixelFormat(currentPixelFormat);
    }
    else
    {
        texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
    }
    
    if (texture)
    {
        addSpriteFramesWithDictionary(dict, texture);
    }
    else
    {
        CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
    }
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist, Texture2D *texture)
{
    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        return; // We already added it
    }
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

    addSpriteFramesWithDictionary(dict, texture);
    _loadedFileNames->insert(plist);
}

void SpriteFrameCache::addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture)
{
    ValueMap dict = FileUtils::getInstance()->getValueMapFromData(plist_content.c_str(), static_cast<int>(plist_content.size()));
    addSpriteFramesWithDictionary(dict, texture);
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName)
{
    CCASSERT(textureFileName.size()>0, "texture name should not be null");
    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        return; // We already added it
    }
    
    const std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    addSpriteFramesWithDictionary(dict, textureFileName);
    _loadedFileNames->insert(plist);
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist)
{
    CCASSERT(plist.size()>0, "plist filename should not be nullptr");
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    if (fullPath.size() == 0)
    {
        // return if plist file doesn't exist
        CCLOG("cocos2d: SpriteFrameCache: can not find %s", plist.c_str());
        return;
    }

    if (_loadedFileNames->find(plist) == _loadedFileNames->end())
    {
        
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

        string texturePath("");

        if (dict.find("metadata") != dict.end())
        {
            ValueMap& metadataDict = dict["metadata"].asValueMap();
            // try to read  texture file name from meta data
            texturePath = metadataDict["textureFileName"].asString();
        }

        if (!texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath, plist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = plist;

            // remove .xxx
            size_t startPos = texturePath.find_last_of("."); 
            texturePath = texturePath.erase(startPos);

            // append .png
            texturePath = texturePath.append(".png");

            CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }
        addSpriteFramesWithDictionary(dict, texturePath);
        _loadedFileNames->insert(plist);
    }
}

bool SpriteFrameCache::isSpriteFramesWithFileLoaded(const std::string& plist) const
{
    bool result = false;

    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        result = true;
    }

    return result;
}

void SpriteFrameCache::addSpriteFrame(SpriteFrame* frame, const std::string& frameName)
{
    _spriteFrames.insert(frameName, frame);
}

void SpriteFrameCache::removeSpriteFrames()
{
    _spriteFrames.clear();
    _spriteFramesAliases.clear();
    _loadedFileNames->clear();
}

void SpriteFrameCache::removeUnusedSpriteFrames()
{
    bool removed = false;
    std::vector<std::string> toRemoveFrames;
    
    for (auto iter = _spriteFrames.begin(); iter != _spriteFrames.end(); ++iter)
    {
        SpriteFrame* spriteFrame = iter->second;
        if( spriteFrame->getReferenceCount() == 1 )
        {
            toRemoveFrames.push_back(iter->first);
            spriteFrame->getTexture()->removeSpriteFrameCapInset(spriteFrame);
            CCLOG("cocos2d: SpriteFrameCache: removing unused frame: %s", iter->first.c_str());
            removed = true;
        }
    }

    _spriteFrames.erase(toRemoveFrames);

    // FIXME:. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    if( removed )
    {
        _loadedFileNames->clear();
    }
}


void SpriteFrameCache::removeSpriteFrameByName(const std::string& name)
{
    // explicit nil handling
    if( !(name.size()>0) )
        return;

    // Is this an alias ?
    std::string key = _spriteFramesAliases[name].asString();

    if (!key.empty())
    {
        _spriteFrames.erase(key);
        _spriteFramesAliases.erase(key);
    }
    else
    {
        _spriteFrames.erase(name);
    }

    // FIXME:. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    _loadedFileNames->clear();
}

void SpriteFrameCache::removeSpriteFramesFromFile(const std::string& plist)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFile: create dict by %s fail.",plist.c_str());
        return;
    }
    removeSpriteFramesFromDictionary(dict);

    // remove it from the cache
    set<string>::iterator ret = _loadedFileNames->find(plist);
    if (ret != _loadedFileNames->end())
    {
        _loadedFileNames->erase(ret);
    }
}

void SpriteFrameCache::removeSpriteFramesFromFileContent(const std::string& plist_content)
{
    ValueMap dict = FileUtils::getInstance()->getValueMapFromData(plist_content.data(), static_cast<int>(plist_content.size()));
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFileContent: create dict by fail.");
        return;
    }
    removeSpriteFramesFromDictionary(dict);
}

void SpriteFrameCache::removeSpriteFramesFromDictionary(ValueMap& dictionary)
{
    if (dictionary["frames"].getType() != cocos2d::Value::Type::MAP)
        return;

    ValueMap framesDict = dictionary["frames"].asValueMap();
    std::vector<std::string> keysToRemove;

    for (auto iter = framesDict.cbegin(); iter != framesDict.cend(); ++iter)
    {
        if (_spriteFrames.at(iter->first))
        {
            keysToRemove.push_back(iter->first);
        }
    }

    _spriteFrames.erase(keysToRemove);
}

void SpriteFrameCache::removeSpriteFramesFromTexture(Texture2D* texture)
{
    std::vector<std::string> keysToRemove;

    for (auto iter = _spriteFrames.cbegin(); iter != _spriteFrames.cend(); ++iter)
    {
        std::string key = iter->first;
        SpriteFrame* frame = _spriteFrames.at(key);
        if (frame && (frame->getTexture() == texture))
        {
            keysToRemove.push_back(key);
        }
    }

    _spriteFrames.erase(keysToRemove);
}

SpriteFrame* SpriteFrameCache::getSpriteFrameByName(const std::string& name)
{
    SpriteFrame* frame = _spriteFrames.at(name);
    if (!frame)
    {
        // try alias dictionary
        std::string key = _spriteFramesAliases[name].asString();
        if (!key.empty())
        {
            frame = _spriteFrames.at(key);
            if (!frame)
            {
                CCLOG("cocos2d: SpriteFrameCache: Frame '%s' not found", name.c_str());
            }
        }
    }
    return frame;
}

void SpriteFrameCache::reloadSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture)
{
    ValueMap& framesDict = dictionary["frames"].asValueMap();
    int format = 0;

    // get the format
    if (dictionary.find("metadata") != dictionary.end())
    {
        ValueMap& metadataDict = dictionary["metadata"].asValueMap();
        format = metadataDict["format"].asInt();
    }

    // check the format
    CCASSERT(format >= 0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        ValueMap& frameDict = iter->second.asValueMap();
        std::string spriteFrameName = iter->first;

        auto it = _spriteFrames.find(spriteFrameName);
        if (it != _spriteFrames.end())
        {
            _spriteFrames.erase(it);
        }

        SpriteFrame* spriteFrame = nullptr;

        if (format == 0)
        {
            float x = frameDict["x"].asFloat();
            float y = frameDict["y"].asFloat();
            float w = frameDict["width"].asFloat();
            float h = frameDict["height"].asFloat();
            float ox = frameDict["offsetX"].asFloat();
            float oy = frameDict["offsetY"].asFloat();
            int ow = frameDict["originalWidth"].asInt();
            int oh = frameDict["originalHeight"].asInt();
            // check ow/oh
            if (!ow || !oh)
            {
                CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenerate the .plist");
            }
            // abs ow/oh
            ow = std::abs(ow);
            oh = std::abs(oh);
            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                Rect(x, y, w, h),
                false,
                Vec2(ox, oy),
                Size((float)ow, (float)oh)
                );
        }
        else if (format == 1 || format == 2)
        {
            Rect frame = RectFromString(frameDict["frame"].asString());
            bool rotated = false;

            // rotation
            if (format == 2)
            {
                rotated = frameDict["rotated"].asBool();
            }

            Vec2 offset = PointFromString(frameDict["offset"].asString());
            Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());

            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                frame,
                rotated,
                offset,
                sourceSize
                );
        }
        else if (format == 3)
        {
            // get values
            Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
            Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
            Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
            Rect textureRect = RectFromString(frameDict["textureRect"].asString());
            bool textureRotated = frameDict["textureRotated"].asBool();

            // get aliases
            ValueVector& aliases = frameDict["aliases"].asValueVector();

            for (const auto &value : aliases) {
                std::string oneAlias = value.asString();
                if (_spriteFramesAliases.find(oneAlias) != _spriteFramesAliases.end())
                {
                    CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
                }

                _spriteFramesAliases[oneAlias] = Value(spriteFrameName);
            }

            // create frame
            spriteFrame = SpriteFrame::createWithTexture(texture,
                Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
                textureRotated,
                spriteOffset,
                spriteSourceSize);
        }

        // add sprite frame
        _spriteFrames.insert(spriteFrameName, spriteFrame);
    }
}

bool SpriteFrameCache::reloadTexture(const std::string& plist)
{
    CCASSERT(plist.size()>0, "plist filename should not be nullptr");

    auto it = _loadedFileNames->find(plist);
    if (it != _loadedFileNames->end()) {
        _loadedFileNames->erase(it);
    }
    else
    {
        //If one plist has't be loaded, we don't load it here.
        return false;
    }

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

    string texturePath("");

    if (dict.find("metadata") != dict.end())
    {
        ValueMap& metadataDict = dict["metadata"].asValueMap();
        // try to read  texture file name from meta data
        texturePath = metadataDict["textureFileName"].asString();
    }

    if (!texturePath.empty())
    {
        // build texture path relative to plist file
        texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath, plist);
    }
    else
    {
        // build texture path by replacing file extension
        texturePath = plist;

        // remove .xxx
        size_t startPos = texturePath.find_last_of(".");
        texturePath = texturePath.erase(startPos);

        // append .png
        texturePath = texturePath.append(".png");
    }

    Texture2D *texture = nullptr;
    if (Director::getInstance()->getTextureCache()->reloadTexture(texturePath))
        texture = Director::getInstance()->getTextureCache()->getTextureForKey(texturePath);

    if (texture)
    {
        reloadSpriteFramesWithDictionary(dict, texture);
        _loadedFileNames->insert(plist);
    }
    else
    {
        CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
    }
    return true;
}

NS_CC_END
