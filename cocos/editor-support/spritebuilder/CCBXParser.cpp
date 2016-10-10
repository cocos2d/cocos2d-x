
//
//  CCBXReader.cpp
//  cocos2d_libs
//
//  Created by Sergey on 29.10.14.
//
//

#include "CCBXParser.h"
#include <set>
#include "CCBXSequence.h"
#include "CCBXNodeLoader.h"
#include "2d/CCSpriteFrameCache.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "base/CCDirector.h"
#include "physics/CCPhysicsBody.h"
#include "platform/CCFileUtils.h"
#include "CCBXNodeLoaderLibrary.h"
#include "CCBXReaderParams.h"

#define CCBX_MIN_VERSION 7
#define CCBX_MAX_VERSION 8
#define ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(PROPERTYTYPE) cocos2d::log("Unexpected property type: '%d'!\n", PROPERTYTYPE); assert(false)

NS_CC_BEGIN

namespace spritebuilder {
    
class BasePhysicsBodyLoader : public PhysicsBodyLoader
{
public:
    void setParams(PhysicsBody* body) const
    {
#if CC_USE_PHYSICS
        body->setDynamic(dynamic);
        
        if(dynamic && setMass)
            body->setMass(mass);
        if(dynamic && setMoment)
            body->setMoment(moment);
        
        body->setCategoryBitmask(categoryBitmask);
        body->setContactTestBitmask(contactTestBitmask);
        body->setCollisionBitmask(collisionBitmask);
        
        if(dynamic)
        {
            body->setVelocity(velocity * CCBXReader::getResolutionScale());
            body->setVelocityLimit(velocityLimit * CCBXReader::getResolutionScale());
            body->setAngularVelocity(angularVelocity * CCBXReader::getResolutionScale());
            body->setAngularVelocityLimit(angularVelocityLimit * CCBXReader::getResolutionScale());
            body->setLinearDamping(linearDamping * CCBXReader::getResolutionScale());
            body->setAngularDamping(angularDamping * CCBXReader::getResolutionScale());
        }
        
        if (dynamic)
        {
            body->setGravityEnable(affectedByGravity);
            body->setRotationEnable(allowsRotation);
        }
        
        for(const auto &it : body->getShapes())
        {
            it->setDensity(density);
            it->setFriction(friction);
            it->setRestitution(elasticity);
        }
#endif
    }
    
    bool dynamic;
    bool affectedByGravity;
    bool allowsRotation;
    
    float density;
    float friction;
    float elasticity;
    
    bool setMass;
    float mass;
    bool setMoment;
    float moment;
    unsigned categoryBitmask;
    unsigned contactTestBitmask;
    unsigned collisionBitmask;
    Vec2 velocity;
    float velocityLimit;
    float angularVelocity;
    float angularVelocityLimit;
    float linearDamping;
    float angularDamping;
    
};

enum class PhysicsShapeType
{
    Polygon,
    Circle
};

class ShapePolygonLoader : public BasePhysicsBodyLoader
{
public:
    static ShapePolygonLoader* create(const std::vector<std::vector<Point>> &polygons)
    {
        ShapePolygonLoader *ret = new ShapePolygonLoader(polygons);
        ret->autorelease();
        return ret;
    }
    virtual PhysicsBody* createBody(const Node* node) const override
    {
#if CC_USE_PHYSICS
        const Size &size = node->getContentSize();
        PhysicsBody *ret =  PhysicsBody::create();
        for (size_t i=0; i < _polygons.size(); i++)
        {
            std::vector<Point> polygon;
            polygon.reserve(_polygons[i].size());
            for(size_t j=0;j<_polygons[i].size();++j)
            {
                polygon.push_back(Point(_polygons[i][j].x * CCBXReader::getResolutionScale() - size.width/2, _polygons[i][j].y * CCBXReader::getResolutionScale() - size.height/2));
            }
            ret->addShape(PhysicsShapePolygon::create(&polygon.front(), (int)polygon.size(), PHYSICSBODY_MATERIAL_DEFAULT));
        }
        setParams(ret);
        return ret;
#else
        return nullptr;
#endif
    }
CC_CONSTRUCTOR_ACCESS:
    ShapePolygonLoader(const std::vector<std::vector<Point>> &polygons):_polygons(polygons){}
    ~ShapePolygonLoader(){}
    
private:
    std::vector<std::vector<Point>> _polygons;
};

class ShapeCircleLoader : public BasePhysicsBodyLoader
{
public:
    static ShapeCircleLoader* create(const Vec2 &center, float radius)
    {
        ShapeCircleLoader *ret = new ShapeCircleLoader(center, radius);
        ret->autorelease();
        return ret;
    }
    virtual PhysicsBody* createBody(const Node* node) const override
    {
#if CC_USE_PHYSICS
        const Size &size = node->getContentSize();
        PhysicsBody* ret = PhysicsBody::createCircle(_radius * CCBXReader::getResolutionScale(), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(_center.x * CCBXReader::getResolutionScale() - size.width/2, _center.y * CCBXReader::getResolutionScale() - size.height/2));
        setParams(ret);
        return ret;
#else
        return nullptr;
#endif
    }
CC_CONSTRUCTOR_ACCESS:
    ShapeCircleLoader(const Vec2 &center, float radius):_center(center),_radius(radius){}
    ~ShapeCircleLoader(){}
    
private:
    Vec2 _center;
    float _radius;
};


class InternalReader
{
public:
    static  NodeLoader* parse(const Data &data, const NodeLoaderLibrary *library, const std::string &rootPath, const CCBReaderParams* params)
    {
        InternalReader reader(data, rootPath, params);
        return reader.parse(library);
    }
private:
    enum class FloatType {
        _0 = 0,
        _1,
        MINUS1,
        _05,
        INTEGER,
        FULL
    };
    
