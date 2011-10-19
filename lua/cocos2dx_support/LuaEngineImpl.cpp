/****************************************************************************
Copyright (c) 2011 cocos2d-x.org
Copyright (c) 2011 NetDragon.com

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
#include "LuaEngineImpl.h"

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}

#include "tolua++.h"
#include "CCTouch.h"
#include "CCNode.h"
#include "CCObject.h"
#include "LuaCocos2d.h"
#include "LuaSimpleAudioEngine.h"
#include "Cocos2dxLuaLoader.h"

using namespace cocos2d;

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
    CC_UNUSED_PARAM(nOpen);
    nOpen = tolua_SimpleAudioEngine_open(d_state);
    CC_UNUSED_PARAM(nOpen);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	addLuaLoader(loader_Android);
#endif
}


/*************************************************************************
	Constructor (uses given Lua state)
*************************************************************************/
CCLuaScriptModule::CCLuaScriptModule(lua_State* state)
{
	// just use the given state
	d_ownsState = false;
	d_state = state;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	addLuaLoader(loader_Android);
#endif
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
    Add a path to find lua files in (equivalent to LUA_PATH)
 *************************************************************************/
bool CCLuaScriptModule::addSearchPath(const std::string& path)
{
    lua_getglobal( d_state, "package" );
    lua_getfield( d_state, -1, "path" ); // get field "path" from table at top of stack (-1)
    const char* cur_path =  lua_tostring( d_state, -1 ); // grab path string from top of stack
    lua_pop( d_state, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushfstring(d_state, "%s;%s/?.lua", cur_path, path.c_str());
    lua_setfield( d_state, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( d_state, 1 ); // get rid of package table from top of stack
    return 0; // all done!
}

/*************************************************************************
Add lua loader, now it is used on android
*************************************************************************/
void CCLuaScriptModule::addLuaLoader(lua_CFunction func)
{
	if (! func)
	{
		return;
	}
                                                           // stack content after the invoking of the function
	// get loader table
	lua_getglobal(d_state, "package");                     // package
	lua_getfield(d_state, -1, "loaders");                  // package, loaders

	// insert loader into index 2
	lua_pushcfunction(d_state, func);                      // package, loaders, func
	for (int i = lua_objlen(d_state, -2) + 1; i > 2; --i)
	{
		lua_rawgeti(d_state, -2, i - 1);                   // package, loaders, func, function
		// we call lua_rawgeti, so the loader table now is at -3
		lua_rawseti(d_state, -3, i);                       // package, loaders, func
	}
	lua_rawseti(d_state, -2, 2);                           // package, loaders

	// set loaders into package
	lua_setfield(d_state, -2, "loaders");                  // package

	lua_pop(d_state, 1);
}


/*************************************************************************
	Execute script file
*************************************************************************/
bool CCLuaScriptModule::executeScriptFile(const std::string& filename)
{
	int nRet = luaL_dofile(d_state,filename.c_str());

	// Collect
	lua_gc(d_state, LUA_GCCOLLECT, 0);

	if (nRet != 0)
	{		        
        // print the error msg
        CCLog("%s", lua_tostring(d_state, -1));

		// pop the error code
		lua_pop(d_state, 1);
        
		return false;
	}

	return true;
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

	// Collect
	lua_gc(d_state, LUA_GCCOLLECT, 0);

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
		std::string msg = handler_name + "\n" + "name does not represent a Lua function" + "\n";
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
		std::string msgerror = handler_name + "\n\n" + msg + "\n";
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
		std::string msg = handler_name + "name does not represent a Lua function" + "\n";
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
		std::string msgerror = handler_name + msg + "\n";
		CCLog("%s %s  %d", __FILE__, msgerror.c_str(), __LINE__);
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
		std::string msg = handler_name + "name does not represent a Lua function" + "\n";
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
		std::string msgerror = handler_name + msg + "\n";
			CCLog("%s %s %d", __FILE__, msgerror.c_str(),  __LINE__);
		return false;
	}
	// return it
	return true;

}

bool CCLuaScriptModule::executeCallFuncO(const std::string &handler_name, cocos2d::CCObject *pObject)
{
	if (handler_name.size() == 0)
	{
		std::string msg = "(executeCallFuncO) Unable to execute scripted event handler: handler_name == NULL\n";
		CCLog("%s  %d ", msg.c_str(), __LINE__);
		return false;
	}
	lua_getglobal(d_state, handler_name.c_str());


	// is it a function
	if ( !lua_isfunction(d_state,-1) )
	{
		lua_settop( d_state, 0 );
		std::string msg = handler_name + "name does not represent a Lua function" + "\n";
		CCLog("%s  %d", msg.c_str(), __LINE__);
		return false;
	}
	// push EventArgs as the first parameter
	tolua_pushusertype(d_state,(void*)pObject,"cocos2d::CCObject");
	// call it
	int error = lua_pcall(d_state,1,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = handler_name + msg + "\n";
		CCLog("%s %s %d", __FILE__, msgerror.c_str(),  __LINE__);
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
		std::string msg = handler_name + "name does not represent a Lua function" + "\n";
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
		std::string msgerror = handler_name + msg + "\n";
		CCLog("%s  %d", __FILE__, msgerror.c_str(), __LINE__);
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
			std::string msg = handler_name + "name does not represent a Lua function" + "\n";
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
			std::string msgerror = handler_name + msg + "\n";
			CCLog("%s %s %d", __FILE__, msgerror.c_str(), __LINE__);
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
		std::string msg = handler_name+" does not represent a Lua function"+"\n";
		CCLog("%s %d", msg.c_str(), __LINE__);
		return false;
	}
	// push array to lua
	lua_createtable(d_state, pobj->count(), 0);
	int newTable = lua_gettop(d_state);
	int index = 1;
	CCSetIterator iter = pobj->begin();
	for (; iter != pobj->end(); iter++)
	{
        tolua_pushusertype(d_state,(void*)(*iter),"cocos2d::CCTouch");
		lua_rawseti(d_state, newTable, index++);
	}
	
	// call it
	int error = lua_pcall(d_state,1,0,0);
	// handle errors
	if ( error )
	{
		std::string msg = lua_tostring(d_state,-1);
		lua_pop(d_state,1);
		lua_settop( d_state, 0 );
		std::string msgerror = handler_name + msg + "\n";
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
			std::string msg = handler_name+"\n"+" does not represent a Lua function"+"\n";
			CCLog("%s %d", msg.c_str(), __LINE__);
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
			std::string msgerror = handler_name + "\n" + msg + "\n";
			CCLog("%s %s %d", __FILE__, msgerror.c_str(), __LINE__);
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
		std::string msg = handler_name + "\n" + " does not represent a Lua function" + "\n";
		CCLog("%s %d", msg.c_str(), __LINE__);
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
		std::string msgerror = handler_name + "\n" + msg + "\n";
		CCLog("%s %s %d", __FILE__, msgerror.c_str(), __LINE__);
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
		std::string msg = handler_name + " does not represent a Lua function" + "\n";
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
		std::string msgerror = handler_name  + msg + "\n";
		CCLog("%s %s  %d", __FILE__, msgerror.c_str(), __LINE__);
		return false;
	}
	// return it
	return true;
}

/*************************************************************************
	Execute script code string
*************************************************************************/
bool CCLuaScriptModule::executeString(const std::string& str)
{
	// load code into lua and call it
	int error =	luaL_dostring(d_state, str.c_str());

	// Collect
	lua_gc(d_state, LUA_GCCOLLECT, 0);

	// handle errors
	if (error)
	{
		// print error message and pop it
		CCLog("%s", lua_tostring(d_state, -1));
		lua_pop(d_state, 1);

		return false;
	}

	return true;
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
	// called? necessary? by sunzhuoshi@gmail.com
	lua_pushnil(d_state);
	lua_setglobal(d_state, "CocosDenshion");
}
