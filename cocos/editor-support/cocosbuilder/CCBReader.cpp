#include <ctype.h>
#include <algorithm>

#include "CCDirector.h"
#include "platform/CCFileUtils.h"
#include "CCScene.h"
#include "CCTextureCache.h"
#include "CCSpriteFrameCache.h"

#include "CCBReader.h"
#include "CCNodeLoader.h"
#include "CCNodeLoaderLibrary.h"
#include "CCNodeLoaderListener.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"
#include "CCBAnimationManager.h"
#include "CCBSequenceProperty.h"
#include "CCBKeyframe.h"



using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocosbuilder {;

/*************************************************************************
 Implementation of CCBFile
 *************************************************************************/

CCBFile::CCBFile():_CCBFileNode(nullptr) {}

CCBFile* CCBFile::create()
{
    CCBFile *ret = new CCBFile();
    
    if (ret)
    {
        ret->autorelease();
    }
    
    return ret;
}

Node* CCBFile::getCCBFileNode()
{
    return _CCBFileNode;
}

void CCBFile::setCCBFileNode(Node *pNode)
{
    CC_SAFE_RELEASE(_CCBFileNode);
    _CCBFileNode = pNode;
    CC_SAFE_RETAIN(_CCBFileNode);
}

/*************************************************************************
 Implementation of CCBReader
 *************************************************************************/

CCBReader::CCBReader(NodeLoaderLibrary * pNodeLoaderLibrary, CCBMemberVariableAssigner * pCCBMemberVariableAssigner, CCBSelectorResolver * pCCBSelectorResolver, NodeLoaderListener * pNodeLoaderListener) 
: _data(nullptr)
, _bytes(nullptr)
, _currentByte(-1)
, _currentBit(-1)
, _owner(nullptr)
, _animationManager(nullptr)
, _animatedProps(nullptr)
{
    this->_nodeLoaderLibrary = pNodeLoaderLibrary;
    this->_nodeLoaderLibrary->retain();
    this->_CCBMemberVariableAssigner = pCCBMemberVariableAssigner;
    this->_CCBSelectorResolver = pCCBSelectorResolver;
    this->_nodeLoaderListener = pNodeLoaderListener;
    init();
}

CCBReader::CCBReader(CCBReader * ccbReader) 
: _data(nullptr)
, _bytes(nullptr)
, _currentByte(-1)
, _currentBit(-1)
, _owner(nullptr)
, _animationManager(nullptr)
, _animatedProps(nullptr)
{
    this->_loadedSpriteSheets = ccbReader->_loadedSpriteSheets;
    this->_nodeLoaderLibrary = ccbReader->_nodeLoaderLibrary;
    this->_nodeLoaderLibrary->retain();

    this->_CCBMemberVariableAssigner = ccbReader->_CCBMemberVariableAssigner;
    this->_CCBSelectorResolver = ccbReader->_CCBSelectorResolver;
    this->_nodeLoaderListener = ccbReader->_nodeLoaderListener;
    
    this->_CCBRootPath = ccbReader->getCCBRootPath();
    
    init();
}

CCBReader::CCBReader()
: _data(nullptr)
, _bytes(nullptr)
, _currentByte(-1)
, _currentBit(-1)
, _owner(nullptr)
, _animationManager(nullptr)
, _nodeLoaderLibrary(nullptr)
, _nodeLoaderListener(nullptr)
, _CCBMemberVariableAssigner(nullptr)
, _CCBSelectorResolver(nullptr)
{
    init();
}

CCBReader::~CCBReader()
{
    CC_SAFE_RELEASE_NULL(_owner);

    this->_nodeLoaderLibrary->release();

    _ownerOutletNames.clear();
    _ownerCallbackNames.clear();
    
    // Clear string cache.
    this->_stringCache.clear();

    setAnimationManager(nullptr);
}

void CCBReader::setCCBRootPath(const char* ccbRootPath)
{
    CCASSERT(ccbRootPath != nullptr, "");
    _CCBRootPath = ccbRootPath;
}

const std::string& CCBReader::getCCBRootPath() const
{
    return _CCBRootPath;
}

bool CCBReader::init()
{
    // Setup action manager
    CCBAnimationManager *pActionManager = new CCBAnimationManager();
    setAnimationManager(pActionManager);
    pActionManager->release();
    
    // Setup resolution scale and container size
    _animationManager->setRootContainerSize(Director::getInstance()->getWinSize());
    
    return true;
}

CCBAnimationManager* CCBReader::getAnimationManager()
{
    return _animationManager;
}

void CCBReader::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE(_animationManager);
    _animationManager = pAnimationManager;
    CC_SAFE_RETAIN(_animationManager);
}