    enum class PropertyType {
        POSITION = 0,
        SIZE,
        POINT,
        POINT_LOCK,
        SCALE_LOCK,
        DEGREES,
        INTEGER,
        FLOAT,
        FLOAT_VAR,
        CHECK,
        SPRITEFRAME,
        TEXTURE,
        BYTE,
        COLOR3,
        COLOR4F_VAR,
        FLIP,
        BLEND_MODE,
        FNT_FILE,
        TEXT,
        FONT_TTF,
        INTEGER_LABELED,
        BLOCK,
        ANIMATION,
        CCB_FILE,
        STRING,
        BLOCK_CONTROL,
        FLOAT_SCALE,
        FLOAT_XY,
        COLOR4,
        NODE_REFERENCE,
        FLOAT_CHECK,
        EFFECT_CONTROL,
        SOUND_FILE,
        OFFSETS,
    };
    
    
    InternalReader(const Data &data, const std::string &rootPath, const CCBReaderParams* params):_data(data),_rootPath(rootPath),_params(params),_position(0)
    {
        
    }
    
    static std::string deletePathExtension(const char* pPath) {
        std::string path(pPath);
        size_t dotPos = path.find_last_of(".");
        if(dotPos != std::string::npos) {
            return path.substr(0, dotPos);
        }
        return path;
    }
    
    NodeLoader* parse(const NodeLoaderLibrary *library)
    {
        if (! readHeader())
        {
            return nullptr;
        }
        
        if (! readStringCache())
        {
            return nullptr;
        }
        
        Vector<CCBSequence*> sequences;
        int autoPlaySequenceId = -1;
        
        if (! readSequences(sequences, autoPlaySequenceId))
        {
            return nullptr;
        }
        
        //setAnimationManagers(am);
        
        NodeLoader* loader = readNodeGraph(library);
        
        if(loader)
        {
            loader->setSequences(sequences);
            loader->setAutoPlaySequenceId(autoPlaySequenceId);
        }
        
        return loader;
        
        /*_animationManagers->insert(pNode, _animationManager);
        
        if (bCleanUp)
        {
            cleanUpNodeGraph(pNode);
        }
        
        return pNode;*/
    }
    
    bool readStringCache() {
        int numStrings = readInt(false);
        
        for(int i = 0; i < numStrings; i++) {
            _stringCache.push_back(readUTF8());
        }
        
        return true;
    }
    
    bool readCallbackKeyframesForSeq(CCBSequence* seq)
    {
        int numKeyframes = readInt(false);
        if(!numKeyframes) return true;
        
        CCBSequenceProperty* channel = new (std::nothrow) CCBSequenceProperty();
        channel->autorelease();
        
        for(int i = 0; i < numKeyframes; ++i) {
            
            float time = readFloat();
            std::string callbackName = readCachedString();
            
            int callbackType = readInt(false);
            
            ValueVector valueVector;
            valueVector.push_back(Value(callbackName));
            valueVector.push_back(Value(callbackType));
            
            CCBKeyframe* keyframe = new (std::nothrow) CCBKeyframe();
            keyframe->autorelease();
            
            keyframe->setTime(time);
            keyframe->setValue(Value(valueVector));
            
            channel->getKeyframes().pushBack(keyframe);
        }
        
        seq->setCallbackChannel(channel);
        
        return true;
    }
    
    bool readSoundKeyframesForSeq(CCBSequence* seq) {
        int numKeyframes = readInt(false);
        if(!numKeyframes) return true;
        
        CCBSequenceProperty* channel = new (std::nothrow) CCBSequenceProperty();
        channel->autorelease();
        
        for(int i = 0; i < numKeyframes; ++i) {
            
            float time = readFloat();
            std::string soundFile = readCachedString();
            float pitch = readFloat();
            float pan = readFloat();
            float gain = readFloat();
            
            ValueVector vec;
            vec.push_back(Value(soundFile));
            vec.push_back(Value(pitch));
            vec.push_back(Value(pan));
            vec.push_back(Value(gain));
            
            CCBKeyframe* keyframe = new (std::nothrow) CCBKeyframe();
            keyframe->setTime(time);
            keyframe->setValue(Value(vec));
            channel->getKeyframes().pushBack(keyframe);
            keyframe->release();
        }
        
        seq->setSoundChannel(channel);
        
        return true;
    }
    
    bool readSequences(Vector<CCBSequence*> &sequences, int &autoPlaySequenceId)
    {
        int numSeqs = readInt(false);
        
        if(_version>7)
        {
            /*bool hasPhysicsBodies = */readBool();
            /*bool hasPhysicsNode = */readBool();
        }
        
        for (int i = 0; i < numSeqs; i++)
        {
            CCBSequence *seq = new CCBSequence();
            seq->autorelease();
            
            seq->setDuration(readFloat());
            seq->setName(readCachedString().c_str());
            seq->setSequenceId(readInt(false));
            seq->setChainedSequenceId(readInt(true));
            
            if(!readCallbackKeyframesForSeq(seq)) return false;
            if(!readSoundKeyframesForSeq(seq)) return false;
            
            sequences.pushBack(seq);
        }
        autoPlaySequenceId = readInt(true);
        return true;
    }
    
