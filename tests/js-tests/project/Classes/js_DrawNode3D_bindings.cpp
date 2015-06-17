/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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
#include "cocos2d.h"
#include "cocos2d_specifics.hpp"
#include "js_DrawNode3D_bindings.h"

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
    _customCommand.init(_globalZOrder, transform, flags);
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

/**
 * bindings for cc.DrawNode3D
 **/
JSClass  *jsb_cocos2d_DrawNode3D_class;
JSObject *jsb_cocos2d_DrawNode3D_prototype;

bool js_cocos2dx_DrawNode3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_DrawNode3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_DrawNode3D_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_DrawNode3D_drawLine(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_drawLine : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Color4F arg2;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        ok &= jsval_to_cccolor4f(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_DrawNode3D_drawLine : Error processing arguments");
        cobj->drawLine(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_drawLine : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_DrawNode3D_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_DrawNode3D_onDraw(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_onDraw : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Mat4 arg0;
        unsigned int arg1;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_DrawNode3D_onDraw : Error processing arguments");
        cobj->onDraw(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_onDraw : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_DrawNode3D_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_DrawNode3D_drawCube(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::DrawNode3D* cobj = (cocos2d::DrawNode3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DrawNode3D_drawCube : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec3 arg0[8];
        cocos2d::Color4F arg1;
  
        JS::RootedObject jsVec3Array(cx, args.get(0).toObjectOrNull());
        JSB_PRECONDITION3( jsVec3Array && JS_IsArrayObject( cx, jsVec3Array),  cx, false, "augument must be an array");
        uint32_t len = 0;
        JS_GetArrayLength(cx, jsVec3Array, &len);
    
        if (len != 8)
        {
            JS_ReportError(cx, "array length error: %d, was expecting 8", len);
        }
        for (uint32_t i=0; i < len; i++)
        {
            JS::RootedValue value(cx);
            if (JS_GetElement(cx, jsVec3Array, i, &value))
            {
                ok &= jsval_to_vector3(cx, value, &arg0[i]);
                if(!ok)
                    break;
            }
        }

        ok &= jsval_to_cccolor4f(cx, args.get(1), &arg1);
        
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_DrawNode3D_drawCube : Error processing arguments");
        cobj->drawCube(arg0, arg1);

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_DrawNode3D_drawCube : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_cocos2dx_DrawNode3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::DrawNode3D* cobj = new (std::nothrow) cocos2d::DrawNode3D();
    cobj->init();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::DrawNode3D> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::DrawNode3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}

extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_DrawNode3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (DrawNode3D)", obj);
}

void js_register_cocos2dx_DrawNode3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_DrawNode3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_DrawNode3D_class->name = "DrawNode3D";
    jsb_cocos2d_DrawNode3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_DrawNode3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_DrawNode3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_DrawNode3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_DrawNode3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_DrawNode3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_DrawNode3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_DrawNode3D_class->finalize = js_cocos2d_DrawNode3D_finalize;
    jsb_cocos2d_DrawNode3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBlendFunc", js_cocos2dx_DrawNode3D_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_DrawNode3D_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("drawLine", js_cocos2dx_DrawNode3D_drawLine, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_cocos2dx_DrawNode3D_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onDraw", js_cocos2dx_DrawNode3D_onDraw, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_DrawNode3D_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("drawCube", js_cocos2dx_DrawNode3D_drawCube, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };

    jsb_cocos2d_DrawNode3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_cocos2d_DrawNode3D_class,
        js_cocos2dx_DrawNode3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "DrawNode3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::DrawNode3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_DrawNode3D_class;
        p->proto = jsb_cocos2d_DrawNode3D_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_DrawNode3D_bindings(JSContext *cx, JS::HandleObject global)
{
    JS::RootedObject ccobj(cx);
    get_or_create_js_obj(cx, global, "cc", &ccobj);
    js_register_cocos2dx_DrawNode3D(cx, ccobj);
}