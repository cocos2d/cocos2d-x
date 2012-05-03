/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2012 XiaoLong Zhang, Chukong Inc.
 
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


#ifndef __CCB_READER_H__
#define __CCB_READER_H__

#include "cocos2d.h"
#include "CObject.h"

namespace cocos2d{

enum {
    kCCBMemberVarAssignmentTypeNone = 0,
    kCCBMemberVarAssignmentTypeDocumentRoot = 1,
    kCCBMemberVarAssignmentTypeOwner = 2,
};    

// 解析ccb类。 
class CCBReader : public CCObject {
    
#pragma mark -  init  
public:
    // CCBReader();
    // virtual ~CCBReader();
    // static CCBReader* sharedCCBReader() ;
    // static void dispose();
    
#pragma mark - read property from dict
public:
    
    static CCScene* sceneWithNodeGraphFromFile(const char* file);
    
    static CCScene* sceneWithNodeGraphFromFile(const char* file, CCObject* owner);

    static CCNode* nodeGraphFromFile(const char* file);
    
    static CCNode* nodeGraphFromFile(const char* file, CCObject* owner);
    
    static CCNode* nodeGraphFromDictionary(CCDictionary*dict) ;

    static CCNode* nodeGraphFromDictionary(CCDictionary* dict, CCObject* owner);
    
#pragma mark -  value from dict
private:
    static int intValFromDict(CCDictionary* dict, const std::string key);
    
    static float floatValFromDict(CCDictionary* dict, const std::string key);
    
    static bool boolValFromDict(CCDictionary* dict, const std::string key);
    
    static CCPoint pointValFromDict(CCDictionary* dict, const std::string key);
    
    static CCSize sizeValFromDict(CCDictionary* dict, const std::string key);
    
    static ccColor3B ccColor3ValFromDict(CCDictionary* dict, const std::string key);
    
    static ccColor4F ccColor4fValFromDict(CCDictionary* dict, const std::string key);
    
    static ccBlendFunc blendFuncValFromDict(CCDictionary* dict, const std::string key);
    
#pragma mark -    setExtraProp
private:    
    static CCNode* createCustomClassWithName(CCString* className);
    
    static CCNode* nodeGraphFromDictionary(CCDictionary* dict, CCDictionary* extraProps, const char* assetsDir, CCObject* owner);
    
    static CCNode* ccObjectFromDictionary(CCDictionary* dict, CCDictionary* extraProps, const char* assetsDir, CCObject* owner);
    
    static CCNode* ccObjectFromDictionary(CCDictionary* dict, CCDictionary* extraProps, const char* assetsDir, CCObject* owner, CObject* root);
    
    static void setExtraProp(CCObject* prop, const char* key, int tag, CCDictionary* dict);
    
    static void setPropsForNode(CCNode* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForSprite(CCSprite* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLabelBMFont(CCLabelBMFont* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForParticleSystem(CCParticleSystem* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForMenu(CCMenu* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForMenuItem(CCMenuItem* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForMenuItemImage(CCMenuItemImage* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLayer(CCLayer* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLayerColor(CCLayerColor* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLayerGradient(CCLayerGradient* node, CCDictionary* props, CCDictionary* extraProps);
    
/*    
#pragma mark -  point
private:
    static CCBReader* static_bReader;
 */
};

} // end of namespace cocos2d

#endif // __CCB_READER_H__