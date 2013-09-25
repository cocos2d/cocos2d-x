#include "lua_cocos2dx_extensions_manual.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"


USING_NS_CC;
USING_NS_CC_EXT;

class LuaScrollViewDelegate:public CCObject, public CCScrollViewDelegate
{
public:
    virtual ~LuaScrollViewDelegate()
    {}
    
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        if (NULL != view)
        {
            int nHandler = view->getScriptHandler(CCScrollView::kScrollViewScroll);
            if (0 != nHandler)
            {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(nHandler, "");
            }
        }
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        if (NULL != view)
        {
            int nHandler = view->getScriptHandler(CCScrollView::kScrollViewZoom);
            if (-1 != nHandler)
            {
                CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(nHandler,"");
            }
        }
    }
};

/**
 This function is empty because of the request for compatible with 3.0-alpha0
 */
static int tolua_Cocos2dx_CCScrollView_setDelegate(lua_State* tolua_S)
{
    return 0;
}

static int tolua_Cocos2dx_CCScrollView_registerScriptHandler(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)               ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCScrollView* self = (CCScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
        if (NULL == self->getDelegate())
        {
            LuaScrollViewDelegate* delegate = new LuaScrollViewDelegate();
            if (NULL == delegate)
                return 0;
            
            self->setUserObject(delegate);
            self->setDelegate(delegate);
            
            delegate->release();
        }
        
        LUA_FUNCTION nFunID = (  toluafix_ref_function(tolua_S,2,0));
        int scriptHandlerType = ((int)  tolua_tonumber(tolua_S,3,0));
        self->registerScriptHandler(nFunID,scriptHandlerType);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendCCScrollView(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCScrollView");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setDelegate", tolua_Cocos2dx_CCScrollView_setDelegate);
        tolua_function(tolua_S, "registerScriptHandler", tolua_Cocos2dx_CCScrollView_registerScriptHandler);
    }
}

#define KEY_TABLEVIEW_DATA_SOURCE  "TableViewDataSource"
#define KEY_TABLEVIEW_DELEGATE     "TableViewDelegate"

class LUA_TableViewDelegate:public CCObject, public CCTableViewDelegate
{
public:
    LUA_TableViewDelegate(){}
    
    virtual ~LUA_TableViewDelegate(){}
    
    
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        if (NULL != view)
        {
            int nHandler = view->getScriptHandler(CCTableView::kTableViewScroll);
            if (0 != nHandler)
            {
                CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableViewScroll, dynamic_cast<CCTableView*>(view));
            }
        }
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        if (NULL != view)
        {
            int nHandler = view->getScriptHandler(CCTableView::kTableViewZoom);
            if (0 != nHandler)
            {
                CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableViewZoom, dynamic_cast<CCTableView*>(view));
            }
        }
    }
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell)
    {
        if (NULL != table && NULL != cell)
        {
            int nHandler = table->getScriptHandler(CCTableView::kTableCellTouched);
            if (0 != nHandler)
            {                
                CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableCellTouched, table,cell);
            }
        }
    }
    
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
    {
        if (NULL != table && NULL != cell)
        {
            int nHandler = table->getScriptHandler(CCTableView::kTableCellHighLight);
            if (0 != nHandler)
            {
                CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableCellHighLight, table,cell);
            }
        }
    }
    
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
    {
        if (NULL != table && NULL != cell)
        {
            int nHandler = table->getScriptHandler(CCTableView::kTableCellUnhighLight);
            if (0 != nHandler)
            {
                CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableCellUnhighLight, table,cell);
            }
        }
    }
    
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell)
    {
        if (NULL != table && NULL != cell)
        {
            int nHandler = table->getScriptHandler(CCTableView::kTableCellWillRecycle);
            if (0 != nHandler)
            {
                CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableCellWillRecycle, table,cell);
            }
        }
    }
};

/**
 This function is empty because of the request for compatible with 3.0-alpha0
 */
static int tolua_Cocos2dx_CCTableView_setDelegate(lua_State* tolua_S)
{
    return 0;
}

static int tolua_Cocos2dx_CCTableView_registerScriptHandler(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)               ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
        if (NULL == self->getDelegate())
        {
            LUA_TableViewDelegate* delegate = new LUA_TableViewDelegate();
            if (NULL == delegate)
                return 0;
            
            CCDictionary* userDict = static_cast<CCDictionary*>(self->getUserObject());
            if (NULL == userDict)
            {
                userDict = new CCDictionary();
                if (NULL == userDict)
                    return 0;
                
                self->setUserObject(userDict);
                userDict->release();
            }
            
            userDict->setObject(delegate, KEY_TABLEVIEW_DELEGATE);
            self->setDelegate(delegate);
            delegate->release();
        }
        
        LUA_FUNCTION nFunID = (  toluafix_ref_function(tolua_S,2,0));
        int scriptHandlerType = ((int)  tolua_tonumber(tolua_S,3,0));
        self->registerScriptHandler(nFunID,scriptHandlerType);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

