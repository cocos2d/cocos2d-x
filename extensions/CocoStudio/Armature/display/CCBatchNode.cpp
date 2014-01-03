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

#include "CCBatchNode.h"
#include "../utils/CCArmatureDefine.h"
#include "../CCArmature.h"
#include "CCSkin.h"

NS_CC_EXT_BEGIN

CCBatchNode *CCBatchNode::create()
{
    CCBatchNode *batchNode = new CCBatchNode();
    if (batchNode && batchNode->init())
    {
        batchNode->autorelease();
        return batchNode;
    }
    CC_SAFE_DELETE(batchNode);
    return NULL;
}

CCBatchNode::CCBatchNode()
    : m_pAtlas(NULL)
    , m_pTextureAtlasDic(NULL)
{
}

CCBatchNode::~CCBatchNode()
{
    CC_SAFE_RELEASE_NULL(m_pTextureAtlasDic);
}

bool CCBatchNode::init()
{
    bool ret = CCNode::init();
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    
    CC_SAFE_DELETE(m_pTextureAtlasDic);
    m_pTextureAtlasDic = new CCDictionary();

    return ret;
}

void CCBatchNode::addChild(CCNode *pChild)
{
    CCNode::addChild(pChild);
}

void CCBatchNode::addChild(CCNode *child, int zOrder)
{
    CCNode::addChild(child, zOrder);
}

void CCBatchNode::addChild(CCNode *child, int zOrder, int tag)
{
    CCNode::addChild(child, zOrder, tag);
    CCArmature *armature = dynamic_cast<CCArmature *>(child);
    if (armature != NULL)
    {
        armature->setBatchNode(this);
        
        CCDictionary *dict = armature->getBoneDic();
        CCDictElement *element = NULL;
        CCDICT_FOREACH(dict, element)
        {
            CCBone *bone = static_cast<CCBone*>(element->getObject());
            
            CCArray *displayList = bone->getDisplayManager()->getDecorativeDisplayList();
            CCObject *object = NULL;
            CCARRAY_FOREACH(displayList, object)
            {
                CCDecorativeDisplay *display = static_cast<CCDecorativeDisplay*>(object);
                
                if (CCSkin *skin = dynamic_cast<CCSkin*>(display->getDisplay()))
                {
                    skin->setTextureAtlas(getTexureAtlasWithTexture(skin->getTexture()));
                }
            }
        }
    }
}

void CCBatchNode::removeChild(CCNode* child, bool cleanup)
{
    CCArmature *armature = dynamic_cast<CCArmature *>(child);
    if (armature != NULL)
    {
        armature->setBatchNode(NULL);

        CCDictionary *dict = armature->getBoneDic();
        CCDictElement *element = NULL;
        CCDICT_FOREACH(dict, element)
        {
            CCBone *bone = static_cast<CCBone*>(element->getObject());

            CCArray *displayList = bone->getDisplayManager()->getDecorativeDisplayList();
            CCObject *object = NULL;
            CCARRAY_FOREACH(displayList, object)
            {
                CCDecorativeDisplay *display = static_cast<CCDecorativeDisplay*>(object);

                if (CCSkin *skin = dynamic_cast<CCSkin*>(display->getDisplay()))
                {
                    skin->setTextureAtlas(armature->getTexureAtlasWithTexture(skin->getTexture()));
                }
            }
        }
    }

    CCNode::removeChild(child, cleanup);
}

void CCBatchNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!m_bVisible)
    {
        return;
    }
    kmGLPushMatrix();

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
    }

    transform();
    sortAllChildren();
    draw();

    // reset for next frame
    m_uOrderOfArrival = 0;

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }

    kmGLPopMatrix();
}

void CCBatchNode::draw()
{
    CC_NODE_DRAW_SETUP();
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pChildren, object)
    {
        CCArmature *armature = dynamic_cast<CCArmature *>(object);
        if (armature)
        {
            CCTextureAtlas *atlas = armature->getTextureAtlas();
            if(atlas != m_pAtlas && m_pAtlas)
            {
                m_pAtlas->drawQuads();
                m_pAtlas->removeAllQuads();
            }
            
            armature->visit();
            m_pAtlas = armature->getTextureAtlas();
        }
        else
        {
            ((CCNode *)object)->visit();
        }
    }

    if (m_pAtlas)
    {
        m_pAtlas->drawQuads();
        m_pAtlas->removeAllQuads();
    }
}

CCTextureAtlas *CCBatchNode::getTexureAtlasWithTexture(CCTexture2D *texture)
{
    int key = texture->getName();

    CCTextureAtlas *atlas = (CCTextureAtlas *)m_pTextureAtlasDic->objectForKey(key);
    if (atlas == NULL)
    {
        atlas = CCTextureAtlas::createWithTexture(texture, 4);
        m_pTextureAtlasDic->setObject(atlas, key);
    }
    return atlas;
}

NS_CC_EXT_END
