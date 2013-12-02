/*
** Lua binding: CocoStudio
** Generated automatically by tolua++-1.0.92 on Mon Dec  2 10:22:19 2013.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

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

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;



#include "LuaCocoStudio.h"

/* function to release collected object via destructor */
#ifdef __cplusplus



static int tolua_collect_UILayout (lua_State* tolua_S)
{
 UILayout* self = (UILayout*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UILayoutParameter (lua_State* tolua_S)
{
 UILayoutParameter* self = (UILayoutParameter*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIWidget (lua_State* tolua_S)
{
 UIWidget* self = (UIWidget*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UILabelAtlas (lua_State* tolua_S)
{
 UILabelAtlas* self = (UILabelAtlas*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIRelativeLayoutParameter (lua_State* tolua_S)
{
 UIRelativeLayoutParameter* self = (UIRelativeLayoutParameter*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UILoadingBar (lua_State* tolua_S)
{
 UILoadingBar* self = (UILoadingBar*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCComController (lua_State* tolua_S)
{
 CCComController* self = (CCComController*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIRootWidget (lua_State* tolua_S)
{
 UIRootWidget* self = (UIRootWidget*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_CCTween (lua_State* tolua_S)
{
 CCTween* self = (CCTween*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCBaseData (lua_State* tolua_S)
{
 CCBaseData* self = (CCBaseData*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIListView (lua_State* tolua_S)
{
 UIListView* self = (UIListView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}





static int tolua_collect_ActionManager (lua_State* tolua_S)
{
 ActionManager* self = (ActionManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UISlider (lua_State* tolua_S)
{
 UISlider* self = (UISlider*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ActionObject (lua_State* tolua_S)
{
 ActionObject* self = (ActionObject*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GUIReader (lua_State* tolua_S)
{
 GUIReader* self = (GUIReader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIButton (lua_State* tolua_S)
{
 UIButton* self = (UIButton*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_UILinearLayoutParameter (lua_State* tolua_S)
{
 UILinearLayoutParameter* self = (UILinearLayoutParameter*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_CCSkin (lua_State* tolua_S)
{
 CCSkin* self = (CCSkin*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCArmature (lua_State* tolua_S)
{
 CCArmature* self = (CCArmature*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_UIImageView (lua_State* tolua_S)
{
 UIImageView* self = (UIImageView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIScrollView (lua_State* tolua_S)
{
 UIScrollView* self = (UIScrollView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIPageView (lua_State* tolua_S)
{
 UIPageView* self = (UIPageView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_UITextField (lua_State* tolua_S)
{
 UITextField* self = (UITextField*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_CCArmatureAnimation (lua_State* tolua_S)
{
 CCArmatureAnimation* self = (CCArmatureAnimation*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UICheckBox (lua_State* tolua_S)
{
 UICheckBox* self = (UICheckBox*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UILabel (lua_State* tolua_S)
{
 UILabel* self = (UILabel*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UILabelBMFont (lua_State* tolua_S)
{
 UILabelBMFont* self = (UILabelBMFont*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCBone (lua_State* tolua_S)
{
 CCBone* self = (CCBone*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SceneReader (lua_State* tolua_S)
{
 SceneReader* self = (SceneReader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UILayer (lua_State* tolua_S)
{
 UILayer* self = (UILayer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCBatchNode (lua_State* tolua_S)
{
 CCBatchNode* self = (CCBatchNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCDisplayManager (lua_State* tolua_S)
{
 CCDisplayManager* self = (CCDisplayManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}


#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"UITextField");
 tolua_usertype(tolua_S,"UILabelAtlas");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCComController");
 tolua_usertype(tolua_S,"UIRootWidget");
 tolua_usertype(tolua_S,"GLubyte");
 tolua_usertype(tolua_S,"UILayer");
 tolua_usertype(tolua_S,"CCArmatureData");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCComAudio");
 tolua_usertype(tolua_S,"UISlider");
 tolua_usertype(tolua_S,"CCTextureAtlas");
 tolua_usertype(tolua_S,"CCAnimationData");
 tolua_usertype(tolua_S,"UICheckBox");
 tolua_usertype(tolua_S,"CCActionManager");
 tolua_usertype(tolua_S,"UIScrollView");
 tolua_usertype(tolua_S,"UIPageView");
 tolua_usertype(tolua_S,"CCAffineTransform");
 tolua_usertype(tolua_S,"ccBlendFunc");
 tolua_usertype(tolua_S,"CCComRender");
 tolua_usertype(tolua_S,"CCComponent");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCMovementBoneData");
 tolua_usertype(tolua_S,"CCBatchNode");
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"UILayout");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"UILinearGravity");
 tolua_usertype(tolua_S,"CCTextAlignment");
 tolua_usertype(tolua_S,"UIRelativeLayoutParameter");
 tolua_usertype(tolua_S,"UILoadingBar");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCNodeRGBA");
 tolua_usertype(tolua_S,"CCBlendProtocol");
 tolua_usertype(tolua_S,"UIButton");
 tolua_usertype(tolua_S,"CCBaseData");
 tolua_usertype(tolua_S,"UILayoutParameter");
 tolua_usertype(tolua_S,"CCArmatureDataManager");
 tolua_usertype(tolua_S,"UIListView");
 tolua_usertype(tolua_S,"SceneReader");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"SEL_TouchEvent");
 tolua_usertype(tolua_S,"DisplayType");
 tolua_usertype(tolua_S,"ActionObject");
 tolua_usertype(tolua_S,"CCColliderFilter");
 tolua_usertype(tolua_S,"ActionManager");
 tolua_usertype(tolua_S,"GUIReader");
 tolua_usertype(tolua_S,"ActionNode");
 tolua_usertype(tolua_S,"CCComAttribute");
 tolua_usertype(tolua_S,"CCDisplayData");
 tolua_usertype(tolua_S,"CCTexture2D");
 tolua_usertype(tolua_S,"UIWidget");
 tolua_usertype(tolua_S,"UIRelativeAlign");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"UILinearLayoutParameter");
 tolua_usertype(tolua_S,"CCBone");
 tolua_usertype(tolua_S,"CCSkin");
 tolua_usertype(tolua_S,"CCArmature");
 tolua_usertype(tolua_S,"CCArray");
 tolua_usertype(tolua_S,"UIImageView");
 tolua_usertype(tolua_S,"UILabel");
 tolua_usertype(tolua_S,"rapidjson::Value");
 tolua_usertype(tolua_S,"CCArmatureAnimation");
 tolua_usertype(tolua_S,"ccColor4B");
 tolua_usertype(tolua_S,"UIScrollInterface");
 tolua_usertype(tolua_S,"CCAction");
 tolua_usertype(tolua_S,"UIHelper");
 tolua_usertype(tolua_S,"CCTween");
 tolua_usertype(tolua_S,"UILabelBMFont");
 tolua_usertype(tolua_S,"CCVerticalTextAlignment");
 tolua_usertype(tolua_S,"CCProcessBase");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"CCInputDelegate");
 tolua_usertype(tolua_S,"CCDisplayManager");
 tolua_usertype(tolua_S,"CCBlendType");
}

/* method: create of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_create00
static int tolua_CocoStudio_CCArmature_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmature* tolua_ret = (CCArmature*)  CCArmature::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
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

/* method: create of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_create01
static int tolua_CocoStudio_CCArmature_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCArmature* tolua_ret = (CCArmature*)  CCArmature::create(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCArmature_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_create02
static int tolua_CocoStudio_CCArmature_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCBone* parentBone = ((CCBone*)  tolua_tousertype(tolua_S,3,0));
  {
   CCArmature* tolua_ret = (CCArmature*)  CCArmature::create(name,parentBone);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCArmature_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_new00
static int tolua_CocoStudio_CCArmature_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmature* tolua_ret = (CCArmature*)  Mtolua_new((CCArmature)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
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

/* method: new_local of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_new00_local
static int tolua_CocoStudio_CCArmature_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmature* tolua_ret = (CCArmature*)  Mtolua_new((CCArmature)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
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

/* method: delete of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_delete00
static int tolua_CocoStudio_CCArmature_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_init00
static int tolua_CocoStudio_CCArmature_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_init01
static int tolua_CocoStudio_CCArmature_init01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCArmature_init00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_init02
static int tolua_CocoStudio_CCArmature_init02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCBone* parentBone = ((CCBone*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(name,parentBone);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCArmature_init01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBone of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_addBone00
static int tolua_CocoStudio_CCArmature_addBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
  const char* parentName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBone'", NULL);
#endif
  {
   self->addBone(bone,parentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBone of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getBone00
static int tolua_CocoStudio_CCArmature_getBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBone'", NULL);
#endif
  {
   CCBone* tolua_ret = (CCBone*)  self->getBone(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeBoneParent of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_changeBoneParent00
static int tolua_CocoStudio_CCArmature_changeBoneParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
  const char* parentName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeBoneParent'", NULL);
#endif
  {
   self->changeBoneParent(bone,parentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeBoneParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBone of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_removeBone00
static int tolua_CocoStudio_CCArmature_removeBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
  bool recursion = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBone'", NULL);
#endif
  {
   self->removeBone(bone,recursion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoneDic of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getBoneDic00
static int tolua_CocoStudio_CCArmature_getBoneDic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoneDic'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->getBoneDic();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoneDic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: boundingBox of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_boundingBox00
static int tolua_CocoStudio_CCArmature_boundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'boundingBox'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->boundingBox();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'boundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoneAtPoint of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getBoneAtPoint00
static int tolua_CocoStudio_CCArmature_getBoneAtPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoneAtPoint'", NULL);
#endif
  {
   CCBone* tolua_ret = (CCBone*)  self->getBoneAtPoint(x,y);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoneAtPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_visit00
static int tolua_CocoStudio_CCArmature_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'visit'", NULL);
#endif
  {
   self->visit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'visit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_update00
static int tolua_CocoStudio_CCArmature_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_draw00
static int tolua_CocoStudio_CCArmature_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nodeToParentTransform of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_nodeToParentTransform00
static int tolua_CocoStudio_CCArmature_nodeToParentTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nodeToParentTransform'", NULL);
#endif
  {
   CCAffineTransform tolua_ret = (CCAffineTransform)  self->nodeToParentTransform();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCAffineTransform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCAffineTransform));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nodeToParentTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateOffsetPoint of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_updateOffsetPoint00
static int tolua_CocoStudio_CCArmature_updateOffsetPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateOffsetPoint'", NULL);
#endif
  {
   self->updateOffsetPoint();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateOffsetPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setBlendFunc00
static int tolua_CocoStudio_CCArmature_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc blendFunc = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(blendFunc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendFunc of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getBlendFunc00
static int tolua_CocoStudio_CCArmature_getBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  self->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimation of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setAnimation00
static int tolua_CocoStudio_CCArmature_setAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCArmatureAnimation* animation = ((CCArmatureAnimation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimation'", NULL);
#endif
  {
   self->setAnimation(animation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimation of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getAnimation00
static int tolua_CocoStudio_CCArmature_getAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimation'", NULL);
#endif
  {
   CCArmatureAnimation* tolua_ret = (CCArmatureAnimation*)  self->getAnimation();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmatureAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTexureAtlasWithTexture of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getTexureAtlasWithTexture00
static int tolua_CocoStudio_CCArmature_getTexureAtlasWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTexureAtlasWithTexture'", NULL);
#endif
  {
   CCTextureAtlas* tolua_ret = (CCTextureAtlas*)  self->getTexureAtlasWithTexture(texture);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextureAtlas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTexureAtlasWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColliderFilter of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setColliderFilter00
static int tolua_CocoStudio_CCArmature_setColliderFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCColliderFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCColliderFilter* filter = ((CCColliderFilter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColliderFilter'", NULL);
#endif
  {
   self->setColliderFilter(filter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColliderFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmatureData of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getArmatureData00
static int tolua_CocoStudio_CCArmature_getArmatureData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmatureData'", NULL);
#endif
  {
   CCArmatureData* tolua_ret = (CCArmatureData*)  self->getArmatureData();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArmatureData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArmatureData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setArmatureData of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setArmatureData00
static int tolua_CocoStudio_CCArmature_setArmatureData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmatureData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCArmatureData* var = ((CCArmatureData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmatureData'", NULL);
#endif
  {
   self->setArmatureData(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setArmatureData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBatchNode of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getBatchNode00
static int tolua_CocoStudio_CCArmature_getBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBatchNode'", NULL);
#endif
  {
   CCBatchNode* tolua_ret = (CCBatchNode*)  self->getBatchNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBatchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBatchNode of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setBatchNode00
static int tolua_CocoStudio_CCArmature_setBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCBatchNode* var = ((CCBatchNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBatchNode'", NULL);
#endif
  {
   self->setBatchNode(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getName00
static int tolua_CocoStudio_CCArmature_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setName00
static int tolua_CocoStudio_CCArmature_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  std::string var = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTextureAtlas of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getTextureAtlas00
static int tolua_CocoStudio_CCArmature_getTextureAtlas00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextureAtlas'", NULL);
#endif
  {
   CCTextureAtlas* tolua_ret = (CCTextureAtlas*)  self->getTextureAtlas();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextureAtlas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTextureAtlas'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextureAtlas of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setTextureAtlas00
static int tolua_CocoStudio_CCArmature_setTextureAtlas00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTextureAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCTextureAtlas* var = ((CCTextureAtlas*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextureAtlas'", NULL);
#endif
  {
   self->setTextureAtlas(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextureAtlas'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParentBone of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getParentBone00
static int tolua_CocoStudio_CCArmature_getParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParentBone'", NULL);
#endif
  {
   CCBone* tolua_ret = (CCBone*)  self->getParentBone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParentBone of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setParentBone00
static int tolua_CocoStudio_CCArmature_setParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  CCBone* var = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParentBone'", NULL);
#endif
  {
   self->setParentBone(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersion of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getVersion00
static int tolua_CocoStudio_CCArmature_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getVersion();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVersion of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_setVersion00
static int tolua_CocoStudio_CCArmature_setVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
  float var = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVersion'", NULL);
#endif
  {
   self->setVersion(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmatureTransformDirty of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmature_getArmatureTransformDirty00
static int tolua_CocoStudio_CCArmature_getArmatureTransformDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmature* self = (const CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmatureTransformDirty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getArmatureTransformDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArmatureTransformDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCBlendProtocol__ of class  CCArmature */
#ifndef TOLUA_DISABLE_tolua_get_CCArmature___CCBlendProtocol__
static int tolua_get_CCArmature___CCBlendProtocol__(lua_State* tolua_S)
{
  CCArmature* self = (CCArmature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCBlendProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCBlendProtocol*>(self), "CCBlendProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCBlendProtocol*)self), "CCBlendProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_create00
static int tolua_CocoStudio_CCArmatureAnimation_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmature* armature = ((CCArmature*)  tolua_tousertype(tolua_S,2,0));
  {
   CCArmatureAnimation* tolua_ret = (CCArmatureAnimation*)  CCArmatureAnimation::create(armature);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmatureAnimation");
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

/* method: new of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_new00
static int tolua_CocoStudio_CCArmatureAnimation_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmatureAnimation* tolua_ret = (CCArmatureAnimation*)  Mtolua_new((CCArmatureAnimation)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmatureAnimation");
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

/* method: new_local of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_new00_local
static int tolua_CocoStudio_CCArmatureAnimation_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmatureAnimation* tolua_ret = (CCArmatureAnimation*)  Mtolua_new((CCArmatureAnimation)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmatureAnimation");
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

/* method: delete of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_delete00
static int tolua_CocoStudio_CCArmatureAnimation_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_init00
static int tolua_CocoStudio_CCArmatureAnimation_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  CCArmature* armature = ((CCArmature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(armature);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpeedScale of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_setSpeedScale00
static int tolua_CocoStudio_CCArmatureAnimation_setSpeedScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  float speedScale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpeedScale'", NULL);
#endif
  {
   self->setSpeedScale(speedScale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpeedScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSpeedScale of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_getSpeedScale00
static int tolua_CocoStudio_CCArmatureAnimation_getSpeedScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCArmatureAnimation* self = (const CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSpeedScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSpeedScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSpeedScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationInternal of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_setAnimationInternal00
static int tolua_CocoStudio_CCArmatureAnimation_setAnimationInternal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  float animationInternal = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationInternal'", NULL);
#endif
  {
   self->setAnimationInternal(animationInternal);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationInternal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_play00
static int tolua_CocoStudio_CCArmatureAnimation_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
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
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  int durationTo = ((int)  tolua_tonumber(tolua_S,2,0));
  int durationTween = ((int)  tolua_tonumber(tolua_S,3,0));
  int loop = ((int)  tolua_tonumber(tolua_S,4,0));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_play01
static int tolua_CocoStudio_CCArmatureAnimation_play01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int durationTo = ((int)  tolua_tonumber(tolua_S,3,-1));
  int durationTween = ((int)  tolua_tonumber(tolua_S,4,-1));
  int loop = ((int)  tolua_tonumber(tolua_S,5,-1));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,6,TWEEN_EASING_MAX));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(animationName,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCArmatureAnimation_play00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: playByIndex of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_playByIndex00
static int tolua_CocoStudio_CCArmatureAnimation_playByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  int animationIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int durationTo = ((int)  tolua_tonumber(tolua_S,3,-1));
  int durationTween = ((int)  tolua_tonumber(tolua_S,4,-1));
  int loop = ((int)  tolua_tonumber(tolua_S,5,-1));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,6,TWEEN_EASING_MAX));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playByIndex'", NULL);
#endif
  {
   self->playByIndex(animationIndex,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoAndPlay of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_gotoAndPlay00
static int tolua_CocoStudio_CCArmatureAnimation_gotoAndPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoAndPlay'", NULL);
#endif
  {
   self->gotoAndPlay(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoAndPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoAndPause of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_gotoAndPause00
static int tolua_CocoStudio_CCArmatureAnimation_gotoAndPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoAndPause'", NULL);
#endif
  {
   self->gotoAndPause(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoAndPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_pause00
static int tolua_CocoStudio_CCArmatureAnimation_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_resume00
static int tolua_CocoStudio_CCArmatureAnimation_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_stop00
static int tolua_CocoStudio_CCArmatureAnimation_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMovementCount of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_getMovementCount00
static int tolua_CocoStudio_CCArmatureAnimation_getMovementCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMovementCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMovementCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMovementCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_update00
static int tolua_CocoStudio_CCArmatureAnimation_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentMovementID of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_getCurrentMovementID00
static int tolua_CocoStudio_CCArmatureAnimation_getCurrentMovementID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentMovementID'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getCurrentMovementID();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentMovementID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUserObject of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_getUserObject00
static int tolua_CocoStudio_CCArmatureAnimation_getUserObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUserObject'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->getUserObject();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUserObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUserObject of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_setUserObject00
static int tolua_CocoStudio_CCArmatureAnimation_setUserObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pUserObject = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUserObject'", NULL);
#endif
  {
   self->setUserObject(pUserObject);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUserObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationData of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_getAnimationData00
static int tolua_CocoStudio_CCArmatureAnimation_getAnimationData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationData'", NULL);
#endif
  {
   CCAnimationData* tolua_ret = (CCAnimationData*)  self->getAnimationData();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCAnimationData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationData of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_setAnimationData00
static int tolua_CocoStudio_CCArmatureAnimation_setAnimationData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAnimationData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
  CCAnimationData* var = ((CCAnimationData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationData'", NULL);
#endif
  {
   self->setAnimationData(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_create00
static int tolua_CocoStudio_CCSkin_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSkin* tolua_ret = (CCSkin*)  CCSkin::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSkin");
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

/* method: createWithSpriteFrameName of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_createWithSpriteFrameName00
static int tolua_CocoStudio_CCSkin_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCSkin* tolua_ret = (CCSkin*)  CCSkin::createWithSpriteFrameName(pszSpriteFrameName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSkin");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_create01
static int tolua_CocoStudio_CCSkin_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCSkin* tolua_ret = (CCSkin*)  CCSkin::create(pszFileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSkin");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCSkin_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_new00
static int tolua_CocoStudio_CCSkin_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSkin* tolua_ret = (CCSkin*)  Mtolua_new((CCSkin)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSkin");
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

/* method: new_local of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_new00_local
static int tolua_CocoStudio_CCSkin_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSkin* tolua_ret = (CCSkin*)  Mtolua_new((CCSkin)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSkin");
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

/* method: initWithSpriteFrameName of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_initWithSpriteFrameName00
static int tolua_CocoStudio_CCSkin_initWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithSpriteFrameName'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithSpriteFrameName(pszSpriteFrameName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_initWithFile00
static int tolua_CocoStudio_CCSkin_initWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(pszFilename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateArmatureTransform of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_updateArmatureTransform00
static int tolua_CocoStudio_CCSkin_updateArmatureTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateArmatureTransform'", NULL);
#endif
  {
   self->updateArmatureTransform();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateArmatureTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateTransform of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_updateTransform00
static int tolua_CocoStudio_CCSkin_updateTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateTransform'", NULL);
#endif
  {
   self->updateTransform();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nodeToWorldTransform of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_nodeToWorldTransform00
static int tolua_CocoStudio_CCSkin_nodeToWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nodeToWorldTransform'", NULL);
#endif
  {
   CCAffineTransform tolua_ret = (CCAffineTransform)  self->nodeToWorldTransform();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCAffineTransform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCAffineTransform));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nodeToWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nodeToWorldTransformAR of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_nodeToWorldTransformAR00
static int tolua_CocoStudio_CCSkin_nodeToWorldTransformAR00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nodeToWorldTransformAR'", NULL);
#endif
  {
   CCAffineTransform tolua_ret = (CCAffineTransform)  self->nodeToWorldTransformAR();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCAffineTransform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCAffineTransform));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nodeToWorldTransformAR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkinData of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_getSkinData00
static int tolua_CocoStudio_CCSkin_getSkinData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkinData'", NULL);
#endif
  {
   const CCBaseData& tolua_ret = (const CCBaseData&)  self->getSkinData();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCBaseData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkinData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSkinData of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_setSkinData00
static int tolua_CocoStudio_CCSkin_setSkinData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCBaseData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
  const CCBaseData* var = ((const CCBaseData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSkinData'", NULL);
#endif
  {
   self->setSkinData(*var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSkinData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBone of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_getBone00
static int tolua_CocoStudio_CCSkin_getBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBone'", NULL);
#endif
  {
   CCBone* tolua_ret = (CCBone*)  self->getBone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBone of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_setBone00
static int tolua_CocoStudio_CCSkin_setBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkin",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkin* self = (CCSkin*)  tolua_tousertype(tolua_S,1,0);
  CCBone* var = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBone'", NULL);
#endif
  {
   self->setBone(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayName of class  CCSkin */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCSkin_getDisplayName00
static int tolua_CocoStudio_CCSkin_getDisplayName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCSkin",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCSkin* self = (const CCSkin*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDisplayName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_create00
static int tolua_CocoStudio_CCBone_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBone* tolua_ret = (CCBone*)  CCBone::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
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

/* method: create of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_create01
static int tolua_CocoStudio_CCBone_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCBone* tolua_ret = (CCBone*)  CCBone::create(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCBone_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_new00
static int tolua_CocoStudio_CCBone_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBone* tolua_ret = (CCBone*)  Mtolua_new((CCBone)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
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

/* method: new_local of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_new00_local
static int tolua_CocoStudio_CCBone_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBone* tolua_ret = (CCBone*)  Mtolua_new((CCBone)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
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

/* method: delete of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_delete00
static int tolua_CocoStudio_CCBone_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_init00
static int tolua_CocoStudio_CCBone_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_init01
static int tolua_CocoStudio_CCBone_init01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCBone_init00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDisplay of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_addDisplay00
static int tolua_CocoStudio_CCBone_addDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDisplayData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCDisplayData* displayData = ((CCDisplayData*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDisplay'", NULL);
#endif
  {
   self->addDisplay(displayData,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDisplay of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_addDisplay01
static int tolua_CocoStudio_CCBone_addDisplay01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCNode* display = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDisplay'", NULL);
#endif
  {
   self->addDisplay(display,index);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCBone_addDisplay00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeDisplay of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_removeDisplay00
static int tolua_CocoStudio_CCBone_removeDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeDisplay'", NULL);
#endif
  {
   self->removeDisplay(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeDisplayByIndex of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_changeDisplayByIndex00
static int tolua_CocoStudio_CCBone_changeDisplayByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  bool force = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeDisplayByIndex'", NULL);
#endif
  {
   self->changeDisplayByIndex(index,force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeDisplayByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChildBone of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_addChildBone00
static int tolua_CocoStudio_CCBone_addChildBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCBone* child = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChildBone'", NULL);
#endif
  {
   self->addChildBone(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChildBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParentBone of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setParentBone00
static int tolua_CocoStudio_CCBone_setParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCBone* parent = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParentBone'", NULL);
#endif
  {
   self->setParentBone(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParentBone of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getParentBone00
static int tolua_CocoStudio_CCBone_getParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParentBone'", NULL);
#endif
  {
   CCBone* tolua_ret = (CCBone*)  self->getParentBone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParent of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_removeFromParent00
static int tolua_CocoStudio_CCBone_removeFromParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromParent'", NULL);
#endif
  {
   self->removeFromParent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParent of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_removeFromParent01
static int tolua_CocoStudio_CCBone_removeFromParent01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  bool recursion = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromParent'", NULL);
#endif
  {
   self->removeFromParent(recursion);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCBone_removeFromParent00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChildBone of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_removeChildBone00
static int tolua_CocoStudio_CCBone_removeChildBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
  bool recursion = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChildBone'", NULL);
#endif
  {
   self->removeChildBone(bone,recursion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChildBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_update00
static int tolua_CocoStudio_CCBone_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDisplayedColor of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_updateDisplayedColor00
static int tolua_CocoStudio_CCBone_updateDisplayedColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* parentColor = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDisplayedColor'", NULL);
#endif
  {
   self->updateDisplayedColor(*parentColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDisplayedColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDisplayedOpacity of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_updateDisplayedOpacity00
static int tolua_CocoStudio_CCBone_updateDisplayedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  GLubyte parentOpacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDisplayedOpacity'", NULL);
#endif
  {
   self->updateDisplayedOpacity(parentOpacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDisplayedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setColor00
static int tolua_CocoStudio_CCBone_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setOpacity00
static int tolua_CocoStudio_CCBone_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateColor of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_updateColor00
static int tolua_CocoStudio_CCBone_updateColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateColor'", NULL);
#endif
  {
   self->updateColor();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateZOrder of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_updateZOrder00
static int tolua_CocoStudio_CCBone_updateZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateZOrder'", NULL);
#endif
  {
   self->updateZOrder();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZOrder of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setZOrder00
static int tolua_CocoStudio_CCBone_setZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZOrder'", NULL);
#endif
  {
   self->setZOrder(zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTween of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getTween00
static int tolua_CocoStudio_CCBone_getTween00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTween'", NULL);
#endif
  {
   CCTween* tolua_ret = (CCTween*)  self->getTween();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTween");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTween'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransformDirty of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setTransformDirty00
static int tolua_CocoStudio_CCBone_setTransformDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  bool dirty = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransformDirty'", NULL);
#endif
  {
   self->setTransformDirty(dirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTransformDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTransformDirty of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_isTransformDirty00
static int tolua_CocoStudio_CCBone_isTransformDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTransformDirty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTransformDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTransformDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nodeToArmatureTransform of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_nodeToArmatureTransform00
static int tolua_CocoStudio_CCBone_nodeToArmatureTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nodeToArmatureTransform'", NULL);
#endif
  {
   CCAffineTransform tolua_ret = (CCAffineTransform)  self->nodeToArmatureTransform();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCAffineTransform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCAffineTransform));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nodeToArmatureTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nodeToWorldTransform of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_nodeToWorldTransform00
static int tolua_CocoStudio_CCBone_nodeToWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nodeToWorldTransform'", NULL);
#endif
  {
   CCAffineTransform tolua_ret = (CCAffineTransform)  self->nodeToWorldTransform();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCAffineTransform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCAffineTransform));
     tolua_pushusertype(tolua_S,tolua_obj,"CCAffineTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nodeToWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayRenderNode of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getDisplayRenderNode00
static int tolua_CocoStudio_CCBone_getDisplayRenderNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayRenderNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getDisplayRenderNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayRenderNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayRenderNodeType of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getDisplayRenderNodeType00
static int tolua_CocoStudio_CCBone_getDisplayRenderNodeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayRenderNodeType'", NULL);
#endif
  {
   DisplayType tolua_ret = (DisplayType)  self->getDisplayRenderNodeType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DisplayType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DisplayType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DisplayType));
     tolua_pushusertype(tolua_S,tolua_obj,"DisplayType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayRenderNodeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmature of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getArmature00
static int tolua_CocoStudio_CCBone_getArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmature'", NULL);
#endif
  {
   CCArmature* tolua_ret = (CCArmature*)  self->getArmature();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setArmature of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setArmature00
static int tolua_CocoStudio_CCBone_setArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCArmature* var = ((CCArmature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmature'", NULL);
#endif
  {
   self->setArmature(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildArmature of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getChildArmature00
static int tolua_CocoStudio_CCBone_getChildArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildArmature'", NULL);
#endif
  {
   CCArmature* tolua_ret = (CCArmature*)  self->getChildArmature();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmature");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChildArmature of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setChildArmature00
static int tolua_CocoStudio_CCBone_setChildArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCArmature* var = ((CCArmature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChildArmature'", NULL);
#endif
  {
   self->setChildArmature(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChildArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayManager of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getDisplayManager00
static int tolua_CocoStudio_CCBone_getDisplayManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCBone* self = (const CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayManager'", NULL);
#endif
  {
   CCDisplayManager* tolua_ret = (CCDisplayManager*)  self->getDisplayManager();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDisplayManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplayManager of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setDisplayManager00
static int tolua_CocoStudio_CCBone_setDisplayManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCDisplayManager* var = ((CCDisplayManager*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplayManager'", NULL);
#endif
  {
   self->setDisplayManager(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplayManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIgnoreMovementBoneData of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getIgnoreMovementBoneData00
static int tolua_CocoStudio_CCBone_getIgnoreMovementBoneData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIgnoreMovementBoneData'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIgnoreMovementBoneData();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIgnoreMovementBoneData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIgnoreMovementBoneData of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setIgnoreMovementBoneData00
static int tolua_CocoStudio_CCBone_setIgnoreMovementBoneData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  bool var = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIgnoreMovementBoneData'", NULL);
#endif
  {
   self->setIgnoreMovementBoneData(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIgnoreMovementBoneData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendType of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getBlendType00
static int tolua_CocoStudio_CCBone_getBlendType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCBone* self = (const CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendType'", NULL);
#endif
  {
   CCBlendType tolua_ret = (CCBlendType)  self->getBlendType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCBlendType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCBlendType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCBlendType));
     tolua_pushusertype(tolua_S,tolua_obj,"CCBlendType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendType of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setBlendType00
static int tolua_CocoStudio_CCBone_setBlendType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCBlendType",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  CCBlendType var = *((CCBlendType*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendType'", NULL);
#endif
  {
   self->setBlendType(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getName00
static int tolua_CocoStudio_CCBone_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCBone* self = (const CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_setName00
static int tolua_CocoStudio_CCBone_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBone",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  std::string var = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldInfo of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_getWorldInfo00
static int tolua_CocoStudio_CCBone_getWorldInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCBone* self = (const CCBone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldInfo'", NULL);
#endif
  {
   CCBaseData* tolua_ret = (CCBaseData*)  self->getWorldInfo();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBaseData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedArmatureDataManager of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_sharedArmatureDataManager00
static int tolua_CocoStudio_CCArmatureDataManager_sharedArmatureDataManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmatureDataManager* tolua_ret = (CCArmatureDataManager*)  CCArmatureDataManager::sharedArmatureDataManager();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmatureDataManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedArmatureDataManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purge of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_purge00
static int tolua_CocoStudio_CCArmatureDataManager_purge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArmatureDataManager::purge();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_init00
static int tolua_CocoStudio_CCArmatureDataManager_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addArmatureFileInfo of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo00
static int tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* configFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfo'", NULL);
#endif
  {
   self->addArmatureFileInfo(configFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addArmatureFileInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addArmatureFileInfo of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo01
static int tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* imagePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* plistPath = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* configFilePath = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfo'", NULL);
#endif
  {
   self->addArmatureFileInfo(imagePath,plistPath,configFilePath);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeArmatureFileInfo of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_removeArmatureFileInfo00
static int tolua_CocoStudio_CCArmatureDataManager_removeArmatureFileInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* configFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeArmatureFileInfo'", NULL);
#endif
  {
   self->removeArmatureFileInfo(configFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeArmatureFileInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSpriteFrameFromFile of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_addSpriteFrameFromFile00
static int tolua_CocoStudio_CCArmatureDataManager_addSpriteFrameFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* plistPath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* imagePath = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* configFilePath = ((const char*)  tolua_tostring(tolua_S,4,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSpriteFrameFromFile'", NULL);
#endif
  {
   self->addSpriteFrameFromFile(plistPath,imagePath,configFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSpriteFrameFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAutoLoadSpriteFile of class  CCArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureDataManager_isAutoLoadSpriteFile00
static int tolua_CocoStudio_CCArmatureDataManager_isAutoLoadSpriteFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAutoLoadSpriteFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAutoLoadSpriteFile();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAutoLoadSpriteFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_create00
static int tolua_CocoStudio_CCBatchNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBatchNode* tolua_ret = (CCBatchNode*)  CCBatchNode::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBatchNode");
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

/* method: new of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_new00
static int tolua_CocoStudio_CCBatchNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBatchNode* tolua_ret = (CCBatchNode*)  Mtolua_new((CCBatchNode)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBatchNode");
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

/* method: new_local of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_new00_local
static int tolua_CocoStudio_CCBatchNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBatchNode* tolua_ret = (CCBatchNode*)  Mtolua_new((CCBatchNode)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBatchNode");
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

/* method: delete of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_delete00
static int tolua_CocoStudio_CCBatchNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBatchNode* self = (CCBatchNode*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addChild of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_addChild00
static int tolua_CocoStudio_CCBatchNode_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBatchNode* self = (CCBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pChild = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(pChild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_addChild01
static int tolua_CocoStudio_CCBatchNode_addChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCBatchNode* self = (CCBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pChild = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(pChild,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCBatchNode_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_addChild02
static int tolua_CocoStudio_CCBatchNode_addChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCBatchNode* self = (CCBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pChild = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(pChild,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCBatchNode_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_removeChild00
static int tolua_CocoStudio_CCBatchNode_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBatchNode* self = (CCBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTexureAtlasWithTexture of class  CCBatchNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBatchNode_getTexureAtlasWithTexture00
static int tolua_CocoStudio_CCBatchNode_getTexureAtlasWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBatchNode* self = (CCBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTexureAtlasWithTexture'", NULL);
#endif
  {
   CCTextureAtlas* tolua_ret = (CCTextureAtlas*)  self->getTexureAtlasWithTexture(texture);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextureAtlas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTexureAtlasWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_create00
static int tolua_CocoStudio_CCTween_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
  {
   CCTween* tolua_ret = (CCTween*)  CCTween::create(bone);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTween");
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

/* method: new of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_new00
static int tolua_CocoStudio_CCTween_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTween* tolua_ret = (CCTween*)  Mtolua_new((CCTween)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTween");
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

/* method: new_local of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_new00_local
static int tolua_CocoStudio_CCTween_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTween* tolua_ret = (CCTween*)  Mtolua_new((CCTween)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTween");
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

/* method: delete of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_delete00
static int tolua_CocoStudio_CCTween_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTween* self = (CCTween*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_init00
static int tolua_CocoStudio_CCTween_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTween* self = (CCTween*)  tolua_tousertype(tolua_S,1,0);
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(bone);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_play00
static int tolua_CocoStudio_CCTween_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMovementBoneData",0,&tolua_err) ||
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
  CCTween* self = (CCTween*)  tolua_tousertype(tolua_S,1,0);
  CCMovementBoneData* movementBoneData = ((CCMovementBoneData*)  tolua_tousertype(tolua_S,2,0));
  int durationTo = ((int)  tolua_tonumber(tolua_S,3,0));
  int durationTween = ((int)  tolua_tonumber(tolua_S,4,0));
  int loop = ((int)  tolua_tonumber(tolua_S,5,0));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(movementBoneData,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoAndPlay of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_gotoAndPlay00
static int tolua_CocoStudio_CCTween_gotoAndPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTween* self = (CCTween*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoAndPlay'", NULL);
#endif
  {
   self->gotoAndPlay(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoAndPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoAndPause of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_gotoAndPause00
static int tolua_CocoStudio_CCTween_gotoAndPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTween* self = (CCTween*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoAndPause'", NULL);
#endif
  {
   self->gotoAndPause(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoAndPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimation of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_setAnimation00
static int tolua_CocoStudio_CCTween_setAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTween",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArmatureAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTween* self = (CCTween*)  tolua_tousertype(tolua_S,1,0);
  CCArmatureAnimation* animation = ((CCArmatureAnimation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimation'", NULL);
#endif
  {
   self->setAnimation(animation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimation of class  CCTween */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCTween_getAnimation00
static int tolua_CocoStudio_CCTween_getAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCTween",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCTween* self = (const CCTween*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimation'", NULL);
#endif
  {
   CCArmatureAnimation* tolua_ret = (CCArmatureAnimation*)  self->getAnimation();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArmatureAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCBaseData */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBaseData_create00
static int tolua_CocoStudio_CCBaseData_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBaseData* self = (CCBaseData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'create'", NULL);
#endif
  {
   CCBaseData* tolua_ret = (CCBaseData*)  self->create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBaseData");
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

/* method: new of class  CCBaseData */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBaseData_new00
static int tolua_CocoStudio_CCBaseData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBaseData* tolua_ret = (CCBaseData*)  Mtolua_new((CCBaseData)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBaseData");
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

/* method: new_local of class  CCBaseData */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBaseData_new00_local
static int tolua_CocoStudio_CCBaseData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBaseData* tolua_ret = (CCBaseData*)  Mtolua_new((CCBaseData)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBaseData");
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

/* method: setColor of class  CCBaseData */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBaseData_setColor00
static int tolua_CocoStudio_CCBaseData_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBaseData",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBaseData* self = (CCBaseData*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  CCBaseData */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBaseData_getColor00
static int tolua_CocoStudio_CCBaseData_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBaseData* self = (CCBaseData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   ccColor4B tolua_ret = (ccColor4B)  self->getColor();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor4B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor4B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccColor4B));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor4B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_create00
static int tolua_CocoStudio_CCDisplayManager_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
  {
   CCDisplayManager* tolua_ret = (CCDisplayManager*)  CCDisplayManager::create(bone);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDisplayManager");
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

/* method: new of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_new00
static int tolua_CocoStudio_CCDisplayManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDisplayManager* tolua_ret = (CCDisplayManager*)  Mtolua_new((CCDisplayManager)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDisplayManager");
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

/* method: new_local of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_new00_local
static int tolua_CocoStudio_CCDisplayManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDisplayManager* tolua_ret = (CCDisplayManager*)  Mtolua_new((CCDisplayManager)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDisplayManager");
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

/* method: delete of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_delete00
static int tolua_CocoStudio_CCDisplayManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_init00
static int tolua_CocoStudio_CCDisplayManager_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCBone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  CCBone* bone = ((CCBone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(bone);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDisplay of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_addDisplay00
static int tolua_CocoStudio_CCDisplayManager_addDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDisplayData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  CCDisplayData* displayData = ((CCDisplayData*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDisplay'", NULL);
#endif
  {
   self->addDisplay(displayData,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDisplay of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_addDisplay01
static int tolua_CocoStudio_CCDisplayManager_addDisplay01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  CCNode* display = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDisplay'", NULL);
#endif
  {
   self->addDisplay(display,index);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCDisplayManager_addDisplay00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeDisplay of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_removeDisplay00
static int tolua_CocoStudio_CCDisplayManager_removeDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeDisplay'", NULL);
#endif
  {
   self->removeDisplay(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDecorativeDisplayList of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getDecorativeDisplayList00
static int tolua_CocoStudio_CCDisplayManager_getDecorativeDisplayList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDecorativeDisplayList'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getDecorativeDisplayList();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDecorativeDisplayList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeDisplayByIndex of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_changeDisplayByIndex00
static int tolua_CocoStudio_CCDisplayManager_changeDisplayByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  bool force = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeDisplayByIndex'", NULL);
#endif
  {
   self->changeDisplayByIndex(index,force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeDisplayByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayRenderNode of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getDisplayRenderNode00
static int tolua_CocoStudio_CCDisplayManager_getDisplayRenderNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayRenderNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getDisplayRenderNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayRenderNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayRenderNodeType of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getDisplayRenderNodeType00
static int tolua_CocoStudio_CCDisplayManager_getDisplayRenderNodeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayRenderNodeType'", NULL);
#endif
  {
   DisplayType tolua_ret = (DisplayType)  self->getDisplayRenderNodeType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DisplayType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DisplayType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DisplayType));
     tolua_pushusertype(tolua_S,tolua_obj,"DisplayType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayRenderNodeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentDisplayIndex of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getCurrentDisplayIndex00
static int tolua_CocoStudio_CCDisplayManager_getCurrentDisplayIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentDisplayIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurrentDisplayIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentDisplayIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_setVisible00
static int tolua_CocoStudio_CCDisplayManager_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVisible of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_isVisible00
static int tolua_CocoStudio_CCDisplayManager_isVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getContentSize00
static int tolua_CocoStudio_CCDisplayManager_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getContentSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoundingBox of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getBoundingBox00
static int tolua_CocoStudio_CCDisplayManager_getBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoundingBox'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getBoundingBox();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchorPoint of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getAnchorPoint00
static int tolua_CocoStudio_CCDisplayManager_getAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchorPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getAnchorPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchorPointInPoints of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_getAnchorPointInPoints00
static int tolua_CocoStudio_CCDisplayManager_getAnchorPointInPoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchorPointInPoints'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getAnchorPointInPoints();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchorPointInPoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containPoint of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_containPoint00
static int tolua_CocoStudio_CCDisplayManager_containPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  CCPoint* _point = ((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containPoint(*_point);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'containPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containPoint of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_containPoint01
static int tolua_CocoStudio_CCDisplayManager_containPoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDisplayManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCDisplayManager* self = (CCDisplayManager*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containPoint(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCDisplayManager_containPoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByTag of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIHelper_seekWidgetByTag00
static int tolua_CocoStudio_UIHelper_seekWidgetByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   UIWidget* tolua_ret = (UIWidget*)  UIHelper::seekWidgetByTag(root,tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByName of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIHelper_seekWidgetByName00
static int tolua_CocoStudio_UIHelper_seekWidgetByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   UIWidget* tolua_ret = (UIWidget*)  UIHelper::seekWidgetByName(root,name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByRelativeName of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIHelper_seekWidgetByRelativeName00
static int tolua_CocoStudio_UIHelper_seekWidgetByRelativeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   UIWidget* tolua_ret = (UIWidget*)  UIHelper::seekWidgetByRelativeName(root,name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByRelativeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekActionWidgetByActionTag of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIHelper_seekActionWidgetByActionTag00
static int tolua_CocoStudio_UIHelper_seekActionWidgetByActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   UIWidget* tolua_ret = (UIWidget*)  UIHelper::seekActionWidgetByActionTag(root,tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekActionWidgetByActionTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_new00
static int tolua_CocoStudio_UILayout_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayout* tolua_ret = (UILayout*)  Mtolua_new((UILayout)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayout");
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

/* method: new_local of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_new00_local
static int tolua_CocoStudio_UILayout_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayout* tolua_ret = (UILayout*)  Mtolua_new((UILayout)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayout");
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

/* method: delete of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_delete00
static int tolua_CocoStudio_UILayout_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_create00
static int tolua_CocoStudio_UILayout_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayout* tolua_ret = (UILayout*)  UILayout::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayout");
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

/* method: hitTest of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_hitTest00
static int tolua_CocoStudio_UILayout_hitTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hitTest'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hitTest(*pt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hitTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImage of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundImage00
static int tolua_CocoStudio_UILayout_setBackGroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundImage'", NULL);
#endif
  {
   self->setBackGroundImage(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImageCapInsets of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundImageCapInsets00
static int tolua_CocoStudio_UILayout_setBackGroundImageCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundImageCapInsets'", NULL);
#endif
  {
   self->setBackGroundImageCapInsets(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundImageCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColorType of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundColorType00
static int tolua_CocoStudio_UILayout_setBackGroundColorType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  LayoutBackGroundColorType type = ((LayoutBackGroundColorType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundColorType'", NULL);
#endif
  {
   self->setBackGroundColorType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundColorType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImageScale9Enabled of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundImageScale9Enabled00
static int tolua_CocoStudio_UILayout_setBackGroundImageScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundImageScale9Enabled'", NULL);
#endif
  {
   self->setBackGroundImageScale9Enabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundImageScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColor of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundColor00
static int tolua_CocoStudio_UILayout_setBackGroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundColor'", NULL);
#endif
  {
   self->setBackGroundColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColor of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundColor01
static int tolua_CocoStudio_UILayout_setBackGroundColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* startColor = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
  const ccColor3B* endColor = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundColor'", NULL);
#endif
  {
   self->setBackGroundColor(*startColor,*endColor);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_UILayout_setBackGroundColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColorOpacity of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundColorOpacity00
static int tolua_CocoStudio_UILayout_setBackGroundColorOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  int opacity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundColorOpacity'", NULL);
#endif
  {
   self->setBackGroundColorOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundColorOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColorVector of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundColorVector00
static int tolua_CocoStudio_UILayout_setBackGroundColorVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* vector = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundColorVector'", NULL);
#endif
  {
   self->setBackGroundColorVector(*vector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundColorVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setColor00
static int tolua_CocoStudio_UILayout_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setOpacity00
static int tolua_CocoStudio_UILayout_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  int opacity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBackGroundImage of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_removeBackGroundImage00
static int tolua_CocoStudio_UILayout_removeBackGroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBackGroundImage'", NULL);
#endif
  {
   self->removeBackGroundImage();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBackGroundImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackGroundImageTextureSize of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_getBackGroundImageTextureSize00
static int tolua_CocoStudio_UILayout_getBackGroundImageTextureSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILayout* self = (const UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundImageTextureSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getBackGroundImageTextureSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundImageTextureSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setClippingEnabled of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setClippingEnabled00
static int tolua_CocoStudio_UILayout_setClippingEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClippingEnabled'", NULL);
#endif
  {
   self->setClippingEnabled(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setClippingEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClippingEnabled of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_isClippingEnabled00
static int tolua_CocoStudio_UILayout_isClippingEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClippingEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isClippingEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClippingEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_getContentSize00
static int tolua_CocoStudio_UILayout_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILayout* self = (const UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_getDescription00
static int tolua_CocoStudio_UILayout_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILayout* self = (const UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayoutType of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setLayoutType00
static int tolua_CocoStudio_UILayout_setLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  LayoutType type = ((LayoutType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayoutType'", NULL);
#endif
  {
   self->setLayoutType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayoutType of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_getLayoutType00
static int tolua_CocoStudio_UILayout_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILayout* self = (const UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutType'", NULL);
#endif
  {
   LayoutType tolua_ret = (LayoutType)  self->getLayoutType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doLayout of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_doLayout00
static int tolua_CocoStudio_UILayout_doLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doLayout'", NULL);
#endif
  {
   self->doLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_addChild00
static int tolua_CocoStudio_UILayout_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addChild(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImageScale9Enable of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setBackGroundImageScale9Enable00
static int tolua_CocoStudio_UILayout_setBackGroundImageScale9Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundImageScale9Enable'", NULL);
#endif
  {
   self->setBackGroundImageScale9Enable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundImageScale9Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setClippingEnable of class  UILayout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayout_setClippingEnable00
static int tolua_CocoStudio_UILayout_setClippingEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayout* self = (UILayout*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClippingEnable'", NULL);
#endif
  {
   self->setClippingEnable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setClippingEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_new00
static int tolua_CocoStudio_UIWidget_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  Mtolua_new((UIWidget)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
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

/* method: new_local of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_new00_local
static int tolua_CocoStudio_UIWidget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  Mtolua_new((UIWidget)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
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

/* method: delete of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_delete00
static int tolua_CocoStudio_UIWidget_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_create00
static int tolua_CocoStudio_UIWidget_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  UIWidget::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
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

/* method: setEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setEnabled00
static int tolua_CocoStudio_UIWidget_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isEnabled00
static int tolua_CocoStudio_UIWidget_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setVisible00
static int tolua_CocoStudio_UIWidget_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVisible of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isVisible00
static int tolua_CocoStudio_UIWidget_isVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBright of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setBright00
static int tolua_CocoStudio_UIWidget_setBright00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool bright = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBright'", NULL);
#endif
  {
   self->setBright(bright);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBright'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBright of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isBright00
static int tolua_CocoStudio_UIWidget_isBright00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBright'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBright();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBright'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setTouchEnabled00
static int tolua_CocoStudio_UIWidget_setTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnabled'", NULL);
#endif
  {
   self->setTouchEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBrightStyle of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setBrightStyle00
static int tolua_CocoStudio_UIWidget_setBrightStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  BrightStyle style = ((BrightStyle) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBrightStyle'", NULL);
#endif
  {
   self->setBrightStyle(style);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBrightStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isTouchEnabled00
static int tolua_CocoStudio_UIWidget_isTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFocused of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isFocused00
static int tolua_CocoStudio_UIWidget_isFocused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFocused'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFocused();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFocused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFocused of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setFocused00
static int tolua_CocoStudio_UIWidget_setFocused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool fucosed = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFocused'", NULL);
#endif
  {
   self->setFocused(fucosed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFocused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZOrder of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setZOrder00
static int tolua_CocoStudio_UIWidget_setZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int z = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZOrder'", NULL);
#endif
  {
   self->setZOrder(z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZOrder of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getZOrder00
static int tolua_CocoStudio_UIWidget_getZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getZOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftInParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getLeftInParent00
static int tolua_CocoStudio_UIWidget_getLeftInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftInParent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getLeftInParent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftInParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBottomInParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getBottomInParent00
static int tolua_CocoStudio_UIWidget_getBottomInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBottomInParent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getBottomInParent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBottomInParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightInParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRightInParent00
static int tolua_CocoStudio_UIWidget_getRightInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightInParent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRightInParent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightInParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTopInParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getTopInParent00
static int tolua_CocoStudio_UIWidget_getTopInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTopInParent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTopInParent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTopInParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_addChild00
static int tolua_CocoStudio_UIWidget_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addChild(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeChild00
static int tolua_CocoStudio_UIWidget_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeChild(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeFromParent00
static int tolua_CocoStudio_UIWidget_removeFromParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromParent'", NULL);
#endif
  {
   self->removeFromParent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildren of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeAllChildren00
static int tolua_CocoStudio_UIWidget_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildren'", NULL);
#endif
  {
   self->removeAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reorderChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_reorderChild00
static int tolua_CocoStudio_UIWidget_reorderChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reorderChild'", NULL);
#endif
  {
   self->reorderChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reorderChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getChildByName00
static int tolua_CocoStudio_UIWidget_getChildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getChildByName(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getChildByTag00
static int tolua_CocoStudio_UIWidget_getChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByTag'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getChildByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildren of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getChildren00
static int tolua_CocoStudio_UIWidget_getChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildren'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getChildren();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRenderer of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRenderer00
static int tolua_CocoStudio_UIWidget_getRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addRenderer of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_addRenderer00
static int tolua_CocoStudio_UIWidget_addRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* renderer = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addRenderer'", NULL);
#endif
  {
   self->addRenderer(renderer,zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeRenderer of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeRenderer00
static int tolua_CocoStudio_UIWidget_removeRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* renderer = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeRenderer'", NULL);
#endif
  {
   self->removeRenderer(renderer,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setParent00
static int tolua_CocoStudio_UIWidget_setParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* parent = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParent'", NULL);
#endif
  {
   self->setParent(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getParent00
static int tolua_CocoStudio_UIWidget_getParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParent'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getParent();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTouchEventListener of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_addTouchEventListener00
static int tolua_CocoStudio_UIWidget_addTouchEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_TouchEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_TouchEvent selector = *((SEL_TouchEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTouchEventListener'", NULL);
#endif
  {
   self->addTouchEventListener(target,selector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTouchEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setPosition00
static int tolua_CocoStudio_UIWidget_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pos = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(*pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionPercent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setPositionPercent00
static int tolua_CocoStudio_UIWidget_setPositionPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* percent = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionPercent'", NULL);
#endif
  {
   self->setPositionPercent(*percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPositionPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getPosition00
static int tolua_CocoStudio_UIWidget_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionPercent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getPositionPercent00
static int tolua_CocoStudio_UIWidget_getPositionPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionPercent'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getPositionPercent();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPositionPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionType of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setPositionType00
static int tolua_CocoStudio_UIWidget_setPositionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  PositionType type = ((PositionType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionType'", NULL);
#endif
  {
   self->setPositionType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPositionType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionType of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getPositionType00
static int tolua_CocoStudio_UIWidget_getPositionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionType'", NULL);
#endif
  {
   PositionType tolua_ret = (PositionType)  self->getPositionType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPositionType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setAnchorPoint00
static int tolua_CocoStudio_UIWidget_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchorPoint of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getAnchorPoint00
static int tolua_CocoStudio_UIWidget_getAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchorPoint'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getAnchorPoint();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setScale00
static int tolua_CocoStudio_UIWidget_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float fScale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale'", NULL);
#endif
  {
   self->setScale(fScale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScale of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getScale00
static int tolua_CocoStudio_UIWidget_getScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setScaleX00
static int tolua_CocoStudio_UIWidget_setScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float fScaleX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleX'", NULL);
#endif
  {
   self->setScaleX(fScaleX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getScaleX00
static int tolua_CocoStudio_UIWidget_getScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setScaleY00
static int tolua_CocoStudio_UIWidget_setScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float fScaleY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleY'", NULL);
#endif
  {
   self->setScaleY(fScaleY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getScaleY00
static int tolua_CocoStudio_UIWidget_getScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setRotation00
static int tolua_CocoStudio_UIWidget_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float rotation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'", NULL);
#endif
  {
   self->setRotation(rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRotation00
static int tolua_CocoStudio_UIWidget_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setRotationX00
static int tolua_CocoStudio_UIWidget_setRotationX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float rotationX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationX'", NULL);
#endif
  {
   self->setRotationX(rotationX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotationX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRotationX00
static int tolua_CocoStudio_UIWidget_getRotationX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotationX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotationX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotationX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setRotationY00
static int tolua_CocoStudio_UIWidget_setRotationY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float rotationY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationY'", NULL);
#endif
  {
   self->setRotationY(rotationY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotationY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRotationY00
static int tolua_CocoStudio_UIWidget_getRotationY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotationY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotationY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotationY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setFlipX00
static int tolua_CocoStudio_UIWidget_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isFlipX00
static int tolua_CocoStudio_UIWidget_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setFlipY00
static int tolua_CocoStudio_UIWidget_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isFlipY00
static int tolua_CocoStudio_UIWidget_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setColor00
static int tolua_CocoStudio_UIWidget_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getColor00
static int tolua_CocoStudio_UIWidget_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setOpacity00
static int tolua_CocoStudio_UIWidget_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int opacity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getOpacity00
static int tolua_CocoStudio_UIWidget_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeOpacityEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isCascadeOpacityEnabled00
static int tolua_CocoStudio_UIWidget_isCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeOpacityEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeOpacityEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeOpacityEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setCascadeOpacityEnabled00
static int tolua_CocoStudio_UIWidget_setCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeOpacityEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeOpacityEnabled'", NULL);
#endif
  {
   self->setCascadeOpacityEnabled(cascadeOpacityEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeColorEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isCascadeColorEnabled00
static int tolua_CocoStudio_UIWidget_isCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeColorEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeColorEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeColorEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setCascadeColorEnabled00
static int tolua_CocoStudio_UIWidget_setCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeColorEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeColorEnabled'", NULL);
#endif
  {
   self->setCascadeColorEnabled(cascadeColorEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setBlendFunc00
static int tolua_CocoStudio_UIWidget_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc blendFunc = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(blendFunc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionManager of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setActionManager00
static int tolua_CocoStudio_UIWidget_setActionManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCActionManager* actionManager = ((CCActionManager*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionManager'", NULL);
#endif
  {
   self->setActionManager(actionManager);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionManager of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getActionManager00
static int tolua_CocoStudio_UIWidget_getActionManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionManager'", NULL);
#endif
  {
   CCActionManager* tolua_ret = (CCActionManager*)  self->getActionManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCActionManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAction of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_runAction00
static int tolua_CocoStudio_UIWidget_runAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCAction* action = ((CCAction*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAction'", NULL);
#endif
  {
   CCAction* tolua_ret = (CCAction*)  self->runAction(action);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'runAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAllActions of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_stopAllActions00
static int tolua_CocoStudio_UIWidget_stopAllActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAllActions'", NULL);
#endif
  {
   self->stopAllActions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAllActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAction of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_stopAction00
static int tolua_CocoStudio_UIWidget_stopAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCAction* action = ((CCAction*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAction'", NULL);
#endif
  {
   self->stopAction(action);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopActionByTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_stopActionByTag00
static int tolua_CocoStudio_UIWidget_stopActionByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopActionByTag'", NULL);
#endif
  {
   self->stopActionByTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopActionByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionByTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getActionByTag00
static int tolua_CocoStudio_UIWidget_getActionByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionByTag'", NULL);
#endif
  {
   CCAction* tolua_ret = (CCAction*)  self->getActionByTag(tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: didNotSelectSelf of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_didNotSelectSelf00
static int tolua_CocoStudio_UIWidget_didNotSelectSelf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'didNotSelectSelf'", NULL);
#endif
  {
   self->didNotSelectSelf();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'didNotSelectSelf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clippingParentAreaContainPoint of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_clippingParentAreaContainPoint00
static int tolua_CocoStudio_UIWidget_clippingParentAreaContainPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clippingParentAreaContainPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->clippingParentAreaContainPoint(*pt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clippingParentAreaContainPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkChildInfo of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_checkChildInfo00
static int tolua_CocoStudio_UIWidget_checkChildInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int handleState = ((int)  tolua_tonumber(tolua_S,2,0));
  UIWidget* sender = ((UIWidget*)  tolua_tousertype(tolua_S,3,0));
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkChildInfo'", NULL);
#endif
  {
   self->checkChildInfo(handleState,sender,*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkChildInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchStartPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getTouchStartPos00
static int tolua_CocoStudio_UIWidget_getTouchStartPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchStartPos'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getTouchStartPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchStartPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchMovePos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getTouchMovePos00
static int tolua_CocoStudio_UIWidget_getTouchMovePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchMovePos'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getTouchMovePos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchMovePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchEndPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getTouchEndPos00
static int tolua_CocoStudio_UIWidget_getTouchEndPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchEndPos'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getTouchEndPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchEndPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setTag00
static int tolua_CocoStudio_UIWidget_setTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTag'", NULL);
#endif
  {
   self->setTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getTag00
static int tolua_CocoStudio_UIWidget_getTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setName00
static int tolua_CocoStudio_UIWidget_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getName00
static int tolua_CocoStudio_UIWidget_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetType of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getWidgetType00
static int tolua_CocoStudio_UIWidget_getWidgetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetType'", NULL);
#endif
  {
   WidgetType tolua_ret = (WidgetType)  self->getWidgetType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setSize00
static int tolua_CocoStudio_UIWidget_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'", NULL);
#endif
  {
   self->setSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSizePercent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setSizePercent00
static int tolua_CocoStudio_UIWidget_setSizePercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* percent = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSizePercent'", NULL);
#endif
  {
   self->setSizePercent(*percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSizePercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSizeType of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setSizeType00
static int tolua_CocoStudio_UIWidget_setSizeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  SizeType type = ((SizeType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSizeType'", NULL);
#endif
  {
   self->setSizeType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSizeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSizeType of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getSizeType00
static int tolua_CocoStudio_UIWidget_getSizeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSizeType'", NULL);
#endif
  {
   SizeType tolua_ret = (SizeType)  self->getSizeType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSizeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getSize00
static int tolua_CocoStudio_UIWidget_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSizePercent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getSizePercent00
static int tolua_CocoStudio_UIWidget_getSizePercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSizePercent'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getSizePercent();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSizePercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hitTest of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_hitTest00
static int tolua_CocoStudio_UIWidget_hitTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hitTest'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hitTest(*pt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hitTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchBegan of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onTouchBegan00
static int tolua_CocoStudio_UIWidget_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(*touchPoint);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchMoved of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onTouchMoved00
static int tolua_CocoStudio_UIWidget_onTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchMoved'", NULL);
#endif
  {
   self->onTouchMoved(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchEnded of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onTouchEnded00
static int tolua_CocoStudio_UIWidget_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchCancelled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onTouchCancelled00
static int tolua_CocoStudio_UIWidget_onTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchCancelled'", NULL);
#endif
  {
   self->onTouchCancelled(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchLongClicked of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onTouchLongClicked00
static int tolua_CocoStudio_UIWidget_onTouchLongClicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchLongClicked'", NULL);
#endif
  {
   self->onTouchLongClicked(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchLongClicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayoutParameter of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setLayoutParameter00
static int tolua_CocoStudio_UIWidget_setLayoutParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UILayoutParameter* parameter = ((UILayoutParameter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayoutParameter'", NULL);
#endif
  {
   self->setLayoutParameter(parameter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayoutParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayoutParameter of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getLayoutParameter00
static int tolua_CocoStudio_UIWidget_getLayoutParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  LayoutParameterType type = ((LayoutParameterType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutParameter'", NULL);
#endif
  {
   UILayoutParameter* tolua_ret = (UILayoutParameter*)  self->getLayoutParameter(type);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayoutParameter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayoutParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ignoreContentAdaptWithSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_UIWidget_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool ignore = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ignoreContentAdaptWithSize'", NULL);
#endif
  {
   self->ignoreContentAdaptWithSize(ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ignoreContentAdaptWithSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isIgnoreContentAdaptWithSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isIgnoreContentAdaptWithSize00
static int tolua_CocoStudio_UIWidget_isIgnoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isIgnoreContentAdaptWithSize'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isIgnoreContentAdaptWithSize();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isIgnoreContentAdaptWithSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldPosition of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getWorldPosition00
static int tolua_CocoStudio_UIWidget_getWorldPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldPosition'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getWorldPosition();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertToWorldSpace of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_convertToWorldSpace00
static int tolua_CocoStudio_UIWidget_convertToWorldSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertToWorldSpace'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->convertToWorldSpace(*pt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertToWorldSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getVirtualRenderer00
static int tolua_CocoStudio_UIWidget_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setUpdateEnabled00
static int tolua_CocoStudio_UIWidget_setUpdateEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUpdateEnabled'", NULL);
#endif
  {
   self->setUpdateEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isUpdateEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isUpdateEnabled00
static int tolua_CocoStudio_UIWidget_isUpdateEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isUpdateEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isUpdateEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isUpdateEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getContentSize00
static int tolua_CocoStudio_UIWidget_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getDescription00
static int tolua_CocoStudio_UIWidget_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIWidget* self = (const UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clone of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_clone00
static int tolua_CocoStudio_UIWidget_clone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clone'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->clone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onEnter00
static int tolua_CocoStudio_UIWidget_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnter'", NULL);
#endif
  {
   self->onEnter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onExit of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_onExit00
static int tolua_CocoStudio_UIWidget_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onExit'", NULL);
#endif
  {
   self->onExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUserObject of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getUserObject00
static int tolua_CocoStudio_UIWidget_getUserObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUserObject'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->getUserObject();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUserObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUserObject of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setUserObject00
static int tolua_CocoStudio_UIWidget_setUserObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pUserObject = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUserObject'", NULL);
#endif
  {
   self->setUserObject(pUserObject);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUserObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setTouchEnable00
static int tolua_CocoStudio_UIWidget_setTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnable'", NULL);
#endif
  {
   self->setTouchEnable(enabled,containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_disable00
static int tolua_CocoStudio_UIWidget_disable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disable'", NULL);
#endif
  {
   self->disable(containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: active of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_active00
static int tolua_CocoStudio_UIWidget_active00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'active'", NULL);
#endif
  {
   self->active(containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'active'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isActive of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_isActive00
static int tolua_CocoStudio_UIWidget_isActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isActive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isActive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBright of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setBright01
static int tolua_CocoStudio_UIWidget_setBright01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool bright = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool containChild = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBright'", NULL);
#endif
  {
   self->setBright(bright,containChild);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_UIWidget_setBright00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRect of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRect00
static int tolua_CocoStudio_UIWidget_getRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRect'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getRect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNode of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getValidNode00
static int tolua_CocoStudio_UIWidget_getValidNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getValidNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetZOrder of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setWidgetZOrder00
static int tolua_CocoStudio_UIWidget_setWidgetZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int z = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetZOrder'", NULL);
#endif
  {
   self->setWidgetZOrder(z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetZOrder of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getWidgetZOrder00
static int tolua_CocoStudio_UIWidget_getWidgetZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetZOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWidgetZOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeLeftPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRelativeLeftPos00
static int tolua_CocoStudio_UIWidget_getRelativeLeftPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeLeftPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeLeftPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeLeftPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeBottomPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRelativeBottomPos00
static int tolua_CocoStudio_UIWidget_getRelativeBottomPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeBottomPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeBottomPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeBottomPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeRightPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRelativeRightPos00
static int tolua_CocoStudio_UIWidget_getRelativeRightPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeRightPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeRightPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeRightPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeTopPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getRelativeTopPos00
static int tolua_CocoStudio_UIWidget_getRelativeTopPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeTopPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeTopPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeTopPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainerNode of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getContainerNode00
static int tolua_CocoStudio_UIWidget_getContainerNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainerNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getContainerNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContainerNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setWidgetParent00
static int tolua_CocoStudio_UIWidget_setWidgetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* parent = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetParent'", NULL);
#endif
  {
   self->setWidgetParent(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getWidgetParent00
static int tolua_CocoStudio_UIWidget_getWidgetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetParent'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getWidgetParent();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setWidgetTag00
static int tolua_CocoStudio_UIWidget_setWidgetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetTag'", NULL);
#endif
  {
   self->setWidgetTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getWidgetTag00
static int tolua_CocoStudio_UIWidget_getWidgetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWidgetTag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addCCNode of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_addCCNode00
static int tolua_CocoStudio_UIWidget_addCCNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCCNode'", NULL);
#endif
  {
   self->addCCNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addCCNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeChild01
static int tolua_CocoStudio_UIWidget_removeChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeChild(child,cleanup);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_UIWidget_removeChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParentAndCleanup of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeFromParentAndCleanup00
static int tolua_CocoStudio_UIWidget_removeFromParentAndCleanup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromParentAndCleanup'", NULL);
#endif
  {
   self->removeFromParentAndCleanup(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromParentAndCleanup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildrenAndCleanUp of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_removeAllChildrenAndCleanUp00
static int tolua_CocoStudio_UIWidget_removeAllChildrenAndCleanUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildrenAndCleanUp'", NULL);
#endif
  {
   self->removeAllChildrenAndCleanUp(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildrenAndCleanUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_setActionTag00
static int tolua_CocoStudio_UIWidget_setActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionTag'", NULL);
#endif
  {
   self->setActionTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_getActionTag00
static int tolua_CocoStudio_UIWidget_getActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getActionTag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateSizeAndPosition of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIWidget_updateSizeAndPosition00
static int tolua_CocoStudio_UIWidget_updateSizeAndPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateSizeAndPosition'", NULL);
#endif
  {
   self->updateSizeAndPosition();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateSizeAndPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_new00
static int tolua_CocoStudio_UILayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayer* tolua_ret = (UILayer*)  Mtolua_new((UILayer)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayer");
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

/* method: new_local of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_new00_local
static int tolua_CocoStudio_UILayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayer* tolua_ret = (UILayer*)  Mtolua_new((UILayer)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayer");
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

/* method: delete of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_delete00
static int tolua_CocoStudio_UILayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_create00
static int tolua_CocoStudio_UILayer_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayer* tolua_ret = (UILayer*)  UILayer::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayer");
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

/* method: init of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_init00
static int tolua_CocoStudio_UILayer_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_addWidget00
static int tolua_CocoStudio_UILayer_addWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addWidget'", NULL);
#endif
  {
   self->addWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_removeWidget00
static int tolua_CocoStudio_UILayer_removeWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeWidget'", NULL);
#endif
  {
   self->removeWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_setVisible00
static int tolua_CocoStudio_UILayer_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetByTag of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_getWidgetByTag00
static int tolua_CocoStudio_UILayer_getWidgetByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetByTag'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getWidgetByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetByName of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_getWidgetByName00
static int tolua_CocoStudio_UILayer_getWidgetByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetByName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getWidgetByName(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_clear00
static int tolua_CocoStudio_UILayer_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_getRootWidget00
static int tolua_CocoStudio_UILayer_getRootWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootWidget'", NULL);
#endif
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  self->getRootWidget();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIRootWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_dispose00
static int tolua_CocoStudio_UILayer_dispose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeWidgetAndCleanUp of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayer_removeWidgetAndCleanUp00
static int tolua_CocoStudio_UILayer_removeWidgetAndCleanUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeWidgetAndCleanUp'", NULL);
#endif
  {
   self->removeWidgetAndCleanUp(widget,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeWidgetAndCleanUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_new00
static int tolua_CocoStudio_UIButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  Mtolua_new((UIButton)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIButton");
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

/* method: new_local of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_new00_local
static int tolua_CocoStudio_UIButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  Mtolua_new((UIButton)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIButton");
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

/* method: delete of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_delete00
static int tolua_CocoStudio_UIButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_create00
static int tolua_CocoStudio_UIButton_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  UIButton::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIButton");
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

/* method: loadTextures of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_loadTextures00
static int tolua_CocoStudio_UIButton_loadTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* selected = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,4,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,5,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextures'", NULL);
#endif
  {
   self->loadTextures(normal,selected,disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureNormal of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_loadTextureNormal00
static int tolua_CocoStudio_UIButton_loadTextureNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureNormal'", NULL);
#endif
  {
   self->loadTextureNormal(normal,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureNormal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTexturePressed of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_loadTexturePressed00
static int tolua_CocoStudio_UIButton_loadTexturePressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* selected = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTexturePressed'", NULL);
#endif
  {
   self->loadTexturePressed(selected,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTexturePressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureDisabled of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_loadTextureDisabled00
static int tolua_CocoStudio_UIButton_loadTextureDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureDisabled'", NULL);
#endif
  {
   self->loadTextureDisabled(disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureDisabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setCapInsets00
static int tolua_CocoStudio_UIButton_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsets'", NULL);
#endif
  {
   self->setCapInsets(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetsNormalRenderer of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setCapInsetsNormalRenderer00
static int tolua_CocoStudio_UIButton_setCapInsetsNormalRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsetsNormalRenderer'", NULL);
#endif
  {
   self->setCapInsetsNormalRenderer(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsetsNormalRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetsPressedRenderer of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setCapInsetsPressedRenderer00
static int tolua_CocoStudio_UIButton_setCapInsetsPressedRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsetsPressedRenderer'", NULL);
#endif
  {
   self->setCapInsetsPressedRenderer(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsetsPressedRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetsDisabledRenderer of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setCapInsetsDisabledRenderer00
static int tolua_CocoStudio_UIButton_setCapInsetsDisabledRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsetsDisabledRenderer'", NULL);
#endif
  {
   self->setCapInsetsDisabledRenderer(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsetsDisabledRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setAnchorPoint00
static int tolua_CocoStudio_UIButton_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enabled of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setScale9Enabled00
static int tolua_CocoStudio_UIButton_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enabled'", NULL);
#endif
  {
   self->setScale9Enabled(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setFlipX00
static int tolua_CocoStudio_UIButton_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setFlipY00
static int tolua_CocoStudio_UIButton_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_isFlipX00
static int tolua_CocoStudio_UIButton_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_isFlipY00
static int tolua_CocoStudio_UIButton_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPressedActionEnabled of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setPressedActionEnabled00
static int tolua_CocoStudio_UIButton_setPressedActionEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPressedActionEnabled'", NULL);
#endif
  {
   self->setPressedActionEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPressedActionEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ignoreContentAdaptWithSize of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_UIButton_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  bool ignore = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ignoreContentAdaptWithSize'", NULL);
#endif
  {
   self->ignoreContentAdaptWithSize(ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ignoreContentAdaptWithSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getContentSize00
static int tolua_CocoStudio_UIButton_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButton* self = (const UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getVirtualRenderer00
static int tolua_CocoStudio_UIButton_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setColor00
static int tolua_CocoStudio_UIButton_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getDescription00
static int tolua_CocoStudio_UIButton_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButton* self = (const UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleText of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setTitleText00
static int tolua_CocoStudio_UIButton_setTitleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleText'", NULL);
#endif
  {
   self->setTitleText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleText of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getTitleText00
static int tolua_CocoStudio_UIButton_getTitleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButton* self = (const UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleText'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getTitleText();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleColor of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setTitleColor00
static int tolua_CocoStudio_UIButton_setTitleColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleColor'", NULL);
#endif
  {
   self->setTitleColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleColor of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getTitleColor00
static int tolua_CocoStudio_UIButton_getTitleColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButton* self = (const UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getTitleColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleFontSize of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setTitleFontSize00
static int tolua_CocoStudio_UIButton_setTitleFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleFontSize'", NULL);
#endif
  {
   self->setTitleFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleFontSize of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getTitleFontSize00
static int tolua_CocoStudio_UIButton_getTitleFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButton* self = (const UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleFontSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTitleFontSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleFontName of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setTitleFontName00
static int tolua_CocoStudio_UIButton_setTitleFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleFontName'", NULL);
#endif
  {
   self->setTitleFontName(fontName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleFontName of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_getTitleFontName00
static int tolua_CocoStudio_UIButton_getTitleFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButton* self = (const UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleFontName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getTitleFontName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setText00
static int tolua_CocoStudio_UIButton_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextColor of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setTextColor00
static int tolua_CocoStudio_UIButton_setTextColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  int r = ((int)  tolua_tonumber(tolua_S,2,0));
  int g = ((int)  tolua_tonumber(tolua_S,3,0));
  int b = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextColor'", NULL);
#endif
  {
   self->setTextColor(r,g,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontSize of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setFontSize00
static int tolua_CocoStudio_UIButton_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontSize'", NULL);
#endif
  {
   self->setFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setFontName00
static int tolua_CocoStudio_UIButton_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(fontName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextures of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setTextures00
static int tolua_CocoStudio_UIButton_setTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* selected = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,4,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,5,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextures'", NULL);
#endif
  {
   self->setTextures(normal,selected,disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNormalTexture of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setNormalTexture00
static int tolua_CocoStudio_UIButton_setNormalTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNormalTexture'", NULL);
#endif
  {
   self->setNormalTexture(normal,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNormalTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPressedTexture of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setPressedTexture00
static int tolua_CocoStudio_UIButton_setPressedTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* selected = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPressedTexture'", NULL);
#endif
  {
   self->setPressedTexture(selected,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPressedTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisabledTexture of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setDisabledTexture00
static int tolua_CocoStudio_UIButton_setDisabledTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisabledTexture'", NULL);
#endif
  {
   self->setDisabledTexture(disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisabledTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enable of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setScale9Enable00
static int tolua_CocoStudio_UIButton_setScale9Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enable'", NULL);
#endif
  {
   self->setScale9Enable(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Size of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIButton_setScale9Size00
static int tolua_CocoStudio_UIButton_setScale9Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Size'", NULL);
#endif
  {
   self->setScale9Size(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_new00
static int tolua_CocoStudio_UICheckBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UICheckBox* tolua_ret = (UICheckBox*)  Mtolua_new((UICheckBox)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UICheckBox");
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

/* method: new_local of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_new00_local
static int tolua_CocoStudio_UICheckBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UICheckBox* tolua_ret = (UICheckBox*)  Mtolua_new((UICheckBox)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UICheckBox");
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

/* method: delete of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_delete00
static int tolua_CocoStudio_UICheckBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_create00
static int tolua_CocoStudio_UICheckBox_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UICheckBox* tolua_ret = (UICheckBox*)  UICheckBox::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UICheckBox");
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

/* method: loadTextures of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_loadTextures00
static int tolua_CocoStudio_UICheckBox_loadTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGround = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* backGroundSelected = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* cross = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* backGroundDisabled = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* frontCrossDisabled = ((const char*)  tolua_tostring(tolua_S,6,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,7,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextures'", NULL);
#endif
  {
   self->loadTextures(backGround,backGroundSelected,cross,backGroundDisabled,frontCrossDisabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureBackGround of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_loadTextureBackGround00
static int tolua_CocoStudio_UICheckBox_loadTextureBackGround00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGround = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType type = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureBackGround'", NULL);
#endif
  {
   self->loadTextureBackGround(backGround,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureBackGround'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureBackGroundSelected of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_loadTextureBackGroundSelected00
static int tolua_CocoStudio_UICheckBox_loadTextureBackGroundSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGroundSelected = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureBackGroundSelected'", NULL);
#endif
  {
   self->loadTextureBackGroundSelected(backGroundSelected,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureBackGroundSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureFrontCross of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_loadTextureFrontCross00
static int tolua_CocoStudio_UICheckBox_loadTextureFrontCross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* cross = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureFrontCross'", NULL);
#endif
  {
   self->loadTextureFrontCross(cross,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureFrontCross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureBackGroundDisabled of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_loadTextureBackGroundDisabled00
static int tolua_CocoStudio_UICheckBox_loadTextureBackGroundDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGroundDisabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureBackGroundDisabled'", NULL);
#endif
  {
   self->loadTextureBackGroundDisabled(backGroundDisabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureBackGroundDisabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTextureFrontCrossDisabled of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_loadTextureFrontCrossDisabled00
static int tolua_CocoStudio_UICheckBox_loadTextureFrontCrossDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* frontCrossDisabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTextureFrontCrossDisabled'", NULL);
#endif
  {
   self->loadTextureFrontCrossDisabled(frontCrossDisabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTextureFrontCrossDisabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSelectedState of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setSelectedState00
static int tolua_CocoStudio_UICheckBox_setSelectedState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool selected = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSelectedState'", NULL);
#endif
  {
   self->setSelectedState(selected);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSelectedState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSelectedState of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_getSelectedState00
static int tolua_CocoStudio_UICheckBox_getSelectedState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSelectedState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getSelectedState();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSelectedState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setAnchorPoint00
static int tolua_CocoStudio_UICheckBox_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setFlipX00
static int tolua_CocoStudio_UICheckBox_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setFlipY00
static int tolua_CocoStudio_UICheckBox_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_isFlipX00
static int tolua_CocoStudio_UICheckBox_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_isFlipY00
static int tolua_CocoStudio_UICheckBox_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_getContentSize00
static int tolua_CocoStudio_UICheckBox_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UICheckBox* self = (const UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_getVirtualRenderer00
static int tolua_CocoStudio_UICheckBox_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_getDescription00
static int tolua_CocoStudio_UICheckBox_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UICheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UICheckBox* self = (const UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextures of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setTextures00
static int tolua_CocoStudio_UICheckBox_setTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGround = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* backGroundSelected = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* cross = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* backGroundDisabled = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* frontCrossDisabled = ((const char*)  tolua_tostring(tolua_S,6,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,7,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextures'", NULL);
#endif
  {
   self->setTextures(backGround,backGroundSelected,cross,backGroundDisabled,frontCrossDisabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundTexture of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setBackGroundTexture00
static int tolua_CocoStudio_UICheckBox_setBackGroundTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGround = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType type = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundTexture'", NULL);
#endif
  {
   self->setBackGroundTexture(backGround,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundSelectedTexture of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setBackGroundSelectedTexture00
static int tolua_CocoStudio_UICheckBox_setBackGroundSelectedTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGroundSelected = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundSelectedTexture'", NULL);
#endif
  {
   self->setBackGroundSelectedTexture(backGroundSelected,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundSelectedTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFrontCrossTexture of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setFrontCrossTexture00
static int tolua_CocoStudio_UICheckBox_setFrontCrossTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* cross = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrontCrossTexture'", NULL);
#endif
  {
   self->setFrontCrossTexture(cross,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFrontCrossTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundDisabledTexture of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setBackGroundDisabledTexture00
static int tolua_CocoStudio_UICheckBox_setBackGroundDisabledTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* backGroundDisabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundDisabledTexture'", NULL);
#endif
  {
   self->setBackGroundDisabledTexture(backGroundDisabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundDisabledTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFrontCrossDisabledTexture of class  UICheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UICheckBox_setFrontCrossDisabledTexture00
static int tolua_CocoStudio_UICheckBox_setFrontCrossDisabledTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* frontCrossDisabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrontCrossDisabledTexture'", NULL);
#endif
  {
   self->setFrontCrossDisabledTexture(frontCrossDisabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFrontCrossDisabledTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_new00
static int tolua_CocoStudio_UIImageView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIImageView* tolua_ret = (UIImageView*)  Mtolua_new((UIImageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIImageView");
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

/* method: new_local of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_new00_local
static int tolua_CocoStudio_UIImageView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIImageView* tolua_ret = (UIImageView*)  Mtolua_new((UIImageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIImageView");
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

/* method: delete of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_delete00
static int tolua_CocoStudio_UIImageView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_create00
static int tolua_CocoStudio_UIImageView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIImageView* tolua_ret = (UIImageView*)  UIImageView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIImageView");
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

/* method: loadTexture of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_loadTexture00
static int tolua_CocoStudio_UIImageView_loadTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTexture'", NULL);
#endif
  {
   self->loadTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextureRect of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setTextureRect00
static int tolua_CocoStudio_UIImageView_setTextureRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextureRect'", NULL);
#endif
  {
   self->setTextureRect(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextureRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enabled of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setScale9Enabled00
static int tolua_CocoStudio_UIImageView_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enabled'", NULL);
#endif
  {
   self->setScale9Enabled(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setCapInsets00
static int tolua_CocoStudio_UIImageView_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsets'", NULL);
#endif
  {
   self->setCapInsets(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setFlipX00
static int tolua_CocoStudio_UIImageView_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setFlipY00
static int tolua_CocoStudio_UIImageView_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_isFlipX00
static int tolua_CocoStudio_UIImageView_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_isFlipY00
static int tolua_CocoStudio_UIImageView_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setAnchorPoint00
static int tolua_CocoStudio_UIImageView_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ignoreContentAdaptWithSize of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_UIImageView_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool ignore = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ignoreContentAdaptWithSize'", NULL);
#endif
  {
   self->ignoreContentAdaptWithSize(ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ignoreContentAdaptWithSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_getDescription00
static int tolua_CocoStudio_UIImageView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIImageView* self = (const UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDoubleClickEnabled of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setDoubleClickEnabled00
static int tolua_CocoStudio_UIImageView_setDoubleClickEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDoubleClickEnabled'", NULL);
#endif
  {
   self->setDoubleClickEnabled(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDoubleClickEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doubleClickEvent of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_doubleClickEvent00
static int tolua_CocoStudio_UIImageView_doubleClickEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doubleClickEvent'", NULL);
#endif
  {
   self->doubleClickEvent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doubleClickEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkDoubleClick of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_checkDoubleClick00
static int tolua_CocoStudio_UIImageView_checkDoubleClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkDoubleClick'", NULL);
#endif
  {
   self->checkDoubleClick(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkDoubleClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTexture of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setTexture00
static int tolua_CocoStudio_UIImageView_setTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTexture'", NULL);
#endif
  {
   self->setTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Size of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setScale9Size00
static int tolua_CocoStudio_UIImageView_setScale9Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Size'", NULL);
#endif
  {
   self->setScale9Size(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enable of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_setScale9Enable00
static int tolua_CocoStudio_UIImageView_setScale9Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enable'", NULL);
#endif
  {
   self->setScale9Enable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_getContentSize00
static int tolua_CocoStudio_UIImageView_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIImageView* self = (const UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIImageView_getVirtualRenderer00
static int tolua_CocoStudio_UIImageView_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_new00
static int tolua_CocoStudio_UILabel_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabel* tolua_ret = (UILabel*)  Mtolua_new((UILabel)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILabel");
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

/* method: new_local of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_new00_local
static int tolua_CocoStudio_UILabel_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabel* tolua_ret = (UILabel*)  Mtolua_new((UILabel)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILabel");
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

/* method: delete of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_delete00
static int tolua_CocoStudio_UILabel_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_create00
static int tolua_CocoStudio_UILabel_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabel* tolua_ret = (UILabel*)  UILabel::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILabel");
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

/* method: setText of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setText00
static int tolua_CocoStudio_UILabel_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_getStringValue00
static int tolua_CocoStudio_UILabel_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringValue'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStringValue();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringLength of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_getStringLength00
static int tolua_CocoStudio_UILabel_getStringLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getStringLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontSize of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setFontSize00
static int tolua_CocoStudio_UILabel_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontSize'", NULL);
#endif
  {
   self->setFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setFontName00
static int tolua_CocoStudio_UILabel_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchScaleChangeEnabled of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setTouchScaleChangeEnabled00
static int tolua_CocoStudio_UILabel_setTouchScaleChangeEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchScaleChangeEnabled'", NULL);
#endif
  {
   self->setTouchScaleChangeEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchScaleChangeEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchScaleChangeEnabled of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_isTouchScaleChangeEnabled00
static int tolua_CocoStudio_UILabel_isTouchScaleChangeEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchScaleChangeEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchScaleChangeEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchScaleChangeEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setFlipX00
static int tolua_CocoStudio_UILabel_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setFlipY00
static int tolua_CocoStudio_UILabel_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_isFlipX00
static int tolua_CocoStudio_UILabel_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_isFlipY00
static int tolua_CocoStudio_UILabel_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setAnchorPoint00
static int tolua_CocoStudio_UILabel_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_getContentSize00
static int tolua_CocoStudio_UILabel_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILabel* self = (const UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_getVirtualRenderer00
static int tolua_CocoStudio_UILabel_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setScale00
static int tolua_CocoStudio_UILabel_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  float fScale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale'", NULL);
#endif
  {
   self->setScale(fScale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleX of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setScaleX00
static int tolua_CocoStudio_UILabel_setScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  float fScaleX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleX'", NULL);
#endif
  {
   self->setScaleX(fScaleX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleY of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setScaleY00
static int tolua_CocoStudio_UILabel_setScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  float fScaleY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleY'", NULL);
#endif
  {
   self->setScaleY(fScaleY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_getDescription00
static int tolua_CocoStudio_UILabel_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILabel* self = (const UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextAreaSize of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setTextAreaSize00
static int tolua_CocoStudio_UILabel_setTextAreaSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextAreaSize'", NULL);
#endif
  {
   self->setTextAreaSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextAreaSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextHorizontalAlignment of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setTextHorizontalAlignment00
static int tolua_CocoStudio_UILabel_setTextHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  CCTextAlignment alignment = ((CCTextAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextHorizontalAlignment'", NULL);
#endif
  {
   self->setTextHorizontalAlignment(alignment);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextVerticalAlignment of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setTextVerticalAlignment00
static int tolua_CocoStudio_UILabel_setTextVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCVerticalTextAlignment",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  CCVerticalTextAlignment alignment = *((CCVerticalTextAlignment*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextVerticalAlignment'", NULL);
#endif
  {
   self->setTextVerticalAlignment(alignment);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchScaleChangeAble of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_setTouchScaleChangeAble00
static int tolua_CocoStudio_UILabel_setTouchScaleChangeAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchScaleChangeAble'", NULL);
#endif
  {
   self->setTouchScaleChangeAble(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchScaleChangeAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchScaleChangeAble of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabel_getTouchScaleChangeAble00
static int tolua_CocoStudio_UILabel_getTouchScaleChangeAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchScaleChangeAble'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getTouchScaleChangeAble();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchScaleChangeAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_new00
static int tolua_CocoStudio_UILabelAtlas_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabelAtlas* tolua_ret = (UILabelAtlas*)  Mtolua_new((UILabelAtlas)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILabelAtlas");
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

/* method: new_local of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_new00_local
static int tolua_CocoStudio_UILabelAtlas_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabelAtlas* tolua_ret = (UILabelAtlas*)  Mtolua_new((UILabelAtlas)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILabelAtlas");
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

/* method: delete of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_delete00
static int tolua_CocoStudio_UILabelAtlas_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelAtlas* self = (UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_create00
static int tolua_CocoStudio_UILabelAtlas_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabelAtlas* tolua_ret = (UILabelAtlas*)  UILabelAtlas::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILabelAtlas");
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

/* method: setProperty of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_setProperty00
static int tolua_CocoStudio_UILabelAtlas_setProperty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelAtlas* self = (UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
  const char* stringValue = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* charMapFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  int itemWidth = ((int)  tolua_tonumber(tolua_S,4,0));
  int itemHeight = ((int)  tolua_tonumber(tolua_S,5,0));
  const char* startCharMap = ((const char*)  tolua_tostring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProperty'", NULL);
#endif
  {
   self->setProperty(stringValue,charMapFile,itemWidth,itemHeight,startCharMap);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProperty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStringValue of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_setStringValue00
static int tolua_CocoStudio_UILabelAtlas_setStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelAtlas* self = (UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStringValue'", NULL);
#endif
  {
   self->setStringValue(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_getStringValue00
static int tolua_CocoStudio_UILabelAtlas_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelAtlas* self = (UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringValue'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStringValue();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_setAnchorPoint00
static int tolua_CocoStudio_UILabelAtlas_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelAtlas* self = (UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_getContentSize00
static int tolua_CocoStudio_UILabelAtlas_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILabelAtlas* self = (const UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_getVirtualRenderer00
static int tolua_CocoStudio_UILabelAtlas_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelAtlas* self = (UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UILabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelAtlas_getDescription00
static int tolua_CocoStudio_UILabelAtlas_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILabelAtlas* self = (const UILabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_new00
static int tolua_CocoStudio_UILabelBMFont_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabelBMFont* tolua_ret = (UILabelBMFont*)  Mtolua_new((UILabelBMFont)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UILabelBMFont");
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

/* method: new_local of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_new00_local
static int tolua_CocoStudio_UILabelBMFont_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabelBMFont* tolua_ret = (UILabelBMFont*)  Mtolua_new((UILabelBMFont)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UILabelBMFont");
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

/* method: delete of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_delete00
static int tolua_CocoStudio_UILabelBMFont_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelBMFont* self = (UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_create00
static int tolua_CocoStudio_UILabelBMFont_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabelBMFont* tolua_ret = (UILabelBMFont*)  UILabelBMFont::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UILabelBMFont");
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

/* method: setFntFile of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_setFntFile00
static int tolua_CocoStudio_UILabelBMFont_setFntFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelBMFont* self = (UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFntFile'", NULL);
#endif
  {
   self->setFntFile(fileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFntFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_setText00
static int tolua_CocoStudio_UILabelBMFont_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelBMFont* self = (UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_getStringValue00
static int tolua_CocoStudio_UILabelBMFont_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelBMFont* self = (UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringValue'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStringValue();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_setAnchorPoint00
static int tolua_CocoStudio_UILabelBMFont_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelBMFont* self = (UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_getContentSize00
static int tolua_CocoStudio_UILabelBMFont_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILabelBMFont* self = (const UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_getVirtualRenderer00
static int tolua_CocoStudio_UILabelBMFont_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabelBMFont* self = (UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UILabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILabelBMFont_getDescription00
static int tolua_CocoStudio_UILabelBMFont_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILabelBMFont* self = (const UILabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_new00
static int tolua_CocoStudio_UILoadingBar_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILoadingBar* tolua_ret = (UILoadingBar*)  Mtolua_new((UILoadingBar)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILoadingBar");
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

/* method: new_local of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_new00_local
static int tolua_CocoStudio_UILoadingBar_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILoadingBar* tolua_ret = (UILoadingBar*)  Mtolua_new((UILoadingBar)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILoadingBar");
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

/* method: delete of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_delete00
static int tolua_CocoStudio_UILoadingBar_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_create00
static int tolua_CocoStudio_UILoadingBar_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILoadingBar* tolua_ret = (UILoadingBar*)  UILoadingBar::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILoadingBar");
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

/* method: setDirection of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setDirection00
static int tolua_CocoStudio_UILoadingBar_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  LoadingBarType dir = ((LoadingBarType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirection'", NULL);
#endif
  {
   self->setDirection(dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDirection of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_getDirection00
static int tolua_CocoStudio_UILoadingBar_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDirection'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDirection();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadTexture of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_loadTexture00
static int tolua_CocoStudio_UILoadingBar_loadTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  const char* texture = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadTexture'", NULL);
#endif
  {
   self->loadTexture(texture,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPercent of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setPercent00
static int tolua_CocoStudio_UILoadingBar_setPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  int percent = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPercent'", NULL);
#endif
  {
   self->setPercent(percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPercent of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_getPercent00
static int tolua_CocoStudio_UILoadingBar_getPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPercent'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enabled of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setScale9Enabled00
static int tolua_CocoStudio_UILoadingBar_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enabled'", NULL);
#endif
  {
   self->setScale9Enabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setCapInsets00
static int tolua_CocoStudio_UILoadingBar_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsets'", NULL);
#endif
  {
   self->setCapInsets(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ignoreContentAdaptWithSize of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_UILoadingBar_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  bool ignore = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ignoreContentAdaptWithSize'", NULL);
#endif
  {
   self->ignoreContentAdaptWithSize(ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ignoreContentAdaptWithSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_getContentSize00
static int tolua_CocoStudio_UILoadingBar_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILoadingBar* self = (const UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_getVirtualRenderer00
static int tolua_CocoStudio_UILoadingBar_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_getDescription00
static int tolua_CocoStudio_UILoadingBar_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILoadingBar* self = (const UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTexture of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setTexture00
static int tolua_CocoStudio_UILoadingBar_setTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  const char* texture = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTexture'", NULL);
#endif
  {
   self->setTexture(texture,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Size of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setScale9Size00
static int tolua_CocoStudio_UILoadingBar_setScale9Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Size'", NULL);
#endif
  {
   self->setScale9Size(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enable of class  UILoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILoadingBar_setScale9Enable00
static int tolua_CocoStudio_UILoadingBar_setScale9Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILoadingBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILoadingBar* self = (UILoadingBar*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enable'", NULL);
#endif
  {
   self->setScale9Enable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_new00
static int tolua_CocoStudio_UISlider_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UISlider* tolua_ret = (UISlider*)  Mtolua_new((UISlider)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UISlider");
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

/* method: new_local of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_new00_local
static int tolua_CocoStudio_UISlider_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UISlider* tolua_ret = (UISlider*)  Mtolua_new((UISlider)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UISlider");
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

/* method: delete of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_delete00
static int tolua_CocoStudio_UISlider_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_create00
static int tolua_CocoStudio_UISlider_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UISlider* tolua_ret = (UISlider*)  UISlider::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UISlider");
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

/* method: loadBarTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_loadBarTexture00
static int tolua_CocoStudio_UISlider_loadBarTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadBarTexture'", NULL);
#endif
  {
   self->loadBarTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadBarTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enabled of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setScale9Enabled00
static int tolua_CocoStudio_UISlider_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enabled'", NULL);
#endif
  {
   self->setScale9Enabled(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setCapInsets00
static int tolua_CocoStudio_UISlider_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsets'", NULL);
#endif
  {
   self->setCapInsets(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetsBarRenderer of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setCapInsetsBarRenderer00
static int tolua_CocoStudio_UISlider_setCapInsetsBarRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsetsBarRenderer'", NULL);
#endif
  {
   self->setCapInsetsBarRenderer(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsetsBarRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetProgressBarRebderer of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setCapInsetProgressBarRebderer00
static int tolua_CocoStudio_UISlider_setCapInsetProgressBarRebderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsetProgressBarRebderer'", NULL);
#endif
  {
   self->setCapInsetProgressBarRebderer(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsetProgressBarRebderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadSlidBallTextures of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_loadSlidBallTextures00
static int tolua_CocoStudio_UISlider_loadSlidBallTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* pressed = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,4,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,5,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadSlidBallTextures'", NULL);
#endif
  {
   self->loadSlidBallTextures(normal,pressed,disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadSlidBallTextures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadSlidBallTextureNormal of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_loadSlidBallTextureNormal00
static int tolua_CocoStudio_UISlider_loadSlidBallTextureNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadSlidBallTextureNormal'", NULL);
#endif
  {
   self->loadSlidBallTextureNormal(normal,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadSlidBallTextureNormal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadSlidBallTexturePressed of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_loadSlidBallTexturePressed00
static int tolua_CocoStudio_UISlider_loadSlidBallTexturePressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* pressed = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadSlidBallTexturePressed'", NULL);
#endif
  {
   self->loadSlidBallTexturePressed(pressed,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadSlidBallTexturePressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadSlidBallTextureDisabled of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_loadSlidBallTextureDisabled00
static int tolua_CocoStudio_UISlider_loadSlidBallTextureDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadSlidBallTextureDisabled'", NULL);
#endif
  {
   self->loadSlidBallTextureDisabled(disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadSlidBallTextureDisabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadProgressBarTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_loadProgressBarTexture00
static int tolua_CocoStudio_UISlider_loadProgressBarTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadProgressBarTexture'", NULL);
#endif
  {
   self->loadProgressBarTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadProgressBarTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPercent of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setPercent00
static int tolua_CocoStudio_UISlider_setPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  int percent = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPercent'", NULL);
#endif
  {
   self->setPercent(percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPercent of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_getPercent00
static int tolua_CocoStudio_UISlider_getPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPercent'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_getContentSize00
static int tolua_CocoStudio_UISlider_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UISlider* self = (const UISlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_getVirtualRenderer00
static int tolua_CocoStudio_UISlider_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ignoreContentAdaptWithSize of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_UISlider_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  bool ignore = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ignoreContentAdaptWithSize'", NULL);
#endif
  {
   self->ignoreContentAdaptWithSize(ignore);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ignoreContentAdaptWithSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_getDescription00
static int tolua_CocoStudio_UISlider_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UISlider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UISlider* self = (const UISlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBarTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setBarTexture00
static int tolua_CocoStudio_UISlider_setBarTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBarTexture'", NULL);
#endif
  {
   self->setBarTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBarTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlidBallTextures of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setSlidBallTextures00
static int tolua_CocoStudio_UISlider_setSlidBallTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* pressed = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,4,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,5,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlidBallTextures'", NULL);
#endif
  {
   self->setSlidBallTextures(normal,pressed,disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlidBallTextures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlidBallNormalTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setSlidBallNormalTexture00
static int tolua_CocoStudio_UISlider_setSlidBallNormalTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* normal = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlidBallNormalTexture'", NULL);
#endif
  {
   self->setSlidBallNormalTexture(normal,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlidBallNormalTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlidBallPressedTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setSlidBallPressedTexture00
static int tolua_CocoStudio_UISlider_setSlidBallPressedTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* pressed = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlidBallPressedTexture'", NULL);
#endif
  {
   self->setSlidBallPressedTexture(pressed,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlidBallPressedTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlidBallDisabledTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setSlidBallDisabledTexture00
static int tolua_CocoStudio_UISlider_setSlidBallDisabledTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* disabled = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlidBallDisabledTexture'", NULL);
#endif
  {
   self->setSlidBallDisabledTexture(disabled,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlidBallDisabledTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setProgressBarTexture of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setProgressBarTexture00
static int tolua_CocoStudio_UISlider_setProgressBarTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProgressBarTexture'", NULL);
#endif
  {
   self->setProgressBarTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProgressBarTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlidBallPercent of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setSlidBallPercent00
static int tolua_CocoStudio_UISlider_setSlidBallPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  int percent = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlidBallPercent'", NULL);
#endif
  {
   self->setSlidBallPercent(percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlidBallPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Size of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setScale9Size00
static int tolua_CocoStudio_UISlider_setScale9Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Size'", NULL);
#endif
  {
   self->setScale9Size(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enable of class  UISlider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UISlider_setScale9Enable00
static int tolua_CocoStudio_UISlider_setScale9Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enable'", NULL);
#endif
  {
   self->setScale9Enable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_new00
static int tolua_CocoStudio_UITextField_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITextField* tolua_ret = (UITextField*)  Mtolua_new((UITextField)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UITextField");
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

/* method: new_local of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_new00_local
static int tolua_CocoStudio_UITextField_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITextField* tolua_ret = (UITextField*)  Mtolua_new((UITextField)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UITextField");
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

/* method: delete of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_delete00
static int tolua_CocoStudio_UITextField_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_create00
static int tolua_CocoStudio_UITextField_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITextField* tolua_ret = (UITextField*)  UITextField::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UITextField");
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

/* method: init of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_init00
static int tolua_CocoStudio_UITextField_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initRenderer of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_initRenderer00
static int tolua_CocoStudio_UITextField_initRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initRenderer'", NULL);
#endif
  {
   self->initRenderer();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchSize of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setTouchSize00
static int tolua_CocoStudio_UITextField_setTouchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchSize'", NULL);
#endif
  {
   self->setTouchSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setText00
static int tolua_CocoStudio_UITextField_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceHolder of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setPlaceHolder00
static int tolua_CocoStudio_UITextField_setPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceHolder'", NULL);
#endif
  {
   self->setPlaceHolder(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontSize of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setFontSize00
static int tolua_CocoStudio_UITextField_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontSize'", NULL);
#endif
  {
   self->setFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setFontName00
static int tolua_CocoStudio_UITextField_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: didNotSelectSelf of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_didNotSelectSelf00
static int tolua_CocoStudio_UITextField_didNotSelectSelf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'didNotSelectSelf'", NULL);
#endif
  {
   self->didNotSelectSelf();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'didNotSelectSelf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getStringValue00
static int tolua_CocoStudio_UITextField_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringValue'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStringValue();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchBegan of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_onTouchBegan00
static int tolua_CocoStudio_UITextField_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(*touchPoint);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxLengthEnabled of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setMaxLengthEnabled00
static int tolua_CocoStudio_UITextField_setMaxLengthEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxLengthEnabled'", NULL);
#endif
  {
   self->setMaxLengthEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxLengthEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isMaxLengthEnabled of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_isMaxLengthEnabled00
static int tolua_CocoStudio_UITextField_isMaxLengthEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isMaxLengthEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isMaxLengthEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isMaxLengthEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxLength of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setMaxLength00
static int tolua_CocoStudio_UITextField_setMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  int length = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxLength'", NULL);
#endif
  {
   self->setMaxLength(length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxLength of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getMaxLength00
static int tolua_CocoStudio_UITextField_getMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPasswordEnabled of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setPasswordEnabled00
static int tolua_CocoStudio_UITextField_setPasswordEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPasswordEnabled'", NULL);
#endif
  {
   self->setPasswordEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPasswordEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPasswordEnabled of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_isPasswordEnabled00
static int tolua_CocoStudio_UITextField_isPasswordEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPasswordEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPasswordEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPasswordEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPasswordStyleText of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setPasswordStyleText00
static int tolua_CocoStudio_UITextField_setPasswordStyleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const char* styleText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPasswordStyleText'", NULL);
#endif
  {
   self->setPasswordStyleText(styleText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPasswordStyleText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_update00
static int tolua_CocoStudio_UITextField_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttachWithIME of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getAttachWithIME00
static int tolua_CocoStudio_UITextField_getAttachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getAttachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttachWithIME of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setAttachWithIME00
static int tolua_CocoStudio_UITextField_setAttachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool attach = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttachWithIME'", NULL);
#endif
  {
   self->setAttachWithIME(attach);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDetachWithIME of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getDetachWithIME00
static int tolua_CocoStudio_UITextField_getDetachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDetachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getDetachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDetachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDetachWithIME of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setDetachWithIME00
static int tolua_CocoStudio_UITextField_setDetachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool detach = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDetachWithIME'", NULL);
#endif
  {
   self->setDetachWithIME(detach);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDetachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInsertText of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getInsertText00
static int tolua_CocoStudio_UITextField_getInsertText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInsertText'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getInsertText();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInsertText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsertText of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setInsertText00
static int tolua_CocoStudio_UITextField_setInsertText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool insertText = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsertText'", NULL);
#endif
  {
   self->setInsertText(insertText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsertText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeleteBackward of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getDeleteBackward00
static int tolua_CocoStudio_UITextField_getDeleteBackward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDeleteBackward'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getDeleteBackward();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeleteBackward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDeleteBackward of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setDeleteBackward00
static int tolua_CocoStudio_UITextField_setDeleteBackward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool deleteBackward = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDeleteBackward'", NULL);
#endif
  {
   self->setDeleteBackward(deleteBackward);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDeleteBackward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setAnchorPoint00
static int tolua_CocoStudio_UITextField_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setColor00
static int tolua_CocoStudio_UITextField_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setOpacity00
static int tolua_CocoStudio_UITextField_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  int opacity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getDescription00
static int tolua_CocoStudio_UITextField_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UITextField* self = (const UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxLengthEnable of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setMaxLengthEnable00
static int tolua_CocoStudio_UITextField_setMaxLengthEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxLengthEnable'", NULL);
#endif
  {
   self->setMaxLengthEnable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxLengthEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPasswordEnable of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_setPasswordEnable00
static int tolua_CocoStudio_UITextField_setPasswordEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPasswordEnable'", NULL);
#endif
  {
   self->setPasswordEnable(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPasswordEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getContentSize00
static int tolua_CocoStudio_UITextField_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UITextField* self = (const UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVirtualRenderer of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_getVirtualRenderer00
static int tolua_CocoStudio_UITextField_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVirtualRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachWithIME of class  UITextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UITextField_attachWithIME00
static int tolua_CocoStudio_UITextField_attachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachWithIME'", NULL);
#endif
  {
   self->attachWithIME();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_new00
static int tolua_CocoStudio_UIScrollView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIScrollView* tolua_ret = (UIScrollView*)  Mtolua_new((UIScrollView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIScrollView");
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

/* method: new_local of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_new00_local
static int tolua_CocoStudio_UIScrollView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIScrollView* tolua_ret = (UIScrollView*)  Mtolua_new((UIScrollView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIScrollView");
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

/* method: delete of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_delete00
static int tolua_CocoStudio_UIScrollView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_create00
static int tolua_CocoStudio_UIScrollView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIScrollView* tolua_ret = (UIScrollView*)  UIScrollView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIScrollView");
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

/* method: setDirection of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_setDirection00
static int tolua_CocoStudio_UIScrollView_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  SCROLLVIEW_DIR dir = ((SCROLLVIEW_DIR) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirection'", NULL);
#endif
  {
   self->setDirection(dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDirection of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_getDirection00
static int tolua_CocoStudio_UIScrollView_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDirection'", NULL);
#endif
  {
   SCROLLVIEW_DIR tolua_ret = (SCROLLVIEW_DIR)  self->getDirection();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInnerContainer of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_getInnerContainer00
static int tolua_CocoStudio_UIScrollView_getInnerContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInnerContainer'", NULL);
#endif
  {
   UILayout* tolua_ret = (UILayout*)  self->getInnerContainer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayout");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInnerContainer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToBottom of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToBottom00
static int tolua_CocoStudio_UIScrollView_scrollToBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToBottom'", NULL);
#endif
  {
   self->scrollToBottom(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToTop of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToTop00
static int tolua_CocoStudio_UIScrollView_scrollToTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToTop'", NULL);
#endif
  {
   self->scrollToTop(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToLeft of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToLeft00
static int tolua_CocoStudio_UIScrollView_scrollToLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToLeft'", NULL);
#endif
  {
   self->scrollToLeft(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToRight of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToRight00
static int tolua_CocoStudio_UIScrollView_scrollToRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToRight'", NULL);
#endif
  {
   self->scrollToRight(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToTopLeft of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToTopLeft00
static int tolua_CocoStudio_UIScrollView_scrollToTopLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToTopLeft'", NULL);
#endif
  {
   self->scrollToTopLeft(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToTopLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToTopRight of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToTopRight00
static int tolua_CocoStudio_UIScrollView_scrollToTopRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToTopRight'", NULL);
#endif
  {
   self->scrollToTopRight(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToTopRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToBottomLeft of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToBottomLeft00
static int tolua_CocoStudio_UIScrollView_scrollToBottomLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToBottomLeft'", NULL);
#endif
  {
   self->scrollToBottomLeft(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToBottomLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToBottomRight of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToBottomRight00
static int tolua_CocoStudio_UIScrollView_scrollToBottomRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToBottomRight'", NULL);
#endif
  {
   self->scrollToBottomRight(time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToBottomRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToPercentVertical of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToPercentVertical00
static int tolua_CocoStudio_UIScrollView_scrollToPercentVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float percent = ((float)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToPercentVertical'", NULL);
#endif
  {
   self->scrollToPercentVertical(percent,time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToPercentVertical'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToPercentHorizontal of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToPercentHorizontal00
static int tolua_CocoStudio_UIScrollView_scrollToPercentHorizontal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float percent = ((float)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToPercentHorizontal'", NULL);
#endif
  {
   self->scrollToPercentHorizontal(percent,time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToPercentHorizontal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToPercentBothDirection of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_scrollToPercentBothDirection00
static int tolua_CocoStudio_UIScrollView_scrollToPercentBothDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* percent = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  bool attenuated = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToPercentBothDirection'", NULL);
#endif
  {
   self->scrollToPercentBothDirection(*percent,time,attenuated);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToPercentBothDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToBottom of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToBottom00
static int tolua_CocoStudio_UIScrollView_jumpToBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToBottom'", NULL);
#endif
  {
   self->jumpToBottom();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToTop of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToTop00
static int tolua_CocoStudio_UIScrollView_jumpToTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToTop'", NULL);
#endif
  {
   self->jumpToTop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToLeft of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToLeft00
static int tolua_CocoStudio_UIScrollView_jumpToLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToLeft'", NULL);
#endif
  {
   self->jumpToLeft();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToRight of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToRight00
static int tolua_CocoStudio_UIScrollView_jumpToRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToRight'", NULL);
#endif
  {
   self->jumpToRight();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToTopLeft of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToTopLeft00
static int tolua_CocoStudio_UIScrollView_jumpToTopLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToTopLeft'", NULL);
#endif
  {
   self->jumpToTopLeft();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToTopLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToTopRight of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToTopRight00
static int tolua_CocoStudio_UIScrollView_jumpToTopRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToTopRight'", NULL);
#endif
  {
   self->jumpToTopRight();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToTopRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToBottomLeft of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToBottomLeft00
static int tolua_CocoStudio_UIScrollView_jumpToBottomLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToBottomLeft'", NULL);
#endif
  {
   self->jumpToBottomLeft();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToBottomLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToBottomRight of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToBottomRight00
static int tolua_CocoStudio_UIScrollView_jumpToBottomRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToBottomRight'", NULL);
#endif
  {
   self->jumpToBottomRight();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToBottomRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToPercentVertical of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToPercentVertical00
static int tolua_CocoStudio_UIScrollView_jumpToPercentVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float percent = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToPercentVertical'", NULL);
#endif
  {
   self->jumpToPercentVertical(percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToPercentVertical'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToPercentHorizontal of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToPercentHorizontal00
static int tolua_CocoStudio_UIScrollView_jumpToPercentHorizontal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float percent = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToPercentHorizontal'", NULL);
#endif
  {
   self->jumpToPercentHorizontal(percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToPercentHorizontal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: jumpToPercentBothDirection of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_jumpToPercentBothDirection00
static int tolua_CocoStudio_UIScrollView_jumpToPercentBothDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* percent = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'jumpToPercentBothDirection'", NULL);
#endif
  {
   self->jumpToPercentBothDirection(*percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpToPercentBothDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInnerContainerSize of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_setInnerContainerSize00
static int tolua_CocoStudio_UIScrollView_setInnerContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInnerContainerSize'", NULL);
#endif
  {
   self->setInnerContainerSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInnerContainerSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInnerContainerSize of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_getInnerContainerSize00
static int tolua_CocoStudio_UIScrollView_getInnerContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIScrollView* self = (const UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInnerContainerSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getInnerContainerSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInnerContainerSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_addChild00
static int tolua_CocoStudio_UIScrollView_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addChild(widget);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildren of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_removeAllChildren00
static int tolua_CocoStudio_UIScrollView_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildren'", NULL);
#endif
  {
   self->removeAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_removeChild00
static int tolua_CocoStudio_UIScrollView_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeChild(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildren of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_getChildren00
static int tolua_CocoStudio_UIScrollView_getChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildren'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getChildren();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_update00
static int tolua_CocoStudio_UIScrollView_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBounceEnabled of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_setBounceEnabled00
static int tolua_CocoStudio_UIScrollView_setBounceEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBounceEnabled'", NULL);
#endif
  {
   self->setBounceEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBounceEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBounceEnabled of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_isBounceEnabled00
static int tolua_CocoStudio_UIScrollView_isBounceEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIScrollView* self = (const UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBounceEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBounceEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBounceEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInertiaScrollEnabled of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_setInertiaScrollEnabled00
static int tolua_CocoStudio_UIScrollView_setInertiaScrollEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInertiaScrollEnabled'", NULL);
#endif
  {
   self->setInertiaScrollEnabled(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInertiaScrollEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInertiaScrollEnabled of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_isInertiaScrollEnabled00
static int tolua_CocoStudio_UIScrollView_isInertiaScrollEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIScrollView* self = (const UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInertiaScrollEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInertiaScrollEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInertiaScrollEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayoutType of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_setLayoutType00
static int tolua_CocoStudio_UIScrollView_setLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
  LayoutType type = ((LayoutType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayoutType'", NULL);
#endif
  {
   self->setLayoutType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayoutType of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_getLayoutType00
static int tolua_CocoStudio_UIScrollView_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIScrollView* self = (const UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutType'", NULL);
#endif
  {
   LayoutType tolua_ret = (LayoutType)  self->getLayoutType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doLayout of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_doLayout00
static int tolua_CocoStudio_UIScrollView_doLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doLayout'", NULL);
#endif
  {
   self->doLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIScrollView_getDescription00
static int tolua_CocoStudio_UIScrollView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIScrollView* self = (const UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __UIScrollInterface__ of class  UIScrollView */
#ifndef TOLUA_DISABLE_tolua_get_UIScrollView___UIScrollInterface__
static int tolua_get_UIScrollView___UIScrollInterface__(lua_State* tolua_S)
{
  UIScrollView* self = (UIScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__UIScrollInterface__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<UIScrollInterface*>(self), "UIScrollInterface");
#else
   tolua_pushusertype(tolua_S,(void*)((UIScrollInterface*)self), "UIScrollInterface");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_new00
static int tolua_CocoStudio_UIPageView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIPageView* tolua_ret = (UIPageView*)  Mtolua_new((UIPageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIPageView");
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

/* method: new_local of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_new00_local
static int tolua_CocoStudio_UIPageView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIPageView* tolua_ret = (UIPageView*)  Mtolua_new((UIPageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIPageView");
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

/* method: delete of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_delete00
static int tolua_CocoStudio_UIPageView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_create00
static int tolua_CocoStudio_UIPageView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIPageView* tolua_ret = (UIPageView*)  UIPageView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIPageView");
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

/* method: addWidgetToPage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_addWidgetToPage00
static int tolua_CocoStudio_UIPageView_addWidgetToPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  int pageIdx = ((int)  tolua_tonumber(tolua_S,3,0));
  bool forceCreate = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addWidgetToPage'", NULL);
#endif
  {
   self->addWidgetToPage(widget,pageIdx,forceCreate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addWidgetToPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_addPage00
static int tolua_CocoStudio_UIPageView_addPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  UILayout* page = ((UILayout*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPage'", NULL);
#endif
  {
   self->addPage(page);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insertPage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_insertPage00
static int tolua_CocoStudio_UIPageView_insertPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  UILayout* page = ((UILayout*)  tolua_tousertype(tolua_S,2,0));
  int idx = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertPage'", NULL);
#endif
  {
   self->insertPage(page,idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removePage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_removePage00
static int tolua_CocoStudio_UIPageView_removePage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  UILayout* page = ((UILayout*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removePage'", NULL);
#endif
  {
   self->removePage(page);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removePage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removePageAtIndex of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_removePageAtIndex00
static int tolua_CocoStudio_UIPageView_removePageAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removePageAtIndex'", NULL);
#endif
  {
   self->removePageAtIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removePageAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllPages of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_removeAllPages00
static int tolua_CocoStudio_UIPageView_removeAllPages00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllPages'", NULL);
#endif
  {
   self->removeAllPages();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllPages'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollToPage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_scrollToPage00
static int tolua_CocoStudio_UIPageView_scrollToPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollToPage'", NULL);
#endif
  {
   self->scrollToPage(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollToPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurPageIndex of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_getCurPageIndex00
static int tolua_CocoStudio_UIPageView_getCurPageIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIPageView* self = (const UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurPageIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurPageIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurPageIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPages of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_getPages00
static int tolua_CocoStudio_UIPageView_getPages00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPages'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getPages();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPages'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_getPage00
static int tolua_CocoStudio_UIPageView_getPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPage'", NULL);
#endif
  {
   UILayout* tolua_ret = (UILayout*)  self->getPage(index);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayout");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_update00
static int tolua_CocoStudio_UIPageView_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doLayout of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_doLayout00
static int tolua_CocoStudio_UIPageView_doLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doLayout'", NULL);
#endif
  {
   self->doLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayoutType of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_setLayoutType00
static int tolua_CocoStudio_UIPageView_setLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  LayoutType type = ((LayoutType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayoutType'", NULL);
#endif
  {
   self->setLayoutType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayoutType of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_getLayoutType00
static int tolua_CocoStudio_UIPageView_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutType'", NULL);
#endif
  {
   LayoutType tolua_ret = (LayoutType)  self->getLayoutType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_getDescription00
static int tolua_CocoStudio_UIPageView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIPageView* self = (const UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_getPage01
static int tolua_CocoStudio_UIPageView_getPage01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIPageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const UIPageView* self = (const UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPage'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_UIPageView_getPage00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removePage of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_removePage01
static int tolua_CocoStudio_UIPageView_removePage01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  UILayout* page = ((UILayout*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removePage'", NULL);
#endif
  {
   self->removePage(page,cleanup);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_UIPageView_removePage00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removePageAtIndex of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIPageView_removePageAtIndex01
static int tolua_CocoStudio_UIPageView_removePageAtIndex01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removePageAtIndex'", NULL);
#endif
  {
   self->removePageAtIndex(index,cleanup);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_UIPageView_removePageAtIndex00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __UIScrollInterface__ of class  UIPageView */
#ifndef TOLUA_DISABLE_tolua_get_UIPageView___UIScrollInterface__
static int tolua_get_UIPageView___UIScrollInterface__(lua_State* tolua_S)
{
  UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__UIScrollInterface__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<UIScrollInterface*>(self), "UIScrollInterface");
#else
   tolua_pushusertype(tolua_S,(void*)((UIScrollInterface*)self), "UIScrollInterface");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_new00
static int tolua_CocoStudio_UIListView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIListView* tolua_ret = (UIListView*)  Mtolua_new((UIListView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIListView");
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

/* method: new_local of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_new00_local
static int tolua_CocoStudio_UIListView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIListView* tolua_ret = (UIListView*)  Mtolua_new((UIListView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIListView");
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

/* method: delete of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_delete00
static int tolua_CocoStudio_UIListView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_create00
static int tolua_CocoStudio_UIListView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIListView* tolua_ret = (UIListView*)  UIListView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIListView");
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

/* method: addChild of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_addChild00
static int tolua_CocoStudio_UIListView_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addChild(widget);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildren of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_removeAllChildren00
static int tolua_CocoStudio_UIListView_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildren'", NULL);
#endif
  {
   self->removeAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_removeChild00
static int tolua_CocoStudio_UIListView_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeChild(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDirection of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_setDirection00
static int tolua_CocoStudio_UIListView_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
  ListViewDirection dir = ((ListViewDirection) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDirection'", NULL);
#endif
  {
   self->setDirection(dir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDirection of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_getDirection00
static int tolua_CocoStudio_UIListView_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDirection'", NULL);
#endif
  {
   ListViewDirection tolua_ret = (ListViewDirection)  self->getDirection();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initChildWithDataLength of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_initChildWithDataLength00
static int tolua_CocoStudio_UIListView_initChildWithDataLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
  int length = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initChildWithDataLength'", NULL);
#endif
  {
   self->initChildWithDataLength(length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initChildWithDataLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDataLength of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_getDataLength00
static int tolua_CocoStudio_UIListView_getDataLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDataLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDataLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDataLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateChild of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_getUpdateChild00
static int tolua_CocoStudio_UIListView_getUpdateChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateChild'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getUpdateChild();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateDataIndex of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_getUpdateDataIndex00
static int tolua_CocoStudio_UIListView_getUpdateDataIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateDataIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getUpdateDataIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateDataIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateSuccess of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_getUpdateSuccess00
static int tolua_CocoStudio_UIListView_getUpdateSuccess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateSuccess'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getUpdateSuccess();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateSuccess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateSuccess of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_setUpdateSuccess00
static int tolua_CocoStudio_UIListView_setUpdateSuccess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
  bool sucess = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUpdateSuccess'", NULL);
#endif
  {
   self->setUpdateSuccess(sucess);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateSuccess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_update00
static int tolua_CocoStudio_UIListView_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doLayout of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_doLayout00
static int tolua_CocoStudio_UIListView_doLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doLayout'", NULL);
#endif
  {
   self->doLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDescription of class  UIListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIListView_getDescription00
static int tolua_CocoStudio_UIListView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIListView* self = (const UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayoutParameter_new00
static int tolua_CocoStudio_UILayoutParameter_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayoutParameter* tolua_ret = (UILayoutParameter*)  Mtolua_new((UILayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayoutParameter");
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

/* method: new_local of class  UILayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayoutParameter_new00_local
static int tolua_CocoStudio_UILayoutParameter_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayoutParameter* tolua_ret = (UILayoutParameter*)  Mtolua_new((UILayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayoutParameter");
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

/* method: delete of class  UILayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayoutParameter_delete00
static int tolua_CocoStudio_UILayoutParameter_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayoutParameter* self = (UILayoutParameter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayoutParameter_create00
static int tolua_CocoStudio_UILayoutParameter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayoutParameter* tolua_ret = (UILayoutParameter*)  UILayoutParameter::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILayoutParameter");
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

/* method: getLayoutType of class  UILayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILayoutParameter_getLayoutType00
static int tolua_CocoStudio_UILayoutParameter_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILayoutParameter* self = (const UILayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutType'", NULL);
#endif
  {
   LayoutParameterType tolua_ret = (LayoutParameterType)  self->getLayoutType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayoutType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UILinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILinearLayoutParameter_new00
static int tolua_CocoStudio_UILinearLayoutParameter_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILinearLayoutParameter* tolua_ret = (UILinearLayoutParameter*)  Mtolua_new((UILinearLayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILinearLayoutParameter");
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

/* method: new_local of class  UILinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILinearLayoutParameter_new00_local
static int tolua_CocoStudio_UILinearLayoutParameter_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILinearLayoutParameter* tolua_ret = (UILinearLayoutParameter*)  Mtolua_new((UILinearLayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILinearLayoutParameter");
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

/* method: delete of class  UILinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILinearLayoutParameter_delete00
static int tolua_CocoStudio_UILinearLayoutParameter_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILinearLayoutParameter* self = (UILinearLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UILinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILinearLayoutParameter_create00
static int tolua_CocoStudio_UILinearLayoutParameter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILinearLayoutParameter* tolua_ret = (UILinearLayoutParameter*)  UILinearLayoutParameter::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UILinearLayoutParameter");
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

/* method: setGravity of class  UILinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILinearLayoutParameter_setGravity00
static int tolua_CocoStudio_UILinearLayoutParameter_setGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILinearLayoutParameter* self = (UILinearLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
  UILinearGravity gravity = ((UILinearGravity) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGravity'", NULL);
#endif
  {
   self->setGravity(gravity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGravity of class  UILinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UILinearLayoutParameter_getGravity00
static int tolua_CocoStudio_UILinearLayoutParameter_getGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UILinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UILinearLayoutParameter* self = (const UILinearLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGravity'", NULL);
#endif
  {
   UILinearGravity tolua_ret = (UILinearGravity)  self->getGravity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((UILinearGravity)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"UILinearGravity");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(UILinearGravity));
     tolua_pushusertype(tolua_S,tolua_obj,"UILinearGravity");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_new00
static int tolua_CocoStudio_UIRelativeLayoutParameter_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRelativeLayoutParameter* tolua_ret = (UIRelativeLayoutParameter*)  Mtolua_new((UIRelativeLayoutParameter)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRelativeLayoutParameter");
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

/* method: new_local of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_new00_local
static int tolua_CocoStudio_UIRelativeLayoutParameter_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRelativeLayoutParameter* tolua_ret = (UIRelativeLayoutParameter*)  Mtolua_new((UIRelativeLayoutParameter)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRelativeLayoutParameter");
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

/* method: delete of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_delete00
static int tolua_CocoStudio_UIRelativeLayoutParameter_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIRelativeLayoutParameter* self = (UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_create00
static int tolua_CocoStudio_UIRelativeLayoutParameter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRelativeLayoutParameter* tolua_ret = (UIRelativeLayoutParameter*)  UIRelativeLayoutParameter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRelativeLayoutParameter");
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

/* method: setAlign of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_setAlign00
static int tolua_CocoStudio_UIRelativeLayoutParameter_setAlign00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UIRelativeAlign",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIRelativeLayoutParameter* self = (UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
  UIRelativeAlign align = *((UIRelativeAlign*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAlign'", NULL);
#endif
  {
   self->setAlign(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAlign'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAlign of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_getAlign00
static int tolua_CocoStudio_UIRelativeLayoutParameter_getAlign00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIRelativeLayoutParameter* self = (const UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAlign'", NULL);
#endif
  {
   UIRelativeAlign tolua_ret = (UIRelativeAlign)  self->getAlign();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((UIRelativeAlign)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"UIRelativeAlign");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(UIRelativeAlign));
     tolua_pushusertype(tolua_S,tolua_obj,"UIRelativeAlign");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAlign'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRelativeToWidgetName of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_setRelativeToWidgetName00
static int tolua_CocoStudio_UIRelativeLayoutParameter_setRelativeToWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIRelativeLayoutParameter* self = (UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRelativeToWidgetName'", NULL);
#endif
  {
   self->setRelativeToWidgetName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRelativeToWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeToWidgetName of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_getRelativeToWidgetName00
static int tolua_CocoStudio_UIRelativeLayoutParameter_getRelativeToWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIRelativeLayoutParameter* self = (const UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeToWidgetName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getRelativeToWidgetName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeToWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRelativeName of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_setRelativeName00
static int tolua_CocoStudio_UIRelativeLayoutParameter_setRelativeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIRelativeLayoutParameter* self = (UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRelativeName'", NULL);
#endif
  {
   self->setRelativeName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRelativeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeName of class  UIRelativeLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRelativeLayoutParameter_getRelativeName00
static int tolua_CocoStudio_UIRelativeLayoutParameter_getRelativeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIRelativeLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIRelativeLayoutParameter* self = (const UIRelativeLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getRelativeName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_new00
static int tolua_CocoStudio_CCComController_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCComController* tolua_ret = (CCComController*)  Mtolua_new((CCComController)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCComController");
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

/* method: new_local of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_new00_local
static int tolua_CocoStudio_CCComController_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCComController* tolua_ret = (CCComController*)  Mtolua_new((CCComController)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCComController");
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

/* method: delete of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_delete00
static int tolua_CocoStudio_CCComController_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComController* self = (CCComController*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_init00
static int tolua_CocoStudio_CCComController_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComController* self = (CCComController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_update00
static int tolua_CocoStudio_CCComController_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComController* self = (CCComController*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_isEnabled00
static int tolua_CocoStudio_CCComController_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCComController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCComController* self = (const CCComController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_setEnabled00
static int tolua_CocoStudio_CCComController_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComController* self = (CCComController*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComController_create00
static int tolua_CocoStudio_CCComController_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCComController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCComController* tolua_ret = (CCComController*)  CCComController::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCComController");
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

/* get function: __CCInputDelegate__ of class  CCComController */
#ifndef TOLUA_DISABLE_tolua_get_CCComController___CCInputDelegate__
static int tolua_get_CCComController___CCInputDelegate__(lua_State* tolua_S)
{
  CCComController* self = (CCComController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCInputDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCInputDelegate*>(self), "CCInputDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCInputDelegate*)self), "CCInputDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_init00
static int tolua_CocoStudio_CCComAudio_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_isEnabled00
static int tolua_CocoStudio_CCComAudio_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCComAudio* self = (const CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_setEnabled00
static int tolua_CocoStudio_CCComAudio_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_create00
static int tolua_CocoStudio_CCComAudio_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCComAudio* tolua_ret = (CCComAudio*)  CCComAudio::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCComAudio");
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

/* method: end of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_end00
static int tolua_CocoStudio_CCComAudio_end00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   self->end();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'end'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_preloadBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_preloadBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadBackgroundMusic'", NULL);
#endif
  {
   self->preloadBackgroundMusic(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_playBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_playBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playBackgroundMusic'", NULL);
#endif
  {
   self->playBackgroundMusic(pszFilePath,bLoop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_playBackgroundMusic01
static int tolua_CocoStudio_CCComAudio_playBackgroundMusic01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playBackgroundMusic'", NULL);
#endif
  {
   self->playBackgroundMusic(pszFilePath);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCComAudio_playBackgroundMusic00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_stopBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_stopBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  bool bReleaseData = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopBackgroundMusic'", NULL);
#endif
  {
   self->stopBackgroundMusic(bReleaseData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_stopBackgroundMusic01
static int tolua_CocoStudio_CCComAudio_stopBackgroundMusic01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopBackgroundMusic'", NULL);
#endif
  {
   self->stopBackgroundMusic();
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCComAudio_stopBackgroundMusic00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_pauseBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_pauseBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseBackgroundMusic'", NULL);
#endif
  {
   self->pauseBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_resumeBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_resumeBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeBackgroundMusic'", NULL);
#endif
  {
   self->resumeBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rewindBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_rewindBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_rewindBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rewindBackgroundMusic'", NULL);
#endif
  {
   self->rewindBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rewindBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: willPlayBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_willPlayBackgroundMusic00
static int tolua_CocoStudio_CCComAudio_willPlayBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'willPlayBackgroundMusic'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->willPlayBackgroundMusic();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'willPlayBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBackgroundMusicPlaying of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_isBackgroundMusicPlaying00
static int tolua_CocoStudio_CCComAudio_isBackgroundMusicPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBackgroundMusicPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBackgroundMusicPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBackgroundMusicPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundMusicVolume of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_getBackgroundMusicVolume00
static int tolua_CocoStudio_CCComAudio_getBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundMusicVolume'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getBackgroundMusicVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundMusicVolume of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_setBackgroundMusicVolume00
static int tolua_CocoStudio_CCComAudio_setBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundMusicVolume'", NULL);
#endif
  {
   self->setBackgroundMusicVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEffectsVolume of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_getEffectsVolume00
static int tolua_CocoStudio_CCComAudio_getEffectsVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEffectsVolume'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getEffectsVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEffectsVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEffectsVolume of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_setEffectsVolume00
static int tolua_CocoStudio_CCComAudio_setEffectsVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEffectsVolume'", NULL);
#endif
  {
   self->setEffectsVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEffectsVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_playEffect00
static int tolua_CocoStudio_CCComAudio_playEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->playEffect(pszFilePath,bLoop);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_playEffect01
static int tolua_CocoStudio_CCComAudio_playEffect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->playEffect(pszFilePath);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCComAudio_playEffect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_pauseEffect00
static int tolua_CocoStudio_CCComAudio_pauseEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseEffect'", NULL);
#endif
  {
   self->pauseEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseAllEffects of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_pauseAllEffects00
static int tolua_CocoStudio_CCComAudio_pauseAllEffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pauseAllEffects'", NULL);
#endif
  {
   self->pauseAllEffects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseAllEffects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_resumeEffect00
static int tolua_CocoStudio_CCComAudio_resumeEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeEffect'", NULL);
#endif
  {
   self->resumeEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeAllEffects of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_resumeAllEffects00
static int tolua_CocoStudio_CCComAudio_resumeAllEffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resumeAllEffects'", NULL);
#endif
  {
   self->resumeAllEffects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeAllEffects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_stopEffect00
static int tolua_CocoStudio_CCComAudio_stopEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nSoundId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopEffect'", NULL);
#endif
  {
   self->stopEffect(nSoundId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAllEffects of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_stopAllEffects00
static int tolua_CocoStudio_CCComAudio_stopAllEffects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAllEffects'", NULL);
#endif
  {
   self->stopAllEffects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAllEffects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: preloadEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_preloadEffect00
static int tolua_CocoStudio_CCComAudio_preloadEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'preloadEffect'", NULL);
#endif
  {
   self->preloadEffect(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'preloadEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_unloadEffect00
static int tolua_CocoStudio_CCComAudio_unloadEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadEffect'", NULL);
#endif
  {
   self->unloadEffect(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFile of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_setFile00
static int tolua_CocoStudio_CCComAudio_setFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFile'", NULL);
#endif
  {
   self->setFile(pszFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFile of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_getFile00
static int tolua_CocoStudio_CCComAudio_getFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFile'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getFile();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoop of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_setLoop00
static int tolua_CocoStudio_CCComAudio_setLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoop'", NULL);
#endif
  {
   self->setLoop(bLoop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLoop of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_isLoop00
static int tolua_CocoStudio_CCComAudio_isLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAudio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAudio* self = (CCComAudio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLoop'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLoop();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_init00
static int tolua_CocoStudio_CCComAttribute_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAttribute* self = (CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_create00
static int tolua_CocoStudio_CCComAttribute_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCComAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCComAttribute* tolua_ret = (CCComAttribute*)  CCComAttribute::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCComAttribute");
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

/* method: setInt of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_setInt00
static int tolua_CocoStudio_CCComAttribute_setInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAttribute* self = (CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInt'", NULL);
#endif
  {
   self->setInt(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFloat of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_setFloat00
static int tolua_CocoStudio_CCComAttribute_setFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAttribute* self = (CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFloat'", NULL);
#endif
  {
   self->setFloat(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBool of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_setBool00
static int tolua_CocoStudio_CCComAttribute_setBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAttribute* self = (CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBool'", NULL);
#endif
  {
   self->setBool(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCString of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_setCString00
static int tolua_CocoStudio_CCComAttribute_setCString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComAttribute* self = (CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCString'", NULL);
#endif
  {
   self->setCString(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInt of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_getInt00
static int tolua_CocoStudio_CCComAttribute_getInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCComAttribute* self = (const CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getInt(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFloat of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_getFloat00
static int tolua_CocoStudio_CCComAttribute_getFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCComAttribute* self = (const CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFloat(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBool of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_getBool00
static int tolua_CocoStudio_CCComAttribute_getBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCComAttribute* self = (const CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBool'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBool(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCString of class  CCComAttribute */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAttribute_getCString00
static int tolua_CocoStudio_CCComAttribute_getCString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCComAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCComAttribute* self = (const CCComAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCString'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getCString(key);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  CCComRender */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComRender_getNode00
static int tolua_CocoStudio_CCComRender_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComRender",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComRender* self = (CCComRender*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNode of class  CCComRender */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComRender_setNode00
static int tolua_CocoStudio_CCComRender_setNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCComRender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCComRender* self = (CCComRender*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNode'", NULL);
#endif
  {
   self->setNode(pNode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCComRender */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComRender_create00
static int tolua_CocoStudio_CCComRender_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCComRender",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* pNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const char* comName = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CCComRender* tolua_ret = (CCComRender*)  CCComRender::create(pNode,comName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCComRender");
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

/* method: new of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_new00
static int tolua_CocoStudio_ActionManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ActionManager* tolua_ret = (ActionManager*)  Mtolua_new((ActionManager)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionManager");
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

/* method: new_local of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_new00_local
static int tolua_CocoStudio_ActionManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ActionManager* tolua_ret = (ActionManager*)  Mtolua_new((ActionManager)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionManager");
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

/* method: delete of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_delete00
static int tolua_CocoStudio_ActionManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionManager* self = (ActionManager*)  tolua_tousertype(tolua_S,1,0);
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

/* method: shareManager of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_shareManager00
static int tolua_CocoStudio_ActionManager_shareManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ActionManager* tolua_ret = (ActionManager*)  ActionManager::shareManager();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shareManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeActionManager of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_purgeActionManager00
static int tolua_CocoStudio_ActionManager_purgeActionManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ActionManager::purgeActionManager();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeActionManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionByName of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_getActionByName00
static int tolua_CocoStudio_ActionManager_getActionByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionManager* self = (ActionManager*)  tolua_tousertype(tolua_S,1,0);
  const char* jsonName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* actionName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionByName'", NULL);
#endif
  {
   ActionObject* tolua_ret = (ActionObject*)  self->getActionByName(jsonName,actionName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playActionByName of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_playActionByName00
static int tolua_CocoStudio_ActionManager_playActionByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionManager* self = (ActionManager*)  tolua_tousertype(tolua_S,1,0);
  const char* jsonName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* actionName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playActionByName'", NULL);
#endif
  {
   ActionObject* tolua_ret = (ActionObject*)  self->playActionByName(jsonName,actionName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playActionByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: releaseActions of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_releaseActions00
static int tolua_CocoStudio_ActionManager_releaseActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionManager* self = (ActionManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'releaseActions'", NULL);
#endif
  {
   self->releaseActions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'releaseActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_new00
static int tolua_CocoStudio_SceneReader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SceneReader* tolua_ret = (SceneReader*)  Mtolua_new((SceneReader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneReader");
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

/* method: new_local of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_new00_local
static int tolua_CocoStudio_SceneReader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SceneReader* tolua_ret = (SceneReader*)  Mtolua_new((SceneReader)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneReader");
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

/* method: delete of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_delete00
static int tolua_CocoStudio_SceneReader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneReader* self = (SceneReader*)  tolua_tousertype(tolua_S,1,0);
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

/* method: sharedSceneReader of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_sharedSceneReader00
static int tolua_CocoStudio_SceneReader_sharedSceneReader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SceneReader* tolua_ret = (SceneReader*)  SceneReader::sharedSceneReader();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneReader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedSceneReader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeSceneReader of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_purgeSceneReader00
static int tolua_CocoStudio_SceneReader_purgeSceneReader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneReader* self = (SceneReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purgeSceneReader'", NULL);
#endif
  {
   self->purgeSceneReader();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeSceneReader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sceneReaderVersion of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_sceneReaderVersion00
static int tolua_CocoStudio_SceneReader_sceneReaderVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const char* tolua_ret = (const char*)  SceneReader::sceneReaderVersion();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sceneReaderVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createNodeWithSceneFile of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_createNodeWithSceneFile00
static int tolua_CocoStudio_SceneReader_createNodeWithSceneFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneReader* self = (SceneReader*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createNodeWithSceneFile'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->createNodeWithSceneFile(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createNodeWithSceneFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_new00
static int tolua_CocoStudio_GUIReader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUIReader* tolua_ret = (GUIReader*)  Mtolua_new((GUIReader)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GUIReader");
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

/* method: new_local of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_new00_local
static int tolua_CocoStudio_GUIReader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUIReader* tolua_ret = (GUIReader*)  Mtolua_new((GUIReader)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GUIReader");
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

/* method: delete of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_delete00
static int tolua_CocoStudio_GUIReader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUIReader* self = (GUIReader*)  tolua_tousertype(tolua_S,1,0);
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

/* method: shareReader of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_shareReader00
static int tolua_CocoStudio_GUIReader_shareReader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUIReader* tolua_ret = (GUIReader*)  GUIReader::shareReader();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"GUIReader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shareReader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeGUIReader of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_purgeGUIReader00
static int tolua_CocoStudio_GUIReader_purgeGUIReader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GUIReader::purgeGUIReader();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeGUIReader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: widgetFromJsonFile of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_widgetFromJsonFile00
static int tolua_CocoStudio_GUIReader_widgetFromJsonFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUIReader* self = (GUIReader*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'widgetFromJsonFile'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->widgetFromJsonFile(fileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'widgetFromJsonFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRootWidget_new00
static int tolua_CocoStudio_UIRootWidget_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  Mtolua_new((UIRootWidget)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIRootWidget");
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

/* method: new_local of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRootWidget_new00_local
static int tolua_CocoStudio_UIRootWidget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  Mtolua_new((UIRootWidget)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIRootWidget");
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

/* method: delete of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRootWidget_delete00
static int tolua_CocoStudio_UIRootWidget_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIRootWidget* self = (UIRootWidget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRootWidget_create00
static int tolua_CocoStudio_UIRootWidget_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  UIRootWidget::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"UIRootWidget");
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

/* method: getDescription of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_UIRootWidget_getDescription00
static int tolua_CocoStudio_UIRootWidget_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIRootWidget* self = (const UIRootWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDescription();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_new00
static int tolua_CocoStudio_ActionObject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ActionObject* tolua_ret = (ActionObject*)  Mtolua_new((ActionObject)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionObject");
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

/* method: new_local of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_new00_local
static int tolua_CocoStudio_ActionObject_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ActionObject* tolua_ret = (ActionObject*)  Mtolua_new((ActionObject)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionObject");
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

/* method: delete of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_delete00
static int tolua_CocoStudio_ActionObject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setName of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_setName00
static int tolua_CocoStudio_ActionObject_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_getName00
static int tolua_CocoStudio_ActionObject_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoop of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_setLoop00
static int tolua_CocoStudio_ActionObject_setLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoop'", NULL);
#endif
  {
   self->setLoop(bLoop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLoop of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_getLoop00
static int tolua_CocoStudio_ActionObject_getLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLoop'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getLoop();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUnitTime of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_setUnitTime00
static int tolua_CocoStudio_ActionObject_setUnitTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  float fTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUnitTime'", NULL);
#endif
  {
   self->setUnitTime(fTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUnitTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUnitTime of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_getUnitTime00
static int tolua_CocoStudio_ActionObject_getUnitTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUnitTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getUnitTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnitTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurrentTime of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_setCurrentTime00
static int tolua_CocoStudio_ActionObject_setCurrentTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  float fTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurrentTime'", NULL);
#endif
  {
   self->setCurrentTime(fTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurrentTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentTime of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_getCurrentTime00
static int tolua_CocoStudio_ActionObject_getCurrentTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getCurrentTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPlaying of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_isPlaying00
static int tolua_CocoStudio_ActionObject_isPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_play00
static int tolua_CocoStudio_ActionObject_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_pause00
static int tolua_CocoStudio_ActionObject_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_stop00
static int tolua_CocoStudio_ActionObject_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addActionNode of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_addActionNode00
static int tolua_CocoStudio_ActionObject_addActionNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ActionNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  ActionNode* node = ((ActionNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addActionNode'", NULL);
#endif
  {
   self->addActionNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addActionNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeActionNode of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_removeActionNode00
static int tolua_CocoStudio_ActionObject_removeActionNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ActionNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  ActionNode* node = ((ActionNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeActionNode'", NULL);
#endif
  {
   self->removeActionNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeActionNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateToFrameByTime of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_updateToFrameByTime00
static int tolua_CocoStudio_ActionObject_updateToFrameByTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  float fTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateToFrameByTime'", NULL);
#endif
  {
   self->updateToFrameByTime(fTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateToFrameByTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithDictionary of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_initWithDictionary00
static int tolua_CocoStudio_ActionObject_initWithDictionary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const rapidjson::Value",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  const rapidjson::Value* dic = ((const rapidjson::Value*)  tolua_tousertype(tolua_S,2,0));
  CCObject* root = ((CCObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithDictionary'", NULL);
#endif
  {
   self->initWithDictionary(*dic,root);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithDictionary'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: simulationActionUpdate of class  ActionObject */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionObject_simulationActionUpdate00
static int tolua_CocoStudio_ActionObject_simulationActionUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ActionObject* self = (ActionObject*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'simulationActionUpdate'", NULL);
#endif
  {
   self->simulationActionUpdate(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'simulationActionUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CocoStudio_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCArmature","CCArmature","CCNodeRGBA",tolua_collect_CCArmature);
  #else
  tolua_cclass(tolua_S,"CCArmature","CCArmature","CCNodeRGBA",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCArmature");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCArmature_create00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCArmature_create01);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCArmature_create02);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCArmature_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCArmature_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCArmature_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCArmature_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCArmature_init00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCArmature_init01);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCArmature_init02);
   tolua_function(tolua_S,"addBone",tolua_CocoStudio_CCArmature_addBone00);
   tolua_function(tolua_S,"getBone",tolua_CocoStudio_CCArmature_getBone00);
   tolua_function(tolua_S,"changeBoneParent",tolua_CocoStudio_CCArmature_changeBoneParent00);
   tolua_function(tolua_S,"removeBone",tolua_CocoStudio_CCArmature_removeBone00);
   tolua_function(tolua_S,"getBoneDic",tolua_CocoStudio_CCArmature_getBoneDic00);
   tolua_function(tolua_S,"boundingBox",tolua_CocoStudio_CCArmature_boundingBox00);
   tolua_function(tolua_S,"getBoneAtPoint",tolua_CocoStudio_CCArmature_getBoneAtPoint00);
   tolua_function(tolua_S,"visit",tolua_CocoStudio_CCArmature_visit00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_CCArmature_update00);
   tolua_function(tolua_S,"draw",tolua_CocoStudio_CCArmature_draw00);
   tolua_function(tolua_S,"nodeToParentTransform",tolua_CocoStudio_CCArmature_nodeToParentTransform00);
   tolua_function(tolua_S,"updateOffsetPoint",tolua_CocoStudio_CCArmature_updateOffsetPoint00);
   tolua_function(tolua_S,"setBlendFunc",tolua_CocoStudio_CCArmature_setBlendFunc00);
   tolua_function(tolua_S,"getBlendFunc",tolua_CocoStudio_CCArmature_getBlendFunc00);
   tolua_function(tolua_S,"setAnimation",tolua_CocoStudio_CCArmature_setAnimation00);
   tolua_function(tolua_S,"getAnimation",tolua_CocoStudio_CCArmature_getAnimation00);
   tolua_function(tolua_S,"getTexureAtlasWithTexture",tolua_CocoStudio_CCArmature_getTexureAtlasWithTexture00);
   tolua_function(tolua_S,"setColliderFilter",tolua_CocoStudio_CCArmature_setColliderFilter00);
   tolua_function(tolua_S,"getArmatureData",tolua_CocoStudio_CCArmature_getArmatureData00);
   tolua_function(tolua_S,"setArmatureData",tolua_CocoStudio_CCArmature_setArmatureData00);
   tolua_function(tolua_S,"getBatchNode",tolua_CocoStudio_CCArmature_getBatchNode00);
   tolua_function(tolua_S,"setBatchNode",tolua_CocoStudio_CCArmature_setBatchNode00);
   tolua_function(tolua_S,"getName",tolua_CocoStudio_CCArmature_getName00);
   tolua_function(tolua_S,"setName",tolua_CocoStudio_CCArmature_setName00);
   tolua_function(tolua_S,"getTextureAtlas",tolua_CocoStudio_CCArmature_getTextureAtlas00);
   tolua_function(tolua_S,"setTextureAtlas",tolua_CocoStudio_CCArmature_setTextureAtlas00);
   tolua_function(tolua_S,"getParentBone",tolua_CocoStudio_CCArmature_getParentBone00);
   tolua_function(tolua_S,"setParentBone",tolua_CocoStudio_CCArmature_setParentBone00);
   tolua_function(tolua_S,"getVersion",tolua_CocoStudio_CCArmature_getVersion00);
   tolua_function(tolua_S,"setVersion",tolua_CocoStudio_CCArmature_setVersion00);
   tolua_function(tolua_S,"getArmatureTransformDirty",tolua_CocoStudio_CCArmature_getArmatureTransformDirty00);
   tolua_variable(tolua_S,"__CCBlendProtocol__",tolua_get_CCArmature___CCBlendProtocol__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCArmatureAnimation","CCArmatureAnimation","CCProcessBase",tolua_collect_CCArmatureAnimation);
  #else
  tolua_cclass(tolua_S,"CCArmatureAnimation","CCArmatureAnimation","CCProcessBase",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCArmatureAnimation");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCArmatureAnimation_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCArmatureAnimation_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCArmatureAnimation_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCArmatureAnimation_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCArmatureAnimation_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCArmatureAnimation_init00);
   tolua_function(tolua_S,"setSpeedScale",tolua_CocoStudio_CCArmatureAnimation_setSpeedScale00);
   tolua_function(tolua_S,"getSpeedScale",tolua_CocoStudio_CCArmatureAnimation_getSpeedScale00);
   tolua_function(tolua_S,"setAnimationInternal",tolua_CocoStudio_CCArmatureAnimation_setAnimationInternal00);
   tolua_function(tolua_S,"play",tolua_CocoStudio_CCArmatureAnimation_play00);
   tolua_function(tolua_S,"play",tolua_CocoStudio_CCArmatureAnimation_play01);
   tolua_function(tolua_S,"playByIndex",tolua_CocoStudio_CCArmatureAnimation_playByIndex00);
   tolua_function(tolua_S,"gotoAndPlay",tolua_CocoStudio_CCArmatureAnimation_gotoAndPlay00);
   tolua_function(tolua_S,"gotoAndPause",tolua_CocoStudio_CCArmatureAnimation_gotoAndPause00);
   tolua_function(tolua_S,"pause",tolua_CocoStudio_CCArmatureAnimation_pause00);
   tolua_function(tolua_S,"resume",tolua_CocoStudio_CCArmatureAnimation_resume00);
   tolua_function(tolua_S,"stop",tolua_CocoStudio_CCArmatureAnimation_stop00);
   tolua_function(tolua_S,"getMovementCount",tolua_CocoStudio_CCArmatureAnimation_getMovementCount00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_CCArmatureAnimation_update00);
   tolua_function(tolua_S,"getCurrentMovementID",tolua_CocoStudio_CCArmatureAnimation_getCurrentMovementID00);
   tolua_function(tolua_S,"getUserObject",tolua_CocoStudio_CCArmatureAnimation_getUserObject00);
   tolua_function(tolua_S,"setUserObject",tolua_CocoStudio_CCArmatureAnimation_setUserObject00);
   tolua_function(tolua_S,"getAnimationData",tolua_CocoStudio_CCArmatureAnimation_getAnimationData00);
   tolua_function(tolua_S,"setAnimationData",tolua_CocoStudio_CCArmatureAnimation_setAnimationData00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCSkin","CCSkin","CCSprite",tolua_collect_CCSkin);
  #else
  tolua_cclass(tolua_S,"CCSkin","CCSkin","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCSkin");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCSkin_create00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_CocoStudio_CCSkin_createWithSpriteFrameName00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCSkin_create01);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCSkin_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCSkin_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCSkin_new00_local);
   tolua_function(tolua_S,"initWithSpriteFrameName",tolua_CocoStudio_CCSkin_initWithSpriteFrameName00);
   tolua_function(tolua_S,"initWithFile",tolua_CocoStudio_CCSkin_initWithFile00);
   tolua_function(tolua_S,"updateArmatureTransform",tolua_CocoStudio_CCSkin_updateArmatureTransform00);
   tolua_function(tolua_S,"updateTransform",tolua_CocoStudio_CCSkin_updateTransform00);
   tolua_function(tolua_S,"nodeToWorldTransform",tolua_CocoStudio_CCSkin_nodeToWorldTransform00);
   tolua_function(tolua_S,"nodeToWorldTransformAR",tolua_CocoStudio_CCSkin_nodeToWorldTransformAR00);
   tolua_function(tolua_S,"getSkinData",tolua_CocoStudio_CCSkin_getSkinData00);
   tolua_function(tolua_S,"setSkinData",tolua_CocoStudio_CCSkin_setSkinData00);
   tolua_function(tolua_S,"getBone",tolua_CocoStudio_CCSkin_getBone00);
   tolua_function(tolua_S,"setBone",tolua_CocoStudio_CCSkin_setBone00);
   tolua_function(tolua_S,"getDisplayName",tolua_CocoStudio_CCSkin_getDisplayName00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCBone","CCBone","CCNodeRGBA",tolua_collect_CCBone);
  #else
  tolua_cclass(tolua_S,"CCBone","CCBone","CCNodeRGBA",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCBone");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCBone_create00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCBone_create01);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCBone_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCBone_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCBone_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCBone_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCBone_init00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCBone_init01);
   tolua_function(tolua_S,"addDisplay",tolua_CocoStudio_CCBone_addDisplay00);
   tolua_function(tolua_S,"addDisplay",tolua_CocoStudio_CCBone_addDisplay01);
   tolua_function(tolua_S,"removeDisplay",tolua_CocoStudio_CCBone_removeDisplay00);
   tolua_function(tolua_S,"changeDisplayByIndex",tolua_CocoStudio_CCBone_changeDisplayByIndex00);
   tolua_function(tolua_S,"addChildBone",tolua_CocoStudio_CCBone_addChildBone00);
   tolua_function(tolua_S,"setParentBone",tolua_CocoStudio_CCBone_setParentBone00);
   tolua_function(tolua_S,"getParentBone",tolua_CocoStudio_CCBone_getParentBone00);
   tolua_function(tolua_S,"removeFromParent",tolua_CocoStudio_CCBone_removeFromParent00);
   tolua_function(tolua_S,"removeFromParent",tolua_CocoStudio_CCBone_removeFromParent01);
   tolua_function(tolua_S,"removeChildBone",tolua_CocoStudio_CCBone_removeChildBone00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_CCBone_update00);
   tolua_function(tolua_S,"updateDisplayedColor",tolua_CocoStudio_CCBone_updateDisplayedColor00);
   tolua_function(tolua_S,"updateDisplayedOpacity",tolua_CocoStudio_CCBone_updateDisplayedOpacity00);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_CCBone_setColor00);
   tolua_function(tolua_S,"setOpacity",tolua_CocoStudio_CCBone_setOpacity00);
   tolua_function(tolua_S,"updateColor",tolua_CocoStudio_CCBone_updateColor00);
   tolua_function(tolua_S,"updateZOrder",tolua_CocoStudio_CCBone_updateZOrder00);
   tolua_function(tolua_S,"setZOrder",tolua_CocoStudio_CCBone_setZOrder00);
   tolua_function(tolua_S,"getTween",tolua_CocoStudio_CCBone_getTween00);
   tolua_function(tolua_S,"setTransformDirty",tolua_CocoStudio_CCBone_setTransformDirty00);
   tolua_function(tolua_S,"isTransformDirty",tolua_CocoStudio_CCBone_isTransformDirty00);
   tolua_function(tolua_S,"nodeToArmatureTransform",tolua_CocoStudio_CCBone_nodeToArmatureTransform00);
   tolua_function(tolua_S,"nodeToWorldTransform",tolua_CocoStudio_CCBone_nodeToWorldTransform00);
   tolua_function(tolua_S,"getDisplayRenderNode",tolua_CocoStudio_CCBone_getDisplayRenderNode00);
   tolua_function(tolua_S,"getDisplayRenderNodeType",tolua_CocoStudio_CCBone_getDisplayRenderNodeType00);
   tolua_function(tolua_S,"getArmature",tolua_CocoStudio_CCBone_getArmature00);
   tolua_function(tolua_S,"setArmature",tolua_CocoStudio_CCBone_setArmature00);
   tolua_function(tolua_S,"getChildArmature",tolua_CocoStudio_CCBone_getChildArmature00);
   tolua_function(tolua_S,"setChildArmature",tolua_CocoStudio_CCBone_setChildArmature00);
   tolua_function(tolua_S,"getDisplayManager",tolua_CocoStudio_CCBone_getDisplayManager00);
   tolua_function(tolua_S,"setDisplayManager",tolua_CocoStudio_CCBone_setDisplayManager00);
   tolua_function(tolua_S,"getIgnoreMovementBoneData",tolua_CocoStudio_CCBone_getIgnoreMovementBoneData00);
   tolua_function(tolua_S,"setIgnoreMovementBoneData",tolua_CocoStudio_CCBone_setIgnoreMovementBoneData00);
   tolua_function(tolua_S,"getBlendType",tolua_CocoStudio_CCBone_getBlendType00);
   tolua_function(tolua_S,"setBlendType",tolua_CocoStudio_CCBone_setBlendType00);
   tolua_function(tolua_S,"getName",tolua_CocoStudio_CCBone_getName00);
   tolua_function(tolua_S,"setName",tolua_CocoStudio_CCBone_setName00);
   tolua_function(tolua_S,"getWorldInfo",tolua_CocoStudio_CCBone_getWorldInfo00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCArmatureDataManager","CCArmatureDataManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCArmatureDataManager");
   tolua_function(tolua_S,"sharedArmatureDataManager",tolua_CocoStudio_CCArmatureDataManager_sharedArmatureDataManager00);
   tolua_function(tolua_S,"purge",tolua_CocoStudio_CCArmatureDataManager_purge00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCArmatureDataManager_init00);
   tolua_function(tolua_S,"addArmatureFileInfo",tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo00);
   tolua_function(tolua_S,"addArmatureFileInfo",tolua_CocoStudio_CCArmatureDataManager_addArmatureFileInfo01);
   tolua_function(tolua_S,"removeArmatureFileInfo",tolua_CocoStudio_CCArmatureDataManager_removeArmatureFileInfo00);
   tolua_function(tolua_S,"addSpriteFrameFromFile",tolua_CocoStudio_CCArmatureDataManager_addSpriteFrameFromFile00);
   tolua_function(tolua_S,"isAutoLoadSpriteFile",tolua_CocoStudio_CCArmatureDataManager_isAutoLoadSpriteFile00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCBatchNode","CCBatchNode","CCNode",tolua_collect_CCBatchNode);
  #else
  tolua_cclass(tolua_S,"CCBatchNode","CCBatchNode","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCBatchNode");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCBatchNode_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCBatchNode_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCBatchNode_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCBatchNode_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCBatchNode_delete00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_CCBatchNode_addChild00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_CCBatchNode_addChild01);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_CCBatchNode_addChild02);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_CCBatchNode_removeChild00);
   tolua_function(tolua_S,"getTexureAtlasWithTexture",tolua_CocoStudio_CCBatchNode_getTexureAtlasWithTexture00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCTween","CCTween","CCProcessBase",tolua_collect_CCTween);
  #else
  tolua_cclass(tolua_S,"CCTween","CCTween","CCProcessBase",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCTween");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCTween_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCTween_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCTween_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCTween_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCTween_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCTween_init00);
   tolua_function(tolua_S,"play",tolua_CocoStudio_CCTween_play00);
   tolua_function(tolua_S,"gotoAndPlay",tolua_CocoStudio_CCTween_gotoAndPlay00);
   tolua_function(tolua_S,"gotoAndPause",tolua_CocoStudio_CCTween_gotoAndPause00);
   tolua_function(tolua_S,"setAnimation",tolua_CocoStudio_CCTween_setAnimation00);
   tolua_function(tolua_S,"getAnimation",tolua_CocoStudio_CCTween_getAnimation00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCBaseData","CCBaseData","CCObject",tolua_collect_CCBaseData);
  #else
  tolua_cclass(tolua_S,"CCBaseData","CCBaseData","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCBaseData");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCBaseData_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCBaseData_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCBaseData_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCBaseData_new00_local);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_CCBaseData_setColor00);
   tolua_function(tolua_S,"getColor",tolua_CocoStudio_CCBaseData_getColor00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCDisplayManager","CCDisplayManager","CCObject",tolua_collect_CCDisplayManager);
  #else
  tolua_cclass(tolua_S,"CCDisplayManager","CCDisplayManager","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCDisplayManager");
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCDisplayManager_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCDisplayManager_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCDisplayManager_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCDisplayManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCDisplayManager_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCDisplayManager_init00);
   tolua_function(tolua_S,"addDisplay",tolua_CocoStudio_CCDisplayManager_addDisplay00);
   tolua_function(tolua_S,"addDisplay",tolua_CocoStudio_CCDisplayManager_addDisplay01);
   tolua_function(tolua_S,"removeDisplay",tolua_CocoStudio_CCDisplayManager_removeDisplay00);
   tolua_function(tolua_S,"getDecorativeDisplayList",tolua_CocoStudio_CCDisplayManager_getDecorativeDisplayList00);
   tolua_function(tolua_S,"changeDisplayByIndex",tolua_CocoStudio_CCDisplayManager_changeDisplayByIndex00);
   tolua_function(tolua_S,"getDisplayRenderNode",tolua_CocoStudio_CCDisplayManager_getDisplayRenderNode00);
   tolua_function(tolua_S,"getDisplayRenderNodeType",tolua_CocoStudio_CCDisplayManager_getDisplayRenderNodeType00);
   tolua_function(tolua_S,"getCurrentDisplayIndex",tolua_CocoStudio_CCDisplayManager_getCurrentDisplayIndex00);
   tolua_function(tolua_S,"setVisible",tolua_CocoStudio_CCDisplayManager_setVisible00);
   tolua_function(tolua_S,"isVisible",tolua_CocoStudio_CCDisplayManager_isVisible00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_CCDisplayManager_getContentSize00);
   tolua_function(tolua_S,"getBoundingBox",tolua_CocoStudio_CCDisplayManager_getBoundingBox00);
   tolua_function(tolua_S,"getAnchorPoint",tolua_CocoStudio_CCDisplayManager_getAnchorPoint00);
   tolua_function(tolua_S,"getAnchorPointInPoints",tolua_CocoStudio_CCDisplayManager_getAnchorPointInPoints00);
   tolua_function(tolua_S,"containPoint",tolua_CocoStudio_CCDisplayManager_containPoint00);
   tolua_function(tolua_S,"containPoint",tolua_CocoStudio_CCDisplayManager_containPoint01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIHelper","UIHelper","",NULL);
  tolua_beginmodule(tolua_S,"UIHelper");
   tolua_function(tolua_S,"seekWidgetByTag",tolua_CocoStudio_UIHelper_seekWidgetByTag00);
   tolua_function(tolua_S,"seekWidgetByName",tolua_CocoStudio_UIHelper_seekWidgetByName00);
   tolua_function(tolua_S,"seekWidgetByRelativeName",tolua_CocoStudio_UIHelper_seekWidgetByRelativeName00);
   tolua_function(tolua_S,"seekActionWidgetByActionTag",tolua_CocoStudio_UIHelper_seekActionWidgetByActionTag00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LAYOUT_COLOR_NONE",LAYOUT_COLOR_NONE);
  tolua_constant(tolua_S,"LAYOUT_COLOR_SOLID",LAYOUT_COLOR_SOLID);
  tolua_constant(tolua_S,"LAYOUT_COLOR_GRADIENT",LAYOUT_COLOR_GRADIENT);
  tolua_constant(tolua_S,"LAYOUT_ABSOLUTE",LAYOUT_ABSOLUTE);
  tolua_constant(tolua_S,"LAYOUT_LINEAR_VERTICAL",LAYOUT_LINEAR_VERTICAL);
  tolua_constant(tolua_S,"LAYOUT_LINEAR_HORIZONTAL",LAYOUT_LINEAR_HORIZONTAL);
  tolua_constant(tolua_S,"LAYOUT_RELATIVE",LAYOUT_RELATIVE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILayout","UILayout","UIWidget",tolua_collect_UILayout);
  #else
  tolua_cclass(tolua_S,"UILayout","UILayout","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILayout");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILayout_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILayout_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILayout_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILayout_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILayout_create00);
   tolua_function(tolua_S,"hitTest",tolua_CocoStudio_UILayout_hitTest00);
   tolua_function(tolua_S,"setBackGroundImage",tolua_CocoStudio_UILayout_setBackGroundImage00);
   tolua_function(tolua_S,"setBackGroundImageCapInsets",tolua_CocoStudio_UILayout_setBackGroundImageCapInsets00);
   tolua_function(tolua_S,"setBackGroundColorType",tolua_CocoStudio_UILayout_setBackGroundColorType00);
   tolua_function(tolua_S,"setBackGroundImageScale9Enabled",tolua_CocoStudio_UILayout_setBackGroundImageScale9Enabled00);
   tolua_function(tolua_S,"setBackGroundColor",tolua_CocoStudio_UILayout_setBackGroundColor00);
   tolua_function(tolua_S,"setBackGroundColor",tolua_CocoStudio_UILayout_setBackGroundColor01);
   tolua_function(tolua_S,"setBackGroundColorOpacity",tolua_CocoStudio_UILayout_setBackGroundColorOpacity00);
   tolua_function(tolua_S,"setBackGroundColorVector",tolua_CocoStudio_UILayout_setBackGroundColorVector00);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_UILayout_setColor00);
   tolua_function(tolua_S,"setOpacity",tolua_CocoStudio_UILayout_setOpacity00);
   tolua_function(tolua_S,"removeBackGroundImage",tolua_CocoStudio_UILayout_removeBackGroundImage00);
   tolua_function(tolua_S,"getBackGroundImageTextureSize",tolua_CocoStudio_UILayout_getBackGroundImageTextureSize00);
   tolua_function(tolua_S,"setClippingEnabled",tolua_CocoStudio_UILayout_setClippingEnabled00);
   tolua_function(tolua_S,"isClippingEnabled",tolua_CocoStudio_UILayout_isClippingEnabled00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UILayout_getContentSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UILayout_getDescription00);
   tolua_function(tolua_S,"setLayoutType",tolua_CocoStudio_UILayout_setLayoutType00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_UILayout_getLayoutType00);
   tolua_function(tolua_S,"doLayout",tolua_CocoStudio_UILayout_doLayout00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_UILayout_addChild00);
   tolua_function(tolua_S,"setBackGroundImageScale9Enable",tolua_CocoStudio_UILayout_setBackGroundImageScale9Enable00);
   tolua_function(tolua_S,"setClippingEnable",tolua_CocoStudio_UILayout_setClippingEnable00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"BRIGHT_NONE",BRIGHT_NONE);
  tolua_constant(tolua_S,"BRIGHT_NORMAL",BRIGHT_NORMAL);
  tolua_constant(tolua_S,"BRIGHT_HIGHLIGHT",BRIGHT_HIGHLIGHT);
  tolua_constant(tolua_S,"WidgetTypeWidget",WidgetTypeWidget);
  tolua_constant(tolua_S,"WidgetTypeContainer",WidgetTypeContainer);
  tolua_constant(tolua_S,"UI_TEX_TYPE_LOCAL",UI_TEX_TYPE_LOCAL);
  tolua_constant(tolua_S,"UI_TEX_TYPE_PLIST",UI_TEX_TYPE_PLIST);
  tolua_constant(tolua_S,"TOUCH_EVENT_BEGAN",TOUCH_EVENT_BEGAN);
  tolua_constant(tolua_S,"TOUCH_EVENT_MOVED",TOUCH_EVENT_MOVED);
  tolua_constant(tolua_S,"TOUCH_EVENT_ENDED",TOUCH_EVENT_ENDED);
  tolua_constant(tolua_S,"TOUCH_EVENT_CANCELED",TOUCH_EVENT_CANCELED);
  tolua_constant(tolua_S,"SIZE_ABSOLUTE",SIZE_ABSOLUTE);
  tolua_constant(tolua_S,"SIZE_PERCENT",SIZE_PERCENT);
  tolua_constant(tolua_S,"POSITION_ABSOLUTE",POSITION_ABSOLUTE);
  tolua_constant(tolua_S,"POSITION_PERCENT",POSITION_PERCENT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIWidget","UIWidget","CCObject",tolua_collect_UIWidget);
  #else
  tolua_cclass(tolua_S,"UIWidget","UIWidget","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIWidget");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIWidget_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIWidget_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIWidget_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIWidget_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIWidget_create00);
   tolua_function(tolua_S,"setEnabled",tolua_CocoStudio_UIWidget_setEnabled00);
   tolua_function(tolua_S,"isEnabled",tolua_CocoStudio_UIWidget_isEnabled00);
   tolua_function(tolua_S,"setVisible",tolua_CocoStudio_UIWidget_setVisible00);
   tolua_function(tolua_S,"isVisible",tolua_CocoStudio_UIWidget_isVisible00);
   tolua_function(tolua_S,"setBright",tolua_CocoStudio_UIWidget_setBright00);
   tolua_function(tolua_S,"isBright",tolua_CocoStudio_UIWidget_isBright00);
   tolua_function(tolua_S,"setTouchEnabled",tolua_CocoStudio_UIWidget_setTouchEnabled00);
   tolua_function(tolua_S,"setBrightStyle",tolua_CocoStudio_UIWidget_setBrightStyle00);
   tolua_function(tolua_S,"isTouchEnabled",tolua_CocoStudio_UIWidget_isTouchEnabled00);
   tolua_function(tolua_S,"isFocused",tolua_CocoStudio_UIWidget_isFocused00);
   tolua_function(tolua_S,"setFocused",tolua_CocoStudio_UIWidget_setFocused00);
   tolua_function(tolua_S,"setZOrder",tolua_CocoStudio_UIWidget_setZOrder00);
   tolua_function(tolua_S,"getZOrder",tolua_CocoStudio_UIWidget_getZOrder00);
   tolua_function(tolua_S,"getLeftInParent",tolua_CocoStudio_UIWidget_getLeftInParent00);
   tolua_function(tolua_S,"getBottomInParent",tolua_CocoStudio_UIWidget_getBottomInParent00);
   tolua_function(tolua_S,"getRightInParent",tolua_CocoStudio_UIWidget_getRightInParent00);
   tolua_function(tolua_S,"getTopInParent",tolua_CocoStudio_UIWidget_getTopInParent00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_UIWidget_addChild00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_UIWidget_removeChild00);
   tolua_function(tolua_S,"removeFromParent",tolua_CocoStudio_UIWidget_removeFromParent00);
   tolua_function(tolua_S,"removeAllChildren",tolua_CocoStudio_UIWidget_removeAllChildren00);
   tolua_function(tolua_S,"reorderChild",tolua_CocoStudio_UIWidget_reorderChild00);
   tolua_function(tolua_S,"getChildByName",tolua_CocoStudio_UIWidget_getChildByName00);
   tolua_function(tolua_S,"getChildByTag",tolua_CocoStudio_UIWidget_getChildByTag00);
   tolua_function(tolua_S,"getChildren",tolua_CocoStudio_UIWidget_getChildren00);
   tolua_function(tolua_S,"getRenderer",tolua_CocoStudio_UIWidget_getRenderer00);
   tolua_function(tolua_S,"addRenderer",tolua_CocoStudio_UIWidget_addRenderer00);
   tolua_function(tolua_S,"removeRenderer",tolua_CocoStudio_UIWidget_removeRenderer00);
   tolua_function(tolua_S,"setParent",tolua_CocoStudio_UIWidget_setParent00);
   tolua_function(tolua_S,"getParent",tolua_CocoStudio_UIWidget_getParent00);
   tolua_function(tolua_S,"addTouchEventListener",tolua_CocoStudio_UIWidget_addTouchEventListener00);
   tolua_function(tolua_S,"setPosition",tolua_CocoStudio_UIWidget_setPosition00);
   tolua_function(tolua_S,"setPositionPercent",tolua_CocoStudio_UIWidget_setPositionPercent00);
   tolua_function(tolua_S,"getPosition",tolua_CocoStudio_UIWidget_getPosition00);
   tolua_function(tolua_S,"getPositionPercent",tolua_CocoStudio_UIWidget_getPositionPercent00);
   tolua_function(tolua_S,"setPositionType",tolua_CocoStudio_UIWidget_setPositionType00);
   tolua_function(tolua_S,"getPositionType",tolua_CocoStudio_UIWidget_getPositionType00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UIWidget_setAnchorPoint00);
   tolua_function(tolua_S,"getAnchorPoint",tolua_CocoStudio_UIWidget_getAnchorPoint00);
   tolua_function(tolua_S,"setScale",tolua_CocoStudio_UIWidget_setScale00);
   tolua_function(tolua_S,"getScale",tolua_CocoStudio_UIWidget_getScale00);
   tolua_function(tolua_S,"setScaleX",tolua_CocoStudio_UIWidget_setScaleX00);
   tolua_function(tolua_S,"getScaleX",tolua_CocoStudio_UIWidget_getScaleX00);
   tolua_function(tolua_S,"setScaleY",tolua_CocoStudio_UIWidget_setScaleY00);
   tolua_function(tolua_S,"getScaleY",tolua_CocoStudio_UIWidget_getScaleY00);
   tolua_function(tolua_S,"setRotation",tolua_CocoStudio_UIWidget_setRotation00);
   tolua_function(tolua_S,"getRotation",tolua_CocoStudio_UIWidget_getRotation00);
   tolua_function(tolua_S,"setRotationX",tolua_CocoStudio_UIWidget_setRotationX00);
   tolua_function(tolua_S,"getRotationX",tolua_CocoStudio_UIWidget_getRotationX00);
   tolua_function(tolua_S,"setRotationY",tolua_CocoStudio_UIWidget_setRotationY00);
   tolua_function(tolua_S,"getRotationY",tolua_CocoStudio_UIWidget_getRotationY00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_UIWidget_setFlipX00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_UIWidget_isFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_UIWidget_setFlipY00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_UIWidget_isFlipY00);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_UIWidget_setColor00);
   tolua_function(tolua_S,"getColor",tolua_CocoStudio_UIWidget_getColor00);
   tolua_function(tolua_S,"setOpacity",tolua_CocoStudio_UIWidget_setOpacity00);
   tolua_function(tolua_S,"getOpacity",tolua_CocoStudio_UIWidget_getOpacity00);
   tolua_function(tolua_S,"isCascadeOpacityEnabled",tolua_CocoStudio_UIWidget_isCascadeOpacityEnabled00);
   tolua_function(tolua_S,"setCascadeOpacityEnabled",tolua_CocoStudio_UIWidget_setCascadeOpacityEnabled00);
   tolua_function(tolua_S,"isCascadeColorEnabled",tolua_CocoStudio_UIWidget_isCascadeColorEnabled00);
   tolua_function(tolua_S,"setCascadeColorEnabled",tolua_CocoStudio_UIWidget_setCascadeColorEnabled00);
   tolua_function(tolua_S,"setBlendFunc",tolua_CocoStudio_UIWidget_setBlendFunc00);
   tolua_function(tolua_S,"setActionManager",tolua_CocoStudio_UIWidget_setActionManager00);
   tolua_function(tolua_S,"getActionManager",tolua_CocoStudio_UIWidget_getActionManager00);
   tolua_function(tolua_S,"runAction",tolua_CocoStudio_UIWidget_runAction00);
   tolua_function(tolua_S,"stopAllActions",tolua_CocoStudio_UIWidget_stopAllActions00);
   tolua_function(tolua_S,"stopAction",tolua_CocoStudio_UIWidget_stopAction00);
   tolua_function(tolua_S,"stopActionByTag",tolua_CocoStudio_UIWidget_stopActionByTag00);
   tolua_function(tolua_S,"getActionByTag",tolua_CocoStudio_UIWidget_getActionByTag00);
   tolua_function(tolua_S,"didNotSelectSelf",tolua_CocoStudio_UIWidget_didNotSelectSelf00);
   tolua_function(tolua_S,"clippingParentAreaContainPoint",tolua_CocoStudio_UIWidget_clippingParentAreaContainPoint00);
   tolua_function(tolua_S,"checkChildInfo",tolua_CocoStudio_UIWidget_checkChildInfo00);
   tolua_function(tolua_S,"getTouchStartPos",tolua_CocoStudio_UIWidget_getTouchStartPos00);
   tolua_function(tolua_S,"getTouchMovePos",tolua_CocoStudio_UIWidget_getTouchMovePos00);
   tolua_function(tolua_S,"getTouchEndPos",tolua_CocoStudio_UIWidget_getTouchEndPos00);
   tolua_function(tolua_S,"setTag",tolua_CocoStudio_UIWidget_setTag00);
   tolua_function(tolua_S,"getTag",tolua_CocoStudio_UIWidget_getTag00);
   tolua_function(tolua_S,"setName",tolua_CocoStudio_UIWidget_setName00);
   tolua_function(tolua_S,"getName",tolua_CocoStudio_UIWidget_getName00);
   tolua_function(tolua_S,"getWidgetType",tolua_CocoStudio_UIWidget_getWidgetType00);
   tolua_function(tolua_S,"setSize",tolua_CocoStudio_UIWidget_setSize00);
   tolua_function(tolua_S,"setSizePercent",tolua_CocoStudio_UIWidget_setSizePercent00);
   tolua_function(tolua_S,"setSizeType",tolua_CocoStudio_UIWidget_setSizeType00);
   tolua_function(tolua_S,"getSizeType",tolua_CocoStudio_UIWidget_getSizeType00);
   tolua_function(tolua_S,"getSize",tolua_CocoStudio_UIWidget_getSize00);
   tolua_function(tolua_S,"getSizePercent",tolua_CocoStudio_UIWidget_getSizePercent00);
   tolua_function(tolua_S,"hitTest",tolua_CocoStudio_UIWidget_hitTest00);
   tolua_function(tolua_S,"onTouchBegan",tolua_CocoStudio_UIWidget_onTouchBegan00);
   tolua_function(tolua_S,"onTouchMoved",tolua_CocoStudio_UIWidget_onTouchMoved00);
   tolua_function(tolua_S,"onTouchEnded",tolua_CocoStudio_UIWidget_onTouchEnded00);
   tolua_function(tolua_S,"onTouchCancelled",tolua_CocoStudio_UIWidget_onTouchCancelled00);
   tolua_function(tolua_S,"onTouchLongClicked",tolua_CocoStudio_UIWidget_onTouchLongClicked00);
   tolua_function(tolua_S,"setLayoutParameter",tolua_CocoStudio_UIWidget_setLayoutParameter00);
   tolua_function(tolua_S,"getLayoutParameter",tolua_CocoStudio_UIWidget_getLayoutParameter00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_UIWidget_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"isIgnoreContentAdaptWithSize",tolua_CocoStudio_UIWidget_isIgnoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getWorldPosition",tolua_CocoStudio_UIWidget_getWorldPosition00);
   tolua_function(tolua_S,"convertToWorldSpace",tolua_CocoStudio_UIWidget_convertToWorldSpace00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UIWidget_getVirtualRenderer00);
   tolua_function(tolua_S,"setUpdateEnabled",tolua_CocoStudio_UIWidget_setUpdateEnabled00);
   tolua_function(tolua_S,"isUpdateEnabled",tolua_CocoStudio_UIWidget_isUpdateEnabled00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UIWidget_getContentSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIWidget_getDescription00);
   tolua_function(tolua_S,"clone",tolua_CocoStudio_UIWidget_clone00);
   tolua_function(tolua_S,"onEnter",tolua_CocoStudio_UIWidget_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_CocoStudio_UIWidget_onExit00);
   tolua_function(tolua_S,"getUserObject",tolua_CocoStudio_UIWidget_getUserObject00);
   tolua_function(tolua_S,"setUserObject",tolua_CocoStudio_UIWidget_setUserObject00);
   tolua_function(tolua_S,"setTouchEnable",tolua_CocoStudio_UIWidget_setTouchEnable00);
   tolua_function(tolua_S,"disable",tolua_CocoStudio_UIWidget_disable00);
   tolua_function(tolua_S,"active",tolua_CocoStudio_UIWidget_active00);
   tolua_function(tolua_S,"isActive",tolua_CocoStudio_UIWidget_isActive00);
   tolua_function(tolua_S,"setBright",tolua_CocoStudio_UIWidget_setBright01);
   tolua_function(tolua_S,"getRect",tolua_CocoStudio_UIWidget_getRect00);
   tolua_function(tolua_S,"getValidNode",tolua_CocoStudio_UIWidget_getValidNode00);
   tolua_function(tolua_S,"setWidgetZOrder",tolua_CocoStudio_UIWidget_setWidgetZOrder00);
   tolua_function(tolua_S,"getWidgetZOrder",tolua_CocoStudio_UIWidget_getWidgetZOrder00);
   tolua_function(tolua_S,"getRelativeLeftPos",tolua_CocoStudio_UIWidget_getRelativeLeftPos00);
   tolua_function(tolua_S,"getRelativeBottomPos",tolua_CocoStudio_UIWidget_getRelativeBottomPos00);
   tolua_function(tolua_S,"getRelativeRightPos",tolua_CocoStudio_UIWidget_getRelativeRightPos00);
   tolua_function(tolua_S,"getRelativeTopPos",tolua_CocoStudio_UIWidget_getRelativeTopPos00);
   tolua_function(tolua_S,"getContainerNode",tolua_CocoStudio_UIWidget_getContainerNode00);
   tolua_function(tolua_S,"setWidgetParent",tolua_CocoStudio_UIWidget_setWidgetParent00);
   tolua_function(tolua_S,"getWidgetParent",tolua_CocoStudio_UIWidget_getWidgetParent00);
   tolua_function(tolua_S,"setWidgetTag",tolua_CocoStudio_UIWidget_setWidgetTag00);
   tolua_function(tolua_S,"getWidgetTag",tolua_CocoStudio_UIWidget_getWidgetTag00);
   tolua_function(tolua_S,"addCCNode",tolua_CocoStudio_UIWidget_addCCNode00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_UIWidget_removeChild01);
   tolua_function(tolua_S,"removeFromParentAndCleanup",tolua_CocoStudio_UIWidget_removeFromParentAndCleanup00);
   tolua_function(tolua_S,"removeAllChildrenAndCleanUp",tolua_CocoStudio_UIWidget_removeAllChildrenAndCleanUp00);
   tolua_function(tolua_S,"setActionTag",tolua_CocoStudio_UIWidget_setActionTag00);
   tolua_function(tolua_S,"getActionTag",tolua_CocoStudio_UIWidget_getActionTag00);
   tolua_function(tolua_S,"updateSizeAndPosition",tolua_CocoStudio_UIWidget_updateSizeAndPosition00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILayer","UILayer","CCLayer",tolua_collect_UILayer);
  #else
  tolua_cclass(tolua_S,"UILayer","UILayer","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILayer");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILayer_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILayer_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILayer_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILayer_create00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_UILayer_init00);
   tolua_function(tolua_S,"addWidget",tolua_CocoStudio_UILayer_addWidget00);
   tolua_function(tolua_S,"removeWidget",tolua_CocoStudio_UILayer_removeWidget00);
   tolua_function(tolua_S,"setVisible",tolua_CocoStudio_UILayer_setVisible00);
   tolua_function(tolua_S,"getWidgetByTag",tolua_CocoStudio_UILayer_getWidgetByTag00);
   tolua_function(tolua_S,"getWidgetByName",tolua_CocoStudio_UILayer_getWidgetByName00);
   tolua_function(tolua_S,"clear",tolua_CocoStudio_UILayer_clear00);
   tolua_function(tolua_S,"getRootWidget",tolua_CocoStudio_UILayer_getRootWidget00);
   tolua_function(tolua_S,"dispose",tolua_CocoStudio_UILayer_dispose00);
   tolua_function(tolua_S,"removeWidgetAndCleanUp",tolua_CocoStudio_UILayer_removeWidgetAndCleanUp00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIButton","UIButton","UIWidget",tolua_collect_UIButton);
  #else
  tolua_cclass(tolua_S,"UIButton","UIButton","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIButton");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIButton_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIButton_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIButton_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIButton_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIButton_create00);
   tolua_function(tolua_S,"loadTextures",tolua_CocoStudio_UIButton_loadTextures00);
   tolua_function(tolua_S,"loadTextureNormal",tolua_CocoStudio_UIButton_loadTextureNormal00);
   tolua_function(tolua_S,"loadTexturePressed",tolua_CocoStudio_UIButton_loadTexturePressed00);
   tolua_function(tolua_S,"loadTextureDisabled",tolua_CocoStudio_UIButton_loadTextureDisabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_UIButton_setCapInsets00);
   tolua_function(tolua_S,"setCapInsetsNormalRenderer",tolua_CocoStudio_UIButton_setCapInsetsNormalRenderer00);
   tolua_function(tolua_S,"setCapInsetsPressedRenderer",tolua_CocoStudio_UIButton_setCapInsetsPressedRenderer00);
   tolua_function(tolua_S,"setCapInsetsDisabledRenderer",tolua_CocoStudio_UIButton_setCapInsetsDisabledRenderer00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UIButton_setAnchorPoint00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_UIButton_setScale9Enabled00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_UIButton_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_UIButton_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_UIButton_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_UIButton_isFlipY00);
   tolua_function(tolua_S,"setPressedActionEnabled",tolua_CocoStudio_UIButton_setPressedActionEnabled00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_UIButton_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UIButton_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UIButton_getVirtualRenderer00);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_UIButton_setColor00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIButton_getDescription00);
   tolua_function(tolua_S,"setTitleText",tolua_CocoStudio_UIButton_setTitleText00);
   tolua_function(tolua_S,"getTitleText",tolua_CocoStudio_UIButton_getTitleText00);
   tolua_function(tolua_S,"setTitleColor",tolua_CocoStudio_UIButton_setTitleColor00);
   tolua_function(tolua_S,"getTitleColor",tolua_CocoStudio_UIButton_getTitleColor00);
   tolua_function(tolua_S,"setTitleFontSize",tolua_CocoStudio_UIButton_setTitleFontSize00);
   tolua_function(tolua_S,"getTitleFontSize",tolua_CocoStudio_UIButton_getTitleFontSize00);
   tolua_function(tolua_S,"setTitleFontName",tolua_CocoStudio_UIButton_setTitleFontName00);
   tolua_function(tolua_S,"getTitleFontName",tolua_CocoStudio_UIButton_getTitleFontName00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_UIButton_setText00);
   tolua_function(tolua_S,"setTextColor",tolua_CocoStudio_UIButton_setTextColor00);
   tolua_function(tolua_S,"setFontSize",tolua_CocoStudio_UIButton_setFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_CocoStudio_UIButton_setFontName00);
   tolua_function(tolua_S,"setTextures",tolua_CocoStudio_UIButton_setTextures00);
   tolua_function(tolua_S,"setNormalTexture",tolua_CocoStudio_UIButton_setNormalTexture00);
   tolua_function(tolua_S,"setPressedTexture",tolua_CocoStudio_UIButton_setPressedTexture00);
   tolua_function(tolua_S,"setDisabledTexture",tolua_CocoStudio_UIButton_setDisabledTexture00);
   tolua_function(tolua_S,"setScale9Enable",tolua_CocoStudio_UIButton_setScale9Enable00);
   tolua_function(tolua_S,"setScale9Size",tolua_CocoStudio_UIButton_setScale9Size00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CHECKBOX_STATE_EVENT_SELECTED",CHECKBOX_STATE_EVENT_SELECTED);
  tolua_constant(tolua_S,"CHECKBOX_STATE_EVENT_UNSELECTED",CHECKBOX_STATE_EVENT_UNSELECTED);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UICheckBox","UICheckBox","UIWidget",tolua_collect_UICheckBox);
  #else
  tolua_cclass(tolua_S,"UICheckBox","UICheckBox","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UICheckBox");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UICheckBox_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UICheckBox_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UICheckBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UICheckBox_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UICheckBox_create00);
   tolua_function(tolua_S,"loadTextures",tolua_CocoStudio_UICheckBox_loadTextures00);
   tolua_function(tolua_S,"loadTextureBackGround",tolua_CocoStudio_UICheckBox_loadTextureBackGround00);
   tolua_function(tolua_S,"loadTextureBackGroundSelected",tolua_CocoStudio_UICheckBox_loadTextureBackGroundSelected00);
   tolua_function(tolua_S,"loadTextureFrontCross",tolua_CocoStudio_UICheckBox_loadTextureFrontCross00);
   tolua_function(tolua_S,"loadTextureBackGroundDisabled",tolua_CocoStudio_UICheckBox_loadTextureBackGroundDisabled00);
   tolua_function(tolua_S,"loadTextureFrontCrossDisabled",tolua_CocoStudio_UICheckBox_loadTextureFrontCrossDisabled00);
   tolua_function(tolua_S,"setSelectedState",tolua_CocoStudio_UICheckBox_setSelectedState00);
   tolua_function(tolua_S,"getSelectedState",tolua_CocoStudio_UICheckBox_getSelectedState00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UICheckBox_setAnchorPoint00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_UICheckBox_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_UICheckBox_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_UICheckBox_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_UICheckBox_isFlipY00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UICheckBox_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UICheckBox_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UICheckBox_getDescription00);
   tolua_function(tolua_S,"setTextures",tolua_CocoStudio_UICheckBox_setTextures00);
   tolua_function(tolua_S,"setBackGroundTexture",tolua_CocoStudio_UICheckBox_setBackGroundTexture00);
   tolua_function(tolua_S,"setBackGroundSelectedTexture",tolua_CocoStudio_UICheckBox_setBackGroundSelectedTexture00);
   tolua_function(tolua_S,"setFrontCrossTexture",tolua_CocoStudio_UICheckBox_setFrontCrossTexture00);
   tolua_function(tolua_S,"setBackGroundDisabledTexture",tolua_CocoStudio_UICheckBox_setBackGroundDisabledTexture00);
   tolua_function(tolua_S,"setFrontCrossDisabledTexture",tolua_CocoStudio_UICheckBox_setFrontCrossDisabledTexture00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIImageView","UIImageView","UIWidget",tolua_collect_UIImageView);
  #else
  tolua_cclass(tolua_S,"UIImageView","UIImageView","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIImageView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIImageView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIImageView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIImageView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIImageView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIImageView_create00);
   tolua_function(tolua_S,"loadTexture",tolua_CocoStudio_UIImageView_loadTexture00);
   tolua_function(tolua_S,"setTextureRect",tolua_CocoStudio_UIImageView_setTextureRect00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_UIImageView_setScale9Enabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_UIImageView_setCapInsets00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_UIImageView_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_UIImageView_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_UIImageView_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_UIImageView_isFlipY00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UIImageView_setAnchorPoint00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_UIImageView_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIImageView_getDescription00);
   tolua_function(tolua_S,"setDoubleClickEnabled",tolua_CocoStudio_UIImageView_setDoubleClickEnabled00);
   tolua_function(tolua_S,"doubleClickEvent",tolua_CocoStudio_UIImageView_doubleClickEvent00);
   tolua_function(tolua_S,"checkDoubleClick",tolua_CocoStudio_UIImageView_checkDoubleClick00);
   tolua_function(tolua_S,"setTexture",tolua_CocoStudio_UIImageView_setTexture00);
   tolua_function(tolua_S,"setScale9Size",tolua_CocoStudio_UIImageView_setScale9Size00);
   tolua_function(tolua_S,"setScale9Enable",tolua_CocoStudio_UIImageView_setScale9Enable00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UIImageView_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UIImageView_getVirtualRenderer00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILabel","UILabel","UIWidget",tolua_collect_UILabel);
  #else
  tolua_cclass(tolua_S,"UILabel","UILabel","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILabel");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILabel_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILabel_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILabel_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILabel_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILabel_create00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_UILabel_setText00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_UILabel_getStringValue00);
   tolua_function(tolua_S,"getStringLength",tolua_CocoStudio_UILabel_getStringLength00);
   tolua_function(tolua_S,"setFontSize",tolua_CocoStudio_UILabel_setFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_CocoStudio_UILabel_setFontName00);
   tolua_function(tolua_S,"setTouchScaleChangeEnabled",tolua_CocoStudio_UILabel_setTouchScaleChangeEnabled00);
   tolua_function(tolua_S,"isTouchScaleChangeEnabled",tolua_CocoStudio_UILabel_isTouchScaleChangeEnabled00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_UILabel_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_UILabel_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_UILabel_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_UILabel_isFlipY00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UILabel_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UILabel_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UILabel_getVirtualRenderer00);
   tolua_function(tolua_S,"setScale",tolua_CocoStudio_UILabel_setScale00);
   tolua_function(tolua_S,"setScaleX",tolua_CocoStudio_UILabel_setScaleX00);
   tolua_function(tolua_S,"setScaleY",tolua_CocoStudio_UILabel_setScaleY00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UILabel_getDescription00);
   tolua_function(tolua_S,"setTextAreaSize",tolua_CocoStudio_UILabel_setTextAreaSize00);
   tolua_function(tolua_S,"setTextHorizontalAlignment",tolua_CocoStudio_UILabel_setTextHorizontalAlignment00);
   tolua_function(tolua_S,"setTextVerticalAlignment",tolua_CocoStudio_UILabel_setTextVerticalAlignment00);
   tolua_function(tolua_S,"setTouchScaleChangeAble",tolua_CocoStudio_UILabel_setTouchScaleChangeAble00);
   tolua_function(tolua_S,"getTouchScaleChangeAble",tolua_CocoStudio_UILabel_getTouchScaleChangeAble00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILabelAtlas","UILabelAtlas","UIWidget",tolua_collect_UILabelAtlas);
  #else
  tolua_cclass(tolua_S,"UILabelAtlas","UILabelAtlas","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILabelAtlas");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILabelAtlas_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILabelAtlas_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILabelAtlas_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILabelAtlas_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILabelAtlas_create00);
   tolua_function(tolua_S,"setProperty",tolua_CocoStudio_UILabelAtlas_setProperty00);
   tolua_function(tolua_S,"setStringValue",tolua_CocoStudio_UILabelAtlas_setStringValue00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_UILabelAtlas_getStringValue00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UILabelAtlas_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UILabelAtlas_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UILabelAtlas_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UILabelAtlas_getDescription00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILabelBMFont","UILabelBMFont","UIWidget",tolua_collect_UILabelBMFont);
  #else
  tolua_cclass(tolua_S,"UILabelBMFont","UILabelBMFont","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILabelBMFont");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILabelBMFont_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILabelBMFont_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILabelBMFont_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILabelBMFont_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILabelBMFont_create00);
   tolua_function(tolua_S,"setFntFile",tolua_CocoStudio_UILabelBMFont_setFntFile00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_UILabelBMFont_setText00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_UILabelBMFont_getStringValue00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UILabelBMFont_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UILabelBMFont_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UILabelBMFont_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UILabelBMFont_getDescription00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LoadingBarTypeLeft",LoadingBarTypeLeft);
  tolua_constant(tolua_S,"LoadingBarTypeRight",LoadingBarTypeRight);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILoadingBar","UILoadingBar","UIWidget",tolua_collect_UILoadingBar);
  #else
  tolua_cclass(tolua_S,"UILoadingBar","UILoadingBar","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILoadingBar");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILoadingBar_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILoadingBar_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILoadingBar_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILoadingBar_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILoadingBar_create00);
   tolua_function(tolua_S,"setDirection",tolua_CocoStudio_UILoadingBar_setDirection00);
   tolua_function(tolua_S,"getDirection",tolua_CocoStudio_UILoadingBar_getDirection00);
   tolua_function(tolua_S,"loadTexture",tolua_CocoStudio_UILoadingBar_loadTexture00);
   tolua_function(tolua_S,"setPercent",tolua_CocoStudio_UILoadingBar_setPercent00);
   tolua_function(tolua_S,"getPercent",tolua_CocoStudio_UILoadingBar_getPercent00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_UILoadingBar_setScale9Enabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_UILoadingBar_setCapInsets00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_UILoadingBar_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UILoadingBar_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UILoadingBar_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UILoadingBar_getDescription00);
   tolua_function(tolua_S,"setTexture",tolua_CocoStudio_UILoadingBar_setTexture00);
   tolua_function(tolua_S,"setScale9Size",tolua_CocoStudio_UILoadingBar_setScale9Size00);
   tolua_function(tolua_S,"setScale9Enable",tolua_CocoStudio_UILoadingBar_setScale9Enable00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"SLIDER_PERCENTCHANGED",SLIDER_PERCENTCHANGED);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UISlider","UISlider","UIWidget",tolua_collect_UISlider);
  #else
  tolua_cclass(tolua_S,"UISlider","UISlider","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UISlider");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UISlider_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UISlider_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UISlider_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UISlider_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UISlider_create00);
   tolua_function(tolua_S,"loadBarTexture",tolua_CocoStudio_UISlider_loadBarTexture00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_UISlider_setScale9Enabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_UISlider_setCapInsets00);
   tolua_function(tolua_S,"setCapInsetsBarRenderer",tolua_CocoStudio_UISlider_setCapInsetsBarRenderer00);
   tolua_function(tolua_S,"setCapInsetProgressBarRebderer",tolua_CocoStudio_UISlider_setCapInsetProgressBarRebderer00);
   tolua_function(tolua_S,"loadSlidBallTextures",tolua_CocoStudio_UISlider_loadSlidBallTextures00);
   tolua_function(tolua_S,"loadSlidBallTextureNormal",tolua_CocoStudio_UISlider_loadSlidBallTextureNormal00);
   tolua_function(tolua_S,"loadSlidBallTexturePressed",tolua_CocoStudio_UISlider_loadSlidBallTexturePressed00);
   tolua_function(tolua_S,"loadSlidBallTextureDisabled",tolua_CocoStudio_UISlider_loadSlidBallTextureDisabled00);
   tolua_function(tolua_S,"loadProgressBarTexture",tolua_CocoStudio_UISlider_loadProgressBarTexture00);
   tolua_function(tolua_S,"setPercent",tolua_CocoStudio_UISlider_setPercent00);
   tolua_function(tolua_S,"getPercent",tolua_CocoStudio_UISlider_getPercent00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UISlider_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UISlider_getVirtualRenderer00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_UISlider_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UISlider_getDescription00);
   tolua_function(tolua_S,"setBarTexture",tolua_CocoStudio_UISlider_setBarTexture00);
   tolua_function(tolua_S,"setSlidBallTextures",tolua_CocoStudio_UISlider_setSlidBallTextures00);
   tolua_function(tolua_S,"setSlidBallNormalTexture",tolua_CocoStudio_UISlider_setSlidBallNormalTexture00);
   tolua_function(tolua_S,"setSlidBallPressedTexture",tolua_CocoStudio_UISlider_setSlidBallPressedTexture00);
   tolua_function(tolua_S,"setSlidBallDisabledTexture",tolua_CocoStudio_UISlider_setSlidBallDisabledTexture00);
   tolua_function(tolua_S,"setProgressBarTexture",tolua_CocoStudio_UISlider_setProgressBarTexture00);
   tolua_function(tolua_S,"setSlidBallPercent",tolua_CocoStudio_UISlider_setSlidBallPercent00);
   tolua_function(tolua_S,"setScale9Size",tolua_CocoStudio_UISlider_setScale9Size00);
   tolua_function(tolua_S,"setScale9Enable",tolua_CocoStudio_UISlider_setScale9Enable00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_ATTACH_WITH_IME",TEXTFIELD_EVENT_ATTACH_WITH_IME);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_DETACH_WITH_IME",TEXTFIELD_EVENT_DETACH_WITH_IME);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_INSERT_TEXT",TEXTFIELD_EVENT_INSERT_TEXT);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_DELETE_BACKWARD",TEXTFIELD_EVENT_DELETE_BACKWARD);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UITextField","UITextField","UIWidget",tolua_collect_UITextField);
  #else
  tolua_cclass(tolua_S,"UITextField","UITextField","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UITextField");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UITextField_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UITextField_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UITextField_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UITextField_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UITextField_create00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_UITextField_init00);
   tolua_function(tolua_S,"initRenderer",tolua_CocoStudio_UITextField_initRenderer00);
   tolua_function(tolua_S,"setTouchSize",tolua_CocoStudio_UITextField_setTouchSize00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_UITextField_setText00);
   tolua_function(tolua_S,"setPlaceHolder",tolua_CocoStudio_UITextField_setPlaceHolder00);
   tolua_function(tolua_S,"setFontSize",tolua_CocoStudio_UITextField_setFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_CocoStudio_UITextField_setFontName00);
   tolua_function(tolua_S,"didNotSelectSelf",tolua_CocoStudio_UITextField_didNotSelectSelf00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_UITextField_getStringValue00);
   tolua_function(tolua_S,"onTouchBegan",tolua_CocoStudio_UITextField_onTouchBegan00);
   tolua_function(tolua_S,"setMaxLengthEnabled",tolua_CocoStudio_UITextField_setMaxLengthEnabled00);
   tolua_function(tolua_S,"isMaxLengthEnabled",tolua_CocoStudio_UITextField_isMaxLengthEnabled00);
   tolua_function(tolua_S,"setMaxLength",tolua_CocoStudio_UITextField_setMaxLength00);
   tolua_function(tolua_S,"getMaxLength",tolua_CocoStudio_UITextField_getMaxLength00);
   tolua_function(tolua_S,"setPasswordEnabled",tolua_CocoStudio_UITextField_setPasswordEnabled00);
   tolua_function(tolua_S,"isPasswordEnabled",tolua_CocoStudio_UITextField_isPasswordEnabled00);
   tolua_function(tolua_S,"setPasswordStyleText",tolua_CocoStudio_UITextField_setPasswordStyleText00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_UITextField_update00);
   tolua_function(tolua_S,"getAttachWithIME",tolua_CocoStudio_UITextField_getAttachWithIME00);
   tolua_function(tolua_S,"setAttachWithIME",tolua_CocoStudio_UITextField_setAttachWithIME00);
   tolua_function(tolua_S,"getDetachWithIME",tolua_CocoStudio_UITextField_getDetachWithIME00);
   tolua_function(tolua_S,"setDetachWithIME",tolua_CocoStudio_UITextField_setDetachWithIME00);
   tolua_function(tolua_S,"getInsertText",tolua_CocoStudio_UITextField_getInsertText00);
   tolua_function(tolua_S,"setInsertText",tolua_CocoStudio_UITextField_setInsertText00);
   tolua_function(tolua_S,"getDeleteBackward",tolua_CocoStudio_UITextField_getDeleteBackward00);
   tolua_function(tolua_S,"setDeleteBackward",tolua_CocoStudio_UITextField_setDeleteBackward00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_UITextField_setAnchorPoint00);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_UITextField_setColor00);
   tolua_function(tolua_S,"setOpacity",tolua_CocoStudio_UITextField_setOpacity00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UITextField_getDescription00);
   tolua_function(tolua_S,"setMaxLengthEnable",tolua_CocoStudio_UITextField_setMaxLengthEnable00);
   tolua_function(tolua_S,"setPasswordEnable",tolua_CocoStudio_UITextField_setPasswordEnable00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_UITextField_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_UITextField_getVirtualRenderer00);
   tolua_function(tolua_S,"attachWithIME",tolua_CocoStudio_UITextField_attachWithIME00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"SCROLLVIEW_DIR_NONE",SCROLLVIEW_DIR_NONE);
  tolua_constant(tolua_S,"SCROLLVIEW_DIR_VERTICAL",SCROLLVIEW_DIR_VERTICAL);
  tolua_constant(tolua_S,"SCROLLVIEW_DIR_HORIZONTAL",SCROLLVIEW_DIR_HORIZONTAL);
  tolua_constant(tolua_S,"SCROLLVIEW_DIR_BOTH",SCROLLVIEW_DIR_BOTH);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_SCROLL_TO_TOP",SCROLLVIEW_EVENT_SCROLL_TO_TOP);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM",SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_SCROLL_TO_LEFT",SCROLLVIEW_EVENT_SCROLL_TO_LEFT);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_SCROLL_TO_RIGHT",SCROLLVIEW_EVENT_SCROLL_TO_RIGHT);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_SCROLLING",SCROLLVIEW_EVENT_SCROLLING);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_BOUNCE_TOP",SCROLLVIEW_EVENT_BOUNCE_TOP);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_BOUNCE_BOTTOM",SCROLLVIEW_EVENT_BOUNCE_BOTTOM);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_BOUNCE_LEFT",SCROLLVIEW_EVENT_BOUNCE_LEFT);
  tolua_constant(tolua_S,"SCROLLVIEW_EVENT_BOUNCE_RIGHT",SCROLLVIEW_EVENT_BOUNCE_RIGHT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIScrollView","UIScrollView","UILayout",tolua_collect_UIScrollView);
  #else
  tolua_cclass(tolua_S,"UIScrollView","UIScrollView","UILayout",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIScrollView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIScrollView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIScrollView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIScrollView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIScrollView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIScrollView_create00);
   tolua_function(tolua_S,"setDirection",tolua_CocoStudio_UIScrollView_setDirection00);
   tolua_function(tolua_S,"getDirection",tolua_CocoStudio_UIScrollView_getDirection00);
   tolua_function(tolua_S,"getInnerContainer",tolua_CocoStudio_UIScrollView_getInnerContainer00);
   tolua_function(tolua_S,"scrollToBottom",tolua_CocoStudio_UIScrollView_scrollToBottom00);
   tolua_function(tolua_S,"scrollToTop",tolua_CocoStudio_UIScrollView_scrollToTop00);
   tolua_function(tolua_S,"scrollToLeft",tolua_CocoStudio_UIScrollView_scrollToLeft00);
   tolua_function(tolua_S,"scrollToRight",tolua_CocoStudio_UIScrollView_scrollToRight00);
   tolua_function(tolua_S,"scrollToTopLeft",tolua_CocoStudio_UIScrollView_scrollToTopLeft00);
   tolua_function(tolua_S,"scrollToTopRight",tolua_CocoStudio_UIScrollView_scrollToTopRight00);
   tolua_function(tolua_S,"scrollToBottomLeft",tolua_CocoStudio_UIScrollView_scrollToBottomLeft00);
   tolua_function(tolua_S,"scrollToBottomRight",tolua_CocoStudio_UIScrollView_scrollToBottomRight00);
   tolua_function(tolua_S,"scrollToPercentVertical",tolua_CocoStudio_UIScrollView_scrollToPercentVertical00);
   tolua_function(tolua_S,"scrollToPercentHorizontal",tolua_CocoStudio_UIScrollView_scrollToPercentHorizontal00);
   tolua_function(tolua_S,"scrollToPercentBothDirection",tolua_CocoStudio_UIScrollView_scrollToPercentBothDirection00);
   tolua_function(tolua_S,"jumpToBottom",tolua_CocoStudio_UIScrollView_jumpToBottom00);
   tolua_function(tolua_S,"jumpToTop",tolua_CocoStudio_UIScrollView_jumpToTop00);
   tolua_function(tolua_S,"jumpToLeft",tolua_CocoStudio_UIScrollView_jumpToLeft00);
   tolua_function(tolua_S,"jumpToRight",tolua_CocoStudio_UIScrollView_jumpToRight00);
   tolua_function(tolua_S,"jumpToTopLeft",tolua_CocoStudio_UIScrollView_jumpToTopLeft00);
   tolua_function(tolua_S,"jumpToTopRight",tolua_CocoStudio_UIScrollView_jumpToTopRight00);
   tolua_function(tolua_S,"jumpToBottomLeft",tolua_CocoStudio_UIScrollView_jumpToBottomLeft00);
   tolua_function(tolua_S,"jumpToBottomRight",tolua_CocoStudio_UIScrollView_jumpToBottomRight00);
   tolua_function(tolua_S,"jumpToPercentVertical",tolua_CocoStudio_UIScrollView_jumpToPercentVertical00);
   tolua_function(tolua_S,"jumpToPercentHorizontal",tolua_CocoStudio_UIScrollView_jumpToPercentHorizontal00);
   tolua_function(tolua_S,"jumpToPercentBothDirection",tolua_CocoStudio_UIScrollView_jumpToPercentBothDirection00);
   tolua_function(tolua_S,"setInnerContainerSize",tolua_CocoStudio_UIScrollView_setInnerContainerSize00);
   tolua_function(tolua_S,"getInnerContainerSize",tolua_CocoStudio_UIScrollView_getInnerContainerSize00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_UIScrollView_addChild00);
   tolua_function(tolua_S,"removeAllChildren",tolua_CocoStudio_UIScrollView_removeAllChildren00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_UIScrollView_removeChild00);
   tolua_function(tolua_S,"getChildren",tolua_CocoStudio_UIScrollView_getChildren00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_UIScrollView_update00);
   tolua_function(tolua_S,"setBounceEnabled",tolua_CocoStudio_UIScrollView_setBounceEnabled00);
   tolua_function(tolua_S,"isBounceEnabled",tolua_CocoStudio_UIScrollView_isBounceEnabled00);
   tolua_function(tolua_S,"setInertiaScrollEnabled",tolua_CocoStudio_UIScrollView_setInertiaScrollEnabled00);
   tolua_function(tolua_S,"isInertiaScrollEnabled",tolua_CocoStudio_UIScrollView_isInertiaScrollEnabled00);
   tolua_function(tolua_S,"setLayoutType",tolua_CocoStudio_UIScrollView_setLayoutType00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_UIScrollView_getLayoutType00);
   tolua_function(tolua_S,"doLayout",tolua_CocoStudio_UIScrollView_doLayout00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIScrollView_getDescription00);
   tolua_variable(tolua_S,"__UIScrollInterface__",tolua_get_UIScrollView___UIScrollInterface__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"PAGEVIEW_EVENT_TURNING",PAGEVIEW_EVENT_TURNING);
  tolua_constant(tolua_S,"PAGEVIEW_TOUCHLEFT",PAGEVIEW_TOUCHLEFT);
  tolua_constant(tolua_S,"PAGEVIEW_TOUCHRIGHT",PAGEVIEW_TOUCHRIGHT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIPageView","UIPageView","UILayout",tolua_collect_UIPageView);
  #else
  tolua_cclass(tolua_S,"UIPageView","UIPageView","UILayout",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIPageView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIPageView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIPageView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIPageView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIPageView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIPageView_create00);
   tolua_function(tolua_S,"addWidgetToPage",tolua_CocoStudio_UIPageView_addWidgetToPage00);
   tolua_function(tolua_S,"addPage",tolua_CocoStudio_UIPageView_addPage00);
   tolua_function(tolua_S,"insertPage",tolua_CocoStudio_UIPageView_insertPage00);
   tolua_function(tolua_S,"removePage",tolua_CocoStudio_UIPageView_removePage00);
   tolua_function(tolua_S,"removePageAtIndex",tolua_CocoStudio_UIPageView_removePageAtIndex00);
   tolua_function(tolua_S,"removeAllPages",tolua_CocoStudio_UIPageView_removeAllPages00);
   tolua_function(tolua_S,"scrollToPage",tolua_CocoStudio_UIPageView_scrollToPage00);
   tolua_function(tolua_S,"getCurPageIndex",tolua_CocoStudio_UIPageView_getCurPageIndex00);
   tolua_function(tolua_S,"getPages",tolua_CocoStudio_UIPageView_getPages00);
   tolua_function(tolua_S,"getPage",tolua_CocoStudio_UIPageView_getPage00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_UIPageView_update00);
   tolua_function(tolua_S,"doLayout",tolua_CocoStudio_UIPageView_doLayout00);
   tolua_function(tolua_S,"setLayoutType",tolua_CocoStudio_UIPageView_setLayoutType00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_UIPageView_getLayoutType00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIPageView_getDescription00);
   tolua_function(tolua_S,"getPage",tolua_CocoStudio_UIPageView_getPage01);
   tolua_function(tolua_S,"removePage",tolua_CocoStudio_UIPageView_removePage01);
   tolua_function(tolua_S,"removePageAtIndex",tolua_CocoStudio_UIPageView_removePageAtIndex01);
   tolua_variable(tolua_S,"__UIScrollInterface__",tolua_get_UIPageView___UIScrollInterface__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LISTVIEW_DIR_NONE",LISTVIEW_DIR_NONE);
  tolua_constant(tolua_S,"LISTVIEW_DIR_VERTICAL",LISTVIEW_DIR_VERTICAL);
  tolua_constant(tolua_S,"LISTVIEW_DIR_HORIZONTAL",LISTVIEW_DIR_HORIZONTAL);
  tolua_constant(tolua_S,"LISTVIEW_MOVE_DIR_NONE",LISTVIEW_MOVE_DIR_NONE);
  tolua_constant(tolua_S,"LISTVIEW_MOVE_DIR_UP",LISTVIEW_MOVE_DIR_UP);
  tolua_constant(tolua_S,"LISTVIEW_MOVE_DIR_DOWN",LISTVIEW_MOVE_DIR_DOWN);
  tolua_constant(tolua_S,"LISTVIEW_MOVE_DIR_LEFT",LISTVIEW_MOVE_DIR_LEFT);
  tolua_constant(tolua_S,"LISTVIEW_MOVE_DIR_RIGHT",LISTVIEW_MOVE_DIR_RIGHT);
  tolua_constant(tolua_S,"LISTVIEW_EVENT_INIT_CHILD",LISTVIEW_EVENT_INIT_CHILD);
  tolua_constant(tolua_S,"LISTVIEW_EVENT_UPDATE_CHILD",LISTVIEW_EVENT_UPDATE_CHILD);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIListView","UIListView","UILayout",tolua_collect_UIListView);
  #else
  tolua_cclass(tolua_S,"UIListView","UIListView","UILayout",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIListView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIListView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIListView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIListView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIListView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIListView_create00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_UIListView_addChild00);
   tolua_function(tolua_S,"removeAllChildren",tolua_CocoStudio_UIListView_removeAllChildren00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_UIListView_removeChild00);
   tolua_function(tolua_S,"setDirection",tolua_CocoStudio_UIListView_setDirection00);
   tolua_function(tolua_S,"getDirection",tolua_CocoStudio_UIListView_getDirection00);
   tolua_function(tolua_S,"initChildWithDataLength",tolua_CocoStudio_UIListView_initChildWithDataLength00);
   tolua_function(tolua_S,"getDataLength",tolua_CocoStudio_UIListView_getDataLength00);
   tolua_function(tolua_S,"getUpdateChild",tolua_CocoStudio_UIListView_getUpdateChild00);
   tolua_function(tolua_S,"getUpdateDataIndex",tolua_CocoStudio_UIListView_getUpdateDataIndex00);
   tolua_function(tolua_S,"getUpdateSuccess",tolua_CocoStudio_UIListView_getUpdateSuccess00);
   tolua_function(tolua_S,"setUpdateSuccess",tolua_CocoStudio_UIListView_setUpdateSuccess00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_UIListView_update00);
   tolua_function(tolua_S,"doLayout",tolua_CocoStudio_UIListView_doLayout00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIListView_getDescription00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LAYOUT_PARAMETER_NONE",LAYOUT_PARAMETER_NONE);
  tolua_constant(tolua_S,"LAYOUT_PARAMETER_LINEAR",LAYOUT_PARAMETER_LINEAR);
  tolua_constant(tolua_S,"LAYOUT_PARAMETER_RELATIVE",LAYOUT_PARAMETER_RELATIVE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILayoutParameter","UILayoutParameter","CCObject",tolua_collect_UILayoutParameter);
  #else
  tolua_cclass(tolua_S,"UILayoutParameter","UILayoutParameter","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILayoutParameter");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILayoutParameter_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILayoutParameter_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILayoutParameter_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILayoutParameter_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILayoutParameter_create00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_UILayoutParameter_getLayoutType00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UILinearLayoutParameter","UILinearLayoutParameter","UILayoutParameter",tolua_collect_UILinearLayoutParameter);
  #else
  tolua_cclass(tolua_S,"UILinearLayoutParameter","UILinearLayoutParameter","UILayoutParameter",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UILinearLayoutParameter");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UILinearLayoutParameter_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UILinearLayoutParameter_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UILinearLayoutParameter_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UILinearLayoutParameter_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UILinearLayoutParameter_create00);
   tolua_function(tolua_S,"setGravity",tolua_CocoStudio_UILinearLayoutParameter_setGravity00);
   tolua_function(tolua_S,"getGravity",tolua_CocoStudio_UILinearLayoutParameter_getGravity00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIRelativeLayoutParameter","UIRelativeLayoutParameter","UILayoutParameter",tolua_collect_UIRelativeLayoutParameter);
  #else
  tolua_cclass(tolua_S,"UIRelativeLayoutParameter","UIRelativeLayoutParameter","UILayoutParameter",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIRelativeLayoutParameter");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIRelativeLayoutParameter_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIRelativeLayoutParameter_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIRelativeLayoutParameter_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIRelativeLayoutParameter_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIRelativeLayoutParameter_create00);
   tolua_function(tolua_S,"setAlign",tolua_CocoStudio_UIRelativeLayoutParameter_setAlign00);
   tolua_function(tolua_S,"getAlign",tolua_CocoStudio_UIRelativeLayoutParameter_getAlign00);
   tolua_function(tolua_S,"setRelativeToWidgetName",tolua_CocoStudio_UIRelativeLayoutParameter_setRelativeToWidgetName00);
   tolua_function(tolua_S,"getRelativeToWidgetName",tolua_CocoStudio_UIRelativeLayoutParameter_getRelativeToWidgetName00);
   tolua_function(tolua_S,"setRelativeName",tolua_CocoStudio_UIRelativeLayoutParameter_setRelativeName00);
   tolua_function(tolua_S,"getRelativeName",tolua_CocoStudio_UIRelativeLayoutParameter_getRelativeName00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCComController","CCComController","CCComponent",tolua_collect_CCComController);
  #else
  tolua_cclass(tolua_S,"CCComController","CCComController","CCComponent",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCComController");
   tolua_function(tolua_S,"new",tolua_CocoStudio_CCComController_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CCComController_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CCComController_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CCComController_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCComController_init00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_CCComController_update00);
   tolua_function(tolua_S,"isEnabled",tolua_CocoStudio_CCComController_isEnabled00);
   tolua_function(tolua_S,"setEnabled",tolua_CocoStudio_CCComController_setEnabled00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCComController_create00);
   tolua_variable(tolua_S,"__CCInputDelegate__",tolua_get_CCComController___CCInputDelegate__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCComAudio","CCComAudio","CCComponent",NULL);
  tolua_beginmodule(tolua_S,"CCComAudio");
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCComAudio_init00);
   tolua_function(tolua_S,"isEnabled",tolua_CocoStudio_CCComAudio_isEnabled00);
   tolua_function(tolua_S,"setEnabled",tolua_CocoStudio_CCComAudio_setEnabled00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCComAudio_create00);
   tolua_function(tolua_S,"end",tolua_CocoStudio_CCComAudio_end00);
   tolua_function(tolua_S,"preloadBackgroundMusic",tolua_CocoStudio_CCComAudio_preloadBackgroundMusic00);
   tolua_function(tolua_S,"playBackgroundMusic",tolua_CocoStudio_CCComAudio_playBackgroundMusic00);
   tolua_function(tolua_S,"playBackgroundMusic",tolua_CocoStudio_CCComAudio_playBackgroundMusic01);
   tolua_function(tolua_S,"stopBackgroundMusic",tolua_CocoStudio_CCComAudio_stopBackgroundMusic00);
   tolua_function(tolua_S,"stopBackgroundMusic",tolua_CocoStudio_CCComAudio_stopBackgroundMusic01);
   tolua_function(tolua_S,"pauseBackgroundMusic",tolua_CocoStudio_CCComAudio_pauseBackgroundMusic00);
   tolua_function(tolua_S,"resumeBackgroundMusic",tolua_CocoStudio_CCComAudio_resumeBackgroundMusic00);
   tolua_function(tolua_S,"rewindBackgroundMusic",tolua_CocoStudio_CCComAudio_rewindBackgroundMusic00);
   tolua_function(tolua_S,"willPlayBackgroundMusic",tolua_CocoStudio_CCComAudio_willPlayBackgroundMusic00);
   tolua_function(tolua_S,"isBackgroundMusicPlaying",tolua_CocoStudio_CCComAudio_isBackgroundMusicPlaying00);
   tolua_function(tolua_S,"getBackgroundMusicVolume",tolua_CocoStudio_CCComAudio_getBackgroundMusicVolume00);
   tolua_function(tolua_S,"setBackgroundMusicVolume",tolua_CocoStudio_CCComAudio_setBackgroundMusicVolume00);
   tolua_function(tolua_S,"getEffectsVolume",tolua_CocoStudio_CCComAudio_getEffectsVolume00);
   tolua_function(tolua_S,"setEffectsVolume",tolua_CocoStudio_CCComAudio_setEffectsVolume00);
   tolua_function(tolua_S,"playEffect",tolua_CocoStudio_CCComAudio_playEffect00);
   tolua_function(tolua_S,"playEffect",tolua_CocoStudio_CCComAudio_playEffect01);
   tolua_function(tolua_S,"pauseEffect",tolua_CocoStudio_CCComAudio_pauseEffect00);
   tolua_function(tolua_S,"pauseAllEffects",tolua_CocoStudio_CCComAudio_pauseAllEffects00);
   tolua_function(tolua_S,"resumeEffect",tolua_CocoStudio_CCComAudio_resumeEffect00);
   tolua_function(tolua_S,"resumeAllEffects",tolua_CocoStudio_CCComAudio_resumeAllEffects00);
   tolua_function(tolua_S,"stopEffect",tolua_CocoStudio_CCComAudio_stopEffect00);
   tolua_function(tolua_S,"stopAllEffects",tolua_CocoStudio_CCComAudio_stopAllEffects00);
   tolua_function(tolua_S,"preloadEffect",tolua_CocoStudio_CCComAudio_preloadEffect00);
   tolua_function(tolua_S,"unloadEffect",tolua_CocoStudio_CCComAudio_unloadEffect00);
   tolua_function(tolua_S,"setFile",tolua_CocoStudio_CCComAudio_setFile00);
   tolua_function(tolua_S,"getFile",tolua_CocoStudio_CCComAudio_getFile00);
   tolua_function(tolua_S,"setLoop",tolua_CocoStudio_CCComAudio_setLoop00);
   tolua_function(tolua_S,"isLoop",tolua_CocoStudio_CCComAudio_isLoop00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCComAttribute","CCComAttribute","CCComponent",NULL);
  tolua_beginmodule(tolua_S,"CCComAttribute");
   tolua_function(tolua_S,"init",tolua_CocoStudio_CCComAttribute_init00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCComAttribute_create00);
   tolua_function(tolua_S,"setInt",tolua_CocoStudio_CCComAttribute_setInt00);
   tolua_function(tolua_S,"setFloat",tolua_CocoStudio_CCComAttribute_setFloat00);
   tolua_function(tolua_S,"setBool",tolua_CocoStudio_CCComAttribute_setBool00);
   tolua_function(tolua_S,"setCString",tolua_CocoStudio_CCComAttribute_setCString00);
   tolua_function(tolua_S,"getInt",tolua_CocoStudio_CCComAttribute_getInt00);
   tolua_function(tolua_S,"getFloat",tolua_CocoStudio_CCComAttribute_getFloat00);
   tolua_function(tolua_S,"getBool",tolua_CocoStudio_CCComAttribute_getBool00);
   tolua_function(tolua_S,"getCString",tolua_CocoStudio_CCComAttribute_getCString00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCComRender","CCComRender","CCComponent",NULL);
  tolua_beginmodule(tolua_S,"CCComRender");
   tolua_function(tolua_S,"getNode",tolua_CocoStudio_CCComRender_getNode00);
   tolua_function(tolua_S,"setNode",tolua_CocoStudio_CCComRender_setNode00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CCComRender_create00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ActionManager","ActionManager","CCObject",tolua_collect_ActionManager);
  #else
  tolua_cclass(tolua_S,"ActionManager","ActionManager","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ActionManager");
   tolua_function(tolua_S,"new",tolua_CocoStudio_ActionManager_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_ActionManager_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_ActionManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ActionManager_delete00);
   tolua_function(tolua_S,"shareManager",tolua_CocoStudio_ActionManager_shareManager00);
   tolua_function(tolua_S,"purgeActionManager",tolua_CocoStudio_ActionManager_purgeActionManager00);
   tolua_function(tolua_S,"getActionByName",tolua_CocoStudio_ActionManager_getActionByName00);
   tolua_function(tolua_S,"playActionByName",tolua_CocoStudio_ActionManager_playActionByName00);
   tolua_function(tolua_S,"releaseActions",tolua_CocoStudio_ActionManager_releaseActions00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SceneReader","SceneReader","",tolua_collect_SceneReader);
  #else
  tolua_cclass(tolua_S,"SceneReader","SceneReader","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SceneReader");
   tolua_function(tolua_S,"new",tolua_CocoStudio_SceneReader_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_SceneReader_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_SceneReader_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_SceneReader_delete00);
   tolua_function(tolua_S,"sharedSceneReader",tolua_CocoStudio_SceneReader_sharedSceneReader00);
   tolua_function(tolua_S,"purgeSceneReader",tolua_CocoStudio_SceneReader_purgeSceneReader00);
   tolua_function(tolua_S,"sceneReaderVersion",tolua_CocoStudio_SceneReader_sceneReaderVersion00);
   tolua_function(tolua_S,"createNodeWithSceneFile",tolua_CocoStudio_SceneReader_createNodeWithSceneFile00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GUIReader","GUIReader","CCObject",tolua_collect_GUIReader);
  #else
  tolua_cclass(tolua_S,"GUIReader","GUIReader","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GUIReader");
   tolua_function(tolua_S,"new",tolua_CocoStudio_GUIReader_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_GUIReader_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_GUIReader_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_GUIReader_delete00);
   tolua_function(tolua_S,"shareReader",tolua_CocoStudio_GUIReader_shareReader00);
   tolua_function(tolua_S,"purgeGUIReader",tolua_CocoStudio_GUIReader_purgeGUIReader00);
   tolua_function(tolua_S,"widgetFromJsonFile",tolua_CocoStudio_GUIReader_widgetFromJsonFile00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIRootWidget","UIRootWidget","UILayout",tolua_collect_UIRootWidget);
  #else
  tolua_cclass(tolua_S,"UIRootWidget","UIRootWidget","UILayout",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIRootWidget");
   tolua_function(tolua_S,"new",tolua_CocoStudio_UIRootWidget_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_UIRootWidget_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_UIRootWidget_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_UIRootWidget_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_UIRootWidget_create00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_UIRootWidget_getDescription00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ActionObject","ActionObject","CCObject",tolua_collect_ActionObject);
  #else
  tolua_cclass(tolua_S,"ActionObject","ActionObject","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ActionObject");
   tolua_function(tolua_S,"new",tolua_CocoStudio_ActionObject_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_ActionObject_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_ActionObject_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ActionObject_delete00);
   tolua_function(tolua_S,"setName",tolua_CocoStudio_ActionObject_setName00);
   tolua_function(tolua_S,"getName",tolua_CocoStudio_ActionObject_getName00);
   tolua_function(tolua_S,"setLoop",tolua_CocoStudio_ActionObject_setLoop00);
   tolua_function(tolua_S,"getLoop",tolua_CocoStudio_ActionObject_getLoop00);
   tolua_function(tolua_S,"setUnitTime",tolua_CocoStudio_ActionObject_setUnitTime00);
   tolua_function(tolua_S,"getUnitTime",tolua_CocoStudio_ActionObject_getUnitTime00);
   tolua_function(tolua_S,"setCurrentTime",tolua_CocoStudio_ActionObject_setCurrentTime00);
   tolua_function(tolua_S,"getCurrentTime",tolua_CocoStudio_ActionObject_getCurrentTime00);
   tolua_function(tolua_S,"isPlaying",tolua_CocoStudio_ActionObject_isPlaying00);
   tolua_function(tolua_S,"play",tolua_CocoStudio_ActionObject_play00);
   tolua_function(tolua_S,"pause",tolua_CocoStudio_ActionObject_pause00);
   tolua_function(tolua_S,"stop",tolua_CocoStudio_ActionObject_stop00);
   tolua_function(tolua_S,"addActionNode",tolua_CocoStudio_ActionObject_addActionNode00);
   tolua_function(tolua_S,"removeActionNode",tolua_CocoStudio_ActionObject_removeActionNode00);
   tolua_function(tolua_S,"updateToFrameByTime",tolua_CocoStudio_ActionObject_updateToFrameByTime00);
   tolua_function(tolua_S,"initWithDictionary",tolua_CocoStudio_ActionObject_initWithDictionary00);
   tolua_function(tolua_S,"simulationActionUpdate",tolua_CocoStudio_ActionObject_simulationActionUpdate00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CocoStudio (lua_State* tolua_S) {
 return tolua_CocoStudio_open(tolua_S);
};
#endif

