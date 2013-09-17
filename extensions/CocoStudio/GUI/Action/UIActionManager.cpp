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

#include "UIActionManager.h"
#include "../../Json/DictionaryHelper.h"
#include "UIAction.h"

NS_CC_EXT_BEGIN

static UIActionManager* sharedActionManager = NULL;

UIActionManager* UIActionManager::shareManager()
{
    if (!sharedActionManager)
    {
        sharedActionManager = new UIActionManager();
    }
    return sharedActionManager;
}

void UIActionManager::purgeUIActionManager()
{
	CC_SAFE_DELETE(sharedActionManager);
}

UIActionManager::UIActionManager()
{
    m_pActionDic = CCDictionary::create();
    m_pActionDic->retain();
}

UIActionManager::~UIActionManager()
{
    m_pActionDic->removeAllObjects();
    m_pActionDic->release();
}

void UIActionManager::initWithDictionary(const char* jsonName,cs::JsonDictionary *dic,UIWidget* root)
{
    std::string path = jsonName;
    int pos = path.find_last_of("/");
    std::string fileName = path.substr(pos+1,path.length());
    CCLOG("filename == %s",fileName.c_str());
    Array* actionList = Array::create();
    int actionCount = DICTOOL->getArrayCount_json(dic, "actionlist");
    for (int i=0; i<actionCount; i++)
    {
        UIAction* action = new UIAction();
        action->autorelease();
        cs::JsonDictionary* actionDic = DICTOOL->getDictionaryFromArray_json(dic, "actionlist", i);
        action->initWithDictionary(actionDic,root);
        actionList->addObject(action);
		CC_SAFE_DELETE(actionDic);
    }
    m_pActionDic->setObject(actionList, fileName);
}

UIAction* UIActionManager::GetActionByName(const char* jsonName,const char* actionName)
{
    Array* actionList = (Array*)(m_pActionDic->objectForKey(jsonName));
    if (!actionList)
    {
        return NULL;
    }
    for (unsigned int i=0; i<actionList->count(); i++)
    {
        UIAction* action = dynamic_cast<UIAction*>(actionList->getObjectAtIndex(i));
        if (strcmp(actionName, action->getName()) == 0)
        {
            return action;
        }
    }
    return NULL;
}

void UIActionManager::PlayActionByName(const char* jsonName,const char* actionName)
{
    UIAction* action = GetActionByName(jsonName,actionName);
    if (action)
    {
        action->Play();
    }
}

/*temp */
void UIActionManager::releaseActions()
{
    m_pActionDic->removeAllObjects();
}

NS_CC_EXT_END