class LUA_TableViewDataSource:public CCObject,public CCTableViewDataSource
{
public:
    LUA_TableViewDataSource(){}
    virtual ~LUA_TableViewDataSource(){}
    
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx)
    {
        if (NULL != table )
        {
            int nHandler = table->getScriptHandler(CCTableView::kTableCellSizeForIndex);
            if (0 != nHandler)
            {
                CCArray* resultArray = CCArray::create();
                if (NULL != resultArray)
                {
                    CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableCellSizeForIndex, table,&idx,resultArray);
                    CCAssert(resultArray->count() == 2, "tableCellSizeForIndex Array count error");
                    CCDouble* width  = dynamic_cast<CCDouble*>(resultArray->objectAtIndex(0));
                    CCDouble* height = dynamic_cast<CCDouble*>(resultArray->objectAtIndex(1));
                    if (NULL != width && NULL != height)
                    {
                        return CCSizeMake((float)width->getValue(), (float)height->getValue());
                    }
                }
            }
        }
        
        return CCSizeMake(0,0);
    }
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx)
    {
        if (NULL != table )
        {
            int nHandler = table->getScriptHandler(CCTableView::kTableCellSizeAtIndex);
            if (0 != nHandler)
            {
                CCArray* resultArray = CCArray::create();
                if (NULL != resultArray)
                {
                    CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kTableCellSizeAtIndex, table,&idx,resultArray);
                    CCTableViewCell* viewCell = NULL;
                    if (resultArray->count() > 0)
                    {
                        viewCell = dynamic_cast<CCTableViewCell*>(resultArray->objectAtIndex(0));
                    }
                    return viewCell;
                }
            }
        }
        
        return NULL;
    }
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table)
    {
        if (NULL != table )
        {
            int nHandler = table->getScriptHandler(CCTableView::kNumberOfCellsInTableView);
            if (0 != nHandler)
            {
                CCArray* resultArray = CCArray::create();
                if (NULL != resultArray)
                {
                    CCLuaEngine::defaultEngine()->executeTableViewEvent(CCTableView::kNumberOfCellsInTableView, table,NULL,resultArray);
                    CCDouble* numbers  = dynamic_cast<CCDouble*>(resultArray->objectAtIndex(0));
                    if (NULL != numbers)
                    {
                        return (int)numbers->getValue();
                    }
                }
            }
        }
        return 0;
    }
};

static int tolua_Cocos2dx_CCTableView_setDataSource(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCTableView* self = (CCTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDataSource'", NULL);
#endif
        LUA_TableViewDataSource* dataSource = new LUA_TableViewDataSource();
        if (NULL == dataSource)
            return 0;
        
        CCDictionary* userDict = static_cast<CCDictionary*>(self->getUserObject());
        if (NULL == userDict)
        {
            userDict = new CCDictionary();
            if (NULL == userDict)
                return 0;
            
            self->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->setObject(dataSource, KEY_TABLEVIEW_DATA_SOURCE);
        
        self->setDataSource(dataSource);
        
        dataSource->release();
        
        return 0;
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setDataSource'.",&tolua_err);
    return 0;
#endif    
}

static int tolua_Cocos2dx_CCTableView_create00(lua_State* tolua_S)
{
    
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S, 1, "CCTableView", 0, &tolua_err) ||
        !tolua_isusertype(tolua_S, 2, "CCSize", 0, &tolua_err)       ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LUA_TableViewDataSource* dataSource = new LUA_TableViewDataSource();
        if (NULL == dataSource)
            return 0;
        
        CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
        CCTableView* tolua_ret = CCTableView::create(dataSource, size);
        if (NULL == tolua_ret)
            return 0;
        
        tolua_ret->reloadData();
        
        CCDictionary* userDict = new CCDictionary();
        userDict->setObject(dataSource, KEY_TABLEVIEW_DATA_SOURCE);
        tolua_ret->setUserObject(userDict);
        userDict->release();
        
        dataSource->release();
        
        int  nID = (int)tolua_ret->m_uID;
        int* pLuaID =  &tolua_ret->m_nLuaID;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTableView");
        
        return 1;
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2dx_CCTableView_create01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCTableView",0,&tolua_err) ||
        !tolua_isusertype(tolua_S, 2, "CCSize", 0, &tolua_err)   ||
        !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err)       ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        
        LUA_TableViewDataSource* dataSource = new LUA_TableViewDataSource();
        if (NULL == dataSource)
            return 0;
        
        CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
        CCNode* node = static_cast<CCNode*>(tolua_tousertype(tolua_S, 3, 0));
        CCTableView* tolua_ret = CCTableView::create(dataSource,size,node);
        if (NULL == tolua_ret)
            return 0;
        
        tolua_ret->reloadData();
        
        CCDictionary* userDict = new CCDictionary();
        userDict->setObject(dataSource, KEY_TABLEVIEW_DATA_SOURCE);
        tolua_ret->setUserObject(userDict);
        userDict->release();
        
        dataSource->release();
        
        
        int  nID = (int)tolua_ret->m_uID;
        int* pLuaID =  &tolua_ret->m_nLuaID;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTableView");
        return 1;
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2dx_CCTableView_create00(tolua_S);
}

static void extendCCTableView(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCTableView");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setDelegate", tolua_Cocos2dx_CCTableView_setDelegate);
        tolua_function(tolua_S, "setDataSource", tolua_Cocos2dx_CCTableView_setDataSource);
        tolua_function(tolua_S, "create", tolua_Cocos2dx_CCTableView_create00);
        tolua_function(tolua_S, "create", tolua_Cocos2dx_CCTableView_create01);
        tolua_function(tolua_S, "registerScriptHandler", tolua_Cocos2dx_CCTableView_registerScriptHandler);
    }
}

static int tolua_Cocos2d_CCTableViewCell_new(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCTableViewCell",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCTableViewCell* tolua_ret = new CCTableViewCell();
        if (NULL == tolua_ret)
            return 0;
            
        tolua_ret->autorelease();
        int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCTableViewCell");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
    return 0;
#endif
}

static void extendCCTableViewCell(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCTableViewCell");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "new", tolua_Cocos2d_CCTableViewCell_new);
    }
}

int register_all_cocos2dx_extension_manual(lua_State* tolua_S)
{
    extendCCScrollView(tolua_S);
    extendCCTableView(tolua_S);
    extendCCTableViewCell(tolua_S);
    return 0;
}