CCBReader::CCBAnimationManagerMapPtr CCBReader::getAnimationManagers()
{
    return _animationManagers;
}

void CCBReader::setAnimationManagers(CCBAnimationManagerMapPtr x)
{
    _animationManagers = x;
}

CCBMemberVariableAssigner * CCBReader::getCCBMemberVariableAssigner() {
    return this->_CCBMemberVariableAssigner;
}

CCBSelectorResolver * CCBReader::getCCBSelectorResolver() {
    return this->_CCBSelectorResolver;
}

set<string>* CCBReader::getAnimatedProperties()
{
    return _animatedProps;
}

set<string>& CCBReader::getLoadedSpriteSheet()
{
    return _loadedSpriteSheets;
}

Object* CCBReader::getOwner()
{
    return _owner;
}

Node* CCBReader::readNodeGraphFromFile(const char *pCCBFileName)
{
    return this->readNodeGraphFromFile(pCCBFileName, nullptr);
}

Node* CCBReader::readNodeGraphFromFile(const char* pCCBFileName, Object* pOwner) 
{
    return this->readNodeGraphFromFile(pCCBFileName, pOwner, Director::getInstance()->getWinSize());
}

Node* CCBReader::readNodeGraphFromFile(const char *pCCBFileName, Object *pOwner, const Size &parentSize)
{
    if (nullptr == pCCBFileName || strlen(pCCBFileName) == 0)
    {
        return nullptr;
    }

    std::string strCCBFileName(pCCBFileName);
    std::string strSuffix(".ccbi");
    // Add ccbi suffix
    if (!CCBReader::endsWith(strCCBFileName.c_str(), strSuffix.c_str()))
    {
        strCCBFileName += strSuffix;
    }

    std::string strPath = FileUtils::getInstance()->fullPathForFilename(strCCBFileName.c_str());

    auto dataPtr = std::make_shared<Data>(FileUtils::getInstance()->getDataFromFile(strPath));
    
    Node *ret =  this->readNodeGraphFromData(dataPtr, pOwner, parentSize);
    
    return ret;
}

Node* CCBReader::readNodeGraphFromData(std::shared_ptr<cocos2d::Data> data, Object *pOwner, const Size &parentSize)
{
    _data = data;
    _bytes =_data->getBytes();
    _currentByte = 0;
    _currentBit = 0;
    _owner = pOwner;
    CC_SAFE_RETAIN(_owner);

    _animationManager->setRootContainerSize(parentSize);
    _animationManager->_owner = _owner;
    
    Node *pNodeGraph = readFileWithCleanUp(true, std::make_shared<CCBAnimationManagerMap>());
    
    if (pNodeGraph && _animationManager->getAutoPlaySequenceId() != -1)
    {
        // Auto play animations
        _animationManager->runAnimationsForSequenceIdTweenDuration(_animationManager->getAutoPlaySequenceId(), 0);
    }
    
    // Assign actionManagers to userObject
    for (auto iter = _animationManagers->begin(); iter != _animationManagers->end(); ++iter)
    {
        Node* pNode = iter->first;
        CCBAnimationManager* manager = iter->second;
        
        pNode->setUserObject(manager);

        if (_jsControlled)
        {
            _nodesWithAnimationManagers.pushBack(pNode);
            _animationManagersForNodes.pushBack(manager);
        }
    }
    
    return pNodeGraph;
}

Scene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName)
{
    return createSceneWithNodeGraphFromFile(pCCBFileName, nullptr);
}

Scene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, Object *pOwner)
{
    return createSceneWithNodeGraphFromFile(pCCBFileName, pOwner, Director::getInstance()->getWinSize());
}

Scene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName, Object *pOwner, const Size &parentSize)
{
    Node *pNode = readNodeGraphFromFile(pCCBFileName, pOwner, parentSize);
    Scene *pScene = Scene::create();
    pScene->addChild(pNode);
    
    return pScene;
}

