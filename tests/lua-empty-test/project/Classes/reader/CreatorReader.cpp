/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

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

#include "CreatorReader.h"
#include "animation/AnimationClip.h"
#include "animation/AnimateClip.h"
#include "ui/RichtextStringVisitor.h"
#include "ui/PageView.h"
#include "collider/Collider.h"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace cocos2d;
using namespace creator;
using namespace creator::buffers;

USING_NS_CCR;

static void setSpriteQuad(V3F_C4B_T2F_Quad* quad, const cocos2d::Size& origSize, const int x, const int y, float x_factor, float y_factor);
static void tileSprite(cocos2d::Sprite* sprite);

namespace {
    template <typename T, typename U>
    void setupAnimClipsPropValue(T fbPropList, U& proplist)
    {
        if (fbPropList) {
            for(const auto fbProp: *fbPropList) {
                const auto fbFrame = fbProp->frame();
                const auto fbValue = fbProp->value();
                
                const auto fbCurveType = fbProp->curveType();
                std::string curveType = fbCurveType ? fbCurveType->c_str() : "";
                
                const auto fbCurveData = fbProp->curveData();
                std::vector<float> curveData;
                if (fbCurveData)
                    for (const auto& value : *fbCurveData)
                        curveData.push_back(value);
                    
                proplist.push_back({fbFrame,
                                    fbValue,
                                    curveData,
                                    curveType
                                   });
            }
        }
    }
    
    template <typename T, typename U>
    void setupAnimClipsPropVec2(T fbPropList, U& proplist)
    {
        if (fbPropList) {
            for(const auto fbProp: *fbPropList) {
                const auto fbFrame = fbProp->frame();
                const auto fbValue = fbProp->value();
                
                const auto fbCurveType = fbProp->curveType();
                std::string curveType = fbCurveType ? fbCurveType->c_str() : "";
                
                const auto fbCurveData = fbProp->curveData();
                std::vector<float> curveData;
                if (fbCurveData)
                    for (const auto& value : *fbCurveData)
                        curveData.push_back(value);
                
                proplist.push_back({fbFrame,
                                    cocos2d::Vec2(fbValue->x(), fbValue->y()),
                                    curveData,
                                    curveType
                                   });
            }
        }
    }
    
    template <typename T, typename U>
    void setupAnimClipsPropColor(T fbPropList, U& proplist)
    {
        if (fbPropList) {
            for(const auto fbProp: *fbPropList) {
                const auto fbFrame = fbProp->frame();
                const auto fbValue = fbProp->value();
                
                const auto fbCurveType = fbProp->curveType();
                std::string curveType = fbCurveType ? fbCurveType->c_str() : "";
                
                const auto fbCurveData = fbProp->curveData();
                std::vector<float> curveData;
                if (fbCurveData)
                    for (const auto& value : *fbCurveData)
                        curveData.push_back(value);
                
                proplist.push_back({fbFrame,
                                    cocos2d::Color3B(fbValue->r(), fbValue->g(), fbValue->b()),
                                    curveData,
                                    curveType
                                   });
            }
        }
    }
}

//
// CreatorReader main class
//
CreatorReader::CreatorReader()
: _version("")
, _positionDiffDesignResolution(0, 0)
{
    _animationManager = new AnimationManager();
    _collisionManager = new ColliderManager();
}

CreatorReader::~CreatorReader()
{
    CC_SAFE_RELEASE_NULL(_collisionManager);
    CC_SAFE_RELEASE_NULL(_animationManager);
}

CreatorReader* CreatorReader::createWithFilename(const std::string& filename)
{
    CreatorReader* reader = new(std::nothrow) CreatorReader;
    if (reader && reader->initWithFilename(filename)) {
        reader->autorelease();
        return reader;
    }
    return nullptr;
}

bool CreatorReader::initWithFilename(const std::string& filename)
{
    FileUtils* fileUtils = FileUtils::getInstance();

    const std::string& fullpath = fileUtils->fullPathForFilename(filename);
    if (fullpath.size() == 0)
    {
        CCLOG("CreatorReader: file not found: %s", filename.c_str());
        return false;
    }

    _data = fileUtils->getDataFromFile(fullpath);

    const void* buffer = _data.getBytes();
    auto sceneGraph = GetSceneGraph(buffer);
    _version = sceneGraph->version()->str();
    return true;
}

void CreatorReader::setup()
{
    const void* buffer = _data.getBytes();
    auto sceneGraph = GetSceneGraph(buffer);
    
    const auto& designResolution = sceneGraph->designResolution();
    const auto& fitWidth = sceneGraph->resolutionFitWidth();
    const auto& fitHeight = sceneGraph->resolutionFitHeight();
    
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if (fitWidth && fitHeight)
        glview->setDesignResolutionSize(designResolution->w(), designResolution->h(), ResolutionPolicy::SHOW_ALL);
    else if (fitHeight)
        glview->setDesignResolutionSize(designResolution->w(), designResolution->h(), ResolutionPolicy::FIXED_HEIGHT);
    else if (fitWidth)
        glview->setDesignResolutionSize(designResolution->w(), designResolution->h(), ResolutionPolicy::FIXED_WIDTH);
    else
        if (designResolution)
            glview->setDesignResolutionSize(designResolution->w(), designResolution->h(), ResolutionPolicy::NO_BORDER);

    setupSpriteFrames();
    setupCollisionMatrix();
    
    if (designResolution)
    {
        const auto& realDesignResolution = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        _positionDiffDesignResolution = cocos2d::Vec2((realDesignResolution.width - designResolution->w())/2,
                                                      (realDesignResolution.height - designResolution->h())/2);
    }
}

void CreatorReader::setupSpriteFrames()
{
    const void* buffer = _data.getBytes();
    const auto& sceneGraph = GetSceneGraph(buffer);
    const auto& spriteFrames = sceneGraph->spriteFrames();
    auto frameCache = cocos2d::SpriteFrameCache::getInstance();

    if (spriteFrames) {
        for (const auto& spriteFrame: *spriteFrames) {
            const auto& name = spriteFrame->name()->str();
            const auto& filename = spriteFrame->texturePath()->str();
            const auto& rect = spriteFrame->rect();
            const auto& rotated = spriteFrame->rotated();
            const auto& offset = spriteFrame->offset();
            const auto& originalSize = spriteFrame->originalSize();

            auto sf = cocos2d::SpriteFrame::create(filename,
                                                   cocos2d::Rect(rect->x(), rect->y(), rect->w(), rect->h()),
                                                   rotated,
                                                   cocos2d::Vec2(offset->x(), offset->y()),
                                                   cocos2d::Size(originalSize->w(), originalSize->h())
                                                   );

            const auto& centerRect = spriteFrame->centerRect();
            if (sf && centerRect) {
                sf->setCenterRectInPixels(cocos2d::Rect(centerRect->x(), centerRect->y(), centerRect->w(), centerRect->h()));
            }

            if (sf) {
                frameCache->addSpriteFrame(sf, name);
                CCLOG("Adding sprite frame: %s", name.c_str());
            }
        }
    }
}

void CreatorReader::setupCollisionMatrix()
{
    const void* buffer = _data.getBytes();
    const auto& sceneGraph = GetSceneGraph(buffer);
    const auto& collisionMatrixBuffer = sceneGraph->collisionMatrix();
    
    std::vector<std::vector<bool>> collisionMatrix;
    for (const auto& matrixLineBuffer : *collisionMatrixBuffer)
    {
        std::vector<bool> line;
        for (const auto& value : *(matrixLineBuffer->value()))
            line.push_back(value);
        
        collisionMatrix.push_back(line);
    }
    
    _collisionManager->setCollistionMatrix(collisionMatrix);
}