    bool readHeader()
    {
        /* If no bytes loaded, don't crash about it. */
        if(_data.isNull()) {
            return false;
        }
        
        /* Read magic bytes */
        int magicBytes = *((int*)(_data.getBytes()));
        _position += 4;
        
        if(CC_SWAP_INT32_BIG_TO_HOST(magicBytes) != (*reinterpret_cast<const int*>("ccbx")))
            return false;
        
        /* Read version. */
        _version = readInt(false);
        if((_version > CCBX_MAX_VERSION)||(_version < CCBX_MIN_VERSION)) {
            log("WARNING! Incompatible ccbx file version (file: %d reader min: %d reader max: %d)", _version, CCBX_MIN_VERSION, CCBX_MAX_VERSION);
            return false;
        }
        
        return true;
    }
    
    unsigned char readByte()
    {
        unsigned char byte = _data.getBytes()[_position];
        _position++;
        return byte;
    }
    
    bool readBool()
    {
        return 0 == this->readByte() ? false : true;
    }
    
    std::string readUTF8()
    {
        std::string ret;
        
        int b0 = this->readByte();
        int b1 = this->readByte();
        
        int numBytes = b0 << 8 | b1;
        
        char* pStr = (char*)malloc(numBytes+1);
        memcpy(pStr, _data.getBytes() + _position, numBytes);
        pStr[numBytes] = '\0';
        ret = pStr;
        free(pStr);
        
        _position += numBytes;
        
        return ret;
    }
    
    inline long readVariableLengthIntFromArray(const uint8_t* buffer, uint32_t &value) {
        const uint8_t* ptr = buffer;
        uint32_t b;
        uint32_t result;
        
        b = *(ptr++); result  = (b & 0x7F)      ; if (!(b & 0x80)) goto done;
        b = *(ptr++); result |= (b & 0x7F) <<  7; if (!(b & 0x80)) goto done;
        b = *(ptr++); result |= (b & 0x7F) << 14; if (!(b & 0x80)) goto done;
        b = *(ptr++); result |= (b & 0x7F) << 21; if (!(b & 0x80)) goto done;
        b = *(ptr++); result |=  b         << 28; if (!(b & 0x80)) goto done;
        
    done:
        value = result;
        return ptr - buffer;
    }
    
    int readInt(bool pSigned)
    {
        unsigned int value = 0;
        _position += readVariableLengthIntFromArray(_data.getBytes() + _position, value);
        int num = 0;
        
        if (pSigned)
        {
            if (value & 0x1)
                num = -(int)((value+1) >> 1);
            else
                num = (int)(value >> 1);
        }
        else
        {
            num = (int)value;
        }
        
        return num;
    }
    
    
    float readFloat()
    {
        FloatType type = static_cast<FloatType>(this->readByte());
        
        switch (type)
        {
            case FloatType::_0:
                return 0;
            case FloatType::_1:
                return 1;
            case FloatType::MINUS1:
                return -1;
            case FloatType::_05:
                return 0.5f;
            case FloatType::INTEGER:
                return (float)this->readInt(true);
            default:
            {
                /* using a memcpy since the compiler isn't
                 * doing the float ptr math correctly on device.
                 * TODO still applies in C++ ? */
                unsigned char* pF = (_data.getBytes() + _position);
                float f = 0;
                
                // N.B - in order to avoid an unaligned memory access crash on 'memcpy()' the the (void*) casts of the source and
                // destination pointers are EXTREMELY important for the ARM compiler.
                //
                // Without a (void*) cast, the ARM compiler makes the assumption that the float* pointer is naturally aligned
                // according to it's type size (aligned along 4 byte boundaries) and thus tries to call a more optimized
                // version of memcpy() which makes this alignment assumption also. When reading back from a file of course our pointers
                // may not be aligned, hence we need to avoid the compiler making this assumption. The (void*) cast serves this purpose,
                // and causes the ARM compiler to choose the slower, more generalized (unaligned) version of memcpy()
                //
                // For more about this compiler behavior, see:
                // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka3934.html
                memcpy((void*) &f, (const void*) pF, sizeof(float));
                
                _position += sizeof(float);
                return f;
            }
        }
    }
    
    const std::string& readCachedString()
    {
        int n = this->readInt(false);
        return this->_stringCache[n];
    }
    
    PositionDescription parsePropTypePosition()
    {
        PositionDescription ret;
        ret.pos.x = readFloat();
        ret.pos.y = readFloat();

        {
            ret.referenceCorner = static_cast<PositionReferenceCorner>(readByte());
            ret.xUnits = static_cast<PositionUnit>(readByte());
            ret.yUnits = static_cast<PositionUnit>(readByte());
        }
        return ret;
    }
    
    Point parsePropTypePoint()
    {
        float x = readFloat();
        float y = readFloat();
        
        return Point(x, y);
    }

    
    SizeDescription parsePropTypeSize()
    {
        SizeDescription ret;
        ret.size.width = readFloat();
        ret.size.height = readFloat();
        ret.widthUnits = static_cast<SizeUnit>(readByte());
        ret.heightUnits = static_cast<SizeUnit>(readByte());

        return ret;
    }
    
    ScaleDescription parsePropTypeScale()
    {
        ScaleDescription ret;
        ret.xScale = readFloat();
        ret.yScale = readFloat();
        ret.type = readByte();
        return ret;
    }
    
    float parsePropTypeFloat() {
        return readFloat();
    }
    
    float parsePropTypeDegrees() {
        return readFloat();
    }
    
    Vec2 parsePropTypeFloatXY()
    {
        Vec2 ret;
        ret.x = readFloat();
        ret.y = readFloat();
        return ret;
    }
    
    FloatScaleDescription parsePropTypeFloatScale()
    {
        FloatScaleDescription ret;
        ret.scale = readFloat();
        ret.type = readInt(false);
        return ret;
    }
    
    int parsePropTypeInteger()
    {
        return readInt(true);
    }
    
