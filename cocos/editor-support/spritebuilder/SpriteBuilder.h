#ifndef _CCB_CCBXREADER_H_
#define _CCB_CCBXREADER_H_

#include <string>
#include <vector>
#include <functional>

#include "2d/CCNode.h"
#include "base/CCValue.h"
#include "2d/CCSpriteFrame.h"
#include "base/CCData.h"
#include "base/CCMap.h"
#include "base/CCVector.h"
#include "CCBXAnimationManager.h"

NS_CC_BEGIN

namespace ui { enum class WidgetTouchEventType; }

namespace spritebuilder {
    
enum class SceneScaleType
{
    NONE,
    CUSTOM,
    MINSIZE,
    MAXSIZE,
    MINSCALE,
    MAXSCALE
};
    
enum class TargetType {
    NONE = 0,
    DOCUMENT_ROOT = 1,
    OWNER = 2,
    PARENT_OWNER = 3,
};

    
typedef std::function<void(Ref*, ui::WidgetTouchEventType)> ccReaderTouchCallback;
typedef std::function<void(Ref*)> ccReaderClickCallback;
typedef std::function<void(Node*)> ccReaderEventCallback;

class CC_DLL CCBXReaderOwner
{
public:
    virtual bool onAssignCCBMemberVariable(const std::string &memberVariableName, Node* node) { return false; }
    virtual bool onAssignCCBCustomProperty(const std::string &customPropertyName, const Value& value) { return false; }
    virtual ccReaderClickCallback onResolveCCBClickSelector(const std::string &selectorName, Node* node) { return ccReaderClickCallback(); }
    virtual ccReaderTouchCallback onResolveCCBTouchSelector(const std::string &selectorName, Node* node) { return ccReaderTouchCallback(); }
    virtual ccReaderEventCallback onResolveCCBCallFuncSelector(const std::string &selectorName, Node* node) { return ccReaderEventCallback(); };
    virtual void onNodeLoaded(Node* node) {}
    virtual ~CCBXReaderOwner() {}
};
    
class CC_DLL CCBXReaderOwnerHelper:public CCBXReaderOwner
{
public:
    
    CCBXReaderOwnerHelper(const std::function<bool(const std::string&, Node*)> &onAssignCCBMemberVariable = nullptr,
                          const std::function<bool(const std::string&, const Value&)> &onAssignCCBCustomProperty = nullptr,
                          const std::function<ccReaderClickCallback(const std::string&, Node*)> &onResolveCCBClickSelector = nullptr,
                          const std::function<ccReaderTouchCallback(const std::string&, Node*)> &onResolveCCBTouchSelector = nullptr,
                          const std::function<ccReaderEventCallback(const std::string&, Node*)> &onResolveCCBCallFuncSelector = nullptr)
        :onAssignCCBMemberVariableFunction(onAssignCCBMemberVariable)
        ,onAssignCCBCustomPropertyFunction(onAssignCCBCustomProperty)
        ,onResolveCCBClickSelectorFunction(onResolveCCBClickSelector)
        ,onResolveCCBTouchSelectorFunction(onResolveCCBTouchSelector)
        ,onResolveCCBCallFuncSelectorFunction(onResolveCCBCallFuncSelector){}
    
    virtual bool onAssignCCBMemberVariable(const std::string &memberVariableName, Node* node){
        if(onAssignCCBMemberVariableFunction)
            return onAssignCCBMemberVariableFunction(memberVariableName, node);
        else
            return false;
    }
    virtual bool onAssignCCBCustomProperty(const std::string &customPropertyName, const Value& value){
        if(onAssignCCBCustomPropertyFunction)
            return onAssignCCBCustomPropertyFunction(customPropertyName, value);
        else
            return false;
    }

    virtual ccReaderClickCallback onResolveCCBClickSelector(const std::string &selectorName, Node* node){
        if(onResolveCCBClickSelectorFunction)
            return onResolveCCBClickSelectorFunction(selectorName, node);
        else
            return ccReaderClickCallback();
    }

    virtual ccReaderTouchCallback onResolveCCBTouchSelector(const std::string &selectorName, Node* node){
        if(onResolveCCBTouchSelectorFunction)
            return onResolveCCBTouchSelectorFunction(selectorName, node);
        else
            return ccReaderTouchCallback();
    }