cocos2d::Scene* CreatorReader::getSceneGraph() const
{
    const void* buffer = _data.getBytes();

    auto sceneGraph = GetSceneGraph(buffer);
    auto nodeTree = sceneGraph->root();
    CCLOG("NodeTree: %p", nodeTree);

    cocos2d::Node* node = createTree(nodeTree);

    // make scene at the center of screen
    // should not just node's position because it is a Scene, and it will cause issue that click position is not correct(it is a bug of cocos2d-x)
    // and should not change camera's position
    for (auto& child : node->getChildren())
        if (dynamic_cast<Camera*>(child) == nullptr)
            child->setPosition(child->getPosition() + _positionDiffDesignResolution);
    
    _animationManager->playOnLoad();
    
    node->addChild(_collisionManager);
    node->addChild(_animationManager);
    _collisionManager->start();

    return static_cast<cocos2d::Scene*>(node);
}

AnimationManager* CreatorReader::getAnimationManager() const
{
    return _animationManager;
}

ColliderManager* CreatorReader::getColliderManager() const
{
    return _collisionManager;
}

std::string CreatorReader::getVersion() const
{
    return _version;
}

cocos2d::Node* CreatorReader::createTree(const buffers::NodeTree* tree) const
{
    cocos2d::Node *node = nullptr;

    const void* buffer = tree->object();
    buffers::AnyNode bufferType = tree->object_type();
    bool parsing_button = false;
    
    switch (static_cast<int>(bufferType))
    {
        case buffers::AnyNode_NONE:
            break;
        case buffers::AnyNode_Node:
            node = createNode(static_cast<const buffers::Node*>(buffer));
            break;
        case buffers::AnyNode_Label:
            node = createLabel(static_cast<const buffers::Label*>(buffer));
            break;
        case buffers::AnyNode_RichText:
            node = createRichText(static_cast<const buffers::RichText*>(buffer));
            break;
        case buffers::AnyNode_Sprite:
            node = createSprite(static_cast<const buffers::Sprite*>(buffer));
            break;
        case buffers::AnyNode_TileMap:
            node = createTileMap(static_cast<const buffers::TileMap*>(buffer));
            break;
        case buffers::AnyNode_Particle:
            node = createParticle(static_cast<const buffers::Particle*>(buffer));
            break;
        case buffers::AnyNode_Scene:
            node = createScene(static_cast<const buffers::Scene*>(buffer));
            break;
        case buffers::AnyNode_ScrollView:
            node = createScrollView(static_cast<const buffers::ScrollView*>(buffer));
            break;
        case buffers::AnyNode_ProgressBar:
            node = createProgressBar(static_cast<const buffers::ProgressBar*>(buffer));
            break;
        case buffers::AnyNode_Button:
            node = createButton(static_cast<const buffers::Button*>(buffer));
            parsing_button = true;
            break;
        case buffers::AnyNode_EditBox:
            node = createEditBox(static_cast<const buffers::EditBox*>(buffer));
            break;
        case buffers::AnyNode_CreatorScene:
            break;
        case buffers::AnyNode_SpineSkeleton:
            node = createSpineSkeleton(static_cast<const buffers::SpineSkeleton*>(buffer));
            break;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        case buffers::AnyNode_VideoPlayer:
            node = createVideoPlayer(static_cast<const buffers::VideoPlayer*>(buffer));
            break;
        case buffers::AnyNode_WebView:
            node = createWebView(static_cast<const buffers::WebView*>(buffer));
            break;
#endif
        case buffers::AnyNode_Slider:
            node = createSlider(static_cast<const buffers::Slider*>(buffer));
            break;
        case buffers::AnyNode_Toggle:
            node = createToggle(static_cast<const buffers::Toggle*>(buffer));
            break;
        case buffers::AnyNode_ToggleGroup:
            node = createToggleGroup(static_cast<const buffers::ToggleGroup*>(buffer));
            break;
        case buffers::AnyNode_PageView:
            node = createPageView(static_cast<const buffers::PageView*>(buffer));
            break;
        case buffers::AnyNode_Mask:
            node = createMask(static_cast<const buffers::Mask*>(buffer));
            break;
        case buffers::AnyNode_DragonBones:
            node = createArmatureDisplay(static_cast<const buffers::DragonBones*>(buffer));
            break;
        case buffers::AnyNode_MotionStreak:
            node = createMotionStreak(static_cast<const buffers::MotionStreak*>(buffer));
            break;
    }

    // recursively add its children
    const auto& children = tree->children();
    for(const auto& childBuffer: *children)
    {
        cocos2d::Node* child = createTree(childBuffer);
        if (child && node)
        {
            // should adjust child's position except Button's label
            if (parsing_button && dynamic_cast<cocos2d::Label*>(child) != nullptr)
            {
                auto button = static_cast<cocos2d::ui::Button*>(node);
                auto label = static_cast<cocos2d::Label*>(child);
                button->setTitleLabel(label);
            }
            else
            {
                node->addChild(child);
                adjustPosition(child);
            }
        }
    }

    return node;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 *
 * Render Nodes
 *
 *=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
cocos2d::Scene* CreatorReader::createScene(const buffers::Scene* sceneBuffer) const
{
    cocos2d::Scene* scene = cocos2d::Scene::create();
    return scene;
}

void CreatorReader::parseScene(cocos2d::Scene* scene, const buffers::Scene* sceneBuffer) const
{

}

cocos2d::Node* CreatorReader::createNode(const buffers::Node* nodeBuffer) const
{
    cocos2d::Node* node = cocos2d::Node::create();
    if (node)
        parseNode(node, nodeBuffer);
    return node;
}

void CreatorReader::parseNode(cocos2d::Node* node, const buffers::Node* nodeBuffer) const
{
    const auto& globalZOrder = nodeBuffer->globalZOrder();
    node->setGlobalZOrder(globalZOrder);
    const auto& localZOrder = nodeBuffer->localZOrder();
    node->setLocalZOrder(localZOrder);
    const auto& name = nodeBuffer->name();
    if (name) node->setName(name->str());
    const auto& anchorPoint = nodeBuffer->anchorPoint();
    if (anchorPoint) node->setAnchorPoint(cocos2d::Vec2(anchorPoint->x(), anchorPoint->y()));
    const auto& color = nodeBuffer->color();
    if (color) node->setColor(cocos2d::Color3B(color->r(), color->g(), color->b()));
    const auto& opacity = nodeBuffer->opacity();
    node->setOpacity(opacity);
    const auto& cascadeOpacityEnabled = nodeBuffer->cascadeOpacityEnabled();
    node->setCascadeOpacityEnabled(cascadeOpacityEnabled);
    const auto& opacityModifyRGB = nodeBuffer->opacityModifyRGB();
    node->setOpacityModifyRGB(opacityModifyRGB);
    const auto position = nodeBuffer->position();
    if (position) node->setPosition(cocos2d::Vec2(position->x(), position->y()));
    node->setRotationSkewX(nodeBuffer->rotationSkewX());
    node->setRotationSkewY(nodeBuffer->rotationSkewY());
    node->setScaleX(nodeBuffer->scaleX());
    node->setScaleY(nodeBuffer->scaleY());
    node->setSkewX(nodeBuffer->skewX());
    node->setSkewY(nodeBuffer->skewY());
    const auto& tag = nodeBuffer->tag();
    node->setTag(tag);
    const auto contentSize = nodeBuffer->contentSize();
    if (contentSize) node->setContentSize(cocos2d::Size(contentSize->w(), contentSize->h()));
    const auto enabled = nodeBuffer->enabled();
    node->setVisible(enabled);

    // animation?
    parseNodeAnimation(node, nodeBuffer);
    
    parseColliders(node, nodeBuffer);
}

void CreatorReader::parseNodeAnimation(cocos2d::Node* node, const buffers::Node* nodeBuffer) const
{
    const AnimationRef *animRef = nodeBuffer->anim();
    
    if (animRef) {
        AnimationInfo animationInfo;
        animationInfo.playOnLoad = animRef->playOnLoad();
        animationInfo.target = node;
        node->retain();
        bool hasDefaultAnimclip = animRef->defaultClip() != nullptr;
        
        const auto& animationClips = animRef->clips();
        
        for (const auto& fbAnimationClip: *animationClips) {
            auto animClip = AnimationClip::create();
            
            const auto& duration = fbAnimationClip->duration();
            animClip->setDuration(duration);
            
            const auto& speed = fbAnimationClip->speed();
            animClip->setSpeed(speed);
            
            const auto& sample = fbAnimationClip->sample();
            animClip->setSample(sample);
            
            const auto& name = fbAnimationClip->name();
            animClip->setName(name->str());
            
            const auto& wrapMode = fbAnimationClip->wrapMode();
            animClip->setWrapMode(static_cast<AnimationClip::WrapMode>(wrapMode));
            
            // is it defalut animation clip?
            if (hasDefaultAnimclip && name->str() == animRef->defaultClip()->str())
                animationInfo.defaultClip = animClip;
            
            const auto& curveDatas = fbAnimationClip->curveData();
            for (const auto& fbCurveData: *curveDatas) {
                
                if (fbCurveData) {
                    const AnimProps* fbAnimProps = fbCurveData->props();
                    AnimProperties properties;
                    
                    // position
                    setupAnimClipsPropVec2(fbAnimProps->position(), properties.animPosition);
                    
                    // position X
                    setupAnimClipsPropValue(fbAnimProps->positionX(), properties.animPositionX);
                    
                    // position Y
                    setupAnimClipsPropValue(fbAnimProps->positionY(), properties.animPositionY);
                    
                    // rotation
                    setupAnimClipsPropValue(fbAnimProps->rotation(), properties.animRotation);
                    
                    // skew X
                    setupAnimClipsPropValue(fbAnimProps->skewX(), properties.animSkewX);
                    
                    // skew Y
                    setupAnimClipsPropValue(fbAnimProps->skewY(), properties.animSkewY);
                    
                    // scaleX
                    setupAnimClipsPropValue(fbAnimProps->scaleX(), properties.animScaleX);
                    
                    // scaleY
                    setupAnimClipsPropValue(fbAnimProps->scaleY(), properties.animScaleY);
                    
                    // Color
                    setupAnimClipsPropColor(fbAnimProps->color(), properties.animColor);
                    
                    // opacity
                    setupAnimClipsPropValue(fbAnimProps->opacity(), properties.animOpacity);
                    
                    // anchor x
                    setupAnimClipsPropValue(fbAnimProps->anchorX(), properties.animAnchorX);
                    
                    // anchor y
                    setupAnimClipsPropValue(fbAnimProps->anchorY(), properties.animAnchorY);
                    
                    // path: self's animation doesn't have path
                    // path is used for sub node
                    if (fbCurveData->path())
                        properties.path = fbCurveData->path()->str();
                    
                    animClip->addAnimProperties(properties);
                }
            }
            
            animationInfo.clips.pushBack(animClip);
        }
        
        // record animation information -> {node: AnimationInfo}
        _animationManager->addAnimation(std::move(animationInfo));
    }
}

void CreatorReader::parseColliders(cocos2d::Node* node, const buffers::Node* nodeBuffer) const
{
    const auto& collidersBuffer = nodeBuffer->colliders();
    const auto& groupIndex = nodeBuffer->groupIndex();
    
    Collider *collider = nullptr;
    for (const auto& colliderBuffer : *collidersBuffer)
    {
        const auto& type = colliderBuffer->type();
        const auto& offsetBuffer = colliderBuffer->offset();
        cocos2d::Vec2 offset(offsetBuffer->x(), offsetBuffer->y());
        
        if (type == buffers::ColliderType::ColliderType_CircleCollider)
            collider = new CircleCollider(node, groupIndex, offset, colliderBuffer->radius());
        else if (type == buffers::ColliderType::ColliderType_BoxCollider)
        {
            const auto& sizeBuffer = colliderBuffer->size();
            cocos2d::Size size(sizeBuffer->w(), sizeBuffer->h());
            collider = new BoxCollider(node, groupIndex, offset, size);
        }
        else if (type == buffers::ColliderType::ColliderType_PolygonCollider)
        {
            const auto& pointsBuffer = colliderBuffer->points();
            std::vector<cocos2d::Vec2> points;
            for (const auto& pointBuffer : *pointsBuffer)
                points.push_back(cocos2d::Vec2(pointBuffer->x(), pointBuffer->y()));
            
            collider = new PolygonCollider(node, groupIndex, offset, points);
        }
        else
            assert(false);
    }
    
    if (collider)
        _collisionManager->addCollider(collider);
}

cocos2d::Sprite* CreatorReader::createSprite(const buffers::Sprite* spriteBuffer) const
{
    cocos2d::Sprite* sprite = cocos2d::Sprite::create();
    if (sprite)
        parseSprite(sprite, spriteBuffer);
    return sprite;
}

void CreatorReader::parseSprite(cocos2d::Sprite* sprite, const buffers::Sprite* spriteBuffer) const
{
    // order is important:
    // 1st: set sprite frame
    const auto& frameName = spriteBuffer->spriteFrameName();
    if (frameName)
        sprite->setSpriteFrame(frameName->str());

    
    // 2nd: node properties
    const auto& nodeBuffer = spriteBuffer->node();
    parseNode(sprite, nodeBuffer);


    // 3rd: sprite type
    const auto& spriteType = spriteBuffer->spriteType();
    switch (spriteType) {
        case buffers::SpriteType_Simple:
            sprite->setCenterRectNormalized(cocos2d::Rect(0,0,1,1));
            break;
        case buffers::SpriteType_Tiled:
            tileSprite(sprite);
            break;
        case buffers::SpriteType_Filled:
        case buffers::SpriteType_Sliced:
            break;
    }

    const auto& srcBlend = spriteBuffer->srcBlend();
    const auto& dstBlend = spriteBuffer->dstBlend();
    cocos2d::BlendFunc blendFunc;
    blendFunc.src = srcBlend;
    blendFunc.dst = dstBlend;
    sprite->setBlendFunc(blendFunc);

#if 0
    // FIXME: do something with these values
    const auto& isTrimmed = spriteBuffer->trimEnabled();
    const auto& sizeMode = spriteBuffer->sizeMode();
#endif
}

cocos2d::TMXTiledMap* CreatorReader::createTileMap(const buffers::TileMap* tilemapBuffer) const
{
    const auto& tmxfilename = tilemapBuffer->tmxFilename();
    cocos2d::TMXTiledMap* tilemap = TMXTiledMap::create(tmxfilename->str());
    if (tilemap)
        parseTilemap(tilemap, tilemapBuffer);
    return tilemap;
}

void CreatorReader::parseTilemap(cocos2d::TMXTiledMap* tilemap, const buffers::TileMap* tilemapBuffer) const
{
    const auto& nodeBuffer = tilemapBuffer->node();
    parseNode(tilemap, nodeBuffer);

    // calculate scale. changing the contentSize in TMX doesn't affect its visual size
    // so we have to re-scale the map
    const auto& desiredSize = tilemapBuffer->desiredContentSize();
    const auto& currentSize = tilemap->getContentSize();

    float wr = desiredSize->w() / currentSize.width;
    float hr = desiredSize->h() / currentSize.height;

    float sx = tilemap->getScaleX();
    float sy = tilemap->getScaleY();

    tilemap->setScaleX(wr * sx);
    tilemap->setScaleY(hr * sy);
}

cocos2d::Label* CreatorReader::createLabel(const buffers::Label* labelBuffer) const
{
    cocos2d::Label* label = nullptr;
    auto text = labelBuffer->labelText();
    auto fontSize = labelBuffer->fontSize();
    auto fontName = labelBuffer->fontName();

    auto fontType = labelBuffer->fontType();
    switch (fontType) {
        case buffers::FontType_TTF:
            label = cocos2d::Label::createWithTTF(text->str(), fontName->str(), fontSize);
            break;
        case buffers::FontType_BMFont:
            label = cocos2d::Label::createWithBMFont(fontName->str(), text->str());
            if (label)
                label->setBMFontSize(fontSize);
            break;
        case buffers::FontType_System:
            label = cocos2d::Label::createWithSystemFont(text->str(), fontName->str(), fontSize);
            break;
    }

    if (label)
        parseLabel(label, labelBuffer);
    return label;
}

void CreatorReader::parseLabel(cocos2d::Label* label, const buffers::Label* labelBuffer) const
{
    const auto& nodeBuffer = labelBuffer->node();
    parseNode(label, nodeBuffer);

    const auto& lineHeight = labelBuffer->lineHeight();
    const auto& verticalA = labelBuffer->verticalAlignment();
    const auto& horizontalA = labelBuffer->horizontalAlignment();
    const auto& overflowType = labelBuffer->overflowType();
    const auto& enableWrap = labelBuffer->enableWrap();

    if (labelBuffer->fontType() != FontType_System)
        label->setLineHeight(lineHeight);
    label->setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(verticalA));
    label->setHorizontalAlignment(static_cast<cocos2d::TextHAlignment>(horizontalA));
    label->setOverflow(static_cast<cocos2d::Label::Overflow>(overflowType));
    label->enableWrap(enableWrap);

    const auto& outline = labelBuffer->outline();
    if (outline)
    {
        const auto& color = outline->color();
        label->enableOutline(cocos2d::Color4B(color->r(), color->g(), color->b(), color->a()),
                             outline->width());
    }
}

