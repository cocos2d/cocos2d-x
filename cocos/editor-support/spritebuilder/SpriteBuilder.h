#ifndef _CCB_CCBXREADER_H_
#define _CCB_CCBXREADER_H_

#include <string>
#include <vector>
#include <functional>
#include <type_traits>

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
    virtual bool onAssignCCBMemberVariable(const std::string &memberVariableName, Node* node)
    {
        auto it = _assignVariableMap.find(memberVariableName);
        if (it != _assignVariableMap.end())
            return it->second(node);
        return false;
    }
    virtual bool onAssignCCBCustomProperty(const std::string &customPropertyName, const Value& value)
    {
        auto it = _assignCustomMap.find(customPropertyName);
        if (it != _assignCustomMap.end())
        {
            it->second = value;
            return true;
        }
        return false;
    }
    virtual ccReaderClickCallback onResolveCCBClickSelector(const std::string &selectorName, Node* node)
    {
        auto it = _clickCallbacksMap.find(selectorName);
        if (it != _clickCallbacksMap.end())
            return it->second;
        return ccReaderClickCallback();
    }
    virtual ccReaderTouchCallback onResolveCCBTouchSelector(const std::string &selectorName, Node* node)
    {
        auto it = _touchCallbacksMap.find(selectorName);
        if (it != _touchCallbacksMap.end())
            return it->second;
        return ccReaderTouchCallback();
    }
    virtual ccReaderEventCallback onResolveCCBCallFuncSelector(const std::string &selectorName, Node* node)
    {
        auto it = _eventCallbacksMap.find(selectorName);
        if (it != _eventCallbacksMap.end())
            return it->second;
        return ccReaderEventCallback();
    };
    virtual void onNodeLoaded(Node* node) {}
    virtual ~CCBXReaderOwner() {}
    
    template<class T> void addVariable(const std::string &memberVariableName, T* &node)
    {
        _assignVariableMap.emplace(memberVariableName, [&node](Node *result)
        {
           node = dynamic_cast<T*>(result);
           return node != nullptr;
        });
    }
    
    template<class T> void addVector(const std::string &memberVariableName, std::vector<T*> &vector)
    {
        _assignVariableMap.emplace(memberVariableName, [&vector](Node *result)
        {
            T*node = dynamic_cast<T*>(result);
            if(!node)
                return false;
            vector.push_back(node);
            return true;
        });
    }
    
    template<class T> void addVector(const std::string &memberVariableName, Vector<T*> &vector)
    {
        _assignVariableMap.emplace(memberVariableName, [&vector](Node *result)
        {
            T*node = dynamic_cast<T*>(result);
            if(!node)
                return false;
            vector.pushBack(node);
            return true;
        });
    }
    
    void addCustom(const std::string &customPropertyName, Value& value)
    {
        _assignCustomMap.emplace(customPropertyName, value);
    }
    
    void addClick(const std::string &selectorName, const ccReaderClickCallback &callback)
    {
        _clickCallbacksMap.emplace(selectorName, callback);
    }
    
    template<class T> void addClick(const std::string &selectorName, T* target, void (T::*callback)(Ref*))
    {
        _clickCallbacksMap.emplace(selectorName, std::bind(callback, target, std::placeholders::_1));
    }
    
    void addTouch(const std::string &selectorName, const ccReaderTouchCallback &callback)
    {
        _touchCallbacksMap.emplace(selectorName, callback);
    }
    
    template<class T> void addTouch(const std::string &selectorName, T* target, void (T::*callback)(Ref*, ui::WidgetTouchEventType))
    {
        _touchCallbacksMap.emplace(selectorName, std::bind(callback, target, std::placeholders::_1, std::placeholders::_2));
    }
    
    void addEvent(const std::string &selectorName, const ccReaderEventCallback &callback)
    {
        _eventCallbacksMap.emplace(selectorName, callback);
    }
    
    template<class T> void addEvent(const std::string &selectorName, T* target, void (T::*callback)(Node*))
    {
        _eventCallbacksMap.emplace(selectorName, std::bind(callback, target, std::placeholders::_1));
    }
    