void CCBReader::cleanUpNodeGraph(Node *node)
{
    node->setUserObject(nullptr);
    
    auto& children = node->getChildren();
    for(const auto &obj : children) {
        cleanUpNodeGraph(obj);
    }
}

Node* CCBReader::readFileWithCleanUp(bool bCleanUp, CCBAnimationManagerMapPtr am)
{
    if (! readHeader())
    {
        return nullptr;
    }
    
    if (! readStringCache())
    {
        return nullptr;
    }
    
    if (! readSequences())
    {
        return nullptr;
    }
    
    setAnimationManagers(am);

    Node *pNode = readNodeGraph(nullptr);

    _animationManagers->insert(pNode, _animationManager);

    if (bCleanUp)
    {
        cleanUpNodeGraph(pNode);
    }
    
    return pNode;
}

bool CCBReader::readStringCache() {
    int numStrings = this->readInt(false);

    for(int i = 0; i < numStrings; i++) {
        this->_stringCache.push_back(this->readUTF8());
    }

    return true;
}

bool CCBReader::readHeader()
{
    /* If no bytes loaded, don't crash about it. */
    if(this->_bytes == nullptr) {
        return false;
    }

    /* Read magic bytes */
    int magicBytes = *((int*)(this->_bytes + this->_currentByte));
    this->_currentByte += 4;

    if(CC_SWAP_INT32_BIG_TO_HOST(magicBytes) != (*reinterpret_cast<const int*>("ccbi"))) {
        return false; 
    }

    /* Read version. */
    int version = this->readInt(false);
    if(version != CCB_VERSION) {
        log("WARNING! Incompatible ccbi file version (file: %d reader: %d)", version, CCB_VERSION);
        return false;
    }

    // Read JS check
    _jsControlled = this->readBool();
    _animationManager->_jsControlled = _jsControlled;

    return true;
}

unsigned char CCBReader::readByte()
{
    unsigned char byte = this->_bytes[this->_currentByte];
    this->_currentByte++;
    return byte;
}

bool CCBReader::readBool()
{
    return 0 == this->readByte() ? false : true;
}

std::string CCBReader::readUTF8()
{
    std::string ret;

    int b0 = this->readByte();
    int b1 = this->readByte();

    int numBytes = b0 << 8 | b1;

    char* pStr = (char*)malloc(numBytes+1);
    memcpy(pStr, _bytes+_currentByte, numBytes);
    pStr[numBytes] = '\0';
    ret = pStr;
    free(pStr);

    _currentByte += numBytes;

    return ret;
}

bool CCBReader::getBit() {
    bool bit;
    unsigned char byte = *(this->_bytes + this->_currentByte);
    if(byte & (1 << this->_currentBit)) {
        bit = true;
    } else {
        bit = false;
    }

    this->_currentBit++;

    if(this->_currentBit >= 8) {
        this->_currentBit = 0;
        this->_currentByte++;
    }

    return bit;
}

void CCBReader::alignBits() {
    if(this->_currentBit) {
        this->_currentBit = 0;
        this->_currentByte++;
    }
}

int CCBReader::readInt(bool pSigned) {
    // Read encoded int
    int numBits = 0;
    while(!this->getBit()) {
        numBits++;
    }
    
    long long current = 0;
    for(int a = numBits - 1; a >= 0; a--) {
        if(this->getBit()) {
            current |= 1LL << a;
        }
    }
    current |= 1LL << numBits;
    
    int num;
    if(pSigned) {
        int s = current % 2;
        if(s) {
            num = static_cast<int>(current / 2);
        } else {
            num = static_cast<int>(-current / 2);
        }
    } else {
        num = static_cast<int>(current - 1);
    }
    
    this->alignBits();
    
    return num;
}


float CCBReader::readFloat()
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
                unsigned char* pF = (this->_bytes + this->_currentByte);
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
                
                this->_currentByte += sizeof(float);
                return f;
            }
    }
}

std::string CCBReader::readCachedString()
{
    int n = this->readInt(false);
    return this->_stringCache[n];
}

