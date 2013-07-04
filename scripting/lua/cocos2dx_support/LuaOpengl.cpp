#ifdef __cplusplus
extern "C" {
#endif
    #include "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include <map>
#include <string>
#include "LuaOpengl.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GLNode:public Node
{
public:
    
    GLNode():m_scriptDrawHandler(0)
    {
        
    }
    virtual ~GLNode()
    {
        if (0 != m_scriptDrawHandler) {
            this->unregisterScriptHandler();
        }
    }
    
    virtual void draw()
    {
        if (0 != m_scriptDrawHandler)
        {
            ScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_scriptDrawHandler,"");
        }
    }
    
    void registerScriptDrawHandler(int nHandler)
    {
        this->unregisterScriptDrawHandler();
        m_scriptDrawHandler = nHandler;
    }
    
    void unregisterScriptDrawHandler()
    {
        if (0 != m_scriptDrawHandler)
        {
            ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_scriptDrawHandler);
            LUALOG("[LUA] Remove GLNode script handler: %d", m_scriptDrawHandler);
            m_scriptDrawHandler = 0;
        }
    }
    int getScriptDrawHandler()
    {
        return 0;
    }
private:
    int m_scriptDrawHandler;
};

/* function to release collected object via destructor */
static void tolua_reg_gl_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "GLNode");
    tolua_usertype(tolua_S, "CCShaderCache");
}

