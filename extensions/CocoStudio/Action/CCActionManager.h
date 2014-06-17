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

#ifndef __ActionMANAGER_H__
#define __ActionMANAGER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCActionObject.h"
#include "../Json/rapidjson/document.h"
NS_CC_EXT_BEGIN

class CocoLoader;
struct stExpCocoNode;
	/**
	*   @js NA
	*   @lua NA
	*/
class CC_EX_DLL ActionManager:public CCObject
{
public:

	/**
	* Default constructor
	* @js ctor
	*/
	ActionManager();

	/**
	* Default destructor
	* @js NA
	*/
	virtual ~ActionManager();

	/**
	* Gets the static instance of ActionManager.
	*/
	static ActionManager* shareManager();

	/**
	* Purges ActionManager point.
	*/
	static void purge();

	/**
	* Gets an ActionObject with a name.
	*
	* @param jsonName  UI file name
	*
	* @param actionName  action name in the UI file.
	*
	* @return  ActionObject which named as the param name
	*/
	ActionObject* getActionByName(const char* jsonName,const char* actionName);

	/**
	* Play an Action with a name.
	*
	* @param jsonName  UI file name
	*
	* @param actionName  action name in teh UIfile.
	*/
	ActionObject* playActionByName(const char* jsonName,const char* actionName);

	/**
	* Play an Action with a name.
	*
	* @param jsonName  UI file name
	*
	* @param actionName  action name in teh UIfile.
	*
	* @param func ui action call back
	*/
	ActionObject* playActionByName(const char* jsonName,const char* actionName, CCCallFunc* func);

	/*init properties with json dictionay*/
	void initWithDictionary(const char* jsonName,const rapidjson::Value &dic,CCObject* root);
    void initWithBinary(const char* file, CCObject* root,  CocoLoader* pCocoLoader, stExpCocoNode*	pCocoNode);
	/**
	* Release all actions.
	*
	*/
	void releaseActions();

protected:
	CCDictionary* m_pActionDic;
};

NS_CC_EXT_END

#endif
