#include "CCLuaSrcipt.h"
#if CC_ENABLE_LUA

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}


#include "tolua++.h"
#include "CCTouch.h"
#include "CCNode.h"
#include "CCObject.h"
#include "LuaCocos2d.h"
namespace cocos2d
{

CCLuaScriptModule* CCLuaScriptModule::s_luaScriptModule = NULL;

CCLuaScriptModule* CCLuaScriptModule::sharedLuaScriptModule(void)
{
	if (s_luaScriptModule == NULL)
	{
		s_luaScriptModule = new CCLuaScriptModule();
	}
	return s_luaScriptModule;
}
void CCLuaScriptModule::purgeSharedLuaScriptModule()
{
	s_luaScriptModule->release();
	s_luaScriptModule = NULL;
}

/*************************************************************************
	Constructor (creates Lua state)
*************************************************************************/
CCLuaScriptModule::CCLuaScriptModule()
{
	
	d_ownsState = true;
	d_state = lua_open();
	luaL_openlibs(d_state);
	int nOpen = tolua_Cocos2d_open(d_state);
	// init all standard libraries
	/*luaopen_base(d_state);
	luaopen_io(d_state);
	luaopen_string(d_state);
	luaopen_table(d_state);
	luaopen_math(d_state);
	*/
	//luaopen_debug(d_state);
}


/*************************************************************************
	Constructor (uses given Lua state)
*************************************************************************/
CCLuaScriptModule::CCLuaScriptModule(lua_State* state)
{
	// just use the given state
	d_ownsState = false;
	d_state = state;
}


/*************************************************************************
	Destructor
*************************************************************************/
CCLuaScriptModule::~CCLuaScriptModule()
{
	if ( d_ownsState && d_state )
	{
		lua_close( d_state );
	}
	s_luaScriptModule = NULL;

}

/*************************************************************************
	Execute script file
*************************************************************************/
void CCLuaScriptModule::executeScriptFile(const std::string& filename)
{
	int nRet = luaL_dofile(d_state,filename.c_str());
	if (nRet != 0)
	{
		CCLog("executeScriptFile Error nRet = %d", nRet);
	}
}


/*************************************************************************
	Execute global script function
*************************************************************************/
int	CCLuaScriptModule::executeScriptGlobal(const std::string& function_name)
{
	// get the function from lua
	lua_getglobal(d_state, function_name.c_str());
	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		CCLog("name does not represent a Lua function");
		lua_settop( d_state, 0 );
		return 0;
	}

	// call it
	int error = lua_pcall(d_state,0,1,0);		

	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		CCLog("%s", msg.c_str());
		lua_settop( d_state, 0 );
		return 0;
	}

	// get return value
	if ( !lua_isnumber(d_state,-1) )
	{
		CCLog("return value is not a number %s", function_name.c_str());
		lua_settop( d_state, 0 );
		return 0;
	}

	int ret = (int)lua_tonumber(d_state,-1);
	lua_pop(d_state,1);

	// return it
	return ret;

	
}


/*************************************************************************
	Execute scripted event handler
*************************************************************************/


