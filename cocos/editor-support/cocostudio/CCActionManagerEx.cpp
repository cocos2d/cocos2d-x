/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "cocostudio/CCActionManagerEx.h"
#include "cocostudio/DictionaryHelper.h"

using namespace cocos2d;

namespace cocostudio {

static ActionManagerEx* sharedActionManager = nullptr;

ActionManagerEx* ActionManagerEx::getInstance()
{
	if (!sharedActionManager) {
		sharedActionManager = new ActionManagerEx();
	}
	return sharedActionManager;
}

void ActionManagerEx::destroyInstance()
{
	CC_SAFE_DELETE(sharedActionManager);
}

ActionManagerEx::ActionManagerEx()
{
}

ActionManagerEx::~ActionManagerEx()
{
	_actionDic.clear();
}

void ActionManagerEx::initWithDictionary(const char* jsonName,const rapidjson::Value &dic,Object* root)
{
	std::string path = jsonName;
	ssize_t pos = path.find_last_of("/");
	std::string fileName = path.substr(pos+1,path.length());
	CCLOG("filename == %s",fileName.c_str());
	cocos2d::Vector<ActionObject*> actionList;
	int actionCount = DICTOOL->getArrayCount_json(dic, "actionlist");
	for (int i=0; i<actionCount; i++) {
		ActionObject* action = new ActionObject();
		action->autorelease();
		const rapidjson::Value &actionDic = DICTOOL->getDictionaryFromArray_json(dic, "actionlist", i);
		action->initWithDictionary(actionDic,root);
		actionList.pushBack(action);
	}
	_actionDic.insert(std::pair<std::string, cocos2d::Vector<ActionObject*>>(fileName, actionList));
}


ActionObject* ActionManagerEx::getActionByName(const char* jsonName,const char* actionName)
{
	auto iterator = _actionDic.find(jsonName);
	if (iterator == _actionDic.end())
	{
		return nullptr;
	}
	auto actionList = iterator->second;
	for (int i = 0; i < actionList.size(); i++)
	{
		ActionObject* action = actionList.at(i);
		if (strcmp(actionName, action->getName()) == 0)
		{
			return action;
		}
	}
	return nullptr;
}

ActionObject* ActionManagerEx::playActionByName(const char* jsonName,const char* actionName)
{
	ActionObject* action = getActionByName(jsonName,actionName);
	if (action)
	{
		action->play();
	}
	return action;
}

ActionObject* ActionManagerEx::playActionByName(const char* jsonName,const char* actionName, CallFunc* func)
{
	ActionObject* action = getActionByName(jsonName,actionName);
	if (action)
	{
		action->play(func);
	}
	return action;
}

void ActionManagerEx::releaseActions()
{
	_actionDic.clear();
}

}