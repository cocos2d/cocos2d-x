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

#ifndef __CCBATCHNODE_H__
#define __CCBATCHNODE_H__

#include "cocostudio/CCArmatureDefine.h"

namespace cocostudio {

class BatchNode : public cocos2d::Node
{
public:
    static BatchNode *create();
public:
	/**
     * @js ctor
     */
    BatchNode();
    ~BatchNode();

    virtual bool init();
    virtual void addChild(cocos2d::Node *pChild);
    virtual void addChild(cocos2d::Node *pChild, int zOrder);
    virtual void addChild(cocos2d::Node *pChild, int zOrder, int tag);
    virtual void removeChild(cocos2d::Node* child, bool cleanup);
    virtual void visit();
    void draw();

    virtual cocos2d::TextureAtlas *getTexureAtlasWithTexture(cocos2d::Texture2D *texture);
protected:
    cocos2d::TextureAtlas *_atlas;
    cocos2d::Dictionary *_textureAtlasDic;
};

}

#endif /*__CCBATCHNODE_H__*/
