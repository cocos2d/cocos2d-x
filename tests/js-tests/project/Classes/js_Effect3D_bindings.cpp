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

#include "js_Effect3D_bindings.h"
#include "cocos2d_specifics.hpp"

using namespace cocos2d;

class EffectSprite3D;

class Effect3D : public Ref
{
public:
    virtual void draw(const Mat4 &transform) = 0;
    virtual void setTarget(EffectSprite3D *sprite) = 0;
protected:
    Effect3D() : _glProgramState(nullptr) {}
    virtual ~Effect3D()
    {
        CC_SAFE_RELEASE(_glProgramState);
    }
protected:
    GLProgramState* _glProgramState;
};

class Effect3DOutline: public Effect3D
{
public:
    static Effect3DOutline* create();
    
    void setOutlineColor(const Vec3& color);
    
    void setOutlineWidth(float width);
    
    virtual void draw(const Mat4 &transform) override;
    virtual void setTarget(EffectSprite3D *sprite) override;

    
    Effect3DOutline();
    virtual ~Effect3DOutline();
    
    bool init();
protected: 
    Vec3 _outlineColor;
    float _outlineWidth;
    //weak reference
    EffectSprite3D* _sprite;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundListener;
#endif
    
protected:
    static const std::string _vertShaderFile;
    static const std::string _fragShaderFile;
    static const std::string _keyInGLProgramCache;
    
    static const std::string _vertSkinnedShaderFile;
    static const std::string _fragSkinnedShaderFile;
    static const std::string _keySkinnedInGLProgramCache;
    
    static GLProgram* getOrCreateProgram(bool isSkinned = false);
};

class EffectSprite3D : public Sprite3D
{
public:
    static EffectSprite3D* createFromObjFileAndTexture(const std::string& objFilePath, const std::string& textureFilePath);
    static EffectSprite3D* create(const std::string& path);
    
    void setEffect3D(Effect3D* effect);
    void addEffect(Effect3DOutline* effect, ssize_t order);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    EffectSprite3D();
    virtual ~EffectSprite3D();
protected:
    std::vector<std::tuple<ssize_t,Effect3D*,CustomCommand>> _effects;
    Effect3D* _defaultEffect;
    CustomCommand _command;
};