Node * CCBReader::readNodeGraph(Node * pParent)
{
    /* Read class name. */
    std::string className = this->readCachedString();

    std::string _jsControlledName;
    
    if(_jsControlled) {
        _jsControlledName = this->readCachedString();
    }
    
    // Read assignment type and name
    TargetType memberVarAssignmentType = static_cast<TargetType>(this->readInt(false));
    std::string memberVarAssignmentName;
    if(memberVarAssignmentType != TargetType::NONE)
    {
        memberVarAssignmentName = this->readCachedString();
    }
    
    NodeLoader *ccNodeLoader = this->_nodeLoaderLibrary->getNodeLoader(className.c_str());
     
    if (! ccNodeLoader)
    {
        log("no corresponding node loader for %s", className.c_str());
        return nullptr;
    }

    Node *node = ccNodeLoader->loadNode(pParent, this);

    // Set root node
    if (! _animationManager->getRootNode())
    {
        _animationManager->setRootNode(node);
    }
    
    // Assign controller
    if(_jsControlled && node == _animationManager->getRootNode())
    {
        _animationManager->setDocumentControllerName(_jsControlledName);
    }

    // Read animated properties
    std::unordered_map<int, Map<std::string, CCBSequenceProperty*>> seqs;
    _animatedProps = new set<string>();
    
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
            _animatedProps->insert(seqProp->getName());
            
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
    
    if (!seqs.empty())
    {
        _animationManager->addNode(node, seqs);
    }
    
    // Read properties
    ccNodeLoader->parseProperties(node, pParent, this);
    
    bool isCCBFileNode = (nullptr == dynamic_cast<CCBFile*>(node)) ? false : true;
    // Handle sub ccb files (remove middle node)
    if (isCCBFileNode)
    {
        CCBFile *ccbFileNode = (CCBFile*)node;
        
        Node *embeddedNode = ccbFileNode->getCCBFileNode();
        embeddedNode->setPosition(ccbFileNode->getPosition());
        embeddedNode->setRotation(ccbFileNode->getRotation());
        embeddedNode->setScaleX(ccbFileNode->getScaleX());
        embeddedNode->setScaleY(ccbFileNode->getScaleY());
        embeddedNode->setTag(ccbFileNode->getTag());
        embeddedNode->setVisible(true);
        //embeddedNode->ignoreAnchorPointForPosition(ccbFileNode->isIgnoreAnchorPointForPosition());
        
        _animationManager->moveAnimationsFromNode(ccbFileNode, embeddedNode);

        ccbFileNode->setCCBFileNode(nullptr);
        
        node = embeddedNode;
    }

#ifdef CCB_ENABLE_JAVASCRIPT
    /*
     if (memberVarAssignmentType && memberVarAssignmentName && ![memberVarAssignmentName isEqualToString:@""])
     {
     [[JSCocoa sharedController] setObject:node withName:memberVarAssignmentName];
     }*/
#else
    if (memberVarAssignmentType != TargetType::NONE)
    {
        if(!_jsControlled)
        {
            Object * target = nullptr;
            if(memberVarAssignmentType == TargetType::DOCUMENT_ROOT)
            {
                target = _animationManager->getRootNode();
            } 
            else if(memberVarAssignmentType == TargetType::OWNER)
            {
                target = this->_owner;
            }
            
            if(target != nullptr)
            {
                CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                
                bool assigned = false;
                if (memberVarAssignmentType != TargetType::NONE)
                {
                    if(targetAsCCBMemberVariableAssigner != nullptr)
                    {
                        assigned = targetAsCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                    }
                    
                    if(!assigned && this->_CCBMemberVariableAssigner != nullptr)
                    {
                        assigned = this->_CCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                    }
                }
            }
        }
        else
        {
            if(memberVarAssignmentType == TargetType::DOCUMENT_ROOT)
            {
                _animationManager->addDocumentOutletName(memberVarAssignmentName);
                _animationManager->addDocumentOutletNode(node);
            }
            else
            {
                _ownerOutletNames.push_back(memberVarAssignmentName);
                _ownerOutletNodes.pushBack(node);
            }
        }
    }
    
    // Assign custom properties.
    if (!ccNodeLoader->getCustomProperties().empty())
    {
        bool customAssigned = false;
        
        if(!_jsControlled)
        {
            Object * target = node;
            if(target != nullptr)
            {
                CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                if(targetAsCCBMemberVariableAssigner != nullptr)
                {
                    auto& customPropeties = ccNodeLoader->getCustomProperties();
                    
                    for (auto iter = customPropeties.begin(); iter != customPropeties.end(); ++iter)
                    {
                        customAssigned = targetAsCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, iter->first.c_str(), iter->second);

                        if(!customAssigned && this->_CCBMemberVariableAssigner != nullptr)
                        {
                            customAssigned = this->_CCBMemberVariableAssigner->onAssignCCBCustomProperty(target, iter->first.c_str(), iter->second);
                        }
                    }
                }
            }
        }
    }

