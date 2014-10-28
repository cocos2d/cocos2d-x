#include "lua_test_bindings.h"
#include "cocos2d.h"
#include "LuaBasicConversions.h"

NS_CC_BEGIN

/**
 * Copy DrawNode for 3D geometry drawing.
 */
class DrawNode3D: public Node
{
public:
    /** creates and initialize a DrawNode3D node */
    static DrawNode3D* create();
    
    /**
     * Draw 3D Line
     */
    void drawLine(const Vec3 &from, const Vec3 &to, const Color4F &color);
    
    /**
     * Draw 3D cube
     * @param point to a vertex array who has 8 element.
     *        vertices[0]:Left-top-front,
     *        vertices[1]:Left-bottom-front,
     *        vertices[2]:Right-bottom-front,
     *        vertices[3]:Right-top-front,
     *        vertices[4]:Right-top-back,
     *        vertices[5]:Right-bottom-back,
     *        vertices[6]:Left-bottom-back,
     *        vertices[7]:Left-top-back.
     * @param color
     */
    void drawCube(Vec3* vertices, const Color4F &color);
    
    /** Clear the geometry in the node's buffer. */
    void clear();
    
    /**
     * @js NA
     * @lua NA
     */
    const BlendFunc& getBlendFunc() const;
    
    /**
     * @code
     * When this function bound into js or lua,the parameter will be changed
     * In js: var setBlendFunc(var src, var dst)
     * @endcode
     * @lua NA
     */
    void setBlendFunc(const BlendFunc &blendFunc);
    
    void onDraw(const Mat4 &transform, uint32_t flags);
    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    DrawNode3D();
    virtual ~DrawNode3D();
    virtual bool init();
    
protected:
    struct V3F_C4B
    {
        Vec3     vertices;
        Color4B  colors;
    };
    void ensureCapacity(int count);
    
    GLuint      _vao;
    GLuint      _vbo;
    
    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V3F_C4B*    _buffer;
    
    BlendFunc   _blendFunc;
    CustomCommand _customCommand;
    
    bool        _dirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode3D);
};




DrawNode3D::DrawNode3D()
: _vao(0)
, _vbo(0)
, _bufferCapacity(0)
, _bufferCount(0)
, _buffer(nullptr)
, _dirty(false)
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

DrawNode3D::~DrawNode3D()
{
    free(_buffer);
    _buffer = nullptr;
    
    glDeleteBuffers(1, &_vbo);
    _vbo = 0;
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }
}

DrawNode3D* DrawNode3D::create()
{
    DrawNode3D* ret = new (std::nothrow) DrawNode3D();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

void DrawNode3D::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCount + count > _bufferCapacity)
    {
		_bufferCapacity += MAX(_bufferCapacity, count);
		_buffer = (V3F_C4B*)realloc(_buffer, _bufferCapacity*sizeof(V3F_C4B));
	}
}

bool DrawNode3D::init()
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    ensureCapacity(512);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, vertices));
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, colors));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    _dirty = true;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Need to listen the event only when not use batchnode, because it will use VBO
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
        /** listen the event that coming to foreground on Android */
        this->init();
    });
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
    
    return true;
}

void DrawNode3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawNode3D::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void DrawNode3D::onDraw(const Mat4 &transform, uint32_t flags)
{
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    glEnable(GL_DEPTH_TEST);
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    
    if (_dirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B)*_bufferCapacity, _buffer, GL_STREAM_DRAW);
        _dirty = false;
    }
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    else
    {
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // vertex
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, vertices));
        
        // color
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B), (GLvoid *)offsetof(V3F_C4B, colors));
    }
    
    glDrawArrays(GL_LINES, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);
	glDisable(GL_DEPTH_TEST);
    CHECK_GL_ERROR_DEBUG();
}

void DrawNode3D::drawLine(const Vec3 &from, const Vec3 &to, const Color4F &color)
{
    unsigned int vertex_count = 2;
    ensureCapacity(vertex_count);
    
    Color4B col = Color4B(color);
    V3F_C4B a = {Vec3(from.x, from.y, from.z), col};
    V3F_C4B b = {Vec3(to.x, to.y, to.z), col, };
    
    V3F_C4B *lines = (V3F_C4B *)(_buffer + _bufferCount);
    lines[0] = a;
    lines[1] = b;
    
    _bufferCount += vertex_count;
    _dirty = true;
    
}

void DrawNode3D::drawCube(Vec3* vertices, const Color4F &color)
{
    // front face
    drawLine(vertices[0], vertices[1], color);
    drawLine(vertices[1], vertices[2], color);
    drawLine(vertices[2], vertices[3], color);
    drawLine(vertices[3], vertices[0], color);
    
    // back face
    drawLine(vertices[4], vertices[5], color);
    drawLine(vertices[5], vertices[6], color);
    drawLine(vertices[6], vertices[7], color);
    drawLine(vertices[7], vertices[4], color);
    
    // edge
    drawLine(vertices[0], vertices[7], color);
    drawLine(vertices[1], vertices[6], color);
    drawLine(vertices[2], vertices[5], color);
    drawLine(vertices[3], vertices[4], color);
}