cocos2d::ui::RichText* CreatorReader::createRichText(const buffers::RichText* richTextBuffer) const
{
    cocos2d::ui::RichText* richText = cocos2d::ui::RichText::create();
    parseRichText(richText, richTextBuffer);
    return richText;
}

void CreatorReader::parseRichText(cocos2d::ui::RichText* richText, const buffers::RichText* richTextBuffer) const
{
    const auto& nodeBuffer = richTextBuffer->node();
    parseNode(richText, nodeBuffer);

    const auto& fontSize = richTextBuffer->fontSize();
    richText->setFontSize(fontSize);
    const auto& fontFilename = richTextBuffer->fontFilename();
    richText->setFontFace(fontFilename->str());
    
    const auto& text = richTextBuffer->text();
    if (text)
    {
        RichtextStringVisitor visitor;;
        SAXParser parser;
        parser.setDelegator(&visitor);
        parser.parseIntrusive(const_cast<char*>(text->c_str()), text->Length());
        
        richText->initWithXML(visitor.getOutput());
        
        // FIXME: content width from Creator is not correct
        // so should recompute it here
        
        const auto& rawString = visitor.getRawString();
        auto maxFontSize = visitor.getMaxFontSize();
        int finalFontSize = std::max(static_cast<float>(maxFontSize), fontSize);
        auto label = cocos2d::Label::createWithSystemFont(rawString, fontFilename->str(), finalFontSize);
        
        auto realContentSize = label->getContentSize();
        auto finalWidth = std::max(realContentSize.width, richText->getContentSize().width);
        richText->setContentSize(cocos2d::Size(finalWidth, richText->getContentSize().height));
    }
        
    // should do it after richText->initWithXML
    richText->ignoreContentAdaptWithSize(false);
    
    const auto& maxWidth = richTextBuffer->maxWidth();
    if (maxWidth > 0)
    {
        const auto& contentSize = richText->getContentSize();
        richText->setContentSize(cocos2d::Size(maxWidth, contentSize.height));
    }
}