#endif // CCB_ENABLE_JAVASCRIPT
    
    delete _animatedProps;
    _animatedProps = nullptr;

    /* Read and add children. */
    int numChildren = this->readInt(false);
    for(int i = 0; i < numChildren; i++)
    {
        Node * child = this->readNodeGraph(node);
        node->addChild(child);
    }

    // FIX ISSUE #1860: "onNodeLoaded will be called twice if ccb was added as a CCBFile".
    // If it's a sub-ccb node, skip notification to NodeLoaderListener since it will be
    // notified at LINE #734: Node * child = this->readNodeGraph(node);
    if (!isCCBFileNode)
    {
        // Call onNodeLoaded
        NodeLoaderListener * nodeAsNodeLoaderListener = dynamic_cast<NodeLoaderListener *>(node);
        if(nodeAsNodeLoaderListener != nullptr)
        {
            nodeAsNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
        }
        else if(this->_nodeLoaderListener != nullptr)
        {
            this->_nodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
        }
    }
    return node;
}

CCBKeyframe* CCBReader::readKeyframe(PropertyType type)
{
    CCBKeyframe *keyframe = new CCBKeyframe();
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
    else if (type == PropertyType::BYTE)
    {
        value = readByte();
    }
    else if (type == PropertyType::COLOR3)
    {
        unsigned char r = readByte();
        unsigned char g = readByte();
        unsigned char b = readByte();
        
        ValueMap colorMap;
        colorMap["r"] = r;
        colorMap["g"] = g;
        colorMap["b"] = b;
        
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
        std::string spriteSheet = readCachedString();
        std::string spriteFile = readCachedString();
        
        SpriteFrame* spriteFrame;

        if (spriteSheet.length() == 0)
        {
            spriteFile = _CCBRootPath + spriteFile;

            Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(spriteFile.c_str());
            Rect bounds = Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height);
            
            spriteFrame = SpriteFrame::createWithTexture(texture, bounds);
        }
        else
        {
            spriteSheet = _CCBRootPath + spriteSheet;
            SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
            
            // Load the sprite sheet only if it is not loaded            
            if (_loadedSpriteSheets.find(spriteSheet) == _loadedSpriteSheets.end())
            {
                frameCache->addSpriteFramesWithFile(spriteSheet.c_str());
                _loadedSpriteSheets.insert(spriteSheet);
            }
            
            spriteFrame = frameCache->getSpriteFrameByName(spriteFile.c_str());
        }
        
        keyframe->setObject(spriteFrame);
    }
    
    if (!value.isNull())
        keyframe->setValue(value);
    
    return  keyframe;
}


bool CCBReader::readCallbackKeyframesForSeq(CCBSequence* seq)
{
    int numKeyframes = readInt(false);
    if(!numKeyframes) return true;
    
    CCBSequenceProperty* channel = new CCBSequenceProperty();
    channel->autorelease();

    for(int i = 0; i < numKeyframes; ++i) {
      
        float time = readFloat();
        std::string callbackName = readCachedString();
      
        int callbackType = readInt(false);
      
        ValueVector valueVector;
        valueVector.push_back(Value(callbackName));
        valueVector.push_back(Value(callbackType));
        
        CCBKeyframe* keyframe = new CCBKeyframe();
        keyframe->autorelease();
        
        keyframe->setTime(time);
        keyframe->setValue(Value(valueVector));
        
        if(_jsControlled) {
            std::stringstream callbackIdentifier;
            callbackIdentifier << callbackType;
            callbackIdentifier << ":" + callbackName;
            _animationManager->getKeyframeCallbacks().push_back(Value(callbackIdentifier.str()));
        }
    
        channel->getKeyframes().pushBack(keyframe);
    }
    
    seq->setCallbackChannel(channel);
    
    return true;
}

