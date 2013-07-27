#include "CCBReader.h"

#include <algorithm>

#include "CCNodeLoader.h"
#include "CCNodeLoaderLibrary.h"
#include "CCNodeLoaderListener.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBSelectorResolver.h"
#include "CCBAnimationManager.h"
#include "CCBSequenceProperty.h"
#include "CCBKeyframe.h"
#include "CCBValue.h"

#include <ctype.h>

using namespace std;

NS_CC_EXT_BEGIN;

/*************************************************************************
 Implementation of CCBFile
 *************************************************************************/

CCBFile::CCBFile():_CCBFileNode(NULL) {}

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
: _data(NULL)
, _bytes(NULL)
, _currentByte(-1)
, _currentBit(-1)
, _owner(NULL)
, _actionManager(NULL)
, _actionManagers(NULL)
, _animatedProps(NULL)
, _ownerOutletNodes(NULL)
, _nodesWithAnimationManagers(NULL)
, _animationManagersForNodes(NULL)
, _ownerCallbackNodes(NULL)
, _hasScriptingOwner(false)
{
    this->_nodeLoaderLibrary = pNodeLoaderLibrary;
    this->_nodeLoaderLibrary->retain();
    this->_CCBMemberVariableAssigner = pCCBMemberVariableAssigner;
    this->_CCBSelectorResolver = pCCBSelectorResolver;
    this->_nodeLoaderListener = pNodeLoaderListener;
    init();
}

CCBReader::CCBReader(CCBReader * ccbReader) 
: _data(NULL)
, _bytes(NULL)
, _currentByte(-1)
, _currentBit(-1)
, _owner(NULL)
, _actionManager(NULL)
, _actionManagers(NULL)
, _animatedProps(NULL)
, _ownerOutletNodes(NULL)
, _nodesWithAnimationManagers(NULL)
, _animationManagersForNodes(NULL)
, _ownerCallbackNodes(NULL)
, _hasScriptingOwner(false)
{
    this->_loadedSpriteSheets = ccbReader->_loadedSpriteSheets;
    this->_nodeLoaderLibrary = ccbReader->_nodeLoaderLibrary;
    this->_nodeLoaderLibrary->retain();

    this->_CCBMemberVariableAssigner = ccbReader->_CCBMemberVariableAssigner;
    this->_CCBSelectorResolver = ccbReader->_CCBSelectorResolver;
    this->_nodeLoaderListener = ccbReader->_nodeLoaderListener;

    this->_ownerCallbackNames = ccbReader->_ownerCallbackNames;
    this->_ownerCallbackNodes = ccbReader->_ownerCallbackNodes;
    this->_ownerCallbackNodes->retain();
    this->_ownerOutletNames = ccbReader->_ownerOutletNames;
    this->_ownerOutletNodes = ccbReader->_ownerOutletNodes;
    this->_ownerOutletNodes->retain();
    
    this->_CCBRootPath = ccbReader->getCCBRootPath();
    
    init();
}

CCBReader::CCBReader()
: _data(NULL)
, _bytes(NULL)
, _currentByte(-1)
, _currentBit(-1)
, _owner(NULL)
, _actionManager(NULL)
, _actionManagers(NULL)
, _nodeLoaderLibrary(NULL)
, _nodeLoaderListener(NULL)
, _CCBMemberVariableAssigner(NULL)
, _CCBSelectorResolver(NULL)
, _nodesWithAnimationManagers(NULL)
, _animationManagersForNodes(NULL)
, _hasScriptingOwner(false)
{
    init();
}

CCBReader::~CCBReader() {
    CC_SAFE_RELEASE_NULL(_owner);
    CC_SAFE_RELEASE_NULL(_data);

    this->_nodeLoaderLibrary->release();

    CC_SAFE_RELEASE(_ownerOutletNodes);
    _ownerOutletNames.clear();
    CC_SAFE_RELEASE(_ownerCallbackNodes);
    _ownerCallbackNames.clear();

    // Clear string cache.

    this->_stringCache.clear();
    CC_SAFE_RELEASE(_nodesWithAnimationManagers);
    CC_SAFE_RELEASE(_animationManagersForNodes);

    setAnimationManager(NULL);
}

void CCBReader::setCCBRootPath(const char* ccbRootPath)
{
    CCASSERT(ccbRootPath != NULL, "");
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
    _actionManager->setRootContainerSize(Director::getInstance()->getWinSize());
    
    return true;
}

CCBAnimationManager* CCBReader::getAnimationManager()
{
    return _actionManager;
}

void CCBReader::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
    CC_SAFE_RELEASE(_actionManager);
    _actionManager = pAnimationManager;
    CC_SAFE_RETAIN(_actionManager);
}

