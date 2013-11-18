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

#include "cocostudio/CCBatchNode.h"
#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCSkin.h"

using namespace cocos2d;

namespace cocostudio {

BatchNode *BatchNode::create()
{
    BatchNode *batchNode = new BatchNode();
    if (batchNode && batchNode->init())
    {
        batchNode->autorelease();
        return batchNode;
    }
    CC_SAFE_DELETE(batchNode);
    return nullptr;
}

BatchNode::BatchNode()
    : _atlas(nullptr)
    , _textureAtlasDic(nullptr)
{
}

BatchNode::~BatchNode()
{
    CC_SAFE_RELEASE_NULL(_textureAtlasDic);
}

bool BatchNode::init()
{
    bool ret = Node::init();
    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    CC_SAFE_DELETE(_textureAtlasDic);
    _textureAtlasDic = new Dictionary();

    return ret;
}

void BatchNode::addChild(Node *pChild)
{
    Node::addChild(pChild);
}

void BatchNode::addChild(Node *child, int zOrder)
{
    Node::addChild(child, zOrder);
}

void BatchNode::addChild(Node *child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    Armature *armature = dynamic_cast<Armature *>(child);
    if (armature != nullptr)
    {
        armature->setBatchNode(this);

        const Dictionary *dict = armature->getBoneDic();
        DictElement *element = nullptr;
        CCDICT_FOREACH(dict, element)
        {
            Bone *bone = static_cast<Bone*>(element->getObject());

            Array *displayList = bone->getDisplayManager()->getDecorativeDisplayList();
            for(auto object : *displayList)
            {
                DecorativeDisplay *display = static_cast<DecorativeDisplay*>(object);
                                
                if (Skin *skin = dynamic_cast<Skin*>(display->getDisplay()))
                {
                    skin->setTextureAtlas(getTexureAtlasWithTexture(skin->getTexture()));
                }
            }
        }
    }
}

void BatchNode::removeChild(Node* child, bool cleanup)
{
    Armature *armature = dynamic_cast<Armature *>(child);
    if (armature != nullptr)
    {
        armature->setBatchNode(nullptr);
        
        const Dictionary *dict = armature->getBoneDic();
        DictElement *element = nullptr;
        CCDICT_FOREACH(dict, element)
        {
            Bone *bone = static_cast<Bone*>(element->getObject());
            
            Array *displayList = bone->getDisplayManager()->getDecorativeDisplayList();
            for(auto object : *displayList)
            {
                DecorativeDisplay *display = static_cast<DecorativeDisplay*>(object);
                
                if (Skin *skin = dynamic_cast<Skin*>(display->getDisplay()))
                {
                    skin->setTextureAtlas(armature->getTexureAtlasWithTexture(skin->getTexture()));
                }
            }
        }
    }

    Node::removeChild(child, cleanup);
}

void BatchNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    kmGLPushMatrix();

    if (_grid && _grid->isActive())
    {
        _grid->beforeDraw();
    }

    transform();
    sortAllChildren();
    draw();

    // reset for next frame
    _orderOfArrival = 0;

    if (_grid && _grid->isActive())
    {
        _grid->afterDraw(this);
    }

    kmGLPopMatrix();
}

void BatchNode::draw()
{
    if (_children == nullptr)
    {
        return;
    }

    CC_NODE_DRAW_SETUP();

    for(auto object : *_children)
    {
        Armature *armature = dynamic_cast<Armature *>(object);
        if (armature)
        {
            armature->visit();
            _atlas = armature->getTextureAtlas();
        }
        else
        {
            ((Node *)object)->visit();
        }
    }

    if (_atlas)
    {
        _atlas->drawQuads();
        _atlas->removeAllQuads();
    }
}

TextureAtlas *BatchNode::getTexureAtlasWithTexture(Texture2D *texture) const
{
    int key = texture->getName();
    
    TextureAtlas *atlas = static_cast<TextureAtlas *>(_textureAtlasDic->objectForKey(key));
    if (atlas == nullptr)
    {
        atlas = CCTextureAtlas::createWithTexture(texture, 4);
        _textureAtlasDic->setObject(atlas, key);
    }
    return atlas;
}

}