bool CCBReader::readSoundKeyframesForSeq(CCBSequence* seq) {
    int numKeyframes = readInt(false);
    if(!numKeyframes) return true;
    
    CCBSequenceProperty* channel = new CCBSequenceProperty();
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
        
        CCBKeyframe* keyframe = new CCBKeyframe();
        keyframe->setTime(time);
        keyframe->setValue(Value(vec));
        channel->getKeyframes().pushBack(keyframe);
        keyframe->release();
    }
    
    seq->setSoundChannel(channel);
    
    return true;
}


Node * CCBReader::readNodeGraph() {
    return this->readNodeGraph(nullptr);
}

bool CCBReader::readSequences()
{
    auto& sequences = _animationManager->getSequences();
    
    int numSeqs = readInt(false);
    
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
    
    _animationManager->setAutoPlaySequenceId(readInt(true));
    return true;
}

std::string CCBReader::lastPathComponent(const char* pPath) {
    std::string path(pPath);
    size_t slashPos = path.find_last_of("/");
    if(slashPos != std::string::npos) {
        return path.substr(slashPos + 1, path.length() - slashPos);
    }
    return path;
}

std::string CCBReader::deletePathExtension(const char* pPath) {
    std::string path(pPath);
    size_t dotPos = path.find_last_of(".");
    if(dotPos != std::string::npos) {
        return path.substr(0, dotPos);
    }
    return path;
}

std::string CCBReader::toLowerCase(const char* pString) {
    std::string copy(pString);
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return copy;
}

bool CCBReader::endsWith(const char* pString, const char* pEnding) {
    std::string string(pString);
    std::string ending(pEnding);
    if(string.length() >= ending.length()) {
        return (string.compare(string.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return false;
    }
}

bool CCBReader::isJSControlled()
{
    return _jsControlled;
}

void CCBReader::addOwnerCallbackName(const std::string& name)
{
    _ownerCallbackNames.push_back(name);
}

void CCBReader::addOwnerCallbackNode(Node *node)
{
    _ownerCallbackNodes.pushBack(node);
}

void CCBReader::addOwnerCallbackControlEvents(Control::EventType type)
{
    _ownerOwnerCallbackControlEvents.push_back(Value((int)type));
}

void CCBReader::addDocumentCallbackName(const std::string& name)
{
    _animationManager->addDocumentCallbackName(name);
}

void CCBReader::addDocumentCallbackNode(Node *node)
{
    _animationManager->addDocumentCallbackNode(node);
}

void CCBReader::addDocumentCallbackControlEvents(Control::EventType eventType)
{
    _animationManager->addDocumentCallbackControlEvents(eventType);
}

ValueVector CCBReader::getOwnerCallbackNames()
{
    ValueVector ret;
    ret.reserve(_ownerCallbackNames.size());
    
    std::vector<std::string>::iterator it = _ownerCallbackNames.begin();
    for (; it != _ownerCallbackNames.end(); ++it)
    {
        ret.push_back(Value(*it));
    }
    
    return ret;
}

Vector<Node*>& CCBReader::getOwnerCallbackNodes()
{
    return _ownerCallbackNodes;
}

ValueVector& CCBReader::getOwnerCallbackControlEvents()
{
    return _ownerOwnerCallbackControlEvents;
}

ValueVector CCBReader::getOwnerOutletNames()
{
    ValueVector ret;
    ret.reserve(_ownerOutletNames.size());
    std::vector<std::string>::iterator it = _ownerOutletNames.begin();
    for (; it != _ownerOutletNames.end(); ++it)
    {
        ret.push_back(Value(*it));
    }
    return ret;
}

Vector<Node*>& CCBReader::getOwnerOutletNodes()
{
    return _ownerOutletNodes;
}

Vector<Node*>& CCBReader::getNodesWithAnimationManagers()
{
    return _nodesWithAnimationManagers;
}

Vector<CCBAnimationManager*>& CCBReader::getAnimationManagersForNodes()
{
    return _animationManagersForNodes;
}

void CCBReader::addOwnerOutletName(std::string name)
{
    _ownerOutletNames.push_back(name);
}

void CCBReader::addOwnerOutletNode(Node *node)
{
    if (nullptr == node)
        return;
    
    _ownerOutletNodes.pushBack(node);
}

/************************************************************************
 Static functions
 ************************************************************************/

static float __ccbResolutionScale = 1.0f;

float CCBReader::getResolutionScale()
{
    return __ccbResolutionScale;
}

void CCBReader::setResolutionScale(float scale)
{
    __ccbResolutionScale = scale;
}

};
