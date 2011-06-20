#ifndef _CCLUASRCIPT_H
#define _CCLUASRCIPT_H

#include <string>

#include "cocos2d.h"

// include Lua
extern "C" {
#include "lua.h"
}

class CCLuaScriptModule :  public cocos2d::CCObject
{
public:
	/*************************************************************************
		Construction and Destruction
	*************************************************************************/
	/*!
	\brief
		Constructor for LuaScriptModule class which create a lua_State
	*/
	CCLuaScriptModule();

	/*!
	\brief
		Constructor for LuaScriptModule class which takes a lua_State

	\param state
		Pointer to the lua_State that the script module should attach to.
	*/
	CCLuaScriptModule(lua_State* state);


	/*!
	\brief
		Destructor for LuaScriptModule class.
	*/
	virtual ~CCLuaScriptModule();


	/*************************************************************************
		Script Execution Functions
	*************************************************************************/
	/*!
	\brief
		Execute a script file.

	\param filename
		String object holding the filename of the script file that is to be executed
		
	*/
	bool executeScriptFile(const std::string& filename);


	/*!
	\brief
		Execute a scripted global function.  The function should not take any parameters and should return an integer.

	\param function_name
		String object holding the name of the function, in the global script environment, that
		is to be executed.

	\return
		The integer value returned from the script function.
	*/
	int executeScriptGlobal(const std::string& function_name);


	/*!
	\brief
		Execute a scripted global 'event handler' function.  The function should take some kind of EventArgs like parameter
		that the concrete implementation of this function can create from the passed EventArgs based object.  The function
		should not return anything.

	\param handler_name
		String object holding the name of the scripted handler function.

	\param e
		EventArgs based object that should be passed, by any appropriate means, to the scripted function.

	\return
		- true if the event was handled.
		- false if the event was not handled.
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
	/*!
    \brief
        Execute script code contained in the given CEGUI::String object.

    \param str
        String object holding the valid script code that should be executed.

    \return
	- true if the string is excuted correctly.
	- false if the string is excuted wrongly.
    */
	bool executeString(const std::string& str);


	/*************************************************************************
		Bindings creation / destruction
	*************************************************************************/
	/*!
    \brief
        Method called during system initialisation, prior to running any scripts via the ScriptModule, to enable the ScriptModule
        to perform any operations required to complete initialisation or binding of the script language to the gui system objects.

    \return
        Nothing.
    */
	void createBindings(void);


	/*!
    \brief
        Method called during system destruction, after all scripts have been run via the ScriptModule, to enable the ScriptModule
        to perform any operations required to cleanup bindings of the script language to the gui system objects, as set-up in the
        earlier createBindings call.

    \return
        Nothing.
    */
	void destroyBindings(void);


	/*************************************************************************
		Accessor type functions
	*************************************************************************/
	/*!
    \brief
		Method used to get a pointer to the lua_State that the script module is attached to.

    \return
        A pointer to the lua_State that the script module is attached to.
    */
	lua_State* getLuaState(void) const	{return d_state;}


	static CCLuaScriptModule* sharedLuaScriptModule(void);

	static void purgeSharedLuaScriptModule();

	
private:
	static CCLuaScriptModule* s_luaScriptModule;
	/*************************************************************************
		Implementation Data
	*************************************************************************/
	bool d_ownsState;		//!< true when the attached lua_State was created by this script module
	lua_State* d_state;		//!< The lua_State that this script module uses.

};


#endif // end of guard _CCLUASRCIPT_H