    virtual ccReaderEventCallback onResolveCCBCallFuncSelector(const std::string &selectorName, Node* node){
        if(onResolveCCBCallFuncSelectorFunction)
            return onResolveCCBCallFuncSelectorFunction(selectorName, node);
        else
            return ccReaderEventCallback();
    }

    std::function<bool(const std::string&, Node*)> onAssignCCBMemberVariableFunction;
    std::function<bool(const std::string&, const Value&)> onAssignCCBCustomPropertyFunction;
    std::function<ccReaderClickCallback(const std::string&, Node*)> onResolveCCBClickSelectorFunction;
    std::function<ccReaderTouchCallback(const std::string&, Node*)> onResolveCCBTouchSelectorFunction;
    std::function<ccReaderEventCallback(const std::string&, Node*)> onResolveCCBCallFuncSelectorFunction;
    
};
    
#define CCBX_MEMBERVARIABLEASSIGNER_GLUE(MEMBERVARIABLENAME, MEMBERVARIABLE) \
    if(cocos2d::spritebuilder::membervariableAssign(MEMBERVARIABLENAME, memberVariableName, MEMBERVARIABLE, node)) {\
        return true; \
    }
    
#define CCBX_MEMBERVARIABLEASSIGNER_GLUE_VECTOR(MEMBERVARIABLENAME, MEMBERVARIABLE) \
    if(cocos2d::spritebuilder::membervariableAssignVector(MEMBERVARIABLENAME, memberVariableName, MEMBERVARIABLE, node)) {\
        return true; \
    }
    
#define CCBX_MEMBERVARIABLEASSIGNER_GLUE_SIMPLE(MEMBERVARIABLENAME) \
    if(cocos2d::spritebuilder::membervariableAssign(#MEMBERVARIABLENAME, memberVariableName, _##MEMBERVARIABLENAME, node)) {\
        return true; \
    }
    
#define CCBX_MEMBERVARIABLEASSIGNER_GLUE_VECTOR_SIMPLE(MEMBERVARIABLENAME) \
    if(cocos2d::spritebuilder::membervariableAssignVector(#MEMBERVARIABLENAME, memberVariableName, _##MEMBERVARIABLENAME, node)) {\
        return true; \
    }

#define CCBX_SELECTORRESOLVER_CLICK_GLUE(TARGET, SELECTORNAME, METHOD) \
    if(selectorName == SELECTORNAME) { \
        return std::bind(&METHOD, TARGET, std::placeholders::_1); \
    }
    
#define CCBX_SELECTORRESOLVER_CLICK_GLUE_SIMPLE(SELECTORNAME) \
    if(selectorName == #SELECTORNAME) { \
        return [this](Ref* ref){ this->SELECTORNAME(ref); }; \
    }
    
#define CCBX_SELECTORRESOLVER_TOUCH_GLUE(TARGET, SELECTORNAME, METHOD) \
    if(selectorName == SELECTORNAME) { \
        return std::bind(&METHOD, TARGET, std::placeholders::_1, std::placeholders::_2); \
    }
    
#define CCBX_SELECTORRESOLVER_TOUCH_GLUE_SIMPLE(SELECTORNAME) \
    if(selectorName == #SELECTORNAME) { \
        return [this](Ref* ref, ui::WidgetTouchEventType type){ this->SELECTORNAME(ref, type); }; \
    }
    
#define CCBX_SELECTORRESOLVER_EVENT_GLUE(TARGET, SELECTORNAME, METHOD) \
    if(selectorName == SELECTORNAME) { \
        return std::bind(&METHOD, TARGET, std::placeholders::_1); \
    }
    
#define CCBX_SELECTORRESOLVER_EVENT_GLUE_SIMPLE(SELECTORNAME) \
    if(selectorName == #SELECTORNAME) { \
        return [this](Node* node){ this->SELECTORNAME(node); }; \
    }
    
template <class T>
inline bool membervariableAssign(const std::string &name, const std::string &memberVariableName, T *&variable, Node* node)
{
    if(memberVariableName != name)
        return false;
    T *result = dynamic_cast<T*>(node);
    if(result)
    {
        variable = result;
        return true;
    }
    return false;
}
    
template <class T>
inline bool membervariableAssignVector(const std::string &name, const std::string &memberVariableName, Vector<T*> &variable, Node* node)
{
    if(memberVariableName != name)
        return false;
    T *result = dynamic_cast<T*>(node);
    if(result)
    {
        variable.pushBack(result);
        return true;
    }
    return false;
}
    
template <class T>
inline bool membervariableAssignVector(const std::string &name, const std::string &memberVariableName, std::vector<T*> &variable, Node* node)
{
    if(memberVariableName != name)
        return false;
    T *result = dynamic_cast<T*>(node);
    if(result)
    {
        variable.push_back(result);
        return true;
    }
    return false;
}
    
class NodeLoader;
class NodeLoaderLibrary;
class CCBReaderParams;
    
typedef std::function<Node*(const Size &parentSize, float mainScale, float additionalScale)> CreateNodeFunction;

class CC_DLL CCBXReader : public Ref
{
public:
    
    static CCBXReader* createFromFile(const std::string &pCCBFileName, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr);
    static CCBXReader* createFromData(const Data &data, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr);
    
    Node *createNode(CCBXReaderOwner *pOwner, SceneScaleType scaleType = SceneScaleType::NONE, const CreateNodeFunction &createNodeFunction = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    Node *createNode(CCBXReaderOwner *pOwner, float mainScale, float additionalScale, const CreateNodeFunction &createNodeFunction = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    
    Node *createNode(CCBXReaderOwner *pOwner, const Size& parentSize, SceneScaleType scaleType = SceneScaleType::NONE, const CreateNodeFunction &createNodeFunction = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    Node *createNode(CCBXReaderOwner *pOwner, const Size& parentSize, const Size& screenSize, SceneScaleType scaleType = SceneScaleType::NONE, const CreateNodeFunction &createNodeFunction = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    Node *createNode(CCBXReaderOwner *pOwner, const Size& parentSize, float mainScale, float additionalScale, const CreateNodeFunction &createNodeFunction = nullptr, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    
    bool loadNode(Node * node, CCBXReaderOwner *pOwner, SceneScaleType scaleType = SceneScaleType::NONE, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    bool loadNode(Node * node, CCBXReaderOwner *pOwner, float mainScale, float additionalScale, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    
    bool loadNode(Node * node, CCBXReaderOwner *pOwner, const Size& parentSize, SceneScaleType scaleType = SceneScaleType::NONE, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    bool loadNode(Node * node, CCBXReaderOwner *pOwner, const Size& parentSize, const Size& screenSize, SceneScaleType scaleType = SceneScaleType::NONE, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    bool loadNode(Node * node, CCBXReaderOwner *pOwner, const Size& parentSize, float mainScale, float additionalScale, const std::function<void(cocos2d::Node*, AnimationCompleteType)> &defaultAnimationCallback = nullptr) const;
    
    static float getResolutionScale();
    static void setResolutionScale(float scale);
    
    static CCBXReader* addToCache(const std::string &pCCBFileName, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr);
    static bool removeFromCache(const std::string &pCCBFileName, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr);
    
    const std::string& getRootPath();
    
    CCBReaderParams* getParams() const;
    
    void calcScales(SceneScaleType scaleType, const Size &parentSize, float &mainScale, float &additionalScale) const;
    static void calcScales(SceneScaleType scaleType, const Size &parentSize, const Size &designResolution, float designScale, float &mainScale, float &additionalScale);
    
    static void setPlaySound(bool value);
    static bool getPlaySound();
    
    static CCBReaderParams* createParams(const std::string &rootPath);
    
CC_CONSTRUCTOR_ACCESS:
    CCBXReader(const std::string &rootPath, CCBReaderParams *params, NodeLoader *rootNodeLoader);
    virtual ~CCBXReader();
    
private:
    static Map<std::string,CCBReaderParams*> _paramsMap;
    static Map<std::string,CCBXReader*> _cache;
    static bool _playSound;
    std::string _rootPath;
    NodeLoader *_rootNodeLoader;
    CCBReaderParams *_params;
    static float _resolutionScale;
};

}

NS_CC_END

#endif
