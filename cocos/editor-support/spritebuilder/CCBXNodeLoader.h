//
//  CCBXNodeLoader.h
//  cocos2d_libs
//
//  Created by Sergey on 29.10.14.
//
//

#ifndef __cocos2d_libs__CCBXNodeLoader__
#define __cocos2d_libs__CCBXNodeLoader__

#include "SpriteBuilder.h"
#include "base/CCMap.h"
#include "base/CCRefPtr.h"
#include <set>

NS_CC_BEGIN

class PhysicsBody;

namespace spritebuilder {
    
class CC_DLL PhysicsBodyLoader : public Ref
{
public:
    virtual PhysicsBody* createBody(const Node* node) const = 0;
};
    
enum class PositionUnit
{
    /// Position is set in points (this is the default)
    POINTS,
    
    /// Position is UI points, on iOS this corresponds to the native point system
    UIPOINTS,
    
    /// Position is a normalized value multiplied by the content size of the parent's container
    NORMALIZED,
    
};

enum class PositionReferenceCorner
{
    /// Position is relative to the bottom left corner of the parent container (this is the default)
    BOTTOMLEFT,
    
    /// Position is relative to the top left corner of the parent container
    TOPLEFT,
    
    /// Position is relative to the top right corner of the parent container
    TOPRIGHT,
    
    /// Position is relative to the bottom right corner of the parent container
    BOTTOMRIGHT,
};

enum class SizeUnit
{
    /// Content size is set in points (this is the default)
    POINTS,
    
    /// Position is UI points, on iOS this corresponds to the native point system
    UIPOINTS,
    
    /// Content size is a normalized value multiplied by the content size of the parent's container
    NORMALIZED,
    
    /// Content size is the size of the parents container inset by the supplied value
    INSETPOINTS,
    
    /// Content size is the size of the parents container inset by the supplied value multiplied by the UIScaleFactor (as defined by CCDirector)
    INSETUIPOINTS,
    
};

enum class ScaleType
{
    ABSOLUTE = 0,
    MULTIPLY_RESOURCES_SCALE = 1,
    MULTIPLY_MAIN_SCALE = 2,
    MULTIPLY_ADDITION_SCALE_X = 4,
    MULTIPLY_ADDITION_SCALE_Y = 8,
    INVERT_SCALE = 16,
};

Vec2 getAbsolutePosition(float mainScale, float additionalScale, const Vec2 &pt, PositionReferenceCorner corner, PositionUnit xUnit, PositionUnit yUnit, const Size &containerSize);
Size getAbsoluteSize(float mainScale, float additionalScale, const Size &contentSize, SizeUnit widthUnit, SizeUnit heightUnit, const Size &containerSize);
Vec2 getAbsoluteScale(float mainScale, float additionalScale, float scaleX, float scaleY, unsigned int type);
float getAbsoluteScale(float mainScale, float additionalScale, float scale, unsigned int type);

struct PositionDescription
{
    PositionReferenceCorner referenceCorner;
    PositionUnit xUnits;
    PositionUnit yUnits;
    Vec2 pos;
};

struct SizeDescription
{
    SizeUnit widthUnits;
    SizeUnit heightUnits;
    Size size;
};

struct ScaleDescription
{
    int type;
    float xScale;
    float yScale;
};

struct FloatScaleDescription
{
    int type;
    float scale;
};

struct CallbackDescription
{
    TargetType type;
    std::string name;
};
    
struct SpriteFrameDescription
{
    enum class TextureResType
    {
        NONE,
        LOCAL,
        PLIST
    };
    SpriteFrameDescription():type(TextureResType::NONE) {}
    TextureResType type;
    std::string path;
    RefPtr<SpriteFrame> spriteFrame;
};
    
class CCBSequenceProperty;
class CCBAnimationManager;
class CCBSequence;

class CC_DLL NodeLoader : public Ref
{
public:
    static NodeLoader *create();
    Node *createNode(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner = nullptr, CCBAnimationManager *manager = nullptr, Node *rootNode = nullptr, CCBXReaderOwner *parentOwner = nullptr, const CreateNodeFunction &createNodeFunction = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr, bool nestedPrefab = false);
    bool loadNode(Node *node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner = nullptr,CCBAnimationManager *manager = nullptr, Node *parentOwner = nullptr, CCBXReaderOwner *rootOwner = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr, bool nestedPrefab = false);
    void setProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner = nullptr);
    void setAnimation(Node* node, CCBAnimationManager *manager);
    