Dictionary* CCBReader::getAnimationManagers()
{
    return _actionManagers;
}

void CCBReader::setAnimationManagers(Dictionary* x)
{
    _actionManagers = x;
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
    return this->readNodeGraphFromFile(pCCBFileName, NULL);
}

Node* CCBReader::readNodeGraphFromFile(const char* pCCBFileName, Object* pOwner) 
{
    return this->readNodeGraphFromFile(pCCBFileName, pOwner, Director::getInstance()->getWinSize());
}

Node* CCBReader::readNodeGraphFromFile(const char *pCCBFileName, Object *pOwner, const Size &parentSize)
{
    if (NULL == pCCBFileName || strlen(pCCBFileName) == 0)
    {
        return NULL;
    }

    std::string strCCBFileName(pCCBFileName);
    std::string strSuffix(".ccbi");
    // Add ccbi suffix
    if (!CCBReader::endsWith(strCCBFileName.c_str(), strSuffix.c_str()))
    {
        strCCBFileName += strSuffix;
    }

    std::string strPath = FileUtils::getInstance()->fullPathForFilename(strCCBFileName.c_str());
    unsigned long size = 0;

    unsigned char * pBytes = FileUtils::getInstance()->getFileData(strPath.c_str(), "rb", &size);
    Data *data = new Data(pBytes, size);
    CC_SAFE_DELETE_ARRAY(pBytes);

    Node *ret =  this->readNodeGraphFromData(data, pOwner, parentSize);
    
    data->release();
    
    return ret;
}

Node* CCBReader::readNodeGraphFromData(Data *pData, Object *pOwner, const Size &parentSize)
{
   _data = pData;
    CC_SAFE_RETAIN(_data);
    _bytes =_data->getBytes();
    _currentByte = 0;
    _currentBit = 0;
    _owner = pOwner;
    CC_SAFE_RETAIN(_owner);

    _actionManager->setRootContainerSize(parentSize);
    _actionManager->_owner = _owner;
    _ownerOutletNodes = new Array();
    _ownerCallbackNodes = new Array();
    
    Dictionary* animationManagers = Dictionary::create();
    Node *pNodeGraph = readFileWithCleanUp(true, animationManagers);
    
    if (pNodeGraph && _actionManager->getAutoPlaySequenceId() != -1 && !_jsControlled)
    {
        // Auto play animations
        _actionManager->runAnimationsForSequenceIdTweenDuration(_actionManager->getAutoPlaySequenceId(), 0);
    }
    // Assign actionManagers to userObject
    if(_jsControlled) {
        _nodesWithAnimationManagers = new Array();
        _animationManagersForNodes = new Array();
    }
    
    DictElement* pElement = NULL;
    CCDICT_FOREACH(animationManagers, pElement)
    {
        Node* pNode = (Node*)pElement->getIntKey();
        CCBAnimationManager* manager = static_cast<CCBAnimationManager*>(animationManagers->objectForKey((intptr_t)pNode));
        pNode->setUserObject(manager);

        if (_jsControlled)
        {
            _nodesWithAnimationManagers->addObject(pNode);
            _animationManagersForNodes->addObject(manager);
        }
    }
    
    return pNodeGraph;
}