bool CCLuaScriptModule::executeSchedule(const std::string& handler_name, ccTime cc)
{

	if (handler_name.size() == 0)
	{
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == NULL\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	
	// get the function from lua
	lua_getglobal(d_state, handler_name.c_str());

	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"\n\n"+"name does not represent a Lua function"+"\n";
		CCLog("%s %d", msg.c_str(), __FILE__);
		return false;
	}

	// push EventArgs as the first parameter
	//tolua_pushusertype(d_state,(void*)&cc,"dFloat");
	lua_pushfstring(d_state, "%f", cc);

	// call it
	int error = lua_pcall(d_state,1,0,0);

	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"\n\n"+msg+"\n";
		CCLog("%s %d", msgerror.c_str(), __FILE__);
		return false;
	}
	// return it
	return true;


}
bool CCLuaScriptModule::executeCallFunc(const std::string& handler_name)
{
	
	if (handler_name.size() == 0)
	{
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler:handler_name == NULL\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	lua_getglobal(d_state, handler_name.c_str());

	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name + "name does not represent a Lua functio"+"\n";
		CCLog("%s %d", msg.c_str(), __LINE__);
		return false;
	}
	// push EventArgs as the first parameter
	//tolua_pushusertype(d_state,(void*)&cc,"cocos2d::ccTime");
	// call it
	int error = lua_pcall(d_state,0,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name + msg +"\n";
		CCLog("%s  %d", msgerror.c_str(), __LINE__);
		return false;
	}
	// return it
	return true;

}
bool CCLuaScriptModule::executeCallFuncN(const std::string& handler_name, CCNode* pNode)
{

	if (handler_name.size() == 0)
	{
		std::string msg = "(executeCallFuncN) Unable to execute scripted event handler: handler_name == NULL\n";
		CCLog("%s  %d ", msg.c_str(), __LINE__);
		return false;
	}
	lua_getglobal(d_state, handler_name.c_str());


	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(executeCallFuncN) Unable to execute scripted event handler: "+handler_name +"name does not represent a Lua function"+"\n";
			CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	// push EventArgs as the first parameter
	tolua_pushusertype(d_state,(void*)pNode,"cocos2d::CCNode");
	// call it
	int error = lua_pcall(d_state,1,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(executeCallFuncN) Unable to execute scripted event handler: "+handler_name +msg+"\n";
			CCLog("%s %d", msgerror.c_str(),  __LINE__);
		return false;
	}
	// return it
	return true;

}
bool CCLuaScriptModule::executeCallFuncND(const std::string& handler_name, CCNode* pNode,  void*pData)
{


	if (handler_name.size() == 0)
	{
		std::string msg = "(executeCallFuncND) Unable to execute scripted event handler: handler_name == NULL\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	// get the function from lua
	lua_getglobal(d_state, handler_name.c_str());

	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(executeCallFuncND) Unable to execute scripted event handler: "+handler_name +"name does not represent a Lua function"+"\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	// push EventArgs as the first parameter
	tolua_pushusertype(d_state,(void*)pNode,"cocos2d::CCNode");
	tolua_pushusertype(d_state,(void*)pData,"void*");
	// call it
	int error = lua_pcall(d_state,2,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(executeCallFuncND) Unable to execute scripted event handler: "+handler_name +msg+"\n";
		CCLog("%s  %d", msgerror.c_str(), __LINE__);
		return false;
	}
	// return it
	return true;

}
bool CCLuaScriptModule::executeMenuHandler(const std::string& handler_name, CCObject* pobj)
{

		if (handler_name.size() == 0)
		{
			std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == NULL\n";
			CCLog("%s  %d", msg.c_str(), __LINE__);
			return false;
		}
		// get the function from lua
		lua_getglobal(d_state, handler_name.c_str());

		// is it a function
		if ( !lua_isfunction(d_state,-1) )
		{
			lua_settop( d_state, 0 );
			std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name + "name does not represent a Lua function"+"\n";
			CCLog("%s %d", msg.c_str(), __LINE__);
			return false;
		}
		// push EventArgs as the first parameter
		tolua_pushusertype(d_state,(void*)pobj,"cocos2d::CCObject");
		// call it
		int error = lua_pcall(d_state,1,0,0);
		// handle errors
		if ( error )
		{
			std::string msg = lua_tostring(d_state,-1);
			lua_pop(d_state,1);
			std::string msgerror = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name +msg+"\n";
			CCLog("%s %d", msgerror.c_str(), __LINE__);
			return false;
		}
		// return it
		return true;

}

bool CCLuaScriptModule::executeTouchesEvent(const std::string& handler_name, CCSet *pobj)
{

	if (handler_name.size() == 0)
	{
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == null\n";
		CCLog("%s %d", msg.c_str(), __LINE__);
		return false;
	}
	// get the function from lua
	lua_getglobal(d_state, handler_name.c_str());

	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"name does not represent a Lua function"+"\n";
		CCLog("%s %d", msg.c_str(), __LINE__);
		return false;
	}
	// push EventArgs as the first parameter
	tolua_pushusertype(d_state,(void*)pobj,"cocos2d::CCSet");
	// call it
	int error = lua_pcall(d_state,1,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+msg+"\n";
		CCLog("%s %d", msgerror.c_str(), __LINE__);
		return false;
	}
	// return it
	return true;
}