void DrawNode3D::clear()
{
    _bufferCount = 0;
    _dirty = true;
}

const BlendFunc& DrawNode3D::getBlendFunc() const
{
    return _blendFunc;
}

void DrawNode3D::setBlendFunc(const BlendFunc &blendFunc)
{
    _blendFunc = blendFunc;
}
NS_CC_END

int lua_cocos2dx_DrawNode3D_getBlendFunc(lua_State* L)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_DrawNode3D_getBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(L, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:getBlendFunc",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_DrawNode3D_getBlendFunc'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_DrawNode3D_setBlendFunc(lua_State* L)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_DrawNode3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 2)
    {
        GLenum src, dst;
        if (!luaval_to_int32(L, 2, (int32_t*)&src, "cc.DrawNode3D:setBlendFunc"))
            return 0;
        
        if (!luaval_to_int32(L, 3, (int32_t*)&dst, "cc.DrawNode3D:setBlendFunc"))
            return 0;
        
        BlendFunc blendFunc = {src, dst};
        cobj->setBlendFunc(blendFunc);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:setBlendFunc",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_DrawNode3D_setBlendFunc'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_DrawNode3D_drawLine(lua_State* L)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_DrawNode3D_drawLine'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 3)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Color4F arg2;
        
        ok &= luaval_to_vec3(L, 2, &arg0, "cc.DrawNode3D:drawLine");
        
        ok &= luaval_to_vec3(L, 3, &arg1, "cc.DrawNode3D:drawLine");
        
        ok &=luaval_to_color4f(L, 4, &arg2, "cc.DrawNode3D:drawLine");
        if(!ok)
            return 0;
        cobj->drawLine(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:drawLine",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_DrawNode3D_drawLine'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_DrawNode3D_clear(lua_State* L)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_DrawNode3D_clear'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->clear();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:clear",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_DrawNode3D_clear'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_DrawNode3D_drawCube(lua_State* L)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_DrawNode3D_drawCube'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 2)
    {
        std::vector<cocos2d::Vec3> arg0;
        cocos2d::Color4F arg1;
        Vec3 vec3;
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        size_t size = lua_objlen(L, 2);
        for (int i = 0; i < size; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, 2);
#if COCOS2D_DEBUG >= 1
            if (!tolua_istable(L, -1, 0, &tolua_err))
            {
                lua_pop(L, 1);
                goto tolua_lerror;
            }
#endif
            ok &= luaval_to_vec3(L, lua_gettop(L), &vec3);
            
#if COCOS2D_DEBUG >= 1
            if (!ok)
            {
                lua_pop(L, 1);
                goto tolua_lerror;
            }
#endif
            //arg0[i] = vec3;
            arg0.push_back(vec3);
            lua_pop(L, 1);
        }
        
        ok &=luaval_to_color4f(L, 3, &arg1, "cc.DrawNode3D:drawCube");
        if(!ok)
            return 0;
        cobj->drawCube(&arg0[0], arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:drawCube",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_DrawNode3D_drawCube'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_DrawNode3D_create(lua_State* L)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(L,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::DrawNode3D* ret = cocos2d::DrawNode3D::create();
        object_to_luaval<cocos2d::DrawNode3D>(L, "cc.DrawNode3D",(cocos2d::DrawNode3D*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.DrawNode3D:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_DrawNode3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_register_cocos2dx_DrawNode3D(lua_State* L)
{
    tolua_usertype(L,"cc.DrawNode3D");
    tolua_cclass(L,"DrawNode3D","cc.DrawNode3D","cc.Node",nullptr);
    
    tolua_beginmodule(L,"DrawNode3D");
    tolua_function(L,"getBlendFunc",lua_cocos2dx_DrawNode3D_getBlendFunc);
    tolua_function(L,"setBlendFunc",lua_cocos2dx_DrawNode3D_setBlendFunc);
    tolua_function(L,"drawLine",lua_cocos2dx_DrawNode3D_drawLine);
    tolua_function(L,"clear",lua_cocos2dx_DrawNode3D_clear);
    tolua_function(L,"drawCube",lua_cocos2dx_DrawNode3D_drawCube);
    tolua_function(L,"create", lua_cocos2dx_DrawNode3D_create);
    tolua_endmodule(L);
    std::string typeName = typeid(cocos2d::DrawNode3D).name();
    g_luaType[typeName] = "cc.DrawNode3D";
    g_typeCast["DrawNode3D"] = "cc.DrawNode3D";
    return 1;
}

int register_test_binding(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, "cc", 0);
    tolua_beginmodule(L, "cc");
        lua_register_cocos2dx_DrawNode3D(L);
    tolua_endmodule(L);
    return 0;
}
