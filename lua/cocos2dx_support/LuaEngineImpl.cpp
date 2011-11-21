
//bool LuaEngine::executeCallFunc(const char* handler_name)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(LuaScriptModule) Unable to execute scripted event handler:handler_name == NULL\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + "name does not represent a Lua function" + "\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    //tolua_pushusertype(m_state,(void*)&cc,"cocos2d::ccTime");
//    // call it
//    int error = lua_pcall(m_state,0,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name + msg + "\n";
//        CCLog("%s %s  %d", __FILE__, msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeCallFuncN(const char* handler_name, CCNode* pNode)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(executeCallFuncN) Unable to execute scripted event handler: handler_name == NULL\n";
//        CCLog("%s  %d ", msg.c_str(), __LINE__);
//        return false;
//    }
//    lua_getglobal(m_state, handler_name.c_str());
//
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + "name does not represent a Lua function" + "\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    tolua_pushusertype(m_state,(void*)pNode,"cocos2d::CCNode");
//    // call it
//    int error = lua_pcall(m_state,1,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name + msg + "\n";
//        CCLog("%s %s %d", __FILE__, msgerror.c_str(),  __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//
//}
//
//bool LuaEngine::executeCallFuncO(const std::string &handler_name, cocos2d::CCObject *pObject)
//{
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(executeCallFuncO) Unable to execute scripted event handler: handler_name == NULL\n";
//        CCLog("%s  %d ", msg.c_str(), __LINE__);
//        return false;
//    }
//    lua_getglobal(m_state, handler_name.c_str());
//
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + "name does not represent a Lua function" + "\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    tolua_pushusertype(m_state,(void*)pObject,"cocos2d::CCObject");
//    // call it
//    int error = lua_pcall(m_state,1,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name + msg + "\n";
//        CCLog("%s %s %d", __FILE__, msgerror.c_str(),  __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeCallFuncND(const char* handler_name, CCNode* pNode,  void*pData)
//{
//
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(executeCallFuncND) Unable to execute scripted event handler: handler_name == NULL\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // get the function from lua
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + "name does not represent a Lua function" + "\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    tolua_pushusertype(m_state,(void*)pNode,"cocos2d::CCNode");
//    tolua_pushusertype(m_state,(void*)pData,"void*");
//    // call it
//    int error = lua_pcall(m_state,2,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name + msg + "\n";
//        CCLog("%s  %d", __FILE__, msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeMenuHandler(const char* handler_name, CCObject* pobj)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == NULL\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // get the function from lua
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + "name does not represent a Lua function" + "\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    tolua_pushusertype(m_state,(void*)pobj,"cocos2d::CCObject");
//    // call it
//    int error = lua_pcall(m_state,1,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        std::string msgerror = handler_name + msg + "\n";
//        CCLog("%s %s %d", __FILE__, msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeTouchesEvent(const char* handler_name, CCSet *pobj)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == null\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // get the function from lua
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name+" does not represent a Lua function"+"\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push array to lua
//    lua_createtable(m_state, pobj->count(), 0);
//    int newTable = lua_gettop(m_state);
//    int index = 1;
//    CCSetIterator iter = pobj->begin();
//    for (; iter != pobj->end(); iter++)
//    {
//        tolua_pushusertype(m_state,(void*)(*iter),"cocos2d::CCTouch");
//        lua_rawseti(m_state, newTable, index++);
//    }
//
//    // call it
//    int error = lua_pcall(m_state,1,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name + msg + "\n";
//        CCLog("%s %d", msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeTouch(const char* handler_name, CCTouch *pobj)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == null\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // get the function from lua
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name+"\n"+" does not represent a Lua function"+"\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    tolua_pushusertype(m_state,(void*)pobj,"cocos2d::CCTouch");
//    // call it
//    int error = lua_pcall(m_state,1,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        std::string msgerror = handler_name + "\n" + msg + "\n";
//        CCLog("%s %s %d", __FILE__, msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeEventHandler(const char* handler_name, CCEvent* pEvent)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(LuaScriptModule) Unable to execute scripted event handler: handler_name == NULL\n";
//        CCLog("%s ", msg.c_str());
//        return false;
//    }
//    // get the function from lua
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + "\n" + " does not represent a Lua function" + "\n";
//        CCLog("%s %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    tolua_pushusertype(m_state,(void*)pEvent,"cocos2d::CCEvent");
//    // call it
//    int error = lua_pcall(m_state,1,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name + "\n" + msg + "\n";
//        CCLog("%s %s %d", __FILE__, msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
//
//bool LuaEngine::executeListItem(const char* handler_name, int index, CCObject* pobj)
//{
//
//    if (handler_name.size() == 0)
//    {
//        std::string msg = "(LuaEngine) Unable to execute scripted event handler: handler_name == NULL\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // get the function from lua
//    lua_getglobal(m_state, handler_name.c_str());
//
//    // is it a function
//    if ( !lua_isfunction(m_state,-1) )
//    {
//        lua_settop(m_state, 0 );
//        std::string msg = handler_name + " does not represent a Lua function" + "\n";
//        CCLog("%s  %d", msg.c_str(), __LINE__);
//        return false;
//    }
//    // push EventArgs as the first parameter
//    lua_pushfstring(m_state, "%d", index);
//    tolua_pushusertype(m_state,(void*)pobj,"cocos2d::CCObject");
//    // call it
//    int error = lua_pcall(m_state,2,0,0);
//    // handle errors
//    if ( error )
//    {
//        std::string msg = lua_tostring(m_state,-1);
//        lua_pop(m_state,1);
//        lua_settop(m_state, 0 );
//        std::string msgerror = handler_name  + msg + "\n";
//        CCLog("%s %s  %d", __FILE__, msgerror.c_str(), __LINE__);
//        return false;
//    }
//    // return it
//    return true;
//}
