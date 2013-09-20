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

#include "CCActionManagerEx.h"
#include "../Json/DictionaryHelper.h"

NS_CC_EXT_BEGIN

static ActionManagerEx* sharedActionManager = NULL;

ActionManagerEx* ActionManagerEx::shareManager()
{
    if (!sharedActionManager) {
        sharedActionManager = new ActionManagerEx();
    }
    return sharedActionManager;
}

void ActionManagerEx::purgeActionManager()
{
	CC_SAFE_DELETE(sharedActionManager);
}

ActionManagerEx::ActionManagerEx()
: _pActionDic(NULL)
{
	_pActionDic = Dictionary::create();
    _pActionDic->retain();
}

ActionManagerEx::~ActionManagerEx()
{
	_pActionDic->removeAllObjects();
    _pActionDic->release();
}

void ActionManagerEx::initWithDictionary(const char* jsonName,cs::JsonDictionary *dic,Object* root)
{
	std::string path = jsonName;
	int pos = path.find_last_of("/");
	std::string fileName = path.substr(pos+1,path.length());
	CCLOG("filename == %s",fileName.c_str());
	Array* actionList = Array::create();
	int actionCount = DICTOOL->getArrayCount_json(dic, "actionlist");
    for (int i=0; i<actionCount; i++) {
        ActionObject* action = new ActionObject();
		action->autorelease();
        cs::JsonDictionary* actionDic = DICTOOL->getDictionaryFromArray_json(dic, "actionlist", i);
        action->initWithDictionary(actionDic,root);
        actionList->addObject(action);
		CC_SAFE_DELETE(actionDic);
    }
	_pActionDic->setObject(actionList, fileName);
}


ActionObject* ActionManagerEx::getActionByName(const char* jsonName,const char* actionName)
{
	Array* actionList = (Array*)(_pActionDic->objectForKey(jsonName));
	if (!actionList)
	{
		return NULL;
	}
	for (unsigned int i=0; i<actionList->count(); i++)
	{
		ActionObject* action = dynamic_cast<ActionObject*>(actionList->getObjectAtIndex(i));
		if (strcmp(actionName, action->getName()) == 0)
		{
			return action;
		}
	}
	return NULL;
}

void ActionManagerEx::playActionByName(const char* jsonName,const char* actionName)
{
	ActionObject* action = getActionByName(jsonName,actionName);
	if (action)
	{
		action->play();
	}
}

void ActionManagerEx::releaseActions()
{
    _pActionDic->removeAllObjects();

}

NS_CC_EXT_END