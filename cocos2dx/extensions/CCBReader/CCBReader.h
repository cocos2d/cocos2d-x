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
#include "CCBCustomClass.h"

NS_CC_EXT_BEGIN

enum {
    kCCBMemberVarAssignmentTypeNone = 0,
    kCCBMemberVarAssignmentTypeDocumentRoot = 1,
    kCCBMemberVarAssignmentTypeOwner = 2,
};    

// 解析ccb类。 
class CCBReader : public cocos2d::CCObject {
        
#pragma mark - read property from dict
public:
    
    static CCScene* sceneWithNodeGraphFromFile(const char* file);
    
    static CCScene* sceneWithNodeGraphFromFile(const char* file, CCNode* owner);

    static CCNode* nodeGraphFromFile(const char* file);
    
    static CCNode* nodeGraphFromFile(const char* file, CCNode* owner);
    
    static CCNode* nodeGraphFromDictionary(CCDictionary*dict) ;

    static CCNode* nodeGraphFromDictionary(CCDictionary* dict, 
                                                    CCNode* owner);
    
#pragma mark -  value from dict
private:
    static int intValFromDict(CCDictionary* dict, const std::string key);
    
    static float floatValFromDict(CCDictionary* dict, const std::string key);
    
    static bool boolValFromDict(CCDictionary* dict, const std::string key);
    
    static CCPoint pointValFromDict(CCDictionary* dict, const std::string key);
    
    static CCSize sizeValFromDict(CCDictionary* dict, const std::string key);
    
    static ccColor3B ccColor3ValFromDict(CCDictionary* dict, 
                                                  const std::string key);
    
    static ccColor4F ccColor4fValFromDict(CCDictionary* dict, 
                                                   const std::string key);
    
    static ccBlendFunc blendFuncValFromDict(cocos2d::CCDictionary* dict, 
                                                     const std::string key);
    
#pragma mark -    setExtraProp
private:    
    static cocos2d::CCNode* createCustomClassWithName(cocos2d::CCString* className);
    
    static cocos2d::CCNode* nodeGraphFromDictionary(cocos2d::CCDictionary* dict, cocos2d::CCDictionary* extraProps, const char* assetsDir, cocos2d::CCNode* owner);
    
    static cocos2d::CCNode* ccObjectFromDictionary(cocos2d::CCDictionary* dict, cocos2d::CCDictionary* extraProps, const char* assetsDir, cocos2d::CCNode* owner);
    
    static cocos2d::CCNode* ccObjectFromDictionary(cocos2d::CCDictionary* dict, cocos2d::CCDictionary* extraProps, const char* assetsDir, cocos2d::CCNode* owner, cocos2d::CCNode* root);
    
    static void setExtraProp(cocos2d::CCObject* prop, const char* key, int tag, cocos2d::CCDictionary* dict);
    
    static void setPropsForNode(cocos2d::CCNode* node, cocos2d::CCDictionary* props, cocos2d::CCDictionary* extraProps);
    
    static void setPropsForSprite(cocos2d::CCSprite* node, cocos2d::CCDictionary* props, 
                                  cocos2d::CCDictionary* extraProps);
    
    static void setPropsForLabelBMFont(cocos2d::CCLabelBMFont* node, cocos2d::CCDictionary* props, 
                                       cocos2d::CCDictionary* extraProps);
    
    static void setPropsForParticleSystem(cocos2d::CCParticleSystem* node, cocos2d::CCDictionary* props, cocos2d::CCDictionary* extraProps);
    
    static void setPropsForMenu(cocos2d::CCMenu* node, cocos2d::CCDictionary* props, 
                                cocos2d::CCDictionary* extraProps);
    
    static void setPropsForMenuItem(cocos2d::CCMenuItem* node, cocos2d::CCDictionary* props, 
                                    cocos2d::CCDictionary* extraProps);
    
    static void setPropsForMenuItemImage(cocos2d::CCMenuItemImage* node, cocos2d::CCDictionary* props, 
                                         cocos2d::CCDictionary* extraProps);
    
    static void setPropsForLayer(cocos2d::CCLayer* node, cocos2d::CCDictionary* props, 
                                 cocos2d::CCDictionary* extraProps);
    
    static void setPropsForLayerColor(cocos2d::CCLayerColor* node, cocos2d::CCDictionary* props, 
                                      cocos2d::CCDictionary* extraProps);
    
    static void setPropsForLayerGradient(cocos2d::CCLayerGradient* node, cocos2d::CCDictionary* props, 
                                         cocos2d::CCDictionary* extraProps);
}; // end of class CCBReader

NS_CC_EXT_END

#endif // __CCB_READER_H__