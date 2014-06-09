
#include <lua.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
  const char *name;			//name of method
  lua_CFunction func;		//entry of method
  const char *retType;	    //return type of method
  const char *methodSign;	//signatures of method
  							//'T': string
} cclass_method_Reg;

int luabinderload(const char * classname);
int lua_binder_open(lua_State *L);
    
int cclass_reg(lua_State *L, const char *classname, lua_CFunction regfunc);
void cclass_runtime_reg(lua_State *L, cclass_method_Reg reg[], const char *super[]);

#ifdef __cplusplus
} // extern "C"
#endif

