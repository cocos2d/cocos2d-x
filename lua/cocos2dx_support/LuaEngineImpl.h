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

#ifndef _LUA_ENGINE_IMPL_H
#define _LUA_ENGINE_IMPL_H

#include <string>

#include "cocos2d.h"

// include Lua
extern "C" {
#include "lua.h"
}

/** 
 @brief invoke lua script from c++ code
 */
class CCLuaScriptModule :  public cocos2d::CCObject
{
public:
	/*************************************************************************
		Construction and Destruction
	*************************************************************************/
	/**
     @brief Constructor for LuaScriptModule class which create a lua_State
	*/
	CCLuaScriptModule();

	/**
	 @brief Constructor for LuaScriptModule class which takes a lua_State
     @param state Pointer to the lua_State that the script module should attach to.
	*/
	CCLuaScriptModule(lua_State* state);


	/**
     @brief Destructor for LuaScriptModule class.
	*/
	virtual ~CCLuaScriptModule();
    
	/*************************************************************************
        Seting Functions
     *************************************************************************/
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
    */
    bool addSearchPath(const std::string& path);

	/**
	 @brief Add a loader for lua
	*/
	void addLuaLoader(lua_CFunction func);

	/*************************************************************************
		Script Execution Functions
	*************************************************************************/
	/**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
	*/
	bool executeScriptFile(const std::string& filename);

	/**
     @brief Execute a scripted global function.  
     @brief The function should not take any parameters and should return an integer.
     @param function_name String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
	*/
	int executeScriptGlobal(const std::string& function_name);


	/**
     @brief Execute a scripted global 'event handler' function.
     
     The function should take some kind of EventArgs like parameter
     that the concrete implementation of this function can create from the passed EventArgs based object.  The function
     should not return anything.

     @param handler_name String object holding the name of the scripted handler function.
     @param e EventArgs based object that should be passed, by any appropriate means, to the scripted function.
     
     @return true if the event was handled.
     @return false if the event was not handled.
	*/
	bool executeSchedule(const std::string& handler_name, cocos2d::ccTime cc);
	bool executeCallFunc(const std::string& handler_name);
	bool executeCallFuncN(const std::string& handler_name, cocos2d::CCNode* pNode);
	bool executeCallFuncND(const std::string& handler_name, cocos2d::CCNode* pNode,  void*pData);
	bool executeCallFuncO(const std::string& handler_name, cocos2d::CCObject* pObject);
	bool executeMenuHandler(const std::string& handler_name, cocos2d::CCObject* pobj);
	bool executeEventHandler(const std::string& handler_name, cocos2d::CCEvent* pEvent);
	bool executeTouchesEvent(const std::string& handler_name, cocos2d::CCSet *pobj);
	bool executeTouch(const std::string& handler_name, cocos2d::CCTouch *pobj);
	bool executeListItem(const std::string& handler_name, int index, cocos2d::CCObject* pobj);
	
    /**
     @brief Execute script code contained in the given CEGUI::String object.
     @param str String object holding the valid script code that should be executed.
     @return true if the string is excuted correctly.
     @return false if the string is excuted wrongly.
    */
	bool executeString(const std::string& str);


	/*************************************************************************
		Bindings creation / destruction
	*************************************************************************/
	/**
     @brief Method called during system initialisation, prior to running any scripts via the ScriptModule, 
     @brief to enable the ScriptModule to perform any operations required to complete initialisation or binding 
     @brief of the script language to the gui system objects.
     @return Nothing.
    */
	void createBindings(void);


	/**
     @brief Method called during system destruction, after all scripts have been run via the ScriptModule, 
     @brief to enable the ScriptModule to perform any operations required to cleanup bindings of the script 
     @brief language to the gui system objects, as set-up in the earlier createBindings call.
     @return Nothing.
    */
	void destroyBindings(void);


	/*************************************************************************
		Accessor type functions
	*************************************************************************/
	/**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
    */
	lua_State* getLuaState(void) const	{return d_state;}


    /**
     @breif Get the instance of CCLuaScriptModule singleton
     */
	static CCLuaScriptModule* sharedLuaScriptModule(void);

    /**
     @brief Purge and release the CCLuaScriptModule singleton 
     */
	static void purgeSharedLuaScriptModule();

	
private:
	static CCLuaScriptModule* s_luaScriptModule;
	/*************************************************************************
		Implementation Data
	*************************************************************************/
	bool d_ownsState;		//!< true when the attached lua_State was created by this script module
	lua_State* d_state;		//!< The lua_State that this script module uses.

};


#endif // end of guard _LUA_ENGINE_IMPL_H