EffectSprite3D* EffectSprite3D::createFromObjFileAndTexture(const std::string &objFilePath, const std::string &textureFilePath)
{
    auto sprite = new (std::nothrow) EffectSprite3D();
    if (sprite && sprite->initWithFile(objFilePath))
    {
        sprite->autorelease();
        if(textureFilePath.size() > 0)
            sprite->setTexture(textureFilePath);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D* EffectSprite3D::create(const std::string &path)
{
    if (path.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new (std::nothrow) EffectSprite3D();
    if (sprite && sprite->initWithFile(path))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D::EffectSprite3D()
: _defaultEffect(nullptr)
{
    
}

EffectSprite3D::~EffectSprite3D()
{
    for(auto effect : _effects)
    {
        CC_SAFE_RELEASE_NULL(std::get<1>(effect));
    }
    CC_SAFE_RELEASE(_defaultEffect);
}

void EffectSprite3D::setEffect3D(Effect3D *effect)
{
    if(_defaultEffect == effect) return;
    CC_SAFE_RETAIN(effect);
    CC_SAFE_RELEASE(_defaultEffect);
    _defaultEffect = effect;
}

static int tuple_sort( const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple1, const std::tuple<ssize_t,Effect3D*,CustomCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

void EffectSprite3D::addEffect(Effect3DOutline* effect, ssize_t order)
{
    if(nullptr == effect) return;
    effect->retain();
    effect->setTarget(this);
    
    _effects.push_back(std::make_tuple(order,effect,CustomCommand()));
    
    std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
}

const std::string Effect3DOutline::_vertShaderFile = "Shaders3D/OutLine.vert";
const std::string Effect3DOutline::_fragShaderFile = "Shaders3D/OutLine.frag";
const std::string Effect3DOutline::_keyInGLProgramCache = "Effect3DLibrary_Outline";

const std::string Effect3DOutline::_vertSkinnedShaderFile = "Shaders3D/SkinnedOutline.vert";
const std::string Effect3DOutline::_fragSkinnedShaderFile = "Shaders3D/OutLine.frag";
const std::string Effect3DOutline::_keySkinnedInGLProgramCache = "Effect3DLibrary_Outline";
GLProgram* Effect3DOutline::getOrCreateProgram(bool isSkinned /* = false */ )
{
    if(isSkinned)
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(_keySkinnedInGLProgramCache);
        if(program == nullptr)
        {
            program = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);
            GLProgramCache::getInstance()->addGLProgram(program, _keySkinnedInGLProgramCache);
        }
        return program;
    }
    else
    {
        auto program = GLProgramCache::getInstance()->getGLProgram(_keyInGLProgramCache);
        if(program == nullptr)
        {
            program = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
            GLProgramCache::getInstance()->addGLProgram(program, _keyInGLProgramCache);
        }
        return program;
    }
    
}

Effect3DOutline* Effect3DOutline::create()
{
    Effect3DOutline* effect = new (std::nothrow) Effect3DOutline();
    if(effect && effect->init())
    {
        effect->autorelease();
        return effect;
    }
    else
    {
        CC_SAFE_DELETE(effect);
        return nullptr;
    }
}

bool Effect3DOutline::init()
{
    
    return true;
}

Effect3DOutline::Effect3DOutline()
: _outlineWidth(1.0f)
, _outlineColor(1, 1, 1)
, _sprite(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                auto glProgram = _glProgramState->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames(_vertShaderFile, _fragShaderFile);
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

Effect3DOutline::~Effect3DOutline()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void Effect3DOutline::setOutlineColor(const Vec3& color)
{
    if(_outlineColor != color)
    {
        _outlineColor = color;
        if(_glProgramState)
            _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
    }
}

void Effect3DOutline::setOutlineWidth(float width)
{
    if(_outlineWidth != width)
    {
        _outlineWidth = width;
        if(_glProgramState)
            _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
    }
}

void Effect3DOutline::setTarget(EffectSprite3D *sprite)
{
    CCASSERT(nullptr != sprite && nullptr != sprite->getMesh(),"Error: Setting a null pointer or a null mesh EffectSprite3D to Effect3D");
    
    if(sprite != _sprite)
    {
        GLProgram* glprogram;
        if(!sprite->getMesh()->getSkin())
            glprogram = GLProgram::createWithFilenames(_vertShaderFile, _fragShaderFile);
        else
            glprogram = GLProgram::createWithFilenames(_vertSkinnedShaderFile, _fragSkinnedShaderFile);
        
        _glProgramState = GLProgramState::create(glprogram);
        
        _glProgramState->retain();
        _glProgramState->setUniformVec3("OutLineColor", _outlineColor);
        _glProgramState->setUniformFloat("OutlineWidth", _outlineWidth);
        
        
        _sprite = sprite;
        
        auto mesh = sprite->getMesh();
        long offset = 0;
        for (auto i = 0; i < mesh->getMeshVertexAttribCount(); i++)
        {
            auto meshvertexattrib = mesh->getMeshVertexAttribute(i);
            
            _glProgramState->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib],
                                                    meshvertexattrib.size,
                                                    meshvertexattrib.type,
                                                    GL_FALSE,
                                                    mesh->getVertexSizeInBytes(),
                                                    (void*)offset);
            offset += meshvertexattrib.attribSizeBytes;
        }
        
        Color4F color(_sprite->getDisplayedColor());
        color.a = _sprite->getDisplayedOpacity() / 255.0f;
        _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
    }
    
}

static void MatrixPalleteCallBack( GLProgram* glProgram, Uniform* uniform, int paletteSize, const float* palette)
{
    glUniform4fv( uniform->location, (GLsizei)paletteSize, (const float*)palette );
}

void Effect3DOutline::draw(const Mat4 &transform)
{
    //draw
    Color4F color(_sprite->getDisplayedColor());
    color.a = _sprite->getDisplayedOpacity() / 255.0f;
    _glProgramState->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
    if(_sprite && _sprite->getMesh())
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);
        
        auto mesh = _sprite->getMesh();
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
        
        auto skin = _sprite->getMesh()->getSkin();
        if(_sprite && skin)
        {
            auto function = std::bind(MatrixPalleteCallBack, std::placeholders::_1, std::placeholders::_2,
                                      skin->getMatrixPaletteSize(), (float*)skin->getMatrixPalette());
            _glProgramState->setUniformCallback("u_matrixPalette", function);
        }
        
        if(_sprite)
            _glProgramState->apply(transform);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
        glDrawElements(mesh->getPrimitiveType(), (GLsizei)mesh->getIndexCount(), mesh->getIndexFormat(), 0);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, mesh->getIndexCount());
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);
    }
}

