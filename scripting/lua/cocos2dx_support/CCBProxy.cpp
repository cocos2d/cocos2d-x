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

CCBReader* CCBProxy::createCCBreader()
{
    CCNodeLoaderLibrary *ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("", CCBLayerLoader::loader());
    
    CCBReader * pCCBReader = new CCBReader(ccNodeLoaderLibrary);
    pCCBReader->autorelease();
    
    return pCCBReader;
}
CCNode* CCBProxy::readCCBFromFile(const char *pszFileName,CCBReader* pCCBReader,bool bSetOwner)
{
    if (NULL == pCCBReader || NULL == pszFileName || 0 == strlen(pszFileName)) {
        return NULL;
    }
    CCNode *pNode = NULL;
    if (bSetOwner) {
        pNode = pCCBReader->readNodeGraphFromFile(pszFileName,this);
    }
    else
    {
        pNode = pCCBReader->readNodeGraphFromFile(pszFileName);
    }
    
    
    return pNode;
}

const char* CCBProxy::getNodeTypeName(CCNode* pNode)
{
    if (NULL == pNode) {
        return NULL;
    }
    
    if (NULL != dynamic_cast<CCLabelTTF*>(pNode)) {
        return "CCLabelTTF";
    }

    if (NULL != dynamic_cast<CCLabelBMFont*>(pNode)) {
        return "CCLabelBMFont";
    }

    if (NULL != dynamic_cast<CCSprite*>(pNode)) {
        return "CCSprite";
    }
    
    if (NULL != dynamic_cast<CCControlButton*>(pNode)) {
        return "CCControlButton";
    }
    
    if (NULL != dynamic_cast<CCLayerGradient*>(pNode)) {
        return "CCLayerGradient";
    }
    
    if (NULL != dynamic_cast<CCLayerColor*>(pNode)) {
        return "CCLayerColor";
    }
    
    if (NULL != dynamic_cast<CCScale9Sprite*>(pNode)) {
        return "CCLayerGradient";
    }
    
    if (NULL != dynamic_cast<CCMenu*>(pNode)) {
        return "CCMenu";
    }
    
    if (NULL != dynamic_cast<CCMenuItemAtlasFont*>(pNode)) {
        return "CCMenuItemAtlasFont";
    }
    
    if (NULL != dynamic_cast<CCMenuItemFont*>(pNode)) {
        return "CCMenuItemFont";
    }
    
    if (NULL != dynamic_cast<CCMenuItemLabel*>(pNode)) {
        return "CCMenuItemLabel";
    }
    
    if (NULL != dynamic_cast<CCMenuItemImage*>(pNode)) {
        return "CCMenuItemImage";
    }
    
    if (NULL != dynamic_cast<CCMenuItemToggle*>(pNode)) {
        return "CCMenuItemToggle";
    }
    
    if (NULL != dynamic_cast<CCMenuItemSprite*>(pNode)) {
        return "CCMenuItemSprite";
    }

    if (NULL != dynamic_cast<CCMenuItem*>(pNode)) {
        return "CCMenuItem";
    }

    if (NULL != dynamic_cast<CCLayer*>(pNode)) {
        return "CCLayer";
    }

    if (NULL != dynamic_cast<CCString*>(pNode)) {
        return "CCString";
    }
    
    if (NULL != dynamic_cast<CCParticleSystemQuad*>(pNode)) {
        return "CCParticleSystemQuad";
    }

    return "No Support";
}

void CCBProxy::setCallback(CCNode* pNode,int nHandle)
{
    if (NULL == pNode) {
        return;
    }
    
    if (NULL != dynamic_cast<CCMenuItem*>(pNode))
    {
        CCMenuItem *pMenuItem = dynamic_cast<CCMenuItem*>(pNode);
        if (NULL != pMenuItem) {
            pMenuItem->registerScriptTapHandler(nHandle);
        }
    }
    else  if (NULL != dynamic_cast<CCControlButton*>(pNode))
    {
        CCControlButton *pBtnItem = dynamic_cast<CCControlButton*>(pNode);
        if (NULL != pBtnItem) {
            //UNOD,need Btn Pros to addHanldeOfControlEvent
            pBtnItem->addHandleOfControlEvent(nHandle,CCControlEventTouchUpInside);
        }
    }
    
    
}

