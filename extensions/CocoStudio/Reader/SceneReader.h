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

#ifndef __SceneReader_H__
#define __SceneReader_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"
#include "../Json/CocoLoader.h"

NS_CC_EXT_BEGIN


typedef void (CCObject::*SEL_CallFuncOD)(CCObject*, void*);
#define callfuncOD_selector(_SELECTOR) (SEL_CallFuncOD)(&_SELECTOR)

typedef enum {
    ///parent: Empty Node
    ///            ComRender(Sprite, Armature, TMXTiledMap, ParticleSystemQuad, GUIComponent)
    ///            ComAttribute
    ///            ComAudio
    ///            ....
    ATTACH_EMPTY_NODE,

    ///parent:   ComRender(Sprite, Armature, TMXTiledMap, ParticleSystemQuad, GUIComponent)
    ///          ComAttribute
    ///          ComAudio
    ///          .....
    ATTACH_RENDER_NODE,

    /// Default AttachComponentType is _EmptyNode
    DEFAULT = ATTACH_EMPTY_NODE,
} AttachComponentType;

/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL SceneReader
{

public:
	static SceneReader* sharedSceneReader();
	static void purge();
	static const char* sceneReaderVersion();
	cocos2d::CCNode* createNodeWithSceneFile(const char *pszFileName, AttachComponentType eAttachComponent = ATTACH_EMPTY_NODE);

	static void setTarget(CCObject *rec, SEL_CallFuncOD selector);
	cocos2d::CCNode* getNodeByTag(int nTag);
    inline AttachComponentType getAttachComponentType(){return _eAttachComponent;}

public:
    SceneReader(void);
    virtual ~SceneReader(void);

private:
    cocos2d::CCNode* createObject(const rapidjson::Value &root, cocos2d::CCNode* parent, AttachComponentType eAttachComponent);
    void setPropertyFromJsonDict(const rapidjson::Value &root, cocos2d::CCNode *node);
    bool readJson(const char *pszFileName, rapidjson::Document &doc);

	cocos2d::CCNode* createObject(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, cocos2d::CCNode* parent, AttachComponentType eAttachComponent);
	void setPropertyFromJsonDict(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, cocos2d::CCNode *node);

	cocos2d::CCNode* nodeByTag(cocos2d::CCNode *pParent, int nTag);
private:
	static SceneReader* _sharedReader;
	static CCObject*       _pListener;
	static SEL_CallFuncOD  _pfnSelector;
	cocos2d::CCNode *_pNode;
	AttachComponentType _eAttachComponent;
};


NS_CC_EXT_END

#endif