void EffectSprite3D::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    for(auto &effect : _effects)
    {
        if(std::get<0>(effect) >=0)
            break;
        CustomCommand &cc = std::get<2>(effect);
        cc.func = CC_CALLBACK_0(Effect3D::draw,std::get<1>(effect),transform);
        renderer->addCommand(&cc);
        
    }
    
    if(!_defaultEffect)
    {
        Sprite3D::draw(renderer, transform, flags);
    }
    else
    {
        _command.init(_globalZOrder, transform, flags);
        _command.func = CC_CALLBACK_0(Effect3D::draw, _defaultEffect, transform);
        renderer->addCommand(&_command);
    }
    
    for(auto &effect : _effects)
    {
        if(std::get<0>(effect) <=0)
            continue;
        CustomCommand &cc = std::get<2>(effect);
        cc.func = CC_CALLBACK_0(Effect3D::draw,std::get<1>(effect),transform);
        renderer->addCommand(&cc);
        
    }
}

// js bindings

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}

JSClass  *jsb_Effect3DOutline_class;
JSObject *jsb_Effect3DOutline_prototype;

bool js_cocos2dx_Effect3DOutline_setOutlineWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Effect3DOutline* cobj = (Effect3DOutline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_Effect3DOutline_setOutlineWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_Effect3DOutline_setOutlineWidth : Error processing arguments");
        cobj->setOutlineWidth(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_Effect3DOutline_setOutlineWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_Effect3DOutline_setOutlineColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    Effect3DOutline* cobj = (Effect3DOutline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_Effect3DOutline_setOutlineColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_Effect3DOutline_setOutlineColor : Error processing arguments");
        cobj->setOutlineColor(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_Effect3DOutline_setOutlineColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_Effect3DOutline_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        Effect3DOutline* ret = Effect3DOutline::create();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<Effect3DOutline>(cx, (Effect3DOutline*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_Effect3DOutline_create : wrong number of arguments");
    return false;
}


JSObject *jsb_Effect3D_prototype;

void js_Effect3DOutline_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Effect3DOutline)", obj);
}

bool jsb_Effect3DOutline_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    Effect3DOutline* cobj = new (std::nothrow) Effect3DOutline();
    cobj->init();
    cobj->autorelease();
    TypeTest<Effect3DOutline> t;
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
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Effect3DOutline");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_register_cocos2dx_Effect3DOutline(JSContext *cx, JS::HandleObject global) {
    jsb_Effect3DOutline_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_Effect3DOutline_class->name = "Effect3DOutline";
    jsb_Effect3DOutline_class->addProperty = JS_PropertyStub;
    jsb_Effect3DOutline_class->delProperty = JS_DeletePropertyStub;
    jsb_Effect3DOutline_class->getProperty = JS_PropertyStub;
    jsb_Effect3DOutline_class->setProperty = JS_StrictPropertyStub;
    jsb_Effect3DOutline_class->enumerate = JS_EnumerateStub;
    jsb_Effect3DOutline_class->resolve = JS_ResolveStub;
    jsb_Effect3DOutline_class->convert = JS_ConvertStub;
    jsb_Effect3DOutline_class->finalize = js_Effect3DOutline_finalize;
    jsb_Effect3DOutline_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("setOutlineWidth", js_cocos2dx_Effect3DOutline_setOutlineWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOutlineColor", js_cocos2dx_Effect3DOutline_setOutlineColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_Effect3DOutline_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    jsb_Effect3DOutline_prototype = JS_InitClass(
                                                 cx, global,
                                                 JS::RootedObject(cx, jsb_Effect3D_prototype),
                                                 jsb_Effect3DOutline_class,
                                                 jsb_Effect3DOutline_constructor, 0, 
                                                 properties,
                                                 funcs,
                                                 NULL, // no static properties
                                                 st_funcs);
    // make the class enumerable in the registered namespace
    //  bool found;
    //FIXME: Removed in Firefox v27
    //  JS_SetPropertyAttributes(cx, global, "Effect3DOutline", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<Effect3DOutline> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_Effect3DOutline_class;
        p->proto = jsb_Effect3DOutline_prototype;
        p->parentProto = jsb_Effect3D_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}


JSClass  *jsb_EffectSprite3D_class;
JSObject *jsb_EffectSprite3D_prototype;

bool js_cocos2dx_EffectSprite3D_setEffect3D(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    EffectSprite3D* cobj = (EffectSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_EffectSprite3D_setEffect3D : Invalid Native Object");
    if (argc == 1) {
        Effect3D* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (Effect3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EffectSprite3D_setEffect3D : Error processing arguments");
        cobj->setEffect3D(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_EffectSprite3D_setEffect3D : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_EffectSprite3D_addEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    EffectSprite3D* cobj = (EffectSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_EffectSprite3D_addEffect : Invalid Native Object");
    if (argc == 2) {
        Effect3DOutline* arg0;
        ssize_t arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (Effect3DOutline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ssize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EffectSprite3D_addEffect : Error processing arguments");
        cobj->addEffect(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_EffectSprite3D_addEffect : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_EffectSprite3D_createFromObjFileAndTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EffectSprite3D_createFromObjFileAndTexture : Error processing arguments");
        EffectSprite3D* ret = EffectSprite3D::createFromObjFileAndTexture(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<EffectSprite3D>(cx, (EffectSprite3D*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_EffectSprite3D_createFromObjFileAndTexture : wrong number of arguments");
    return false;
}

bool js_cocos2dx_EffectSprite3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EffectSprite3D_create : Error processing arguments");
        EffectSprite3D* ret = EffectSprite3D::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<EffectSprite3D>(cx, (EffectSprite3D*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_EffectSprite3D_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite3D_prototype;

void js_EffectSprite3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EffectSprite3D)", obj);
}

bool jsb_EffectSprite3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    EffectSprite3D* cobj = new (std::nothrow) EffectSprite3D();
    if(argc == 1 || argc == 2)
    {
        std::string path;
        jsval_to_std_string(cx, args.get(0), &path);
        cobj->initWithFile(path);
        if(argc == 2)
        {
            std::string texture;
            jsval_to_std_string(cx, args.get(1), &texture);
            cobj->setTexture(texture);
        }
    }
    cobj->autorelease();
    TypeTest<EffectSprite3D> t;
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
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::EffectSprite3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_register_cocos2dx_EffectSprite3D(JSContext *cx, JS::HandleObject global) {
    jsb_EffectSprite3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_EffectSprite3D_class->name = "EffectSprite3D";
    jsb_EffectSprite3D_class->addProperty = JS_PropertyStub;
    jsb_EffectSprite3D_class->delProperty = JS_DeletePropertyStub;
    jsb_EffectSprite3D_class->getProperty = JS_PropertyStub;
    jsb_EffectSprite3D_class->setProperty = JS_StrictPropertyStub;
    jsb_EffectSprite3D_class->enumerate = JS_EnumerateStub;
    jsb_EffectSprite3D_class->resolve = JS_ResolveStub;
    jsb_EffectSprite3D_class->convert = JS_ConvertStub;
    jsb_EffectSprite3D_class->finalize = js_EffectSprite3D_finalize;
    jsb_EffectSprite3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("setEffect3D", js_cocos2dx_EffectSprite3D_setEffect3D, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addEffect", js_cocos2dx_EffectSprite3D_addEffect, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("createFromObjFileAndTexture", js_cocos2dx_EffectSprite3D_createFromObjFileAndTexture, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_cocos2dx_EffectSprite3D_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    jsb_EffectSprite3D_prototype = JS_InitClass(
                                                cx, global,
                                                JS::RootedObject(cx, jsb_cocos2d_Sprite3D_prototype),
                                                jsb_EffectSprite3D_class,
                                                jsb_EffectSprite3D_constructor, 1,
                                                properties,
                                                funcs,
                                                NULL, // no static properties
                                                st_funcs);
    // make the class enumerable in the registered namespace
    //  bool found;
    //FIXME: Removed in Firefox v27
    //  JS_SetPropertyAttributes(cx, global, "EffectSprite3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<EffectSprite3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_EffectSprite3D_class;
        p->proto = jsb_EffectSprite3D_prototype;
        p->parentProto = jsb_cocos2d_Sprite3D_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_Effect3D_bindings(JSContext *cx, JS::HandleObject global)
{
    JS::RootedObject ccobj(cx);
    get_or_create_js_obj(cx, global, "cc", &ccobj);
    js_register_cocos2dx_Effect3DOutline(cx, ccobj);
    js_register_cocos2dx_EffectSprite3D(cx, ccobj);
}