static int tolua_collect_GLNode (lua_State* tolua_S)
{
    GLNode *self = (GLNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCGLProgram (lua_State* tolua_S)
{
 GLProgram* self = (GLProgram*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCShaderCache (lua_State* tolua_S)
{
 ShaderCache* self = (ShaderCache*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

/* method: create of class  GLNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_GLNode_create00
static int tolua_Cocos2d_GLNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"GLNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLNode *glNode = new GLNode();
        if (NULL != glNode)
        {
            glNode->autorelease();
            tolua_pushusertype(tolua_S,(void*)glNode,"GLNode");
            //tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
        else
        {
            return 0;
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptDrawHandler of class  GLNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_GLNode_registerScriptDrawHandler00
static int tolua_Cocos2d_GLNode_registerScriptDrawHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"GLNode",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        GLNode* self = (GLNode*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION funcID = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptDrawHandler'", NULL);
#endif
        if(NULL != self)
            self->registerScriptDrawHandler(funcID);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptDrawHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptDrawHandler of class  GLNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00
static int tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"GLNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        GLNode* self = (GLNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptDrawHandler'", NULL);
#endif
        if(NULL != self)
            self->unregisterScriptHandler();
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptDrawHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShaderProgram of class  GLNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_GLNode_setShaderProgram00
static int tolua_Cocos2d_GLNode_setShaderProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"GLNode",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLNode* self = (GLNode*)  tolua_tousertype(tolua_S,1,0);
        GLProgram* pShaderProgram = ((GLProgram*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShaderProgram'", NULL);
#endif
        if(NULL != self)
            self->setShaderProgram(pShaderProgram);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setShaderProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetSupportedExtensions*/
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetSupportedExtensions00
static int tolua_Cocos2d_glGetSupportedExtensions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isnoobj(tolua_S,1,&tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        const GLubyte* extensions = glGetString(GL_EXTENSIONS);
        size_t len  = std::strlen((const char*)extensions);
        GLubyte* copy = new GLubyte[len+1];
        std::strncpy((char*)copy, (const char*)extensions, len );
        
        int start_extension=0;
        LuaValueArray array;
        for (unsigned int i=0; i < len+1; i++)
        {
            if( copy[i]==' ' || copy[i]==',' || i == len )
            {
                copy[i] = 0;
                LuaValue value = LuaValue::stringValue((const char*)&copy[start_extension]);
                array.push_back(value);                
                start_extension = i+1;
                i++;
            }
        }
        
        lua_newtable(tolua_S);                                              /* L: table */
        int index = 1;
        for (LuaValueArrayIterator it = array.begin(); it != array.end(); ++it)
        {
            lua_pushstring(tolua_S, (*it).stringValue().c_str());     /* L: table value */
            lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
            ++index;
        }
        CC_SAFE_DELETE_ARRAY(copy);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetSupportedExtensions'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* function: glActiveTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glActiveTexture00
static int tolua_Cocos2d_glActiveTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isnumber(tolua_S,1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int activeTexture = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glActiveTexture((GLenum)activeTexture);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glActiveTexture'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glAttachShader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glAttachShader00
static int tolua_Cocos2d_glAttachShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int program = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int shader  = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glAttachShader ((GLuint)program,(GLuint) shader);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glAttachShader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBindAttribLocation  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBindAttribLocation00
static int tolua_Cocos2d_glBindAttribLocation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isstring(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int program = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int index   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        const char* name = (const char*)tolua_tostring(tolua_S, 3, "");
        glBindAttribLocation ((GLuint)program,(GLuint) index,name);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBindAttribLocation'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBindBuffer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBindBuffer00
static int tolua_Cocos2d_glBindBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int buffer   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glBindBuffer((GLenum)target,(GLuint)buffer);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBindBuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: glBindFramebuffer of class  GLNode */
/*
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBindFramebuffer00
static int tolua_Cocos2d_glBindFramebuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"GLNode",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        unsigned int framebuffer   = (unsigned int)tolua_tonumber(tolua_S,3,0);
        glBindFramebuffer((GLenum)target,(GLuint)framebuffer);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBindFramebuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE
*/

/* function: glBindRenderbuffer  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBindRenderbuffer00
static int tolua_Cocos2d_glBindRenderbuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int renderbuffer   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glBindRenderbuffer((GLenum)target,(GLuint)renderbuffer);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBindRenderbuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBindTexture  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBindTexture00
static int tolua_Cocos2d_glBindTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int texture   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glBindTexture((GLenum)target,(GLuint)texture);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBindTexture'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBlendColor  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBlendColor00
static int tolua_Cocos2d_glBlendColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int red   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int green = (unsigned int)tolua_tonumber(tolua_S,2,0);
        unsigned int blue  = (unsigned int)tolua_tonumber(tolua_S,3,0);
        unsigned int alpha  = (unsigned int)tolua_tonumber(tolua_S,4,0);
        glBlendColor((GLclampf)red , (GLclampf)green , (GLclampf)blue , (GLclampf)alpha );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBlendColor'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBlendEquation */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBlendEquation00
static int tolua_Cocos2d_glBlendEquation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int mode   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glBlendEquation((GLenum)mode);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBlendEquation'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBlendEquationSeparate  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBlendEquationSeparate00
static int tolua_Cocos2d_glBlendEquationSeparate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int modeRGB   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int modeAlpha   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glBlendEquationSeparate((GLenum)modeRGB , (GLenum)modeAlpha  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBlendEquationSeparate'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBlendFunc  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBlendFunc00
static int tolua_Cocos2d_glBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int sfactor   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int dfactor   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glBlendFunc((GLenum)sfactor , (GLenum)dfactor);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBlendFunc'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBlendFuncSeparate */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBlendFuncSeparate00
static int tolua_Cocos2d_glBlendFuncSeparate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int srcRGB   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int dstRGB = (unsigned int)tolua_tonumber(tolua_S,2,0);
        unsigned int srcAlpha  = (unsigned int)tolua_tonumber(tolua_S,3,0);
        unsigned int dstAlpha  = (unsigned int)tolua_tonumber(tolua_S,4,0);
        glBlendFuncSeparate((GLenum)srcRGB , (GLenum)dstRGB , (GLenum)srcAlpha , (GLenum)dstAlpha );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBlendFuncSeparate'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBufferData  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBufferData00
static int tolua_Cocos2d_glBufferData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,2, 0,&tolua_err)            ||
        !tolua_istable(tolua_S, 3, 0, &tolua_err)           ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        long length   = (long)tolua_tonumber(tolua_S,2,0);
        float* floatArray     = new float[length];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= length; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        unsigned int usage  = (unsigned int)tolua_tonumber(tolua_S,4,0);
        long lengthInByte = length * sizeof(float);
        glBufferData((GLenum)target , (GLsizeiptr)lengthInByte, (GLvoid*)floatArray , (GLenum)usage);
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBufferData'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glBufferSubData  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glBufferSubData00
static int tolua_Cocos2d_glBufferSubData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,2, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)           ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)           ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        long offset = (long)tolua_tonumber(tolua_S,2,0);
        long length   = (long)tolua_tonumber(tolua_S,3,0);
        float* floatArray     = new float[length];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= length; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        long lengthInByte = length * sizeof(float);
        long offsetInByte = offset * sizeof(float);
        glBufferSubData((GLenum)target,(GLintptr)offsetInByte,(GLsizei)lengthInByte,(GLvoid*)floatArray);

        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glBufferData'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCheckFramebufferStatus */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCheckFramebufferStatus00
static int tolua_Cocos2d_glCheckFramebufferStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int retVal = glCheckFramebufferStatus((GLenum)target);
        tolua_pushnumber(tolua_S,retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCheckFramebufferStatus'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glClear */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glClear00
static int tolua_Cocos2d_glClear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int mask   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glClear((GLbitfield)mask);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glClear'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glClearColor  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glClearColor00
static int tolua_Cocos2d_glClearColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int red   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int green   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        unsigned int blue   = (unsigned int)tolua_tonumber(tolua_S,3,0);
        unsigned int alpha   = (unsigned int)tolua_tonumber(tolua_S,4,0);
        glClearColor((GLclampf)red , (GLclampf)green , (GLclampf)blue , (GLclampf)alpha);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glClearColor'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glClearDepthf  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glClearDepthf00
static int tolua_Cocos2d_glClearDepthf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int depth   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glClearDepthf((GLclampf)depth  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glClearDepthf'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glClearStencil */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glClearStencil00
static int tolua_Cocos2d_glClearStencil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int stencil   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glClearStencil((GLint)stencil  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glClearStencil'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glColorMask  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glColorMask00
static int tolua_Cocos2d_glColorMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned char red   = (unsigned char)tolua_tonumber(tolua_S,1,0);
        unsigned char green   = (unsigned char)tolua_tonumber(tolua_S,2,0);
        unsigned char blue   = (unsigned char)tolua_tonumber(tolua_S,3,0);
        unsigned char alpha   = (unsigned char)tolua_tonumber(tolua_S,4,0);
        glColorMask((GLboolean)red , (GLboolean)green , (GLboolean)blue , (GLboolean)alpha);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glColorMask'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCompileShader  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCompileShader00
static int tolua_Cocos2d_glCompileShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int shader   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glCompileShader((GLuint)shader  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCompileShader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCompressedTexImage2D */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCompressedTexImage2D00
static int tolua_Cocos2d_glCompressedTexImage2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,2, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,5, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 7, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 8, 0, &tolua_err)          ||
        !tolua_istable(tolua_S, 9, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 10, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        int level   = (int)tolua_tonumber(tolua_S,2,0);
        unsigned int internalformat = (unsigned int)tolua_tonumber(tolua_S,3,0);
        int width   = (int)tolua_tonumber(tolua_S, 4, 0);
        int height   = (int)tolua_tonumber(tolua_S, 5, 0);
        int border   = (int)tolua_tonumber(tolua_S, 6, 0);
        int imageSize   = (int)tolua_tonumber(tolua_S, 7, 0);
        
        long length   = (long)tolua_tonumber(tolua_S,8,0);
        float* floatArray     = new float[length];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= length; i++)
        {
            floatArray[i - 1] = (float)tolua_tofieldnumber(tolua_S, 9, i, 0);
        }
        glCompressedTexImage2D((GLenum)target , (GLint)level , (GLenum)internalformat , (GLsizei)width , (GLsizei)height , (GLint)border , (GLsizei)imageSize , (GLvoid*)floatArray  );
        
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCompressedTexImage2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCompressedTexSubImage2D  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCompressedTexSubImage2D00
static int tolua_Cocos2d_glCompressedTexSubImage2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,2, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,5, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 7, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 8, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 9, 0, &tolua_err)          ||
        !tolua_istable(tolua_S, 10, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 11, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        int level   = (int)tolua_tonumber(tolua_S,2,0);
        int xoffset = (int)tolua_tonumber(tolua_S, 3, 0);
        int yoffset = (int)tolua_tonumber(tolua_S, 4, 0);
        int width   = (int)tolua_tonumber(tolua_S, 5, 0);
        int height   = (int)tolua_tonumber(tolua_S, 6, 0);
        unsigned int format = (unsigned int)tolua_tonumber(tolua_S,7,0);
        int imageSize   = (int)tolua_tonumber(tolua_S, 8, 0);
        
        long length   = (long)tolua_tonumber(tolua_S,9,0);
        float* floatArray     = new float[length];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= length; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 10, i, 0);
        }
        glCompressedTexSubImage2D((GLenum)target , (GLint)level , (GLint)xoffset , (GLint)yoffset , (GLsizei)width , (GLsizei)height , (GLenum)format , (GLsizei)imageSize , (GLvoid*)floatArray  );
        
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCompressedTexSubImage2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCopyTexImage2D  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCopyTexImage2D00
static int tolua_Cocos2d_glCopyTexImage2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,5, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 7, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 8, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 9, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        int level   = (int)tolua_tonumber(tolua_S,2,0);
        unsigned int internalformat = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        int x  = (int)tolua_tonumber(tolua_S, 4, 0);
        int y   = (int)tolua_tonumber(tolua_S, 5, 0);
        int width   = (int)tolua_tonumber(tolua_S, 6, 0);
        int height = (int)tolua_tonumber(tolua_S,7,0);
        int border   = (int)tolua_tonumber(tolua_S, 8, 0);
        glCopyTexImage2D((GLenum)target , (GLint)level , (GLenum)internalformat , (GLint)x , (GLint)y , (GLsizei)width , (GLsizei)height , (GLint)border  );
        
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCopyTexImage2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCopyTexSubImage2D */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCopyTexSubImage2D00
static int tolua_Cocos2d_glCopyTexSubImage2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,2, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S,5, 0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 7, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 8, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 9, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        int level   = (int)tolua_tonumber(tolua_S,2,0);
        int xoffset = (int)tolua_tonumber(tolua_S, 3, 0);
        int yoffset = (int)tolua_tonumber(tolua_S, 4, 0);
        int x  = (int)tolua_tonumber(tolua_S, 5, 0);
        int y   = (int)tolua_tonumber(tolua_S, 6, 0);
        int width   = (int)tolua_tonumber(tolua_S, 7, 0);
        int height = (int)tolua_tonumber(tolua_S,8,0);
        glCopyTexSubImage2D((GLenum)target , (GLint)level , (GLint)xoffset ,(GLint)yoffset , (GLint)x , (GLint)y , (GLsizei)width , (GLsizei)height);
        
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCopyTexSubImage2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCreateProgram  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCreateProgram00
static int tolua_Cocos2d_glCreateProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isnoobj(tolua_S, 1, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        int retVal = glCreateProgram();
        tolua_pushnumber(tolua_S,retVal);
        
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCreateProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCreateShader  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCreateShader00
static int tolua_Cocos2d_glCreateShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int type   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        int retVal = glCreateShader((GLenum)type  );
        tolua_pushnumber(tolua_S,retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCreateShader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glCullFace */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glCullFace00
static int tolua_Cocos2d_glCullFace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int mode   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glCullFace((GLenum)mode  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glCullFace'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDeleteBuffers  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDeleteBuffers00
static int tolua_Cocos2d_glDeleteBuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int buffers   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDeleteBuffers(1,&buffers );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDeleteBuffers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDeleteFramebuffers  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDeleteFramebuffers00
static int tolua_Cocos2d_glDeleteFramebuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int framebuffers   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDeleteBuffers(1,&framebuffers );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDeleteFramebuffers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDeleteProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDeleteProgram00
static int tolua_Cocos2d_glDeleteProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int program   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDeleteProgram((GLuint)program);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDeleteProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDeleteRenderbuffers */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDeleteRenderbuffers00
static int tolua_Cocos2d_glDeleteRenderbuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int renderbuffers   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDeleteRenderbuffers(1,&renderbuffers);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDeleteRenderbuffers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDeleteShader  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDeleteShader00
static int tolua_Cocos2d_glDeleteShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int shader   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDeleteShader((GLuint)shader  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDeleteShader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDeleteTextures  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDeleteTextures00
static int tolua_Cocos2d_glDeleteTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int textures   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDeleteTextures(1,&textures );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDeleteTextures'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDepthFunc  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDepthFunc00
static int tolua_Cocos2d_glDepthFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int func   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDepthFunc((GLenum)func);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDepthFunc'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDepthMask  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDepthMask00
static int tolua_Cocos2d_glDepthMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned char flag   = (unsigned char)tolua_tonumber(tolua_S,1,0);
        glDepthMask((GLboolean)flag  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDepthMask'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDepthRangef  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDepthRangef00
static int tolua_Cocos2d_glDepthRangef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int zNear   = (int)tolua_tonumber(tolua_S,1,0);
        int zFar    = (int)tolua_tonumber(tolua_S,2,0);
        glDepthRangef((GLclampf)zNear , (GLclampf)zFar  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDepthRangef'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDetachShader  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDetachShader00
static int tolua_Cocos2d_glDetachShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int program   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        unsigned int shader    = (unsigned int)tolua_tonumber(tolua_S,2,0);
        glDetachShader((GLuint)program , (GLuint)shader  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDetachShader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDisable  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDisable00
static int tolua_Cocos2d_glDisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int cap   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDisable((GLenum)cap );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDisable'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDisableVertexAttribArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDisableVertexAttribArray00
static int tolua_Cocos2d_glDisableVertexAttribArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int index   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glDisableVertexAttribArray((GLuint)index  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDisableVertexAttribArray'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glDrawArrays  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDrawArrays00
static int tolua_Cocos2d_glDrawArrays00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int mode   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        int first   = (unsigned int)tolua_tonumber(tolua_S,2,0);
        int count   = (unsigned int)tolua_tonumber(tolua_S,3,0);
        glDrawArrays((GLenum)mode , (GLint)first , (GLsizei)count );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDrawArrays'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* function: glDrawElements  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glDrawElements00
static int tolua_Cocos2d_glDrawElements00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err)            ||
        !tolua_istable(tolua_S,5,0,&tolua_err)             ||
        !tolua_isnoobj(tolua_S,6, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1  = (int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int arg2  = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        unsigned int arg3  = (unsigned int)tolua_tonumber(tolua_S, 4, 0);
        if (GL_UNSIGNED_BYTE == arg2)
        {
            unsigned char* unit8Array     = new unsigned char[arg3];
            if (NULL == unit8Array)
            {
                return 0;
            }
            for (unsigned int i = 1; i <= arg3; i++)
            {
                unit8Array[i-1] = (unsigned char)tolua_tofieldnumber(tolua_S, 5, i, 0);
            }
            glDrawElements((GLenum)arg0 , (GLsizei)arg1 , (GLenum)arg2 , (GLvoid*)unit8Array);
            CC_SAFE_DELETE_ARRAY(unit8Array);
        }
        else if(GL_UNSIGNED_SHORT == arg2)
        {
            unsigned short* shortArray     = new unsigned short[arg3];
            if (NULL == shortArray)
            {
                return 0;
            }
            for (unsigned int i = 1; i <= arg3; i++)
            {
                shortArray[i-1] = (unsigned short)tolua_tofieldnumber(tolua_S, 5, i, 0);
            }
            glDrawElements((GLenum)arg0 , (GLsizei)arg1 , (GLenum)arg2 , (GLvoid*)shortArray);
            CC_SAFE_DELETE_ARRAY(shortArray);
        }
        else if(GL_UNSIGNED_INT == arg2)
        {
            unsigned int* intArray     = new unsigned int[arg3];
            if (NULL == intArray)
            {
                return 0;
            }
            for (unsigned int i = 1; i <= arg3; i++)
            {
                intArray[i-1] = (unsigned int)tolua_tofieldnumber(tolua_S, 5, i, 0);
            }
            glDrawElements((GLenum)arg0 , (GLsizei)arg1 , (GLenum)arg2 , (GLvoid*)intArray);
            CC_SAFE_DELETE_ARRAY(intArray);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glDrawElements'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* function: glEnable  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glEnable00
static int tolua_Cocos2d_glEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int cap   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glEnable((GLenum)cap);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glEnable'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glEnableVertexAttribArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glEnableVertexAttribArray00
static int tolua_Cocos2d_glEnableVertexAttribArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int index   = (unsigned int)tolua_tonumber(tolua_S,1,0);
        glEnableVertexAttribArray((GLuint)index);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glEnableVertexAttribArray'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glFinish */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glFinish00
static int tolua_Cocos2d_glFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S, 1, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        glFinish();
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glFinish'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glFlush */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glFlush00
static int tolua_Cocos2d_glFlush00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S, 1, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        glFlush();
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glFlush'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glFramebufferRenderbuffer  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glFramebufferRenderbuffer00
static int tolua_Cocos2d_glFramebufferRenderbuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int attachment = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int renderbuffertarget = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        unsigned int renderbuffer = (unsigned int)tolua_tonumber(tolua_S, 4, 0);
        glFramebufferRenderbuffer((GLenum)target , (GLenum)attachment , (GLenum)renderbuffertarget , (GLuint)renderbuffer  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glFramebufferRenderbuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glFramebufferTexture2D  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glFramebufferTexture2D00
static int tolua_Cocos2d_glFramebufferTexture2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 6, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int attachment = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int textarget = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        unsigned int texture = (unsigned int)tolua_tonumber(tolua_S, 4, 0);
        int level = (int)tolua_tonumber(tolua_S, 5, 0);
        glFramebufferTexture2D((GLenum)target , (GLenum)attachment , (GLenum)textarget , (GLuint)texture,(GLuint)level );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glFramebufferTexture2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glFrontFace */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glFrontFace00
static int tolua_Cocos2d_glFrontFace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int mode = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glFrontFace((GLenum)mode);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glFrontFace'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGenBuffers */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGenBuffers00
static int tolua_Cocos2d_glGenBuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S, 1, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int buffer = 0;
        glGenBuffers(1, &buffer);
        tolua_pushnumber(tolua_S, buffer);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGenBuffers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGenFramebuffers  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGenFramebuffers00
static int tolua_Cocos2d_glGenFramebuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int framebuffer = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glGenFramebuffers(1, &framebuffer);
        tolua_pushnumber(tolua_S, framebuffer);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGenFramebuffers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGenRenderbuffers  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGenRenderbuffers00
static int tolua_Cocos2d_glGenRenderbuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int renderbuffer = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glGenRenderbuffers(1, &renderbuffer);
        tolua_pushnumber(tolua_S, renderbuffer);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGenRenderbuffers'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGenTextures  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGenTextures00
static int tolua_Cocos2d_glGenTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S, 1, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLuint texture;
        glGenTextures(1, &texture);
        tolua_pushnumber(tolua_S, texture);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGenTextures'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGenerateMipmap  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGenerateMipmap00
static int tolua_Cocos2d_glGenerateMipmap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int target = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glGenerateMipmap((GLenum)target );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGenerateMipmap'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetActiveAttrib  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetActiveAttrib00
static int tolua_Cocos2d_glGetActiveAttrib00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        GLsizei length;
        glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
        GLchar* buffer = new GLchar[length];
        GLint size = -1;
        GLenum type = -1;
        glGetActiveAttrib(arg0, arg1, length, NULL, &size, &type, buffer);
        lua_pushnumber(tolua_S, size);
        lua_pushnumber(tolua_S, type);
        //may check
        std::string name = buffer;
        lua_pushstring(tolua_S, name.c_str());
        CC_SAFE_DELETE_ARRAY(buffer);
    }
    return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetActiveAttrib'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetActiveUniform  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetActiveUniform00
static int tolua_Cocos2d_glGetActiveUniform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        GLsizei length;
        glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
        GLchar* buffer = new GLchar[length];
        GLint size = -1;
        GLenum type = -1;
        glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, buffer);
        lua_pushnumber(tolua_S, size);
        lua_pushnumber(tolua_S, type);
        //may check
        std::string name = buffer;
        lua_pushstring(tolua_S, name.c_str());
        CC_SAFE_DELETE_ARRAY(buffer);
    }
    return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetActiveUniform'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetAttachedShaders */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetAttachedShaders00
static int tolua_Cocos2d_glGetAttachedShaders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
     	GLsizei length;
        glGetProgramiv(arg0, GL_ATTACHED_SHADERS, &length);
        GLuint* buffer = new GLuint[length];
        memset(buffer, 0, length * sizeof(GLuint));
        glGetAttachedShaders(arg0, length, NULL, buffer);
        lua_newtable(tolua_S);                                        /* L: table */
        int index = 1;
        for (int  i = 0; i < length; i++)
        {
            lua_pushnumber(tolua_S, buffer[i]);                       /* L: table value */
            lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
            ++index;
        }
        CC_SAFE_DELETE_ARRAY(buffer);        
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetAttachedShaders'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetAttribLocation  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetAttribLocation00
static int tolua_Cocos2d_glGetAttribLocation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)          ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int program = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        const char*  name    = (const char*)tolua_tostring(tolua_S, 2, "");
        int retVal = glGetAttribLocation((GLuint)program , name  );
        lua_pushnumber(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetAttribLocation'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetError  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetError00
static int tolua_Cocos2d_glGetError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S, 1, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int retVal = glGetError();
        lua_pushnumber(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetAttribLocation'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetProgramInfoLog */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetProgramInfoLog00
static int tolua_Cocos2d_glGetProgramInfoLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        GLsizei length;
        glGetProgramiv(arg0, GL_INFO_LOG_LENGTH, &length);
        GLchar* src = new GLchar[length];
        glGetProgramInfoLog(arg0, length, NULL, src);
        lua_pushstring(tolua_S, src);
        CC_SAFE_DELETE_ARRAY(src);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetProgramInfoLog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetProgramiv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetProgramiv00
static int tolua_Cocos2d_glGetProgramiv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1  = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        GLint ret;
        glGetProgramiv(arg0, arg1, &ret);
        lua_pushnumber(tolua_S, ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetProgramiv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetShaderInfoLog  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetShaderInfoLog00
static int tolua_Cocos2d_glGetShaderInfoLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        GLsizei length;
        glGetShaderiv(arg0, GL_INFO_LOG_LENGTH, &length);
        GLchar* src = new GLchar[length];
        glGetShaderInfoLog(arg0, length, NULL, src);
        lua_pushstring(tolua_S, src);
        CC_SAFE_DELETE_ARRAY(src);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetShaderInfoLog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetShaderSource  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetShaderSource00
static int tolua_Cocos2d_glGetShaderSource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        GLsizei length;
        glGetShaderiv(arg0, GL_SHADER_SOURCE_LENGTH, &length);
        GLchar* src = new GLchar[length];
        glGetShaderSource(arg0, length, NULL, src);
        lua_pushstring(tolua_S, src);
        CC_SAFE_DELETE_ARRAY(src);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetShaderSource'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetShaderiv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetShaderiv00
static int tolua_Cocos2d_glGetShaderiv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1  = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        GLint ret;
        glGetShaderiv(arg0, arg1, &ret);
        lua_pushnumber(tolua_S, ret);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetShaderiv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetTexParameterfv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetTexParameterfv00
static int tolua_Cocos2d_glGetTexParameterfv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1  = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        GLfloat param;
        glGetTexParameterfv(arg0, arg1, &param);
        lua_pushnumber(tolua_S, param);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetTexParameterfv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* function: glGetUniformLocation  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetUniformLocation00
static int tolua_Cocos2d_glGetUniformLocation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isstring(tolua_S, 2,0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        const char*  arg1 = tolua_tostring(tolua_S, 2, "");
        int retVal = glGetUniformLocation((GLuint)arg0 , arg1  );
        lua_pushnumber(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetUniformLocation'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glGetUniformfv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glGetUniformfv00
static int tolua_Cocos2d_glGetUniformfv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S, 2,0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        
       	GLsizei length;
        glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
        GLchar* namebuffer = new GLchar[length];
        GLint size = -1;
        GLenum type = -1;
        
        glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, namebuffer);
        CC_SAFE_DELETE_ARRAY(namebuffer);
        
        int usize = 0;
        int utype = 0;
        switch(type) {
                // float
            case GL_FLOAT:
                usize = 1;
                utype = GL_FLOAT;
                break;
            case GL_FLOAT_MAT2:
                usize = 2 * 2;
                utype = GL_FLOAT;
                break;
            case GL_FLOAT_MAT3:
                usize = 3 * 3;
                utype = GL_FLOAT;
                break;
            case GL_FLOAT_MAT4:
                usize = 4 * 4;
                utype = GL_FLOAT;
                break;
            case GL_FLOAT_VEC2:
                usize = 2;
                utype = GL_FLOAT;
                break;
            case GL_FLOAT_VEC3:
                usize = 3;
                utype = GL_FLOAT;
                break;
            case GL_FLOAT_VEC4:
                usize = 4;
                utype = GL_FLOAT;
                break;
                
                // int
            case GL_INT:
                usize = 1;
                utype = GL_INT;
                break;
            case GL_INT_VEC2:
                usize = 1;
                utype = GL_INT;
                break;
            case GL_INT_VEC3:
                usize = 1;
                utype = GL_INT;
                break;
            case GL_INT_VEC4:
                usize = 1;
                utype = GL_INT;
                break;
                
            default:
#ifndef TOLUA_RELEASE
                tolua_error(tolua_S,"#ferror in function 'glGetUniformfv'.",&tolua_err);
                return 0;
#endif
                break;
        }
        if( utype == GL_FLOAT) {
            GLfloat* param = new GLfloat[usize];
            glGetUniformfv(arg0, arg1, param);
            
            lua_newtable(tolua_S);                                        /* L: table */
            int index = 1;
            for (int  i = 0; i < usize; i++)
            {
                lua_pushnumber(tolua_S, param[i]);                       /* L: table value */
                lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
                ++index;
            }
            CC_SAFE_DELETE_ARRAY(param);
            
        } else if( utype == GL_INT ) {
            GLint* param = new GLint[usize];
            glGetUniformiv(arg0, arg1, param);
            
            lua_newtable(tolua_S);                                        /* L: table */
            int index = 1;
            for (int  i = 0; i < usize; i++)
            {
                lua_pushnumber(tolua_S, param[i]);                       /* L: table value */
                lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
                ++index;
            }
            CC_SAFE_DELETE_ARRAY(param);
        }

    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glGetUniformfv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glHint  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glHint00
static int tolua_Cocos2d_glHint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,2,0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int  arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        glHint((GLenum)arg0 , (GLenum)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glHint'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsBuffer  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsBuffer00
static int tolua_Cocos2d_glIsBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsBuffer((GLuint)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsBuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsEnabled  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsEnabled00
static int tolua_Cocos2d_glIsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsEnabled((GLenum)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsEnabled'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsFramebuffer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsFramebuffer00
static int tolua_Cocos2d_glIsFramebuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsFramebuffer((GLuint)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsFramebuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsProgram  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsProgram00
static int tolua_Cocos2d_glIsProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsProgram((GLuint)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsRenderbuffer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsRenderbuffer00
static int tolua_Cocos2d_glIsRenderbuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsRenderbuffer((GLuint)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsRenderbuffer'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsShader */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsShader00
static int tolua_Cocos2d_glIsShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsShader((GLuint)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsShader'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glIsTexture  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glIsTexture00
static int tolua_Cocos2d_glIsTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        bool retVal = glIsTexture((GLuint)arg0  );
        lua_pushboolean(tolua_S, retVal);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glIsTexture'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glLineWidth  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glLineWidth00
static int tolua_Cocos2d_glLineWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        float arg0  = (float)tolua_tonumber(tolua_S, 1, 0);
        glLineWidth((GLfloat)arg0  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glLineWidth'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glLinkProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glLinkProgram00
static int tolua_Cocos2d_glLinkProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glLinkProgram((GLuint)arg0  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glLinkProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glPixelStorei  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glPixelStorei00
static int tolua_Cocos2d_glPixelStorei00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0  = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1  = (int)tolua_tonumber(tolua_S, 2, 0);
        glPixelStorei((GLenum)arg0 , (GLint)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glPixelStorei'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glPolygonOffset */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glPolygonOffset00
static int tolua_Cocos2d_glPolygonOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err)            ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0  = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1  = (int)tolua_tonumber(tolua_S, 2, 0);
        glPolygonOffset((GLfloat)arg0 , (GLfloat)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glPolygonOffset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* function: glReadPixels  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glReadPixels00
static int tolua_Cocos2d_glReadPixels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S,1,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,6,0,&tolua_err)            ||
        !tolua_isnumber(tolua_S,7, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S,8, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0  = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1  = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2  = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3  = (int)tolua_tonumber(tolua_S, 4, 0);
        unsigned int arg4  = (unsigned int)tolua_tonumber(tolua_S, 5, 0);
        unsigned int arg5  = (unsigned int)tolua_tonumber(tolua_S, 6, 0);
        
        long length   = (long)tolua_tonumber(tolua_S,7,0);
        unsigned char* unit8Array     = new unsigned char[length];
        if (NULL == unit8Array)
        {
            return  0;
        }
        for (int i = 0; i < length; i++)
        {
            unit8Array[i] = 0;
        }

        glReadPixels((GLint)arg0 , (GLint)arg1 , (GLsizei)arg2 , (GLsizei)arg3 , (GLenum)arg4 , (GLenum)arg5 , (GLvoid*)unit8Array);
        
        lua_newtable(tolua_S);                                              /* L: table */
        int index = 1;
        for (int i = 0; i < length; i++)
        {
            lua_pushnumber(tolua_S, unit8Array[i]);                   /* L: unit8 value */
            lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
            ++index;
        }
        
        CC_SAFE_DELETE_ARRAY(unit8Array);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glReadPixels'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glReleaseShaderCompiler  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glReleaseShaderCompiler00
static int tolua_Cocos2d_glReleaseShaderCompiler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnoobj(tolua_S, 1, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        glReleaseShaderCompiler( );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glReleaseShaderCompiler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glRenderbufferStorage  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glRenderbufferStorage00
static int tolua_Cocos2d_glRenderbufferStorage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        glRenderbufferStorage((GLenum)arg0 , (GLenum)arg1 , (GLsizei)arg2 , (GLsizei)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glRenderbufferStorage'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glSampleCoverage */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glSampleCoverage00
static int tolua_Cocos2d_glSampleCoverage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        unsigned short arg1 = (unsigned short)tolua_tonumber(tolua_S, 2, 0);
        glSampleCoverage((GLclampf)arg0 , (GLboolean)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glSampleCoverage'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glScissor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glScissor00
static int tolua_Cocos2d_glScissor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        glScissor((GLint)arg0 , (GLint)arg1 , (GLsizei)arg2 , (GLsizei)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glScissor'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glShaderSource  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glShaderSource00
static int tolua_Cocos2d_glShaderSource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        const char* arg1 = tolua_tostring(tolua_S, 2, "");
        glShaderSource(arg0, 1, &arg1, NULL);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glShaderSource'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glStencilFunc */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glStencilFunc00
static int tolua_Cocos2d_glStencilFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int arg2 = (unsigned int)tolua_tonumber(tolua_S, 3, 0);        
        glStencilFunc((GLenum)arg0 , (GLint)arg1 , (GLuint)arg2  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glStencilFunc'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glStencilFuncSeparate  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glStencilFuncSeparate00
static int tolua_Cocos2d_glStencilFuncSeparate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        unsigned int arg3 = (unsigned int)tolua_tonumber(tolua_S, 4, 0);
        glStencilFuncSeparate((GLenum)arg0 , (GLenum)arg1 , (GLint)arg2 , (GLuint)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glStencilFuncSeparate'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glStencilMask  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glStencilMask00
static int tolua_Cocos2d_glStencilMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glStencilMask((GLuint)arg0);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glStencilMask'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glStencilMaskSeparate  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glStencilMaskSeparate00
static int tolua_Cocos2d_glStencilMaskSeparate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        glStencilMaskSeparate((GLenum)arg0 , (GLuint)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glStencilMaskSeparate'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glStencilOp  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glStencilOp00
static int tolua_Cocos2d_glStencilOp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int arg2 = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        glStencilOp((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glStencilOp'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glStencilOpSeparate */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glStencilOpSeparate00
static int tolua_Cocos2d_glStencilOpSeparate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int arg2 = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        unsigned int arg3 = (unsigned int)tolua_tonumber(tolua_S, 4, 0);
        glStencilOpSeparate((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2 , (GLenum)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glStencilOpSeparate'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glTexImage2D  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glTexImage2D00
static int tolua_Cocos2d_glTexImage2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 7, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 8, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 9, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 10, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 11, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        int arg4 = (int)tolua_tonumber(tolua_S, 5, 0);
        int arg5 = (int)tolua_tonumber(tolua_S, 6, 0);
        unsigned int arg6 = (unsigned int)tolua_tonumber(tolua_S, 7, 0);
        unsigned int arg7 = (unsigned int)tolua_tonumber(tolua_S, 8, 0);
        unsigned int arg8 = (unsigned int)tolua_tonumber(tolua_S, 9, 0);
        
        unsigned char* unit8Array     = new unsigned char[arg8];
        if (NULL == unit8Array)
        {
            return  0;
        }
        
        for (unsigned int i = 1; i <= arg8; i++)
        {
            unit8Array[i-1] = (unsigned char)tolua_tofieldnumber(tolua_S, 10, i, 0);
        }
        
       	glTexImage2D((GLenum)arg0 , (GLint)arg1 , (GLint)arg2 , (GLsizei)arg3 , (GLsizei)arg4 , (GLint)arg5 , (GLenum)arg6 , (GLenum)arg7 , (GLvoid*)unit8Array);

//        lua_newtable(tolua_S);                                         /* L: table */
//        int index = 1;
//        for (int i = 0; i < arg8; i++)
//        {
//            lua_pushnumber(tolua_S, unit8Array[i]);                   /* L: unit8 value */
//            lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
//            ++index;
//        }

        
        CC_SAFE_DELETE_ARRAY(unit8Array);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glTexImage2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glTexParameterf  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glTexParameterf00
static int tolua_Cocos2d_glTexParameterf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        glTexParameterf((GLenum)arg0 , (GLenum)arg1 , (GLfloat)arg2  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glTexParameterf'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glTexParameteri */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glTexParameteri00
static int tolua_Cocos2d_glTexParameteri00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        unsigned int arg1 = (unsigned int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        glTexParameteri((GLenum)arg0 , (GLenum)arg1 , (GLint)arg2  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glTexParameteri'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glTexSubImage2D  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glTexSubImage2D00
static int tolua_Cocos2d_glTexSubImage2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 7, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 8, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 9, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 10, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        int arg4 = (int)tolua_tonumber(tolua_S, 5, 0);
        int arg5 = (int)tolua_tonumber(tolua_S, 6, 0);
        unsigned int arg6 = (unsigned int)tolua_tonumber(tolua_S, 7, 0);
        unsigned int arg7 = (unsigned int)tolua_tonumber(tolua_S, 8, 0);
        unsigned int arg8 = (unsigned int)tolua_tonumber(tolua_S, 9, 0);
        
        unsigned char* unit8Array     = new unsigned char[arg8];
        if (NULL == unit8Array)
        {
            return  0;
        }
        for (unsigned int i = 0; i < arg8; i++)
        {
            unit8Array[i] = 0;
        }
        
        glTexSubImage2D((GLenum)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3 , (GLsizei)arg4 , (GLsizei)arg5 , (GLenum)arg6 , (GLenum)arg7 , (GLvoid*)unit8Array  );
        
        lua_newtable(tolua_S);                                         /* L: table */
        int index = 1;
        for (unsigned int i = 0; i < arg8; i++)
        {
            lua_pushnumber(tolua_S, unit8Array[i]);                   /* L: unit8 value */
            lua_rawseti(tolua_S, -2, index);                          /* table[index] = value, L: table */
            ++index;
        }
        
        CC_SAFE_DELETE_ARRAY(unit8Array);
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glTexSubImage2D'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform1f */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform1f00
static int tolua_Cocos2d_glUniform1f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        glUniform1f((GLint)arg0 , (GLfloat)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform1f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform1fv */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform1fv00
static int tolua_Cocos2d_glUniform1fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray     = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform1fv((GLint)arg0 , (GLsizei)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform1fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform1i */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform1i00
static int tolua_Cocos2d_glUniform1i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        glUniform1i((GLint)arg0 , (GLint)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform1i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform1iv */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform1iv00
static int tolua_Cocos2d_glUniform1iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int* intArray   = new int[arg2];
        if (NULL == intArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            intArray[i-1] = (int)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform1iv((GLint)arg0 , (GLsizei)arg1 , (GLint*)intArray  );
        CC_SAFE_DELETE_ARRAY(intArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform1fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform2f  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform2f00
static int tolua_Cocos2d_glUniform2f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        glUniform2f((GLint)arg0 , (GLfloat)arg1 , (GLfloat)arg2);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform2f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform2fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform2fv00
static int tolua_Cocos2d_glUniform2fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray     = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform1fv((GLint)arg0 , (GLsizei)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform2fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform2i */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform2i00
static int tolua_Cocos2d_glUniform2i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        glUniform2i((GLint)arg0 , (GLint)arg1 , (GLint)arg2  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform2i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform2iv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform2iv00
static int tolua_Cocos2d_glUniform2iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int* intArray   = new int[arg2];
        if (NULL == intArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            intArray[i-1] = (int)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform2iv((GLint)arg0 , (GLsizei)arg1 , (GLint*)intArray  );
        CC_SAFE_DELETE_ARRAY(intArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform2iv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform3f */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform3f00
static int tolua_Cocos2d_glUniform3f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        glUniform3f((GLint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform4f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform3fv */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform3fv00
static int tolua_Cocos2d_glUniform3fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray     = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform1fv((GLint)arg0 , (GLsizei)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform3fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform3i  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform3i00
static int tolua_Cocos2d_glUniform3i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        glUniform3i((GLint)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform3i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform3iv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform3iv00
static int tolua_Cocos2d_glUniform3iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int* intArray   = new int[arg2];
        if (NULL == intArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            intArray[i-1] = (int)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform3iv((GLint)arg0 , (GLsizei)arg1 , (GLint*)intArray  );
        CC_SAFE_DELETE_ARRAY(intArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform3iv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform4f  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform4f00
static int tolua_Cocos2d_glUniform4f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 6, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        int arg4 = (int)tolua_tonumber(tolua_S, 5, 0);
        glUniform4f((GLint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3 , (GLfloat)arg4  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform4f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform4fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform4fv00
static int tolua_Cocos2d_glUniform4fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray     = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform4fv((GLint)arg0 , (GLsizei)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform4fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform4i  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform4i00
static int tolua_Cocos2d_glUniform4i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 6, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        int arg4 = (int)tolua_tonumber(tolua_S, 5, 0);
        glUniform4i((GLint)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3 , (GLint)arg4  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform4i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniform4iv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniform4iv00
static int tolua_Cocos2d_glUniform4iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int* intArray   = new int[arg2];
        if (NULL == intArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            intArray[i-1] = (int)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniform4iv((GLint)arg0 , (GLsizei)arg1 , (GLint*)intArray  );
        CC_SAFE_DELETE_ARRAY(intArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniform4iv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniformMatrix2fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniformMatrix2fv00
static int tolua_Cocos2d_glUniformMatrix2fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        unsigned short arg1 = (unsigned short)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray   = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        glUniformMatrix2fv(arg0, 1, (GLboolean)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniformMatrix2fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniformMatrix3fv */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniformMatrix3fv00
static int tolua_Cocos2d_glUniformMatrix3fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        unsigned short arg1 = (unsigned short)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray   = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        
        glUniformMatrix3fv(arg0, 1, (GLboolean)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniformMatrix3fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUniformMatrix4fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUniformMatrix4fv00
static int tolua_Cocos2d_glUniformMatrix4fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isboolean(tolua_S, 2, 0, &tolua_err)        ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 4, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        bool arg1 = (bool)tolua_toboolean(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        float* floatArray   = new float[arg2];
        if (NULL == floatArray)
        {
            return  0;
        }
        
        for (int i = 1; i <= arg2; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 4, i, 0);
        }
        
        glUniformMatrix4fv(arg0, 1, (GLboolean)arg1 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUniformMatrix4fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glUseProgram  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glUseProgram00
static int tolua_Cocos2d_glUseProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glUseProgram((GLuint)arg0  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glUseProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glValidateProgram  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glValidateProgram00
static int tolua_Cocos2d_glValidateProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        glValidateProgram((GLuint)arg0  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glValidateProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib1f */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib1f00
static int tolua_Cocos2d_glVertexAttrib1f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1          = (int)tolua_tonumber(tolua_S, 2, 0);
        glVertexAttrib1f((GLuint)arg0 , (GLfloat)arg1  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib1f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib1fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib1fvf00
static int tolua_Cocos2d_glVertexAttrib1fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        float* floatArray   = new float[arg1];
        if (NULL == floatArray)
        {
            return  0;
        }
        
        for (int i = 1; i <= arg1; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        
        glVertexAttrib1fv((GLuint)arg0 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib1fv'.",&tolua_err);
    return 0;
#endif

}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib2f  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib2f00
static int tolua_Cocos2d_glVertexAttrib2f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1          = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2          = (int)tolua_tonumber(tolua_S, 3, 0);
        glVertexAttrib2f((GLuint)arg0 , (GLfloat)arg1 , (GLfloat)arg2  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib2f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib2fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib2fv00
static int tolua_Cocos2d_glVertexAttrib2fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        float* floatArray   = new float[arg1];
        if (NULL == floatArray)
        {
            return  0;
        }
        
        for (int i = 1; i <= arg1; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        
        glVertexAttrib2fv((GLuint)arg0 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib2fv'.",&tolua_err);
    return 0;
#endif
    
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib3f  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib3f00
static int tolua_Cocos2d_glVertexAttrib3f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1          = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2          = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3          = (int)tolua_tonumber(tolua_S, 4, 0);
        glVertexAttrib3f((GLuint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib3f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib3fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib3fv00
static int tolua_Cocos2d_glVertexAttrib3fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        float* floatArray   = new float[arg1];
        if (NULL == floatArray)
        {
            return  0;
        }
        
        for (int i = 1; i <= arg1; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        
        glVertexAttrib3fv((GLuint)arg0 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib3fv'.",&tolua_err);
    return 0;
#endif
    
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib4f  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib4f00
static int tolua_Cocos2d_glVertexAttrib4f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 6, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1          = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2          = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3          = (int)tolua_tonumber(tolua_S, 4, 0);
        int arg4          = (int)tolua_tonumber(tolua_S, 5, 0);
        glVertexAttrib4f((GLuint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3 , (GLfloat)arg4  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib4f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttrib4fv  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttrib4fv00
static int tolua_Cocos2d_glVertexAttrib4fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_istable(tolua_S, 3, 0, &tolua_err)          ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        float* floatArray   = new float[arg1];
        if (NULL == floatArray)
        {
            return  0;
        }
        
        for (int i = 1; i <= arg1; i++)
        {
            floatArray[i-1] = (float)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        
        glVertexAttrib4fv((GLuint)arg0 , (GLfloat*)floatArray  );
        CC_SAFE_DELETE_ARRAY(floatArray);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttrib4fv'.",&tolua_err);
    return 0;
#endif
    
}
#endif //#ifndef TOLUA_DISABLE

/* function: glVertexAttribPointer  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glVertexAttribPointer00
static int tolua_Cocos2d_glVertexAttribPointer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isboolean(tolua_S, 4, 0, &tolua_err)        ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 6, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 7, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        unsigned int arg0 = (unsigned int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        unsigned int arg2 = (unsigned int)tolua_tonumber(tolua_S, 3, 0);
        bool arg3 = tolua_toboolean(tolua_S, 4, 0);
        int arg4 = (int)tolua_tonumber(tolua_S, 5, 0);
        //int arg5 = (int)tolua_tonumber(tolua_S, 7, 0);
        glVertexAttribPointer((GLuint)arg0 , (GLint)arg1 , (GLenum)arg2 , (GLboolean)arg3 , (GLsizei)arg4 , (GLvoid*)NULL);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glVertexAttribPointer'.",&tolua_err);
    return 0;
#endif
    
}
#endif //#ifndef TOLUA_DISABLE

/* function: glViewport  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glViewport00
static int tolua_Cocos2d_glViewport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)         ||
        !tolua_isnumber(tolua_S, 4, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 5, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        int arg1 = (int)tolua_tonumber(tolua_S, 2, 0);
        int arg2 = (int)tolua_tonumber(tolua_S, 3, 0);
        int arg3 = (int)tolua_tonumber(tolua_S, 4, 0);
        glViewport((GLint)arg0 , (GLint)arg1 , (GLsizei)arg2 , (GLsizei)arg3  );
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glViewport'.",&tolua_err);
    return 0;
#endif
    
}
#endif //#ifndef TOLUA_DISABLE

/* function: glEnableVertexAttribs  */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_glEnableVertexAttribs00
static int tolua_Cocos2d_glEnableVertexAttribs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isnumber(tolua_S, 1, 0, &tolua_err)         ||
        !tolua_isnoobj(tolua_S, 2, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        int arg0 = (int)tolua_tonumber(tolua_S, 1, 0);
        ccGLEnableVertexAttribs(arg0);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'glEnableVertexAttribs'.",&tolua_err);
    return 0;
#endif
    
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_new00
static int tolua_Cocos2d_CCGLProgram_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            GLProgram* tolua_ret = (GLProgram*)  Mtolua_new((GLProgram)());
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCGLProgram");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_new00_local
static int tolua_Cocos2d_CCGLProgram_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            GLProgram* tolua_ret = (GLProgram*)  Mtolua_new((GLProgram)());
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCGLProgram");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_delete00
static int tolua_Cocos2d_CCGLProgram_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
        Mtolua_delete(self);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithVertexShaderByteArray of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_initWithVertexShaderByteArray00
static int tolua_Cocos2d_CCGLProgram_initWithVertexShaderByteArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        const char* vShaderByteArray = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* fShaderByteArray = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithVertexShaderByteArray'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->initWithVertexShaderByteArray(vShaderByteArray,fShaderByteArray);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'initWithVertexShaderByteArray'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithVertexShaderFilename of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_initWithVertexShaderFilename00
static int tolua_Cocos2d_CCGLProgram_initWithVertexShaderFilename00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        const char* vShaderFilename = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* fShaderFilename = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithVertexShaderFilename'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->initWithVertexShaderFilename(vShaderFilename,fShaderFilename);
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'initWithVertexShaderFilename'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAttribute of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_addAttribute00
static int tolua_Cocos2d_CCGLProgram_addAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        const char* attributeName = ((const char*)  tolua_tostring(tolua_S,2,0));
        unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAttribute'", NULL);
#endif
        {
            self->addAttribute(attributeName,index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addAttribute'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: link of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_link00
static int tolua_Cocos2d_CCGLProgram_link00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'link'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->link();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'link'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: use of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_use00
static int tolua_Cocos2d_CCGLProgram_use00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'use'", NULL);
#endif
        {
            self->use();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'use'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateUniforms of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_updateUniforms00
static int tolua_Cocos2d_CCGLProgram_updateUniforms00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateUniforms'", NULL);
#endif
        {
            self->updateUniforms();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'updateUniforms'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUniformLocationForName of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_getUniformLocationForName00
static int tolua_Cocos2d_CCGLProgram_getUniformLocationForName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUniformLocationForName'", NULL);
#endif
        {
            int tolua_ret = (int)  self->getUniformLocationForName(name);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getUniformLocationForName'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith1i of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith1i00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith1i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int i1 = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith1i'", NULL);
#endif
        {
            self->setUniformLocationWith1i(location,i1);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith1i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith2i of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith2i00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith2i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int i1 = ((int)  tolua_tonumber(tolua_S,3,0));
        int i2 = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith2i'", NULL);
#endif
        {
            self->setUniformLocationWith2i(location,i1,i2);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith2i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith3i of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith3i00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith3i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int i1 = ((int)  tolua_tonumber(tolua_S,3,0));
        int i2 = ((int)  tolua_tonumber(tolua_S,4,0));
        int i3 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith3i'", NULL);
#endif
        {
            self->setUniformLocationWith3i(location,i1,i2,i3);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith3i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith4i of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith4i00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith4i00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,7,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int i1 = ((int)  tolua_tonumber(tolua_S,3,0));
        int i2 = ((int)  tolua_tonumber(tolua_S,4,0));
        int i3 = ((int)  tolua_tonumber(tolua_S,5,0));
        int i4 = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith4i'", NULL);
#endif
        {
            self->setUniformLocationWith4i(location,i1,i2,i3,i4);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith4i'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith2iv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith2iv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith2iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int ints = ((int)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfArrays = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith2iv'", NULL);
#endif
        {
            self->setUniformLocationWith2iv(location,&ints,numberOfArrays);
            tolua_pushnumber(tolua_S,(lua_Number)ints);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith2iv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith3iv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith3iv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith3iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int ints = ((int)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfArrays = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith3iv'", NULL);
#endif
        {
            self->setUniformLocationWith3iv(location,&ints,numberOfArrays);
            tolua_pushnumber(tolua_S,(lua_Number)ints);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith3iv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith4iv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith4iv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith4iv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        int ints = ((int)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfArrays = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith4iv'", NULL);
#endif
        {
            self->setUniformLocationWith4iv(location,&ints,numberOfArrays);
            tolua_pushnumber(tolua_S,(lua_Number)ints);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith4iv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith1f of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith1f00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith1f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float f1 = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith1f'", NULL);
#endif
        {
            self->setUniformLocationWith1f(location,f1);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith1f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith2f of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith2f00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith2f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float f1 = ((float)  tolua_tonumber(tolua_S,3,0));
        float f2 = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith2f'", NULL);
#endif
        {
            self->setUniformLocationWith2f(location,f1,f2);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith2f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith3f of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith3f00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith3f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float f1 = ((float)  tolua_tonumber(tolua_S,3,0));
        float f2 = ((float)  tolua_tonumber(tolua_S,4,0));
        float f3 = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith3f'", NULL);
#endif
        {
            self->setUniformLocationWith3f(location,f1,f2,f3);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith3f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith4f of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith4f00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith4f00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,7,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float f1 = ((float)  tolua_tonumber(tolua_S,3,0));
        float f2 = ((float)  tolua_tonumber(tolua_S,4,0));
        float f3 = ((float)  tolua_tonumber(tolua_S,5,0));
        float f4 = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith4f'", NULL);
#endif
        {
            self->setUniformLocationWith4f(location,f1,f2,f3,f4);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith4f'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith2fv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith2fv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith2fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float floats = ((float)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfArrays = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith2fv'", NULL);
#endif
        {
            self->setUniformLocationWith2fv(location,&floats,numberOfArrays);
            tolua_pushnumber(tolua_S,(lua_Number)floats);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith2fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith3fv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith3fv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith3fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float floats = ((float)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfArrays = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith3fv'", NULL);
#endif
        {
            self->setUniformLocationWith3fv(location,&floats,numberOfArrays);
            tolua_pushnumber(tolua_S,(lua_Number)floats);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith3fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWith4fv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWith4fv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWith4fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float floats = ((float)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfArrays = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWith4fv'", NULL);
#endif
        {
            self->setUniformLocationWith4fv(location,&floats,numberOfArrays);
            tolua_pushnumber(tolua_S,(lua_Number)floats);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWith4fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformLocationWithMatrix4fv of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformLocationWithMatrix4fv00
static int tolua_Cocos2d_CCGLProgram_setUniformLocationWithMatrix4fv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
        int location = ((int)  tolua_tonumber(tolua_S,2,0));
        float matrixArray = ((float)  tolua_tonumber(tolua_S,3,0));
        unsigned int numberOfMatrices = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformLocationWithMatrix4fv'", NULL);
#endif
        {
            self->setUniformLocationWithMatrix4fv(location,&matrixArray,numberOfMatrices);
            tolua_pushnumber(tolua_S,(lua_Number)matrixArray);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationWithMatrix4fv'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUniformsForBuiltins of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_setUniformsForBuiltins00
static int tolua_Cocos2d_CCGLProgram_setUniformsForBuiltins00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUniformsForBuiltins'", NULL);
#endif
        {
            self->setUniformsForBuiltins();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformsForBuiltins'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: vertexShaderLog of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_vertexShaderLog00
static int tolua_Cocos2d_CCGLProgram_vertexShaderLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'vertexShaderLog'", NULL);
#endif
        {
            const char* tolua_ret = (const char*)  self->vertexShaderLog();
            tolua_pushstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'vertexShaderLog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fragmentShaderLog of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_fragmentShaderLog00
static int tolua_Cocos2d_CCGLProgram_fragmentShaderLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fragmentShaderLog'", NULL);
#endif
        {
            const char* tolua_ret = (const char*)  self->fragmentShaderLog();
            tolua_pushstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'fragmentShaderLog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: programLog of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_programLog00
static int tolua_Cocos2d_CCGLProgram_programLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'programLog'", NULL);
#endif
        {
            const char* tolua_ret = (const char*)  self->programLog();
            tolua_pushstring(tolua_S,(const char*)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'programLog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_reset00
static int tolua_Cocos2d_CCGLProgram_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'", NULL);
#endif
        {
            self->reset();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getProgram of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_getProgram00
static int tolua_Cocos2d_CCGLProgram_getProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        GLProgram* self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getProgram'", NULL);
#endif
        {
            unsigned const int tolua_ret = ( unsigned const int)  self->getProgram();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getProgram'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* method: create of class  GLProgram */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGLProgram_create00
static int tolua_Cocos2d_CCGLProgram_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCGLProgram",0,&tolua_err) ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)              ||
        !tolua_isstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const char* arg0 = tolua_tostring(tolua_S, 2, "");
        const char* arg1 = tolua_tostring(tolua_S, 3, "");
        GLProgram* tolua_ret = new GLProgram();
        tolua_ret->autorelease();
        tolua_ret->initWithVertexShaderFilename(arg0, arg1);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCGLProgram");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif 
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_new00
static int tolua_Cocos2d_CCShaderCache_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ShaderCache* tolua_ret = (ShaderCache*)  Mtolua_new((ShaderCache)());
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCShaderCache");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_new00_local
static int tolua_Cocos2d_CCShaderCache_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ShaderCache* tolua_ret = (ShaderCache*)  Mtolua_new((ShaderCache)());
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCShaderCache");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_delete00
static int tolua_Cocos2d_CCShaderCache_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ShaderCache* self = (ShaderCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedShaderCache of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_sharedShaderCache00
static int tolua_Cocos2d_CCShaderCache_sharedShaderCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ShaderCache* tolua_ret = (ShaderCache*)  ShaderCache::sharedShaderCache();
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCShaderCache");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedShaderCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeSharedShaderCache of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_purgeSharedShaderCache00
static int tolua_Cocos2d_CCShaderCache_purgeSharedShaderCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ShaderCache::purgeSharedShaderCache();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeSharedShaderCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadDefaultShaders of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_loadDefaultShaders00
static int tolua_Cocos2d_CCShaderCache_loadDefaultShaders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ShaderCache* self = (ShaderCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadDefaultShaders'", NULL);
#endif
  {
   self->loadDefaultShaders();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadDefaultShaders'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reloadDefaultShaders of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_reloadDefaultShaders00
static int tolua_Cocos2d_CCShaderCache_reloadDefaultShaders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ShaderCache* self = (ShaderCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reloadDefaultShaders'", NULL);
#endif
  {
   self->reloadDefaultShaders();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reloadDefaultShaders'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: programForKey of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_programForKey00
static int tolua_Cocos2d_CCShaderCache_programForKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ShaderCache* self = (ShaderCache*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'programForKey'", NULL);
#endif
  {
   GLProgram* tolua_ret = (GLProgram*)  self->programForKey(key);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGLProgram");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'programForKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addProgram of class  ShaderCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShaderCache_addProgram00
static int tolua_Cocos2d_CCShaderCache_addProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShaderCache",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCGLProgram",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ShaderCache* self = (ShaderCache*)  tolua_tousertype(tolua_S,1,0);
  GLProgram* program = ((GLProgram*)  tolua_tousertype(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addProgram'", NULL);
#endif
  {
   self->addProgram(program,key);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addProgram'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE



TOLUA_API int tolua_opengl_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_gl_type(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
      tolua_cclass(tolua_S,"GLNode","GLNode","CCNode",tolua_collect_GLNode);
        tolua_beginmodule(tolua_S,"GLNode");
            tolua_function(tolua_S, "create", tolua_Cocos2d_GLNode_create00);
            tolua_function(tolua_S, "registerScriptDrawHandler", tolua_Cocos2d_GLNode_registerScriptDrawHandler00);
            tolua_function(tolua_S, "unregisterScriptDrawHandler", tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00);
            tolua_function(tolua_S, "setShaderProgram", tolua_Cocos2d_GLNode_setShaderProgram00);
        tolua_endmodule(tolua_S);
    tolua_module(tolua_S, "gl", 0);
    tolua_beginmodule(tolua_S,"gl");
        tolua_function(tolua_S, "getSupportedExtensions", tolua_Cocos2d_glGetSupportedExtensions00);
        tolua_function(tolua_S, "activeTexture", tolua_Cocos2d_glActiveTexture00);
        tolua_function(tolua_S, "_attachShader", tolua_Cocos2d_glAttachShader00);
        tolua_function(tolua_S, "_bindAttribLocation", tolua_Cocos2d_glBindAttribLocation00);
        tolua_function(tolua_S, "_bindBuffer", tolua_Cocos2d_glBindBuffer00);
        tolua_function(tolua_S, "_bindFramebuffer", tolua_Cocos2d_glBindBuffer00);
        tolua_function(tolua_S, "_bindRenderbuffer", tolua_Cocos2d_glBindRenderbuffer00);
        tolua_function(tolua_S, "_bindTexture", tolua_Cocos2d_glBindTexture00);
        tolua_function(tolua_S, "blendColor", tolua_Cocos2d_glBlendColor00);
        tolua_function(tolua_S, "blendEquation", tolua_Cocos2d_glBlendEquation00);
        tolua_function(tolua_S, "blendEquationSeparate", tolua_Cocos2d_glBlendEquationSeparate00);
        tolua_function(tolua_S, "blendFunc", tolua_Cocos2d_glBlendFunc00);
        tolua_function(tolua_S, "blendFuncSeparate", tolua_Cocos2d_glBlendFuncSeparate00);
        tolua_function(tolua_S, "bufferData", tolua_Cocos2d_glBufferData00);
        tolua_function(tolua_S, "bufferSubData", tolua_Cocos2d_glBufferSubData00);
        tolua_function(tolua_S, "checkFramebufferStatus", tolua_Cocos2d_glCheckFramebufferStatus00);
        tolua_function(tolua_S, "clear", tolua_Cocos2d_glClear00);
        tolua_function(tolua_S, "clearColor", tolua_Cocos2d_glClearColor00);
        tolua_function(tolua_S, "clearDepthf", tolua_Cocos2d_glClearDepthf00);
        tolua_function(tolua_S, "clearStencil", tolua_Cocos2d_glClearStencil00);
        tolua_function(tolua_S, "colorMask", tolua_Cocos2d_glColorMask00);
        tolua_function(tolua_S, "_compileShader", tolua_Cocos2d_glCompileShader00);
        tolua_function(tolua_S, "compressedTexImage2D", tolua_Cocos2d_glCompressedTexImage2D00);
        tolua_function(tolua_S, "compressedTexSubImage2D", tolua_Cocos2d_glCompressedTexSubImage2D00);
        tolua_function(tolua_S, "copyTexImage2D", tolua_Cocos2d_glCopyTexImage2D00);
        tolua_function(tolua_S, "copyTexSubImage2D", tolua_Cocos2d_glCopyTexSubImage2D00);
        tolua_function(tolua_S, "_createProgram", tolua_Cocos2d_glCreateProgram00);
        tolua_function(tolua_S, "_createShader", tolua_Cocos2d_glCreateShader00);
        tolua_function(tolua_S, "cullFace", tolua_Cocos2d_glCullFace00);
        tolua_function(tolua_S, "_deleteBuffer", tolua_Cocos2d_glDeleteBuffers00);
        tolua_function(tolua_S, "_deleteFramebuffer", tolua_Cocos2d_glDeleteFramebuffers00);
        tolua_function(tolua_S, "_deleteProgram", tolua_Cocos2d_glDeleteProgram00);
        tolua_function(tolua_S, "_deleteRenderbuffer", tolua_Cocos2d_glDeleteRenderbuffers00);
        tolua_function(tolua_S, "_deleteShader", tolua_Cocos2d_glDeleteShader00);
        tolua_function(tolua_S, "_deleteTexture", tolua_Cocos2d_glDeleteTextures00);
        tolua_function(tolua_S, "depthFunc", tolua_Cocos2d_glDepthFunc00);
        tolua_function(tolua_S, "depthMask", tolua_Cocos2d_glDepthMask00);
        tolua_function(tolua_S, "depthRangef", tolua_Cocos2d_glDepthRangef00);
        tolua_function(tolua_S, "detachShader", tolua_Cocos2d_glDetachShader00);
        tolua_function(tolua_S, "disable", tolua_Cocos2d_glDisable00);
        tolua_function(tolua_S, "disableVertexAttribArray", tolua_Cocos2d_glDisableVertexAttribArray00);
        tolua_function(tolua_S, "drawArrays", tolua_Cocos2d_glDrawArrays00);
        tolua_function(tolua_S, "drawElements", tolua_Cocos2d_glDrawElements00);
        tolua_function(tolua_S, "enable", tolua_Cocos2d_glEnable00);
        tolua_function(tolua_S, "enableVertexAttribArray", tolua_Cocos2d_glEnableVertexAttribArray00);
        tolua_function(tolua_S, "finish", tolua_Cocos2d_glFinish00);
        tolua_function(tolua_S, "flush", tolua_Cocos2d_glFlush00);
        tolua_function(tolua_S, "framebufferRenderbuffer", tolua_Cocos2d_glFramebufferRenderbuffer00);
        tolua_function(tolua_S, "framebufferTexture2D", tolua_Cocos2d_glFramebufferTexture2D00);
        tolua_function(tolua_S, "frontFace", tolua_Cocos2d_glFrontFace00);
        tolua_function(tolua_S, "_createBuffer", tolua_Cocos2d_glGenBuffers00);
        tolua_function(tolua_S, "_createFramebuffer", tolua_Cocos2d_glGenFramebuffers00);
        tolua_function(tolua_S, "_createRenderbuffer", tolua_Cocos2d_glGenRenderbuffers00);
        tolua_function(tolua_S, "_createTexture", tolua_Cocos2d_glGenTextures00);
        tolua_function(tolua_S, "generateMipmap", tolua_Cocos2d_glGenerateMipmap00);
        tolua_function(tolua_S, "_getActiveAttrib", tolua_Cocos2d_glGetActiveAttrib00);
        tolua_function(tolua_S, "_getActiveUniform", tolua_Cocos2d_glGetActiveUniform00);
        tolua_function(tolua_S, "_getAttachedShaders", tolua_Cocos2d_glGetAttachedShaders00);
        tolua_function(tolua_S, "_getAttribLocation", tolua_Cocos2d_glGetAttribLocation00);
        tolua_function(tolua_S, "getError", tolua_Cocos2d_glGetError00);
        tolua_function(tolua_S, "_getProgramInfoLog", tolua_Cocos2d_glGetProgramInfoLog00);
        tolua_function(tolua_S, "_getProgramParameter", tolua_Cocos2d_glGetProgramiv00);
        tolua_function(tolua_S, "_getShaderInfoLog", tolua_Cocos2d_glGetShaderInfoLog00);
        tolua_function(tolua_S, "_getShaderSource", tolua_Cocos2d_glGetShaderSource00);
        tolua_function(tolua_S, "_getShaderParameter", tolua_Cocos2d_glGetShaderiv00);
        tolua_function(tolua_S, "getTexParameter", tolua_Cocos2d_glGetTexParameterfv00);
        tolua_function(tolua_S, "_getUniformLocation", tolua_Cocos2d_glGetUniformLocation00);
        tolua_function(tolua_S, "_getUniform", tolua_Cocos2d_glGetUniformfv00);
        tolua_function(tolua_S, "hint", tolua_Cocos2d_glHint00);
        tolua_function(tolua_S, "isBuffer",tolua_Cocos2d_glIsBuffer00);
        tolua_function(tolua_S, "isEnabled", tolua_Cocos2d_glIsEnabled00);
        tolua_function(tolua_S, "isFramebuffer", tolua_Cocos2d_glIsFramebuffer00);
        tolua_function(tolua_S, "isProgram", tolua_Cocos2d_glIsProgram00);
        tolua_function(tolua_S, "isRenderbuffer", tolua_Cocos2d_glIsRenderbuffer00);
        tolua_function(tolua_S, "isShader", tolua_Cocos2d_glIsShader00);
        tolua_function(tolua_S, "isTexture", tolua_Cocos2d_glIsTexture00);
        tolua_function(tolua_S, "lineWidth", tolua_Cocos2d_glLineWidth00);
        tolua_function(tolua_S, "_linkProgram", tolua_Cocos2d_glLinkProgram00);
        tolua_function(tolua_S, "pixelStorei", tolua_Cocos2d_glPixelStorei00);
        tolua_function(tolua_S, "polygonOffset", tolua_Cocos2d_glPolygonOffset00);
        tolua_function(tolua_S, "readPixels", tolua_Cocos2d_glReadPixels00);
        tolua_function(tolua_S, "releaseShaderCompiler", tolua_Cocos2d_glReleaseShaderCompiler00);
        tolua_function(tolua_S, "renderbufferStorage", tolua_Cocos2d_glRenderbufferStorage00);
        tolua_function(tolua_S, "sampleCoverage", tolua_Cocos2d_glSampleCoverage00);
        tolua_function(tolua_S, "scissor", tolua_Cocos2d_glScissor00);
        tolua_function(tolua_S, "_shaderSource", tolua_Cocos2d_glShaderSource00);
        tolua_function(tolua_S, "stencilFunc", tolua_Cocos2d_glStencilFunc00);
        tolua_function(tolua_S, "stencilFuncSeparate", tolua_Cocos2d_glStencilFuncSeparate00);
        tolua_function(tolua_S, "stencilMask", tolua_Cocos2d_glStencilMask00);
        tolua_function(tolua_S, "stencilMaskSeparate", tolua_Cocos2d_glStencilMaskSeparate00);
        tolua_function(tolua_S, "stencilOp", tolua_Cocos2d_glStencilOp00);
        tolua_function(tolua_S, "stencilOpSeparate", tolua_Cocos2d_glStencilOpSeparate00);
        tolua_function(tolua_S, "_texImage2D", tolua_Cocos2d_glTexImage2D00);
        tolua_function(tolua_S, "texParameterf", tolua_Cocos2d_glTexParameterf00);
        tolua_function(tolua_S, "texParameteri", tolua_Cocos2d_glTexParameteri00);
        tolua_function(tolua_S, "_texSubImage2D", tolua_Cocos2d_glTexSubImage2D00);
        tolua_function(tolua_S, "uniform1f", tolua_Cocos2d_glUniform1f00);
        tolua_function(tolua_S, "uniform1fv", tolua_Cocos2d_glUniform1fv00);
        tolua_function(tolua_S, "uniform1i", tolua_Cocos2d_glUniform1i00);
        tolua_function(tolua_S, "uniform1iv", tolua_Cocos2d_glUniform1iv00);
        tolua_function(tolua_S, "uniform2f", tolua_Cocos2d_glUniform2f00);
        tolua_function(tolua_S, "uniform2fv", tolua_Cocos2d_glUniform2fv00);
        tolua_function(tolua_S, "uniform2i", tolua_Cocos2d_glUniform2i00);
        tolua_function(tolua_S, "uniform2iv", tolua_Cocos2d_glUniform2iv00);
        tolua_function(tolua_S, "uniform3f", tolua_Cocos2d_glUniform3f00);
        tolua_function(tolua_S, "uniform3fv", tolua_Cocos2d_glUniform3fv00);
        tolua_function(tolua_S, "uniform3i", tolua_Cocos2d_glUniform3i00);
        tolua_function(tolua_S, "uniform3iv", tolua_Cocos2d_glUniform3iv00);
        tolua_function(tolua_S, "uniform4f", tolua_Cocos2d_glUniform4f00);
        tolua_function(tolua_S, "uniform4fv", tolua_Cocos2d_glUniform4fv00);
        tolua_function(tolua_S, "uniform4i", tolua_Cocos2d_glUniform4i00);
        tolua_function(tolua_S, "uniform4iv", tolua_Cocos2d_glUniform4iv00);
        tolua_function(tolua_S, "uniformMatrix2fv", tolua_Cocos2d_glUniformMatrix2fv00);
        tolua_function(tolua_S, "uniformMatrix3fv", tolua_Cocos2d_glUniformMatrix3fv00);
        tolua_function(tolua_S, "uniformMatrix4fv", tolua_Cocos2d_glUniformMatrix4fv00);
        tolua_function(tolua_S, "_useProgram", tolua_Cocos2d_glUseProgram00);
        tolua_function(tolua_S, "_validateProgram", tolua_Cocos2d_glValidateProgram00);
        tolua_function(tolua_S, "vertexAttrib1f", tolua_Cocos2d_glVertexAttrib1f00);
        tolua_function(tolua_S, "vertexAttrib1fv", tolua_Cocos2d_glVertexAttrib1fv00);
        tolua_function(tolua_S, "vertexAttrib2f", tolua_Cocos2d_glVertexAttrib2f00);
        tolua_function(tolua_S, "vertexAttrib2fv", tolua_Cocos2d_glVertexAttrib2fv00);
        tolua_function(tolua_S, "vertexAttrib3f", tolua_Cocos2d_glVertexAttrib3f00);
        tolua_function(tolua_S, "vertexAttrib3fv", tolua_Cocos2d_glVertexAttrib3fv00);
        tolua_function(tolua_S, "vertexAttrib4f", tolua_Cocos2d_glVertexAttrib4f00);
        tolua_function(tolua_S, "vertexAttrib4fv", tolua_Cocos2d_glVertexAttrib4fv00);
        tolua_function(tolua_S, "vertexAttribPointer", tolua_Cocos2d_glVertexAttribPointer00);
        tolua_function(tolua_S, "viewport", tolua_Cocos2d_glViewport00);
        tolua_function(tolua_S, "glEnableVertexAttribs", tolua_Cocos2d_glEnableVertexAttribs00);
      tolua_endmodule(tolua_S);
      tolua_cclass(tolua_S,"CCGLProgram","CCGLProgram","CCObject",tolua_collect_CCGLProgram);
      tolua_beginmodule(tolua_S,"CCGLProgram");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCGLProgram_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCGLProgram_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCGLProgram_new00_local);
        tolua_function(tolua_S,"delete",tolua_Cocos2d_CCGLProgram_delete00);
        tolua_function(tolua_S,"initWithVertexShaderByteArray",tolua_Cocos2d_CCGLProgram_initWithVertexShaderByteArray00);
        tolua_function(tolua_S,"initWithVertexShaderFilename",tolua_Cocos2d_CCGLProgram_initWithVertexShaderFilename00);
        tolua_function(tolua_S,"addAttribute",tolua_Cocos2d_CCGLProgram_addAttribute00);
        tolua_function(tolua_S,"link",tolua_Cocos2d_CCGLProgram_link00);
        tolua_function(tolua_S,"use",tolua_Cocos2d_CCGLProgram_use00);
        tolua_function(tolua_S,"updateUniforms",tolua_Cocos2d_CCGLProgram_updateUniforms00);
        tolua_function(tolua_S,"getUniformLocationForName",tolua_Cocos2d_CCGLProgram_getUniformLocationForName00);
        tolua_function(tolua_S,"setUniformLocationWith1i",tolua_Cocos2d_CCGLProgram_setUniformLocationWith1i00);
        tolua_function(tolua_S,"setUniformLocationWith2i",tolua_Cocos2d_CCGLProgram_setUniformLocationWith2i00);
        tolua_function(tolua_S,"setUniformLocationWith3i",tolua_Cocos2d_CCGLProgram_setUniformLocationWith3i00);
        tolua_function(tolua_S,"setUniformLocationWith4i",tolua_Cocos2d_CCGLProgram_setUniformLocationWith4i00);
        tolua_function(tolua_S,"setUniformLocationWith2iv",tolua_Cocos2d_CCGLProgram_setUniformLocationWith2iv00);
        tolua_function(tolua_S,"setUniformLocationWith3iv",tolua_Cocos2d_CCGLProgram_setUniformLocationWith3iv00);
        tolua_function(tolua_S,"setUniformLocationWith4iv",tolua_Cocos2d_CCGLProgram_setUniformLocationWith4iv00);
        tolua_function(tolua_S,"setUniformLocationWith1f",tolua_Cocos2d_CCGLProgram_setUniformLocationWith1f00);
        tolua_function(tolua_S,"setUniformLocationWith2f",tolua_Cocos2d_CCGLProgram_setUniformLocationWith2f00);
        tolua_function(tolua_S,"setUniformLocationWith3f",tolua_Cocos2d_CCGLProgram_setUniformLocationWith3f00);
        tolua_function(tolua_S,"setUniformLocationWith4f",tolua_Cocos2d_CCGLProgram_setUniformLocationWith4f00);
        tolua_function(tolua_S,"setUniformLocationWith2fv",tolua_Cocos2d_CCGLProgram_setUniformLocationWith2fv00);
        tolua_function(tolua_S,"setUniformLocationWith3fv",tolua_Cocos2d_CCGLProgram_setUniformLocationWith3fv00);
        tolua_function(tolua_S,"setUniformLocationWith4fv",tolua_Cocos2d_CCGLProgram_setUniformLocationWith4fv00);
        tolua_function(tolua_S,"setUniformLocationWithMatrix4fv",tolua_Cocos2d_CCGLProgram_setUniformLocationWithMatrix4fv00);
        tolua_function(tolua_S,"setUniformsForBuiltins",tolua_Cocos2d_CCGLProgram_setUniformsForBuiltins00);
        tolua_function(tolua_S,"vertexShaderLog",tolua_Cocos2d_CCGLProgram_vertexShaderLog00);
        tolua_function(tolua_S,"fragmentShaderLog",tolua_Cocos2d_CCGLProgram_fragmentShaderLog00);
        tolua_function(tolua_S,"programLog",tolua_Cocos2d_CCGLProgram_programLog00);
        tolua_function(tolua_S,"reset",tolua_Cocos2d_CCGLProgram_reset00);
        tolua_function(tolua_S,"getProgram",tolua_Cocos2d_CCGLProgram_getProgram00);
        tolua_function(tolua_S, "create", tolua_Cocos2d_CCGLProgram_create00);
     tolua_endmodule(tolua_S);
     tolua_cclass(tolua_S,"CCShaderCache","CCShaderCache","CCObject",tolua_collect_CCShaderCache);
     tolua_beginmodule(tolua_S,"CCShaderCache");
        tolua_function(tolua_S,"new",tolua_Cocos2d_CCShaderCache_new00);
        tolua_function(tolua_S,"new_local",tolua_Cocos2d_CCShaderCache_new00_local);
        tolua_function(tolua_S,".call",tolua_Cocos2d_CCShaderCache_new00_local);
        tolua_function(tolua_S,"delete",tolua_Cocos2d_CCShaderCache_delete00);
        tolua_function(tolua_S,"getInstance",tolua_Cocos2d_CCShaderCache_sharedShaderCache00);
        tolua_function(tolua_S,"purgeSharedShaderCache",tolua_Cocos2d_CCShaderCache_purgeSharedShaderCache00);
        tolua_function(tolua_S,"loadDefaultShaders",tolua_Cocos2d_CCShaderCache_loadDefaultShaders00);
        tolua_function(tolua_S,"reloadDefaultShaders",tolua_Cocos2d_CCShaderCache_reloadDefaultShaders00);
        tolua_function(tolua_S,"getProgram",tolua_Cocos2d_CCShaderCache_programForKey00);
        tolua_function(tolua_S,"addProgram",tolua_Cocos2d_CCShaderCache_addProgram00);
     tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}