    Vec2 parsePropTypeFloatVar()
    {
        float f = readFloat();
        float fVar = readFloat();
        
        Vec2 ret;
        ret.x = f;
        ret.y = fVar;
        
        return ret;
    }
    
    bool parsePropTypeCheck()
    {
        bool ret = readBool();
        return ret;
    }
    
    
    SpriteFrameDescription parsePropTypeSpriteFrame()
    {
        SpriteFrameDescription ret;
        std::string spriteFile = readCachedString();
        if (spriteFile.length() != 0)
        {
            ret.spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFile);
            if(ret.spriteFrame)
            {
                ret.type = SpriteFrameDescription::TextureResType::PLIST;
                ret.path = spriteFile;
            }
            else
            {
                Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(_rootPath + spriteFile);
                if(texture != NULL) {
                    Rect bounds = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                    ret.spriteFrame = SpriteFrame::createWithTexture(texture, bounds);
                    ret.type = SpriteFrameDescription::TextureResType::LOCAL;
                    ret.path = _rootPath + spriteFile;
                }
            }
        }
        /*if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
        {
            ccbReader->getAnimationManager()->setObject(spriteFrame, pNode, pPropertyName);
        }*/
        return ret;
    }
    
    Texture2D * parsePropTypeTexture() {
        std::string spriteFile = _rootPath + readCachedString();
        
        if (spriteFile.length() > 0)
        {
            return Director::getInstance()->getTextureCache()->addImage(spriteFile.c_str());
        }
        else
        {
            return nullptr;
        }
    }
    
    Color3B parsePropTypeColor3()
    {
        unsigned char r = std::min(readFloat(),1.0f) * 255.0;
        unsigned char g = std::min(readFloat(),1.0f) * 255.0;
        unsigned char b = std::min(readFloat(),1.0f) * 255.0;
        readFloat();
        Color3B color(r, g, b);
        return color;
    }
    
    Color4B parsePropTypeColor4() {
        unsigned char r = std::min(readFloat(),1.0f) * 255.0;
        unsigned char g = std::min(readFloat(),1.0f) * 255.0;
        unsigned char b = std::min(readFloat(),1.0f) * 255.0;
        unsigned char a = std::min(readFloat(),1.0f) * 255.0;
        
        Color4B color(r, g, b, a);
        return color;
    }
    
    std::pair<Color4F, Color4F> parsePropTypeColor4FVar() {
        float red = readFloat();
        float green = readFloat();
        float blue = readFloat();
        float alpha = readFloat();
        float redVar = readFloat();
        float greenVar = readFloat();
        float blueVar = readFloat();
        float alphaVar = readFloat();
        
        std::pair<Color4F, Color4F> colors;
        colors.first.r = red;
        colors.first.g = green;
        colors.first.b = blue;
        colors.first.a = alpha;
        
        colors.second.r = redVar;
        colors.second.g = greenVar;
        colors.second.b = blueVar;
        colors.second.a = alphaVar;
        
        return colors;
    }
    
    std::pair<bool, bool> parsePropTypeFlip()
    {
        bool flipX = readBool();
        bool flipY = readBool();
        
        std::pair<bool, bool> ret;
        ret.first = flipX;
        ret.second = flipY;
        
        return ret;
    }
    
    BlendFunc parsePropTypeBlendFunc()
    {
        int source = readInt(false);
        int destination = readInt(false);
        
        BlendFunc blendFunc;
        blendFunc.src = source;
        blendFunc.dst = destination;
        
        return blendFunc;
    }
    
    const std::string parsePropTypeFntFile()
    {
        return _rootPath + readCachedString();
    }
    
    const std::string& parsePropTypeText()
    {
        const std::string &text=readCachedString();
        bool localized = readBool();
        if(localized)
            return _params->getLocalizedString(text);
        return text;
    }
    
    const std::string parsePropTypeFontTTF()
    {
        return _rootPath + readCachedString();
    }
    
    CallbackDescription parsePropTypeBlock()
    {
        CallbackDescription ret;
        
        ret.name = readCachedString();
        ret.type =  static_cast<TargetType>(readInt(false));
        
        return ret;
    }
    
    CallbackDescription parsePropTypeBlockControl()
    {
        CallbackDescription ret;
        
        ret.name = readCachedString();
        ret.type =  static_cast<TargetType>(readInt(false));
        readInt(false);
        
        return ret;
    }
    
