/*
** Lua binding: CocoStudio
** Generated automatically by tolua++-1.0.92 on Wed Jun 18 16:00:33 2014.
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
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace CocosDenshion;



#include "LuaCocoStudio.h"

/* function to release collected object via destructor */
#ifdef __cplusplus



static int tolua_collect_Label (lua_State* tolua_S)
{
 Label* self = (Label*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_LabelAtlas (lua_State* tolua_S)
{
 LabelAtlas* self = (LabelAtlas*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ListView (lua_State* tolua_S)
{
 ListView* self = (ListView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_PageView (lua_State* tolua_S)
{
 PageView* self = (PageView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCComController (lua_State* tolua_S)
{
 CCComController* self = (CCComController*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_ImageView (lua_State* tolua_S)
{
 ImageView* self = (ImageView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ActionTimelineCache (lua_State* tolua_S)
{
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CheckBox (lua_State* tolua_S)
{
 CheckBox* self = (CheckBox*) tolua_tousertype(tolua_S,1,0);
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

static int tolua_collect_Widget (lua_State* tolua_S)
{
 Widget* self = (Widget*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_NodeReader (lua_State* tolua_S)
{
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GUIReader (lua_State* tolua_S)
{
 GUIReader* self = (GUIReader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_LayoutParameter (lua_State* tolua_S)
{
 LayoutParameter* self = (LayoutParameter*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_RichText (lua_State* tolua_S)
{
 RichText* self = (RichText*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_RichElementCustomNode (lua_State* tolua_S)
{
 RichElementCustomNode* self = (RichElementCustomNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ActionManager (lua_State* tolua_S)
{
 ActionManager* self = (ActionManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_RichElementImage (lua_State* tolua_S)
{
 RichElementImage* self = (RichElementImage*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_RichElementText (lua_State* tolua_S)
{
 RichElementText* self = (RichElementText*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_RichElement (lua_State* tolua_S)
{
 RichElement* self = (RichElement*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ActionObject (lua_State* tolua_S)
{
 ActionObject* self = (ActionObject*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ActionTimeline (lua_State* tolua_S)
{
    cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SceneReader (lua_State* tolua_S)
{
 SceneReader* self = (SceneReader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCBone (lua_State* tolua_S)
{
 CCBone* self = (CCBone*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_UIRelativeLayoutParameter (lua_State* tolua_S)
{
 UIRelativeLayoutParameter* self = (UIRelativeLayoutParameter*) tolua_tousertype(tolua_S,1,0);
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

static int tolua_collect_ScrollView (lua_State* tolua_S)
{
 ScrollView* self = (ScrollView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_LinearLayoutParameter (lua_State* tolua_S)
{
 LinearLayoutParameter* self = (LinearLayoutParameter*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_CCArmatureAnimation (lua_State* tolua_S)
{
 CCArmatureAnimation* self = (CCArmatureAnimation*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_TextField (lua_State* tolua_S)
{
 TextField* self = (TextField*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_Button (lua_State* tolua_S)
{
 Button* self = (Button*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Timeline (lua_State* tolua_S)
{
 Timeline* self = (Timeline*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_LabelBMFont (lua_State* tolua_S)
{
 LabelBMFont* self = (LabelBMFont*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_LoadingBar (lua_State* tolua_S)
{
 LoadingBar* self = (LoadingBar*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}



static int tolua_collect_TouchGroup (lua_State* tolua_S)
{
 TouchGroup* self = (TouchGroup*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Layout (lua_State* tolua_S)
{
 Layout* self = (Layout*) tolua_tousertype(tolua_S,1,0);
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

static int tolua_collect_Slider (lua_State* tolua_S)
{
 Slider* self = (Slider*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"UILayoutParameter");
 tolua_usertype(tolua_S,"ListView");
 tolua_usertype(tolua_S,"cocos2d::CCArray");
 tolua_usertype(tolua_S,"PageView");
 tolua_usertype(tolua_S,"CCComController");
 tolua_usertype(tolua_S,"ActionTimelineCache");
 tolua_usertype(tolua_S,"CheckBox");
 tolua_usertype(tolua_S,"CCArmatureData");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"RichElementCustomNode");
 tolua_usertype(tolua_S,"LayoutParameter");
 tolua_usertype(tolua_S,"LabelBMFont");
 tolua_usertype(tolua_S,"CCComAudio");
 tolua_usertype(tolua_S,"CCTextureAtlas");
 tolua_usertype(tolua_S,"CCAnimationData");
 tolua_usertype(tolua_S,"ActionTimeline");
 tolua_usertype(tolua_S,"Button");
 tolua_usertype(tolua_S,"CCAction");
 tolua_usertype(tolua_S,"LinearLayoutParameter");
 tolua_usertype(tolua_S,"CCAffineTransform");
 tolua_usertype(tolua_S,"cocos2d::CCNode");
 tolua_usertype(tolua_S,"ccBlendFunc");
 tolua_usertype(tolua_S,"CCComRender");
 tolua_usertype(tolua_S,"LoadingBar");
 tolua_usertype(tolua_S,"CCComponent");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCMovementBoneData");
 tolua_usertype(tolua_S,"CCBatchNode");
 tolua_usertype(tolua_S,"Widget");
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"Label");
 tolua_usertype(tolua_S,"UIRelativeLayoutParameter");
 tolua_usertype(tolua_S,"ActionObject");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCNodeRGBA");
 tolua_usertype(tolua_S,"ImageView");
 tolua_usertype(tolua_S,"Frame");
 tolua_usertype(tolua_S,"CCBlendProtocol");
 tolua_usertype(tolua_S,"Timeline");
 tolua_usertype(tolua_S,"NodeReader");
 tolua_usertype(tolua_S,"CCTween");
 tolua_usertype(tolua_S,"CCBaseData");
 tolua_usertype(tolua_S,"RichText");
 tolua_usertype(tolua_S,"CCArmatureDataManager");
 tolua_usertype(tolua_S,"RichElementImage");
 tolua_usertype(tolua_S,"RichElementText");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"ScrollView");
 tolua_usertype(tolua_S,"DisplayType");
 tolua_usertype(tolua_S,"UIRelativeAlign");
 tolua_usertype(tolua_S,"SceneReader");
 tolua_usertype(tolua_S,"ActionManager");
 tolua_usertype(tolua_S,"GUIReader");
 tolua_usertype(tolua_S,"ActionNode");
 tolua_usertype(tolua_S,"CCComAttribute");
 tolua_usertype(tolua_S,"CCTexture2D");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"TextField");
 tolua_usertype(tolua_S,"Layout");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"LabelAtlas");
 tolua_usertype(tolua_S,"CCBone");
 tolua_usertype(tolua_S,"CCSkin");
 tolua_usertype(tolua_S,"CCArmature");
 tolua_usertype(tolua_S,"CCArray");
 tolua_usertype(tolua_S,"ccColor4B");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"rapidjson::Value");
 tolua_usertype(tolua_S,"CCArmatureAnimation");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"CCProcessBase");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"UIHelper");
 tolua_usertype(tolua_S,"UIScrollInterface");
 tolua_usertype(tolua_S,"RichElement");
 tolua_usertype(tolua_S,"TouchGroup");
 tolua_usertype(tolua_S,"CCDisplayData");
 tolua_usertype(tolua_S,"CCInputDelegate");
 tolua_usertype(tolua_S,"CCDisplayManager");
 tolua_usertype(tolua_S,"Slider");
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
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDictionary");
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

/* method: playWithIndex of class  CCArmatureAnimation */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCArmatureAnimation_playWithIndex00
static int tolua_CocoStudio_CCArmatureAnimation_playWithIndex00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playWithIndex'", NULL);
#endif
  {
   self->playWithIndex(animationIndex,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playWithIndex'.",&tolua_err);
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

/* method: changeDisplayWithIndex of class  CCBone */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCBone_changeDisplayWithIndex00
static int tolua_CocoStudio_CCBone_changeDisplayWithIndex00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeDisplayWithIndex'", NULL);
#endif
  {
   self->changeDisplayWithIndex(index,force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeDisplayWithIndex'.",&tolua_err);
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
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  GLubyte parentOpacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,2,0));
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
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBone* self = (CCBone*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,2,0));
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
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
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

/* method: changeDisplayWithIndex of class  CCDisplayManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCDisplayManager_changeDisplayWithIndex00
static int tolua_CocoStudio_CCDisplayManager_changeDisplayWithIndex00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeDisplayWithIndex'", NULL);
#endif
  {
   self->changeDisplayWithIndex(index,force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeDisplayWithIndex'.",&tolua_err);
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
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* root = ((Widget*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Widget* tolua_ret = (Widget*)  UIHelper::seekWidgetByTag(root,tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* root = ((Widget*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   Widget* tolua_ret = (Widget*)  UIHelper::seekWidgetByName(root,name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* root = ((Widget*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   Widget* tolua_ret = (Widget*)  UIHelper::seekWidgetByRelativeName(root,name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* root = ((Widget*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   Widget* tolua_ret = (Widget*)  UIHelper::seekActionWidgetByActionTag(root,tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: new of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_new00
static int tolua_CocoStudio_Widget_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Widget* tolua_ret = (Widget*)  Mtolua_new((Widget)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: new_local of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_new00_local
static int tolua_CocoStudio_Widget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Widget* tolua_ret = (Widget*)  Mtolua_new((Widget)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: delete of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_delete00
static int tolua_CocoStudio_Widget_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_create00
static int tolua_CocoStudio_Widget_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Widget* tolua_ret = (Widget*)  Widget::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: setEnabled of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setEnabled00
static int tolua_CocoStudio_Widget_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isEnabled of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isEnabled00
static int tolua_CocoStudio_Widget_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setBright of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setBright00
static int tolua_CocoStudio_Widget_setBright00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isBright of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isBright00
static int tolua_CocoStudio_Widget_isBright00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTouchEnabled of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setTouchEnabled00
static int tolua_CocoStudio_Widget_setTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setBrightStyle of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setBrightStyle00
static int tolua_CocoStudio_Widget_setBrightStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isTouchEnabled of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isTouchEnabled00
static int tolua_CocoStudio_Widget_isTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isFocused of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isFocused00
static int tolua_CocoStudio_Widget_isFocused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFocused of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setFocused00
static int tolua_CocoStudio_Widget_setFocused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getLeftInParent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getLeftInParent00
static int tolua_CocoStudio_Widget_getLeftInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getBottomInParent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getBottomInParent00
static int tolua_CocoStudio_Widget_getBottomInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getRightInParent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getRightInParent00
static int tolua_CocoStudio_Widget_getRightInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTopInParent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getTopInParent00
static int tolua_CocoStudio_Widget_getTopInParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addChild of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_addChild00
static int tolua_CocoStudio_Widget_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
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

/* method: addChild of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_addChild01
static int tolua_CocoStudio_Widget_addChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Widget_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_addChild02
static int tolua_CocoStudio_Widget_addChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Widget_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByTag of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getChildByTag00
static int tolua_CocoStudio_Widget_getChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getChildByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: sortAllChildren of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_sortAllChildren00
static int tolua_CocoStudio_Widget_sortAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sortAllChildren'", NULL);
#endif
  {
   self->sortAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildren of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getChildren00
static int tolua_CocoStudio_Widget_getChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildren'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getChildren();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
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

/* method: getChildrenCount of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getChildrenCount00
static int tolua_CocoStudio_Widget_getChildrenCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildrenCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getChildrenCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildrenCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeFromParent00
static int tolua_CocoStudio_Widget_removeFromParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeFromParentAndCleanup of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeFromParentAndCleanup00
static int tolua_CocoStudio_Widget_removeFromParentAndCleanup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeChild of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeChild00
static int tolua_CocoStudio_Widget_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child);
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

/* method: removeChild of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeChild01
static int tolua_CocoStudio_Widget_removeChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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
tolua_lerror:
 return tolua_CocoStudio_Widget_removeChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChildByTag of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeChildByTag00
static int tolua_CocoStudio_Widget_removeChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChildByTag'", NULL);
#endif
  {
   self->removeChildByTag(tag,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChildByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildren of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeAllChildren00
static int tolua_CocoStudio_Widget_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeAllChildrenWithCleanup of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeAllChildrenWithCleanup00
static int tolua_CocoStudio_Widget_removeAllChildrenWithCleanup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildrenWithCleanup'", NULL);
#endif
  {
   self->removeAllChildrenWithCleanup(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildrenWithCleanup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByName of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getChildByName00
static int tolua_CocoStudio_Widget_getChildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByName'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->getChildByName(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: addNode of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_addNode00
static int tolua_CocoStudio_Widget_addNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_addNode01
static int tolua_CocoStudio_Widget_addNode01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Widget_addNode00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_addNode02
static int tolua_CocoStudio_Widget_addNode02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Widget_addNode01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodeByTag of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getNodeByTag00
static int tolua_CocoStudio_Widget_getNodeByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodeByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNodeByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodeByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodes of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getNodes00
static int tolua_CocoStudio_Widget_getNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodes'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getNodes();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeNode of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeNode00
static int tolua_CocoStudio_Widget_removeNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeNode'", NULL);
#endif
  {
   self->removeNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeNodeByTag of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeNodeByTag00
static int tolua_CocoStudio_Widget_removeNodeByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeNodeByTag'", NULL);
#endif
  {
   self->removeNodeByTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeNodeByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllNodes of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_removeAllNodes00
static int tolua_CocoStudio_Widget_removeAllNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllNodes'", NULL);
#endif
  {
   self->removeAllNodes();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_visit00
static int tolua_CocoStudio_Widget_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPosition of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setPosition00
static int tolua_CocoStudio_Widget_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPositionPercent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setPositionPercent00
static int tolua_CocoStudio_Widget_setPositionPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPositionPercent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getPositionPercent00
static int tolua_CocoStudio_Widget_getPositionPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPositionType of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setPositionType00
static int tolua_CocoStudio_Widget_setPositionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPositionType of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getPositionType00
static int tolua_CocoStudio_Widget_getPositionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFlipX of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setFlipX00
static int tolua_CocoStudio_Widget_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isFlipX of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isFlipX00
static int tolua_CocoStudio_Widget_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFlipY of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setFlipY00
static int tolua_CocoStudio_Widget_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isFlipY of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isFlipY00
static int tolua_CocoStudio_Widget_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setColor of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setColor00
static int tolua_CocoStudio_Widget_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setOpacity of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setOpacity00
static int tolua_CocoStudio_Widget_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,2,0));
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

/* method: getColor of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getColor00
static int tolua_CocoStudio_Widget_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getOpacity of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getOpacity00
static int tolua_CocoStudio_Widget_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getOpacity();
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

/* method: didNotSelectSelf of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_didNotSelectSelf00
static int tolua_CocoStudio_Widget_didNotSelectSelf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: clippingParentAreaContainPoint of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_clippingParentAreaContainPoint00
static int tolua_CocoStudio_Widget_clippingParentAreaContainPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: checkChildInfo of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_checkChildInfo00
static int tolua_CocoStudio_Widget_checkChildInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  int handleState = ((int)  tolua_tonumber(tolua_S,2,0));
  Widget* sender = ((Widget*)  tolua_tousertype(tolua_S,3,0));
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

/* method: getTouchStartPos of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getTouchStartPos00
static int tolua_CocoStudio_Widget_getTouchStartPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTouchMovePos of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getTouchMovePos00
static int tolua_CocoStudio_Widget_getTouchMovePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTouchEndPos of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getTouchEndPos00
static int tolua_CocoStudio_Widget_getTouchEndPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setName of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setName00
static int tolua_CocoStudio_Widget_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getName of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getName00
static int tolua_CocoStudio_Widget_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getWidgetType of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getWidgetType00
static int tolua_CocoStudio_Widget_getWidgetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setSize00
static int tolua_CocoStudio_Widget_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSizePercent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setSizePercent00
static int tolua_CocoStudio_Widget_setSizePercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSizeType of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setSizeType00
static int tolua_CocoStudio_Widget_setSizeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getSizeType of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getSizeType00
static int tolua_CocoStudio_Widget_getSizeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getSize00
static int tolua_CocoStudio_Widget_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getLayoutSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getLayoutSize00
static int tolua_CocoStudio_Widget_getLayoutSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getLayoutSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayoutSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSizePercent of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getSizePercent00
static int tolua_CocoStudio_Widget_getSizePercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCustomSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getCustomSize00
static int tolua_CocoStudio_Widget_getCustomSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCustomSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getCustomSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCustomSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hitTest of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_hitTest00
static int tolua_CocoStudio_Widget_hitTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onTouchBegan of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_onTouchBegan00
static int tolua_CocoStudio_Widget_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(touch,unused_event);
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

/* method: onTouchMoved of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_onTouchMoved00
static int tolua_CocoStudio_Widget_onTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchMoved'", NULL);
#endif
  {
   self->onTouchMoved(touch,unused_event);
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

/* method: onTouchEnded of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_onTouchEnded00
static int tolua_CocoStudio_Widget_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(touch,unused_event);
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

/* method: onTouchCancelled of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_onTouchCancelled00
static int tolua_CocoStudio_Widget_onTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchCancelled'", NULL);
#endif
  {
   self->onTouchCancelled(touch,unused_event);
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

/* method: setLayoutParameter of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setLayoutParameter00
static int tolua_CocoStudio_Widget_setLayoutParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"LayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  LayoutParameter* parameter = ((LayoutParameter*)  tolua_tousertype(tolua_S,2,0));
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

/* method: getLayoutParameter of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getLayoutParameter00
static int tolua_CocoStudio_Widget_getLayoutParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  LayoutParameterType type = ((LayoutParameterType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayoutParameter'", NULL);
#endif
  {
   LayoutParameter* tolua_ret = (LayoutParameter*)  self->getLayoutParameter(type);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LayoutParameter");
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

/* method: ignoreContentAdaptWithSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_Widget_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isIgnoreContentAdaptWithSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_isIgnoreContentAdaptWithSize00
static int tolua_CocoStudio_Widget_isIgnoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getWorldPosition of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getWorldPosition00
static int tolua_CocoStudio_Widget_getWorldPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getVirtualRenderer00
static int tolua_CocoStudio_Widget_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getContentSize of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getContentSize00
static int tolua_CocoStudio_Widget_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getDescription00
static int tolua_CocoStudio_Widget_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Widget* self = (const Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: clone of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_clone00
static int tolua_CocoStudio_Widget_clone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clone'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->clone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: onEnter of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_onEnter00
static int tolua_CocoStudio_Widget_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onExit of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_onExit00
static int tolua_CocoStudio_Widget_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: updateSizeAndPosition of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_updateSizeAndPosition00
static int tolua_CocoStudio_Widget_updateSizeAndPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: updateSizeAndPosition of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_updateSizeAndPosition01
static int tolua_CocoStudio_Widget_updateSizeAndPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* parentSize = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateSizeAndPosition'", NULL);
#endif
  {
   self->updateSizeAndPosition(*parentSize);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Widget_updateSizeAndPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionTag of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_setActionTag00
static int tolua_CocoStudio_Widget_setActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getActionTag of class  Widget */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Widget_getActionTag00
static int tolua_CocoStudio_Widget_getActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Widget* self = (Widget*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_new00
static int tolua_CocoStudio_Layout_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Layout* tolua_ret = (Layout*)  Mtolua_new((Layout)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Layout");
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

/* method: new_local of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_new00_local
static int tolua_CocoStudio_Layout_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Layout* tolua_ret = (Layout*)  Mtolua_new((Layout)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Layout");
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

/* method: delete of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_delete00
static int tolua_CocoStudio_Layout_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_create00
static int tolua_CocoStudio_Layout_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Layout* tolua_ret = (Layout*)  Layout::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Layout");
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

/* method: setBackGroundImage of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundImage00
static int tolua_CocoStudio_Layout_setBackGroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setBackGroundImageCapInsets of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundImageCapInsets00
static int tolua_CocoStudio_Layout_setBackGroundImageCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getBackGroundImageCapInsets of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundImageCapInsets00
static int tolua_CocoStudio_Layout_getBackGroundImageCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundImageCapInsets'", NULL);
#endif
  {
   const CCRect& tolua_ret = (const CCRect&)  self->getBackGroundImageCapInsets();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundImageCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColorType of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundColorType00
static int tolua_CocoStudio_Layout_setBackGroundColorType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getBackGroundColorType of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundColorType00
static int tolua_CocoStudio_Layout_getBackGroundColorType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundColorType'", NULL);
#endif
  {
   LayoutBackGroundColorType tolua_ret = (LayoutBackGroundColorType)  self->getBackGroundColorType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundColorType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImageScale9Enabled of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundImageScale9Enabled00
static int tolua_CocoStudio_Layout_setBackGroundImageScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isBackGroundImageScale9Enabled of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_isBackGroundImageScale9Enabled00
static int tolua_CocoStudio_Layout_isBackGroundImageScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBackGroundImageScale9Enabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBackGroundImageScale9Enabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBackGroundImageScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundColor00
static int tolua_CocoStudio_Layout_setBackGroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getBackGroundColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundColor00
static int tolua_CocoStudio_Layout_getBackGroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getBackGroundColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundColor01
static int tolua_CocoStudio_Layout_setBackGroundColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_CocoStudio_Layout_setBackGroundColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackGroundStartColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundStartColor00
static int tolua_CocoStudio_Layout_getBackGroundStartColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundStartColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getBackGroundStartColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundStartColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackGroundEndColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundEndColor00
static int tolua_CocoStudio_Layout_getBackGroundEndColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundEndColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getBackGroundEndColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundEndColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColorOpacity of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundColorOpacity00
static int tolua_CocoStudio_Layout_setBackGroundColorOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,2,0));
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

/* method: getBackGroundColorOpacity of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundColorOpacity00
static int tolua_CocoStudio_Layout_getBackGroundColorOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundColorOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getBackGroundColorOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundColorOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundColorVector of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundColorVector00
static int tolua_CocoStudio_Layout_setBackGroundColorVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getBackGroundColorVector of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundColorVector00
static int tolua_CocoStudio_Layout_getBackGroundColorVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundColorVector'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getBackGroundColorVector();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundColorVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImageColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundImageColor00
static int tolua_CocoStudio_Layout_setBackGroundImageColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundImageColor'", NULL);
#endif
  {
   self->setBackGroundImageColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundImageColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackGroundImageOpacity of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setBackGroundImageOpacity00
static int tolua_CocoStudio_Layout_setBackGroundImageOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackGroundImageOpacity'", NULL);
#endif
  {
   self->setBackGroundImageOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackGroundImageOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackGroundImageColor of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundImageColor00
static int tolua_CocoStudio_Layout_getBackGroundImageColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundImageColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getBackGroundImageColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundImageColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackGroundImageOpacity of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundImageOpacity00
static int tolua_CocoStudio_Layout_getBackGroundImageOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackGroundImageOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getBackGroundImageOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackGroundImageOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBackGroundImage of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_removeBackGroundImage00
static int tolua_CocoStudio_Layout_removeBackGroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getBackGroundImageTextureSize of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getBackGroundImageTextureSize00
static int tolua_CocoStudio_Layout_getBackGroundImageTextureSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Layout* self = (const Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setClippingEnabled of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setClippingEnabled00
static int tolua_CocoStudio_Layout_setClippingEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClippingEnabled'", NULL);
#endif
  {
   self->setClippingEnabled(enabled);
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

/* method: setClippingType of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setClippingType00
static int tolua_CocoStudio_Layout_setClippingType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  LayoutClippingType type = ((LayoutClippingType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClippingType'", NULL);
#endif
  {
   self->setClippingType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setClippingType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClippingType of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getClippingType00
static int tolua_CocoStudio_Layout_getClippingType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClippingType'", NULL);
#endif
  {
   LayoutClippingType tolua_ret = (LayoutClippingType)  self->getClippingType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClippingType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClippingEnabled of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_isClippingEnabled00
static int tolua_CocoStudio_Layout_isClippingEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getDescription00
static int tolua_CocoStudio_Layout_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Layout* self = (const Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: setLayoutType of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_setLayoutType00
static int tolua_CocoStudio_Layout_setLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getLayoutType of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_getLayoutType00
static int tolua_CocoStudio_Layout_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Layout* self = (const Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addChild of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_addChild00
static int tolua_CocoStudio_Layout_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
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

/* method: addChild of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_addChild01
static int tolua_CocoStudio_Layout_addChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Layout_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_addChild02
static int tolua_CocoStudio_Layout_addChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Layout_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_removeChild00
static int tolua_CocoStudio_Layout_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child);
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

/* method: removeChild of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_removeChild01
static int tolua_CocoStudio_Layout_removeChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  CCNode* widget = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(widget,cleanup);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_Layout_removeChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildren of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_removeAllChildren00
static int tolua_CocoStudio_Layout_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeAllChildrenWithCleanup of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_removeAllChildrenWithCleanup00
static int tolua_CocoStudio_Layout_removeAllChildrenWithCleanup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildrenWithCleanup'", NULL);
#endif
  {
   self->removeAllChildrenWithCleanup(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildrenWithCleanup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_visit00
static int tolua_CocoStudio_Layout_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: sortAllChildren of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_sortAllChildren00
static int tolua_CocoStudio_Layout_sortAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sortAllChildren'", NULL);
#endif
  {
   self->sortAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: requestDoLayout of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_requestDoLayout00
static int tolua_CocoStudio_Layout_requestDoLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestDoLayout'", NULL);
#endif
  {
   self->requestDoLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestDoLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_onEnter00
static int tolua_CocoStudio_Layout_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onExit of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_onExit00
static int tolua_CocoStudio_Layout_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: hitTest of class  Layout */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Layout_hitTest00
static int tolua_CocoStudio_Layout_hitTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Layout",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Layout* self = (Layout*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_new00
static int tolua_CocoStudio_Button_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Button* tolua_ret = (Button*)  Mtolua_new((Button)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Button");
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

/* method: new_local of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_new00_local
static int tolua_CocoStudio_Button_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Button* tolua_ret = (Button*)  Mtolua_new((Button)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Button");
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

/* method: delete of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_delete00
static int tolua_CocoStudio_Button_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_create00
static int tolua_CocoStudio_Button_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Button* tolua_ret = (Button*)  Button::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Button");
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

/* method: loadTextures of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_loadTextures00
static int tolua_CocoStudio_Button_loadTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
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
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureNormal of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_loadTextureNormal00
static int tolua_CocoStudio_Button_loadTextureNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTexturePressed of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_loadTexturePressed00
static int tolua_CocoStudio_Button_loadTexturePressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureDisabled of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_loadTextureDisabled00
static int tolua_CocoStudio_Button_loadTextureDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setCapInsets of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setCapInsets00
static int tolua_CocoStudio_Button_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setCapInsetsNormalRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setCapInsetsNormalRenderer00
static int tolua_CocoStudio_Button_setCapInsetsNormalRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCapInsetNormalRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getCapInsetNormalRenderer00
static int tolua_CocoStudio_Button_getCapInsetNormalRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCapInsetNormalRenderer'", NULL);
#endif
  {
   const CCRect& tolua_ret = (const CCRect&)  self->getCapInsetNormalRenderer();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCapInsetNormalRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetsPressedRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setCapInsetsPressedRenderer00
static int tolua_CocoStudio_Button_setCapInsetsPressedRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCapInsetPressedRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getCapInsetPressedRenderer00
static int tolua_CocoStudio_Button_getCapInsetPressedRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCapInsetPressedRenderer'", NULL);
#endif
  {
   const CCRect& tolua_ret = (const CCRect&)  self->getCapInsetPressedRenderer();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCapInsetPressedRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetsDisabledRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setCapInsetsDisabledRenderer00
static int tolua_CocoStudio_Button_setCapInsetsDisabledRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCapInsetDisabledRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getCapInsetDisabledRenderer00
static int tolua_CocoStudio_Button_getCapInsetDisabledRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCapInsetDisabledRenderer'", NULL);
#endif
  {
   const CCRect& tolua_ret = (const CCRect&)  self->getCapInsetDisabledRenderer();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCapInsetDisabledRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setAnchorPoint00
static int tolua_CocoStudio_Button_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setScale9Enabled of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setScale9Enabled00
static int tolua_CocoStudio_Button_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isScale9Enabled of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_isScale9Enabled00
static int tolua_CocoStudio_Button_isScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isScale9Enabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isScale9Enabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPressedActionEnabled of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setPressedActionEnabled00
static int tolua_CocoStudio_Button_setPressedActionEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ignoreContentAdaptWithSize of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_Button_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getContentSize00
static int tolua_CocoStudio_Button_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getVirtualRenderer00
static int tolua_CocoStudio_Button_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getDescription of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getDescription00
static int tolua_CocoStudio_Button_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: setTitleText of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setTitleText00
static int tolua_CocoStudio_Button_setTitleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleText'", NULL);
#endif
  {
   self->setTitleText(text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleText of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getTitleText00
static int tolua_CocoStudio_Button_getTitleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTitleColor of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setTitleColor00
static int tolua_CocoStudio_Button_setTitleColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTitleColor of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getTitleColor00
static int tolua_CocoStudio_Button_getTitleColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTitleFontSize of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setTitleFontSize00
static int tolua_CocoStudio_Button_setTitleFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTitleFontSize of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getTitleFontSize00
static int tolua_CocoStudio_Button_getTitleFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTitleFontName of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_setTitleFontName00
static int tolua_CocoStudio_Button_setTitleFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTitleFontName of class  Button */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Button_getTitleFontName00
static int tolua_CocoStudio_Button_getTitleFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_new00
static int tolua_CocoStudio_CheckBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CheckBox* tolua_ret = (CheckBox*)  Mtolua_new((CheckBox)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CheckBox");
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

/* method: new_local of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_new00_local
static int tolua_CocoStudio_CheckBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CheckBox* tolua_ret = (CheckBox*)  Mtolua_new((CheckBox)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CheckBox");
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

/* method: delete of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_delete00
static int tolua_CocoStudio_CheckBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_create00
static int tolua_CocoStudio_CheckBox_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CheckBox* tolua_ret = (CheckBox*)  CheckBox::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CheckBox");
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

/* method: loadTextures of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_loadTextures00
static int tolua_CocoStudio_CheckBox_loadTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
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
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureBackGround of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_loadTextureBackGround00
static int tolua_CocoStudio_CheckBox_loadTextureBackGround00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureBackGroundSelected of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_loadTextureBackGroundSelected00
static int tolua_CocoStudio_CheckBox_loadTextureBackGroundSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureFrontCross of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_loadTextureFrontCross00
static int tolua_CocoStudio_CheckBox_loadTextureFrontCross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureBackGroundDisabled of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_loadTextureBackGroundDisabled00
static int tolua_CocoStudio_CheckBox_loadTextureBackGroundDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTextureFrontCrossDisabled of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_loadTextureFrontCrossDisabled00
static int tolua_CocoStudio_CheckBox_loadTextureFrontCrossDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setSelectedState of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_setSelectedState00
static int tolua_CocoStudio_CheckBox_setSelectedState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getSelectedState of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_getSelectedState00
static int tolua_CocoStudio_CheckBox_getSelectedState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorPoint of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_setAnchorPoint00
static int tolua_CocoStudio_CheckBox_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onTouchEnded of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_onTouchEnded00
static int tolua_CocoStudio_CheckBox_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(touch,unused_event);
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

/* method: getContentSize of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_getContentSize00
static int tolua_CocoStudio_CheckBox_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CheckBox* self = (const CheckBox*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_getVirtualRenderer00
static int tolua_CocoStudio_CheckBox_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getDescription of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CheckBox_getDescription00
static int tolua_CocoStudio_CheckBox_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CheckBox* self = (const CheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: new of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_new00
static int tolua_CocoStudio_ImageView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ImageView* tolua_ret = (ImageView*)  Mtolua_new((ImageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ImageView");
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

/* method: new_local of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_new00_local
static int tolua_CocoStudio_ImageView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ImageView* tolua_ret = (ImageView*)  Mtolua_new((ImageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ImageView");
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

/* method: delete of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_delete00
static int tolua_CocoStudio_ImageView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_create00
static int tolua_CocoStudio_ImageView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ImageView* tolua_ret = (ImageView*)  ImageView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ImageView");
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

/* method: loadTexture of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_loadTexture00
static int tolua_CocoStudio_ImageView_loadTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTextureRect of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_setTextureRect00
static int tolua_CocoStudio_ImageView_setTextureRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setScale9Enabled of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_setScale9Enabled00
static int tolua_CocoStudio_ImageView_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setCapInsets of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_setCapInsets00
static int tolua_CocoStudio_ImageView_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFlipX of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_setFlipX00
static int tolua_CocoStudio_ImageView_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFlipY of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_setFlipY00
static int tolua_CocoStudio_ImageView_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isFlipX of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_isFlipX00
static int tolua_CocoStudio_ImageView_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isFlipY of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_isFlipY00
static int tolua_CocoStudio_ImageView_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorPoint of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_setAnchorPoint00
static int tolua_CocoStudio_ImageView_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ignoreContentAdaptWithSize of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_ImageView_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_getDescription00
static int tolua_CocoStudio_ImageView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ImageView* self = (const ImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: getContentSize of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_getContentSize00
static int tolua_CocoStudio_ImageView_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ImageView* self = (const ImageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  ImageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ImageView_getVirtualRenderer00
static int tolua_CocoStudio_ImageView_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageView* self = (ImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: new of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_new00
static int tolua_CocoStudio_Label_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Label* tolua_ret = (Label*)  Mtolua_new((Label)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Label");
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

/* method: new_local of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_new00_local
static int tolua_CocoStudio_Label_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Label* tolua_ret = (Label*)  Mtolua_new((Label)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Label");
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

/* method: delete of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_delete00
static int tolua_CocoStudio_Label_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_create00
static int tolua_CocoStudio_Label_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Label* tolua_ret = (Label*)  Label::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Label");
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

/* method: setText of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setText00
static int tolua_CocoStudio_Label_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getStringValue00
static int tolua_CocoStudio_Label_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getStringLength of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getStringLength00
static int tolua_CocoStudio_Label_getStringLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFontSize of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setFontSize00
static int tolua_CocoStudio_Label_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getFontSize of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getFontSize00
static int tolua_CocoStudio_Label_getFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFontSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFontSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setFontName00
static int tolua_CocoStudio_Label_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFontName of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getFontName00
static int tolua_CocoStudio_Label_getFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFontName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getFontName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchScaleChangeEnabled of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setTouchScaleChangeEnabled00
static int tolua_CocoStudio_Label_setTouchScaleChangeEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isTouchScaleChangeEnabled of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_isTouchScaleChangeEnabled00
static int tolua_CocoStudio_Label_isTouchScaleChangeEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorPoint of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setAnchorPoint00
static int tolua_CocoStudio_Label_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getContentSize00
static int tolua_CocoStudio_Label_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Label* self = (const Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getVirtualRenderer00
static int tolua_CocoStudio_Label_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getDescription of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getDescription00
static int tolua_CocoStudio_Label_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Label* self = (const Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: setTextAreaSize of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setTextAreaSize00
static int tolua_CocoStudio_Label_setTextAreaSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTextAreaSize of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getTextAreaSize00
static int tolua_CocoStudio_Label_getTextAreaSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextAreaSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getTextAreaSize();
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
 tolua_error(tolua_S,"#ferror in function 'getTextAreaSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextHorizontalAlignment of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setTextHorizontalAlignment00
static int tolua_CocoStudio_Label_setTextHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTextHorizontalAlignment of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getTextHorizontalAlignment00
static int tolua_CocoStudio_Label_getTextHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextHorizontalAlignment'", NULL);
#endif
  {
   CCTextAlignment tolua_ret = (CCTextAlignment)  self->getTextHorizontalAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTextHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextVerticalAlignment of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_setTextVerticalAlignment00
static int tolua_CocoStudio_Label_setTextVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
  CCVerticalTextAlignment alignment = ((CCVerticalTextAlignment) (int)  tolua_tonumber(tolua_S,2,0));
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

/* method: getTextVerticalAlignment of class  Label */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Label_getTextVerticalAlignment00
static int tolua_CocoStudio_Label_getTextVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Label",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Label* self = (Label*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextVerticalAlignment'", NULL);
#endif
  {
   CCVerticalTextAlignment tolua_ret = (CCVerticalTextAlignment)  self->getTextVerticalAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTextVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_new00
static int tolua_CocoStudio_LabelAtlas_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LabelAtlas* tolua_ret = (LabelAtlas*)  Mtolua_new((LabelAtlas)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LabelAtlas");
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

/* method: new_local of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_new00_local
static int tolua_CocoStudio_LabelAtlas_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LabelAtlas* tolua_ret = (LabelAtlas*)  Mtolua_new((LabelAtlas)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LabelAtlas");
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

/* method: delete of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_delete00
static int tolua_CocoStudio_LabelAtlas_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelAtlas* self = (LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_create00
static int tolua_CocoStudio_LabelAtlas_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LabelAtlas* tolua_ret = (LabelAtlas*)  LabelAtlas::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LabelAtlas");
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

/* method: setProperty of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_setProperty00
static int tolua_CocoStudio_LabelAtlas_setProperty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelAtlas* self = (LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
  const std::string stringValue = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string charMapFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  int itemWidth = ((int)  tolua_tonumber(tolua_S,4,0));
  int itemHeight = ((int)  tolua_tonumber(tolua_S,5,0));
  const std::string startCharMap = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProperty'", NULL);
#endif
  {
   self->setProperty(stringValue,charMapFile,itemWidth,itemHeight,startCharMap);
   tolua_pushcppstring(tolua_S,(const char*)stringValue);
   tolua_pushcppstring(tolua_S,(const char*)charMapFile);
   tolua_pushcppstring(tolua_S,(const char*)startCharMap);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProperty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStringValue of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_setStringValue00
static int tolua_CocoStudio_LabelAtlas_setStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelAtlas* self = (LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
  const std::string value = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStringValue'", NULL);
#endif
  {
   self->setStringValue(value);
   tolua_pushcppstring(tolua_S,(const char*)value);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_getStringValue00
static int tolua_CocoStudio_LabelAtlas_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LabelAtlas* self = (const LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorPoint of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_setAnchorPoint00
static int tolua_CocoStudio_LabelAtlas_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelAtlas* self = (LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_getContentSize00
static int tolua_CocoStudio_LabelAtlas_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LabelAtlas* self = (const LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_getVirtualRenderer00
static int tolua_CocoStudio_LabelAtlas_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelAtlas* self = (LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getDescription of class  LabelAtlas */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelAtlas_getDescription00
static int tolua_CocoStudio_LabelAtlas_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LabelAtlas",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LabelAtlas* self = (const LabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: new of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_new00
static int tolua_CocoStudio_LabelBMFont_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LabelBMFont* tolua_ret = (LabelBMFont*)  Mtolua_new((LabelBMFont)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LabelBMFont");
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

/* method: new_local of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_new00_local
static int tolua_CocoStudio_LabelBMFont_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LabelBMFont* tolua_ret = (LabelBMFont*)  Mtolua_new((LabelBMFont)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LabelBMFont");
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

/* method: delete of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_delete00
static int tolua_CocoStudio_LabelBMFont_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelBMFont* self = (LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_create00
static int tolua_CocoStudio_LabelBMFont_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LabelBMFont* tolua_ret = (LabelBMFont*)  LabelBMFont::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LabelBMFont");
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

/* method: setFntFile of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_setFntFile00
static int tolua_CocoStudio_LabelBMFont_setFntFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelBMFont* self = (LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setText of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_setText00
static int tolua_CocoStudio_LabelBMFont_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelBMFont* self = (LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getStringValue of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_getStringValue00
static int tolua_CocoStudio_LabelBMFont_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelBMFont* self = (LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorPoint of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_setAnchorPoint00
static int tolua_CocoStudio_LabelBMFont_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelBMFont* self = (LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_getContentSize00
static int tolua_CocoStudio_LabelBMFont_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LabelBMFont* self = (const LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_getVirtualRenderer00
static int tolua_CocoStudio_LabelBMFont_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LabelBMFont* self = (LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getDescription of class  LabelBMFont */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LabelBMFont_getDescription00
static int tolua_CocoStudio_LabelBMFont_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LabelBMFont* self = (const LabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: new of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_new00
static int tolua_CocoStudio_LoadingBar_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LoadingBar* tolua_ret = (LoadingBar*)  Mtolua_new((LoadingBar)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LoadingBar");
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

/* method: new_local of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_new00_local
static int tolua_CocoStudio_LoadingBar_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LoadingBar* tolua_ret = (LoadingBar*)  Mtolua_new((LoadingBar)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LoadingBar");
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

/* method: delete of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_delete00
static int tolua_CocoStudio_LoadingBar_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_create00
static int tolua_CocoStudio_LoadingBar_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LoadingBar* tolua_ret = (LoadingBar*)  LoadingBar::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LoadingBar");
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

/* method: setDirection of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_setDirection00
static int tolua_CocoStudio_LoadingBar_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDirection of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_getDirection00
static int tolua_CocoStudio_LoadingBar_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadTexture of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_loadTexture00
static int tolua_CocoStudio_LoadingBar_loadTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPercent of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_setPercent00
static int tolua_CocoStudio_LoadingBar_setPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPercent of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_getPercent00
static int tolua_CocoStudio_LoadingBar_getPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setScale9Enabled of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_setScale9Enabled00
static int tolua_CocoStudio_LoadingBar_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setCapInsets of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_setCapInsets00
static int tolua_CocoStudio_LoadingBar_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ignoreContentAdaptWithSize of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_LoadingBar_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_getContentSize00
static int tolua_CocoStudio_LoadingBar_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LoadingBar* self = (const LoadingBar*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_getVirtualRenderer00
static int tolua_CocoStudio_LoadingBar_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LoadingBar* self = (LoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getDescription of class  LoadingBar */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LoadingBar_getDescription00
static int tolua_CocoStudio_LoadingBar_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LoadingBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LoadingBar* self = (const LoadingBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: new of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_new00
static int tolua_CocoStudio_Slider_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Slider* tolua_ret = (Slider*)  Mtolua_new((Slider)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Slider");
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

/* method: new_local of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_new00_local
static int tolua_CocoStudio_Slider_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Slider* tolua_ret = (Slider*)  Mtolua_new((Slider)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Slider");
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

/* method: delete of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_delete00
static int tolua_CocoStudio_Slider_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_create00
static int tolua_CocoStudio_Slider_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Slider* tolua_ret = (Slider*)  Slider::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Slider");
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

/* method: loadBarTexture of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_loadBarTexture00
static int tolua_CocoStudio_Slider_loadBarTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setScale9Enabled of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_setScale9Enabled00
static int tolua_CocoStudio_Slider_setScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isScale9Enabled of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_isScale9Enabled00
static int tolua_CocoStudio_Slider_isScale9Enabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isScale9Enabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isScale9Enabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isScale9Enabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_setCapInsets00
static int tolua_CocoStudio_Slider_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setCapInsetsBarRenderer of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_setCapInsetsBarRenderer00
static int tolua_CocoStudio_Slider_setCapInsetsBarRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCapInsetBarRenderer of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_getCapInsetBarRenderer00
static int tolua_CocoStudio_Slider_getCapInsetBarRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCapInsetBarRenderer'", NULL);
#endif
  {
   const CCRect& tolua_ret = (const CCRect&)  self->getCapInsetBarRenderer();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCapInsetBarRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsetProgressBarRebderer of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_setCapInsetProgressBarRebderer00
static int tolua_CocoStudio_Slider_setCapInsetProgressBarRebderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCapInsetProgressBarRebderer of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_getCapInsetProgressBarRebderer00
static int tolua_CocoStudio_Slider_getCapInsetProgressBarRebderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCapInsetProgressBarRebderer'", NULL);
#endif
  {
   const CCRect& tolua_ret = (const CCRect&)  self->getCapInsetProgressBarRebderer();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCapInsetProgressBarRebderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadSlidBallTextures of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_loadSlidBallTextures00
static int tolua_CocoStudio_Slider_loadSlidBallTextures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
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
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadSlidBallTextureNormal of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_loadSlidBallTextureNormal00
static int tolua_CocoStudio_Slider_loadSlidBallTextureNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadSlidBallTexturePressed of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_loadSlidBallTexturePressed00
static int tolua_CocoStudio_Slider_loadSlidBallTexturePressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadSlidBallTextureDisabled of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_loadSlidBallTextureDisabled00
static int tolua_CocoStudio_Slider_loadSlidBallTextureDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: loadProgressBarTexture of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_loadProgressBarTexture00
static int tolua_CocoStudio_Slider_loadProgressBarTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPercent of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_setPercent00
static int tolua_CocoStudio_Slider_setPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPercent of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_getPercent00
static int tolua_CocoStudio_Slider_getPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onTouchBegan of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_onTouchBegan00
static int tolua_CocoStudio_Slider_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(touch,unused_event);
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

/* method: onTouchMoved of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_onTouchMoved00
static int tolua_CocoStudio_Slider_onTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchMoved'", NULL);
#endif
  {
   self->onTouchMoved(touch,unused_event);
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

/* method: onTouchEnded of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_onTouchEnded00
static int tolua_CocoStudio_Slider_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(touch,unused_event);
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

/* method: onTouchCancelled of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_onTouchCancelled00
static int tolua_CocoStudio_Slider_onTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchCancelled'", NULL);
#endif
  {
   self->onTouchCancelled(touch,unused_event);
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

/* method: getContentSize of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_getContentSize00
static int tolua_CocoStudio_Slider_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_getVirtualRenderer00
static int tolua_CocoStudio_Slider_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: ignoreContentAdaptWithSize of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_Slider_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  Slider */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Slider_getDescription00
static int tolua_CocoStudio_Slider_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: new of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_new00
static int tolua_CocoStudio_TextField_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextField* tolua_ret = (TextField*)  Mtolua_new((TextField)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"TextField");
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

/* method: new_local of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_new00_local
static int tolua_CocoStudio_TextField_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextField* tolua_ret = (TextField*)  Mtolua_new((TextField)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"TextField");
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

/* method: delete of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_delete00
static int tolua_CocoStudio_TextField_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_create00
static int tolua_CocoStudio_TextField_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextField* tolua_ret = (TextField*)  TextField::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"TextField");
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

/* method: setTouchSize of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setTouchSize00
static int tolua_CocoStudio_TextField_setTouchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getTouchSize of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getTouchSize00
static int tolua_CocoStudio_TextField_getTouchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getTouchSize();
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
 tolua_error(tolua_S,"#ferror in function 'getTouchSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchAreaEnabled of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setTouchAreaEnabled00
static int tolua_CocoStudio_TextField_setTouchAreaEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchAreaEnabled'", NULL);
#endif
  {
   self->setTouchAreaEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchAreaEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hitTest of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_hitTest00
static int tolua_CocoStudio_TextField_hitTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setText of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setText00
static int tolua_CocoStudio_TextField_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceHolder of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setPlaceHolder00
static int tolua_CocoStudio_TextField_setPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
  const std::string value = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceHolder'", NULL);
#endif
  {
   self->setPlaceHolder(value);
   tolua_pushcppstring(tolua_S,(const char*)value);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlaceHolder of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getPlaceHolder00
static int tolua_CocoStudio_TextField_getPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlaceHolder'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPlaceHolder();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontSize of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setFontSize00
static int tolua_CocoStudio_TextField_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getFontSize of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getFontSize00
static int tolua_CocoStudio_TextField_getFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFontSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getFontSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setFontName00
static int tolua_CocoStudio_TextField_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFontName of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getFontName00
static int tolua_CocoStudio_TextField_getFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFontName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getFontName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: didNotSelectSelf of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_didNotSelectSelf00
static int tolua_CocoStudio_TextField_didNotSelectSelf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getStringValue of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getStringValue00
static int tolua_CocoStudio_TextField_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onTouchBegan of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_onTouchBegan00
static int tolua_CocoStudio_TextField_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unused_event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(touch,unused_event);
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

/* method: setMaxLengthEnabled of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setMaxLengthEnabled00
static int tolua_CocoStudio_TextField_setMaxLengthEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isMaxLengthEnabled of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_isMaxLengthEnabled00
static int tolua_CocoStudio_TextField_isMaxLengthEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setMaxLength of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setMaxLength00
static int tolua_CocoStudio_TextField_setMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getMaxLength of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getMaxLength00
static int tolua_CocoStudio_TextField_getMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPasswordEnabled of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setPasswordEnabled00
static int tolua_CocoStudio_TextField_setPasswordEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isPasswordEnabled of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_isPasswordEnabled00
static int tolua_CocoStudio_TextField_isPasswordEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPasswordStyleText of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setPasswordStyleText00
static int tolua_CocoStudio_TextField_setPasswordStyleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPasswordStyleText of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getPasswordStyleText00
static int tolua_CocoStudio_TextField_getPasswordStyleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPasswordStyleText'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPasswordStyleText();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPasswordStyleText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_update00
static int tolua_CocoStudio_TextField_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getAttachWithIME of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getAttachWithIME00
static int tolua_CocoStudio_TextField_getAttachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAttachWithIME of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setAttachWithIME00
static int tolua_CocoStudio_TextField_setAttachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDetachWithIME of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getDetachWithIME00
static int tolua_CocoStudio_TextField_getDetachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setDetachWithIME of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setDetachWithIME00
static int tolua_CocoStudio_TextField_setDetachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getInsertText of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getInsertText00
static int tolua_CocoStudio_TextField_getInsertText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setInsertText of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setInsertText00
static int tolua_CocoStudio_TextField_setInsertText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDeleteBackward of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getDeleteBackward00
static int tolua_CocoStudio_TextField_getDeleteBackward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setDeleteBackward of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setDeleteBackward00
static int tolua_CocoStudio_TextField_setDeleteBackward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAnchorPoint of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setAnchorPoint00
static int tolua_CocoStudio_TextField_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getDescription00
static int tolua_CocoStudio_TextField_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TextField* self = (const TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: getContentSize of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getContentSize00
static int tolua_CocoStudio_TextField_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TextField* self = (const TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getVirtualRenderer of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_getVirtualRenderer00
static int tolua_CocoStudio_TextField_getVirtualRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVirtualRenderer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getVirtualRenderer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: attachWithIME of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_attachWithIME00
static int tolua_CocoStudio_TextField_attachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onEnter of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_onEnter00
static int tolua_CocoStudio_TextField_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTextAreaSize of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setTextAreaSize00
static int tolua_CocoStudio_TextField_setTextAreaSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTextHorizontalAlignment of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setTextHorizontalAlignment00
static int tolua_CocoStudio_TextField_setTextHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTextVerticalAlignment of class  TextField */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TextField_setTextVerticalAlignment00
static int tolua_CocoStudio_TextField_setTextVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextField",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextField* self = (TextField*)  tolua_tousertype(tolua_S,1,0);
  CCVerticalTextAlignment alignment = ((CCVerticalTextAlignment) (int)  tolua_tonumber(tolua_S,2,0));
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

/* method: new of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_new00
static int tolua_CocoStudio_ScrollView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScrollView* tolua_ret = (ScrollView*)  Mtolua_new((ScrollView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ScrollView");
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

/* method: new_local of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_new00_local
static int tolua_CocoStudio_ScrollView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScrollView* tolua_ret = (ScrollView*)  Mtolua_new((ScrollView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ScrollView");
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

/* method: delete of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_delete00
static int tolua_CocoStudio_ScrollView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_create00
static int tolua_CocoStudio_ScrollView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ScrollView* tolua_ret = (ScrollView*)  ScrollView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ScrollView");
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

/* method: setDirection of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_setDirection00
static int tolua_CocoStudio_ScrollView_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDirection of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getDirection00
static int tolua_CocoStudio_ScrollView_getDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getInnerContainer of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getInnerContainer00
static int tolua_CocoStudio_ScrollView_getInnerContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInnerContainer'", NULL);
#endif
  {
   Layout* tolua_ret = (Layout*)  self->getInnerContainer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Layout");
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

/* method: scrollToBottom of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToBottom00
static int tolua_CocoStudio_ScrollView_scrollToBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToTop of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToTop00
static int tolua_CocoStudio_ScrollView_scrollToTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToLeft of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToLeft00
static int tolua_CocoStudio_ScrollView_scrollToLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToRight of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToRight00
static int tolua_CocoStudio_ScrollView_scrollToRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToTopLeft of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToTopLeft00
static int tolua_CocoStudio_ScrollView_scrollToTopLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToTopRight of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToTopRight00
static int tolua_CocoStudio_ScrollView_scrollToTopRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToBottomLeft of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToBottomLeft00
static int tolua_CocoStudio_ScrollView_scrollToBottomLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToBottomRight of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToBottomRight00
static int tolua_CocoStudio_ScrollView_scrollToBottomRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToPercentVertical of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToPercentVertical00
static int tolua_CocoStudio_ScrollView_scrollToPercentVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToPercentHorizontal of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToPercentHorizontal00
static int tolua_CocoStudio_ScrollView_scrollToPercentHorizontal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToPercentBothDirection of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_scrollToPercentBothDirection00
static int tolua_CocoStudio_ScrollView_scrollToPercentBothDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToBottom of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToBottom00
static int tolua_CocoStudio_ScrollView_jumpToBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToTop of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToTop00
static int tolua_CocoStudio_ScrollView_jumpToTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToLeft of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToLeft00
static int tolua_CocoStudio_ScrollView_jumpToLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToRight of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToRight00
static int tolua_CocoStudio_ScrollView_jumpToRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToTopLeft of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToTopLeft00
static int tolua_CocoStudio_ScrollView_jumpToTopLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToTopRight of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToTopRight00
static int tolua_CocoStudio_ScrollView_jumpToTopRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToBottomLeft of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToBottomLeft00
static int tolua_CocoStudio_ScrollView_jumpToBottomLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToBottomRight of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToBottomRight00
static int tolua_CocoStudio_ScrollView_jumpToBottomRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToPercentVertical of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToPercentVertical00
static int tolua_CocoStudio_ScrollView_jumpToPercentVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToPercentHorizontal of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToPercentHorizontal00
static int tolua_CocoStudio_ScrollView_jumpToPercentHorizontal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: jumpToPercentBothDirection of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_jumpToPercentBothDirection00
static int tolua_CocoStudio_ScrollView_jumpToPercentBothDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setInnerContainerSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_setInnerContainerSize00
static int tolua_CocoStudio_ScrollView_setInnerContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getInnerContainerSize of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getInnerContainerSize00
static int tolua_CocoStudio_ScrollView_getInnerContainerSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_addChild00
static int tolua_CocoStudio_ScrollView_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
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

/* method: addChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_addChild01
static int tolua_CocoStudio_ScrollView_addChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ScrollView_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_addChild02
static int tolua_CocoStudio_ScrollView_addChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ScrollView_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildren of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeAllChildren00
static int tolua_CocoStudio_ScrollView_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeAllChildrenWithCleanup of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeAllChildrenWithCleanup00
static int tolua_CocoStudio_ScrollView_removeAllChildrenWithCleanup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildrenWithCleanup'", NULL);
#endif
  {
   self->removeAllChildrenWithCleanup(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildrenWithCleanup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeChild00
static int tolua_CocoStudio_ScrollView_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child);
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

/* method: removeChild of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeChild01
static int tolua_CocoStudio_ScrollView_removeChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool cleaup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child,cleaup);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ScrollView_removeChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildren of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getChildren00
static int tolua_CocoStudio_ScrollView_getChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildren'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getChildren();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
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

/* method: getChildrenCount of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getChildrenCount00
static int tolua_CocoStudio_ScrollView_getChildrenCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildrenCount'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getChildrenCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildrenCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByTag of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getChildByTag00
static int tolua_CocoStudio_ScrollView_getChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getChildByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getChildByName of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getChildByName00
static int tolua_CocoStudio_ScrollView_getChildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByName'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->getChildByName(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: addNode of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_addNode00
static int tolua_CocoStudio_ScrollView_addNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_addNode01
static int tolua_CocoStudio_ScrollView_addNode01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ScrollView_addNode00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_addNode02
static int tolua_CocoStudio_ScrollView_addNode02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ScrollView_addNode01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodeByTag of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getNodeByTag00
static int tolua_CocoStudio_ScrollView_getNodeByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodeByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNodeByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodeByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeNodeByTag of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeNodeByTag00
static int tolua_CocoStudio_ScrollView_removeNodeByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeNodeByTag'", NULL);
#endif
  {
   self->removeNodeByTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeNodeByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodes of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getNodes00
static int tolua_CocoStudio_ScrollView_getNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodes'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getNodes();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeNode of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeNode00
static int tolua_CocoStudio_ScrollView_removeNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeNode'", NULL);
#endif
  {
   self->removeNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllNodes of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_removeAllNodes00
static int tolua_CocoStudio_ScrollView_removeAllNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllNodes'", NULL);
#endif
  {
   self->removeAllNodes();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_update00
static int tolua_CocoStudio_ScrollView_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setBounceEnabled of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_setBounceEnabled00
static int tolua_CocoStudio_ScrollView_setBounceEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isBounceEnabled of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_isBounceEnabled00
static int tolua_CocoStudio_ScrollView_isBounceEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setInertiaScrollEnabled of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_setInertiaScrollEnabled00
static int tolua_CocoStudio_ScrollView_setInertiaScrollEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isInertiaScrollEnabled of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_isInertiaScrollEnabled00
static int tolua_CocoStudio_ScrollView_isInertiaScrollEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setLayoutType of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_setLayoutType00
static int tolua_CocoStudio_ScrollView_setLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getLayoutType of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getLayoutType00
static int tolua_CocoStudio_ScrollView_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ScrollView_getDescription00
static int tolua_CocoStudio_ScrollView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* get function: __UIScrollInterface__ of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_get_ScrollView___UIScrollInterface__
static int tolua_get_ScrollView___UIScrollInterface__(lua_State* tolua_S)
{
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_new00
static int tolua_CocoStudio_PageView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PageView* tolua_ret = (PageView*)  Mtolua_new((PageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PageView");
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

/* method: new_local of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_new00_local
static int tolua_CocoStudio_PageView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PageView* tolua_ret = (PageView*)  Mtolua_new((PageView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PageView");
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

/* method: delete of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_delete00
static int tolua_CocoStudio_PageView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_create00
static int tolua_CocoStudio_PageView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PageView* tolua_ret = (PageView*)  PageView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PageView");
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

/* method: addWidgetToPage of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_addWidgetToPage00
static int tolua_CocoStudio_PageView_addWidgetToPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  Widget* widget = ((Widget*)  tolua_tousertype(tolua_S,2,0));
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

/* method: addPage of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_addPage00
static int tolua_CocoStudio_PageView_addPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  Layout* page = ((Layout*)  tolua_tousertype(tolua_S,2,0));
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

/* method: insertPage of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_insertPage00
static int tolua_CocoStudio_PageView_insertPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Layout",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  Layout* page = ((Layout*)  tolua_tousertype(tolua_S,2,0));
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

/* method: removePage of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_removePage00
static int tolua_CocoStudio_PageView_removePage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Layout",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  Layout* page = ((Layout*)  tolua_tousertype(tolua_S,2,0));
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

/* method: removePageAtIndex of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_removePageAtIndex00
static int tolua_CocoStudio_PageView_removePageAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeAllPages of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_removeAllPages00
static int tolua_CocoStudio_PageView_removeAllPages00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scrollToPage of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_scrollToPage00
static int tolua_CocoStudio_PageView_scrollToPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getCurPageIndex of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_getCurPageIndex00
static int tolua_CocoStudio_PageView_getCurPageIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PageView* self = (const PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getPages of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_getPages00
static int tolua_CocoStudio_PageView_getPages00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPages'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getPages();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
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

/* method: getPage of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_getPage00
static int tolua_CocoStudio_PageView_getPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPage'", NULL);
#endif
  {
   Layout* tolua_ret = (Layout*)  self->getPage(index);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Layout");
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

/* method: onTouchBegan of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_onTouchBegan00
static int tolua_CocoStudio_PageView_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unusedEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(touch,unusedEvent);
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

/* method: onTouchMoved of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_onTouchMoved00
static int tolua_CocoStudio_PageView_onTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unusedEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchMoved'", NULL);
#endif
  {
   self->onTouchMoved(touch,unusedEvent);
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

/* method: onTouchEnded of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_onTouchEnded00
static int tolua_CocoStudio_PageView_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unusedEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(touch,unusedEvent);
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

/* method: onTouchCancelled of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_onTouchCancelled00
static int tolua_CocoStudio_PageView_onTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* unusedEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchCancelled'", NULL);
#endif
  {
   self->onTouchCancelled(touch,unusedEvent);
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

/* method: update of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_update00
static int tolua_CocoStudio_PageView_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setLayoutType of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_setLayoutType00
static int tolua_CocoStudio_PageView_setLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getLayoutType of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_getLayoutType00
static int tolua_CocoStudio_PageView_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PageView* self = (const PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  PageView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_PageView_getDescription00
static int tolua_CocoStudio_PageView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PageView* self = (const PageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* get function: __UIScrollInterface__ of class  PageView */
#ifndef TOLUA_DISABLE_tolua_get_PageView___UIScrollInterface__
static int tolua_get_PageView___UIScrollInterface__(lua_State* tolua_S)
{
  PageView* self = (PageView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_new00
static int tolua_CocoStudio_ListView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ListView* tolua_ret = (ListView*)  Mtolua_new((ListView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ListView");
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

/* method: new_local of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_new00_local
static int tolua_CocoStudio_ListView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ListView* tolua_ret = (ListView*)  Mtolua_new((ListView)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ListView");
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

/* method: delete of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_delete00
static int tolua_CocoStudio_ListView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_create00
static int tolua_CocoStudio_ListView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ListView* tolua_ret = (ListView*)  ListView::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ListView");
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

/* method: setItemModel of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_setItemModel00
static int tolua_CocoStudio_ListView_setItemModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  Widget* model = ((Widget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setItemModel'", NULL);
#endif
  {
   self->setItemModel(model);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setItemModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pushBackDefaultItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_pushBackDefaultItem00
static int tolua_CocoStudio_ListView_pushBackDefaultItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushBackDefaultItem'", NULL);
#endif
  {
   self->pushBackDefaultItem();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushBackDefaultItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insertDefaultItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_insertDefaultItem00
static int tolua_CocoStudio_ListView_insertDefaultItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertDefaultItem'", NULL);
#endif
  {
   self->insertDefaultItem(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertDefaultItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pushBackCustomItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_pushBackCustomItem00
static int tolua_CocoStudio_ListView_pushBackCustomItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  Widget* item = ((Widget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushBackCustomItem'", NULL);
#endif
  {
   self->pushBackCustomItem(item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushBackCustomItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insertCustomItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_insertCustomItem00
static int tolua_CocoStudio_ListView_insertCustomItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  Widget* item = ((Widget*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertCustomItem'", NULL);
#endif
  {
   self->insertCustomItem(item,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertCustomItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeLastItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_removeLastItem00
static int tolua_CocoStudio_ListView_removeLastItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeLastItem'", NULL);
#endif
  {
   self->removeLastItem();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeLastItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_removeItem00
static int tolua_CocoStudio_ListView_removeItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeItem'", NULL);
#endif
  {
   self->removeItem(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllItems of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_removeAllItems00
static int tolua_CocoStudio_ListView_removeAllItems00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllItems'", NULL);
#endif
  {
   self->removeAllItems();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllItems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_getItem00
static int tolua_CocoStudio_ListView_getItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItem'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->getItem(index);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItems of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_getItems00
static int tolua_CocoStudio_ListView_getItems00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItems'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getItems();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIndex of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_getIndex00
static int tolua_CocoStudio_ListView_getIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
  Widget* item = ((Widget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIndex'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getIndex(item);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGravity of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_setGravity00
static int tolua_CocoStudio_ListView_setGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  ListViewGravity gravity = ((ListViewGravity) (int)  tolua_tonumber(tolua_S,2,0));
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

/* method: setItemsMargin of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_setItemsMargin00
static int tolua_CocoStudio_ListView_setItemsMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  float margin = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setItemsMargin'", NULL);
#endif
  {
   self->setItemsMargin(margin);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setItemsMargin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sortAllChildren of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_sortAllChildren00
static int tolua_CocoStudio_ListView_sortAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sortAllChildren'", NULL);
#endif
  {
   self->sortAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurSelectedIndex of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_getCurSelectedIndex00
static int tolua_CocoStudio_ListView_getCurSelectedIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurSelectedIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurSelectedIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurSelectedIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDirection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_setDirection00
static int tolua_CocoStudio_ListView_setDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getDescription of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_getDescription00
static int tolua_CocoStudio_ListView_getDescription00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDescription'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
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

/* method: requestRefreshView of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_requestRefreshView00
static int tolua_CocoStudio_ListView_requestRefreshView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'requestRefreshView'", NULL);
#endif
  {
   self->requestRefreshView();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'requestRefreshView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: refreshView of class  ListView */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ListView_refreshView00
static int tolua_CocoStudio_ListView_refreshView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'refreshView'", NULL);
#endif
  {
   self->refreshView();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'refreshView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  LayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LayoutParameter_new00
static int tolua_CocoStudio_LayoutParameter_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LayoutParameter* tolua_ret = (LayoutParameter*)  Mtolua_new((LayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LayoutParameter");
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

/* method: new_local of class  LayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LayoutParameter_new00_local
static int tolua_CocoStudio_LayoutParameter_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LayoutParameter* tolua_ret = (LayoutParameter*)  Mtolua_new((LayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LayoutParameter");
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

/* method: delete of class  LayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LayoutParameter_delete00
static int tolua_CocoStudio_LayoutParameter_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LayoutParameter* self = (LayoutParameter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  LayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LayoutParameter_create00
static int tolua_CocoStudio_LayoutParameter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LayoutParameter* tolua_ret = (LayoutParameter*)  LayoutParameter::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LayoutParameter");
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

/* method: getLayoutType of class  LayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LayoutParameter_getLayoutType00
static int tolua_CocoStudio_LayoutParameter_getLayoutType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LayoutParameter* self = (const LayoutParameter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  LinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LinearLayoutParameter_new00
static int tolua_CocoStudio_LinearLayoutParameter_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LinearLayoutParameter* tolua_ret = (LinearLayoutParameter*)  Mtolua_new((LinearLayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LinearLayoutParameter");
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

/* method: new_local of class  LinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LinearLayoutParameter_new00_local
static int tolua_CocoStudio_LinearLayoutParameter_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LinearLayoutParameter* tolua_ret = (LinearLayoutParameter*)  Mtolua_new((LinearLayoutParameter)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LinearLayoutParameter");
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

/* method: delete of class  LinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LinearLayoutParameter_delete00
static int tolua_CocoStudio_LinearLayoutParameter_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LinearLayoutParameter* self = (LinearLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  LinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LinearLayoutParameter_create00
static int tolua_CocoStudio_LinearLayoutParameter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LinearLayoutParameter* tolua_ret = (LinearLayoutParameter*)  LinearLayoutParameter::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LinearLayoutParameter");
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

/* method: setGravity of class  LinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LinearLayoutParameter_setGravity00
static int tolua_CocoStudio_LinearLayoutParameter_setGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LinearLayoutParameter* self = (LinearLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
  LinearGravity gravity = ((LinearGravity) (int)  tolua_tonumber(tolua_S,2,0));
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

/* method: getGravity of class  LinearLayoutParameter */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_LinearLayoutParameter_getGravity00
static int tolua_CocoStudio_LinearLayoutParameter_getGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LinearLayoutParameter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LinearLayoutParameter* self = (const LinearLayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGravity'", NULL);
#endif
  {
   LinearGravity tolua_ret = (LinearGravity)  self->getGravity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: new of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_new00
static int tolua_CocoStudio_TouchGroup_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TouchGroup* tolua_ret = (TouchGroup*)  Mtolua_new((TouchGroup)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TouchGroup");
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

/* method: new_local of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_new00_local
static int tolua_CocoStudio_TouchGroup_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TouchGroup* tolua_ret = (TouchGroup*)  Mtolua_new((TouchGroup)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TouchGroup");
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

/* method: delete of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_delete00
static int tolua_CocoStudio_TouchGroup_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_create00
static int tolua_CocoStudio_TouchGroup_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TouchGroup* tolua_ret = (TouchGroup*)  TouchGroup::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TouchGroup");
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

/* method: init of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_init00
static int tolua_CocoStudio_TouchGroup_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onEnter of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_onEnter00
static int tolua_CocoStudio_TouchGroup_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onExit of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_onExit00
static int tolua_CocoStudio_TouchGroup_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
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

/* method: onEnterTransitionDidFinish of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_onEnterTransitionDidFinish00
static int tolua_CocoStudio_TouchGroup_onEnterTransitionDidFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnterTransitionDidFinish'", NULL);
#endif
  {
   self->onEnterTransitionDidFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnterTransitionDidFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_ccTouchBegan00
static int tolua_CocoStudio_TouchGroup_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(pTouch,pEvent);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_ccTouchMoved00
static int tolua_CocoStudio_TouchGroup_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_ccTouchEnded00
static int tolua_CocoStudio_TouchGroup_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchCancelled of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_ccTouchCancelled00
static int tolua_CocoStudio_TouchGroup_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
  {
   self->ccTouchCancelled(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addWidget of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_addWidget00
static int tolua_CocoStudio_TouchGroup_addWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  Widget* widget = ((Widget*)  tolua_tousertype(tolua_S,2,0));
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

/* method: removeWidget of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_removeWidget00
static int tolua_CocoStudio_TouchGroup_removeWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Widget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  Widget* widget = ((Widget*)  tolua_tousertype(tolua_S,2,0));
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

/* method: getWidgetByTag of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_getWidgetByTag00
static int tolua_CocoStudio_TouchGroup_getWidgetByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetByTag'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->getWidgetByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: getWidgetByName of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_getWidgetByName00
static int tolua_CocoStudio_TouchGroup_getWidgetByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetByName'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->getWidgetByName(name);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: clear of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_clear00
static int tolua_CocoStudio_TouchGroup_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getRootWidget of class  TouchGroup */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_TouchGroup_getRootWidget00
static int tolua_CocoStudio_TouchGroup_getRootWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TouchGroup",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TouchGroup* self = (TouchGroup*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootWidget'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->getRootWidget();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: playBackgroundMusic of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_playBackgroundMusic02
static int tolua_CocoStudio_CCComAudio_playBackgroundMusic02(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playBackgroundMusic'", NULL);
#endif
  {
   self->playBackgroundMusic();
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_CCComAudio_playBackgroundMusic01(tolua_S);
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

/* method: playEffect of class  CCComAudio */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_CCComAudio_playEffect02
static int tolua_CocoStudio_CCComAudio_playEffect02(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->playEffect();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CocoStudio_CCComAudio_playEffect01(tolua_S);
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
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: purge of class  ActionManager */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionManager_purge00
static int tolua_CocoStudio_ActionManager_purge00(lua_State* tolua_S)
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
   ActionManager::purge();
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

/* method: purge of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_purge00
static int tolua_CocoStudio_SceneReader_purge00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purge'", NULL);
#endif
  {
   self->purge();
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
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneReader* self = (SceneReader*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  AttachComponentType eAttachComponent = ((AttachComponentType) (int)  tolua_tonumber(tolua_S,3,ATTACH_EMPTY_NODE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createNodeWithSceneFile'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->createNodeWithSceneFile(pszFileName,eAttachComponent);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
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

/* method: getNodeByTag of class  SceneReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_SceneReader_getNodeByTag00
static int tolua_CocoStudio_SceneReader_getNodeByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneReader",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneReader* self = (SceneReader*)  tolua_tousertype(tolua_S,1,0);
  int nTag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodeByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNodeByTag(nTag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodeByTag'.",&tolua_err);
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

/* method: purge of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_purge00
static int tolua_CocoStudio_GUIReader_purge00(lua_State* tolua_S)
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
   GUIReader::purge();
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
   Widget* tolua_ret = (Widget*)  self->widgetFromJsonFile(fileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
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

/* method: widgetFromBinaryFile of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_widgetFromBinaryFile00
static int tolua_CocoStudio_GUIReader_widgetFromBinaryFile00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'widgetFromBinaryFile'", NULL);
#endif
  {
   Widget* tolua_ret = (Widget*)  self->widgetFromBinaryFile(fileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Widget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'widgetFromBinaryFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersionInteger of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_getVersionInteger00
static int tolua_CocoStudio_GUIReader_getVersionInteger00(lua_State* tolua_S)
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
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersionInteger'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getVersionInteger(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersionInteger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: storeFileDesignSize of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_storeFileDesignSize00
static int tolua_CocoStudio_GUIReader_storeFileDesignSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GUIReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GUIReader* self = (GUIReader*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'storeFileDesignSize'", NULL);
#endif
  {
   self->storeFileDesignSize(fileName,*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'storeFileDesignSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDesignSize of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_getFileDesignSize00
static int tolua_CocoStudio_GUIReader_getFileDesignSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUIReader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUIReader* self = (const GUIReader*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDesignSize'", NULL);
#endif
  {
   const CCSize tolua_ret = (const CCSize)  self->getFileDesignSize(fileName);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"const CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDesignSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFilePath of class  GUIReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_GUIReader_getFilePath00
static int tolua_CocoStudio_GUIReader_getFilePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const GUIReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const GUIReader* self = (const GUIReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFilePath'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getFilePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFilePath'.",&tolua_err);
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

/* method: new of class  RichElement */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElement_new00
static int tolua_CocoStudio_RichElement_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElement* tolua_ret = (RichElement*)  Mtolua_new((RichElement)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElement");
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

/* method: new_local of class  RichElement */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElement_new00_local
static int tolua_CocoStudio_RichElement_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElement* tolua_ret = (RichElement*)  Mtolua_new((RichElement)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElement");
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

/* method: delete of class  RichElement */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElement_delete00
static int tolua_CocoStudio_RichElement_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElement* self = (RichElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  RichElement */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElement_init00
static int tolua_CocoStudio_RichElement_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElement* self = (RichElement*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(tag,*color,opacity);
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

/* method: new of class  RichElementText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementText_new00
static int tolua_CocoStudio_RichElementText_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElementText* tolua_ret = (RichElementText*)  Mtolua_new((RichElementText)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementText");
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

/* method: new_local of class  RichElementText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementText_new00_local
static int tolua_CocoStudio_RichElementText_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElementText* tolua_ret = (RichElementText*)  Mtolua_new((RichElementText)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementText");
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

/* method: delete of class  RichElementText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementText_delete00
static int tolua_CocoStudio_RichElementText_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElementText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElementText* self = (RichElementText*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  RichElementText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementText_init00
static int tolua_CocoStudio_RichElementText_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElementText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElementText* self = (RichElementText*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,6,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(tag,*color,opacity,text,fontName,fontSize);
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

/* method: create of class  RichElementText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementText_create00
static int tolua_CocoStudio_RichElementText_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,6,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,7,0));
  {
   RichElementText* tolua_ret = (RichElementText*)  RichElementText::create(tag,*color,opacity,text,fontName,fontSize);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementText");
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

/* method: new of class  RichElementImage */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementImage_new00
static int tolua_CocoStudio_RichElementImage_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElementImage* tolua_ret = (RichElementImage*)  Mtolua_new((RichElementImage)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementImage");
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

/* method: new_local of class  RichElementImage */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementImage_new00_local
static int tolua_CocoStudio_RichElementImage_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElementImage* tolua_ret = (RichElementImage*)  Mtolua_new((RichElementImage)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementImage");
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

/* method: delete of class  RichElementImage */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementImage_delete00
static int tolua_CocoStudio_RichElementImage_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElementImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElementImage* self = (RichElementImage*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  RichElementImage */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementImage_init00
static int tolua_CocoStudio_RichElementImage_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElementImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElementImage* self = (RichElementImage*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
  const char* filePath = ((const char*)  tolua_tostring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(tag,*color,opacity,filePath);
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

/* method: create of class  RichElementImage */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementImage_create00
static int tolua_CocoStudio_RichElementImage_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
  const char* filePath = ((const char*)  tolua_tostring(tolua_S,5,0));
  {
   RichElementImage* tolua_ret = (RichElementImage*)  RichElementImage::create(tag,*color,opacity,filePath);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementImage");
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

/* method: new of class  RichElementCustomNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementCustomNode_new00
static int tolua_CocoStudio_RichElementCustomNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementCustomNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElementCustomNode* tolua_ret = (RichElementCustomNode*)  Mtolua_new((RichElementCustomNode)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementCustomNode");
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

/* method: new_local of class  RichElementCustomNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementCustomNode_new00_local
static int tolua_CocoStudio_RichElementCustomNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementCustomNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichElementCustomNode* tolua_ret = (RichElementCustomNode*)  Mtolua_new((RichElementCustomNode)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementCustomNode");
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

/* method: delete of class  RichElementCustomNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementCustomNode_delete00
static int tolua_CocoStudio_RichElementCustomNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElementCustomNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElementCustomNode* self = (RichElementCustomNode*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  RichElementCustomNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementCustomNode_init00
static int tolua_CocoStudio_RichElementCustomNode_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichElementCustomNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichElementCustomNode* self = (RichElementCustomNode*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
  CCNode* customNode = ((CCNode*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(tag,*color,opacity,customNode);
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

/* method: create of class  RichElementCustomNode */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichElementCustomNode_create00
static int tolua_CocoStudio_RichElementCustomNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichElementCustomNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  GLubyte opacity = ((GLubyte) (int)  tolua_tonumber(tolua_S,4,0));
  CCNode* customNode = ((CCNode*)  tolua_tousertype(tolua_S,5,0));
  {
   RichElementCustomNode* tolua_ret = (RichElementCustomNode*)  RichElementCustomNode::create(tag,*color,opacity,customNode);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichElementCustomNode");
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

/* method: new of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_new00
static int tolua_CocoStudio_RichText_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichText* tolua_ret = (RichText*)  Mtolua_new((RichText)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichText");
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

/* method: new_local of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_new00_local
static int tolua_CocoStudio_RichText_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichText* tolua_ret = (RichText*)  Mtolua_new((RichText)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichText");
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

/* method: delete of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_delete00
static int tolua_CocoStudio_RichText_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_create00
static int tolua_CocoStudio_RichText_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RichText* tolua_ret = (RichText*)  RichText::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"RichText");
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

/* method: insertElement of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_insertElement00
static int tolua_CocoStudio_RichText_insertElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RichElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
  RichElement* element = ((RichElement*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertElement'", NULL);
#endif
  {
   self->insertElement(element,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pushBackElement of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_pushBackElement00
static int tolua_CocoStudio_RichText_pushBackElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RichElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
  RichElement* element = ((RichElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushBackElement'", NULL);
#endif
  {
   self->pushBackElement(element);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushBackElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeElement of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_removeElement00
static int tolua_CocoStudio_RichText_removeElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeElement'", NULL);
#endif
  {
   self->removeElement(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeElement of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_removeElement01
static int tolua_CocoStudio_RichText_removeElement01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RichElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
  RichElement* element = ((RichElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeElement'", NULL);
#endif
  {
   self->removeElement(element);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_RichText_removeElement00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_visit00
static int tolua_CocoStudio_RichText_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setVerticalSpace of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_setVerticalSpace00
static int tolua_CocoStudio_RichText_setVerticalSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
  float space = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVerticalSpace'", NULL);
#endif
  {
   self->setVerticalSpace(space);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVerticalSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_setAnchorPoint00
static int tolua_CocoStudio_RichText_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getContentSize of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_getContentSize00
static int tolua_CocoStudio_RichText_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RichText* self = (const RichText*)  tolua_tousertype(tolua_S,1,0);
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

/* method: formatText of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_formatText00
static int tolua_CocoStudio_RichText_formatText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'formatText'", NULL);
#endif
  {
   self->formatText();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'formatText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ignoreContentAdaptWithSize of class  RichText */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_RichText_ignoreContentAdaptWithSize00
static int tolua_CocoStudio_RichText_ignoreContentAdaptWithSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RichText",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RichText* self = (RichText*)  tolua_tousertype(tolua_S,1,0);
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

/* method: create of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_create00
static int tolua_CocoStudio_ActionTimeline_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  cocostudio::timeline::ActionTimeline::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
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

/* method: new of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_new00
static int tolua_CocoStudio_ActionTimeline_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  Mtolua_new((cocostudio::timeline::ActionTimeline)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
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

/* method: new_local of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_new00_local
static int tolua_CocoStudio_ActionTimeline_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  Mtolua_new((cocostudio::timeline::ActionTimeline)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
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

/* method: delete of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_delete00
static int tolua_CocoStudio_ActionTimeline_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_init00
static int tolua_CocoStudio_ActionTimeline_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: gotoFrameAndPlay of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay00
static int tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  int startIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoFrameAndPlay'", NULL);
#endif
  {
   self->gotoFrameAndPlay(startIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoFrameAndPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoFrameAndPlay of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay01
static int tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  int startIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  bool loop = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoFrameAndPlay'", NULL);
#endif
  {
   self->gotoFrameAndPlay(startIndex,loop);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoFrameAndPlay of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay02
static int tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  int startIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int endIndex = ((int)  tolua_tonumber(tolua_S,3,0));
  bool loop = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoFrameAndPlay'", NULL);
#endif
  {
   self->gotoFrameAndPlay(startIndex,endIndex,loop);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoFrameAndPause of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_gotoFrameAndPause00
static int tolua_CocoStudio_ActionTimeline_gotoFrameAndPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  int startIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoFrameAndPause'", NULL);
#endif
  {
   self->gotoFrameAndPause(startIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoFrameAndPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_pause00
static int tolua_CocoStudio_ActionTimeline_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: resume of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_resume00
static int tolua_CocoStudio_ActionTimeline_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isPlaying of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_isPlaying00
static int tolua_CocoStudio_ActionTimeline_isPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setTimeSpeed of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_setTimeSpeed00
static int tolua_CocoStudio_ActionTimeline_setTimeSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  float speed = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeSpeed'", NULL);
#endif
  {
   self->setTimeSpeed(speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeSpeed of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_getTimeSpeed00
static int tolua_CocoStudio_ActionTimeline_getTimeSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeSpeed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTimeSpeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDuration of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_setDuration00
static int tolua_CocoStudio_ActionTimeline_setDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  int duration = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDuration'", NULL);
#endif
  {
   self->setDuration(duration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDuration of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_getDuration00
static int tolua_CocoStudio_ActionTimeline_getDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDuration'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDuration();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStartFrame of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_getStartFrame00
static int tolua_CocoStudio_ActionTimeline_getStartFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStartFrame'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getStartFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStartFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEndFrame of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_getEndFrame00
static int tolua_CocoStudio_ActionTimeline_getEndFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEndFrame'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getEndFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEndFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentFrame of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_getCurrentFrame00
static int tolua_CocoStudio_ActionTimeline_getCurrentFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentFrame'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurrentFrame();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTimeline of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_addTimeline00
static int tolua_CocoStudio_ActionTimeline_addTimeline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  cocostudio::timeline::Timeline* timeline = ((cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTimeline'", NULL);
#endif
  {
   self->addTimeline(timeline);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTimeline of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_removeTimeline00
static int tolua_CocoStudio_ActionTimeline_removeTimeline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  cocostudio::timeline::Timeline* timeline = ((cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTimeline'", NULL);
#endif
  {
   self->removeTimeline(timeline);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clone of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_clone00
static int tolua_CocoStudio_ActionTimeline_clone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clone'", NULL);
#endif
  {
     cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  self->clone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
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

/* method: reverse of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_reverse00
static int tolua_CocoStudio_ActionTimeline_reverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::ActionTimeline* self = (const cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverse'", NULL);
#endif
  {
    cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  self->reverse();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: step of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_step00
static int tolua_CocoStudio_ActionTimeline_step00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'step'", NULL);
#endif
  {
   self->step(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'step'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startWithTarget of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_startWithTarget00
static int tolua_CocoStudio_ActionTimeline_startWithTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"cocos2d::CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
  cocos2d::CCNode* target = ((cocos2d::CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startWithTarget'", NULL);
#endif
  {
   self->startWithTarget(target);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startWithTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDone of class  ActionTimeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimeline_isDone00
static int tolua_CocoStudio_ActionTimeline_isDone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::ActionTimeline* self = (cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDone'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDone();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_getInstance00
static int tolua_CocoStudio_ActionTimelineCache_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::ActionTimelineCache* tolua_ret = ( cocostudio::timeline::ActionTimelineCache*)cocostudio::timeline::ActionTimelineCache::getInstance();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimelineCache");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroyInstance of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_destroyInstance00
static int tolua_CocoStudio_ActionTimelineCache_destroyInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   cocostudio::timeline::ActionTimelineCache::destroyInstance();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroyInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_delete00
static int tolua_CocoStudio_ActionTimelineCache_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
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

/* method: purge of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_purge00
static int tolua_CocoStudio_ActionTimelineCache_purge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purge'", NULL);
#endif
  {
   self->purge();
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

/* method: init of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_init00
static int tolua_CocoStudio_ActionTimelineCache_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   self->init();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAction of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_removeAction00
static int tolua_CocoStudio_ActionTimelineCache_removeAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAction'", NULL);
#endif
  {
   self->removeAction(fileName);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAction of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_createAction00
static int tolua_CocoStudio_ActionTimelineCache_createAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createAction'", NULL);
#endif
  {
    cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  self->createAction(fileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadAnimationActionWithFile of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_loadAnimationActionWithFile00
static int tolua_CocoStudio_ActionTimelineCache_loadAnimationActionWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadAnimationActionWithFile'", NULL);
#endif
  {
    cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  self->loadAnimationActionWithFile(fileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadAnimationActionWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadAnimationActionWithContent of class  ActionTimelineCache */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_ActionTimelineCache_loadAnimationActionWithContent00
static int tolua_CocoStudio_ActionTimelineCache_loadAnimationActionWithContent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ActionTimelineCache",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::ActionTimelineCache* self = (cocostudio::timeline::ActionTimelineCache*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string content = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadAnimationActionWithContent'", NULL);
#endif
  {
   cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  self->loadAnimationActionWithContent(fileName,content);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
   tolua_pushcppstring(tolua_S,(const char*)fileName);
   tolua_pushcppstring(tolua_S,(const char*)content);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadAnimationActionWithContent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_getInstance00
static int tolua_CocoStudio_NodeReader_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::NodeReader* tolua_ret = (cocostudio::timeline::NodeReader*)  cocostudio::timeline::NodeReader::getInstance();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"NodeReader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroyInstance of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_destroyInstance00
static int tolua_CocoStudio_NodeReader_destroyInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::NodeReader::destroyInstance();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroyInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_new00
static int tolua_CocoStudio_NodeReader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   cocostudio::timeline::NodeReader* tolua_ret = (cocostudio::timeline::NodeReader*)  Mtolua_new((cocostudio::timeline::NodeReader)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"NodeReader");
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

/* method: new_local of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_new00_local
static int tolua_CocoStudio_NodeReader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   cocostudio::timeline::NodeReader* tolua_ret = (cocostudio::timeline::NodeReader*)  Mtolua_new((cocostudio::timeline::NodeReader)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"NodeReader");
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

/* method: delete of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_delete00
static int tolua_CocoStudio_NodeReader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
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

/* method: purge of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_purge00
static int tolua_CocoStudio_NodeReader_purge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purge'", NULL);
#endif
  {
   self->purge();
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

/* method: init of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_init00
static int tolua_CocoStudio_NodeReader_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   self->init();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createNode of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_createNode00
static int tolua_CocoStudio_NodeReader_createNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->createNode(filename);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadNodeWithFile of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_loadNodeWithFile00
static int tolua_CocoStudio_NodeReader_loadNodeWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadNodeWithFile'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->loadNodeWithFile(fileName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadNodeWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadNodeWithContent of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_loadNodeWithContent00
static int tolua_CocoStudio_NodeReader_loadNodeWithContent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
  const std::string content = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadNodeWithContent'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->loadNodeWithContent(content);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
   tolua_pushcppstring(tolua_S,(const char*)content);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadNodeWithContent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRecordJsonPath of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_setRecordJsonPath00
static int tolua_CocoStudio_NodeReader_setRecordJsonPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
  bool record = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRecordJsonPath'", NULL);
#endif
  {
   self->setRecordJsonPath(record);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRecordJsonPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRecordJsonPath of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_isRecordJsonPath00
static int tolua_CocoStudio_NodeReader_isRecordJsonPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::NodeReader* self = (const cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRecordJsonPath'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRecordJsonPath();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRecordJsonPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setJsonPath of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_setJsonPath00
static int tolua_CocoStudio_NodeReader_setJsonPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NodeReader",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
   cocostudio::timeline::NodeReader* self = (cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
  std::string jsonPath = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setJsonPath'", NULL);
#endif
  {
   self->setJsonPath(jsonPath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setJsonPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getJsonPath of class  NodeReader */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_NodeReader_getJsonPath00
static int tolua_CocoStudio_NodeReader_getJsonPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NodeReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::NodeReader* self = (const cocostudio::timeline::NodeReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getJsonPath'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getJsonPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getJsonPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_create00
static int tolua_CocoStudio_Timeline_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   cocostudio::timeline::Timeline* tolua_ret = (cocostudio::timeline::Timeline*)  cocostudio::timeline::Timeline::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Timeline");
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

/* method: new of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_new00
static int tolua_CocoStudio_Timeline_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::Timeline* tolua_ret = ( cocostudio::timeline::Timeline*)  Mtolua_new(( cocostudio::timeline::Timeline)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Timeline");
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

/* method: new_local of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_new00_local
static int tolua_CocoStudio_Timeline_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
    cocostudio::timeline::Timeline* tolua_ret = ( cocostudio::timeline::Timeline*)  Mtolua_new(( cocostudio::timeline::Timeline)());
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Timeline");
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

/* method: delete of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_delete00
static int tolua_CocoStudio_Timeline_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: init of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_init00
static int tolua_CocoStudio_Timeline_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: gotoFrame of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_gotoFrame00
static int tolua_CocoStudio_Timeline_gotoFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoFrame'", NULL);
#endif
  {
   self->gotoFrame(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stepToFrame of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_stepToFrame00
static int tolua_CocoStudio_Timeline_stepToFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stepToFrame'", NULL);
#endif
  {
   self->stepToFrame(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stepToFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrames of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_getFrames00
static int tolua_CocoStudio_Timeline_getFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrames'", NULL);
#endif
  {
   const cocos2d::CCArray* tolua_ret = (const cocos2d::CCArray*)  self->getFrames();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const cocos2d::CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addFrame of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_addFrame00
static int tolua_CocoStudio_Timeline_addFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Frame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  cocostudio::timeline::Frame* frame = ((cocostudio::timeline::Frame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFrame'", NULL);
#endif
  {
   self->addFrame(frame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insertFrame of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_insertFrame00
static int tolua_CocoStudio_Timeline_insertFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Frame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  cocostudio::timeline::Frame* frame = ((cocostudio::timeline::Frame*)  tolua_tousertype(tolua_S,2,0));
  int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertFrame'", NULL);
#endif
  {
   self->insertFrame(frame,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFrame of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_removeFrame00
static int tolua_CocoStudio_Timeline_removeFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Frame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  cocostudio::timeline::Frame* frame = ((cocostudio::timeline::Frame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFrame'", NULL);
#endif
  {
   self->removeFrame(frame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionTag of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_setActionTag00
static int tolua_CocoStudio_Timeline_setActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getActionTag of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_getActionTag00
static int tolua_CocoStudio_Timeline_getActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::Timeline* self = (const cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setNode of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_setNode00
static int tolua_CocoStudio_Timeline_setNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"cocos2d::CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  cocos2d::CCNode* node = ((cocos2d::CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNode'", NULL);
#endif
  {
   self->setNode(node);
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

/* method: getNode of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_getNode00
static int tolua_CocoStudio_Timeline_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::Timeline* self = (const cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'", NULL);
#endif
  {
   cocos2d::CCNode* tolua_ret = (cocos2d::CCNode*)  self->getNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cocos2d::CCNode");
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

/* method: setActionTimeline of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_setActionTimeline00
static int tolua_CocoStudio_Timeline_setActionTimeline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ActionTimeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
  cocostudio::timeline::ActionTimeline* action = ((cocostudio::timeline::ActionTimeline*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionTimeline'", NULL);
#endif
  {
   self->setActionTimeline(action);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionTimeline of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_getActionTimeline00
static int tolua_CocoStudio_Timeline_getActionTimeline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const cocostudio::timeline::Timeline* self = (const cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionTimeline'", NULL);
#endif
  {
   cocostudio::timeline::ActionTimeline* tolua_ret = (cocostudio::timeline::ActionTimeline*)  self->getActionTimeline();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ActionTimeline");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clone of class  Timeline */
#ifndef TOLUA_DISABLE_tolua_CocoStudio_Timeline_clone00
static int tolua_CocoStudio_Timeline_clone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timeline",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  cocostudio::timeline::Timeline* self = (cocostudio::timeline::Timeline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clone'", NULL);
#endif
  {
   cocostudio::timeline::Timeline* tolua_ret = (cocostudio::timeline::Timeline*)  self->clone();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Timeline");
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
   tolua_function(tolua_S,"play",tolua_CocoStudio_CCArmatureAnimation_play00);
   tolua_function(tolua_S,"play",tolua_CocoStudio_CCArmatureAnimation_play01);
   tolua_function(tolua_S,"playWithIndex",tolua_CocoStudio_CCArmatureAnimation_playWithIndex00);
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
   tolua_function(tolua_S,"changeDisplayWithIndex",tolua_CocoStudio_CCBone_changeDisplayWithIndex00);
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
   tolua_function(tolua_S,"changeDisplayWithIndex",tolua_CocoStudio_CCDisplayManager_changeDisplayWithIndex00);
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
  tolua_cclass(tolua_S,"Widget","Widget","CCNode",tolua_collect_Widget);
  #else
  tolua_cclass(tolua_S,"Widget","Widget","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Widget");
   tolua_function(tolua_S,"new",tolua_CocoStudio_Widget_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_Widget_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_Widget_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_Widget_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_Widget_create00);
   tolua_function(tolua_S,"setEnabled",tolua_CocoStudio_Widget_setEnabled00);
   tolua_function(tolua_S,"isEnabled",tolua_CocoStudio_Widget_isEnabled00);
   tolua_function(tolua_S,"setBright",tolua_CocoStudio_Widget_setBright00);
   tolua_function(tolua_S,"isBright",tolua_CocoStudio_Widget_isBright00);
   tolua_function(tolua_S,"setTouchEnabled",tolua_CocoStudio_Widget_setTouchEnabled00);
   tolua_function(tolua_S,"setBrightStyle",tolua_CocoStudio_Widget_setBrightStyle00);
   tolua_function(tolua_S,"isTouchEnabled",tolua_CocoStudio_Widget_isTouchEnabled00);
   tolua_function(tolua_S,"isFocused",tolua_CocoStudio_Widget_isFocused00);
   tolua_function(tolua_S,"setFocused",tolua_CocoStudio_Widget_setFocused00);
   tolua_function(tolua_S,"getLeftInParent",tolua_CocoStudio_Widget_getLeftInParent00);
   tolua_function(tolua_S,"getBottomInParent",tolua_CocoStudio_Widget_getBottomInParent00);
   tolua_function(tolua_S,"getRightInParent",tolua_CocoStudio_Widget_getRightInParent00);
   tolua_function(tolua_S,"getTopInParent",tolua_CocoStudio_Widget_getTopInParent00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_Widget_addChild00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_Widget_addChild01);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_Widget_addChild02);
   tolua_function(tolua_S,"getChildByTag",tolua_CocoStudio_Widget_getChildByTag00);
   tolua_function(tolua_S,"sortAllChildren",tolua_CocoStudio_Widget_sortAllChildren00);
   tolua_function(tolua_S,"getChildren",tolua_CocoStudio_Widget_getChildren00);
   tolua_function(tolua_S,"getChildrenCount",tolua_CocoStudio_Widget_getChildrenCount00);
   tolua_function(tolua_S,"removeFromParent",tolua_CocoStudio_Widget_removeFromParent00);
   tolua_function(tolua_S,"removeFromParentAndCleanup",tolua_CocoStudio_Widget_removeFromParentAndCleanup00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_Widget_removeChild00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_Widget_removeChild01);
   tolua_function(tolua_S,"removeChildByTag",tolua_CocoStudio_Widget_removeChildByTag00);
   tolua_function(tolua_S,"removeAllChildren",tolua_CocoStudio_Widget_removeAllChildren00);
   tolua_function(tolua_S,"removeAllChildrenWithCleanup",tolua_CocoStudio_Widget_removeAllChildrenWithCleanup00);
   tolua_function(tolua_S,"getChildByName",tolua_CocoStudio_Widget_getChildByName00);
   tolua_function(tolua_S,"addNode",tolua_CocoStudio_Widget_addNode00);
   tolua_function(tolua_S,"addNode",tolua_CocoStudio_Widget_addNode01);
   tolua_function(tolua_S,"addNode",tolua_CocoStudio_Widget_addNode02);
   tolua_function(tolua_S,"getNodeByTag",tolua_CocoStudio_Widget_getNodeByTag00);
   tolua_function(tolua_S,"getNodes",tolua_CocoStudio_Widget_getNodes00);
   tolua_function(tolua_S,"removeNode",tolua_CocoStudio_Widget_removeNode00);
   tolua_function(tolua_S,"removeNodeByTag",tolua_CocoStudio_Widget_removeNodeByTag00);
   tolua_function(tolua_S,"removeAllNodes",tolua_CocoStudio_Widget_removeAllNodes00);
   tolua_function(tolua_S,"visit",tolua_CocoStudio_Widget_visit00);
   tolua_function(tolua_S,"setPosition",tolua_CocoStudio_Widget_setPosition00);
   tolua_function(tolua_S,"setPositionPercent",tolua_CocoStudio_Widget_setPositionPercent00);
   tolua_function(tolua_S,"getPositionPercent",tolua_CocoStudio_Widget_getPositionPercent00);
   tolua_function(tolua_S,"setPositionType",tolua_CocoStudio_Widget_setPositionType00);
   tolua_function(tolua_S,"getPositionType",tolua_CocoStudio_Widget_getPositionType00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_Widget_setFlipX00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_Widget_isFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_Widget_setFlipY00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_Widget_isFlipY00);
   tolua_function(tolua_S,"setColor",tolua_CocoStudio_Widget_setColor00);
   tolua_function(tolua_S,"setOpacity",tolua_CocoStudio_Widget_setOpacity00);
   tolua_function(tolua_S,"getColor",tolua_CocoStudio_Widget_getColor00);
   tolua_function(tolua_S,"getOpacity",tolua_CocoStudio_Widget_getOpacity00);
   tolua_function(tolua_S,"didNotSelectSelf",tolua_CocoStudio_Widget_didNotSelectSelf00);
   tolua_function(tolua_S,"clippingParentAreaContainPoint",tolua_CocoStudio_Widget_clippingParentAreaContainPoint00);
   tolua_function(tolua_S,"checkChildInfo",tolua_CocoStudio_Widget_checkChildInfo00);
   tolua_function(tolua_S,"getTouchStartPos",tolua_CocoStudio_Widget_getTouchStartPos00);
   tolua_function(tolua_S,"getTouchMovePos",tolua_CocoStudio_Widget_getTouchMovePos00);
   tolua_function(tolua_S,"getTouchEndPos",tolua_CocoStudio_Widget_getTouchEndPos00);
   tolua_function(tolua_S,"setName",tolua_CocoStudio_Widget_setName00);
   tolua_function(tolua_S,"getName",tolua_CocoStudio_Widget_getName00);
   tolua_function(tolua_S,"getWidgetType",tolua_CocoStudio_Widget_getWidgetType00);
   tolua_function(tolua_S,"setSize",tolua_CocoStudio_Widget_setSize00);
   tolua_function(tolua_S,"setSizePercent",tolua_CocoStudio_Widget_setSizePercent00);
   tolua_function(tolua_S,"setSizeType",tolua_CocoStudio_Widget_setSizeType00);
   tolua_function(tolua_S,"getSizeType",tolua_CocoStudio_Widget_getSizeType00);
   tolua_function(tolua_S,"getSize",tolua_CocoStudio_Widget_getSize00);
   tolua_function(tolua_S,"getLayoutSize",tolua_CocoStudio_Widget_getLayoutSize00);
   tolua_function(tolua_S,"getSizePercent",tolua_CocoStudio_Widget_getSizePercent00);
   tolua_function(tolua_S,"getCustomSize",tolua_CocoStudio_Widget_getCustomSize00);
   tolua_function(tolua_S,"hitTest",tolua_CocoStudio_Widget_hitTest00);
   tolua_function(tolua_S,"onTouchBegan",tolua_CocoStudio_Widget_onTouchBegan00);
   tolua_function(tolua_S,"onTouchMoved",tolua_CocoStudio_Widget_onTouchMoved00);
   tolua_function(tolua_S,"onTouchEnded",tolua_CocoStudio_Widget_onTouchEnded00);
   tolua_function(tolua_S,"onTouchCancelled",tolua_CocoStudio_Widget_onTouchCancelled00);
   tolua_function(tolua_S,"setLayoutParameter",tolua_CocoStudio_Widget_setLayoutParameter00);
   tolua_function(tolua_S,"getLayoutParameter",tolua_CocoStudio_Widget_getLayoutParameter00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_Widget_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"isIgnoreContentAdaptWithSize",tolua_CocoStudio_Widget_isIgnoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getWorldPosition",tolua_CocoStudio_Widget_getWorldPosition00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_Widget_getVirtualRenderer00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_Widget_getContentSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_Widget_getDescription00);
   tolua_function(tolua_S,"clone",tolua_CocoStudio_Widget_clone00);
   tolua_function(tolua_S,"onEnter",tolua_CocoStudio_Widget_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_CocoStudio_Widget_onExit00);
   tolua_function(tolua_S,"updateSizeAndPosition",tolua_CocoStudio_Widget_updateSizeAndPosition00);
   tolua_function(tolua_S,"updateSizeAndPosition",tolua_CocoStudio_Widget_updateSizeAndPosition01);
   tolua_function(tolua_S,"setActionTag",tolua_CocoStudio_Widget_setActionTag00);
   tolua_function(tolua_S,"getActionTag",tolua_CocoStudio_Widget_getActionTag00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LAYOUT_COLOR_NONE",LAYOUT_COLOR_NONE);
  tolua_constant(tolua_S,"LAYOUT_COLOR_SOLID",LAYOUT_COLOR_SOLID);
  tolua_constant(tolua_S,"LAYOUT_COLOR_GRADIENT",LAYOUT_COLOR_GRADIENT);
  tolua_constant(tolua_S,"LAYOUT_ABSOLUTE",LAYOUT_ABSOLUTE);
  tolua_constant(tolua_S,"LAYOUT_LINEAR_VERTICAL",LAYOUT_LINEAR_VERTICAL);
  tolua_constant(tolua_S,"LAYOUT_LINEAR_HORIZONTAL",LAYOUT_LINEAR_HORIZONTAL);
  tolua_constant(tolua_S,"LAYOUT_RELATIVE",LAYOUT_RELATIVE);
  tolua_constant(tolua_S,"LAYOUT_CLIPPING_STENCIL",LAYOUT_CLIPPING_STENCIL);
  tolua_constant(tolua_S,"LAYOUT_CLIPPING_SCISSOR",LAYOUT_CLIPPING_SCISSOR);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Layout","Layout","Widget",tolua_collect_Layout);
  #else
  tolua_cclass(tolua_S,"Layout","Layout","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Layout");
   tolua_function(tolua_S,"new",tolua_CocoStudio_Layout_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_Layout_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_Layout_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_Layout_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_Layout_create00);
   tolua_function(tolua_S,"setBackGroundImage",tolua_CocoStudio_Layout_setBackGroundImage00);
   tolua_function(tolua_S,"setBackGroundImageCapInsets",tolua_CocoStudio_Layout_setBackGroundImageCapInsets00);
   tolua_function(tolua_S,"getBackGroundImageCapInsets",tolua_CocoStudio_Layout_getBackGroundImageCapInsets00);
   tolua_function(tolua_S,"setBackGroundColorType",tolua_CocoStudio_Layout_setBackGroundColorType00);
   tolua_function(tolua_S,"getBackGroundColorType",tolua_CocoStudio_Layout_getBackGroundColorType00);
   tolua_function(tolua_S,"setBackGroundImageScale9Enabled",tolua_CocoStudio_Layout_setBackGroundImageScale9Enabled00);
   tolua_function(tolua_S,"isBackGroundImageScale9Enabled",tolua_CocoStudio_Layout_isBackGroundImageScale9Enabled00);
   tolua_function(tolua_S,"setBackGroundColor",tolua_CocoStudio_Layout_setBackGroundColor00);
   tolua_function(tolua_S,"getBackGroundColor",tolua_CocoStudio_Layout_getBackGroundColor00);
   tolua_function(tolua_S,"setBackGroundColor",tolua_CocoStudio_Layout_setBackGroundColor01);
   tolua_function(tolua_S,"getBackGroundStartColor",tolua_CocoStudio_Layout_getBackGroundStartColor00);
   tolua_function(tolua_S,"getBackGroundEndColor",tolua_CocoStudio_Layout_getBackGroundEndColor00);
   tolua_function(tolua_S,"setBackGroundColorOpacity",tolua_CocoStudio_Layout_setBackGroundColorOpacity00);
   tolua_function(tolua_S,"getBackGroundColorOpacity",tolua_CocoStudio_Layout_getBackGroundColorOpacity00);
   tolua_function(tolua_S,"setBackGroundColorVector",tolua_CocoStudio_Layout_setBackGroundColorVector00);
   tolua_function(tolua_S,"getBackGroundColorVector",tolua_CocoStudio_Layout_getBackGroundColorVector00);
   tolua_function(tolua_S,"setBackGroundImageColor",tolua_CocoStudio_Layout_setBackGroundImageColor00);
   tolua_function(tolua_S,"setBackGroundImageOpacity",tolua_CocoStudio_Layout_setBackGroundImageOpacity00);
   tolua_function(tolua_S,"getBackGroundImageColor",tolua_CocoStudio_Layout_getBackGroundImageColor00);
   tolua_function(tolua_S,"getBackGroundImageOpacity",tolua_CocoStudio_Layout_getBackGroundImageOpacity00);
   tolua_function(tolua_S,"removeBackGroundImage",tolua_CocoStudio_Layout_removeBackGroundImage00);
   tolua_function(tolua_S,"getBackGroundImageTextureSize",tolua_CocoStudio_Layout_getBackGroundImageTextureSize00);
   tolua_function(tolua_S,"setClippingEnabled",tolua_CocoStudio_Layout_setClippingEnabled00);
   tolua_function(tolua_S,"setClippingType",tolua_CocoStudio_Layout_setClippingType00);
   tolua_function(tolua_S,"getClippingType",tolua_CocoStudio_Layout_getClippingType00);
   tolua_function(tolua_S,"isClippingEnabled",tolua_CocoStudio_Layout_isClippingEnabled00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_Layout_getDescription00);
   tolua_function(tolua_S,"setLayoutType",tolua_CocoStudio_Layout_setLayoutType00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_Layout_getLayoutType00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_Layout_addChild00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_Layout_addChild01);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_Layout_addChild02);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_Layout_removeChild00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_Layout_removeChild01);
   tolua_function(tolua_S,"removeAllChildren",tolua_CocoStudio_Layout_removeAllChildren00);
   tolua_function(tolua_S,"removeAllChildrenWithCleanup",tolua_CocoStudio_Layout_removeAllChildrenWithCleanup00);
   tolua_function(tolua_S,"visit",tolua_CocoStudio_Layout_visit00);
   tolua_function(tolua_S,"sortAllChildren",tolua_CocoStudio_Layout_sortAllChildren00);
   tolua_function(tolua_S,"requestDoLayout",tolua_CocoStudio_Layout_requestDoLayout00);
   tolua_function(tolua_S,"onEnter",tolua_CocoStudio_Layout_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_CocoStudio_Layout_onExit00);
   tolua_function(tolua_S,"hitTest",tolua_CocoStudio_Layout_hitTest00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Button","Button","Widget",tolua_collect_Button);
  #else
  tolua_cclass(tolua_S,"Button","Button","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Button");
   tolua_function(tolua_S,"new",tolua_CocoStudio_Button_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_Button_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_Button_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_Button_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_Button_create00);
   tolua_function(tolua_S,"loadTextures",tolua_CocoStudio_Button_loadTextures00);
   tolua_function(tolua_S,"loadTextureNormal",tolua_CocoStudio_Button_loadTextureNormal00);
   tolua_function(tolua_S,"loadTexturePressed",tolua_CocoStudio_Button_loadTexturePressed00);
   tolua_function(tolua_S,"loadTextureDisabled",tolua_CocoStudio_Button_loadTextureDisabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_Button_setCapInsets00);
   tolua_function(tolua_S,"setCapInsetsNormalRenderer",tolua_CocoStudio_Button_setCapInsetsNormalRenderer00);
   tolua_function(tolua_S,"getCapInsetNormalRenderer",tolua_CocoStudio_Button_getCapInsetNormalRenderer00);
   tolua_function(tolua_S,"setCapInsetsPressedRenderer",tolua_CocoStudio_Button_setCapInsetsPressedRenderer00);
   tolua_function(tolua_S,"getCapInsetPressedRenderer",tolua_CocoStudio_Button_getCapInsetPressedRenderer00);
   tolua_function(tolua_S,"setCapInsetsDisabledRenderer",tolua_CocoStudio_Button_setCapInsetsDisabledRenderer00);
   tolua_function(tolua_S,"getCapInsetDisabledRenderer",tolua_CocoStudio_Button_getCapInsetDisabledRenderer00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_Button_setAnchorPoint00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_Button_setScale9Enabled00);
   tolua_function(tolua_S,"isScale9Enabled",tolua_CocoStudio_Button_isScale9Enabled00);
   tolua_function(tolua_S,"setPressedActionEnabled",tolua_CocoStudio_Button_setPressedActionEnabled00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_Button_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_Button_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_Button_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_Button_getDescription00);
   tolua_function(tolua_S,"setTitleText",tolua_CocoStudio_Button_setTitleText00);
   tolua_function(tolua_S,"getTitleText",tolua_CocoStudio_Button_getTitleText00);
   tolua_function(tolua_S,"setTitleColor",tolua_CocoStudio_Button_setTitleColor00);
   tolua_function(tolua_S,"getTitleColor",tolua_CocoStudio_Button_getTitleColor00);
   tolua_function(tolua_S,"setTitleFontSize",tolua_CocoStudio_Button_setTitleFontSize00);
   tolua_function(tolua_S,"getTitleFontSize",tolua_CocoStudio_Button_getTitleFontSize00);
   tolua_function(tolua_S,"setTitleFontName",tolua_CocoStudio_Button_setTitleFontName00);
   tolua_function(tolua_S,"getTitleFontName",tolua_CocoStudio_Button_getTitleFontName00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CHECKBOX_STATE_EVENT_SELECTED",CHECKBOX_STATE_EVENT_SELECTED);
  tolua_constant(tolua_S,"CHECKBOX_STATE_EVENT_UNSELECTED",CHECKBOX_STATE_EVENT_UNSELECTED);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CheckBox","CheckBox","Widget",tolua_collect_CheckBox);
  #else
  tolua_cclass(tolua_S,"CheckBox","CheckBox","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CheckBox");
   tolua_function(tolua_S,"new",tolua_CocoStudio_CheckBox_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_CheckBox_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_CheckBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_CheckBox_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_CheckBox_create00);
   tolua_function(tolua_S,"loadTextures",tolua_CocoStudio_CheckBox_loadTextures00);
   tolua_function(tolua_S,"loadTextureBackGround",tolua_CocoStudio_CheckBox_loadTextureBackGround00);
   tolua_function(tolua_S,"loadTextureBackGroundSelected",tolua_CocoStudio_CheckBox_loadTextureBackGroundSelected00);
   tolua_function(tolua_S,"loadTextureFrontCross",tolua_CocoStudio_CheckBox_loadTextureFrontCross00);
   tolua_function(tolua_S,"loadTextureBackGroundDisabled",tolua_CocoStudio_CheckBox_loadTextureBackGroundDisabled00);
   tolua_function(tolua_S,"loadTextureFrontCrossDisabled",tolua_CocoStudio_CheckBox_loadTextureFrontCrossDisabled00);
   tolua_function(tolua_S,"setSelectedState",tolua_CocoStudio_CheckBox_setSelectedState00);
   tolua_function(tolua_S,"getSelectedState",tolua_CocoStudio_CheckBox_getSelectedState00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_CheckBox_setAnchorPoint00);
   tolua_function(tolua_S,"onTouchEnded",tolua_CocoStudio_CheckBox_onTouchEnded00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_CheckBox_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_CheckBox_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_CheckBox_getDescription00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ImageView","ImageView","Widget",tolua_collect_ImageView);
  #else
  tolua_cclass(tolua_S,"ImageView","ImageView","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ImageView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_ImageView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_ImageView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_ImageView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ImageView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_ImageView_create00);
   tolua_function(tolua_S,"loadTexture",tolua_CocoStudio_ImageView_loadTexture00);
   tolua_function(tolua_S,"setTextureRect",tolua_CocoStudio_ImageView_setTextureRect00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_ImageView_setScale9Enabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_ImageView_setCapInsets00);
   tolua_function(tolua_S,"setFlipX",tolua_CocoStudio_ImageView_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_CocoStudio_ImageView_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_CocoStudio_ImageView_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_CocoStudio_ImageView_isFlipY00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_ImageView_setAnchorPoint00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_ImageView_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_ImageView_getDescription00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_ImageView_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_ImageView_getVirtualRenderer00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Label","Label","Widget",tolua_collect_Label);
  #else
  tolua_cclass(tolua_S,"Label","Label","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Label");
   tolua_function(tolua_S,"new",tolua_CocoStudio_Label_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_Label_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_Label_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_Label_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_Label_create00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_Label_setText00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_Label_getStringValue00);
   tolua_function(tolua_S,"getStringLength",tolua_CocoStudio_Label_getStringLength00);
   tolua_function(tolua_S,"setFontSize",tolua_CocoStudio_Label_setFontSize00);
   tolua_function(tolua_S,"getFontSize",tolua_CocoStudio_Label_getFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_CocoStudio_Label_setFontName00);
   tolua_function(tolua_S,"getFontName",tolua_CocoStudio_Label_getFontName00);
   tolua_function(tolua_S,"setTouchScaleChangeEnabled",tolua_CocoStudio_Label_setTouchScaleChangeEnabled00);
   tolua_function(tolua_S,"isTouchScaleChangeEnabled",tolua_CocoStudio_Label_isTouchScaleChangeEnabled00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_Label_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_Label_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_Label_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_Label_getDescription00);
   tolua_function(tolua_S,"setTextAreaSize",tolua_CocoStudio_Label_setTextAreaSize00);
   tolua_function(tolua_S,"getTextAreaSize",tolua_CocoStudio_Label_getTextAreaSize00);
   tolua_function(tolua_S,"setTextHorizontalAlignment",tolua_CocoStudio_Label_setTextHorizontalAlignment00);
   tolua_function(tolua_S,"getTextHorizontalAlignment",tolua_CocoStudio_Label_getTextHorizontalAlignment00);
   tolua_function(tolua_S,"setTextVerticalAlignment",tolua_CocoStudio_Label_setTextVerticalAlignment00);
   tolua_function(tolua_S,"getTextVerticalAlignment",tolua_CocoStudio_Label_getTextVerticalAlignment00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LabelAtlas","LabelAtlas","Widget",tolua_collect_LabelAtlas);
  #else
  tolua_cclass(tolua_S,"LabelAtlas","LabelAtlas","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LabelAtlas");
   tolua_function(tolua_S,"new",tolua_CocoStudio_LabelAtlas_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_LabelAtlas_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_LabelAtlas_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_LabelAtlas_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_LabelAtlas_create00);
   tolua_function(tolua_S,"setProperty",tolua_CocoStudio_LabelAtlas_setProperty00);
   tolua_function(tolua_S,"setStringValue",tolua_CocoStudio_LabelAtlas_setStringValue00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_LabelAtlas_getStringValue00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_LabelAtlas_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_LabelAtlas_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_LabelAtlas_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_LabelAtlas_getDescription00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LabelBMFont","LabelBMFont","Widget",tolua_collect_LabelBMFont);
  #else
  tolua_cclass(tolua_S,"LabelBMFont","LabelBMFont","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LabelBMFont");
   tolua_function(tolua_S,"new",tolua_CocoStudio_LabelBMFont_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_LabelBMFont_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_LabelBMFont_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_LabelBMFont_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_LabelBMFont_create00);
   tolua_function(tolua_S,"setFntFile",tolua_CocoStudio_LabelBMFont_setFntFile00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_LabelBMFont_setText00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_LabelBMFont_getStringValue00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_LabelBMFont_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_LabelBMFont_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_LabelBMFont_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_LabelBMFont_getDescription00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LoadingBarTypeLeft",LoadingBarTypeLeft);
  tolua_constant(tolua_S,"LoadingBarTypeRight",LoadingBarTypeRight);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LoadingBar","LoadingBar","Widget",tolua_collect_LoadingBar);
  #else
  tolua_cclass(tolua_S,"LoadingBar","LoadingBar","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LoadingBar");
   tolua_function(tolua_S,"new",tolua_CocoStudio_LoadingBar_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_LoadingBar_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_LoadingBar_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_LoadingBar_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_LoadingBar_create00);
   tolua_function(tolua_S,"setDirection",tolua_CocoStudio_LoadingBar_setDirection00);
   tolua_function(tolua_S,"getDirection",tolua_CocoStudio_LoadingBar_getDirection00);
   tolua_function(tolua_S,"loadTexture",tolua_CocoStudio_LoadingBar_loadTexture00);
   tolua_function(tolua_S,"setPercent",tolua_CocoStudio_LoadingBar_setPercent00);
   tolua_function(tolua_S,"getPercent",tolua_CocoStudio_LoadingBar_getPercent00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_LoadingBar_setScale9Enabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_LoadingBar_setCapInsets00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_LoadingBar_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_LoadingBar_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_LoadingBar_getVirtualRenderer00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_LoadingBar_getDescription00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"SLIDER_PERCENTCHANGED",SLIDER_PERCENTCHANGED);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Slider","Slider","Widget",tolua_collect_Slider);
  #else
  tolua_cclass(tolua_S,"Slider","Slider","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Slider");
   tolua_function(tolua_S,"new",tolua_CocoStudio_Slider_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_Slider_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_Slider_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_Slider_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_Slider_create00);
   tolua_function(tolua_S,"loadBarTexture",tolua_CocoStudio_Slider_loadBarTexture00);
   tolua_function(tolua_S,"setScale9Enabled",tolua_CocoStudio_Slider_setScale9Enabled00);
   tolua_function(tolua_S,"isScale9Enabled",tolua_CocoStudio_Slider_isScale9Enabled00);
   tolua_function(tolua_S,"setCapInsets",tolua_CocoStudio_Slider_setCapInsets00);
   tolua_function(tolua_S,"setCapInsetsBarRenderer",tolua_CocoStudio_Slider_setCapInsetsBarRenderer00);
   tolua_function(tolua_S,"getCapInsetBarRenderer",tolua_CocoStudio_Slider_getCapInsetBarRenderer00);
   tolua_function(tolua_S,"setCapInsetProgressBarRebderer",tolua_CocoStudio_Slider_setCapInsetProgressBarRebderer00);
   tolua_function(tolua_S,"getCapInsetProgressBarRebderer",tolua_CocoStudio_Slider_getCapInsetProgressBarRebderer00);
   tolua_function(tolua_S,"loadSlidBallTextures",tolua_CocoStudio_Slider_loadSlidBallTextures00);
   tolua_function(tolua_S,"loadSlidBallTextureNormal",tolua_CocoStudio_Slider_loadSlidBallTextureNormal00);
   tolua_function(tolua_S,"loadSlidBallTexturePressed",tolua_CocoStudio_Slider_loadSlidBallTexturePressed00);
   tolua_function(tolua_S,"loadSlidBallTextureDisabled",tolua_CocoStudio_Slider_loadSlidBallTextureDisabled00);
   tolua_function(tolua_S,"loadProgressBarTexture",tolua_CocoStudio_Slider_loadProgressBarTexture00);
   tolua_function(tolua_S,"setPercent",tolua_CocoStudio_Slider_setPercent00);
   tolua_function(tolua_S,"getPercent",tolua_CocoStudio_Slider_getPercent00);
   tolua_function(tolua_S,"onTouchBegan",tolua_CocoStudio_Slider_onTouchBegan00);
   tolua_function(tolua_S,"onTouchMoved",tolua_CocoStudio_Slider_onTouchMoved00);
   tolua_function(tolua_S,"onTouchEnded",tolua_CocoStudio_Slider_onTouchEnded00);
   tolua_function(tolua_S,"onTouchCancelled",tolua_CocoStudio_Slider_onTouchCancelled00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_Slider_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_Slider_getVirtualRenderer00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_Slider_ignoreContentAdaptWithSize00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_Slider_getDescription00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_ATTACH_WITH_IME",TEXTFIELD_EVENT_ATTACH_WITH_IME);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_DETACH_WITH_IME",TEXTFIELD_EVENT_DETACH_WITH_IME);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_INSERT_TEXT",TEXTFIELD_EVENT_INSERT_TEXT);
  tolua_constant(tolua_S,"TEXTFIELD_EVENT_DELETE_BACKWARD",TEXTFIELD_EVENT_DELETE_BACKWARD);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TextField","TextField","Widget",tolua_collect_TextField);
  #else
  tolua_cclass(tolua_S,"TextField","TextField","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TextField");
   tolua_function(tolua_S,"new",tolua_CocoStudio_TextField_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_TextField_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_TextField_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_TextField_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_TextField_create00);
   tolua_function(tolua_S,"setTouchSize",tolua_CocoStudio_TextField_setTouchSize00);
   tolua_function(tolua_S,"getTouchSize",tolua_CocoStudio_TextField_getTouchSize00);
   tolua_function(tolua_S,"setTouchAreaEnabled",tolua_CocoStudio_TextField_setTouchAreaEnabled00);
   tolua_function(tolua_S,"hitTest",tolua_CocoStudio_TextField_hitTest00);
   tolua_function(tolua_S,"setText",tolua_CocoStudio_TextField_setText00);
   tolua_function(tolua_S,"setPlaceHolder",tolua_CocoStudio_TextField_setPlaceHolder00);
   tolua_function(tolua_S,"getPlaceHolder",tolua_CocoStudio_TextField_getPlaceHolder00);
   tolua_function(tolua_S,"setFontSize",tolua_CocoStudio_TextField_setFontSize00);
   tolua_function(tolua_S,"getFontSize",tolua_CocoStudio_TextField_getFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_CocoStudio_TextField_setFontName00);
   tolua_function(tolua_S,"getFontName",tolua_CocoStudio_TextField_getFontName00);
   tolua_function(tolua_S,"didNotSelectSelf",tolua_CocoStudio_TextField_didNotSelectSelf00);
   tolua_function(tolua_S,"getStringValue",tolua_CocoStudio_TextField_getStringValue00);
   tolua_function(tolua_S,"onTouchBegan",tolua_CocoStudio_TextField_onTouchBegan00);
   tolua_function(tolua_S,"setMaxLengthEnabled",tolua_CocoStudio_TextField_setMaxLengthEnabled00);
   tolua_function(tolua_S,"isMaxLengthEnabled",tolua_CocoStudio_TextField_isMaxLengthEnabled00);
   tolua_function(tolua_S,"setMaxLength",tolua_CocoStudio_TextField_setMaxLength00);
   tolua_function(tolua_S,"getMaxLength",tolua_CocoStudio_TextField_getMaxLength00);
   tolua_function(tolua_S,"setPasswordEnabled",tolua_CocoStudio_TextField_setPasswordEnabled00);
   tolua_function(tolua_S,"isPasswordEnabled",tolua_CocoStudio_TextField_isPasswordEnabled00);
   tolua_function(tolua_S,"setPasswordStyleText",tolua_CocoStudio_TextField_setPasswordStyleText00);
   tolua_function(tolua_S,"getPasswordStyleText",tolua_CocoStudio_TextField_getPasswordStyleText00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_TextField_update00);
   tolua_function(tolua_S,"getAttachWithIME",tolua_CocoStudio_TextField_getAttachWithIME00);
   tolua_function(tolua_S,"setAttachWithIME",tolua_CocoStudio_TextField_setAttachWithIME00);
   tolua_function(tolua_S,"getDetachWithIME",tolua_CocoStudio_TextField_getDetachWithIME00);
   tolua_function(tolua_S,"setDetachWithIME",tolua_CocoStudio_TextField_setDetachWithIME00);
   tolua_function(tolua_S,"getInsertText",tolua_CocoStudio_TextField_getInsertText00);
   tolua_function(tolua_S,"setInsertText",tolua_CocoStudio_TextField_setInsertText00);
   tolua_function(tolua_S,"getDeleteBackward",tolua_CocoStudio_TextField_getDeleteBackward00);
   tolua_function(tolua_S,"setDeleteBackward",tolua_CocoStudio_TextField_setDeleteBackward00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_TextField_setAnchorPoint00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_TextField_getDescription00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_TextField_getContentSize00);
   tolua_function(tolua_S,"getVirtualRenderer",tolua_CocoStudio_TextField_getVirtualRenderer00);
   tolua_function(tolua_S,"attachWithIME",tolua_CocoStudio_TextField_attachWithIME00);
   tolua_function(tolua_S,"onEnter",tolua_CocoStudio_TextField_onEnter00);
   tolua_function(tolua_S,"setTextAreaSize",tolua_CocoStudio_TextField_setTextAreaSize00);
   tolua_function(tolua_S,"setTextHorizontalAlignment",tolua_CocoStudio_TextField_setTextHorizontalAlignment00);
   tolua_function(tolua_S,"setTextVerticalAlignment",tolua_CocoStudio_TextField_setTextVerticalAlignment00);
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
  tolua_cclass(tolua_S,"ScrollView","ScrollView","Layout",tolua_collect_ScrollView);
  #else
  tolua_cclass(tolua_S,"ScrollView","ScrollView","Layout",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ScrollView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_ScrollView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_ScrollView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_ScrollView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ScrollView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_ScrollView_create00);
   tolua_function(tolua_S,"setDirection",tolua_CocoStudio_ScrollView_setDirection00);
   tolua_function(tolua_S,"getDirection",tolua_CocoStudio_ScrollView_getDirection00);
   tolua_function(tolua_S,"getInnerContainer",tolua_CocoStudio_ScrollView_getInnerContainer00);
   tolua_function(tolua_S,"scrollToBottom",tolua_CocoStudio_ScrollView_scrollToBottom00);
   tolua_function(tolua_S,"scrollToTop",tolua_CocoStudio_ScrollView_scrollToTop00);
   tolua_function(tolua_S,"scrollToLeft",tolua_CocoStudio_ScrollView_scrollToLeft00);
   tolua_function(tolua_S,"scrollToRight",tolua_CocoStudio_ScrollView_scrollToRight00);
   tolua_function(tolua_S,"scrollToTopLeft",tolua_CocoStudio_ScrollView_scrollToTopLeft00);
   tolua_function(tolua_S,"scrollToTopRight",tolua_CocoStudio_ScrollView_scrollToTopRight00);
   tolua_function(tolua_S,"scrollToBottomLeft",tolua_CocoStudio_ScrollView_scrollToBottomLeft00);
   tolua_function(tolua_S,"scrollToBottomRight",tolua_CocoStudio_ScrollView_scrollToBottomRight00);
   tolua_function(tolua_S,"scrollToPercentVertical",tolua_CocoStudio_ScrollView_scrollToPercentVertical00);
   tolua_function(tolua_S,"scrollToPercentHorizontal",tolua_CocoStudio_ScrollView_scrollToPercentHorizontal00);
   tolua_function(tolua_S,"scrollToPercentBothDirection",tolua_CocoStudio_ScrollView_scrollToPercentBothDirection00);
   tolua_function(tolua_S,"jumpToBottom",tolua_CocoStudio_ScrollView_jumpToBottom00);
   tolua_function(tolua_S,"jumpToTop",tolua_CocoStudio_ScrollView_jumpToTop00);
   tolua_function(tolua_S,"jumpToLeft",tolua_CocoStudio_ScrollView_jumpToLeft00);
   tolua_function(tolua_S,"jumpToRight",tolua_CocoStudio_ScrollView_jumpToRight00);
   tolua_function(tolua_S,"jumpToTopLeft",tolua_CocoStudio_ScrollView_jumpToTopLeft00);
   tolua_function(tolua_S,"jumpToTopRight",tolua_CocoStudio_ScrollView_jumpToTopRight00);
   tolua_function(tolua_S,"jumpToBottomLeft",tolua_CocoStudio_ScrollView_jumpToBottomLeft00);
   tolua_function(tolua_S,"jumpToBottomRight",tolua_CocoStudio_ScrollView_jumpToBottomRight00);
   tolua_function(tolua_S,"jumpToPercentVertical",tolua_CocoStudio_ScrollView_jumpToPercentVertical00);
   tolua_function(tolua_S,"jumpToPercentHorizontal",tolua_CocoStudio_ScrollView_jumpToPercentHorizontal00);
   tolua_function(tolua_S,"jumpToPercentBothDirection",tolua_CocoStudio_ScrollView_jumpToPercentBothDirection00);
   tolua_function(tolua_S,"setInnerContainerSize",tolua_CocoStudio_ScrollView_setInnerContainerSize00);
   tolua_function(tolua_S,"getInnerContainerSize",tolua_CocoStudio_ScrollView_getInnerContainerSize00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_ScrollView_addChild00);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_ScrollView_addChild01);
   tolua_function(tolua_S,"addChild",tolua_CocoStudio_ScrollView_addChild02);
   tolua_function(tolua_S,"removeAllChildren",tolua_CocoStudio_ScrollView_removeAllChildren00);
   tolua_function(tolua_S,"removeAllChildrenWithCleanup",tolua_CocoStudio_ScrollView_removeAllChildrenWithCleanup00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_ScrollView_removeChild00);
   tolua_function(tolua_S,"removeChild",tolua_CocoStudio_ScrollView_removeChild01);
   tolua_function(tolua_S,"getChildren",tolua_CocoStudio_ScrollView_getChildren00);
   tolua_function(tolua_S,"getChildrenCount",tolua_CocoStudio_ScrollView_getChildrenCount00);
   tolua_function(tolua_S,"getChildByTag",tolua_CocoStudio_ScrollView_getChildByTag00);
   tolua_function(tolua_S,"getChildByName",tolua_CocoStudio_ScrollView_getChildByName00);
   tolua_function(tolua_S,"addNode",tolua_CocoStudio_ScrollView_addNode00);
   tolua_function(tolua_S,"addNode",tolua_CocoStudio_ScrollView_addNode01);
   tolua_function(tolua_S,"addNode",tolua_CocoStudio_ScrollView_addNode02);
   tolua_function(tolua_S,"getNodeByTag",tolua_CocoStudio_ScrollView_getNodeByTag00);
   tolua_function(tolua_S,"removeNodeByTag",tolua_CocoStudio_ScrollView_removeNodeByTag00);
   tolua_function(tolua_S,"getNodes",tolua_CocoStudio_ScrollView_getNodes00);
   tolua_function(tolua_S,"removeNode",tolua_CocoStudio_ScrollView_removeNode00);
   tolua_function(tolua_S,"removeAllNodes",tolua_CocoStudio_ScrollView_removeAllNodes00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_ScrollView_update00);
   tolua_function(tolua_S,"setBounceEnabled",tolua_CocoStudio_ScrollView_setBounceEnabled00);
   tolua_function(tolua_S,"isBounceEnabled",tolua_CocoStudio_ScrollView_isBounceEnabled00);
   tolua_function(tolua_S,"setInertiaScrollEnabled",tolua_CocoStudio_ScrollView_setInertiaScrollEnabled00);
   tolua_function(tolua_S,"isInertiaScrollEnabled",tolua_CocoStudio_ScrollView_isInertiaScrollEnabled00);
   tolua_function(tolua_S,"setLayoutType",tolua_CocoStudio_ScrollView_setLayoutType00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_ScrollView_getLayoutType00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_ScrollView_getDescription00);
   tolua_variable(tolua_S,"__UIScrollInterface__",tolua_get_ScrollView___UIScrollInterface__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"PAGEVIEW_EVENT_TURNING",PAGEVIEW_EVENT_TURNING);
  tolua_constant(tolua_S,"PAGEVIEW_TOUCHLEFT",PAGEVIEW_TOUCHLEFT);
  tolua_constant(tolua_S,"PAGEVIEW_TOUCHRIGHT",PAGEVIEW_TOUCHRIGHT);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PageView","PageView","Layout",tolua_collect_PageView);
  #else
  tolua_cclass(tolua_S,"PageView","PageView","Layout",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PageView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_PageView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_PageView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_PageView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_PageView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_PageView_create00);
   tolua_function(tolua_S,"addWidgetToPage",tolua_CocoStudio_PageView_addWidgetToPage00);
   tolua_function(tolua_S,"addPage",tolua_CocoStudio_PageView_addPage00);
   tolua_function(tolua_S,"insertPage",tolua_CocoStudio_PageView_insertPage00);
   tolua_function(tolua_S,"removePage",tolua_CocoStudio_PageView_removePage00);
   tolua_function(tolua_S,"removePageAtIndex",tolua_CocoStudio_PageView_removePageAtIndex00);
   tolua_function(tolua_S,"removeAllPages",tolua_CocoStudio_PageView_removeAllPages00);
   tolua_function(tolua_S,"scrollToPage",tolua_CocoStudio_PageView_scrollToPage00);
   tolua_function(tolua_S,"getCurPageIndex",tolua_CocoStudio_PageView_getCurPageIndex00);
   tolua_function(tolua_S,"getPages",tolua_CocoStudio_PageView_getPages00);
   tolua_function(tolua_S,"getPage",tolua_CocoStudio_PageView_getPage00);
   tolua_function(tolua_S,"onTouchBegan",tolua_CocoStudio_PageView_onTouchBegan00);
   tolua_function(tolua_S,"onTouchMoved",tolua_CocoStudio_PageView_onTouchMoved00);
   tolua_function(tolua_S,"onTouchEnded",tolua_CocoStudio_PageView_onTouchEnded00);
   tolua_function(tolua_S,"onTouchCancelled",tolua_CocoStudio_PageView_onTouchCancelled00);
   tolua_function(tolua_S,"update",tolua_CocoStudio_PageView_update00);
   tolua_function(tolua_S,"setLayoutType",tolua_CocoStudio_PageView_setLayoutType00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_PageView_getLayoutType00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_PageView_getDescription00);
   tolua_variable(tolua_S,"__UIScrollInterface__",tolua_get_PageView___UIScrollInterface__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LISTVIEW_GRAVITY_LEFT",LISTVIEW_GRAVITY_LEFT);
  tolua_constant(tolua_S,"LISTVIEW_GRAVITY_RIGHT",LISTVIEW_GRAVITY_RIGHT);
  tolua_constant(tolua_S,"LISTVIEW_GRAVITY_CENTER_HORIZONTAL",LISTVIEW_GRAVITY_CENTER_HORIZONTAL);
  tolua_constant(tolua_S,"LISTVIEW_GRAVITY_TOP",LISTVIEW_GRAVITY_TOP);
  tolua_constant(tolua_S,"LISTVIEW_GRAVITY_BOTTOM",LISTVIEW_GRAVITY_BOTTOM);
  tolua_constant(tolua_S,"LISTVIEW_GRAVITY_CENTER_VERTICAL",LISTVIEW_GRAVITY_CENTER_VERTICAL);
  tolua_constant(tolua_S,"LISTVIEW_ONSELECTEDITEM_START",LISTVIEW_ONSELECTEDITEM_START);
  tolua_constant(tolua_S,"LISTVIEW_ONSELECTEDITEM_END",LISTVIEW_ONSELECTEDITEM_END);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ListView","ListView","ScrollView",tolua_collect_ListView);
  #else
  tolua_cclass(tolua_S,"ListView","ListView","ScrollView",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ListView");
   tolua_function(tolua_S,"new",tolua_CocoStudio_ListView_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_ListView_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_ListView_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ListView_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_ListView_create00);
   tolua_function(tolua_S,"setItemModel",tolua_CocoStudio_ListView_setItemModel00);
   tolua_function(tolua_S,"pushBackDefaultItem",tolua_CocoStudio_ListView_pushBackDefaultItem00);
   tolua_function(tolua_S,"insertDefaultItem",tolua_CocoStudio_ListView_insertDefaultItem00);
   tolua_function(tolua_S,"pushBackCustomItem",tolua_CocoStudio_ListView_pushBackCustomItem00);
   tolua_function(tolua_S,"insertCustomItem",tolua_CocoStudio_ListView_insertCustomItem00);
   tolua_function(tolua_S,"removeLastItem",tolua_CocoStudio_ListView_removeLastItem00);
   tolua_function(tolua_S,"removeItem",tolua_CocoStudio_ListView_removeItem00);
   tolua_function(tolua_S,"removeAllItems",tolua_CocoStudio_ListView_removeAllItems00);
   tolua_function(tolua_S,"getItem",tolua_CocoStudio_ListView_getItem00);
   tolua_function(tolua_S,"getItems",tolua_CocoStudio_ListView_getItems00);
   tolua_function(tolua_S,"getIndex",tolua_CocoStudio_ListView_getIndex00);
   tolua_function(tolua_S,"setGravity",tolua_CocoStudio_ListView_setGravity00);
   tolua_function(tolua_S,"setItemsMargin",tolua_CocoStudio_ListView_setItemsMargin00);
   tolua_function(tolua_S,"sortAllChildren",tolua_CocoStudio_ListView_sortAllChildren00);
   tolua_function(tolua_S,"getCurSelectedIndex",tolua_CocoStudio_ListView_getCurSelectedIndex00);
   tolua_function(tolua_S,"setDirection",tolua_CocoStudio_ListView_setDirection00);
   tolua_function(tolua_S,"getDescription",tolua_CocoStudio_ListView_getDescription00);
   tolua_function(tolua_S,"requestRefreshView",tolua_CocoStudio_ListView_requestRefreshView00);
   tolua_function(tolua_S,"refreshView",tolua_CocoStudio_ListView_refreshView00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_NONE",LINEAR_GRAVITY_NONE);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_LEFT",LINEAR_GRAVITY_LEFT);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_TOP",LINEAR_GRAVITY_TOP);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_RIGHT",LINEAR_GRAVITY_RIGHT);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_BOTTOM",LINEAR_GRAVITY_BOTTOM);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_CENTER_VERTICAL",LINEAR_GRAVITY_CENTER_VERTICAL);
  tolua_constant(tolua_S,"LINEAR_GRAVITY_CENTER_HORIZONTAL",LINEAR_GRAVITY_CENTER_HORIZONTAL);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_NONE",RELATIVE_ALIGN_NONE);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_TOP_LEFT",RELATIVE_ALIGN_PARENT_TOP_LEFT);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL",RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_TOP_RIGHT",RELATIVE_ALIGN_PARENT_TOP_RIGHT);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL",RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL);
  tolua_constant(tolua_S,"RELATIVE_CENTER_IN_PARENT",RELATIVE_CENTER_IN_PARENT);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL",RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_LEFT_BOTTOM",RELATIVE_ALIGN_PARENT_LEFT_BOTTOM);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL",RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL);
  tolua_constant(tolua_S,"RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM",RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_ABOVE_LEFTALIGN",RELATIVE_LOCATION_ABOVE_LEFTALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_ABOVE_CENTER",RELATIVE_LOCATION_ABOVE_CENTER);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_ABOVE_RIGHTALIGN",RELATIVE_LOCATION_ABOVE_RIGHTALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_LEFT_OF_TOPALIGN",RELATIVE_LOCATION_LEFT_OF_TOPALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_LEFT_OF_CENTER",RELATIVE_LOCATION_LEFT_OF_CENTER);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN",RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_RIGHT_OF_TOPALIGN",RELATIVE_LOCATION_RIGHT_OF_TOPALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_RIGHT_OF_CENTER",RELATIVE_LOCATION_RIGHT_OF_CENTER);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN",RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_BELOW_LEFTALIGN",RELATIVE_LOCATION_BELOW_LEFTALIGN);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_BELOW_CENTER",RELATIVE_LOCATION_BELOW_CENTER);
  tolua_constant(tolua_S,"RELATIVE_LOCATION_BELOW_RIGHTALIGN",RELATIVE_LOCATION_BELOW_RIGHTALIGN);
  tolua_constant(tolua_S,"LAYOUT_PARAMETER_NONE",LAYOUT_PARAMETER_NONE);
  tolua_constant(tolua_S,"LAYOUT_PARAMETER_LINEAR",LAYOUT_PARAMETER_LINEAR);
  tolua_constant(tolua_S,"LAYOUT_PARAMETER_RELATIVE",LAYOUT_PARAMETER_RELATIVE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LayoutParameter","LayoutParameter","CCObject",tolua_collect_LayoutParameter);
  #else
  tolua_cclass(tolua_S,"LayoutParameter","LayoutParameter","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LayoutParameter");
   tolua_function(tolua_S,"new",tolua_CocoStudio_LayoutParameter_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_LayoutParameter_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_LayoutParameter_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_LayoutParameter_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_LayoutParameter_create00);
   tolua_function(tolua_S,"getLayoutType",tolua_CocoStudio_LayoutParameter_getLayoutType00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LinearLayoutParameter","LinearLayoutParameter","LayoutParameter",tolua_collect_LinearLayoutParameter);
  #else
  tolua_cclass(tolua_S,"LinearLayoutParameter","LinearLayoutParameter","LayoutParameter",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LinearLayoutParameter");
   tolua_function(tolua_S,"new",tolua_CocoStudio_LinearLayoutParameter_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_LinearLayoutParameter_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_LinearLayoutParameter_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_LinearLayoutParameter_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_LinearLayoutParameter_create00);
   tolua_function(tolua_S,"setGravity",tolua_CocoStudio_LinearLayoutParameter_setGravity00);
   tolua_function(tolua_S,"getGravity",tolua_CocoStudio_LinearLayoutParameter_getGravity00);
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
  tolua_cclass(tolua_S,"TouchGroup","TouchGroup","CCLayer",tolua_collect_TouchGroup);
  #else
  tolua_cclass(tolua_S,"TouchGroup","TouchGroup","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TouchGroup");
   tolua_function(tolua_S,"new",tolua_CocoStudio_TouchGroup_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_TouchGroup_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_TouchGroup_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_TouchGroup_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_TouchGroup_create00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_TouchGroup_init00);
   tolua_function(tolua_S,"onEnter",tolua_CocoStudio_TouchGroup_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_CocoStudio_TouchGroup_onExit00);
   tolua_function(tolua_S,"onEnterTransitionDidFinish",tolua_CocoStudio_TouchGroup_onEnterTransitionDidFinish00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_CocoStudio_TouchGroup_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_CocoStudio_TouchGroup_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_CocoStudio_TouchGroup_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_CocoStudio_TouchGroup_ccTouchCancelled00);
   tolua_function(tolua_S,"addWidget",tolua_CocoStudio_TouchGroup_addWidget00);
   tolua_function(tolua_S,"removeWidget",tolua_CocoStudio_TouchGroup_removeWidget00);
   tolua_function(tolua_S,"getWidgetByTag",tolua_CocoStudio_TouchGroup_getWidgetByTag00);
   tolua_function(tolua_S,"getWidgetByName",tolua_CocoStudio_TouchGroup_getWidgetByName00);
   tolua_function(tolua_S,"clear",tolua_CocoStudio_TouchGroup_clear00);
   tolua_function(tolua_S,"getRootWidget",tolua_CocoStudio_TouchGroup_getRootWidget00);
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
   tolua_function(tolua_S,"playBackgroundMusic",tolua_CocoStudio_CCComAudio_playBackgroundMusic02);
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
   tolua_function(tolua_S,"playEffect",tolua_CocoStudio_CCComAudio_playEffect02);
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
   tolua_function(tolua_S,"purge",tolua_CocoStudio_ActionManager_purge00);
   tolua_function(tolua_S,"getActionByName",tolua_CocoStudio_ActionManager_getActionByName00);
   tolua_function(tolua_S,"playActionByName",tolua_CocoStudio_ActionManager_playActionByName00);
   tolua_function(tolua_S,"releaseActions",tolua_CocoStudio_ActionManager_releaseActions00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"ATTACH_EMPTY_NODE",ATTACH_EMPTY_NODE);
  tolua_constant(tolua_S,"ATTACH_RENDER_NODE",ATTACH_RENDER_NODE);
  tolua_constant(tolua_S,"DEFAULT",DEFAULT);
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
   tolua_function(tolua_S,"purge",tolua_CocoStudio_SceneReader_purge00);
   tolua_function(tolua_S,"sceneReaderVersion",tolua_CocoStudio_SceneReader_sceneReaderVersion00);
   tolua_function(tolua_S,"createNodeWithSceneFile",tolua_CocoStudio_SceneReader_createNodeWithSceneFile00);
   tolua_function(tolua_S,"getNodeByTag",tolua_CocoStudio_SceneReader_getNodeByTag00);
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
   tolua_function(tolua_S,"purge",tolua_CocoStudio_GUIReader_purge00);
   tolua_function(tolua_S,"widgetFromJsonFile",tolua_CocoStudio_GUIReader_widgetFromJsonFile00);
   tolua_function(tolua_S,"widgetFromBinaryFile",tolua_CocoStudio_GUIReader_widgetFromBinaryFile00);
   tolua_function(tolua_S,"getVersionInteger",tolua_CocoStudio_GUIReader_getVersionInteger00);
   tolua_function(tolua_S,"storeFileDesignSize",tolua_CocoStudio_GUIReader_storeFileDesignSize00);
   tolua_function(tolua_S,"getFileDesignSize",tolua_CocoStudio_GUIReader_getFileDesignSize00);
   tolua_function(tolua_S,"getFilePath",tolua_CocoStudio_GUIReader_getFilePath00);
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
  tolua_constant(tolua_S,"RICH_TEXT",RICH_TEXT);
  tolua_constant(tolua_S,"RICH_IMAGE",RICH_IMAGE);
  tolua_constant(tolua_S,"RICH_CUSTOM",RICH_CUSTOM);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RichElement","RichElement","CCObject",tolua_collect_RichElement);
  #else
  tolua_cclass(tolua_S,"RichElement","RichElement","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RichElement");
   tolua_function(tolua_S,"new",tolua_CocoStudio_RichElement_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_RichElement_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_RichElement_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_RichElement_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_RichElement_init00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RichElementText","RichElementText","RichElement",tolua_collect_RichElementText);
  #else
  tolua_cclass(tolua_S,"RichElementText","RichElementText","RichElement",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RichElementText");
   tolua_function(tolua_S,"new",tolua_CocoStudio_RichElementText_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_RichElementText_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_RichElementText_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_RichElementText_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_RichElementText_init00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_RichElementText_create00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RichElementImage","RichElementImage","RichElement",tolua_collect_RichElementImage);
  #else
  tolua_cclass(tolua_S,"RichElementImage","RichElementImage","RichElement",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RichElementImage");
   tolua_function(tolua_S,"new",tolua_CocoStudio_RichElementImage_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_RichElementImage_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_RichElementImage_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_RichElementImage_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_RichElementImage_init00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_RichElementImage_create00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RichElementCustomNode","RichElementCustomNode","RichElement",tolua_collect_RichElementCustomNode);
  #else
  tolua_cclass(tolua_S,"RichElementCustomNode","RichElementCustomNode","RichElement",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RichElementCustomNode");
   tolua_function(tolua_S,"new",tolua_CocoStudio_RichElementCustomNode_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_RichElementCustomNode_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_RichElementCustomNode_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_RichElementCustomNode_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_RichElementCustomNode_init00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_RichElementCustomNode_create00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RichText","RichText","Widget",tolua_collect_RichText);
  #else
  tolua_cclass(tolua_S,"RichText","RichText","Widget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RichText");
   tolua_function(tolua_S,"new",tolua_CocoStudio_RichText_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_RichText_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_RichText_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_RichText_delete00);
   tolua_function(tolua_S,"create",tolua_CocoStudio_RichText_create00);
   tolua_function(tolua_S,"insertElement",tolua_CocoStudio_RichText_insertElement00);
   tolua_function(tolua_S,"pushBackElement",tolua_CocoStudio_RichText_pushBackElement00);
   tolua_function(tolua_S,"removeElement",tolua_CocoStudio_RichText_removeElement00);
   tolua_function(tolua_S,"removeElement",tolua_CocoStudio_RichText_removeElement01);
   tolua_function(tolua_S,"visit",tolua_CocoStudio_RichText_visit00);
   tolua_function(tolua_S,"setVerticalSpace",tolua_CocoStudio_RichText_setVerticalSpace00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_CocoStudio_RichText_setAnchorPoint00);
   tolua_function(tolua_S,"getContentSize",tolua_CocoStudio_RichText_getContentSize00);
   tolua_function(tolua_S,"formatText",tolua_CocoStudio_RichText_formatText00);
   tolua_function(tolua_S,"ignoreContentAdaptWithSize",tolua_CocoStudio_RichText_ignoreContentAdaptWithSize00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ActionTimeline","ActionTimeline","CCAction",tolua_collect_ActionTimeline);
  #else
  tolua_cclass(tolua_S,"ActionTimeline","ActionTimeline","CCAction",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ActionTimeline");
   tolua_function(tolua_S,"create",tolua_CocoStudio_ActionTimeline_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_ActionTimeline_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_ActionTimeline_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_ActionTimeline_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ActionTimeline_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_ActionTimeline_init00);
   tolua_function(tolua_S,"gotoFrameAndPlay",tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay00);
   tolua_function(tolua_S,"gotoFrameAndPlay",tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay01);
   tolua_function(tolua_S,"gotoFrameAndPlay",tolua_CocoStudio_ActionTimeline_gotoFrameAndPlay02);
   tolua_function(tolua_S,"gotoFrameAndPause",tolua_CocoStudio_ActionTimeline_gotoFrameAndPause00);
   tolua_function(tolua_S,"pause",tolua_CocoStudio_ActionTimeline_pause00);
   tolua_function(tolua_S,"resume",tolua_CocoStudio_ActionTimeline_resume00);
   tolua_function(tolua_S,"isPlaying",tolua_CocoStudio_ActionTimeline_isPlaying00);
   tolua_function(tolua_S,"setTimeSpeed",tolua_CocoStudio_ActionTimeline_setTimeSpeed00);
   tolua_function(tolua_S,"getTimeSpeed",tolua_CocoStudio_ActionTimeline_getTimeSpeed00);
   tolua_function(tolua_S,"setDuration",tolua_CocoStudio_ActionTimeline_setDuration00);
   tolua_function(tolua_S,"getDuration",tolua_CocoStudio_ActionTimeline_getDuration00);
   tolua_function(tolua_S,"getStartFrame",tolua_CocoStudio_ActionTimeline_getStartFrame00);
   tolua_function(tolua_S,"getEndFrame",tolua_CocoStudio_ActionTimeline_getEndFrame00);
   tolua_function(tolua_S,"getCurrentFrame",tolua_CocoStudio_ActionTimeline_getCurrentFrame00);
   tolua_function(tolua_S,"addTimeline",tolua_CocoStudio_ActionTimeline_addTimeline00);
   tolua_function(tolua_S,"removeTimeline",tolua_CocoStudio_ActionTimeline_removeTimeline00);
   tolua_function(tolua_S,"clone",tolua_CocoStudio_ActionTimeline_clone00);
   tolua_function(tolua_S,"reverse",tolua_CocoStudio_ActionTimeline_reverse00);
   tolua_function(tolua_S,"step",tolua_CocoStudio_ActionTimeline_step00);
   tolua_function(tolua_S,"startWithTarget",tolua_CocoStudio_ActionTimeline_startWithTarget00);
   tolua_function(tolua_S,"isDone",tolua_CocoStudio_ActionTimeline_isDone00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ActionTimelineCache","ActionTimelineCache","CCObject",tolua_collect_ActionTimelineCache);
  #else
  tolua_cclass(tolua_S,"ActionTimelineCache","ActionTimelineCache","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ActionTimelineCache");
   tolua_function(tolua_S,"getInstance",tolua_CocoStudio_ActionTimelineCache_getInstance00);
   tolua_function(tolua_S,"destroyInstance",tolua_CocoStudio_ActionTimelineCache_destroyInstance00);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_ActionTimelineCache_delete00);
   tolua_function(tolua_S,"purge",tolua_CocoStudio_ActionTimelineCache_purge00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_ActionTimelineCache_init00);
   tolua_function(tolua_S,"removeAction",tolua_CocoStudio_ActionTimelineCache_removeAction00);
   tolua_function(tolua_S,"createAction",tolua_CocoStudio_ActionTimelineCache_createAction00);
   tolua_function(tolua_S,"loadAnimationActionWithFile",tolua_CocoStudio_ActionTimelineCache_loadAnimationActionWithFile00);
   tolua_function(tolua_S,"loadAnimationActionWithContent",tolua_CocoStudio_ActionTimelineCache_loadAnimationActionWithContent00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"NodeReader","NodeReader","CCObject",tolua_collect_NodeReader);
  #else
  tolua_cclass(tolua_S,"NodeReader","NodeReader","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"NodeReader");
   tolua_function(tolua_S,"getInstance",tolua_CocoStudio_NodeReader_getInstance00);
   tolua_function(tolua_S,"destroyInstance",tolua_CocoStudio_NodeReader_destroyInstance00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_NodeReader_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_NodeReader_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_NodeReader_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_NodeReader_delete00);
   tolua_function(tolua_S,"purge",tolua_CocoStudio_NodeReader_purge00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_NodeReader_init00);
   tolua_function(tolua_S,"createNode",tolua_CocoStudio_NodeReader_createNode00);
   tolua_function(tolua_S,"loadNodeWithFile",tolua_CocoStudio_NodeReader_loadNodeWithFile00);
   tolua_function(tolua_S,"loadNodeWithContent",tolua_CocoStudio_NodeReader_loadNodeWithContent00);
   tolua_function(tolua_S,"setRecordJsonPath",tolua_CocoStudio_NodeReader_setRecordJsonPath00);
   tolua_function(tolua_S,"isRecordJsonPath",tolua_CocoStudio_NodeReader_isRecordJsonPath00);
   tolua_function(tolua_S,"setJsonPath",tolua_CocoStudio_NodeReader_setJsonPath00);
   tolua_function(tolua_S,"getJsonPath",tolua_CocoStudio_NodeReader_getJsonPath00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Timeline","Timeline","CCObject",tolua_collect_Timeline);
  #else
  tolua_cclass(tolua_S,"Timeline","Timeline","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Timeline");
   tolua_function(tolua_S,"create",tolua_CocoStudio_Timeline_create00);
   tolua_function(tolua_S,"new",tolua_CocoStudio_Timeline_new00);
   tolua_function(tolua_S,"new_local",tolua_CocoStudio_Timeline_new00_local);
   tolua_function(tolua_S,".call",tolua_CocoStudio_Timeline_new00_local);
   tolua_function(tolua_S,"delete",tolua_CocoStudio_Timeline_delete00);
   tolua_function(tolua_S,"init",tolua_CocoStudio_Timeline_init00);
   tolua_function(tolua_S,"gotoFrame",tolua_CocoStudio_Timeline_gotoFrame00);
   tolua_function(tolua_S,"stepToFrame",tolua_CocoStudio_Timeline_stepToFrame00);
   tolua_function(tolua_S,"getFrames",tolua_CocoStudio_Timeline_getFrames00);
   tolua_function(tolua_S,"addFrame",tolua_CocoStudio_Timeline_addFrame00);
   tolua_function(tolua_S,"insertFrame",tolua_CocoStudio_Timeline_insertFrame00);
   tolua_function(tolua_S,"removeFrame",tolua_CocoStudio_Timeline_removeFrame00);
   tolua_function(tolua_S,"setActionTag",tolua_CocoStudio_Timeline_setActionTag00);
   tolua_function(tolua_S,"getActionTag",tolua_CocoStudio_Timeline_getActionTag00);
   tolua_function(tolua_S,"setNode",tolua_CocoStudio_Timeline_setNode00);
   tolua_function(tolua_S,"getNode",tolua_CocoStudio_Timeline_getNode00);
   tolua_function(tolua_S,"setActionTimeline",tolua_CocoStudio_Timeline_setActionTimeline00);
   tolua_function(tolua_S,"getActionTimeline",tolua_CocoStudio_Timeline_getActionTimeline00);
   tolua_function(tolua_S,"clone",tolua_CocoStudio_Timeline_clone00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CocoStudio (lua_State* tolua_S) {
 return tolua_CocoStudio_open(tolua_S);
};
#endif