bool CCLuaScriptModule::executeTouch(const std::string& handler_name, CCTouch *pobj)
{

		if (handler_name.size() == 0)
		{
			std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == null\n";
			CCLog("%s %d", msg.c_str(), __LINE__);
			return false;
		}
		// get the function from lua
		lua_getglobal(d_state, handler_name.c_str());

		// is it a function
		if ( !lua_isfunction(d_state,-1) )
		{
			lua_settop( d_state, 0 );
			std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"\n\n"+"name does not represent a Lua function"+"\n";
			CCLog("%s ", msg.c_str());
			return false;
		}
		// push EventArgs as the first parameter
		tolua_pushusertype(d_state,(void*)pobj,"cocos2d::CCTouch");
		// call it
		int error = lua_pcall(d_state,1,0,0);
		// handle errors
		if ( error )
		{
			std::string msg = lua_tostring(d_state,-1);
			lua_pop(d_state,1);
			std::string msgerror = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"\n\n"+msg+"\n";
			CCLog("%s ", msgerror.c_str());
			return false;
		}
		// return it
		return true;
	

}
bool CCLuaScriptModule::executeEventHandler(const std::string& handler_name, CCEvent* pEvent)
{

	if (handler_name.size() == 0)
	{
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == NULL\n";
		CCLog("%s ", msg.c_str());
		return false;
	}
	// get the function from lua
	lua_getglobal(d_state, handler_name.c_str());

	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"\n\n"+"name does not represent a Lua function"+"\n";
		CCLog("%s ", msg.c_str());
		return false;
	}
	// push EventArgs as the first parameter
	tolua_pushusertype(d_state,(void*)pEvent,"cocos2d::CCEvent");
	// call it
	int error = lua_pcall(d_state,1,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(LuaScriptModule) Unable to execute scripted event handler: "+handler_name+"\n\n"+msg+"\n";
		CCLog("%s ", msgerror.c_str());
		return false;
	}
	// return it
	return true;

}

bool CCLuaScriptModule::executeListItem(const std::string& handler_name, int index, CCObject* pobj)
{

	if (handler_name.size() == 0)
	{
		std::string msg = "(CCLuaScriptModule) Unable to execute scripted event handler: handler_name == NULL\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	// get the function from lua
	lua_getglobal(d_state, handler_name.c_str());

	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = "(CCLuaScriptModule) Unable to execute scripted event handler: "+handler_name +"name does not represent a Lua function"+"\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	// push EventArgs as the first parameter
	lua_pushfstring(d_state, "%d", index);
	tolua_pushusertype(d_state,(void*)pobj,"cocos2d::CCObject");
	// call it
	int error = lua_pcall(d_state,2,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = "(CCLuaScriptModule) Unable to execute scripted event handler: "+handler_name +msg+"\n";
		CCLog("%s  %d", msgerror.c_str(), __LINE__);
		return false;
	}
	// return it
	return true;

}

/*************************************************************************
	Execute script code string
*************************************************************************/
void CCLuaScriptModule::executeString(const std::string& str)
{
	// load code into lua and call it
	int error =	luaL_loadbuffer(d_state, str.c_str(), str.length(), str.c_str()) || lua_pcall(d_state,0,0,0);

	// handle errors
	if ( error )
	{
		CCLog("executeString %d", error);
	}

}
	

/*************************************************************************
	Create Lua bindings
*************************************************************************/
void CCLuaScriptModule::createBindings(void)
{
	
	//tolua_Cocos2d_open(d_state);
}


/*************************************************************************
	Destroy Lua bindings
*************************************************************************/
void CCLuaScriptModule::destroyBindings(void)
{
	
	lua_pushnil(d_state);
	lua_setglobal(d_state,"cocos2d");
}


} // namespace CEGUI

#endif //CC_ENABLE_LUA