private:
    std::map<std::string, ccReaderClickCallback> _clickCallbacksMap;
    std::map<std::string, ccReaderTouchCallback> _touchCallbacksMap;
    std::map<std::string, ccReaderEventCallback> _eventCallbacksMap;
    
    std::map<std::string, std::function<bool(Node*)>> _assignVariableMap;
    std::map<std::string, Value&> _assignCustomMap;
    
};
/** addVariable("MEMBERVARIABLENAME", _MEMBERVARIABLENAME); */
#define CCBX_SIMPLE_MEMBER_VARIABLE(MEMBERVARIABLENAME) addVariable(#MEMBERVARIABLENAME, _##MEMBERVARIABLENAME)

/** addVector("MEMBERVARIABLENAME", _MEMBERVARIABLENAME); */
#define CCBX_SIMPLE_MEMBER_VECTOR(MEMBERVARIABLENAME) addVector(#MEMBERVARIABLENAME, _##MEMBERVARIABLENAME)

/** addClick("SELECTORNAME", this, &TYPE_OF_THIS::SELECTORNAME); */
#define CCBX_SIMPLE_SELECTOR_CLICK(SELECTORNAME) addClick(#SELECTORNAME, this, &std::remove_reference<decltype(*this)>::type::SELECTORNAME)

/** addTouch("SELECTORNAME", this, &TYPE_OF_THIS::SELECTORNAME); */
#define CCBX_SIMPLE_SELECTOR_TOUCH(SELECTORNAME) addTouch(#SELECTORNAME, this, &std::remove_reference<decltype(*this)>::type::SELECTORNAME)

/** addEvent("SELECTORNAME", this, &TYPE_OF_THIS::SELECTORNAME); */
#define CCBX_SIMPLE_SELECTOR_EVENT(SELECTORNAME) addEvent(#SELECTORNAME, this, &std::remove_reference<decltype(*this)>::type::SELECTORNAME)
    
class NodeLoader;
class NodeLoaderLibrary;
class NodeLoaderCache;
class CCBReaderParams;
    
typedef std::function<Node*(const Size &parentSize, float mainScale, float additionalScale)> CreateNodeFunction;

class CC_DLL CCBXReader : public Ref
{
public:
    
    static CCBXReader* createFromFile(const std::string &pCCBFileName, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr, NodeLoaderCache *cache= nullptr);
    static CCBXReader* createFromData(const Data &data, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr, NodeLoaderCache *cache= nullptr);
    
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
    
    static CCBXReader* addToCache(const std::string &pCCBFileName, const std::string &rootPath = "", const NodeLoaderLibrary *library = nullptr, NodeLoaderCache *cache = nullptr);
    static bool removeFromCache(const std::string &pCCBFileName);
    static void clearCache();
    
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


/***********************************************
 *  DEPRECATED
 ***********************************************/
    
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
            return CCBXReaderOwner::onAssignCCBMemberVariable(memberVariableName, node);
    }
    virtual bool onAssignCCBCustomProperty(const std::string &customPropertyName, const Value& value){
        if(onAssignCCBCustomPropertyFunction)
            return onAssignCCBCustomPropertyFunction(customPropertyName, value);
        else
            return CCBXReaderOwner::onAssignCCBCustomProperty(customPropertyName, value);
    }

    virtual ccReaderClickCallback onResolveCCBClickSelector(const std::string &selectorName, Node* node){
        if(onResolveCCBClickSelectorFunction)
            return onResolveCCBClickSelectorFunction(selectorName, node);
        else
            return CCBXReaderOwner::onResolveCCBClickSelector(selectorName, node);
    }

    virtual ccReaderTouchCallback onResolveCCBTouchSelector(const std::string &selectorName, Node* node){
        if(onResolveCCBTouchSelectorFunction)
            return onResolveCCBTouchSelectorFunction(selectorName, node);
        else
            return CCBXReaderOwner::onResolveCCBTouchSelector(selectorName, node);
    }

    virtual ccReaderEventCallback onResolveCCBCallFuncSelector(const std::string &selectorName, Node* node){
        if(onResolveCCBCallFuncSelectorFunction)
            return onResolveCCBCallFuncSelectorFunction(selectorName, node);
        else
            return CCBXReaderOwner::onResolveCCBCallFuncSelector(selectorName, node);
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
        return [this](Ref* ref, cocos2d::ui::WidgetTouchEventType type){ this->SELECTORNAME(ref, type); }; \
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


}

NS_CC_END

#endif