    virtual Node *createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner = nullptr);
    virtual void setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner = nullptr);
    virtual void setCallbacks(Node* node, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *parentOwner);
    virtual void setVariables(Node* node, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *parentOwner);
    
    
    void setMemberVarAssignment(TargetType type, const std::string &name);
    void setPhysicsLoader(PhysicsBodyLoader *loader);
    
    void addChild(NodeLoader *loader);
    void setSequences(const Vector<CCBSequence*> &sequences);
    void setAutoPlaySequenceId(int id);
    void setBaseValues(const std::unordered_map<std::string, cocos2d::Value> &values);
    void setObjects(const std::unordered_map<std::string, cocos2d::Ref*> &objects);
    void setNodeSequences(const std::unordered_map<int, Map<std::string, CCBSequenceProperty*>> &sequences);
    
    virtual void onHandlePropTypePosition(const std::string &propertyName, bool isExtraProp, const PositionDescription &value);
    virtual void onHandlePropTypePoint(const std::string &propertyName, bool isExtraProp, const Vec2 &value);
    virtual void onHandlePropTypeSize(const std::string &propertyName, bool isExtraProp, const SizeDescription &value);
    virtual void onHandlePropTypeScale(const std::string &propertyName, bool isExtraProp, const ScaleDescription &value);
    virtual void onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value);
    virtual void onHandlePropTypeDegrees(const std::string &propertyName, bool isExtraProp, float value);
    virtual void onHandlePropTypeFloatScale(const std::string &propertyName, bool isExtraProp, const FloatScaleDescription &value);
    virtual void onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value);
    virtual void onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value);
    virtual void onHandlePropTypeFloatVar(const std::string &propertyName, bool isExtraProp, const Vec2 &value);
    virtual void onHandlePropTypeAnimation(const std::string &propertyName, bool isExtraProp, int value);
    
    virtual void onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value);
    virtual void onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value);
    virtual void onHandlePropTypeTexture(const std::string &propertyName, bool isExtraProp, Texture2D * value);
    virtual void onHandlePropTypeColor3(const std::string &propertyName, bool isExtraProp, const Color3B &value);
    virtual void onHandlePropTypeColor4FVar(const std::string &propertyName, bool isExtraProp, const std::pair<Color4F, Color4F> &value);
    virtual void onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &flip);
    virtual void onHandlePropTypeColor4(const std::string &propertyName, bool isExtraProp, const Color4B &value);
    virtual void onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value);
    virtual void onHandlePropTypeFntFile(const std::string &propertyName, bool isExtraProp, const std::string &value);
    virtual void onHandlePropTypeText(const std::string &propertyName, bool isExtraProp, const std::string &value);
    virtual void onHandlePropTypeFontTTF(const std::string &propertyName, bool isExtraProp, const std::string &value);
    virtual void onHandlePropTypeClickCallback(const std::string &propertyName, bool isExtraProp, const CallbackDescription &value);
    virtual void onHandlePropTypeTouchCallback(const std::string &propertyName, bool isExtraProp, const CallbackDescription &value);
    virtual void onHandlePropTypeCCBFile(const std::string &propertyName, bool isExtraProp, NodeLoader *value);
    virtual void onHandlePropTypeFloatXY(const std::string &propertyName, bool isExtraProp, const Vec2 &value);
    virtual void onHandlePropTypeSoundFile(const std::string &propertyName, bool isExtraProp, const std::string &value);
    virtual void onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value);
    
    virtual void onLoaded();
    virtual void onNodeLoaded(Node *node);
    
CC_CONSTRUCTOR_ACCESS:
    NodeLoader();
    ~NodeLoader();
    
private:
    Vector<NodeLoader*> _children;
    PositionDescription _position;
    bool _anchorPointLoaded;
    Vec2 _anchorPoint;
    Vec2 _skew;
    bool _sizeLoaded;
    SizeDescription _size;
    ScaleDescription _scale;
    GLubyte _opacity;
    float _rotation;
    int _tag;
    bool _visible;
    bool _cascadeColorEnabled;
    bool _cascadeOpacityEnabled;
    Color3B _color;
    std::string _name;
    TargetType _memberVarAssignmentType;
    std::string _memberVarAssignmentName;
    PhysicsBodyLoader *_physicsLoader;
    Vector<CCBSequence*> _sequences;
    int _autoPlaySequenceId;
    std::unordered_map<int, Map<std::string, CCBSequenceProperty*>> _nodeSequences;
    std::unordered_map<std::string, cocos2d::Value> _baseValues;
    std::unordered_map<std::string, cocos2d::Ref*> _objects;
    cocos2d::ValueMap _customProperties;
};
    
template <class CustomNode>
class SimpleNodeLoader : public NodeLoader {
public:
    static NodeLoader* create()
    {
        SimpleNodeLoader *ret = new SimpleNodeLoader();
        ret->autorelease();
        return ret;
    }
    
    virtual cocos2d::Node *createNodeInstance(const cocos2d::Size &parentSize, float mainScale, float additionalScale, cocos2d::spritebuilder::CCBXReaderOwner *owner, cocos2d::Node *rootNode, cocos2d::spritebuilder::CCBXReaderOwner *parentOwner) override
    {
        return CustomNode::create();
    }
};
    
template <class CustomNode>
class AdvanceNodeLoader : public NodeLoader {
public:
    static NodeLoader* create()
    {
        AdvanceNodeLoader *ret = new AdvanceNodeLoader();
        ret->autorelease();
        return ret;
    }
    
    virtual cocos2d::Node *createNodeInstance(const cocos2d::Size &parentSize, float mainScale, float additionalScale, cocos2d::spritebuilder::CCBXReaderOwner *owner, cocos2d::Node *rootNode, cocos2d::spritebuilder::CCBXReaderOwner *parentOwner) override
    {
        return CustomNode::create();
    }
    
    virtual void onNodeLoaded(Node *node) override
    {
        static_cast<CustomNode*>(node)->onLoaded();
    }
};

}

NS_CC_END


#endif /* defined(__cocos2d_libs__CCBXNodeLoader__) */
