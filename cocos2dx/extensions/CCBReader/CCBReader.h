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

#define CCB_READER_VERSION 2

NS_CC_EXT_BEGIN

/**
 @brief Parse CCB file which is generated by CocosBuilder
 @warning support CocosBuilder v1 currently. I will update this to v3 when CCB format is stable
 */
class CC_DLL CCBReader : public CCObject 
{        
public:   
    static CCNode* nodeGraphFromFile(const char* ccbFileName, CCNode* owner = NULL);
            
private:
    static CCNode* nodeGraphFromDictionary(CCDictionary* dict, 
                                           CCDictionary* extraProps, 
                                           const char* ccbFilePath, 
                                           CCNode* owner);    
    static CCNode* createCustomClassWithName(CCString* className);
    
    static CCNode* ccObjectFromDictionary(CCDictionary* dict, CCDictionary* extraProps, 
                                          const char* assetsDir, CCNode* owner, CCNode* root);
    
    // read different types of values from dict

    static int intValFromDict(CCDictionary* dict, const std::string key);
    
    static float floatValFromDict(CCDictionary* dict, const std::string key);
    
    static bool boolValFromDict(CCDictionary* dict, const std::string key);
    
    static CCPoint pointValFromDict(CCDictionary* dict, const std::string key);
    
    static CCSize sizeValFromDict(CCDictionary* dict, const std::string key);
    
    static ccColor3B ccColor3ValFromDict(CCDictionary* dict, 
                                                  const std::string key);
    
    static ccColor4F ccColor4fValFromDict(CCDictionary* dict, 
                                                   const std::string key);
    
    static ccBlendFunc blendFuncValFromDict(CCDictionary* dict, 
                                                     const std::string key);
    
private: 
    // set properties

    static void setExtraProp(CCObject* prop, const char* key, int tag, CCDictionary* dict);
    
    static void setPropsForNode(CCNode* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForSprite(CCSprite* node, CCDictionary* props, 
                                  CCDictionary* extraProps);
    
    static void setPropsForLabelBMFont(CCLabelBMFont* node, CCDictionary* props, 
                                       CCDictionary* extraProps);
    
    static void setPropsForParticleSystem(CCParticleSystem* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForMenu(CCMenu* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForMenuItem(CCMenuItem* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForMenuItemImage(CCMenuItemImage* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLayer(CCLayer* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLayerColor(CCLayerColor* node, CCDictionary* props, CCDictionary* extraProps);
    
    static void setPropsForLayerGradient(CCLayerGradient* node, CCDictionary* props, CCDictionary* extraProps);
    
private:
    enum 
    {
        kCCBMemberVarAssignmentTypeNone = 0,
        kCCBMemberVarAssignmentTypeDocumentRoot = 1,
        kCCBMemberVarAssignmentTypeOwner = 2,
    };
    
    enum {
        kInvalidRelativePosition = 0,
        kBottomLeft = 1,
        kBottom = 2,
        kBottomRight = 3,
        kCenterLeft = 4,
        kCenter = 5,
        kCenterRight = 6,
        kTopLeft = 7,
        kTop = 8,
        kTopRight = 9,
    };
}; // end of class CCBReader

NS_CC_EXT_END

#endif // __CCB_READER_H__