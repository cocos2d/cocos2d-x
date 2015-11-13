
#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"
    
#define TOLUA_REFID_PTR_MAPPING "toluafix_refid_ptr_mapping"
#define TOLUA_REFID_TYPE_MAPPING "toluafix_refid_type_mapping"
#define TOLUA_REFID_FUNCTION_MAPPING "toluafix_refid_function_mapping"

/**
 * @addtogroup lua
 * @{
 */
/// @cond
TOLUA_API void toluafix_open(lua_State* L);
/// @endcond

/**@~english
 * Push the userdata correspondings to the ptr on the top index of the Lua stack.
 * If the userdata correspondings to the ptr don't exist, it would call lua_newuserdata to new a userdata.
 * If the userdata correspondings to the ptr exist,it would update the metatable information of the super.
 * In addition, this function would update some table in the Lua registry,such as toluafix_refid_ptr_mapping, toluafix_refid_type_mapping,tolua_value_root,and so on.
 * Meanwhile, Add a reference about the userdata corresponding to the ptr in the tolua_ubox table.
 * The ptr should be point to a Ref object.
 * 
 * @~chinese 
 * 把对应于ptr的userdata压到Lua栈顶。
 * 如果对应ptr的userdata不存在,它将调用lua_newuserdata新建一个userdata。
 * 如果对应ptr的userdata存在,它将更新父类的元表信息。
 * 此外,此函数会更新一些Lua注册表的属性table,如toluafix_refid_ptr_mapping,toluafix_refid_type_mapping,tolua_value_root等等。
 * 同时,在tolua_ubox table中增加对应ptr的一个引用。
 * ptr应该指向一个Ref对象。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param uid @~english the object id of the ptr.
 * @~chinese ptr的object id。
 * @param p_refid @~english the pointer points to the Lua reference id of the ptr.
 * @~chinese 指向ptr的reference id成员变量的指针。
 * @param ptr @~english the pointer points to the Ref object.
 * @~chinese Ref对象指针。
 * @param type @~english the type name of the ptr.
 * @~chinese ptr的类型名称。
 * @return @~english -1 if the p_refid equal to nullptr or ptr equal to nullptr, otherwise return 0.
 * @~chinese 如果p_refid为nullptr或者ptr为nullptr,返回1，否则返回0。
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_pushusertype_ccobject(lua_State* L,
                                             int uid,
                                             int* p_refid,
                                             void* ptr,
                                             const char* type);

/**@~english
 * Find the value of Ref object pointer in the Lua registry by the refid.
 * Then, remove the corresponding reference in some table in the Lua registry by refid, such as toluafix_refid_type_mapping, toluafix_refid_ptr_mapping,tolua_value_root,and so on.
 * Set the value of userdata nullptr and remove the reference of userdata in the tolua_ubox table.
 * This function is called in the destructor of the Ref automatically.
 *
 * @~chinese 
 * 在Lua注册表中根据refid查找对应的Ref对象指针。
 * 然后,移除Lua注册表中一些与refids相关的table中的值引用，如toluafix_refid_type_mapping,toluafix_refid_ptr_mapping tolua_value_root等等。
 * 同时，设置对应的userdata为nullptr以及移除tolua_ubox table的关于userdata的引用。
 * 这个函数会在Ref的析构函数中自动调用。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param refid @~english the value of the _luaID of a Ref object.
 * @~chinese Ref对旬中_luaID的值
 * @return @~english -1,if refid equals to 0 , type name found by refid equals to nil or corresponding userdata pointer equal to nullptr; return -2, if the Ref object pointer found by refid is nullptr; return 3, if the value corresponding to the Ref object pointer in the tolua_ubox is nil; otherwise return 0.
 * @~chinese -1：如果refid等于0,根据refid查找到的类型名字为nil或者相应的userdata指针等于nullptr;-2 : 如果根据refid查找到的Ref对象指针为nullptr;3:如果在tolua_ubox table中对应Ref对象指针的值为nil;否则返回0。
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_remove_ccobject_by_refid(lua_State* L, int refid);

/**@~english
 * Get the reference id of the Lua function at the given accepteable index lo of stack.
 * Meanwhile add reference about the Lua function through the toluafix_refid_function_mapping table in the Lua registry.
 *
 * @~chinese 
 * 获取给定Lua栈索引上Lua函数的引用id。
 * 同时，在Lua注册表的toluafix_refid_function_mapping table中增加Lua函数的引用映射。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param lo @~english the given accepteable index lo of stack.
 * @~chinese 给定合理的Lua栈索引。
 * @param def @~english useless.
 * @~chinese 无用的参数。
 * @return @~english 0 if the type of value at the given accepteable index lo of stack is not LUA_TFUNCTION; otherwise return the reference id.
 * @~chinese 如果给定合理的Lua栈索引上的值的类型不是LUA_TFUNCTION，返回0；否则，返回对应的reference id。 
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_ref_function(lua_State* L, int lo, int def);

/**@~english
 * Push the Lua function found by the refid in the toluafix_refid_function_mapping table in the Lua registry on the top index of the current stack.
 *
 * @~chinese 
 * 在Lua注册表中toluafix_refid_function_mappingn table中查找对应refid对应的Lua函数，并且将压到当前的栈顶。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param refid @~english referenc id corresponding to the Lua function.
 * @~chinese 对应Lua函数的reference id。
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid);

/**@~english
 * Remove the reference of the Lua function corresponding to the refid in the toluafix_refid_function_mapping table in the Lua registry.
 *
 * @~chinese
 * 移除Lua注册表中toluafix_refid_function_mapping表中对应refid的Lua函数引用。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param refid @~english referenc id corresponding to the Lua function.
 * @~chinese 对应Lua函数的reference id。
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid);

/**@~english
 * Verify the value at the given acceptable index is a function or not.
 * 
 * @~chinese 
 * 验证给定合理的Lua栈索引上是否为一个Lua函数。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param lo @~english the given accepteable index lo of stack.
 * @~chinese 给定合理的Lua栈索引。
 * @param type @~english useless.
 * @~chinese 无用的。
 * @param def @~english useless.
 * @~chinese 无用的。
 * @param err @~english if triggger the error, record the error message to err.
 * @~chinese 如果验证过程中触发了错误,将错误信息记录在err中。
 * @return @~english 1 if the value at the given acceptable index is a function, otherwise return 0.
 * @~chinese 如果给定合理的栈索引上一个函数返回1，否则返回0。
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// @cond
TOLUA_API int toluafix_totable(lua_State* L, int lo, int def);
/// @endcond

/**@~english
 * Verify the value at the given acceptable index is a table or not.
 * 
 * @~chinese 
 * 验证给定合理的Lua栈索引上是否为一个table。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param lo @~english the given accepteable index lo of stack.
 * @~chinese 给定合理的Lua栈索引。
 * @param type @~english useless.
 * @~chinese 无用的。
 * @param def @~english whether has the default value or not.
 * @~chinese 是否有默认值。
 * @param err @~english if triggger the error, record the error message to err.
 * @~chinese 如果验证过程中触发了错误,将错误信息记录在err中。
 * @return @~english 1 if the value at the given acceptable index is a table or have def value is not 0, otherwise return 0.
 * @~chinese 给定合理的Lua栈索引上是一个table返回1，否则返回0。
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_istable(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/**@~english
 * Print all information of the stack from the top index.
 * If the type corresponding to the index of the stack is LUA_TSTRING, LUA_TBOOLEAN or LUA_TNUMBER, it would output the value of the index,otherwise output the type name of the index.
 *
 * @~chinese 
 * 打印栈顶开始打印栈中的所有信息。
 * 如果栈索引上的值的类型是LUA_TSTRING LUA_TBOOLEAN或LUA_TNUMBER,它将输出栈索引上的值,否则输出栈索引的值的类型名称。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param label @~english the string pointer to define the label of the dump information.
 * @~chinese 指向dump信息的标签的字符串指针，可以为空。
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_stack_dump(lua_State* L, const char* label);

// end group
/// @}

#endif // __TOLUA_FIX_H_
