#include "lua_cocos2dx_coco_studio_manual.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "CocoStudio.h"
#include "CCLuaEngine.h"

using namespace cocostudio;

class LuaArmatureWrapper:public Object
{
public:
    LuaArmatureWrapper();
    virtual ~LuaArmatureWrapper();
    
    virtual void addArmatureFileInfoAsyncCallback(float percent);
};

LuaArmatureWrapper::LuaArmatureWrapper()
{
    
}

LuaArmatureWrapper::~LuaArmatureWrapper()
{
    
}

void LuaArmatureWrapper::addArmatureFileInfoAsyncCallback(float percent)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
    
    if (0 != handler)
    {
        LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FILE_ASYNC , (void*)&percent);
        
        BasicScriptData data(this,(void*)&wrapperData);
        
        LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
    }
}

static int lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ArmatureAnimation* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureAnimation*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        Vector<LuaArmatureWrapper*> vec;
        vec.pushBack(wrapper);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
                
        self->setMovementEventCallFunc([=](Armature *armature, MovementEventType movementType, const std::string& movementID){
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)vec.at(0), ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
            
            if (0 != handler)
            {
                std::string strMovementID = movementID;
                LuaArmatureMovementEventData movementData(armature,(int)movementType, strMovementID);
                
                LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::MOVEMENT_EVENT , (void*)&movementData);
                
                BasicScriptData data((void*)vec.at(0),(void*)&wrapperData);
                
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
            }
        });
        return 0;
    }
    
    CCLOG("'setMovementEventCallFunc' function of ArmatureAnimation has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setMovementEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ArmatureAnimation* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureAnimation*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        Vector<LuaArmatureWrapper*> vec;
        vec.pushBack(wrapper);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);

        self->setFrameEventCallFunc([=](Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex){
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)vec.at(0), ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
            
            if (0 != handler)
            {
                std::string strFrameEventName(frameEventName);
                
                LuaArmatureFrameEventData frameData(bone,frameEventName,originFrameIndex,currentFrameIndex);
                
                LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FRAME_EVENT , (void*)&frameData);
                
                BasicScriptData data((void*)vec.at(0),(void*)&wrapperData);
                
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
            }
        });
        
        return 0;
    }
    
    
    CCLOG("'setFrameEventCallFunc' function of ArmatureAnimation has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setFrameEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static void extendArmatureAnimation(lua_State* L)
{
    lua_pushstring(L, "ArmatureAnimation");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setMovementEventCallFunc", lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc);
        tolua_function(L, "setFrameEventCallFunc", lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0 ;
    
    int argc = 0;
    ArmatureDataManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureDataManager*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err)  ||
            !toluafix_isfunction(L,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* configFilePath = tolua_tostring(L, 2, "");
        LUA_FUNCTION handler = (  toluafix_ref_function(L, 3, 0));
    
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->addArmatureFileInfoAsync(configFilePath, wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    else if (4 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if ( !tolua_isstring(L, 2, 0, &tolua_err)  ||
             !tolua_isstring(L, 3, 0, &tolua_err)  ||
             !tolua_isstring(L, 4, 0, &tolua_err)  ||
             !toluafix_isfunction(L,5,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif        
        const char* imagePath = tolua_tostring(L, 2, "");
        const char* plistPath = tolua_tostring(L, 3, "");
        const char* configFilePath = tolua_tostring(L, 4, "");
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,5,0));
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->addArmatureFileInfoAsync(imagePath, plistPath,configFilePath,wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    
    CCLOG("'addArmatureFileInfoAsync' function of ArmatureDataManager has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addArmatureFileInfoAsync'.",&tolua_err);
    return 0;
#endif
}

static void extendArmatureDataManager(lua_State* L)
{
    lua_pushstring(L, "ArmatureDataManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addArmatureFileInfoAsync", lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc);
    }
    lua_pop(L, 1);
}

int register_all_cocos2dx_coco_studio_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendArmatureAnimation(L);
    extendArmatureDataManager(L);
    
    return 0;
}