cocos2d::ParticleSystemQuad* CreatorReader::createParticle(const buffers::Particle* particleBuffer) const
{
    const auto& particleFilename = particleBuffer->particleFilename();
    cocos2d::ParticleSystemQuad* particle = cocos2d::ParticleSystemQuad::create(particleFilename->str());
    if (particle)
        parseParticle(particle, particleBuffer);
    return particle;
}

void CreatorReader::parseParticle(cocos2d::ParticleSystemQuad* particle, const buffers::Particle* particleBuffer) const
{
    const auto& nodeBuffer = particleBuffer->node();
    parseNode(particle, nodeBuffer);
    
    const auto& texturePath = particleBuffer->texturePath();
    if (texturePath)
    {
        auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(texturePath->c_str());
        particle->setTexture(texture);
    }
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 *
 * UI Nodes
 *
 *=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
cocos2d::ui::ScrollView* CreatorReader::createScrollView(const buffers::ScrollView* scrollViewBuffer) const
{
    auto scrollView = ui::ScrollView::create();
    parseScrollView(scrollView, scrollViewBuffer);
    return scrollView;
}

void CreatorReader::parseScrollView(cocos2d::ui::ScrollView* scrollView, const buffers::ScrollView* scrollViewBuffer) const
{
    const auto& nodeBuffer = scrollViewBuffer->node();
    parseNode(scrollView, nodeBuffer);

    // backgroundImage:string;
    // backgroundImageScale9Enabled:bool;
    // backgroundImageColor:ColorRGB;
    // direction:ScrollViewDirection;
    // bounceEnabled:bool;
    // innerContainerSize:Size;

    const auto& backgroundImage = scrollViewBuffer->backgroundImage();
    const auto& backgroundImageScale9Enabled = scrollViewBuffer->backgroundImageScale9Enabled();
    const auto& backgroundImageColor = scrollViewBuffer->backgroundImageColor();
    const auto& direction = scrollViewBuffer->direction();
    const auto& bounceEnabled = scrollViewBuffer->bounceEnabled();
    const auto& innerContainerSize = scrollViewBuffer->innerContainerSize();
    
    if (backgroundImage)
    {
        scrollView->setBackGroundImage(backgroundImage->str(), cocos2d::ui::Widget::TextureResType::PLIST);
        scrollView->setBackGroundImageScale9Enabled(backgroundImageScale9Enabled);
        scrollView->setBackGroundImageColor(cocos2d::Color3B(backgroundImageColor->r(), backgroundImageColor->g(), backgroundImageColor->b()));
    }

    scrollView->setDirection(static_cast<cocos2d::ui::ScrollView::Direction>(direction));
    scrollView->setBounceEnabled(bounceEnabled);
    scrollView->setInnerContainerSize(cocos2d::Size(innerContainerSize->w(), innerContainerSize->h()));

    // FIXME: Call setJumpToPercent at the end, because it depens on having the contentSize correct
    // FIXME: uses the anchorPoint for the percent in the bar, but this migh break if it changes the position of the bar content node
    const auto& anchorPoint = scrollViewBuffer->node()->anchorPoint();
    scrollView->jumpToPercentHorizontal(anchorPoint->x() * 100.0f);
    scrollView->jumpToPercentVertical((1-anchorPoint->y() * 100.0f));
}

cocos2d::ui::LoadingBar* CreatorReader::createProgressBar(const buffers::ProgressBar* progressBarBuffer) const
{
    ui::LoadingBar* progressBar = ui::LoadingBar::create();

    parseProgressBar(progressBar, progressBarBuffer);
    return progressBar;
}
void CreatorReader::parseProgressBar(cocos2d::ui::LoadingBar* progressBar, const buffers::ProgressBar* progressBarBuffer) const
{
    const auto& nodeBuffer = progressBarBuffer->node();
    parseNode(progressBar, nodeBuffer);
    
    progressBar->ignoreContentAdaptWithSize(false);
    
    if (progressBarBuffer->barSpriteFrameName())
        progressBar->loadTexture(progressBarBuffer->barSpriteFrameName()->c_str());
    
    progressBar->setPercent(progressBarBuffer->percent());
    
    // TODO: other types support?
    if (progressBarBuffer->barSpriteType() == buffers::SpriteType_Sliced)
        progressBar->setScale9Enabled(true);
    
    // background sprite
    if (progressBarBuffer->backgroundSpriteFrameName()) {
        auto sprite = cocos2d::Sprite::create(progressBarBuffer->backgroundSpriteFrameName()->c_str());
        sprite->setStretchEnabled(true);
        sprite->setContentSize(progressBar->getContentSize());
        sprite->setAnchorPoint(cocos2d::Vec2(0,0));
        // background sprite should show first
        progressBar->addChild(sprite, -1);
    }
    
    if (progressBarBuffer->reverse())
        progressBar->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
}

cocos2d::ui::EditBox* CreatorReader::createEditBox(const buffers::EditBox* editBoxBuffer) const
{
    const auto& contentSize = editBoxBuffer->node()->contentSize();
    const auto& spriteFrameName = editBoxBuffer->backgroundImage();
    
    auto editBox = ui::EditBox::create(cocos2d::Size(contentSize->w(), contentSize->h()),
                                                         spriteFrameName->str(),
                                                         cocos2d::ui::Widget::TextureResType::PLIST);
    parseEditBox(editBox, editBoxBuffer);
    return editBox;
}

void CreatorReader::parseEditBox(cocos2d::ui::EditBox* editBox, const buffers::EditBox* editBoxBuffer) const
{
    const auto& nodeBuffer = editBoxBuffer->node();
    parseNode(editBox, nodeBuffer);

    // backgroundImage:string;
    // returnType:EditBoxReturnType;
    // inputFlag:EditBoxInputFlag;
    // inputMode:EditBoxInputMode;
    // fontSize:int;
    // fontColor:ColorRGB;
    // placeholder:string;
    // placeholderFontSize:int;
    // placeholderFontColor:ColorRGB;
    // maxLength:int;
    // text:string;
    const auto& returnType = editBoxBuffer->returnType();
    const auto& inputFlag = editBoxBuffer->inputFlag();
    const auto& inputMode = editBoxBuffer->inputMode();
    const auto& fontSize = editBoxBuffer->fontSize();
    const auto& fontColor = editBoxBuffer->fontColor();
    const auto& placerholder = editBoxBuffer->placeholder();
    const auto& placerholderFontSize = editBoxBuffer->placeholderFontSize();
    const auto& placerholderFontColor = editBoxBuffer->placeholderFontColor();
    const auto& maxLen = editBoxBuffer->maxLength();
    const auto& text = editBoxBuffer->text();

    editBox->setReturnType(static_cast<cocos2d::ui::EditBox::KeyboardReturnType>(returnType));
    editBox->setInputFlag(static_cast<cocos2d::ui::EditBox::InputFlag>(inputFlag));
    editBox->setInputMode(static_cast<cocos2d::ui::EditBox::InputMode>(inputMode));
    editBox->setFontSize(fontSize);
    editBox->setFontColor(cocos2d::Color3B(fontColor->r(), fontColor->g(), fontColor->b()));
    editBox->setPlaceHolder(placerholder->c_str());
    editBox->setPlaceholderFontSize(placerholderFontSize);
    editBox->setPlaceholderFontColor(cocos2d::Color3B(placerholderFontColor->r(), placerholderFontColor->g(), placerholderFontColor->b()));
    editBox->setMaxLength(maxLen);
    editBox->setText(text->c_str());
}

cocos2d::ui::Button* CreatorReader::createButton(const buffers::Button* buttonBuffer) const
{
    
    ui::Button* button = nullptr;
    
    const auto& spriteFrameName = buttonBuffer->spriteFrameName();
    const auto& pressedSpriteFrameName = buttonBuffer->pressedSpriteFrameName();
    const auto& disabledSpriteFrameName = buttonBuffer->disabledSpriteFrameName();
    if (spriteFrameName)
        button = ui::Button::create(spriteFrameName->str(),
                                    pressedSpriteFrameName ? pressedSpriteFrameName->str() : "",
                                    disabledSpriteFrameName ? disabledSpriteFrameName->str() : "",
                                    cocos2d::ui::Widget::TextureResType::PLIST);
    else
        button = ui::Button::create();

    parseButton(button, buttonBuffer);
    return button;
}

void CreatorReader::parseButton(cocos2d::ui::Button* button, const buffers::Button* buttonBuffer) const
{
    const auto& nodeBuffer = buttonBuffer->node();
    parseNode(button, nodeBuffer);

    const auto& ignoreContentAdaptWithSize = buttonBuffer->ignoreContentAdaptWithSize();
    button->ignoreContentAdaptWithSize(ignoreContentAdaptWithSize);
    
    if (buttonBuffer->transition() == 3)
    {
        button->setZoomScale(buttonBuffer->zoomScale() - 1);
        button->setPressedActionEnabled(true);
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
cocos2d::experimental::ui::VideoPlayer* CreatorReader::createVideoPlayer(const buffers::VideoPlayer* videoPlayerBuffer) const
{
    auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    parseVideoPlayer(videoPlayer, videoPlayerBuffer);
    return videoPlayer;
}

void CreatorReader::parseVideoPlayer(cocos2d::experimental::ui::VideoPlayer* videoPlayer, const buffers::VideoPlayer* videoPlayerBuffer) const
{
    const auto& nodeBuffer = videoPlayerBuffer->node();
    parseNode(videoPlayer, nodeBuffer);
    
    const auto& fullScreen = videoPlayerBuffer->fullScreen();
    videoPlayer->setFullScreenEnabled(fullScreen);
    
    const auto& keepAspect = videoPlayerBuffer->keepAspect();
    videoPlayer->setKeepAspectRatioEnabled(keepAspect);
    
    const auto& isLocal = videoPlayerBuffer->isLocal();
    const auto& url = videoPlayerBuffer->url();
    if (isLocal)
        videoPlayer->setFileName(url->str());
    else
        videoPlayer->setURL(url->str());
}

cocos2d::experimental::ui::WebView* CreatorReader::createWebView(const buffers::WebView* webViewBuffer) const
{
    auto webView = cocos2d::experimental::ui::WebView::create();
    parseWebView(webView, webViewBuffer);
    return webView;
}

void CreatorReader::parseWebView(cocos2d::experimental::ui::WebView* webView, const buffers::WebView* webViewBuffer) const
{
    const auto& nodeBuffer = webViewBuffer->node();
    parseNode(webView, nodeBuffer);
    
    const auto& url = webViewBuffer->url();
    if (url)
        webView->loadURL(url->str());
}
#endif

cocos2d::ui::Slider* CreatorReader::createSlider(const buffers::Slider* sliderBuffer) const
{
    auto slider = cocos2d::ui::Slider::create();
    parseSlider(slider, sliderBuffer);
    return slider;
}

void CreatorReader::parseSlider(cocos2d::ui::Slider* slider, const buffers::Slider* sliderBuffer) const
{
    const auto& nodeBuffer = sliderBuffer->node();
    parseNode(slider, nodeBuffer);
    
    const auto& percent = sliderBuffer->percent();
    slider->setPercent(percent);
    slider->setMaxPercent(100);
    
    slider->setScale9Enabled(true);
    const auto& barSpritePath = sliderBuffer->barTexturePath();
    if (barSpritePath)
    {
        slider->loadBarTexture(barSpritePath->str());
        const auto& barSize = sliderBuffer->barSize();
        slider->setCapInsetsBarRenderer(cocos2d::Rect(0, 0, barSize->w(), barSize->h()));
    }
    
    cocos2d::Sprite* render = nullptr;
    
    const auto& normalSpritePath = sliderBuffer->normalTexturePath();
    if (normalSpritePath)
    {
        slider->loadSlidBallTextureNormal(normalSpritePath->str());
        render = slider->getSlidBallNormalRenderer();
    }
    
    const auto& pressedSpritePath = sliderBuffer->pressedTexturePath();
    if (pressedSpritePath)
        slider->loadSlidBallTexturePressed(pressedSpritePath->str());
        
    const auto& disabledSpritePath = sliderBuffer->disabledTexturePath();
    if (disabledSpritePath)
        slider->loadSlidBallTextureDisabled(disabledSpritePath->str());
    
    slider->setUnifySizeEnabled(true);
    
    if (render)
    {
        const auto&& ballSize = sliderBuffer->ballSize();
        const auto&& ball = slider->getSlidBallRenderer();
        const auto contentSize = render->getContentSize();
        ball->setScale(ballSize->w() / contentSize.width,
                       ballSize->h() / contentSize.height);
    }
}

cocos2d::ui::CheckBox* CreatorReader::createToggle(const buffers::Toggle* toggleBuffer) const
{
    const auto& backgroundSpritePath = toggleBuffer->backgroundSpritePath();
    const auto& checkMarkSpritePath = toggleBuffer->checkMarkSpritePath();
    const std::string strBackgroundSpritePath = backgroundSpritePath ? backgroundSpritePath->str() : "";
    const std::string crossSpritePath = checkMarkSpritePath ? checkMarkSpritePath->str() : "";
    
    auto checkBox = cocos2d::ui::CheckBox::create(strBackgroundSpritePath, crossSpritePath);
    parseToggle(checkBox, toggleBuffer);
    return checkBox;
}

void CreatorReader::parseToggle(cocos2d::ui::CheckBox* checkBox, const buffers::Toggle* toggleBuffer) const
{
    const auto& nodeBuffer = toggleBuffer->node();
    parseNode(checkBox, nodeBuffer);
    
    const auto& isChecked = toggleBuffer->isChecked();
    checkBox->setSelected(isChecked);
    
    const auto& zoomScale = toggleBuffer->zoomScale();
    checkBox->setZoomScale(zoomScale);
    checkBox->ignoreContentAdaptWithSize(false);
    
    const auto& interactable = toggleBuffer->interactable();
    if (!interactable)
    {
        checkBox->setTouchEnabled(false);
        
        const auto& enableAutoGrayEffect = toggleBuffer->enableAutoGrayEffect();
        if (enableAutoGrayEffect)
            checkBox->setSelected(false);
    }
}

cocos2d::ui::RadioButtonGroup* CreatorReader::createToggleGroup(const buffers::ToggleGroup* toggleGroupBuffer) const
{
    auto radioGroup = cocos2d::ui::RadioButtonGroup::create();
    parseToggleGroup(radioGroup, toggleGroupBuffer);
    return radioGroup;
}

void CreatorReader::parseToggleGroup(cocos2d::ui::RadioButtonGroup* radioGroup, const buffers::ToggleGroup* toggleGroupBuffer) const
{
    const auto& nodeBuffer = toggleGroupBuffer->node();
    parseNode(radioGroup, nodeBuffer);
    
    const auto& allowSwitchOff = toggleGroupBuffer->allowSwitchOff();
    if (allowSwitchOff)
        radioGroup->setAllowedNoSelection(true);
    
    const auto& toggles = toggleGroupBuffer->toggles();
    for (const auto& toggleBuffer : *toggles)
    {
        const auto& backgroundSpritePath = toggleBuffer->backgroundSpritePath();
        const auto& checkMarkSpritePath = toggleBuffer->checkMarkSpritePath();
        const std::string strBackgroundSpritePath = backgroundSpritePath ? backgroundSpritePath->str() : "";
        const std::string crossSpritePath = checkMarkSpritePath ? checkMarkSpritePath->str() : "";
        auto radioButton = cocos2d::ui::RadioButton::create(strBackgroundSpritePath, crossSpritePath);
        
        const auto& radioButtonNodeBuffer = toggleBuffer->node();
        parseNode(radioButton, radioButtonNodeBuffer);
        
        const auto& isChecked = toggleBuffer->isChecked();
        radioButton->setSelected(isChecked);
        
        const auto& interactable = toggleBuffer->interactable();
        if (!interactable)
        {
            radioButton->setTouchEnabled(false);
            
            const auto& enableAutoGrayEffect = toggleBuffer->enableAutoGrayEffect();
            if (enableAutoGrayEffect)
                radioButton->setSelected(false);
        }
        
        const auto& zoomScale = toggleBuffer->zoomScale();
        radioButton->setZoomScale(zoomScale);
        radioButton->ignoreContentAdaptWithSize(false);
        
        radioGroup->addRadioButton(radioButton);
        radioGroup->addChild(radioButton);
    }
}

cocos2d::ui::PageView* CreatorReader::createPageView(const buffers::PageView* pageViewBuffer) const
{
    auto pageview = CreatorPageView::create();
    parsePageView(pageview, pageViewBuffer);
    return pageview;
}

void CreatorReader::parsePageView(cocos2d::ui::PageView* pageview, const buffers::PageView* pageViewBuffer) const
{
    const auto& nodeBuffer = pageViewBuffer->node();
    parseNode(pageview, nodeBuffer);
    
    const auto& direction = pageViewBuffer->direction();
    pageview->setDirection(static_cast<cocos2d::ui::ScrollView::Direction>(direction));
    
    const auto& inertia = pageViewBuffer->inertia();
    pageview->setInertiaScrollEnabled(inertia);
    
    const auto& bounceEnabled = pageViewBuffer->bounceEnabled();
    pageview->setBounceEnabled(bounceEnabled);
    
    // indicator
    const auto& indicator = pageViewBuffer->indicator();
    const auto ICSpriteFrame = indicator->spriteFrame();
    if (ICSpriteFrame)
    {
        // should enable before loading texture
        pageview->setIndicatorEnabled(true);
        
        const auto spriteFrameFromTP = indicator->spriteFrameFromTP();
        const auto textureType = spriteFrameFromTP ? cocos2d::ui::Widget::TextureResType::PLIST : cocos2d::ui::Widget::TextureResType::LOCAL;
        pageview->setIndicatorIndexNodesTexture(ICSpriteFrame->str(), textureType);
        
        const auto& space = indicator->space();
        pageview->setIndicatorSpaceBetweenIndexNodes(space);
        
        const auto& positionAnchor = indicator->positionAnchor();
        pageview->setIndicatorPositionAsAnchorPoint(cocos2d::Vec2(positionAnchor->x(), positionAnchor->y()));
    }
    
    // pages
    const auto& pages = pageViewBuffer->pages();
    for (const auto& page : *pages)
    {
        auto imageView = cocos2d::ui::ImageView::create();
        
        const auto& spriteFrame = page->spriteFrame();
        const auto& spriteFrameFromTP = page->spriteFrameFromTP();
        const auto textureType = spriteFrameFromTP ? cocos2d::ui::Widget::TextureResType::PLIST : cocos2d::ui::Widget::TextureResType::LOCAL;
        imageView->loadTexture(spriteFrame->str(), textureType);
        
        // should prase node after loading texture
        const auto& imageViewNodeBuffer = page->node();
        parseNode(imageView, imageViewNodeBuffer);
        
        const auto scale9Enabled = page->scale9Enabled();
        imageView->setScale9Enabled(scale9Enabled);
        
        pageview->addPage(imageView);
    }
    
    // background
    const auto& background = pageViewBuffer->background();
    const auto& backgroundSpriteFrame = background->spriteFrame();
    if (backgroundSpriteFrame)
    {
        const auto& spriteFrameFromTP = background->spriteFrameFromTP();
        const auto textureType = spriteFrameFromTP ? cocos2d::ui::Widget::TextureResType::PLIST : cocos2d::ui::Widget::TextureResType::LOCAL;
        pageview->setBackGroundImage(backgroundSpriteFrame->str(), textureType);
        pageview->setBackGroundImageScale9Enabled(true);
    }
}

cocos2d::ClippingNode* CreatorReader::createMask(const buffers::Mask* maskBuffer) const
{
    auto mask = cocos2d::ClippingNode::create();
    parseMask(mask, maskBuffer);
    return mask;
}

void CreatorReader::parseMask(cocos2d::ClippingNode* mask, const buffers::Mask* maskBuffer) const
{
    const auto& nodeBuffer = maskBuffer->node();
    parseNode(mask, nodeBuffer);
    
    const auto& inverted = maskBuffer->inverted();
    mask->setInverted(inverted);
    
    const auto& type = maskBuffer->type();
    if (MaskType::MaskType_Rect == type)
    {
        const auto size = mask->getContentSize();
        cocos2d::Vec2 rectangle[4] = {
            {0, 0},
            {size.width, 0 },
            {size.width, size.height},
            {0, size.height}
        };
        auto stencil = cocos2d::DrawNode::create();
        stencil->drawPolygon(rectangle, 4, cocos2d::Color4F::WHITE, 1, cocos2d::Color4F::WHITE);
        
        mask->setStencil(stencil);
    }
    else if (MaskType::MaskType_Ellipse == type)
    {
        const auto size = mask->getContentSize();
        const auto r = MIN(size.width, size.height) / 2;
        const auto& segments = maskBuffer->segments();
        auto stencil = cocos2d::DrawNode::create();
        stencil->drawSolidCircle(cocos2d::Vec2(r, r), r, M_PI * 2, segments, cocos2d::Color4F::WHITE);
        
        mask->setStencil(stencil);
    }
    else
    {
        // image stencil type
        const auto& alphaThreshold = maskBuffer->alphaThreshold();
        const auto& spriteFrame = maskBuffer->spriteFrame();
        auto stencil = cocos2d::Sprite::createWithSpriteFrameName(spriteFrame->c_str());
        stencil->setContentSize(mask->getContentSize());
        
        mask->setStencil(stencil);
        mask->setAlphaThreshold(alphaThreshold);
    }
}

cocos2d::MotionStreak* CreatorReader::createMotionStreak(const buffers::MotionStreak* motionStreakBuffer) const
{
    const auto& timeToFade = motionStreakBuffer->timeToFade();
    const auto& minSeg = motionStreakBuffer->minSeg();
    const auto& strokeWidth = motionStreakBuffer->strokeWidth();
    
    const auto& color = motionStreakBuffer->strokeColor();
    const cocos2d::Color3B strokeColor(color->r(), color->g(), color->b());
    
    const auto& imagePath = motionStreakBuffer->texturePath();
    
    auto motionStreak = cocos2d::MotionStreak::create(timeToFade, minSeg, strokeWidth, strokeColor, imagePath->c_str());
    parseMotionStreak(motionStreak, motionStreakBuffer);
    
    return motionStreak;
}

void CreatorReader::parseMotionStreak(cocos2d::MotionStreak* motionStreak, const buffers::MotionStreak* motionStreakBuffer) const
{
    const auto& nodeBuffer = motionStreakBuffer->node();
    
    // can not reuse parseNode because MotionStreak::setOpacity will cause assert error
    // parseNode(motionStreak, nodeBuffer);
    {
        auto node = motionStreak;
        const auto& globalZOrder = nodeBuffer->globalZOrder();
        node->setGlobalZOrder(globalZOrder);
        const auto& localZOrder = nodeBuffer->localZOrder();
        node->setLocalZOrder(localZOrder);
        const auto& name = nodeBuffer->name();
        if (name) node->setName(name->str());
        const auto& anchorPoint = nodeBuffer->anchorPoint();
        if (anchorPoint) node->setAnchorPoint(cocos2d::Vec2(anchorPoint->x(), anchorPoint->y()));
        const auto& color = nodeBuffer->color();
        if (color) node->setColor(cocos2d::Color3B(color->r(), color->g(), color->b()));
        const auto& cascadeOpacityEnabled = nodeBuffer->cascadeOpacityEnabled();
        node->setCascadeOpacityEnabled(cascadeOpacityEnabled);
        const auto& opacityModifyRGB = nodeBuffer->opacityModifyRGB();
        node->setOpacityModifyRGB(opacityModifyRGB);
        const auto position = nodeBuffer->position();
        if (position) node->setPosition(cocos2d::Vec2(position->x(), position->y()));
        node->setRotationSkewX(nodeBuffer->rotationSkewX());
        node->setRotationSkewY(nodeBuffer->rotationSkewY());
        node->setScaleX(nodeBuffer->scaleX());
        node->setScaleY(nodeBuffer->scaleY());
        node->setSkewX(nodeBuffer->skewX());
        node->setSkewY(nodeBuffer->skewY());
        const auto& tag = nodeBuffer->tag();
        node->setTag(tag);
        const auto contentSize = nodeBuffer->contentSize();
        if (contentSize) node->setContentSize(cocos2d::Size(contentSize->w(), contentSize->h()));
        const auto enabled = nodeBuffer->enabled();
        node->setVisible(enabled);
        
        // animation?
        parseNodeAnimation(node, nodeBuffer);
        
        parseColliders(node, nodeBuffer);
    }
    
    const auto& fastMode = motionStreakBuffer->fastMode();
    motionStreak->setFastMode(fastMode);
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 *
 * Misc Nodes
 *
 *=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
spine::SkeletonAnimation* CreatorReader::createSpineSkeleton(const buffers::SpineSkeleton* spineBuffer) const
{
    const auto& jsonFile = spineBuffer->jsonFile()->str();
    const auto& atlasFile = spineBuffer->atlasFile()->str();
    const auto& timeScale = spineBuffer->timeScale();

    auto spine = spine::SkeletonAnimation::createWithJsonFile(jsonFile, atlasFile, timeScale);

    if (spine)
        parseSpineSkeleton(spine, spineBuffer);
    return spine;
}

void CreatorReader::parseSpineSkeleton(spine::SkeletonAnimation* spine, const buffers::SpineSkeleton* spineBuffer) const
{
    const auto& nodeBuffer = spineBuffer->node();
    parseNode(spine, nodeBuffer);

    // defaultSkin:string;
    // defaultAnimation:string;
    // loop:bool;
    // premultipliedAlpha:bool;
    // timeScale:float = 1;
    // debugSlots:bool;
    // debugBones:bool;

    const auto& defaultSkin = spineBuffer->defaultSkin()->str();
    const auto& defaultAnimation = spineBuffer->defaultAnimation()->str();
    const auto& loop = spineBuffer->loop();
//    const auto& premultipledAlpha = spineBuffer->premultipliedAlpha();
    const auto& debugSlots = spineBuffer->debugSlots();
    const auto& debugBones = spineBuffer->debugBones();

    spine->setSkin(defaultSkin);
    spine->setAnimation(0, defaultAnimation, loop);
    spine->setDebugSlotsEnabled(debugSlots);
    spine->setDebugBonesEnabled(debugBones);
}

dragonBones::CCArmatureDisplay* CreatorReader::createArmatureDisplay(const buffers::DragonBones* dragonBonesBuffer) const
{
    const auto& boneDataPath = dragonBonesBuffer->boneDataPath();
    const auto& atlasDataPath = dragonBonesBuffer->textureDataPath();
    
    if (boneDataPath && atlasDataPath)
    {
        auto factory = dragonBones::CCFactory::getInstance();
        const auto& boneDataName = dragonBonesBuffer->boneDataName();
        
        // DragonBones can not reload Bone data in debug mode, may cause asset crash.
        if (factory->getDragonBonesData(boneDataName->str()) == nullptr)
        {
            factory->loadDragonBonesData(boneDataPath->str());
            factory->loadTextureAtlasData(atlasDataPath->str());
        }
        
        const auto& armatureName = dragonBonesBuffer->armature();
        auto display = factory->buildArmatureDisplay(armatureName->str());
        parseArmatureDisplay(display, dragonBonesBuffer);
        
        return display;
    }
    else
        return nullptr;
    
}

void CreatorReader::parseArmatureDisplay(dragonBones::CCArmatureDisplay* armatureDisplay, const buffers::DragonBones* dragonBonesBuffer) const
{
    const auto& nodeBuffer = dragonBonesBuffer->node();
    parseNode(armatureDisplay, nodeBuffer);
    
    const auto& animationName = dragonBonesBuffer->animation();
    if (animationName)
    {
        armatureDisplay->getAnimation().play(animationName->str());
    }
}


//
// Helper methods
//
void CreatorReader::adjustPosition(cocos2d::Node* node) const
{
    const cocos2d::Node* parent = node->getParent();
    // only adjust position if there is a parent, and the parent is no the root scene
    if (parent && dynamic_cast<const cocos2d::Scene*>(parent) == nullptr) {
        const auto p_ap = parent->getAnchorPoint();
        const auto p_cs = parent->getContentSize();

        const auto offset = cocos2d::Vec2(p_ap.x * p_cs.width, p_ap.y * p_cs.height);
        const auto new_pos = node->getPosition() + offset;
        node->setPosition(new_pos);
    }
}

//
// Helper free functions
//
static void setSpriteQuad(cocos2d::V3F_C4B_T2F_Quad* quad, const cocos2d::Size& origSize, const int x, const int y, float x_factor, float y_factor)
{
    float offset_x = origSize.width * x;
    float offset_y = origSize.height * y;

    quad->bl.vertices.set(cocos2d::Vec3(offset_x, offset_y, 0));
    quad->br.vertices.set(cocos2d::Vec3(offset_x + (origSize.width * x_factor), offset_y, 0));
    quad->tl.vertices.set(cocos2d::Vec3(offset_x, offset_y + (origSize.height * y_factor), 0));
    quad->tr.vertices.set(cocos2d::Vec3(offset_x + (origSize.width * x_factor), offset_y + (origSize.height * y_factor), 0));

    if (x_factor != 1.0f || y_factor != 1.0f) {
        float x_size = (quad->br.texCoords.u - quad->bl.texCoords.u) * x_factor;
        float y_size = (quad->tl.texCoords.v - quad->bl.texCoords.v) * y_factor;

        quad->br.texCoords = Tex2F(quad->bl.texCoords.u + x_size, quad->bl.texCoords.v);
        quad->tl.texCoords = Tex2F(quad->tl.texCoords.u, quad->bl.texCoords.v + y_size);
        quad->tr.texCoords = Tex2F(quad->bl.texCoords.u + x_size, quad->bl.texCoords.v + y_size);
    }
}

static void tileSprite(cocos2d::Sprite* sprite)
{
    const auto new_s = sprite->getContentSize();
    const auto frame = sprite->getSpriteFrame();
    const auto orig_s_pixel = frame->getOriginalSizeInPixels();
    const auto orig_rect = frame->getRectInPixels();

    // cheat: let the sprite calculate the original Quad for us.
    sprite->setContentSize(orig_s_pixel);
    V3F_C4B_T2F_Quad origQuad = sprite->getQuad();

    // restore the size
    sprite->setContentSize(new_s);

    const float f_x = new_s.width / orig_rect.size.width;
    const float f_y = new_s.height / orig_rect.size.height;
    const int n_x = std::ceil(f_x);
    const int n_y = std::ceil(f_y);

    const int totalQuads = n_x * n_y;

    // use new instead of malloc, since Polygon info will release them using delete
    V3F_C4B_T2F_Quad* quads = new (std::nothrow) V3F_C4B_T2F_Quad[totalQuads];
    unsigned short* indices = new (std::nothrow) unsigned short[totalQuads * 6];

    // populate the vertices
    for (int y=0; y<n_y; ++y) {
        for (int x=0; x<n_x; ++x) {
            quads[y * n_x + x] = origQuad;
            float x_factor = (orig_rect.size.width * (x+1) <= new_s.width) ? 1 : f_x - (long)f_x;
            float y_factor = (orig_rect.size.height * (y+1) <= new_s.height) ? 1 : f_y - (long)f_y;
            CCLOG("x=%g, y=%g", x_factor, y_factor);
            setSpriteQuad(&quads[y * n_x + x], orig_rect.size, x, y, x_factor, y_factor);
        }
    }

    // populate the indices
    for( int i=0; i < totalQuads; i++)
    {
        indices[i*6+0] = (GLushort) (i*4+0);
        indices[i*6+1] = (GLushort) (i*4+1);
        indices[i*6+2] = (GLushort) (i*4+2);
        indices[i*6+3] = (GLushort) (i*4+3);
        indices[i*6+4] = (GLushort) (i*4+2);
        indices[i*6+5] = (GLushort) (i*4+1);
    }

    TrianglesCommand::Triangles triangles;
    triangles.vertCount = 4 * totalQuads;
    triangles.indexCount = 6 * totalQuads;
    triangles.verts = (V3F_C4B_T2F*) quads;
    triangles.indices = indices;

    PolygonInfo poly;
    poly.setTriangles(triangles);

    // FIXME: setPolygonInfo will create new arrays and copy the recently alloced one
    // there should be a way to pass ownership so that it is not needed to copy them
    sprite->setPolygonInfo(poly);
}