Scene* CCBReader::createSceneWithNodeGraphFromFile(const char *pCCBFileName)
{
    return createSceneWithNodeGraphFromFile(pCCBFileName, NULL);
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

void CCBReader::cleanUpNodeGraph(Node *pNode)
{
    pNode->setUserObject(NULL);
    
    Object *pChild = NULL;
    CCARRAY_FOREACH(pNode->getChildren(), pChild)
    {
        cleanUpNodeGraph(static_cast<Node*>(pChild));
    }
}

Node* CCBReader::readFileWithCleanUp(bool bCleanUp, Dictionary* am)
{
    if (! readHeader())
    {
        return NULL;
    }
    
    if (! readStringCache())
    {
        return NULL;
    }
    
    if (! readSequences())
    {
        return NULL;
    }
    
    setAnimationManagers(am);

    Node *pNode = readNodeGraph(NULL);

    _actionManagers->setObject(_actionManager, intptr_t(pNode));

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
    if(this->_bytes == NULL) {
        return false;
    }

    /* Read magic bytes */
    int magicBytes = *((int*)(this->_bytes + this->_currentByte));
    this->_currentByte += 4;

    if(CC_SWAP_INT32_LITTLE_TO_HOST(magicBytes) != 'ccbi') {
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
    _actionManager->_jsControlled = _jsControlled;

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
            num = (int)(current / 2);
        } else {
            num = (int)(-current / 2);
        }
    } else {
        num = current - 1;
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
        return NULL;
    }

    Node *node = ccNodeLoader->loadNode(pParent, this);

    // Set root node
    if (! _actionManager->getRootNode())
    {
        _actionManager->setRootNode(node);
    }
    
    // Assign controller
    if(_jsControlled && node == _actionManager->getRootNode())
    {
        _actionManager->setDocumentControllerName(_jsControlledName);
    }

    // Read animated properties
    Dictionary *seqs = Dictionary::create();
    _animatedProps = new set<string>();
    
    int numSequence = readInt(false);
    for (int i = 0; i < numSequence; ++i)
    {
        int seqId = readInt(false);
        Dictionary *seqNodeProps = Dictionary::create();
        
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
                
                seqProp->getKeyframes()->addObject(keyframe);
            }
            
            seqNodeProps->setObject(seqProp, seqProp->getName());
        }
        
        seqs->setObject(seqNodeProps, seqId);
    }
    
    if (seqs->count() > 0)
    {
        _actionManager->addNode(node, seqs);
    }
    
    // Read properties
    ccNodeLoader->parseProperties(node, pParent, this);
    
    bool isCCBFileNode = (NULL == dynamic_cast<CCBFile*>(node)) ? false : true;
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
        
        _actionManager->moveAnimationsFromNode(ccbFileNode, embeddedNode);

        ccbFileNode->setCCBFileNode(NULL);
        
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
            Object * target = NULL;
            if(memberVarAssignmentType == TargetType::DOCUMENT_ROOT)
            {
                target = _actionManager->getRootNode();
            } 
            else if(memberVarAssignmentType == TargetType::OWNER)
            {
                target = this->_owner;
            }
            
            if(target != NULL)
            {
                CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                
                bool assigned = false;
                if (memberVarAssignmentType != TargetType::NONE)
                {
                    if(targetAsCCBMemberVariableAssigner != NULL)
                    {
                        assigned = targetAsCCBMemberVariableAssigner->onAssignCCBMemberVariable(target, memberVarAssignmentName.c_str(), node);
                    }
                    
                    if(!assigned && this->_CCBMemberVariableAssigner != NULL)
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
                _actionManager->addDocumentOutletName(memberVarAssignmentName);
                _actionManager->addDocumentOutletNode(node);
            }
            else
            {
                _ownerOutletNames.push_back(memberVarAssignmentName);
                _ownerOutletNodes->addObject(node);
            }
        }
    }
    
    // Assign custom properties.
    if (ccNodeLoader->getCustomProperties()->count() > 0)
    {
        bool customAssigned = false;
        
        if(!_jsControlled)
        {
            Object * target = node;
            if(target != NULL)
            {
                CCBMemberVariableAssigner * targetAsCCBMemberVariableAssigner = dynamic_cast<CCBMemberVariableAssigner *>(target);
                if(targetAsCCBMemberVariableAssigner != NULL) {
                    
                    Dictionary* pCustomPropeties = ccNodeLoader->getCustomProperties();
                    DictElement* pElement;
                    CCDICT_FOREACH(pCustomPropeties, pElement)
                    {
                        customAssigned = targetAsCCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), static_cast<CCBValue*>(pElement->getObject()));

                        if(!customAssigned && this->_CCBMemberVariableAssigner != NULL)
                        {
                            customAssigned = this->_CCBMemberVariableAssigner->onAssignCCBCustomProperty(target, pElement->getStrKey(), static_cast<CCBValue*>(pElement->getObject()));
                        }
                    }
                }
            }
        }
    }