    NodeLoader *parsePropTypeCCBFile(const NodeLoaderLibrary *library)
    {
        std::string ccbFileName = _rootPath + readCachedString();
        
        if(ccbFileName.empty())
            return nullptr;
        
        /* Change path extension to .ccbi. */
        std::string ccbFileWithoutPathExtension = deletePathExtension(ccbFileName.c_str());
        ccbFileName = ccbFileWithoutPathExtension + ".ccbi";
        
        // Load sub file
        //std::string path = FileUtils::getInstance()->fullPathForFilename(ccbFileName.c_str());
        
        Data data = FileUtils::getInstance()->getDataFromFile(ccbFileName);
        NodeLoader *ret = InternalReader::parse(data, library, _rootPath, _params);
        
        
        /*reader->_bytes = dataPtr.getBytes();
        reader->_currentByte = 0;
        reader->_currentBit = 0;
        CC_SAFE_RETAIN(pCCBReader->_owner);
        reader->_owner = pCCBReader->_owner;
        
        reader->getAnimationManager()->_owner = reader->_owner;
        
        // The assignments below are done in the CCBReader constructor.
        //     reader->_ownerOutletNames = pCCBReader->_ownerOutletNames;
        //     reader->_ownerOutletNodes = pCCBReader->_ownerOutletNodes;
        //     reader->_ownerOutletNodes->retain();
        //     reader->_ownerCallbackNames = pCCBReader->_ownerCallbackNames;
        //     reader->_ownerCallbackNodes = pCCBReader->_ownerCallbackNodes;
        //     reader->_ownerCallbackNodes->retain();
        
        
        Node * ccbFileNode = reader->readFileWithCleanUp(false, pCCBReader->getAnimationManagers());
        
        if (ccbFileNode && reader->getAnimationManager()->getAutoPlaySequenceId() != -1)
        {
            // Auto play animations
            reader->getAnimationManager()->runAnimationsForSequenceIdTweenDuration(reader->getAnimationManager()->getAutoPlaySequenceId(), 0);
        }
        
        if (reader->isJSControlled() && pCCBReader->isJSControlled() && nullptr == reader->_owner)
        {
            //set variables and callback to owner
            //set callback
            auto ownerCallbackNames = reader->getOwnerCallbackNames();
            auto& ownerCallbackNodes = reader->getOwnerCallbackNodes();
            if (!ownerCallbackNames.empty() && !ownerCallbackNodes.empty())
            {
                CCASSERT(ownerCallbackNames.size() == ownerCallbackNodes.size(), "");
                ssize_t nCount = ownerCallbackNames.size();
                
                for (ssize_t i = 0 ; i < nCount; i++)
                {
                    pCCBReader->addOwnerCallbackName(ownerCallbackNames[i].asString());
                    pCCBReader->addOwnerCallbackNode(ownerCallbackNodes.at(i));
                }
            }
            //set variables
            auto ownerOutletNames = reader->getOwnerOutletNames();
            auto ownerOutletNodes = reader->getOwnerOutletNodes();
            if (!ownerOutletNames.empty() && !ownerOutletNodes.empty())
            {
                CCASSERT(ownerOutletNames.size() == ownerOutletNodes.size(), "");
                ssize_t nCount = ownerOutletNames.size();
                
                for (ssize_t i = 0 ; i < nCount; i++)
                {
                    pCCBReader->addOwnerOutletName(ownerOutletNames.at(i).asString());
                    pCCBReader->addOwnerOutletNode(ownerOutletNodes.at(i));
                }
            }
        }*/
        return ret;
    }
    
    std::string parsePropTypeSoundFile()
    {
        std::string ccbFileName = _rootPath + readCachedString();
        return ccbFileName;
    }
    
    Vec4 parsePropTypeOffsets()
    {
        Vec4 ret;
        ret.x = readFloat();
        ret.y = readFloat();
        ret.z = readFloat();
        ret.w = readFloat();
        return ret;
    }

    
    void parseProperties(NodeLoader * loader, const NodeLoaderLibrary *library, const std::set<std::string> &animatedProperties)
    {
        int numRegularProps = readInt(false);
        int numExturaProps = readInt(false);
        int propertyCount = numRegularProps + numExturaProps;
        
        std::unordered_map<std::string, cocos2d::Value> baseValues;
        std::unordered_map<std::string, cocos2d::Ref*> objects;
        //cocos2d::ValueMap customProperties;
        
        for(int i = 0; i < propertyCount; i++) {
            bool isExtraProp = (i >= numRegularProps);
            PropertyType type = (PropertyType)readInt(false);
            std::string propertyName = readCachedString();
            
            // Forward properties for sub ccb files
            /*if (dynamic_cast<CCBFile*>(pNode) != nullptr)
            {
                CCBFile *ccbNode = (CCBFile*)pNode;
                if (ccbNode->getCCBFileNode() && isExtraProp)
                {
                    pNode = ccbNode->getCCBFileNode();
                    
                    // Skip properties that doesn't have a value to override
                    __Array *extraPropsNames = (__Array*)pNode->getUserObject();
                    Ref* pObj = nullptr;
                    bool bFound = false;
                    CCARRAY_FOREACH(extraPropsNames, pObj)
                    {
                        __String* pStr = static_cast<__String*>(pObj);
                        if (0 == pStr->compare(propertyName.c_str()))
                        {
                            bFound = true;
                            break;
                        }
                    }
                    setProp &= bFound;
                }
            }
            else if (isExtraProp && pNode == ccbReader->getAnimationManager()->getRootNode())
            {
                __Array *extraPropsNames = static_cast<__Array*>(pNode->getUserObject());
                if (! extraPropsNames)
                {
                    extraPropsNames = Array::create();
                    pNode->setUserObject(extraPropsNames);
                }
                
                extraPropsNames->addObject(String::create(propertyName));
            }*/
            
            switch(type)
            {
                case PropertyType::POSITION:
                {
                    PositionDescription position = parsePropTypePosition();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        ValueVector vec;
                        vec.push_back(Value(position.pos.x));
                        vec.push_back(Value(position.pos.y));
                        vec.push_back(Value((int)position.referenceCorner));
                        vec.push_back(Value((int)position.xUnits));
                        vec.push_back(Value((int)position.yUnits));
                        baseValues.emplace(propertyName, Value(vec));
                    }
                    loader->onHandlePropTypePosition(propertyName, isExtraProp, position);
                    break;
                }
                case PropertyType::POINT:
                {
                    Vec2 point = this->parsePropTypePoint();
                    loader->onHandlePropTypePoint(propertyName, isExtraProp, point);
                    break;
                }
                case PropertyType::POINT_LOCK:
                {
                    Point pointLock = this->parsePropTypePoint();
                    loader->onHandlePropTypePoint(propertyName, isExtraProp, pointLock);
                }
                case PropertyType::SIZE:
                {
                    SizeDescription size = parsePropTypeSize();
                    loader->onHandlePropTypeSize(propertyName, isExtraProp, size);
                    break;
                }
                case PropertyType::SCALE_LOCK:
                {
                    ScaleDescription scale = parsePropTypeScale();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        ValueVector baseValue;
                        baseValue.push_back(Value(scale.xScale));
                        baseValue.push_back(Value(scale.yScale));
                        baseValue.push_back(Value(scale.type));
                        baseValues.emplace(propertyName, Value(baseValue));
                    }
                    loader->onHandlePropTypeScale(propertyName, isExtraProp, scale);
                    break;
                }
                case PropertyType::FLOAT:
                {
                    float f = parsePropTypeFloat();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        baseValues.emplace(propertyName, Value(f));
                    }
                    loader->onHandlePropTypeFloat(propertyName, isExtraProp, f);
                    break;
                }
                case PropertyType::FLOAT_XY:
                {
                    Point xy = parsePropTypeFloatXY();
                    loader->onHandlePropTypeFloatXY(propertyName, isExtraProp, xy);
                    break;
                }
                    
