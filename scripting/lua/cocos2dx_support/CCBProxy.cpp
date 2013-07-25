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
    
    ccNodeLoaderLibrary->registerNodeLoader("", CCBLayerLoader::loader());
    
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
    
    if (NULL != dynamic_cast<LabelTTF*>(pNode)) {
        return "CCLabelTTF";
    }

    if (NULL != dynamic_cast<LabelBMFont*>(pNode)) {
        return "CCLabelBMFont";
    }

    if (NULL != dynamic_cast<Sprite*>(pNode)) {
        return "CCSprite";
    }
    
    if (NULL != dynamic_cast<ControlButton*>(pNode)) {
        return "CCControlButton";
    }
    
    if (NULL != dynamic_cast<LayerGradient*>(pNode)) {
        return "CCLayerGradient";
    }
    
    if (NULL != dynamic_cast<LayerColor*>(pNode)) {
        return "CCLayerColor";
    }
    
    if (NULL != dynamic_cast<Scale9Sprite*>(pNode)) {
        return "CCLayerGradient";
    }
    
    if (NULL != dynamic_cast<Menu*>(pNode)) {
        return "CCMenu";
    }
    
    if (NULL != dynamic_cast<MenuItemAtlasFont*>(pNode)) {
        return "CCMenuItemAtlasFont";
    }
    
    if (NULL != dynamic_cast<MenuItemFont*>(pNode)) {
        return "CCMenuItemFont";
    }
    
    if (NULL != dynamic_cast<MenuItemLabel*>(pNode)) {
        return "CCMenuItemLabel";
    }
    
    if (NULL != dynamic_cast<MenuItemImage*>(pNode)) {
        return "CCMenuItemImage";
    }
    
    if (NULL != dynamic_cast<MenuItemToggle*>(pNode)) {
        return "CCMenuItemToggle";
    }
    
    if (NULL != dynamic_cast<MenuItemSprite*>(pNode)) {
        return "CCMenuItemSprite";
    }

    if (NULL != dynamic_cast<MenuItem*>(pNode)) {
        return "CCMenuItem";
    }

    if (NULL != dynamic_cast<Layer*>(pNode)) {
        return "CCLayer";
    }

    if (NULL != dynamic_cast<String*>(pNode)) {
        return "CCString";
    }
    
    if (NULL != dynamic_cast<ParticleSystemQuad*>(pNode)) {
        return "CCParticleSystemQuad";
    }

    return "No Support";
}

void CCBProxy::setCallback(Node* pNode,int nHandle)
{
    if (NULL == pNode) {
        return;
    }
    
    if (NULL != dynamic_cast<MenuItem*>(pNode))
    {
        MenuItem *pMenuItem = dynamic_cast<MenuItem*>(pNode);
        if (NULL != pMenuItem) {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)pMenuItem, nHandle, ScriptHandlerMgr::kMenuClickHandler);
        }
    }
    else  if (NULL != dynamic_cast<ControlButton*>(pNode))
    {
        ControlButton *pBtnItem = dynamic_cast<ControlButton*>(pNode);
        if (NULL != pBtnItem) {
            //UNOD,need Btn Pros to addHanldeOfControlEvent
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)pBtnItem, nHandle, ScriptHandlerMgr::kControlTouchUpInsideHandler);
        }
    }
}