#endif // CCB_ENABLE_JAVASCRIPT
    
    delete _animatedProps;
    _animatedProps = NULL;

    /* Read and add children. */
    int numChildren = this->readInt(false);
    for(int i = 0; i < numChildren; i++) {
        Node * child = this->readNodeGraph(node);
        node->addChild(child);
    }

    // FIX ISSUE #1860: "onNodeLoaded will be called twice if ccb was added as a CCBFile".
    // If it's a sub-ccb node, skip notification to NodeLoaderListener since it will be
    // notified at LINE #734: Node * child = this->readNodeGraph(node);
    if (!isCCBFileNode) {
        // Call onNodeLoaded
        NodeLoaderListener * nodeAsNodeLoaderListener = dynamic_cast<NodeLoaderListener *>(node);
        if(nodeAsNodeLoaderListener != NULL) {
            nodeAsNodeLoaderListener->onNodeLoaded(node, ccNodeLoader);
        } else if(this->_nodeLoaderListener != NULL) {
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
    Object *value = NULL;
    
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
        value = CCBValue::create(readBool());
    }
    else if (type == PropertyType::BYTE)
    {
        value = CCBValue::create(readByte());
    }
    else if (type == PropertyType::COLOR3)
    {
        int r = readByte();
        int g = readByte();
        int b = readByte();
        
        Color3B c = Color3B(r,g,b);
        value = Color3BWapper::create(c);
    }
    else if (type == PropertyType::DEGREES)
    {
        value = CCBValue::create(readFloat());
    }
    else if (type == PropertyType::SCALE_LOCK || type == PropertyType::POSITION
	     || type == PropertyType::FLOAT_XY)
    {
        float a = readFloat();
        float b = readFloat();
        
        value = Array::create(CCBValue::create(a),
                                CCBValue::create(b),
                                NULL);
    }
    else if (type == PropertyType::SPRITEFRAME)
    {
        std::string spriteSheet = readCachedString();
        std::string spriteFile = readCachedString();
        
        SpriteFrame* spriteFrame;

        if (spriteSheet.length() == 0)
        {
            spriteFile = _CCBRootPath + spriteFile;

            Texture2D *texture = TextureCache::getInstance()->addImage(spriteFile.c_str());
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
        value = spriteFrame;
    }
    
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
      
        Array* value = Array::create();
        value->addObject(String::create(callbackName));
        value->addObject(String::createWithFormat("%d", callbackType));
        
        CCBKeyframe* keyframe = new CCBKeyframe();
        keyframe->autorelease();
        
        keyframe->setTime(time);
        keyframe->setValue(value);
        
        if(_jsControlled) {
            string callbackIdentifier;
            _actionManager->getKeyframeCallbacks()->addObject(String::createWithFormat("%d:%s",callbackType, callbackName.c_str()));
        }
    
        channel->getKeyframes()->addObject(keyframe);
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
                
        Array* value = Array::create();
        
        value->addObject(String::create(soundFile));
        value->addObject(String::createWithFormat("%f", pitch));
        value->addObject(String::createWithFormat("%f", pan));
        value->addObject(String::createWithFormat("%f", gain));
        
        CCBKeyframe* keyframe = new CCBKeyframe();
        keyframe->setTime(time);
        keyframe->setValue(value);
        channel->getKeyframes()->addObject(keyframe);
        keyframe->release();
    }
    
    seq->setSoundChannel(channel);
    
    return true;
}


Node * CCBReader::readNodeGraph() {
    return this->readNodeGraph(NULL);
}

bool CCBReader::readSequences()
{
    Array *sequences = _actionManager->getSequences();
    
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
        
        sequences->addObject(seq);
    }
    
    _actionManager->setAutoPlaySequenceId(readInt(true));
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

bool CCBReader::isJSControlled() {
    return _jsControlled;
}

void CCBReader::addOwnerCallbackName(std::string name) {
    _ownerCallbackNames.push_back(name);
}

void CCBReader::addOwnerCallbackNode(Node *node) {
    _ownerCallbackNodes->addObject(node);
}


void CCBReader::addDocumentCallbackName(std::string name) {
    _actionManager->addDocumentCallbackName(name);
}

void CCBReader::addDocumentCallbackNode(Node *node) {
    _actionManager->addDocumentCallbackNode(node);
}


Array* CCBReader::getOwnerCallbackNames() {
    Array* pRet = Array::createWithCapacity(_ownerCallbackNames.size());
    std::vector<std::string>::iterator it = _ownerCallbackNames.begin();
    for (; it != _ownerCallbackNames.end(); ++it)
    {
        pRet->addObject(String::create(*it));
    }
    
    return pRet;
}

Array* CCBReader::getOwnerCallbackNodes() {
    return _ownerCallbackNodes;
}

Array* CCBReader::getOwnerOutletNames() {
    Array* pRet = Array::createWithCapacity(_ownerOutletNames.size());
    std::vector<std::string>::iterator it = _ownerOutletNames.begin();
    for (; it != _ownerOutletNames.end(); ++it)
    {
        pRet->addObject(String::create(*it));
    }
    return pRet;
}

Array* CCBReader::getOwnerOutletNodes() {
    return _ownerOutletNodes;
}

Array* CCBReader::getNodesWithAnimationManagers() {
    return _nodesWithAnimationManagers;
}

Array* CCBReader::getAnimationManagersForNodes() {
    return _animationManagersForNodes;
}

void CCBReader::addOwnerOutletName(std::string name)
{
    _ownerOutletNames.push_back(name);

}
void CCBReader::addOwnerOutletNode(Node *node)
{
    if (NULL != node)
        return;
    
    _ownerOutletNodes->addObject(node);
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

NS_CC_EXT_END;