                case PropertyType::DEGREES:
                {
                    float degrees = parsePropTypeDegrees();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        baseValues.emplace(propertyName, Value(degrees));
                    }
                    loader->onHandlePropTypeDegrees(propertyName, isExtraProp, degrees);
                    break;
                }
                case PropertyType::FLOAT_SCALE:
                {
                    FloatScaleDescription floatScale = parsePropTypeFloatScale();
                    loader->onHandlePropTypeFloatScale(propertyName, isExtraProp, floatScale);
                    break;
                }
                case PropertyType::INTEGER:
                {
                    int integer = parsePropTypeInteger();
                    loader->onHandlePropTypeInteger(propertyName, isExtraProp, integer);
                    break;
                }
                case PropertyType::INTEGER_LABELED:
                {
                    int integerLabeled = this->parsePropTypeInteger();
                    loader->onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, integerLabeled);
                    break;
                }
                case PropertyType::ANIMATION:
                {
                    int animation = this->parsePropTypeInteger();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        baseValues.emplace(propertyName, Value(animation));
                    }
                    loader->onHandlePropTypeAnimation(propertyName, isExtraProp, animation);
                    break;
                }
                case PropertyType::FLOAT_VAR:
                {
                    Vec2 floatVar = parsePropTypeFloatVar();
                    loader->onHandlePropTypeFloatVar(propertyName, isExtraProp, floatVar);
                    break;
                }
                case PropertyType::CHECK:
                {
                    bool check = parsePropTypeCheck();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        baseValues.emplace(propertyName, Value(check));
                    }
                    
                    loader->onHandlePropTypeCheck(propertyName, isExtraProp, check);
                    break;
                }
                case PropertyType::SPRITEFRAME:
                {
                    SpriteFrameDescription ccSpriteFrame = parsePropTypeSpriteFrame();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        objects.emplace(propertyName,ccSpriteFrame.spriteFrame.get());
                    }
                    loader->onHandlePropTypeSpriteFrame(propertyName, isExtraProp, ccSpriteFrame);
                    
                    break;
                }
                case PropertyType::TEXTURE:
                {
                    Texture2D * ccTexture2D = parsePropTypeTexture();
                    loader->onHandlePropTypeTexture(propertyName, isExtraProp, ccTexture2D);
                    break;
                }
                case PropertyType::COLOR3:
                {
                    Color3B color3B = parsePropTypeColor3();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        ValueMap colorMap;
                        colorMap["r"] = color3B.r;
                        colorMap["g"] = color3B.g;
                        colorMap["b"] = color3B.b;
                        colorMap["a"] = 255;
                        baseValues.emplace(propertyName, Value(colorMap));
                    }
                    loader->onHandlePropTypeColor3(propertyName, isExtraProp, color3B);
                    break;
                }
                case PropertyType::COLOR4F_VAR:
                {
                    std::pair<Color4F, Color4F> color4FVar = parsePropTypeColor4FVar();
                    loader->onHandlePropTypeColor4FVar(propertyName, isExtraProp, color4FVar);
                    break;
                }
                case PropertyType::FLIP:
                {
                    std::pair<bool, bool> flip = parsePropTypeFlip();
                    loader->onHandlePropTypeFlip(propertyName, isExtraProp, flip);
                    break;
                }
                case PropertyType::BLEND_MODE:
                {
                    BlendFunc blendFunc = this->parsePropTypeBlendFunc();
                    loader->onHandlePropTypeBlendFunc(propertyName, isExtraProp, blendFunc);
                    break;
                }
                case PropertyType::FNT_FILE:
                {
                    std::string fntFile = parsePropTypeFntFile();
                    loader->onHandlePropTypeFntFile(propertyName, isExtraProp, fntFile);
                    break;
                }
                case PropertyType::FONT_TTF:
                {
                    const std::string fontTTF = parsePropTypeFontTTF();
                    loader->onHandlePropTypeFontTTF(propertyName, isExtraProp, fontTTF);
                    break;
                }
                case PropertyType::STRING:
                {
                    const std::string &string = parsePropTypeText();
                    loader->onHandlePropTypeText(propertyName, isExtraProp, string);
                    break;
                }
                case PropertyType::TEXT:
                {
                    const std::string& text = parsePropTypeText();
                    loader->onHandlePropTypeText(propertyName, isExtraProp, text);
                    break;
                }
                case PropertyType::BLOCK:
                {
                    CallbackDescription blockData = parsePropTypeBlock();
                    loader->onHandlePropTypeClickCallback(propertyName, isExtraProp, blockData);
                    break;
                }
                case PropertyType::BLOCK_CONTROL:
                {
                    CallbackDescription blockData = parsePropTypeBlockControl();
                    loader->onHandlePropTypeTouchCallback(propertyName, isExtraProp, blockData);
                    break;
                }
                case PropertyType::CCB_FILE:
                {
                    NodeLoader * ccbNodeLoader = parsePropTypeCCBFile(library);
                    loader->onHandlePropTypeCCBFile(propertyName, isExtraProp, ccbNodeLoader);
                    break;
                }
                case PropertyType::COLOR4:
                {
                    Color4B color4B = parsePropTypeColor4();
                    if (animatedProperties.find(propertyName) != animatedProperties.end())
                    {
                        ValueMap colorMap;
                        colorMap["r"] = color4B.r;
                        colorMap["g"] = color4B.g;
                        colorMap["b"] = color4B.b;
                        colorMap["a"] = color4B.a;
                        baseValues.emplace(propertyName, Value(colorMap));
                    }
                    loader->onHandlePropTypeColor4(propertyName, isExtraProp, color4B);
                    break;
                }
                case PropertyType::SOUND_FILE:
                {
                    std::string sound = parsePropTypeSoundFile();
                    loader->onHandlePropTypeSoundFile(propertyName, isExtraProp, sound);
                    break;
                }
                case PropertyType::OFFSETS:
                {
                    Vec4 offsets = parsePropTypeOffsets();
                    loader->onHandlePropTypeOffsets(propertyName, isExtraProp, offsets);
                    break;
                }
                default:
                    ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(type);
                    break;
            }
        }
        loader->setBaseValues(baseValues);
        loader->setObjects(objects);
    }
    
    CCBKeyframe* readKeyframe(PropertyType type)
    {
        CCBKeyframe *keyframe = new (std::nothrow) CCBKeyframe();
        keyframe->autorelease();
        
        keyframe->setTime(readFloat());
        
        CCBKeyframe::EasingType easingType = static_cast<CCBKeyframe::EasingType>(readInt(false));
        float easingOpt = 0;
        Value value;
        
        if (easingType == CCBKeyframe::EasingType::CUBIC_IN
            || easingType == CCBKeyframe::EasingType::CUBIC_OUT
            || easingType == CCBKeyframe::EasingType::CUBIC_INOUT
            || easingType == CCBKeyframe::EasingType::ELASTIC_IN
            || easingType == CCBKeyframe::EasingType::ELASTIC_OUT
            || easingType == CCBKeyframe::EasingType::ELASTIC_INOUT)
        {
            easingOpt = readFloat();
        }
        keyframe->setEasingType(easingType);
        keyframe->setEasingOpt(easingOpt);
        
        if (type == PropertyType::CHECK)
        {
            value = readBool();
        }
        else if (type == PropertyType::FLOAT)
        {
            value = readFloat();
        }
        else if (type == PropertyType::BYTE)
        {
            value = readByte();
        }
        else if (type == PropertyType::COLOR3)
        {
            ValueMap colorMap;
            if(this->_version<6)
            {
                colorMap["r"] = readByte();
                colorMap["g"] = readByte();
                colorMap["b"] = readByte();
            }
            else
            {
                colorMap["r"] = static_cast<unsigned char>(readFloat()*255.0);
                colorMap["g"] = static_cast<unsigned char>(readFloat()*255.0);
                colorMap["b"] = static_cast<unsigned char>(readFloat()*255.0);
                colorMap["a"] = static_cast<unsigned char>(readFloat()*255.0);
            }
            
            value = colorMap;
        }
        else if (type == PropertyType::DEGREES)
        {
            value = readFloat();
        }
        else if (type == PropertyType::SCALE_LOCK || type == PropertyType::POSITION
                 || type == PropertyType::FLOAT_XY)
        {
            float a = readFloat();
            float b = readFloat();
            
            ValueVector ab;
            ab.push_back(Value(a));
            ab.push_back(Value(b));
            
            value = ab;
        }
        else if (type == PropertyType::SPRITEFRAME)
        {
            SpriteFrame* spriteFrame = nullptr;
            {
                std::string spriteFile = readCachedString();
                if (spriteFile.length() != 0)
                {
                    spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFile.c_str());
                    if(!spriteFrame)
                    {
                        Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(spriteFile.c_str());
                        if(texture != NULL) {
                            Rect bounds = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
                            spriteFrame = SpriteFrame::createWithTexture(texture, bounds);
                        }
                    }
                }
            }
            
            keyframe->setObject(spriteFrame);
        }
        else if (type == PropertyType::ANIMATION)
        {
            value = readInt(true);
        }
            
        
        if (!value.isNull())
            keyframe->setValue(value);
        
        return  keyframe;
    }
    
    NodeLoader * readNodeGraph(const NodeLoaderLibrary *library)
    {
        /* Read class name. */
        std::string className = this->readCachedString();
        
        // Read assignment type and name
        TargetType memberVarAssignmentType = static_cast<TargetType>(this->readInt(false));
        std::string memberVarAssignmentName;
        if(memberVarAssignmentType != TargetType::NONE)
        {
            memberVarAssignmentName = this->readCachedString();
        }
        
        NodeLoader *ccNodeLoader = library->createNodeLoader(className);
        
        if (! ccNodeLoader)
        {
            log("no corresponding node loader for %s", className.c_str());
            return nullptr;
        }
        
        if(!memberVarAssignmentName.empty())
        {
            ccNodeLoader->setMemberVarAssignment(memberVarAssignmentType, memberVarAssignmentName);
        }
        
        //Node *node = ccNodeLoader->loadNode(pParent, this);
        
        // Set root node
        /*if (! _animationManager->getRootNode())
        {
            _animationManager->setRootNode(node);
        }*/
        
        // Read animated properties
        std::unordered_map<int, Map<std::string, CCBSequenceProperty*>> seqs;
        std::set<std::string> animatedProps;
        
        int numSequence = readInt(false);
        for (int i = 0; i < numSequence; ++i)
        {
            int seqId = readInt(false);
            Map<std::string, CCBSequenceProperty*> seqNodeProps;
            
            int numProps = readInt(false);
            
            for (int j = 0; j < numProps; ++j)
            {
                CCBSequenceProperty *seqProp = new CCBSequenceProperty();
                seqProp->autorelease();
                
                seqProp->setName(readCachedString().c_str());
                seqProp->setType(readInt(false));
                animatedProps.insert(seqProp->getName());
                
                int numKeyframes = readInt(false);
                
                for (int k = 0; k < numKeyframes; ++k)
                {
                    CCBKeyframe *keyframe = readKeyframe(static_cast<PropertyType>(seqProp->getType()));
                    
                    seqProp->getKeyframes().pushBack(keyframe);
                }
                
                seqNodeProps.insert(seqProp->getName(), seqProp);
            }
            
            seqs[seqId] = seqNodeProps;
        }
        ccNodeLoader->setNodeSequences(seqs);
        
        if(this->_version >= 8)
        /*int uuid = */readInt(false);
        
        // Read properties
        parseProperties(ccNodeLoader, library, animatedProps);
        
        bool hasPhysicsBody = false;
        
        // Read physics
        if(this->_version >= 6)
            hasPhysicsBody = this->readBool();
        
        if (hasPhysicsBody)
        {
            // Read body shape
            int bodyShape = this->readInt(false);
            float cornerRadius = this->readFloat();
            
            //Point physicsOffset = Point(-node->getContentSize().width * node->getAnchorPoint().x, -node->getContentSize().height * node->getAnchorPoint().y);
            
            BasePhysicsBodyLoader *physicsLoader = nullptr;
            
            {
                if (bodyShape == 0)
                {
                    
                    int numPolygons = this->readInt(false);
                    
                    std::vector<std::vector<Point>> polygons(numPolygons);
                    
                    for(int j = 0; j < numPolygons; j++)
                    {
                        // Read points
                        int numPoints = this->readInt(false);
                        polygons[j].reserve(numPoints);
                        
                        for (int i = 0; i < numPoints; i++)
                        {
                            float x = this->readFloat();
                            float y = this->readFloat();
                            
                            polygons[j].push_back(Point(x, y));
                        }
                    }
                    
                    physicsLoader = ShapePolygonLoader::create(polygons);
                }
                else if (bodyShape == 1)
                {
                    float x = this->readFloat();
                    float y = this->readFloat();
                    
                    physicsLoader = ShapeCircleLoader::create(Vec2(x, y), cornerRadius);
                }
            }
            
            CCAssert(physicsLoader, "Unknown body shape");
            
            ccNodeLoader->setPhysicsLoader(physicsLoader);
            
            bool dynamic = readBool();
            bool affectedByGravity = readBool();
            bool allowsRotation = readBool();
            
            float density = readFloat();
            float friction = readFloat();
            float elasticity = readFloat();
            
            bool setMass = readBool();
            float mass = setMass?readFloat():0.0f;
            bool setMoment = readBool();
            float moment = setMoment?readFloat():0.0f;
            
            unsigned categoryBitmask = readInt(true);
            unsigned contactTestBitmask = readInt(true);
            unsigned collisionBitmask = readInt(true);
            
            Vec2 velocity;
            velocity.x = readFloat();
            velocity.y = readFloat();
            float velocityLimit = readFloat();
            float angularVelocity = readFloat();
            float angularVelocityLimit = readFloat();
            float linearDamping = readFloat();
            float angularDamping = readFloat();
            
            if(physicsLoader)
            {
                physicsLoader->dynamic = dynamic;
                physicsLoader->affectedByGravity = affectedByGravity;
                physicsLoader->allowsRotation = allowsRotation;
                physicsLoader->density = density;
                physicsLoader->friction = friction;
                physicsLoader->elasticity = elasticity;
                physicsLoader->setMass = setMass;
                physicsLoader->mass = mass;
                physicsLoader->setMoment = setMoment;
                physicsLoader->moment = moment;
                physicsLoader->categoryBitmask = categoryBitmask;
                physicsLoader->contactTestBitmask = contactTestBitmask;
                physicsLoader->collisionBitmask = collisionBitmask;
                physicsLoader->velocity = velocity;
                physicsLoader->velocityLimit = velocityLimit;
                physicsLoader->angularVelocity = angularVelocity;
                physicsLoader->angularVelocityLimit = angularVelocityLimit;
                physicsLoader->linearDamping = linearDamping;
                physicsLoader->angularDamping = angularDamping;
            }
            
        }
        
        /* Read and add children. */
        int numChildren = this->readInt(false);
        for(int i = 0; i < numChildren; i++)
        {
            NodeLoader * child = this->readNodeGraph(library);
            ccNodeLoader->addChild(child);
        }
        
        ccNodeLoader->onLoaded();
        
        return ccNodeLoader;
    }
    
private:
    const Data &_data;
    int _position;
    int _version;
    std::vector<std::string> _stringCache;
    std::string _rootPath;
    const CCBReaderParams *_params;
};
    
NodeLoader* ParseCCBXData(const Data &data, const NodeLoaderLibrary *library, const std::string &rootPath, const CCBReaderParams* params)
{
    return InternalReader::parse(data, library, rootPath, params);
}
NodeLoader* ParseCCBXFile(const std::string &filename, const NodeLoaderLibrary *library, const std::string &rootPath, const CCBReaderParams* params)
{
    Data data = FileUtils::getInstance()->getDataFromFile(filename);
    return InternalReader::parse(data, library, rootPath, params);
}
    
}

NS_CC_END
