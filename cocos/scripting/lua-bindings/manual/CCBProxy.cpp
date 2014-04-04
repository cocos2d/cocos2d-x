/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCBProxy.h"
#include "LuaScriptHandlerMgr.h"

CCBReader* CCBProxy::createCCBReader()
{
    NodeLoaderLibrary *ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    CCBReader * pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->autorelease();
    
    return pCCBReader;
}
Node* CCBProxy::readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner)
{
    if (NULL == pCCBReader || NULL == pszFileName || 0 == strlen(pszFileName)) {
        return NULL;
    }
    Node *pNode = NULL;
    if (bSetOwner) {
        pNode = pCCBReader->readNodeGraphFromFile(pszFileName,this);
    }
    else
    {
        pNode = pCCBReader->readNodeGraphFromFile(pszFileName);
    }
    
    
    return pNode;
}

const char* CCBProxy::getNodeTypeName(Node* pNode)
{
    if (NULL == pNode) {
        return NULL;
    }
    
    if (NULL != dynamic_cast<Label*>(pNode)) {
        return "cc.Label";
    }

    if (NULL != dynamic_cast<Sprite*>(pNode)) {
        return "cc.Sprite";
    }
    
    if (NULL != dynamic_cast<ControlButton*>(pNode)) {
        return "cc.ControlButton";
    }
    
    if (NULL != dynamic_cast<LayerGradient*>(pNode)) {
        return "cc.LayerGradient";
    }
    
    if (NULL != dynamic_cast<LayerColor*>(pNode)) {
        return "cc.LayerColor";
    }
    
    if (NULL != dynamic_cast<Scale9Sprite*>(pNode)) {
        return "cc.LayerGradient";
    }
    
    if (NULL != dynamic_cast<Menu*>(pNode)) {
        return "cc.Menu";
    }
    
    if (NULL != dynamic_cast<MenuItemAtlasFont*>(pNode)) {
        return "cc.MenuItemAtlasFont";
    }
    
    if (NULL != dynamic_cast<MenuItemFont*>(pNode)) {
        return "cc.MenuItemFont";
    }
    
    if (NULL != dynamic_cast<MenuItemLabel*>(pNode)) {
        return "cc.MenuItemLabel";
    }
    
    if (NULL != dynamic_cast<MenuItemImage*>(pNode)) {
        return "cc.MenuItemImage";
    }
    
    if (NULL != dynamic_cast<MenuItemToggle*>(pNode)) {
        return "cc.MenuItemToggle";
    }
    
    if (NULL != dynamic_cast<MenuItemSprite*>(pNode)) {
        return "cc.MenuItemSprite";
    }

    if (NULL != dynamic_cast<MenuItem*>(pNode)) {
        return "cc.MenuItem";
    }

    if (NULL != dynamic_cast<Layer*>(pNode)) {
        return "cc.Layer";
    }

    if (NULL != dynamic_cast<__String*>(pNode)) {
        return "cc.String";
    }
    
    if (NULL != dynamic_cast<ParticleSystemQuad*>(pNode)) {
        return "cc.ParticleSystemQuad";
    }

    return "No Support";
}

void CCBProxy::setCallback(Node* node,int handle, int controlEvents)
{
    if (nullptr == node) {
        return;
    }
    
    if (nullptr != dynamic_cast<MenuItem*>(node))
    {
        MenuItem *menuItem = dynamic_cast<MenuItem*>(node);
        if (nullptr != menuItem) {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)menuItem, handle, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        }
    }
    else  if (NULL != dynamic_cast<Control*>(node))
    {
        Control* control = dynamic_cast<Control*>(node);
        if (nullptr != control)
        {
            for (int i = 0; i < kControlEventTotalNumber; i++)
            {
                if ((controlEvents & (1 << i)))
                {
                    ScriptHandlerMgr::HandlerType handlerType = ScriptHandlerMgr::HandlerType((int)ScriptHandlerMgr::HandlerType::CONTROL_TOUCH_DOWN + i);
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)control, handle, handlerType);
                }
            }
        }
    }
}

